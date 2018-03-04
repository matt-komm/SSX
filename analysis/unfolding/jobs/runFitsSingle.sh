syst=(
"systematics/topMassDown"
"systematics/topMassUp"
"systematics/ttbarPtUp"
"systematics/ttbarPtDown"
"systematics/pdfUp"
"systematics/pdfDown"
"systematics/ttbarHdampPSDown"
"systematics/ttbarHdampPSUp"
"systematics/ttbarScaleISRPSDown"
"systematics/ttbarScaleISRPSUp"
"systematics/ttbarScaleFSRPSDown"
"systematics/ttbarScaleFSRPSUp"
"systematics/tchanHdampPSDown"
"systematics/tchanHdampPSUp"
"systematics/tchanScalePSDown"
"systematics/tchanScalePSUp"
"systematics/tchanScaleTmpl -c qscale:ND"
"systematics/tchanScaleTmpl -c qscale:NU"
"systematics/tchanScaleTmpl -c qscale:DN"
"systematics/tchanScaleTmpl -c qscale:UN"
"systematics/tchanScaleTmpl -c qscale:Up"
"systematics/tchanScaleTmpl -c qscale:Down"
)

#syst=(
#"systematics/ttbarPtUp"
#"systematics/ttbarPtDown"
#)

setups="TopPtParton TopYParton TopCosParton LeptonPtParton LeptonEtaParton WPtParton"
#setups="TopPtParton"

for channels in ele mu ele,mu
    do
    python driver.py -m tasks/makeFitSingle -c channels:$channels
    python driver.py -m tasks/makeFitSingle -c channels:$channels -m setup/Wjets
    for setup in $setups
        do
        python driver.py -m tasks/makeFitSingle -m setup/$setup -c channels:$channels
        done
    #just smooth all systematics
    for sys  in "${syst[@]}"
        do
        python driver.py -m tasks/makeFitSingle -m $sys -c channels:$channels -c smooth:1
        for setup in $setups
            do
            python driver.py -m tasks/makeFitSingle -m $sys -m setup/$setup -c channels:$channels -c smooth:1
            done
        done
    done
    
    
