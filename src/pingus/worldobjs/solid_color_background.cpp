// src/pingus/worldobjs/solid_color_background.cpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 2000 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#include "pingus/worldobjs/solid_color_background.hpp"

#include "engine/display/scene_context.hpp"

namespace pingus::worldobjs {

SolidColorBackground::SolidColorBackground(const FileReader& reader) :
  color()
{
  if (!reader.read_colori("colori", color))
    reader.read_colorf("color", color);
}

void
SolidColorBackground::draw (SceneContext& gc)
{
  gc.color().fill_screen(color);
}

} // namespace pingus::worldobjs

// EOF
