#ifndef BLOCK_HH
#define BLOCK_HH

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "AST/Decl.hh"
#include "AST/StmtBase.hh"
#include "Driver/Object.hh"
#include "Driver/Scope.hh"

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

    std::shared_ptr<Driver::Object> Exec(std::shared_ptr<Driver::Scope> scope);

    /// Print block as an AST element
    void Print(const i32 offset = 0);

    /// Returns a pointer to a parent block object if it exists, else returns nullptr
    inline std::shared_ptr<Block> GetParent() { return ParentBlock; }

    /// Add a statement to the block body
    void AddToBody(std::unique_ptr<Stmt> stmt) { Body.emplace_back(std::move(stmt)); }

    /// Add a variable to the variables map
    void AddVariable(const std::string &name, std::shared_ptr<VarDecl> decl) {
        Variables[name] = decl;
    }

    /// Returns true is a variable with given name is declared in this block or in one of
    /// its ancestors
    bool VariableDeclared(const std::string &name);

    /// Returns a variable declaration from the current block or one of its ancestors if a
    /// variable with given name exists, else returns nullptr
    std::shared_ptr<VarDecl> GetVarDecl(const std::string &name);
};
} // namespace AST
} // namespace Language

#endif
