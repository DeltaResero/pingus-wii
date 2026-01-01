// src/pingus/worldobjs/switch_door_door.hpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 1998-2011 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#ifndef HEADER_PINGUS_PINGUS_WORLDOBJS_SWITCH_DOOR_DOOR_HPP
#define HEADER_PINGUS_PINGUS_WORLDOBJS_SWITCH_DOOR_DOOR_HPP

#include "math/vector3f.hpp"
#include "pingus/collision_mask.hpp"
#include "pingus/worldobj.hpp"

namespace WorldObjs {

class SwitchDoorDoor : public WorldObj
{
private:
  /// The upper/middle pos of the door
  Vector3f door_pos;

  // The height of the door in graphic tiles
  int door_height;

  Sprite door_box;
  CollisionMask door_box_cmap;
  Sprite door_tile;
  CollisionMask door_tile_cmap;

  /** True if the door is opening */
  bool is_opening;

  /** The current height of the door, it might decrease when the door
      is opening, it will be zero when the door is fully opened */
  int current_door_height;

public:
  SwitchDoorDoor(const FileReader& reader);

  void on_startup();
  void draw (SceneContext& gc);
  void update ();

  /// The switch and the door should stay above the pingus
  float get_z_pos() const { return 100; }
  void set_pos(const Vector3f& p) { door_pos = p; }
  Vector3f get_pos() const { return door_pos; }

  void open_door();

private:
  SwitchDoorDoor(const SwitchDoorDoor&);
  SwitchDoorDoor& operator=(const SwitchDoorDoor&);
};

} // namespace WorldObjs

#endif

// EOF
