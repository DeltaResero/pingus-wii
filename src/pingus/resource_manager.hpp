// src/pingus/resource_manager.hpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 2005 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#ifndef HEADER_PINGUS_PINGUS_RESOURCE_MANAGER_HPP
#define HEADER_PINGUS_PINGUS_RESOURCE_MANAGER_HPP

#include <map>
#include <set>
#include <memory>
#include <string>
#include <vector>

class FileReader;
class Pathname;
class SpriteDescription;

class ResourceManager
{
public:
  typedef std::map<std::string, std::shared_ptr<SpriteDescription> > Resources;

private:
  Resources m_cache;
  std::set<std::string> m_resources;

public:
  ResourceManager();
  ~ResourceManager();

  void add_resources_from_directory(const Pathname& path);

  /** Returns a pointer to the requested SpriteDescription or 0 if it's not found */
  SpriteDescription* get_sprite_description(const std::string& name);
  std::shared_ptr<SpriteDescription> get_sprite_description_from_file(const std::string& name);

  std::vector<std::string> get_section(const std::string& name);

private:
  ResourceManager (const ResourceManager&);
  ResourceManager& operator= (const ResourceManager&);
};

#endif

// EOF
