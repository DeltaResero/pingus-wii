// src/pingus/worldobjs/liquid.hpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 1999 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#ifndef HEADER_PINGUS_PINGUS_WORLDOBJS_LIQUID_HPP
#define HEADER_PINGUS_PINGUS_WORLDOBJS_LIQUID_HPP

#include "math/vector3f.hpp"
#include "pingus/res_descriptor.hpp"
#include "pingus/worldobj.hpp"

namespace pingus::worldobjs {

class Liquid : public WorldObj
{
private:
  Sprite sur;

  Vector3f pos;

  /** Cause to interpret the width in pixels instead of tiles */
  bool old_width_handling;

  int width;

  /** Number of miliseconds between frames */
  int speed;

public:
  Liquid(const FileReader& reader);

  float get_z_pos () const;
  void set_pos(const Vector3f& p) { pos = p; }
  Vector3f get_pos() const { return pos; }

  void  on_startup();
  void  draw      (SceneContext& gc);
  void  update();

private:
  Liquid (const Liquid&);
  Liquid& operator= (const Liquid&);
};

} // namespace pingus::worldobjs

#endif

// EOF
