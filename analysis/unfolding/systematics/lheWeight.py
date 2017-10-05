import ROOT
import math
import numpy
import random
import os

from defaultModules.Module import Module

import logging

class SamplesLHEWeight(Module.getClass("Samples")):
    def __init__(self,options=[]):
        SamplesLHEWeight.baseClass.__init__(self,options)
        self._logger = logging.getLogger(__file__)
        self._logger.setLevel(logging.DEBUG)
        
    def getGenWeight(self):
        return "genweight*"+self.module("Samples").getLumi()+"*mcweight*(lheweight_"+self.getOption("lheWeight")+"/lheweight_1001)"


class UtilsLHEWeight(Module.getClass("Utils")):
    def __init__(self,options=[]):
        UtilsLHEWeight.baseClass.__init__(self,options)
        self._logger = logging.getLogger(__file__)
        self._logger.setLevel(logging.DEBUG)
        
    def getUncertaintyName(self):
        return "lheWeight_"+self.getOption("lheWeight")
        
