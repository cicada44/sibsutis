#pragma once

int sc_memoryInit();
int sc_memorySet(int address, int value);
int sc_memoryGet(int address, int *value);
int sc_memorySave(char *filename);
int sc_memoryLoad(char *filename);

int sc_regInit();
int sc_regSet(int reg, int value);
int sc_regGet(int reg, int *value);

int sc_commandEncode(int command, int operand, int *value);
int sc_commandDecode(int value, int *command, int *operand);

void output_memory();
void bin(unsigned n);
int comp(const void *n1, const void *n2);
