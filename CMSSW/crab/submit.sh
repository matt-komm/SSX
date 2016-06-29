#!/bin/bash
for i in {1..5};
    do
    #echo $i
    python crab/main.py $i
    done
