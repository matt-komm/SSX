import re
import os
import ROOT
import random

from Module import Module

import logging

class Files(Module):
    def __init__(self,options=[]):
        Module.__init__(self,options)
        self._logger = logging.getLogger(__file__)
        self._logger.setLevel(logging.DEBUG)
        
        
    def getVersion(self):
        return "7"
        
        
    def getSystematicPostfix(self):
        return ""


    def getMCSignal(self,channel,requireFriends=True):
        rootFiles = []
        nFriends = 0
    
        basedirSignalMC = "/nfs/user/mkomm/SSX13/signalMC/"+channel+self.module("Files").getVersion()
        matchSignalMC = re.compile("^signalMC[A-Za-z0-9_\-]*[0-9]+.root$")
        
        for f in os.listdir(basedirSignalMC):
            if matchSignalMC.match(f) and f.find("veto")<0 and f.find("train")<0 and f.find("test")<0:
                l = []
                l.append(os.path.join(basedirSignalMC,f))
                if os.path.exists(os.path.join(basedirSignalMC,f+".friend")):
                    l.append(os.path.join(basedirSignalMC,f+".friend"))
                    rootFiles.append(l)
                    nFriends+=1
                else:
                    if requireFriends:
                        self._logger.error("friend of file '"+os.path.join(basedirSignalMC,f)+"' missing! -> skip")
                    else:
                        rootFiles.append(l)
                        
        self._logger.debug("found signal files "+str(len(rootFiles))+"/"+str(nFriends)+" in "+basedirSignalMC)
        return rootFiles
        
    def getMCSignalGen(self,channel):
        rootFiles = []
        nFriends = 0
    
        basedirSignalMCGen = "/nfs/user/mkomm/SSX13/signalMCGen/"+channel+self.module("Files").getVersion()
        matchSignalMCGen = re.compile("^signalMC_gen[0-9]+.root$")
        
        for f in os.listdir(basedirSignalMCGen):
            if matchSignalMCGen.match(f):
                rootFiles.append([os.path.join(basedirSignalMCGen,f)])
                        
        self._logger.debug("found signal gen files "+str(len(rootFiles))+" in "+basedirSignalMCGen)
        return rootFiles
        

    def getMCBackground(self,channel,requireFriends=True):
        rootFiles = []
        nFriends = 0

        basedirBackgroundMC = "/nfs/user/mkomm/SSX13/backgroundMC/"+channel+self.module("Files").getVersion()
        matchBackgroundMC = re.compile("^backgroundMC[A-Za-z0-9_\-]*[0-9]+.root$")
        
        for f in os.listdir(basedirBackgroundMC):
            if matchBackgroundMC.match(f) and f.find("veto")<0 and f.find("train")<0 and f.find("test")<0:
                l = []
                l.append(os.path.join(basedirBackgroundMC,f))
                if os.path.exists(os.path.join(basedirBackgroundMC,f+".friend")):
                    l.append(os.path.join(basedirBackgroundMC,f+".friend"))
                    rootFiles.append(l)
                    nFriends+=1
                else:
                    if requireFriends:
                        self._logger.error("friend of file '"+os.path.join(basedirBackgroundMC,f)+"' missing! -> skip")
                    else:
                        rootFiles.append(l)
                       
        self._logger.debug("found background files "+str(len(rootFiles))+"/"+str(nFriends)+" in "+basedirBackgroundMC)
        return rootFiles


    def getDataFiles(self,channel,requireFriends=True):
        rootFiles = []
        nFriends = 0

        basedirData = "/nfs/user/mkomm/SSX13/data/"+channel+self.module("Files").getVersion()
        matchData = re.compile("^data[0-9]+.root$")
        
        for f in os.listdir(basedirData):
            if matchData.match(f):
                l = []
                l.append(os.path.join(basedirData,f))
                if os.path.exists(os.path.join(basedirData,f+".friend")):
                    l.append(os.path.join(basedirData,f+".friend"))
                    rootFiles.append(l)
                    nFriends+=1
                else:
                    if requireFriends:
                        self._logger.error("friend of file '"+os.path.join(basedirData,f)+"' missing! -> skip")
                    else:
                        rootFiles.append(l)

        self._logger.debug("found data files "+str(len(rootFiles))+"/"+str(nFriends)+" in "+basedirData)
        return rootFiles
        
        
               
    def getEfficiencyFiles(self,channel):
        rootFiles = []
    
        basedirSignalMC = "/nfs/user/mkomm/SSX13/signalMC/"+channel+self.module("Files").getVersion()
        matchSignalMC = re.compile("^signalMC_veto[0-9]+.root$")
        
        for f in os.listdir(basedirSignalMC):
            if matchSignalMC.match(f) and f.find("veto")>=0:
                rootFiles.append([os.path.join(basedirSignalMC,f)])
                        
        self._logger.debug("found efficiency files "+str(len(rootFiles))+" in "+basedirSignalMC)
        return rootFiles
        
