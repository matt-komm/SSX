import ROOT
import math
import numpy
import random
import os

from defaultModules.Module import Module

import logging

class SamplesMuMultiDown(Module.getClass("Samples")):
    def __init__(self,options=[]):
        SamplesMuMultiDown.baseClass.__init__(self,options)
        self._logger = logging.getLogger(__file__)
        self._logger.setLevel(logging.DEBUG)
        
    def getMuAntiisoSelection(self):
        return "(Reconstructed_1__IsoMu24_vALL==1)*(Reconstructed_1__muoncat==2)*(SingleTop_1__TightLepton_1__deltaBetaRelIso<0.4)"

class UtilsMuMultiDown(Module.getClass("Utils")):
    def __init__(self,options=[]):
        UtilsMuMultiDown.baseClass.__init__(self,options)
        self._logger = logging.getLogger(__file__)
        self._logger.setLevel(logging.DEBUG)
        
    def getUncertaintyName(self):
        return "muMultiDown"
