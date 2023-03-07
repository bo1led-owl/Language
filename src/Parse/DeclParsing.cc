#include "Lex/Token.hh"
#include "Parse/Exception.hh"
#include "Parse/Parser.hh"

namespace Language {
namespace Parse {
std::unique_ptr<AST::VarDecl> Parser::ParseVarDecl() {
  // eat "let"
  Advance();
  THROW_IF_TOKEN_IS_NOT(Lex::TokenKind::Identifier, "Syntax error: missing variable name")
  bool mut{CurToken->Is(Lex::TokenKind::Mut)};

  EAT_IF_TOKEN_IS(Lex::TokenKind::Mut)

  THROW_IF_TOKEN_IS_NOT(Lex::TokenKind::Identifier, "Syntax error: missing variable name")
  std::string varName{CurToken->GetIdentifierData()};
  // eat variable name
  Advance();

  std::string varType{};
  if (CurToken->Is(Lex::TokenKind::Colon)) {
    // eat ":"
    Advance();
    THROW_IF_TOKEN_IS_NOT(Lex::TokenKind::Identifier,
                          "Syntax error: missing variable type")
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
      CurToken->IsNot(Lex::TokenKind::RCurBracket)) {
    throw ParseException{"Syntax error: unexpected token at the end of statement"};
  }

  // eat newline and NOT eat end of input
  EAT_IF_TOKEN_IS(Lex::TokenKind::Newline)

  return std::make_unique<AST::VarDecl>(varName, varType, mut, varValue);
}

std::unique_ptr<AST::FnDecl> Parser::ParseFnDecl() {
  // eat "fn"
  Advance();

  if (CurToken->IsNot(Lex::TokenKind::Identifier)) {
    throw ParseException{"Syntax error: missing function name declaration"};
  }
  std::string fnName = CurToken->GetIdentifierData();
  // eat function name
  Advance();
  THROW_IF_TOKEN_IS_NOT(Lex::TokenKind::LParen,
                        "Syntax error: expected function arguments")
  // eat "("
  Advance();

  std::vector<AST::FnDecl::Argument> fnArgs;
  while (CurToken->IsNot(Lex::TokenKind::RParen)) {
    THROW_IF_TOKEN_IS_NOT(Lex::TokenKind::Identifier,
                          "Syntax error: missing function parameter name declaration")
    std::string argName = CurToken->GetIdentifierData();
    // eat argument name
    Advance();
    THROW_IF_TOKEN_IS_NOT(Lex::TokenKind::Colon,
                          "Syntax error: missing function parameter type declaration")
    // eat ":"
    Advance();
    THROW_IF_TOKEN_IS_NOT(Lex::TokenKind::Identifier,
                          "Syntax error: missing function parameter type declaration")
    if (!Types.contains(CurToken->GetIdentifierData())) {
      throw ParseException{"Syntax error: unknown parameter type"};
    }
    std::string argType{CurToken->GetIdentifierData()};
    // eat argument type
    Advance();
    fnArgs.push_back(AST::FnDecl::Argument{argName, argType});
  }

  // eat ")"
  Advance();

  std::string fnReturnType{""};
  if (CurToken->Is(Lex::TokenKind::RightArrow)) {
    // eat "->"
    Advance();
    THROW_IF_TOKEN_IS_NOT(Lex::TokenKind::Identifier,
                          "Syntax error: missing function return type")
    fnReturnType = CurToken->GetIdentifierData();
    if (!Types.contains(fnReturnType)) {
      throw ParseException{"Syntax error: unknown function return type"};
    }
    // eat return type
    Advance();
  }

  auto fnBody = ParseBlock();
  return std::make_unique<AST::FnDecl>(fnName, fnReturnType, fnArgs, fnBody);
}
} // namespace Parse
} // namespace Language
