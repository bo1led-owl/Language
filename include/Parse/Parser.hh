#ifndef PARSER_HH
#define PARSER_HH

#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "AST/Block.hh"
#include "AST/Decl.hh"
#include "AST/LiteralExpr.hh"
#include "AST/Stmt.hh"
#include "Lex/Lexer.hh"
#include "Lex/Token.hh"
#include "Lex/TokenKind.hh"
#include "Parse/Exception.hh"
#include "Types.hh"

#define THROW_IF_TOKEN_IS(Kind, Message)                                                 \
    if (CurToken->Is(Kind)) {                                                            \
        throw ParseException{Message};                                                   \
    }

#define THROW_IF_TOKEN_IS_NOT(Kind, Message)                                             \
    if (CurToken->IsNot(Kind)) {                                                         \
        throw ParseException{Message};                                                   \
    }

#define EAT_IF_TOKEN_IS(Kind)                                                            \
    if (CurToken->Is(Kind)) {                                                            \
        Advance();                                                                       \
    }

#define EAT_WHILE_TOKEN_IS(Kind)                                                         \
    while (CurToken->Is(Kind)) {                                                         \
        Advance();                                                                       \
    }

namespace Language {
namespace Parse {
/// Class for parsing lexed tokens
class Parser {
    Lex::Lexer &Lexer;
    std::unique_ptr<Lex::Token> CurToken;
    std::shared_ptr<AST::Block> CurBlock{nullptr};
    std::unique_ptr<AST::FnDecl> CurFn{nullptr};

    std::unordered_map<std::string, std::shared_ptr<AST::FnDecl>> Functions;
    std::unordered_map<std::string, std::shared_ptr<AST::VarDecl>> Variables;

    static const std::unordered_set<std::string> Types;
    static std::unordered_map<Lex::TokenKind, i32> BinopPrecedence;

    i32 GetCurTokenPrecedence() {
        i32 TokPrec = BinopPrecedence[CurToken->GetKind()];
        if (TokPrec <= 0)
            return -1;
        return TokPrec;
    }

    /// Move to the next token
    inline void Advance() { CurToken = Lexer.LexToken(); }

    inline bool FunctionDeclared(const std::string &name) {
        return Functions.contains(name);
    }

    /// Returns type of the function with given name
    inline std::string GetFunctionType(const std::string &name) {
        return Functions[name]->GetType();
    }

    /// Returns true if a variable with given name is declared in global scope or in
    /// CurBlock or in one of its ancestors
    bool VariableDeclared(const std::string &name);
    /// Returns a variable declaration from the current block or one of its ancestors if a
    /// variable with given name exists, else returns nullptr
    std::shared_ptr<AST::VarDecl> GetVarDecl(const std::string &name);

    /// Returns type of the variable with given name
    std::string GetVariableType(const std::string &name) {
        return GetVarDecl(name)->GetType();
    }

    std::unique_ptr<AST::VarDecl> ParseVarDecl();
    std::unique_ptr<AST::FnDecl> ParseFnDecl();

    std::unique_ptr<AST::Stmt> ParseStmt();
    std::shared_ptr<AST::Block> ParseBlock();

    std::unique_ptr<AST::Expr> ParseExpr();
    std::unique_ptr<AST::Expr> ParsePrimaryExpr();
    std::unique_ptr<AST::Expr> ParseBinExpr(i32 opPrec, std::unique_ptr<AST::Expr> LHS);
    std::unique_ptr<AST::Expr> ParseRefExpr();
    std::unique_ptr<AST::Expr> ParseNumberExpr();

  public:
    Parser(Lex::Lexer &lexer) : Lexer(lexer), CurToken(Lexer.LexToken()) {}

    std::vector<std::shared_ptr<AST::Decl>> Parse();
};
} // namespace Parse
} // namespace Language

#endif
