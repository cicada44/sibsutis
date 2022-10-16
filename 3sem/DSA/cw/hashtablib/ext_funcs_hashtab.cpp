#include "ext_funcs_hashtab.hpp"
#include "Hashtab.hpp"
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#define SIZE_HT 100

using std::cin;
using std::cout;

const int PRIME_CONST = 31;

void print_hashtab(Hashtab &ht) {
  int coll = 0;
  const std::vector<std::string> &hashtab = ht.get_ht();
  for (int x = 0; x < SIZE_HT; x++) {
    if (!(hashtab[x].empty()))
      cout << x << " - " << hashtab[x] << "\n";
    else
      coll++;
  }
  cout << "collisions - " << coll << "\n";
}

int hash_prime(const std::string &key) {
  int hashCode = 0;
  for (size_t i = 0; i < key.length(); i++) {
    hashCode += key[i] * pow(PRIME_CONST, i);
  }
  return abs(hashCode % SIZE_HT);
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