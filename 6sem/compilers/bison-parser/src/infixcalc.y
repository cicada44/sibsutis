%{
  #include <math.h>
  #include <stdio.h>
  int yylex (void);
  void yyerror (char const *);
%}

/* Bison declarations */
%define api.value.type {double}
%token NUM
%left '-' '+'
%left '*' '/'
%precedence NEG   /* Negation--unary minus */
%right '^'        /* Exponentiation */

%%
input:
  %empty
| input line
;

line:
  '\n'
| exp '\n'  { printf ("%.10g\n", $1); }
;

exp:
  NUM
| exp '+' exp        { $$ = $1 + $3;      }
| exp '-' exp        { $$ = $1 - $3;      }
| exp '*' exp        { $$ = $1 * $3;      }
| exp '/' exp        { $$ = $1 / $3;      }
| '-' exp  %prec NEG { $$ = -$2;          }
| exp '^' exp        { $$ = pow ($1, $3); }
| '(' exp ')'        { $$ = $2;           }
;
%%

#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

int yylex() {
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
void yyerror (char const *s) {
    fprintf (stderr, "Error: %s\n", s);
}

int main() {
    return yyparse();
}
