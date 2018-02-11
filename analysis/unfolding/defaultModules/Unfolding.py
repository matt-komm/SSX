import ROOT
import pyfit
import numpy
import math
import os
import os.path
import re
import random
import sys

from Module import Module

import logging

class Unfolding(Module):
    def __init__(self,options=[]):
        Module.__init__(self,options)
        self._logger = logging.getLogger(__file__)
        self._logger.setLevel(logging.DEBUG)
        
    def getUnfoldingName(self):
        return "inc"
        
    def getUnfoldingVariableName(self):
        raise NotImplementedError()
        
    def getUnfoldingSymbol(self):
        raise NotImplementedError()
        
    def getUnfoldingVariableUnit(self):
        raise NotImplementedError()
        
    def getUnfoldingLevel(self):
        raise NotImplementedError()
        
    def getRecoBinning(self,channel):
        raise NotImplementedError()
        
    def getRecoVariable(self,channel):
        raise NotImplementedError()
        
    def getRecoWeight(self,channel):
        raise NotImplementedError()
        
    def getRecoCut(self,channel):
        raise NotImplementedError()
        
        
    def getGenBinning(self,channel):
        raise NotImplementedError()
        
    def getGenVariable(self,channel):
        raise NotImplementedError()
        
    def getGenWeight(self,channel):
        raise NotImplementedError()
        
    def getGenCut(self,channel):
        raise NotImplementedError()
         
    def getRecoBinCenters(self,channel):
        binning = self.module("Unfolding").getRecoBinning(channel)
        result = numpy.zeros(len(binning)-1)
        for i in range(len(result)):
            result[i]=0.5*(binning[i]+binning[i+1])
        return result
        
    def getGenBinCenters(self,channel):
        binning = self.module("Unfolding").getGenBinning(channel)
        result = numpy.zeros(len(binning)-1)
        for i in range(len(result)):
            result[i]=0.5*(binning[i]+binning[i+1])
        return result
        
    def buildGlobalBinMap(self,globalBinning,eleBinning,muBinning):
        #need to associate bin numbers to actual values!!!
        channelToGlobalBins = {"ele":{},"mu":{},"comb":{}}
        for iglobalBin in range(len(globalBinning)):
            channelToGlobalBins["comb"][iglobalBin]=iglobalBin
        for ieleBin, eleBin in enumerate(eleBinning):
            for iglobal,globalBin in enumerate(globalBinning):
                if math.fabs(globalBin-eleBin)<0.00001:
                    channelToGlobalBins["ele"][ieleBin]=iglobal
                    break
        if len(channelToGlobalBins["ele"].keys())!=len(eleBinning):
            self._logger.critical("Not all bins of ele channel could be associated to the global binning scheme")
            sys.exit(1)
        #self._logger.info("Ele to global binning map: "+str(channelToGlobalBins["ele"]))
        for imuBin, muBin in enumerate(muBinning):
            for iglobal,globalBin in enumerate(globalBinning):
                if math.fabs(globalBin-muBin)<0.00001:
                    channelToGlobalBins["mu"][imuBin]=iglobal
                    break
        #self._logger.info("Mu to global binning map: "+str(channelToGlobalBins["mu"]))
        if len(channelToGlobalBins["mu"].keys())!=len(muBinning):
            self._logger.critical("Not all bins of mu channel could be associated to the global binning scheme")
            sys.exit(1)
        return channelToGlobalBins
        
    def buildGlobalRecoBinMap(self):
        #need to associate bin numbers to actual values!!!
        globalBinning = self.module("Unfolding").getRecoBinCenters("comb")
        eleBinning = self.module("Unfolding").getRecoBinCenters("ele")
        muBinning = self.module("Unfolding").getRecoBinCenters("mu")
        return self.module("Unfolding").buildGlobalBinMap(globalBinning,eleBinning,muBinning)
        
    def buildGlobalGenBinMap(self):
        #need to associate bin numbers to actual values!!!
        channelToGlobalBins = {"ele":{},"mu":{}}
        globalBinning = self.module("Unfolding").getGenBinCenters("comb")
        eleBinning = self.module("Unfolding").getGenBinCenters("ele")
        muBinning = self.module("Unfolding").getGenBinCenters("mu")
        return self.module("Unfolding").buildGlobalBinMap(globalBinning,eleBinning,muBinning)
        
    def getRecoBinSelection(self,ibin,channel):
        if ibin<0:
            return "1"
        binning = self.module("Unfolding").getRecoBinning(channel)
        if ibin>=len(binning):
            self._logger.critical("Requested unfolding bin '"+str(ibin)+"' out of binning range")
            sys.exit(1)
            
        if ibin>=0:
            return "(("+self.module("Unfolding").getRecoVariable(channel)+">="+str(binning[ibin])+")*("+self.module("Unfolding").getRecoVariable(channel)+"<"+str(binning[ibin+1])+"))"

            
    
    def getGenBinSelection(self,ibin,channel):
        if ibin<0:
            return "1"
        binning = self.module("Unfolding").getGenBinning(channel)
        if ibin>=len(binning):
            self._logger.critical("Requested unfolding bin '"+str(ibin)+"' out of binning range")
            sys.exit(1)
            
        if ibin>=0:
            return "(("+self.module("Unfolding").getGenVariable(channel)+">="+str(binning[ibin])+")*("+self.module("Unfolding").getGenVariable(channel)+"<"+str(binning[ibin+1])+"))"
            
        
    def calculateGenUncertaintyBandRatio(self,channels,uncertainties):
        ratiosPerUncertainty = numpy.zeros((len(uncertainties),len(self.module("Unfolding").getGenBinning(self.module("Samples").getChannelName(channels)))-1))
        for iunc, uncertaintyName in enumerate(uncertainties):
            genPos = None
            genNeg = None
            for channel in channels:
                responseFileNamePos = self.module("Response").getOutputResponseFile(
                    channel,
                    self.module("Unfolding").getUnfoldingName(),
                    self.module("Unfolding").getUnfoldingLevel(),
                    uncertaintyName,
                    1
                )
                rootFilePos = ROOT.TFile(responseFileNamePos)
                if not rootFilePos:
                    self._logger.critical("Response file '"+responseFileNamePos+"' does not exist")
                    sys.exit(1)
                if not rootFilePos.Get("gen"):
                    self._logger.critical("Histogram 'gen' does not exist in response file '"+responseFileNamePos+"'")
                    sys.exit(1)
                    
                if genPos==None:
                    genPos = rootFilePos.Get("gen").Clone()
                    genPos.SetDirectory(0)
                else:
                    genPos.Add(rootFilePos.Get("gen"))
                rootFilePos.Close()
                
                responseFileNameNeg = self.module("Response").getOutputResponseFile(
                    channel,
                    self.module("Unfolding").getUnfoldingName(),
                    self.module("Unfolding").getUnfoldingLevel(),
                    uncertaintyName,
                    -1
                )
                rootFileNeg = ROOT.TFile(responseFileNameNeg)
                if not rootFileNeg:
                    self._logger.critical("Response file '"+responseFileNameNeg+"' does not exist")
                    sys.exit(1)
                if not rootFileNeg.Get("gen"):
                    self._logger.critical("Histogram 'gen' does not exist in response file '"+responseFileNameNeg+"'")
                    sys.exit(1)
                if genNeg==None:
                    genNeg = rootFileNeg.Get("gen").Clone()
                    genNeg.SetDirectory(0)
                else:
                    genNeg.Add(rootFileNeg.Get("gen"))
                rootFileNeg.Close()
            
            for ibin in range(genPos.GetNbinsX()):
                if numpy.isinf(genPos.GetBinContent(ibin+1)) or numpy.isinf(genNeg.GetBinContent(ibin+1)):
                    ratiosPerUncertainty[iunc][ibin] = float('NaN')
                else:
                    if genPos.GetBinContent(ibin+1)>0 and genNeg.GetBinContent(ibin+1)>0:
                        ratiosPerUncertainty[iunc][ibin]=genPos.GetBinContent(ibin+1)/(genPos.GetBinContent(ibin+1)+genNeg.GetBinContent(ibin+1))
                    else:
                        ratiosPerUncertainty[iunc][ibin] = float('NaN')
                #print "%3i %3i %8.0f %8.0f %5.3f"%(iunc,ibin,genPos.GetBinContent(ibin+1),genNeg.GetBinContent(ibin+1),ratiosPerUncertainty[iunc][ibin])
        meanResult = numpy.nanmean(ratiosPerUncertainty,axis=0)
        sigResult = numpy.nanstd(ratiosPerUncertainty,axis=0)
        
 
        result = numpy.zeros((len(self.module("Unfolding").getGenBinning(self.module("Samples").getChannelName(channels)))-1,3))     
        for ibin in range(len(self.module("Unfolding").getGenBinning(self.module("Samples").getChannelName(channels)))-1):
            result[ibin][0]=meanResult[ibin]-sigResult[ibin]
            result[ibin][1]=meanResult[ibin]
            result[ibin][2]=meanResult[ibin]+sigResult[ibin]
        return result
        
     
    def doScan(self,tunfold,genBins,output=None):
        N=100
        xvalues = numpy.logspace(-8,-2,N)
        yvalues = numpy.zeros((len(genBins)-1,N))
        bestTauAtMinCorrelation = xvalues[0]
        minGlobalCorrlation = 1.0
        self._logger.info("Scan for regularization: ["+str(xvalues[0])+", "+str(xvalues[-1])+"]")
        for i in range(N):
            covariance = ROOT.TH2D("correlation"+str(random.random())+str(i),"",len(genBins)-1,genBins,len(genBins)-1,genBins)
            unfoldedHist = ROOT.TH1D("unfoldedHist"+str(random.random())+str(i),"",len(genBins)-1,genBins)
            unfoldedHist.Sumw2()
            tunfold.doUnfolding(xvalues[i],unfoldedHist,covariance)
            rhos = ROOT.PyUtils.getBinByBinCorrelations(covariance) #rho[0] -> global correlation
            if rhos[0]<minGlobalCorrlation:
                bestTauAtMinCorrelation=xvalues[i]
                minGlobalCorrlation=rhos[0]
            for ibin in range(len(genBins)-1):
                yvalues[ibin][i]=rhos[ibin]
        cv = ROOT.TCanvas("cvScan","",800,700)
        cv.SetLogx()
        cv.SetRightMargin(0.18)
        axis = ROOT.TH2F("axisScan",";#tau;#rho",50,xvalues[0],xvalues[-1],50,-1.1,1.1)
        axis.Draw("AXIS")
        rootObj =[]
        legend = ROOT.TLegend(0.83,0.9,0.99,0.9-0.055*len(genBins))
        legend.SetFillColor(ROOT.kWhite)
        legend.SetBorderSize(0)
        legend.SetTextFont(42)
        for ibin in range(len(genBins)-2):
            graph = ROOT.TGraph(N,xvalues,yvalues[ibin+1])
            graph.SetLineWidth(len(genBins)/2-ibin/2)
            graph.SetLineColor(ROOT.kBlue-ibin/2+2)
            graph.SetLineStyle(1+ibin%3)
            rootObj.append(graph)
            graph.Draw("SameL")
            legend.AddEntry(graph,"#rho (1,"+str(ibin+2)+")","L")
        graph = ROOT.TGraph(N,xvalues,yvalues[0])
        graph.SetLineWidth(3)
        graph.SetLineColor(ROOT.kOrange+10)
        graph.SetLineStyle(2)
        rootObj.append(graph)
        bestTauLine = ROOT.TLine(bestTauAtMinCorrelation,-1.1,bestTauAtMinCorrelation,1.1)
        rootObj.append(bestTauLine)
        bestTauLine.SetLineWidth(2)
        bestTauLine.SetLineStyle(2)
        bestTauLine.SetLineColor(ROOT.kGray+1)
        bestTauLine.Draw("SameL")
        graph.Draw("SameL")
        legend.AddEntry(graph,"#bar{#rho}","L")
        legend.Draw("Same")
        #cv.Update()
        #cv.WaitPrimitive()
        if output:
            cv.Print(output+".pdf")
            cv.Print(output+".png")
        return bestTauAtMinCorrelation
        
        
    def calculateSum(self,hist1,hist2,covariance):
        if hist1.GetNbinsX()!=hist2.GetNbinsX():
            self._logger.critical("Cannot sum histograms - different number of bins")
            sys.exit(1)
        if covariance.GetNbinsX()!=2*hist1.GetNbinsX() or covariance.GetNbinsY()!=2*hist1.GetNbinsX():
            self._logger.critical("Cannot sum histograms - covariance matrix ("+str(covariance.GetNbinsX())+"x"+str(covariance.GetNbinsY())+") has wrong binning")
            sys.exit(1)
        N = hist1.GetNbinsX()
        means = numpy.zeros(2*N)
        cov = numpy.zeros((2*N,2*N))
        for i in range(N):
            means[i] = hist1.GetBinContent(i+1)
            means[i+N] = hist2.GetBinContent(i+1)
            
        for i in range(2*N):
            for j in range(2*N):
                cov[i][j]=covariance.GetBinContent(i+1,j+1)
                
        NTOYS = 5000
        numpy.random.seed(seed=12345)
        toys = numpy.zeros((NTOYS,N))
        

        for itoy in range(NTOYS):
            diced=numpy.random.multivariate_normal(mean=means,cov=cov)
            for i in range(N):
                toys[itoy][i]=diced[i]+diced[i+N]
                
        histResult = hist1.Clone("summedHists"+hist1.GetName()+hist2.GetName())
                
        meanResult = numpy.mean(toys,axis=0)
        covResult = numpy.cov(toys,rowvar=False)
        
        for i in range(N):
            histResult.SetBinContent(i+1,meanResult[i])
            histResult.SetBinError(i+1,math.sqrt(covResult[i][i]))
        return histResult
        
    
    def calculateRatio(self,hist1,hist2,covariance):
        if hist1.GetNbinsX()!=hist2.GetNbinsX():
            self._logger.critical("Cannot sum histograms - different number of bins")
            sys.exit(1)
        if covariance.GetNbinsX()!=2*hist1.GetNbinsX() or covariance.GetNbinsY()!=2*hist1.GetNbinsX():
            self._logger.critical("Cannot sum histograms - covariance matrix has wrong binning")
            sys.exit(1)
        N = hist1.GetNbinsX()
        means = numpy.zeros(2*N)
        cov = numpy.zeros((2*N,2*N))
        for i in range(N):
            means[i] = hist1.GetBinContent(i+1)
            means[i+N] = hist2.GetBinContent(i+1)
            
        for i in range(2*N):
            for j in range(2*N):
                cov[i][j]=covariance.GetBinContent(i+1,j+1)
                
        NTOYS = 5000
        numpy.random.seed(seed=12345)
        toys = numpy.zeros((NTOYS,N))
        

        for itoy in range(NTOYS):
            diced=numpy.random.multivariate_normal(mean=means,cov=cov)
            for i in range(N):
                toys[itoy][i]=diced[i]/(diced[i]+diced[i+N])
                
        histResult = hist1.Clone("summedHists"+hist1.GetName()+hist2.GetName())
                
        meanResult = numpy.mean(toys,axis=0)
        covResult = numpy.cov(toys,rowvar=False)
        
        for i in range(N):
            histResult.SetBinContent(i+1,meanResult[i])
            histResult.SetBinError(i+1,math.sqrt(covResult[i][i]))
        return histResult
            
    
    def unfold(self,responseMatrix,data,regularizations=[],dataCovariance=None,scanOutput=None,fixedTau=None):
        genHist = responseMatrix.ProjectionX(responseMatrix.GetName()+"genX")
        genBinning = numpy.zeros((genHist.GetNbinsX()+1))
        for i in range(len(genBinning)):
            genBinning[i]=genHist.GetXaxis().GetBinLowEdge(i+1)
        responseMatrixReweighted = responseMatrix.Clone(responseMatrix.GetName()+"Reweighted")
        '''
        for ibin in range(responseMatrix.GetNbinsX()):
            w = 1.0/genHist.GetBinContent(ibin+1)*genHist.Integral()/genHist.GetNbinsX()
            responseMatrixReweighted.SetBinContent(
                    ibin+1,
                    0,
                    responseMatrix.GetBinContent(ibin+1,0)*w
            )
        '''
        
        tunfold = ROOT.PyUnfold(responseMatrixReweighted)
        self._logger.info("Regularize the following bins: "+str(regularizations))
        for reg in regularizations:
            tunfold.addRegularization(reg)
            
        if (tunfold.setData(data,dataCovariance)>=10000):
            self._logger.critical("TUnfold indicates a fatal error")
            sys.exit(1)

        if fixedTau==None:
            bestTau = self.module("Unfolding").doScan(tunfold,genBinning,scanOutput)
        else:
            bestTau=fixedTau

        self._logger.info("Found tau for regularization: "+str(bestTau))
        
        
        covariance = ROOT.TH2D("covariance","",len(genBinning)-1,genBinning,len(genBinning)-1,genBinning)
        unfoldedHist = ROOT.TH1D("unfoldedHist","",len(genBinning)-1,genBinning)
        unfoldedHist.Sumw2()
        if (tunfold.setData(data,dataCovariance)>=10000):
            self._logger.critical("TUnfold indicates a fatal error")
            sys.exit(1)
        tunfold.doUnfolding(bestTau,unfoldedHist,covariance,True,False,False)
        
        for ibin in range(unfoldedHist.GetNbinsX()):
            unfoldedHist.SetBinError(ibin+1,math.sqrt(covariance.GetBinContent(ibin+1,ibin+1)))
        '''
        for ibin in range(unfoldedHist.GetNbinsX()):
            w = 1.0/genHist.GetBinContent(ibin+1)*genHist.Integral()/genHist.GetNbinsX()
            unfoldedHist.SetBinContent(
                ibin+1,
                unfoldedHist.GetBinContent(ibin+1)/w
            )
            unfoldedHist.SetBinError(
                ibin+1,
                unfoldedHist.GetBinError(ibin+1)/w
            )
        '''
        return unfoldedHist,covariance,bestTau

        
