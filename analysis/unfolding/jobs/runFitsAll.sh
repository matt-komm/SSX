syst="btag,ltag,eleEff,muEff,en,res,pu,unc,dy,tw,eleMultiIso,eleMultiVeto,muMulti,ttbarUE,pdf,topMass,tchanHdampPS,tchanScaleME,tchanScalePS,ttbarScaleME,ttbarHdampPS,ttbarPt,ttbarScaleFSRPS,ttbarScaleISRPS,wjetsScaleME"

for channels in ele mu ele,mu
    do
    python driver.py -m tasks/makeFitMarginalized -c channels:$channels -c systematics:$syst
    python driver.py -m setup/Wjets -m tasks/makeFitMarginalized -c channels:$channels -c systematics:$syst
    for setup in TopPtParton TopYParton TopCosParton LeptonPtParton LeptonEtaParton WPtParton
        do
        #echo "!!!! ADD LTAG SYST !!!!"
        python driver.py -m tasks/makeFitMarginalized -m setup/$setup -c channels:$channels -c systematics:$syst
        done
    done
