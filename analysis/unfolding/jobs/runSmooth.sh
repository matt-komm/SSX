syst="btag,eleEff,muEff,en,res,pu,unc,dy,tw,eleMultiIso,eleMultiVeto,muMulti,topMass,tchanHdampPS,tchanScaleME,tchanScalePS,ttbarHdampPS,ttbarPt,ttbarScaleFSRPS,ttbarScaleISRPS"

for channel in ele mu
    do
    echo $channels
    echo "ADD PDF/LTAG SYST!!!!"
    python driver.py -m tasks/makeHistSmooth -c channel:$channel -c systematics:$syst
    for setup in TopPtParton TopYParton TopCosParton LeptonPtParton LeptonEtaParton WPtParton
        do
        echo $setup $channels
        echo "ADD PDF/LTAG SYST!!!!"
        python driver.py -m setup/$setup -m tasks/makeHistSmooth -c channel:$channel -c systematics:$syst
        done
    done
