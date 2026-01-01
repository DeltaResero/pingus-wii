// src/engine/display/delta/rect_merger.hpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 2008 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#ifndef HEADER_PINGUS_ENGINE_DISPLAY_RECT_MERGER_HPP
#define HEADER_PINGUS_ENGINE_DISPLAY_RECT_MERGER_HPP

#include <vector>

#include "math/rect.hpp"

void merge_rectangles(const std::vector<Rect>& rects_in, std::vector<Rect>& rects_out);

#endif

// EOF
