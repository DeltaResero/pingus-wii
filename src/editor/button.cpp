// src/editor/button.cpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 2007 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#include "editor/button.hpp"

#include "editor/gui_style.hpp"
#include "pingus/fonts.hpp"

namespace Editor {

Button::Button(const Rect& rect_, const std::string& text_) :
  RectComponent(rect_),
  text(text_),
  mouse_over(false),
  mouse_down(false),
  enabled(true),
  on_click()
{
}

void
Button::set_text(const std::string& text_)
{
  text = text_;
}

void
Button::draw (DrawingContext& gc)
{
  if (enabled)
  {
    if (mouse_down && mouse_over)
      GUIStyle::draw_lowered_box(gc, rect, Color(237, 233, 227), 2);
    else if (mouse_over)
      GUIStyle::draw_raised_box(gc, rect, Color(255, 255, 255), 2);
    else
      GUIStyle::draw_raised_box(gc, rect, Color(237, 233, 227), 2);
  }

  gc.print_center(Fonts::verdana11,
                  Vector2i(rect.left + rect.get_width()/2, rect.top + rect.get_height()/2 - 6),
                  text);
}

void
Button::update (float delta)
{
}

void
Button::on_pointer_enter ()
{
  mouse_over = true;
}

void
Button::on_pointer_leave ()
{
  mouse_over = false;
}

void
Button::on_primary_button_press (int x, int y)
{
  mouse_down = true;
}

void
Button::on_primary_button_release (int x, int y)
{
  mouse_down = false;
  if (mouse_over && on_click)
    on_click();
}

} // namespace Editor

// EOF
