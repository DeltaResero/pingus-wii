// src/util/sexpr_file_writer.cpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 2007 Jimmy Salmon
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#include "util/sexpr_file_writer.hpp"

#include <map>

#include "util/pathname.hpp"

namespace pingus {


SExprFileWriter::SExprFileWriter(std::ostream& out_) :
  out(&out_),
  level(0)
{
}

SExprFileWriter::~SExprFileWriter()
{
}

std::string
SExprFileWriter::indent()
{
  return std::string(level*2, ' ');
}

void
SExprFileWriter::begin_collection(const char* name)
{
  begin_mapping(name);
}

void
SExprFileWriter::end_collection()
{
  end_mapping();
}

void
SExprFileWriter::begin_mapping(const char* name)
{
  if (level != 0)
    (*out) << std::endl;

  (*out) << indent() << "(" << name << " ";
  ++level;
}

void
SExprFileWriter::end_mapping()
{
  --level;
  (*out) << ")";
}

void
SExprFileWriter::write_int(const char* name, int value)
{
  (*out) << "\n" << indent() << "(" << name << " " << value << ")";
}

void
SExprFileWriter::write_float(const char* name, float value)
{
  (*out) << "\n" << indent() << "(" << name << " " << value << ")";
}

void
SExprFileWriter::write_colorf(const char* name, const Color& color)
{
  (*out) << "\n" << indent() << "(" << name << " "
         << static_cast<float>(color.r)/255.0f << " "
         << static_cast<float>(color.g)/255.0f << " "
         << static_cast<float>(color.b)/255.0f << " "
         << static_cast<float>(color.a)/255.0f << ")";
}

void
SExprFileWriter::write_colori(const char* name, const Color& color)
{
  (*out) << "\n" << indent() << "(" << name << " "
         << static_cast<int>(color.r) << " "
         << static_cast<int>(color.g) << " "
         << static_cast<int>(color.b) << " "
         << static_cast<int>(color.a) << ")";
}

void
SExprFileWriter::write_bool(const char* name, bool value)
{
  (*out) << "\n" << indent() << "(" << name << " " << (value ? "#t" : "#f") << ")";
}

void
SExprFileWriter::write_string(const char* name, const std::string& value)
{
  (*out) << "\n" << indent() << "(" << name << " \"";

  for (char c : value)
  {
    if (c == '\"')
      (*out) << "\\\"";
    else if (c == '\\')
      (*out) << "\\\\";
    else
      (*out) << c;
  }

  (*out) << "\")";
}

void
SExprFileWriter::write_vector(const char* name, const Vector3f& value)
{
  (*out) << "\n" << indent() << "(" << name << " "
         << value.x << " " << value.y << " " << value.z << ")";
}

void
SExprFileWriter::write_size(const char* name, const Size& size)
{
  (*out) << "\n" << indent() << "(" << name << " " << size.width << " " << size.height << ")";
}

void
SExprFileWriter::write_vector2i(const char* name, const Vector2i& v)
{
  (*out) << "\n" << indent() << "(" << name << " " << v.x << " " << v.y << ")";
}

void
SExprFileWriter::write_path(const char* name, const Pathname& path)
{
  write_string(name, path.get_raw_path());
}


} // namespace pingus

// EOF
