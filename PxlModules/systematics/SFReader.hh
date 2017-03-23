#ifndef __SFReader_H__
#define __SFReader_H__

#include "pxl/core.hh"
#include "pxl/hep.hh"
#include "pxl/modules/Module.hh"

#include "TH1F.h"
#include "TH2F.h"
#include "TFile.h"

#include <string>
#include <vector>
#include <stdexcept>
#include <cstdlib>

struct SFReader
{
    std::string prefix;
    
    std::string fileName;
    std::string histogramName;
    bool _histOrientationIsPtX;
    double additionalUncertainty;
    
    std::unique_ptr<TH2> rootHistogramPtEta;
    
    
    SFReader(
        pxl::Module* module,
        const std::string& prefix
    ):
        prefix(prefix),
        fileName(),
        histogramName(),
        _histOrientationIsPtX(true),
        additionalUncertainty(0),
        rootHistogramPtEta(nullptr)
    {
        module->addOption(prefix+" file name","","",pxl::OptionDescription::USAGE_FILE_OPEN);
        module->addOption(prefix+" hist name","","");
        module->addOption(prefix+" x=pt, y=eta","",_histOrientationIsPtX);
        module->addOption(prefix+" add uncertainty", "", 0.0);
    }
    
    int getPtBin(double pt)
    {
        int bin = 0; 
        int binMax = 0; rootHistogramPtEta->GetXaxis()->GetNbins();
        if (_histOrientationIsPtX)
        {
            bin = rootHistogramPtEta->GetXaxis()->FindBin(pt);
            binMax = rootHistogramPtEta->GetXaxis()->GetNbins();
        }
        else
        {
            bin = rootHistogramPtEta->GetYaxis()->FindBin(pt);
            binMax = rootHistogramPtEta->GetYaxis()->GetNbins();
        }
        if (bin<=0)
        {
            throw std::runtime_error("Got lepton with pt="+std::to_string(pt)+" that underflows the SF histogram '"+histogramName+"'");
        }
        else if (bin>binMax)
        {
            bin=binMax;
        }
        return bin;
    }
    
    int getEtaBin(double eta)
    {
        int bin = 0; 
        int binMax = 0; rootHistogramPtEta->GetYaxis()->GetNbins();
        if (_histOrientationIsPtX)
        {
            bin = rootHistogramPtEta->GetYaxis()->FindBin(eta);
            binMax = rootHistogramPtEta->GetYaxis()->GetNbins();
        }
        else
        {
            bin = rootHistogramPtEta->GetXaxis()->FindBin(eta);
            binMax = rootHistogramPtEta->GetXaxis()->GetNbins();
        }
        if (bin<=0)
        {
            throw std::runtime_error("Got lepton with eta="+std::to_string(eta)+" that underflows the SF histogram '"+histogramName+"'");
        }
        else if (bin>binMax)
        {
            bin=binMax;
        }
        return bin;
    }
    
    std::pair<float,float> getSFAndError(double pt, double eta)
    {
        if (!rootHistogramPtEta)
        {
            throw std::runtime_error("Histogram '"+histogramName+"' not yet read from file or it has been deleted");
        }
        float sf = 1.0;
        float error = 0.0;
        int ptBin = getPtBin(pt);
        int etaBin = getEtaBin(eta);
        if (_histOrientationIsPtX)
        {
            sf = rootHistogramPtEta->GetBinContent(ptBin,etaBin);
            error = rootHistogramPtEta->GetBinError(ptBin,etaBin);
        }
        else
        {
            sf = rootHistogramPtEta->GetBinContent(etaBin,ptBin);
            error = rootHistogramPtEta->GetBinError(etaBin,ptBin);
        }
        if (sf<0.1)
        {
            throw std::runtime_error("Got lepton SF of "+std::to_string(sf)+"(<0.1) for pt="+std::to_string(pt)+" eta="+std::to_string(eta)+" from histogram '"+histogramName+"'");
        }
        
        error = std::sqrt(error*error+additionalUncertainty*additionalUncertainty);
       
        return std::pair<float,float>(sf,error);
    }
    
    void init(pxl::Module* module)
    {
        module->getOption(prefix+" file name",fileName);
        module->getOption(prefix+" hist name",histogramName);
        module->getOption(prefix+" add uncertainty", additionalUncertainty);
        module->getOption(prefix+" x=pt, y=eta",_histOrientationIsPtX);
        
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
        if (_histOrientationIsPtX)
        {
            if (h->GetXaxis()->GetXmax()>50.0 and h->GetYaxis()->GetXmax()<5.0)
            {
                rootHistogramPtEta.reset((TH2*)h->Clone((std::string("SF")+prefix+std::to_string(std::rand())).c_str()));
                rootHistogramPtEta->SetDirectory(0);
            }
            else
            {
                throw std::runtime_error("Histogram '"+histogramName+"' in file '"+fileName+"' does not seem to be binned x=pt and y=eta");
            }
        }
        else
        {
            if (h->GetYaxis()->GetXmax()>50.0 and h->GetXaxis()->GetXmax()<5.0)
            {
                rootHistogramPtEta.reset((TH2*)h->Clone((std::string("SF")+prefix+std::to_string(std::rand())).c_str()));
                rootHistogramPtEta->SetDirectory(0);
            }
            else
            {
                throw std::runtime_error("Histogram '"+histogramName+"' in file '"+fileName+"' does not seem to be binned y=pt and x=eta");
            }
        }
        rootFile.Close();
    }
    
    
   
};

#endif
