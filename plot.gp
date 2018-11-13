#!/usr/local/bin/gnuplot --persist

set datafile separator " "
plot "plot-numeral.dat" using 1:2 title "Numeral" with lines,\
    "plot-original.dat" using 1:2 title "Original" with li lw 3 lt 0
