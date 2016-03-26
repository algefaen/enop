#!/bin/bash

dir=$(dirname $0)

cd $dir

while true;
do
	./meteo_read.rb &> /tmp/meteo.log
done
