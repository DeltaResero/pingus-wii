// src/engine/gui/component.cpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 2007 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#include "engine/gui/group_component.hpp"

namespace pingus::gui {

GroupComponent*
Component::get_parent() const
{
  return parent;
}

void
Component::set_parent(GroupComponent* p)
{
  assert(parent == nullptr);
  parent = p;
}

void
Component::grab()
{
  if (parent)
    parent->grab(this);
}

void
Component::ungrab()
{
  if (parent)
    parent->ungrab(this);
}

} // namespace pingus::gui

// EOF
