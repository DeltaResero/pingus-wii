// src/editor/label.hpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 2007 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#ifndef HEADER_PINGUS_EDITOR_LABEL_HPP
#define HEADER_PINGUS_EDITOR_LABEL_HPP

#include "engine/gui/rect_component.hpp"

namespace pingus::editor {

class Label : public GUI::RectComponent
{
private:
  std::string text;

public:
  Label(const Rect& rect, const std::string& text);
  Label(const std::string& text);

  bool is_at(int, int) { return false; }
  void draw (DrawingContext& gc);
  void update (float delta);
  void update_layout() {}

  void set_text(const std::string& text_) { text = text_; }
};

} // namespace pingus::editor

#endif

// EOF
