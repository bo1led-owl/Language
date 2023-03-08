#include "AST/Decl.hh"
#include "AST/Stmt.hh"
#include "Lex/TokenKind.hh"
#include "Parse/Exception.hh"
#include "Parse/Parser.hh"
#include <memory>

namespace Language {
namespace Parse {
std::shared_ptr<AST::Block> Parser::ParseBlock() {
  THROW_IF_TOKEN_IS_NOT(Lex::TokenKind::LCurBracket,
                        "Syntax error: missing block opening curly bracket")
  // eat "{"
  Advance();
  EAT_IF_TOKEN_IS(Lex::TokenKind::Newline)

  CurBlock = std::make_unique<AST::Block>(CurBlock);

  while (CurToken->IsNot(Lex::TokenKind::RCurBracket)) {
    THROW_IF_TOKEN_IS(Lex::TokenKind::EndOfInput,
                      "Syntax error: expected closed statement block")
    EAT_IF_TOKEN_IS(Lex::TokenKind::Newline)

    switch (CurToken->GetKind()) {
    case Lex::TokenKind::RCurBracket:
      break;
    case Lex::TokenKind::Let: {
      std::shared_ptr<AST::VarDecl> decl = ParseVarDecl();
      CurBlock->AddVariable(decl->GetName(), decl);
      CurBlock->AddToBody(std::make_unique<AST::DeclStmt>(std::move(decl)));
      break;
    } // case Lex::TokenKind::Lex
    default:
      CurBlock->AddToBody(ParseStmt());
    }
  }

  EAT_IF_TOKEN_IS(Lex::TokenKind::Newline)
  // eat "}"
  Advance();

  auto result{std::move(CurBlock)};
  CurBlock = result->GetParent();
  return result;
}

std::unique_ptr<AST::Stmt> Parser::ParseStmt() {
  while (CurToken->Is(Lex::TokenKind::Newline)) {
    Advance();
  }

  THROW_IF_TOKEN_IS(Lex::TokenKind::EndOfInput,
                    "Syntax error: expected statement, found end of input")

  switch (CurToken->GetKind()) {
  case Lex::TokenKind::Let:
    return std::make_unique<AST::DeclStmt>(ParseVarDecl());

  case Lex::TokenKind::LCurBracket:
    return std::make_unique<AST::BlockStmt>(ParseBlock());

  case Lex::TokenKind::Return: {
    // eat "return"
    Advance();
    if (CurToken->Is(Lex::TokenKind::Newline) ||
        CurToken->Is(Lex::TokenKind::RCurBracket)) {
      if (CurFn->GetType() == "") {
        return std::make_unique<AST::ReturnStmt>(nullptr);
      } else {
        throw ParseException{"Function return type differs from the type of the "
                             "expression in return statement"};
      }
    }
    auto expr{ParseExpr()};
    if (expr->GetType() == CurFn->GetType()) {
      return std::make_unique<AST::ReturnStmt>(std::move(expr));
    } else {
      throw ParseException{"Function return type differs from the type of the expression "
                           "in return statement"};
    }
  } // case Lex::TokenKind::Return

  default:
    return ParseExpr();
  }
}
} // namespace Parse
} // namespace Language
