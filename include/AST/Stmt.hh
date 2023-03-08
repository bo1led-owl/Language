#ifndef STMT_HH
#define STMT_HH

#include <memory>

#include "AST/DeclBase.hh"
#include "Print/Print.hh"
#include "Types.hh"

namespace Language {
namespace AST {
/// Base AST statement class
class Stmt {
 protected:
  std::string Type;

 public:
  Stmt() : Type("void") {}
  Stmt(const std::string &type) : Type(type) {}
  virtual ~Stmt() = default;

  virtual void Print(i32 offset = 0) { Print::MakeOffset(offset); };

  inline const std::string &GetType() const { return Type; }
};

/// Declaration statement (e.g. variable declaration in function body)
class DeclStmt : public Stmt {
  std::shared_ptr<Decl> Value;

 public:
  DeclStmt(std::shared_ptr<Decl> decl) : Value(decl) {}

  void Print(i32 offset = 0) override;
  inline std::shared_ptr<Decl> GetValue() const { return Value; }
};
} // namespace AST
} // namespace Language

#endif
