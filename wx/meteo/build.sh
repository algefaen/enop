#!/bin/bash
cd Binaries
echo "Build command line tools"
echo "========================"
make $1 || exit 1
cd ../
echo -e "done"
