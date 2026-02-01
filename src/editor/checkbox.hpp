// src/editor/checkbox.hpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 2007 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#ifndef HEADER_PINGUS_EDITOR_CHECKBOX_HPP
#define HEADER_PINGUS_EDITOR_CHECKBOX_HPP

#include <functional>

#include "engine/gui/rect_component.hpp"

namespace pingus::editor {

class Checkbox : public GUI::RectComponent
{
private:
  bool checked;
  std::string label;

public:
  Checkbox(const Rect& rect, const std::string& label = "");
  ~Checkbox();

  void draw(DrawingContext& gc);
  void update_layout() {}

  void set_checked(bool t);
  bool is_checked() const { return checked; }
  void on_primary_button_press(int x, int y);

  std::function<void (bool)> on_change;

private:
  Checkbox (const Checkbox&);
  Checkbox& operator= (const Checkbox&);
};

} // namespace pingus::editor

#endif

// EOF
