syst="btag,ltag,eleEff,muEff,en~,res~,pu,unc~,dy,tw,eleMultiIso,eleMultiVeto,muMulti"


python driver.py -m tasks/makeFitMarginalized -c channels:$1 -c systematics:$syst
python driver.py -m tasks/makeFitMarginalized -c channels:$1 -c systematics:en~ -c output:jesonly
python driver.py -m setup/Wjets -m tasks/makeFitMarginalized -c channels:$1 -c systematics:$syst
for setup in TopPtParton TopYParton TopCosParton LeptonPtParton LeptonEtaParton WPtParton
    do
    #echo "!!!! ADD LTAG SYST !!!!"
    python driver.py -m tasks/makeFitMarginalized -m setup/$setup -c channels:$1 -c systematics:$syst
    python driver.py -m tasks/makeFitMarginalized -m setup/$setup -c channels:$1 -c systematics:en~ -c output:jesonly
    done

