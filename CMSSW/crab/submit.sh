#!/bin/bash
for i in {0..20};
    do
    echo
    #sleep 1s
    #echo $i
    python crab/main.py $i
    done
