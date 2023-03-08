#include <iostream>
#include <memory>

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
    std::cout << Args[i].Name << ": " << Args[i].Type;
    if (i != Args.size() - 1) {
      std::cout << ", ";
    }
  }
  std::cout << ") ";
  Body->Print(offset);
}

std::unique_ptr<AST::FnDecl::Argument>
FnDecl::GetArgumentByName(const std::string &name) const {
  for (const auto &arg : Args) {
    if (arg.Name == name) {
      return std::make_unique<AST::FnDecl::Argument>(arg);
    }
  }
  return nullptr;
}

std::unique_ptr<AST::FnDecl::Argument> FnDecl::GetArgumentByIndex(const size_t index) const {
  if (Args.size() > index) {
    return std::make_unique<AST::FnDecl::Argument>(Args[index]);
  }
  return nullptr;
}
} // namespace AST
} // namespace Language
