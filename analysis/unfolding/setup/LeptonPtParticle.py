from defaultModules.Module import Module

import logging
import ROOT
import numpy

class LeptonPtParticle(Module.getClass("Unfolding")):
    def __init__(self,options=[]):
        LeptonPtParticle.baseClass.__init__(self,options)
        self._logger = logging.getLogger(__file__)
        self._logger.setLevel(logging.DEBUG)
        
    def getUnfoldingName(self):
        return "lpt"
        
    def getUnfoldingVariableName(self):
        return "lepton p#scale[0.7]{#lower[0.3]{T}}"
        
    def getUnfoldingVariableUnit(self):
        return "GeV"
        
    def getUnfoldingLevel(self):
        return "particle"
        
    def getRecoBinning(self):
        return numpy.array([30.,50.,60.,70.,90.,200.])
        
    def getRecoVariable(self):
        return "SingleTop_1__TightLepton_1__Pt"
        
    def getRecoWeight(self,channel="mu"):
        return self.module("Samples").getMCWeightReco(channel)
        
    def getRecoCut(self,channel="mu"):
        selection = self.module("Samples").getEventSelection(channel,iso=True)
        selection += "*"+self.module("Samples").getNjets(2)
        selection += "*"+self.module("Samples").getNbjets(1)
        return selection        
        
    def getGenBinning(self):
        return numpy.array([30.,50.,60.,70.,90.,200.])
        
    def getGenVariable(self):
        return "PTR_1__TightLepton_1__Pt"
        
    def getGenWeight(self,channel):
        return self.module("Samples").getGenWeight()
        
    def getGenCut(self,channel="mu"):
        selection = "(PTR_1__TopBest_1__Pt>0)*(PTR_1__nTightLepton==1)*(PTR_1__nSelectedJet==2)"
        if channel == "mu":
            selection+="*(abs(Parton_1__Lepton_1__pdg)==13)"
        elif channel == "ele":
            selection+="*(abs(Parton_1__Lepton_1__pdg)==11)"
        else:
            self._logger.error("Unknown channel selection '"+channel+"'")
        return selection
            
        
            
