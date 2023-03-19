#include <any>
#include <iostream>
#include <memory>

#include "AST/Expr.hh"
#include "AST/LiteralExpr.hh"
#include "Driver/Object.hh"
#include "Lex/TokenKind.hh"
#include "Print/Print.hh"

namespace Language {
namespace AST {
void BinExpr::Print(const i32 offset) {
    Print::MakeOffset(offset);
    std::cout << "BinExpr \"";
    switch (Operator) {
    case Lex::TokenKind::Plus:
        std::cout << "+";
        break;
    case Lex::TokenKind::Minus:
        std::cout << "-";
        break;
    case Lex::TokenKind::Asterisk:
        std::cout << "*";
        break;
    case Lex::TokenKind::Slash:
        std::cout << "/";
        break;
    case Lex::TokenKind::Equals:
        std::cout << "=";
        break;
    case Lex::TokenKind::LessThan:
        std::cout << "<";
        break;
    case Lex::TokenKind::GreaterThan:
        std::cout << ">";
        break;
    default:
        break;
    }
    std::cout << "\" {\n";
    LHS->Print(offset + 1);
    RHS->Print(offset + 1);

    Print::MakeOffset(offset);
    std::cout << "}\n";
}

template <typename T> std::any BinExpr::Calc(std::any a, std::any b) {
    const T aValue{std::any_cast<T>(a)};
    const T bValue{std::any_cast<T>(b)};
    T res;
    switch (Operator) {
    case Lex::TokenKind::Plus:
        res = aValue + bValue;
        break;
    case Lex::TokenKind::Minus:
        res = aValue - bValue;
        break;
    case Lex::TokenKind::Asterisk:
        res = aValue * bValue;
        break;
    case Lex::TokenKind::Slash:
        res = aValue / bValue;
        break;
    default:
        return std::any();
    }
    return std::any(res);
}

std::shared_ptr<Driver::Object> BinExpr::Exec(std::shared_ptr<Driver::Scope> scope) {
    if (Operator == Lex::TokenKind::Equals) {
        const std::string varName{static_cast<VarRefExpr *>(LHS.get())->GetName()};
        scope->SetValue(varName, RHS->Exec(scope));
        return scope->GetValue(varName);
    }
    // TODO comparison

    auto lhsValue = LHS->Exec(scope)->Value;
    auto rhsValue = RHS->Exec(scope)->Value;
    if (!lhsValue.has_value() || !rhsValue.has_value()) {
        return std::make_shared<Driver::Object>();
    }

    if (Type == "int") {
        return std::make_shared<Driver::Object>(Calc<i32>(lhsValue, rhsValue));
    }
    if (Type == "float") {
        return std::make_shared<Driver::Object>(Calc<f64>(lhsValue, rhsValue));
    }

    return std::make_shared<Driver::Object>();
}

void VarRefExpr::Print(const i32 offset) {
    Print::MakeOffset(offset);
    std::cout << "VarRefExpr " << Name << '\n';
};

std::shared_ptr<Driver::Object> VarRefExpr::Exec(std::shared_ptr<Driver::Scope> scope) {
    return scope->GetValue(Name);
}

void CallExpr::Print(const i32 offset) {
    Print::MakeOffset(offset);
    std::cout << "CallExpr " << Callee;
    std::cout << '(';
    if (Args.size() > 0) {
        std::cout << '\n';
    }
    for (size_t i{}; i < Args.size(); ++i) {
        Args[i]->Print(offset + 1);
    }
    if (Args.size() > 0) {
        Print::MakeOffset(offset);
    }
    std::cout << ")\n";
}

std::shared_ptr<Driver::Object> CallExpr::Exec(std::shared_ptr<Driver::Scope> scope) {
    std::vector<std::shared_ptr<Driver::Object>> args{};
    for (const auto &arg : Args) {
        args.push_back(arg->Exec(scope));
    }
    return scope->ExecFn(Callee, args);
}
} // namespace AST
} // namespace Language
