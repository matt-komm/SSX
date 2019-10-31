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
"systematics/bfracCentral"
"systematics/bfracUp"
"systematics/bfracDown"
"systematics/bfracPeterson"
"systematics/tchanGluonMove"
"systematics/tchanGluonMoveErdOn"
"systematics/tchanErdOn"
"systematics/ttbarGluonMove"
"systematics/ttbarGluonMoveErdOn"
"systematics/ttbarErdOn"
)

syst=(
"systematics/resUp"
"systematics/resDown"
"systematics/enUp"
"systematics/enDown"
"systematics/puUp"
"systematics/puDown"
"systematics/uncUp"
"systematics/uncDown"
"systematics/btagUp"
"systematics/btagDown"
"systematics/ltagUp"
"systematics/ltagDown"
"systematics/eleMutliIsoUp"
"systematics/eleMutliIsoDown"
"systematics/eleMutliVetoUp"
"systematics/eleMutliVetoDown"
"systematics/muMutliIsoUp"
"systematics/muMutliIsoDown"
"systematics/muEffUp"
"systematics/muEffDown"
"systematics/eleEffUp"
"systematics/eleEffDown"
)

for setup in  TopPtParton TopYParton TopCosParton TopCosTauParton LeptonPtParton LeptonEtaParton WPtParton TopPtParticle TopYParticle TopCosParticle LeptonPtParticle LeptonEtaParticle WPtParticle
    do
    echo $setup $1
    python driver.py -m setup/$setup -m tasks/makeUnfoldingSingle -c channels:$1 
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

