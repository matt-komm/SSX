import ROOT
import math
import numpy
import random
import os

from defaultModules.Module import Module

import logging

class SamplesDYUp(Module.getClass("Samples")):
    def __init__(self,options=[]):
        SamplesDYUp.baseClass.__init__(self,options)
        self._logger = logging.getLogger(__file__)
        self._logger.setLevel(logging.DEBUG)
        
    def getSample(self,name,channel="mu",sys=None):
        result = SamplesDYUp.baseClass.getSample(self,name,channel,sys)
        if name=="DYMG" or name=="DYAMC":
            result["weight"]+="*(1.2)
        if name=="WJetsAMCex" or name=="WJetsAMC":
            result["weight"]+="*(0.97)
        return result


class UtilsDYUp(Module.getClass("Utils")):
    def __init__(self,options=[]):
        UtilsDYUp.baseClass.__init__(self,options)
        self._logger = logging.getLogger(__file__)
        self._logger.setLevel(logging.DEBUG)
        
    def getUncertaintyName(self):
        return "dyUp"
