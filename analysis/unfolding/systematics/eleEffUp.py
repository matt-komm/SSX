import ROOT
import math
import numpy
import random
import os

from defaultModules.Module import Module

import logging

class SamplesEleEffUp(Module.getClass("Samples")):
    def __init__(self,options=[]):
        SamplesEleEffUp.baseClass.__init__(self,options)
        self._logger = logging.getLogger(__file__)
        self._logger.setLevel(logging.DEBUG)
        
    def getEleMCWeight(self):
        return "(testing==1)*(1./testing_frac)*(Reconstructed_1__btagging_nominal*Reconstructed_1__PU69000_weight*Reconstructed_1__eleRECO_SF_up*Reconstructed_1__eleID_SF_up*Reconstructed_1__eleTRIGGER_SF_up)"
        
class UtilsEleEffUp(Module.getClass("Utils")):
    def __init__(self,options=[]):
        UtilsEleEffUp.baseClass.__init__(self,options)
        self._logger = logging.getLogger(__file__)
        self._logger.setLevel(logging.DEBUG)
        
    def getUncertaintyName(self):
        return "eleEffUp"
