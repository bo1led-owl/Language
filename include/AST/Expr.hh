#ifndef EXPR_HH
#define EXPR_HH

#include <memory>
#include <string>
#include <vector>

#include "AST/BinaryExprKind.hh"
#include "AST/Type.hh"
#include "Types.hh"

namespace Language {
namespace AST {
/// The base class for all AST expression classes
class Expr {
 public:
  virtual ~Expr() {}
};

/// Expression class for integer literals
class IntegerExpr : public Expr {
  i32 Value;

 public:
  IntegerExpr(const i32 value) : Value(value) {}
};

/// Expression class for variables
class VariableExpr : public Expr {
  std::string Name;
  DataType Type;

 public:
  VariableExpr(const std::string &name, DataType type) : Name(name), Type(type) {}
};

/// Expression class for a binary operation
class BinaryExpr : public Expr {
  BinaryExprKind Kind;
  std::unique_ptr<Expr> LHS, RHS;

 public:
  BinaryExpr(const BinaryExprKind K, std::unique_ptr<Expr> lhs, std::unique_ptr<Expr> rhs)
      : Kind(K), LHS(std::move(lhs)), RHS(std::move(rhs)) {}
};

/// Expression class for a function declaration
class FunctionDecl : public Expr {
  struct Argument {
    std::string Name;
    DataType Type;

    Argument(const std::string &name, DataType type) : Name(name), Type(type) {}
  };

  std::string Name;
  std::vector<Argument> Args;
  DataType ReturnType;
  std::unique_ptr<Expr> Body;

 public:
  FunctionDecl(const std::string &name, std::vector<Argument> args, DataType returnType,
               std::unique_ptr<Expr> body)
      : Name(name), Args(std::move(args)), ReturnType(returnType), Body(std::move(body)) {
  }
};

/// Expression class for a function call
class CallExpr : public Expr {
  std::string Callee;
  std::vector<std::unique_ptr<Expr>> Args;

 public:
  CallExpr(const std::string &callee, std::vector<std::unique_ptr<Expr>> args)
      : Callee(callee), Args(std::move(args)) {}
};
} // namespace AST
} // namespace Language

#endif