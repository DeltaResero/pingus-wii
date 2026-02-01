// src/pingus/actions/boarder.hpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 2000 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#ifndef HEADER_PINGUS_PINGUS_ACTIONS_BOARDER_HPP
#define HEADER_PINGUS_PINGUS_ACTIONS_BOARDER_HPP

#include "pingus/pingu_action.hpp"
#include "pingus/state_sprite.hpp"

namespace pingus::actions {

/** The Boarder action causes a pingu to use a skateboard to move
    forward. */
class Boarder : public PinguAction
{
private:
  float x_pos;
  float speed;
  StateSprite sprite;
public:
  Boarder (Pingu* p);

  ActionName::Enum get_type () const { return ActionName::BOARDER; }

  void  draw (SceneContext& gc);
  void  update ();

private:
  bool on_ground ();

  Boarder (const Boarder&);
  Boarder& operator= (const Boarder&);
};

} // namespace pingus::actions

#endif

// EOF
