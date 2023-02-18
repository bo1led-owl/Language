#include <fstream>
#include <iostream>

#include "Lex/Lexer.hh"

#include "Types.hh"

i32 main(i32 argc, char **argv) {
  using TokenKind = Language::TokenKind;

  Language::Lexer lexer{(argc > 1) ? argv[1] : "input.txt"};

  while (true) {
    const auto t = lexer.LexToken();

    switch (t->GetKind()) {
    case TokenKind::Number:
      std::cout << "Number: " << t->GetNumberData() << '\n';
      break;
    case TokenKind::Identifier:
      std::cout << "Identifier: " << t->GetIdentifierData() << '\n';
      break;
    case TokenKind::Fn:
      std::cout << "Fn\n";
      break;
    case TokenKind::Unknown:
      std::cout << "Unknown\n";
      return 0;
      break;
    case TokenKind::Plus:
      std::cout << "Plus\n";
      break;
    case TokenKind::Minus:
      std::cout << "Minus\n";
      break;
    case TokenKind::Asterisk:
      std::cout << "Asterisk\n";
      break;
    case TokenKind::Slash:
      std::cout << "Slash\n";
      break;
    case TokenKind::EndOfInput:
      return 0;
      break;
    }
  }

  return 0;
}
