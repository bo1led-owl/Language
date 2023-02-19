#ifndef TOKEN_HH
#define TOKEN_HH

#include <cassert>
#include <string>

#include "Lex/TokenKind.hh"
#include "Types.hh"

namespace Language {
namespace Lex {
/// Base token class
class Token {
 protected:
  TokenKind Kind;

 public:
  Token(const TokenKind kind) : Kind(kind) {}

  virtual ~Token() = default;

  TokenKind GetKind() const { return Kind; }

  virtual i32 GetNumberData() const {
    assert(Kind == TokenKind::Number && "The token is not a NumberToken");
    return 0;
  }

  virtual std::string GetIdentifierData() const {
    assert(Kind == TokenKind::Identifier && "The token is not an IdentifierToken");
    return "";
  }

  bool Is(TokenKind otherKind) const { return Kind == otherKind; }
  bool IsNot(TokenKind otherKind) const { return Kind != otherKind; }
};

/// Token class for numeric literals
class NumberToken : public Token {
  i32 Data;

 public:
  NumberToken(const i32 data) : Token(TokenKind::Number), Data(data) {}

  i32 GetNumberData() const override { return Data; }
};

/// Token class for identifiers (string literals)
class IdentifierToken : public Token {
  std::string Data;

 public:
  IdentifierToken() : Token(TokenKind::Identifier) {}
  IdentifierToken(const std::string &data) : Token(TokenKind::Identifier), Data(data) {}

  std::string GetIdentifierData() const override { return Data; }
};
} // namespace Lex
} // namespace Language

#endif