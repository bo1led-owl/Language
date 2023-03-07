#include "Driver/Driver.hh"

#include "Lex/Lexer.hh"
#include "Parse/Parser.hh"

#include "Types.hh"
#include <iostream>

i32 main(i32 argc, char **argv) {
  Language::Driver::Driver driver{(argc > 1) ? argv[1] : "input.txt"};
  driver.PrintAST();

  return 0;
}
