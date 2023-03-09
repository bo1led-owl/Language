#include <memory>
#include <string>

#include "AST/Decl.hh"
#include "AST/Expr.hh"
#include "Lex/TokenKind.hh"
#include "Parse/Exception.hh"
#include "Parse/Parser.hh"

namespace Language {
namespace Parse {
std::unique_ptr<AST::Expr> Parser::ParseExpr() {
  std::unique_ptr<AST::Expr> LHS{ParsePrimaryExpr()};
  return ParseBinExpr(0, std::move(LHS));
}

std::unique_ptr<AST::Expr> Parser::ParsePrimaryExpr() {
  // unexpected end of input
  THROW_IF_TOKEN_IS(Lex::TokenKind::EndOfInput, "expected expression, found end of input")
  switch (CurToken->GetKind()) {
  case Lex::TokenKind::LParen: {
    // expression in parentheses
    // eat "("
    Advance();
    auto result{ParseExpr()};
    // no ")"
    THROW_IF_TOKEN_IS_NOT(Lex::TokenKind::RParen, "expected closing parenthesis")
    // eat ")"
    Advance();
    return result;
  } // case LParen

  case Lex::TokenKind::Identifier:
    // variable reference or function call
    return ParseRefExpr();
  case Lex::TokenKind::Number:
    // integer or floating point number
    return ParseNumberExpr();
  default:
    // unknown expression
    throw ParseException{"unknown expression"};
  }
}

std::unique_ptr<AST::Expr> Parser::ParseRefExpr() {
  const std::string name{CurToken->GetIdentifierData()};
  // eat identifier
  Advance();
  // check whether it is a variable reference or a function call
  if (CurToken->Is(Lex::TokenKind::LParen)) {
    if (!Functions.contains(name)) {
      // function is not declared
      throw ParseException{"function with name \"" + name + "\" is not declared"};
    }
    // callee declaration
    const std::shared_ptr<AST::FnDecl> fnRef = Functions[name];

    // parse arguments
    std::vector<std::unique_ptr<AST::Expr>> args;
    // eat "("
    Advance();
    while (CurToken->IsNot(Lex::TokenKind::RParen)) {
      args.push_back(ParseExpr());
      // current argument in function declaration
      const std::unique_ptr<AST::FnDecl::Argument> curArg{
          fnRef->GetArgumentByIndex(args.size() - 1)};

      // too many arguments
      if (curArg == nullptr) {
        throw ParseException{"bad argument list for call of function \"" + name +
                             "\": too many arguments passed"};
      }
      // argument type mismatch
      if (args[args.size() - 1]->GetType() != curArg->Type) {
        throw ParseException{"bad argument list for call of function \"" + name +
                             "\": argument \"" + curArg->Name + "\" type mismatch"};
      }

      switch (CurToken->GetKind()) {
      case Lex::TokenKind::Comma:
        // next argument
        // eat ","
        Advance();
        break;
      case Lex::TokenKind::RParen:
        // end of argument list
        break;
      default:
        // expected "," or ")"
        throw ParseException{"expected \",\" or \")\" in argument list"};
      }
    }
    // this must be eaten after the loop, because it is looping while CurToken is not ")"
    // eat ")"
    Advance();

    // too few arguments
    if (args.size() < fnRef->GetArgCount()) {
      // too few arguments
      throw ParseException{"bad argument list for call of function \"" + name +
                           "\": too few arguments passed"};
    }
    return std::make_unique<AST::CallExpr>(name, GetFunctionType(name), std::move(args));
  }

  std::string varType;
  if (VariableDeclared(name)) {
    varType = GetVariableType(name);
    if (varType.empty()) {
      // no variable type
      throw ParseException{"attempt to reference a variable with no type"};
    }
  } else if (const auto arg = CurFn->GetArgumentByName(name); arg != nullptr) {
    varType = arg->Type;
  } else {
    // cannot find variable or argument with that name
    throw ParseException{"cannot find variable or argument with name \"" + name + "\""};
  }
  return std::make_unique<AST::VarRefExpr>(name, varType);
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
      // eat fractional part of a number
      Advance(); 
    }
    return std::make_unique<AST::LiteralExpr<f64>>("f64", std::stod(number));
  }

  i64 value{std::stoll(number)};
  if (value > INT32_MAX) {
    return std::make_unique<AST::LiteralExpr<i64>>("i64", value);
  }
  return std::make_unique<AST::LiteralExpr<i32>>("i32", value);
}

std::unique_ptr<AST::Expr> Parser::ParseBinExpr(const i32 opPrec,
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
      // no right operand
      throw ParseException{"expected binary operator second operand"};
    }
    i32 NextPrec = GetCurTokenPrecedence();
    // parse BinExpr with more "weight"
    if (CurPrec < NextPrec) {
      RHS = ParseBinExpr(CurPrec + 1, std::move(RHS));
    }

    LHS = std::make_unique<AST::BinExpr>(BinOp, std::move(LHS), std::move(RHS));
  }
}
} // namespace Parse
} // namespace Language
