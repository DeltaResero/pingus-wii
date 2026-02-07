// src/pingus/fps_counter.hpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 2000 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#ifndef HEADER_PINGUS_PINGUS_FPS_COUNTER_HPP
#define HEADER_PINGUS_PINGUS_FPS_COUNTER_HPP

#include <string>

namespace pingus {

class FPSCounter
{
private:
  /** A string holding the current value of frames + "fps", its
      updated every second */
  std::string fps_string;

  /** Count the fps until one second is passed */
  int fps_count;

  /** The time were the last fps string update was performent */
  unsigned int start_time;

  /** Check if one second is passed and if that is the case, update
      everything then. */
  void update_fps_counter();

public:
  FPSCounter();
  ~FPSCounter();

  void draw();

private:
  FPSCounter (const FPSCounter&);
  FPSCounter& operator= (const FPSCounter&);
};


} // namespace pingus
#endif

// EOF
