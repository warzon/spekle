#!/bin/bash

title=$3
filename="$2.histogram.eps"
datafile=$1

gnuplot <<EOF
set term postscript eps enhanced color solid
set output "$filename"
set grid x y
plot "$datafile" with impulses title "$title"
EOF
