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
        for charge in responseMatrices.keys():
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
            morphedHists[charge] = self.module("Utils").morphHist(nominalHists,sysHists,means,covariances)
            
        return morphedHists
        
        
    def buildCombinedConvarianceMatrix(self,recoBinning,measuredRecoHists,fitResult,binMapReco):
        combinedRecoBinning = numpy.linspace(0,2*len(recoBinning)-2,num=2*len(recoBinning)-1)
        combinedCovarianceMatrix = ROOT.TH2F("combinedCovarianceMatrix","",
            len(combinedRecoBinning)-1,combinedRecoBinning,
            len(combinedRecoBinning)-1,combinedRecoBinning
        )
        #covariance (need loop over reco binning here)
        for ibin in range(len(recoBinning)-1):
            for jbin in range(len(recoBinning)-1):
                signalFitResultCovPP = fitResult["covariances"]["values"]["tChannel_"+self.module("Samples").getChargeName(1)+"_bin"+str(1+binMapReco[ibin])]["tChannel_"+self.module("Samples").getChargeName(1)+"_bin"+str(1+binMapReco[jbin])]
                signalFitResultCovPN = fitResult["covariances"]["values"]["tChannel_"+self.module("Samples").getChargeName(1)+"_bin"+str(1+binMapReco[ibin])]["tChannel_"+self.module("Samples").getChargeName(-1)+"_bin"+str(1+binMapReco[jbin])]
                signalFitResultCovNP = fitResult["covariances"]["values"]["tChannel_"+self.module("Samples").getChargeName(-1)+"_bin"+str(1+binMapReco[ibin])]["tChannel_"+self.module("Samples").getChargeName(1)+"_bin"+str(1+binMapReco[jbin])]
                signalFitResultCovNN = fitResult["covariances"]["values"]["tChannel_"+self.module("Samples").getChargeName(-1)+"_bin"+str(1+binMapReco[ibin])]["tChannel_"+self.module("Samples").getChargeName(-1)+"_bin"+str(1+binMapReco[jbin])]
                combinedCovarianceMatrix.SetBinContent(
                    ibin+1,
                    jbin+1,
                    measuredRecoHists[1].GetBinContent(ibin+1)*measuredRecoHists[1].GetBinContent(jbin+1)*signalFitResultCovPP
                )
                combinedCovarianceMatrix.SetBinContent(
                    ibin+1+(len(recoBinning)-1),
                    jbin+1,
                    measuredRecoHists[1].GetBinContent(ibin+1)*measuredRecoHists[-1].GetBinContent(jbin+1)*signalFitResultCovPN
                )
                combinedCovarianceMatrix.SetBinContent(
                    ibin+1,
                    jbin+1+(len(recoBinning)-1),
                    measuredRecoHists[-1].GetBinContent(ibin+1)*measuredRecoHists[1].GetBinContent(jbin+1)*signalFitResultCovNP
                )
                combinedCovarianceMatrix.SetBinContent(
                    ibin+1+(len(recoBinning)-1),
                    jbin+1+(len(recoBinning)-1),
                    measuredRecoHists[-1].GetBinContent(ibin+1)*measuredRecoHists[-1].GetBinContent(jbin+1)*signalFitResultCovNN
                )
        return combinedCovarianceMatrix
        
    def buildCombinedResponseMatrix(self,genBinning,recoBinning,nominalRecoHists,measuredRecoHists,responseMatrices,nominalGenHists):
        combinedRecoBinning = numpy.linspace(0,2*len(recoBinning)-2,num=2*len(recoBinning)-1)
        combinedGenBinning = numpy.linspace(0,2*len(genBinning)-2,num=2*len(genBinning)-1)
        
        combinedNominalRecoHist = ROOT.TH1F("combinedNominalRecoHist","",len(combinedRecoBinning)-1,combinedRecoBinning)
        combinedNominalGenHist = ROOT.TH1F("combinedNominalGenHist","",len(combinedRecoBinning)-1,combinedRecoBinning)
        combinedMeasuredRecoHist = ROOT.TH1F("combinedMeasuredRecoHist","",len(combinedRecoBinning)-1,combinedRecoBinning)
        
        combinedResponseMatrix = ROOT.TH2F("combinedResponseMatrix","",
            len(combinedGenBinning)-1,combinedGenBinning,
            len(combinedRecoBinning)-1,combinedRecoBinning
        )
        for ibin in range(len(recoBinning)-1):
            #merge nominal hists
            combinedNominalRecoHist.SetBinContent(
                ibin+1,
                nominalRecoHists[1].GetBinContent(ibin+1)
            )
            combinedNominalRecoHist.SetBinContent(
                ibin+1+(len(genBinning)-1),
                nominalRecoHists[-1].GetBinContent(ibin+1)
            )
        
            #merge measured hists with errors
            combinedMeasuredRecoHist.SetBinContent(
                ibin+1,
                measuredRecoHists[1].GetBinContent(ibin+1)
            )
            combinedMeasuredRecoHist.SetBinContent(
                ibin+1+(len(genBinning)-1),
                measuredRecoHists[-1].GetBinContent(ibin+1)
            )
            combinedMeasuredRecoHist.SetBinError(
                ibin+1,
                measuredRecoHists[1].GetBinError(ibin+1)
            )
            combinedMeasuredRecoHist.SetBinError(
                ibin+1+(len(genBinning)-1),
                measuredRecoHists[-1].GetBinError(ibin+1)
            )
            
            #merge response matrices
            for jbin in range(len(genBinning)-1):
                #migration
                combinedResponseMatrix.SetBinContent(
                    jbin+1,
                    ibin+1,
                    responseMatrices[1].GetBinContent(jbin+1,ibin+1)
                )
                combinedResponseMatrix.SetBinContent(
                    jbin+1+(len(genBinning)-1),
                    ibin+1+(len(recoBinning)-1),
                    responseMatrices[-1].GetBinContent(jbin+1,ibin+1)
                )
                #efficiencies
                combinedResponseMatrix.SetBinContent(
                    jbin+1,
                    0,
                    responseMatrices[1].GetBinContent(jbin+1,0)
                )
                combinedResponseMatrix.SetBinContent(
                    jbin+1+(len(genBinning)-1),
                    0,
                    responseMatrices[-1].GetBinContent(jbin+1,0)
                )
            
            
        for ibin in range(len(genBinning)-1):
            #merge nominal hists
            combinedNominalGenHist.SetBinContent(
                ibin+1,
                nominalGenHists[1].GetBinContent(ibin+1)
            )
            combinedNominalGenHist.SetBinContent(
                ibin+1+(len(genBinning)-1),
                nominalGenHists[-1].GetBinContent(ibin+1)
            )
        return {
            "nominalReco":combinedNominalRecoHist,
            "measuredReco":combinedMeasuredRecoHist,
            "response":combinedResponseMatrix,
            "nominalGen":combinedNominalGenHist
        }
            
       
        
    def gatherResponse(self,unfoldingName,unfoldingLevel,channels,uncertainties=[]):
        responseMatrices = {}
        
    
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
                        responseMatrices[channel][0][uncertainty].Add(
                            responseMatrices[channel][charge][uncertainty]
                        )
                    rootResponseFile.Close()
        
        return responseMatrices
        
    #properly adding orthogonal response matrices by removing overlapping events in efficiency
    #TODO figure out how to do this correctly???
    def addResponseMatrices(self,h1,h2):
        result = h1.Clone(h1.GetName()+"sum")
        result.SetDirectory(0)
        result.Add(h2)
        for ibin in range(h1.GetNbinsX()):
            overlap = 0.
            for jbin in range(h1.GetNbinsY()):
                overlap+=h1.GetBinContent(ibin+1,jbin+1)
                overlap+=h2.GetBinContent(ibin+1,jbin+1)
            c = result.GetBinContent(ibin+1,0)
            #result.SetBinContent(ibin+1,0,c-overlap)
        return result
        
        
    def combineResponseMatrices(self,responseMatrices):
        combName = self.module("Samples").getChannelName(["ele","mu"])
        responseMatricesCombined = {}
        for channel in responseMatrices.keys():
            for charge in responseMatrices[channel].keys():
                if not responseMatricesCombined.has_key(charge):
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
        
    def getError(self,responseHist):
        w = responseHist.Integral()/responseHist.GetEntries()
        err = math.sqrt(responseHist.GetEntries())*w
        return err
                
    
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
        efficiencyHistUnweighted = ROOT.TH1F(
            "efficiencyUnweighted",
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
        
        self._logger.info("Projected gen/summed unweighted events "+str(xsecGenSelectionHist.Integral())+"/"+str(responseHistUnweighted.Integral()+efficiencyHistMatrixUnweighted.Integral())+" for response matrix (should be identical)") 
                
        #force no sys samples for veto files!
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
        efficiencyHistUnweighted.Add(efficiencyHistMatrixUnweighted)
        
        efficiencyHist.Add(efficiencyHistVeto)
        efficiencyHistUnweighted.Add(efficiencyHistVeto)
        
        #efficiency needs to be correct to account for the reco weight (e.g. lepton scale factors)
        # -> projection on y axis gives weighted reco distribution
        # -> projection on x axis gives unweighted gen distribution
        
        #R+e=R'+w*e' =>  w=(R+e-R')/e'
        for ibin in range(efficiencyHist.GetNbinsX()):
            denominator = efficiencyHist.GetBinContent(ibin+1)
            nominator = efficiencyHistUnweighted.GetBinContent(ibin+1)
            
            for jbin in range(responseHist.GetNbinsY()):
                nominator-=responseHist.GetBinContent(ibin+1,jbin+1)
                nominator+=responseHistUnweighted.GetBinContent(ibin+1,jbin+1)
            
            w = 1.*nominator/denominator
            self._logger.info("Bin "+str(ibin+1)+": apply reco reweighting of "+str(w))
            efficiencyHist.SetBinContent(ibin+1,w*efficiencyHist.GetBinContent(ibin+1))
            efficiencyHist.SetBinError(ibin+1,w*efficiencyHist.GetBinError(ibin+1))
        
        
        
        #self._logger.info("Average selection efficiency: "+str(responseHist.Integral()/efficiencyHist.Integral()))

        #put efficiencies in underflow
        for i in range(responseHist.GetNbinsX()):
            responseHist.SetBinContent(i+1,0,efficiencyHist.GetBinContent(i+1))
            responseHistUnweighted.SetBinContent(i+1,0,efficiencyHistUnweighted.GetBinContent(i+1))
                
        rootFile = ROOT.TFile(output,"RECREATE")
        responseHist.SetDirectory(rootFile)
        responseHist.Write()
        genHist = responseHist.ProjectionX("gen")
        genHistUnweighted = responseHistUnweighted.ProjectionX("genUnweighted")
        self._logger.info("Cross section in bin range: "+str(genHist.Integral()/self.module("Samples").getLumi())+"+-"+str(self.getError(genHist)/self.module("Samples").getLumi())+" pb")
        self._logger.info("Cross section in bin range (unweighted): "+str(genHistUnweighted.Integral()/self.module("Samples").getLumi())+" pb")
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
        
        
