#ifndef DRIVER_HH
#define DRIVER_HH

#include "Lex/Lexer.hh"
#include "Parse/Parser.hh"

namespace Language {
namespace Driver {
/// Compiler class that unites lexer and parser
class Driver {
    Lex::Lexer Lexer;
    Parse::Parser Parser;

    i32 ArgCount;
    char **Args;

  public:
    Driver(const std::string &filepath, i32 argc, char **argv)
        : Lexer(Lex::Lexer{filepath}), Parser(Lexer), ArgCount(argc), Args(argv) {}

    void Run();
    void Execute();
    void PrintTokens();
    void PrintAST();
};
} // namespace Driver
} // namespace Language

#endif
