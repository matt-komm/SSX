import ROOT
import math
import numpy
import random
import os

from defaultModules.Module import Module

import logging

class SamplesEleMultiVetoDown(Module.getClass("Samples")):
    def __init__(self,options=[]):
        SamplesEleMultiVetoDown.baseClass.__init__(self,options)
        self._logger = logging.getLogger(__file__)
        self._logger.setLevel(logging.DEBUG)
        
    def getEleAntiisoSelection(self):
        return "(Reconstructed_1__EleTight32_vALL==1)*(Reconstructed_1__elecat==2)*(abs(SingleTop_1__TightLepton_1__superClusterEta)<1.479)*(SingleTop_1__TightLepton_1__passConversionVeto<0.5)"
        
class UtilsEleMultiVetoDown(Module.getClass("Utils")):
    def __init__(self,options=[]):
        UtilsEleMultiVetoDown.baseClass.__init__(self,options)
        self._logger = logging.getLogger(__file__)
        self._logger.setLevel(logging.DEBUG)
        
    def getUncertaintyName(self):
        return "eleMultiVetoDown"
