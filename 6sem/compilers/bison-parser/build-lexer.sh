#!/bin/sh

CXXFLAGS="-Wall -Isrc/ -Wno-unused -Wno-deprecated -Wno-write-strings -Wno-free-nonheap-object"

flex -d -o obj/cool-flex-lexer.cc src/cool.flex
g++ $CXXFLAGS src/utilities.cc src/stringtab.cc obj/cool-flex-lexer.cc src/lexer-test.cc -o bin/lexer
