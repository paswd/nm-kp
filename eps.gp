#!/usr/local/bin/gnuplot --persist

set datafile separator " "
set xlabel "h"
set ylabel "eps"
plot "plot-eps.dat" using 1:2 title "" with lines,\
