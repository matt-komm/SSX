syst="pdf,tchanHdampPS,tchanScaleME,tchanScalePS,topMass,ttbarHdampPS,ttbarPt,ttbarScaleFSRPS,ttbarScaleISRPS"

for channels in ele mu ele,mu
    do
    for setup in TopCosParton
        do
        echo $setup $channels
        python driver.py -m setup/$setup -m tasks/plotCrossSection -c channels:$channels -c systematics:$syst
        done
    done
