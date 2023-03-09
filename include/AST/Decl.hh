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

  /// Print VarDecl as an AST element
  void Print(const i32 offset = 0) override;

  inline bool IsMutable() const { return Mutable; }
  inline const std::unique_ptr<Expr> &GetValue() { return Value; }
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

  /// Prints FnDecl as an AST element
  void Print(const i32 offset = 0) override;

  size_t GetArgCount() const { return Args.size(); }
  /// Returns a pointer to an Argument object if an argument with given name exists
  std::unique_ptr<AST::FnDecl::Argument> GetArgumentByName(const std::string &name) const;

  /// Returns a pointer to an Argument object at the given index in the Args vector if
  /// that argument exists
  std::unique_ptr<AST::FnDecl::Argument> GetArgumentByIndex(const size_t) const;

  /// Set function body
  inline void SetBody(std::shared_ptr<Block> body) { Body = body; }
  /// Sets HasReturn to true
  inline void AddReturnStmt() { HasReturn = true; }
  inline bool HasReturnStmt() { return HasReturn; }
};
} // namespace AST
} // namespace Language

#endif
