#include <libcomputer/comp.h>

#include <stdlib.h>

#include <stdio.h>

#define ONE_BIT 0x1

static int flags;

static int *memory = NULL;

static int size_memory = 0;

int sc_memoryInit()
{
    memory = calloc(100, sizeof(int));

    if (memory == NULL)
    {
        sc_regSet(1, 1);
        return -1;
    }

    return 0;
}

int sc_memorySet(int address, int value)
{
    if (address < 0 || address > 99)
    {
        sc_regSet(1, 1);
        return -1;
    }

    memory[address] = value;

    return 0;
}

int sc_memoryGet(int address, int *value)
{
    if (value == NULL || address < 0 || address > 99)
    {
        sc_regSet(1, 1);
        return -1;
    }

    *value = memory[address];

    return 0;
}

int sc_memorySave(char *filename)
{
    FILE *output_file = fopen(filename, "wb");

    if (output_file == NULL)
    {
        fclose(output_file);
        return -1;
    }

    if (fwrite(memory, sizeof(int), 100, output_file) != 100)
    {
        return -1;
    }

    fclose(output_file);

    return 0;
}

int sc_memoryLoad(char *filename)
{
    FILE *input_file = fopen(filename, "rb");

    if (input_file == NULL)
    {
        fclose(input_file);
        return -1;
    }

    if (fread(memory, sizeof(int), 100, input_file) != 100)
    {
        return -1;
    }

    fclose(input_file);

    return 0;
}

int sc_regInit()
{
    flags = 0;
}

int sc_regSet(int reg, int value)
{
    if (reg < 0 || reg > 32 || (value != 0 && value != 1))
    {
        return -1;
    }

    (value == 1) ? (flags |= (1 << (reg - 1))) : (flags &= (~(1 << (reg - 1))));

    return 0;
}

int sc_regGet(int reg, int *value)
{
    if (reg < 0 || reg > 32 || value == NULL)
    {
        return -1;
    }

    *value = (flags >> (reg - 1)) & ONE_BIT;

    return 0;
}

void output_memory()
{
    for (size_t i = 0; i != 100; ++i)
    {
        if (i % 10 == 0 && i != 0)
        {
            printf("\n");
        }
        printf("%3d ", memory[i]);
    }

    printf("\n");
}
