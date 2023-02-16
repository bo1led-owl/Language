#ifndef TOKEN_HH
#define TOKEN_HH

#include <cassert>
#include <memory>
#include <string>

#include "Lex/TokenKind.hh"
#include "Types.hh"

class Token {
protected:
  TokenKind Kind;
  void *Data;

public:
  Token() : Kind(TokenKind::Unknown), Data(nullptr) {}
  Token(TokenKind K) : Kind(K) {}

  Token(const Token &) = delete;
  virtual ~Token() = default;

  TokenKind GetKind() const { return Kind; }

  virtual i32 GetNumberData() const {
    assert(Kind == TokenKind::Number);
    return 0;
  }

  virtual std::string_view GetIdentifierData() const {
    assert(Kind == TokenKind::Identifier);
    return "";
  }

  void SetData(void *D) { Data = D; }
  bool HasData() const { return Data != nullptr; }

  bool Is(TokenKind K) const { return Kind == K; }
  bool IsNot(TokenKind K) const { return Kind != K; }
};

class NumberToken : public Token {
  i32 Data;

public:
  NumberToken(const NumberToken &) = delete;

  NumberToken() : Token(TokenKind::Number) {}
  NumberToken(i32 D) : Token(TokenKind::Number), Data(D) {}

  i32 GetNumberData() const override { return Data; }
};

class IdentifierToken : public Token {
  std::string Data;

public:
  IdentifierToken(const IdentifierToken &) = delete;

  IdentifierToken() : Token(TokenKind::Identifier) {}
  IdentifierToken(std::string D) : Token(TokenKind::Identifier), Data(D) {}

  std::string_view GetIdentifierData() const override {
    return std::string_view{Data};
  }
};

#endif