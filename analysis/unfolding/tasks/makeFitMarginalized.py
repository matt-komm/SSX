from defaultModules.Module import Module

import logging
import ROOT
import copy
import math
import os
import sys
import re
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
        output = self.getOption("output") if (self.getOption("output")!=None) else "profiled"
        freezeParams = map(lambda x: re.compile(x.replace("*","[A-Za-z0-9_\-]*")), self.getOption("freeze").split(',')) if (self.getOption("freeze")!=None) else []
        self._logger.info("make fit for: "+str(channels))
        # channel,sysName,binList,[up,down]
        histogramsPerChannelAndUncertainty = {}
        
        unfoldingName = self.module("Unfolding").getUnfoldingName()
        uncertaintyList = self.getOption("systematics").split(",") if len(self.getOption("systematics"))>0 else []
        smoothing = []
        for isys in range(len(uncertaintyList)):
            if uncertaintyList[isys].endswith("~"):
                uncertaintyList[isys] = uncertaintyList[isys].replace("~","")
                smoothing.append(True)
                self._logger.info("add syst: "+uncertaintyList[isys]+" [smooth]")
            else:
                self._logger.info("add syst: "+uncertaintyList[isys])
                smoothing.append(False)
                
        #self._logger.info("profile systematics: "+str(uncertaintyList))
        
        freezeParamValues = {}
        if len(freezeParams)>0:
            fitOutputProfiled = os.path.join(
                self.module("Utils").getOutputFolder("fit/profiled"),
                self.module("ThetaModel").getFitFileName(channels,unfoldingName,"profiled")
            )
            fitResultProfiled = self.module("ThetaFit").loadFitResult(fitOutputProfiled+".json")
            
            for freezeParam in freezeParams:
                for fitParameter in fitResultProfiled['parameters'].keys():
                    if freezeParam.match(fitParameter):
                        self._logger.info("Freezing parameter: "+fitParameter+" to "+str(fitResultProfiled['parameters'][fitParameter]['mean_fit']))
                        freezeParamValues[fitParameter] = fitResultProfiled['parameters'][fitParameter]['mean_fit']
                        
        
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
                    
            for isys,sysName in enumerate(uncertaintyList):
                histogramsPerChannelAndUncertainty[channel][sysName]={}
                if unfoldingName=="inc":
                    histogramsPerChannelAndUncertainty[channel][sysName]["binInc"] = [
                        self.module("ThetaModel").getHistsFromFiles(channel,unfoldingName,-1,sysName+"Up",smooth=smoothing[isys]),
                        self.module("ThetaModel").getHistsFromFiles(channel,unfoldingName,-1,sysName+"Down",smooth=smoothing[isys])
                    ]
                else:
                    nbins = len(self.module("Unfolding").getRecoBinning(channel))-1
                    for ibin in range(nbins):
                        histogramsPerChannelAndUncertainty[channel][sysName]["bin"+str(1+binMap[channel][ibin])] = [
                            self.module("ThetaModel").getHistsFromFiles(channel,unfoldingName,ibin,sysName+"Up",smooth=smoothing[isys]),
                            self.module("ThetaModel").getHistsFromFiles(channel,unfoldingName,ibin,sysName+"Down",smooth=smoothing[isys])
                        ]
                        
        
        

        fitSetup = {}
        
        combineChannels = False
        
        uncertainyParameterDict = self.module("ThetaModel").getUncertaintsDict()
        parametersDict = {}#"lumi":uncertainyParameterDict["lumi"]}
        for channel in channels:
            observableDict = self.module("ThetaModel").getObservablesDict(channel)
            fitComponentDict = self.module("ThetaModel").getFitComponentsDict()
            
            for obserableName in observableDict.keys():
                #make a separate observable per channel (and bin) 
                binNames = histogramsPerChannelAndUncertainty[channel]["nominal"].keys()
                
                for binName in binNames:
                    obsName = channel+"__"+obserableName+"__"+binName
                    if combineChannels and len(channels)>=2:
                        obsName = obserableName+"__"+binName
                        
                    if not fitSetup.has_key(obsName):
                        fitSetup[obsName] = {
                            "bins":observableDict[obserableName]["bins"],
                            "range":observableDict[obserableName]["range"],
                            "components":{},
                            "data":[histogramsPerChannelAndUncertainty[channel]["nominal"][binName][obserableName]["data"]]
                        }
                    else:
                        #sanity checks!
                        if fitSetup[obsName]["bins"]!=observableDict[obserableName]["bins"]:
                            self._logger.critical("Binning in different channels not identical! ("+str(fitSetup[obsName]["bins"])+" vs. "+str(observableDict[obserableName]["bins"])+")")
                            sys.exit(1)
                        if fitSetup[obsName]["range"]!=observableDict[obserableName]["range"]:
                            self._logger.critical("Range in different channels not identical!")
                            sys.exit(1)
                        fitSetup[obsName]["data"].append(
                            histogramsPerChannelAndUncertainty[channel]["nominal"][binName][obserableName]["data"]
                        )
                        
                        
                    for componentName in fitComponentDict.keys():
                        uncertaintyParameters = fitComponentDict[componentName]["uncertainties"]
                        fitSetup[obsName]["components"][channel+"_"+componentName]={
                            "nominal":histogramsPerChannelAndUncertainty[channel]["nominal"][binName][obserableName][componentName],
                            #"yield":["lumi"],
                            "yield":[],
                            "shape":[]
                        }
                        #print channel,obserableName,componentName,fitSetup[channel+"_"+obserableName][componentName]["nominal"]
                        for uncertaintyParameter in uncertaintyParameters:
                            if uncertaintyParameter.find("tChannel")>=0:
                                #make extra parameter per bin for signal
                                fitSetup[obsName]["components"][channel+"_"+componentName]["yield"].append(uncertaintyParameter+"_"+binName)
                                if not parametersDict.has_key(uncertaintyParameter+"_"+binName):
                                    parametersDict[uncertaintyParameter+"_"+binName]=copy.deepcopy(uncertainyParameterDict[uncertaintyParameter])                                    
                            elif uncertaintyParameter.find("QCD")>=0:
                                #make extra parameter per channel for QCD but not per bin
                                fitSetup[obsName]["components"][channel+"_"+componentName]["yield"].append(uncertaintyParameter+"_"+binName+"_"+channel)
                                if not parametersDict.has_key(uncertaintyParameter+"_"+binName+"_"+channel):
                                    parametersDict[uncertaintyParameter+"_"+binName+"_"+channel]=copy.deepcopy(uncertainyParameterDict[uncertaintyParameter])
                            else:
                                #take all other processes 100% correlated between channels
                                fitSetup[obsName]["components"][channel+"_"+componentName]["yield"].append(uncertaintyParameter+"_"+binName)
                                if not parametersDict.has_key(uncertaintyParameter+"_"+binName):
                                    parametersDict[uncertaintyParameter+"_"+binName]=copy.deepcopy(uncertainyParameterDict[uncertaintyParameter])
                            
                        #add shape uncertainties
                        for sysName in uncertaintyList:
                            if not parametersDict.has_key(sysName):
                                if sysName.find("eleEff")>=0 or sysName.find("muEff")>=0 or sysName.find("eleMultiIso")>=0 or sysName.find("eleMultiVeto")>=0 or sysName.find("muMulti")>=0 or sysName.find("ltag")>=0:
                                    parametersDict[sysName]=self.module("ThetaModel").makeGaus(0.,1,r=[-2.5,2.5],name=sysName)
                                else:
                                    parametersDict[sysName]=self.module("ThetaModel").makeGaus(0.,1,name=sysName)
                            fitSetup[obsName]["components"][channel+"_"+componentName]["shape"].append({
                                "parameter":sysName,
                                "up":histogramsPerChannelAndUncertainty[channel][sysName][binName][0][obserableName][componentName],
                                "down":histogramsPerChannelAndUncertainty[channel][sysName][binName][1][obserableName][componentName]
                            })
                
        for parameter in parametersDict.keys():
            eps = 1e-3
            if freezeParamValues.has_key(parameter):
                prevP = str(parametersDict[parameter])+"\n"
                parametersDict[parameter] = self.module("ThetaModel").makeGaus(
                    freezeParamValues[parameter],
                    eps,
                    r=[freezeParamValues[parameter]-5*eps,freezeParamValues[parameter]+5*eps],
                    name=parameter
                )
                prevP +="\t -> "+str(parametersDict[parameter])
                self._logger.info("Replacing parameter:\n\t"+prevP)
                              
        #sys.exit(1)

        self.module("Utils").createFolder("fit/"+output)
        fitOutput = os.path.join(
            self.module("Utils").getOutputFolder("fit/"+output),
            self.module("ThetaModel").getFitFileName(channels,unfoldingName,postfix=output)

        )
        
        fitResultsSucess = []
        isuccess = -1
        while (len(fitResultsSucess)<4 and isuccess<20):
            success = False
            retry = 40
            itry = 0
            isuccess+=1
            while (not success and itry<retry):
                self.module("ThetaModel").makeModel(
                    fitOutput+".cfg",
                    fitSetup,parametersDict,
                    outputFile=fitOutput+".root",
                    pseudo=False,
                    seed = 123+7*itry-31*itry+173*itry+len(fitResultsSucess)*1023-len(fitResultsSucess)*97*(1+itry),
                    cov=0.001+itry*0.001 if unfoldingName=='inc' else 0.01+itry*0.002
                )
                
                itry+=1
                success = self.module("ThetaFit").run(fitOutput+".cfg")
                try:
                    fitResult = self.module("ThetaFit").parseFitResult(
                        fitOutput+".root",
                        parametersDict
                    )
                    #for ["correlations"]["values"]
                    avgcorr = self.module("ThetaFit").checkDegenerated(fitResult)
                    self._logger.info("Fit avg correlation: "+str(avgcorr))
                    if (unfoldingName!="inc"):
                        if (avgcorr>0.4):
                            raise Exception("Degenerated fit with average covariance: "+str(avgcorr))
                    else:
                        if (avgcorr>0.6):
                            raise Exception("Degenerated fit with average covariance: "+str(avgcorr))
                    if (unfoldingName!="inc"):
                        dets = self.module("ThetaFit").checkSignalDeterminant(fitResult,channelName)
                        self._logger.info("Fit signal dets: "+str(dets))
                        if (min(dets)<10.**(-60) or max(dets)>10.**(60)):
                            raise Exception("Degenerated fit with signal determinant: "+str(dets))
                        
                    fitResultsSucess.append(fitResult)
                                    
                except Exception,e:
                    success = False
                    self._logger.error(str(e))
                
                if (not success):
                    self._logger.info("Retry with new seed")

            if (not success):
                self._logger.critical("No theta run succeeded")
                sys.exit(1)
                
        if (isuccess>=20 or len(fitResultsSucess)<4):
            self._logger.critical("No sufficient sucessful fits")
            sys.exit(1)
        
        fitResult = self.module("ThetaFit").averageFitResults(fitResultsSucess)
        
        
        #fitResult = self.module("ThetaFit").loadFitResult(fitOutput+".json")
        
        ROOT.gStyle.SetPaintTextFormat("4.0f")
        cv = ROOT.TCanvas("corr","",1000,900)
        cv.SetLeftMargin(0.26 if unfoldingName=="inc" else 0.16)
        cv.SetRightMargin(0.15)
        cv.SetBottomMargin(0.3 if unfoldingName=="inc" else 0.19)
        fitResult["correlations"]["hist"].SetMarkerSize(0.7 if unfoldingName=="inc" else 0.35)
        fitResult["correlations"]["hist"].Scale(100.)
        fitResult["correlations"]["hist"].GetXaxis().SetTitleSize(0.5)
        fitResult["correlations"]["hist"].GetXaxis().LabelsOption("v")
        fitResult["correlations"]["hist"].GetXaxis().SetLabelSize(20 if unfoldingName=="inc" else 10)
        fitResult["correlations"]["hist"].GetYaxis().SetLabelSize(20 if unfoldingName=="inc" else 10)
        fitResult["correlations"]["hist"].GetZaxis().SetLabelSize(25)
        fitResult["correlations"]["hist"].GetYaxis().SetTitleSize(0.5)
        fitResult["correlations"]["hist"].GetZaxis().SetTitle("Correlation (%)")
        fitResult["correlations"]["hist"].GetZaxis().SetTitleSize(25)
        fitResult["correlations"]["hist"].Draw("colztext")
        cv.Print(fitOutput+"_correlation.pdf")
        
        
        #note: this deletes the cov/corr histograms
        self.module("ThetaFit").saveFitResult(fitOutput+".json",fitResult)
        
        print fitResult["parameters"].items()[0]
        print fitResult["parameters"].items()[0]
        #print fitResult["parameters"]["en"]
        self.module("Drawing").drawPosterior({channelName:fitResult},fitOutput+"__posteriors_yield.pdf",
            selection=["tChannel_*_bin*","WZjets_bin*","WZjets_HF_bin*","WZjets_LF_bin*","TopBkg_bin*"],#,"WZjets*","WZjets_HF*","WZjets_LF*","TopBkg*"],
            ranges = [0.2,1.8],
            default=1,
        )
        
        self.module("Drawing").drawPosterior({channelName:fitResult},fitOutput+"__posteriors_qcd.pdf",
            selection=["QCD_*_bin*_*"],#,"QCD_*"],
            ranges = [0,2.],
            default=1,
        )
        
        self.module("Drawing").drawPosterior({channelName:fitResult},fitOutput+"__posteriors_ratios.pdf",
            selection=["WZjets_ratio_bin*","WZjets_HF_ratio_bin*","WZjets_LF_ratio_bin*","TopBkg_ratio_bin*","QCD_*_ratio_bin*_*"],
            ranges = [0.85,1.15],
            default=1,
        )
        
        self.module("Drawing").drawPosterior({channelName:fitResult},fitOutput+"__posteriors_sys.pdf",
            selection=uncertaintyList,
            nameDict={"unc":"uncl. energy","tw":"tW/t#bar{t} ratio","res":"JER","pu":"pileup","muMulti":"#mu multijet iso. range","muEff":"#mu efficency","ltag":"mistagging eff.","en":"JEC","eleMultiVeto":"ele. multijet #gamma veto","eleMultiIso":"ele. multijet iso. range","eleEff":"ele. efficiency","dy":"W/Z+jet ratio","btag":"b-tagging"},  
            ranges = [-2.5,2.5],
            default=0
        )

        if channelName==self.module("Samples").getChannelName(["ele","mu"]):
            fitOutputEle = os.path.join(
                self.module("Utils").getOutputFolder("fit/"+output),
                self.module("ThetaModel").getFitFileName(["ele"],unfoldingName,output)
            )
            fitOutputMu = os.path.join(
                self.module("Utils").getOutputFolder("fit/"+output),
                self.module("ThetaModel").getFitFileName(["mu"],unfoldingName,output)
            )
            if os.path.exists(fitOutputEle+".json") and os.path.exists(fitOutputMu+".json"):
                fitResultEle = self.module("ThetaFit").loadFitResult(fitOutputEle+".json")
                fitResultMu = self.module("ThetaFit").loadFitResult(fitOutputMu+".json")
        
                self.module("Drawing").drawPosterior({"mu":fitResultMu,"ele":fitResultEle,"comb":fitResult},fitOutput+"__posteriors_yield_comparison.pdf",
                    selection=["tChannel_*_bin*","WZjets_bin*","WZjets_HF_bin*","WZjets_LF_bin*","TopBkg_bin*"],#,"WZjets*","WZjets_HF*","WZjets_LF*","TopBkg*"],
                    ranges = [0.2,1.8],
                    default=1,
                )
                
                self.module("Drawing").drawPosterior({"mu":fitResultMu,"ele":fitResultEle,"comb":fitResult},fitOutput+"__posteriors_qcd_comparison.pdf",
                    selection=["QCD_*_bin*_*"],#,"QCD_*"],
                    ranges = [0,2.],
                    default=1,
                )
                
                self.module("Drawing").drawPosterior({"mu":fitResultMu,"ele":fitResultEle,"comb":fitResult},fitOutput+"__posteriors_ratios_comparison.pdf",
                    selection=["WZjets_ratio_bin*","WZjets_HF_ratio_bin*","WZjets_LF_ratio_bin*","TopBkg_ratio_bin*","QCD_*_ratio_bin*_*"],
                    ranges = [0.85,1.15],
                    default=1,
                )
                
                self.module("Drawing").drawPosterior({"mu":fitResultMu,"ele":fitResultEle,"comb":fitResult},fitOutput+"__posteriors_sys_comparison.pdf",
                    selection=uncertaintyList,
                    nameDict={"unc":"uncl. energy","tw":"tW/t#bar{t} ratio","res":"JER","pu":"pileup","muMulti":"#mu multijet iso. range","muEff":"#mu eff.","ltag":"mistagging eff.","en":"JEC","eleMultiVeto":"e multijet #gamma veto","eleMultiIso":"e multijet iso. range","eleEff":"e efficiency","dy":"W/Z+jet ratio","btag":"b-tagging"},  
                    ranges = [-2.5,2.5],
                    default=0
                )
            else:
                self._logger.warning("Single channel fit results not found -> comparisons are not produced!")
                
