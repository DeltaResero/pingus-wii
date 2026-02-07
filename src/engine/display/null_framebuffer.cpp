// src/engine/display/null_framebuffer.cpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 2008 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#include "engine/display/null_framebuffer.hpp"

#include "util/log.hpp"

namespace pingus {


class NullFramebufferSurfaceImpl : public FramebufferSurfaceImpl
{
private:
  Size size;

public:
  NullFramebufferSurfaceImpl(const Size& size_) : size(size_) {}
  ~NullFramebufferSurfaceImpl() {}

  int get_width()  const { return size.width; }
  int get_height() const { return size.height; }
};


NullFramebuffer::NullFramebuffer() :
  m_size(),
  m_fullscreen(false),
  m_resizable(false)
{
}

NullFramebuffer::~NullFramebuffer()
{
}

FramebufferSurface
NullFramebuffer::create_surface(const Surface& surface)
{
  log_info("creating surface: {}x{}", surface.get_size().width, surface.get_size().height);
  return FramebufferSurface(new NullFramebufferSurfaceImpl(surface.get_size()));
}

void
NullFramebuffer::set_video_mode(const Size& size, bool fullscreen, bool resizable)
{
  m_size = size;
  m_fullscreen = fullscreen;
  m_resizable  = resizable;

  log_info("size: {}x{} fullscreen: {} resizable: {}",
           m_size.width, m_size.height,
           m_fullscreen, m_resizable);
}

bool
NullFramebuffer::is_fullscreen() const
{
  return m_fullscreen;
}

bool
NullFramebuffer::is_resizable() const
{
  return m_resizable;
}

void
NullFramebuffer::flip()
{
}

void
NullFramebuffer::push_cliprect(const Rect&)
{
}

void
NullFramebuffer::pop_cliprect()
{
}

void
NullFramebuffer::draw_surface(const FramebufferSurface& /*src*/, const Vector2i& /*pos*/)
{
}

void
NullFramebuffer::draw_surface(const FramebufferSurface& /*src*/, const Rect& /*srcrect*/, const Vector2i& /*pos*/)
{
}

void
NullFramebuffer::draw_line(const Vector2i& /*pos1*/, const Vector2i& /*pos2*/, const Color& /*color*/)
{
}

void
NullFramebuffer::draw_rect(const Rect& /*rect*/, const Color& /*color*/)
{
}

void
NullFramebuffer::fill_rect(const Rect& /*rect*/, const Color& /*color*/)
{
}

Size
NullFramebuffer::get_size() const
{
  return m_size;
}


} // namespace pingus

// EOF
