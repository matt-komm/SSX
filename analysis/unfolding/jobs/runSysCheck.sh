systProfiled="en res unc"
systExternalized="ttbarUE pdf topMass tchanHdampPS tchanScaleME tchanScalePS ttbarScaleME ttbarHdampPS ttbarPt ttbarScaleFSRPS ttbarScaleISRPS wjetsScaleME"
syst="$systProfiled $systExternalized"
syst="topMass"
for channel in ele mu
    do
    for sys in $syst
        do
        echo $sys"Up",$sys"Down"
        python driver.py -m tasks/checkSys -c channel:$channel -c uncertainties:$sys"Up",$sys"Down" -c name:$sys
        done
    done
