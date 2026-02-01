// src/pingus/worldobjs/fake_exit.hpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 1999 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#ifndef HEADER_PINGUS_PINGUS_WORLDOBJS_FAKE_EXIT_HPP
#define HEADER_PINGUS_PINGUS_WORLDOBJS_FAKE_EXIT_HPP

#include "math/vector3f.hpp"
#include "pingus/worldobj.hpp"

class Pingu;

namespace pingus::worldobjsData {
class FakeExitData;
} // namespace pingus::worldobjsData

namespace pingus::worldobjs {

/** The FakeExit is an object that looks similar to the traditional
    IceExit, but is really a trap that smashed all pingus that try to
    enter it. */
class FakeExit : public WorldObj
{
private:
  Sprite   surface;
  Sprite   smallmap_symbol;

  Vector3f pos;

  bool smashing;

public:
  FakeExit(const FileReader& reader);

  float get_z_pos () const;
  void set_pos(const Vector3f& p) { pos = p; }
  Vector3f get_pos() const { return pos; }

  void draw (SceneContext& gc);

  void update ();

  /** Draws an exit symbol on to the small map. */
  void draw_smallmap(SmallMap* smallmap);

private:
  void catch_pingu (Pingu*);

  FakeExit (const FakeExit&);
  FakeExit& operator= (const FakeExit&);
};

} // namespace pingus::worldobjs

#endif

// EOF
