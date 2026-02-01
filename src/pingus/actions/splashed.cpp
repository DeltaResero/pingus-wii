// src/pingus/actions/splashed.cpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 1999 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#include "pingus/actions/splashed.hpp"

#include "engine/display/scene_context.hpp"
#include "pingus/pingu.hpp"
#include "pingus/world.hpp"
#include "pingus/worldobj.hpp"

namespace pingus::action {

Splashed::Splashed (Pingu* p) :
  PinguAction(p),
  particle_thrown(false),
  sound_played(false),
  sprite()
{
  sprite = Sprite("pingus/player" + pingu->get_owner_str() + "/splat");
}

void
Splashed::update ()
{
  sprite.update();

  if (!particle_thrown)
  {
    particle_thrown = true;
    WorldObj::get_world()->play_sound("splash", pingu->get_pos());
  }

  if (sprite.is_finished())
  {
    pingu->set_status(Pingu::PS_DEAD);
  }
}

void
Splashed::draw (SceneContext& gc)
{
  gc.color().draw(sprite, pingu->get_pos ());
}

} // namespace pingus::action

// EOF
