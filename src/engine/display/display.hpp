// src/engine/display/display.hpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 2000 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#ifndef HEADER_PINGUS_ENGINE_DISPLAY_DISPLAY_HPP
#define HEADER_PINGUS_ENGINE_DISPLAY_DISPLAY_HPP

#include <memory>
#include <vector>

#include "math/size.hpp"
#include "pingus/options.hpp"

namespace pingus {


class Vector2i;
class Rect;
class Color;
class Framebuffer;

class Display
{
private:
  static std::unique_ptr<Framebuffer> s_framebuffer;

public:
  static void flip_display();

  static int  get_width();
  static int  get_height();
  static Size get_size();

  static void create_window(FramebufferType framebuffer_type, const Size& size, bool fullscreen, bool resizable);
  static void set_video_mode(const Size& size, bool fullscreen, bool resizable);
  static void resize(const Size& size);

  static bool is_fullscreen();
  static bool is_resizable();

  static Framebuffer* get_framebuffer();

  static Size find_closest_fullscreen_video_mode(const Size& size);
  static std::vector<Size> get_fullscreen_video_modes();

private:
  Display ();
  Display (const Display&);
  Display& operator= (const Display&);
};


} // namespace pingus
#endif

// EOF
