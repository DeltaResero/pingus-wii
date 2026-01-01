// src/pingus/worldobjs/liquid.cpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 1999 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#include "pingus/worldobjs/liquid.hpp"

#include "engine/display/scene_context.hpp"
#include "pingus/collision_map.hpp"
#include "pingus/world.hpp"

namespace WorldObjs {

Liquid::Liquid(const FileReader& reader) :
  sur(),
  pos(),
  old_width_handling(false),
  width(0),
  speed()
{
  ResDescriptor desc;

  reader.read_vector("position", pos);
  reader.read_desc  ("surface",  desc);
  reader.read_int   ("repeat",   width);

  sur = Sprite(desc);

  if (!old_width_handling)
    width = width * sur.get_width();
}

float
Liquid::get_z_pos () const
{
  return pos.z;
}

void
Liquid::on_startup ()
{
  CollisionMask mask("liquids/water_cmap");

  for(int i=0; i < width; ++i)
    world->get_colmap()->put(mask,
                             static_cast<int>(pos.x + static_cast<float>(i)),
                             static_cast<int>(pos.y),
                             Groundtype::GP_WATER);
}

void
Liquid::draw (SceneContext& gc)
{
  for(int x = static_cast<int>(pos.x);
      x < static_cast<int>(pos.x) + width;
      x += sur.get_width())
  {
    gc.color().draw(sur, Vector3f(static_cast<float>(x), pos.y));
  }
}

void
Liquid::update()
{
  sur.update(0.033f);
}

} // namespace WorldObjs

// EOF
