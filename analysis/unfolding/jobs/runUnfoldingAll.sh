syst="btag,ltag,eleEff,muEff,en,res,pu,unc,dy,tw,eleMultiIso,eleMultiVeto,muMulti,ttbarUE,pdf,topMass,tchanHdampPS,tchanScaleME,tchanScalePS,ttbarScaleME,ttbarHdampPS,ttbarPt,ttbarScaleFSRPS,ttbarScaleISRPS,wjetsScaleME"

for channels in ele mu ele,mu
    do
    for setup in TopPtParton TopYParton TopCosParton LeptonPtParton LeptonEtaParton WPtParton TopPtParticle TopYParticle TopCosParticle LeptonPtParticle LeptonEtaParticle WPtParticle
        do
        echo $setup $channels
        #echo "!!!! ADD LTAG SYST !!!!"
        python driver.py -m setup/$setup -m tasks/makeUnfolding -c channels:$channels -c systematics:$syst
        done
    done
