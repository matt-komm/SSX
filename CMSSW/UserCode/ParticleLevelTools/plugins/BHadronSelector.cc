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


class BHadronSelector:
    public edm::EDProducer
{
    private:    
        edm::EDGetTokenT<std::vector<reco::GenParticle>> _genParticleToken;
        std::unique_ptr<StringCutObjectSelector<reco::GenParticle>> _selector;

    public:
        explicit BHadronSelector(const edm::ParameterSet& iConfig):
            _genParticleToken(consumes<std::vector<reco::GenParticle>>(iConfig.getParameter<edm::InputTag>("src"))),
            _selector(nullptr)
        {
            if (iConfig.exists("cut"))
            {
                _selector.reset(new StringCutObjectSelector<reco::GenParticle>(iConfig.getParameter<std::string>("cut")));
            }
            produces<std::vector<pat::PackedGenParticle>>();
        }
        
        virtual void produce(edm::Event& edmEvent, const edm::EventSetup& edmSetup) override
        {
            edm::Handle<std::vector<reco::GenParticle>> genParticleCollection;
            edmEvent.getByToken(_genParticleToken, genParticleCollection);
            
            std::unique_ptr<std::vector<pat::PackedGenParticle>> output(new std::vector<pat::PackedGenParticle>());
            
            for (const reco::GenParticle& genParticle: *genParticleCollection.product())
            {
                if (plt::isBHadron(genParticle.pdgId()) and not hasDaughterBHadron(&genParticle))
                {
                    if (_selector and not (*_selector)(genParticle))
                    {
                        continue;
                    }
                    pat::PackedGenParticle ghost(genParticle);
                    output->emplace_back(std::move(ghost));
                }
            }
            
            edmEvent.put(std::move(output));
        }
        
        static bool hasDaughterBHadron(const reco::Candidate* genParticle)
        {
            for (unsigned int idaughter = 0; idaughter < genParticle->numberOfDaughters (); ++idaughter)
            {
                if (plt::isBHadron(genParticle->daughter(idaughter)->pdgId()))
                {
                    return true;
                }
                else if (hasDaughterBHadron(genParticle->daughter(idaughter)))
                {
                    return true;
                }
            }
            return false;
        }
        
        ~BHadronSelector()
        {
        }

        static void fillDescriptions(edm::ConfigurationDescriptions& descriptions)
        {
            edm::ParameterSetDescription desc;
            desc.setUnknown();
            descriptions.addDefault(desc);
        }
};



DEFINE_FWK_MODULE(BHadronSelector);
