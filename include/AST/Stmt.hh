#ifndef STMT_HH
#define STMT_HH

#include <memory>

#include "AST/Block.hh"
#include "AST/DeclBase.hh"
#include "Driver/Object.hh"
#include "Driver/Scope.hh"
#include "Print/Print.hh"
#include "Types.hh"

namespace Language {
namespace AST {
class ReturnStmt : public Stmt {
    std::unique_ptr<Expr> Value;

  public:
    ReturnStmt(std::unique_ptr<Expr> expr) : Value(std::move(expr)) {}

    std::shared_ptr<Driver::Object> Exec(std::shared_ptr<Driver::Scope> scope) override {
        return Value->Exec(scope);
    }

    bool IsReturn() override { return true; }

    /// Print ReturnStmt as an AST element
    void Print(const i32 offset = 0) override;
    const std::unique_ptr<Expr> &GetValue() const { return Value; }
};

/// Declaration statement (e.g. variable declaration in function body)
class DeclStmt : public Stmt {
    std::shared_ptr<Decl> Value;

  public:
    DeclStmt(std::shared_ptr<Decl> decl) : Value(decl) {}

    std::shared_ptr<Driver::Object> Exec(std::shared_ptr<Driver::Scope> scope) override {
        Value->Exec(scope);
        return std::make_shared<Driver::Object>();
    }

    /// Print DeclStmt as an AST element
    void Print(const i32 offset = 0) override;
    inline std::shared_ptr<Decl> GetValue() const { return Value; }
};

class BlockStmt : public Stmt {
    std::shared_ptr<Block> Value;

  public:
    BlockStmt(std::shared_ptr<Block> block) : Value(block) {}

    std::shared_ptr<Driver::Object> Exec(std::shared_ptr<Driver::Scope> scope) override {
        Value->Exec(scope);
        return std::make_shared<Driver::Object>();
    }

    /// Print BlockStmt as an AST element
    void Print(const i32 offset = 0) override;
    std::shared_ptr<Block> GetValue() { return Value; }
};
} // namespace AST
} // namespace Language

#endif
