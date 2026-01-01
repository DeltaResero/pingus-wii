// src/pingus/savegame_manager.hpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 2002 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#ifndef HEADER_PINGUS_PINGUS_SAVEGAME_MANAGER_HPP
#define HEADER_PINGUS_PINGUS_SAVEGAME_MANAGER_HPP

#include "pingus/savegame.hpp"

class SavegameManager
{
private:
  static SavegameManager* instance_;
  typedef std::vector<Savegame*> SavegameTable;

  std::string   filename;
  SavegameTable savegames;

  SavegameTable::iterator find(const std::string& filename);

public:
  static SavegameManager* instance();
  SavegameManager(const std::string& filename);
  ~SavegameManager();

  Savegame* get(const std::string& filename);

  void store(Savegame&);

  /** Write the current savegames down to file */
  void flush();

private:
  SavegameManager (const SavegameManager&);
  SavegameManager& operator= (const SavegameManager&);
};

#endif

// EOF
