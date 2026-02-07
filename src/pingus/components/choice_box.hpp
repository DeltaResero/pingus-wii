// src/pingus/components/choice_box.hpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 2007 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#ifndef HEADER_PINGUS_PINGUS_COMPONENTS_CHOICE_BOX_HPP
#define HEADER_PINGUS_PINGUS_COMPONENTS_CHOICE_BOX_HPP

#include <functional>

#include "engine/gui/rect_component.hpp"

namespace pingus {

class ChoiceBox : public gui::RectComponent
{
private:
  int current_choice;
  std::vector<std::string> choices;

public:
  ChoiceBox(const Rect& rect);

  void draw(DrawingContext& gc);
  void on_primary_button_press(int x, int y);
  void update_layout() {}
  void add_choice(const std::string& str);
  void set_current_choice(int choice);

  std::function<void (std::string)> on_change;

private:
  ChoiceBox (const ChoiceBox&);
  ChoiceBox& operator= (const ChoiceBox&);
};


} // namespace pingus
#endif

// EOF
