from defaultModules.Module import Module

import logging
import ROOT
import os
import sys
import math
import copy

# this generates the histograms (compound variable) for fitting

class ThetaModelWjets(Module.getClass("ThetaModel")):
    def __init__(self,options=[]):
        ThetaModelWjets.baseClass.__init__(self,options)
        self._logger = logging.getLogger(__file__)
        self._logger.setLevel(logging.DEBUG)
        
        
    def getFitFileName(self,channels,unfoldingName,postfix):
        return self.module("Samples").getChannelName(channels)+"__wjet"+unfoldingName+"__"+postfix
        
    def getHistogramPath(self,channel,unfoldingName,uncertainty=None):
        if not uncertainty:
            uncertainty = "nominal"
        return self.module("Utils").getOutputFolder(channel+"/"+uncertainty+"/"+unfoldingName)
        
    def getHistogramFile(self,channel,unfoldingName,unfoldingBin=-1,uncertainty="nominal",smooth=False):
        if smooth:
            return self.module("Utils").getHistogramFile("fitWjetHists_smooth",channel,unfoldingName,unfoldingBin,uncertainty)
        else:
            return self.module("Utils").getHistogramFile("fitWjetHists",channel,unfoldingName,unfoldingBin,uncertainty)

   
        
    def getObservablesDict(self,channel):
        tch = self.module("ThetaModel").getBDTtchan(channel)
        ttw = self.module("ThetaModel").getBDTttw(channel)
        charge = self.module("Samples").getRecoCharge()
    
        observables = {
            "2j0t": {
                "weight":self.module("Samples").getNjets(2)+"*"+self.module("Samples").getNbjets(0),
                "variable":charge+"*SingleTop_1__mtw_beforePz",
                "bins":32,
                "range":[-200.,200.]
            }
        }
        
        return observables
        
    def getUncertaintsDict(self):
        uncertaintiesBkg = {
            "Other":self.module("ThetaModel").makeLogNormal(1.0,0.3),
            "QCD_2j0t":self.module("ThetaModel").makeLogNormal(1.0,1.),
            
            "lumi":{"type":"gauss","config":{"mean": "1.0", "width":"0.025", "range":"(0.0,\"inf\")"}}
        }
        
        uncertainties={}
        for uncName in uncertaintiesBkg.keys():
            uncertainties[uncName]=copy.deepcopy(uncertaintiesBkg[uncName])
            # set 1% conservative charge confusion - might be far too high!!!
            uncertainties[uncName+"_ratio"]=self.module("ThetaModel").makeGaus(1.0,0.01)
        return uncertainties
    
    def getFitComponentsDict(self):
        componentsBkg = {
            "Other":
            {
                "sets":["tChannel","WJetsAMCex","DYMG","tWChannel","TTJets"],
                "uncertainties":["Other"],
                "weight":"1",
                "color":ROOT.kGreen+1
            },
            
            "QCD_2j0t":
            {
                "sets":["QCD_DD"],
                "uncertainties":["QCD_2j0t"],
                "weight":self.module("Samples").getNjets(2)+"*"+self.module("Samples").getNbjets(0),
                "color":ROOT.kGray
            },
        }
        
        components={}
        
        #use reco charge for backgrounds to add some uncertainty on the charge confusion!!!
        for compName in componentsBkg.keys():
            components[compName+"_pos"]=copy.deepcopy(componentsBkg[compName])
            components[compName+"_pos"]["weight"]+="*"+self.module("Samples").getRecoChargeSelection(1)
            components[compName+"_pos"]["uncertainties"].append(compName+"_ratio")
            components[compName+"_neg"]=copy.deepcopy(componentsBkg[compName])
            components[compName+"_neg"]["weight"]+="*"+self.module("Samples").getRecoChargeSelection(-1)

        return components
        
