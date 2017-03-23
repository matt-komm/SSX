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

static pxl::Logger logger("ElectronSF");

class ElectronSF:
    public pxl::Module
{
    private:
        struct ScaleFactor
        {
            std::string prefix;
            
            std::string fileName;
            std::string histogramName;
            double additionalUncertainty;
            
            TH2* rootHistogramPtEta;
            
            ScaleFactor(
                pxl::Module* module,
                const std::string& prefix
            ):
                prefix(prefix),
                fileName(),
                histogramName(),
                additionalUncertainty(0),
                rootHistogramPtEta(nullptr)
            {
                module->addOption(prefix+" file name","","",pxl::OptionDescription::USAGE_FILE_OPEN);
                module->addOption(prefix+" hist name","","");
                module->addOption(prefix+" add uncertainty", "", 0.0);
            }
            
            void init(pxl::Module* module)
            {
                module->getOption(prefix+" file name",fileName);
                module->getOption(prefix+" hist name",histogramName);
                module->getOption(prefix+" add uncertainty", additionalUncertainty);
                
                fileName = module->getAnalysis()->findFile(fileName);
            
                TFile rootFile(fileName.c_str());
                if ((not rootFile.IsOpen()) or (rootFile.GetSize()==0))
                {
                    throw std::runtime_error("SF file '"+fileName+"' does not exits!");
                }
                TH2* h = dynamic_cast<TH2*>(rootFile.Get(histogramName.c_str()));
                if (!h)
                {
                    throw std::runtime_error("Histogram '"+histogramName+"' does not exist in file '"+fileName+"'");
                }
                if (h->GetXaxis()->GetXmax()>50.0 and h->GetYaxis()->GetXmax()<5.0)
                {
                    rootHistogramPtEta = (TH2*)h->Clone((std::string("histMuonSF")+std::to_string(std::rand())).c_str());
                    rootHistogramPtEta->SetDirectory(0);
                }
                else
                {
                    throw std::runtime_error("Histogram '"+histogramName+"' in file '"+fileName+"' does not seem to be binned x=pt and y=eta");
                }
            }
            
            float getScaleFactor(double pt, double eta,int shift=0)
            {
                if (rootHistogramPtEta)
                {
                    int xbin = rootHistogramPtEta->GetXaxis()->FindBin(pt);
                    int ybin = rootHistogramPtEta->GetYaxis()->FindBin(fabs(eta));
                    if (xbin<=0)
                    {
                        throw std::runtime_error("Got muon with pt="+std::to_string(pt)+" that underflows the SF histogram '"+histogramName+"'");
                    }
                    else if (xbin>rootHistogramPtEta->GetXaxis()->GetNbins())
                    {
                        xbin=rootHistogramPtEta->GetXaxis()->GetNbins();
                    }
                    if (ybin<=0)
                    {
                        throw std::runtime_error("Got muon with eta="+std::to_string(eta)+" that underflows the SF histogram '"+histogramName+"'");
                    }
                    else if (ybin>rootHistogramPtEta->GetYaxis()->GetNbins())
                    {
                        ybin=rootHistogramPtEta->GetYaxis()->GetNbins();
                    }
                    float sf = rootHistogramPtEta->GetBinContent(xbin,ybin);
                    if (sf<0.1)
                    {
                        throw std::runtime_error("Got muon SF of "+std::to_string(sf)+"(<0.1) for pt="+std::to_string(pt)+" eta="+std::to_string(eta)+" from histogram '"+histogramName+"'");
                    }
                    if (shift>=1)
                    {
                        sf += fabs(rootHistogramPtEta->GetBinError(xbin,ybin))+fabs(additionalUncertainty);
                    }
                    else if (shift<=-1)
                    {
                        sf -= fabs(rootHistogramPtEta->GetBinError(xbin,ybin))+fabs(additionalUncertainty);
                    }
                    return sf;
                }
                else
                {
                    throw std::runtime_error("Histogram '"+histogramName+"' not yet read from file or it has been deleted");
                }
            }
        };
    
        std::string _eventViewName;
        std::string _electronName;
        std::string _sfName;
        std::string _electronCatgeory;
        std::string _electronMatchingFlag;
        
        bool _failIfNoLepton;
        
        pxl::Source* _outputSource;
        
        
        ScaleFactor* _scaleFactor;
        
    public:
        ElectronSF():
            Module(),
            _eventViewName("Reconstructed"),
            _electronName("TightLepton"),
            _sfName("iso"),
            _electronCatgeory("elecat"),
            _failIfNoLepton(true),
            _electronMatchingFlag("")
        {
            addSink("input", "input");
            addOption("event view name", "", _eventViewName);
            addOption("lepton name", "", _electronName);
            addOption("SF name", "", _sfName);
            //for dimuon events triggered with single mu trigger one needs to apply
            //trigger Sf only to the one matched to the trigger
            //id&iso to both since they passed the selection
            addOption("selection flag","",_electronCatgeory);
            addOption("matching flag", "", _electronMatchingFlag);
            
            addOption("fail if no lepton found", "", _failIfNoLepton);
            
            _outputSource = addSource("output","output");
            
            _scaleFactor=new ScaleFactor(this,"SF");
        }

        ~ElectronSF()
        {
        }

        // every Module needs a unique type
        static const std::string &getStaticType()
        {
            static std::string type ("ElectronSF");
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
            getOption("lepton name", _electronName);
            getOption("SF name", _sfName);
            //for dimuon events triggered with single mu trigger one needs to apply
            //trigger Sf only to the one matched to the trigger
            //id&iso to both since they passed the selection
            getOption("selection flag",_electronCatgeory);
            getOption("matching flag", _electronMatchingFlag);
            
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
                            
                            if (eventView->hasUserRecord(_electronCatgeory) and eventView->getUserRecord(_electronCatgeory).toInt32()==0)
                            {
                                int nElectrons = 0;
                                std::vector<pxl::Particle*> particles;
                                eventView->getObjectsOfType(particles);
                                for (pxl::Particle* particle: particles)
                                {
                                    if (particle->getName()==_electronName)
                                    {
                                        if (_electronMatchingFlag.size()>0)
                                        {
                                            if (particle->hasUserRecord(_electronMatchingFlag) and particle->getUserRecord(_electronMatchingFlag).toBool())
                                            {
                                                ++nElectrons;
                                                nominalSF *= _scaleFactor->getScaleFactor(particle->getPt(),particle->getEta(),0);
                                                upSF *= _scaleFactor->getScaleFactor(particle->getPt(),particle->getEta(),1);
                                                downSF *= _scaleFactor->getScaleFactor(particle->getPt(),particle->getEta(),-1);
                                            }
                                        }
                                        else
                                        {
                                            ++nElectrons;
                                            nominalSF *= _scaleFactor->getScaleFactor(particle->getPt(),particle->getEta(),0);
                                            upSF *= _scaleFactor->getScaleFactor(particle->getPt(),particle->getEta(),1);
                                            downSF *= _scaleFactor->getScaleFactor(particle->getPt(),particle->getEta(),-1);
                                        }
                                    }
                                }
                                if (_failIfNoLepton and nElectrons==0)
                                {
                                    throw std::runtime_error("No electrons with name '"+_electronName+"' for scale factors found");
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


PXL_MODULE_INIT(ElectronSF)
PXL_PLUGIN_INIT
