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

%}

white_space               [ \t\f\b\r]*
digit                     [0-9]
alpha                     [A-Za-z_]
alpha_num                 ({alpha}|{digit})

%x COMMENT
%x STRING

%option warn nodefault batch noyywrap c++
%option yylineno
%option yyclass="CoolLexer"

%%

--.*                      { }
"*)"                      { Error("Unmatched comment ending"); BEGIN(INITIAL); return ERROR; }
"(*"                      { BEGIN(COMMENT); comment_level = 0; }
<COMMENT>"(*"             { comment_level++; }
<COMMENT><<EOF>>          { Error("EOF in comment"); BEGIN(INITIAL); return ERROR; }
<COMMENT>\n               { lineno++; }
<COMMENT>.                { }
<COMMENT>"*)"             {
                            if (comment_level == 0) {
                                BEGIN(INITIAL);
                            }
                            comment_level--;
                          }

"\""                      { BEGIN(STRING); yymore(); }
<STRING>\n                { Error("Wrong newline in string"); BEGIN(INITIAL); lineno++; return ERROR; }
<STRING><<EOF>>           { Error("EOF in string"); BEGIN(INITIAL); return ERROR; }
<STRING>\0                { Error("Can't use \\0 in strings"); BEGIN(INITIAL); yymore(); return ERROR; }
<STRING>[^\\\"\n]*        { yymore(); }
<STRING>\\[^\n]           { yymore(); }
<STRING>\\\n              { lineno++; yymore(); }
<STRING>"\""              { BEGIN(INITIAL); EscapeStrLexeme(); return TOKEN_STRING; }

t(?i:rue)                 return TOKEN_TRUE;
f(?i:alse)                return TOKEN_FALSE;
(?i:class)                return TOKEN_CLASS;
(?i:else)                 return TOKEN_ELSE;
(?i:fi)                   return TOKEN_FI;
(?i:if)                   return TOKEN_IF;
(?i:in)                   return TOKEN_IN;
(?i:inherits)             return TOKEN_INHERITS;
(?i:let)                  return TOKEN_LET;
(?i:loop)                 return TOKEN_LOOP;
(?i:pool)                 return TOKEN_POOL;
(?i:then)                 return TOKEN_THEN;
(?i:while)                return TOKEN_WHILE;
(?i:case)                 return TOKEN_CASE;
(?i:esac)                 return TOKEN_ESAC;
(?i:new)                  return TOKEN_NEW;
(?i:isvoid)               return TOKEN_ISVOID;
(?i:of)                   return TOKEN_OF;
(?i:not)                  return TOKEN_NOT;

"<="                      return TOKEN_LEQ;
"<-"                      return TOKEN_ASSIGN;
"=>"                      return TOKEN_ARROW;
"<"                       return TOKEN_LESS;
"="                       return TOKEN_EQUAL;
"@"                       return TOKEN_AT;
"*"                       return TOKEN_MUL;
"/"                       return TOKEN_DIVIDE;
"+"                       return TOKEN_PLUS;
"-"                       return TOKEN_MINUS;
","                       return TOKEN_COMMA;
"."                       return TOKEN_DOT;
";"                       return TOKEN_SEMICOLON;
":"                       return TOKEN_COLON;
"~"                       return TOKEN_LOGICAL_NOT;
"("                       return TOKEN_OPEN_REGULAR;
")"                       return TOKEN_CLOSE_REGULAR;
"["                       return TOKEN_OPEN_SQUARE;
"]"                       return TOKEN_CLOSE_SQUARE;
"{"                       return TOKEN_OPEN_BLOCK;
"}"                       return TOKEN_CLOSE_BLOCK;

{digit}+                  return TOKEN_CONST_INT;

[a-z]{alpha_num}*         return TOKEN_IDENTIFIER_OBJECT;
[A-Z]{alpha_num}*         return TOKEN_IDENTIFIER_TYPE;
_{alpha_num}*             return TOKEN_IDENTIFIER_OTHER;

{white_space}             { }
\n                        lineno++;
.                         { BEGIN(INITIAL); Error("Unrecognized character"); return ERROR; }

%%

void CoolLexer::Error(const char* msg) const {
    std::cerr << "Lexer error (line " << lineno << "): " << msg << ": lexeme '" << YYText() << "'\n";
}

void CoolLexer::EscapeStrLexeme() const {
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
    *output = '\0'; // Null-terminate the output string
}