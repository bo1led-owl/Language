#include <iostream>

#include "AST/Stmt.hh"
#include "Print/Print.hh"

namespace Language {
namespace AST {
void ReturnStmt::Print(const i32 offset) {
  Print::MakeOffset(offset);
  std::cout << "ReturnStmt\n";
  if (Value != nullptr) {
    Value->Print(offset + 1);
  }
}

void DeclStmt::Print(const i32 offset) {
  Print::MakeOffset(offset);
  std::cout << "DeclStmt {\n";
  Value->Print(offset + 1);
  Print::MakeOffset(offset);
  std::cout << "}\n";
}

void BlockStmt::Print(const i32 offset) {
  Print::MakeOffset(offset);
  std::cout << "BlockStmt ";
  Value->Print(offset);
}
} // namespace AST
} // namespace Language
