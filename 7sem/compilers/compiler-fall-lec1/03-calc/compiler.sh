#!/bin/bash

# Output assembly code
llc -opaque-pointers -o=$1.s $1.ll

# Compiles LLVM IR (bytecode) into assembly language for a specified architecture
llc -march=x86-64 -O3 -filetype=obj -relocation-model=pic -opaque-pointers -o=$1.o $1.ll

# Linking
clang -o $1 $1.o rtcalc.c
