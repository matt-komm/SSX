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
        
        smoothing = True if (self.getOption("smoothing")!=None and self.getOption("smoothing")=="1") else False
        self._logger.info("apply smoothing: "+str(smoothing))
        
        #maps channel bins to global bins for combinations
        if unfoldingName!="inc":
            binMap = self.module("Unfolding").buildGlobalRecoBinMap()
        
        for channel in channels:
            histogramsPerChannel[channel]={}
            histogramsPerChannel[channel]["nominal"]={}
            if unfoldingName=="inc":
                histogramsPerChannel[channel]["nominal"]["binInc"] = \
                    self.module("ThetaModel").getHistsFromFiles(channel,unfoldingName,-1,uncertainty,smooth=smoothing and uncertainty!="nominal")
                
            else:
                nbins = len(self.module("Unfolding").getRecoBinning(channel))-1
                for ibin in range(nbins):
                    histogramsPerChannel[channel]["nominal"]["bin"+str(1+binMap[channel][ibin])] = \
                        self.module("ThetaModel").getHistsFromFiles(channel,unfoldingName,ibin,uncertainty,smooth=smoothing and uncertainty!="nominal")
                    
            
        fitSetup = {}
        combineChannels = False
        parametersDict = {}
        
        
        for channel in channels:
            observableDict = self.module("ThetaModel").getObservablesDict(channel)
            fitComponentDict = self.module("ThetaModel").getFitComponentsDict()
            uncertainyParameterDict = self.module("ThetaModel").getUncertaintsDict()
        
            for obserableName in observableDict.keys():
                #make a separate observable per channel (and bin) 
                binNames = histogramsPerChannel[channel]["nominal"].keys()
                for binName in binNames:
                    obsName = channel+"__"+obserableName+"__"+binName
                    if combineChannels and len(channels)>=2:
                        obsName = obserableName+"__"+binName
                
                    if not fitSetup.has_key(obsName):
                        fitSetup[obsName] = {
                            "bins":observableDict[obserableName]["bins"],
                            "range":observableDict[obserableName]["range"],
                            "components":{},
                            "data":[histogramsPerChannel[channel]["nominal"][binName][obserableName]["data"]]
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
                            histogramsPerChannel[channel]["nominal"][binName][obserableName]["data"]
                        )
                        
                    for componentName in fitComponentDict.keys():
                        uncertaintyParameters = fitComponentDict[componentName]["uncertainties"]
                        fitSetup[obsName]["components"][channel+"_"+componentName]={
                            "nominal":histogramsPerChannel[channel]["nominal"][binName][obserableName][componentName],
                            "yield":[],
                            "shape":[]
                        }
                        #print channel,obserableNamechannel+"_"+,componentName,fitSetup[channel+"_"+obserableName][componentName]["nominal"]
                        for uncertaintyParameter in uncertaintyParameters:
                            if uncertaintyParameter.find("QCD")>=0:
                                #make extra parameter per channel for QCD
                                fitSetup[obsName]["components"][channel+"_"+componentName]["yield"].append(uncertaintyParameter+"_"+binName+"_"+channel)
                                if not parametersDict.has_key(uncertaintyParameter+"_"+binName+"_"+channel):
                                    parametersDict[uncertaintyParameter+"_"+binName+"_"+channel]=copy.deepcopy(uncertainyParameterDict[uncertaintyParameter])
                            else:
                                #take all other processes 100% correlated between channels
                                fitSetup[obsName]["components"][channel+"_"+componentName]["yield"].append(uncertaintyParameter+"_"+binName)
                                if not parametersDict.has_key(uncertaintyParameter+"_"+binName):
                                    parametersDict[uncertaintyParameter+"_"+binName]=copy.deepcopy(uncertainyParameterDict[uncertaintyParameter])
                        
                        
                
                                    
        
        self.module("Utils").createFolder("fit/"+uncertainty)
        fitOutput = os.path.join(
            self.module("Utils").getOutputFolder("fit/"+uncertainty),
            self.module("ThetaModel").getFitFileName(channels,unfoldingName,uncertainty)
        )
        
        fitResultsSucess = []
        isuccess = -1
        while (len(fitResultsSucess)<4 and isuccess<20):
            success = False
            retry = 20
            itry = 0
            isuccess+=1
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
                    avgcorr = self.module("ThetaFit").checkDegenerated(fitResult)
                    self._logger.info("Fit avg correlation: "+str(avgcorr))
                    if (avgcorr>0.4):
                        raise Exception("Degenerated fit: "+str(avgcorr))
                        
                    dets = self.module("ThetaFit").checkSignalDeterminant(fitResult,channelName)
                    self._logger.info("Fit signal dets: "+str(dets))
                    if (unfoldingName!="inc") and (min(dets)<10.**(-60) or max(dets)>10.**(60)):
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
        
        ROOT.gStyle.SetPaintTextFormat("4.0f")
        cv = ROOT.TCanvas("corr","",1000,900)
        cv.SetLeftMargin(0.3 if unfoldingName=="inc" else 0.16)
        cv.SetRightMargin(0.15)
        cv.SetBottomMargin(0.34 if unfoldingName=="inc" else 0.19)
        fitResult["correlations"]["hist"].SetMarkerSize(1. if unfoldingName=="inc" else 0.35)
        fitResult["correlations"]["hist"].Scale(100.)
        fitResult["correlations"]["hist"].GetXaxis().SetTitleSize(0.5)
        fitResult["correlations"]["hist"].GetXaxis().LabelsOption("v")
        fitResult["correlations"]["hist"].GetXaxis().SetLabelSize(22 if unfoldingName=="inc" else 12)
        fitResult["correlations"]["hist"].GetYaxis().SetLabelSize(22 if unfoldingName=="inc" else 12)
        fitResult["correlations"]["hist"].GetZaxis().SetLabelSize(25)
        fitResult["correlations"]["hist"].GetYaxis().SetTitleSize(0.5)
        fitResult["correlations"]["hist"].GetZaxis().SetTitle("Correlation (%)")
        fitResult["correlations"]["hist"].GetZaxis().SetTitleSize(25)
        fitResult["correlations"]["hist"].Draw("colztext")
        cv.Print(fitOutput+"_correlation.pdf")
                
        print fitResult["covariances"]["values"].keys()
        self.module("ThetaFit").saveFitResult(fitOutput+".json",fitResult)
        
        for channel in channels:
            observableDict = self.module("ThetaModel").getObservablesDict(channel)
            fitComponentDict = self.module("ThetaModel").getFitComponentsDict()
            uncertainyParameterDict = self.module("ThetaModel").getUncertaintsDict()
        
            for obserableName in observableDict.keys():
                
                #make a separate observable per channel (and bin) 
                binNames = histogramsPerChannel[channel]["nominal"].keys()
                for binName in binNames:
                    mcSum = 0.0
                    mcSumErr2 = 0.0
                    
                    yieldsPerComp = {}
                    err2PerComp = {}
                    
                    hist = histogramsPerChannel[channel]["nominal"][binName][obserableName]["data"]["hist"]
                    hist.Rebin(hist.GetNbinsX())
                    
                    #print channel,obserableName,binName,"data",round(hist.GetBinContent(1),1),round(math.sqrt(hist.GetBinContent(1)),1)
                    
                    for componentName in fitComponentDict.keys():
                        uncertaintyParameters = fitComponentDict[componentName]["uncertainties"]
                        
                        hist = histogramsPerChannel[channel]["nominal"][binName][obserableName][componentName]["hist"]
                        hist.Rebin(hist.GetNbinsX())
                        for uncertaintyParameter in uncertaintyParameters:
                            if uncertaintyParameter.find("QCD")>=0:
                                parameterName = uncertaintyParameter+"_"+binName+"_"+channel
                            else:
                                parameterName = uncertaintyParameter+"_"+binName
                            hist.Scale(fitResult["parameters"][parameterName]["mean_fit"])
                        err = math.sqrt(
                            hist.GetBinError(1)**2 + \
                            hist.GetBinContent(1)**2*fitResult["parameters"][parameterName]["unc_fit"]**2
                        )
                        compName =  componentName.replace("_neg","").replace("_pos","")
                        if not yieldsPerComp.has_key(compName):
                            yieldsPerComp[compName] = 0.0
                            err2PerComp[compName] = 0.0
                        yieldsPerComp[compName] += hist.GetBinContent(1)
                        err2PerComp[compName] += err**2
                        mcSum += hist.GetBinContent(1)

                        mcSumErr2 += err**2
                        
                    '''
                    for componentName in yieldsPerComp.keys():
                        print channel,obserableName,binName,componentName,round(yieldsPerComp[componentName],1),round(math.sqrt(err2PerComp[componentName]),1)
                        
                    print channel,obserableName,binName,"total",round(mcSum,1),round(math.sqrt(mcSumErr2),1)
                    '''
        self.module("Drawing").drawPosterior({channelName:fitResult},fitOutput+"__posteriors_yield.pdf",
            selection=["Other_bin*","tChannel_*_bin*","WZjets_bin*","WZjets_HF_bin*","WZjets_LF_bin*","TopBkg_bin*","QCD_*_bin*"],
            ranges = [0,2.0],
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
                
            else:
                self._logger.warning("Single channel fit results not found -> comparisons are not produced!")
                

        
        
