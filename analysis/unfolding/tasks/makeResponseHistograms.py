from defaultModules.Module import Module

import logging
import ROOT
import os

# this generates the histograms (compound variable) for fitting

class ResponseHistograms(Module.getClass("Program")):
    def __init__(self,options=[]):
        Module.__init__(self,options)
        self._logger = logging.getLogger(__file__)
        self._logger.setLevel(logging.DEBUG)
        
    def execute(self):
        self.module("Samples").loadProcessFileDict(self.module("Utils").getOutputFolder("global/fileDictMu.json"),"mu")
        self.module("Samples").loadProcessFileDict(self.module("Utils").getOutputFolder("global/fileDictEle.json"),"ele")
    
        channel = self.getOption("channel")
        genCharge = int(self.getOption("charge"))
        
        unfoldingName = self.module("Unfolding").getUnfoldingName()
        unfoldingLevel = self.module("Unfolding").getUnfoldingLevel()
        
        self._logger.info("Select channel: "+channel)
        self._logger.info("Select gen charge: "+str(genCharge))
        self._logger.info("Unfolding name: "+unfoldingName)
        self._logger.info("Unfolding level: "+unfoldingLevel)
        
        outputFolder = self.module("Response").getOutputFolder(channel,unfoldingName,self.module("Utils").getUncertaintyName())
        self.module("Utils").createFolder(outputFolder)
        
        self.module("Response").makeResponse(
            channel,
            genCharge,
            self.module("Response").getOutputResponseFile(channel,unfoldingName,unfoldingLevel,self.module("Utils").getUncertaintyName(),genCharge)
        )
        
        

        
        
        
