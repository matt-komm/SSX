import ROOT
import math
import numpy
import random
import os

from defaultModules.Module import Module

import logging

class SamplesResUp(Module.getClass("Samples")):
    def __init__(self,options=[]):
        SamplesResUp.baseClass.__init__(self,options)
        self._logger = logging.getLogger(__file__)
        self._logger.setLevel(logging.DEBUG)
        
    def getSystematicPostFix(self):
        return "_ResUp"


class UtilsResUp(Module.getClass("Utils")):
    def __init__(self,options=[]):
        UtilsResUp.baseClass.__init__(self,options)
        self._logger = logging.getLogger(__file__)
        self._logger.setLevel(logging.DEBUG)
        
    def getUncertaintyName(self):
        return "resUp"
        
