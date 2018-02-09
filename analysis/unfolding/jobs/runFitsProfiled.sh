syst="btag,ltag,eleEff,muEff,en,pu,unc,dy,tw,eleMultiIso,eleMultiVeto,muMulti"
for channels in mu
    do
    python driver.py -m tasks/makeFitMarginalized -c channels:$channels -c systematics:$syst
    #for setup in TopPtParton TopYParton TopCosParton LeptonPtParton LeptonEtaParton WCosParton WPtParton
    #    do
    #    python driver.py -m tasks/makeFitMarginalized -m setup/$setup -c channels:$channels -c systematics:$syst
    #    done
    done
