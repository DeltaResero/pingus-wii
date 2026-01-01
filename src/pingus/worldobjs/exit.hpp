// src/pingus/worldobjs/exit.hpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 1999 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#ifndef HEADER_PINGUS_PINGUS_WORLDOBJS_EXIT_HPP
#define HEADER_PINGUS_PINGUS_WORLDOBJS_EXIT_HPP

#include "math/vector3f.hpp"
#include "pingus/res_descriptor.hpp"
#include "pingus/worldobj.hpp"

namespace WorldObjs {

class Exit : public WorldObj
{
private:
  ResDescriptor desc;
  Vector3f pos;
  int owner_id;

  Sprite sprite;
  Sprite flag;
  Sprite smallmap_symbol;

public:
  Exit(const FileReader& reader);
  ~Exit();

  void  on_startup ();

  void  draw (SceneContext& gc);
  void  draw_smallmap(SmallMap* smallmap);

  void  update ();

  float get_z_pos () const;
  void set_pos(const Vector3f& p) { pos = p; }
  Vector3f get_pos() const { return pos; }

private:
  Exit (const Exit&);
  Exit& operator= (const Exit&);
};

} // namespace WorldObjs

#endif

// EOF
