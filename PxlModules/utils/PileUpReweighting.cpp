#include "pxl/hep.hh"
#include "pxl/core.hh"
#include "pxl/core/macros.hh"
#include "pxl/core/PluginManager.hh"
#include "pxl/modules/Module.hh"
#include "pxl/modules/ModuleFactory.hh"

#include <string>
#include <iostream>
#include <cstdlib>

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
        int64_t _rebinMC;
        
        std::vector<std::string> _dataFiles;
        std::string _dataHistName;
        
        std::vector<std::pair<std::string,TH1F>> _reweightingHists;
        
        unsigned int _N;
        std::vector<double> _mean;

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
            getOption("mc rebin",_rebinMC);
            
            getOption("data histogram files",_dataFiles);
            getOption("data histogram name",_dataHistName);
            
            _mcFile = getAnalysis()->findFile(_mcFile);
            
            
            
            TFile mcFile(_mcFile.c_str());
            TH1* histMC = dynamic_cast<TH1*>(mcFile.Get(_mcHistName.c_str()));
            if (not histMC)
            {
                throw std::runtime_error(getName()+": Failed to retrieve MC PU histogram from file '"+_mcFile+"' with name '"+_mcHistName+"'");
            }
            if (histMC->GetEntries()<10)
            {
                throw std::runtime_error(getName()+": PU histogram from file '"+_mcFile+"' with name '"+_mcHistName+"' contains only "+std::to_string(histMC->GetEntries())+" entires.");
            }
            //histMC->SetDirectory(0); delete with file closing
            histMC->Rebin(_rebinMC);
            histMC->Scale(histMC->GetNbinsX()/histMC->Integral());
            
            _mean=std::vector<double>(_dataFiles.size(),0);
            
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
                //histData->SetDirectory(0); ensure deletion with file closing
                histData->Scale(histData->GetNbinsX()/histData->Integral());
                
                //range checking
                if (std::fabs(histMC->GetXaxis()->GetXmin()-histData->GetXaxis()->GetXmin())>0.0001)
                {
                    throw std::runtime_error(getName()+": PU MC/data histograms have different xmin: MC="+std::to_string(histMC->GetXaxis()->GetXmin())+"; data="+std::to_string(histData->GetXaxis()->GetXmin()));
                }
                
                if (std::fabs(histMC->GetXaxis()->GetXmax()-histData->GetXaxis()->GetXmax())>0.0001)
                {
                    throw std::runtime_error(getName()+": PU MC/data histograms have different xmax: MC="+std::to_string(histMC->GetXaxis()->GetXmax())+"; data="+std::to_string(histData->GetXaxis()->GetXmax()));
                }
                
                if (histMC->GetNbinsX()<histData->GetNbinsX())
                {
                    throw std::runtime_error(getName()+": PU MC histogram has less bins than data. Adjust the rebinning if any applied! MC="+std::to_string(histMC->GetNbinsX())+"; data="+std::to_string(histData->GetNbinsX()));
                }
                
                if (histMC->GetNbinsX()%histData->GetNbinsX()!=0)
                {
                    logger(pxl::LOG_LEVEL_INFO, "Data histogram binning (",histData->GetNbinsX(),") is not a multiple of MC histogram binning (",histMC->GetNbinsX(),").");
                }
                
                const int pos = _dataFiles[idataFile].find_last_of('/')+1;
                const int end = _dataFiles[idataFile].find_first_of('.',pos+1);
                std::string puName = std::string(_dataFiles[idataFile],pos,end-pos);
                _reweightingHists.push_back(
                    std::make_pair(
                        puName,
                        TH1F(
                            (std::string("reweightingHist")+std::to_string(idataFile)+std::to_string(std::rand())).c_str(),
                            ";N true interactions; weight",
                            histMC->GetNbinsX(),
                            histMC->GetXaxis()->GetXmin(),
                            histMC->GetXaxis()->GetXmax()
                        )
                    )
                );
                TH1F& weightHist = _reweightingHists.back().second;
                weightHist.SetDirectory(0);
                
                
                for (unsigned int ibin = 0; ibin < weightHist.GetNbinsX(); ++ibin)
                {
                    const double binCenter = weightHist.GetBinCenter(ibin+1);
                    
                    const double puMC = histMC->GetBinContent(histMC->FindBin(binCenter));
                    const double puData = histData->GetBinContent(histData->FindBin(binCenter));


                    //cut off events with too less statistics <0.01% or unphysical weights >10
                    if (puMC>0.0001 and (puData/puMC)<10)
                    {
                        weightHist.SetBinContent(weightHist.FindBin(binCenter),puData/puMC);
                    }
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
                        for (unsigned int ihist = 0; ihist < _reweightingHists.size(); ++ihist)
                        {
                            const double ntrueInteractionsAtBX0 = trueInteractions->getElement(1);
                            if (ntrueInteractionsAtBX0<_reweightingHists[ihist].second.GetNbinsX())
                            {
                                const int bin = _reweightingHists[ihist].second.FindBin(ntrueInteractionsAtBX0);
                                const float weight = _reweightingHists[ihist].second.GetBinContent(bin);
                                recoEventView->setUserRecord(_reweightingHists[ihist].first+"_weight",weight);
                                _mean[ihist]+=weight;
                            }
                            else
                            {
                                recoEventView->setUserRecord(_reweightingHists[ihist].first+"_weight",1.0);
                                _mean[ihist]+=1;
                            }
                            
                            //sanity check
                            if (((_N%1000)==0) and (_N>=1000) and (_mean[ihist]/_N-1)*(_mean[ihist]/_N-1)>5./std::sqrt(_N))
                            {
                                //std::cout<<_N<<": "<<(_mean[ihist]/_N-1)*(_mean[ihist]/_N-1)<<">"<<5./std::sqrt(_N)<<std::endl;
                                logger(pxl::LOG_LEVEL_WARNING, "Mean PU weight not 1.0! weight="+std::to_string(_mean[ihist]/_N)+" after "+std::to_string(_N)+" events.");
                                throw std::runtime_error("Mean PU weight not 1.0! weight="+std::to_string(_mean[ihist]/_N)+" after "+std::to_string(_N)+" events.");
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
            for (unsigned int ihist = 0; ihist < _reweightingHists.size(); ++ihist)
            {
                logger(pxl::LOG_LEVEL_INFO , "mean PU weight for histogram ",_reweightingHists[ihist].first," = ",_mean[ihist]/_N);
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
