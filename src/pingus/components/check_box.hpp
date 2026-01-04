// src/pingus/components/check_box.hpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 2007 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#ifndef HEADER_PINGUS_PINGUS_COMPONENTS_CHECK_BOX_HPP
#define HEADER_PINGUS_PINGUS_COMPONENTS_CHECK_BOX_HPP

#include <functional>

#include "engine/display/sprite.hpp"
#include "engine/gui/rect_component.hpp"

class CheckBox : public GUI::RectComponent
{
private:
  Sprite m_checkbox_marked;
  Sprite m_checkbox;

  bool state;

public:
  CheckBox(const Rect& rect);

  void draw(DrawingContext& gc);
  void on_primary_button_press(int x, int y);
  void update_layout() {}

  void set_state(bool v, bool send_signal);

  std::function<void (bool)> on_change;

private:
  CheckBox (const CheckBox&);
  CheckBox& operator= (const CheckBox&);
};

#endif

// EOF
