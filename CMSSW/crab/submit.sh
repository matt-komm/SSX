#!/bin/bash
for i in {8..16};
    do
    echo
    sleep 2s
    #echo $i
    python crab/main.py $i
    done
