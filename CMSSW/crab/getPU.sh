#!/bin/bash
for pu in {64..76}
    do
    echo $pu"000" "for" $1
    pileupCalc.py -i $1 \
    --inputLumiJSON /afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions16/13TeV/PileUp/pileup_latest.txt \
    --calcMode true --minBiasXsec $pu"000" --maxPileupBin 100 --numPileupBins 500 \
    "PU"$pu"000.root"
    
    echo $pu"500" "for" $1
    pileupCalc.py -i $1 \
    --inputLumiJSON /afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions16/13TeV/PileUp/pileup_latest.txt \
    --calcMode true --minBiasXsec $pu"500" --maxPileupBin 100 --numPileupBins 500 \
    "PU"$pu"500.root"
    done
