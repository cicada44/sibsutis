#!/usr/bin/gnuplot

set termoption enhanced
set terminal svg size 800,600 font "Arial, 16"
set output "plot.svg"
set style line 1 lc rgb "0xDC143C" lt 1 lw 4 pt 9 ps 1
set style line 2 lc rgb "0x6495ED" lt 1 lw 4 pt 7 ps 1
set border lw 2
set grid
set key top left
set xlabel "Amount of elements"
set ylabel "Time, с" rotate by 90
set logscale y
set xtics 50000
set ytics 3
set mxtics
set format x "%5.0f"
set format y "%g"
plot "data.dat" using 1:2 title "Quick sort" with linespoints ls 1