// system include files
#include <memory>
#include <vector>
// user include files

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/stream/EDProducer.h"
#include "FWCore/Framework/interface/one/EDProducer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/ESHandle.h"

#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/GsfTrackReco/interface/GsfTrack.h"
#include "DataFormats/VertexReco/interface/Vertex.h"

#include "EgammaAnalysis/ElectronTools/interface/ElectronEnergyShifter.h"

class ElectronRegressionUncertainties:
    public edm::one::EDProducer<>
    
{
    private:    
        edm::InputTag _electronInputTag;
        edm::EDGetTokenT<edm::View<reco::GsfElectron>> _electronToken;
        
        bool _isMC;
    
        ElectronEnergyShifter _energyShifter;
    
        virtual void beginJob() override;
        virtual void produce(edm::Event& iEvent, const edm::EventSetup& iSetup);
        virtual void endJob() override;
        
        
        template<typename HANDLE, typename TYPE>
        void writeValueMap(edm::Event &out, const HANDLE& handle, const std::vector<TYPE> values, const std::string &name) const 
        {
             typedef edm::ValueMap<TYPE> Map;
             std::unique_ptr<Map> map(new Map());
             typename Map::Filler filler(*map);
             filler.insert(handle, values.begin(), values.end());
             filler.fill();
             out.put(std::move(map), name);
        }
 

    public:
        explicit ElectronRegressionUncertainties(const edm::ParameterSet&);
        ~ElectronRegressionUncertainties();

        static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

};


//
// constructors and destructor

//
ElectronRegressionUncertainties::ElectronRegressionUncertainties(const edm::ParameterSet& iConfig):
    _electronInputTag(iConfig.getParameter<edm::InputTag>("src")),
    _electronToken(consumes<edm::View<reco::GsfElectron>>(_electronInputTag)),
    _isMC(iConfig.getParameter<bool>("isMC"))
{
    _energyShifter.setConsume(iConfig.getParameter<edm::ParameterSet>("egmUncertaintyConfig"), consumesCollector());
    
    produces<edm::ValueMap<double>>("energyUp");
    produces<edm::ValueMap<double>>("energyDown");
}


ElectronRegressionUncertainties::~ElectronRegressionUncertainties()
{
}

// ------------ method called once each job just before starting event loop  ------------
void 
ElectronRegressionUncertainties::beginJob()
{
}

// ------------ method called to produce the data  ------------
void
ElectronRegressionUncertainties::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
    edm::Handle<edm::View<reco::GsfElectron>> electronCollectionProduct;
    iEvent.getByToken(_electronToken, electronCollectionProduct);
    
    _energyShifter.setEvent(iEvent);
    
    std::vector<double> energyUp(electronCollectionProduct->size(),0.0);
    std::vector<double> energyDown(electronCollectionProduct->size(),0.0);
    
    for (unsigned int iele = 0; iele < electronCollectionProduct->size(); ++iele)
    {
        auto electron = electronCollectionProduct->refAt(iele);
        reco::GsfElectron electronUp;
        reco::GsfElectron electronDown;
        
        if (_isMC)
        {
            electronUp = _energyShifter.getSimpleShiftedObject(electron, EGMSmearer::ResolutionUp);
            electronDown = _energyShifter.getSimpleShiftedObject(electron, EGMSmearer::ResolutionDown);
        }
        else
        {
            electronUp = _energyShifter.getSimpleShiftedObject(electron, EGMSmearer::ScaleUp);
            electronDown = _energyShifter.getSimpleShiftedObject(electron, EGMSmearer::ScaleDown);
        }
        energyUp[iele] = electronUp.energy();
        energyDown[iele] = electronDown.energy();
    }
    
    writeValueMap(iEvent,electronCollectionProduct,energyUp,"energyUp");
    writeValueMap(iEvent,electronCollectionProduct,energyDown,"energyDown");
}



// ------------ method called once each job just after ending the event loop  ------------
void 
ElectronRegressionUncertainties::endJob() {
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
ElectronRegressionUncertainties::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}



//define this as a plug-in
DEFINE_FWK_MODULE(ElectronRegressionUncertainties);
