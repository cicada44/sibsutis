# size
# m=15000
# n=15000

# threads
threads=2

# compiling
gcc -fopenmp -Wall main.c -o ./benchmark

for (( i=threads;i<=6;i+=1 ))
do
    ./benchmark 15000 15000 $i
    ./benchmark 20000 20000 $i
    ./benchmark 25000 25000 $i
done
