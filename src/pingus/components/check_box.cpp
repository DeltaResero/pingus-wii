// src/pingus/components/check_box.cpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 2007 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#include "pingus/components/check_box.hpp"

#include "engine/display/drawing_context.hpp"
#include "pingus/fonts.hpp"
#include "pingus/globals.hpp"

CheckBox::CheckBox(const Rect& rect_) :
  RectComponent(rect_),
  m_checkbox_marked("core/menu/checkbox_marked_small"),
  m_checkbox("core/menu/checkbox_small"),
  state(false),
  on_change()
{
}

void
CheckBox::on_primary_button_press (int x, int y)
{
  state = !state;
  if (on_change)
    on_change(state);
}

void
CheckBox::draw(DrawingContext& gc)
{
  if (globals::developer_mode)
    gc.draw_rect(rect, Color(0, 255, 255));

  if (state)
  {
    gc.draw(m_checkbox_marked, Vector2i(rect.left, rect.top));
  }
  else
  {
    gc.draw(m_checkbox, Vector2i(rect.left, rect.top));
  }
}

void
CheckBox::set_state(bool v, bool send_signal)
{
  state = v;

  if (send_signal && on_change)
    on_change(state);
}

// EOF
