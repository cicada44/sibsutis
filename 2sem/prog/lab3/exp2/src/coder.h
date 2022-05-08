#include "coder.c"
#include <stdio.h>

int encode(uint32_t code_point, CodeUnits* code_units);

uint32_t decode(const CodeUnits* code_unit);

int read_next_code_unit(FILE* in, CodeUnits* code_units);

int write_code_unit(FILE* out, const CodeUnits* code_unit);
