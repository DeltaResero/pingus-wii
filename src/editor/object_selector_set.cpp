// src/editor/object_selector_set.cpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 2007 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#include "editor/object_selector_set.hpp"

namespace pingus::editor {

ObjectSelectorSet::ObjectSelectorSet(ObjectSelectorList* list_, int thumb_w, int thumb_h) :
  list(list_),
  thumb_size(thumb_w, thumb_h),
  objects(),
  offset(0)
{
}

ObjectSelectorSet::~ObjectSelectorSet()
{
  for(Objects::iterator i = objects.begin(); i != objects.end(); ++i)
    delete (*i);
}

void
ObjectSelectorSet::add(ObjectSelectorList::Object* obj)
{
  objects.push_back(obj);
}

int
ObjectSelectorSet::get_width() const
{
  return list->get_rect().get_width() / thumb_size.width;
}

int
ObjectSelectorSet::get_height() const
{
  return (static_cast<int>(objects.size()) / get_width()) + ((static_cast<int>(objects.size()) % get_width() > 0) ? 1 : 0);
}

} // namespace pingus::editor

// EOF
