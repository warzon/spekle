#!/bin/bash

echo "creating image $1"

# destination filename
filename=$1

# data filename
datafile=$2

# graphic title
title="$2"

# plot type
ptype="$3"

if [ "$title" == "" ]; then
	title=${datafile%.*}
fi

if [ "$filename" == "" ]; then
	echo "destination filename is not set"
	exit 
fi

if [ -f $datafile ]; then

	if [ "$ptype" == "pm3d" ]; then	
		../../splot_pm3d.sh $datafile $filename $title
	elif [ "$ptype" == "image" ]; then
		../../plot_image.sh $datafile $filename $title
	elif [ "$ptype" == "line" ]; then
		../../plot_line.sh $datafile $filename $title
	elif [ "$ptype" == "histogram" ]; then
		../../plot_histogram.sh $datafile $filename $title
	fi

else
	echo "data file [ $datafile ] doesnot exists"
	exit
fi

