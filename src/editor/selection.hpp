// src/editor/selection.hpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 1998-2011 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#ifndef HEADER_PINGUS_EDITOR_SELECTION_HPP
#define HEADER_PINGUS_EDITOR_SELECTION_HPP

#include <set>

#include "editor/level_obj_ptr.hpp"

namespace Editor {

typedef std::set<LevelObjPtr> Selection;

} // namespace Editor

#endif

// EOF
