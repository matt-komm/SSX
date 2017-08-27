import ROOT
import math
import numpy
import random
import os

from defaultModules.Module import Module

import logging

class SamplesEnUp(Module.getClass("Samples")):
    def __init__(self,options=[]):
        SamplesEnUp.baseClass.__init__(self,options)
        self._logger = logging.getLogger(__file__)
        self._logger.setLevel(logging.DEBUG)
        
    def getSystematicPostFix(self):
        return "_EnUp"


class UtilsEnUp(Module.getClass("Utils")):
    def __init__(self,options=[]):
        UtilsEnUp.baseClass.__init__(self,options)
        self._logger = logging.getLogger(__file__)
        self._logger.setLevel(logging.DEBUG)
        
    def getUncertaintyName(self):
        return "enUp"
        
