#include "Hashtab.hpp"
#include "../Ext_funcs/ext_funcs.hpp"
#include <algorithm>
#include <array>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using std::array;
using std::pair;
using std::string;

Hashtab::Hashtab(int64_t cap) : capacity(cap) {
  for (long long i = 0; i != SIZE_HT; i++)
    (*ht)[i] = {"", -1};
  _size = 0;
}

const array<pair<string, int>, SIZE_HT> &Hashtab::get_ht() { return (*ht); }

unsigned int Hashtab::AddHash(char *s) {
  unsigned int h = 0;
  unsigned int cnter_s = 0;
  while (*s) {
    h += (unsigned int)*s++;
    ++cnter_s;
  }
  return h % SIZE_HT;
}

unsigned int Hashtab::Jen(const string &s) {
  unsigned int hash, i;
  for (hash = i = 0; i < s.size(); ++i) {
    hash += s[i];
    hash += (hash << 10);
    hash ^= (hash >> 6);
  }
  hash += (hash << 3);
  hash ^= (hash >> 11);
  hash += (hash << 15);
  return hash % SIZE_HT;
}

unsigned int Hashtab::DJB2(const string &s) {
  unsigned long hash = 5381;
  for (auto c : s) {
    hash = (hash << 5) + hash + c; /* hash * 33 + c */
  }
  return hash % SIZE_HT;
}

unsigned int Hashtab::FNVHash(const string &str) {
  const unsigned int fnv_prime = 0x811C9DC5;
  unsigned int hash = 0;
  unsigned int i = 0;
  unsigned int len = str.length();

  for (i = 0; i < len; i++) {
    hash *= fnv_prime;
    hash ^= (str[i]);
  }

  return hash % SIZE_HT;
}

unsigned int Hashtab::KRHash(const string &s) {
  unsigned int h = 0, hash_mul = 31;
  for (auto x = s.begin(); x != s.end(); x++)
    h = h * hash_mul + (unsigned int)*x;
  return h % SIZE_HT;
}

unsigned int Hashtab::ELFHash(const string &s) {
  unsigned int h = 0, g;
  for (auto c = s.begin(); c != s.end(); c++) {
    h = (h << 4) + (unsigned int)*c;
    g = h & 0xF0000000L;
    if (g)
      h ^= g >> 24;
    h &= ~g;
  }
  return h % SIZE_HT;
}

void Hashtab::insert(const string &key, const int &value) {
  int hcode = DJB2(key);
  int probe = FNVHash(key);
  for (long unsigned i = 1; i < SIZE_HT; i++) {
    if ((*ht)[hcode].second != -1) {
      if (key == (*ht)[hcode].first)
        break;
      hcode = (hcode + i * probe) % SIZE_HT;
    } else {
      (*ht)[hcode] = {key, value};
      ++_size;
      break;
    }
  }
}

void Hashtab::insert(const string &key, const int &value, int &col, int opt) {
  int flag = 0;
  int hcode;
  int probe;
  if (opt == 0) {
    hcode = ELFHash(key);
    probe = KRHash(key);
  } else if (opt == 1) {
    hcode = DJB2(key);
    probe = FNVHash(key);
  } else if (opt == 2) {
    char *c = new char[20];
    std::copy(key.begin(), key.end(), c);
    hcode = AddHash(c);
    probe = Jen(key);
  }
  for (long unsigned i = 1; i < SIZE_HT; i++) {
    if ((*ht)[hcode].second != -1) {
      hcode = (hcode + i * probe) % SIZE_HT;
      if (!flag) {
        col++;
      }
      flag = 1;
    } else {
      (*ht)[hcode] = {key, value};
      ++_size;
      break;
    }
  }
}

int Hashtab::lookup(const string &key) {
  int hcode = DJB2(key);
  int probe = FNVHash(key);
  for (long unsigned i = 1; i < SIZE_HT; i++) {
    if ((*ht)[hcode].second != -1 && (*ht)[hcode].first == key)
      return (*ht)[hcode].second;
    hcode = (hcode + i * probe) % SIZE_HT;
  }
  return (*ht)[hcode].second;
}

pair<string, int> &Hashtab::lookup_pair(const string &key) {
  int hcode = DJB2(key);
  int probe = FNVHash(key);
  for (long unsigned i = 1; i < SIZE_HT; i++) {
    if ((*ht)[hcode].second != -1 && (*ht)[hcode].first == key)
      return (*ht)[hcode];
    hcode = (hcode + i * probe) % SIZE_HT;
  }
  return (*ht)[hcode];
}

bool Hashtab::delete_node(const std::string &key) {
  int hcode = DJB2(key);
  int probe = FNVHash(key);
  for (long unsigned i = 1; i < SIZE_HT; i++) {
    if ((*ht)[hcode].second != -1 && (*ht)[hcode].first == key) {
      (*ht)[hcode].first = "";
      (*ht)[hcode].second = -1;
      --_size;
      return 1;
    }
    hcode = (hcode + i * probe) % SIZE_HT;
  }
  return 0;
}

int Hashtab::max() {
  pair<string, int> pair_max;
  for (auto x = (*ht).cbegin(); x != (*ht).cend(); ++x)
    if (x->first > pair_max.first)
      pair_max = *x;
  return pair_max.second;
}

int Hashtab::min() {
  pair<string, int> pair_min;
  for (auto x = (*ht).cbegin(); x != (*ht).cend(); ++x)
    if (x->first < pair_min.first)
      pair_min = *x;
  return pair_min.second;
}

int64_t Hashtab::size() { return _size; }

void Hashtab::set_null() {
  for (auto &c : *ht) {
    c.first = "";
    c.second = -1;
  }
}

void Hashtab::delete_ht() { delete ht; }
