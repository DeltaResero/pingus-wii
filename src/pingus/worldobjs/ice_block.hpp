// src/pingus/worldobjs/ice_block.hpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 2000 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#ifndef HEADER_PINGUS_PINGUS_WORLDOBJS_ICE_BLOCK_HPP
#define HEADER_PINGUS_PINGUS_WORLDOBJS_ICE_BLOCK_HPP

#include "math/vector3f.hpp"
#include "pingus/collision_mask.hpp"
#include "pingus/worldobj.hpp"

namespace pingus::worldobjs {

class IceBlock : public WorldObj
{
private:
  /// The upper/left position  of the iceblock's
  Vector3f pos;

  /** The number of iceblocks, only complete blocks are supported */
  int width;

  float thickness;
  bool  is_finished;
  int   last_contact;
  Sprite block_sur;
  CollisionMask block_sur_cmap;

public:
  IceBlock(const FileReader& reader);

  float get_z_pos () const { return pos.z; }
  void set_pos(const Vector3f& p) { pos = p; }
  Vector3f get_pos() const { return pos; }

  void on_startup ();
  void draw (SceneContext& gc);
  void update ();

private:
  IceBlock (const IceBlock&);
  IceBlock& operator= (const IceBlock&);
};

} // namespace pingus::worldobjs

#endif

// EOF
