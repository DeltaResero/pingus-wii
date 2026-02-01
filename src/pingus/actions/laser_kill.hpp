// src/pingus/actions/laser_kill.hpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 1999 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#ifndef HEADER_PINGUS_PINGUS_ACTIONS_LASER_KILL_HPP
#define HEADER_PINGUS_PINGUS_ACTIONS_LASER_KILL_HPP

#include "pingus/pingu_action.hpp"
#include "pingus/state_sprite.hpp"

namespace pingus::action {

/** This action is triggered by the LaserExit trap and causes the
    pingu to 'burn-away' */
class LaserKill : public PinguAction
{
private:
  StateSprite sprite;

public:
  LaserKill (Pingu*);

  ActionName::Enum get_type () const { return ActionName::LASERKILL; }
  void init (void);

  void draw (SceneContext& gc);
  void update ();

  bool catchable () { return false; }

private:
  LaserKill (const LaserKill&);
  LaserKill& operator= (const LaserKill&);
};

} // namespace pingus::action

#endif

// EOF
