// src/pingus/particles/pingu_particle_holder.hpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 1999 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#ifndef HEADER_PINGUS_PINGUS_PARTICLES_PINGU_PARTICLE_HOLDER_HPP
#define HEADER_PINGUS_PINGUS_PARTICLES_PINGU_PARTICLE_HOLDER_HPP

#include <vector>

#include "engine/display/sprite.hpp"
#include "math/vector3f.hpp"
#include "pingus/worldobj.hpp"

class SceneContext;

namespace Particles {

class PinguParticleHolder : public WorldObj
{
  struct PinguParticle {
    int  livetime;
    bool use_frame2;
    /// The current position of the particle
    Vector3f pos;

    /// The velocity of the particle
    Vector3f velocity;

    PinguParticle (int x, int y);
  };

private:
  Sprite surface;
  std::vector<PinguParticle> particles;

public:
  PinguParticleHolder ();

  void add_particle (int x, int y);

  float get_z_pos () const { return 1000.0f; }
  void set_pos(const Vector3f& /*p*/) { }
  Vector3f get_pos() const { return Vector3f(); }

  /// Let the particle move
  void update ();

  /// Draw the particle with the correct zoom resize
  void draw (SceneContext& gc);

private:
  PinguParticleHolder (const PinguParticleHolder&);
  PinguParticleHolder& operator= (const PinguParticleHolder&);
};

} // namespace Particles

#endif

// EOF
