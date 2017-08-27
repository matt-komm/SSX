import ROOT
import math
import numpy
import random
import os

from defaultModules.Module import Module

import logging

class SamplesEnDown(Module.getClass("Samples")):
    def __init__(self,options=[]):
        SamplesEnDown.baseClass.__init__(self,options)
        self._logger = logging.getLogger(__file__)
        self._logger.setLevel(logging.DEBUG)
        
    def getSystematicPostFix(self):
        return "_EnDown"


class UtilsEnDown(Module.getClass("Utils")):
    def __init__(self,options=[]):
        UtilsEnDown.baseClass.__init__(self,options)
        self._logger = logging.getLogger(__file__)
        self._logger.setLevel(logging.DEBUG)
        
    def getUncertaintyName(self):
        return "enDown"
        
