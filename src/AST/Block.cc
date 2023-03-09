#include <iostream>
#include <memory>

#include "AST/Block.hh"
#include "Print/Print.hh"

namespace Language {
namespace AST {
void Block::Print(const i32 offset) {
  std::cout << "{";
  if (Body.size() != 0) {
    std::cout << '\n';
  }
  for (const std::unique_ptr<Stmt> &stmt : Body) {
    stmt->Print(offset + 1);
  }
  Print::MakeOffset(offset);
  std::cout << "}\n";
}

bool Block::VariableDeclared(const std::string &name) {
  if (Variables.contains(name)) {
    return true;
  }
  if (ParentBlock != nullptr) {
    return ParentBlock->VariableDeclared(name);
  }
  return false;
}

std::shared_ptr<VarDecl> Block::GetVarDecl(const std::string &name) {
  if (Variables.contains(name))
    return Variables[name];
  if (ParentBlock != nullptr)
    return ParentBlock->GetVarDecl(name);

  return nullptr;
}
} // namespace AST
} // namespace Language
