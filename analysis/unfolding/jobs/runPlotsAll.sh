#syst="ttbarUE,pdf,topMass,tchanHdampPS,tchanScaleME,tchanScalePS,ttbarScaleME,ttbarHdampPS,ttbarPt,ttbarScaleFSRPS,ttbarScaleISRPS,wjetsScaleME"
syst=""
for channels in ele mu ele,mu
    do
    for setup in TopPtParton TopYParton TopCosParton LeptonPtParton LeptonEtaParton WPtParton TopPtParticle TopYParticle TopCosParticle LeptonPtParticle LeptonEtaParticle WPtParticle
        do
        echo $setup $channels
        #echo "ADD PDF SYST!!!!"
        python driver.py -m setup/$setup -m tasks/plotCrossSection -c channels:$channels
        done
    done
