#ifndef LEXER_HH
#define LEXER_HH

#include <memory>
#include <string>
#include <vector>

#include "Lex/Token.hh"
#include "Types.hh"

class Lexer {
private:
  std::string::iterator CurChar;
  char CurCharValue;

  inline char GetCurChar() const { return CurCharValue; }

  inline char Advance() {
    CurChar++;
    CurCharValue = *CurChar;
    return GetCurChar();
  }

public:
  Lexer(std::string &input) : CurChar(input.begin()), CurCharValue(*CurChar) {}

  std::unique_ptr<Token> LexToken();
};

#endif
