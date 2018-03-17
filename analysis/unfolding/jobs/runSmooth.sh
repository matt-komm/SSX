syst="pdf,topMass,tchanHdampPS,tchanScaleME,tchanScalePS,ttbarHdampPS,ttbarPt,ttbarScaleFSRPS,ttbarScaleISRPS,ttbarScaleME,wjetsScaleME"
for channel in ele mu
    do
    echo $channels
    python driver.py -m tasks/makeHistSmooth -c channel:$channel -c systematics:$syst
    for setup in TopPtParton TopYParton TopCosParton LeptonPtParton LeptonEtaParton WPtParton
        do
        echo $setup $channels
        python driver.py -m setup/$setup -m tasks/makeHistSmooth -c channel:$channel -c systematics:$syst
        done
    done
