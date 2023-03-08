#ifndef LITERALEXPR_HH
#define LITERALEXPR_HH

#include <iostream>

#include "AST/Expr.hh"
#include "Print/Print.hh"
#include "Types.hh"

namespace Language {
namespace AST {
/// Literal expression class (e.g. 5, 1.1, "hello")
template <typename T> class LiteralExpr : public Expr {
  T Value;

 public:
  LiteralExpr(const std::string &type) : Expr(type) {}
  LiteralExpr(const std::string &type, const T value) : Expr(type), Value(value) {}

  void Print(i32 offset = 0) override {
    Print::MakeOffset(offset);

    std::cout << "LiteralExpr \"" << Type << "\" " << Value;
    std::cout << '\n';
  };
  inline T GetValue() const { return Value; }
};
} // namespace AST
} // namespace Language

#endif
