#ifndef LEXER_H
#define LEXER_H

#include "llvm/ADT/StringRef.h"
// pointer to a C string and its length
#include "llvm/Support/MemoryBuffer.h"
// Block of memory, filled with the content of a file.
// On request, a trailing zero character ('\x00') is added to the end of the buffer.

//
// Expression: with a, b: a * (4 + b)
//
// Expressions grammar (extended Backus-Naur form -- EBNF):
// calc : ("with" ident ("," ident)* ":")? expr ;
// expr : term (( "+" | "-" ) term)* ;
// term : factor (( "*" | "/") factor)* ;
// factor : ident | number | "(" expr ")" ;
// ident : ([a-zAZ])+ ;
// number : ([0-9])+ ;
//

class Lexer;

class Token {
  friend class Lexer;

public:
  enum TokenKind: unsigned short {
    eoi,
    unknown,
    ident,
    number,
    comma,
    colon,
    plus,
    minus,
    star,
    slash,
    l_paren,
    r_paren,
    KW_with
  };

private:
  TokenKind Kind;
  llvm::StringRef Text;

public:
  TokenKind getKind() const { return Kind; }
  llvm::StringRef getText() const {
    return Text;
  }

  bool is(TokenKind K) const { return Kind == K; }
  bool isOneOf(TokenKind K1, TokenKind K2) const {
    return is(K1) || is(K2);
  }

  // isOneOf(): variadic template, allowing a variable number of arguments:
  template <typename... Ts>
  bool isOneOf(TokenKind K1, TokenKind K2, Ts... Ks) const {
    return is(K1) || isOneOf(K2, Ks...);
  }
};

class Lexer {
  const char *BufferStart;
  const char *BufferPtr;

public:
  Lexer(const llvm::StringRef &Buffer) {
    BufferStart = Buffer.begin();
    BufferPtr = BufferStart;
  }

  void next(Token &token);
  // returns next token

private:
  void formToken(Token &Result, const char *TokEnd,
                 Token::TokenKind Kind);
};
#endif
