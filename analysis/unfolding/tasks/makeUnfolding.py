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
        systematics =self.getOption("systematics").split(",")
        channelName = self.module("Samples").getChannelName(channels)
        #inc,pt,y,cos
        unfoldingName = self.module("Unfolding").getUnfoldingName()
        if unfoldingName=="inc":
            self._logger.critical("Cannot unfolding inclusive xsec")
            sys.exit(1)
        unfoldingLevel = self.module("Unfolding").getUnfoldingLevel()
        
        
        self.module("Utils").createFolder("unfolding/"+unfoldingName+"/"+unfoldingLevel)


        
        #for profiled syst use nominal hist atm - later take envelop of all profiled response matrices
        responseMatricesPerChannel = self.module("Response").gatherResponse(
            unfoldingName,
            unfoldingLevel,
            channels,
            systematics=systematics
        )
        
        if len(channels)==2:
            responseMatricesPerChannel = self.module("Response").combineResponseMatrices(
                responseMatricesPerChannel
            )
        
        #use either per channel or their combination - no need to keep the rest
        responseMatrices = responseMatricesPerChannel[channelName]
        
        
        
        fitOutput = os.path.join(
            self.module("Utils").getOutputFolder("fit"),
            self.module("ThetaModel").getFitFileName(channels,unfoldingName)
        )
        fitResult = self.module("ThetaFit").loadFitResult(fitOutput+".json")
        
        responseMatricesMorphed = self.module("Response").morphResponses(
            responseMatrices,
            systematics,
            fitResult
        )

        

        self.module("Drawing").drawHistogramResponseAndEfficiency(
            responseMatrices[0]["nominal"],
            os.path.join(self.module("Utils").getOutputFolder("unfolding/"+unfoldingName+"/"+unfoldingLevel),self.module("Samples").getChannelName(channels)+"_response"), 
            xaxis=unfoldingLevel+" level "+self.module("Unfolding").getUnfoldingVariableName(),
            yaxis="reco. "+self.module("Unfolding").getUnfoldingVariableName(),
            title=self.module("Samples").getPlotTitle(channels)+"#kern[-0.5]{ }+#kern[-0.5]{ }jets"
        )
        
        self.module("Drawing").drawStabilityPurity(
            responseMatrices[0]["nominal"],
            os.path.join(self.module("Utils").getOutputFolder("unfolding/"+unfoldingName+"/"+unfoldingLevel),self.module("Samples").getChannelName(channels)+"_pstest"), 
            title=self.module("Samples").getPlotTitle(channels)+"#kern[-0.5]{ }+#kern[-0.5]{ }jets",
            xaxis=unfoldingLevel+" level "+self.module("Unfolding").getUnfoldingVariableName()
        )

        '''
        nominalRecoHists = {}
        nominalGenHists = {}
        measuredRecoHists = {}
        measuredRecoCovariances = {}
        unfoldedHists = {}
        recoBinning = self.module("Unfolding").getRecoBinning(channelName)
        genBinning = self.module("Unfolding").getGenBinning(channelName)
        binMapReco = self.module("Unfolding").buildGlobalRecoBinMap()[channelName]
        binMapGen = self.module("Unfolding").buildGlobalGenBinMap()[channelName]

        for charge in [-1,1]:
            nominalRecoHists[charge] = responseMatrices[charge].ProjectionY()
            #TODO: this is wrong since responseMatrices contains the morphed ones!!!
            nominalGenHists[charge] = responseMatrices[charge].ProjectionX() 
            unfoldedHists[charge] = nominalGenHists[charge].Clone(nominalGenHists[charge].GetName()+"meas")
            measuredRecoHists[charge] = nominalRecoHists[charge].Clone(nominalRecoHists[charge].GetName()+"meas")
            measuredRecoCovariances[charge] = ROOT.TH2F(
                "covariance"+str(charge),"",
                len(recoBinning)-1,recoBinning,
                len(recoBinning)-1,recoBinning
            )
            #scale to fit result
            for ibin in range(len(recoBinning)-1):
                signalFitResult = fitResult["parameters"]["tChannel_"+self.module("Samples").getChargeName(charge)+"_bin"+str(1+binMapReco[ibin])]
                measuredRecoHists[charge].SetBinContent(
                    ibin+1,
                    nominalRecoHists[charge].GetBinContent(ibin+1)*signalFitResult["mean_fit"]
                )
                measuredRecoHists[charge].SetBinError(
                    ibin+1,
                    math.sqrt(
                        (nominalRecoHists[charge].GetBinContent(ibin+1)*signalFitResult["unc_fit"])**2 + \
                        measuredRecoHists[charge].GetBinError(ibin+1)**2
                    )
                )
                
                for jbin in range(len(recoBinning)-1):
                    signalFitResultCov = \
                        fitResult["covariances"]["values"]["tChannel_"+self.module("Samples").getChargeName(charge)+"_bin"+str(1+binMapReco[ibin])]["tChannel_"+self.module("Samples").getChargeName(charge)+"_bin"+str(1+binMapReco[jbin])]
                    measuredRecoCovariances[charge].SetBinContent(
                        ibin+1,
                        jbin+1,
                        nominalRecoHists[charge].GetBinContent(ibin+1)*nominalRecoHists[charge].GetBinContent(jbin+1)*signalFitResultCov
                    )
                    
            #draw reco hists
            self.module("Drawing").plotDataHistogram(nominalRecoHists[charge],measuredRecoHists[charge],
                os.path.join(self.module("Utils").getOutputFolder("unfolding/"+unfoldingName+"/"+unfoldingLevel),self.module("Samples").getChannelName(channels)+"_"+self.module("Samples").getChargeName(charge)+"_recoHist"),
                xaxis="reconstructed "+self.module("Unfolding").getUnfoldingVariableName(),
                title=self.module("Samples").getPlotTitle(channels,charge)+"#kern[-0.5]{ }+#kern[-0.5]{ }jets"
            )
        
            #draw input covariance,correlation
            self.module("Drawing").drawHistogramMatrix(
                measuredRecoCovariances[charge], 
                os.path.join(self.module("Utils").getOutputFolder("unfolding/"+unfoldingName+"/"+unfoldingLevel),self.module("Samples").getChannelName(channels)+"_"+self.module("Samples").getChargeName(charge)+"_recoCovariance"), 
                xaxis="reconstructed "+self.module("Unfolding").getUnfoldingVariableName(),
                yaxis="reconstructed "+self.module("Unfolding").getUnfoldingVariableName(),
                zaxis="covariance",
                title=self.module("Samples").getPlotTitle(channels,charge)+"#kern[-0.5]{ }+#kern[-0.5]{ }jets"
            )
            measuredRecoCorrelations = self.module("Utils").calculateCorrelations(measuredRecoCovariances[charge])
            self.module("Drawing").drawHistogramMatrix(
                measuredRecoCorrelations, 
                os.path.join(self.module("Utils").getOutputFolder("unfolding/"+unfoldingName+"/"+unfoldingLevel),self.module("Samples").getChannelName(channels)+"_"+self.module("Samples").getChargeName(charge)+"_recoCorrelation"), 
                xaxis="reconstructed "+self.module("Unfolding").getUnfoldingVariableName(),
                yaxis="reconstructed "+self.module("Unfolding").getUnfoldingVariableName(),
                zaxis="correlation",
                title=self.module("Samples").getPlotTitle(channels,charge)+"#kern[-0.5]{ }+#kern[-0.5]{ }jets"
            )
        
        combinedRecoBinning = numpy.linspace(0,2*len(genBinning)-2,num=2*len(recoBinning)-1)
        combinedGenBinning = numpy.linspace(0,2*len(genBinning)-2,num=2*len(genBinning)-1)
        
        combinedNominalRecoHist = ROOT.TH1F("combinedNominalRecoHist","",len(combinedRecoBinning)-1,combinedRecoBinning)
        combinedNominalGenHist = ROOT.TH1F("combinedNominalRecoHist","",len(combinedRecoBinning)-1,combinedRecoBinning)
        combinedMeasuredRecoHist = ROOT.TH1F("combinedMeasuredRecoHist","",len(combinedRecoBinning)-1,combinedRecoBinning)
        combinedCovarianceMatrix = ROOT.TH2F("combinedResponseMatrix","",
            len(combinedRecoBinning)-1,combinedRecoBinning,
            len(combinedRecoBinning)-1,combinedRecoBinning
        )
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
            
            #covariance (need loop over reco binning here)
            for jbin in range(len(recoBinning)-1):
                signalFitResultCovPP = fitResult["covariances"]["values"]["tChannel_"+self.module("Samples").getChargeName(1)+"_bin"+str(1+binMapReco[ibin])]["tChannel_"+self.module("Samples").getChargeName(1)+"_bin"+str(1+binMapReco[jbin])]
                signalFitResultCovPN = fitResult["covariances"]["values"]["tChannel_"+self.module("Samples").getChargeName(1)+"_bin"+str(1+binMapReco[ibin])]["tChannel_"+self.module("Samples").getChargeName(-1)+"_bin"+str(1+binMapReco[jbin])]
                signalFitResultCovNP = fitResult["covariances"]["values"]["tChannel_"+self.module("Samples").getChargeName(-1)+"_bin"+str(1+binMapReco[ibin])]["tChannel_"+self.module("Samples").getChargeName(1)+"_bin"+str(1+binMapReco[jbin])]
                signalFitResultCovNN = fitResult["covariances"]["values"]["tChannel_"+self.module("Samples").getChargeName(-1)+"_bin"+str(1+binMapReco[ibin])]["tChannel_"+self.module("Samples").getChargeName(-1)+"_bin"+str(1+binMapReco[jbin])]
                combinedCovarianceMatrix.SetBinContent(
                    ibin+1,
                    jbin+1,
                    nominalRecoHists[1].GetBinContent(ibin+1)*nominalRecoHists[1].GetBinContent(jbin+1)*signalFitResultCovPP
                )
                combinedCovarianceMatrix.SetBinContent(
                    ibin+1+(len(recoBinning)-1),
                    jbin+1,
                    nominalRecoHists[1].GetBinContent(ibin+1)*nominalRecoHists[-1].GetBinContent(jbin+1)*signalFitResultCovPN
                )
                combinedCovarianceMatrix.SetBinContent(
                    ibin+1,
                    jbin+1+(len(recoBinning)-1),
                    nominalRecoHists[-1].GetBinContent(ibin+1)*nominalRecoHists[1].GetBinContent(jbin+1)*signalFitResultCovNP
                )
                combinedCovarianceMatrix.SetBinContent(
                    ibin+1+(len(recoBinning)-1),
                    jbin+1+(len(recoBinning)-1),
                    nominalRecoHists[-1].GetBinContent(ibin+1)*nominalRecoHists[-1].GetBinContent(jbin+1)*signalFitResultCovNN
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
                    
            
        self.module("Drawing").plotDataHistogram(combinedNominalRecoHist,combinedMeasuredRecoHist,
            os.path.join(self.module("Utils").getOutputFolder("unfolding/"+unfoldingName+"/"+unfoldingLevel),self.module("Samples").getChannelName(channels)+"_comb_recoHist"),
            xaxis="reconstructed "+self.module("Unfolding").getUnfoldingVariableName(),
        )
        self.module("Drawing").drawHistogramMatrix(
            self.module("Utils").normalizeByTransistionProbability(combinedResponseMatrix), 
            os.path.join(self.module("Utils").getOutputFolder("unfolding/"+unfoldingName+"/"+unfoldingLevel),self.module("Samples").getChannelName(channels)+"_comb_response"), 
            xaxis=unfoldingLevel+" "+self.module("Unfolding").getUnfoldingVariableName(),
            yaxis="reconstructed "+self.module("Unfolding").getUnfoldingVariableName(),
            zaxis="transition",
            title=self.module("Samples").getPlotTitle(channels)+"#kern[-0.5]{ }+#kern[-0.5]{ }jets"
        )
        self.module("Drawing").drawHistogramMatrix(
            combinedCovarianceMatrix, 
            os.path.join(self.module("Utils").getOutputFolder("unfolding/"+unfoldingName+"/"+unfoldingLevel),self.module("Samples").getChannelName(channels)+"_comb_recoCovariance"), 
            xaxis="reconstructed "+self.module("Unfolding").getUnfoldingVariableName(),
            yaxis="reconstructed "+self.module("Unfolding").getUnfoldingVariableName(),
            zaxis="covariance",
            title=self.module("Samples").getPlotTitle(channels)+"#kern[-0.5]{ }+#kern[-0.5]{ }jets"
        )
        self.module("Drawing").drawHistogramMatrix(
            self.module("Utils").calculateCorrelations(combinedCovarianceMatrix), 
            os.path.join(self.module("Utils").getOutputFolder("unfolding/"+unfoldingName+"/"+unfoldingLevel),self.module("Samples").getChannelName(channels)+"_comb_recoCorrelation"), 
            xaxis="reconstructed "+self.module("Unfolding").getUnfoldingVariableName(),
            yaxis="reconstructed "+self.module("Unfolding").getUnfoldingVariableName(),
            zaxis="correlation",
            title=self.module("Samples").getPlotTitle(channels)+"#kern[-0.5]{ }+#kern[-0.5]{ }jets"
        )
        
        
        #unfolding
        combinedUnfoldedHist,combinedUnfoldedCovariance,bestTau = self.module("Unfolding").unfold(
            combinedResponseMatrix,
            combinedMeasuredRecoHist,
            combinedGenBinning,
            #regularize only between the two merged histograms
            regularizations=range(1,len(genBinning)-2)+range(1+(len(genBinning)-1),len(genBinning)-2+(len(genBinning)-1)),
            dataCovariance=combinedCovarianceMatrix,
            scanOutput=os.path.join(self.module("Utils").getOutputFolder("unfolding/"+unfoldingName+"/"+unfoldingLevel),self.module("Samples").getChannelName(channels)+"_comb_tauScan"),
            fixedTau=None
        )
        #draw unfolded hist
        self.module("Drawing").plotDataHistogram(combinedNominalGenHist,combinedUnfoldedHist,
            os.path.join(self.module("Utils").getOutputFolder("unfolding/"+unfoldingName+"/"+unfoldingLevel),self.module("Samples").getChannelName(channels)+"_comb_unfoldedHist"),
            xaxis="unfolded "+self.module("Unfolding").getUnfoldingVariableName(),
            title=self.module("Samples").getPlotTitle(channels)+"#kern[-0.5]{ }+#kern[-0.5]{ }jets"
        )
        self.module("Drawing").drawHistogramMatrix(
            combinedUnfoldedCovariance, 
            os.path.join(self.module("Utils").getOutputFolder("unfolding/"+unfoldingName+"/"+unfoldingLevel),self.module("Samples").getChannelName(channels)+"_comb_unfoldedCovariance"), 
            xaxis="unfolded "+self.module("Unfolding").getUnfoldingVariableName(),
            yaxis="unfolded "+self.module("Unfolding").getUnfoldingVariableName(),
            zaxis="covariance",
            title=self.module("Samples").getPlotTitle(channels)+"#kern[-0.5]{ }+#kern[-0.5]{ }jets"
        )
        combinedUnfoldedCorrelation = self.module("Utils").calculateCorrelations(combinedUnfoldedCovariance)
        self.module("Drawing").drawHistogramMatrix(
            combinedUnfoldedCorrelation,
            os.path.join(self.module("Utils").getOutputFolder("unfolding/"+unfoldingName+"/"+unfoldingLevel),self.module("Samples").getChannelName(channels)+"_comb_unfoldedCorrelation"), 
            xaxis="unfolded "+self.module("Unfolding").getUnfoldingVariableName(),
            yaxis="unfolded "+self.module("Unfolding").getUnfoldingVariableName(),
            zaxis="correlation",
            title=self.module("Samples").getPlotTitle(channels)+"#kern[-0.5]{ }+#kern[-0.5]{ }jets"
        )
        
        
        for ibin in range(len(genBinning)-1):
            unfoldedHists[1].SetBinContent(ibin+1,combinedUnfoldedHist.GetBinContent(ibin+1))
            unfoldedHists[1].SetBinError(ibin+1,combinedUnfoldedHist.GetBinError(ibin+1))
            unfoldedHists[-1].SetBinContent(ibin+1,combinedUnfoldedHist.GetBinContent(ibin+1+(len(genBinning)-1)))
            unfoldedHists[-1].SetBinError(ibin+1,combinedUnfoldedHist.GetBinError(ibin+1+(len(genBinning)-1)))
        
        xtitle = self.module("Unfolding").getUnfoldingLevel()+" "+self.module("Unfolding").getUnfoldingVariableName()
        ytitleSum = "d#kern[-0.5]{ }#sigma#kern[-0.5]{ }#lower[0.2]{#scale[1.3]{#/}}#kern[-2]{ }d#kern[-0.5]{ }"+self.module("Unfolding").getUnfoldingSymbol()+""
        ytitleRatio = "d#kern[-0.5]{ }(#sigma#lower[0.3]{#scale[0.8]{#kern[-0.5]{ }t}}#kern[-0.5]{ }/#sigma#lower[0.3]{#scale[0.8]{#kern[-0.5]{ }t+#bar{t}}}#kern[-0.5]{ })#kern[-0.5]{ }#lower[0.2]{#scale[1.3]{#/}}#kern[-2]{ }d#kern[-0.5]{ }"+self.module("Unfolding").getUnfoldingVariableName()+""
        unit = self.module("Unfolding").getUnfoldingVariableUnit()
        if unit!="":
            xtitle += " ("+unit+")"
            ytitleSum += " (pb#kern[-0.5]{ }/#kern[-0.5]{ }"+unit+")"
            ytitleRatio += " (1#kern[-0.5]{ }/#kern[-0.5]{ }"+unit+")"
        else:
            ytitleSum += " (pb)"
            
        for charge in unfoldedHists.keys():
            self.module("Drawing").plotDataHistogram(nominalGenHists[charge],unfoldedHists[charge],
                os.path.join(self.module("Utils").getOutputFolder("unfolding/"+unfoldingName+"/"+unfoldingLevel),self.module("Samples").getChannelName(channels)+"_"+self.module("Samples").getChargeName(charge)+"_unfoldedHist"),
                title=self.module("Samples").getPlotTitle(channels,charge)+"#kern[-0.5]{ }+#kern[-0.5]{ }jets",xaxis=xtitle,yaxis=ytitleSum,logy=unfoldingName=="pt" or unfoldingName=="lpt" or unfoldingName=="wpt",normalizeByCrossSection=True
                
            )
            
            
        genSum = nominalGenHists[1].Clone("sumGen")
        genSum.Add(nominalGenHists[-1])
        
        histSum = self.module("Unfolding").calculateSum(unfoldedHists[1],unfoldedHists[-1],combinedUnfoldedCovariance)
        self.module("Drawing").plotDataHistogram(genSum,histSum,
            os.path.join(self.module("Utils").getOutputFolder("unfolding/"+unfoldingName+"/"+unfoldingLevel),self.module("Samples").getChannelName(channels)+"_sum_unfoldedHist"),
            title=self.module("Samples").getPlotTitle(channels)+"#kern[-0.5]{ }+#kern[-0.5]{ }jets",xaxis=xtitle,yaxis=ytitleSum,logy=unfoldingName=="pt" or unfoldingName=="lpt" or unfoldingName=="wpt",normalizeByCrossSection=True
        )
        
        
        genRatio= nominalGenHists[1].Clone("ratioGen")
        genRatio.Divide(genSum)
        histRatio = self.module("Unfolding").calculateRatio(unfoldedHists[1],unfoldedHists[-1],combinedUnfoldedCovariance)
        self.module("Drawing").plotDataHistogram(genRatio,histRatio,
            os.path.join(self.module("Utils").getOutputFolder("unfolding/"+unfoldingName+"/"+unfoldingLevel),self.module("Samples").getChannelName(channels)+"_ratio_unfoldedHist"),
            title=self.module("Samples").getPlotTitle(channels)+"#kern[-0.5]{ }+#kern[-0.5]{ }jets",xaxis=xtitle,yaxis=ytitleRatio,yrange=[0.2,1.],
            #uncBand=ratioUncBand
        )
        
        '''
        
        
        
        
        
        
        
        
        
        
        
