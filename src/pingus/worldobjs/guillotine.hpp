// src/pingus/worldobjs/guillotine.hpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 1999 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#ifndef HEADER_PINGUS_PINGUS_WORLDOBJS_GUILLOTINE_HPP
#define HEADER_PINGUS_PINGUS_WORLDOBJS_GUILLOTINE_HPP

#include "math/vector3f.hpp"
#include "pingus/direction.hpp"
#include "pingus/worldobj.hpp"

namespace pingus::worldobjsData {
class GuillotineData;
}

class Pingu;

namespace pingus::worldobjs {

class Guillotine : public WorldObj
{
private:
  Sprite    sprite_kill_right;
  Sprite    sprite_kill_left;
  Sprite    sprite_idle;
  Vector3f  pos;
  Direction direction;

  bool killing;

public:
  Guillotine(const FileReader& reader);

  float get_z_pos() const;
  void set_pos(const Vector3f& p) { pos = p; }
  Vector3f get_pos() const { return pos; }

  void update();
  void draw(SceneContext& gc);
protected:
  void catch_pingu(Pingu*);

private:
  Guillotine(const Guillotine&);
  Guillotine& operator=(const Guillotine&);
};

} // namespace pingus::worldobjs

#endif

// EOF
