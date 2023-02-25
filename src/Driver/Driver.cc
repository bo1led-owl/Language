#include "Driver/Driver.hh"
#include "Lex/Token.hh"
#include "Lex/TokenKind.hh"

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
} // namespace Driver
} // namespace Language