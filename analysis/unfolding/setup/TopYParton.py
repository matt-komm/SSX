from defaultModules.Module import Module

import logging
import ROOT
import numpy

class TopYParton(Module.getClass("Unfolding")):
    def __init__(self,options=[]):
        TopYParton.baseClass.__init__(self,options)
        self._logger = logging.getLogger(__file__)
        self._logger.setLevel(logging.DEBUG)
        
    def getUnfoldingName(self):
        return "y"
        
    def getRecoBinning(self):
        return [0.,0.15,0.45,0.7,1.1,1.5,2.4]
        
    def getRecoVariable(self):
        return "fabs(SingleTop_1__Top_1__Y)"
        
    def getRecoWeight(self,channel="mu"):
        return self.module("Samples").getMCWeight(channel,iso=True)
        
    def getRecoCut(self,channel="mu"):
        selection = self.module("Samples").getEventSelection(channel,iso=True)
        selection += "*"+self.module("Samples").getNjets(2)
        selection += "*"+self.module("Samples").getNbjets(1)
        return selection        
        
    def getGenBinning(self):
        return [0.,0.15,0.45,0.7,1.1,1.5,2.4]
        
    def getGenVariable(self):
        return "fabs(PTR_1__TopBest_1__Y)"
        
    def getGenWeight(self):
        return self.module("Samples").getGenWeight()
        
    def getGenCut(self,channel="mu"):
        selection = "(PTR_1__TopBest_1__Pt>0)*(PTR_1__nTightLepton==1)*(PTR_1__nSelectedJet==2)"
        if channel == "mu":
            selection+="*(abs(PTR_1__TightLepton_1__pdg)==13)"
        elif channel == "ele":
            selection+="*(abs(PTR_1__TightLepton_1__pdg)==11)"
        else:
            self._logger.error("Unknown channel selection '"+channel+"'")

            
        
            