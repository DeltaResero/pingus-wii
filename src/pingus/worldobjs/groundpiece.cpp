// src/pingus/worldobjs/groundpiece.cpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 2002 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#include "pingus/worldobjs/groundpiece.hpp"

#include "pingus/world.hpp"

namespace WorldObjs {

Groundpiece::Groundpiece(const FileReader& reader) :
  pos(),
  desc(),
  gptype()
{
  reader.read_vector("position", pos);
  reader.read_desc  ("surface",  desc);

  gptype = Groundtype::GP_GROUND;
  reader.read_enum("type", gptype, &Groundtype::string_to_type);
}

void
Groundpiece::on_startup ()
{
  // FIXME: using a CollisionMask is kind of unneeded here
  CollisionMask mask(desc);

  // FIXME: overdrawing of bridges and similar things aren't handled here
  if (gptype == Groundtype::GP_REMOVE)
    get_world()->remove(mask, static_cast<int>(pos.x), static_cast<int>(pos.y));
  else
    get_world()->put(mask, static_cast<int>(pos.x), static_cast<int>(pos.y), gptype);
}

} // namespace WorldObjs

// EOF
