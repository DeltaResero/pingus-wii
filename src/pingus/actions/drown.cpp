// src/pingus/actions/drown.cpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 2000 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#include "pingus/actions/drown.hpp"

#include "engine/display/scene_context.hpp"
#include "pingus/pingu.hpp"

namespace pingus::actions {

Drown::Drown (Pingu* p) :
  PinguAction(p),
  sprite()
{
  sprite.load(Direction::LEFT,  Sprite("pingus/player" +
                                       pingu->get_owner_str() + "/drownfall/left"));
  sprite.load(Direction::RIGHT, Sprite("pingus/player" +
                                       pingu->get_owner_str() + "/drownfall/right"));
}

void
Drown::draw (SceneContext& gc)
{
  gc.color().draw(sprite[pingu->direction], pingu->get_pos ());
}

void
Drown::update ()
{
  sprite[pingu->direction].update();
  if (sprite[pingu->direction].is_finished())
  {
    pingu->set_status(Pingu::PS_DEAD);
  }
}

} // namespace pingus::actions

// EOF
