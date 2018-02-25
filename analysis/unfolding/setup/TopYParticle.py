from defaultModules.Module import Module

import logging
import ROOT
import numpy

class TopYParticle(Module.getClass("Unfolding")):
    def __init__(self,options=[]):
        TopYParticle.baseClass.__init__(self,options)
        self._logger = logging.getLogger(__file__)
        self._logger.setLevel(logging.DEBUG)
        
    def getUnfoldingName(self):
        return "y"
        
    def getUnfoldingVariableName(self):
        return "top quark |y|"
        
    def getUnfoldingSymbol(self):
        return "|y|"
        
    def getUnfoldingVariableUnit(self):
        return ""
        
    def getUnfoldingLevel(self):
        return "particle"
        
    def getRecoBinning(self,channel):
        return numpy.array([0.,0.2,0.5,0.8,1.3,2.6])
        
    def getRecoVariable(self,channel):
        return "fabs(SingleTop_1__Top_1__Y)"
        
    def getRecoWeight(self,channel):
        return self.module("Samples").getMCWeightReco(channel)
        
    def getRecoCut(self,channel):
        selection = self.module("Samples").getEventSelection(channel,iso=True)
        selection += "*"+self.module("Samples").getNjets(2)
        selection += "*"+self.module("Samples").getNbjets(1)
        return selection        
        
    def getGenBinning(self,channel):
        return numpy.array([0.,0.2,0.5,0.8,1.3,2.6])
        
    def getGenVariable(self,channel):
        return "fabs(PTR_1__TopBest_1__Y)"
        
    def getGenWeight(self,channel):
        return self.module("Samples").getGenWeight()
        
    def getGenCut(self,channel):
        selection = "(PTR_1__TopBest_1__Pt>0)*(PTR_1__nTightLepton==1)*(PTR_1__nSelectedJet==2)"
        if channel == "mu":
            selection+="*(abs(Parton_1__Lepton_1__pdg)==13)"
        elif channel == "ele":
            selection+="*(abs(Parton_1__Lepton_1__pdg)==11)"
        else:
            self._logger.error("Unknown channel selection '"+channel+"'")
        return selection



            
        
            
