#include "Lex/Token.hh"
#include "Lex/TokenKind.hh"
#include "Parse/Exception.hh"
#include "Parse/Parser.hh"
#include <iostream>
#include <unordered_set>

namespace Language {
namespace Parse {
std::unique_ptr<AST::VarDecl> Parser::ParseVarDecl() {
  // eat "let"
  Advance();

  bool mut{CurToken->Is(Lex::TokenKind::Mut)};
  EAT_IF_TOKEN_IS(Lex::TokenKind::Mut)

  THROW_IF_TOKEN_IS_NOT(Lex::TokenKind::Identifier, "missing variable name")
  std::string varName{CurToken->GetIdentifierData()};
  if (VariableDeclared(varName) ||
      (CurFn != nullptr && CurFn->GetArgumentByName(varName) != nullptr)) {
    throw ParseException{"variable with name \"" + varName + "\" is already declared"};
  }
  // eat variable name
  Advance();

  std::string varType{};
  if (CurToken->Is(Lex::TokenKind::Colon)) {
    // eat ":"
    Advance();
    THROW_IF_TOKEN_IS_NOT(Lex::TokenKind::Identifier,
                          "missing variable type")
    varType = CurToken->GetIdentifierData();
    // eat variable type
    Advance();
  }

  std::unique_ptr<AST::Expr> varValue{nullptr};
  if (CurToken->Is(Lex::TokenKind::Equals)) {
    // eat "="
    Advance();
    varValue = ParseExpr();
    if (varType.empty()) {
      varType = varValue->GetType();
    }
  }

  if (CurToken->IsNot(Lex::TokenKind::Newline) &&
      CurToken->IsNot(Lex::TokenKind::EndOfInput) &&
      CurToken->IsNot(Lex::TokenKind::LCurBracket) &&
      CurToken->IsNot(Lex::TokenKind::RCurBracket)) {
    throw ParseException{"unexpected token at the end of statement"};
  }

  // eat newline and NOT eat end of input
  EAT_IF_TOKEN_IS(Lex::TokenKind::Newline)

  return std::make_unique<AST::VarDecl>(varName, varType, mut, varValue);
}

std::unique_ptr<AST::FnDecl> Parser::ParseFnDecl() {
  // eat "fn"
  Advance();

  if (CurToken->IsNot(Lex::TokenKind::Identifier)) {
    throw ParseException{"missing function name declaration"};
  }
  std::string fnName = CurToken->GetIdentifierData();
  if (Functions.contains(fnName)) {
    throw ParseException{"function with name \"" + fnName + "\" is already declared"};
  }
  // eat function name
  Advance();
  THROW_IF_TOKEN_IS_NOT(Lex::TokenKind::LParen,
                        "expected function arguments")
  // eat "("
  Advance();

  std::vector<AST::FnDecl::Argument> fnArgs;
  std::unordered_set<std::string> argNames;
  while (CurToken->IsNot(Lex::TokenKind::RParen)) {
    THROW_IF_TOKEN_IS_NOT(Lex::TokenKind::Identifier,
                          "missing function parameter name declaration")
    std::string argName = CurToken->GetIdentifierData();
    if (argNames.contains(argName)) {
      throw ParseException{"argument with name " + argName +
                           " is already declared in that function"};
    }
    if (VariableDeclared(argName)) {
      throw ParseException{
          "variable with name \"" + argName +
          "\" is already declared, this name cannot be used as an argument name"};
    }
    argNames.emplace(argName);
    // eat argument name
    Advance();
    THROW_IF_TOKEN_IS_NOT(Lex::TokenKind::Colon,
                          "missing function parameter type declaration")
    // eat ":"
    Advance();
    THROW_IF_TOKEN_IS_NOT(Lex::TokenKind::Identifier,
                          "missing function parameter type declaration")
    if (!Types.contains(CurToken->GetIdentifierData())) {
      throw ParseException{"unknown parameter type"};
    }
    std::string argType{CurToken->GetIdentifierData()};
    // eat argument type
    Advance();
    fnArgs.push_back(AST::FnDecl::Argument{argName, argType});
    EAT_IF_TOKEN_IS(Lex::TokenKind::Comma)
  }

  // eat ")"
  Advance();

  std::string fnReturnType{""};
  if (CurToken->Is(Lex::TokenKind::RightArrow)) {
    // eat "->"
    Advance();
    THROW_IF_TOKEN_IS_NOT(Lex::TokenKind::Identifier,
                          "missing function return type")
    fnReturnType = CurToken->GetIdentifierData();
    if (!Types.contains(fnReturnType)) {
      throw ParseException{"unknown function return type"};
    }
    // eat return type
    Advance();
  }

  CurFn = std::make_unique<AST::FnDecl>(fnName, fnReturnType, fnArgs);

  CurFn->SetBody(ParseBlock());
  if (CurFn->GetType() != "" && !CurFn->HasReturnStmt()) {
    throw ParseException{"function do not return a value"};
  }
  auto result = std::move(CurFn);
  CurFn = nullptr;
  return result;
}
} // namespace Parse
} // namespace Language
