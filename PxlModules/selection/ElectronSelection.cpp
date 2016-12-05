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
        pxl::Source* _outputIsoSource;
        pxl::Source* _outputMidIsoSource;
        pxl::Source* _outputAntiIsoSource;
        pxl::Source* _outputOtherSource;

        std::string _inputEventViewName;
        std::string _inputElectronName;
        std::string _tightElectronName;
  
        /*Tight Electron Related Criteria*/
        double _pTMinTightElectron;  //Minimum transverse momentum
        double _etaMaxTightElectron; //Maximum pseudorapidity
        double _pfRelRelIsoTightElectron; //relIso relative to tight WP
        double _pfRelRelMidIsoTightElectron; //relIso relative to tight WP

      
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

            _pTMinTightElectron(24),
            _etaMaxTightElectron(2.4),
            _pfRelRelIsoTightElectron(1.0),
            _pfRelRelMidIsoTightElectron(2.0),
            
            _numElectrons(1)

        {
            addSink("input", "input");
            _outputIsoSource = addSource("1 iso ele", "iso");
            _outputMidIsoSource = addSource("1 mid-iso ele", "mid-iso");
            _outputAntiIsoSource = addSource("1 anti-iso ele", "anti-iso");
            _outputOtherSource = addSource("other", "other");

            addOption("Event view","name of the event view where electrons are selected",_inputEventViewName);
            addOption("Input electron name","name of particles to consider for selection",_inputElectronName);
            addOption("Name of selected tight electrons","",_tightElectronName);

            addOption("TightElectron Minimum pT","",_pTMinTightElectron);
            addOption("TightElectron Maximum Eta","",_etaMaxTightElectron);
            addOption("TightElectron Minimum Rel Relative Iso","",_pfRelRelIsoTightElectron);
            addOption("TightElectron Minimum Rel Relative MidIso","",_pfRelRelMidIsoTightElectron);
        
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
            getOption("TightElectron Minimum Rel Relative Iso",_pfRelRelIsoTightElectron);
            getOption("TightElectron Minimum Rel Relative MidIso",_pfRelRelMidIsoTightElectron);
        
            getOption("number of electrons",_numElectrons);

        }

        bool passesTightCriteria(pxl::Particle* particle)
        {
            if (not (particle->getPt()>_pTMinTightElectron))
            {
                return false;
            }
            if (not (fabs(particle->getEta())<_etaMaxTightElectron))
            {
                return false;
            }
            
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
                    
                    std::vector<pxl::Particle*> tightIsoEles;
                    std::vector<pxl::Particle*> tightMidIsoEles;
                    std::vector<pxl::Particle*> tightAntiIsoEles;

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
                                    const float relrelIso = pfRelRelElectronIso(particle,0.0588,0.0571);
                                    particle->setUserRecord("relrelIso",relrelIso);
                                    if (passesTightCriteria(particle))
                                    {
                                        if (relrelIso<_pfRelRelIsoTightElectron)
                                        {
                                            //highly isolated electrons
                                            tightIsoEles.push_back(particle);
                                        }
                                        else if (relrelIso>_pfRelRelIsoTightElectron && relrelIso<_pfRelRelMidIsoTightElectron)
                                        {
                                            //intermediate isolated electrons
                                            tightMidIsoEles.push_back(particle);
                                        }
                                        else
                                        {
                                            //non-isolated electrons
                                            tightAntiIsoEles.push_back(particle);
                                        }
                                    }
                                }
                            }
                            break;
                        }
                    }
                    std::sort(tightIsoEles.begin(),tightIsoEles.end(),ElectronSelection::SortByPt());
                    std::sort(tightMidIsoEles.begin(),tightMidIsoEles.end(),ElectronSelection::SortByPt());
                    std::sort(tightAntiIsoEles.begin(),tightAntiIsoEles.end(),ElectronSelection::SortByPt());
                    
                    //0=iso, 1=midiso, 2=looseiso, 3=other
                    
                    //N highly iso ele only
                    if (tightIsoEles.size()==_numElectrons)
                    {
                        for (pxl::Particle* p: tightIsoEles)
                        {
                            p->setName(_tightElectronName);
                        }
                        eventView->setUserRecord("elecat",0);
                        _outputIsoSource->setTargets(event);
                        return _outputIsoSource->processTargets();
                    }
                    //<N highly iso ele, rest intermediate iso eles
                    else if (tightIsoEles.size()<_numElectrons && (tightIsoEles.size()+tightMidIsoEles.size())==_numElectrons)
                    {
                        for (pxl::Particle* p: tightIsoEles)
                        {
                            p->setName(_tightElectronName);
                        }
                        for (pxl::Particle* p: tightMidIsoEles)
                        {
                            p->setName(_tightElectronName);
                        }
                        eventView->setUserRecord("elecat",1);
                        _outputMidIsoSource->setTargets(event);
                        return _outputMidIsoSource->processTargets();
                    }
                    //<N highly iso ele, <N intermediate iso eles, rest non-iso ele
                    else if (tightIsoEles.size()<_numElectrons && tightMidIsoEles.size()<_numElectrons && (tightIsoEles.size()+tightMidIsoEles.size()+tightAntiIsoEles.size())==_numElectrons)
                    {
                        for (pxl::Particle* p: tightIsoEles)
                        {
                            p->setName(_tightElectronName);
                        }
                        for (pxl::Particle* p: tightMidIsoEles)
                        {
                            p->setName(_tightElectronName);
                        }
                        for (pxl::Particle* p: tightAntiIsoEles)
                        {
                            p->setName(_tightElectronName);
                        }
                        eventView->setUserRecord("elecat",2);
                        _outputAntiIsoSource->setTargets(event);
                        return _outputAntiIsoSource->processTargets();
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

