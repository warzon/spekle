#!/bin/bash

title=$3
filename="$2.pm3d.eps"
datafile=$1

gnuplot <<EOF
set term postscript eps enhanced color solid
set output "$filename"
set grid x y z
splot "$datafile" matrix with pm3d title "$title"
EOF
