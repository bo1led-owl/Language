#ifndef PARSER_HH
#define PARSER_HH

#include <memory>
#include <string>
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

  std::unordered_set<std::string> Types{"bool", "i8",  "i16", "i32", "i64", "u8",
                                        "u16",  "u32", "u64", "f32", "f64"};

  /// Move to the next token
  void Advance() { CurToken = Lexer.LexToken(); }
  
  const inline std::string &GetFunctionType(const std::string &name) {
    std::shared_ptr<AST::VarDecl> var{CurBlock->SearchForVariable(name)};

    if (var == nullptr) {
      if (!Variables.contains(name)) {
        throw ParseException{"Error: cannot find variable with name" + name};
      } else {
        return Variables[name]->GetType();
      }
    }
    return var->GetType();
  }

  const inline std::string &GetVariableType(const std::string &name) {
    std::shared_ptr<AST::VarDecl> fn{CurBlock->SearchForVariable(name)};

    if (fn == nullptr) {
      if (!Functions.contains(name)) {
        throw ParseException{"Error: cannot find variable with name" + name};
      } else {
        return Functions[name]->GetType();
      }
    }
    return fn->GetType();
  }

  std::unique_ptr<AST::VarDecl> ParseVarDecl();
  std::unique_ptr<AST::FnDecl> ParseFnDecl();

  std::unique_ptr<AST::Stmt> ParseStmt();
  std::unique_ptr<AST::Block> ParseBlock();

  std::unique_ptr<AST::Expr> ParseExpr();
  std::unique_ptr<AST::Expr> ParseRefExpr();
  std::unique_ptr<AST::Expr> ParseNumberExpr();
  std::unique_ptr<AST::BinaryExpr> ParseBinaryExpr();

 public:
  Parser(Lex::Lexer &lexer) : Lexer(lexer), CurToken(Lexer.LexToken()) {}

  std::vector<std::shared_ptr<AST::Decl>> Parse();
};
} // namespace Parse
} // namespace Language

#endif
