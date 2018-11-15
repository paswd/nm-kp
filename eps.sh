#!/bin/bash

make > /dev/null
./nm-kp $1 $2 $3 $4
gnuplot -persist "eps.gp"
