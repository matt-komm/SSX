from defaultModules.Module import Module

import logging
import ROOT
import copy
import os
import sys
import random
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
        unfoldingLevel = self.module("Unfolding").getUnfoldingLevel()
            
        self.module("Utils").createFolder("unfolding/"+unfoldingName+"/"+unfoldingLevel)


        fitOutput = os.path.join(
            self.module("Utils").getOutputFolder("fit"),
            self.module("ThetaModel").getFitFileName(channels,unfoldingName)
        )
        fitResult = self.module("ThetaFit").loadFitResult(fitOutput+".json")
        
        #print fitResult["parameters"]["tChannel_neg_bin0"]
        #print fitResult["parameters"]["tChannel_pos_bin0"]
        #print fitResult["covariances"]["values"]["tChannel_pos_bin0"]["tChannel_neg_bin0"]
        
        
        #for profiled syst use nominal hist atm - later take envelop of all profiled response matrices
        responseMatrices = {1:None,-1:None}
        for charge in responseMatrices.keys():
            for channel in channels:
                responseFileName = self.module("Response").getOutputResponseFile(channel,unfoldingName,unfoldingLevel,"nominal",charge)
                rootResponseFile = ROOT.TFile(responseFileName)
                if not rootResponseFile:
                    self._logger.critical("Cannot find response file '"+responseFileName+"'")
                    sys.exit(1)
                responseMatrix = rootResponseFile.Get("response")
                if not responseMatrix:
                    self._logger.critical("Cannot find response matrix 'response' in file '"+responseFileName+"'")
                    sys.exit(1)
                if responseMatrices[charge]==None:
                    responseMatrices[charge] = responseMatrix.Clone("response"+str(charge)+channel+str(random.random()))
                    responseMatrices[charge].SetDirectory(0)
                else:
                    responseMatrices[charge].Add(responseMatrix)
                rootResponseFile.Close()
            
        nominalRecoHists = {}
        nominalGenHists = {}
        measuredRecoHists = {}
        measuredRecoCovariances = {}
        unfoldedHists = {}
        recoBinning = self.module("Unfolding").getRecoBinning()
        genBinning = self.module("Unfolding").getGenBinning()
        for charge in responseMatrices.keys():
            nominalRecoHists[charge] = responseMatrices[charge].ProjectionY()
            nominalGenHists[charge] = responseMatrices[charge].ProjectionX()
            measuredRecoHists[charge] = nominalRecoHists[charge].Clone(nominalRecoHists[charge].GetName()+"meas")
            measuredRecoCovariances[charge] = ROOT.TH2F(
                "covariance"+str(charge),"",
                len(recoBinning)-1,recoBinning,
                len(recoBinning)-1,recoBinning
            )
            #scale to fit result
            for ibin in range(len(recoBinning)-1):
                signalFitResult = fitResult["parameters"]["tChannel_"+self.module("Samples").getChargeName(charge)+"_bin"+str(ibin)]
                measuredRecoHists[charge].SetBinContent(ibin+1,nominalRecoHists[charge].GetBinContent(ibin+1)*signalFitResult["mean_fit"])
                measuredRecoHists[charge].SetBinError(ibin+1,nominalRecoHists[charge].GetBinContent(ibin+1)*signalFitResult["unc_fit"])
                for jbin in range(len(recoBinning)-1):
                    signalFitResultCov = fitResult["covariances"]["values"]["tChannel_"+self.module("Samples").getChargeName(charge)+"_bin"+str(ibin)]["tChannel_"+self.module("Samples").getChargeName(charge)+"_bin"+str(jbin)]
                    measuredRecoCovariances[charge].SetBinContent(ibin+1,jbin+1,nominalRecoHists[charge].GetBinContent(ibin+1)*nominalRecoHists[charge].GetBinContent(jbin+1)*signalFitResultCov)
                    #sanity check
                    if ibin==jbin and math.fabs(measuredRecoHists[charge].GetBinError(ibin+1)**2-measuredRecoCovariances[charge].GetBinContent(ibin+1,jbin+1))/measuredRecoCovariances[charge].GetBinContent(ibin+1,jbin+1)>0.0001:
                        self._logger.critical("Diagonal elements of covariance matrix do not align with histogram errors")
                        sys.exit(1)
            #draw reco hists
            self.module("Drawing").plotDataHistogram(nominalRecoHists[charge],measuredRecoHists[charge],"reconstructed "+self.module("Unfolding").getUnfoldingVariableName(),
                os.path.join(self.module("Utils").getOutputFolder("unfolding/"+unfoldingName+"/"+unfoldingLevel),self.module("Samples").getChannelName(channels)+"_"+self.module("Samples").getChargeName(charge)+"_recoHist")
            )
            #draw input covariance,correlation
            self.module("Drawing").drawHistogramMatrix(
                measuredRecoCovariances[charge], 
                os.path.join(self.module("Utils").getOutputFolder("unfolding/"+unfoldingName+"/"+unfoldingLevel),self.module("Samples").getChannelName(channels)+"_"+self.module("Samples").getChargeName(charge)+"_recoCovariance"), 
                xaxis="reconstructed "+self.module("Unfolding").getUnfoldingVariableName(),
                yaxis="reconstructed "+self.module("Unfolding").getUnfoldingVariableName(),
                zaxis="covariance"
            )
            measuredRecoCorrelations = self.module("Utils").calculateCorrelations(measuredRecoCovariances[charge])
            self.module("Drawing").drawHistogramMatrix(
                measuredRecoCorrelations, 
                os.path.join(self.module("Utils").getOutputFolder("unfolding/"+unfoldingName+"/"+unfoldingLevel),self.module("Samples").getChannelName(channels)+"_"+self.module("Samples").getChargeName(charge)+"_recoCorrelation"), 
                xaxis="reconstructed "+self.module("Unfolding").getUnfoldingVariableName(),
                yaxis="reconstructed "+self.module("Unfolding").getUnfoldingVariableName(),
                zaxis="correlation"
            )
            #unfolding
            unfoldedHist,unfoldedCovariance,bestTau = self.module("Unfolding").unfold(
                responseMatrices[charge],
                measuredRecoHists[charge],
                self.module("Unfolding").getGenBinning(),
                dataCovariance=measuredRecoCovariances[charge],
                scanOutput=os.path.join(self.module("Utils").getOutputFolder("unfolding/"+unfoldingName+"/"+unfoldingLevel),self.module("Samples").getChannelName(channels)+"_"+self.module("Samples").getChargeName(charge)+"_tauScan"),
                fixedTau=None
            )
            #draw unfolded hists
            self.module("Drawing").plotDataHistogram(nominalGenHists[charge],unfoldedHist,"unfolded "+self.module("Unfolding").getUnfoldingVariableName(),
                os.path.join(self.module("Utils").getOutputFolder("unfolding/"+unfoldingName+"/"+unfoldingLevel),self.module("Samples").getChannelName(channels)+"_"+self.module("Samples").getChargeName(charge)+"_unfoldedHist")
            )
            #draw unfolded covariance/correlation
            self.module("Drawing").drawHistogramMatrix(
                unfoldedCovariance, 
                os.path.join(self.module("Utils").getOutputFolder("unfolding/"+unfoldingName+"/"+unfoldingLevel),self.module("Samples").getChannelName(channels)+"_"+self.module("Samples").getChargeName(charge)+"_unfoldedCovariance"), 
                xaxis="unfolded "+self.module("Unfolding").getUnfoldingVariableName(),
                yaxis="unfolded "+self.module("Unfolding").getUnfoldingVariableName(),
                zaxis="covariance"
            )
            unfoldedCorrelation = self.module("Utils").calculateCorrelations(unfoldedCovariance)
            self.module("Drawing").drawHistogramMatrix(
                unfoldedCorrelation, 
                os.path.join(self.module("Utils").getOutputFolder("unfolding/"+unfoldingName+"/"+unfoldingLevel),self.module("Samples").getChannelName(channels)+"_"+self.module("Samples").getChargeName(charge)+"_unfoldedCorrelation"), 
                xaxis="unfolded "+self.module("Unfolding").getUnfoldingVariableName(),
                yaxis="unfolded "+self.module("Unfolding").getUnfoldingVariableName(),
                zaxis="correlation"
            )
