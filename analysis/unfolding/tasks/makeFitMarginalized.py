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
       
        # channel,sysName,binList,[up,down]
        histogramsPerChannelAndUncertainty = {}
        
        unfoldingName = self.module("Unfolding").getUnfoldingName()
        uncertaintyList = self.getOption("systematics").split(",") if len(self.getOption("systematics"))>0 else []

        for channel in channels:
            histogramsPerChannelAndUncertainty[channel]={}
            histogramsPerChannelAndUncertainty[channel]["nominal"]=[]
            if unfoldingName=="inc":
                histogramsPerChannelAndUncertainty[channel]["nominal"].append(
                    self.module("ThetaModel").getHistsFromFiles(channel,unfoldingName,-1,"nominal")
                )
            else:
                nbins = len(self.module("Unfolding").getRecoBinning())-1
                for ibin in range(nbins):
                    histogramsPerChannelAndUncertainty[channel]["nominal"].append(
                        self.module("ThetaModel").getHistsFromFiles(channel,unfoldingName,ibin,"nominal")
                    )
            for sysName in uncertaintyList:
                histogramsPerChannelAndUncertainty[channel][sysName]=[]
                if unfoldingName=="inc":
                    histogramsPerChannelAndUncertainty[channel][sysName].append([
                        self.module("ThetaModel").getHistsFromFiles(channel,unfoldingName,-1,sysName+"Up"),
                        self.module("ThetaModel").getHistsFromFiles(channel,unfoldingName,-1,sysName+"Down")
                    ])
                else:
                    nbins = len(self.module("Unfolding").getRecoBinning())-1
                    for ibin in range(nbins):
                        histogramsPerChannelAndUncertainty[channel][sysName].append([
                            self.module("ThetaModel").getHistsFromFiles(channel,unfoldingName,ibin,sysName+"Up"),
                            self.module("ThetaModel").getHistsFromFiles(channel,unfoldingName,ibin,sysName+"Down")
                        ])
                        
        
        observableDict = self.module("ThetaModel").getObservablesDict()
        fitComponentDict = self.module("ThetaModel").getFitComponentsDict()
        uncertainyParameterDict = self.module("ThetaModel").getUncertaintsDict()

        fitSetup = {}
        parametersDict = {}
        for channel in channels:
            for obserableName in observableDict.keys():
                #make a separate observable per channel (and bin) 
                binRanges = [0]
                if unfoldingName!="inc":
                    binRanges=range(len(self.module("Unfolding").getRecoBinning())-1)
                    
                for ibinRange in binRanges:
                    fitSetup[channel+"__"+obserableName+"__bin"+str(ibinRange)] = {
                        "bins":observableDict[obserableName]["bins"],
                        "range":observableDict[obserableName]["range"],
                        "components":{},
                        "data":histogramsPerChannelAndUncertainty[channel]["nominal"][ibinRange][obserableName]["data"]
                    }
                    for componentName in fitComponentDict.keys():
                        uncertaintyParameters = fitComponentDict[componentName]["uncertainties"]
                        fitSetup[channel+"__"+obserableName+"__bin"+str(ibinRange)]["components"][componentName]={
                            "nominal":histogramsPerChannelAndUncertainty[channel]["nominal"][ibinRange][obserableName][componentName],
                            "yield":[],
                            "shape":[]
                        }
                        #print channel,obserableName,componentName,fitSetup[channel+"_"+obserableName][componentName]["nominal"]
                        for uncertaintyParameter in uncertaintyParameters:
                            if uncertaintyParameter.find("QCD")>=0:
                                #make extra parameter per channel for QCD
                                fitSetup[channel+"__"+obserableName+"__bin"+str(ibinRange)]["components"][componentName]["yield"].append(uncertaintyParameter+"_bin"+str(ibinRange)+"_"+channel)
                                if not parametersDict.has_key(uncertaintyParameter+"_bin"+str(ibinRange)+"_"+channel):
                                    parametersDict[uncertaintyParameter+"_bin"+str(ibinRange)+"_"+channel]=copy.deepcopy(uncertainyParameterDict[uncertaintyParameter])
                            else:
                                #take all other processes 100% correlated between channels
                                fitSetup[channel+"__"+obserableName+"__bin"+str(ibinRange)]["components"][componentName]["yield"].append(uncertaintyParameter+"_bin"+str(ibinRange))
                                if not parametersDict.has_key(uncertaintyParameter+"_bin"+str(ibinRange)):
                                    parametersDict[uncertaintyParameter+"_bin"+str(ibinRange)]=copy.deepcopy(uncertainyParameterDict[uncertaintyParameter])
                        
                        #add shape uncertainties
                        for sysName in uncertaintyList:
                            if not parametersDict.has_key(sysName):
                                parametersDict[sysName]=self.module("ThetaModel").makeGaus(0.,1.)
                            fitSetup[channel+"__"+obserableName+"__bin"+str(ibinRange)]["components"][componentName]["shape"].append({
                                "parameter":sysName,
                                "up":histogramsPerChannelAndUncertainty[channel][sysName][ibinRange][0][obserableName][componentName],
                                "down":histogramsPerChannelAndUncertainty[channel][sysName][ibinRange][1][obserableName][componentName]
                            })
                
                                    
        
        
        fitOutput = os.path.join(
            self.module("Utils").getOutputFolder(),
            self.module("ThetaModel").getFitFileName(channels,unfoldingName)
        )
        
        self.module("ThetaModel").makeModel(
            fitOutput+".cfg",
            fitSetup,parametersDict,
            outputFile=fitOutput+".root",
            pseudo=False
        )
        self.module("ThetaFit").run(fitOutput+".cfg")
        fitResult = self.module("ThetaFit").readFitResult(
            fitOutput+".root",
            unfoldingName,
            parametersDict
        )
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
        print fitResult["parameters"]["tChannel_neg_bin0"]
        print fitResult["parameters"]["tChannel_pos_bin0"]
        #print fitResult["parameters"]["en"]
        self.module("Drawing").drawPosterior(fitResult,fitOutput+"__posteriors_yield.pdf",
            selection=["tChannel_*_bin*","WZjets_bin*","TopBkg_bin*","QCD_*_bin*_*"],
            ranges = [0,1.5],
            default=1,
        )
        
        self.module("Drawing").drawPosterior(fitResult,fitOutput+"__posteriors_ratios.pdf",
            selection=["WZjets_ratio_bin*","TopBkg_ratio_bin*","QCD_*_ratio_bin*_*"],
            ranges = [0.85,1.15],
            default=1,
        )
        
        self.module("Drawing").drawPosterior(fitResult,fitOutput+"__posteriors_sys.pdf",
            selection=uncertaintyList,
            ranges = [-1.5,1.5],
            default=0
        )

        
        
