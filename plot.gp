#!/usr/local/bin/gnuplot --persist

set datafile separator " "
plot "plot.dat" using 1:2 title "Numeral" with lines,\
    "plot.dat" using 1:3 title "Original" with li lw 3 lt 0
