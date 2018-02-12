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
    for setup in TopPtParton TopYParton TopCosParton LeptonPtParton LeptonEtaParton WCosParton WPtParton TopPtParticle TopYParticle TopCosParticle LeptonPtParticle LeptonEtaParticle WCosParticle WPtParticle
        do
        echo $setup $channels
        python driver.py -m setup/$setup -m tasks/makeUnfolding -c channels:$channels -c systematics:$syst
        done
    for sys  in "${syst[@]}"
        for setup in TopPtParton TopYParton TopCosParton LeptonPtParton LeptonEtaParton WCosParton WPtParton TopPtParticle TopYParticle TopCosParticle LeptonPtParticle LeptonEtaParticle WCosParticle WPtParticle
            do
            echo $setup $channels
            python driver.py -m setup/$setup -m tasks/makeUnfolding -m $sys -c channels:$channels
            done
        done
    done
