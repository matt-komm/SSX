syst="ttbarUE,pdf,topMass,tchanHdampPS,tchanScaleME,tchanScalePS,ttbarScaleME,ttbarHdampPS,ttbarPt,ttbarScaleFSRPS,ttbarScaleISRPS,wjetsScaleME,bfrac,tchanColor,ttbarColor"

#    for setup in TopPtParton TopYParton TopCosParton TopCosTauParton LeptonPtParton LeptonEtaParton WPtParton TopPtParticle TopYParticle TopCosParticle LeptonPtParticle LeptonEtaParticle WPtParticle

for channels in ele mu ele,mu
    do
    for setup in TopPtParton TopYParton TopCosParton TopCosTauParton LeptonPtParton LeptonEtaParton WPtParton TopPtParticle TopYParticle TopCosParticle LeptonPtParticle LeptonEtaParticle WPtParticle
        do
        echo $setup $channels
        #echo "ADD PDF SYST!!!!"
        python driver.py -m setup/$setup -m tasks/plotCrossSection -c channels:$channels -c systematics:$syst &
        done
    wait ${!}
    done
