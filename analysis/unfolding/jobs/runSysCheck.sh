systProfiled="en res unc"
systExternalized="topMass"
syst="$systProfiled $systExternalized"

for channel in ele mu
    do
    for sys in $syst
        do
        echo $sys"Up",$sys"Down"
        python driver.py -m tasks/checkSys -c channel:$channel -c uncertainties:$sys"Up",$sys"Down" -c name:$sys
        done
    done
