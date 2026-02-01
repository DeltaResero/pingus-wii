// src/pingus/actions/digger.hpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 1999 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#ifndef HEADER_PINGUS_PINGUS_ACTIONS_DIGGER_HPP
#define HEADER_PINGUS_PINGUS_ACTIONS_DIGGER_HPP

#include "pingus/collision_mask.hpp"
#include "engine/display/sprite.hpp"
#include "pingus/pingu_action.hpp"

namespace pingus::action {

class Digger : public PinguAction
{
private:
  CollisionMask digger_radius;
  CollisionMask digger_radius_final;
  Sprite sprite;
  int delay_count;

public:
  Digger(Pingu*);

  ActionName::Enum get_type() const { return ActionName::DIGGER; }

  bool have_something_to_dig();
  void dig(bool final);

  void draw(SceneContext& gc);
  void update();

private:
  Digger (const Digger&);
  Digger& operator= (const Digger&);
};

} // namespace pingus::action

#endif

// EOF
