#!/bin/bash
for i in {0..4};
    do
    #echo $i
    python crab/main.py $i
    done
