// system include files
#include <memory>
#include <vector>
#include <regex>
// user include files

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/stream/EDProducer.h"
#include "FWCore/Framework/interface/one/EDProducer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/ESHandle.h"

#include "DataFormats/Common/interface/ValueMap.h"

#include "DataFormats/PatCandidates/interface/Muon.h"

#include "DataFormats/Math/interface/deltaR.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/PatCandidates/interface/TriggerObjectStandAlone.h"
#include "DataFormats/PatCandidates/interface/PackedTriggerPrescales.h"

template<class TYPE>
class TriggerMatcher:
    public edm::stream::EDProducer<>
{
    private:    
        edm::InputTag _triggerResultsInputTag;
        edm::EDGetTokenT<edm::TriggerResults> _triggerResultsToken;
    
        edm::InputTag _triggerObjectStandAloneInputTag;
        edm::EDGetTokenT<std::vector<pat::TriggerObjectStandAlone>> _triggerObjectStandAloneToken;
        
        edm::InputTag _recoInputTag;
        edm::EDGetTokenT<std::vector<TYPE>> _recoToken;
        
        double _dR2match;
        
        std::vector<std::pair<std::string,std::regex>> _flagList;
        
        
        virtual void produce( edm::Event& iEvent, const edm::EventSetup& iSetup)
        {
            edm::Handle<edm::TriggerResults> triggerResultsProduct;
            iEvent.getByToken(_triggerResultsToken,triggerResultsProduct);
            
            const edm::TriggerNames& triggerNames = iEvent.triggerNames(*triggerResultsProduct);

            edm::Handle<std::vector<pat::TriggerObjectStandAlone>> triggerObjectStandAloneProduct;
            iEvent.getByToken(_triggerObjectStandAloneToken, triggerObjectStandAloneProduct);
            
            edm::Handle<std::vector<TYPE>> recoObjectsProduct;
            iEvent.getByToken(_recoToken, recoObjectsProduct);
            
            std::vector<pat::TriggerObjectStandAlone> unpackedTriggerObjs;
            for (pat::TriggerObjectStandAlone trigObj: *triggerObjectStandAloneProduct)
            {
                trigObj.unpackPathNames(triggerNames);
                unpackedTriggerObjs.emplace_back(trigObj);
            }
            
            std::vector<std::unique_ptr<edm::ValueMap<bool>>> resultList;
            std::vector<std::vector<bool>> resultFlagList;
            for (unsigned int iflagList = 0; iflagList < _flagList.size(); ++iflagList)
            {
                resultList.emplace_back(new edm::ValueMap<bool>());
                resultFlagList.emplace_back(recoObjectsProduct->size(),false);
            }
            
            for (unsigned int iobj = 0; iobj < recoObjectsProduct->size(); ++iobj)
            {
                const TYPE& recoObj = recoObjectsProduct->at(iobj);
                for (pat::TriggerObjectStandAlone trigObj: unpackedTriggerObjs)
                {
                    const double dR2 = reco::deltaR2(trigObj,recoObj);
                    if (dR2<_dR2match) 
                    {
                        for (unsigned int iflagList = 0; iflagList < _flagList.size(); ++iflagList)
                        {
                            for (std::string s: trigObj.pathNames())
                            { 
                                if (std::regex_match(s,_flagList[iflagList].second))
                                {
                                    resultFlagList[iflagList][iobj] = true;
                                    break;
                                }
                            } 
                        }
                    }
                }
            }
            
            for (unsigned int iflagList = 0; iflagList < _flagList.size(); ++iflagList)
            {
                edm::ValueMap<bool>::Filler filler(*resultList[iflagList]);
                filler.insert(recoObjectsProduct,resultFlagList[iflagList].begin(),resultFlagList[iflagList].end());
                filler.fill();
                iEvent.put(std::move(resultList[iflagList]),_flagList[iflagList].first);
            }
        }

    public:
        explicit TriggerMatcher(const edm::ParameterSet& iConfig):
            _triggerResultsInputTag(iConfig.getParameter<edm::InputTag>("triggerResult")),
            _triggerResultsToken(consumes<edm::TriggerResults>(_triggerResultsInputTag)),

            _triggerObjectStandAloneInputTag(iConfig.getParameter<edm::InputTag>("triggerObjects")),
            _triggerObjectStandAloneToken(consumes<std::vector<pat::TriggerObjectStandAlone>>(_triggerObjectStandAloneInputTag)),
        
            _recoInputTag(iConfig.getParameter<edm::InputTag>("recoObjects")),
            _recoToken(consumes<std::vector<TYPE>>(_recoInputTag))
            
        {
            _dR2match = std::pow(iConfig.getParameter<double>("dR"),2);
            
            const edm::ParameterSet& flagConfigs = iConfig.getParameter<edm::ParameterSet>("flags");
            const std::vector<std::string> flagConfigNames = flagConfigs.getParameterNamesForType<std::string>();
            for (unsigned int iflag=0; iflag< flagConfigNames.size(); ++iflag)
            {
                const std::string& name = flagConfigNames[iflag];
                _flagList.push_back(std::make_pair(name,std::regex(flagConfigs.getParameter<std::string>(name))));
            
                produces<edm::ValueMap<bool>>(name);
            }
        }
        
        virtual ~TriggerMatcher()
        {
        }

        static void fillDescriptions(edm::ConfigurationDescriptions& descriptions)
        {
            //The following says we do not know what parameters are allowed so do no validation
            // Please change this to state exactly what you do use, even if it is no parameters
            edm::ParameterSetDescription desc;
            desc.setUnknown();
            descriptions.addDefault(desc);
        }

};

typedef TriggerMatcher<pat::Muon> TriggerMatcherMuons;

DEFINE_FWK_MODULE (TriggerMatcherMuons);

