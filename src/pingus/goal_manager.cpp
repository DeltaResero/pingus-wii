// src/pingus/goal_manager.cpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 2002 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#include "pingus/goal_manager.hpp"

#include "pingus/pingu_holder.hpp"
#include "pingus/server.hpp"
#include "pingus/world.hpp"

namespace pingus {

GoalManager::GoalManager(Server* s)
  : server(s), goal(GT_NONE), exit_time(0)
{
}

bool
GoalManager::is_finished()
{
  switch (goal)
  {
    case GT_NONE:
      return false;

    case GT_GAME_ABORTED:
      return true;

    case GT_OUT_OF_TIME:
    case GT_NO_PINGUS_IN_WORLD:
    case GT_ARMAGEDDON:
      if (exit_time == 0)
      {
        // we are finished, now wait a few second so that everybody can
        // see the particles, etc.
        exit_time = server->get_time() + 125;
        return false;
      }
      else
      {
        return (exit_time < server->get_time());
      }

    default:
      assert(!"GoalManager: unknown goal state");
      return false;
  }
}

void
GoalManager::update()
{
  if (exit_time == 0)
  {
    World*       world  = server->get_world();
    PinguHolder* pingus = world->get_pingus();
    const PingusLevel& plf    = server->get_plf();

    if (pingus->get_number_of_allowed() == pingus->get_number_of_released()
        && pingus->get_number_of_alive() == 0)
    {
      goal = GT_NO_PINGUS_IN_WORLD;
    }
    else if (pingus->get_number_of_alive() == 0 && world->check_armageddon())
    {
      goal = GT_ARMAGEDDON;
    }
    else if (plf.get_time() != -1
             && plf.get_time() <= server->get_time())
    {
      goal = GT_OUT_OF_TIME;
    }
  }
}

void
GoalManager::set_abort_goal()
{
  goal = GT_GAME_ABORTED;
}


} // namespace pingus

// EOF
