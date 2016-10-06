#include <algorithm>
#include <fstream>
#include <set>
#include <sstream>
#include <streambuf>
#include <regex>

#include "pxl/hep.hh"
#include "pxl/core.hh"
#include "pxl/core/macros.hh"
#include "pxl/core/PluginManager.hh"
#include "pxl/modules/Module.hh"
#include "pxl/modules/ModuleFactory.hh"

static pxl::Logger logger("PLSelection");



class PLSelection:
    public pxl::Module
{
    private:
        pxl::Source* _selectedSource;

        std::regex _inputEventViewName;
        std::string _inputName;
        std::vector<std::string> _cleaningNames;
        std::string _outputName;
  
        
        double _pTMinTight;
        double _etaMaxTight;
        
        double _dRclean;
        
        double _muonFractionRangeMin;
        double _muonFractionRangeMax;
        
        double _electronFractionRangeMin;
        double _electronFractionRangeMax;
        
        double _photonFractionRangeMin;
        double _photonFractionRangeMax;
        
        double _hadronFractionRangeMin;
        double _hadronFractionRangeMax;
        
        double _neutrinoFractionRangeMin;
        double _neutrinoFractionRangeMax;
        
        int64_t _bHadronInstancesMin;
        int64_t _bHadronInstancesMax;

        bool _clear;
        
    public:
        PLSelection():

            Module(),
            _inputName("Lepton"),
            _outputName("TightMuon"),

            _pTMinTight(24),
            _etaMaxTight(2.4),
            
            _dRclean(0.3),
            
            _muonFractionRangeMin(0.5),
            _muonFractionRangeMax(1.0),
            
            _electronFractionRangeMin(0.0),
            _electronFractionRangeMax(1.0),
            
            _photonFractionRangeMin(0.0),
            _photonFractionRangeMax(1.0),
            
            _hadronFractionRangeMin(0.0),
            _hadronFractionRangeMax(1.0),
            
            _neutrinoFractionRangeMin(0.0),
            _neutrinoFractionRangeMax(1.0),
            
            _bHadronInstancesMin(0),
            _bHadronInstancesMax(100),
            
            _clear(false)

        {
            addSink("input", "input");
            _selectedSource = addSource("selected", "selected");

            addOption("input event view","","PL[A-Za-z0-9_]+");
            addOption("input particle name","",_inputName);
            addOption("cleaning particle names","",_cleaningNames);
            addOption("dR cleaning","",_dRclean);
            addOption("selected output particle name","",_outputName);

            addOption("Minimum pT","",_pTMinTight);
            addOption("Maximum Eta","",_etaMaxTight);
            
            addOption("min Muon Fraction Range","",_muonFractionRangeMin);
            addOption("max Muon Fraction Range","",_muonFractionRangeMax);
                        
            addOption("min Electron Fraction Range","",_electronFractionRangeMin);
            addOption("max Electron Fraction Range","",_electronFractionRangeMax);
            
            addOption("min Photon Fraction Range","",_photonFractionRangeMin);
            addOption("max Photon Fraction Range","",_photonFractionRangeMax);
            
            addOption("min Hadron Fraction Range","",_hadronFractionRangeMin);
            addOption("max Hadron Fraction Range","",_hadronFractionRangeMax);
            
            addOption("min Neutrino Fraction Range","",_neutrinoFractionRangeMin);
            addOption("max Neutrino Fraction Range","",_neutrinoFractionRangeMax);
            
            addOption("min BHadron instances","",_bHadronInstancesMin);
            addOption("max BHadron instances","",_bHadronInstancesMax);
            
            addOption("clear event","will copy all instances found otherwise for vetoing",_clear);
        }

        ~PLSelection()
        {
        }

        // every Module needs a unique type
        static const std::string &getStaticType()
        {
            static std::string type ("PLSelection");
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
            std::string evname;
            getOption("input event view",evname);
            _inputEventViewName = evname;
            getOption("input particle name",_inputName);
            getOption("cleaning particle names",_cleaningNames);
            getOption("dR cleaning",_dRclean);
            getOption("selected output particle name",_outputName);

            getOption("Minimum pT",_pTMinTight);
            getOption("Maximum Eta",_etaMaxTight);
            
            getOption("min Muon Fraction Range",_muonFractionRangeMin);
            getOption("max Muon Fraction Range",_muonFractionRangeMax);
                        
            getOption("min Electron Fraction Range",_electronFractionRangeMin);
            getOption("max Electron Fraction Range",_electronFractionRangeMax);
            
            getOption("min Photon Fraction Range",_photonFractionRangeMin);
            getOption("max Photon Fraction Range",_photonFractionRangeMax);
            
            getOption("min Hadron Fraction Range",_hadronFractionRangeMin);
            getOption("max Hadron Fraction Range",_hadronFractionRangeMax);
            
            getOption("min Neutrino Fraction Range",_neutrinoFractionRangeMin);
            getOption("max Neutrino Fraction Range",_neutrinoFractionRangeMax);
            
            getOption("min BHadron instances",_bHadronInstancesMin);
            getOption("max BHadron instances",_bHadronInstancesMax);
            
            getOption("clear event",_clear);
        }

        bool passesTightCriteria(pxl::Particle* particle)
        {
            if (not (particle->getPt()>_pTMinTight))
            {
                return false;
            }
            
            if (not (fabs(particle->getEta())<_etaMaxTight))
            {
                return false;
            }
            
            auto to_range = [](float x) {return std::min(std::max(x,0.0f),1.0f);};
            
            const float muonFraction = to_range(particle->getUserRecord("muonFraction").toFloat());
            if ((muonFraction<_muonFractionRangeMin) or (muonFraction>_muonFractionRangeMax))
            {
                return false;
            }
            
            const float electronFraction = to_range(particle->getUserRecord("electronFraction").toFloat());
            if ((electronFraction<_electronFractionRangeMin) or (electronFraction>_electronFractionRangeMax))
            {
                return false;
            }
            
            const float photonFraction = to_range(particle->getUserRecord("photonFraction").toFloat());
            if ((photonFraction<_photonFractionRangeMin) or (photonFraction>_photonFractionRangeMax))
            {
                return false;
            }
        
            const float hadronFraction = to_range(particle->getUserRecord("hadronFraction").toFloat());
            if ((hadronFraction<_hadronFractionRangeMin) or (hadronFraction>_hadronFractionRangeMax))
            {
                return false;
            }
            
            const float neutrinoFraction = to_range(particle->getUserRecord("neutrinoFraction").toFloat());
            if ((neutrinoFraction<_neutrinoFractionRangeMin) or (neutrinoFraction>_neutrinoFractionRangeMax))
            {
                return false;
            }

            const int bHadrons = particle->hasUserRecord("bHadrons")?particle->getUserRecord("bHadrons").toUInt32():0;
            {
                if ((bHadrons<_bHadronInstancesMin) or (bHadrons>_bHadronInstancesMax))
                {
                    return false;
                }
            }
            
            return true;
        }

        bool analyse(pxl::Sink *sink) throw (std::runtime_error)
        {
            try
            {
                pxl::Event *event  = dynamic_cast<pxl::Event *> (sink->get());
                if (event)
                {
                    std::vector<pxl::EventView*> eventViews;
                    event->getObjectsOfType(eventViews);

                    for (unsigned ieventView=0; ieventView<eventViews.size();++ieventView)
                    {
                        if (std::regex_match(eventViews[ieventView]->getName(),_inputEventViewName))
                        {
                            pxl::EventView* inputEV = eventViews[ieventView];
                            
                            std::vector<pxl::Particle*> particles;
                            inputEV->getObjectsOfType(particles);
                            
                            std::vector<pxl::Particle*> particlesSelected;
                            std::vector<pxl::Particle*> cleaningParticles;
                            std::vector<pxl::Particle*> particlesUnselected;

                            for (unsigned iparticle=0; iparticle<particles.size();++iparticle)
                            {
                                pxl::Particle* particle = particles[iparticle];

                                if (particle->getName()==_inputName) 
                                {
                                    if (passesTightCriteria(particle))
                                    {
                                        particlesSelected.push_back(particle);
                                    }
                                    else if (_clear)
                                    {
                                        particlesUnselected.push_back(particle);
                                    }
                                }
                                else if (_dRclean>0.0 && std::find(_cleaningNames.begin(),_cleaningNames.end(),particle->getName())!=_cleaningNames.end())
                                {
                                    cleaningParticles.push_back(particle);
                                }
                            }
                            
                            //make dR cleaning
                            if (_dRclean>0.0)
                            {
                                for (auto it = particlesSelected.begin(); it!=particlesSelected.end();)
                                {
                                    bool cleaned = false;
                                    for (auto cleanP: cleaningParticles)
                                    {
                                        if (cleanP->getVector().deltaR(&(*it)->getVector())<_dRclean)
                                        {
                                            particlesUnselected.push_back(*it);
                                            particlesSelected.erase(it);
                                            
                                            cleaned = true;
                                            break;
                                        }
                                    }
                                    if (!cleaned)
                                    {
                                        ++it;
                                    }
                                }
                            }
                            
                            
                            inputEV->setUserRecord("n"+_outputName,(int)(particlesSelected.size()));
                            
                            for (auto p: particlesSelected)
                            {
                                p->setName(_outputName);
                            }
                            for (auto p: particlesUnselected)
                            {
                                inputEV->removeObject(p);
                            }
                        }
                    }
                    
                    _selectedSource->setTargets(event);
                    return _selectedSource->processTargets();
                    
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

        void shutdown() throw(std::runtime_error)
        {
        }

        void destroy() throw (std::runtime_error)
        {
            delete this;
        }

};

PXL_MODULE_INIT(PLSelection)
PXL_PLUGIN_INIT

