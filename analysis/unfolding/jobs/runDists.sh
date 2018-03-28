systProfiled="btag,ltag,eleEff,muEff,en,res,pu,unc,dy,tw,eleMultiIso,eleMultiVeto,muMulti"
systExtern="topMass,tchanHdampPS,tchanScaleME,tchanScalePS,ttbarHdampPS,ttbarPt,ttbarScaleFSRPS,ttbarScaleISRPS"

for channels in ele mu ele,mu
    do
    python driver.py -m setup/Wjets -m tasks/plotDistribution -c channels:$channels -c plot:2j0t,mtw2j0t -c profiled:$systProfiled
    for setup in 2j1t,mtw2j1t 2j1t,bdtttw2j1t 2j1t,bdttch2j1t 3j2t,mtw3j2t 2j1t,pt2j1t 2j1t,y2j1t 2j1t,cos2j1t 2j1t,lpt2j1t 2j1t,leta2j1t 2j1t,wpt2j1t  
        do
        echo $setup $channels
        #echo "ADD PDF/LTAG SYST!!!!"
        python driver.py -m tasks/plotDistribution -c channels:$channels -c plot:$setup -c profiled:$systProfiled
        done
    done
