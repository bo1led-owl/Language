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
  TokenKind Kind;

 public:
  Token(const TokenKind kind) : Kind(kind) {}
  virtual ~Token() = default;

  void Print() const;
  inline TokenKind GetKind() const { return Kind; }

  inline virtual std::string GetNumberData() const {
    assert(Kind == TokenKind::Number && "The token is not a NumberToken");
    return 0;
  }

  inline virtual std::string GetIdentifierData() const {
    assert(Kind == TokenKind::Identifier && "The token is not an IdentifierToken");
    return "";
  }

  inline bool Is(TokenKind otherKind) const { return Kind == otherKind; }
  inline bool IsNot(TokenKind otherKind) const { return Kind != otherKind; }
};

/// Token class for numeric literals
class NumberToken : public Token {
  std::string Data;

 public:
  NumberToken(const std::string &data) : Token(TokenKind::Number), Data(data) {}

  inline std::string GetNumberData() const override { return Data; }
};

/// Token class for identifiers (string literals)
class IdentifierToken : public Token {
  std::string Data;

 public:
  IdentifierToken(std::string data) : Token(TokenKind::Identifier), Data(data) {}

  inline std::string GetIdentifierData() const override { return Data; }
};
} // namespace Lex
} // namespace Language

#endif
