#include <unordered_set>

#include "Lex/Token.hh"
#include "Lex/TokenKind.hh"
#include "Parse/Exception.hh"
#include "Parse/Parser.hh"

namespace Language {
namespace Parse {
std::unique_ptr<AST::VarDecl> Parser::ParseVarDecl() {
    // eat "let"
    Advance();

    // check whether the variable is mutable
    bool mut{CurToken->Is(Lex::TokenKind::Mut)};
    EAT_IF_TOKEN_IS(Lex::TokenKind::Mut)

    // variable name parsing
    // missing variable name
    THROW_IF_TOKEN_IS_NOT(Lex::TokenKind::Identifier, "missing variable name")
    std::string varName{CurToken->GetIdentifierData()};
    if (VariableDeclared(varName) ||
        (CurFn != nullptr && CurFn->GetArgumentByName(varName) != nullptr)) {
        // variable is already declared
        throw ParseException{"variable with name \"" + varName +
                             "\" is already declared"};
    }
    // eat variable name
    Advance();

    // variable type parsing
    std::string varType{};
    if (CurToken->Is(Lex::TokenKind::Colon)) {
        // eat ":"
        Advance(); // missing variable type
        THROW_IF_TOKEN_IS_NOT(Lex::TokenKind::Identifier, "missing variable type")
        varType = CurToken->GetIdentifierData();
        // eat variable type
        Advance();
    }

    // variable value parsing (if presented)
    std::unique_ptr<AST::Expr> varValue{nullptr};
    if (CurToken->Is(Lex::TokenKind::Equals)) {
        // eat "="
        Advance();
        varValue = ParseExpr();
        if (varType.empty()) {
            varType = varValue->GetType();
        } else if (varType != varValue->GetType()) {
            // variable and value type mismatch
            throw ParseException{
                "declared variable type differs from the type of its value"};
        }
    }

    if (CurToken->IsNot(Lex::TokenKind::Newline) &&
        CurToken->IsNot(Lex::TokenKind::EndOfInput) &&
        CurToken->IsNot(Lex::TokenKind::LCurBracket) &&
        CurToken->IsNot(Lex::TokenKind::RCurBracket) &&
        CurToken->IsNot(Lex::TokenKind::Comment)) {
        // unexpected token at the end of statement
        throw ParseException{"unexpected token at the end of statement"};
    }

    // eat newline and NOT eat end of input
    EAT_IF_TOKEN_IS(Lex::TokenKind::Newline)
    return std::make_unique<AST::VarDecl>(varName, varType, mut, varValue);
}

std::unique_ptr<AST::FnDecl> Parser::ParseFnDecl() {
    // eat "fn"
    Advance();

    // function name parsing
    // mising function name
    THROW_IF_TOKEN_IS_NOT(Lex::TokenKind::Identifier, "missing function name declaration")
    std::string fnName = CurToken->GetIdentifierData();
    if (Functions.contains(fnName)) {
        // function is already declared
        throw ParseException{"function with name \"" + fnName + "\" is already declared"};
    }
    // eat function name
    Advance();
    // missing function argument list
    THROW_IF_TOKEN_IS_NOT(Lex::TokenKind::LParen, "expected function arguments")
    // eat "("
    Advance();

    // function arguments parsing
    std::vector<AST::FnDecl::Argument> fnArgs;
    std::unordered_set<std::string> argNames;
    while (CurToken->IsNot(Lex::TokenKind::RParen)) {
        // missing argument name
        THROW_IF_TOKEN_IS_NOT(Lex::TokenKind::Identifier,
                              "missing argument name declaration")

        std::string argName = CurToken->GetIdentifierData();
        if (argNames.contains(argName)) {
            // argument name duplicate
            throw ParseException{"argument with name " + argName +
                                 " is already declared in that function"};
        }
        if (VariableDeclared(argName)) {
            // variable with the name of the argument is declared
            throw ParseException{
                "variable with name \"" + argName +
                "\" is already declared, this name cannot be used as an argument name"};
        }
        argNames.emplace(argName);
        // eat argument name
        Advance();
        // missing argument type (missing ":")
        THROW_IF_TOKEN_IS_NOT(Lex::TokenKind::Colon, "missing argument type declaration")
        // eat ":"
        Advance();
        // missing argument type (missing type identifier)
        THROW_IF_TOKEN_IS_NOT(Lex::TokenKind::Identifier,
                              "missing argument type declaration")

        if (!Types.contains(CurToken->GetIdentifierData())) {
            // unknown argument type
            throw ParseException{"unknown argument type"};
        }
        std::string argType{CurToken->GetIdentifierData()};
        // eat argument type
        Advance();
        fnArgs.push_back(AST::FnDecl::Argument{argName, argType});
        EAT_IF_TOKEN_IS(Lex::TokenKind::Comma)
    }
    // eat ")"
    Advance();

    // parse function return type (if presented)
    std::string fnReturnType{""};
    if (CurToken->Is(Lex::TokenKind::RightArrow)) {
        // eat "->"
        Advance();
        // missing return type
        THROW_IF_TOKEN_IS_NOT(Lex::TokenKind::Identifier, "missing function return type")
        fnReturnType = CurToken->GetIdentifierData();
        if (!Types.contains(fnReturnType)) {
            // unknown function return type
            throw ParseException{"unknown function return type"};
        }
        // eat return type
        Advance();
    }

    CurFn = std::make_unique<AST::FnDecl>(fnName, fnReturnType, fnArgs);

    // parse function body
    CurFn->SetBody(ParseBlock());
    if (CurFn->GetType() != "" && !CurFn->HasReturnStmt()) {
        // no return
        throw ParseException{"function do not return a value, but is declared to"};
    }

    auto result = std::move(CurFn);
    CurFn = nullptr;
    return result;
}
} // namespace Parse
} // namespace Language
