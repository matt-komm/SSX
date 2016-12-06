#include <algorithm>
#include <fstream>
#include <set>
#include <sstream>
#include <streambuf>


#include "pxl/hep.hh"
#include "pxl/core.hh"
#include "pxl/core/macros.hh"
#include "pxl/core/PluginManager.hh"
#include "pxl/modules/Module.hh"
#include "pxl/modules/ModuleFactory.hh"

#include "isolation.h"

static pxl::Logger logger("MuonSelection");



class MuonSelection:
    public pxl::Module
{
    private:
        pxl::Source* _outputIsoSource;
        pxl::Source* _outputMidIsoSource;
        pxl::Source* _outputAntiIsoSource;
        pxl::Source* _outputOtherSource;

        std::string _inputEventViewName;
        std::string _inputMuonName;
        std::string _tightMuonName;
  
        /*Tight Muon Related Criteria*/
        double _pTMinTightMuon;  //Minimum transverse momentum
        double _etaMaxTightMuon; //Maximum pseudorapidity
        double _pfRelIsoTightMuon;
        double _pfRelMidIsoTightMuon;

      
        int64_t _numMuons;
        
        
        struct SortByPt
        {
            bool operator()(const pxl::Particle* p1, const pxl::Particle* p2) const
            {
                //sort descending
                return p1->getPt()>p2->getPt();
            }
        };
    public:
        MuonSelection():

            Module(),
            _inputEventViewName("Reconstructed"),
            _inputMuonName("Muon"),
            _tightMuonName("TightLepton"),

            _pTMinTightMuon(26),
            _etaMaxTightMuon(2.4),
            _pfRelIsoTightMuon(0.06),
            _pfRelMidIsoTightMuon(0.15),
            
            _numMuons(1)
        {
            addSink("input", "input");
            _outputIsoSource = addSource("1 iso muon", "iso");
            _outputMidIsoSource = addSource("1 mid-iso muon", "mid-iso");
            _outputAntiIsoSource = addSource("1 anti-iso muon", "anti-iso");
            _outputOtherSource = addSource("other", "other");

            addOption("Event view","name of the event view where muons are selected",_inputEventViewName);
            addOption("Input muon name","name of particles to consider for selection",_inputMuonName);
            addOption("Name of selected tight muons","",_tightMuonName);

            addOption("TightMuon Minimum pT","",_pTMinTightMuon);
            addOption("TightMuon Maximum Eta","",_etaMaxTightMuon);
            addOption("TightMuon Minimum Relative Iso","",_pfRelIsoTightMuon);
            addOption("TightMuon Minimum Relative MidIso","",_pfRelMidIsoTightMuon);
        
            addOption("number of muons","",_numMuons);
        }

        ~MuonSelection()
        {
        }

        // every Module needs a unique type
        static const std::string &getStaticType()
        {
            static std::string type ("MuonSelection");
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
            getOption("Event view",_inputEventViewName);
            getOption("Input muon name",_inputMuonName);
            getOption("Name of selected tight muons",_tightMuonName);

            getOption("TightMuon Minimum pT",_pTMinTightMuon);
            getOption("TightMuon Maximum Eta",_etaMaxTightMuon);
            getOption("TightMuon Minimum Relative Iso",_pfRelIsoTightMuon);
            getOption("TightMuon Minimum Relative MidIso",_pfRelMidIsoTightMuon);
        
            getOption("number of muons",_numMuons);
        }

        bool passesTightCriteria(pxl::Particle* particle)
        {
            if (not (particle->getPt()>_pTMinTightMuon))
            {
                return false;
            }
            if (not (fabs(particle->getEta())<_etaMaxTightMuon))
            {
                return false;
            }
            if (not particle->hasUserRecord("isTightMuon") || not particle->getUserRecord("isTightMuon"))
            {
                return false;
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
                    
                    pxl::EventView* eventView = nullptr;
                    
                    std::vector<pxl::Particle*> tightIsoMuons;
                    std::vector<pxl::Particle*> tightMidIsoMuons;
                    std::vector<pxl::Particle*> tightAntiIsoMuons;

                    for (unsigned ieventView=0; ieventView<eventViews.size();++ieventView)
                    {
                        eventView = eventViews[ieventView];
                        if (eventView->getName()==_inputEventViewName)
                        {
                            std::vector<pxl::Particle*> particles;
                            eventView->getObjectsOfType(particles);

                            for (unsigned iparticle=0; iparticle<particles.size();++iparticle)
                            {
                                pxl::Particle* particle = particles[iparticle];

                                if (particle->getName()==_inputMuonName)
                                {
                                    const float relIso = pfRelMuonIso(particle,0.5);
                                    particle->setUserRecord("relIso",relIso);
                                    if (passesTightCriteria(particle))
                                    {
                                        if (relIso<_pfRelIsoTightMuon)
                                        {
                                            //highly isolated muons
                                            tightIsoMuons.push_back(particle);
                                        }
                                        else if (relIso>_pfRelIsoTightMuon && relIso<_pfRelMidIsoTightMuon)
                                        {
                                            //intermediate isolated muons
                                            tightMidIsoMuons.push_back(particle);
                                        }
                                        else
                                        {
                                            //non-isolated muons
                                            tightAntiIsoMuons.push_back(particle);
                                        }
                                    }
                                }
                            }
                            break;
                        }
                    }
                    std::sort(tightIsoMuons.begin(),tightIsoMuons.end(),MuonSelection::SortByPt());
                    std::sort(tightMidIsoMuons.begin(),tightMidIsoMuons.end(),MuonSelection::SortByPt());
                    std::sort(tightAntiIsoMuons.begin(),tightAntiIsoMuons.end(),MuonSelection::SortByPt());
                    
                    //0=iso, 1=midiso, 2=looseiso, 3=other
                    
                    //N highly iso muon only
                    if (tightIsoMuons.size()==_numMuons)
                    {
                        for (pxl::Particle* p: tightIsoMuons)
                        {
                            p->setName(_tightMuonName);
                        }
                        eventView->setUserRecord("muoncat",0);
                        _outputIsoSource->setTargets(event);
                        return _outputIsoSource->processTargets();
                    }
                    //<N highly iso muon, rest intermediate iso muons
                    else if (tightIsoMuons.size()<_numMuons && (tightIsoMuons.size()+tightMidIsoMuons.size())==_numMuons)
                    {
                        for (pxl::Particle* p: tightIsoMuons)
                        {
                            p->setName(_tightMuonName);
                        }
                        for (pxl::Particle* p: tightMidIsoMuons)
                        {
                            p->setName(_tightMuonName);
                        }
                        eventView->setUserRecord("muoncat",1);
                        _outputMidIsoSource->setTargets(event);
                        return _outputMidIsoSource->processTargets();
                    }
                    //<N highly iso muon, <N intermediate iso muons, rest non-iso muon
                    else if (tightIsoMuons.size()<_numMuons && tightMidIsoMuons.size()<_numMuons && (tightIsoMuons.size()+tightMidIsoMuons.size()+tightAntiIsoMuons.size())==_numMuons)
                    {
                        for (pxl::Particle* p: tightIsoMuons)
                        {
                            p->setName(_tightMuonName);
                        }
                        for (pxl::Particle* p: tightMidIsoMuons)
                        {
                            p->setName(_tightMuonName);
                        }
                        for (pxl::Particle* p: tightAntiIsoMuons)
                        {
                            p->setName(_tightMuonName);
                        }
                        eventView->setUserRecord("muoncat",2);
                        _outputAntiIsoSource->setTargets(event);
                        return _outputAntiIsoSource->processTargets();
                    }
                    else
                    {
                        eventView->setUserRecord("muoncat",3);
                        _outputOtherSource->setTargets(event);
                        return _outputOtherSource->processTargets();
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

PXL_MODULE_INIT(MuonSelection)
PXL_PLUGIN_INIT

