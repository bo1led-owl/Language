#ifndef PARSER_HH
#define PARSER_HH

#include "AST/BinaryExprKind.hh"
#include "AST/Expr.hh"
#include "Lex/Lexer.hh"
#include "Lex/Token.hh"
#include "Lex/TokenKind.hh"
#include "Types.hh"

namespace Language {
namespace Parse {
/// Class for parsing lexed tokens
class Parser {
  std::unique_ptr<Lex::Lexer> Lexer;
  std::unique_ptr<Lex::Token> CurToken;

  /// Move to the next token and return a pointer to it
  std::unique_ptr<Lex::Token> Advance() {
    return std::move(CurToken = Lexer->LexToken());
  }

 public:
  Parser(std::unique_ptr<Lex::Lexer> lexer)
      : Lexer(std::move(lexer)), CurToken(Lexer->LexToken()) {}
};
} // namespace Parse
} // namespace Language

#endif