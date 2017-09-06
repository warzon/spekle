#!/bin/bash

title=$3
filename="$2.line.eps"
datafile=$1

gnuplot <<EOF
set term postscript eps enhanced color solid
set output "$filename"
set grid x y
plot "$datafile"  with lines title "$title"
EOF
