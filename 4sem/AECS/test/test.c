#include <libcomputer/comp.h>

#include <ctest.h>

#include <string.h>

#include <stdlib.h>

CTEST(init, mem_init)
{
    ASSERT_EQUAL(sc_memoryInit(), 0);
}

CTEST(set_get, mem_set_get)
{
    for (int x = 25; x != 75; ++x) {
        sc_memorySet(x, x);
    }

    int* accum = malloc(sizeof(int));

    for (int x = 0; x != 100; ++x) {
        int actual = sc_memoryGet(x, accum);
        if (x > 24 && x < 75) {
            ASSERT_EQUAL(actual, 0);
            ASSERT_EQUAL(*accum, x);
        } else {
            ASSERT_EQUAL(actual, 0);
            ASSERT_EQUAL(*accum, 0);
        }
    }

    free(accum);
}

CTEST(save_load, mem_save_load)
{
    char* mem_path1
            = "/home/cicada44/cicada-main/edu/SimpleComputer/test/"
              "test_memory_snapshots/mem1";
    char* mem_path2
            = "/home/cicada44/cicada-main/edu/SimpleComputer/test/"
              "test_memory_snapshots/mem2";

    for (int x = 0; x != 100; ++x) {
        sc_memorySet(x, 0);
    }

    sc_memorySave(mem_path2);

    sc_memorySet(10, 1);

    sc_memorySave(mem_path1);

    sc_memoryInit();

    sc_memoryLoad(mem_path1);

    int* accum = malloc(sizeof(int));

    for (int x = 0; x != 100; ++x) {
        sc_memoryGet(x, accum);
        if (x == 10) {
            ASSERT_EQUAL(*accum, 1);
        } else {
            ASSERT_EQUAL(*accum, 0);
        }
    }

    for (int x = 0; x != 100; ++x) {
        sc_memorySet(x, 0);
    }

    sc_memorySave(mem_path2);

    sc_memoryLoad(mem_path2);

    for (int x = 0; x != 100; ++x) {
        sc_memoryGet(x, accum);
        ASSERT_EQUAL(*accum, 0);
    }

    free(accum);
}
