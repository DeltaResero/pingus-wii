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

#include <sstream>
#include <stdexcept>

#include "engine/display/opengl/opengl_framebuffer_surface_impl.hpp"

OpenGLFramebuffer::OpenGLFramebuffer() :
  screen(),
  cliprect_stack()
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

  glOrtho(0, screen->w, screen->h, 0, -1, 1);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
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
    cliprect_stack.push_back(Rect(Math::max(cliprect_stack.back().left,   rect.left),
                                  Math::max(cliprect_stack.back().top,    rect.top),
                                  Math::min(cliprect_stack.back().right,  rect.right),
                                  Math::min(cliprect_stack.back().bottom, rect.bottom)));
  }

  glScissor(cliprect_stack.back().left,
            screen->h - cliprect_stack.back().bottom,
            cliprect_stack.back().get_width(),
            cliprect_stack.back().get_height());
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
    const Rect& rect = cliprect_stack.back();
    glScissor(rect.left,        rect.top,
              rect.get_width(), rect.get_height());
  }
}

void
OpenGLFramebuffer::draw_surface(const FramebufferSurface& src, const Vector2i& pos)
{
  draw_surface(src, Rect(Vector2i(0, 0), src.get_size()),  pos);
}

void
OpenGLFramebuffer::draw_surface(const FramebufferSurface& src, const Rect& srcrect, const Vector2i& pos)
{
  const OpenGLFramebufferSurfaceImpl* impl = static_cast<OpenGLFramebufferSurfaceImpl*>(src.get_impl());
  const std::vector<OpenGLTile>& tiles = impl->get_tiles();

  // Iterate over all tiles that make up this surface
  for (const auto& tile : tiles)
  {
    // Calculate intersection between the requested source rect and this tile's area
    Rect intersection = srcrect;
    intersection.left   = Math::max(srcrect.left,   tile.rect.left);
    intersection.top    = Math::max(srcrect.top,    tile.rect.top);
    intersection.right  = Math::min(srcrect.right,  tile.rect.right);
    intersection.bottom = Math::min(srcrect.bottom, tile.rect.bottom);

    // If this tile is not visible in the requested rect, skip it
    if (intersection.left >= intersection.right || intersection.top >= intersection.bottom)
      continue;

    // Calculate draw position on screen
    int draw_x = pos.x + (intersection.left - srcrect.left);
    int draw_y = pos.y + (intersection.top  - srcrect.top);

    // Calculate UV coordinates relative to the tile's texture
    // Note: tile.rect.left/top is the offset of the tile in the original image
    float u1 = static_cast<float>(intersection.left - tile.rect.left) / static_cast<float>(tile.texture_size.width);
    float v1 = static_cast<float>(intersection.top  - tile.rect.top)  / static_cast<float>(tile.texture_size.height);
    float u2 = static_cast<float>(intersection.right - tile.rect.left) / static_cast<float>(tile.texture_size.width);
    float v2 = static_cast<float>(intersection.bottom - tile.rect.top) / static_cast<float>(tile.texture_size.height);

    glBindTexture(GL_TEXTURE_2D, tile.handle);

    int vertices[] = {
      draw_x,                                   draw_y,
      draw_x + intersection.get_width(),        draw_y,
      draw_x + intersection.get_width(),        draw_y + intersection.get_height(),
      draw_x,                                   draw_y + intersection.get_height(),
    };
    glVertexPointer(2, GL_INT, 0, vertices);

    float uvs[] = {
      u1, v1,
      u2, v1,
      u2, v2,
      u1, v2
    };

    glTexCoordPointer(2, GL_FLOAT, 0, uvs);

    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
  }

  glBindTexture(GL_TEXTURE_2D, 0);
}

void
OpenGLFramebuffer::draw_line(const Vector2i& pos1, const Vector2i& pos2, const Color& color)
{
  glDisable(GL_TEXTURE_2D);
  glColor4ub(color.r, color.g, color.b, color.a);
  glDisableClientState(GL_TEXTURE_COORD_ARRAY);

  int vertices[] = {
    pos1.x, pos1.y,
    pos2.x, pos2.y,
  };
  glVertexPointer(2, GL_INT, 0, vertices);

  glDrawArrays(GL_LINES, 0, 2);

  glEnableClientState(GL_TEXTURE_COORD_ARRAY);
  glEnable(GL_TEXTURE_2D);
  glColor4f(1, 1, 1, 1);
}

void
OpenGLFramebuffer::draw_rect(const Rect& rect, const Color& color)
{
  glDisable(GL_TEXTURE_2D);
  glColor4ub(color.r, color.g, color.b, color.a);
  glDisableClientState(GL_TEXTURE_COORD_ARRAY);

  int vertices[] = {
    rect.left,  rect.top,
    rect.right, rect.top,
    rect.right, rect.bottom,
    rect.left,  rect.bottom,
  };
  glVertexPointer(2, GL_INT, 0, vertices);

  glDrawArrays(GL_LINE_LOOP, 0, 4);

  glEnableClientState(GL_TEXTURE_COORD_ARRAY);
  glEnable(GL_TEXTURE_2D);
  glColor4f(1, 1, 1, 1);
}

void
OpenGLFramebuffer::fill_rect(const Rect& rect, const Color& color)
{
  glDisable(GL_TEXTURE_2D);
  glColor4ub(color.r, color.g, color.b, color.a);
  glDisableClientState(GL_TEXTURE_COORD_ARRAY);

  int vertices[] = {
    rect.left,  rect.top,
    rect.right, rect.top,
    rect.right, rect.bottom,
    rect.left,  rect.bottom,
  };
  glVertexPointer(2, GL_INT, 0, vertices);

  glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

  glEnableClientState(GL_TEXTURE_COORD_ARRAY);
  glEnable(GL_TEXTURE_2D);
  glColor4f(1, 1, 1, 1);
}

Size
OpenGLFramebuffer::get_size() const
{
  return Size(screen->w, screen->h);
}

// EOF
