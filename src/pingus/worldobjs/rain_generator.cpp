// src/pingus/worldobjs/rain_generator.cpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 2000 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#include "pingus/worldobjs/rain_generator.hpp"

#include "engine/display/scene_context.hpp"
#include "engine/sound/sound.hpp"
#include "pingus/particles/rain_particle_holder.hpp"
#include "pingus/world.hpp"
#include "util/log.hpp"

namespace pingus::worldobjs {

RainGenerator::RainGenerator (const FileReader& /*reader*/) :
  do_thunder(false),
  thunder_count (0),
  waiter_count()
{
}

RainGenerator::~RainGenerator ()
{
}

void
RainGenerator::draw (SceneContext& gc)
{
  if (do_thunder)
  {
    if (thunder_count < 0.0f) {
      do_thunder = false;
      thunder_count = 0.0f;
      waiter_count = 1.0f;
    }

    gc.color().fill_screen(Color(255, 255, 255, static_cast<uint8_t>(thunder_count*255)));
  }
}

void
RainGenerator::update()
{
  if (waiter_count < 0.0f && rand () % 150 == 0)
  {
    log_info("Doing thunder");
    do_thunder = true;
    thunder_count = 1.0f;
    waiter_count = 1.0f;
    pingus::sound::PingusSound::play_sound ("thunder");
  }

  if (do_thunder)
    thunder_count -= 10.0f * 0.025f;

  waiter_count -= 20.0f * 0.025f;

  for (int i=0; i < 16; ++i)
    world->get_rain_particle_holder()->add_particle(rand() % (world->get_width() * 2), -32);
}

} // namespace pingus::worldobjs

// EOF
