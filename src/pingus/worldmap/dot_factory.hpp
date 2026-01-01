// src/pingus/worldmap/dot_factory.hpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 2002 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#ifndef HEADER_PINGUS_PINGUS_WORLDMAP_DOT_FACTORY_HPP
#define HEADER_PINGUS_PINGUS_WORLDMAP_DOT_FACTORY_HPP

#include "util/file_reader.hpp"

namespace WorldmapNS {

class Dot;

class DotFactory
{
private:
public:
  /** Create a Dot from a given piece of XML */
  static Dot* create(const FileReader& reader);
private:
  DotFactory (const DotFactory&);
  DotFactory& operator= (const DotFactory&);
};

} // namespace WorldmapNS

#endif

// EOF
