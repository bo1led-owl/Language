#ifndef LEXER_HH
#define LEXER_HH

#include <fstream>
#include <memory>
#include <string>

#include "Lex/Token.hh"
#include "Types.hh"

namespace Language {
namespace Lex {
/// Class for lexing tokens from code
class Lexer {
    std::ifstream Input;
    char CurChar;

    u64 CurLine{1};

    /// Move to the next character from the input and return it
    inline char Advance();

  public:
    Lexer(std::string path) : Input(std::ifstream{path}), CurChar(Input.get()) {}

    /// Lex next token from input
    std::unique_ptr<Token> LexToken();

    u64 GetCurLine() { return CurLine; }
};
} // namespace Lex
} // namespace Language

#endif
