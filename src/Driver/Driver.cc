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
      decl->Print();
    }
  } catch (const Parse::ParseException e) {
    std::cout << "Error on line " << Lexer.GetCurLine() << " column " << Lexer.GetCurColumn()
              << ":\n"
              << e.what() << '\n';
    return;
  }
}
} // namespace Driver
} // namespace Language
