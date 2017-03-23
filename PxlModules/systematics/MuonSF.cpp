#include "pxl/hep.hh"
#include "pxl/core.hh"
#include "pxl/core/macros.hh"
#include "pxl/core/PluginManager.hh"
#include "pxl/modules/Module.hh"
#include "pxl/modules/ModuleFactory.hh"

#include <string>
#include <vector>
#include <stdexcept>
#include <cstdlib>

#include "TH2.h"
#include "TFile.h"

#include "SFReader.hh"

static pxl::Logger logger("MuonSF");

class MuonSF:
    public pxl::Module
{
    private:

            
        std::string _eventViewName;
        std::string _muonName;
        std::string _sfName;
        std::string _muonCatgeory;
        std::string _muonMatchingFlag;
        
        bool _failIfNoLepton;
        
        pxl::Source* _outputSource;
        
        
        SFReader* _scaleFactor;
        
    public:
        MuonSF():
            Module(),
            _eventViewName("Reconstructed"),
            _muonName("TightLepton"),
            _sfName("iso"),
            _muonCatgeory("muoncat"),
            _muonMatchingFlag(""),
            _failIfNoLepton(true)
        {
            addSink("input", "input");
            addOption("event view name", "", _eventViewName);
            addOption("muon name", "", _muonName);
            addOption("SF name", "", _sfName);
            //for dimuon events triggered with single mu trigger one needs to apply
            //trigger Sf only to the one matched to the trigger
            //id&iso to both since they passed the selection
            addOption("selection flag","",_muonCatgeory);
            addOption("muon matching flag", "", _muonMatchingFlag);
            
            addOption("fail if no lepton found", "", _failIfNoLepton);
            
            _outputSource = addSource("output","output");
            
            _scaleFactor=new SFReader(this,"SF");
        }

        ~MuonSF()
        {
        }

        // every Module needs a unique type
        static const std::string &getStaticType()
        {
            static std::string type ("MuonSF");
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
            getOption("muon name", _muonName);
            getOption("SF name", _sfName);
            //for dimuon events triggered with single mu trigger one needs to apply
            //trigger Sf only to the one matched to the trigger
            //id&iso to both since they passed the selection
            getOption("selection flag",_muonCatgeory);
            getOption("muon matching flag", _muonMatchingFlag);
            
            getOption("fail if no lepton found", _failIfNoLepton);

            _scaleFactor->init(this);
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
                            double nominalSF = 1.0;
                            double upSF = 1.0;
                            double downSF = 1.0;
                            
                            if (eventView->hasUserRecord(_muonCatgeory) and eventView->getUserRecord(_muonCatgeory).toInt32()==0)
                            {
                                int nMuons = 0;
                                std::vector<pxl::Particle*> particles;
                                eventView->getObjectsOfType(particles);
                                for (pxl::Particle* particle: particles)
                                {
                                    if (particle->getName()==_muonName)
                                    {
                                        if (_muonMatchingFlag.size()>0)
                                        {
                                            if (particle->hasUserRecord(_muonMatchingFlag) and particle->getUserRecord(_muonMatchingFlag).toBool())
                                            {
                                                ++nMuons;
                                                auto sfAndError = _scaleFactor->getSFAndError(particle->getPt(),std::fabs(particle->getEta()));
                                                nominalSF *= sfAndError.first;
                                                upSF *= sfAndError.first+sfAndError.second;
                                                downSF *= sfAndError.first-sfAndError.second;
                                            }
                                        }
                                        else
                                        {
                                            ++nMuons;
                                            auto sfAndError = _scaleFactor->getSFAndError(particle->getPt(),std::fabs(particle->getEta()));
                                            nominalSF *= sfAndError.first;
                                            upSF *= sfAndError.first+sfAndError.second;
                                            downSF *= sfAndError.first-sfAndError.second;
                                        }
                                    }
                                }
                                if (_failIfNoLepton and nMuons==0)
                                {
                                    throw std::runtime_error("No muons with name '"+_muonName+"' for scale factors found");
                                }
                            }
                            eventView->setUserRecord(_sfName+"_SF_nominal",nominalSF),
                            eventView->setUserRecord(_sfName+"_SF_up",upSF);
                            eventView->setUserRecord(_sfName+"_SF_down",downSF);
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


PXL_MODULE_INIT(MuonSF)
PXL_PLUGIN_INIT
