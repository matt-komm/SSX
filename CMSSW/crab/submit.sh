#!/bin/bash
for i in {1..32};
    do
    echo
    sleep 10s
    #echo $i
    python crab/main.py $i
    done
