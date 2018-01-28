for channels in ele mu ele,mu
    do
    for setup in TopPtParton TopYParton TopCosParton LeptonPtParton LeptonEtaParton WCosParton TopPtParticle TopYParticle TopCosParticle LeptonPtParticle LeptonEtaParticle WCosParticle
        do
        echo $setup $channels
        python driver.py -m setup/$setup -m tasks/makeUnfolding -c channels:$channels
        done
    done
