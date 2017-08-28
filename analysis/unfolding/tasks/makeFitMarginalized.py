from defaultModules.Module import Module

import logging
import ROOT
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
                if unfoldingName=="inc":
                    fitSetup[channel+"_"+obserableName] = {
                        "bins":observableDict[obserableName]["bins"],
                        "range":observableDict[obserableName]["range"],
                        "components":{},
                        "data":histogramsPerChannelAndUncertainty[channel]["nominal"][0][obserableName]["data"]
                    }
                    for componentName in fitComponentDict.keys():
                        uncertaintyParameters = fitComponentDict[componentName]["uncertainties"]
                        fitSetup[channel+"_"+obserableName]["components"][componentName]={
                            "nominal":histogramsPerChannelAndUncertainty[channel]["nominal"][0][obserableName][componentName],
                            "yield":[],
                            "shape":[]
                        }
                        #print channel,obserableName,componentName,fitSetup[channel+"_"+obserableName][componentName]["nominal"]
                        for uncertaintyParameter in uncertaintyParameters:
                            if uncertaintyParameter.find("QCD")>=0:
                                #make extra parameter per channel for QCD
                                fitSetup[channel+"_"+obserableName]["components"][componentName]["yield"].append(uncertaintyParameter+"_"+channel)
                                if not parametersDict.has_key(uncertaintyParameter):
                                    parametersDict[uncertaintyParameter+"_"+channel]=uncertainyParameterDict[uncertaintyParameter]
                            else:
                                #take all other processes 100% correlated between channels
                                fitSetup[channel+"_"+obserableName]["components"][componentName]["yield"].append(uncertaintyParameter)
                                if not parametersDict.has_key(uncertaintyParameter):
                                    parametersDict[uncertaintyParameter]=uncertainyParameterDict[uncertaintyParameter]
                        
                        #add shape uncertainties
                        for sysName in uncertaintyList:
                            if not parametersDict.has_key(sysName):
                                parametersDict[sysName]=self.module("ThetaModel").makeGaus(0.,1.)
                            fitSetup[channel+"_"+obserableName]["components"][componentName]["shape"].append({
                                "parameter":sysName,
                                "up":histogramsPerChannelAndUncertainty[channel][sysName][0][0][obserableName][componentName],
                                "down":histogramsPerChannelAndUncertainty[channel][sysName][0][1][obserableName][componentName]
                            })
                            
        
        print parametersDict
        
        
        
        self.module("ThetaModel").makeModel(
            "fit_"+unfoldingName,
            fitSetup,parametersDict,
            outputFile=os.path.join(self.module("Utils").getOutputFolder(),"fit.root"),
            pseudo=False
        )
        '''
        else:
            nbins = len(self.module("Unfolding").getRecoBinning())-1
            for ibin in range(nbins):
                fitSetup[channel+"_"+obserableName+"_"+unfoldingName+str(ibin)] = {}
                for componentName in fitComponentDict.keys():
                    pass
        '''
        


        
        
