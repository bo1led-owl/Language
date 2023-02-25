#include <memory>

#include "Parse/Exception.hh"
#include "Parse/Parser.hh"
#include "Types.hh"

#define THROW_IF_TOKEN_IS(Kind, Message)                                                 \
  if (CurToken->Is(Kind)) {                                                              \
    throw ParseException{Message};                                                       \
  }

#define THROW_IF_TOKEN_IS_NOT(Kind, Message)                                             \
  if (CurToken->IsNot(Kind)) {                                                           \
    throw ParseException{Message};                                                       \
  }

namespace Language {
namespace Parse {
std::vector<AST::Decl> Parser::Parse() {
  std::vector<AST::Decl> AST;
  while (CurToken->IsNot(Lex::TokenKind::EndOfInput)) {
    switch (CurToken->GetKind()) {
    case Lex::TokenKind::Fn:
      // skip fn token
      Advance();
      ParseFnDecl();
      break;
    case Lex::TokenKind::Let:
      // skip let token
      Advance();
      ParseVarDecl();
      break;
    default:
      throw ParseException{"Syntax error: expected function or variable declaration\n"};
    }
  }

  return AST;
}

std::unique_ptr<AST::Decl> Parser::ParseFnDecl() {
  if (CurToken->IsNot(Lex::TokenKind::Identifier)) {
    throw ParseException{"Syntax error: missing function name declaration\n"};
  }

  //* function name
  std::string fnName = CurToken->GetIdentifierData();
  // eat function name
  Advance();

  THROW_IF_TOKEN_IS_NOT(Lex::TokenKind::LParen,
                        "Syntax error: expected function arguments\n")
  // eat left parenthesis
  Advance();

  //* function args
  std::vector<AST::FnDecl::Argument> fnArgs;
  while (CurToken->IsNot(Lex::TokenKind::RParen)) {
    THROW_IF_TOKEN_IS_NOT(Lex::TokenKind::Identifier,
                          "Syntax error: missing function parameter name declaration")

    std::string argName = CurToken->GetIdentifierData();
    // eat argument name
    Advance();

    THROW_IF_TOKEN_IS_NOT(Lex::TokenKind::Colon,
                          "Syntax error: missing function parameter type declaration")
    // eat colon
    Advance();

    THROW_IF_TOKEN_IS_NOT(Lex::TokenKind::Identifier,
                          "Syntax error: missing function parameter type declaration")

    if (!TypeMap.contains(CurToken->GetIdentifierData())) {
      throw ParseException{"Syntax error: unknown parameter type"};
    }
    AST::DataType argType{TypeMap[CurToken->GetIdentifierData()]};
    // eat argument's type
    Advance();

    fnArgs.push_back(AST::FnDecl::Argument{argName, argType});
  }

  //* function return type
  AST::DataType fnReturnType{AST::DataType::Void};
  if (CurToken->Is(Lex::TokenKind::RightArrow)) {
    // eat arrow (->)
    Advance();

    THROW_IF_TOKEN_IS_NOT(Lex::TokenKind::Identifier,
                          "Syntax error: missing function return type")

    if (!TypeMap.contains(CurToken->GetIdentifierData())) {
      throw ParseException{"Syntax error: unknown function return type"};
    }
    fnReturnType = {TypeMap[CurToken->GetIdentifierData()]};

    // eat return type
    Advance();
  }

  //* function body
  THROW_IF_TOKEN_IS_NOT(Lex::TokenKind::LCurBracket,
                        "Syntax error: missing function body")
  // eat left curly bracket
  Advance();

  std::unique_ptr<AST::Expr> fnBody = nullptr;
  while (CurToken->IsNot(Lex::TokenKind::RCurBracket)) {
    fnBody = ParseExpr(); // TODO: function body parsing
  }

  // eat rigth curly bracket
  Advance();

  return std::make_unique<AST::FnDecl>(fnName, fnArgs, fnReturnType, fnBody);
}
} // namespace Parse
} // namespace Language