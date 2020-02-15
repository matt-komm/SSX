from defaultModules.Module import Module

import logging
import ROOT
import os
import sys
import math

# this generates the histograms (compound variable) for fitting

class FitHistograms(Module.getClass("Program")):
    def __init__(self,options=[]):
        Module.__init__(self,options)
        self._logger = logging.getLogger(__file__)
        self._logger.setLevel(logging.DEBUG)
        
    def execute(self):
        self.module("Samples").loadProcessFileDict(self.module("Utils").getOutputFolder("global/fileDictMu.json"),"mu")
        self.module("Samples").loadProcessFileDict(self.module("Utils").getOutputFolder("global/fileDictEle.json"),"ele")
    
        channel = self.getOption("channel")
        unfoldingBin = int(self.getOption("bin"))
       
        unfoldingName = self.module("Unfolding").getUnfoldingName()
        
        
        histFilePath = self.module("ThetaModel").getHistogramFile(
            channel,
            unfoldingName,
            unfoldingBin,
            self.module("Utils").getUncertaintyName()
        )
        
        if os.path.exists(histFilePath):
            self._logger.info("Output file '"+histFilePath+"' already exists! -> skip")
            sys.exit(0)
            
        eventSelection = self.module("Samples").getEventSelection(channel)
        
        observablesDict = self.module("ThetaModel").getObservablesDict(channel)
        fitComponentsDict = self.module("ThetaModel").getFitComponentsDict()
        
        
        
        histograms = {}
    
        for observableName in observablesDict.keys():
            fitVariable = observablesDict[observableName]["variable"]
            fitBins = observablesDict[observableName]["bins"]
            fitRange = observablesDict[observableName]["range"]
            fitWeight = observablesDict[observableName]["weight"]
            
            
            #no selection in case unfoldingBin<0
            binSelection = self.module("Unfolding").getRecoBinSelection(unfoldingBin,channel)
            
            for fitComponentName in fitComponentsDict.keys():
                componentWeight = fitComponentsDict[fitComponentName]["weight"]
            
                fitHist = self.module("ThetaModel").canUseNominalHistogram(
                    channel,observableName,fitComponentName,unfoldingName,unfoldingBin,uncertainty=self.module("Utils").getUncertaintyName(),smooth=False
                )
                if fitHist==None:
                    fitHist = ROOT.TH1F(
                        self.module("ThetaModel").getHistogramName(observableName,fitComponentName,unfoldingName,unfoldingBin,uncertainty=self.module("Utils").getUncertaintyName()),
                        ";"+fitVariable+";",
                        fitBins,
                        fitRange[0],
                        fitRange[1]
                    )
                    fitHist.SetDirectory(0)
                    fitHist.Sumw2()
                    histograms[fitHist.GetName()]=fitHist
                    
                    #self._logger.debug(observableName+", "+fitComponentName+": weight="+fitWeight+"*"+componentWeight+"*"+binSelection)
                    
                    for setName in fitComponentsDict[fitComponentName]["sets"]:
                        self.module("Samples").getSetHist1D(
                            fitHist,
                            setName,
                            channel,
                            fitVariable,
                            fitWeight+"*"+componentWeight+"*"+binSelection,
                            True,
                        )
                    self._logger.info("produced hist: "+fitHist.GetName()+", entries="+str(int(fitHist.GetEntries()))+", events="+str(round(fitHist.Integral(),1)))
                else:
                    histograms[fitHist.GetName()]=fitHist
                    self._logger.info("use default hist: "+fitHist.GetName()+", entries="+str(int(fitHist.GetEntries()))+", events="+str(round(fitHist.Integral(),1)))
                    
                if fitHist.GetEntries()>0:
                    avgWeight = math.fabs(fitHist.Integral()/fitHist.GetEntries())
                    for ibin in range(fitHist.GetNbinsX()):
                        if fitHist.GetBinContent(ibin+1)<0:
                            fitHist.SetBinContent(ibin+1,avgWeight*0.01)
                            fitHist.SetBinError(ibin+1,math.sqrt(avgWeight))
                else:
                    for ibin in range(fitHist.GetNbinsX()):
                        fitHist.SetBinContent(ibin+1,0.01)
                        fitHist.SetBinError(ibin+1,0.1)
                        
            dataHist = self.module("ThetaModel").canUseNominalHistogram(
                channel,observableName,"data",unfoldingName,unfoldingBin
            )
            if dataHist==None:
                dataHist = ROOT.TH1F(
                    self.module("ThetaModel").getHistogramName(observableName,"data",unfoldingName,unfoldingBin),
                    ";"+fitVariable+";",
                    fitBins,
                    fitRange[0],
                    fitRange[1]
                )
                dataHist.SetDirectory(0)
                dataHist.Sumw2()
                histograms[dataHist.GetName()]=dataHist
                
                self.module("Samples").getSetHist1D(
                    dataHist,
                    "data",
                    channel,
                    fitVariable,
                    fitWeight+"*"+binSelection,
                    True,
                )
                self._logger.info("produced hist: "+dataHist.GetName()+", entries="+str(int(dataHist.GetEntries()))+", events="+str(round(dataHist.Integral(),1)))
            else:
                histograms[dataHist.GetName()]=dataHist
                self._logger.info("use default hist: "+dataHist.GetName()+", entries="+str(int(dataHist.GetEntries()))+", events="+str(round(dataHist.Integral(),1)))
                
        outputFolder = self.module("ThetaModel").getHistogramPath(
            channel,
            unfoldingName,
            self.module("Utils").getUncertaintyName()
        )
        self.module("Utils").createFolder(outputFolder)
        
        
        
        rootFileOutput = ROOT.TFile(
            histFilePath,"RECREATE"
        )
        
        for histName in histograms.keys():
            histograms[histName].SetDirectory(rootFileOutput)
            histograms[histName].Write()
        rootFileOutput.Close()
        
        
