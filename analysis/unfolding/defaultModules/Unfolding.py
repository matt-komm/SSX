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
        
    def applyEfficiencyCorrection1D(self,hist):
        binMap = self.module("Unfolding").buildGlobalGenBinMap()
        eff = {}
        for ibin in range(len(self.module("Unfolding").getGenBinning("comb"))-1):
            eff=0.
            for channel in ["ele","mu"]:
                if binMap[channel].has_key(ibin):
                    eff+=1.
            c = hist.GetBinContent(ibin+1)
            err = hist.GetBinError(ibin+1)
            hist.SetBinContent(ibin+1,c/eff)
            hist.SetBinError(ibin+1,err/eff)
            
    def applyEfficiencyCorrection2D(self,hist):
        #need to apply propagation of uncertainty Y=J*X*J^T=l(i)*X(ij)*l(j)
        binMap = self.module("Unfolding").buildGlobalGenBinMap()
        L = len(self.module("Unfolding").getGenBinning("comb"))-1
        for ibin in range(L):
            for jbin in range(L):
                ieff=0.
                jeff=0.
                for channel in ["ele","mu"]:
                    if binMap[channel].has_key(ibin):
                        ieff+=1.
                for channel in ["ele","mu"]:
                    if binMap[channel].has_key(jbin):
                        jeff+=1.
                
                
                #diagonal
                c = hist.GetBinContent(ibin+1,jbin+1)
                err = hist.GetBinError(ibin+1,jbin+1)
                hist.SetBinContent(ibin+1,jbin+1,c/(ieff*jeff))
                hist.SetBinError(ibin+1,jbin+1,err/(ieff*jeff))
                
                c = hist.GetBinContent(L+ibin+1,L+jbin+1)
                err = hist.GetBinError(L+ibin+1,L+jbin+1)
                hist.SetBinContent(L+ibin+1,L+jbin+1,c/(ieff*jeff))
                hist.SetBinError(L+ibin+1,L+jbin+1,err/(ieff*jeff))
                
                #off-diagonal
                c = hist.GetBinContent(ibin+1,L+jbin+1)
                err = hist.GetBinError(ibin+1,L+jbin+1)
                hist.SetBinContent(ibin+1,L+jbin+1,c/(ieff*jeff))
                hist.SetBinError(ibin+1,L+jbin+1,err/(ieff*jeff))
                
                c = hist.GetBinContent(L+ibin+1,jbin+1)
                err = hist.GetBinError(L+ibin+1,jbin+1)
                hist.SetBinContent(L+ibin+1,jbin+1,c/(ieff*jeff))
                hist.SetBinError(L+ibin+1,jbin+1,err/(ieff*jeff))
                
            
        
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
        
        
    #TODO: not yet working
    def scanCoverage(self,responseMatrix,data,regularizations=[],dataCovariance=None,output=None):
        N=10
        xvalues = numpy.logspace(-8,12,N)
        bestTauAtMinCorrelation = xvalues[0]
        minGlobalCorrlation = 1.0
        self._logger.info("Scan for coverage: ["+str(xvalues[0])+", "+str(xvalues[-1])+"]")
        
        B = data.GetNbinsX()
        means = numpy.zeros(B)
        cov = numpy.zeros((B,B))
        for ibin in range(B):
            means[ibin]=data.GetBinContent(ibin+1)
            for jbin in range(B):
                cov[ibin][jbin]=dataCovariance.GetBinContent(ibin+1,jbin+1)
                 
        dataToy = data.Clone(data.GetName()+"_toy"+str(random.random()))
        dataToy.SetDirectory(0)
        TOYS = 500
        
        sigmas = [3]
        probs = map(lambda s: 100.*(0.5+0.5*ROOT.TMath.Erf(s/math.sqrt(2))),sigmas)
        
        coverage = numpy.zeros((B,len(sigmas),N))
        for i in range(N):
            unfoldedHist,covariance,bestTau = self.module("Unfolding").unfold(
                responseMatrix,
                data,
                regularizations,
                dataCovariance,
                scanOutput=None,
                fixedTau=xvalues[i]
            )
            toyResult = numpy.zeros((B,TOYS))
            for t in range(TOYS):
                
                diced = numpy.random.multivariate_normal(means,cov)
                for ibin in range(B):
                    dataToy.SetBinContent(ibin+1,diced[ibin])
                
                unfoldedHistDiced,covarianceDiced,bestTauDiced = self.module("Unfolding").unfold(
                    responseMatrix,
                    dataToy,
                    regularizations,
                    dataCovariance,
                    scanOutput=None,
                    fixedTau=xvalues[i]
                )
                for ibin in range(B):
                    toyResult[ibin][t]=unfoldedHistDiced.GetBinContent(ibin+1)
            resultQuantiles = numpy.percentile(toyResult, probs,axis=1)
            resultMean = numpy.mean(toyResult,axis=1)
            resultSigma = numpy.std(toyResult,axis=1)
            
            for ibin in range(B):
                for s in range(len(sigmas)):
                    estimated = unfoldedHist.GetBinContent(ibin+1)+sigmas[s]*math.sqrt(covariance.GetBinContent(ibin+1,ibin+1))
                    diced = resultQuantiles[s][ibin]
                    #diced = resultMean[ibin]+sigmas[s]*resultSigma[ibin]
                    coverage[ibin][s][i] = (diced-estimated)/estimated+1. #<0 if diced<estimated
        
        cv = ROOT.TCanvas("coverage","",800,700)
        cv.SetLogx()
        #cv.SetLogy()
        cv.SetRightMargin(0.18)
        axis = ROOT.TH2F("axisScan",";#tau;coverage",50,xvalues[0],xvalues[-1],50,0.5,1.5)
        axis.Draw("AXIS")
        rootObj =[]
        legend = ROOT.TLegend(0.83,0.9,0.99,0.9-0.05*len(sigmas)*B)
        legend.SetFillColor(ROOT.kWhite)
        legend.SetBorderSize(0)
        legend.SetTextFont(42)
        print "probs",probs
        colors = [ROOT.kAzure+4,ROOT.kViolet,ROOT.kGreen+1,ROOT.kYellow+1,ROOT.kOrange+7,ROOT.kRed+1]
        for s in range(len(sigmas)):
            for ibin in range(B):

                #print sigmas[s],probs[s],coverage[0][s]
                graph = ROOT.TGraph(N,xvalues,coverage[ibin][s])
                graph.SetLineWidth(3)
                graph.SetLineColor(colors[ibin%(B/2)])
                graph.SetLineStyle(1+ibin%2)
                rootObj.append(graph)
                graph.Draw("SameL")
                legend.AddEntry(graph,"bin%i %3.1f#sigma"%(ibin+1,sigmas[s]),"L")
        
        
        legend.Draw("Same")
        if output:
            cv.Print(output+".pdf")
            cv.Print(output+".png")
        
    def calculateSum(self,hist1,hist2,covariance,nominal=None,systematics=[]):
        return self.module("Unfolding").calculate(
            lambda pos,neg: pos+neg,
            hist1,
            hist2,
            covariance,
            nominal,
            systematics
        )
        
    def calculateRatio(self,hist1,hist2,covariance,nominal=None,systematics=[]):
        return self.module("Unfolding").calculate(
            lambda pos,neg: pos/(pos+neg),
            hist1,
            hist2,
            covariance,
            nominal,
            systematics
        )
        
            
        
    def calculate(self,fct,hist1,hist2,covariance,nominal=None,systematics=[]):
        if hist1.GetNbinsX()!=hist2.GetNbinsX():
            self._logger.critical("Cannot sum histograms - different number of bins")
            sys.exit(1)
        if covariance.GetNbinsX()!=2*hist1.GetNbinsX() or covariance.GetNbinsY()!=2*hist1.GetNbinsX():
            self._logger.critical("Cannot sum histograms - covariance matrix ("+str(covariance.GetNbinsX())+"x"+str(covariance.GetNbinsY())+") has wrong binning")
            sys.exit(1)
        if len(systematics)>0 and nominal==None:
            self._logger.critical("Require nominal histogram to which relative syst. variations are calculated.")
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
            nuciances = numpy.random.normal(0,1,size=(len(systematics))) #independent per sys
            for i in range(N):
                diced_pos = diced[i] 
                diced_neg = diced[i+N] 
                
                for isys,sysDict in enumerate(systematics):
                    rel_up_pos = sysDict[1]["Up"].GetBinContent(i+1)/nominal[1].GetBinContent(i+1)
                    rel_up_neg = sysDict[-1]["Up"].GetBinContent(i+1)/nominal[-1].GetBinContent(i+1)
                    
                    rel_down_pos = sysDict[1]["Down"].GetBinContent(i+1)/nominal[1].GetBinContent(i+1)
                    rel_down_neg = sysDict[-1]["Down"].GetBinContent(i+1)/nominal[-1].GetBinContent(i+1)
                    
                    if rel_up_pos<0 or rel_down_pos<0 or rel_up_neg<0 or rel_down_neg<0:
                        self._logger.critical("Discovered inconsitent systematic envelope for uncertainty "+str(isys))
                        self._logger.critical("Rel. up variations: "+str(rel_up_pos)+"/"+str(rel_up_neg)+" (pos/neg)")
                        self._logger.critical("Rel. down variations: "+str(rel_down_pos)+"/"+str(rel_down_neg)+" (pos/neg)")
                        sys.exit(1)
                        
                    #symmetrize uncertainties
                    if math.fabs(rel_up_pos-1)>math.fabs(rel_down_pos-1):
                        rel_down_pos = 1.-numpy.sign(rel_up_pos-1)*math.fabs(rel_up_pos-1)
                    else:
                        rel_up_pos = 1.-numpy.sign(rel_down_pos-1)*math.fabs(rel_down_pos-1)
                        
                    if math.fabs(rel_up_neg-1)>math.fabs(rel_down_neg-1):
                        rel_down_neg = 1.-numpy.sign(rel_up_neg-1)*math.fabs(rel_up_neg-1)
                    else:
                        rel_up_neg = 1.-numpy.sign(rel_down_neg-1)*math.fabs(rel_down_neg-1)
                        
                    
                    nominal_pos = means[i]
                    nominal_neg = means[i+N]
                    
                    up_pos = rel_up_pos*nominal_pos
                    up_neg = rel_up_neg*nominal_neg
                    
                    down_pos = rel_down_pos*nominal_pos
                    down_neg = rel_down_neg*nominal_neg
                    '''
                    up_pos = sys[1]["Up"].GetBinContent(i+1)
                    up_neg = sys[-1]["Up"].GetBinContent(i+1)
                   
                    down_pos = sys[1]["Down"].GetBinContent(i+1)
                    down_neg = sys[-1]["Down"].GetBinContent(i+1)
                    '''
                    #print i,isys,sys[-1]["Down"].GetBinContent(i+1),sys[-1]["Up"].GetBinContent(i+1)
                    #print i,isys,rel_up_pos-1,rel_down_pos-1
                    #print i,isys,rel_up_neg-1,rel_down_neg-1
                    '''
                    if nuciances[isys]>0:
                        
                        diced_pos += (up_pos-nominal_pos)*math.fabs(nuciances[isys])
                        diced_neg += (up_neg-nominal_neg)*math.fabs(nuciances[isys])
                    else:
                        diced_pos += (down_pos-nominal_pos)*math.fabs(nuciances[isys])
                        diced_neg += (down_neg-nominal_neg)*math.fabs(nuciances[isys])
                    '''
                    diced_pos += self.module("Utils").morphValueDiff(
                        nominal_pos,up_pos,down_pos,nuciances[isys]
                    )
                    diced_neg += self.module("Utils").morphValueDiff(
                        nominal_neg,up_neg,down_neg,nuciances[isys]
                    )
                    
                    
                toys[itoy][i]=fct(diced_pos,diced_neg)
                
        histResult = hist1.Clone("summedHists"+hist1.GetName()+hist2.GetName()+str(random.random()))
                
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
        
        
        covariance = ROOT.TH2D("covariance"+data.GetName()+str(random.random()),"",len(genBinning)-1,genBinning,len(genBinning)-1,genBinning)
        covariance.SetDirectory(0)
        unfoldedHist = ROOT.TH1D("unfoldedHist"+data.GetName()+str(random.random()),"",len(genBinning)-1,genBinning)
        unfoldedHist.SetDirectory(0)
        unfoldedHist.Sumw2()
        if (tunfold.setData(data,dataCovariance)>=10000):
            self._logger.critical("TUnfold indicates a fatal error")
            sys.exit(1)
        tunfold.doUnfolding(bestTau,unfoldedHist,covariance,True,False,False)
        
        for ibin in range(unfoldedHist.GetNbinsX()):
            #reset bins <0 to -> 0
            if unfoldedHist.GetBinContent(ibin+1)<0:
                unfoldedHist.SetBinContent(ibin+1,0.1)
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

        
