#include <iostream>
#include <memory>

#include "AST/Expr.hh"
#include "AST/LiteralExpr.hh"
#include "Print/Print.hh"

namespace Language {
namespace AST {
void BinaryExpr::Print(i32 offset) {
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

void VarRefExpr::Print(i32 offset) {
  Print::MakeOffset(offset);

  std::cout << "VarRefExpr " << Name;
  std::cout << '\n';
};

void CallExpr::Print(i32 offset) {
  Print::MakeOffset(offset);

  std::cout << "CallExpr " << Callee;
  std::cout << '(';
  for (const std::unique_ptr<Expr> &expr : Args) {
    expr->Print();
  }
  std::cout << ')';
  std::cout << '\n';
}

// template <typename T> void LiteralExpr<T>::Print() {
//   std::cout << "LiteralExpr \"" << Type << "\" " << Value;
// }
} // namespace AST
} // namespace Language
