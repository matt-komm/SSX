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
        
        enum JetProjectionMode
        {
            NONE=0, //no projection
            EXL=1, //exclude prompt leptons
            EXLN=2, //exclude prompt leptons + neutrinos
            EXLNN=3 //exclude prompt leptons + all neutrinos
        };
        
        enum TauMode
        {
            EXCLUDE=0, //exlude promt leptons from tau, include them in jets
            INCLUDE=1 //include promt leptons from tau, exclude them in jets
        };

        struct Setup
        {
            TauMode tauMode;
            JetProjectionMode jetMode;
            std::string outName;
            std::string leptonName;
            std::string jetName;
            std::string metName;

            Setup(
                TauMode tauMode,
                JetProjectionMode jetMode
                
            ):
                tauMode(tauMode),
                jetMode(jetMode)
            {
                if (tauMode==INCLUDE) { leptonName="Lepton"; outName="incTau"; }
                else { leptonName="LeptonWOTau"; outName="exTau"; }
                
                jetName = "Jet";
                
                if (jetMode==EXL) { jetName+="ExL"; outName+="_exL"; }
                else if (jetMode==EXLN) { jetName+="ExLN"; outName+="_exLN";}
                else if (jetMode==EXLNN) { jetName+="ExLNN"; outName+="_exLNN"; }
                
                if (tauMode==EXCLUDE and jetMode!=NONE) { jetName+="WTau"; }
                
                metName = "NeutrinoPrompt";
                if (jetMode==EXLNN) { metName = "NeutrinoAll"; }  
                else if (tauMode==EXCLUDE) { metName = "NeutrinoPromptWOTau"; }
            }
        };
        
        std::vector<std::pair<Setup,bool>> _setups;
        
        pxl::Source* _nominalSource;
        
        
    public:
        PLObjects():
            Module(),
            _eventViewName("ParticleLevel")
            
        {
            addSink("input", "input");
            addOption("event view name", "", _eventViewName);

            _nominalSource = addSource("nominal","output");
            
            for (auto tauMode: {EXCLUDE,INCLUDE})
            {
                for (auto jetMode: {NONE,EXL,EXLN,EXLNN})
                {
                    _setups.emplace_back(Setup(tauMode,jetMode),true);
                    bool enabled = true;
                    addOption(_setups.back().first.outName,"",enabled);
                    _setups.back().second = enabled;
                }
            }
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
            
            for (auto setup: _setups)
            { 
                getOption(setup.first.outName,setup.second);
            }
        
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
                            for (auto setup: _setups)
                            {
                                if (not setup.second)
                                {
                                    //continue;
                                }
                                
                                pxl::EventView* evClone = (pxl::EventView*)ev->clone();
                                evClone->setName("PL_"+setup.first.outName);
                                event->insertObject(evClone);
                                
                                std::vector<pxl::Particle*> particles;
                                evClone->getObjectsOfType(particles);
                                
                                for (auto p: particles)
                                {
                                    const std::string name = p->getName();
                                    if (name == setup.first.leptonName)
                                    {
                                        p->setName("Lepton");
                                    }
                                    else if (name == setup.first.jetName)
                                    {
                                        p->setName("Jet");
                                    }
                                    else if (name == setup.first.metName)
                                    {
                                        p->setName("Neutrino");
                                    }
                                    else
                                    {
                                        evClone->removeObject(p);
                                    }
                                }
                                
                                  
                            }
                            event->removeObject(ev);
                            break;
                        }
                    }
                    _nominalSource->setTargets(event);
                    return _nominalSource->processTargets();
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
