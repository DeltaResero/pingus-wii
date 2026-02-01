// src/editor/gui_style.hpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 2007 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#ifndef HEADER_PINGUS_EDITOR_GUI_STYLE_HPP
#define HEADER_PINGUS_EDITOR_GUI_STYLE_HPP

#include "engine/display/drawing_context.hpp"

namespace pingus::editor {

class GUIStyle
{
private:
  public:
  static void draw_raised_box(DrawingContext& gc, const Rect& rect,
                              const Color& color = Color(237, 233, 227), int border = 1);
  static void draw_lowered_box(DrawingContext& gc, const Rect& rect,
                               const Color& color = Color(237, 233, 227), int border = 1);
};

} // namespace pingus::editor

#endif

// EOF
