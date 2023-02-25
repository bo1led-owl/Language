#ifndef DECL_HH
#define DECL_HH

#include <memory>
#include <string>
#include <vector>

#include "AST/BuiltinTypes.hh"
#include "AST/Expr.hh"

namespace Language {
namespace AST {
/// Base AST declaration class
class Decl {
 public:
  virtual ~Decl() = default;
};

/// Variable declaration class
class VarDecl : public Decl {
  std::string Name;
  DataType Type;

 public:
  VarDecl(const std::string &name, DataType type) : Name(name), Type(type) {}
};

/// Function declaration class
class FnDecl : public Decl {
 public:
  struct Argument {
    std::string Name;
    DataType Type;

    Argument(const std::string &name, DataType type) : Name(name), Type(type) {}
  };

 private:
  std::string Name;
  std::vector<Argument> Args;
  DataType ReturnType;
  std::unique_ptr<Expr> Body;

 public:
  FnDecl(const std::string &name, std::vector<Argument> args, DataType returnType,
         std::unique_ptr<Expr> &body)
      : Name(name), Args(std::move(args)), ReturnType(returnType), Body(std::move(body)) {
  }
};
} // namespace AST
} // namespace Language

#endif