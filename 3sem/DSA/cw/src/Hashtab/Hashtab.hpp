#ifndef __HASHTAB_H__
#define __HASHTAB_H__

#include <array>
#include <cmath>
#include <map>
#include <string>

#define SIZE_HT 1000000000

static const int PRIME_CONST = 31;

class Hashtab {
public:
  Hashtab() = delete;
  Hashtab(int64_t cap);
  unsigned int KRHash(const std::string &);
  unsigned int ELFHash(const std::string &);
  const std::array<std::pair<std::string, int>, SIZE_HT> &get_ht();
  void insert(const std::string &, const int &, int &);
  void add_kidding(const std::string &key, const int &value, int &col);
  bool delete_node(const std::string &key);
  int lookup(const std::string &);
  std::pair<std::string, int> &lookup_pair(const std::string &);
  int64_t size();
  int max();
  int min();

private:
  int64_t _size;
  int64_t capacity;
  std::array<std::pair<std::string, int>, SIZE_HT> ht;
};

#endif // __HASHTAB_H__