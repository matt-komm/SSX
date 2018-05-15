systProfiled="btag,ltag,eleEff,muEff,en,res,pu,unc,dy,tw,eleMultiIso,eleMultiVeto,muMulti"
systExternalized="ttbarUE,pdf,topMass,tchanHdampPS,tchanScaleME,tchanScalePS,ttbarHdampPS,ttbarPt,ttbarScaleFSRPS,ttbarScaleISRPS,ttbarScaleME,wjetsScaleME"
syst="$systProfiled,$systExternalized"

for channel in ele mu
    do
    echo $channels
    python driver.py -m tasks/makeHistSmooth -c channel:$channel -c systematics:$syst
    python driver.py -m tasks/makeHistSmooth -m setup/Wjets -c channel:$channel -c systematics:$syst
    for setup in TopPtParton TopYParton TopCosParton LeptonPtParton LeptonEtaParton WPtParton
        do
        echo $setup $channels
        python driver.py -m setup/$setup -m tasks/makeHistSmooth -c channel:$channel -c systematics:$syst
        done
    done
