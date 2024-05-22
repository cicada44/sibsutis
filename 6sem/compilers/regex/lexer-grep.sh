#!/bin/sh

SIGNS="[+-]?"

# literals
INTLITERALS="(u|U|l|L|ll|LL|ul|UL|uL|Ul|ull|ULL|uLL|Ull|llu|LLu|llU|LLU|z|Z|uz|UZ|uZ|Uz)?"
FLOATLITERALS="(l|f|L|F)?"

# numbers
DEC="([1-9]('?[0-9]+)*|0)"
OCT="0[[0-9]']*"
HEX="0x[0-9a-f]*"
BINARY="0b[01]+"

ONELINECOM="//.+"
MULTILINECOM="/\\*[^*]*\\*+([^/*][^*]*\\*+)*/"

# READY REGEXPS
KEYWORDS="(for|if|while)"
IDENTIFIERS="[_a-zA-Z][_a-zA-Z0-9]*"
CHARS="(u8|u|U|L)?'(\\\.+|.)'"
STRINGS="(R|L|LR|u8|u8R|u|uR|U|UR)?\"(\\.|[^\"\\\])*\""
ALLINT="$SIGNS($DEC|$OCT|$HEX|$BINARY)$INTLITERALS"
ALLFLOAT="(0x((([0-9]|[a-f])*\.([0-9]|[a-f])+)|(([0-9]|[a-f])+\.?))(p$SIGNS([0-9]|[a-f])+)?(f|l|F|L)?)|((([0-9]*\.[0-9]+)|([0-9]+\.?))(e$SIGNS[0-9]+)?(f|l|F|L)?)"
USERDEFLITERALS="(($ALLINT|$ALLFLOAT|$STRINGS|$CHARS)\s?)+_[a-su-zA-SU-Z][_a-zA-Z0-9]*"
COMPARISON="(==|!=|<|>|<=|>=)"
ASSIGNMENT="(\+|\-|\*|/|%|&|\||\^|<<|>>)?="
MEMBERACCESS="[*&]?$IDENTIFIERS(\[$IDENTIFIERS\]|\.\*?$IDENTIFIERS|->\*?$IDENTIFIERS)"
PREPROCESSOR="([#!][ \t]*[A-z]{2,}[\s]{1,}?([A-z]{2,}[\s]{1,}?)?)([\\(]?[^\s\\)]{1,}[\\)]?)?"
ALLCOMMENTS="($ONELINECOM|$MULTILINECOM)"

# value to change
REGEXP="$ALLCOMMENTS"

DIR="."
GREP="pcregrep -M -o"
f="example.cpp"
echo "*** File $f"
echo "KEYWORDS"
$GREP "$KEYWORDS" $f
echo "\nIDENTIFIERS"
$GREP "$IDENTIFIERS" $f
echo "\nCHARS"
$GREP "$CHARS" $f
echo "\nSTRINGS"
$GREP "$STRINGS" $f
echo "\nALLINT"
$GREP "$ALLINT" $f
echo "\nALLFLOAT"
$GREP "$ALLFLOAT" $f
echo "\nUSERDEFINEDLITERALS"
$GREP "$USERDEFLITERALS" $f
echo "\nCOMPARISON"
$GREP "$COMPARISON" $f
echo "\nASSIGNMENT"
$GREP "$ASSIGNMENT" $f
echo "\nMEMBERACCESS"
$GREP "$MEMBERACCESS" $f
echo "\nPREPROCESSOR"
$GREP "$PREPROCESSOR" $f
echo "\nALLCOMMENTS"
$GREP "$ALLCOMMENTS" $f


### deprecated

#for f in `find $DIR -name "example.cpp"`; do
    #echo "*** File $f"
    #pcregrep -M -o "$REGEXP" $f
#done

# types
#INTTYPES="(unsigned|long)?\s?(long|long long)?\s?(int)?"
#FLOATTYPES="(double|float|long float)"

# left-hand side
# INTBEGIN="$INTTYPES $IDENTIFIERS ="

# right-hand side
#DECIMAL="$INTBEGIN $DEC$INTLITERALS"
#OCTAL="$INTBEGIN $OCT$INTLITERALS"
#HEXADECIMAL="$INTBEGIN $HEX$INTLITERALS"
#BYTE="$INTBEGIN $BINARY$INTLITERALS"
#INT="($DECIMAL|$OCTAL|$HEXADECIMAL|$BYTE)"