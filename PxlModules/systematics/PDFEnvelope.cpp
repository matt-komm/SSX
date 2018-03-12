#include "pxl/hep.hh"
#include "pxl/core.hh"
#include "pxl/core/macros.hh"
#include "pxl/core/PluginManager.hh"
#include "pxl/modules/Module.hh"
#include "pxl/modules/ModuleFactory.hh"

#include <string>
#include <vector>
#include <unordered_map>
#include <stdexcept>
#include <cstdlib>
#include <regex>

#include "TH3.h"
#include "TFile.h"
#include "TKey.h"

static pxl::Logger logger("PDFEnvelope");

class PDFEnvelope:
    public pxl::Module
{
    private:
        
    
        std::string _histFile;
        
        pxl::Source* _outputSource;
        
        std::unordered_map<std::string,std::shared_ptr<TH3>> _histsUp; 
        std::unordered_map<std::string,std::shared_ptr<TH3>> _histsDown;
        

    public:
        PDFEnvelope():
            Module(),
            _histFile()
        {
            addSink("input", "input");
            
            addOption("pdfHistFile", "", _histFile,pxl::OptionDescription::USAGE_FILE_OPEN);
            
            _outputSource = addSource("output","output");

        }

        ~PDFEnvelope()
        {
        }

        // every Module needs a unique type
        static const std::string &getStaticType()
        {
            static std::string type ("PDFEnvelope");
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
            getOption("pdfHistFile", _histFile);

            TFile rootFile(getAnalysis()->findFile(_histFile).c_str());
            if (not rootFile.IsOpen())
            {
                throw std::runtime_error("Cannot open file: "+_histFile);
            }
            TList* keyList = rootFile.GetListOfKeys();
            TIterator* it = keyList->MakeIterator();
            TObject* obj;
            std::set<std::string> keys;
            while(obj= it->Next())
            {
                keys.insert(((TKey*)obj)->GetName());
            }
            for (const std::string& key: keys)
            {
                TH3* histUp = dynamic_cast<TH3*>(rootFile.Get((key+"/upShift").c_str()));
                if (not histUp)
                {
                    throw std::runtime_error("Variation '"+key+"/upShift' not found in file '"+_histFile+"'");
                }
                TH3* histDown = dynamic_cast<TH3*>(rootFile.Get((key+"/downShift").c_str()));
                if (not histDown)
                {
                    throw std::runtime_error("Variation '"+key+"/downShift' not found in file '"+_histFile+"'");
                }
                histUp = dynamic_cast<TH3*>(histUp->Clone((key+"_upShift").c_str()));
                histDown = dynamic_cast<TH3*>(histDown->Clone((key+"_downShift").c_str()));
                
                _histsUp[key].reset(histUp);
                _histsUp[key]->SetDirectory(0);
                _histsDown[key].reset(histDown);
                _histsDown[key]->SetDirectory(0);
            }
            rootFile.Close();
        }
        
        
        bool analyse(pxl::Sink *sink) throw (std::runtime_error)
        {
            
            try
            {
                pxl::Event *event  = dynamic_cast<pxl::Event*>(sink->get());
                if (event)
                {
                    std::string processName = event->getUserRecord("ProcessName");
                    
                    auto it = _histsUp.find(processName);
                    float pdfUp = 1.;
                    float pdfDown = 1.;
                    if (it!=_histsUp.end())
                    {
                    
                        float mtw = -1;
                        float lpt = -1;
                        float ljeta = -1;
                        //SingleTop_1__Top_1__Mass:SingleTop_1__absLEta:SingleTop_1__mtw_beforePz
                        std::vector<pxl::EventView*> eventViews;
                        event->getObjectsOfType(eventViews);
                        for (pxl::EventView* eventView: eventViews)
                        {
                            if (eventView->getName()=="SingleTop")
                            {
                                if (eventView->hasUserRecord("mtw_beforePz"))
                                {
                                    mtw = eventView->getUserRecord("mtw_beforePz").toFloat();
                                }
                                if (eventView->hasUserRecord("absLEta"))
                                {
                                    ljeta = eventView->getUserRecord("absLEta").toFloat();
                                }
                                std::vector<pxl::Particle*> particles;
                                eventView->getObjectsOfType(particles);
                                for (pxl::Particle* particle: particles)
                                {
                                    if (particle->getName()=="TightLepton")
                                    {
                                        lpt = particle->getPt();
                                        //std::cout<<"lpt: "<<lpt<<std::endl;
                                        break;
                                    }
                                }
                                break;
                            }
                        }
                        if (mtw>0 and lpt>0 and ljeta>0)
                        {
                            const std::shared_ptr<TH3>& histUp = _histsUp.at(processName);
                            const std::shared_ptr<TH3>& histDown = _histsDown.at(processName);
                            int xbin = histUp->GetXaxis()->FindBin(mtw);
                            int ybin = histUp->GetYaxis()->FindBin(ljeta);
                            int zbin = histUp->GetZaxis()->FindBin(lpt);
                            if (xbin>0 and xbin<=histUp->GetNbinsX() and ybin>0 and ybin<=histUp->GetNbinsY() and zbin>0 and zbin<=histUp->GetNbinsZ())
                            {
                                pdfUp = histUp->GetBinContent(xbin,ybin,zbin);
                                pdfDown = histDown->GetBinContent(xbin,ybin,zbin);
                            }
                        }
                    }
                    event->setUserRecord("pdfUp",pdfUp);
                    event->setUserRecord("pdfDown",pdfDown);
                    
                    
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


PXL_MODULE_INIT(PDFEnvelope)
PXL_PLUGIN_INIT
