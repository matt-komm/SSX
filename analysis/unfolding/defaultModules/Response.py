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
        
    def transformResponseToGlobalBinning(self,responseMatrix,channel):
        globalRecoBinning = self.module("Unfolding").getRecoBinning("comb")
        globalGenBinning = self.module("Unfolding").getGenBinning("comb")
        tranformedResponse = ROOT.TH2F(
            "tranformedResponse"+responseMatrix.GetName(),
            responseMatrix.GetTitle()+";"+responseMatrix.GetXaxis().GetTitle()+";"+responseMatrix.GetYaxis().GetTitle(),
            len(globalGenBinning)-1,
            globalGenBinning,
            len(globalRecoBinning)-1,
            globalRecoBinning
        )
        tranformedResponse.SetDirectory(0)
        recoBinMap  = self.module("Unfolding").buildGlobalRecoBinMap()
        genBinMap = self.module("Unfolding").buildGlobalRecoBinMap()
        for genBin in range(responseMatrix.GetNbinsX()):
            tranformedResponse.SetBinContent(
                genBinMap[channel][genBin]+1,
                0,
                responseMatrix.GetBinContent(genBin+1,0)
            )
            tranformedResponse.SetBinError(
                genBinMap[channel][genBin]+1,
                0,
                responseMatrix.GetBinError(genBin+1,0)
            )
            for recoBin in range(responseMatrix.GetNbinsY()):
                tranformedResponse.SetBinContent(
                    genBinMap[channel][genBin]+1,
                    recoBinMap[channel][recoBin]+1,
                    responseMatrix.GetBinContent(genBin+1,recoBin+1)+0.000000000001
                )
                tranformedResponse.SetBinError(
                    genBinMap[channel][genBin]+1,
                    recoBinMap[channel][recoBin]+1,
                    responseMatrix.GetBinError(genBin+1,recoBin+1)
                )
                
        return tranformedResponse
                
    
    def makeResponse(self,channel,genCharge,output):
        recoBinning = self.module("Unfolding").getRecoBinning(channel)
        self._logger.info("Reco binning: "+str(recoBinning))
        genBinning = self.module("Unfolding").getGenBinning(channel)
        self._logger.info("Gen binning: "+str(genBinning))
        
        recoVariable = self.module("Unfolding").getRecoVariable(channel)
        self._logger.info("Reco variable: "+recoVariable)
        genVariable = self.module("Unfolding").getGenVariable(channel)
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
            ";"+self.module("Unfolding").getGenVariable(channel)+";"+self.module("Unfolding").getRecoVariable(channel),
            len(genBinning)-1,
            genBinning,
            len(recoBinning)-1,
            recoBinning
        )
        efficiencyHist = ROOT.TH1F(
            "efficiency",
            ";"+self.module("Unfolding").getGenVariable(channel)+";",
            len(genBinning)-1,
            genBinning
        )
        efficiencyHistMatrix = ROOT.TH1F(
            "efficiencyMatrix",
            ";"+self.module("Unfolding").getGenVariable(channel)+";",
            len(genBinning)-1,
            genBinning
        )
        efficiencyHistVeto = ROOT.TH1F(
            "efficiencyVeto",
            ";"+self.module("Unfolding").getGenVariable(channel)+";",
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
                self.module("Utils").getHist1D(efficiencyHistMatrix,fileName,processName,genVariable,
                    genWeight+"*"+genSelection+"*"+recoWeight+"*(!("+recoSelection+"))"
                )
        self._logger.info("Projected selected events "+str(responseHist.Integral())+" in response matrix") 
        self._logger.info("Projected unselected events "+str(efficiencyHistMatrix.Integral())+" in efficiency hist")
        #force no sys samples !
        for processName in self.module("Samples").getSample("tChannel",channel,sys="")["processes"]:
             self._logger.info("Projecting events from '"+processName+"'")
             for fileName in self.module("Files").getEfficiencyFiles(channel):
                self.module("Utils").getHist1D(efficiencyHistVeto,fileName,processName,genVariable,
                    genWeight+"*"+genSelection+"*(1./veto_frac)"
                )
        self._logger.info("Projected unselected events from veto "+str(efficiencyHistVeto.Integral())+" in efficiency hist")
        efficiencyHist.Add(efficiencyHistMatrix)
        efficiencyHist.Add(efficiencyHistVeto)
        
        self._logger.info("Average selection efficiency: "+str(responseHist.Integral()/efficiencyHist.Integral()))

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
        
