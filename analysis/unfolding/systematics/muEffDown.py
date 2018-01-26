import ROOT
import math
import numpy
import random
import os

from defaultModules.Module import Module

import logging

class SamplesMuEffDown(Module.getClass("Samples")):
    def __init__(self,options=[]):
        SamplesMuEffDown.baseClass.__init__(self,options)
        self._logger = logging.getLogger(__file__)
        self._logger.setLevel(logging.DEBUG)
        
    def getMuMCWeight(self):
        return "(testing==1)*(1./testing_frac)*(Reconstructed_1__btagging_nominal*Reconstructed_1__PU69000_weight*Reconstructed_1__muISO06_SF_down*Reconstructed_1__muID06_SF_down*Reconstructed_1__muTRIGGER06_SF_down)"

class UtilsMuEffDown(Module.getClass("Utils")):
    def __init__(self,options=[]):
        UtilsMuEffDown.baseClass.__init__(self,options)
        self._logger = logging.getLogger(__file__)
        self._logger.setLevel(logging.DEBUG)
        
    def getUncertaintyName(self):
        return "muEffDown"
