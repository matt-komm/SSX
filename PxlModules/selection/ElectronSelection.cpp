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

static pxl::Logger logger("ElectronSelection");

class ElectronSelection:
    public pxl::Module
{
    private:
        pxl::Source* _outputTightSource;
        pxl::Source* _outputVetoSource;
        pxl::Source* _outputAntivetoSource;
        pxl::Source* _outputOtherSource;

        std::string _inputEventViewName;
        std::string _inputElectronName;
        std::string _tightElectronName;
  
        /*Tight Electron Related Criteria*/
        double _pTMinTightElectron;  //Minimum transverse momentum
        double _etaMaxTightElectron; //Maximum pseudorapidity

        std::string _hltPreselectionString;
        std::string _tightIdString;
        std::string _vetoIdString;
      
        int64_t _numElectrons;
        
        
        struct SortByPt
        {
            bool operator()(const pxl::Particle* p1, const pxl::Particle* p2) const
            {
                //sort descending
                return p1->getPt()>p2->getPt();
            }
        };
    public:
        ElectronSelection():

            Module(),
            _inputEventViewName("Reconstructed"),
            _inputElectronName("Electron"),
            _tightElectronName("TightLepton"),

            _pTMinTightElectron(35),
            _etaMaxTightElectron(2.1),
            
            _hltPreselectionString(""),
            _tightIdString("summer16eleIDTight25ns"),
            _vetoIdString("summer16eleIDVeto25ns"),
            
            _numElectrons(1)

        {
            addSink("input", "input");
            _outputTightSource = addSource("1 tight ele", "tight");
            _outputVetoSource = addSource("1 veto ele", "veto");
            _outputAntivetoSource = addSource("1 antiveto ele", "antiveto");
            _outputOtherSource = addSource("other", "other");

            addOption("Event view","name of the event view where electrons are selected",_inputEventViewName);
            addOption("Input electron name","name of particles to consider for selection",_inputElectronName);
            addOption("Name of selected tight electrons","",_tightElectronName);

            addOption("TightElectron Minimum pT","",_pTMinTightElectron);
            addOption("TightElectron Maximum Eta","",_etaMaxTightElectron);
            
            addOption("HLT ID","",_hltPreselectionString),
            addOption("tight ID","",_tightIdString),
            addOption("veto ID","",_vetoIdString),
 
        
            addOption("number of electrons","",_numElectrons);
        }

        ~ElectronSelection()
        {
        }

        // every Module needs a unique type
        static const std::string &getStaticType()
        {
            static std::string type ("ElectronSelection");
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
            getOption("Input electron name",_inputElectronName);
            getOption("Name of selected tight electrons",_tightElectronName);

            getOption("TightElectron Minimum pT",_pTMinTightElectron);
            getOption("TightElectron Maximum Eta",_etaMaxTightElectron);
            
            getOption("HLT ID",_hltPreselectionString),
            getOption("tight ID",_tightIdString),
            getOption("veto ID",_vetoIdString),
        
            getOption("number of electrons",_numElectrons);

        }
        
        bool passesTightCriteria(pxl::Particle* particle)
        {
            if (not particle->getUserRecord("passConversionVeto").toBool())
            {
                return false;
            }
            if (_hltPreselectionString.size()>0)
            {
                if (not particle->getUserRecord(_hltPreselectionString).toBool())
                {
                    return false;
                }
            }
            return particle->getUserRecord(_tightIdString).toBool();
            /*
            if (std::fabs(particle->getUserRecord("superClusterEta").toFloat())<1.479)
            {
                if (not (particle->getUserRecord("full5x5_sigmaIetaIeta").toFloat()<0.00998))
                {
                    return false;
                }
                if (not (particle->getUserRecord("deltaEtaSuperClusterTrackAtVtx").toFloat()<0.00308))
                {
                    return false;
                }
                if (not (particle->getUserRecord("deltaPhiSuperClusterTrackAtVtx").toFloat()<0.0816))
                {
                    return false;
                }
                if (not (particle->getUserRecord("hadronicOverEm").toFloat()<0.0414))
                {
                    return false;
                }
                if (not (particle->getUserRecord("ooEmooP").toFloat()<0.0129))
                {
                    return false;
                }
                if (not (particle->getUserRecord("numberOfMissingInnerHits").toInt32()<=1))
                {
                    return false;
                }
                if (not (particle->getUserRecord("passConversionVeto").toBool()==true))
                {
                    return false;
                }
                if (not (particle->getUserRecord("dxy").toFloat()<0.05))
                {
                    return false;
                }
                if (not (particle->getUserRecord("dz").toFloat()<0.10))
                {
                    return false;
                }
            }
            else
            {
                if (not (particle->getUserRecord("full5x5_sigmaIetaIeta").toFloat()<0.0292))
                {
                    return false;
                }
                if (not (particle->getUserRecord("deltaEtaSuperClusterTrackAtVtx").toFloat()<0.00605))
                {
                    return false;
                }
                if (not (particle->getUserRecord("deltaPhiSuperClusterTrackAtVtx").toFloat()<0.0394))
                {
                    return false;
                }
                if (not (particle->getUserRecord("hadronicOverEm").toFloat()<0.0641))
                {
                    return false;
                }
                if (not (particle->getUserRecord("ooEmooP").toFloat()<0.0129))
                {
                    return false;
                }
                if (not (particle->getUserRecord("numberOfMissingInnerHits").toInt32()<=1))
                {
                    return false;
                }
                if (not (particle->getUserRecord("passConversionVeto").toBool()==true))
                {
                    return false;
                }
                if (not (particle->getUserRecord("dxy").toFloat()<0.10))
                {
                    return false;
                }
                if (not (particle->getUserRecord("dz").toFloat()<0.20))
                {
                    return false;
                }
            }
            */
        }
        
        bool passesVetoCriteria(pxl::Particle* particle)
        {
            if (not particle->getUserRecord("passConversionVeto").toBool())
            {
                return false;
            }
            if (_hltPreselectionString.size()>0)
            {
                if (not particle->getUserRecord(_hltPreselectionString).toBool())
                {
                    return false;
                }
            }
            return particle->getUserRecord(_vetoIdString).toBool();
        }
        
        

        bool passesSelectionCriteria(pxl::Particle* particle)
        {
            if (not (particle->getPt()>_pTMinTightElectron))
            {
                return false;
            }
            if (not (fabs(particle->getEta())<_etaMaxTightElectron))
            {
                return false;
            }
            float scEta = particle->getUserRecord("superClusterEta").toFloat();
            if (std::fabs(scEta)>1.4442 && std::fabs(scEta)<1.5660)
            {
                return false;
            }
            
            if (std::fabs(scEta)<1.479)
            {
                if (not (particle->getUserRecord("dxy").toFloat()<0.05))
                {
                    return false;
                }
                if (not (particle->getUserRecord("dz").toFloat()<0.10))
                {
                    return false;
                }
            }
            else
            {
                if (not (particle->getUserRecord("dxy").toFloat()<0.10))
                {
                    return false;
                }
                if (not (particle->getUserRecord("dz").toFloat()<0.20))
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
                    
                    pxl::EventView* eventView = nullptr;
                    
                    std::vector<pxl::Particle*> tightEles;
                    std::vector<pxl::Particle*> vetoEles;
                    std::vector<pxl::Particle*> antivetoEles;

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

                                if (particle->getName()==_inputElectronName)
                                {
                                    if (passesSelectionCriteria(particle))
                                    {
                                        if (passesTightCriteria(particle))
                                        {
                                            tightEles.push_back(particle);
                                        }
                                        else if (passesVetoCriteria(particle))
                                        {
                                            vetoEles.push_back(particle);
                                        }
                                        else
                                        {
                                            antivetoEles.push_back(particle);
                                        }
                                    }
                                }
                            }
                            break;
                        }
                    }
                    std::sort(tightEles.begin(),tightEles.end(),ElectronSelection::SortByPt());
                    std::sort(vetoEles.begin(),vetoEles.end(),ElectronSelection::SortByPt());
                    std::sort(antivetoEles.begin(),antivetoEles.end(),ElectronSelection::SortByPt());
                    
                    //0=tight, 1=veto, 2=antiveto, 3=other
                    
                    //N tight ele only
                    if (tightEles.size()==_numElectrons)
                    {
                        for (pxl::Particle* p: tightEles)
                        {
                            p->setName(_tightElectronName);
                        }
                        eventView->setUserRecord("elecat",0);
                        _outputTightSource->setTargets(event);
                        return _outputTightSource->processTargets();
                    }
                    //<N tight ele, rest veto eles
                    else if (tightEles.size()<_numElectrons && (tightEles.size()+vetoEles.size())==_numElectrons)
                    {
                        for (pxl::Particle* p: tightEles)
                        {
                            p->setName(_tightElectronName);
                        }
                        for (pxl::Particle* p: vetoEles)
                        {
                            p->setName(_tightElectronName);
                        }
                        eventView->setUserRecord("elecat",1);
                        _outputVetoSource->setTargets(event);
                        return _outputVetoSource->processTargets();
                    }
                    //<N tight ele, <N veto eles, rest antiveto ele
                    else if (tightEles.size()<_numElectrons && vetoEles.size()<_numElectrons && (tightEles.size()+vetoEles.size()+antivetoEles.size())==_numElectrons)
                    {
                        for (pxl::Particle* p: tightEles)
                        {
                            p->setName(_tightElectronName);
                        }
                        for (pxl::Particle* p: vetoEles)
                        {
                            p->setName(_tightElectronName);
                        }
                        for (pxl::Particle* p: antivetoEles)
                        {
                            p->setName(_tightElectronName);
                        }
                        eventView->setUserRecord("elecat",2);
                        _outputAntivetoSource->setTargets(event);
                        return _outputAntivetoSource->processTargets();
                    }
                    else
                    {
                        eventView->setUserRecord("elecat",3);
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

PXL_MODULE_INIT(ElectronSelection)
PXL_PLUGIN_INIT

