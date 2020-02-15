syst=(
"systematics/ttbarUEUp"
"systematics/ttbarUEDown"
"systematics/topMassDown -c smoothing:1"
"systematics/topMassUp -c smoothing:1"
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

syst=(
"systematics/pdftchDown"
"systematics/pdftchUp"
"systematics/pdfBkgDown"
"systematics/pdfBkgUp"
)

setups="TopPtParton TopYParton TopCosParton LeptonPtParton LeptonEtaParton WPtParton"
#setups="TopPtParton"



#python driver.py -m tasks/makeFitSingle -c channels:$1
#python driver.py -m setup/Wjets -m tasks/makeFitSingle -c channels:$1
#for setup in $setups
#    do
#    python driver.py -m tasks/makeFitSingle -m setup/$setup -c channels:$1
#    done


for sys  in "${syst[@]}"
    do
    python driver.py -m tasks/makeFitSingle -m $sys -c channels:$1
    python driver.py -m setup/Wjets -m tasks/makeFitSingle -m $sys -c channels:$1
    for setup in $setups
        do
        python driver.py -m tasks/makeFitSingle -m $sys -m setup/$setup -c channels:$1 &
        done
    wait ${!}
    done

    
    
