import ROOT
import math
import numpy
import random
import os

from defaultModules.Module import Module

import logging

class SamplesPUDown(Module.getClass("Samples")):
    def __init__(self,options=[]):
        SamplesPUDown.baseClass.__init__(self,options)
        self._logger = logging.getLogger(__file__)
        self._logger.setLevel(logging.DEBUG)
        
    def getMuMCWeight(self):
        return "(Reconstructed_1__btagging_nominal*Reconstructed_1__PU65000_weight*Reconstructed_1__muISO_SF_nominal*Reconstructed_1__muID_SF_nominal*Reconstructed_1__muTRIGGER_SF_nominal)"
        
    def getEleMCWeight(self):
        return "(Reconstructed_1__btagging_nominal*Reconstructed_1__PU65000_weight*Reconstructed_1__eleRECO_SF_nominal*Reconstructed_1__eleID_SF_nominal)"


class UtilsPUDown(Module.getClass("Utils")):
    def __init__(self,options=[]):
        UtilsPUDown.baseClass.__init__(self,options)
        self._logger = logging.getLogger(__file__)
        self._logger.setLevel(logging.DEBUG)
        
    def getUncertaintyName(self):
        return "puDown"
