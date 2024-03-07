#!/bin/sh

bison -o rpcalc.c rpcalc.y
gcc -Wall -o rpcalc rpcalc.c -lm
# rm rpcalc.c
