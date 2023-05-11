#!/bin/bash

N=25

echo "Serial:"

./serial.out $N data/serial.dat $p

echo ""

echo "ompv1:"

for ((p=2; p <= 6; p = $[ $p+1 ]))
do
echo "p = $p"
./ompv1.out $N data/prog1.dat $p
done

echo ""

echo "ompv2:"

for ((p=2; p <= 6; p = $[ $p+1 ]))
do
echo "p = $p"
./ompv2.out $N data/prog2.dat $p
done

echo ""

echo "ompv3:"

for ((p=2; p <= 6; p = $[ $p+1 ]))
do
echo "p = $p"
./ompv3.out $N data/prog3.dat $p
done

echo ""

echo "ompv4:"

for ((p=2; p <= 6; p = $[ $p+1 ]))
do
echo "p = $p"
./ompv4.out $N data/prog4.dat $p
done

echo ""

echo "ompv5:"

for ((p=2; p <= 6; p = $[ $p+1 ]))
do
echo "p = $p"
./ompv5.out $N data/prog5.dat $p
done

echo ""

rm *.out
