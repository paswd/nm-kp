#!/bin/bash

make > /dev/null
./nm-kp $1 $2 $3
gnuplot -persist "plot.gp"
