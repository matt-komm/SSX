#include "pxl/hep.hh"
#include "pxl/core.hh"
#include "pxl/core/macros.hh"
#include "pxl/core/PluginManager.hh"
#include "pxl/modules/Module.hh"
#include "pxl/modules/ModuleFactory.hh"

#include "angles.h"

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
        
        bool _sumAddNeutrinos;
        
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
            _lastCopies(false),
            _sumAddNeutrinos(false)
        {
            addSink("input", "Input");
            _outputLeptonic = addSource("leptonic", "leptonic");
            _outputHadronic = addSource("hadronic", "hadronic");

            addOption("input event view","name of the event view",_inputEventViewName);
            addOption("output event view","name of the neutrino",_outputEventViewName);
            
            addOption("add tau","allows tau to be a lepton",_addTau);
            addOption("add tau decays","allows promt mu/e from tau decays",_addTauDecays);
            
            addOption("last copies","consider last copy (first otherwise)",_lastCopies);
            
            addOption("sum add neutrinos","add additional neutrinos in tau decays together",_sumAddNeutrinos);
            
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
            
            getOption("sum add neutrinos",_sumAddNeutrinos);
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
        
        bool isInDecay(const pxl::Particle* mother, const pxl::Particle* decayee) const
        {
            if (mother->numberOfDaughters ()==0)
            {
                return false;
            }
            for (auto d: mother->getDaughters())
            {
                const pxl::Particle* daughter = dynamic_cast<const pxl::Particle*>(d);
                if (daughter==decayee)
                {
                    return true;
                }
                else if (isInDecay(daughter,decayee))
                {
                    return true;
                }
            }
            return false;
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
                    std::vector<pxl::Particle*> additionalBquarkCandidates;

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
                                //unpackFlags(particle);
                                
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
                                
                                //Find l quarks --------------------------------------------------------
                                //First copy flag is not always present
                                if (std::fabs(particle->getPdgNumber())<5 and checkFlag(particle,FromHardProcess))
                                {
                                    if (_lastCopies and checkFlag(particle,IsLastCopy))
                                    {
                                        lquarkCandidates.push_back(particle);
                                    }
                                    else if (!_lastCopies and particle->numberOfMothers()==2)
                                    {
                                        lquarkCandidates.push_back(particle);
                                    }
                                }
                                
                                //Find leptons --------------------------------------------------------
                                if (std::fabs(particle->getPdgNumber())==11 or std::fabs(particle->getPdgNumber())==13)
                                {
                                    //deal with direct W->lnu
                                    if (checkFlag(particle,FromHardProcess) and checkFlag(particle,copyGenFlag) and checkFlag(particle,IsPrompt))
                                    {
                                        leptonCandidates.push_back(particle);
                                    }
                                    //deal with tau->lnu
                                    else if (_addTauDecays and checkFlag(particle,IsDirectPromptTauDecayProduct) and checkFlag(particle,copyGenFlag))
                                    {
                                        leptonCandidates.push_back(particle);
                                    }
                                }
                                //protect against tau->gamma,tau FSR
                                else if (_addTau and checkFlag(particle,FromHardProcess) and std::fabs(particle->getPdgNumber())==15 and checkFlag(particle,IsPrompt) and checkFlag(particle,copyGenFlag))
                                {
                                    leptonCandidates.push_back(particle);
                                }
                                
                                
                                //Find neutrinos --------------------------------------------------------
                                if (std::fabs(particle->getPdgNumber())==12 or std::fabs(particle->getPdgNumber())==14 or std::fabs(particle->getPdgNumber())==16)
                                {
                                    //deal only with direct W->lnu, ignore subsequent neutrinos from tau decays
                                    if (checkFlag(particle,FromHardProcess) and checkFlag(particle,copyGenFlag) and checkFlag(particle,IsPrompt))
                                    {
                                        neutrinoCandidates.push_back(particle);
                                    }

                                    if (_addTauDecays and checkFlag(particle,IsDirectPromptTauDecayProduct) and checkFlag(particle,copyGenFlag))
                                    {
                                        additionalNeutrinoCandidates.push_back(particle);
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
                            
                            for (pxl::Particle* p: bquarkCandidates)
                            {
                                if (isInDecay(top,p))
                                {
                                    if (bquark!=nullptr)
                                    {
                                        throw std::runtime_error("Multiple b quarks in hard process from top decay detected");
                                    }
                                    bquark = p;
                                }
                                else
                                {
                                    additionalBquarkCandidates.push_back(p);
                                }
                            }
                            
                            if (!bquark)
                            {
                                throw std::runtime_error("no b quark from top decay found");
                            }
                            
                            if (lquarkCandidates.size()==0)
                            {
                                throw std::runtime_error("no light quarks found in hard process");
                            }
                            
                            //take the hardest spectator jet not interacting to top (prevents initial states)
                            for (pxl::Particle* p: lquarkCandidates)
                            {
                                if ((lquark==nullptr or p->getE()>lquark->getE()) and (!isInDecay(p,top)))
                                {
                                    lquark = p;
                                }
                            }
                            
                            if (!lquark)
                            {
                                throw std::runtime_error("no light quark detected");
                            }
                            
                            if (leptonCandidates.size()>1)
                            {
                                throw std::runtime_error("Lepton ambiguity discovered");
                            }
                            if (leptonCandidates.size()==1)
                            {
                                lepton = leptonCandidates.front();
                            }
                            
                            if (neutrinoCandidates.size()>1)
                            {
                                throw std::runtime_error("Neutrino ambiguity discovered");
                            }
                            if (neutrinoCandidates.size()==1)
                            {
                                neutrino = neutrinoCandidates.front();
                            }
                            
                            if (top and bquark and wboson and lepton and neutrino and lquark)
                            {
                                pxl::EventView* outputEV = event->create<pxl::EventView>();
                                outputEV->setName(_outputEventViewName);
                                
                                pxl::Particle* topClone = (pxl::Particle*)top->clone();
                                topClone->setName("Top");
                                outputEV->insertObject(topClone);
                                
                                pxl::Particle* bquarkClone = (pxl::Particle*)bquark->clone();
                                bquarkClone->setName("bQuark");
                                outputEV->insertObject(bquarkClone);
                                topClone->linkDaughter(bquarkClone);
                                
                                pxl::Particle* wbosonClone = (pxl::Particle*)wboson->clone();
                                wbosonClone->setName("W");
                                outputEV->insertObject(wbosonClone);
                                topClone->linkDaughter(wbosonClone);
                                
                                pxl::Particle* leptonClone = (pxl::Particle*)lepton->clone();
                                leptonClone->setName("Lepton");
                                outputEV->insertObject(leptonClone);
                                wbosonClone->linkDaughter(leptonClone);
                                
                                pxl::Particle* neutrinoClone = (pxl::Particle*)neutrino->clone();
                                neutrinoClone->setName("Neutrino");
                                outputEV->insertObject(neutrinoClone);
                                wbosonClone->linkDaughter(neutrinoClone);
                                
                                if (_sumAddNeutrinos)
                                {
                                    for (pxl::Particle* p: additionalNeutrinoCandidates)
                                    {
                                        neutrinoClone->addP4(p->getVector());
                                    }
                                }
                                
                                pxl::Particle* met = (pxl::Particle*)neutrinoClone->clone();
                                met->setName("MET");
                                met->getVector().setPz(0);
                                outputEV->insertObject(met);
                                wbosonClone->linkDaughter(met);
                                
                                pxl::Particle* lquarkClone = (pxl::Particle*)lquark->clone();
                                lquarkClone->setName("lQuark");
                                outputEV->insertObject(lquarkClone);
                                
                                std::sort(additionalBquarkCandidates.begin(), additionalBquarkCandidates.end(), [](pxl::Particle* a, pxl::Particle* b) {return b->getPt()<a->getPt();});
                                
                                for (pxl::Particle* p: additionalBquarkCandidates)
                                {
                                    pxl::Particle* addBquarkClone = (pxl::Particle*)p->clone();
                                    addBquarkClone->setName("bQuarkAdd");
                                    outputEV->insertObject(addBquarkClone);
                                }
                                
                                outputEV->setUserRecord("mtw_beforePz",calculateMTW(lepton,met));
                                
                                calculateAngles(
                                    outputEV, 
                                    leptonClone, 
                                    neutrinoClone, 
                                    wbosonClone, 
                                    bquarkClone, 
                                    topClone, 
                                    lquarkClone
                                );
                                
                            }
                                        
                            break; 
                        }
                    } //loop over event views

                    if (leptonCandidates.size()==0 or neutrinoCandidates.size()==0)
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

