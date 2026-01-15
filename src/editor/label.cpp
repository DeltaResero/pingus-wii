// src/editor/label.cpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 2007 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#include "editor/label.hpp"

#include "engine/display/drawing_context.hpp"
#include "pingus/fonts.hpp"

namespace Editor {

Label::Label(const Rect& rect_, const std::string& text_) :
  RectComponent(rect_),
  text(text_)
{
}

Label::Label(const std::string& text_) :
  text(text_)
{
}

void
Label::draw (DrawingContext& gc)
{
  gc.print_left(Fonts::verdana11,
                Vector2i(rect.left, rect.top + rect.get_height()/2 - Fonts::verdana11.get_height()/2),
                text);
}

void
Label::update (float /*delta*/)
{
}

} // namespace Editor

// EOF
