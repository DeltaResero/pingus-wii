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
  v(), type(TYPE_INT)
{
  v.int_ = val;
}

Lisp::Lisp(float val) :
  v(), type(TYPE_FLOAT)
{
  v.float_ = val;
}

Lisp::Lisp(bool val) :
  v(), type(TYPE_BOOL)
{
  v.bool_ = val;
}

Lisp::Lisp(LispType newtype, const std::string& str) :
  v(), type(newtype)
{
  assert(newtype == TYPE_SYMBOL || type == TYPE_STRING);
  v.string = new char[str.size()+1];
  memcpy(v.string, str.c_str(), str.size()+1);
}

Lisp::Lisp(const std::vector<std::shared_ptr<Lisp> >& list_elements) :
  v(), type(TYPE_LIST)
{
  v.list.size = list_elements.size();
  v.list.entries = new std::shared_ptr<Lisp> [v.list.size];
  for(size_t i = 0; i < v.list.size; ++i) {
    v.list.entries[i] = list_elements[i];
  }
}

Lisp::~Lisp()
{
  if(type == TYPE_SYMBOL || type == TYPE_STRING) {
    delete[] v.string;
  } else if(type == TYPE_LIST) {
    delete[] v.list.entries;
  }
}

void
Lisp::print(std::ostream& out, int indent) const
{
  for(int i = 0; i < indent; ++i)
    out << ' ';

  switch(type) {
    case TYPE_LIST:
      out << "(\n";
      for(size_t i = 0; i < v.list.size; ++i)
        v.list.entries[i]->print(out, indent+2);
      for(int i = 0; i < indent; ++i)
        out << ' ';
      out << ")";
      break;
    case TYPE_STRING:
      out << '\'' << v.string << '\'';
      break;
    case TYPE_INT:
      out << v.int_;
      break;
    case TYPE_FLOAT:
      out << v.float_;
      break;
    case TYPE_SYMBOL:
      out << v.string;
      break;
    case TYPE_BOOL:
      out << (v.bool_ ? "true" : "false");
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
