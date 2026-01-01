// src/pingus/components/label.hpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 2007 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#ifndef HEADER_PINGUS_PINGUS_COMPONENTS_LABEL_HPP
#define HEADER_PINGUS_PINGUS_COMPONENTS_LABEL_HPP

#include "engine/gui/rect_component.hpp"

class Label : public GUI::RectComponent
{
private:
  std::string label;

public:
  Label(const std::string& label, const Rect& rect);

  void draw(DrawingContext& gc);
  void update_layout() {}

private:
  Label (const Label&);
  Label& operator= (const Label&);
};

#endif

// EOF
