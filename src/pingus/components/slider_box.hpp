// src/pingus/components/slider_box.hpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 2007 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#ifndef HEADER_PINGUS_PINGUS_COMPONENTS_SLIDER_BOX_HPP
#define HEADER_PINGUS_PINGUS_COMPONENTS_SLIDER_BOX_HPP

#include <functional>

#include "engine/gui/rect_component.hpp"

namespace pingus {

class SliderBox : public gui::RectComponent
{
private:
  int m_steps;
  int value;
  bool drag_drop;

public:
  SliderBox(const Rect& rect, int steps);

  void draw(DrawingContext& gc);
  void on_primary_button_press(int x, int y);
  void on_primary_button_release(int x, int y);
  void on_pointer_move(int x, int y);
  void update_layout() {}

  void set_value(int v);

  std::function<void (int)> on_change;

private:
  SliderBox (const SliderBox&);
  SliderBox& operator= (const SliderBox&);
};


} // namespace pingus
#endif

// EOF
