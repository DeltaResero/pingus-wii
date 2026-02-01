// src/pingus/actions/smashed.cpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 1999 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#include "pingus/actions/smashed.hpp"

#include "engine/display/scene_context.hpp"
#include "pingus/pingu.hpp"

namespace pingus::actions {

Smashed::Smashed (Pingu* p) :
  PinguAction(p),
  sound_played(false),
  sprite()
{
  sprite = Sprite("pingus/player" + pingu->get_owner_str() + "/bomber");
}

void
Smashed::draw (SceneContext& gc)
{
  gc.color().draw(sprite, pingu->get_pos ());
}

void
Smashed::update()
{
  sprite.update();
  //  pingu->particle->add_pingu_explo(pingu->x_pos, pingu->y_pos - 16);
  if (sprite.is_finished())
    pingu->set_status(Pingu::PS_DEAD);
}

} // namespace pingus::actions

// EOF
