#!/bin/bash

make > /dev/null
./nm-kp $1 $2 $3 $4 > plot.dat
gnuplot -persist "plot.gp"
