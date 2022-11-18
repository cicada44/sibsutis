#include "ext_funcs.hpp"
#include "../Hashtab/Hashtab.hpp"
#include <algorithm>
#include <array>
#include <cmath>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <string>
#include <vector>

#define SIZE_HT 500000

#define RESET "\033[0m"
#define BLACK "\033[30m"   /* Black */
#define RED "\033[31m"     /* Red */
#define GREEN "\033[32m"   /* Green */
#define YELLOW "\033[33m"  /* Yellow */
#define BLUE "\033[34m"    /* Blue */
#define MAGENTA "\033[35m" /* Magenta */
#define CYAN "\033[36m"    /* Cyan */
#define WHITE "\033[37m"   /* White */

using std::array;
using std::cin;
using std::cout;
using std::ifstream;
using std::istream_iterator;
using std::pair;
using std::string;
using std::vector;

void print_hashtab(Hashtab &ht) {
  const array<pair<string, int>, SIZE_HT> &hashtab = ht.get_ht();
  for (long unsigned x = 0; x < SIZE_HT; x++) {
    cout << MAGENTA << x << GREEN << " ---> ";
    if (hashtab[x].first.empty() && hashtab[x].second == -1)
      ;
    // cout << RED << "EMPTY" << '\n' << RESET;
    else
      cout << YELLOW << " key - " << hashtab[x].first << GREEN << " | " << CYAN
           << "value - " << hashtab[x].second << '\n'
           << RESET;
  }
}

int read_dict(char *&name_of_file, vector<string> &dict) {
  ifstream file(name_of_file);
  if (!file.is_open())
    return 1;

  istream_iterator<string> is_iter(file), eof;

  std::copy(is_iter, eof, std::back_inserter(dict));

  return 0;
}