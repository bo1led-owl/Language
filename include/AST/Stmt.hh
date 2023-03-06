#ifndef STMT_HH
#define STMT_HH

#include <memory>

#include "AST/DeclBase.hh"
#include "Types.hh"

namespace Language {
namespace AST {
/// Base AST statement class
class Stmt {
  std::string Type;

 public:
  Stmt() : Type("void") {}
  Stmt(const std::string &type) : Type(type) {}
  virtual ~Stmt() = default;

  inline const std::string &GetType() const { return Type; }
};

/// Declaration statement (e.g. variable declaration in function body)
class DeclStmt : public Stmt {
  std::shared_ptr<Decl> Value;

 public:
  DeclStmt(std::shared_ptr<Decl> decl) : Value(decl) {}

  inline std::shared_ptr<Decl> GetValue() const { return Value; }
};
} // namespace AST
} // namespace Language

#endif
