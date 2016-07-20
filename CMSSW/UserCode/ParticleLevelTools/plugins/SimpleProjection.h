
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/ESHandle.h"

#include "DataFormats/Candidate/interface/Candidate.h"

#include <vector>
#include <unordered_map>
#include <cstddef>
#include <memory>

template<class OBJECT, class HASHFCT>
class SimpleProjection:
    public edm::EDProducer
{
    private:
        static HASHFCT _hashfct;
        
        std::vector<edm::EDGetTokenT<std::vector<OBJECT>>> _combineTokens;
        std::vector<edm::EDGetTokenT<std::vector<OBJECT>>> _excludeTokens;
        

    public:
        explicit SimpleProjection(const edm::ParameterSet& config)
        {
            for (const edm::InputTag& inputTag: config.getParameter<std::vector<edm::InputTag>>("combine"))
            {
                _combineTokens.push_back(consumes<std::vector<OBJECT>>(inputTag));
            }
            if (config.exists("exclude"))
            {
                for (const edm::InputTag& inputTag: config.getParameter<std::vector<edm::InputTag>>("exclude"))
                {
                    _excludeTokens.push_back(consumes<std::vector<OBJECT>>(inputTag));
                }
            }
            produces<std::vector<OBJECT>>();
        }
        ~SimpleProjection()
        {
        }
        
        virtual void produce(edm::Event& edmEvent, const edm::EventSetup& edmSetup)
        {
            std::unordered_map<std::size_t,const OBJECT*> _finalObjects;
            
            //add all objects together
            for (unsigned int iToken = 0; iToken < _combineTokens.size(); ++iToken)
            {
                edm::Handle<std::vector<OBJECT>> particleCollection;
                edmEvent.getByToken(_combineTokens[iToken], particleCollection);
                
                for (unsigned int iParticle = 0; iParticle < particleCollection->size(); ++iParticle)
                {
                    _finalObjects[_hashfct(&particleCollection->at(iParticle))] = &particleCollection->at(iParticle);
                } 
            }
            
            //remove excluded objects
            for (unsigned int iToken = 0; iToken < _excludeTokens.size(); ++iToken)
            {
                edm::Handle<std::vector<OBJECT>> particleCollection;
                edmEvent.getByToken(_excludeTokens[iToken], particleCollection);
                
                for (unsigned int iParticle = 0; iParticle < particleCollection->size(); ++iParticle)
                {
                    auto it = _finalObjects.find(_hashfct(&particleCollection->at(iParticle)));
                    if (it!=_finalObjects.cend())
                    {
                        _finalObjects.erase(it);
                    }
                } 
            }
            
            //create final list and clone all objects
            std::unique_ptr<std::vector<OBJECT>> output(new std::vector<OBJECT>());
            for (auto it: _finalObjects)
            {
                output->emplace_back(*it.second);
            }
            
            edmEvent.put(std::move(output));
        }

        static void fillDescriptions(edm::ConfigurationDescriptions& descriptions)
        {
            edm::ParameterSetDescription desc;
            desc.setUnknown();
            descriptions.addDefault(desc);
        }

};

