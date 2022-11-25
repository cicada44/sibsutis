#!/usr/bin/gnuplot

set termoption enhanced
set terminal svg size 800,600 font "Arial, 16"
set output "coll.svg"
set style line 1 lc rgb "0xDC143C" lt 1 lw 4 pt 9 ps 1
set style line 2 lc rgb "0x6495ED" lt 1 lw 4 pt 7 ps 1
set border lw 2
set grid
set key top left
set xlabel "Count"
set ylabel "Collisions" rotate by 90
set xtics 100000
set mxtics
set format x "%6.0f"
set format y "%.2f"
plot "Data/coll.txt" using 1:2 title "ELF KR" with linespoints ls 1 , \
"Data/coll.txt" using 1:3 title "FNV & DJB2" with linespoints ls 2, \
"Data/coll.txt" using 1:4 title "Add & Jen" with linespoints ls 3
