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
  Let,

  Identifier,

  // literals
  Number,

  // characters
  Comma,       // ,
  Fullstop,    // .
  LParen,      // (
  RParen,      // )
  LCurBracket, // {
  RCurBracket, // }
  LSqBracket,  // [
  RSqBracket,  // ]
  Plus,        // +
  Minus,       // -
  Asterisk,    // *
  Slash,       // /
  Equals,      // =
  LArrow,      // <
  RArrow,      // >
};
} // namespace Lex
} // namespace Language

#endif