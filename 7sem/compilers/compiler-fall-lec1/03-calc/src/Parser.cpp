#include "Parser.h"

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

AST *Parser::parse() {
  AST *Res = parseCalc();
  expect(Token::eoi);
  return Res;
}

AST *Parser::parseCalc() {
  // calc : ("with" ident ("," ident)* ":")? expr ;
  Expr *E;
  llvm::SmallVector<llvm::StringRef, 8> Vars;
  if (Tok.is(Token::KW_with)) {
    // Parse list of variables: with a, b, ... c :
    advance();
    if (expect(Token::ident))
      goto _error;
    Vars.push_back(Tok.getText());
    advance();
    while (Tok.is(Token::comma)) {
      advance();
      if (expect(Token::ident))
        goto _error;
      Vars.push_back(Tok.getText());
      advance();
    }
    if (consume(Token::colon))
      goto _error;
  }
  // Parse expressions
  E = parseExpr();
  if (expect(Token::eoi))
    goto _error;
  if (Vars.empty())
    return E;
  else
    return new WithDecl(Vars, E);

_error:
  while (Tok.getKind() != Token::eoi)
    advance();
  return nullptr;
}

Expr *Parser::parseExpr() {
  // expr : term (( "+" | "-" ) term)* ;
  Expr *Left = parseTerm();
  while (Tok.isOneOf(Token::plus, Token::minus)) {
    BinaryOp::Operator Op = Tok.is(Token::plus)
                                ? BinaryOp::Plus
                                : BinaryOp::Minus;
    advance();
    Expr *Right = parseTerm();
    Left = new BinaryOp(Op, Left, Right);
  }
  return Left;
}

Expr *Parser::parseTerm() {
  // term : factor (( "*" | "/") factor)* ;
  Expr *Left = parseFactor();
  while (Tok.isOneOf(Token::star, Token::slash)) {
    BinaryOp::Operator Op =
        Tok.is(Token::star) ? BinaryOp::Mul : BinaryOp::Div;
    advance();
    Expr *Right = parseFactor();
    Left = new BinaryOp(Op, Left, Right);
  }
  return Left;
}

Expr *Parser::parseFactor() {
  // factor : ident | number | "(" expr ")" ;
  Expr *Res = nullptr;
  switch (Tok.getKind()) {
  case Token::number:
    Res = new Factor(Factor::Number, Tok.getText());
    advance(); break;
  case Token::ident:
    Res = new Factor(Factor::Ident, Tok.getText());
    advance(); break;
  case Token::l_paren:
    advance();
    Res = parseExpr();
    if (!consume(Token::r_paren)) break;
  default:
    if (!Res)
      error();
    while (!Tok.isOneOf(Token::r_paren, Token::star,
                        Token::plus, Token::minus,
                        Token::slash, Token::eoi))
      advance();
  }
  return Res;
}
