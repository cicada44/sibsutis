#!/bin/sh

CXXFLAGS="-Wall -Isrc/ -Iobj/ -Wno-unused -Wno-deprecated -Wno-write-strings -Wno-free-nonheap-object"

bison -d -v -y -b cool --debug -p cool_yy -o obj/cool-bison-parser.cc src/cool.bison
flex -d -o obj/cool-flex-lexer.cc src/cool.flex
g++ -g $LDFLAGS $CXXFLAGS src/semantic-phase.cpp src/utilities.cc src/stringtab.cc src/cool-tree.cc obj/cool-flex-lexer.cc obj/cool-bison-parser.cc -o bin/analyzer
