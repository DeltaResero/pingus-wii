// src/lisp/getters.cpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 2011 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#include "getters.hpp"

namespace pingus {


namespace lisp
{

bool get(const Lisp* lisp, bool& val)
{
  if(lisp->get_type() != Lisp::TYPE_BOOL)
    return false;
  val = lisp->get_bool();
  return true;
}

bool get(const Lisp* lisp, float& val)
{
  if(lisp->get_type() == Lisp::TYPE_INT)
    val = static_cast<float>(lisp->get_int());
  else if(lisp->get_type() == Lisp::TYPE_FLOAT)
    val = lisp->get_float();
  else
    return false;
  return true;
}

bool get(const Lisp* lisp, int& val)
{
  if(lisp->get_type() != Lisp::TYPE_INT)
    return false;
  val = lisp->get_int();
  return true;
}

bool get(const Lisp* lisp, std::string& val)
{
  if(lisp->get_type() != Lisp::TYPE_STRING)
    return false;
  val = lisp->get_string();
  return true;
}

}


} // namespace pingus

// EOF
