systProfiled="btag ltag eleEff muEff en res pu unc dy tw eleMultiIso eleMultiVeto muMulti"
systExternalized="ttbarUE pdf topMass tchanHdampPS tchanScaleME tchanScalePS ttbarHdampPS ttbarPt ttbarScaleFSRPS ttbarScaleISRPS ttbarScaleME wjetsScaleME"
syst="$systProfiled $systExternalized"

for channel in ele mu
    do
    for sys in $syst
        do
        echo $sys"Up",$sys"Down"
        python driver.py -m tasks/checkSys -c channel:$channel -c uncertainties:$sys"Up",$sys"Down" -c name:$sys
        done
    done
