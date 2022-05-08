#include "func.h"
#include <stdio.h>
#include <stdlib.h>

char type_func[5][6] = {"void", "char", "int", "float", "double"};

int main(int argc, char* argv[])
{
    int cnt = read_cnt();
    char** dict = read_dict(cnt);

    // print_dict(dict, cnt);

    for (int x = 0; x < cnt; x++) {
    }

    return 0;
}