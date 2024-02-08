#!/bin/sh

INTLITERALS="(u|U|l|L|ll|LL|ul|UL|uL|Ul|ull|ULL|uLL|Ull|llu|LLu|llU|LLU|z|Z|uz|UZ|uZ|Uz)?"
FLOATLITERALS="(l|f|L|F)?"

ONELINECOM="//.+"
# MULTILINECOM="/\\*[^*]*\\*+([^/*][^*]*\\*+)*/"
ALLCOMMENTS="($ONELINECOM|$MULTILINECOM)"

BASEKEYWORDS="(for|if|while)"

CXXIDENTIFIERS="[_a-zA-Z][_a-zA-Z0-9]*"

CHARS="(u8|u|U|L)?'(\\\.+|.)'"
STRINGS="(u8R|u|uR|U|UR|R|L|LR|u8)?\"(\\.|[^\"])*\""

PREPROCESSOR="#(if|ifdef|ifndef|else|elif|elifdef|elifndef|endif|define|undef|include|error|warning|line|pragma)+" # DONE?

DEC="([1-9]('?[0-9]+)*|0)"
OCT="0[[0-9]']*"
HEX="0x[0-9a-f]*"
BINARY="0b[01]+"
ALLINT="[+-]?($DEC|$OCT|$HEX|$BINARY)$INTLITERALS"

ALLFLOAT="(0x((([0-9]|[a-f])*\.([0-9]|[a-f])+)|(([0-9]|[a-f])+\.?))(p[+-]?([0-9]|[a-f])+)?(f|l|F|L)?)|((([0-9]*\.[0-9]+)|([0-9]+\.?))(e[+-]?[0-9]+)?(f|l|F|L)?)"

USERDEFLITERALS="(($ALLINT|$ALLFLOAT|$STRINGS|$CHARS)\s?)+_[a-zA-Z][_a-zA-Z0-9]*"

COMPARISON="(==|!=|<|>|<=|>=)"

ASSIGNMENT="(\+|\-|\*|/|%|&|\||\^|<<|>>)?="

MEMBERACCESS="[*&]?$CXXIDENTIFIERS(\[$CXXIDENTIFIERS\]|\.\*?$CXXIDENTIFIERS|->\*?$CXXIDENTIFIERS)"

REGEXP="$STRINGS"

grep -E -o "$REGEXP" main.cpp
