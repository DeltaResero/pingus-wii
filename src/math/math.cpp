// src/math/math.cpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 2000 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#include "math/math.hpp"

#include <cmath>
#include <cstring>

namespace pingus {

namespace Math {

static char num2hex[] = "0123456789abcdef";

std::string float2string(float value)
{
  std::string str(2*sizeof(float), '0');
  unsigned char bytes[sizeof(float)];

  std::memcpy(bytes, &value, sizeof(float));

  for(size_t i = 0; i < sizeof(float); ++i)
  {
    str[2*i + 0] = num2hex[(bytes[i] & 0xf0) >> 4];
    str[2*i + 1] = num2hex[bytes[i] & 0x0f];
  }
  return str;
}

static char hex2int(char c)
{
  if (c >= '0' && c <= '9')
    return static_cast<char>(c - '0');
  else if (c >= 'a' && c <= 'f')
    return static_cast<char>(c - 'a' + 0xa);
  else
    return 0;
}

float string2float(const std::string& str)
{
  assert(str.size() == 2*sizeof(float));

  unsigned char bytes[sizeof(float)];
  for(size_t i = 0; i < sizeof(float); ++i)
  {
    bytes[i] = static_cast<unsigned char>((hex2int(str[2*i+0]) << 4) | hex2int(str[2*i+1]));
  }

  float value;
  std::memcpy(&value, bytes, sizeof(float));
  return value;
}

} // namespace Math


} // namespace pingus

// EOF
