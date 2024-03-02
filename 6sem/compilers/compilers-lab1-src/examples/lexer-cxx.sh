#!/bin/sh

DIR="folly"

for f in `find $DIR -name "*.cpp"`; do
    echo "*** File $f"
    ./lexer $f
done
