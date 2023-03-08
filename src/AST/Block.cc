#include <iostream>
#include <memory>

#include "AST/Block.hh"
#include "Print/Print.hh"

namespace Language {
namespace AST {
const std::shared_ptr<VarDecl> Block::SearchForVariable(const std::string &name) {
  if (Variables.contains(name))
    return Variables[name];
  if (ParentBlock != nullptr)
    return ParentBlock->SearchForVariable(name);

  return nullptr;
}

void Block::Print(i32 offset) {
  // Print::MakeOffset(offset);

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
} // namespace AST
} // namespace Language
