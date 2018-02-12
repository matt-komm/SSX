import ROOT
import math
import numpy
import random
import os

from defaultModules.Module import Module

import logging

class SamplesResDown(Module.getClass("Samples")):
    def __init__(self,options=[]):
        SamplesResDown.baseClass.__init__(self,options)
        self._logger = logging.getLogger(__file__)
        self._logger.setLevel(logging.DEBUG)
        
    def getSystematicPostFix(self):
        return "_ResDown"


class UtilsResDown(Module.getClass("Utils")):
    def __init__(self,options=[]):
        UtilsResDown.baseClass.__init__(self,options)
        self._logger = logging.getLogger(__file__)
        self._logger.setLevel(logging.DEBUG)
        
    def getUncertaintyName(self):
        return "resDown"
        
