#!/bin/bash
for i in `find . -name "*$1*"`;
    do
    echo $i
    crab resubmit $i/crab_DX_13 
    #python crab/main.py $i
    done
