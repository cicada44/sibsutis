flex lexer.flex
gcc lex.yy.c -o lexer
./lexer < program.cl
