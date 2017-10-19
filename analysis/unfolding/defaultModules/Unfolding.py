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
        
    def getUnfoldingVariableUnit(self):
        raise NotImplementedError()
        
    def getUnfoldingLevel(self):
        raise NotImplementedError()
        
    def getRecoBinning(self):
        raise NotImplementedError()
        
    def getRecoVariable(self):
        raise NotImplementedError()
        
    def getRecoWeight(self,channel):
        raise NotImplementedError()
        
    def getRecoCut(self,channel):
        raise NotImplementedError()
        
        
    def getGenBinning(self):
        raise NotImplementedError()
        
    def getGenVariable(self):
        raise NotImplementedError()
        
    def getGenWeight(self,channel):
        raise NotImplementedError()
        
    def getGenCut(self,channel):
        raise NotImplementedError()
        
        
    def getRecoBinSelection(self,ibin):
        if ibin<0:
            return "1"
        binning = self.module("Unfolding").getRecoBinning()
        if ibin>=len(binning):
            self._logger.critical("Requested unfolding bin '"+str(ibin)+"' out of binning range")
            sys.exit(1)
            
        if ibin>=0:
            return "(("+self.module("Unfolding").getRecoVariable()+">="+str(binning[ibin])+")*("+self.module("Unfolding").getRecoVariable()+"<"+str(binning[ibin+1])+"))"

            
    
    def getGenBinSelection(self,ibin):
        if ibin<0:
            return "1"
        binning = self.module("Unfolding").getGenBinning()
        if ibin>=len(binning):
            self._logger.critical("Requested unfolding bin '"+str(ibin)+"' out of binning range")
            sys.exit(1)
            
        if ibin>=0:
            return "(("+self.module("Unfolding").getGenVariable()+">="+str(binning[ibin])+")*("+self.module("Unfolding").getGenVariable()+"<"+str(binning[ibin+1])+"))"
            
        
     
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
        cv = ROOT.TCanvas("cvScan","",800,600)
        cv.SetLogx()
        cv.SetRightMargin(0.18)
        axis = ROOT.TH2F("axisScan",";#tau;#rho",50,xvalues[0],xvalues[-1],50,-1.1,1.1)
        axis.Draw("AXIS")
        rootObj =[]
        legend = ROOT.TLegend(0.83,0.9,0.99,0.5)
        legend.SetFillColor(ROOT.kWhite)
        legend.SetBorderSize(0)
        legend.SetTextFont(42)
        for ibin in range(len(genBins)-2):
            graph = ROOT.TGraph(N,xvalues,yvalues[ibin+1])
            graph.SetLineWidth(len(genBins)-ibin)
            graph.SetLineColor(ROOT.kBlue-ibin+2)
            rootObj.append(graph)
            graph.Draw("SameL")
            legend.AddEntry(graph,"#rho (1,"+str(ibin+2)+")","L")
        graph = ROOT.TGraph(N,xvalues,yvalues[0])
        graph.SetLineWidth(3)
        graph.SetLineColor(ROOT.kOrange+10)
        graph.SetLineStyle(2)
        rootObj.append(graph)
        graph.Draw("SameL")
        legend.AddEntry(graph,"#bar{#rho}","L")
        legend.Draw("Same")
        #cv.Update()
        #cv.WaitPrimitive()
        if output:
            cv.Print(output+".pdf")
            cv.Print(output+".png")
        return bestTauAtMinCorrelation
        
    
    
    def unfold(self,responseMatrix,data,genBinning,dataCovariance=None,scanOutput=None,fixedTau=None):
        genHist = responseMatrix.ProjectionX(responseMatrix.GetName()+"genX")

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

        
