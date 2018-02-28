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
            
            "WZjets":
            {
                "sets":["WJetsAMCex","DYMG"],
                "uncertainties":["WZjets"],
                "weight":"1",
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
        
        srSelection = "(SingleTop_1__mtw_beforePz>50.)*("+self.module("ThetaModel").getBDTtchan(channel)+">0.7)"
        
        for histSetup in [
            {
                "obsname":"2j1t",
                "name":"mtw2j1t",
                "comp":["tChannel_pos","tChannel_neg","TopBkg_pos","TopBkg_neg","WZjets_pos","WZjets_neg","QCD_2j1t_pos","QCD_2j1t_neg"],
                "var":"SingleTop_1__mtw_beforePz",
                "varTitle":"m#lower[0.3]{#scale[0.7]{T}}(W) (GeV)",
                "selection":self.module("Samples").getNjets(2)+"*"+self.module("Samples").getNbjets(1),
                "binning":numpy.linspace(0,200,num=21)
            },
            {
                "obsname":"2j1t",
                "name":"bdttw2j1t",
                "comp":["tChannel_pos","tChannel_neg","TopBkg_pos","TopBkg_neg","WZjets_pos","WZjets_neg","QCD_2j1t_pos","QCD_2j1t_neg"],
                "var":self.module("ThetaModel").getBDTttw(channel),
                "varTitle":"BDT#lower[0.3]{#scale[0.7]{tt/W}}",
                "selection":self.module("Samples").getNjets(2)+"*"+self.module("Samples").getNbjets(1),
                "binning":numpy.linspace(-1,1,num=21)
            },
            {
                "obsname":"2j1t",
                "name":"bdttch2j1t",
                "comp":["tChannel_pos","tChannel_neg","TopBkg_pos","TopBkg_neg","WZjets_pos","WZjets_neg","QCD_2j1t_pos","QCD_2j1t_neg"],
                "var":self.module("ThetaModel").getBDTtchan(channel),
                "varTitle":"BDT#lower[0.3]{#scale[0.7]{#it{t}-ch}}",
                "selection":self.module("Samples").getNjets(2)+"*"+self.module("Samples").getNbjets(1),
                "binning":numpy.linspace(-1,1,num=21)
            },
            {
                "obsname":"3j2t",
                "name":"mtw3j2t",
                "comp":["tChannel_pos","tChannel_neg","TopBkg_pos","TopBkg_neg","WZjets_pos","WZjets_neg","QCD_3j2t_pos","QCD_3j2t_neg"],
                "var":"SingleTop_1__mtw_beforePz",
                "varTitle":"m#lower[0.3]{#scale[0.7]{T}}(W) (GeV)",
                "selection":self.module("Samples").getNjets(2)+"*"+self.module("Samples").getNbjets(1),
                "binning":numpy.linspace(0,200,num=21)
            },
            {
                "obsname":"2j0t",
                "name":"mtw2j0t",
                "comp":["tChannel_pos","tChannel_neg","TopBkg_pos","TopBkg_neg","WZjets_pos","WZjets_neg","QCD_2j0t_pos","QCD_2j0t_neg"],
                "var":"SingleTop_1__mtw_beforePz",
                "varTitle":"m#lower[0.3]{#scale[0.7]{T}}(W) (GeV)",
                "selection":self.module("Samples").getNjets(2)+"*"+self.module("Samples").getNbjets(0),
                "binning":numpy.linspace(0,200,num=21)
            },
            
            {
                "obsname":"2j1t",
                "name":"pt2j1t",
                "comp":["tChannel_pos","tChannel_neg","TopBkg_pos","TopBkg_neg","WZjets_pos","WZjets_neg","QCD_2j1t_pos","QCD_2j1t_neg"],
                "var":"SingleTop_1__Top_1__Pt",
                "varTitle":"top quark p#scale[0.7]{#lower[0.3]{T}} (GeV)",
                "selection":self.module("Samples").getNjets(2)+"*"+self.module("Samples").getNbjets(1)+"*"+srSelection,
                "binning":numpy.array([0.,50.,80.,120.,180.,300.])
            },
            {
                "obsname":"2j1t",
                "name":"y2j1t",
                "comp":["tChannel_pos","tChannel_neg","TopBkg_pos","TopBkg_neg","WZjets_pos","WZjets_neg","QCD_2j1t_pos","QCD_2j1t_neg"],
                "var":"fabs(SingleTop_1__Top_1__Y)",
                "varTitle":"top quark |y|",
                "selection":self.module("Samples").getNjets(2)+"*"+self.module("Samples").getNbjets(1)+"*"+srSelection,
                "binning":numpy.array([0.,0.2,0.5,0.8,1.3,2.6])
            },
            {
                "obsname":"2j1t",
                "name":"cos2j1t",
                "comp":["tChannel_pos","tChannel_neg","TopBkg_pos","TopBkg_neg","WZjets_pos","WZjets_neg","QCD_2j1t_pos","QCD_2j1t_neg"],
                "var":"SingleTop_1__cosTheta_tPLz",
                "varTitle":"cos#kern[0.1]{#theta}#scale[0.7]{#lower[0.28]{pol.}}#kern[-1.1]{*}",
                "selection":self.module("Samples").getNjets(2)+"*"+self.module("Samples").getNbjets(1)+"*"+srSelection,
                "binning":numpy.array([-1.0,-0.6,-0.3,0.0,0.3,0.6,1.0])
            },
            {
                "obsname":"2j1t",
                "name":"lpt2j1t",
                "comp":["tChannel_pos","tChannel_neg","TopBkg_pos","TopBkg_neg","WZjets_pos","WZjets_neg","QCD_2j1t_pos","QCD_2j1t_neg"],
                "var":"SingleTop_1__TightLepton_1__Pt",
                "varTitle":"lepton p#scale[0.7]{#lower[0.3]{T}}",
                "selection":self.module("Samples").getNjets(2)+"*"+self.module("Samples").getNbjets(1)+"*"+srSelection,
                "binning":numpy.array([26.,35.,45.,60.,85.,200.])
            },
            {
                "obsname":"2j1t",
                "name":"leta2j1t",
                "comp":["tChannel_pos","tChannel_neg","TopBkg_pos","TopBkg_neg","WZjets_pos","WZjets_neg","QCD_2j1t_pos","QCD_2j1t_neg"],
                "var":"fabs(SingleTop_1__TightLepton_1__Eta)",
                "varTitle":"lepton |#eta|",
                "selection":self.module("Samples").getNjets(2)+"*"+self.module("Samples").getNbjets(1)+"*"+srSelection,
                "binning":numpy.array([0.0,0.4,0.8,1.5,1.9,2.4])
            },
        ]:
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
                    ";"+histSetup["varTitle"]+";Events / bin",
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
                ";"+histSetup["varTitle"]+";Events / bin",
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
        
        
