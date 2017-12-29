import ROOT
import math
import numpy
import random
import os

from defaultModules.Module import Module

import logging

class SamplesUncDown(Module.getClass("Samples")):
    def __init__(self,options=[]):
        SamplesUncDown.baseClass.__init__(self,options)
        self._logger = logging.getLogger(__file__)
        self._logger.setLevel(logging.DEBUG)
        
    def getSystematicPostFix(self):
        return "_UncDown"


class UtilsUncDown(Module.getClass("Utils")):
    def __init__(self,options=[]):
        UtilsUncDown.baseClass.__init__(self,options)
        self._logger = logging.getLogger(__file__)
        self._logger.setLevel(logging.DEBUG)
        
    def getUncertaintyName(self):
        return "uncDown"
        
