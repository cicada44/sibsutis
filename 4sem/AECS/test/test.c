#include <libcomputer/comp.h>

#include <ctest.h>

CTEST(init, successfully_init)
{
    ASSERT_EQUAL(sc_memoryInit(), 0);
}