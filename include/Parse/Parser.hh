#ifndef PARSER_HH
#define PARSER_HH

#include <string>
#include <unordered_map>

#include "AST/BinaryExprKind.hh"
#include "AST/BuiltinTypes.hh"
#include "AST/Decl.hh"
#include "AST/Stmt.hh"
#include "Lex/Lexer.hh"
#include "Lex/Token.hh"
#include "Lex/TokenKind.hh"
#include "Types.hh"

namespace Language {
namespace Parse {
/// Class for parsing lexed tokens
class Parser {
  Lex::Lexer &Lexer;
  std::unique_ptr<Lex::Token> CurToken;

  std::unordered_map<std::string, AST::DataType> TypeMap{
      {"i8", AST::DataType::Int8},    {"i16", AST::DataType::Int16},
      {"i32", AST::DataType::Int32},  {"i64", AST::DataType::Int64},
      {"u8", AST::DataType::UInt8},   {"u16", AST::DataType::UInt16},
      {"u32", AST::DataType::UInt32}, {"u64", AST::DataType::UInt64},
  };

  /// Move to the next token and return a pointer to it
  std::unique_ptr<Lex::Token> Advance() { return std::move(CurToken = Lexer.LexToken()); }

  std::unique_ptr<AST::Decl> ParseVarDecl() {}
  std::unique_ptr<AST::Decl> ParseFnDecl();

  std::unique_ptr<AST::Expr> ParseExpr() {}
  std::unique_ptr<AST::Stmt> ParseStmt() {}

 public:
  Parser(Lex::Lexer &lexer) : Lexer(lexer), CurToken(Lexer.LexToken()) {}

  std::vector<AST::Decl> Parse();
};
} // namespace Parse
} // namespace Language

#endif