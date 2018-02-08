import ROOT
import math
import numpy
import random
import os

from defaultModules.Module import Module

import logging

class SamplesEleMultiIsoUp(Module.getClass("Samples")):
    def __init__(self,options=[]):
        SamplesEleMultiIsoUp.baseClass.__init__(self,options)
        self._logger = logging.getLogger(__file__)
        self._logger.setLevel(logging.DEBUG)
        
    def getEleAntiisoSelection(self):
        return "(Reconstructed_1__EleTight32_vALL==1)*(Reconstructed_1__elecat==2)*(SingleTop_1__TightLepton_1__effAreaRelIso<0.85)*(abs(SingleTop_1__TightLepton_1__superClusterEta)<1.479)*(SingleTop_1__TightLepton_1__effAreaRelIso>0.0588)"
        
class UtilsEleMultiIsoUp(Module.getClass("Utils")):
    def __init__(self,options=[]):
        UtilsEleMultiIsoUp.baseClass.__init__(self,options)
        self._logger = logging.getLogger(__file__)
        self._logger.setLevel(logging.DEBUG)
        
    def getUncertaintyName(self):
        return "eleMultiIsoUp"
