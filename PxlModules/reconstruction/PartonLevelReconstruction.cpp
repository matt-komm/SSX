#include "pxl/hep.hh"
#include "pxl/core.hh"
#include "pxl/core/macros.hh"
#include "pxl/core/PluginManager.hh"
#include "pxl/modules/Module.hh"
#include "pxl/modules/ModuleFactory.hh"

#include <iostream>

static pxl::Logger logger("PartonLevelReconstruction");

class PartonLevelReconstruction:
    public pxl::Module
{
    private:
        pxl::Source* _outputLeptonic;
        pxl::Source* _outputHadronic;

        std::string _inputEventViewName;
        std::string _outputEventViewName;
        
        bool _addTau;
        bool _addTauDecays;
        
        bool _lastCopies;
        
        enum GenFlag
        {
            IsPrompt=0, 
            IsDecayedLeptonHadron=1, 
            IsTauDecayProduct=2, 
            IsPromptTauDecayProduct=3,
            IsDirectTauDecayProduct=4, 
            IsDirectPromptTauDecayProduct=5, 
            IsDirectHadronDecayProduct=6, 
            IsHardProcess=7,
            FromHardProcess=8, 
            IsHardProcessTauDecayProduct=9, 
            IsDirectHardProcessTauDecayProduct=10, 
            FromHardProcessBeforeFSR=11,
            IsFirstCopy=12, 
            IsLastCopy=13, 
            IsLastCopyBeforeFSR=14 
        };
        const std::vector<std::string> _flagNames = {
            "IsPrompt", 
            "IsDecayedLeptonHadron", 
            "IsTauDecayProduct", 
            "IsPromptTauDecayProduct",
            "IsDirectTauDecayProduct", 
            "IsDirectPromptTauDecayProduct", 
            "IsDirectHadronDecayProduct", 
            "IsHardProcess",
            "FromHardProcess", 
            "IsHardProcessTauDecayProduct", 
            "IsDirectHardProcessTauDecayProduct", 
            "FromHardProcessBeforeFSR",
            "IsFirstCopy", 
            "IsLastCopy", 
            "IsLastCopyBeforeFSR"
        };
        
    public:
        PartonLevelReconstruction() :
            Module(),
            _inputEventViewName("Generated"),
            _outputEventViewName("PartonLevel"),
            _addTau(true),
            _addTauDecays(false),
            _lastCopies(false)
        {
            addSink("input", "Input");
            _outputLeptonic = addSource("leptonic", "leptonic");
            _outputHadronic = addSource("hadronic", "hadronic");

            addOption("input event view","name of the event view",_inputEventViewName);
            addOption("output event view","name of the neutrino",_outputEventViewName);
            
            addOption("add tau","allows tau to be a lepton",_addTau);
            addOption("add tau decays","allows promt mu/e from tau decays",_addTauDecays);
            
            addOption("last copies","consider last copy (first otherwise)",_lastCopies);
            
        }
        
        

        ~PartonLevelReconstruction()
        {
        }

        // every Module needs a unique type
        static const std::string &getStaticType()
        {
            static std::string type ("PartonLevelReconstruction");
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
            getOption("input event view",_inputEventViewName);
            getOption("output event view",_outputEventViewName);
            
            getOption("add tau",_addTau);
            getOption("add tau decays",_addTauDecays);
            
            getOption("last copies",_lastCopies);
        }

        void endJob()
        {
        }
        
        bool checkFlag(const pxl::Particle* particle, GenFlag flag) const
        {
            if (not particle->hasUserRecord("statusBits"))
            {
                throw std::runtime_error("Unable to find 'statusBits' for particle '"+particle->getName()+"'");
            }
            unsigned int statusBits = particle->getUserRecord("statusBits").toUInt32();
            unsigned int bitMask = 1 << flag;
            return statusBits & bitMask;
        }
        
        void unpackFlags(pxl::Particle* particle)
        {
            if (not particle->hasUserRecord("statusBits"))
            {
                throw std::runtime_error("Unable to find 'statusBits' for particle '"+particle->getName()+"'");
            }
            for (unsigned int i = 0; i<15; ++i)
            {
                particle->setUserRecord(_flagNames[i],bool(particle->getUserRecord("statusBits").toUInt32() & (1 << i)));
            }
        }
        
        bool analyse(pxl::Sink *sink) throw (std::runtime_error)
        {
            pxl::Event *event  = dynamic_cast<pxl::Event *> (sink->get());
            try
            {
                if (event)
                {
                    std::vector<pxl::EventView*> eventViews;
                    event->getObjectsOfType(eventViews);
                    
                    pxl::Particle* top = nullptr;
                    pxl::Particle* bquark = nullptr;
                    pxl::Particle* wboson = nullptr;
                    pxl::Particle* lepton = nullptr;
                    pxl::Particle* neutrino = nullptr;
                    pxl::Particle* lquark = nullptr;
                    
                    std::vector<pxl::Particle*> bquarkCandidates;

                    std::vector<pxl::Particle*> leptonCandidates;
                    std::vector<pxl::Particle*> neutrinoCandidates;
                    std::vector<pxl::Particle*> additionalNeutrinoCandidates;
                    
                    std::vector<pxl::Particle*> lquarkCandidates;
                    
                    const GenFlag copyGenFlag = _lastCopies?IsLastCopy:IsFirstCopy;
                    
                    pxl::EventView* outputEventView = nullptr;
                    for (unsigned ieventView=0; ieventView<eventViews.size();++ieventView)
                    {
                        if (eventViews[ieventView]->getName()==_inputEventViewName)
                        {
                            std::vector<pxl::Particle*> particles;
                            eventViews[ieventView]->getObjectsOfType(particles);
                            
                            for (unsigned int iparticle = 0; iparticle< particles.size(); ++iparticle)
                            {
                                pxl::Particle* particle = particles[iparticle];
                                unpackFlags(particle);
                                
                                //Find Top --------------------------------------------------------
                                if (std::fabs(particle->getPdgNumber())==6 and checkFlag(particle,FromHardProcess) and checkFlag(particle,copyGenFlag))
                                {
                                    if (top!=nullptr)
                                    {
                                        throw std::runtime_error("Multiple top quarks in hard process detected");
                                    }
                                    top = particle;
                                }
                                
                                
                                //Find W boson --------------------------------------------------------
                                //copy flags fails here
                                if (std::fabs(particle->getPdgNumber())==24 and checkFlag(particle,IsHardProcess))
                                {
                                    if (wboson!=nullptr)
                                    {
                                        throw std::runtime_error("Multiple w bosons in hard process detected");
                                    }
                                    wboson = particle;
                                }
                                
                                //Find b quarks --------------------------------------------------------
                                if (std::fabs(particle->getPdgNumber())==5 and checkFlag(particle,FromHardProcess) and checkFlag(particle,copyGenFlag))
                                {
                                    bquarkCandidates.push_back(particle);
                                }
                                
                                //Find leptons --------------------------------------------------------
                                if (checkFlag(particle,FromHardProcess) and (std::fabs(particle->getPdgNumber())==11 or std::fabs(particle->getPdgNumber())==13))
                                {
                                    //deal with direct W->lnu
                                    if (checkFlag(particle,copyGenFlag) and checkFlag(particle,IsPrompt))
                                    {
                                        leptonCandidates.push_back(particle);
                                        //particle->setName(particle->getName()+"_sel");
                                    }
                                    //deal with tau->lnu
                                    else if (_addTauDecays and checkFlag(particle,IsDirectPromptTauDecayProduct) and checkFlag(particle,copyGenFlag))
                                    {
                                        leptonCandidates.push_back(particle);
                                        //particle->setName(particle->getName()+"_sel");
                                    }
                                }
                                //protect against tau->gamma,tau FSR
                                else if (_addTau and checkFlag(particle,FromHardProcess) and std::fabs(particle->getPdgNumber())==15 and checkFlag(particle,IsPrompt) and checkFlag(particle,copyGenFlag))
                                {
                                    leptonCandidates.push_back(particle);
                                    //particle->setName(particle->getName()+"_sel");
                                }
                                
                                
                                //Find neutrinos --------------------------------------------------------
                                if (checkFlag(particle,FromHardProcess) and (std::fabs(particle->getPdgNumber())==12 or std::fabs(particle->getPdgNumber())==14 or std::fabs(particle->getPdgNumber())==16))
                                {
                                    //deal only with direct W->lnu, ignore subsequent neutrinos from tau decays
                                    if (checkFlag(particle,copyGenFlag) and checkFlag(particle,IsPrompt))
                                    {
                                        neutrinoCandidates.push_back(particle);
                                        //particle->setName(particle->getName()+"_sel");
                                    }

                                    if (_addTauDecays and checkFlag(particle,IsDirectPromptTauDecayProduct) and checkFlag(particle,copyGenFlag))
                                    {
                                        additionalNeutrinoCandidates.push_back(particle);
                                        //particle->setName(particle->getName()+"_add");
                                    }
                                }
                            }
                            
                            if (!top)
                            {
                                throw std::runtime_error("No top quarks detected");
                            }
                            
                            if (!wboson)
                            {
                                throw std::runtime_error("No W boson detected");
                            }
                            
                            if (bquarkCandidates.size()==0)
                            {
                                throw std::runtime_error("no b quarks found in hard process");
                            }
                            
                            if (leptonCandidates.size()>1)
                            {
                                throw std::runtime_error("Lepton ambiguity discovered");
                            }
                            lepton = leptonCandidates.front();
                            
                            if (neutrinoCandidates.size()>1)
                            {
                                throw std::runtime_error("Neutrino ambiguity discovered");
                            }
                            neutrino = neutrinoCandidates.front();
                                        
                            /*
                            const pxl::Particle* currentTop = top;
                            while (currentTop->numberOfDaughters()>0)
                            {
                                //just another copy before decaying
                                if (currentTop->numberOfDaughters()==1 and std::fabs(((pxl::Particle*)currentTop->getDaughter())->getPdgNumber())==6)
                                {
                                    currentTop = (pxl::Particle*)currentTop->getDaughter();
                                    continue;
                                }
                                if (currentTop->numberOfDaughters()>2)
                                {
                                    throw std::runtime_error("Unknown top decay into "+std::to_string(currentTop->numberOfDaughters())+" particles");
                                }
                                
                                std::vector<pxl::Particle*> topDaughters;
                                std::transform(currentTop->getDaughters().begin(), currentTop->getDaughters().end(), std::back_inserter(topDaughters), [](pxl::Relative* r){return static_cast<pxl::Particle*>(r);});

                                if (std::fabs(topDaughters[0]->getPdgNumber())==5 and std::fabs(topDaughters[1]->getPdgNumber())==24)
                                {
                                    bquark=topDaughters[0];
                                    wboson=topDaughters[1];
                                    break;
                                }
                                else if (std::fabs(topDaughters[1]->getPdgNumber())==5 and std::fabs(topDaughters[0]->getPdgNumber())==24)
                                {
                                    bquark=topDaughters[1];
                                    wboson=topDaughters[0];
                                    break;
                                }
                                else
                                {
                                    //can be a photon/gluon radiation so one daughter is a top quark again
                                    if (std::fabs(topDaughters[0]->getPdgNumber())==6)
                                    {
                                        currentTop = topDaughters[0];
                                        continue;
                                    }
                                    else if (std::fabs(topDaughters[1]->getPdgNumber())==6)
                                    {
                                        currentTop = topDaughters[1];
                                        continue;
                                    }
                                    else
                                    {
                                        throw std::runtime_error("Strange top decay into pdgs: "+std::to_string(topDaughters[0]->getPdgNumber())+", "+std::to_string(topDaughters[1]->getPdgNumber()));
                                    }
                                }
                            }
                            if (!wboson)
                            {
                                throw std::runtime_error("W boson from top decay not found");
                            }
                            if (!bquark)
                            {
                                throw std::runtime_error("b quark from top decay not found");
                            }
                            */

                            
                            
                            break; 
                        }
                    } //loop over event views

                    if (leptonCandidates.size()==0 and neutrinoCandidates.size()==0)
                    {
                        _outputHadronic->setTargets(event);
                        return _outputHadronic->processTargets();
                    }
                    _outputLeptonic->setTargets(event);
                    return _outputLeptonic->processTargets();
                    
                }
            }
            catch(std::exception &e)
            {
                throw std::runtime_error(getName()+" @event:"+std::to_string(event->getUserRecord("Event number").toUInt64())+": "+e.what());
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

PXL_MODULE_INIT(PartonLevelReconstruction)
PXL_PLUGIN_INIT

