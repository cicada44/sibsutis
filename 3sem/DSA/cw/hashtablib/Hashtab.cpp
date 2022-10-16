#include "Hashtab.hpp"
#include "ext_funcs_hashtab.hpp"
#include <string>
#include <vector>

Hashtab::Hashtab(const long long size) : size_ht(size) {
  for (long long i = 0; i != size; i++)
    ht.push_back("");
}

const std::vector<std::string> &Hashtab::get_ht() { return ht; }

void Hashtab::add(const std::string &key, const std::string &value) {
  int hcode = hash_prime(key);
  ht[hcode] = value;
}