for channels in ele mu ele,mu
    do
    for setup in TopPtParton TopYParton TopCosParton LeptonPtParton WCosParton TopPtParticle TopYParticle TopCosParticle LeptonPtParticle WCosParticle
        do
        python driver.py -m setup/$setup -m tasks/makeUnfolding -c channels:$channels
        done
    done
