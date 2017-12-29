#include "FWCore/Framework/interface/MakerMacros.h"
#include "CommonTools/UtilAlgos/interface/StringCutObjectSelector.h"
#include "CommonTools/UtilAlgos/interface/SingleObjectSelector.h"
#include "DataFormats/PatCandidates/interface/PackedGenParticle.h"

typedef SingleObjectSelector<pat::PackedGenParticleCollection,StringCutObjectSelector<pat::PackedGenParticle>> PackedGenParticleSelector;
 
DEFINE_FWK_MODULE(PackedGenParticleSelector);
