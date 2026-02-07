// src/lisp/property_iterator.hpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 2011 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#ifndef __PROPERTY_ITERATOR_HPP__
#define __PROPERTY_ITERATOR_HPP__

#include <map>
#include <string>

namespace pingus {


namespace lisp
{

struct ListEntry {
  ListEntry(const std::shared_ptr<lisp::Lisp> lisp)
    : lisp(lisp), used(false)
  {}

  const std::shared_ptr<lisp::Lisp> lisp;
  bool used;
};
typedef std::multimap<std::string, ListEntry> PropertyMap;

template<typename T>
class PropertyIterator
{
public:
  PropertyIterator()
  {
    end = i;
  }

  T* operator ->() const
  {
    return &currentval;
  }
  T operator*() const
  {
    return currentval;
  }
  bool next() {
    bool res;
    do {
      if(i == end)
        return false;
      res = property_get(i->second.lisp, currentval);
      if(res) {
        i->second.used = true;
        current_item = i->first;
      }
      ++i;
      if(res)
        return true;
    } while(true);
  }

  const std::string& item() const
  {
    return current_item;
  }

private:
  friend class Properties;

  PropertyIterator(PropertyMap::iterator begin, PropertyMap::iterator end)
    : i(begin), end(end)
  {
  }

  PropertyMap::iterator i;
  PropertyMap::iterator end;
  std::string current_item;
  T currentval;
};

}


} // namespace pingus
#endif

// EOF
