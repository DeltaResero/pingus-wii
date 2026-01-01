// src/pingus/worldobjs/conveyor_belt.hpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 2000 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#ifndef HEADER_PINGUS_PINGUS_WORLDOBJS_CONVEYOR_BELT_HPP
#define HEADER_PINGUS_PINGUS_WORLDOBJS_CONVEYOR_BELT_HPP

#include "math/vector3f.hpp"
#include "pingus/worldobj.hpp"

namespace WorldObjsData {
class ConveyorBeltData;
}

namespace WorldObjs {

class ConveyorBelt : public  WorldObj
{
private:
  Sprite left_sur;
  Sprite right_sur;
  Sprite middle_sur;

  Vector3f pos;
  int    width;
  float  speed;
  float  counter;

public:
  ConveyorBelt(const FileReader& reader);

  void draw (SceneContext& gc);
  void on_startup ();
  void update ();
  float get_z_pos () const;
  void set_pos(const Vector3f& p) { pos = p; }
  Vector3f get_pos() const { return pos; }

private:
  ConveyorBelt (const ConveyorBelt&);
  ConveyorBelt& operator= (const ConveyorBelt&);
};

} // namespace WorldObjs

#endif

// EOF
