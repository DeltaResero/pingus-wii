// src/pingus/actions/superman.hpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 2000 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#ifndef HEADER_PINGUS_PINGUS_ACTIONS_SUPERMAN_HPP
#define HEADER_PINGUS_PINGUS_ACTIONS_SUPERMAN_HPP

#include "engine/display/sprite.hpp"
#include "pingus/pingu_action.hpp"

namespace pingus::action {

class Superman : public PinguAction
{
private:
  float counter;
  float x_pos;
  Sprite sprite;

public:
  Superman (Pingu*);

  ActionName::Enum get_type () const { return ActionName::SUPERMAN; }

  void draw (SceneContext& gc);
  void update ();

private:
  Superman (const Superman&);
  Superman& operator= (const Superman&);
};

} // namespace pingus::action

#endif

// EOF
