gcc -Wall generator.c -o gen.out
g++ -Wall serial.cpp -fopenmp -o serial.out
g++ -Wall parallel.cpp -fopenmp -o parallel.out