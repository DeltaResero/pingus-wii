// src/engine/display/null_framebuffer.hpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 2008 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#ifndef HEADER_PINGUS_ENGINE_DISPLAY_NULL_FRAMEBUFFER_HPP
#define HEADER_PINGUS_ENGINE_DISPLAY_NULL_FRAMEBUFFER_HPP

#include "engine/display/framebuffer.hpp"

namespace pingus {

/** NullFramebuffer is an empty dummy class for debugging purposes */
class NullFramebuffer : public Framebuffer
{
private:
  Size m_size;
  bool m_fullscreen;
  bool m_resizable;

public:
  NullFramebuffer();
  ~NullFramebuffer();

  FramebufferSurface create_surface(const Surface& surface);

  void set_video_mode(const Size& size, bool fullscreen, bool resizable);
  bool is_fullscreen() const;
  bool is_resizable() const;
  void flip();

  void push_cliprect(const Rect&);
  void pop_cliprect();

  void draw_surface(const FramebufferSurface& src, const Vector2i& pos);
  void draw_surface(const FramebufferSurface& src, const Rect& srcrect, const Vector2i& pos);

  void draw_line(const Vector2i& pos1, const Vector2i& pos2, const Color& color);

  void draw_rect(const Rect& rect, const Color& color);
  void fill_rect(const Rect& rect, const Color& color);

  Size get_size() const;
};


} // namespace pingus
#endif

// EOF
