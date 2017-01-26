#!/bin/bash

for i in `echo $@ | sort`;
    do
    echo $i
    crab resubmit $i/crab_SSX 
    echo
    done
