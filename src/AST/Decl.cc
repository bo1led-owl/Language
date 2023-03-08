#include <iostream>

#include "AST/Block.hh"
#include "AST/Decl.hh"
#include "Print/Print.hh"

namespace Language {
namespace AST {
void VarDecl::Print(i32 offset) {
  Print::MakeOffset(offset);

  std::cout << "VarDecl " << Name << ' ';
  if (Mutable) {
    std::cout << "mut ";
  }
  std::cout << '\"' << Type << "\" = ";
  if (Value != nullptr) {
    std::cout << '\n';
    Value->Print(offset + 1);
  }
}

void FnDecl::Print(i32 offset) {
  std::cout << "FnDecl \"";
  if (Type.empty()) {
    std::cout << "void";
  } else {
    std::cout << Type;
  }
  std::cout << "\" " << Name;
  std::cout << '(';
  for (const FnDecl::Argument &arg : Args) {
    std::cout << arg.Type << ", ";
  }
  std::cout << ") ";
  Body->Print(offset);
}
} // namespace AST
} // namespace Language
