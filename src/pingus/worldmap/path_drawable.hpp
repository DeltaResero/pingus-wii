// src/pingus/worldmap/path_drawable.hpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 2002 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#ifndef HEADER_PINGUS_PINGUS_WORLDMAP_PATH_DRAWABLE_HPP
#define HEADER_PINGUS_PINGUS_WORLDMAP_PATH_DRAWABLE_HPP

#include "pingus/worldmap/drawable.hpp"
#include "pingus/worldmap/path_graph.hpp"

namespace pingus::worldmap {

/** Drawable to show the path between two nodes, only used for
    debugging */
class PathDrawable : public Drawable
{
private:
  Path path;

public:
  PathDrawable(const Path& arg_path);

  void draw(DrawingContext& gc);
  void update(float delta);

private:
  PathDrawable (const PathDrawable&);
  PathDrawable& operator= (const PathDrawable&);
};

} // namespace pingus::worldmap

#endif

// EOF
