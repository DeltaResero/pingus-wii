// src/engine/resource/resource_manager.hpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 1998-2011 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#ifndef HEADER_PINGUS_ENGINE_RESOURCE_RESOURCE_MANAGER_HPP
#define HEADER_PINGUS_ENGINE_RESOURCE_RESOURCE_MANAGER_HPP

#include <unordered_map>

#include "engine/resource/resource.hpp"

namespace pingus {

namespace resource {

template<typename Key,
         typename Data,
         typename Loader>
class ResourceManager
{
private:
  std::unordered_map<Key, Resource<Data> > m_resources;

public:
  ResourceManager() :
    m_resources()
  {
  }

  ~ResourceManager()
  {
  }

  Resource<Data> get(const Key& key)
  {
    auto it = m_resources.find(key);
    if (it != m_resources.end())
    {
      return it->second;
    }
    else
    {
      auto [new_it, inserted] = m_resources.emplace(key, Resource<Data>(Loader(key)));
      return new_it->second;
    }
  }

  void reload()
  {
    for(const auto& pair : m_resources)
    {
      if (pair.second)
      {
        pair.second.load();
      }
    }
  }

private:
  ResourceManager(const ResourceManager&);
  ResourceManager& operator=(const ResourceManager&);
};

} // namespace resource


} // namespace pingus
#endif

// EOF
