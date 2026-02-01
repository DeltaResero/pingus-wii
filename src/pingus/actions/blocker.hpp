// src/pingus/actions/blocker.hpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 1999 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#ifndef HEADER_PINGUS_PINGUS_ACTIONS_BLOCKER_HPP
#define HEADER_PINGUS_PINGUS_ACTIONS_BLOCKER_HPP

#include "pingus/pingu_action.hpp"
#include "pingus/state_sprite.hpp"

namespace pingus::action {

class Blocker : public PinguAction
{
private:
  StateSprite sprite;

public:
  Blocker (Pingu* p);

  ActionName::Enum get_type() const { return ActionName::BLOCKER; }

  void  draw (SceneContext& gc);
  void  update();

private:
  bool  standing_on_ground();
  void  catch_pingu(Pingu* pingu);

  Blocker (const Blocker&);
  Blocker& operator= (const Blocker&);
};

} // namespace pingus::action

#endif

// EOF
