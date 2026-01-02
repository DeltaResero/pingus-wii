// test/resource_manager_test.cpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 1998-2009 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#include <functional>

#include "engine/resource/resource.hpp"
#include "engine/resource/resource_manager.hpp"
#include "engine/display/sprite.hpp"

class SpriteLoader
{
private:
  std::string m_key;

public:
  SpriteLoader(const std::string& key) :
    m_key(key)
  {}

  Sprite operator()()
  {
    return Sprite(m_key);
  }
};

int main()
{
  typedef resource::ResourceManager<std::string, Sprite, SpriteLoader> SpriteResourceManager;
  SpriteResourceManager resource_mgr;

  resource::Resource<Sprite> sprite = resource_mgr.get("image/entrances/snow");

  std::function<Sprite()> func(SpriteLoader("Hello World"));

  return 0;
}

// EOF
