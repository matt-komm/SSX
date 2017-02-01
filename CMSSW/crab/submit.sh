#!/bin/bash
for i in {0..36};
    do
    echo
    #sleep 2s
    #echo $i
    python crab/main.py $i
    done
