// src/pingus/worldmap/drawable_factory.cpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 2002 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#include "pingus/worldmap/drawable_factory.hpp"

#include "pingus/worldmap/sprite_drawable.hpp"
#include "util/log.hpp"

namespace WorldmapNS {

Drawable*
DrawableFactory::create(const FileReader& reader)
{
  if (reader.get_name() == "surface")
  {
    return new SpriteDrawable(reader);
  }
  else
  {
    log_error("can't create %1%", reader.get_name());
    return 0;
  }
}

} // namespace WorldmapNS

// EOF
