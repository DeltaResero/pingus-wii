// src/pingus/actions/exiter.hpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 1999 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#ifndef HEADER_PINGUS_PINGUS_ACTIONS_EXITER_HPP
#define HEADER_PINGUS_PINGUS_ACTIONS_EXITER_HPP

#include "pingus/pingu_action.hpp"
#include "pingus/state_sprite.hpp"

namespace pingus::action {

class Exiter : public PinguAction
{
private:
  StateSprite sprite;
  bool sound_played;

public:
  Exiter(Pingu*);
  void init(void);
  ActionName::Enum get_type() const { return ActionName::EXITER; }

  void draw (SceneContext& gc);
  void update();

private:
  Exiter (const Exiter&);
  Exiter& operator= (const Exiter&);
};

} // namespace pingus::action

#endif

// EOF
