syst="btag,ltag,eleEff,muEff,en,pu,unc"
for channels in ele mu ele,mu
    do
    python driver.py -m tasks/makeFitMarginalized -c channels:$channels -c systematics:$syst
    for setup in TopPtParton TopYParton TopCosParton LeptonPtParton LeptonEtaParton WCosParton
        do
        python driver.py -m tasks/makeFitMarginalized -m setup/$setup -c channels:$channels -c systematics:$syst
        done
    done
