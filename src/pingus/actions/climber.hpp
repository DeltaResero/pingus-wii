// src/pingus/actions/climber.hpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 1999 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#ifndef HEADER_PINGUS_PINGUS_ACTIONS_CLIMBER_HPP
#define HEADER_PINGUS_PINGUS_ACTIONS_CLIMBER_HPP

#include "pingus/pingu_action.hpp"
#include "pingus/state_sprite.hpp"

namespace pingus::actions {

class Climber : public PinguAction
{
private:
  StateSprite sprite;
  int sprite_width;
  int sprite_height;

public:
  Climber (Pingu*);

  ActionName::Enum get_type () const { return ActionName::CLIMBER; }

  void draw (SceneContext& gc);

  void update ();

  char get_persistent_char () { return 'c'; }
  bool change_allowed(ActionName::Enum new_action);

  Vector3f get_center_pos() const;

private:
  Climber (const Climber&);
  Climber& operator= (const Climber&);
};

} // namespace pingus::actions

#endif

// EOF
