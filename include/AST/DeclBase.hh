#ifndef DECLBASE_HH
#define DECLBASE_HH

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
/// Base AST declaration class
class Decl {
  protected:
    std::string Name;
    std::string Type;

  public:
    enum class Kind {
        Base,
        Var,
        Fn,
    };

    Decl(const std::string &name, const std::string &type) : Name(name), Type(type) {}
    virtual ~Decl() = default;

    virtual std::shared_ptr<Driver::Object> Exec(std::shared_ptr<Driver::Scope> scope) {
        return std::make_shared<Driver::Object>(std::any());
    }

    virtual Kind GetKind() { return Kind::Base; }

    /// Print Decl as an AST element
    virtual void Print(const i32 offset = 0) { Print::MakeOffset(offset); }

    inline const std::string &GetName() const { return Name; }
    inline const std::string &GetType() const { return Type; }
};
} // namespace AST
} // namespace Language
#endif
