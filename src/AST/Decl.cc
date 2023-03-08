#include <iostream>

#include "AST/Block.hh"
#include "AST/Decl.hh"
#include "Print/Print.hh"

namespace Language {
namespace AST {
void VarDecl::Print(const i32 offset) {
  Print::MakeOffset(offset);

  std::cout << "VarDecl " << Name << ' ';
  if (Mutable) {
    std::cout << "mut ";
  }
  std::cout << '\"' << Type << "\"";
  if (Value != nullptr) {
    std::cout << " = \n";
    Value->Print(offset + 1);
  } else {
    std::cout << '\n';
  }
}

void FnDecl::Print(const i32 offset) {
  std::cout << "FnDecl \"";
  if (Type.empty()) {
    std::cout << "void";
  } else {
    std::cout << Type;
  }
  std::cout << "\" " << Name;
  std::cout << '(';
  for (size_t i{}; i < Args.size(); ++i) {
    std::cout << Args[i].Type;
    if (i != Args.size() - 1) {
      std::cout << ", ";
    }
  }
  std::cout << ") ";
  Body->Print(offset);
}
} // namespace AST
} // namespace Language
