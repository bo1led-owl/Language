#include <any>
#include <cstring>
#include <iostream>
#include <memory>
#include <vector>

#include "AST/Decl.hh"
#include "AST/DeclBase.hh"
#include "Driver/Driver.hh"
#include "Lex/Token.hh"
#include "Lex/TokenKind.hh"
#include "Parse/Exception.hh"

namespace Language {
namespace Driver {

void Driver::Run() {
    if (ArgCount < 3) {
        Execute();
    } else {
        if (std::strcmp(Args[2], "--tokens") == 0) {
            PrintTokens();
        } else if (std::strcmp(Args[2], "--ast") == 0) {
            PrintAST();
        } else {
            std::cerr << "Unknown flag\nUse\n--tokens to print tokens\n--ast to "
                         "print AST\n";
        }
    }
}

void Driver::Execute() {
    try {
        const std::vector<std::shared_ptr<AST::Decl>> AST{Parser.Parse()};
        std::shared_ptr<Scope> scope{std::make_shared<Scope>(nullptr, nullptr)};
        scope->SetTopParent(scope);
        for (auto &decl : AST) {
            switch (decl->GetKind()) {
            case AST::Decl::Kind::Fn: {
                auto fnDecl{static_cast<AST::FnDecl *>(decl.get())};
                scope->AddFunction(std::unique_ptr<AST::FnDecl>(fnDecl));
                break;
            }
            case AST::Decl::Kind::Var: {
                auto varDecl{static_cast<AST::VarDecl *>(decl.get())};
                varDecl->Exec(scope);
                break;
            }
            default:
                return;
            }
        }
        // exec "main"
        const std::string &type{scope->GetFnDecl("main")->GetType()};
        if (type == "int") {
            std::cout << std::any_cast<i32>(scope->ExecFn("main")->Value) << '\n';
        } else if (type == "float") {
            std::cout << std::any_cast<f64>(scope->ExecFn("main")->Value) << '\n';
        }
    } catch (const Parse::ParseException &e) {
        std::cout << "Error on line " << Lexer.GetCurLine() << ":\n" << e.what() << '\n';
        return;
    }
}

void Driver::PrintTokens() {
    while (true) {
        const auto t = Lexer.LexToken();
        t->Print();
        if (t->Is(Language::Lex::TokenKind::EndOfInput)) {
            return;
        }
    }
}

void Driver::PrintAST() {
    try {
        const auto AST{Parser.Parse()};
        for (const auto &decl : AST) {
            decl->Print();
        }
    } catch (const Parse::ParseException &e) {
        std::cout << "Error on line " << Lexer.GetCurLine() << ":\n" << e.what() << '\n';
        return;
    }
}
} // namespace Driver
} // namespace Language
