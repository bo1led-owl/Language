#ifndef EXPR_HH
#define EXPR_HH

#include <memory>
#include <string>
#include <vector>

#include "AST/Stmt.hh"
#include "Types.hh"

namespace Language {
namespace AST {
/// Base AST expression class
class Expr : public Stmt {
 public:
  Expr(const std::string &type) : Stmt(type) {}
};

/// Binary operation expression class
class BinaryExpr : public Expr {
 public:
  enum class Operator : i8 {
    Plus,
    Minus,
    Multiply,
    Divide,
  };

 private:
  Operator Op;
  std::unique_ptr<Expr> LHS, RHS;

  BinaryExpr(const Operator op, std::unique_ptr<Expr> lhs, std::unique_ptr<Expr> rhs)
      : Expr(lhs->GetType()), Op(op), LHS(std::move(lhs)), RHS(std::move(rhs)) {}

  inline Operator GetOperator() const { return Op; }
};

/// Variable reference expression class
class VarRefExpr : public Expr {
  std::string Name;

 public:
  VarRefExpr(const std::string &name, const std::string &type) : Expr(type), Name(name) {}

  inline const std::string &GetName() const { return Name; }
};

/// Function call expression class
class CallExpr : public Expr {
  std::string CalleeName;
  std::vector<std::unique_ptr<Expr>> Args;

 public:
  CallExpr(const std::string &callee, const std::string &type,
           std::vector<std::unique_ptr<Expr>> args)
      : Expr(type), CalleeName(callee), Args(std::move(args)) {}

  inline const std::string &GetCalleeName() { return CalleeName; }
  inline const std::vector<std::unique_ptr<Expr>> &GetArgs() { return Args; }
};
} // namespace AST
} // namespace Language

#endif
