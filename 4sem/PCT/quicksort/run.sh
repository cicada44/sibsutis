#!/bin/bash

max_file=5
min_file=1
cur_file=1

n_start=2000000
n_end=10000000
n_step=2000000

echo "Serial:"
cur_file=$min_file
for ((n=$n_start; n <= $n_end; n = $[ $n+$n_step ]))
do
./serial.out data/$cur_file.txt
cur_file=$[ $cur_file+1 ]
done

echo ""

echo "Parallel:"

for ((p=2; p <= 6; p = $[ $p+1 ]))
do
cur_file=$min_file
for ((n=$n_start; n <= $n_end; n = $[ $n+$n_step ]))
do
for ((t=1000; t <= 2000; t = $[ $t+1000 ]))
do
echo "Threads = $p Threshold = $t  N = $n"
./parallel.out $p $t data/$cur_file.txt
done
cur_file=$[ $cur_file+1 ]
done
done

echo ""

