// src/pingus/actions/superman.cpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 2000 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#include "pingus/actions/superman.hpp"

#include "engine/display/scene_context.hpp"
#include "pingus/pingu.hpp"

namespace Actions {

Superman::Superman (Pingu* p)
  : PinguAction(p),
    counter(0.0f),
    x_pos(pingu->get_x()),
    sprite(Sprite("pingus/player" + pingu->get_owner_str() + "/superman"))
{
}

void
Superman::update ()
{
  sprite.update();
  counter += 0.025f;
  pingu->set_pos(pingu->get_x() + 40.0f * 0.025f, pingu->get_y() - 200.0f * 0.025f);

  if (pingu->get_y() < -32)
    pingu->set_status(Pingu::PS_DEAD);
}

void
Superman::draw (SceneContext& gc)
{
  gc.color().draw(sprite, pingu->get_pos ());
}

} // namespace Actions

// EOF
