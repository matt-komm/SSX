import ROOT
import math
import numpy
import random
import os

from defaultModules.Module import Module

import logging

class SamplesTWUp(Module.getClass("Samples")):
    def __init__(self,options=[]):
        SamplesTWUp.baseClass.__init__(self,options)
        self._logger = logging.getLogger(__file__)
        self._logger.setLevel(logging.DEBUG)
        
    def getSample(self,name,channel="mu",sys=None):
        result = SamplesTWUp.baseClass.getSample(self,name,channel,sys)
        if name=="tWChannel":
            result["weight"]+="*(1.2)"
        if name=="TTJets":
            result["weight"]+="*(0.978)"
        return result


class UtilsTWUp(Module.getClass("Utils")):
    def __init__(self,options=[]):
        UtilsTWUp.baseClass.__init__(self,options)
        self._logger = logging.getLogger(__file__)
        self._logger.setLevel(logging.DEBUG)
        
    def getUncertaintyName(self):
        return "twUp"
