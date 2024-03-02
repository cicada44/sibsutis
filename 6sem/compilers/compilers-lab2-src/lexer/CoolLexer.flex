%{

#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>

#include "Parser.h"
#include "CoolLexer.h"

#undef YY_DECL
#define YY_DECL int CoolLexer::yylex()

#define ERROR -1

int comment_depth = 0;
int curline = 1;

%}

white_space       [ \n\t\f\r\v]*
digit             [0-9]
alpha             [A-Za-z_]
alpha_num         ({alpha}|{digit})
hex_digit         [0-9a-fA-F]
hex_integer       ${hex_digit}{hex_digit}*
exponent          e[+-]?{digit}+
real              ({i}\.{i}?|{i}?\.{i}){exponent}?
string            \'([^'\n]|\'\')*\'
bad_string        \'([^'\n]|\'\')*

%start COMMENT
%start STRING

%option warn nodefault batch noyywrap c++
%option yylineno
%option yyclass="CoolLexer"

%%

<INITIAL>--.*\n     { ++lineno; }
<INITIAL>"*)"       { Error("Wrong comment close-bracket"); BEGIN(INITIAL); return ERROR; }
<INITIAL>"(*"       { BEGIN(COMMENT); comment_depth = 0; }
<COMMENT>"(*"       { ++comment_depth; }
<COMMENT><<EOF>>    { Error("Unterminated comment"); BEGIN(INITIAL); return ERROR; }
<COMMENT>\n         { ++lineno; }
<COMMENT>[^\n*(]*   { }
<COMMENT>[*()]      { }
<COMMENT>"*)"       {
                      if (comment_depth == 0) BEGIN(INITIAL);
                      --comment_depth;
                    }

<INITIAL>"\""       { BEGIN(STRING); yymore(); }
<STRING>\n          { Error("Unexpected nl in string"); BEGIN(INITIAL); curline++; return ERROR; }
<STRING><<EOF>>     { Error("EOF in string"); BEGIN(INITIAL); return ERROR; }
<STRING>"\\0"       { BEGIN(INITIAL); Error("Unexpected null-term in string"); yymore(); return ERROR; }
<STRING>[^\\\"\n]*  { yymore(); }
<STRING>\\[^\n]     { yymore(); }
<STRING>\\\n        { curline++; yymore(); }
<STRING>"\""        { BEGIN(INITIAL); Escape(); return TOKEN_STRING; }

(?i:class)           return TOKEN_CLASS;
t(?i:rue)            return TOKEN_TRUE;
f(?i:alse)           return TOKEN_FALSE;
(?i:else)            return TOKEN_ELSE;
(?i:fi)              return TOKEN_FI;
(?i:if)              return TOKEN_IF;
(?i:in)              return TOKEN_IN;
(?i:inherits)        return TOKEN_INHERITS;
(?i:isvoid)          return TOKEN_ISVOID;
(?i:let)             return TOKEN_LET;
(?i:loop)            return TOKEN_LOOP;
(?i:pool)            return TOKEN_POOL;
(?i:then)            return TOKEN_THEN;
(?i:while)           return TOKEN_WHILE;
(?i:case)            return TOKEN_CASE;
(?i:esac)            return TOKEN_ESAC;
(?i:new)             return TOKEN_NEW;
(?i:of)              return TOKEN_OF;
(?i:not)             return TOKEN_NOT;

{digit}+             return TOKEN_INTCONST;
[a-z]{alpha_num}*    return TOKEN_IDENTIFIER_OBJECT;
[A-Z]{alpha_num}*    return TOKEN_IDENTIFIER_TYPE;
_{alpha_num}*        return TOKEN_IDENTIFIER_OTHER;

"."                  return TOKEN_DOT;
"@"                  return TOKEN_AT;
"~"                  return TOKEN_TILDA;
"*"                  return TOKEN_MUL;
"/"                  return TOKEN_DIV;
"+"                  return TOKEN_PLUS;
"-"                  return TOKEN_MINUS;
"<="                 return TOKEN_LE;
"=>"                 return TOKEN_ME;
"<"                  return TOKEN_LESS;
"="                  return TOKEN_EQ;
"<-"                 return TOKEN_ARROW;

"["                  return TOKEN_SQUARE_PARENTESES_LEFT;
"]"                  return TOKEN_SQUARE_PARENTESES_RIGHT;
"{"                  return TOKEN_CURVE_PARENTESES_LEFT;
"}"                  return TOKEN_CURVE_PARENTESES_RIGHT;
"("                  return TOKEN_ROUND_PARENTESES_LEFT;
")"                  return TOKEN_ROUND_PARENTESES_RIGHT;

";"                  return TOKEN_SEMICOLON;
":"                  return TOKEN_COLON;

\n                   lineno++;
{white_space}        { }
.                    { Error("Unrecognized charachter"); }

%%

void CoolLexer::Error(const char* msg) const
{
    std::cerr << "Lexer error (line " << lineno + 1 << "): " << msg << ": lexeme '" << YYText() << "'\n";
    std::exit(YY_EXIT_FAILURE);
}

void CoolLexer::Escape() const {
    const char *input = yytext;
    char *output = yytext;
    input++; // Skip opening '\"'
    while (*(input + 1) /* Skip closing '\"' */ ) {
        if (*input == '\\') {
            input++; // Skip '\\'
            switch (*input) {
                case 'n': *output++ = '\n'; break;
                case 't': *output++ = '\t'; break;
                case 'f': *output++ = '\f'; break;
                case 'b': *output++ = '\b'; break;
                default: *output++ = *input;
            }
        } else {
            *output++ = *input;
        }
        input++;
    }
    *output = '\0';
}
