#include <stdio.h>

#include <stdlib.h>

#include <libcomputer/comp.h>

void test()
{
    printf("\t\t----- SIMPLE COMPUTER -----\n");
    printf("%-20s"
           " - 1\n"
           "SET VALUE"
           " - 2\n"
           "GET VALUE"
           " - 3\n"
           "SAVE "
           "- 4\n"
           "LOAD "
           "- 5\n"
           "REGISTER INIT"
           " - 6\n"
           "REGISTER SET "
           "- 7\n"
           "REGISTER GET "
           "- 8\n",
           "MEMORY INIT");
}

int main()
{
    // test();

    sc_memoryInit();

    sc_memoryLoad(
            "/home/cicada44/cicada-main/sibsutis/4sem/AECS/test_files_memory/"
            "mem1");

    int* value = malloc(sizeof(int));

    sc_commandEncode(0x33, 0x59, value);

    // printf("%x\n", *value);

    int* command = malloc(sizeof(int));
    int* operand = malloc(sizeof(int));

    sc_commandDecode(*value, command, operand);

    output_memory();

    // printf("%x\n", 0xffff);

    return 0;
}
