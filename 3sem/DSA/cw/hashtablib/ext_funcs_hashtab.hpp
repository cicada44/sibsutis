#ifndef __EXT_FUNCS_HASHTAB_H__
#define __EXT_FUNCS_HASHTAB_H__

#include "Hashtab.hpp"

void print_hashtab(Hashtab &);
int hash_prime(const std::string &);
int read_dict(char *&, std::vector<std::string> &);

#endif // __EXT_FUNCS_HASHTAB_H__