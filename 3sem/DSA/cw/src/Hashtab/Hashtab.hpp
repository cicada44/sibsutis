#ifndef __HASHTAB_H__
#define __HASHTAB_H__

#include <array>
#include <cmath>
#include <map>
#include <string>

#define SIZE_HT 500000

static const int PRIME_CONST = 31;

class Hashtab {
public:
  Hashtab() = default;
  Hashtab(long unsigned);
  unsigned int KRHash(const std::string &);
  unsigned int ELFHash(const std::string &);
  const std::array<std::pair<std::string, int>, SIZE_HT> &get_ht();
  void add_dhash(const std::string &, const int &, int &);
  void add_kidding(const std::string &key, const int &value, int &col);
  int lookup(const std::string &);

private:
  long unsigned size_ht;
  std::array<std::pair<std::string, int>, SIZE_HT> ht;
};

#endif // __HASHTAB_H__