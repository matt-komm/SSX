import ROOT
import math
import numpy
import random
import os

from defaultModules.Module import Module

import logging

class SamplesTWDown(Module.getClass("Samples")):
    def __init__(self,options=[]):
        SamplesTWDown.baseClass.__init__(self,options)
        self._logger = logging.getLogger(__file__)
        self._logger.setLevel(logging.DEBUG)
        
    def getSample(self,name,channel="mu",sys=None):
        result = SamplesTWDown.baseClass.getSample(self,name,channel,sys)
        if name=="tWChannel":
            result["weight"]+="*(0.8)
        if name=="TTJets":
            result["weight"]+="*(1.022)
        return result


class UtilsTWDown(Module.getClass("Utils")):
    def __init__(self,options=[]):
        UtilsTWDown.baseClass.__init__(self,options)
        self._logger = logging.getLogger(__file__)
        self._logger.setLevel(logging.DEBUG)
        
    def getUncertaintyName(self):
        return "twDown"
