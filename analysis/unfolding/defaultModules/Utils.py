import re
import os
import ROOT
import random
import shutil
import sys
import math
import numpy
from Module import Module

import logging

class Utils(Module):
    def __init__(self,options=[]):
        Module.__init__(self,options)
        self._logger = logging.getLogger(__file__)
        self._logger.setLevel(logging.DEBUG)
        
    def getUncertaintyName(self):
        return "nominal"
        
        
    def getOutputFolder(self,subFolder=""):
        return os.path.join(os.getcwd(),"result",subFolder)
        
    def createFolder(self,folderName="",force=False):
    
        try:
            if os.path.exists(self.module("Utils").getOutputFolder(folderName)) and not force:
                self._logger.warning("Output folder already exists!: "+self.module("Utils").getOutputFolder(folderName))
            elif os.path.exists(self.module("Utils").getOutputFolder(folderName)) and force:
                self._logger.info("delete existing output folder: "+self.module("Utils").getOutputFolder(folderName))
                shutil.rmtree(self.module("Utils").getOutputFolder(folderName))
            if not os.path.exists(self.module("Utils").getOutputFolder(folderName)):
                self._logger.info("creating output folder: "+self.module("Utils").getOutputFolder(folderName))
                os.makedirs(self.module("Utils").getOutputFolder(folderName))
            
        except Exception,e:
            self._logger.error(str(e))
            

    def addUnderflowOverflow(self,hist):
        hist.SetBinContent(1,hist.GetBinContent(0)+hist.GetBinContent(1))
        N=hist.GetNbinsX()
        hist.SetBinContent(N,hist.GetBinContent(N)+hist.GetBinContent(N+1))
        hist.SetBinContent(0,0)
        hist.SetBinContent(N+1,0)
        hist.SetEntries(hist.GetEntries()-4)
        
    def getHist1D(self,hist,fileName,processName,variableName,weight,addUnderOverflows=False):
        hist.SetDirectory(0)
        rootFile = ROOT.TFile(fileName[0])
        tree = rootFile.Get(processName)
        tempHist=hist.Clone()
        tempHist.Scale(0)
        tempHist.SetEntries(0)
        tempHist.SetName("hist_"+processName+str(random.random()))
        #print weight
        #print
        if (tree):
            for fileNameExtra in fileName[1:]:  
                tree.AddFriend(processName,fileNameExtra)
            #self._logger.debug("projecting 1D: "+hist.GetName()+", "+processName+", "+variableName+", "+weight)
            tree.Project(tempHist.GetName(),variableName,weight)
            tempHist.SetDirectory(0)
            if addUnderOverflows:
                self.module("Utils").addUnderflowOverflow(tempHist)
            else:
                tempHist.SetBinContent(0,0)
                tempHist.SetBinContent(tempHist.GetNbinsX()+1,0)
                tempHist.SetEntries(tempHist.GetEntries()-2)
            hist.Add(tempHist)
        rootFile.Close()
        
    def getHist2D(self,hist,fileName,processName,variableNameX,variableNameY,weight):
        hist.SetDirectory(0)
        rootFile = ROOT.TFile(fileName[0])
        tree = rootFile.Get(processName)
        tempHist=hist.Clone()
        tempHist.Scale(0)
        tempHist.SetEntries(0)
        if (tree):
            for fileNameExtra in fileName[1:]:  
                tree.AddFriend(processName,fileNameExtra)
            #self._logger.debug("projecting 1D: "+hist.GetName()+", "+processName+", "+variableName+", "+weight)
            tree.Project(tempHist.GetName(),variableNameY+":"+variableNameX,weight)
            tempHist.SetDirectory(0)
            for ibin in range(tempHist.GetNbinsX()+2):
                tempHist.SetBinContent(ibin,0,0)
                tempHist.SetBinContent(ibin,tempHist.GetNbinsY()+1,0)
                tempHist.SetEntries(tempHist.GetEntries()-2)
            for jbin in range(tempHist.GetNbinsY()+2):
                tempHist.SetBinContent(0,jbin,0)
                tempHist.SetBinContent(tempHist.GetNbinsX()+1,jbin,0)
                tempHist.SetEntries(tempHist.GetEntries()-2)
            hist.Add(tempHist)
        rootFile.Close()
        
    #morph difference with nominal subtracted
    def morphValueDiff(self,nominal,up,down,p):
        if p>1:
            return (up-nominal)*math.fabs(p)
        elif p<-1:
            return(down-nominal)*math.fabs(p)
        else:
            return 0.5*p*(up-down)+(p**2-0.5*math.fabs(p**3))*(up+down-2*nominal)
        
    def morphHist(self,nominal,systList,nuciances,covariance):
        if len(nuciances)!=(len(systList)):
            self._logger.critical("Morphing requires nuciances for each systematic")
            sys.exit(1)
        morphed = nominal.Clone(nominal.GetName()+"morph")
        morphed.SetDirectory(0)
        for ibin in range((morphed.GetNbinsX()+2)*(morphed.GetNbinsY()+2)):
            nominal = morphed.GetBinContent(ibin)
            resultDiced = numpy.zeros(200)
            for itoy in range(len(resultDiced)):
                resultDiced[itoy] = morphed.GetBinContent(ibin)
                pdiced = numpy.random.multivariate_normal(nuciances,covariance)
                for isys in range(len(systList)):
                    p = pdiced[isys]
                    up = systList[isys][0].GetBinContent(ibin)
                    down = systList[isys][1].GetBinContent(ibin)
                    resultDiced[itoy]+=self.module("Utils").morphValueDiff(nominal,up,down,p)
            morphed.SetBinContent(ibin,numpy.mean(resultDiced))
            morphed.SetBinError(ibin,numpy.std(resultDiced))
        return morphed
                
        
        
    def calculateCorrelations(self,hist):
        histCorr = hist.Clone(hist.GetName()+"correlations")
        for ibin in range(histCorr.GetNbinsX()):
            for jbin in range(histCorr.GetNbinsY()):
                covij = hist.GetBinContent(ibin+1,jbin+1)
                covii = hist.GetBinContent(ibin+1,ibin+1)
                covjj = hist.GetBinContent(jbin+1,jbin+1)
                histCorr.SetBinContent(
                    ibin+1,
                    jbin+1,
                    covij/math.sqrt(covii*covjj)
                )
        return histCorr
        
    def getHistogramFile(self,prefix,channel,unfoldingName,unfoldingBin=-1,uncertainty="nominal"):
        if not uncertainty:
            uncertainty = "nominal"
        if unfoldingBin<0:
            return os.path.join(
                self.module("ThetaModel").getHistogramPath(channel,unfoldingName,uncertainty),
                prefix+"__"+channel+"__"+unfoldingName+".root"
            )
        else:
            return os.path.join(
                self.module("Utils").getHistogramPath(channel,unfoldingName,uncertainty),
                prefix+"__"+channel+"__"+unfoldingName+str(unfoldingBin)+".root"
            )
            
    def getHistogramPath(self,channel,unfoldingName,uncertainty="nominal"):
        return self.module("Utils").getOutputFolder(channel+"/"+uncertainty+"/"+unfoldingName)
                  
        
    def normalizeByBinWidth(self,hist):
        #hist.Scale(1./hist.Integral())
        
        for ibin in range(hist.GetNbinsX()):
            hist.SetBinContent(ibin+1,hist.GetBinContent(ibin+1)/hist.GetBinWidth(ibin+1))
            hist.SetBinError(ibin+1,hist.GetBinError(ibin+1)/hist.GetBinWidth(ibin+1))
        
            
    def normalizeByTransistionProbability(self,responseMatrix):
        responseMatrixSelectedNormalized = responseMatrix.Clone(responseMatrix.GetName()+"Norm")

        for genBin in range(responseMatrixSelectedNormalized.GetNbinsX()):
            s = 0.0
            for recoBin in range(responseMatrixSelectedNormalized.GetNbinsY()):
                s+=responseMatrixSelectedNormalized.GetBinContent(genBin+1,recoBin+1)
            for recoBin in range(responseMatrixSelectedNormalized.GetNbinsY()):
                c = responseMatrixSelectedNormalized.GetBinContent(genBin+1,recoBin+1)
                if s>0:
                    responseMatrixSelectedNormalized.SetBinContent(genBin+1,recoBin+1,c/s)
                else:
                    responseMatrixSelectedNormalized.SetBinContent(genBin+1,recoBin+1,0)
        return responseMatrixSelectedNormalized
            
