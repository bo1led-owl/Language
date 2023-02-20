#ifndef STMT_HH
#define STMT_HH

#include <memory>

#include "Types.hh"

namespace Language {
namespace AST {
class Decl;

/// Base AST statement class
class Stmt {
 public:
  virtual ~Stmt();
};

/// Integer literal statement class
class IntStmt : public Stmt {
  i32 Value;

 public:
  IntStmt(const i32 value) : Value(value) {}
};

class DeclStmt : public Stmt {
  std::unique_ptr<Decl> Value;

 public:
  DeclStmt(std::unique_ptr<Decl> decl) : Value(std::move(decl)) {}
};
} // namespace AST
} // namespace Language

#endif