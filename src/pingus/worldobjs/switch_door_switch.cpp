// src/pingus/worldobjs/switch_door_switch.cpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 2000 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#include "pingus/worldobjs/switch_door_switch.hpp"

#include "engine/display/scene_context.hpp"
#include "pingus/collision_map.hpp"
#include "pingus/pingu.hpp"
#include "pingus/pingu_holder.hpp"
#include "pingus/world.hpp"
#include "pingus/worldobjs/switch_door_door.hpp"
#include "util/log.hpp"

namespace pingus::worldobjs {

SwitchDoorSwitch::SwitchDoorSwitch(const FileReader& reader) :
  switch_pos(),
  switch_sur("worldobjs/switchdoor_switch"),
  m_target(),
  is_triggered(false),
  m_door()
{
  reader.read_string("target-id", m_target);
  reader.read_vector("position", switch_pos);
}

void
SwitchDoorSwitch::on_startup ()
{
  if (m_target.empty())
  {
    log_error("target-id is empty");
  }
  else
  {
    m_door = dynamic_cast<SwitchDoorDoor*>(world->get_worldobj(m_target));
    if (!m_door)
      log_error("given target-id is not a SwitchDoorDoor");
  }
}

void
SwitchDoorSwitch::draw (SceneContext& gc)
{
  gc.color().draw(switch_sur, switch_pos);
}

void
SwitchDoorSwitch::update ()
{
  if (!is_triggered)
  {
    if (m_door)
    {
      // Check if a pingu is passing the switch
      PinguHolder* holder = world->get_pingus();

      for (PinguIter pingu = holder->begin (); pingu != holder->end (); ++pingu)
      {
        if ((*pingu)->get_pos().x > switch_pos.x &&
            (*pingu)->get_pos().x < switch_pos.x + static_cast<float>(switch_sur.get_width()) &&
            (*pingu)->get_pos().y > switch_pos.y &&
            (*pingu)->get_pos().y < switch_pos.y + static_cast<float>(switch_sur.get_height()))
        {
          is_triggered = true;
          m_door->open_door();
          break;
        }
      }
    }
  }
}

} // namespace pingus::worldobjs

// EOF
