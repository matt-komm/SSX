#include "pxl/hep.hh"
#include "pxl/core.hh"
#include "pxl/core/macros.hh"
#include "pxl/core/PluginManager.hh"
#include "pxl/modules/Module.hh"
#include "pxl/modules/ModuleFactory.hh"

#include <string>
#include <vector>
#include <array>
#include <unordered_map>

static pxl::Logger logger("PLObjects");

class PLObjects:
    public pxl::Module
{
    private:
    
        std::string _eventViewName;

        pxl::Source* _outputSource;
        pxl::Source* _noLeptonSource;
        
        std::string _leptonInputName;
        std::string _selectedLeptonName;
        int64_t _leptonPdgId;
        double _leptonPt;
        double _leptonEta;
        
        std::string _jetInputName;
        std::string _selectedJetName;
        double _jetPt;
        double _jetEta;
        double _dR;
        
        std::string _selectedBjetName;
        double _bJetEta;
        double _bHadronEta;
        
        std::string _neutrinoInputName;
        std::string _selectedMETName;
        
        
    public:
        PLObjects():
            Module(),
            _eventViewName("PTR"),
            _leptonInputName("Lepton"),
            _selectedLeptonName("TightLepton"),
            _leptonPdgId(13),
            _leptonPt(26),
            _leptonEta(2.4),
            _jetInputName("Jet"),
            _selectedJetName("SelectedLJet"),
            _jetPt(40.0),
            _jetEta(4.7),
            _dR(-1),
            _selectedBjetName("SelectedBJet"),
            _bJetEta(2.4),
            _bHadronEta(2.4),
            _neutrinoInputName("Neutrino"),
            _selectedMETName("MET")
        {
            addSink("input", "input");
            addOption("event view name", "", _eventViewName);

            _noLeptonSource = addSource("noLepton","noLepton");
            _outputSource = addSource("output","output");
            
            
            addOption("lepton input name", "", _leptonInputName);
            addOption("selected lepton name", "", _selectedLeptonName);
            addOption("lepton pdgId", "", _leptonPdgId);
            addOption("lepton pt", "", _leptonPt);
            addOption("lepton eta", "", _leptonEta);
            
            addOption("jet input name", "", _jetInputName);
            addOption("selected jet name", "", _selectedJetName);
            addOption("jet pt", "", _jetPt);
            addOption("jet eta", "", _jetEta);
            addOption("lepton-jet dR", "", _dR);
            
            addOption("selected bjet name", "", _selectedBjetName);
            addOption("bjet eta", "", _bJetEta);
            addOption("B hadron eta", "", _bHadronEta);
            
            addOption("neutrino input name","",_neutrinoInputName);
            addOption("MET name", "",_selectedMETName);

        }

        ~PLObjects()
        {
        }

        // every Module needs a unique type
        static const std::string &getStaticType()
        {
            static std::string type ("PLObjects");
            return type;
        }

        // static and dynamic methods are needed
        const std::string &getType() const
        {
            return getStaticType();
        }

        bool isRunnable() const
        {
            // this module does not provide events, so return false
            return false;
        }

        void initialize() throw (std::runtime_error)
        {
        }

        void beginJob() throw (std::runtime_error)
        {
            getOption("event view name", _eventViewName);
            
            getOption("lepton input name", _leptonInputName);
            getOption("selected lepton name", _selectedLeptonName);
            getOption("lepton pdgId", _leptonPdgId);
            getOption("lepton pt", _leptonPt);
            getOption("lepton eta", _leptonEta);
            
            getOption("jet input name", _jetInputName);
            getOption("selected jet name", _selectedJetName);
            getOption("jet pt", _jetPt);
            getOption("jet eta", _jetEta);
            getOption("lepton-jet dR", _dR);
            
            getOption("selected bjet name", _selectedBjetName);
            getOption("bjet eta", _bJetEta);
            getOption("B hadron eta", _bHadronEta);
            
            getOption("neutrino input name",_neutrinoInputName);
            getOption("MET name",_selectedMETName);
        
        }
        
        bool analyse(pxl::Sink *sink) throw (std::runtime_error)
        {
            
            try
            {
                pxl::Event *event  = dynamic_cast<pxl::Event*>(sink->get());
                if (event)
                {
                    std::vector<pxl::EventView*> eventViews;
                    event->getObjectsOfType(eventViews);
                    
                    for (auto ev: eventViews)
                    {
                        if (ev->getName()==_eventViewName)
                        {
                            std::vector<pxl::Particle*> particles;
                            ev->getObjectsOfType(particles);
                            
                            std::vector<pxl::Particle*> leptons;
                            std::vector<pxl::Particle*> jets;
                            
                            pxl::Particle* met = ev->create<pxl::Particle>();
                            met->setName(_selectedMETName);
                            double met_px = 0;
                            double met_py = 0;
                            
                            for (auto particle: particles)
                            {
                                if (particle->getName()==_leptonInputName
                                    and std::abs(particle->getPdgNumber())==_leptonPdgId
                                    and particle->getPt()>_leptonPt
                                    and std::fabs(particle->getEta())<_leptonEta
                                   )
                                {
                                    particle->setName(_selectedLeptonName);
                                    leptons.push_back(particle);
                                }
                                else if (particle->getName()==_jetInputName
                                    and particle->getPt()>_jetPt
                                    and std::fabs(particle->getEta())<_jetEta
                                   )
                                {
                                    particle->setName(_selectedJetName);
                                    jets.push_back(particle);
                                }
                                else if (particle->getName()==_neutrinoInputName)
                                {
                                    met_px+=particle->getPx();
                                    met_py+=particle->getPy();
                                    ev->removeObject(particle);
                                }
                                else
                                {
                                    ev->removeObject(particle);
                                }
                            }
                            ev->setUserRecord("n"+_selectedLeptonName,leptons.size());
                            met->setP4(met_px, met_py, 0.0, std::sqrt(met_px*met_px+met_py*met_py));
                                                        
                            
                            
                            for (auto itjet = jets.begin(); itjet!=jets.end();)
                            {
                                double minDR = 100.0;
                                double minEta = 100.0;
                                double minPhi = 100.0;
                                for (auto lepton: leptons)
                                {
                                    minDR = std::min(minDR,(*itjet)->getVector().deltaR(&lepton->getVector()));
                                    minEta = std::min(minEta,std::fabs((*itjet)->getVector().deltaEta(&lepton->getVector())));
                                    minPhi = std::min(minPhi,std::fabs((*itjet)->getVector().deltaPhi(&lepton->getVector())));
                                }
                                if (_dR>0 and minDR<_dR)
                                {
                                    itjet = jets.erase(itjet);
                                }
                                else
                                {
                                    (*itjet)->setUserRecord("dRcleanMin",minDR);
                                    (*itjet)->setUserRecord("dPhicleanMin",minEta);
                                    (*itjet)->setUserRecord("dEtacleanMin",minPhi);
                                    ++itjet;
                                }
                            }
                            
                            std::vector<pxl::Particle*> bjets;
                            for (auto jet: jets)
                            {
                                if (std::abs(jet->getPdgNumber())==5
                                    and std::fabs(jet->getEta())<_bJetEta
                                   )
                                {
                                    jet->setName(_selectedBjetName);
                                    bjets.push_back(jet);
                                }
                            }
                            ev->setUserRecord("n"+_selectedJetName,jets.size());
                            ev->setUserRecord("n"+_selectedBjetName,bjets.size());
                            
                            if (leptons.size()!=1)
                            {
                                _noLeptonSource->setTargets(event);
                                return _noLeptonSource->processTargets();
                            }
                            else
                            {
                                _outputSource->setTargets(event);
                                return _outputSource->processTargets();
                            }
                        }
                    }
                    _noLeptonSource->setTargets(event);
                    return _noLeptonSource->processTargets();
                }
            }
            catch(std::exception &e)
            {
                throw std::runtime_error(getName()+": "+e.what());
            }
            catch(...)
            {
                throw std::runtime_error(getName()+": unknown exception");
            }

            logger(pxl::LOG_LEVEL_ERROR , "Analysed event is not an pxl::Event !");
            return false;
        }
        
        void endJob() throw (std::runtime_error)
        {
        }

        void shutdown() throw(std::runtime_error)
        {
        }

        void destroy() throw (std::runtime_error)
        {
            delete this;
        }
};


PXL_MODULE_INIT(PLObjects)
PXL_PLUGIN_INIT
