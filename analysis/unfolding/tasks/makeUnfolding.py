from defaultModules.Module import Module

import logging
import ROOT
import copy
import os
import sys
from ModelClasses import *

class RunUnfolding(Module.getClass("Program")):
    def __init__(self,options=[]):
        Module.__init__(self,options)
        self._logger = logging.getLogger(__file__)
        self._logger.setLevel(logging.DEBUG)
        
    def execute(self):
        #mu,ele
        channels = self.getOption("channels").split(",")
        #inc,pt,y,cos
        unfoldingName = self.module("Unfolding").getUnfoldingName()
        if unfoldingName=="inc":
            self._logger.critical("Cannot unfolding inclusive xsec")
            sys.exit(1)


        fitOutput = os.path.join(
            self.module("Utils").getOutputFolder("fit"),
            self.module("ThetaModel").getFitFileName(channels,unfoldingName)
        )
        fitResult = self.module("ThetaFit").loadFitResult(fitOutput+".json")
        
        print fitResult["parameters"]["tChannel_neg_bin0"]
        print fitResult["parameters"]["tChannel_pos_bin0"]
        print fitResult["covariances"]["values"]["tChannel_pos_bin0"]["tChannel_neg_bin0"]
        
        
        #for profiled syst use nominal hist
        responseMatrixPos = None
        for channel in channels:
            responseFileName = self.module("Response").getOutputResponseFile(channel,unfoldingName,self.module("Utils").getUncertaintyName(),1)
            print responseFileName    
            
        responseMatrixNeg = None
        for channel in channels:
            self.module("Response").getOutputResponseFile(channel,unfoldingName,self.module("Utils").getUncertaintyName(),-1)
        
        
