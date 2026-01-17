// src/pingus/worldobj_factory.hpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 2000 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#ifndef HEADER_PINGUS_PINGUS_WORLDOBJ_FACTORY_HPP
#define HEADER_PINGUS_PINGUS_WORLDOBJ_FACTORY_HPP

#include <map>
#include <vector>

#include "util/file_reader.hpp"

class WorldObj;
class WorldObjAbstractFactory;

/** WorldObjFactory which can be used to create all kinds of
    WorldObj's by given its id */
class WorldObjFactory
{
private:
  std::map<std::string, std::unique_ptr<WorldObjAbstractFactory> > factories;

  static std::unique_ptr<WorldObjFactory> instance_;

  WorldObjFactory ();
  void free_factories();

public:
  /** Return the singleton instance */
  static WorldObjFactory& instance();
  static void deinit();
  /** Register a factory for object creation */
  void register_factory(const std::string& id,
                        std::unique_ptr<WorldObjAbstractFactory> factory);

  /** Create a WorldObj type from a given piece of xml, use the
      'type' property for determinating the object type. */
  std::vector<WorldObj*> create(const FileReader& reader);

private:
  WorldObjFactory (const WorldObjFactory&);
  WorldObjFactory& operator= (const WorldObjFactory&);
};

#endif

// EOF
