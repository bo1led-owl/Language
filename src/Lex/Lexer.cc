#include <memory>
#include <string>

#include "Lex/Lexer.hh"
#include "Lex/Token.hh"
#include "Lex/TokenKind.hh"
#include "Types.hh"

namespace Language {
namespace Lex {
std::unique_ptr<Token> Lexer::LexToken() {
  if (CurChar == EOF || CurChar == '\0') {
    return std::make_unique<Token>(TokenKind::EndOfInput);
  }

  if (CurChar == '\n' || CurChar == '\r') {
    Advance();
    return std::make_unique<Token>(TokenKind::Newline);
  }

  // skipping spaces
  while (isspace(CurChar)) {
    Advance();
  }

  if (CurChar == '(' || CurChar == ')') {
    char prevChar = CurChar;
    Advance();
    return std::make_unique<Token>((prevChar == '(') ? TokenKind::LParen
                                                     : TokenKind::RParen);
  }

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