// system include files
#include <memory>
#include <vector>
// user include files

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/ESHandle.h"

#include "DataFormats/PatCandidates/interface/PackedGenParticle.h"

#include "SimpleProjection.h"

struct CandidateHash
{
    static std::hash<double> hash_d;
    std::size_t operator()(const reco::Candidate* candidate) const
    {
        size_t h = 0x72a5a2c1;
        for (double v: {candidate->px(),candidate->py(),candidate->pz(),double(candidate->pdgId())})
        {
            h ^= hash_d(v) + 0x9e3779b9 + (h<<6) + (h>>2);
        }
        return h;
    }
};
typedef SimpleProjection<pat::PackedGenParticle,CandidateHash> PackedGenParticleProjection;

DEFINE_FWK_MODULE(PackedGenParticleProjection);
