#ifndef EXPR_HH
#define EXPR_HH

#include <memory>
#include <string>
#include <vector>

#include "AST/BinaryExprKind.hh"
#include "AST/BuiltinTypes.hh"
#include "AST/Stmt.hh"
#include "Types.hh"

namespace Language {
namespace AST {
/// Base AST expression class
class Expr : public Stmt {};

/// Binary operation expression class
class BinaryExpr : public Expr {
  BinaryExprKind Kind;
  std::unique_ptr<Stmt> LHS, RHS;

 public:
  BinaryExpr(const BinaryExprKind K, std::unique_ptr<Stmt> lhs, std::unique_ptr<Stmt> rhs)
      : Kind(K), LHS(std::move(lhs)), RHS(std::move(rhs)) {}
};

/// Function call expression class
class CallExpr : public Expr {
  std::string Callee;
  std::vector<std::unique_ptr<Stmt>> Args;

 public:
  CallExpr(const std::string &callee, std::vector<std::unique_ptr<Stmt>> args)
      : Callee(callee), Args(std::move(args)) {}
};
} // namespace AST
} // namespace Language

#endif