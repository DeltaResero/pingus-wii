// src/pingus/movers/linear_mover.hpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 2000 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#ifndef HEADER_PINGUS_PINGUS_MOVERS_LINEAR_MOVER_HPP
#define HEADER_PINGUS_PINGUS_MOVERS_LINEAR_MOVER_HPP

#include "pingus/mover.hpp"

class Collider;

namespace pingus::movers {

class LinearMover : public Mover
{
public:
  /** Constructor */
  LinearMover(World* const world_arg, const Vector3f& pos_arg);

  /** Destructor */
  ~LinearMover();

  /** Updates the position of the object taking into account collisions */
  void update(const Vector3f& move, const Collider& collision_at);
};

} // namespace pingus::movers

#endif

// EOF
