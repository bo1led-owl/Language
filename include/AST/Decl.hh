#ifndef DECL_HH
#define DECL_HH

#include <memory>
#include <string>
#include <vector>

#include "AST/DeclBase.hh"
#include "AST/ExprBase.hh"

namespace Language {
namespace AST {
class Block;

/// Variable declaration class
class VarDecl : public Decl {
  bool Mutable;
  // value is optional
  std::unique_ptr<Expr> Value;

 public:
  VarDecl(const std::string &name, const std::string &type, const bool mut,
          std::unique_ptr<Expr> &value)
      : Decl(name, type), Mutable(mut), Value(std::move(value)) {}

  void Print(const i32 offset = 0) override;
  inline bool IsMutable() const { return Mutable; }
  inline std::unique_ptr<Expr> &GetValue() { return Value; }
};

/// Function declaration class
class FnDecl : public Decl {
 public:
  struct Argument {
    std::string Name;
    std::string Type;

    Argument(const std::string &name, const std::string &type) : Name(name), Type(type) {}
  };

 private:
  std::vector<Argument> Args;
  std::shared_ptr<Block> Body;

  bool HasReturn{false};

 public:
  FnDecl(const std::string &name, const std::string &returnType,
         std::vector<Argument> args)
      : Decl(name, returnType), Args(std::move(args)) {}

  FnDecl(const std::string &name, const std::string &returnType,
         std::vector<Argument> args, std::shared_ptr<Block> &body)
      : Decl(name, returnType), Args(std::move(args)), Body(std::move(body)) {}

  size_t GetArgCount() const { return Args.size(); }
  std::unique_ptr<AST::FnDecl::Argument> GetArgumentByName(const std::string &name) const;
  std::unique_ptr<AST::FnDecl::Argument> GetArgumentByIndex(const size_t) const;
  inline void SetBody(std::shared_ptr<Block> body) { Body = body; }
  inline void AddReturnStmt() { HasReturn = true; }
  inline bool HasReturnStmt() { return HasReturn; }
  void Print(const i32 offset = 0) override;
};
} // namespace AST
} // namespace Language

#endif
