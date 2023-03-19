#ifndef LITERALEXPR_HH
#define LITERALEXPR_HH

#include <iostream>
#include <memory>

#include "AST/Expr.hh"
#include "Driver/Object.hh"
#include "Driver/Scope.hh"
#include "Print/Print.hh"
#include "Types.hh"

namespace Language {
namespace AST {
/// AST literal expression class (e.g. 5, 1.1, "hello")
template <typename T> class LiteralExpr : public Expr {
    T Value;

  public:
    LiteralExpr(const std::string &type) : Expr(type) {}
    LiteralExpr(const std::string &type, const T value) : Expr(type), Value(value) {}

    std::shared_ptr<Driver::Object> Exec(std::shared_ptr<Driver::Scope>) override { return std::make_shared<Driver::Object>(Value); }

    /// Print LiteralExpr as an AST element
    void Print(const i32 offset = 0) override {
        Print::MakeOffset(offset);

        std::cout << "LiteralExpr \"" << Type << "\" " << Value << '\n';
    };

    inline T GetValue() const { return Value; }
};
} // namespace AST
} // namespace Language

#endif
