#include "pxl/hep.hh"
#include "pxl/core.hh"
#include "pxl/core/macros.hh"
#include "pxl/core/PluginManager.hh"
#include "pxl/modules/Module.hh"
#include "pxl/modules/ModuleFactory.hh"

#include <string>

static pxl::Logger logger("Matching");

class Matching:
    public pxl::Module
{
    private:
        pxl::Source* _source;
        
        
    public:
        struct SingleTopEvent
        {
            pxl::Particle* lepton;
            pxl::Particle* neutrino;
            pxl::Particle* wboson;
            pxl::Particle* top;
            pxl::Particle* bjet;
            pxl::Particle* ljet;
            
            SingleTopEvent():
                lepton(nullptr),
                neutrino(nullptr),
                wboson(nullptr),
                top(nullptr),
                bjet(nullptr),
                ljet(nullptr)
            {
            }
                
            bool doMatching(std::string prefix, pxl::Particle* p1, pxl::Particle* p2)
            {
                if (p1)
                {
                    if (!p2)
                    {
                        p1->setUserRecord(prefix+"_dR",-1.0);
                        return false;
                    }
                    else
                    {
                        double dR = p1->getVector().deltaR(p2->getVector());
                        p1->setUserRecord(prefix+"_dR",dR);
                        return true;
                    }
                }
            }
            
            bool match(std::string prefix, const SingleTopEvent& st)
            {
                bool completeMatch = true;
                completeMatch &= doMatching(prefix+"_lepton",lepton,st.lepton);
                completeMatch &= doMatching(prefix+"_neutrino", neutrino,st.neutrino);
                completeMatch &= doMatching(prefix+"_wboson",wboson,st.wboson);
                completeMatch &= doMatching(prefix+"_top",top,st.top);
                completeMatch &= doMatching(prefix+"_ljet",ljet,st.ljet);
                completeMatch &= doMatching(prefix+"_bjet",bjet,st.bjet);
                return completeMatch;
            }
        };   

    
        Matching():
            Module()
        {
            addSink("input", "input");
            _source = addSource("out","out");
            
        }

        ~Matching()
        {
        }

        // every Module needs a unique type
        static const std::string &getStaticType()
        {
            static std::string type ("Matching");
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
            
        }
        
        bool analyse(pxl::Sink *sink) throw (std::runtime_error)
        {
            
            try
            {
                pxl::Event *event  = dynamic_cast<pxl::Event*>(sink->get());
                if (event)
                {
                    SingleTopEvent partonST;
                    SingleTopEvent particleST;
                    SingleTopEvent recoST;
                    
                    std::vector<pxl::EventView*> eventViews;
                    event->getObjectsOfType(eventViews);
                    
                    pxl::EventView* recoEV = nullptr;
                    pxl::EventView* particleEV = nullptr;
                    pxl::EventView* partonEV = nullptr;
                    
                    for (auto ev: eventViews)
                    {
                        if (ev->getName()=="Parton")
                        {
                            std::vector<pxl::Particle*> particles;
                            ev->getObjectsOfType(particles);
                            partonEV=ev;
                            for (auto particle: particles)
                            {
                                if (particle->getName()=="Lepton") partonST.lepton=particle;
                                if (particle->getName()=="Neutrino") partonST.neutrino=particle;
                                if (particle->getName()=="W") partonST.wboson=particle;
                                if (particle->getName()=="Top") partonST.top=particle;
                                if (particle->getName()=="bQuark") partonST.bjet=particle;
                                if (particle->getName()=="lQuark") partonST.ljet=particle;
                            }
                        }
                        else if (ev->getName()=="PTR")
                        {
                            std::vector<pxl::Particle*> particles;
                            ev->getObjectsOfType(particles);
                            particleEV=ev;
                            for (auto particle: particles)
                            {
                                if (particle->getName()=="TightLepton") particleST.lepton=particle;
                                if (particle->getName()=="Neutrino") particleST.neutrino=particle;
                                if (particle->getName()=="W") particleST.wboson=particle;
                                if (particle->getName()=="Top") particleST.top=particle;
                                if (particle->getName()=="BJet") particleST.bjet=particle;
                                if (particle->getName()=="LightJet") particleST.ljet=particle;
                            }
                        }
                        else if (ev->getName()=="SingleTop")
                        {
                            std::vector<pxl::Particle*> particles;
                            ev->getObjectsOfType(particles);
                            recoEV=ev;
                            for (auto particle: particles)
                            {
                                if (particle->getName()=="TightLepton") recoST.lepton=particle;
                                if (particle->getName()=="Neutrino") recoST.neutrino=particle;
                                if (particle->getName()=="W") recoST.wboson=particle;
                                if (particle->getName()=="Top") recoST.top=particle;
                                if (particle->getName()=="BJet") recoST.bjet=particle;
                                if (particle->getName()=="LightJet") recoST.ljet=particle;
                            }
                        }
                    }
                    if (recoST.match("PTR",particleST))
                    {
                        recoEV->setUserRecord("matchedToPTR",true);
                    }
                    else
                    {
                        recoEV->setUserRecord("matchedToPTR",false);
                    }
                    if (recoST.match("GEN",partonST))
                    {
                        recoEV->setUserRecord("matchedToGEN",true);
                    }
                    else
                    {
                        recoEV->setUserRecord("matchedToGEN",false);
                    }
                    if (particleST.match("GEN",partonST))
                    {
                        particleEV->setUserRecord("matchedToGEN",true);
                    }
                    else
                    {
                        particleEV->setUserRecord("matchedToGEN",false);
                    }
                    
                    _source->setTargets(event);
                    return _source->processTargets();
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

PXL_MODULE_INIT(Matching)
PXL_PLUGIN_INIT
