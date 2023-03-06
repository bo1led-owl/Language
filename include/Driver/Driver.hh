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

 public:
  Driver(std::string filepath) : Lexer(Lex::Lexer{filepath}), Parser(Lexer) {}
  Driver(Lex::Lexer lexer, Parse::Parser parser)
      : Lexer(std::move(lexer)), Parser(std::move(parser)) {}

  void Run();
  void PrintTokens();
  void PrintAST();
};
} // namespace Driver
} // namespace Language

#endif