#include <iostream>
#include <memory>

#include "AST/Block.hh"
#include "Driver/Object.hh"
#include "Driver/Scope.hh"
#include "Print/Print.hh"

namespace Language {
namespace AST {
std::shared_ptr<Driver::Object> Block::Exec(std::shared_ptr<Driver::Scope> scope) {
    for (auto &stmt : Body) {
        if (stmt->IsReturn()) {
            return stmt->Exec(scope);
        }
        stmt->Exec(scope);
    }
    return std::make_shared<Driver::Object>();
}

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
