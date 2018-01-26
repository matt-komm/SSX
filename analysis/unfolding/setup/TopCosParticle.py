from defaultModules.Module import Module

import logging
import ROOT
import numpy

class TopCosParticle(Module.getClass("Unfolding")):
    def __init__(self,options=[]):
        TopCosParticle.baseClass.__init__(self,options)
        self._logger = logging.getLogger(__file__)
        self._logger.setLevel(logging.DEBUG)
        
    def getUnfoldingName(self):
        return "cos"
        
    def getUnfoldingVariableName(self):
        return "cos#kern[0.1]{#theta}#scale[0.7]{#lower[0.28]{pol.}}#kern[-1.1]{*}"
        
    def getUnfoldingVariableUnit(self):
        return ""
        
    def getUnfoldingLevel(self):
        return "particle"
        
    def getRecoBinning(self,channel):
        return numpy.array([-1.0,-0.6,-0.3,0.0,0.3,0.6,1.0])
        
    def getRecoVariable(self,channel):
        return "SingleTop_1__cosTheta_tPLz"
        
    def getRecoWeight(self,channel):
        return self.module("Samples").getMCWeightReco(channel)
        
    def getRecoCut(self,channel):
        selection = self.module("Samples").getEventSelection(channel,iso=True)
        selection += "*"+self.module("Samples").getNjets(2)
        selection += "*"+self.module("Samples").getNbjets(1)
        return selection        
        
    def getGenBinning(self,channel):
        return numpy.array([-1.0,-0.6,-0.3,0.0,0.3,0.6,1.0])
        
    def getGenVariable(self,channel):
        return "PTR_1__best_cosTheta_tPLz"
        
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

            
        
            
