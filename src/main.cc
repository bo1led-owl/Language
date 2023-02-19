#include <fstream>
#include <iostream>

#include "Lex/Lexer.hh"
#include "Types.hh"

i32 main(i32 argc, char **argv) {
  using TokenKind = Language::Lex::TokenKind;

  Language::Lex::Lexer lexer{(argc > 1) ? argv[1] : "input.txt"};

  while (true) {
    const auto t = lexer.LexToken();

    switch (t->GetKind()) {
    case TokenKind::Newline:
      std::cout << "Newline\n";
      break;
    case TokenKind::Number:
      std::cout << "Number ";
      break;
    case TokenKind::Identifier:
      std::cout << "Identifier ";
      break;
    case TokenKind::Fn:
      std::cout << "Fn ";
      break;
    case TokenKind::Plus:
      std::cout << "Plus ";
      break;
    case TokenKind::Minus:
      std::cout << "Minus ";
      break;
    case TokenKind::Asterisk:
      std::cout << "Asterisk ";
      break;
    case TokenKind::Slash:
      std::cout << "Slash ";
      break;
    case TokenKind::LParen:
      std::cout << "( ";
      break;
    case TokenKind::RParen:
      std::cout << ") ";
      break;
    case TokenKind::Unknown:
      std::cout << "Unknown ";
      return 0;
    case TokenKind::EndOfInput:
      std::cout << "EndOfInput\n";
      return 0;
    }
  }

  return 0;
}
