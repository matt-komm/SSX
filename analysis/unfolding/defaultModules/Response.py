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
        genBinMap = self.module("Unfolding").buildGlobalGenBinMap()
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
        
    def morphResponses(self,responseMatrices,systematics,fitResult):
        morphedHists = {}
        for charge in morphedHists.keys():
            nominalHists = responseMatrices[charge]['nominal']
            sysHists = []
            means = []
            covariances = []
            for unc in systematics:
                sysHists.append([
                    responseMatrices[charge][unc+"Up"],
                    responseMatrices[charge][unc+"Down"],
                ])
                means.append(fitResult["parameters"][unc]["mean_fit"])
                covs = []
                for unc2 in systematics:
                    covs.append(fitResult["covariances"]["values"][unc][unc2])
                covariances.append(covs)
            #NOTE: not 100% correct - ignoring here correlations between charged bins in shape
            #correlation in yields from the fit result is accounted for later
            morphedHists[charge] = self.module("Utils").morphHist(nominalHists[charge],sysHists[charge],means,covariances)
    
        
       
        
    def gatherResponse(self,unfoldingName,unfoldingLevel,channels,systematics=[]):
        responseMatrices = {}
        uncertainties = []
        for unc in systematics:
            uncertainties.append(unc+"Up")
            uncertainties.append(unc+"Down")
    
        for channel in channels:
            responseMatrices[channel] = {1:{},-1:{},0:{}}
            for uncertainty in ["nominal"]+uncertainties:
                responseMatrices[channel][0][uncertainty]=None
                for charge in [-1,1]:
                    responseFileName = self.module("Response").getOutputResponseFile(channel,unfoldingName,unfoldingLevel,uncertainty,charge)
                    rootResponseFile = ROOT.TFile(responseFileName)
                    if not rootResponseFile:
                        self._logger.critical("Cannot find response file '"+responseFileName+"'")
                        sys.exit(1)
                    responseMatrix = rootResponseFile.Get("response")
                    if not responseMatrix:
                        self._logger.critical("Cannot find response matrix 'response' in file '"+responseFileName+"'")
                        sys.exit(1)
                    #responseMatrix = self.module("Response").transformResponseToGlobalBinning(responseMatrix,channel)
                    responseMatrices[channel][charge][uncertainty] = responseMatrix.Clone("response"+str(charge)+channel+uncertainty+str(random.random()))
                    responseMatrices[channel][charge][uncertainty].SetDirectory(0)
                    if responseMatrices[channel][0][uncertainty]==None:
                        responseMatrices[channel][0][uncertainty]=responseMatrices[channel][charge][uncertainty].Clone(responseMatrices[channel][charge][uncertainty].GetName()+"sum")
                        responseMatrices[channel][0][uncertainty].SetDirectory(0)
                    else:
                        responseMatrices[channel][0][uncertainty].Add(responseMatrices[channel][charge][uncertainty])
                    rootResponseFile.Close()
        
        return responseMatrices
        
    def combineResponseMatrices(self,responseMatrices):
        combName = self.module("Samples").getChannelName(["ele","mu"])
        responseMatricesCombined = {}
        for channel in responseMatrices.keys():
            for charge in responseMatrices[channel].keys():
                responseMatricesCombined[charge] = {}
                for unc in responseMatrices[channel][charge].keys():
                    h = responseMatrices[channel][charge][unc]
                    h = h.Clone(h.GetName()+"_comb")
                    h.SetDirectory(0)
                    h = self.module("Response").transformResponseToGlobalBinning(
                        h,
                        channel
                    )
                    if not responseMatricesCombined[charge].has_key(unc):
                        responseMatricesCombined[charge][unc] = h
                    else:
                        responseMatricesCombined[charge][unc].Add(h)
        responseMatrices[combName]=responseMatricesCombined
        return responseMatrices
                    
                
    
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
        
        #events in reco selection
        responseHist = ROOT.TH2F(
            "response",
            ";"+self.module("Unfolding").getGenVariable(channel)+";"+self.module("Unfolding").getRecoVariable(channel),
            len(genBinning)-1,
            genBinning,
            len(recoBinning)-1,
            recoBinning
        )
        #events fail reco selection
        efficiencyHistMatrix = ROOT.TH1F(
            "efficiencyMatrix",
            ";"+self.module("Unfolding").getGenVariable(channel)+";",
            len(genBinning)-1,
            genBinning
        )
        #events in reco selection w/o reco weight
        responseHistUnweighted = ROOT.TH2F(
            "responseUnweighted",
            ";"+self.module("Unfolding").getGenVariable(channel)+";"+self.module("Unfolding").getRecoVariable(channel),
            len(genBinning)-1,
            genBinning,
            len(recoBinning)-1,
            recoBinning
        )
        #events fail reco selection w/o reco weight
        efficiencyHistMatrixUnweighted = ROOT.TH1F(
            "efficiencyMatrixUnweighted",
            ";"+self.module("Unfolding").getGenVariable(channel)+";",
            len(genBinning)-1,
            genBinning
        )
        #events not selected (veto branch)
        efficiencyHistVeto = ROOT.TH1F(
            "efficiencyVeto",
            ";"+self.module("Unfolding").getGenVariable(channel)+";",
            len(genBinning)-1,
            genBinning
        )
        
        #final efficiency (sum of efficiencyHistMatrix and efficiencyHistVeto)
        #and corrected by the reco weight
        efficiencyHist = ROOT.TH1F(
            "efficiency",
            ";"+self.module("Unfolding").getGenVariable(channel)+";",
            len(genBinning)-1,
            genBinning
        )
        #to cross check the cross section
        xsecHist = ROOT.TH1F(
            "xsec",
            ";xsec;",
            1,
            numpy.array([-100.,100.])
        )
        xsecGenSelectionHist = ROOT.TH1F(
            "xsecGenSelection",
            ";xsec;",
            1,
            numpy.array([-100.,100.])
        )
        xsecGenSelectionNoTauHist = ROOT.TH1F(
            "xsecGenSelectionNoTau",
            ";xsec;",
            1,
            numpy.array([-100.,100.])
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
                
                self.module("Utils").getHist2D(responseHistUnweighted,fileName,processName,genVariable,recoVariable,
                    genWeight+"*"+genSelection+"*"+recoSelection
                )
                self.module("Utils").getHist1D(efficiencyHistMatrixUnweighted,fileName,processName,genVariable,
                    genWeight+"*"+genSelection+"*(!("+recoSelection+"))"
                )
                        
                self.module("Utils").getHist1D(xsecHist,fileName,processName,"0",
                    genWeight
                )   
                self.module("Utils").getHist1D(xsecGenSelectionHist,fileName,processName,"0",
                    genWeight+"*"+genSelection
                )
                self.module("Utils").getHist1D(xsecGenSelectionNoTauHist,fileName,processName,"0",
                    genWeight+"*"+genSelection+"*(Parton_1__Lepton_1__fromTau==0)"
                ) 
                     
                        
        self._logger.info("Projected selected events "+str(responseHist.Integral())+" in response matrix") 
        self._logger.info("Projected unselected events "+str(efficiencyHistMatrix.Integral())+" in efficiency hist")
        self._logger.info("Projected selected events (w/o reco weight) "+str(responseHistUnweighted.Integral())+" in response matrix") 
        self._logger.info("Projected unselected events (w/o reco weight) "+str(efficiencyHistMatrixUnweighted.Integral())+" in efficiency hist")
        #force no sys samples !
        for processName in self.module("Samples").getSample("tChannel",channel,sys="")["processes"]:
             self._logger.info("Projecting events from '"+processName+"'")
             for fileName in self.module("Files").getEfficiencyFiles(channel):
                self.module("Utils").getHist1D(efficiencyHistVeto,fileName,processName,genVariable,
                    genWeight+"*"+genSelection+"*(1./veto_frac)"
                )
                self.module("Utils").getHist1D(xsecHist,fileName,processName,"0",
                    genWeight+"*(1./veto_frac)"
                )    
                self.module("Utils").getHist1D(xsecGenSelectionHist,fileName,processName,"0",
                    genWeight+"*"+genSelection+"*(1./veto_frac)"
                )  
                self.module("Utils").getHist1D(xsecGenSelectionNoTauHist,fileName,processName,"0",
                    genWeight+"*"+genSelection+"*(Parton_1__Lepton_1__fromTau==0)"+"*(1./veto_frac)"
                ) 
        self._logger.info("Projected unselected events from veto "+str(efficiencyHistVeto.Integral())+" in efficiency hist")
        
        efficiencyHist.Add(efficiencyHistMatrix)
        
        #efficiency needs to be correct to account for the reco weight (e.g. lepton scale factors)
        # -> projection on y axis gives weighted reco distribution
        # -> projection on x axis gives unweighted gen distribution
        for ibin in range(efficiencyHist.GetNbinsX()):
            sumWeighted = efficiencyHistMatrix.GetBinContent(ibin+1)
            sumUnweighted = efficiencyHistMatrixUnweighted.GetBinContent(ibin+1)
            for jbin in range(responseHist.GetNbinsY()):
                sumWeighted+=responseHist.GetBinContent(ibin+1,jbin+1)
                sumUnweighted+=responseHistUnweighted.GetBinContent(ibin+1,jbin+1)
            scale = 1.*sumUnweighted/sumWeighted
            self._logger.info("Bin "+str(ibin+1)+": apply reco reweighting of "+str(scale))
            efficiencyHist.SetBinContent(ibin+1,scale*efficiencyHist.GetBinContent(ibin+1))
            efficiencyHist.SetBinError(ibin+1,scale*efficiencyHist.GetBinError(ibin+1))
        
        efficiencyHist.Add(efficiencyHistVeto)
        
        self._logger.info("Average selection efficiency: "+str(responseHist.Integral()/efficiencyHist.Integral()))

        #put efficiencies in underflow
        for i in range(responseHist.GetNbinsX()):
            responseHist.SetBinContent(i+1,0,efficiencyHist.GetBinContent(i+1))
                
        rootFile = ROOT.TFile(output,"RECREATE")
        responseHist.SetDirectory(rootFile)
        responseHist.Write()
        genHist = responseHist.ProjectionX("gen")
        self._logger.info("Cross section in bin range: "+str(genHist.Integral()/self.module("Samples").getLumi())+" pb")
        self._logger.info("Cross section after gen selection: "+str(xsecGenSelectionHist.Integral()/self.module("Samples").getLumi())+" pb")
        self._logger.info("Cross section after gen selection (no tau): "+str(xsecGenSelectionNoTauHist.Integral()/self.module("Samples").getLumi())+" pb")
        self._logger.info("Total cross section: "+str(xsecHist.Integral()/self.module("Samples").getLumi())+" pb")
        if math.fabs(xsecHist.Integral()/self.module("Samples").getLumi()-217.0)>1.:
            self._logger.warning("Inclusive cross section not 217 pb. Check normalization of sample!")
        genHist.SetDirectory(rootFile)
        genHist.Write()
        recoHist = responseHist.ProjectionY("reco")
        recoHist.SetDirectory(rootFile)
        recoHist.Write()
        efficiencyHist.SetDirectory(rootFile)
        efficiencyHist.Write()
        
        
