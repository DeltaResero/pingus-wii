// src/util/string_util.hpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 2005 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#ifndef HEADER_PINGUS_UTIL_STRING_UTIL_HPP
#define HEADER_PINGUS_UTIL_STRING_UTIL_HPP

#include <sstream>

class StringUtil
{
private:
public:
  static std::string to_lower(const std::string &str);
  static std::string to_upper(const std::string &str);

  template<class T>
  static T to(const std::string& s, const T& val = T())
  {
    T tmp = val;
    std::istringstream str(s);
    str >> tmp;
    return tmp;
  }

  template<class T>
  static bool from_string(const std::string& s, T& t)
  {
    std::istringstream str(s);
    T tmp;
    str >> tmp;
    if (str.fail())
    {
      return false;
    }
    else
    {
      t = tmp;
      return true;
    }
    return false;
  }

  template<class T>
  static std::string to_string(const T& t)
  {
    std::ostringstream str;
    str << t;
    return str.str();
  }

  static bool has_suffix(const std::string& str, const std::string& suffix)
  {
    if (str.length() >= suffix.length())
      return str.compare(str.length() - suffix.length(), suffix.length(), suffix) == 0;
    else
      return false;
  }

  static bool has_prefix(const std::string& str, const std::string prefix)
  {
    if (str.length() < prefix.length())
      return false;
    else
      return str.compare(0, prefix.length(), prefix) == 0;
  }

private:
  StringUtil ();
  StringUtil (const StringUtil&);
  StringUtil& operator= (const StringUtil&);
};

#endif

// EOF
