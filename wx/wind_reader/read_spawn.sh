#!/bin/bash

dir=$(dirname $0)

while true;
do
	$dir/reader | $dir/ftee $dir/wind &> /dev/null
done
