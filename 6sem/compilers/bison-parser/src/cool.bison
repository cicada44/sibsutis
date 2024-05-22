/* Parser definition for the Cool language */
%{
#include <iostream>
#include "cool-tree.h"
#include "stringtab.h"
#include "utilities.h"

extern char *curr_filename;

/*
 * Default locations represent a range in the source file, but this is not a requirement.
 * It could be a single point or just a line number, or even more complex structures.
 */
#define YYLTYPE int

/*
 * The function yyparse expects to find the textual location of a token just parsed in the global variable yylloc.
 * So yylex must store the proper data in that variable.
 */
#define cool_yylloc curr_lineno

/*
 * YYLLOC_DEFAULT macro is invoked each time a rule is matched, before the associated action is run.
 */
extern int node_lineno;
#define YYLLOC_DEFAULT(Current, Rhs, N)  { Current = Rhs[1]; node_lineno = Current; }
#define SET_NODELOC(Current)  { node_lineno = Current; }

/* Root of AST */
Program ast_root;

/* List of classes */
Classes parse_results;

/* Number of parsing errors */
int parse_errors = 0;

void yyerror(char *s);
extern int yylex();

%}

/*
 * The %union declaration specifies the entire collection of possible data types for semantic values.
 * The keyword %union is followed by braced code containing the same thing that goes inside a union in C.
 */
%union {
    Boolean boolean;
    Symbol symbol;
    Program program;
    Class_ class_;
    Classes classes;
    Feature feature;
    Features features;
    Formal formal;
    Formals formals;
    Case case_;
    Cases cases;
    Expression expression;
    Expressions expressions;
    char *error_msg;
}

/* Token kinds (terminals) */
%token CLASS 258 ELSE 259 FI 260 IF 261 IN 262
%token INHERITS 263 LET 264 LOOP 265 POOL 266 THEN 267 WHILE 268
%token CASE 269 ESAC 270 OF 271 DARROW 272 NEW 273 ISVOID 274
%token <symbol> STR_CONST 275 INT_CONST 276
%token <boolean> BOOL_CONST 277
%token <symbol> TYPEID 278 OBJECTID 279
%token ASSIGN 280 NOT 281 LE 282 ERROR 283

/* Types of non-terminals */
%type <program> program
%type <classes> class_list
%type <class_> class

%type <features> feature_list
%type <feature> feature

%type <formals> formal_list
%type <formal> formal

%type <cases> case_list
%type <case_> case

%type <expressions> expr_list_simicolon expr_list_comma
%type <expression> expr

%type <expression> let_expr
%type <expression> optional_assign
%type <expression> let_binding_list
%type <expression> let_binding

/* Precedence declarations */
%left IN
%right ASSIGN
%left NOT
%nonassoc LE '<' '='
%left '+' '-'
%left '*'
%left '/'
%left ISVOID
%left '~'
%left '@'
%left '.'

%%

/* Grammar rules */

program : class_list {  @$ = @1; ast_root = program($1); }
  /* @$ -- location of the whole grouping, @1 -- location of the first symbol */
;

class_list :
  class     /* single class */
  { $$ = single_Classes($1); parse_results = $$; }
| class_list class  /* several classes */
  { $$ = append_Classes($1, single_Classes($2)); parse_results = $$; }
| error ';' class
  { $$ = single_Classes($3); yyerrok; }
  /* macro yyerrok -- leave the error state before Bison finds the three good tokens */
;

/* Class inherits from the Object class */
class :
  CLASS TYPEID '{' feature_list '}' ';'
  { $$ = class_($2, idtable.add_string("Object"), $4, stringtable.add_string(curr_filename)); }
| CLASS TYPEID INHERITS TYPEID '{' feature_list '}' ';'
  { $$ = class_($2, $4, $6, stringtable.add_string(curr_filename)); }
;

/* Feature list (may be empty), but no empty features in list */
feature_list :
  /* empty */
  { $$ = nil_Features(); }
| feature_list feature /* multiple features */
  { $$ = append_Features($1, single_Features($2)); }
;

feature :
  OBJECTID ':' TYPEID optional_assign ';' /* attribute with initialize */
  { $$ = attr($1, $3, $4); }
