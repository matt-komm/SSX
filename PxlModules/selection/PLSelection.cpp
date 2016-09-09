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
        std::string _outputName;
  
        
        double _pTMinTight;
        double _etaMaxTight;
        
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

        int64_t _numMin;
        int64_t _numMax;
      
        bool _clean;
        
    public:
        PLSelection():

            Module(),
            _inputName("Lepton"),
            _outputName("TightMuon"),

            _pTMinTight(24),
            _etaMaxTight(2.4),
            
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
            
            _numMin(1),
            _numMax(1),
            
            _clean(false)

        {
            addSink("input", "input");
            _selectedSource = addSource("selected", "selected");

            addOption("input event view","","PL[A-Za-z0-9_]+");
            addOption("input particle name","",_inputName);
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
            
            addOption("min number","",_numMin);
            addOption("max number","",_numMax);
            
            addOption("clear event","will copy all instances found otherwise for vetoing",_clean);
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
            
            getOption("min number",_numMin);
            getOption("max number",_numMax);
            
            getOption("clear event",_clean);
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
            
            const float muonFraction = particle->getUserRecord("muonFraction").toFloat();
            if ((muonFraction<_muonFractionRangeMin) or (muonFraction>_muonFractionRangeMax))
            {
                return false;
            }
            
            const float electronFraction = particle->getUserRecord("electronFraction").toFloat();
            if ((electronFraction<_electronFractionRangeMin) or (electronFraction>_electronFractionRangeMax))
            {
                return false;
            }
            
            const float photonFraction = particle->getUserRecord("photonFraction").toFloat();
            if ((photonFraction<_photonFractionRangeMin) or (photonFraction>_photonFractionRangeMax))
            {
                return false;
            }
        
            const float hadronFraction = particle->getUserRecord("hadronFraction").toFloat();
            if ((hadronFraction<_hadronFractionRangeMin) or (hadronFraction>_hadronFractionRangeMax))
            {
                return false;
            }
            
            const float neutrinoFraction = particle->getUserRecord("neutrinoFraction").toFloat();
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
                                    else if (_clean)
                                    {
                                        particlesUnselected.push_back(particle);
                                    }
                                }
                            }
                            
                            inputEV->setUserRecord("n"+_outputName,particlesSelected.size());
                            
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

