#!/bin/bash
for i in `find . -name "*$1*"`;
    do
    echo $i
    crab status $i/crab_SSX 
    done
