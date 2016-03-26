#!/bin/bash

dir=$(dirname $0)

cd $dir

while true;
do
	./wind_upload.rb &> /tmp/upload.log
done
