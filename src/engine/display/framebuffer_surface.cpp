// src/engine/display/framebuffer_surface.cpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 2008 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#include "engine/display/framebuffer_surface.hpp"

FramebufferSurface::FramebufferSurface() :
  impl()
{
}

FramebufferSurface::FramebufferSurface(FramebufferSurfaceImpl* impl_) :
  impl(impl_)
{
}

FramebufferSurface::~FramebufferSurface()
{
}

int
FramebufferSurface::get_width()  const
{
  if (impl.get())
    return impl->get_width();
  else
    return 0;
}

int
FramebufferSurface::get_height() const
{
  if (impl.get())
    return impl->get_height();
  else
    return 0;
}

Size
FramebufferSurface::get_size() const
{
  if (impl.get())
    return Size(impl->get_width(), impl->get_height());
  else
    return Size(0, 0);
}

FramebufferSurfaceImpl*
FramebufferSurface::get_impl() const
{
  return impl.get();
}

bool
FramebufferSurface::operator==(const FramebufferSurface& other) const
{
  return impl == other.impl;
}

FramebufferSurface::operator bool() const
{
  return impl.get() != nullptr;
}

long
FramebufferSurface::use_count() const
{
  return impl.use_count();
}

// EOF
