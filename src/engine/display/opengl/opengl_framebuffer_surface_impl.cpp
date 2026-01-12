// src/engine/display/opengl/opengl_framebuffer_surface_impl.cpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 2008 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#include "engine/display/opengl/opengl_framebuffer_surface_impl.hpp"

#include <assert.h>
#include <algorithm>
#include "util/log.hpp"

namespace {

// Set max texture size to 1024.
// This is the hardware limit for the Wii (Hollywood GPU).
// It is also a safe limit for older Desktop hardware (ATI Rage 128, early Intel).
const int MAX_TEXTURE_SIZE = 1024;

#ifdef __WII__
inline int get_texture_size(int val)
{
  // Wii optimization: Align to 4 bytes instead of full POT to save RAM
  return (val + 3) & ~3;
}
#else
inline int get_texture_size(int val)
{
  // Desktop OpenGL 1.x requires Power-Of-Two textures
  int result = 1;
  while(result < val)
    result *= 2;
  return result;
}
#endif

} // namespace

OpenGLFramebufferSurfaceImpl::OpenGLFramebufferSurfaceImpl(SDL_Surface* src) :
  m_tiles(),
  m_size(src->w, src->h)
{
  // Split the surface into tiles if it exceeds MAX_TEXTURE_SIZE
  for (int y = 0; y < src->h; y += MAX_TEXTURE_SIZE)
  {
    for (int x = 0; x < src->w; x += MAX_TEXTURE_SIZE)
    {
      int w = std::min(src->w - x, MAX_TEXTURE_SIZE);
      int h = std::min(src->h - y, MAX_TEXTURE_SIZE);

      OpenGLTile tile;
      tile.rect = Rect(x, y, x + w, y + h);
      tile.texture_size.width  = get_texture_size(w);
      tile.texture_size.height = get_texture_size(h);

      glGenTextures(1, &tile.handle);

      // Determine format
      // Check for BOTH per-pixel alpha AND colorkey transparency
      bool has_alpha = (src->format->Amask != 0) || (src->flags & SDL_SRCCOLORKEY);

      GLenum gl_format = GL_RGBA;
      GLenum gl_type = GL_UNSIGNED_BYTE;
      int bpp = 32;
      Uint32 rmask, gmask, bmask, amask;

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
      rmask = 0xff000000; gmask = 0x00ff0000; bmask = 0x0000ff00; amask = 0x000000ff;
#else
      rmask = 0x000000ff; gmask = 0x0000ff00; bmask = 0x00ff0000; amask = 0xff000000;
#endif

#ifdef __WII__
      // On Wii, use 16-bit RGB565 for opaque textures to save RAM
      // Only do this if there is absolutely NO transparency
      if (!has_alpha)
      {
        bpp = 16;
        rmask = 0xF800; gmask = 0x07E0; bmask = 0x001F; amask = 0x0000;
        gl_format = GL_RGB;
        gl_type = GL_UNSIGNED_SHORT_5_6_5;
      }
#endif

      // Create a temporary surface for the tile
      SDL_Surface* convert = SDL_CreateRGBSurface(SDL_SWSURFACE,
                                                  tile.texture_size.width,
                                                  tile.texture_size.height,
                                                  bpp, rmask, gmask, bmask, amask);

      if (!convert) {
        log_error("Failed to create surface for texture upload");
        continue;
      }

      // CRITICAL: Clear the surface to transparent black (0)
      // This ensures that:
      // 1. Padding pixels (if texture_size > w/h) are transparent/black.
      // 2. Colorkey pixels (which are skipped during blit) remain transparent.
      SDL_FillRect(convert, NULL, 0);

      // Blit the specific chunk of the source image to the convert surface
      SDL_Rect src_rect = { (Sint16)x, (Sint16)y, (Uint16)w, (Uint16)h };
      SDL_Rect dst_rect = { 0, 0, (Uint16)w, (Uint16)h };

      // Save alpha settings (SDL 1.2 style)
      Uint8 saved_alpha = src->format->alpha;
      Uint32 saved_flags = src->flags & (SDL_SRCALPHA | SDL_RLEACCEL);

      // Disable per-surface alpha blending for the copy so we get raw pixel data.
      // Note: This does NOT disable Colorkeying. SDL_BlitSurface respects colorkey
      // even if Alpha is disabled.
      SDL_SetAlpha(src, 0, 0);

      SDL_BlitSurface(src, &src_rect, convert, &dst_rect);

      // Restore alpha settings
      if (src->format->Amask != 0) {
        SDL_SetAlpha(src, saved_flags, saved_alpha);
      }

      glBindTexture(GL_TEXTURE_2D, tile.handle);

      // Critical fix for "garbage" graphics: Tell GL about row alignment
      glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
      glPixelStorei(GL_UNPACK_ROW_LENGTH, convert->pitch / convert->format->BytesPerPixel);

      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

      // Clamp to edge to prevent artifacts at tile seams
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

      SDL_LockSurface(convert);
      glTexImage2D(GL_TEXTURE_2D, 0, gl_format,
                   tile.texture_size.width, tile.texture_size.height, 0,
                   gl_format, gl_type, convert->pixels);
      SDL_UnlockSurface(convert);

      glPixelStorei(GL_UNPACK_ROW_LENGTH, 0); // Reset state
      SDL_FreeSurface(convert);

      m_tiles.push_back(tile);
    }
  }

  glBindTexture(GL_TEXTURE_2D, 0);
}

OpenGLFramebufferSurfaceImpl::~OpenGLFramebufferSurfaceImpl()
{
  for (std::vector<OpenGLTile>::iterator i = m_tiles.begin(); i != m_tiles.end(); ++i)
  {
    glDeleteTextures(1, &i->handle);
  }
}

// EOF
