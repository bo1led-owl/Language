#ifndef PARSER_HH
#define PARSER_HH

#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "AST/Block.hh"
#include "AST/Decl.hh"
#include "AST/LiteralExpr.hh"
#include "AST/Stmt.hh"
#include "Lex/Lexer.hh"
#include "Lex/Token.hh"
#include "Lex/TokenKind.hh"
#include "Parse/Exception.hh"
#include "Types.hh"

#define THROW_IF_TOKEN_IS(Kind, Message)                                                 \
  if (CurToken->Is(Kind)) {                                                              \
    throw ParseException{Message};                                                       \
  }

#define THROW_IF_TOKEN_IS_NOT(Kind, Message)                                             \
  if (CurToken->IsNot(Kind)) {                                                           \
    throw ParseException{Message};                                                       \
  }

#define EAT_IF_TOKEN_IS(Kind)                                                            \
  if (CurToken->Is(Kind)) {                                                              \
    Advance();                                                                           \
  }

namespace Language {
namespace Parse {
/// Class for parsing lexed tokens
class Parser {
  Lex::Lexer &Lexer;
  std::unique_ptr<Lex::Token> CurToken;
  std::shared_ptr<AST::Block> CurBlock{nullptr};

  std::unordered_map<std::string, std::shared_ptr<AST::FnDecl>> Functions;
  std::unordered_map<std::string, std::shared_ptr<AST::VarDecl>> Variables;

  const std::unordered_set<std::string> Types{"bool", "i8",  "i16", "i32", "i64", "u8",
                                              "u16",  "u32", "u64", "f32", "f64"};

  static std::unordered_map<Lex::TokenKind, i32> BinopPrecedence;

  i32 GetCurTokenPrecedence() {
    int TokPrec = BinopPrecedence[CurToken->GetKind()];
    if (TokPrec <= 0)
      return -1;
    return TokPrec;
  }

  /// Move to the next token
  void Advance() { CurToken = Lexer.LexToken(); }

  std::string GetFunctionType(const std::string &name) {
    if (!Functions.contains(name)) {
      throw ParseException{"Error: cannot find function with name " + name};
    }
    return Functions[name]->GetType();
  }

  std::string GetVariableType(const std::string &name) {
    std::shared_ptr<AST::VarDecl> var{CurBlock->SearchForVariable(name)};

    if (var == nullptr) {
      if (!Functions.contains(name)) {
        throw ParseException{"Error: cannot find variable with name " + name};
      } else {
        return Functions[name]->GetType();
      }
    }
    return var->GetType();
  }

  std::unique_ptr<AST::VarDecl> ParseVarDecl();
  std::unique_ptr<AST::FnDecl> ParseFnDecl();

  std::unique_ptr<AST::Stmt> ParseStmt();
  std::shared_ptr<AST::Block> ParseBlock();

  /// Parse any expression but binary
  std::unique_ptr<AST::Expr> ParsePrimaryExpr();
  std::unique_ptr<AST::Expr> ParseRefExpr();
  std::unique_ptr<AST::Expr> ParseNumberExpr();
  std::unique_ptr<AST::Expr> ParseBinaryExpr(i32 opPrec, std::unique_ptr<AST::Expr> LHS);

 public:
  Parser(Lex::Lexer &lexer) : Lexer(lexer), CurToken(Lexer.LexToken()) {}

  std::unique_ptr<AST::Expr> ParseExpr();

  std::vector<std::shared_ptr<AST::Decl>> Parse();
};
} // namespace Parse
} // namespace Language

#endif
