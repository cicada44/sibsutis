#!/bin/bash

gcc -Wall serial.c -o serial.out -fopenmp -lm
gcc -Wall ompv1.c -o ompv1.out -fopenmp -lm
gcc -Wall ompv2.c -o ompv2.out -fopenmp -lm
gcc -Wall ompv3.c -o ompv3.out -fopenmp -lm
gcc -Wall ompv4.c -o ompv4.out -fopenmp -lm
gcc -Wall ompv5.c -o ompv5.out -fopenmp -lm
