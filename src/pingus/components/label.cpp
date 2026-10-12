// src/pingus/components/label.cpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 2007 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#include "pingus/components/label.hpp"

#include "engine/display/drawing_context.hpp"
#include "pingus/fonts.hpp"
#include "pingus/globals.hpp"

namespace pingus {

Label::Label(const std::string& label_, const Rect& rect_)
  : RectComponent(rect_),
    label(label_),
    struck(false)
{
}

void
Label::draw(DrawingContext& gc)
{
  if (globals::draw_menu_outlines)
    gc.draw_rect(rect, Color(0, 255, 255));

  gc.print_left(fonts::chalk_normal, Vector2i(rect.left, rect.top), label);

  if (struck)
  {
    // Through the middle of the lowercase letters, where fonts put a strikeout.
    const int y = rect.top + fonts::chalk_normal.get_height() * 2 / 3;
    gc.draw_fillrect(Rect(rect.left, y, rect.left + static_cast<int>(fonts::chalk_normal.get_width(label)), y + 2),
                     Color(255, 255, 255));
  }
}


} // namespace pingus

// EOF
