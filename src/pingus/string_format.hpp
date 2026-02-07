// src/pingus/string_format.hpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 2002 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#ifndef HEADER_PINGUS_PINGUS_STRING_FORMAT_HPP
#define HEADER_PINGUS_PINGUS_STRING_FORMAT_HPP

#include <string>

namespace pingus {

class Font;

class StringFormat
{
public:
  /** Takes a string \a text and wraps it into multiple lines, each
      less then \a width long. Line wrappings happens TeX style, i.e.
      a double newline marks a newline, while other whitespace is
      joined to a single space. */
  static std::string break_line(const std::string& text, int width, const Font& font);
};


} // namespace pingus
#endif

// EOF
