#ifndef EXPR_HH
#define EXPR_HH

#include <memory>
#include <string>
#include <vector>

#include "AST/ExprBase.hh"
#include "AST/Stmt.hh"
#include "Lex/TokenKind.hh"
#include "Types.hh"

namespace Language {
namespace AST {
/// Binary operation expression class
class BinaryExpr : public Expr {
  Lex::TokenKind Operator;
  std::unique_ptr<Expr> LHS, RHS;

 public:
  BinaryExpr(const Lex::TokenKind op, std::unique_ptr<Expr> lhs,
             std::unique_ptr<Expr> rhs)
      : Expr(lhs->GetType()), Operator(op), LHS(std::move(lhs)), RHS(std::move(rhs)) {}

  void Print(const i32 offset = 0) override;
  inline Lex::TokenKind GetOperator() const { return Operator; }
};

/// Variable reference expression class
class VarRefExpr : public Expr {
  std::string Name;

 public:
  VarRefExpr(const std::string &name, const std::string &type) : Expr(type), Name(name) {}

  void Print(const i32 offset = 0) override;
  inline const std::string &GetName() const { return Name; }
};

/// Function argument reference expression class
class ArgRefExpr : public VarRefExpr {};

/// Function call expression class
class CallExpr : public Expr {
  std::string Callee;
  std::vector<std::unique_ptr<Expr>> Args;

 public:
  CallExpr(const std::string &callee, const std::string &type,
           std::vector<std::unique_ptr<Expr>> args)
      : Expr(type), Callee(callee), Args(std::move(args)) {}

  void Print(const i32 offset = 0) override;
  inline const std::string &GetCallee() { return Callee; }
  inline const std::vector<std::unique_ptr<Expr>> &GetArgs() { return Args; }
};
} // namespace AST
} // namespace Language

#endif
