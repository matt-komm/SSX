#ifndef __ParticleLevelTools_Jet_H__
#define __ParticleLevelTools_Jet_H__

#include "DataFormats/Math/interface/LorentzVector.h"
#include "DataFormats/Candidate/interface/Candidate.h"

#include <vector>
#include <unordered_map>

namespace plt
{

class Jet
{
    public:
        typedef math::XYZTLorentzVector LorentzVector;
        
        struct Constituent
        {
            const LorentzVector p4;
            const int charge;
            const int pdgId; 
            
            Constituent(const reco::Candidate& candidate):
                p4(candidate.p4()),
                charge(candidate.charge()),
                pdgId(candidate.pdgId())
            {
            }
        };

    protected:
        LorentzVector _lorentzVector;
        
        int _charge;
    
        LorentzVector _electronEnergy;
        LorentzVector _muonEnergy;
        LorentzVector _photonEnergy;
        LorentzVector _neutrinoEnergy;
        
        std::vector<Constituent> _constituents;
        
        std::unordered_map<std::string,unsigned int> _ghostTags;
        
    public:
        Jet();
        
        void addGhostTag(const std::string& type="ghostTag")
        {
            _ghostTags[type]+=1;
        }
        
        std::vector<std::string> getGhostTagTypes() const
        {
            std::vector<std::string> names;
            for (auto it: _ghostTags)
            {
                names.push_back(it.first);
            }
            return names;
        }
        
        inline unsigned int getNumberOfGhostTags(const std::string& type="ghostTag") const
        {
            auto it = _ghostTags.find(type);
            if (it==_ghostTags.cend())
            {
                return 0;
            }
            else
            {
                return it->second;
            }
        }
        
        void addConstituent(const reco::Candidate& candidate);
        
        inline const LorentzVector& p4() const
        {
            return _lorentzVector;
        }
        
        inline int charge() const
        {
            return _charge;
        }
       
        double jetCharge(double exp=1.0) const;
        
        inline double electronFraction() const
        {
            return (_lorentzVector.px()*_electronEnergy.px()+_lorentzVector.py()*_electronEnergy.py()+_lorentzVector.pz()*_electronEnergy.pz())/_lorentzVector.P2();
        }
        
        inline double muonFraction() const
        {
            return (_lorentzVector.px()*_muonEnergy.px()+_lorentzVector.py()*_muonEnergy.py()+_lorentzVector.pz()*_muonEnergy.pz())/_lorentzVector.P2();
        }
        
        inline double photonFraction() const
        {
            return (_lorentzVector.px()*_photonEnergy.px()+_lorentzVector.py()*_photonEnergy.py()+_lorentzVector.pz()*_photonEnergy.pz())/_lorentzVector.P2();
        }
        
        inline double neutrinoFraction() const
        {
            return (_lorentzVector.px()*_neutrinoEnergy.px()+_lorentzVector.py()*_neutrinoEnergy.py()+_lorentzVector.pz()*_neutrinoEnergy.pz())/_lorentzVector.P2();
        }
        
        inline double hadronFraction() const
        {
            LorentzVector hadronEnergy = _lorentzVector-_electronEnergy-_muonEnergy-_photonEnergy-_neutrinoEnergy;
            return (_lorentzVector.px()*hadronEnergy.px()+_lorentzVector.py()*hadronEnergy.py()+_lorentzVector.pz()*hadronEnergy.pz())/_lorentzVector.P2();
        }
};

}

#endif
