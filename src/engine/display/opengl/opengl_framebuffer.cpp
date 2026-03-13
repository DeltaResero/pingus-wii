// src/engine/display/opengl/opengl_framebuffer.cpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 2008 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#include "engine/display/opengl/opengl_framebuffer.hpp"

#include <algorithm>
#include <sstream>
#include <stdexcept>

#include "engine/display/display.hpp"
#include "engine/display/opengl/opengl_framebuffer_surface_impl.hpp"

namespace pingus {


OpenGLFramebuffer::OpenGLFramebuffer() :
  screen(),
  cliprect_stack(),
  m_last_texture_id(0),
  m_texture_enabled(false),
  m_texcoord_array_enabled(false)
{
}

FramebufferSurface
OpenGLFramebuffer::create_surface(const Surface& surface)
{
  return FramebufferSurface(new OpenGLFramebufferSurfaceImpl(surface.get_surface()));
}

void
OpenGLFramebuffer::set_video_mode(const Size& size, bool fullscreen, bool resizable)
{
  int flags = SDL_OPENGL;

#ifdef __WII__
  // Wii Specific OpenGL (OpenGX) setup
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
  SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 0);
  flags |= SDL_FULLSCREEN;
#endif

  if (fullscreen)
  {
    flags |= SDL_FULLSCREEN;
  }
  else if (resizable)
  {
    flags |= SDL_RESIZABLE;
  }

  int width = size.width;
  int height = size.height;
  int bpp = 0; // auto-detect

  screen = SDL_SetVideoMode(width, height, bpp, flags);

  if(screen == 0)
  {
    std::ostringstream msg;
    msg << "Couldn't set video mode (" << width << "x" << height
        << "-" << bpp << "bpp): " << SDL_GetError();
    throw std::runtime_error(msg.str());
  }

  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);

  // setup opengl state and transform
  glDisable(GL_DEPTH_TEST);
  glDisable(GL_CULL_FACE);
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  // Fix for texture corruption (garbage) on some drivers/platforms
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

  glViewport(0, 0, screen->w, screen->h);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  glOrtho(0, Display::LOGICAL_WIDTH, Display::LOGICAL_HEIGHT, 0, -1, 1);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  // Reset state cache to match what we just set
  m_last_texture_id = 0;
  m_texture_enabled = true;
  m_texcoord_array_enabled = true;
}

bool
OpenGLFramebuffer::is_fullscreen() const
{
  return screen->flags & SDL_FULLSCREEN;
}

bool
OpenGLFramebuffer::is_resizable() const
{
  return screen->flags & SDL_RESIZABLE;
}

void
OpenGLFramebuffer::flip()
{
  SDL_GL_SwapBuffers();
}

void
OpenGLFramebuffer::push_cliprect(const Rect& rect)
{
  if (cliprect_stack.empty())
    glEnable(GL_SCISSOR_TEST);

  if (cliprect_stack.empty())
  {
    cliprect_stack.push_back(rect);
  }
  else
  {
    cliprect_stack.push_back(Rect(std::max(cliprect_stack.back().left,   rect.left),
                                  std::max(cliprect_stack.back().top,    rect.top),
                                  std::min(cliprect_stack.back().right,  rect.right),
                                  std::min(cliprect_stack.back().bottom, rect.bottom)));
  }

  {
    // Scale logical cliprect coords to physical pixel coords for glScissor.
    // glScissor operates in physical pixels; cliprects are in logical space.
    const float sx = static_cast<float>(screen->w) / Display::LOGICAL_WIDTH;
    const float sy = static_cast<float>(screen->h) / Display::LOGICAL_HEIGHT;
    const Rect& cr = cliprect_stack.back();
    glScissor(static_cast<int>(cr.left   * sx),
              static_cast<int>(screen->h - cr.bottom * sy),
              static_cast<int>(cr.get_width()  * sx),
              static_cast<int>(cr.get_height() * sy));
  }
}

