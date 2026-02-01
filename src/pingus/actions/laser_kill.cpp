// src/pingus/actions/laser_kill.cpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 1999 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#include "pingus/actions/laser_kill.hpp"

#include "engine/display/scene_context.hpp"
#include "pingus/pingu.hpp"

namespace pingus::action {

LaserKill::LaserKill(Pingu* p) :
  PinguAction(p),
  sprite()
{
  sprite.load(Direction::LEFT,  Sprite("other/laser_kill/left"));
  sprite.load(Direction::RIGHT, Sprite("other/laser_kill/right"));
}

void
LaserKill::draw (SceneContext& gc)
{
  gc.color().draw(sprite[pingu->direction], pingu->get_pos () + Vector3f (0, 2));
}

void
LaserKill::update ()
{
  if (sprite[pingu->direction].is_finished())
    pingu->set_status(Pingu::PS_DEAD);
  else
    sprite[pingu->direction].update();
}

} // namespace pingus::action

// EOF
