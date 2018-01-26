from defaultModules.Module import Module

import logging
import ROOT
import numpy

class LeptonEtaParticle(Module.getClass("Unfolding")):
    def __init__(self,options=[]):
        LeptonEtaParticle.baseClass.__init__(self,options)
        self._logger = logging.getLogger(__file__)
        self._logger.setLevel(logging.DEBUG)
        
    def getUnfoldingName(self):
        return "leta"
        
    def getUnfoldingVariableName(self):
        return "lepton |#eta|"
        
    def getUnfoldingVariableUnit(self):
        return ""
        
    def getUnfoldingLevel(self):
        return "particle"
        
    def getRecoBinning(self,channel):
        return numpy.array([0.0,0.3,0.7,1.5,1.8,2.4])
        
    def getRecoVariable(self,channel):
        return "fabs(SingleTop_1__TightLepton_1__Eta)"
        
    def getRecoWeight(self,channel):
        return self.module("Samples").getMCWeightReco(channel)
        
    def getRecoCut(self,channel):
        selection = self.module("Samples").getEventSelection(channel,iso=True)
        selection += "*"+self.module("Samples").getNjets(2)
        selection += "*"+self.module("Samples").getNbjets(1)
        return selection        
        
    def getGenBinning(self,channel):
        return numpy.array([0.0,0.3,0.7,1.5,1.8,2.4])
        
    def getGenVariable(self,channel):
        return "fabs(PTR_1__TightLepton_1__Eta)"
        
    def getGenWeight(self,channel):
        return self.module("Samples").getGenWeight()
        
    def getGenCut(self,channel="mu"):
        selection = "(Parton_1__Lepton_1__Pt>0)"
        if channel == "mu":
            selection+="*(abs(Parton_1__Lepton_1__pdg)==13)"
        elif channel == "ele":
            selection+="*(abs(Parton_1__Lepton_1__pdg)==11)"
        else:
            self._logger.error("Unknown channel selection '"+channel+"'")
        return selection
            
        
            
