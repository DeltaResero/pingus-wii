// src/pingus/res_descriptor.cpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 1999 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#include "pingus/res_descriptor.hpp"

#include <ostream>

namespace pingus {

/*
  uri -> file:///home/ingo/.pingus/images/...
  uri -> resource://core/result/ok
  uri -> file://bla.png (relative to ~/.pingus/images/)
  ResDescriptor(const std::string& uri);
*/

ResDescriptor::ResDescriptor() :
  res_name(),
  modifier(ResourceModifier::ROT0)
{
}

ResDescriptor::ResDescriptor(const std::string& res_name_)
  : res_name(res_name_),
    modifier(ResourceModifier::ROT0)
{
}

ResDescriptor::ResDescriptor(const std::string& arg_res_name,
                             ResourceModifier::Enum arg_modifier)
  : res_name(arg_res_name),
    modifier(arg_modifier)
{
}

bool
ResDescriptor::operator<(const ResDescriptor& res_desc) const
{
  return (res_name < res_desc.res_name) && (modifier < res_desc.modifier);
}

std::ostream& operator<<(std::ostream& s, const ResDescriptor& desc)
{
  return s << "[" << desc.res_name << ", "
           << ResourceModifier::to_string(desc.modifier) << "]";
}


} // namespace pingus

// EOF
