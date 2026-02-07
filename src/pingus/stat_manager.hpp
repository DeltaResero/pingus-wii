// src/pingus/stat_manager.hpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 2002 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#ifndef HEADER_PINGUS_PINGUS_STAT_MANAGER_HPP
#define HEADER_PINGUS_PINGUS_STAT_MANAGER_HPP

#include <map>
#include <string>

namespace pingus {

class StatManager
{
private:
  static StatManager* instance_;

  /** File from which it loads/saves the stats */
  std::string statfilename;
  typedef std::map<std::string, std::string> Table;
  Table stats;

public:
  static StatManager* instance();

  /** Returns the resource name of a worldmap - strips out everything except after
      the last '/' in the full path + filename, and converts periods to dashes */
  static std::string get_resname(const std::string& filename);

public:
  StatManager(const std::string& filename);
  ~StatManager();

  bool get_int   (const std::string&, int& value);
  bool get_bool  (const std::string&, bool& value);
  bool get_string(const std::string&, std::string& vlaue);

  void set_string(const std::string& name, const std::string& value);
  void set_int   (const std::string& name, int value);
  void set_bool  (const std::string& name, bool value);

  /** Write the current status down */
  void flush();

  void load(const std::string& filename);
  void save(const std::string& filename);
private:
  StatManager (const StatManager&);
  StatManager& operator= (const StatManager&);
};


} // namespace pingus
#endif

// EOF
