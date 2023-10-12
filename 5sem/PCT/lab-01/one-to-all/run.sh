#!/bin/bash

mpicxx one-to-all-1.cpp -o ota1

mpicxx one-to-all-2.cpp -o ota2

for np in {1..6}; do
  echo ""
  echo " --------------------------------------"
  echo "|Executing 'one to all V.1' on $np threads|"
  echo " --------------------------------------"
  echo ""

  mpirun -np $np ./ota1

  echo ""
  echo " ----------------------------------------"
  echo "|Executing 'one to all V.2' on $np threads|"
  echo " ----------------------------------------"
  echo ""

  mpirun -np $np ./ota2

  echo ""
done

# Удаление скомпилированных файлов
rm ota1 ota2
