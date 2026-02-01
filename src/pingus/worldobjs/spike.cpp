// src/pingus/worldobjs/spike.cpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 1999 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#include "pingus/worldobjs/spike.hpp"

#include "engine/display/scene_context.hpp"
#include "pingus/pingu.hpp"
#include "pingus/pingu_holder.hpp"
#include "pingus/world.hpp"

namespace pingus::worldobjs {

Spike::Spike (const FileReader& reader) :
  surface("traps/spike"),
  pos(),
  killing(false)
{
  reader.read_vector("position", pos);
}

float
Spike::get_z_pos () const
{
  return pos.z;
}

void
Spike::draw (SceneContext& gc)
{
  if (killing) {
    gc.color().draw (surface, pos);
  } else {
    // do nothing
  }
}

void
Spike::update()
{
  if (killing)
    surface.update();

  PinguHolder* holder = world->get_pingus();
  for (PinguIter pingu = holder->begin (); pingu != holder->end (); ++pingu)
    catch_pingu(*pingu);

  if (surface.get_current_frame() == surface.get_frame_count() - 1)
    killing = false;
}

void
Spike::catch_pingu (Pingu* pingu)
{
  if (!killing) {
    if ( pingu->get_pos().x > pos.x + 16 - 5 && pingu->get_pos().x < pos.x + 16 + 5
         && pingu->get_pos().y > pos.y          && pingu->get_pos().y < pos.y + 32)
    {
      surface.restart();
      killing = true;
    }
  } else {
    if (surface.get_current_frame() == 3
        && pingu->get_pos().x > pos.x +16 - 12 && pingu->get_pos().x < pos.x + 16 + 12
        && pingu->get_pos().y > pos.y          && pingu->get_pos().y < pos.y + 32)
    {
      pingu->set_status(Pingu::PS_DEAD);
    }
  }
}

} // namespace pingus::worldobjs

// EOF
