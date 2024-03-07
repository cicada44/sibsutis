/*
 * Reverse Polish Notation calculator 
 * 1 2 + 3 * = 9
 */

%{
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
int yylex();
void yyerror(char const *);
%}

/* Type for semantic values (default int) */
%define api.value.type {double}
%token NUM
%left '-' '+'
%left '*' '/'
%precedence NEG /* negation--unary minus */
%right '^' /* exponentiation */

%%

input:
  %empty
| input line
;

line:
  '\n'
| exp '\n'      { printf ("%.10g\n", $1); }
;

exp:
  NUM
| exp '+' exp         { $$ = $1 + $3;      }
| exp '-' exp         { $$ = $1 - $3;      }
| exp '*' exp         { $$ = $1 * $3;      }

| exp '/' exp
{
if ($3 != 0) { $$ = $1 / $3; }
else {
        fprintf (stderr, "%d.%d-%d.%d: division by zero\n",
                    @3.first_line, @3.first_column,
                    @3.last_line, @3.last_column);
        exit(-1);
    }
}

| '-' exp %prec NEG   { $$ = -$2;          }
| exp '^' exp         { $$ = pow ($1, $3); }  /* Exponentiation */
| '(' exp ')'         { $$ = $2;           }
;

%%

#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

int yylex()
{
    int c = getchar();
    while (c == ' ' || c == '\t') {
        c = getchar();
    }

    /* Process floating point numbers */
    if (c == '.' || isdigit(c)) {
        ungetc(c, stdin);
        if (scanf("%lf", &yylval) != 1)
            abort();
        return NUM;
    } else if (c == EOF) {
        return YYEOF;
    }
    /* Single char token */
    return c;
}

/* Called by yyparse on error */
void yyerror (char const *s)
{
    fprintf (stderr, "Error: %s\n", s);
}

int main()
{
    return yyparse();
}
