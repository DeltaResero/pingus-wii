// src/pingus/pingu_enums.hpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 1999 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#ifndef HEADER_PINGUS_PINGUS_PINGU_ENUMS_HPP
#define HEADER_PINGUS_PINGUS_PINGU_ENUMS_HPP

// Pingu "globals".  Make [deadly_velocity = 20 * sqrt("normal gravity")] so
// that the "deadly distance" is the same and therefore doesn't break levels.
const float deadly_velocity   = 10.4f;
const float terminal_velocity = 11.0f;
const int   pingu_height      = 26;

#endif

// EOF
