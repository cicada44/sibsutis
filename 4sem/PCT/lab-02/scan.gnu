#!/usr/bin/gnuplot
set termoption enhanced
set terminal svg size 800,600 font "Arial, 16"
set output "plot.svg"
set style line 1 lc rgb "0xDC143C" lt 1 lw 4 pt 9 ps 1
set style line 2 lc rgb "0x6495ED" lt 1 lw 4 pt 7 ps 1
set style line 3 lc rgb "0x67787B" lt 1 lw 4 pt 5 ps 1
set border lw 2
set grid
set key top left

set xlabel "Number of threads"
set ylabel "Speedup" rotate by 90

set xtics 1
set ytics 1
set mxtics

set format x "%g"
set format y "%.3f"

plot "data.dat" using 1:2 title "N = 15000" with linespoints ls 1, \
"data.dat" using 1:3 title "N = 20000" with linespoints ls 2, \
"data.dat" using 1:4 title "N = 25000" with linespoints ls 3, \
"data.dat" using 1:5 title "linear speedup" with linespoints ls 4
