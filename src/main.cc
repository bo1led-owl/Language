#include <iostream>

#include "Lex/Lexer.hh"
#include "Types.hh"

i32 main() {
  std::string input{"1 aboba 2 3 fn 4\0"};
  Lexer lex{input};

  while (true) {
    const auto t = lex.LexToken();
    if (t->Is(TokenKind::EndOfFile)) {
      break;
    }

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
    case TokenKind::EndOfFile:
      std::cout << "EOF\n";
      break;
    case TokenKind::Unknown:
      std::cout << "Unknown\n";
      break;
    }
  }

  return 0;
}
