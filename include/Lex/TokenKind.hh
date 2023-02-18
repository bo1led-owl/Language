#ifndef TOKENKIND_HH
#define TOKENKIND_HH

#include "Types.hh"

namespace Language {
enum TokenKind : u8 {
  EndOfInput, // 0
  Unknown,    // 1

  // keywords
  Fn, // 2

  Identifier, // 3

  // literals
  Number, // 4

  // symbols
  Plus,     // 5
  Minus,    // 6
  Asterisk, // 7
  Slash,    // 8
};
}

#endif