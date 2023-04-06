#include <memory>
#include <string>

#include "Lex/Lexer.hh"
#include "Lex/Token.hh"
#include "Lex/TokenKind.hh"
#include "Types.hh"

// Macro for matching single characters
#define REGISTER_CHAR(Char, Kind)                                                        \
    if (CurChar == Char) {                                                               \
        Advance();                                                                       \
        return std::make_unique<Token>(Kind);                                            \
    }

// Macro for matching strings
#define REGISTER_STRING(String, Kind)                                                    \
    if (identifierString == String) {                                                    \
        return std::make_unique<Token>(Kind);                                            \
    }

#define REGISTER_CHAR_SEQ(Char1, Char2, SeqKind, CharKind)                               \
    if (CurChar == Char1) {                                                              \
        if (Advance() == Char2) {                                                        \
            Advance();                                                                   \
            return std::make_unique<Token>(SeqKind);                                     \
        } else {                                                                         \
            return std::make_unique<Token>(CharKind);                                    \
        }                                                                                \
    }

namespace Language {
namespace Lex {
char Lexer::Advance() {
    if (CurChar == '\n') {
        ++CurLine;
    }
    return CurChar = Input.get();
}

std::unique_ptr<Token> Lexer::LexToken() {
    // skip spaces
    while (CurChar == ' ' || CurChar == '\t') {
        Advance();
    }

    REGISTER_CHAR(EOF, TokenKind::EndOfInput)
    REGISTER_CHAR('\0', TokenKind::EndOfInput)

    REGISTER_CHAR('\n', TokenKind::Newline)

    REGISTER_CHAR_SEQ('-', '>', Lex::TokenKind::RightArrow, Lex::TokenKind::Minus)
    REGISTER_CHAR_SEQ('<', '-', Lex::TokenKind::LeftArrow, Lex::TokenKind::LessThan)
    REGISTER_CHAR_SEQ('/', '/', Lex::TokenKind::Comment, Lex::TokenKind::Slash)

    REGISTER_CHAR('(', TokenKind::LParen)
    REGISTER_CHAR(')', TokenKind::RParen)
    REGISTER_CHAR('{', TokenKind::LCurBracket)
    REGISTER_CHAR('}', TokenKind::RCurBracket)

    REGISTER_CHAR(',', TokenKind::Comma)
    REGISTER_CHAR('.', TokenKind::Fullstop)
    REGISTER_CHAR(':', TokenKind::Colon)
    REGISTER_CHAR('+', TokenKind::Plus)
    REGISTER_CHAR('*', TokenKind::Asterisk)
    REGISTER_CHAR('=', TokenKind::Equals)
    REGISTER_CHAR('>', TokenKind::GreaterThan)

    // lex identifiers and keywords
    if (std::isalpha(CurChar) || CurChar == '_') {
        std::string identifierString{CurChar};
        while (std::isalnum(Advance()) || CurChar == '_') {
            identifierString += CurChar;
        }

        REGISTER_STRING("fn", TokenKind::Fn)
        REGISTER_STRING("let", TokenKind::Let)
        REGISTER_STRING("mut", TokenKind::Mut)
        REGISTER_STRING("return", TokenKind::Return)

        return std::make_unique<IdentifierToken>(identifierString);
    }

    // lex numbers
    if (std::isdigit(CurChar)) {
        std::string number;

        do {
            number += CurChar;
        } while (std::isdigit(Advance()));

        return std::make_unique<NumberToken>(number);
    }

    return std::make_unique<Token>(TokenKind::Unknown);
}
} // namespace Lex
} // namespace Language
