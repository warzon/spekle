#!/bin/bash

filename=$1
destination="${filename%.*}-sorted.${filename##*.}"

echo "$filename -> $destination"

sort -n $filename > $destination
