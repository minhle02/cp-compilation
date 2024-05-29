#!/bin/bash
fileName=$1
outName=__out__
g++ -DLOCALONLY ${fileName} -o ${outName}.out
./${outName}.out
rm ${outName}.out