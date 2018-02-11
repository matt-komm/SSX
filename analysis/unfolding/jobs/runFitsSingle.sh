syst=(
"systematics/topMassDown"
"systematics/topMassUp"
"systematics/ttbarPt"
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
"systematics/tchanScaleTmpl -c qscale:UU"
"systematics/tchanScaleTmpl -c qscale:DD"
)
for channels in ele mu ele,mu
    do
    python driver.py -m tasks/makeFitSingle -c channels:$channels
    for sys  in "${syst[@]}"
        do
        python driver.py -m tasks/makeFitSingle -m $sys -c channels:$channels
        for setup in TopPtParton TopYParton TopCosParton LeptonPtParton LeptonEtaParton WCosParton WPtParton
            do
            python driver.py -m tasks/makeFitSingle -m $sys -m setup/$setup -c channels:$channels
            done
        done
    done
