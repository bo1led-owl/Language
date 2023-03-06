#ifndef TOKENKIND_HH
#define TOKENKIND_HH

#include "Types.hh"

namespace Language {
namespace Lex {
/// Enum of kinds of tokens
enum class TokenKind : i8 {
  EndOfInput,
  Unknown,
  Newline,

  // keywords
  Fn,
  Let,
  Mut,

  Identifier,

  // literals
  Number,

  // characters
  LParen,      // (
  RParen,      // )
  LCurBracket, // {
  RCurBracket, // }
  LSqBracket,  // [
  RSqBracket,  // ]
  Comma,       // ,
  Fullstop,    // .
  Colon,       // :
  Plus,        // +
  Minus,       // -
  Asterisk,    // *
  Slash,       // /
  Equals,      // =
  LessThan,    // <
  GreaterThan, // >
  LeftArrow,   // <-
  RightArrow,  // ->
};
} // namespace Lex
} // namespace Language

#endif
