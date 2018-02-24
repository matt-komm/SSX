syst="pdf,tchanHdampPS,tchanScaleME,tchanScalePS,topMass,ttbarHdampPS,ttbarPt,ttbarScaleFSRPS,ttbarScaleISRPS"

for channels in ele mu ele,mu
    do
    for setup in TopPtParton TopYParton TopCosParton LeptonPtParton LeptonEtaParton WPtParton TopPtParticle TopYParticle TopCosParticle LeptonPtParticle LeptonEtaParticle WPtParticle
        do
        echo $setup $channels
        python driver.py -m setup/$setup -m tasks/plotCrossSection -c channels:$channels -c systematics:$syst
        done
    done
