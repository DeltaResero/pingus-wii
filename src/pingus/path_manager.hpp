// src/pingus/path_manager.hpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 2000 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#ifndef HEADER_PINGUS_PINGUS_PATH_MANAGER_HPP
#define HEADER_PINGUS_PINGUS_PATH_MANAGER_HPP

#include <list>
#include <string>
#include <vector>

class PathManager
{
private:
  std::string m_base_path;
  std::vector<std::string> m_paths;

public:
  PathManager();
  ~PathManager();

  /** Adds an overlay path, overlay path are search and used instead
      of the main datadir when a file is found in the same relative
      location */
  void add_overlay_path(const std::string& path);

  /** Set the main datadir */
  void set_path(const std::string& path);

  std::string get_path() const { return m_base_path; }

  std::vector<std::string> get_paths() const { return m_paths; }

  /** Complete a releative path to the absolute path, the returned
      path contains a trailing slash */
  std::string complete(const std::string& relative_path);
};

extern PathManager g_path_manager;

#endif

// EOF
