#!/bin/bash
fileName=$1
moreFlag=$2
outName=program
echo compiling...
g++ -DLOCALONLY ${moreFlag} ${fileName} -o ${outName}.out
echo running....
time ./program.out
echo finish
# rm ${outName}.out