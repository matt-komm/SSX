#!/bin/bash

for i in `echo $@ | sort`;
    do
    echo $i
    crab status $i/crab_SSX 
    echo
    done
