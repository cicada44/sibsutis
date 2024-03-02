%{
%}

%option noyywrap

%%

[+-]?([1-9]([0-9]+)*|0) { printf("Integer: %s\n", yytext); }
[ \n\t] { /* eat up white char */ }
. {}

%%

int main()
{
    yylex();
}
