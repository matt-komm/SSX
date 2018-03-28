from defaultModules.Module import Module

import logging
import ROOT
import copy
import math
import os
import sys
from ModelClasses import *

class FitHistograms(Module.getClass("Program")):
    def __init__(self,options=[]):
        Module.__init__(self,options)
        self._logger = logging.getLogger(__file__)
        self._logger.setLevel(logging.DEBUG)
        
    def execute(self):
        #mu,ele,comb
        channels = self.getOption("channels").split(",")
        smooth = False if self.getOption("smooth")==None else True
        self._logger.info("Use smoothed hists: "+str(smooth))
        channelName = self.module("Samples").getChannelName(channels)
        self._logger.info("make fit for: "+str(channels))
        # channel,sysName,binList,[up,down]
        histogramsPerChannelAndUncertainty = {}
        
        unfoldingName = self.module("Unfolding").getUnfoldingName()
        uncertaintyList = self.getOption("systematics").split(",") if len(self.getOption("systematics"))>0 else []
        self._logger.info("profile systematics: "+str(uncertaintyList))
        
        
        #maps channel bins to global bins for combinations
        if unfoldingName!="inc":
            binMap = self.module("Unfolding").buildGlobalRecoBinMap()
            
        for channel in channels:
            histogramsPerChannelAndUncertainty[channel]={}
            histogramsPerChannelAndUncertainty[channel]["nominal"]={}
            if unfoldingName=="inc":
                histogramsPerChannelAndUncertainty[channel]["nominal"]["binInc"] = \
                    self.module("ThetaModel").getHistsFromFiles(channel,unfoldingName,-1,"nominal")
                
            else:
                nbins = len(self.module("Unfolding").getRecoBinning(channel))-1

                for ibin in range(nbins):
                    histogramsPerChannelAndUncertainty[channel]["nominal"]["bin"+str(1+binMap[channel][ibin])] = \
                        self.module("ThetaModel").getHistsFromFiles(channel,unfoldingName,ibin,"nominal")
                    
            for sysName in uncertaintyList:
                histogramsPerChannelAndUncertainty[channel][sysName]={}
                if unfoldingName=="inc":
                    histogramsPerChannelAndUncertainty[channel][sysName]["binInc"] = [
                        self.module("ThetaModel").getHistsFromFiles(channel,unfoldingName,-1,sysName+"Up",smooth=smooth),
                        self.module("ThetaModel").getHistsFromFiles(channel,unfoldingName,-1,sysName+"Down",smooth=smooth)
                    ]
                else:
                    nbins = len(self.module("Unfolding").getRecoBinning(channel))-1
                    for ibin in range(nbins):
                        histogramsPerChannelAndUncertainty[channel][sysName]["bin"+str(1+binMap[channel][ibin])] = [
                            self.module("ThetaModel").getHistsFromFiles(channel,unfoldingName,ibin,sysName+"Up",smooth=smooth),
                            self.module("ThetaModel").getHistsFromFiles(channel,unfoldingName,ibin,sysName+"Down",smooth=smooth)
                        ]
                        
        
        

        fitSetup = {}
        uncertainyParameterDict = self.module("ThetaModel").getUncertaintsDict()
        parametersDict = {}#"lumi":uncertainyParameterDict["lumi"]}
        for channel in channels:
            observableDict = self.module("ThetaModel").getObservablesDict(channel)
            fitComponentDict = self.module("ThetaModel").getFitComponentsDict()
            
            for obserableName in observableDict.keys():
                #make a separate observable per channel (and bin) 
                binNames = histogramsPerChannelAndUncertainty[channel]["nominal"].keys()
                
                for binName in binNames:
                    fitSetup[channel+"__"+obserableName+"__"+binName] = {
                        "bins":observableDict[obserableName]["bins"],
                        "range":observableDict[obserableName]["range"],
                        "components":{},
                        "data":histogramsPerChannelAndUncertainty[channel]["nominal"][binName][obserableName]["data"]
                    }
                    for componentName in fitComponentDict.keys():
                        uncertaintyParameters = fitComponentDict[componentName]["uncertainties"]
                        fitSetup[channel+"__"+obserableName+"__"+binName]["components"][componentName]={
                            "nominal":histogramsPerChannelAndUncertainty[channel]["nominal"][binName][obserableName][componentName],
                            #"yield":["lumi"],
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
                            
                        #add shape uncertainties
                        for sysName in uncertaintyList:
                            if not parametersDict.has_key(sysName):
                                parametersDict[sysName]=self.module("ThetaModel").makeGaus(0.,1)
                            fitSetup[channel+"__"+obserableName+"__"+binName]["components"][componentName]["shape"].append({
                                "parameter":sysName,
                                "up":histogramsPerChannelAndUncertainty[channel][sysName][binName][0][obserableName][componentName],
                                "down":histogramsPerChannelAndUncertainty[channel][sysName][binName][1][obserableName][componentName]
                            })
                
                                    
        
        self.module("Utils").createFolder("fit/profiled")
        fitOutput = os.path.join(
            self.module("Utils").getOutputFolder("fit/profiled"),
            self.module("ThetaModel").getFitFileName(channels,unfoldingName,postfix="profiled")
        )
        
        success = False
        retry = 10
        itry = 0
        while (not success and itry<retry):
            self.module("ThetaModel").makeModel(
                fitOutput+".cfg",
                fitSetup,parametersDict,
                outputFile=fitOutput+".root",
                pseudo=False,
                seed = 123+7*itry-31*itry+173*itry
            )
            
            itry+=1
            success = self.module("ThetaFit").run(fitOutput+".cfg")
            try:
                fitResult = self.module("ThetaFit").parseFitResult(
                    fitOutput+".root",
                    parametersDict
                )
            except Exception,e:
                success = False
                self._logger.error(str(e))
            
            if (not success):
                self._logger.info("Retry with new seed")

        if (not success):
            self._logger.critical("No theta run succeeded")
            sys.exit(1)
        
        
        self.module("ThetaFit").saveFitResult(fitOutput+".json",fitResult)
        
        #fitResult = self.module("ThetaFit").loadFitResult(fitOutput+".json")
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
        print fitResult["parameters"].items()[0]
        print fitResult["parameters"].items()[0]
        #print fitResult["parameters"]["en"]
        self.module("Drawing").drawPosterior({channelName:fitResult},fitOutput+"__posteriors_yield.pdf",
            selection=["tChannel_*_bin*","WZjets_bin*","WZjets_HF_bin*","WZjets_LF_bin*","TopBkg_bin*"],
            ranges = [0.2,1.8],
            default=1,
        )
        
        self.module("Drawing").drawPosterior({channelName:fitResult},fitOutput+"__posteriors_qcd.pdf",
            selection=["QCD_*_bin*_*"],
            ranges = [0,1.5],
            default=1,
        )
        
        self.module("Drawing").drawPosterior({channelName:fitResult},fitOutput+"__posteriors_ratios.pdf",
            selection=["WZjets_ratio_bin*","WZjets_HF_ratio_bin*","WZjets_LF_ratio_bin*","TopBkg_ratio_bin*","QCD_*_ratio_bin*_*"],
            ranges = [0.85,1.15],
            default=1,
        )
        
        self.module("Drawing").drawPosterior({channelName:fitResult},fitOutput+"__posteriors_sys.pdf",
            selection=uncertaintyList,
            ranges = [-2.5,2.5],
            default=0
        )

        if channelName==self.module("Samples").getChannelName(["ele","mu"]):
            fitOutputEle = os.path.join(
                self.module("Utils").getOutputFolder("fit/profiled"),
                self.module("ThetaModel").getFitFileName(["ele"],unfoldingName,"profiled")
            )
            fitOutputMu = os.path.join(
                self.module("Utils").getOutputFolder("fit/profiled"),
                self.module("ThetaModel").getFitFileName(["mu"],unfoldingName,"profiled")
            )
            if os.path.exists(fitOutputEle+".json") and os.path.exists(fitOutputMu+".json"):
                fitResultEle = self.module("ThetaFit").loadFitResult(fitOutputEle+".json")
                fitResultMu = self.module("ThetaFit").loadFitResult(fitOutputMu+".json")
        
                self.module("Drawing").drawPosterior({"mu":fitResultMu,"ele":fitResultEle,"comb":fitResult},fitOutput+"__posteriors_yield_comparison.pdf",
                    selection=["tChannel_*_bin*","WZjets_bin*","WZjets_HF_bin*","WZjets_LF_bin*","TopBkg_bin*"],
                    ranges = [0.2,1.8],
                    default=1,
                )
                
                self.module("Drawing").drawPosterior({"mu":fitResultMu,"ele":fitResultEle,"comb":fitResult},fitOutput+"__posteriors_qcd_comparison.pdf",
                    selection=["QCD_*_bin*_*"],
                    ranges = [0,1.5],
                    default=1,
                )
                
                self.module("Drawing").drawPosterior({"mu":fitResultMu,"ele":fitResultEle,"comb":fitResult},fitOutput+"__posteriors_ratios_comparison.pdf",
                    selection=["WZjets_ratio_bin*","WZjets_HF_ratio_bin*","WZjets_LF_ratio_bin*","TopBkg_ratio_bin*","QCD_*_ratio_bin*_*"],
                    ranges = [0.85,1.15],
                    default=1,
                )
                
                self.module("Drawing").drawPosterior({"mu":fitResultMu,"ele":fitResultEle,"comb":fitResult},fitOutput+"__posteriors_sys_comparison.pdf",
                    selection=uncertaintyList,
                    ranges = [-2.5,2.5],
                    default=0
                )
            else:
                self._logger.warning("Single channel fit results not found -> comparisons are not produced!")
                
