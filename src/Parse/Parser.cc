#include <cstddef>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "AST/Block.hh"
#include "AST/Decl.hh"
#include "AST/Expr.hh"
#include "AST/LiteralExpr.hh"
#include "AST/Stmt.hh"
#include "Lex/Lexer.hh"
#include "Lex/Token.hh"
#include "Lex/TokenKind.hh"
#include "Parse/Exception.hh"
#include "Parse/Parser.hh"
#include "Types.hh"

namespace Language {
namespace Parse {
const std::unordered_set<std::string> Parser::Types{"bool", "int", "float"};

std::unordered_map<Lex::TokenKind, i32> Parser::BinopPrecedence{
    {Lex::TokenKind::Equals, 5},       // <
    {Lex::TokenKind::LessThan, 20},    // <
    {Lex::TokenKind::GreaterThan, 20}, // >
    {Lex::TokenKind::Plus, 30},        // +
    {Lex::TokenKind::Minus, 30},       // -
    {Lex::TokenKind::Asterisk, 40},    // -
    {Lex::TokenKind::Slash, 40},       // -
};

bool Parser::VariableDeclared(const std::string &name) {
    if (CurBlock != nullptr) {
        if (CurBlock->VariableDeclared(name)) {
            return true;
        }
    }
    return Variables.contains(name);
}

std::shared_ptr<AST::VarDecl> Parser::GetVarDecl(const std::string &name) {
    if (Variables.contains(name)) {
        return Variables[name];
    }
    if (CurBlock->VariableDeclared(name)) {
        return CurBlock->GetVarDecl(name);
    }
    throw ParseException{"cannot find variable with name" + name};
}

std::vector<std::shared_ptr<AST::Decl>> Parser::Parse() {
    std::vector<std::shared_ptr<AST::Decl>> AST;

    while (CurToken->IsNot(Lex::TokenKind::EndOfInput)) {
        switch (CurToken->GetKind()) {
        case Lex::TokenKind::Newline:
            Advance();
            break;
        case Lex::TokenKind::Comment:
            while (CurToken->IsNot(Lex::TokenKind::Newline) &&
                   CurToken->IsNot(Lex::TokenKind::EndOfInput)) {
                Advance();
            }
            break;
        case Lex::TokenKind::Fn: {
            std::shared_ptr<AST::FnDecl> decl{ParseFnDecl()};
            AST.push_back(decl);
            Functions[decl->GetName()] = decl;
        } break;
        case Lex::TokenKind::Let: {
            std::shared_ptr<AST::VarDecl> decl{ParseVarDecl()};
            AST.push_back(decl);
            Variables[decl->GetName()] = decl;
        } break;
        default:
            throw ParseException{"expected function or variable declaration"};
        }
    }

    Variables.clear();
    Functions.clear();
    return AST;
}
} // namespace Parse
} // namespace Language
