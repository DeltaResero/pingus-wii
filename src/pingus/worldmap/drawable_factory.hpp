// src/pingus/worldmap/drawable_factory.hpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 2002 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#ifndef HEADER_PINGUS_PINGUS_WORLDMAP_DRAWABLE_FACTORY_HPP
#define HEADER_PINGUS_PINGUS_WORLDMAP_DRAWABLE_FACTORY_HPP

#include <memory>

#include "pingus/worldmap/drawable.hpp"

namespace WorldmapNS {

class DrawableFactory
{
private:
  public:
  /** Create a new drawable */
  static std::unique_ptr<Drawable> create(const FileReader& reader);
private:
  DrawableFactory (const DrawableFactory&);
  DrawableFactory& operator= (const DrawableFactory&);
};

} // namespace WorldmapNS

#endif

// EOF
