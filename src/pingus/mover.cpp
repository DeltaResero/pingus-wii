// src/pingus/mover.cpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 1999 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#include "pingus/mover.hpp"

namespace pingus {


Mover::Mover(World* const world_arg, const Vector3f& pos_arg)
  : world(world_arg),
    pos(pos_arg),
    collision(false)
{
}

Mover::~Mover ()
{
}

Vector3f Mover::get_pos() const
{
  return pos;
}

bool Mover::collided() const
{
  return collision;
}


} // namespace pingus

// EOF
