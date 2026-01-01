// src/pingus/worldmap/dot_factory.cpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 2002 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#include "pingus/worldmap/dot_factory.hpp"

#include <stdexcept>

#include "pingus/worldmap/level_dot.hpp"
#include "pingus/worldmap/story_dot.hpp"
#include "util/raise_exception.hpp"

namespace WorldmapNS {

Dot*
DotFactory::create(const FileReader& reader)
{
  if (reader.get_name() == "storydot")
  {
    return new StoryDot(reader);
  }
  else if (reader.get_name() == "leveldot")
  {
    return new LevelDot(reader);
  }
  else
  {
    raise_exception(std::runtime_error, "DotFactory: unknown tag: " <<  reader.get_name());
    return 0;
  }
}

} // namespace WorldmapNS

// EOF
