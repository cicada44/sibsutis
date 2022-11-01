#include "ext_funcs_hashtab.hpp"
#include "Hashtab.hpp"
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#define SIZE_HT 20001

using std::cin;
using std::cout;

void print_hashtab(Hashtab &ht) {
  int n = 0;
  const std::vector<int> &hashtab = ht.get_ht();
  for (int x = 0; x < SIZE_HT; x++) {
    cout << x << " - " << hashtab[x] << "\n";
    if (hashtab[x] != -1)
      ++n;
  }
  cout << "N - " << n << "\n";
}

int read_dict(char *&name_of_file, std::vector<std::string> &dict) {
  std::ifstream file(name_of_file);
  if (!file.is_open())
    return 1;

  std::string tmp;
  while (file >> tmp)
    dict.push_back(tmp);

  return 0;
}