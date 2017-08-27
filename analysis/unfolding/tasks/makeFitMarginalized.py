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
            
                #TODO: add data!!!
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
        for channel in channels:
            for obserableName in observableDict.keys():
                #make a separate observable per channel (and bin) 
                fitSetup[channel+"_"+obserableName] = {}
                for componentName in fitComponentDict.keys():
                    pass
        


        
        
