// src/pingus/actions/floater.hpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 1999 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#ifndef HEADER_PINGUS_PINGUS_ACTIONS_FLOATER_HPP
#define HEADER_PINGUS_PINGUS_ACTIONS_FLOATER_HPP

#include "engine/display/sprite.hpp"
#include "pingus/pingu_action.hpp"

namespace pingus::actions {

class Floater : public PinguAction
{
private:
  int falling_depth;
  int step;
  Sprite sprite;

public:
  Floater(Pingu* p);

  ActionName::Enum get_type() const { return ActionName::FLOATER; }

  void init(void);

  void draw (SceneContext& gc);
  void update();

  char get_persistent_char () { return 'f'; }
  bool change_allowed (ActionName::Enum new_action);

private:
  Floater (const Floater&);
  Floater& operator= (const Floater&);
};

} // namespace pingus::actions

#endif

// EOF
