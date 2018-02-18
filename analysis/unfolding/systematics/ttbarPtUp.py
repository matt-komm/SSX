import ROOT
import math
import numpy
import random
import os

from defaultModules.Module import Module

import logging

#NOTE: phony class to make nominal sample looking like up variation

class SamplesTtbarPtUp(Module.getClass("Samples")):
    def __init__(self,options=[]):
        SamplesTtbarPtUp.baseClass.__init__(self,options)
        self._logger = logging.getLogger(__file__)
        self._logger.setLevel(logging.DEBUG)
        


class UtilsTtbarPtUp(Module.getClass("Utils")):
    def __init__(self,options=[]):
        UtilsTtbarPtUp.baseClass.__init__(self,options)
        self._logger = logging.getLogger(__file__)
        self._logger.setLevel(logging.DEBUG)
        
    def getUncertaintyName(self):
        return "ttbarPtUp"
        
