#ifndef STMT_HH
#define STMT_HH

#include <memory>

#include "AST/Block.hh"
#include "AST/DeclBase.hh"
#include "Print/Print.hh"
#include "Types.hh"

namespace Language {
namespace AST {
/// Declaration statement (e.g. variable declaration in function body)
class DeclStmt : public Stmt {
  std::shared_ptr<Decl> Value;

 public:
  DeclStmt(std::shared_ptr<Decl> decl) : Value(decl) {}

  void Print(const i32 offset = 0) override;
  inline std::shared_ptr<Decl> GetValue() const { return Value; }
};

class BlockStmt : public Stmt {
  std::shared_ptr<Block> Value;

 public:
  BlockStmt(std::shared_ptr<Block> block) : Value(block) {}

  void Print(const i32 offset = 0) override;
  std::shared_ptr<Block> GetValue() { return Value; }
};
} // namespace AST
} // namespace Language

#endif
