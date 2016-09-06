#include "UserCode/ParticleLevelTools/interface/Jet.h"


namespace plt
{

Jet::Jet():
    _lorentzVector(0,0,0,0),
    _charge(0),
    _electronEnergy(0,0,0,0),
    _muonEnergy(0,0,0,0),
    _photonEnergy(0,0,0,0),
    _neutrinoEnergy(0,0,0,0)
{
}

double Jet::jetCharge(double exp) const
{
    double jetCharge = 0.0;
    for (const Constituent& obj: _constituents)
    {
        jetCharge+=std::pow(obj.p4.pt(),exp)*obj.charge;
    }
    return jetCharge/std::pow(_lorentzVector.pt(),exp);
}

void Jet::addConstituent(const reco::Candidate& candidate)
{
    int absPdgId = std::abs(candidate.pdgId());
    if (absPdgId==11)
    {
        _electronEnergy+=candidate.p4();
    }
    else if (absPdgId==13)
    {
        _muonEnergy+=candidate.p4();
    }
    else if (absPdgId==22)
    {
        _photonEnergy+=candidate.p4();
    }
    else if (absPdgId==12 || absPdgId==14 || absPdgId==15)
    {
        _neutrinoEnergy+=candidate.p4();
    }
    
    _lorentzVector+=candidate.p4();
    _charge+=candidate.charge();
    _constituents.emplace_back(candidate);
}

}
