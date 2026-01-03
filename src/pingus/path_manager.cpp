// src/pingus/path_manager.cpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 2000 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#include "pingus/path_manager.hpp"

#include <sstream>

#include "pingus/globals.hpp"
#include "util/log.hpp"
#include "util/pathname.hpp"
#include "util/system.hpp"

PathManager g_path_manager;

PathManager::PathManager() :
  m_base_path(),
  m_paths()
{
}

PathManager::~PathManager()
{
}

void
PathManager::add_overlay_path(const std::string& path)
{
  m_paths.push_back(System::normalize_path(path));
}

void
PathManager::set_path(const std::string& path)
{
  m_base_path = path;
}

std::string
PathManager::complete(const std::string& relative_path)
{
  for(auto it = m_paths.rbegin(); it != m_paths.rend(); ++it)
  {
    std::string absolute_path = Pathname::join(*it, relative_path);
    bool exist = System::exist(absolute_path);

    log_debug("{}: {}", absolute_path, (exist ? "exist" : "missing"));

    if (exist)
    {
      return absolute_path;
    }
  }

  return Pathname::join(m_base_path, relative_path);
}

// EOF
