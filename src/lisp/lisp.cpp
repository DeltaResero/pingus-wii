// src/lisp/lisp.cpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 2004 Matthias Braun <matze@braunis.de>
//
// Originally from: TuxKart - a fun racing game with go-kart
// Code in this file based on lispreader from Mark Probst
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#include <string.h>
#include <ostream>

#include "lisp.hpp"

namespace pingus {


namespace lisp
{

Lisp::Lisp(int val) :
  v(val), type(TYPE_INT)
{
}

Lisp::Lisp(float val) :
  v(val), type(TYPE_FLOAT)
{
}

Lisp::Lisp(bool val) :
  v(val), type(TYPE_BOOL)
{
}

Lisp::Lisp(LispType newtype, std::string str) :
  v(std::move(str)), type(newtype)
{
  assert(newtype == TYPE_SYMBOL || type == TYPE_STRING);
}

Lisp::Lisp(std::vector<std::shared_ptr<Lisp> > list_elements) :
  v(std::move(list_elements)), type(TYPE_LIST)
{
}

void
Lisp::print(std::ostream& out, int indent) const
{
  for(int i = 0; i < indent; ++i)
    out << ' ';

  switch(type) {
    case TYPE_LIST:
      out << "(\n";
      {
        const auto& list = std::get<std::vector<std::shared_ptr<Lisp>>>(v);
        for(size_t i = 0; i < list.size(); ++i)
          list[i]->print(out, indent+2);
      }
      for(int i = 0; i < indent; ++i)
        out << ' ';
      out << ")";
      break;
    case TYPE_STRING:
      out << '\'' << std::get<std::string>(v) << '\'';
      break;
    case TYPE_INT:
      out << std::get<int>(v);
      break;
    case TYPE_FLOAT:
      out << std::get<float>(v);
      break;
    case TYPE_SYMBOL:
      out << std::get<std::string>(v);
      break;
    case TYPE_BOOL:
      out << (std::get<bool>(v) ? "true" : "false");
      break;
    default:
      out << "UNKNOWN?!?";
      break;
  }
  out << '\n';
}

} // end of namespace lisp


} // namespace pingus

// EOF
