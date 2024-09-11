#!/bin/bash

# Output assembly code
llc -o=examples/$1.s examples/$1.ll

# Compiles LLVM IR (bytecode) into assembly language for a specified architecture
llc -march=x86-64 -O3 -filetype=obj -relocation-model=pic -opaque-pointers -o=examples/$1.o examples/$1.ll

# Linking
clang -o examples/$1.x examples/$1.o src/rtcalc.c