void
OpenGLFramebuffer::pop_cliprect()
{
  cliprect_stack.pop_back();

  if (cliprect_stack.empty())
  {
    glDisable(GL_SCISSOR_TEST);
  }
  else
  {
    {
      // Scale logical cliprect coords to physical pixel coords for glScissor.
      const float sx = static_cast<float>(screen->w) / Display::LOGICAL_WIDTH;
      const float sy = static_cast<float>(screen->h) / Display::LOGICAL_HEIGHT;
      const Rect& rect = cliprect_stack.back();
      glScissor(static_cast<int>(rect.left   * sx),
                static_cast<int>(screen->h - rect.bottom * sy),
                static_cast<int>(rect.get_width()  * sx),
                static_cast<int>(rect.get_height() * sy));
    }
  }
}

void
OpenGLFramebuffer::draw_surface(const FramebufferSurface& src, Vector2i pos)
{
  draw_surface(src, Rect(Vector2i(0, 0), src.get_size()),  pos);
}

void
OpenGLFramebuffer::draw_surface(const FramebufferSurface& src, const Rect& srcrect, Vector2i pos)
{
  // Ensure texture rendering is enabled
  if (!m_texture_enabled)
  {
    glEnable(GL_TEXTURE_2D);
    m_texture_enabled = true;
  }

  if (!m_texcoord_array_enabled)
  {
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    m_texcoord_array_enabled = true;
  }

  // Reset color to white (in case previous draw_line/draw_rect changed it)
  glColor4f(1, 1, 1, 1);

  const OpenGLFramebufferSurfaceImpl* impl = static_cast<OpenGLFramebufferSurfaceImpl*>(src.get_impl());
  const std::vector<OpenGLTile>& tiles = impl->get_tiles();

  // Iterate over all tiles that make up this surface
  for (const auto& tile : tiles)
  {
    // Calculate intersection between the requested source rect and this tile's area
    Rect intersection = srcrect;
    intersection.left   = std::max(srcrect.left,   tile.rect.left);
    intersection.top    = std::max(srcrect.top,    tile.rect.top);
    intersection.right  = std::min(srcrect.right,  tile.rect.right);
    intersection.bottom = std::min(srcrect.bottom, tile.rect.bottom);

    // If this tile is not visible in the requested rect, skip it
    if (intersection.left >= intersection.right || intersection.top >= intersection.bottom)
      continue;

    // Calculate draw position on screen
    int draw_x = pos.x + (intersection.left - srcrect.left);
    int draw_y = pos.y + (intersection.top  - srcrect.top);
    int draw_width = intersection.get_width();
    int draw_height = intersection.get_height();

    // Calculate UV coordinates from tile-local pixel offsets.
    float u1 = static_cast<float>(intersection.left   - tile.rect.left) * tile.u_scale;
    float v1 = static_cast<float>(intersection.top    - tile.rect.top)  * tile.v_scale;
    float u2 = static_cast<float>(intersection.right  - tile.rect.left) * tile.u_scale;
    float v2 = static_cast<float>(intersection.bottom - tile.rect.top)  * tile.v_scale;

    // Unconditionally inset UVs by 0.5 texels at tile boundaries.
    // GL_CLAMP_TO_EDGE is unreliable on some platforms (like Wii GX) and can
    // blend with the border color at u/v = 0.0 or 1.0. Insetting forces
    // GL_LINEAR to sample the exact center of the edge pixels, preventing seams.
    if (intersection.left   == tile.rect.left)   u1 += 0.5f * tile.u_scale;
    if (intersection.top    == tile.rect.top)    v1 += 0.5f * tile.v_scale;
    if (intersection.right  == tile.rect.right)  u2 -= 0.5f * tile.u_scale;
    if (intersection.bottom == tile.rect.bottom) v2 -= 0.5f * tile.v_scale;

    // Only bind texture if it's different from the last one
    if (m_last_texture_id != tile.handle)
    {
      glBindTexture(GL_TEXTURE_2D, tile.handle);
      m_last_texture_id = tile.handle;
    }

    GLfloat vertices[] = {
      static_cast<GLfloat>(draw_x),              static_cast<GLfloat>(draw_y),
      static_cast<GLfloat>(draw_x + draw_width), static_cast<GLfloat>(draw_y),
      static_cast<GLfloat>(draw_x + draw_width), static_cast<GLfloat>(draw_y + draw_height),
      static_cast<GLfloat>(draw_x),              static_cast<GLfloat>(draw_y + draw_height),
    };
    glVertexPointer(2, GL_FLOAT, 0, vertices);

    float uvs[] = {
      u1, v1,
      u2, v1,
      u2, v2,
      u1, v2
    };

    glTexCoordPointer(2, GL_FLOAT, 0, uvs);

    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
  }
}

