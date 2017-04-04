#!/bin/bash
for i in {20..40};
    do
    echo
    #sleep 2s
    #echo $i
    python crab/main.py $i
    done
