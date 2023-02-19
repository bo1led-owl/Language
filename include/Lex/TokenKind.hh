#ifndef TOKENKIND_HH
#define TOKENKIND_HH

#include "Types.hh"

namespace Language {
namespace Lex {
/// Enum of kinds of tokens
enum TokenKind : u8 {
  EndOfInput,
  Unknown,
  Newline,

  // keywords
  Fn,

  Identifier,

  // literals
  Number,

  // symbols
  LParen,   // (
  RParen,   // )
  Plus,     // +
  Minus,    // -
  Asterisk, // *
  Slash,    // /
};
} // namespace Lex
} // namespace Language

#endif