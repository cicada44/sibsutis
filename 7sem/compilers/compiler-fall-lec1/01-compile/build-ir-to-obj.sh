#!/bin/sh

llc ./prog.ll -o prog.s
clang++ ./prog.s -o prog





