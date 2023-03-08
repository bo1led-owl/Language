#ifndef BLOCK_HH
#define BLOCK_HH

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "AST/Decl.hh"
#include "AST/StmtBase.hh"

namespace Language {
namespace AST {
/// Statement block class (e.g. function or "if" body)
class Block {
  std::shared_ptr<Block> ParentBlock;

  std::unordered_map<std::string, std::shared_ptr<VarDecl>> Variables;
  std::vector<std::unique_ptr<Stmt>> Body;

 public:
  Block() : ParentBlock(nullptr) {}
  Block(std::shared_ptr<Block> parent) : ParentBlock(std::move(parent)) {}
  virtual ~Block() = default;

  void Print(const i32 offset = 0);
  void AddVariable(const std::string &name, std::shared_ptr<VarDecl> decl) {
    Variables[name] = decl;
  }
  void AddToBody(std::unique_ptr<Stmt> stmt) { Body.emplace_back(std::move(stmt)); }

  bool VariableDeclared(const std::string &name);
  std::shared_ptr<VarDecl> GetVarDecl(const std::string &name);
  inline std::shared_ptr<Block> GetParent() { return ParentBlock; }
};
} // namespace AST
} // namespace Language

#endif
