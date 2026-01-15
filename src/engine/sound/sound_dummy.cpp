// src/engine/sound/sound_dummy.cpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 2000 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#include "engine/sound/sound_dummy.hpp"

#include "pingus/globals.hpp"
#include "util/log.hpp"

namespace Sound {

void
PingusSoundDummy::real_play_sound(const std::string & filename, float /*volume*/, float /*panning*/)
{
  (void)filename;
  log_info("PingusSoundDummy::real_play_sound: {}", filename);
}

void
PingusSoundDummy::real_play_music(const std::string & filename, float /*volume*/, bool /*loop*/)
{
  (void)filename;
  log_info("PingusSoundDummy::real_play_music: {}", filename);
}

void
PingusSoundDummy::real_stop_music()
{
}

} // namespace Sound

// EOF
