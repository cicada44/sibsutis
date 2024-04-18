#include "cool-parse.h"
#include "cool-tree.h"
#include "utilities.h"
#include <cstdio>
#include <iostream>
#include <vector>
#include <unistd.h>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

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

using CondMatrix = std::unordered_map<std::string, std::unordered_map<std::string, bool>>;

bool findCycle(CondMatrix& m) {
    std::unordered_map<std::string, bool> visited;
    for (auto& [name, N] : m) visited[name] = false;

    std::function<bool(std::string, std::string)> dfs = [&](std::string vertex, std::string parent) -> bool {
        visited[vertex] = true;
        for (auto& [name, condlist] : m) {
            if (condlist[vertex] && name != parent) {
                if (visited[name] || dfs(name, vertex)) return true;
            }
        }
        visited[vertex] = false;
        return false;
    };

    for (auto& [name, condlist] : m) {
        if (!visited[name]) {
            if (dfs(name, "")) return true;
        }
    }

    return false;
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

    /*
    ast_root->dump_with_types(std::cerr, 0);
    std::cerr << "# Identifiers:\n";
    idtable.print();
    std::cerr << "# Strings:\n";
    stringtable.print();
    std::cerr << "# Integers:\n";
    inttable.print();
     */

    GetClassInh classInh;
    std::vector<std::string> classes;
    for (int i = parse_results->first(); parse_results->more(i); i = parse_results->next(i)) {
        parse_results->nth(i)->accept(classInh);
        classes.push_back(classInh.name);
    }

    std::cout << "----- CLASSES -----\n";
    for (const auto& c : classes) std::cout << c << '\n';

    CondMatrix classHierarchy;
    for (const auto &c : classes) for (const auto &j : classes) classHierarchy[c][j] = false;
    for (int i = parse_results->first(); parse_results->more(i); i = parse_results->next(i)) {
        parse_results->nth(i)->accept(classInh);
        if (std::string(classInh.parent).size() != 0 && std::string(classInh.parent) != "Object")
            classHierarchy.at(classInh.name)[classInh.parent] = true;
    }

    std::cout << "\n----- COND -----\n ";
    for (const auto& [name, _] : classHierarchy) std::cout << ' ' << name;
    std::cout << '\n';
    for (const auto& [name, conductivity] : classHierarchy) {
        std::cout << name << ' ';
        for (const auto& [c, val] : conductivity) {
            std::cout << val << ' ';
        }
        std::cout << '\n';
    }

    std::cout << "\n----- INHERITANCE CYCLE -----\n";
    std::cout << findCycle(classHierarchy) << '\n';

    std::fclose(token_file);
  }
}
