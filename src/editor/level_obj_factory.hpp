// src/editor/level_obj_factory.hpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 1998-2011 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#ifndef HEADER_PINGUS_EDITOR_LEVEL_OBJ_FACTORY_HPP
#define HEADER_PINGUS_EDITOR_LEVEL_OBJ_FACTORY_HPP

#include "editor/level_obj_ptr.hpp"

namespace pingus {
class FileReader;
}

namespace pingus::editor {

class LevelObjFactory
{
private:
public:
  static LevelObjPtr create(const pingus::FileReader &reader);

private:
  LevelObjFactory(const LevelObjFactory&);
  LevelObjFactory& operator=(const LevelObjFactory&);
};

} // namespace pingus::editor

#endif

// EOF
