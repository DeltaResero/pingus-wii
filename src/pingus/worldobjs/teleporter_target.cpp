// src/pingus/worldobjs/teleporter_target.cpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 2000 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#include "pingus/worldobjs/teleporter_target.hpp"

#include "engine/display/scene_context.hpp"

namespace pingus::worldobjs {

TeleporterTarget::TeleporterTarget(const FileReader& reader) :
  WorldObj(reader),
  pos(),
  sprite("worldobjs/teleportertarget")
{
  reader.read_vector("position", pos);
}

float
TeleporterTarget::get_z_pos () const
{
  return pos.z;
}

void
TeleporterTarget::draw (SceneContext& gc)
{
  gc.color().draw(sprite, pos);
}

void
TeleporterTarget::update ()
{
  sprite.update();
}

void
TeleporterTarget::teleporter_used()
{
  sprite.restart();
}

} // namespace pingus::worldobjs

// EOF
