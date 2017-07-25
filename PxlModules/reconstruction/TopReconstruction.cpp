#include "pxl/hep.hh"
#include "pxl/core.hh"
#include "pxl/core/macros.hh"
#include "pxl/core/PluginManager.hh"
#include "pxl/modules/Module.hh"
#include "pxl/modules/ModuleFactory.hh"

#include "angles.h"
#include "vdtMath.h"

#include <algorithm>
#include <cmath>
#include <unordered_map>

static pxl::Logger logger("TopReconstruction");

struct SortByUserRecord
{
    const std::string urName;
    SortByUserRecord(std::string urName):
        urName(urName)
    {
    }
    
    bool operator()(const pxl::Particle* p1, const pxl::Particle* p2) const
    {
        return p1->getUserRecord(urName).toFloat()>p2->getUserRecord(urName).toFloat();
    }
};

struct SortByPt
{
    bool operator()(const pxl::Particle* p1, const pxl::Particle* p2) const
    {
        //sort descending
        return p1->getPt()>p2->getPt();
    }
};

struct SortByEta
{
    bool operator()(const pxl::Particle* p1, const pxl::Particle* p2) const
    {
        //sort descending
        return fabs(p1->getEta())>fabs(p2->getEta());
    }
};




class TopReconstruction:
    public pxl::Module
{

    const static std::vector<double> jecBins;
    private:
    
        enum Category
        {
            OTHER=0,
            C0J=1,
            C1J=2,
            C2J0T=3,C2J1T=4,C2J2T=5,
            C3J0T=6,C3J1T=7,C3J2T=8,C3J3T=9
        };
        
        std::unordered_map<int,std::pair<std::string,bool>> _catToState;
    
        pxl::Source* _outputSelected;
        pxl::Source* _outputVeto;
        pxl::Source* _outputNoLepton;
        
        std::string _inputEventViewNameLepton;
        std::string _leptonName;
        
        std::string _inputEventViewNameNeutrino;
        std::string _neutrinoName;
        
        std::string _inputEventViewNameJets;
        std::vector<std::string> _bJetNames;
        std::vector<std::string> _lightJetNames;
        
        std::string _outputEventViewName;
        std::string _wbosonName;
        std::string _topName;
        

        
        
    public:
        TopReconstruction():
            Module(),
            _inputEventViewNameLepton("Reconstructed"),
            _leptonName("TightLepton"),
            
            _inputEventViewNameNeutrino("SingleTop"),
            _neutrinoName("Neutrino"),
            
            _inputEventViewNameJets("Reconstructed"),
            _bJetNames({"SelectedBJetTight"}),
            _lightJetNames({"SelectedJet","SelectedBJetMed","SelectedBJetLoose"}),
            
            _outputEventViewName("SingleTop"),
            _wbosonName("W"),
            _topName("Top")
        {
            addSink("input", "input");
            _outputSelected = addSource("output","output");
            _outputVeto = addSource("veto","veto");
            _outputNoLepton = addSource("noLepton","noLepton");

            addOption("input event view lepton","",_inputEventViewNameLepton);
            addOption("lepton","",_leptonName);
            
            addOption("input event view neutrino","",_inputEventViewNameNeutrino);
            addOption("neutrino","",_neutrinoName);
            
            addOption("input event view jets","",_inputEventViewNameJets);
            addOption("b jets","",_bJetNames);   
            addOption("light jets","",_lightJetNames);
            
            addOption("output event view","",_outputEventViewName);
            addOption("W boson","",_wbosonName);
            addOption("top","",_topName);
            
            
            _catToState[OTHER] = std::make_pair("other",true);
            
            _catToState[C0J] = std::make_pair("0j",true);
            _catToState[C1J] = std::make_pair("1j",true);
            
            _catToState[C2J0T] = std::make_pair("2j0t",true);
            _catToState[C2J1T] = std::make_pair("2j1t",true);
            _catToState[C2J2T] = std::make_pair("2j2t",true);
            
            _catToState[C3J0T] = std::make_pair("3j0t",true);
            _catToState[C3J1T] = std::make_pair("3j1t",true);
            _catToState[C3J2T] = std::make_pair("3j2t",true);
            _catToState[C3J3T] = std::make_pair("3j3t",true);
            
            
            for (int i = 0; i < 10; ++i)
            {
                addOption(_catToState[i].first,"",_catToState[i].second);
            }
        }

        ~TopReconstruction()
        {
        }

        // every Module needs a unique type
        static const std::string &getStaticType()
        {
            static std::string type ("TopReconstruction");
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
            getOption("input event view lepton",_inputEventViewNameLepton);
            getOption("lepton",_leptonName);
            
            getOption("input event view neutrino",_inputEventViewNameNeutrino);
            getOption("neutrino",_neutrinoName);
            
            getOption("input event view jets",_inputEventViewNameJets);
            getOption("b jets",_bJetNames);   
            getOption("light jets",_lightJetNames);
            
            getOption("output event view",_outputEventViewName);
            getOption("W boson",_wbosonName);
            getOption("top",_topName);
            
            for (int i = 0; i < 10; ++i)
            {
                getOption(_catToState[i].first,_catToState[i].second);
            }
        }
        
        
        pxl::Particle* makeWboson(pxl::EventView* eventView, pxl::Particle* p1, pxl::Particle* p2)
        {
            pxl::Particle* wboson = eventView->create<pxl::Particle>();
            wboson->setName(_wbosonName);
            wboson->linkDaughter(p1);
            wboson->linkDaughter(p2);
            wboson->setP4FromDaughters();
            return wboson;
        }
        
        pxl::Particle* makeTop(pxl::EventView* eventView, pxl::Particle* p1, pxl::Particle* p2)
        {
            pxl::Particle* top = eventView->create<pxl::Particle>();
            top->setName(_topName);
            top->linkDaughter(p1);
            top->linkDaughter(p2);
            top->setP4FromDaughters();
            top->setUserRecord("Y",0.5*std::log((top->getE()+top->getPz())/(top->getE()-top->getPz())));
            
            return top;
        }
        
        pxl::Particle* makeBestTop(pxl::EventView* eventView, pxl::Particle* lepton, pxl::Particle* neutrino,  std::vector<pxl::Particle*> lightjets, std::vector<pxl::Particle*> bjets)
        {
            const double bestTopMass = 172.5;
            
            pxl::Particle* ljet = nullptr;
            pxl::Particle* bjet = nullptr;
            
            std::vector<pxl::Particle*> jets = lightjets;
            jets.insert(jets.end(),bjets.begin(),bjets.end());
            
            
            pxl::LorentzVector topVec(0,0,0,0);
            for (pxl::Particle* jet: jets)
            {
                pxl::LorentzVector testVec = lepton->getVector()+neutrino->getVector()+jet->getVector();
                if (std::fabs(topVec.getMass()-bestTopMass)>std::fabs(testVec.getMass()-bestTopMass))
                {
                    topVec=testVec;
                    bjet = jet;
                }
            }
            for (pxl::Particle* jet: jets)
            {
                if (jet!=bjet)
                {
                    if ((ljet==nullptr) or (std::fabs(ljet->getEta())<std::fabs(jet->getEta())))
                    {
                        ljet=jet;
                    }
                }
            }
            
            pxl::Particle* top = eventView->create<pxl::Particle>();
            top->setName(_topName+"Best");
            top->setP4(topVec);
            top->setUserRecord("Y",0.5*std::log((top->getE()+top->getPz())/(top->getE()-top->getPz())));
            
            if (ljet)
            {
                pxl::Particle* ljetClone = (pxl::Particle*)ljet->clone();
                ljetClone->setName("LightJetBest");
                eventView->insertObject(ljetClone);
            }
            if (bjet)
            {
                pxl::Particle* bjetClone = (pxl::Particle*)bjet->clone();
                bjetClone->setName("BJetBest");
                eventView->insertObject(bjetClone);
            }
            
            if (ljet and bjet)
            {
                pxl::Particle wboson;
                wboson.setP4(lepton->getVector()+neutrino->getVector());
                calculateAngles(eventView,"best_", lepton, neutrino, &wboson, bjet, top, ljet);
            }
            
            return top;
        }
        
        pxl::Particle* makeCMSystem(pxl::EventView* eventView, const std::string& name, std::vector<pxl::Particle*> particles)
        {
            pxl::Particle* cm = eventView->create<pxl::Particle>();
            cm->setName(name);
            //linking too much will crash the gui :-(

            float minDEta = 100;
            float maxDEta = -100;
            float minDR = 100;
            float maxDR = -100;
            float minDPhi = 100;
            float maxDPhi = -100;
            for (pxl::Particle* p: particles)
            {
                cm->addP4(p);
            }
            if (particles.size()>=2)
            {
                for (unsigned int i = 0; i < particles.size(); ++i)
                {
                    for (unsigned int j = i+1; j < particles.size(); ++j)
                    {
                        const pxl::Particle* p1 = particles[i];
                        const pxl::Particle* p2 = particles[j];

                        const float deltaEta = fabs(p1->getEta()-p2->getEta());
                        minDEta=std::min(minDEta,deltaEta);
                        maxDEta=std::max(maxDEta,deltaEta);
                        
                        const float deltaR = p1->getVector().deltaR(&(p2->getVector()));
                        minDR=std::min(minDR,deltaR);
                        maxDR=std::max(maxDR,deltaR);
                        
                        const float deltaPhi = fabs(p1->getVector().deltaPhi(&(p2->getVector())));
                        minDPhi=std::min(minDPhi,deltaPhi);
                        maxDPhi=std::max(maxDPhi,deltaPhi);
                    }
                }

                cm->setUserRecord("dEta",minDEta);
                cm->setUserRecord("dR",minDR);
                cm->setUserRecord("dPhi",minDPhi);
            }
        
            return cm;
        }
        
        Category reconstructEvent(pxl::EventView* eventView, pxl::Particle* lepton, pxl::Particle* neutrino, std::vector<pxl::Particle*>& lightjets, std::vector<pxl::Particle*>& bjets) 
        {
            const unsigned int nljets = lightjets.size();
            const unsigned int nbjets = bjets.size();
            const unsigned int njets = nljets+nbjets;
            
            pxl::Particle* wboson = nullptr;
            pxl::Particle* top = nullptr;
            pxl::Particle* lightjet = nullptr;
            pxl::Particle* bjet = nullptr;
            
            //sort descending
            std::sort(lightjets.begin(),lightjets.end(),SortByEta());
            //sort descending
            std::sort(bjets.begin(),bjets.end(),SortByPt());
            
            Category category = OTHER;
            
            if (!lepton)
            {
                throw std::runtime_error("no lepton found!");
            }
            if (!neutrino)
            {
                throw std::runtime_error("no neutrino found!");
            }
            
            if ((lightjets.size()+bjets.size())>0)
            {
                makeBestTop(eventView,lepton, neutrino,lightjets,bjets);
            }
            
            
            if (njets==0)
            {
                category=C0J;
            }
            if (njets==1)
            {
                if (nljets==1)
                {
                    if (_outputEventViewName!=_inputEventViewNameJets)
                    {
                        bjet=(pxl::Particle*)lightjets[0]->clone();
                        eventView->insertObject(bjet);
                    }
                    else
                    {
                        bjet = lightjets[0];
                    }
                    lightjets.erase(lightjets.begin());
                    
                }
                else if (nbjets==1)
                {
                    if (_outputEventViewName!=_inputEventViewNameJets)
                    {
                        bjet=(pxl::Particle*)bjets[0]->clone();
                        eventView->insertObject(bjet);
                    }
                    else
                    {
                        bjet = bjets[0];
                    }
                    bjets.erase(bjets.begin());
                    
                }
                category=C1J;
            }
            else if (njets>=2)
            {
                if (nbjets==0)
                {
                    if (_outputEventViewName!=_inputEventViewNameJets)
                    {
                        lightjet=(pxl::Particle*)lightjets[0]->clone();
                        bjet=(pxl::Particle*)lightjets.back()->clone();
                        eventView->insertObject(lightjet);
                        eventView->insertObject(bjet);
                    }
                    else
                    {
                        lightjet=lightjets[0];
                        bjet=lightjets.back();
                    }
                    lightjets.erase(lightjets.begin());
                    lightjets.pop_back();
                    
                }
                else if (nbjets==njets)
                {
                    if (_outputEventViewName!=_inputEventViewNameJets)
                    {
                        lightjet=(pxl::Particle*)bjets.back()->clone();
                        bjet=(pxl::Particle*)bjets.front()->clone();
                        eventView->insertObject(lightjet);
                        eventView->insertObject(bjet);
                    }
                    else
                    {
                        lightjet=bjets.back();
                        bjet=bjets.front();
                    }
                    bjets.pop_back();
                    bjets.erase(bjets.begin());
                    
                }
                else
                {
                    if (_outputEventViewName!=_inputEventViewNameJets)
                    {
                        lightjet=(pxl::Particle*)lightjets[0]->clone();
                        bjet=(pxl::Particle*)bjets[0]->clone();
                        eventView->insertObject(lightjet);
                        eventView->insertObject(bjet);
                    }
                    else
                    {
                        lightjet=lightjets[0];
                        bjet=bjets[0];
                    }
                    lightjets.erase(lightjets.begin());
                    bjets.erase(bjets.begin());
                    
                }

                if (njets==2)
                {
                    if (nbjets==0) { category = C2J0T; }
                    if (nbjets==1) { category = C2J1T; }
                    if (nbjets==2) { category = C2J2T; }
                }
                else if (njets==3)
                {
                    if (nbjets==0) { category = C3J0T; }
                    if (nbjets==1) { category = C3J1T; }
                    if (nbjets==2) { category = C3J2T; }
                    if (nbjets==2) { category = C3J3T; }
                }   
                else
                {
                    category = OTHER;
                }
            }
            
            if (lightjet)
            {
                lightjet->setName("LightJet");
                const double absLEta = std::fabs(lightjet->getEta());
                eventView->setUserRecord("absLEta",absLEta);
                eventView->setUserRecord("absLEta_binned",5.2);
                for (unsigned int ibin = 1; ibin < jecBins.size(); ++ibin)
                { 
                    if (absLEta>jecBins[ibin-1] and absLEta<jecBins[ibin])
                    {
                        eventView->setUserRecord("absLEta_binned",0.5*(jecBins[ibin-1]+jecBins[ibin]));
                        break;
                    }
                }
            }
            
            for (pxl::Particle* p: lightjets)
            {
                pxl::Particle* pClone = nullptr;
                if (_outputEventViewName!=_inputEventViewNameJets)
                {
                    pClone = (pxl::Particle*)p->clone();
                    eventView->insertObject(pClone);
                }
                else
                {
                    pClone = p;
                }
                pClone->setName("LightJetAdd");
                
            }
            
            if (bjet)
            {
                bjet->setName("BJet");
            }
            for (pxl::Particle* p: bjets)
            {
                pxl::Particle* pClone = nullptr;
                if (_outputEventViewName!=_inputEventViewNameJets)
                {
                    pClone = (pxl::Particle*)p->clone();
                    eventView->insertObject(pClone);
                }
                else
                {
                    pClone = p;
                }
                pClone->setName("BJetAdd");
                
            }
            
            
            if (lepton and neutrino)
            {
                wboson = makeWboson(eventView,lepton,neutrino);
                eventView->setUserRecord(lepton->getName()+"_"+neutrino->getName()+"_dPhi",std::fabs(lepton->getVector().deltaPhi(&neutrino->getVector())));
                eventView->setUserRecord(lepton->getName()+"_"+neutrino->getName()+"_dEta",std::fabs(lepton->getVector().deltaEta(&neutrino->getVector())));
                eventView->setUserRecord(lepton->getName()+"_"+neutrino->getName()+"_dR",lepton->getVector().deltaR(&neutrino->getVector()));
            
                const double mtw_afterPz = calculateMTW(lepton,neutrino);
                eventView->setUserRecord("mtw_afterPz",mtw_afterPz);
            }
            
            if (lepton and neutrino and wboson and bjet)
            {
                top = makeTop(eventView,wboson,bjet);
                
                eventView->setUserRecord(lepton->getName()+"_"+bjet->getName()+"_dPhi",std::fabs(lepton->getVector().deltaPhi(&bjet->getVector())));
                eventView->setUserRecord(lepton->getName()+"_"+bjet->getName()+"_dEta",std::fabs(lepton->getVector().deltaEta(&bjet->getVector())));
                eventView->setUserRecord(lepton->getName()+"_"+bjet->getName()+"_dR",lepton->getVector().deltaR(&bjet->getVector()));
            }
            
            if (lepton and neutrino and wboson and bjet and top and lightjet)
            {   
                eventView->setUserRecord(lepton->getName()+"_"+lightjet->getName()+"_dPhi",std::fabs(lepton->getVector().deltaPhi(&lightjet->getVector())));
                eventView->setUserRecord(lepton->getName()+"_"+lightjet->getName()+"_dEta",std::fabs(lepton->getVector().deltaEta(&lightjet->getVector())));
                eventView->setUserRecord(lepton->getName()+"_"+lightjet->getName()+"_dR",lepton->getVector().deltaR(&lightjet->getVector()));
            
                makeCMSystem(eventView,"Shat",{bjet,lightjet,lepton,neutrino});
            }
            if (bjet and lightjet)
            {
                makeCMSystem(eventView,"Dijet",{bjet,lightjet});
                
                if (bjet->hasUserRecord("pullPhi") and bjet->hasUserRecord("pullY")
                   and lightjet->hasUserRecord("pullPhi") and lightjet->hasUserRecord("pullY")
                )
                {
                    const double bPt = bjet->getPt();
                    pxl::Basic3Vector bpull(
                        bPt*vdt::fast_cos(bjet->getPhi()+bjet->getUserRecord("pullPhi").toFloat()),
                        bPt*vdt::fast_sin(bjet->getPhi()+bjet->getUserRecord("pullPhi").toFloat()),
                        bPt*std::cosh(bjet->getEta()+bjet->getUserRecord("pullY").toFloat())
                    );
                    
                    const double lPt = lightjet->getPt();
                    pxl::Basic3Vector lpull(
                        lPt*vdt::fast_cos(lightjet->getPhi()+lightjet->getUserRecord("pullPhi").toFloat()),
                        lPt*vdt::fast_sin(lightjet->getPhi()+lightjet->getUserRecord("pullPhi").toFloat()),
                        lPt*std::cosh(lightjet->getEta()+lightjet->getUserRecord("pullY").toFloat())
                    );
                    
                    
                    eventView->setUserRecord("dijet_pull_angle",angle(bpull,lpull));
                    eventView->setUserRecord("dijet_angle",angle(bjet->getVector(),lightjet->getVector()));
                
                }
            }
            
            
            
            calculateAngles(eventView, "", lepton, neutrino, wboson, bjet, top, lightjet);
            
            return category;
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
                    
                    pxl::Particle* lepton = nullptr;
                    pxl::Particle* neutrino = nullptr;
                    std::vector<pxl::Particle*> bjets;
                    std::vector<pxl::Particle*> lightjets;
            
                    pxl::EventView* outputEventView = nullptr;
                    for (unsigned ieventView=0; ieventView<eventViews.size();++ieventView)
                    {
                        if (eventViews[ieventView]->getName()==_outputEventViewName)
                        {
                            outputEventView=eventViews[ieventView];
                            break;
                        }
                    }
                    if (!outputEventView)
                    {
                        outputEventView = event->create<pxl::EventView>();
                        outputEventView->setName(_outputEventViewName);
                    }
                    
                    for (unsigned ieventView=0; ieventView<eventViews.size();++ieventView)
                    {
                        pxl::EventView* inputEventView = eventViews[ieventView];
                        
                        
                            
                        std::vector<pxl::Particle*> particles;
                        inputEventView->getObjectsOfType(particles);
                        for (unsigned int iparticle = 0; iparticle<particles.size(); ++iparticle)
                        {
                            pxl::Particle* particle = particles[iparticle];
                            if (inputEventView->getName()==_inputEventViewNameLepton and particle->getName()==_leptonName)
                            {
                                if (lepton!=nullptr)
                                {
                                    throw std::runtime_error("Found multiple Leptons");
                                }
                                if (_inputEventViewNameLepton!=_outputEventViewName)
                                {
                                    lepton=(pxl::Particle*)particle->clone();
                                    outputEventView->insertObject(lepton);
                                }
                                else
                                {
                                    lepton=particle;
                                }
                            }
                            if (inputEventView->getName()==_inputEventViewNameNeutrino and particle->getName()==_neutrinoName)
                            {
                                if (neutrino!=nullptr)
                                {
                                    throw std::runtime_error("Found multiple Leptons");
                                }
                                if (_inputEventViewNameNeutrino!=_outputEventViewName)
                                {
                                    neutrino=(pxl::Particle*)particle->clone();
                                    outputEventView->insertObject(neutrino);
                                }
                                else
                                {
                                    neutrino=particle;
                                }
                            }
                            if (inputEventView->getName()==_inputEventViewNameJets)
                            {
                                if (std::find(_bJetNames.begin(),_bJetNames.end(), particle->getName())!=_bJetNames.end())
                                {
                                    bjets.push_back(particle);
                                }
                                else if (std::find(_lightJetNames.begin(),_lightJetNames.end(), particle->getName())!=_lightJetNames.end())
                                {
                                    lightjets.push_back(particle);
                                }
                            }
                        }
                    }
                    
                    if (lepton==nullptr or neutrino==nullptr)
                    {
                        _outputNoLepton->setTargets(event);
                        return _outputNoLepton->processTargets();
                    }
                    Category category = reconstructEvent(outputEventView,lepton,neutrino,lightjets,bjets);
                    if (_catToState[category].second)
                    {
                        _outputSelected->setTargets(event);
                        return _outputSelected->processTargets();
                    }
                    else
                    {
                        _outputVeto->setTargets(event);
                        return _outputVeto->processTargets();
                    }

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

const std::vector<double> TopReconstruction::jecBins = {
    0.0,0.2,0.4,0.6,0.8,1.0,1.2,1.4,1.6,1.8,2.0,2.4,2.6,2.8,3.0,3.5,4.0,4.4,5.0,5.4
};

PXL_MODULE_INIT(TopReconstruction)
PXL_PLUGIN_INIT
