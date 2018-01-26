from defaultModules.Module import Module

import logging
import ROOT
import os

# this generates the process -> file dict for faster generation of histograms

class FileDictGenerator(Module.getClass("Program")):
    def __init__(self,options=[]):
        Module.__init__(self,options)
        self._logger = logging.getLogger(__file__)
        self._logger.setLevel(logging.DEBUG)
        
    def execute(self):
        self.module("Utils").createFolder("global")
        self.module("Samples").makeProcessFileDict("mu")
        self.module("Samples").makeProcessFileDict("ele")
        self.module("Samples").saveProcessFileDict(self.module("Utils").getOutputFolder("global/fileDictMu.json"),"mu")
        self.module("Samples").saveProcessFileDict(self.module("Utils").getOutputFolder("global/fileDictEle.json"),"ele")
                
        
