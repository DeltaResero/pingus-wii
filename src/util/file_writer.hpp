// src/util/file_writer.hpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 2002 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#ifndef HEADER_PINGUS_UTIL_FILE_WRITER_HPP
#define HEADER_PINGUS_UTIL_FILE_WRITER_HPP

#include <string>

class Vector3f;
class Size;
class Color;
class Pathname;

/** Interface to write out name/value pairs out of some kind of file or
    structure */
class FileWriter
{
private:
public:
  virtual ~FileWriter() {}

  virtual void begin_section (const char* name) =0;
  virtual void end_section () =0;

  virtual void write_int    (const char* name, int) =0;
  virtual void write_float  (const char* name, float) =0;
  virtual void write_colorf (const char* name, const Color&) =0;
  virtual void write_colori (const char* name, const Color&) =0;
  virtual void write_bool   (const char* name, bool) =0;
  virtual void write_string (const char* name, const std::string&) =0;
  virtual void write_vector (const char* name, const Vector3f&) =0;
  virtual void write_size   (const char* name, const Size&) =0;
  virtual void write_vector2i(const char* name, const Vector2i&) =0;
  virtual void write_path   (const char* name, const Pathname&) =0;

  template<class E, class T>
  void write_enum  (const char* name, E& value, T string2enum) const
  {
    write_string(name, string2enum(value));
  }
};

#endif

// EOF
