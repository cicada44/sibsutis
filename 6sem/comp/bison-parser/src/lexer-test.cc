#include <iostream>
#include <fstream>
#include <cstdlib>

#include "cool-parse.h"
#include "stringtab.h"
#include "utilities.h"

std::FILE *token_file = stdin;
int curr_lineno = 0;
const char *curr_filename = "<stdin>";
YYSTYPE cool_yylval;
int cool_yylex();

int main(int argc, char** argv) {
  int curr_lineno;
  for (int token = cool_yylex(); token; token = cool_yylex()) {
    print_cool_token(token);
  }
  std::cout << "# Identifiers:\n";
  idtable.print();
  std::cout << "# Strings:\n";
  stringtable.print();
  std::cout << "# Integers:\n";
  inttable.print();
  return 0;
}
