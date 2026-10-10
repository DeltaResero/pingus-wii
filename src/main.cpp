// src/main.cpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 1998-2009 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#include <SDL2/SDL.h>

#include "pingus/pingus_main.hpp"
#ifdef __WII__
#include "util/wii.hpp"
#endif

int main(int argc, char** argv)
{
#ifdef __WII__
  pingus::Wii::take_power_buttons();
#endif

  int result = pingus::PingusMain().run(argc, argv);

#ifdef __WII__
  // PingusMain has saved everything by now.
  pingus::Wii::power_off_if_requested();
#endif

  return result;
}

// EOF
