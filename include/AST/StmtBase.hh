#ifndef STMTBASE_HH
#define STMTBASE_HH

#include <memory>
#include <string>

#include "Driver/Object.hh"
#include "Print/Print.hh"
#include "Types.hh"

namespace Language {
namespace Driver {
class Scope;
}
namespace AST {
/// Base AST statement class
class Stmt {
  protected:
    std::string Type;

  public:
    Stmt() : Type("void") {}
    Stmt(const std::string &type) : Type(type) {}
    virtual ~Stmt() = default;

    virtual std::shared_ptr<Driver::Object> Exec(std::shared_ptr<Driver::Scope> scope) {
        return std::make_shared<Driver::Object>();
    }

    virtual bool IsReturn() { return false; }

    /// Print Stmt as an AST element
    virtual void Print(const i32 offset = 0) { Print::MakeOffset(offset); };
    inline const std::string &GetType() const { return Type; }
};
} // namespace AST
} // namespace Language

#endif
