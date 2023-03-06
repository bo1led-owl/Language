#include <memory>

#include "AST/Decl.hh"
#include "Lex/TokenKind.hh"
#include "Parse/Exception.hh"
#include "Parse/Parser.hh"

namespace Language {
namespace Parse {
std::unique_ptr<AST::Expr> Parser::ParseExpr() {
  switch (CurToken->GetKind()) {
  // expression in parentheses
  case Lex::TokenKind::LParen: {
    // eat "("
    Advance();
    std::unique_ptr<AST::Expr> result{ParseExpr()};
    // eat ")"
    Advance();
    return result;
  }

  case Lex::TokenKind::Identifier:
    ParseRefExpr();

  // integer or floating point number (1, 1.1, 1. are valid)
  case Lex::TokenKind::Number:
    return ParseNumberExpr();

  default:
    break;
  }
  return std::make_unique<AST::Expr>("void");
}

std::unique_ptr<AST::Expr> Parser::ParseRefExpr() {
  std::string name{CurToken->GetIdentifierData()};
  // eat identifier
  Advance();
  if (CurToken->Is(Lex::TokenKind::LParen)) {
    std::vector<std::unique_ptr<AST::Expr>> args;
    while (CurToken->IsNot(Lex::TokenKind::RParen)) {
      args.push_back(ParseExpr());
    }

    return std::make_unique<AST::CallExpr>(name, GetFunctionType(name), std::move(args));
  }
  return std::make_unique<AST::VarRefExpr>(name, GetVariableType(name));
}

std::unique_ptr<AST::Expr> Parser::ParseNumberExpr() {
  std::string number;
  number = CurToken->GetNumberData();
  // eat integer part of a number
  Advance();

  if (CurToken->Is(Lex::TokenKind::Fullstop)) {
    // eat "."
    Advance();
    number += '.';
    if (CurToken->Is(Lex::TokenKind::Number)) {
      number += CurToken->GetNumberData();
    }
    return std::make_unique<AST::LiteralExpr<f64>>("f64", std::stod(number));
  }

  i64 value{std::stoll(number)};
  if (value > INT32_MAX) {
    return std::make_unique<AST::LiteralExpr<i64>>("i64", value);
  }
  return std::make_unique<AST::LiteralExpr<i32>>("i32", value);
}

std::unique_ptr<AST::BinaryExpr> ParseBinaryExpr() {
  // TODO
}
} // namespace Parse
} // namespace Language
