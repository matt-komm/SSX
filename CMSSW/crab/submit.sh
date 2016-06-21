#!/bin/bash
for i in {1..31};
    do
    #echo $i
    python crab/main.py $i
    done
