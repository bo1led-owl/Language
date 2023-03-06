#include "AST/Decl.hh"
#include "AST/Stmt.hh"
#include "Parse/Exception.hh"
#include "Parse/Parser.hh"
#include <memory>

namespace Language {
namespace Parse {
std::unique_ptr<AST::Block> Parser::ParseBlock() {
  THROW_IF_TOKEN_IS_NOT(Lex::TokenKind::LCurBracket,
                        "Syntax error: missing block opening curly bracket")
  // eat "{"
  Advance();
  EAT_IF_TOKEN_IS(Lex::TokenKind::Newline)

  std::unique_ptr<AST::Block> result = std::make_unique<AST::Block>(CurBlock);

  while (CurToken->IsNot(Lex::TokenKind::RCurBracket)) {
    THROW_IF_TOKEN_IS(Lex::TokenKind::EndOfInput,
                      "Syntax error: expected closed statement block")
    EAT_IF_TOKEN_IS(Lex::TokenKind::Newline)

    if (CurToken->Is(Lex::TokenKind::Let)) {
      std::shared_ptr<AST::VarDecl> decl = ParseVarDecl();
      result->AddVariable(decl->GetName(), decl);
      result->AddToBody(std::make_unique<AST::DeclStmt>(std::move(decl)));
    } else {
      result->AddToBody(ParseStmt());
    }
  }

  EAT_IF_TOKEN_IS(Lex::TokenKind::Newline)
  // eat "}"
  Advance();

  CurBlock = result->GetParent();
  return result;
}

std::unique_ptr<AST::Stmt> Parser::ParseStmt() {
  switch (CurToken->GetKind()) {
  case Lex::TokenKind::Let:
    return std::make_unique<AST::DeclStmt>(ParseVarDecl());

  default:
    return ParseExpr();
  }
}
} // namespace Parse
} // namespace Language
