#ifndef __EXT_FUNCS_HASHTAB_H__
#define __EXT_FUNCS_HASHTAB_H__

#include "../Hashtab/Hashtab.hpp"
#include <string>
#include <vector>

void print_hashtab(Hashtab &);
int read_dict(char *&, std::vector<std::string> &);

#endif // __EXT_FUNCS_HASHTAB_H__