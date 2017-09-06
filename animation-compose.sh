#!/bin/bash

pattern=$1
destname=$2

echo "converting images to animation -> $pattern -> animation/$destname.gif"

convert "$pattern" "animation/$destname.gif"
