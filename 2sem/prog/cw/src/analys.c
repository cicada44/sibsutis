#include "analys.h"
#include "func.h"
#include <stdio.h>
#include <stdlib.h>

void analys()
{
    int size_ign_dict = 0, size_ign_dict_prot = 0, ignore_dict_size_f;
    int tmp;
    int equal_flag;

    char* name;
    char* check;

    int cnt = read_cnt();

    int* ignore_dict = (int*)calloc(cnt, sizeof(int));
    int* ignore_dict_prot = (int*)calloc(cnt, sizeof(int));
    int* ignore_dict_final = (int*)calloc(cnt, sizeof(int));

    char** dict_functions = (char**)malloc(cnt * sizeof(char*));
    for (int i = 0; i < cnt; i++) {
        dict_functions[i] = (char*)malloc(SIZE_STR * sizeof(char));
    }

    char** dict = read_dict(cnt);

    // print_dict(dict, cnt);

    for (int x = 0; x < cnt; x++) {
        for (int i = 0; i < 20; i++) {
            if (is_on_begin_str(dict[x], type_func[i]) == 0) {
                name = read_name_func(dict[x]);
                if (name != NULL) {
                    equal_flag = is_value_in_char_arr(
                            dict_functions, name, size_ign_dict);
                    if (equal_flag == 0) {
                        strcpy(dict_functions[size_ign_dict], name);
                        ignore_dict[size_ign_dict] = x;
                        size_ign_dict++;
                    } else {
                        ignore_dict_prot[size_ign_dict_prot] = x;
                        size_ign_dict_prot++;
                    }
                } else
                    continue;
            }
        }
    }

    ignore_dict_size_f = size_ign_dict + size_ign_dict_prot;

    ignore_dict_final = merge(
            ignore_dict, size_ign_dict, ignore_dict_prot, size_ign_dict_prot);

    char** dict_functions_call = (char**)malloc(size_ign_dict * sizeof(char*));
    for (int i = 0; i < size_ign_dict; i++) {
        dict_functions_call[i] = (char*)malloc(SIZE_STR * sizeof(char));
    }

    for (int x = 0; x < size_ign_dict; x++)
        strcpy(dict_functions_call[x], dict_functions[x]);

    for (int x = 0; x < size_ign_dict; x++)
        dict_functions_call[x][strlen(dict_functions_call[x])] = '(';

    int* calls_dict = add_cnt(
            dict,
            dict_functions_call,
            ignore_dict_final,
            cnt,
            ignore_dict_size_f);

    for (int x = 0; x < cnt; x++) {
        int flag;
        int c = 0;
        while (1) {
            flag = is_value_in_arr(ignore_dict_final, x, ignore_dict_size_f);
            if (flag == 1)
                x++;
            else if (flag == 0)
                break;
        }
        for (int i = 0; i < size_ign_dict; i++) {
            int count = meets_count(dict[x], dict_functions_call[i]);
            calls_dict[i] += count;
        }
    }

    // for (int x = 0; x < y; x++) {
    //     for (int i = 0; i < y; i++) {
    //         if (x == i)
    //             continue;
    //         if (strstr(dict_functions[i], dict_functions[x]) != NULL)
    //             ;
    //         //    calls_dict[i] -= calls_dict[x];
    //     }
    // }

    for (int x = 0; x < size_ign_dict; x++)
        printf("func - %s, calls - %d\n", dict_functions[x], calls_dict[x]);
}