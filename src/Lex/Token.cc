#include <iostream>

#include "Lex/Token.hh"

namespace Language {
namespace Lex {
void Token::Print() const {
  switch (Kind) {
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
  case TokenKind::Colon:
    std::cout << ": ";
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
  case TokenKind::LessThan:
    std::cout << "< ";
    break;
  case TokenKind::GreaterThan:
    std::cout << "> ";
    break;
  case TokenKind::LeftArrow:
    std::cout << "<- ";
    break;
  case TokenKind::RightArrow:
    std::cout << "-> ";
    break;
  case TokenKind::Unknown:
    std::cout << "Unknown ";
    break;
  case TokenKind::EndOfInput:
    std::cout << "EndOfInput\n";
    break;
  }
}
} // namespace Lex
} // namespace Language