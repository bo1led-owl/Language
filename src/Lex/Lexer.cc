#include <memory>
#include <string>

#include "Lex/Lexer.hh"
#include "Lex/Token.hh"
#include "Lex/TokenKind.hh"

#include "Types.hh"

namespace Language {
std::unique_ptr<Token> Lexer::LexToken() {
  if (CurChar == EOF || CurChar == '\0') {
    return std::make_unique<Token>(TokenKind::EndOfInput);
  }

  // skipping spaces
  while (isspace(CurChar)) {
    Advance();
  }

  // lex identifiers and keywords
  if (std::isalpha(CurChar)) {
    std::string IdentifierString{CurChar};
    while (std::isalnum(Advance())) {
      IdentifierString += CurChar;
    }

    if (IdentifierString == "fn") {
      return std::make_unique<Token>(TokenKind::Fn);
    }

    return std::make_unique<IdentifierToken>(IdentifierString);
  }

  // lex numbers
  if (std::isdigit(CurChar)) {
    std::string Number;

    do {
      Number += CurChar;
    } while (std::isdigit(Advance()));

    return std::make_unique<NumberToken>(std::stoi(Number));
  }

  return std::make_unique<Token>(TokenKind::Unknown);
}

inline char Lexer::Advance() {
  CurChar = Input.get();
  return CurChar;
}
} // namespace Language