#include "cool-parse.h"
#include "cool-tree.h"
#include "utilities.h"
#include <cstdio>
#include <functional>
#include <iostream>
#include <unistd.h>
#include <unordered_map>
#include <unordered_set>

std::FILE *token_file = stdin;
extern Classes parse_results;
extern Program ast_root;

extern int curr_lineno;
const char *curr_filename = "<stdin>";
extern int parse_errors;

// Debug flags
extern int yy_flex_debug;
extern int cool_yydebug;
int lex_verbose = 0;

extern int cool_yyparse();

void dump_symtables(IdTable idtable, StrTable strtable, IntTable inttable) {
  ast_root->dump_with_types(std::cerr, 0);
  std::cerr << "# Identifiers:\n";
  idtable.print();
  std::cerr << "# Strings:\n";
  stringtable.print();
  std::cerr << "# Integers:\n";
  inttable.print();
}

int main(int argc, char **argv) {
  yy_flex_debug = 0;
  cool_yydebug = 0;
  lex_verbose = 0;
  for (int i = 1; i < argc; i++) {
    token_file = std::fopen(argv[i], "r");
    if (token_file == NULL) {
      std::cerr << "Error: can not open file " << argv[i] << std::endl;
      std::exit(1);
    }
    curr_lineno = 1;
    cool_yyparse();
    if (parse_errors != 0) {
      std::cerr << "Error: parse errors\n";
      std::exit(1);
    }
    dump_symtables(idtable, stringtable, inttable);
    std::fclose(token_file);
  }
  return 0;
}
