#ifndef __muonisolation_H__
#define __muonisolation_H__

#include "pxl/hep.hh"
#include "pxl/core.hh"
#include <limits>

float pfRelMuonIso(const pxl::Particle* particle, float beta=0.5)
{
    float R04PFsumChargedHadronPt = particle->getUserRecord("R04PFsumChargedHadronPt").toFloat();
    float R04sumNeutralHadronEt = particle->getUserRecord("R04PFsumNeutralHadronEt").toFloat(); //Correct it!
    float R04PFsumPhotonEt = particle->getUserRecord("R04PFsumPhotonEt").toFloat(); //Correct it!
    float R04PFsumPUPt = particle->getUserRecord("R04PFsumPUPt").toFloat();
    float pT =  particle->getPt();
    if( pT < std::numeric_limits<float>::epsilon())
    {
        throw "Division by zero pT!";
    }
    return  (R04PFsumChargedHadronPt + std::max(R04sumNeutralHadronEt+ R04PFsumPhotonEt - beta*R04PFsumPUPt, 0.0f)) / pT;
}

float pfRelRelElectronIso (pxl::Particle* particle, float relIsoBarrel, float relIsoEndcap)
{
    float relIso = particle->getUserRecord("effAreaRelIso").toFloat();
    if (std::fabs(particle->getUserRecord("superClusterEta").toFloat())<1.479)
    {
        return relIso/relIsoBarrel;
    }
    else
    {
        return relIso/relIsoEndcap;
    }
}

#endif

