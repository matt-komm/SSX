from defaultModules.Module import Module

import logging
import ROOT
import numpy

class TopPtParton(Module.getClass("Unfolding")):
    def __init__(self,options=[]):
        Module.__init__(self,options)
        self._logger = logging.getLogger(__file__)
        self._logger.setLevel(logging.DEBUG)
        
    def getUnfoldingName(self):
        return "pt"
        
    def getRecoBinning(self):
        return [0.,50.,90.,130.,180.,240.,300.]
        
    def getRecoVariable(self):
        return "SingleTop_1__Top_1__Pt"
        
    def getRecoWeight(self,channel="mu"):
        return self.module("Samples").getMCWeight(channel,iso=True)
        
    def getRecoCut(self,channel="mu"):
        selection = self.module("Samples").getEventSelection(channel,iso=True)
        selection += "*"+self.module("Samples").getNjets(2)
        selection += "*"+self.module("Samples").getNbjets(1)
        return selection        
        
    def getGenBinning(self):
        return [0.,50.,90.,130.,180.,240.,300.]
        
    def getGenVariable(self):
        return "PTR_1__TopBest_1__Pt"
        
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

            
        
            
