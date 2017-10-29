import ROOT
import math
import numpy
import random
import os

from defaultModules.Module import Module

import logging

class SamplesUncUp(Module.getClass("Samples")):
    def __init__(self,options=[]):
        SamplesUncUp.baseClass.__init__(self,options)
        self._logger = logging.getLogger(__file__)
        self._logger.setLevel(logging.DEBUG)
        
    def getSystematicPostFix(self):
        return "_UncUp"


class UtilsUncUp(Module.getClass("Utils")):
    def __init__(self,options=[]):
        UtilsUncUp.baseClass.__init__(self,options)
        self._logger = logging.getLogger(__file__)
        self._logger.setLevel(logging.DEBUG)
        
    def getUncertaintyName(self):
        return "uncUp"
        
