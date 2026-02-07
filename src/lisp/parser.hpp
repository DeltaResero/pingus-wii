// src/lisp/parser.hpp
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

#ifndef __LISPPARSER_H__
#define __LISPPARSER_H__

#include <memory>
#include <string>

#include "lexer.hpp"

namespace pingus {


namespace lisp
{

class Lisp;

class Parser
{
public:
  ~Parser();
  static std::shared_ptr<Lisp> parse(const std::string& filename);
  static std::shared_ptr<Lisp> parse(std::istream& stream, const std::string& filename = "");

private:
  friend class ParseError;

  Parser();

  std::shared_ptr<Lisp> parse();

  std::string filename;
  Lexer* lexer;
  Lexer::TokenType token;

private:
  Parser(const Parser&);
  Parser & operator=(const Parser&);
};

} // end of namespace lisp


} // namespace pingus
#endif

// EOF
