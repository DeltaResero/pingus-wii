// src/editor/button.hpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 2007 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#ifndef HEADER_PINGUS_EDITOR_BUTTON_HPP
#define HEADER_PINGUS_EDITOR_BUTTON_HPP

#include <boost/signals2.hpp>

#include "engine/gui/rect_component.hpp"

namespace Editor {

class Button : public GUI::RectComponent
{
private:
  std::string text;
  bool mouse_over;
  bool mouse_down;
  bool enabled;

public:
  Button(const Rect& rect, const std::string& text);

  void draw (DrawingContext& gc);
  void update (float delta);
  void update_layout() {}

  void set_text(const std::string& text);

  void on_pointer_enter();
  void on_pointer_leave();
  void on_primary_button_press(int x, int y);
  void on_primary_button_release(int x, int y);

  void enable()  { enabled = true; }
  void disable() { enabled = false; }

  boost::signals2::signal<void()> on_click;

private:
  Button (const Button&);
  Button& operator= (const Button&);
};

} // namespace Editor

#endif

// EOF
