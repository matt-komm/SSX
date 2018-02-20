import ROOT
import math
import numpy
import random
import os

from defaultModules.Module import Module

import logging


#https://indico.cern.ch/event/494682/contributions/1172505/attachments/1223578/1800218/mcaod-Feb15-2016.pdf
#https://twiki.cern.ch/twiki/bin/view/CMS/TopSystematics#Factorization_and_renormalizatio
variations = {
    "NU":"1002",
    "ND":"1003",
    "UN":"1004",
    "DN":"1007",
    "UU":"1005",
    "DD":"1009",
    #these are the max variations
    "Down":"1009",
    "Up":"1005",
}

class SamplesTchanScaleTmpl(Module.getClass("Samples")):
    def __init__(self,options=[]):
        SamplesTchanScaleTmpl.baseClass.__init__(self,options)
        self._logger = logging.getLogger(__file__)
        self._logger.setLevel(logging.DEBUG)
        self._variation = self.getOption("qscale")
        self._lheNumber = variations[self._variation]

    def getSample(self,name,channel="mu",sys=None):
        result = SamplesTchanScaleTmpl.baseClass.getSample(self,name,channel,sys)
        if name == "tChannel":
            result["weight"]+="*(lheweight_"+str(self._lheNumber)+")"
        return result
        
class UnfoldingTchanScaleTmpl(Module.getClass("Unfolding")):
    def __init__(self,options=[]):
        UnfoldingTchanScaleTmpl.baseClass.__init__(self,options)
        self._logger = logging.getLogger(__file__)
        self._logger.setLevel(logging.DEBUG)
        self._variation = self.getOption("qscale")
        self._lheNumber = variations[self._variation]
        
    def getGenWeight(self,channel):
        weight = UnfoldingTchanScaleTmpl.baseClass.getGenWeight(self,channel)
        weight+="*(lheweight_"+str(self._lheNumber)+")"
        return weight
    

class UtilsTchanScaleTmpl(Module.getClass("Utils")):
    def __init__(self,options=[]):
        UtilsTchanScaleTmpl.baseClass.__init__(self,options)
        self._logger = logging.getLogger(__file__)
        self._logger.setLevel(logging.DEBUG)
        self._variation = self.getOption("qscale")
        
    def getUncertaintyName(self):
        return "tchanScaleME"+self._variation
        
