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
        systematics = [] if self.getOption("systematics")==None else self.getOption("systematics").split(",")
        self._logger.info("Systematics: "+str(systematics))
        channelName = self.module("Samples").getChannelName(channels)
        #inc,pt,y,cos
        unfoldingName = self.module("Unfolding").getUnfoldingName()
        fitName = self.module("Unfolding").getFitName()
        if unfoldingName=="inc":
            self._logger.critical("Cannot unfolding inclusive xsec")
            sys.exit(1)
        unfoldingLevel = self.module("Unfolding").getUnfoldingLevel()
        
        
        self.module("Utils").createFolder("unfolding/"+unfoldingName+"/"+unfoldingLevel+"/profiled")
        outputFolder = self.module("Utils").getOutputFolder("unfolding/"+unfoldingName+"/"+unfoldingLevel+"/profiled")

        
        #for profiled syst use nominal hist atm - later take envelop of all profiled response matrices
        uncertainties = []
        for unc in systematics:
            uncertainties.append(unc+"Up")
            uncertainties.append(unc+"Down")
        responseMatricesPerChannel = self.module("Response").gatherResponse(
            unfoldingName,
            unfoldingLevel,
            channels,
            uncertainties=uncertainties
        )
        
        responseMatricesPerChannel = self.module("Response").combineResponseMatrices(responseMatricesPerChannel)
       
        
        #use either per channel or their combination - no need to keep the rest
        responseMatrices = responseMatricesPerChannel[channelName]
        
        
        
        fitOutput = os.path.join(
            self.module("Utils").getOutputFolder("fit/profiled"),
            self.module("ThetaModel").getFitFileName(channels,fitName,"profiled")
        )
        fitResult = self.module("ThetaFit").loadFitResult(fitOutput+".json")
        
        responseMatricesMorphed = self.module("Response").morphResponses(
            responseMatrices,
            systematics,
            fitResult
        )
        

        self.module("Drawing").drawHistogramResponseAndEfficiency(
            responseMatrices[0]["nominal"],
            os.path.join(outputFolder,self.module("Samples").getChannelName(channels)+"_response"), 
            xaxis=unfoldingLevel+" level "+self.module("Unfolding").getUnfoldingVariableName(),
            yaxis="reco. "+self.module("Unfolding").getUnfoldingVariableName(),
            title=self.module("Samples").getPlotTitle(channels)+"#kern[-0.5]{ }+#kern[-0.5]{ }jets"
        )
        
        self.module("Drawing").drawStabilityPurity(
            responseMatrices[0]["nominal"],
            os.path.join(outputFolder,self.module("Samples").getChannelName(channels)+"_pstest"), 
            title=self.module("Samples").getPlotTitle(channels)+"#kern[-0.5]{ }+#kern[-0.5]{ }jets",
            xaxis=unfoldingLevel+" level "+self.module("Unfolding").getUnfoldingVariableName()
        )
        
        
        nominalRecoHists = {}
        nominalRecoHistsMorphed = {}
        nominalGenHists = {}
        measuredRecoHists = {}
        measuredRecoCovariances = {}
        unfoldedHists = {}
        recoBinning = self.module("Unfolding").getRecoBinning(channelName)
        genBinning = self.module("Unfolding").getGenBinning(channelName)
        binMapReco = self.module("Unfolding").buildGlobalRecoBinMap()[channelName]
        binMapGen = self.module("Unfolding").buildGlobalGenBinMap()[channelName]

        for charge in [-1,1]:
            

            nominalGenHists[charge] = responseMatrices[charge]["nominal"].ProjectionX() 
            unfoldedHists[charge] = nominalGenHists[charge].Clone(nominalGenHists[charge].GetName()+"meas")
            
            nominalRecoHists[charge] = responseMatrices[charge]["nominal"].ProjectionY()
            
            nominalRecoHistsMorphed[charge] = responseMatricesMorphed[charge].ProjectionY()
            measuredRecoHists[charge] = nominalRecoHistsMorphed[charge].Clone(nominalRecoHists[charge].GetName()+"meas")
            
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
                    nominalRecoHistsMorphed[charge].GetBinContent(ibin+1)*signalFitResult["mean_fit"]
                )
                measuredRecoHists[charge].SetBinError(
                    ibin+1,
                    math.sqrt(
                        (nominalRecoHistsMorphed[charge].GetBinContent(ibin+1)*signalFitResult["unc_fit"])**2 + \
                        nominalRecoHistsMorphed[charge].GetBinError(ibin+1)**2
                    )
                )
                
                for jbin in range(len(recoBinning)-1):
                    signalFitResultCov = \
                        fitResult["covariances"]["values"]["tChannel_"+self.module("Samples").getChargeName(charge)+"_bin"+str(1+binMapReco[ibin])]["tChannel_"+self.module("Samples").getChargeName(charge)+"_bin"+str(1+binMapReco[jbin])]
                    measuredRecoCovariances[charge].SetBinContent(
                        ibin+1,
                        jbin+1,
                        nominalRecoHistsMorphed[charge].GetBinContent(ibin+1)*nominalRecoHistsMorphed[charge].GetBinContent(jbin+1)*signalFitResultCov
                    )

                    
            #draw reco hists
            self.module("Drawing").plotDataHistogram([nominalRecoHists[charge],nominalRecoHistsMorphed[charge]],measuredRecoHists[charge],
               os.path.join(outputFolder,self.module("Samples").getChannelName(channels)+"_"+self.module("Samples").getChargeName(charge)+"_recoHist"),
                xaxis="reconstructed "+self.module("Unfolding").getUnfoldingVariableName(),
                title=self.module("Samples").getPlotTitle(channels,charge)+"#kern[-0.5]{ }+#kern[-0.5]{ }jets"
            )
        
            #draw input covariance,correlation
            self.module("Drawing").drawHistogramMatrix(
                measuredRecoCovariances[charge], 
                os.path.join(outputFolder,self.module("Samples").getChannelName(channels)+"_"+self.module("Samples").getChargeName(charge)+"_recoCovariance"), 
                xaxis="reconstructed "+self.module("Unfolding").getUnfoldingVariableName(),
                yaxis="reconstructed "+self.module("Unfolding").getUnfoldingVariableName(),
                zaxis="covariance",
                title=self.module("Samples").getPlotTitle(channels,charge)+"#kern[-0.5]{ }+#kern[-0.5]{ }jets"
            )
            measuredRecoCorrelations = self.module("Utils").calculateCorrelations(measuredRecoCovariances[charge])
            self.module("Drawing").drawHistogramMatrix(
                measuredRecoCorrelations, 
                os.path.join(outputFolder,self.module("Samples").getChannelName(channels)+"_"+self.module("Samples").getChargeName(charge)+"_recoCorrelation"), 
                xaxis="reconstructed "+self.module("Unfolding").getUnfoldingVariableName(),
                yaxis="reconstructed "+self.module("Unfolding").getUnfoldingVariableName(),
                zaxis="correlation",
                title=self.module("Samples").getPlotTitle(channels,charge)+"#kern[-0.5]{ }+#kern[-0.5]{ }jets"
            )
            
        #note: nominalReco will be the morphed one!
        combinedHists = self.module("Response").buildCombinedResponseMatrix(
            genBinning,
            recoBinning,
            nominalRecoHists,
            measuredRecoHists,
            responseMatricesMorphed,
            nominalGenHists
        )
        
        combinedCovarianceMatrix = self.module("Response").buildCombinedConvarianceMatrix(
            recoBinning,
            measuredRecoHists,
            fitResult,
            binMapReco
        )
        
        self.module("Drawing").plotDataHistogram([combinedHists["nominalReco"]],combinedHists["measuredReco"],
            os.path.join(outputFolder,self.module("Samples").getChannelName(channels)+"_comb_recoHist"),
            xaxis="reconstructed "+self.module("Unfolding").getUnfoldingVariableName(),
        )
        self.module("Drawing").drawHistogramResponseAndEfficiency(
            combinedHists["response"],
            os.path.join(outputFolder,self.module("Samples").getChannelName(channels)+"_comb_response"), 
            xaxis=unfoldingLevel+" "+self.module("Unfolding").getUnfoldingVariableName(),
            yaxis="reconstructed "+self.module("Unfolding").getUnfoldingVariableName(),
            zaxis="transition probability (%)",
            title=self.module("Samples").getPlotTitle(channels)+"#kern[-0.5]{ }+#kern[-0.5]{ }jets"
        )
        self.module("Drawing").drawHistogramMatrix(
            combinedCovarianceMatrix, 
            os.path.join(outputFolder,self.module("Samples").getChannelName(channels)+"_comb_recoCovariance"), 
            xaxis="reconstructed "+self.module("Unfolding").getUnfoldingVariableName(),
            yaxis="reconstructed "+self.module("Unfolding").getUnfoldingVariableName(),
            zaxis="Covariance",
            title=self.module("Samples").getPlotTitle(channels)+"#kern[-0.5]{ }+#kern[-0.5]{ }jets"
        )
        self.module("Drawing").drawHistogramMatrix(
            self.module("Utils").calculateCorrelations(combinedCovarianceMatrix), 
            os.path.join(outputFolder,self.module("Samples").getChannelName(channels)+"_comb_recoCorrelation"), 
            xaxis="reconstructed "+self.module("Unfolding").getUnfoldingVariableName(),
            yaxis="reconstructed "+self.module("Unfolding").getUnfoldingVariableName(),
            zaxis="Correlation",
            title=self.module("Samples").getPlotTitle(channels)+"#kern[-0.5]{ }+#kern[-0.5]{ }jets"
        )
        
        
        #unfolding
        '''
        self.module("Unfolding").scanCoverage(
            combinedHists["response"],
            combinedHists["measuredReco"],
            #regularize only between the two merged histograms
            regularizations=range(1,len(genBinning)-2)+range(1+(len(genBinning)-1),len(genBinning)-2+(len(genBinning)-1)),
            dataCovariance=combinedCovarianceMatrix,
            output=os.path.join(outputFolder,self.module("Samples").getChannelName(channels)+"_comb_coverageScan")
        )
        '''
        
        #TODO: apply no regularization for lepton unfolding!
        combinedUnfoldedHist,combinedUnfoldedCovariance,bestTau = self.module("Unfolding").unfold(
            combinedHists["response"],
            combinedHists["measuredReco"],
            #regularize only between the two merged histograms
            regularizations=range(1,len(genBinning)-2)+range(1+(len(genBinning)-1),len(genBinning)-2+(len(genBinning)-1)),
            dataCovariance=combinedCovarianceMatrix,
            scanOutput=os.path.join(outputFolder,self.module("Samples").getChannelName(channels)+"_comb_tauScan"),
            fixedTau=1e-10 if (unfoldingName=="lpt" or unfoldingName=="leta") else None
        )
        #draw unfolded hist
        self.module("Drawing").plotDataHistogram([combinedHists["nominalGen"]],combinedUnfoldedHist,
            os.path.join(outputFolder,self.module("Samples").getChannelName(channels)+"_comb_unfoldedHist"),
            xaxis="unfolded "+self.module("Unfolding").getUnfoldingVariableName(),
            title=self.module("Samples").getPlotTitle(channels)+"#kern[-0.5]{ }+#kern[-0.5]{ }jets"
        )
        self.module("Drawing").drawHistogramMatrix(
            combinedUnfoldedCovariance, 
            os.path.join(outputFolder,self.module("Samples").getChannelName(channels)+"_comb_unfoldedCovariance"), 
            xaxis="unfolded "+self.module("Unfolding").getUnfoldingVariableName(),
            yaxis="unfolded "+self.module("Unfolding").getUnfoldingVariableName(),
            zaxis="covariance",
            title=self.module("Samples").getPlotTitle(channels)+"#kern[-0.5]{ }+#kern[-0.5]{ }jets"
        )
        combinedUnfoldedCorrelation = self.module("Utils").calculateCorrelations(combinedUnfoldedCovariance)
        self.module("Drawing").drawHistogramMatrix(
            combinedUnfoldedCorrelation,
            os.path.join(outputFolder,self.module("Samples").getChannelName(channels)+"_comb_unfoldedCorrelation"), 
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
        
        if len(channels)==2:
             self.module("Unfolding").applyEfficiencyCorrection1D(nominalGenHists[1])
             self.module("Unfolding").applyEfficiencyCorrection1D(nominalGenHists[-1])
             self.module("Unfolding").applyEfficiencyCorrection1D(unfoldedHists[1])
             self.module("Unfolding").applyEfficiencyCorrection1D(unfoldedHists[-1])

             self.module("Unfolding").applyEfficiencyCorrection2D(combinedUnfoldedCovariance)
             
        xtitle = self.module("Unfolding").getUnfoldingLevel()+" "+self.module("Unfolding").getUnfoldingVariableName()
        ytitleSum = "d#kern[-0.5]{ }#sigma#kern[-0.5]{ }#lower[0.2]{#scale[1.3]{#/}}#kern[-2]{ }d#kern[-0.5]{ }"+self.module("Unfolding").getUnfoldingSymbol()+""
        ytitleRatio = "d#kern[-0.5]{ }(#sigma#lower[0.3]{#scale[0.8]{#kern[-0.5]{ }t}}#kern[-0.5]{ }/#sigma#lower[0.3]{#scale[0.8]{#kern[-0.5]{ }t+#bar{t}}}#kern[-0.5]{ })#kern[-0.5]{ }#lower[0.2]{#scale[1.3]{#/}}#kern[-2]{ }d#kern[-0.5]{ }"+self.module("Unfolding").getUnfoldingSymbol()+""
        unit = self.module("Unfolding").getUnfoldingVariableUnit()
        if unit!="":
            xtitle += " ("+unit+")"
            ytitleSum += " (pb#kern[-0.5]{ }/#kern[-0.5]{ }"+unit+")"
            ytitleRatio += " (1#kern[-0.5]{ }/#kern[-0.5]{ }"+unit+")"
        else:
            ytitleSum += " (pb)"
            
        for charge in unfoldedHists.keys():
            self.module("Drawing").plotDataHistogram([nominalGenHists[charge]],unfoldedHists[charge],
                os.path.join(outputFolder,self.module("Samples").getChannelName(channels)+"_"+self.module("Samples").getChargeName(charge)+"_unfoldedHist"),
                title=self.module("Samples").getPlotTitle(channels,charge)+"#kern[-0.5]{ }+#kern[-0.5]{ }jets",xaxis=xtitle,yaxis=ytitleSum,logy=unfoldingName=="pt" or unfoldingName=="lpt" or unfoldingName=="wpt",normalizeByCrossSection=True
                
            )
            
        genSum = nominalGenHists[1].Clone("sumGen")
        genSum.Add(nominalGenHists[-1])
        nominalGenHists[0] = genSum
        
        histSum, covSum = self.module("Unfolding").calculateSum(unfoldedHists[1],unfoldedHists[-1],combinedUnfoldedCovariance)
        
        unfoldedHists[0] = histSum
        self.module("Drawing").plotDataHistogram([genSum],histSum,
            os.path.join(outputFolder,self.module("Samples").getChannelName(channels)+"_sum_unfoldedHist"),
            title=self.module("Samples").getPlotTitle(channels)+"#kern[-0.5]{ }+#kern[-0.5]{ }jets",xaxis=xtitle,yaxis=ytitleSum,logy=unfoldingName=="pt" or unfoldingName=="lpt" or unfoldingName=="wpt",normalizeByCrossSection=True
        )
        
        
        genRatio= nominalGenHists[1].Clone("ratioGen")
        genRatio.Divide(genSum)
        histRatio, covRatio = self.module("Unfolding").calculateRatio(unfoldedHists[1],unfoldedHists[-1],combinedUnfoldedCovariance)
        self.module("Drawing").plotDataHistogram([genRatio],histRatio,
            os.path.join(outputFolder,self.module("Samples").getChannelName(channels)+"_ratio_unfoldedHist"),
            title=self.module("Samples").getPlotTitle(channels)+"#kern[-0.5]{ }+#kern[-0.5]{ }jets",xaxis=xtitle,yaxis=ytitleRatio,yrange=[0.2,1.],
            #uncBand=ratioUncBand
        )
        
        for charge in [-1,1]:
            print "Charge: ",charge
            for ibin in range(measuredRecoHists[charge].GetNbinsX()):
                print "Reco/unfolded error ",ibin+1,": ",
                print measuredRecoHists[charge].GetBinError(ibin+1)/measuredRecoHists[charge].GetBinContent(ibin+1),
                print "/",
                print unfoldedHists[charge].GetBinError(ibin+1)/unfoldedHists[charge].GetBinContent(ibin+1)
            
        
        outputPath = os.path.join(outputFolder,self.module("Samples").getChannelName(channels)+"_result.root")
        outputFile = ROOT.TFile(outputPath,"RECREATE")
        for charge in [-1,1]:
            for h in [
                ["nominalReco_"+self.module("Samples").getChargeName(charge),nominalRecoHists[charge]],
                ["measuredReco_"+self.module("Samples").getChargeName(charge),measuredRecoHists[charge]],
                ["nominalGen_"+self.module("Samples").getChargeName(charge),nominalGenHists[charge]],
                ["unfolded_"+self.module("Samples").getChargeName(charge),unfoldedHists[charge]],
            ]:
                h[1].SetName(h[0])
                h[1].SetDirectory(outputFile)
                h[1].Write()
        for h in [
            ["covarianceReco",combinedCovarianceMatrix],
            ["covarianceUnfolded",combinedUnfoldedCovariance],
            ["nominalGen_"+self.module("Samples").getChargeName(0),nominalGenHists[0]],
            ["unfolded_"+self.module("Samples").getChargeName(0),unfoldedHists[0]],
            ["ratioUnfolded",histRatio],
            ["ratioGen",genRatio],
        ]:            
            h[1].SetName(h[0])
            h[1].SetDirectory(outputFile)
            h[1].Write()
        outputFile.Close()
        
            
        
        
        
        
        
        
        
        
