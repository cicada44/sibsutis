#!/bin/bash

mpicxx all-to-all.cpp -o ata

for np in {1..6}; do
  echo ""
  echo "--------------------------------------"
  echo "Executing 'all to all' on $np threads"
  echo "--------------------------------------"
  echo ""

  mpirun -np $np ./ata
done

rm ata
