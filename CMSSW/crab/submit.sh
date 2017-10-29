#!/bin/bash
for i in {16..24};
    do
    echo
    sleep 2s
    #echo $i
    python crab/main.py $i
    done
