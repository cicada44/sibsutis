#pragma once

#include <iostream>
#include <fstream>

#undef yyFlexLexer
#include <FlexLexer.h>

class CoolLexer : public yyFlexLexer {
private:
    std::ostream& out;
    void Error(const char* msg) const;
    void EscapeStrLexeme() const;
    int lineno = 1;
    int comment_level = 0;

public:
    CoolLexer(std::istream& arg_yyin, std::ostream& arg_yyout) :
        yyFlexLexer{arg_yyin, arg_yyout}, out{arg_yyout} {}
    virtual int yylex();
};
