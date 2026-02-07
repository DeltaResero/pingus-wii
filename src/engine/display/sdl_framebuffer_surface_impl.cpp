// src/engine/display/sdl_framebuffer_surface_impl.cpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 2008 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#include "engine/display/sdl_framebuffer_surface_impl.hpp"

namespace pingus {


SDLFramebufferSurfaceImpl::SDLFramebufferSurfaceImpl(SDL_Surface* src) :
  surface()
{
  if (src->format->Amask != 0 || (src->flags & SDL_SRCCOLORKEY))
    surface = SDL_DisplayFormatAlpha(src);
  else
    surface = SDL_DisplayFormat(src);
}

SDLFramebufferSurfaceImpl::~SDLFramebufferSurfaceImpl()
{
  SDL_FreeSurface(surface);
}


} // namespace pingus

// EOF
