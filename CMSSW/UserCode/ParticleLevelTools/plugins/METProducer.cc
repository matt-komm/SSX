// system include files
#include <memory>
#include <vector>
// user include files

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/ESHandle.h"

#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/PatCandidates/interface/PackedGenParticle.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"

#include "CommonTools/Utils/interface/StringCutObjectSelector.h"

#include "UserCode/ParticleLevelTools/interface/Utils.h"


class METProducer:
    public edm::EDProducer
{
    private:    
        edm::EDGetTokenT<std::vector<pat::PackedGenParticle>> _genParticleToken;
        std::unique_ptr<StringCutObjectSelector<pat::PackedGenParticle>> _selector;

    public:
        explicit METProducer(const edm::ParameterSet& iConfig):
            _genParticleToken(consumes<std::vector<pat::PackedGenParticle>>(iConfig.getParameter<edm::InputTag>("src"))),
            _selector(nullptr)
        {
            if (iConfig.exists("cut"))
            {
                _selector.reset(new StringCutObjectSelector<pat::PackedGenParticle>(iConfig.getParameter<std::string>("cut")));
            }
            produces<std::vector<pat::PackedGenParticle>>();
        }
        
        virtual void produce(edm::Event& edmEvent, const edm::EventSetup& edmSetup) override
        {
            edm::Handle<std::vector<pat::PackedGenParticle>> genParticleCollection;
            edmEvent.getByToken(_genParticleToken, genParticleCollection);
            
            std::unique_ptr<std::vector<pat::PackedGenParticle>> output(new std::vector<pat::PackedGenParticle>(1));
            
            
            double px = 0;
            double py = 0;
            double pz = 0;
            for (const pat::PackedGenParticle& genParticle: *genParticleCollection.product())
            {
                if (_selector and not (*_selector)(genParticle))
                {
                    continue;
                }  
                px+=genParticle.px();
                py+=genParticle.py();
                pz+=genParticle.pz();
            }
            reco::Candidate::LorentzVector vector(px,py,pz,std::sqrt(px*px+py*py+pz*pz));
            (*output)[0].setP4(vector);
            
            edmEvent.put(std::move(output));
        }
        
        ~METProducer()
        {
        }

        static void fillDescriptions(edm::ConfigurationDescriptions& descriptions)
        {
            edm::ParameterSetDescription desc;
            desc.setUnknown();
            descriptions.addDefault(desc);
        }
};



DEFINE_FWK_MODULE(METProducer);
