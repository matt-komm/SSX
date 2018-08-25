syst="btag,ltag,eleEff,muEff,en,res,pu,unc,dy,tw,eleMultiIso,eleMultiVeto,muMulti"

for channels in ele mu ele,mu
    do
    for setup in LeptonPtParton LeptonEtaParton LeptonPtParticle LeptonEtaParticle
        do
        echo $setup $channels
        #echo "!!!! ADD LTAG SYST !!!!"
        python driver.py -m setup/$setup -m tasks/makeUnfolding -c channels:$channels -c systematics:$syst
        done
    done
