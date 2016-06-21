
#include <memory>
#include <vector>
#include <iostream>


#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ParameterSet/interface/ParameterSetDescription.h"
#include "FWCore/ParameterSet/interface/ConfigurationDescriptions.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/Utilities/interface/InputTag.h"

#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/Common/interface/Handle.h"

#include "FWCore/Framework/interface/EDAnalyzer.h"

class TriggerTest:
    public edm::EDAnalyzer
{
    private:    
        edm::EDGetTokenT<edm::TriggerResults> token;
    
        virtual void analyze(const edm::Event&, const edm::EventSetup&);

    public:
        explicit TriggerTest(const edm::ParameterSet&);

        static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

};


//
// constructors and destructor
//
TriggerTest::TriggerTest(const edm::ParameterSet& iConfig):
    token(consumes<edm::TriggerResults>(edm::InputTag("TriggerResults","","TestProcess")))
{
}

// ------------ method called to produce the data  ------------
void
TriggerTest::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{

    edm::Handle<edm::TriggerResults> triggerResults;
    iEvent.getByToken(token, triggerResults);
    std::cout<<"available trigger names ("<<triggerResults->getTriggerNames().size()<<"): ";
    for (const std::string& trigName: triggerResults->getTriggerNames())
    {
        std::cout<<trigName<<",";
    }
    std::cout<<std::endl;
    
}


// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
TriggerTest::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
    //The following says we do not know what parameters are allowed so do no validation
    // Please change this to state exactly what you do use, even if it is no parameters
    edm::ParameterSetDescription desc;
    desc.setUnknown();
    descriptions.addDefault(desc);
}



//define this as a plug-in
DEFINE_FWK_MODULE(TriggerTest);
