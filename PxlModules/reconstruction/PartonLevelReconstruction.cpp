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
                    
                    
                                
                    for (unsigned ieventView=0; ieventView<eventViews.size();++ieventView)
                    {
                        if (eventViews[ieventView]->getName()==_inputEventViewName)
                        {
                            pxl::Particle* top = nullptr;
                            pxl::Particle* bquark = nullptr;
                            pxl::Particle* wboson = nullptr;
                            pxl::Particle* lepton = nullptr;
                            pxl::Particle* neutrino = nullptr;
                            pxl::Particle* lquark = nullptr;
                            
                            std::vector<pxl::Particle*> bquarkCandidates;
                            std::vector<pxl::Particle*> additionalBquarkCandidates;

                            std::vector<pxl::Particle*> leptonCandidates;
                            std::vector<pxl::Particle*> leptonCandidatesFromTaus;
                            std::vector<pxl::Particle*> neutrinoCandidates;
                            std::vector<pxl::Particle*> additionalNeutrinoCandidates;
                            
                            std::vector<pxl::Particle*> lquarkCandidates;
                            std::vector<pxl::Particle*> additionalLquarkCandidates;
                            
                            const GenFlag copyGenFlag = _lastCopies?IsLastCopy:IsFirstCopy;
                            
                            pxl::EventView* outputEV = event->create<pxl::EventView>();
                            outputEV->setName(_outputEventViewName);
                        
                            std::vector<pxl::Particle*> particles;
                            eventViews[ieventView]->getObjectsOfType(particles);
                            
                            for (unsigned int iparticle = 0; iparticle< particles.size(); ++iparticle)
                            {
                                pxl::Particle* particle = particles[iparticle];
                                //unpackFlags(particle);
                                
                                //Find Top --------------------------------------------------------
                                if (std::abs(particle->getPdgNumber())==6 and checkFlag(particle,FromHardProcess) and checkFlag(particle,copyGenFlag))
                                {
                                    if (top!=nullptr)
                                    {
                                        throw std::runtime_error("Multiple top quarks in hard process detected");
                                    }
                                    top = particle;
                                }
                                
                                
                                //Find W boson --------------------------------------------------------
                                //copy flags fails here
                                if (std::abs(particle->getPdgNumber())==24 and checkFlag(particle,IsHardProcess))
                                {
                                    if (wboson!=nullptr)
                                    {
                                        throw std::runtime_error("Multiple w bosons in hard process detected");
                                    }
                                    wboson = particle;
                                }
                                
                                //Find b quarks --------------------------------------------------------
                                if (std::abs(particle->getPdgNumber())==5 and checkFlag(particle,FromHardProcess) and checkFlag(particle,copyGenFlag))
                                {
                                    bquarkCandidates.push_back(particle);
                                }
                                
                                //Find l quarks --------------------------------------------------------
                                //First copy flag is not always present
                                if (std::abs(particle->getPdgNumber())<5 and checkFlag(particle,FromHardProcess))
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
                                if (std::abs(particle->getPdgNumber())==11 or std::abs(particle->getPdgNumber())==13)
                                {
                                    //deal with direct W->lnu
                                    if (checkFlag(particle,FromHardProcess) and checkFlag(particle,copyGenFlag) and checkFlag(particle,IsPrompt))
                                    {
                                        leptonCandidates.push_back(particle);
                                    }
                                    //deal with tau->lnu, tau mother needs to be from hard process not from FSR radiation
                                    else if (_addTauDecays and checkFlag(particle,IsDirectPromptTauDecayProduct) and checkFlag(particle,copyGenFlag))
                                    {
                                        pxl::Particle* taumother = (pxl::Particle*)particle->getMother();
                                        while (taumother and std::fabs(taumother->getPdgNumber())!=15)
                                        {
                                            taumother = (pxl::Particle*)particle->getMother();
                                        }
                                        if (taumother and checkFlag(taumother,FromHardProcess))
                                        {
                                            leptonCandidatesFromTaus.push_back(particle);
                                        }
                                    }
                                }
                                //protect against tau->gamma,tau FSR
                                else if (_addTau and checkFlag(particle,FromHardProcess) and std::abs(particle->getPdgNumber())==15 and checkFlag(particle,IsPrompt) and checkFlag(particle,copyGenFlag))
                                {
                                    leptonCandidates.push_back(particle);
                                }
                                
                                
                                //Find neutrinos --------------------------------------------------------
                                if (std::abs(particle->getPdgNumber())==12 or std::abs(particle->getPdgNumber())==14 or std::abs(particle->getPdgNumber())==16)
                                {
                                    //deal only with direct W->lnu, ignore subsequent neutrinos from tau decays
                                    if (checkFlag(particle,FromHardProcess) and checkFlag(particle,copyGenFlag) and checkFlag(particle,IsPrompt))
                                    {
                                        neutrinoCandidates.push_back(particle);
                                    }
                                        
                                    //deal with tau->lnu, tau mother needs to be from hard process not from FSR radiation
                                    if (_addTauDecays and checkFlag(particle,IsDirectPromptTauDecayProduct) and checkFlag(particle,copyGenFlag))
                                    {
                                        pxl::Particle* taumother = (pxl::Particle*)particle->getMother();
                                        while (taumother and std::fabs(taumother->getPdgNumber())!=15)
                                        {
                                            taumother = (pxl::Particle*)particle->getMother();
                                        }
                                        if (taumother and checkFlag(taumother,FromHardProcess))
                                        {
                                            additionalNeutrinoCandidates.push_back(particle);
                                        }
                                    }
                                }
                            }
                            
                            std::sort(lquarkCandidates.begin(), lquarkCandidates.end(), [](pxl::Particle* a, pxl::Particle* b) {return b->getE()<a->getE();});
                            std::sort(bquarkCandidates.begin(), bquarkCandidates.end(), [](pxl::Particle* a, pxl::Particle* b) {return b->getE()<a->getE();});
                            
                            
                            if (!top)
                            {
                                throw std::runtime_error("No top quarks detected");
                            }
                            pxl::Particle* topClone = (pxl::Particle*)top->clone();
                            topClone->setName("Top");
                            topClone->setUserRecord("pdg",top->getPdgNumber());
                            outputEV->insertObject(topClone);
                            topClone->setUserRecord("y",0.5*std::log((topClone->getE()+topClone->getPz())/(topClone->getE()-topClone->getPz())));
                            
                            
                            if (!wboson)
                            {
                                throw std::runtime_error("No W boson detected");
                            }
                            pxl::Particle* wbosonClone = (pxl::Particle*)wboson->clone();
                            wbosonClone->setName("W");
                            wbosonClone->setUserRecord("pdg",wboson->getPdgNumber());
                            outputEV->insertObject(wbosonClone);
                            topClone->linkDaughter(wbosonClone);
                            
                            if (bquarkCandidates.size()==0)
                            {
                                throw std::runtime_error("no b quarks found in hard process");
                            }
                            
                            for (pxl::Particle* p: bquarkCandidates)
                            {
                                if (isInDecay(top,p) and not isInDecay(wboson,p))
                                {
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
                            pxl::Particle* bquarkClone = (pxl::Particle*)bquark->clone();
                            bquarkClone->setName("bQuark");
                            bquarkClone->setUserRecord("pdg",bquark->getPdgNumber());
                            outputEV->insertObject(bquarkClone);
                            topClone->linkDaughter(bquarkClone);
                            for (pxl::Particle* p: additionalBquarkCandidates)
                            {
                                pxl::Particle* addBquarkClone = (pxl::Particle*)p->clone();
                                addBquarkClone->setName("bQuarkAdd");
                                addBquarkClone->setUserRecord("pdg",p->getPdgNumber());
                                outputEV->insertObject(addBquarkClone);
                            }
                            
                            if (lquarkCandidates.size()==0)
                            {
                                throw std::runtime_error("no light quarks found in hard process");
                            }
                            
                            
                          
                            //take the jet balancing top+ljet system
                            double minPt = 100000.0;
                            unsigned int lIndex = 0;
                            for (unsigned int il = 0; il < lquarkCandidates.size(); ++il)
                            {
                                pxl::Particle* p = lquarkCandidates[il];
                                if (!isInDecay(p,top))
                                {
                                    pxl::LorentzVector v = p->getVector();
                                    v+=top->getVector();
                                    if (v.getPt()<minPt)
                                    {
                                        minPt = v.getPt();
                                        lIndex = il;
                                    }
                                }
                            }
                            for (unsigned int il = 0; il < lquarkCandidates.size(); ++il)
                            {
                                if (il == lIndex)
                                {
                                    lquark = lquarkCandidates[il];
                                }
                                else
                                {
                                    additionalLquarkCandidates.push_back(lquarkCandidates[il]);
                                }
                            }
                            
                            
                            if (!lquark)
                            {
                                throw std::runtime_error("no light quark detected");
                            }
                            pxl::Particle* lquarkClone = (pxl::Particle*)lquark->clone();
                            lquarkClone->setName("lQuark");
                            lquarkClone->setUserRecord("pdg",lquark->getPdgNumber());
                            outputEV->insertObject(lquarkClone);
                            
                            for (pxl::Particle* p: additionalLquarkCandidates)
                            {
                                pxl::Particle* addLquarkClone = (pxl::Particle*)p->clone();
                                addLquarkClone->setName("lQuarkAdd");
                                addLquarkClone->setUserRecord("pdg",p->getPdgNumber());
                                outputEV->insertObject(addLquarkClone);
                            }
                            
                            if ((leptonCandidates.size()+leptonCandidatesFromTaus.size())>1
                                or ((leptonCandidates.size()>0) and (leptonCandidatesFromTaus.size()>0))
                            )
                            {
                                throw std::runtime_error("Lepton ambiguity discovered");
                            }
                            
                            if (leptonCandidates.size()==1)
                            {
                                lepton = leptonCandidates.front();
                            
                                pxl::Particle* leptonClone = (pxl::Particle*)lepton->clone();
                                leptonClone->setName("Lepton");
                                leptonClone->setUserRecord("pdg",lepton->getPdgNumber());
                                leptonClone->setUserRecord("fromTau",false);
                                outputEV->insertObject(leptonClone);
                                wbosonClone->linkDaughter(leptonClone);
                                
                            }
                            else if (leptonCandidatesFromTaus.size()==1)
                            {
                                lepton = leptonCandidatesFromTaus.front();
                            
                                pxl::Particle* leptonClone = (pxl::Particle*)lepton->clone();
                                leptonClone->setName("Lepton");
                                leptonClone->setUserRecord("pdg",lepton->getPdgNumber());
                                leptonClone->setUserRecord("fromTau",true);
                                outputEV->insertObject(leptonClone);
                                wbosonClone->linkDaughter(leptonClone);
                            }
                            
                            double minDR = 100.0;
                            double minEta = 100.0;
                            double minPhi = 100.0;
                            for (pxl::Particle* p: lquarkCandidates)
                            {
                                p->setUserRecord("dRcleanMin",p->getVector().deltaR(&lepton->getVector()));
                                p->setUserRecord("dEtacleanMin",std::fabs(p->getVector().deltaEta(&lepton->getVector())));
                                p->setUserRecord("dPhicleanMin",std::fabs(p->getVector().deltaPhi(&lepton->getVector())));
                            }
                            
                            for (pxl::Particle* p: bquarkCandidates)
                            {
                                p->setUserRecord("dRcleanMin",p->getVector().deltaR(&lepton->getVector()));
                                p->setUserRecord("dEtacleanMin",std::fabs(p->getVector().deltaEta(&lepton->getVector())));
                                p->setUserRecord("dPhicleanMin",std::fabs(p->getVector().deltaPhi(&lepton->getVector())));
                            }
                            
                            
                            
                            if (neutrinoCandidates.size()>1)
                            {
                                throw std::runtime_error("Neutrino ambiguity discovered");
                            }
                            
                            pxl::Particle* neutrinoClone = nullptr;
                            if (neutrinoCandidates.size()==1)
                            {
                                neutrino = neutrinoCandidates.front();
                                neutrinoClone = (pxl::Particle*)neutrino->clone();
                                if (_sumAddNeutrinos)
                                {
                                    for (pxl::Particle* p: additionalNeutrinoCandidates)
                                    {
                                        neutrinoClone->addP4(p->getVector());
                                    }
                                }

                                neutrinoClone->setName("Neutrino");
                                neutrinoClone->setUserRecord("pdg",neutrino->getPdgNumber());
                                outputEV->insertObject(neutrinoClone);
                                wbosonClone->linkDaughter(neutrinoClone);
                            }
                                
                            

                            
                            
                            outputEV->setUserRecord("njets",(int)(2+additionalLquarkCandidates.size()+additionalBquarkCandidates.size()));
                            outputEV->setUserRecord("nbjets",(int)(1+additionalBquarkCandidates.size()));
                            
                            if (lepton and neutrinoClone)
                            {
                                const double mtw = calculateMTW(lepton,neutrinoClone);
                                outputEV->setUserRecord("mtw",mtw);
                            }
                            calculateAngles(
                                outputEV, 
                                "",
                                lepton, 
                                neutrinoClone, 
                                wboson, 
                                bquark, 
                                top, 
                                lquark
                            );
                            
                            
                                        
                         
                    

                            if ((leptonCandidates.size()+leptonCandidatesFromTaus.size())==0 or neutrinoCandidates.size()==0)
                            {
                                outputEV->setUserRecord("isLeptonic",false);
                                _outputHadronic->setTargets(event);
                                return _outputHadronic->processTargets();
                            }
                            
                            
                            outputEV->setUserRecord("isLeptonic",true);
                            _outputLeptonic->setTargets(event);
                            return _outputLeptonic->processTargets();
                        }
                    } //loop over event views
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

