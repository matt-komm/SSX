from defaultModules.Module import Module

import logging
import ROOT
import copy
import os
from ModelClasses import *

class FitHistograms(Module.getClass("Program")):
    def __init__(self,options=[]):
        Module.__init__(self,options)
        self._logger = logging.getLogger(__file__)
        self._logger.setLevel(logging.DEBUG)
        
    def execute(self):
        #mu,ele,comb
        channels = self.getOption("channels").split(",")
        channelName = self.module("Samples").getChannelName(channels)
        self._logger.info("make fit for: "+str(channels))
        # channel,sysName,binList,[up,down]
        histogramsPerChannel = {}
        unfoldingName = self.module("Unfolding").getUnfoldingName()
        uncertainty = self.module("Utils").getUncertaintyName()
        self._logger.info("systematic name: "+str(uncertainty))
        
        #maps channel bins to global bins for combinations
        if unfoldingName!="inc":
            binMap = self.module("Unfolding").buildGlobalRecoBinMap()
        
        for channel in channels:
            histogramsPerChannel[channel]={}
            histogramsPerChannel[channel]["nominal"]={}
            if unfoldingName=="inc":
                histogramsPerChannel[channel]["nominal"]["binInc"] = \
                    self.module("ThetaModel").getHistsFromFiles(channel,unfoldingName,-1,uncertainty)
                
            else:
                nbins = len(self.module("Unfolding").getRecoBinning(channel))-1
                for ibin in range(nbins):
                    histogramsPerChannel[channel]["nominal"]["bin"+str(1+binMap[channel][ibin])] = \
                        self.module("ThetaModel").getHistsFromFiles(channel,unfoldingName,ibin,uncertainty)
                    
            
        fitSetup = {}
        parametersDict = {}
        
        
        for channel in channels:
            observableDict = self.module("ThetaModel").getObservablesDict(channel)
            fitComponentDict = self.module("ThetaModel").getFitComponentsDict()
            uncertainyParameterDict = self.module("ThetaModel").getUncertaintsDict()
        
            for obserableName in observableDict.keys():
                #make a separate observable per channel (and bin) 
                binNames = histogramsPerChannel[channel]["nominal"].keys()
                for binName in binNames:
                    fitSetup[channel+"__"+obserableName+"__"+binName] = {
                        "bins":observableDict[obserableName]["bins"],
                        "range":observableDict[obserableName]["range"],
                        "components":{},
                        "data":histogramsPerChannel[channel]["nominal"][binName][obserableName]["data"]
                    }
                    for componentName in fitComponentDict.keys():
                        uncertaintyParameters = fitComponentDict[componentName]["uncertainties"]
                        fitSetup[channel+"__"+obserableName+"__"+binName]["components"][componentName]={
                            "nominal":histogramsPerChannel[channel]["nominal"][binName][obserableName][componentName],
                            "yield":[],
                            "shape":[]
                        }
                        #print channel,obserableName,componentName,fitSetup[channel+"_"+obserableName][componentName]["nominal"]
                        for uncertaintyParameter in uncertaintyParameters:
                            if uncertaintyParameter.find("QCD")>=0:
                                #make extra parameter per channel for QCD
                                fitSetup[channel+"__"+obserableName+"__"+binName]["components"][componentName]["yield"].append(uncertaintyParameter+"_"+binName+"_"+channel)
                                if not parametersDict.has_key(uncertaintyParameter+"_"+binName+"_"+channel):
                                    parametersDict[uncertaintyParameter+"_"+binName+"_"+channel]=copy.deepcopy(uncertainyParameterDict[uncertaintyParameter])
                            else:
                                #take all other processes 100% correlated between channels
                                fitSetup[channel+"__"+obserableName+"__"+binName]["components"][componentName]["yield"].append(uncertaintyParameter+"_"+binName)
                                if not parametersDict.has_key(uncertaintyParameter+"_"+binName):
                                    parametersDict[uncertaintyParameter+"_"+binName]=copy.deepcopy(uncertainyParameterDict[uncertaintyParameter])
                        
                        
                
                                    
        
        self.module("Utils").createFolder("fit/"+uncertainty)
        fitOutput = os.path.join(
            self.module("Utils").getOutputFolder("fit/"+uncertainty),
            self.module("ThetaModel").getFitFileName(channels,unfoldingName,uncertainty)
        )
        self.module("ThetaModel").makeModel(
            fitOutput+".cfg",
            fitSetup,parametersDict,
            outputFile=fitOutput+".root",
            pseudo=False
        )
        self.module("ThetaFit").run(fitOutput+".cfg")
       
        fitResult = self.module("ThetaFit").parseFitResult(
            fitOutput+".root",
            parametersDict
        )
        print fitResult["covariances"]["values"].keys()
        self.module("ThetaFit").saveFitResult(fitOutput+".json",fitResult)
        '''
        ROOT.gStyle.SetPaintTextFormat("4.0f")
        cv = ROOT.TCanvas("corr","",1000,900)
        cv.SetLeftMargin(0.32)
        cv.SetRightMargin(0.15)
        cv.SetBottomMargin(0.36)
        fitResult["correlations"]["hist"].SetMarkerSize(1.)
        fitResult["correlations"]["hist"].Scale(100.)
        fitResult["correlations"]["hist"].GetXaxis().SetTitleSize(0.5)
        fitResult["correlations"]["hist"].GetXaxis().LabelsOption("v")
        fitResult["correlations"]["hist"].GetYaxis().SetTitleSize(0.5)
        fitResult["correlations"]["hist"].GetZaxis().SetTitle("Correlation (%)")
        fitResult["correlations"]["hist"].GetZaxis().SetTitleSize(0.5)
        fitResult["correlations"]["hist"].Draw("colztext")
        cv.Print(os.path.join(
            self.module("Utils").getOutputFolder(),
            self.module("ThetaModel").getFitFileName(channels,unfoldingName)+"_correlation.pdf"
        ))
        '''
        #print fitResult["covariances"]["values"]["tChannel_neg_bin0"]["tChannel_pos_bin0"]
        #print fitResult["parameters"]["tChannel_neg_bin0"]
        #print fitResult["parameters"]["tChannel_pos_bin0"]
        #print fitResult["parameters"]["en"]
        self.module("Drawing").drawPosterior({channelName:fitResult},fitOutput+"__posteriors_yield.pdf",
            selection=["Other_bin*","tChannel_*_bin*","WZjets_bin*","TopBkg_bin*","QCD_*_bin*_*"],
            ranges = [0,1.5],
            default=1,
        )
        
        self.module("Drawing").drawPosterior({channelName:fitResult},fitOutput+"__posteriors_ratios.pdf",
            selection=["*_ratio_bin*"],
            ranges = [0.85,1.15],
            default=1,
        )
        

        if channelName==self.module("Samples").getChannelName(["ele","mu"]):
            fitOutputEle = os.path.join(
                self.module("Utils").getOutputFolder("fit/"+uncertainty),
                self.module("ThetaModel").getFitFileName(["ele"],unfoldingName,uncertainty)
            )
            fitOutputMu = os.path.join(
                self.module("Utils").getOutputFolder("fit/"+uncertainty),
                self.module("ThetaModel").getFitFileName(["mu"],unfoldingName,uncertainty)
            )
            if os.path.exists(fitOutputEle+".json") and os.path.exists(fitOutputMu+".json"):
                fitResultEle = self.module("ThetaFit").loadFitResult(fitOutputEle+".json")
                fitResultMu = self.module("ThetaFit").loadFitResult(fitOutputMu+".json")
        
                self.module("Drawing").drawPosterior({"mu":fitResultMu,"ele":fitResultEle,"comb":fitResult},fitOutput+"__posteriors_yield_comparison.pdf",
                    selection=["tChannel_*_bin*","WZjets_bin*","TopBkg_bin*"],
                    ranges = [0.5,1.5],
                    default=1,
                )
                
                self.module("Drawing").drawPosterior({"mu":fitResultMu,"ele":fitResultEle,"comb":fitResult},fitOutput+"__posteriors_qcd_comparison.pdf",
                    selection=["QCD_*_bin*_*"],
                    ranges = [0,1.5],
                    default=1,
                )
                
                self.module("Drawing").drawPosterior({"mu":fitResultMu,"ele":fitResultEle,"comb":fitResult},fitOutput+"__posteriors_ratios_comparison.pdf",
                    selection=["WZjets_ratio_bin*","TopBkg_ratio_bin*","QCD_*_ratio_bin*_*"],
                    ranges = [0.85,1.15],
                    default=1,
                )
                
            else:
                self._logger.warning("Single channel fit results not found -> comparisons are not produced!")
                

        
        
