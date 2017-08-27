from defaultModules.Module import Module

import logging
import ROOT
import os

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
        
        
        eventSelection = self.module("Samples").getEventSelection()
        
        observablesDict = self.module("ThetaModel").getObservablesDict()
        fitComponentsDict = self.module("ThetaModel").getFitComponentsDict()
        
        
        histograms = {}
    
        for observableName in observablesDict.keys():
            fitVariable = observablesDict[observableName]["variable"]
            fitBins = observablesDict[observableName]["bins"]
            fitRange = observablesDict[observableName]["range"]
            fitWeight = observablesDict[observableName]["weight"]
            
            
            #no selection in case unfoldingBin<0
            binSelection = self.module("Unfolding").getRecoBinSelection(unfoldingBin)
            
            for fitComponentName in fitComponentsDict.keys():
                componentWeight = fitComponentsDict[fitComponentName]["weight"]
            
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
            self._logger.info("produced hist: "+fitHist.GetName()+", entries="+str(int(fitHist.GetEntries()))+", events="+str(round(fitHist.Integral(),1)))
        
        outputFolder = self.module("ThetaModel").getHistogramPath(
            self.module("Utils").getUncertaintyName(),
            channel,
            unfoldingName
        )
        self.module("Utils").createFolder(outputFolder)
        
        rootFileOutput = ROOT.TFile(
            self.module("ThetaModel").getHistogramFile(
                self.module("Utils").getUncertaintyName(),
                channel,
                unfoldingName,
                unfoldingBin
            ),"RECREATE"
        )
        for histName in histograms.keys():
            histograms[histName].SetDirectory(rootFileOutput)
            histograms[histName].Write()
        rootFileOutput.Close()
        
        
