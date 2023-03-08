#include <iostream>

#include "Driver/Driver.hh"
#include "Lex/Token.hh"
#include "Lex/TokenKind.hh"
#include "Parse/Exception.hh"

namespace Language {
namespace Driver {
void Driver::PrintTokens() {
  while (true) {
    const auto t = Lexer.LexToken();
    t->Print();
    if (t->Is(Language::Lex::TokenKind::EndOfInput)) {
      return;
    }
  }
}

void Driver::PrintAST() {
  try {
    const auto AST = Parser.Parse();

    for (const auto &decl : AST) {
      // std::cout << typeid(*decl).name() << '\n';
      decl->Print();
    }
  } catch (Parse::ParseException e) {
    std::cout << e.what() << '\n';
    return;
  }
}
} // namespace Driver
} // namespace Language
