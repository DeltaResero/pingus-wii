// src/lisp/lexer.cpp
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

#include <sstream>
#include <stdexcept>
#include <string.h>

#include "lexer.hpp"

namespace pingus {


namespace lisp
{

class EOFException
{
};

Lexer::Lexer(std::istream& newstream) :
  stream(newstream),
  eof(false),
  linenumber(1),
  bufend(),
  c(),
  token_string()
{
  try {
    // trigger a refill of the buffer
    c = 0;
    bufend = 0;
    nextChar();
  } catch(EOFException&) {
  }
}

Lexer::~Lexer()
{
}

void
Lexer::nextChar()
{
  ++c;
  if(c >= bufend) {
    if(eof)
      throw EOFException();
    stream.read(buffer, BUFFER_SIZE);
    size_t bytes_read = stream.gcount();

    c = buffer;
    bufend = buffer + bytes_read;

    // the following is a hack that appends an additional ' ' at the end of
    // the file to avoid problems when parsing symbols/elements and a sudden
    // EOF. This is faster than relying on unget and IMO also nicer.
    if(bytes_read == 0 || stream.eof()) {
      eof = true;
      *bufend = ' ';
      ++bufend;
    }
  }
}

Lexer::TokenType
Lexer::getNextToken()
{
  static const char* delims = "\"();";

  try {
    while(isspace(*c)) {
      if(*c == '\n')
        ++linenumber;
      nextChar();
    };

    token_string.clear();

    switch(*c) {
      case ';': // comment
        while(true) {
          nextChar();
          if(*c == '\n') {
            ++linenumber;
            break;
          }
        }
        return getNextToken(); // and again
      case '(':
        nextChar();
        return TOKEN_OPEN_PAREN;
      case ')':
        nextChar();
        return TOKEN_CLOSE_PAREN;
      case '"': {  // string
        int startline = linenumber;
        try {
          while(1) {
            nextChar();
            if(*c == '"')
              break;
            else if(*c == '\n')
              linenumber++;
            else if(*c == '\\') {
              nextChar();
              switch(*c) {
                case 'n':
                  *c = '\n';
                  break;
                case 't':
                  *c = '\t';
                  break;
                case '\"':
                  *c = '\"';
                  break;
                case '\\':
                  *c = '\\';
                  break;
              }
            }
            token_string += *c;
          }
        } catch(EOFException& ) {
          std::stringstream msg;
          msg << "Parse error in line " << startline << ": "
              << "EOF while parsing string.";
          throw std::runtime_error(msg.str());
        }
        nextChar();
        return TOKEN_STRING;
      }
      case '#': // constant
        try {
          nextChar();

          while(isalnum(*c) || *c == '_') {
            token_string += *c;
            nextChar();
          }
        } catch(EOFException& ) {
          std::stringstream msg;
          msg << "Parse Error in line " << linenumber << ": "
              << "EOF while parsing constant.";
          throw std::runtime_error(msg.str());
        }

        if(token_string == "t")
          return TOKEN_TRUE;
        if(token_string == "f")
          return TOKEN_FALSE;

        // we only handle #t and #f constants at the moment...

        {
          std::stringstream msg;
          msg << "Parse Error in line " << linenumber << ": "
              << "Unknown constant '" << token_string << "'.";
          throw std::runtime_error(msg.str());
        }

      default:
        if(isdigit(*c) || *c == '-' || *c == '.') {
          bool have_nondigits = false;
          bool have_digits = false;
          int have_floating_point = 0;

          do {
            if(isdigit(*c))
              have_digits = true;
            else if(*c == '.')
              ++have_floating_point;
            else if(isalnum(*c) || *c == '_')
              have_nondigits = true;

            token_string += *c;

            nextChar();
          } while(!isspace(*c) && !strchr(delims, *c));

          // no nextChar

          if(have_nondigits || !have_digits || have_floating_point > 1)
            return TOKEN_SYMBOL;
          else if(have_floating_point == 1)
            return TOKEN_REAL;
          else
            return TOKEN_INTEGER;
        } else {
          do {
            token_string += *c;
            nextChar();
          } while(!isspace(*c) && !strchr(delims, *c));

          // no nextChar

          return TOKEN_SYMBOL;
        }
    }
  } catch(EOFException& ) {
    return TOKEN_EOF;
  }
}

} // end of namespace lisp


} // namespace pingus

// EOF
