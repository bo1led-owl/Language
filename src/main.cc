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
      std::cout << "+ ";
      break;
    case TokenKind::Minus:
      std::cout << "- ";
      break;
    case TokenKind::Asterisk:
      std::cout << "* ";
      break;
    case TokenKind::Slash:
      std::cout << "/ ";
      break;
    case TokenKind::LParen:
      std::cout << "( ";
      break;
    case TokenKind::RParen:
      std::cout << ") ";
      break;
    case TokenKind::Let:
      std::cout << "Let ";
      break;
    case TokenKind::Comma:
      std::cout << ", ";
      break;
    case TokenKind::Fullstop:
      std::cout << ".";
      break;
    case TokenKind::LCurBracket:
      std::cout << "{ ";
      break;
    case TokenKind::RCurBracket:
      std::cout << "} ";
      break;
    case TokenKind::LSqBracket:
      std::cout << "[ ";
      break;
    case TokenKind::RSqBracket:
      std::cout << "] ";
      break;
    case TokenKind::Equals:
      std::cout << "= ";
      break;
    case TokenKind::LArrow:
      std::cout << "< ";
      break;
    case TokenKind::RArrow:
      std::cout << "> ";
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
