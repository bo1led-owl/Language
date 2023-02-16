#include "Lex/Lexer.hh"
#include "Lex/Token.hh"
#include "Lex/TokenKind.hh"

#include <memory>
#include <string>

#include "Types.hh"

std::unique_ptr<Token> Lexer::LexToken() {
  if (GetCurChar() == EOF || GetCurChar() == '\0') {
    return std::make_unique<Token>(TokenKind::EndOfFile);
  }

  while (isspace(GetCurChar())) {
    Advance();
  }

  if (std::isalpha(GetCurChar())) {
    std::string IdentifierString{GetCurChar()};
    while (std::isalnum(Advance())) {
      IdentifierString += GetCurChar();
    }

    if (IdentifierString == "fn") {
      return std::make_unique<Token>(TokenKind::Fn);
    }

    return std::make_unique<IdentifierToken>(IdentifierString);
  }

  if (std::isdigit(GetCurChar())) {
    std::string Number;

    do {
      Number += GetCurChar();
    } while (std::isdigit(Advance()));

    return std::make_unique<NumberToken>(stoi(Number));
  }
  return std::make_unique<Token>(TokenKind::Unknown);
}