#ifndef LEXER_HH
#define LEXER_HH

#include <fstream>
#include <memory>
#include <string>

#include "Lex/Token.hh"

#include "Types.hh"

namespace Language {
class Lexer {
 private:
  std::ifstream Input;
  char CurChar;

  inline char Advance();

 public:
  Lexer(std::string path) : Input(std::ifstream{path}), CurChar(Input.get()) {}

  std::unique_ptr<Token> LexToken();
};
} // namespace Language

#endif