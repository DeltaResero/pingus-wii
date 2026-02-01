// src/pingus/worldobjs/laser_exit.hpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 1999 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#ifndef HEADER_PINGUS_PINGUS_WORLDOBJS_LASER_EXIT_HPP
#define HEADER_PINGUS_PINGUS_WORLDOBJS_LASER_EXIT_HPP

#include "engine/display/sprite.hpp"
#include "math/vector3f.hpp"
#include "pingus/worldobj.hpp"

namespace pingus::worldobjsData {
class LaserExitData;
} // namespace pingus::worldobjsData

class Pingu;

namespace pingus::worldobjs {

class LaserExit : public WorldObj
{
private:
  Sprite   surface;
  Vector3f pos;

  bool killing;

public:
  LaserExit(const FileReader& reader);

  float get_z_pos () const;
  void set_pos(const Vector3f& p) { pos = p; }
  Vector3f get_pos() const { return pos; }

  void draw (SceneContext& gc);
  void update ();

protected:
  void catch_pingu (Pingu*);

private:
  LaserExit (const LaserExit&);
  LaserExit& operator= (const LaserExit&);
};

} // namespace pingus::worldobjs

#endif

// EOF
