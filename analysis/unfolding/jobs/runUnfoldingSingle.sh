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
"systematics/tchanScaleTmpl -c qscale:UU"
"systematics/tchanScaleTmpl -c qscale:DD"
)


for channels in ele mu ele,mu
    do
    echo $channels
    for setup in TopPtParton TopYParton TopCosParton LeptonPtParton LeptonEtaParton WPtParton TopPtParticle TopYParticle TopCosParticle LeptonPtParticle LeptonEtaParticle WPtParticle
        do
        echo $setup $channels
        python driver.py -m setup/$setup -m tasks/makeUnfoldingSingle -c channels:$channels -c systematics:$syst
        done
    for sys  in "${syst[@]}"
        do
        for setup in TopPtParton TopYParton TopCosParton LeptonPtParton LeptonEtaParton WCosParton WPtParton TopPtParticle TopYParticle TopCosParticle LeptonPtParticle LeptonEtaParticle WCosParticle WPtParticle
            do
            echo $setup $channels
            python driver.py -m setup/$setup -m tasks/makeUnfoldingSingle -m $sys -c channels:$channels
            done
        done
    done
