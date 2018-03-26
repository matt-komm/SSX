syst="btag,ltag,eleEff,muEff,en,res,pu,unc,dy,tw,eleMultiIso,eleMultiVeto,muMulti"

for channels in ele mu ele,mu
    do
    python driver.py -m tasks/makeFitMarginalized -c channels:$channels -c systematics:$syst
    #python driver.py -m tasks/makeFitMarginalized -c channels:$channels -c systematics:wjets
    for setup in TopPtParton TopYParton TopCosParton LeptonPtParton LeptonEtaParton WPtParton
        do
        python driver.py -m tasks/makeFitMarginalized -m setup/$setup -c channels:$channels -c systematics:$syst
        done
    done
