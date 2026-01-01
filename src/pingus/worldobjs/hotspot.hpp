// src/pingus/worldobjs/hotspot.hpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 1999 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#ifndef HEADER_PINGUS_PINGUS_WORLDOBJS_HOTSPOT_HPP
#define HEADER_PINGUS_PINGUS_WORLDOBJS_HOTSPOT_HPP

#include "math/vector3f.hpp"
#include "pingus/worldobj.hpp"

namespace WorldObjsData {
class HotspotData;
}

namespace WorldObjs {

class Hotspot : public WorldObj
{
private:
  Sprite   sprite;
  float    para;
  Vector3f pos;

public:
  Hotspot(const FileReader& reader);
  ~Hotspot();

  void  draw(SceneContext& gc);
  void  update();
  float get_z_pos() const;
  void set_pos(const Vector3f& p) { pos = p; }
  Vector3f get_pos() const { return pos; }

private:
  Hotspot (const Hotspot&);
  Hotspot& operator= (const Hotspot&);
};

} // namespace WorldObjs

#endif

// EOF
