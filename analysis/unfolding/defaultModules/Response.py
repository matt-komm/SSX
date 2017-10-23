import ROOT
#import pyTool
import numpy
import math
import os
import os.path
import re
import random
import sys

from Module import Module

import logging

class Response(Module):
    def __init__(self,options=[]):
        Module.__init__(self,options)
        self._logger = logging.getLogger(__file__)
        self._logger.setLevel(logging.DEBUG)
        
        
    def getOutputFolder(self,channel,unfoldingName,uncertaintyName):
        return self.module("ThetaModel").getHistogramPath(
            channel,
            unfoldingName,
            uncertaintyName
        )

    def getOutputResponseFile(self,channel,unfoldingName,unfoldingLevel,uncertaintyName,genCharge):
        return os.path.join(
            self.module("Response").getOutputFolder(channel,unfoldingName,uncertaintyName),
            "response_"+unfoldingLevel+"_"+self.module("Samples").getChargeName(genCharge)+".root"
        )
        
    
    def makeResponse(self,channel,genCharge,output):
        recoBinning = self.module("Unfolding").getRecoBinning()
        self._logger.info("Reco binning: "+str(recoBinning))
        genBinning = self.module("Unfolding").getGenBinning()
        self._logger.info("Gen binning: "+str(genBinning))
        
        recoVariable = self.module("Unfolding").getRecoVariable()
        self._logger.info("Reco variable: "+recoVariable)
        genVariable = self.module("Unfolding").getGenVariable()
        self._logger.info("Gen variable: "+genVariable)
        
        recoSelection = self.module("Unfolding").getRecoCut(channel)
        self._logger.info("Reco selection: "+recoSelection)
        genSelection = self.module("Unfolding").getGenCut(channel)+"*"+self.module("Samples").getGenChargeSelection(genCharge)
        self._logger.info("Gen selection: "+genSelection)
        
        recoWeight = self.module("Unfolding").getRecoWeight(channel)
        self._logger.info("Reco weight: "+recoWeight)
        genWeight = self.module("Unfolding").getGenWeight(channel)
        self._logger.info("Gen weight: "+genWeight)
        
        
        responseHist = ROOT.TH2F(
            "response",
            ";"+self.module("Unfolding").getGenVariable()+";"+self.module("Unfolding").getRecoVariable(),
            len(genBinning)-1,
            genBinning,
            len(recoBinning)-1,
            recoBinning
        )
        efficiencyHist = ROOT.TH1F(
            "efficiency",
            ";"+self.module("Unfolding").getGenVariable()+";",
            len(genBinning)-1,
            genBinning
        )
        #will automatically get the sys varied samples names
        for processName in self.module("Samples").getSample("tChannel",channel)["processes"]:
            self._logger.info("Projecting events from '"+processName+"'")
            for fileName in self.module("Samples").getProcessFiles(processName,channel):
                self.module("Utils").getHist2D(responseHist,fileName,processName,genVariable,recoVariable,
                    genWeight+"*"+genSelection+"*"+recoWeight+"*"+recoSelection
                )
                self.module("Utils").getHist1D(efficiencyHist,fileName,processName,genVariable,
                    genWeight+"*"+genSelection+"*(!("+recoSelection+"))*"+recoWeight
                )
        self._logger.info("Projected selected events "+str(responseHist.Integral())+" in response matrix") 
        self._logger.info("Projected unselected events "+str(efficiencyHist.Integral())+" in efficiency hist")
        #force no sys samples !
        for processName in self.module("Samples").getSample("tChannel",channel,sys="")["processes"]:
             self._logger.info("Projecting events from '"+processName+"'")
             for fileName in self.module("Files").getEfficiencyFiles(channel):
                self.module("Utils").getHist1D(efficiencyHist,fileName,processName,genVariable,
                    genWeight+"*"+genSelection+"*(1./veto_frac)"
                )
        self._logger.info("Projected unselected events from veto "+str(efficiencyHist.Integral())+" in efficiency hist")
        #put efficiencies in underflow
        for i in range(responseHist.GetNbinsX()):
            responseHist.SetBinContent(i+1,0,efficiencyHist.GetBinContent(i+1))
                
        rootFile = ROOT.TFile(output,"RECREATE")
        responseHist.SetDirectory(rootFile)
        responseHist.Write()
        genHist = responseHist.ProjectionX("gen")
        genHist.SetDirectory(rootFile)
        genHist.Write()
        recoHist = responseHist.ProjectionY("reco")
        recoHist.SetDirectory(rootFile)
        recoHist.Write()
        efficiencyHist.SetDirectory(rootFile)
        efficiencyHist.Write()
        
