#include "pxl/hep.hh"
#include "pxl/core.hh"
#include "pxl/core/macros.hh"
#include "pxl/core/PluginManager.hh"
#include "pxl/modules/Module.hh"
#include "pxl/modules/ModuleFactory.hh"


#include <string>
#include <unordered_map>
#include <unordered_set>
#include <regex>
#include <fstream>
#include <sstream>

static pxl::Logger logger("SlimParticleLevelObjects");


class SlimParticleLevelObjects:
    public pxl::Module
{
    private:
        pxl::Source* _outputSource;

        std::string _eventViewName;

        std::vector<std::string> _leptonNames;
        std::vector<std::regex> _leptonNamesRegex;
        int64_t _maxLeptons; 
        std::vector<std::string> _jetNames;
        std::vector<std::regex> _jetNamesRegex;
        int64_t _maxJets;
        
        struct SortByPt
        {
            bool operator()(const pxl::Particle* p1, const pxl::Particle* p2) const
            {
                //sort descending
                return p1->getPt()>p2->getPt();
            }
        };
        
    public:
        SlimParticleLevelObjects():
            Module(),
            _eventViewName("ParticleLevel"),
            _leptonNames({"Lepton"}),
            _maxLeptons(4),
            _jetNames({"Jet"}),
            _maxJets(4)
        {
            addSink("input", "input");
            _outputSource = addSource("output","output");
            
            addOption("event view","",_eventViewName);
            
            addOption("lepton names","",_leptonNames);
            for (auto name: _leptonNames)
            {
                _leptonNamesRegex.emplace_back(name);
            }
            addOption("max leptons","",_maxLeptons);
            
            addOption("jet names","",_jetNames);
            for (auto name: _jetNames)
            {
                _jetNamesRegex.emplace_back(name);
            }
            
            addOption("max jets","",_maxJets);
            
        }

        ~SlimParticleLevelObjects()
        {
        }

        // every Module needs a unique type
        static const std::string &getStaticType()
        {
            static std::string type ("SlimParticleLevelObjects");
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
            getOption("event view",_eventViewName);
            
            getOption("lepton names",_leptonNames);
            getOption("max leptons",_maxLeptons);
            
            getOption("jet names",_jetNames);
            getOption("max jets",_maxJets);
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
                    for (pxl::EventView* eventView: eventViews)
                    {
                        if (eventView->getName()==_eventViewName)
                        {
                            std::vector<pxl::Particle*> particles;
                            
                            std::vector<pxl::Particle*> leptons;
                            std::vector<pxl::Particle*> jets; 
                            
                            for (pxl::Particle* particle: particles)
                            {
                                if (std::find (_leptonNames.begin(), _leptonNames.end(), particle->getName())!=_leptonNames.end())
                                {
                                    leptons.push_back(particle);
                                }
                                else if (std::find (_jetNames.begin(), _jetNames.end(), particle->getName())!=_jetNames.end())
                                {
                                    jets.push_back(particle);
                                }
                            }
                            std::sort(leptons.begin(),leptons.end(),SortByPt());
                            std::sort(jets.begin(),jets.end(),SortByPt());
                            
                            for (unsigned int ilepton = std::min<int>(0,_maxLeptons); ilepton< leptons.size();++ilepton)
                            {
                                eventView->removeObject(leptons[ilepton]);
                            }
                            
                            for (unsigned int ijets = std::min<int>(0,_maxJets); ijets< jets.size();++ijets)
                            {
                                eventView->removeObject(jets[ijets]);
                            }
                            
                            break;
                        }
                    }

                    _outputSource->setTargets(event);
                    return _outputSource->processTargets();
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

PXL_MODULE_INIT(SlimParticleLevelObjects)
PXL_PLUGIN_INIT
