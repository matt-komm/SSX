import ROOT
import math
import numpy
import random
import os

from defaultModules.Module import Module

import logging

class SamplesDYDown(Module.getClass("Samples")):
    def __init__(self,options=[]):
        SamplesDYDown.baseClass.__init__(self,options)
        self._logger = logging.getLogger(__file__)
        self._logger.setLevel(logging.DEBUG)
        
    def getSample(self,name,channel="mu",sys=None):
        result = SamplesDYDown.baseClass.getSample(self,name,channel,sys)
        if name=="DYMG" or name=="DYAMC":
            result["weight"]+="*(0.8)"
        if name=="WJetsAMCex" or name=="WJetsAMC":
            result["weight"]+="*(1.03)"
        return result


class UtilsDYDown(Module.getClass("Utils")):
    def __init__(self,options=[]):
        UtilsDYDown.baseClass.__init__(self,options)
        self._logger = logging.getLogger(__file__)
        self._logger.setLevel(logging.DEBUG)
        
    def getUncertaintyName(self):
        return "dyDown"
