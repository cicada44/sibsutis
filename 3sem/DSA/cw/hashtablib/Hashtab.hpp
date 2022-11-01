#ifndef __HASHTAB_H__
#define __HASHTAB_H__

#include <cmath>
#include <string>
#include <vector>

#define SIZE_HT 20001

static const int PRIME_CONST = 31;

class Hashtab {
public:
  Hashtab() = default;
  Hashtab(const long long);
  unsigned int KRHash(const std::string &);
  unsigned int ELFHash(const std::string &);
  const std::vector<int> &get_ht();
  void add_dhash(const std::string &, const int &, int &);
  void add_kidding(const std::string &key, const int &value, int &col);
  int lookup(const std::string &);

private:
  long long size_ht;
  std::vector<int> ht;
};

#endif // __HASHTAB_H__