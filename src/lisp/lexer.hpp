// src/lisp/lexer.hpp
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Pingus - A free Lemmings clone
// Copyright (C) 2004 Matthias Braun <matze@braunis.de>
//
// Code in this file based on lispreader from Mark Probst
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#ifndef __LISPLEXER_H__
#define __LISPLEXER_H__

#include <iostream>
#include <string>

namespace pingus {


namespace lisp
{

class Lexer
{
public:
  enum TokenType {
    TOKEN_EOF,
    TOKEN_OPEN_PAREN,
    TOKEN_CLOSE_PAREN,
    TOKEN_SYMBOL,
    TOKEN_STRING,
    TOKEN_INTEGER,
    TOKEN_REAL,
    TOKEN_TRUE,
    TOKEN_FALSE
  };

  Lexer(std::istream& stream);
  ~Lexer();

  TokenType getNextToken();
  const std::string& getString() const
  { return token_string; }
  int getLineNumber() const
  { return linenumber; }

private:
  enum {
    BUFFER_SIZE = 1024
  };

  inline void nextChar();

  std::istream& stream;
  bool eof;
  int linenumber;
  char buffer[BUFFER_SIZE+1];
  char* bufend;
  char* c;
  std::string token_string;

private:
  Lexer(const Lexer&);
  Lexer & operator=(const Lexer&);
};

} // end of namespace lisp


} // namespace pingus
#endif

// EOF
