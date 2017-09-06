#!/bin/bash

title=$3
filename="$2.image.eps"
datafile=$1

gnuplot <<EOF
set term postscript eps enhanced color solid
set output "$filename"
plot "$datafile" matrix with image title "$title"
EOF
