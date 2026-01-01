// src/pingus/actions/angel.hpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 2000 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#ifndef HEADER_PINGUS_PINGUS_ACTIONS_ANGEL_HPP
#define HEADER_PINGUS_PINGUS_ACTIONS_ANGEL_HPP

#include "engine/display/sprite.hpp"
#include "pingus/pingu_action.hpp"

namespace Actions {

class Angel : public PinguAction
{
private:
  float counter;
  float x_pos;
  Sprite sprite;

public:
  Angel (Pingu* p);

  ActionName::Enum get_type () const { return ActionName::ANGEL; }

  void  update ();
  void  draw (SceneContext& gc);

private:
  Angel (const Angel&);
  Angel& operator= (const Angel&);
};

} // namespace Actions

#endif

// EOF
