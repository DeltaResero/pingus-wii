// src/pingus/worldobjs/laser_exit.cpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 1999 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#include "pingus/worldobjs/laser_exit.hpp"

#include "engine/display/scene_context.hpp"
#include "pingus/pingu.hpp"
#include "pingus/pingu_holder.hpp"
#include "pingus/world.hpp"

namespace pingus::worldobjs {

LaserExit::LaserExit(const FileReader& reader) :
  surface("traps/laser_exit"),
  pos(),
  killing(false)
{
  reader.read_vector("position", pos);
}

float
LaserExit::get_z_pos () const
{
  return pos.z;
}

void
LaserExit::draw (SceneContext& gc)
{
  gc.color().draw (surface, pos);
}

void
LaserExit::update ()
{

  PinguHolder* holder = world->get_pingus();
  for (PinguIter pingu = holder->begin (); pingu != holder->end (); ++pingu){
    catch_pingu(*pingu);
  }

  if (killing) {
    if (surface.is_finished()) {
      surface.restart();
      killing = false;
    } else {
      surface.update();
    }
  }
}

void
LaserExit::catch_pingu (Pingu* pingu)
{
  if (!killing)
  {
    if (   pingu->get_x () < pos.x + 34 + 10 && pingu->get_x () > pos.x + 34
           && pingu->get_y () < pos.y + 43 + 20 && pingu->get_y () > pos.y + 43)
    {
      if (pingu->get_action() != ActionName::LASERKILL)
      {
        killing = true;
        pingu->set_action(ActionName::LASERKILL);
      }
    }
  }
}

} // namespace pingus::worldobjs

// EOF
