#ifndef LITERALEXPR_HH
#define LITERALEXPR_HH

#include "AST/Expr.hh"
#include "Types.hh"

namespace Language {
namespace AST {
/// Literal expression class (e.g. 5, 1.1, "hello")
template <typename T> class LiteralExpr : public Expr {
  T Value;

 public:
  LiteralExpr(const std::string &type) : Expr(type) {}
  LiteralExpr(const std::string &type, const T value) : Expr(type), Value(value) {}

  inline T GetValue() const { return Value; }
};
} // namespace AST
} // namespace Language

#endif
