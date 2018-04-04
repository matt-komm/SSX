syst=(
"systematics/ttbarUEUp"
"systematics/ttbarUEDown"
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
"systematics/tchanScaleTmpl -c qscale:Up"
"systematics/tchanScaleTmpl -c qscale:Down"
"systematics/ttbarScaleTmpl -c qscale:Up"
"systematics/ttbarScaleTmpl -c qscale:Down"
"systematics/wjetsScaleTmpl -c qscale:Up"
"systematics/wjetsScaleTmpl -c qscale:Down"
)

setups="TopPtParton TopYParton TopCosParton LeptonPtParton LeptonEtaParton WPtParton"
#setups="TopPtParton"

for channels in ele mu ele,mu
    do
    python driver.py -m tasks/makeFitSingle -c channels:$channels
    python driver.py -m setup/Wjets -m tasks/makeFitSingle -c channels:$channels
    for setup in $setups
        do
        python driver.py -m tasks/makeFitSingle -m setup/$setup -c channels:$channels
        done
    #just smooth all systematics
    for sys  in "${syst[@]}"
        do
        python driver.py -m tasks/makeFitSingle -m $sys -c channels:$channels -c smooth:1
        python driver.py -m setup/Wjets -m tasks/makeFitSingle -m $sys -c channels:$channels -c smooth:1
        for setup in $setups
            do
            python driver.py -m tasks/makeFitSingle -m $sys -m setup/$setup -c channels:$channels -c smooth:1
            done
        done
    done
    
    
