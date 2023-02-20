#include <memory>

#include "AST/Decl.hh"
#include "Lex/Token.hh"
#include "Lex/TokenKind.hh"
#include "Parse/Parser.hh"
#include "Types.hh"

namespace Language {
namespace Parse {
std::vector<AST::Decl> Parser::Parse() {
  std::vector<AST::Decl> AST;
  while (CurToken->IsNot(Lex::TokenKind::EndOfInput)) {
    Advance();
  }
}
} // namespace Parse
} // namespace Language