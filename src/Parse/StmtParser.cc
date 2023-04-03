#include "AST/Decl.hh"
#include "AST/Stmt.hh"
#include "Lex/TokenKind.hh"
#include "Parse/Exception.hh"
#include "Parse/Parser.hh"
#include <memory>

namespace Language {
namespace Parse {
std::shared_ptr<AST::Block> Parser::ParseBlock() {
    // no "{"
    THROW_IF_TOKEN_IS_NOT(Lex::TokenKind::LCurBracket,
                          "missing block opening curly bracket")

    EAT_WHILE_TOKEN_IS(Lex::TokenKind::Newline)
    // eat "{"
    Advance();

    // enter new block
    CurBlock = std::make_unique<AST::Block>(CurBlock);

    // block body parsing
    while (CurToken->IsNot(Lex::TokenKind::RCurBracket)) {
        EAT_WHILE_TOKEN_IS(Lex::TokenKind::Newline)
        // unexpected end of input
        THROW_IF_TOKEN_IS(Lex::TokenKind::EndOfInput, "expected closed statement block")

        switch (CurToken->GetKind()) {
        case Lex::TokenKind::RCurBracket:
            // end of the block
            break;
        case Lex::TokenKind::Comment:
            while (CurToken->IsNot(Lex::TokenKind::Newline)) {
                THROW_IF_TOKEN_IS(Lex::TokenKind::EndOfInput,
                                  "unexpected end of input, block is not closed")
                Advance();
            }
            break;
        case Lex::TokenKind::Let: {
            // variable declaration
            std::shared_ptr<AST::VarDecl> decl = ParseVarDecl();
            CurBlock->AddVariable(decl->GetName(), decl);
            CurBlock->AddToBody(std::make_unique<AST::DeclStmt>(std::move(decl)));
            break;
        } // case Lex::TokenKind::Let
        default:
            // ordinary statement
            CurBlock->AddToBody(ParseStmt());
        }
    }

    EAT_WHILE_TOKEN_IS(Lex::TokenKind::Newline)
    // eat "}"
    Advance();

    auto result{std::move(CurBlock)};
    // exit to the parent block
    CurBlock = result->GetParent();
    return result;
}

std::unique_ptr<AST::Stmt> Parser::ParseStmt() {
    EAT_WHILE_TOKEN_IS(Lex::TokenKind::Newline)
    // no statement
    THROW_IF_TOKEN_IS(Lex::TokenKind::EndOfInput,
                      "expected statement, found end of input")

    switch (CurToken->GetKind()) {
    case Lex::TokenKind::Let:
        return std::make_unique<AST::DeclStmt>(ParseVarDecl());

    case Lex::TokenKind::LCurBracket:
        return std::make_unique<AST::BlockStmt>(ParseBlock());

    case Lex::TokenKind::Return: {
        static const ParseException returnTypeException{
            "function return type differs from the type of the "
            "expression in return statement"};
        // eat "return"
        Advance();
        CurFn->AddReturnStmt();
        if (CurToken->Is(Lex::TokenKind::Newline) ||
            CurToken->Is(Lex::TokenKind::RCurBracket)) {
            if (CurFn->GetType() == "") {
                return std::make_unique<AST::ReturnStmt>(nullptr);
            } else {
                throw returnTypeException;
            }
        }
        auto expr{ParseExpr()};
        if (expr->GetType() == CurFn->GetType()) {
            return std::make_unique<AST::ReturnStmt>(std::move(expr));
        } else {
            throw returnTypeException;
        }
    } // case Lex::TokenKind::Return

    default:
        return ParseExpr();
    }
}
} // namespace Parse
} // namespace Language
