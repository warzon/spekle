#!/bin/bash

root=$1
TimeSlices=$2
Dim=$3
Cycles=$4

if [ "$root" == "" ]; then
	root="data"
fi

[ -d $root ] || mkdir $root

cd $root

for i in {1..10} 
do
	echo "data generation cycle $i of $Cycles"

	folder="generation-$i" 

	mkdir $folder

	if [ -d $folder ]; then
		cd $folder 

		echo "TimeSlices $Time | Image Dimensions [$Dim,$Dim]" > config

		mkdir "img"
		echo "entering $folder"

		../../spekle $TimeSlices $Dim 

		if [ -d "img" ]; then
			../../process-data.sh
		fi

		cd ../
	fi
done
