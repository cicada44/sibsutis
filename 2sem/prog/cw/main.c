#include "func.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define flagerr printf("111\n");

char type_func[5][6] = {"void", "char", "int", "float", "double"};

int main(int argc, char* argv[])
{
    int p1, p2;
    char* testc;
    char* isis;
    char* name = (char*)malloc(sizeof(char*));
    int cnt = read_cnt();

    char** dict_functions = (char**)malloc(5 * sizeof(char*));
    for (int i = 0; i < cnt; i++) {
        dict_functions[i] = (char*)malloc(SIZE_STR * sizeof(char));
    }

    char** dict_nontype_functions = (char**)malloc(5 * sizeof(char*));
    for (int i = 0; i < cnt; i++) {
        dict_nontype_functions[i] = (char*)malloc(SIZE_STR * sizeof(char));
    }

    char** dict_clear_functions = (char**)malloc(5 * sizeof(char*));
    for (int i = 0; i < cnt; i++) {
        dict_clear_functions[i] = (char*)malloc(SIZE_STR * sizeof(char));
    }

    char** dict = read_dict(cnt);

    print_dict(dict, cnt);
    int y = 0, pos, z = 0;

    for (int x = 0; x < cnt; x++) {
        for (int x = 0; x < sizeof(name); x++)
            name[x] = NULL;
        for (int i = 0; i < 5; i++) {
            testc = strstr(dict[x], type_func[i]);
            if (testc != NULL) {
                // printf("cnt %d - testc - %s\n", x, testc);
                p1 = isOpnBracket(testc);
                p2 = isClsBracket(testc);
                if (p1 != -1 && p2 != -1 && p2 > p1) {
                    z = 0;
                    pos = cncatNameFunc(testc, p1);
                    for (int x = pos; x < p2 + 1; x++) {
                        name[z] = testc[x];
                        z++;
                    }
                    strcpy(dict_nontype_functions[y], name);
                    dict_functions[y] = testc;
                    y++;
                }
            }
        }
    }

    for (int x = 0; x < y; x++) {
        char* temp = read_to_opnbr(dict_nontype_functions[x]);
        strcpy(dict_clear_functions[x], temp);
        printf("str - %s\tlen - %ld\n",
               dict_clear_functions[x],
               strlen(dict_clear_functions[x]));
    }

    int calls_num[y];

    for (int x = 0; x < cnt; x++) {
        for (int i = 0; i < 5; i++) {
            // isis = strstr(dict[x], );
        }
    }
    // for (int x = 0; x < y; x++)
    //     printf("%s", dict_functions[x]);

    for (int x = 0; x < y; x++)
        printf("%s\n", dict_nontype_functions[x]);

    return 0;
}