| OBJECTID '(' formal_list ')' ':' TYPEID '{' expr '}' ';'
  { $$ = method($1, $3, $6, $8); }
| error ';' {}
;

formal_list :
  /* empty */
  { $$ = nil_Formals(); }
| formal /* single formal */
  { $$ = single_Formals($1); }
| formal_list ',' formal /* multiple formals */
  { $$ = append_Formals($1, single_Formals($3)); }
;

formal :
  OBJECTID ':' TYPEID
  { $$ = formal($1, $3); }
;

expr_list_comma :
  /* empty */
  { $$ = nil_Expressions(); }
| expr /* single expr */
  { $$ = single_Expressions($1); }
| expr_list_comma ',' expr
  { $$ = append_Expressions($1, single_Expressions($3)); }
;

expr_list_simicolon :
  expr ';' /* single expr */
  { $$ = single_Expressions($1); }
| expr_list_simicolon expr ';'
  { $$ = append_Expressions($1, single_Expressions($2)); }
| error ';' { yyerrok; }
;

expr :
  STR_CONST
  { $$ = string_const($1); }
| INT_CONST
  { $$ = int_const($1); }
| BOOL_CONST
  { $$ = bool_const($1); }
| OBJECTID
  { $$ = object($1); }
| OBJECTID ASSIGN expr
  { $$ = assign($1, $3); }

| expr '.' OBJECTID '(' expr_list_comma ')' /* dispatch */
  { $$ = dispatch($1, $3, $5); }
| OBJECTID '(' expr_list_comma ')'
  { $$ = dispatch(object(idtable.add_string("self")), $1, $3); }
| expr '@' TYPEID '.' OBJECTID '(' expr_list_comma ')'
  { $$ = static_dispatch($1, $3, $5, $7); }

| IF expr THEN expr ELSE expr FI
  { $$ = cond($2, $4, $6); }

| '{' expr_list_simicolon '}' /* blocks */
  { $$ = block($2); }

| let_expr
  { $$ = $1; }
| CASE expr OF case_list ESAC
  { $$ = typcase($2, $4); }

| NEW TYPEID
  { $$ = new_($2); }

| ISVOID expr
  { $$ = isvoid($2); }

| expr '+' expr
  { $$ = plus($1, $3); }
| expr '-' expr
  { $$ = sub($1, $3); }
| expr '*' expr
  { $$ = mul($1, $3); }
| expr '/' expr
  { $$ = divide($1, $3); }
| '~' expr
  { $$ = neg($2); }
| expr '<' expr
  { $$ = lt($1, $3); }
| expr '=' expr
  { $$ = eq($1, $3); }
| expr LE expr
  { $$ = leq($1, $3); }
| NOT expr
  { $$ = comp($2); }

| '(' expr ')'
  { $$ = $2; }

| WHILE expr LOOP expr POOL
  { $$ = loop($2, $4); }
;

case_list :
  /* empty */
  { $$ = nil_Cases(); }
| case_list case
  { $$ = append_Cases($1, single_Cases($2)); }
;

case :
  OBJECTID ':' TYPEID DARROW expr ';'
  { $$ = branch($1, $3, $5); }
;

let_expr :
  LET let_binding_list IN expr
  {
    auto bind = $2;
    bind->set_body($4);
    while (bind->parent) {
        bind = bind->parent;
    }
    $$ = bind;
  }
;

let_binding_list :
  let_binding
  { $$ = $1; }
| let_binding_list ',' let_binding
  { auto bind = $1; bind->set_body($3); $$ = $3; }
| error ',' let_binding { yyerrok; $$ = $3; }
;

let_binding :
  OBJECTID ':' TYPEID optional_assign
  { auto res = let($1, $3, $4, no_expr()); $$ = res; }
;

optional_assign :
  /* empty */
  { $$ = no_expr(); }
| ASSIGN expr
  { $$ = $2; }
;

%%

void yyerror(char *s) {
    std::cerr << "Error: \"" << curr_filename << "\", line " << curr_lineno << ": " \
         << s << " at or near ";
    print_cool_token(yychar);
    std::cerr << std::endl;
    parse_errors++;

    if (parse_errors > 50) {
        std::fprintf(stdout, "More than 50 parse errors\n");
        std::exit(1);
    }
}
