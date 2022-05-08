#!/usr/bin/gnuplot
set termoption enhanced
set terminal svg size 800,600 font "Arial, 16"
set output "plot.svg"
set style line 1 lc rgb "0xDC143C" lt 1 lw 4 pt 9 ps 1
set style line 2 lc rgb "0x6495ED" lt 1 lw 4 pt 7 ps 1
set border lw 2
set grid
set key top left
set xlabel "Elements"
set ylabel "Collisions, с" rotate by 90
set xtics 20000
set mxtics
set format x "%5.0f"
set format y "%5.0f"
plot "data2.dat" using 1:2 title "KR" with linespoints ls 1, \
"data2.dat" using 1:3 title "GDB" with linespoints ls 2
