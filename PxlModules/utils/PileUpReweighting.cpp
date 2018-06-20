#include "pxl/hep.hh"
#include "pxl/core.hh"
#include "pxl/core/macros.hh"
#include "pxl/core/PluginManager.hh"
#include "pxl/modules/Module.hh"
#include "pxl/modules/ModuleFactory.hh"

#include <string>
#include <iostream>
#include <cstdlib>
#include <unordered_map>

#include "TFile.h"
#include "TH1F.h"
#include "TCanvas.h"

static pxl::Logger logger("PileUpReweighting");


class PileUpReweighting:
    public pxl::Module
{
    private:
        pxl::Source* _outputSource;
        
        std::string _mcFile;
        std::string _mcHistName;
        std::string _defaultMCHistName;
        int64_t _rebinMC;
        
        std::vector<std::string> _dataFiles;
        std::string _dataHistName;
        
        
        
        std::unordered_map<std::string,std::vector<std::pair<std::string,TH1F>>> _reweightingHists;
        
        unsigned int _N;
        std::unordered_map<std::string,std::vector<double>> _means;

    public:
    
        PileUpReweighting():
            Module(),
            _rebinMC(1),
            _N(0)
        {
            addSink("input", "input");
            _outputSource = addSource("output","output");
            
            addOption("mc histogram file","file containing the number of PU interactions in MC",_mcFile,pxl::OptionDescription::USAGE_FILE_OPEN);
            addOption("mc histogram name","",_mcHistName);
            addOption("mc default histogram name","",_defaultMCHistName);
            addOption("mc rebin","",_rebinMC);
            
            addOption("data histogram files","files containing the number of PU interactions in data",_dataFiles,pxl::OptionDescription::USAGE_FILE_OPEN);
            addOption("data histogram name","",_dataHistName);
        }

        ~PileUpReweighting()
        {
        }

        // every Module needs a unique type
        static const std::string &getStaticType()
        {
            static std::string type ("PileUpReweighting");
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
            getOption("mc histogram file",_mcFile);
            getOption("mc histogram name",_mcHistName);
            getOption("mc default histogram name",_defaultMCHistName);
            getOption("mc rebin",_rebinMC);
            
            getOption("data histogram files",_dataFiles);
            getOption("data histogram name",_dataHistName);
            
            _mcFile = getAnalysis()->findFile(_mcFile);
            
            
            
            TFile mcFile(_mcFile.c_str());
            
            std::vector<std::pair<std::string,TH1F>> mcHists;
            auto keys = mcFile.GetListOfKeys();
            for (int ikey = 0; ikey < keys->GetSize(); ++ikey)
            { 
                const char* histName = keys->At(ikey)->GetName();
                TH1F* histMC = (TH1F*)mcFile.Get(histName);
                if (histMC->GetEntries()<1000)
                {
                    logger(pxl::LOG_LEVEL_INFO,getName()+": PU histogram from file '"+_mcFile+"' with name '"+std::string(histName)+"' contains only "+std::to_string(histMC->GetEntries())+" entires -> skipped and take default!");
                    continue;
                }
                histMC->SetDirectory(0);
                histMC->Rebin(_rebinMC);
                histMC->Scale(histMC->GetNbinsX()/histMC->Integral());
                mcHists.emplace_back(std::string(histName),*histMC);
                
                
            }
            if (mcHists.size()==0)
            {
                throw std::runtime_error(getName()+": No mc histograms for PU reweighting loaded");
            }
            TH1F* histMC = &mcHists[0].second;
            /*
            TH1* histMC = dynamic_cast<TH1*>(mcFile.Get(_mcHistName.c_str()));
            if (not histMC)
            {
                throw std::runtime_error(getName()+": Failed to retrieve MC PU histogram from file '"+_mcFile+"' with name '"+_mcHistName+"'");
            }
            if (histMC->GetEntries()<10)
            {
                throw std::runtime_error(getName()+": PU histogram from file '"+_mcFile+"' with name '"+_mcHistName+"' contains only "+std::to_string(histMC->GetEntries())+" entires.");
            }*/
            //histMC->SetDirectory(0); delete with file closing
            
            
            
            for (unsigned int idataFile = 0; idataFile < _dataFiles.size(); ++idataFile)
            {
                _dataFiles[idataFile] = getAnalysis()->findFile(_dataFiles[idataFile]);
                TFile dataFile(_dataFiles[idataFile].c_str());
                TH1* histData = dynamic_cast<TH1*>(dataFile.Get(_dataHistName.c_str()));
                if (not histData)
                {
                    throw std::runtime_error(getName()+": Failed to retrieve data PU histogram from file '"+_dataFiles[idataFile]+"' with name '"+_dataHistName+"'");
                }
                if (histData->GetEntries()<10)
                {
                    throw std::runtime_error(getName()+": PU histogram from file '"+_dataFiles[idataFile]+"' with name '"+_dataHistName+"' contains only "+std::to_string(histData->GetEntries())+" entires.");
                }
                histData->Scale(histData->GetNbinsX()/histData->Integral());
                
                const int pos = _dataFiles[idataFile].find_last_of('/')+1;
                const int end = _dataFiles[idataFile].find_first_of('.',pos+1);
                std::string puName = std::string(_dataFiles[idataFile],pos,end-pos);
                for (auto& mcHist: mcHists)
                {
                    std::vector<std::pair<std::string,TH1F>> hists;
                    hists.push_back(
                        std::make_pair(
                            puName,
                            TH1F(
                                (std::string("reweightingHist")+mcHist.first+std::to_string(idataFile)+std::to_string(std::rand())).c_str(),
                                ";N true interactions; weight",
                                std::max<int>(histMC->GetNbinsX(),histData->GetNbinsX()),
                                histMC->GetXaxis()->GetXmin(),
                                histMC->GetXaxis()->GetXmax()
                            )
                        )
                    );
                    TH1F& weightHist = hists.back().second;
                    weightHist.SetDirectory(0);
                    
                
                    for (unsigned int ibin = 0; ibin < weightHist.GetNbinsX(); ++ibin)
                    {
                        const double binCenter = weightHist.GetBinCenter(ibin+1);
                        
                        
                        const double puMC = mcHist.second.GetBinContent(mcHist.second.FindBin(binCenter));
                        const double puData = histData->GetBinContent(histData->FindBin(binCenter));

                        
                        //cut off events with too less statistics <0.01% or unphysical weights >10
                        if (puMC>0.0001 and (puData/puMC)<10)
                        {
                            weightHist.SetBinContent(ibin+1,puData/puMC);
                        }
                        
                    }
                    
                    _reweightingHists[mcHist.first] = hists;
                    _means[mcHist.first] = std::vector<double>(0,_dataFiles.size());
                }
                dataFile.Close();
            }
            
            mcFile.Close();
            
            
            
        }

        bool analyse(pxl::Sink *sink) throw (std::runtime_error)
        {
            try
            {
                pxl::Event *event  = dynamic_cast<pxl::Event*>(sink->get());
                if (event)
                {
                    ++_N;
                    
                    const pxl::BasicNVector* trueInteractions = nullptr;
                    pxl::EventView* recoEventView = nullptr;
                
                    std::vector<pxl::EventView*> eventViews;
                    event->getObjectsOfType(eventViews);
                    for (unsigned ieventView=0; ieventView<eventViews.size();++ieventView)
                    {
                        if (eventViews[ieventView]->getName()=="Reconstructed")
                        {
                            recoEventView=eventViews[ieventView];
                            std::vector<pxl::Particle*> particles;
                            eventViews[ieventView]->getObjectsOfType(particles);

                            for (unsigned int iparticle = 0; iparticle<particles.size(); ++iparticle)
                            {
                                pxl::Particle* particle = particles[iparticle];
                                if (particle->getName()=="PU")
                                {
                                    trueInteractions = dynamic_cast<const pxl::BasicNVector*>(&particle->getUserRecord("nTrueInteractions0").asSerializable());
                                }
                            }
                        }
                    }
                    
                    if (trueInteractions)
                    {
                        const double ntrueInteractionsAtBX0 = trueInteractions->getElement(1);
                        
                        
                        std::string processName = event->getUserRecord("ProcessName").asString();
                        
                        std::vector<std::pair<std::string,TH1F>> processReweightingHists;
                        auto it = _reweightingHists.find(processName);
                        if (it==_reweightingHists.end())
                        {
                            if (_reweightingHists.find(_defaultMCHistName)==_reweightingHists.end())
                            {
                                throw std::runtime_error("Cannot find default mc hist '"+_defaultMCHistName+"' in mc pileup file");
                            }
                            processReweightingHists = _reweightingHists[_defaultMCHistName];
                            processName = _defaultMCHistName;
                        }
                        else
                        {
                            processReweightingHists = it->second;
                        }
                        
                        
                        for (unsigned int ihist = 0; ihist < processReweightingHists.size(); ++ihist)
                        {
                            
                            if (ntrueInteractionsAtBX0<processReweightingHists[ihist].second.GetNbinsX())
                            {
                                const int bin = processReweightingHists[ihist].second.FindBin(ntrueInteractionsAtBX0);
                                float weight = processReweightingHists[ihist].second.GetBinContent(bin);
                                if (std::isnan(weight) or std::isinf(weight))
                                {
                                      weight = 1.0;
                                }
                                recoEventView->setUserRecord(processReweightingHists[ihist].first+"_weight",weight);
                                _means[processName][ihist]+=weight;
                            }
                            else
                            {
                                recoEventView->setUserRecord(processReweightingHists[ihist].first+"_weight",1.0);
                                _means[processName][ihist]+=1;
                            }
                            
                            //sanity check
                            if (((_N%1000)==0) and (_N>=1000) and (_means[processName][ihist]/_N-1)*(_means[processName][ihist]/_N-1)>5./std::sqrt(_N))
                            {
                                //std::cout<<_N<<": "<<(_mean[ihist]/_N-1)*(_mean[ihist]/_N-1)<<">"<<5./std::sqrt(_N)<<std::endl;
                                logger(pxl::LOG_LEVEL_WARNING, "Mean PU weight not 1.0! weight="+std::to_string(_means[processName][ihist]/_N)+" after "+std::to_string(_N)+" events.");
                                //throw std::runtime_error("Mean PU weight not 1.0! weight="+std::to_string(_mean[ihist]/_N)+" after "+std::to_string(_N)+" events.");
                            }
                        }
                        
                    }
                    else
                    {
                        throw std::runtime_error("Number of true interactions not found in event!");
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
            logger(pxl::LOG_LEVEL_INFO , "PU reweighting summary !");
            for (const auto& meanList: _means)
            {
                logger(pxl::LOG_LEVEL_INFO , "mean PU weight for process ",meanList.first);
                std::stringstream ss;
                ss<<" -> ";
                for (unsigned int ihist = 0; ihist < meanList.second.size(); ++ihist)
                {
                    ss << meanList.second[ihist]/_N<<",";
                }
                logger(pxl::LOG_LEVEL_INFO , ss.str());
            }
        }

        void shutdown() throw(std::runtime_error)
        {
        }

        void destroy() throw (std::runtime_error)
        {
            delete this;
        }
};

PXL_MODULE_INIT(PileUpReweighting)
PXL_PLUGIN_INIT
