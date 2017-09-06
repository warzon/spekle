#!/bin/bash

for file in $(ls *.plot) 
do
	echo "sorting: processing $file"

	../../sort.sh $file
done

for file in $(ls *.plot && ls *.splot) 
do
	
	dest="img/$file"
	ext=${file##*.}

	echo "image: processing $file -> $dest"

	if [ "$ext" == "plot" ]; then	
		../../gnuplot-compose.sh $dest $file line
		../../gnuplot-compose.sh $dest $file histogram
	elif [ "$ext" == "splot" ]; then 
		../../gnuplot-compose.sh $dest $file image
		../../gnuplot-compose.sh $dest $file pm3d
	fi
done

#./animation-compose.sh "img/phase*-sorted.plot.eps" phase-sorted
#./animation-compose.sh "img/dispo*-sorted.plot.eps" disposition-sorted
