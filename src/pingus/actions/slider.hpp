// src/pingus/actions/slider.hpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 2000 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#ifndef HEADER_PINGUS_PINGUS_ACTIONS_SLIDER_HPP
#define HEADER_PINGUS_PINGUS_ACTIONS_SLIDER_HPP

#include "pingus/pingu_action.hpp"
#include "pingus/state_sprite.hpp"

namespace pingus::actions {

class Slider : public PinguAction
{
private:
  StateSprite sprite;
  float  speed;
public:
  Slider (Pingu* p);

  ActionName::Enum get_type() const { return ActionName::SLIDER; }

  void draw (SceneContext& gc);
  void update();

private:
  Slider (const Slider&);
  Slider& operator= (const Slider&);
};

} // namespace pingus::actions

#endif

// EOF
