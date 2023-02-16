#ifndef TOKENKIND_HH
#define TOKENKIND_HH

enum TokenKind {
  EndOfFile,  // 0
  Unknown,    // 1

  // keywords
  Fn,         // 2

  Identifier, // 3

  // literals
  Number,     // 4
};

#endif