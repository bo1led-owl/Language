#include <memory>

#include "AST/Block.hh"

namespace Language {
namespace AST {
const std::shared_ptr<VarDecl> Block::SearchForVariable(const std::string &name) {
  if (Variables.contains(name))
    return Variables[name];
  if (ParentBlock != nullptr)
    return ParentBlock->SearchForVariable(name);

  return nullptr;
}
} // namespace AST
} // namespace Language
