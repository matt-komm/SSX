from defaultModules.Module import Module

import logging
import ROOT
import os
import sys
import math
import numpy
import copy

# this generates the histograms (compound variable) for fitting

class PlotHistograms(Module.getClass("Program")):
    def __init__(self,options=[]):
        Module.__init__(self,options)
        self._logger = logging.getLogger(__file__)
        self._logger.setLevel(logging.DEBUG)
        
    def getFitComponentsDict(self):
        componentsBkg = {
            
            "TopBkg":
            {
                "sets":["tWChannel","TTJets"],
                "uncertainties":["TopBkg"],
                "weight":"1",
                "color":ROOT.kOrange+1
            },
            
            "WZjets_LF":
            {
                "sets":["WJetsAMCex","DYMG"],
                "uncertainties":["WZjets_LF","WZjets_HF"],
                "weight":"(Reconstructed_1__nBFlavorSelectedJet==0)*(Reconstructed_1__nCFlavorSelectedJet==0)",
                "color":ROOT.kGreen+1
            },
            
            "WZjets_HF":
            {
                "sets":["WJetsAMCex","DYMG"],
                "uncertainties":["WZjets_HF"],
                "weight":"(Reconstructed_1__nBFlavorSelectedJet>0 || Reconstructed_1__nCFlavorSelectedJet>0)",
                "color":ROOT.kGreen+1
            },
            
            "QCD_2j1t":
            {
                "sets":["QCD_DD"],
                "uncertainties":["QCD_2j1t"],
                "weight":self.module("Samples").getNjets(2)+"*"+self.module("Samples").getNbjets(1),
                "color":ROOT.kGray
            },

            "QCD_2j0t":
            {
                "sets":["QCD_DD"],
                "uncertainties":["QCD_2j0t"],
                "weight":self.module("Samples").getNjets(2)+"*"+self.module("Samples").getNbjets(0),
                "color":ROOT.kGray
            },
 
            "QCD_3j2t":
            {
                "sets":["QCD_DD"],
                "uncertainties":["QCD_3j2t"],
                "weight":self.module("Samples").getNjets(3)+"*"+self.module("Samples").getNbjets(2),
                "color":ROOT.kGray
            }
        }
        
        
        # use gen charge as THE charge ratio for signal (no entanglement in unfolding)!
        components = {
            "tChannel_pos":
            {
                "sets":["tChannel"],
                "uncertainties":["tChannel_pos"],
                "weight":self.module("Samples").getGenChargeSelection(1),
                "color":ROOT.kMagenta+1
            },
            "tChannel_neg":
            {
                "sets":["tChannel"],
                "uncertainties":["tChannel_neg"],
                "weight":self.module("Samples").getGenChargeSelection(-1),
                "color":ROOT.kMagenta+1
            }
        }
        
        #use reco charge for backgrounds to add some uncertainty on the charge confusion!!!
        for compName in componentsBkg.keys():
            components[compName+"_pos"]=copy.deepcopy(componentsBkg[compName])
            components[compName+"_pos"]["weight"]+="*"+self.module("Samples").getRecoChargeSelection(1)
            components[compName+"_pos"]["uncertainties"].append(compName+"_ratio")
            components[compName+"_neg"]=copy.deepcopy(componentsBkg[compName])
            components[compName+"_neg"]["weight"]+="*"+self.module("Samples").getRecoChargeSelection(-1)

        return components
        
    def execute(self):
        self.module("Samples").loadProcessFileDict(self.module("Utils").getOutputFolder("global/fileDictMu.json"),"mu")
        self.module("Samples").loadProcessFileDict(self.module("Utils").getOutputFolder("global/fileDictEle.json"),"ele")
    
        channel = self.getOption("channel")
        unfoldingBin = int(self.getOption("bin"))
       
        unfoldingName = self.module("Unfolding").getUnfoldingName()
        
        
        
        for histSetup in self.module("Plots").getHistSetups(channel):
            self._logger.info("Producing plot hists: "+histSetup["name"])
            histFilePath = self.module("Utils").getHistogramFile(
                histSetup["name"],
                channel,
                unfoldingName,
                unfoldingBin,
                self.module("Utils").getUncertaintyName()
            )
            if os.path.exists(histFilePath):
                self._logger.info("Output file '"+histFilePath+"' already exists! -> skip")
                continue
            
            
            
            binSelection = self.module("Unfolding").getRecoBinSelection(unfoldingBin,channel)
            histograms = {}
            
            fitComponentsDict = self.getFitComponentsDict()
            for fitComponentName in histSetup["comp"]:
                componentWeight = fitComponentsDict[fitComponentName]["weight"]
            
                fitHist = ROOT.TH1F(
                    self.module("ThetaModel").getHistogramName(histSetup["obsname"],fitComponentName,unfoldingName,unfoldingBin,uncertainty=self.module("Utils").getUncertaintyName()),
                    ";"+histSetup["xtitle"]+";Events / bin",
                    len(histSetup["binning"])-1,
                    histSetup["binning"]
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
                        histSetup["var"],
                        histSetup["selection"]+"*"+componentWeight+"*"+binSelection,
                        True,
                    )
                self._logger.info("produced hist: "+fitHist.GetName()+", entries="+str(int(fitHist.GetEntries()))+", events="+str(round(fitHist.Integral(),1)))
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
             
            dataHist = ROOT.TH1F(
                self.module("ThetaModel").getHistogramName(histSetup["obsname"],"data",unfoldingName,unfoldingBin),
                ";"+histSetup["xtitle"]+";Events / bin",
                len(histSetup["binning"])-1,
                    histSetup["binning"]
            )
            dataHist.SetDirectory(0)
            dataHist.Sumw2()
            histograms[dataHist.GetName()]=dataHist
            
            self.module("Samples").getSetHist1D(
                dataHist,
                "data",
                channel,
                histSetup["var"],
                histSetup["selection"]+"*"+binSelection,
                True,
            )
            self._logger.info("produced hist: "+dataHist.GetName()+", entries="+str(int(dataHist.GetEntries()))+", events="+str(round(dataHist.Integral(),1)))
        
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
        
        
