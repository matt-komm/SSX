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

#include "DataFormats/Common/interface/ValueMap.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/PatCandidates/interface/PackedGenParticle.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/JetReco/interface/GenJet.h"
#include "DataFormats/PatCandidates/interface/Jet.h"

#include "UserCode/ParticleLevelTools/interface/Utils.h"

#include "fastjet/JetDefinition.hh"
#include "fastjet/ClusterSequence.hh"

#include "UserCode/ParticleLevelTools/interface/Jet.h"

#include <unordered_map>
#include <string>
#include <vector>

class JetClustering:
    public edm::EDProducer
{
    private:    
        edm::EDGetTokenT<std::vector<pat::PackedGenParticle>> _particleToken;
        std::unordered_map<std::string, edm::EDGetTokenT<std::vector<pat::PackedGenParticle>>> _ghostTokens;
        
        double _jetR;
        double _minJetPt;
        
        class ParticleInfo:
            public fastjet::PseudoJet::UserInfoBase
        {
        
            public:
                const std::unique_ptr<reco::Candidate> particle;  
                const std::string origin;  
            
                ParticleInfo(const reco::Candidate* particle, const std::string& origin="src"):
                    particle(particle->clone()),
                    origin(origin)
                {
                }
        };

    public:
        explicit JetClustering(const edm::ParameterSet& iConfig):
            _particleToken(consumes<std::vector<pat::PackedGenParticle>>(iConfig.getParameter<edm::InputTag>("src"))),
            _jetR(iConfig.getParameter<double>("jetR")),
            _minJetPt(0.1)
        {
            if (iConfig.exists("minJetPt"))
            {
                _minJetPt = iConfig.getParameter<double>("minJetPt");
            }
            
            if (iConfig.exists("ghosts"))
            {
                const edm::ParameterSet& ghostTags = iConfig.getParameter<edm::ParameterSet>("ghosts");
                const std::vector<std::string> setNames = ghostTags.getParameterNamesForType<edm::InputTag>();
                for (unsigned int iname=0; iname< setNames.size(); ++iname)
                {
                    const edm::InputTag& inputTag = ghostTags.getParameter<edm::InputTag>(setNames[iname]);
                    _ghostTokens[setNames[iname]]=consumes<std::vector<pat::PackedGenParticle>>(inputTag);
                }
            }

            produces<std::vector<plt::Jet>>();
        }
        
        virtual void produce(edm::Event& edmEvent, const edm::EventSetup& edmSetup) override
        {
            edm::Handle<std::vector<pat::PackedGenParticle>> particleCollection;
            edmEvent.getByToken(_particleToken, particleCollection);
            
            std::vector<fastjet::PseudoJet> jetInputs;
            
            for (unsigned int iparticle = 0; iparticle < particleCollection->size(); ++iparticle)
            {
                const reco::Candidate& particle = particleCollection->at(iparticle);
                jetInputs.emplace_back(particle.px(), particle.py(), particle.pz(), particle.energy());
                jetInputs.back().set_user_info(new ParticleInfo(&particle));
            }
            
            for (auto it: _ghostTokens)
            {
                edm::Handle<std::vector<pat::PackedGenParticle>> particleCollection;
                edmEvent.getByToken(it.second, particleCollection);
                
                for (unsigned int iparticle = 0; iparticle < particleCollection->size(); ++iparticle)
                {
                    const reco::Candidate& particle = particleCollection->at(iparticle);
                    //scale down the momentum
                    double scale = 1e-20/particle.p();
                    jetInputs.emplace_back(scale*particle.px(), scale*particle.py(), scale*particle.pz(), scale*particle.energy());
                    jetInputs.back().set_user_info(new ParticleInfo(&particle,it.first));
                }
            }
            
            fastjet::JetDefinition jetDefinition(fastjet::antikt_algorithm, _jetR);
            fastjet::ClusterSequence clusterSeq(jetInputs, jetDefinition);
            std::vector<fastjet::PseudoJet> inclusiveJets = sorted_by_pt(clusterSeq.inclusive_jets(_minJetPt));

            std::unique_ptr<std::vector<plt::Jet>> output(new std::vector<plt::Jet>(inclusiveJets.size()));
            
            
            for (unsigned int ijet = 0; ijet < inclusiveJets.size(); ++ijet)
            {
                const fastjet::PseudoJet& jet = inclusiveJets[ijet];

                const std::vector<fastjet::PseudoJet> jetConstituents = fastjet::sorted_by_pt(jet.constituents());
                for (unsigned int iparticle = 0; iparticle < jetConstituents.size(); ++iparticle)
                {
                    const fastjet::PseudoJet& particle = jetConstituents[iparticle];
                    const ParticleInfo& particleInfo = particle.user_info<ParticleInfo>();
                
                    if (particleInfo.origin=="src")
                    {
                        (*output)[ijet].addConstituent(*particleInfo.particle);
                    }
                    else
                    {
                        (*output)[ijet].addGhostTag(particleInfo.origin);
                    }
                }
            }
            
            edmEvent.put(std::move(output));
        }
        
        ~JetClustering()
        {
        }

        static void fillDescriptions(edm::ConfigurationDescriptions& descriptions)
        {
            edm::ParameterSetDescription desc;
            desc.setUnknown();
            descriptions.addDefault(desc);
        }
};



DEFINE_FWK_MODULE(JetClustering);
