#include <memory>

#include "AST/Decl.hh"
#include "AST/Expr.hh"
#include "Lex/TokenKind.hh"
#include "Parse/Exception.hh"
#include "Parse/Parser.hh"

namespace Language {
namespace Parse {
std::unique_ptr<AST::Expr> Parser::ParseExpr() {
  std::unique_ptr<AST::Expr> LHS{ParsePrimaryExpr()};

  return ParseBinaryExpr(0, std::move(LHS));
}

std::unique_ptr<AST::Expr> Parser::ParsePrimaryExpr() {
  switch (CurToken->GetKind()) {
  // expression in parentheses
  case Lex::TokenKind::LParen: {
    // eat "("
    Advance();
    auto result{ParseExpr()};
    // eat ")"
    Advance();
    return result;
  } // case LParen
  case Lex::TokenKind::Identifier:
    ParseRefExpr();
  // integer or floating point number (1, 1.1, 1. are valid)
  case Lex::TokenKind::Number:
    return ParseNumberExpr();
  default:
    throw ParseException{"Unknown expression"};
  }
}

std::unique_ptr<AST::Expr> Parser::ParseRefExpr() {
  std::string name{CurToken->GetIdentifierData()};
  // eat identifier
  Advance();
  if (CurToken->Is(Lex::TokenKind::LParen)) {
    std::vector<std::unique_ptr<AST::Expr>> args;
    while (CurToken->IsNot(Lex::TokenKind::RParen)) {
      args.push_back(ParseExpr());
      // eat ","
      if (CurToken->Is(Lex::TokenKind::Comma)) {
        Advance();
      } else {
        throw ParseException{"Syntax error: expected \",\" or \")\" in arguments list"};
      }
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

std::unique_ptr<AST::Expr> Parser::ParseBinaryExpr(const i32 opPrec,
                                                   std::unique_ptr<AST::Expr> LHS) {
  while (true) {
    i32 CurPrec = GetCurTokenPrecedence();
    if (CurPrec < opPrec)
      return LHS;
    Lex::TokenKind BinOp = CurToken->GetKind();
    // eat operator
    Advance();

    auto RHS = ParsePrimaryExpr();
    if (RHS == nullptr) {
      throw ParseException{"Syntax error: expected binary operator second argument"};
    }
    i32 NextPrec = GetCurTokenPrecedence();
    if (CurPrec < NextPrec) {
      RHS = ParseBinaryExpr(CurPrec + 1, std::move(RHS));
    }

    LHS = std::make_unique<AST::BinaryExpr>(BinOp, std::move(LHS), std::move(RHS));
  }
}
} // namespace Parse
} // namespace Language
