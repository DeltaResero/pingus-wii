// src/pingus/result.hpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 1999 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#ifndef HEADER_PINGUS_PINGUS_RESULT_HPP
#define HEADER_PINGUS_PINGUS_RESULT_HPP

#include "pingus/pingus_level.hpp"

/** Result of a Pingus game */
struct Result
{
  /** Leveldata */
  PingusLevel plf;

  /** Total number of that got saved */
  int saved;

  /** Total number of that got killed */
  int killed;

  /** Total number of Pingus */
  int total;

  /** Time used to finish this level */
  int used_time;

  /** Maximum time available for this level */
  int max_time;

  /** Number of Pingus needed to save */
  int needed;

  Result() :
    plf(),
    saved(),
    killed(),
    total(),
    used_time(),
    max_time(),
    needed()
  {}

  bool success() {
    return (saved >= needed);
  }
};

#endif

// EOF
