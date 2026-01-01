// src/pingus/game_time.cpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 1999 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#include "pingus/game_time.hpp"

#include <stdio.h>

#include "gettext.h"
#include "pingus/globals.hpp"

int
GameTime::seconds_to_ticks(int seconds)
{
  if (seconds < 0)
  {
    return seconds;
  }
  else
  {
    return seconds * 1000 / globals::game_speed;
  }
}

int
GameTime::ticks_to_seconds(int ticks)
{
  if (ticks < 0)
  {
    return ticks;
  }
  else
  {
    return ticks * globals::game_speed / 1000;
  }
}

std::string
GameTime::ticks_to_realtime_string(int ticks)
{
  if (ticks == -1)
  {
    return _("unlimited");
  }
  else
  {
    const int time_str_size = 20;
    char time_str[time_str_size];

    int total_seconds = ticks_to_seconds(ticks);
    int seconds       = total_seconds % 60;
    int minutes       = total_seconds / 60;

    // Stop displaying negative seconds, which can happen if armageddon is
    // clicked with 1 second left.
    if (seconds < 0)
      seconds = 0;

    snprintf(time_str, time_str_size, "%2d:%02d", minutes, seconds);

    return time_str;
  }
}

// EOF
