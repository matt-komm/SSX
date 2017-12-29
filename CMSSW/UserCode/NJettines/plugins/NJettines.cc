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
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/Electron.h"

#include "vdt/vdtMath.h"


class NJettines:
    public edm::stream::EDProducer<>
{
    private:    
        edm::InputTag _pfCandidatesTag;
        edm::EDGetTokenT<std::vector<pat::PackedCandidate>> _pfCandidatesToken;
    
        edm::InputTag _muonsTag;
        edm::EDGetTokenT<std::vector<pat::Muon>> _muonsToken;
        
        edm::InputTag _electronsTag;
        edm::EDGetTokenT<std::vector<pat::Electron>> _electronsToken;
        
        edm::InputTag _jetsTag;
        edm::EDGetTokenT<std::vector<pat::Jet>> _jetsToken;
        
        
        
        virtual void produce( edm::Event& iEvent, const edm::EventSetup& iSetup)
        {
            edm::Handle<std::vector<pat::PackedCandidate>> pfCandidates;
            iEvent.getByToken(_pfCandidatesToken,pfCandidates);
            
            edm::Handle<std::vector<pat::Muon>> muons;
            iEvent.getByToken(_muonsToken,muons);
            
            edm::Handle<std::vector<pat::Electron>> electrons;
            iEvent.getByToken(_electronsToken,electrons);
            
            edm::Handle<std::vector<pat::Jet>> jets;
            iEvent.getByToken(_jetsToken,jets);
            
            std::vector<reco::CandidatePtr> leptonFootprints;
            for (unsigned int imuon = 0; imuon < muons->size(); ++imuon)
            {
                for (unsigned int isrcCand = 0; isrcCand < muons->at(imuon).numberOfSourceCandidatePtrs(); ++isrcCand)
                {
                    leptonFootprints.push_back(muons->at(imuon).sourceCandidatePtr(isrcCand));
                }
            }
            for (unsigned int ielectron = 0; ielectron < electrons->size(); ++ielectron)
            {
                for (unsigned int isrcCand = 0; isrcCand < electrons->at(ielectron).numberOfSourceCandidatePtrs(); ++isrcCand)
                {
                    leptonFootprints.push_back(electrons->at(ielectron).sourceCandidatePtr(isrcCand));
                }
            }
            
            std::unique_ptr<double> njettines(new double(0));
            
            //std::unordered_map<reco::PFCandidatePtr,pat::Jet> constitutentMap;
            
            
            
            for (unsigned int ipfCand = 0; ipfCand < pfCandidates->size(); ++ipfCand)
            {
                if (std::find(leptonFootprints.begin(), leptonFootprints.end(), reco::CandidatePtr(pfCandidates,ipfCand)) != leptonFootprints.end())
                {
                    continue;
                }
                const pat::PackedCandidate& pfCandidate = pfCandidates->at(ipfCand);
                
                /*
                for (unsigned int ijet = 0; ijet < jets->size(); ++ijet)
                {
                    reco::Candidate::LorentzVector vec(0,0,0,0);
                    const std::vector<reco::PFCandidatePtr>& jetConstituents = jets->at(ijet).getPFConstituents(); 
                    for (unsigned int iconstituent = 0; iconstituent < jetConstituents.size(); ++iconstituent)
                    {
                        vec+=jetConstituents[iconstituent]->p4();
                    }
                    
                    std::cout<<"jet "<<jets->at(ijet).p4()<<std::endl;
                    std::cout<<"constituents "<<vec<<std::endl;
                    std::cout<<std::endl;
                }
                */
                
                const double dA = pfCandidate.pt()*vdt::fast_expf(-pfCandidate.eta());
                const double dB = pfCandidate.pt()*vdt::fast_expf(pfCandidate.eta());
                double minD = std::min(dA,dB);
                for (unsigned int ijet = 0; ijet < jets->size(); ++ijet)
                {
                    const double dJ = pfCandidate.pt()*2.0*(
                        std::cosh(pfCandidate.eta()-jets->at(ijet).eta())
                        -vdt::fast_cosf(reco::deltaPhi(pfCandidate.phi(),jets->at(ijet).phi()))
                    );
                    minD = std::min(minD,dJ);
                }
                *njettines+=minD;
                
            }
            
            iEvent.put<double>(std::move(njettines));
        }

    public:
        explicit NJettines(const edm::ParameterSet& iConfig):
            _pfCandidatesTag(iConfig.getParameter<edm::InputTag>("pfCand")),
            _pfCandidatesToken(consumes<std::vector<pat::PackedCandidate>>(_pfCandidatesTag)),

            _muonsTag(iConfig.getParameter<edm::InputTag>("muons")),
            _muonsToken(consumes<std::vector<pat::Muon>>(_muonsTag)),
            
            _electronsTag(iConfig.getParameter<edm::InputTag>("electrons")),
            _electronsToken(consumes<std::vector<pat::Electron>>(_electronsTag)),
            
            _jetsTag(iConfig.getParameter<edm::InputTag>("jets")),
            _jetsToken(consumes<std::vector<pat::Jet>>(_jetsTag))
            
        {
            
            produces<double>();
        }
        
        virtual ~NJettines()
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

DEFINE_FWK_MODULE (NJettines);


