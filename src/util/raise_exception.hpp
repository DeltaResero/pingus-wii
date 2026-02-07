// src/util/raise_exception.hpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 1998-2011 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#ifndef HEADER_PINGUS_UTIL_RAISE_EXCEPTION_HPP
#define HEADER_PINGUS_UTIL_RAISE_EXCEPTION_HPP

#include <sstream>
#include <stdexcept>
#include <string>

#include "util/log.hpp"

namespace pingus {

inline std::string raise_log_pretty_print(const std::string &str)
{
  // FIXME: very basic, might not work with complex return types
  std::string::size_type function_start = 0;
  for (std::string::size_type i = 0; i < str.size(); ++i)
  {
    if (str[i] == ' ')
    {
      function_start = i+1;
    }
    else if (str[i] == '(')
    {
      return str.substr(function_start, i - function_start) + "()";
    }
  }

  return str.substr(function_start);
}

#define raise_exception(type, expr)                                            \
  do {                                                                         \
    std::ostringstream b42465a70169;                                           \
    b42465a70169 << raise_log_pretty_print(__PRETTY_FUNCTION__) << ": "        \
                 << expr;                                                      \
    throw type(b42465a70169.str());                                            \
  } while (false)

#define raise_error(expr)                                                      \
  do {                                                                         \
    std::ostringstream b42465a70169;                                           \
    b42465a70169 << raise_log_pretty_print(__PRETTY_FUNCTION__) << ": "        \
                 << expr;                                                      \
    throw std::runtime_error(b42465a70169.str());                              \
  } while (false)

} // namespace pingus
#endif

// EOF