void
OpenGLFramebuffer::draw_line(Vector2i pos1, Vector2i pos2, Color color)
{
  // Disable texturing if currently enabled
  if (m_texture_enabled)
  {
    glDisable(GL_TEXTURE_2D);
    m_texture_enabled = false;
  }

  // Disable texture coordinate array if currently enabled
  if (m_texcoord_array_enabled)
  {
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    m_texcoord_array_enabled = false;
  }

  glColor4ub(color.r, color.g, color.b, color.a);

  GLfloat vertices[] = {
    static_cast<GLfloat>(pos1.x), static_cast<GLfloat>(pos1.y),
    static_cast<GLfloat>(pos2.x), static_cast<GLfloat>(pos2.y),
  };
  glVertexPointer(2, GL_FLOAT, 0, vertices);

  glDrawArrays(GL_LINES, 0, 2);
}

void
OpenGLFramebuffer::draw_rect(const Rect& rect, Color color)
{
  // Disable texturing if currently enabled
  if (m_texture_enabled)
  {
    glDisable(GL_TEXTURE_2D);
    m_texture_enabled = false;
  }

  // Disable texture coordinate array if currently enabled
  if (m_texcoord_array_enabled)
  {
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    m_texcoord_array_enabled = false;
  }

  glColor4ub(color.r, color.g, color.b, color.a);

  GLfloat vertices[] = {
    static_cast<GLfloat>(rect.left),  static_cast<GLfloat>(rect.top),
    static_cast<GLfloat>(rect.right), static_cast<GLfloat>(rect.top),
    static_cast<GLfloat>(rect.right), static_cast<GLfloat>(rect.bottom),
    static_cast<GLfloat>(rect.left),  static_cast<GLfloat>(rect.bottom),
  };
  glVertexPointer(2, GL_FLOAT, 0, vertices);

  glDrawArrays(GL_LINE_LOOP, 0, 4);
}

void
OpenGLFramebuffer::fill_rect(const Rect& rect, Color color)
{
  // Disable texturing if currently enabled
  if (m_texture_enabled)
  {
    glDisable(GL_TEXTURE_2D);
    m_texture_enabled = false;
  }

  // Disable texture coordinate array if currently enabled
  if (m_texcoord_array_enabled)
  {
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    m_texcoord_array_enabled = false;
  }

  glColor4ub(color.r, color.g, color.b, color.a);

  GLfloat vertices[] = {
    static_cast<GLfloat>(rect.left),  static_cast<GLfloat>(rect.top),
    static_cast<GLfloat>(rect.right), static_cast<GLfloat>(rect.top),
    static_cast<GLfloat>(rect.right), static_cast<GLfloat>(rect.bottom),
    static_cast<GLfloat>(rect.left),  static_cast<GLfloat>(rect.bottom),
  };
  glVertexPointer(2, GL_FLOAT, 0, vertices);

  glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

Size
OpenGLFramebuffer::get_size() const
{
  return Size(screen->w, screen->h);
}

void
OpenGLFramebuffer::invalidate_state()
{
  glDisable(GL_TEXTURE_2D);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glDisableClientState(GL_TEXTURE_COORD_ARRAY);
  glEnableClientState(GL_VERTEX_ARRAY);

  m_last_texture_id = 0;
  m_texture_enabled = false;
  m_texcoord_array_enabled = false;
}


} // namespace pingus

// EOF
