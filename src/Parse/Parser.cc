#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "AST/Block.hh"
#include "AST/Decl.hh"
#include "AST/Expr.hh"
#include "AST/LiteralExpr.hh"
#include "AST/Stmt.hh"
#include "Lex/Lexer.hh"
#include "Lex/Token.hh"
#include "Lex/TokenKind.hh"
#include "Parse/Exception.hh"
#include "Parse/Parser.hh"
#include "Types.hh"

namespace Language {
namespace Parse {
std::unordered_map<Lex::TokenKind, i32> Parser::BinopPrecedence{
    {Lex::TokenKind::Equals, 10},      // <
    {Lex::TokenKind::LessThan, 20},    // <
    {Lex::TokenKind::GreaterThan, 20}, // >
    {Lex::TokenKind::Plus, 30},        // +
    {Lex::TokenKind::Minus, 30},       // -
    {Lex::TokenKind::Asterisk, 40},    // -
    {Lex::TokenKind::Slash, 40},       // -
};

std::vector<std::shared_ptr<AST::Decl>> Parser::Parse() {
  std::vector<std::shared_ptr<AST::Decl>> AST;

  while (CurToken->IsNot(Lex::TokenKind::EndOfInput)) {
    switch (CurToken->GetKind()) {
    case Lex::TokenKind::Newline:
      Advance();
      break;
    case Lex::TokenKind::Fn: {
      std::shared_ptr<AST::FnDecl> decl{ParseFnDecl()};
      AST.push_back(decl);
      Functions[decl->GetName()] = decl;
    } break;

    case Lex::TokenKind::Let: {
      std::shared_ptr<AST::VarDecl> decl{ParseVarDecl()};
      AST.emplace_back(decl);
      Variables[decl->GetName()] = decl;
    } break;

    default:
      throw ParseException{"Syntax error: expected function or variable declaration"};
    }
  }

  return AST;
}
} // namespace Parse
} // namespace Language
