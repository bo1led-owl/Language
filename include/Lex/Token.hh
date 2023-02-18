#ifndef TOKEN_HH
#define TOKEN_HH

#include <cassert>
#include <string>

#include "Lex/TokenKind.hh"

#include "Types.hh"

namespace Language {
class Token {
 protected:
  TokenKind Kind;

 public:
  Token() : Kind(TokenKind::Unknown) {}
  Token(TokenKind K) : Kind(K) {}

  virtual ~Token() = default;

  TokenKind GetKind() const { return Kind; }

  virtual i32 GetNumberData() const {
    assert(Kind == TokenKind::Number && "The token is not a NumberToken");
    return 0;
  }

  virtual std::string_view GetIdentifierData() const {
    assert(Kind == TokenKind::Identifier && "The token is not an IdentifierToken");
    return "";
  }

  bool Is(TokenKind K) const { return Kind == K; }
  bool IsNot(TokenKind K) const { return Kind != K; }
};

class NumberToken : public Token {
  i32 Data;

 public:
  NumberToken() : Token(TokenKind::Number) {}
  NumberToken(i32 D) : Token(TokenKind::Number), Data(D) {}

  i32 GetNumberData() const override { return Data; }
};

class IdentifierToken : public Token {
  std::string Data;

 public:
  IdentifierToken() : Token(TokenKind::Identifier) {}
  IdentifierToken(std::string D) : Token(TokenKind::Identifier), Data(D) {}

  std::string_view GetIdentifierData() const override { return std::string_view{Data}; }
};
} // namespace Language

#endif