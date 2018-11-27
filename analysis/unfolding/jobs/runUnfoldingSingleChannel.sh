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


for setup in  TopPtParton TopYParton TopCosParton TopCosTauParton LeptonPtParton LeptonEtaParton WPtParton TopPtParticle TopYParticle TopCosParticle LeptonPtParticle LeptonEtaParticle WPtParticle
    do
    echo $setup $1
    python driver.py -m setup/$setup -m tasks/makeUnfoldingSingle -c channels:$1 &
    done
wait ${!}
for sys  in "${syst[@]}"
    do
    for setup in TopPtParton TopYParton TopCosParton TopCosTauParton LeptonPtParton LeptonEtaParton WPtParton TopPtParticle TopYParticle TopCosParticle LeptonPtParticle LeptonEtaParticle WPtParticle
        do
        echo $setup $1
        python driver.py -m setup/$setup -m tasks/makeUnfoldingSingle -m $sys -c channels:$1 &
        done
    wait ${!}
    done

