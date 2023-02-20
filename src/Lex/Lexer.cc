#include <memory>
#include <string>

#include "Lex/Lexer.hh"
#include "Lex/Token.hh"
#include "Lex/TokenKind.hh"
#include "Types.hh"

namespace Language {
namespace Lex {
/// Macro for matching single characters and tokens
#define REGISTER_TOKEN(Char, Kind)                                                       \
  if (CurChar == Char) {                                                                 \
    Advance();                                                                           \
    return std::make_unique<Token>(Kind);                                                \
  }

std::unique_ptr<Token> Lexer::LexToken() {
  REGISTER_TOKEN(EOF, TokenKind::EndOfInput);
  REGISTER_TOKEN('\0', TokenKind::EndOfInput);

  REGISTER_TOKEN('\r', TokenKind::Newline);
  REGISTER_TOKEN('\n', TokenKind::Newline);

  // skipping spaces
  while (isspace(CurChar)) {
    Advance();
  }

  REGISTER_TOKEN('(', TokenKind::LParen);
  REGISTER_TOKEN(')', TokenKind::RParen);
  REGISTER_TOKEN('{', TokenKind::LCurBracket);
  REGISTER_TOKEN('}', TokenKind::RCurBracket);
  REGISTER_TOKEN('[', TokenKind::LSqBracket);
  REGISTER_TOKEN(']', TokenKind::RSqBracket);

  REGISTER_TOKEN(',', TokenKind::Comma);
  REGISTER_TOKEN('.', TokenKind::Fullstop);
  REGISTER_TOKEN('+', TokenKind::Plus);
  REGISTER_TOKEN('-', TokenKind::Minus);
  REGISTER_TOKEN('*', TokenKind::Asterisk);
  REGISTER_TOKEN('/', TokenKind::Slash);
  REGISTER_TOKEN('=', TokenKind::Equals);
  REGISTER_TOKEN('<', TokenKind::LArrow);
  REGISTER_TOKEN('>', TokenKind::RArrow);

  // lex identifiers and keywords
  if (std::isalpha(CurChar)) {
    std::string identifierString{CurChar};
    while (std::isalnum(Advance())) {
      identifierString += CurChar;
    }

    if (identifierString == "fn") {
      return std::make_unique<Token>(TokenKind::Fn);
    }

    return std::make_unique<IdentifierToken>(identifierString);
  }

  // lex numbers
  if (std::isdigit(CurChar)) {
    std::string number;

    do {
      number += CurChar;
    } while (std::isdigit(Advance()));

    return std::make_unique<NumberToken>(std::stoi(number));
  }

  return std::make_unique<Token>(TokenKind::Unknown);
}
} // namespace Lex
} // namespace Language