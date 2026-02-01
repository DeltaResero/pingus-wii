// src/pingus/worldobjs/teleporter_target.hpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 2000 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#ifndef HEADER_PINGUS_PINGUS_WORLDOBJS_TELEPORTER_TARGET_HPP
#define HEADER_PINGUS_PINGUS_WORLDOBJS_TELEPORTER_TARGET_HPP

#include "math/vector3f.hpp"
#include "pingus/worldobj.hpp"

namespace pingus::worldobjs {

class TeleporterTarget : public WorldObj
{
private:
  Vector3f pos;
  Sprite   sprite;

public:
  TeleporterTarget(const FileReader& reader);

  void  draw (SceneContext& gc);
  void  update ();
  float get_z_pos () const;
  void set_pos(const Vector3f& p) { pos = p; }
  Vector3f get_pos() const { return pos; }

  void  teleporter_used();
private:
  TeleporterTarget (const TeleporterTarget&);
  TeleporterTarget& operator= (const TeleporterTarget&);
};

} // namespace pingus::worldobjs

#endif

// EOF
