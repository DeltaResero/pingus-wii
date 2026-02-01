// src/pingus/particles/smoke_particle_holder.cpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 1999 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#include "pingus/particles/smoke_particle_holder.hpp"

#include "engine/display/scene_context.hpp"

namespace pingus::particles {

SmokeParticleHolder::SmokeParticle::SmokeParticle (float x, float y, float vel_x, float vel_y) :
  time(),
  livetime(),
  use_surf2(),
  pos(Vector3f(x,y)),
  velocity(Vector3f(vel_x, vel_y))
{
  time = livetime = 25 + (rand() % 10);
  use_surf2 = rand() % 2;
}

SmokeParticleHolder::SmokeParticleHolder ()
  : surf1("particles/smoke"),
    surf2("particles/smoke2"),
    particles()
{
}

void
SmokeParticleHolder::add_particle (float x, float y, float vel_x, float vel_y)
{
  // search for dead entry to replace
  for (std::vector<SmokeParticle>::iterator it=particles.begin(); it != particles.end(); ++it)
    if (!it->livetime)
    {
      *it = SmokeParticle(x, y, vel_x, vel_y);
      return;
    }

  // create new entry
  particles.push_back(SmokeParticle(x, y, vel_x, vel_y));
}

void
SmokeParticleHolder::update ()
{
  // update all contained particles
  for (std::vector<SmokeParticle>::iterator it=particles.begin(); it != particles.end(); ++it)
  {
    // skip dead particles
    if (!it->livetime)
      continue;

    it->pos.x += it->velocity.x;
    it->pos.y += it->velocity.y;
    it->pos.z = get_z_pos();

    --it->livetime;
  }
}

void
SmokeParticleHolder::draw (SceneContext& gc)
{
  for (std::vector<SmokeParticle>::iterator it=particles.begin(); it != particles.end(); ++it)
  {
    if (!it->livetime)
      continue;

    if (!it->use_surf2)
      gc.color().draw(surf1, it->pos);
    else
      gc.color().draw(surf2, it->pos);
  }
}

} // namespace pingus::particles

// EOF
