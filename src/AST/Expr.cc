#include <iostream>
#include <memory>

#include "AST/Expr.hh"
#include "AST/LiteralExpr.hh"
#include "Print/Print.hh"

namespace Language {
namespace AST {
void BinExpr::Print(const i32 offset) {
  Print::MakeOffset(offset);
  std::cout << "BinExpr \"";
  switch (Operator) {
  case Lex::TokenKind::Plus:
    std::cout << "+";
    break;
  case Lex::TokenKind::Minus:
    std::cout << "-";
    break;
  case Lex::TokenKind::Asterisk:
    std::cout << "*";
    break;
  case Lex::TokenKind::Slash:
    std::cout << "/";
    break;
  case Lex::TokenKind::Equals:
    std::cout << "=";
    break;
  case Lex::TokenKind::LessThan:
    std::cout << "<";
    break;
  case Lex::TokenKind::GreaterThan:
    std::cout << ">";
    break;
  default:
    break;
  }
  std::cout << "\" {\n";
  LHS->Print(offset + 1);
  RHS->Print(offset + 1);

  Print::MakeOffset(offset);
  std::cout << "}\n";
}

void VarRefExpr::Print(const i32 offset) {
  Print::MakeOffset(offset);
  std::cout << "VarRefExpr " << Name << '\n';
};

void CallExpr::Print(const i32 offset) {
  Print::MakeOffset(offset);
  std::cout << "CallExpr " << Callee;
  std::cout << '(';
  if (Args.size() > 0) {
    std::cout << '\n';
  }
  for (size_t i{}; i < Args.size(); ++i) {
    Args[i]->Print(offset + 1);
  }
  if (Args.size() > 0) {
    Print::MakeOffset(offset);
  }
  std::cout << ")\n";
}
} // namespace AST
} // namespace Language
