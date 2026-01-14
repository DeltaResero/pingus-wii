// src/pingus/worldobjs/rain_generator.hpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 2000 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#ifndef HEADER_PINGUS_PINGUS_WORLDOBJS_RAIN_GENERATOR_HPP
#define HEADER_PINGUS_PINGUS_WORLDOBJS_RAIN_GENERATOR_HPP

#include "pingus/worldobj.hpp"

namespace WorldObjs {

class RainGenerator : public WorldObj
{
private:
  bool  do_thunder;
  float thunder_count;
  float waiter_count;

public:
  RainGenerator(const FileReader& reader);
  ~RainGenerator();

  void update ();
  void draw (SceneContext& gc);
  float get_z_pos () const { return 1000; }
  void set_pos(const Vector3f& /*p*/) {}
  Vector3f get_pos() const { return Vector3f(); }

private:
  RainGenerator (const RainGenerator&);
  RainGenerator& operator= (const RainGenerator&);
};

} // namespace WorldObjs

#endif

// EOF
