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

class MakeChi2(ROOT.TPyMultiGenFunction):
    def __init__(self,hist,cov):
        ROOT.TPyMultiGenFunction.__init__( self, self )
        
        N = hist.GetNbinsX()
        self.N = N
        self.val = numpy.zeros(N)
        self.x = numpy.zeros(N)
        self.cov = cov
        

        for ibin in range(N):
            self.x[ibin] = hist.GetBinCenter(ibin+1)
            self.val[ibin] = hist.GetBinContent(ibin+1)
 
        self.invcov = numpy.linalg.inv(self.cov)
        

        
    def NDim(self):
        return 2
        
    def DoEval(self, x):
        asym = lambda cos,A,N: N*0.5*(1+2*A*cos)
        chi2 = 0.0
        for ibin in range(self.N):
            for jbin in range(self.N):
                chi2 += (asym(self.x[ibin],x[0],x[1])-self.val[ibin])*self.invcov[ibin][jbin]*(asym(self.x[jbin],x[0],x[1])-self.val[jbin])
        return chi2

class MakeChi2Norm(MakeChi2):
    def __init__(self,hist,cov):
        MakeChi2.__init__( self, hist,cov)
        self.N = self.N-1
        self.val = self.val[:-1]
        self.x = self.x[:-1]
        self.cov = self.cov[:-1,:-1]
  
        self.invcov = numpy.linalg.inv(self.cov)
        
        
    def NDim(self):
        return 1
        
    def DoEval(self, x):
        asym = lambda cos,A: 0.5*(1+2*A*cos)
        chi2 = 0.0
        for ibin in range(self.N):
            for jbin in range(self.N):
                chi2 += (asym(self.x[ibin],x[0])-self.val[ibin])*self.invcov[ibin][jbin]*(asym(self.x[jbin],x[0])-self.val[jbin])
        return chi2

class Asymmetry(Module):
    def __init__(self,options=[]):
        Module.__init__(self,options)
        self._logger = logging.getLogger(__file__)
        self._logger.setLevel(logging.DEBUG)
        
    def calculateAsymmetry(self,hist):
        cosUp = 0.
        cosDown = 0.
        for ibin in range(hist.GetNbinsX()):
            if hist.GetBinCenter(ibin+1)<0:
                cosDown+=hist.GetBinContent(ibin+1)
            else:
                cosUp+=hist.GetBinContent(ibin+1)
        return (cosUp-cosDown)/(cosUp+cosDown)
            

    def fitDistribution(self,hist,cov):
        
        minimizer = ROOT.Math.Factory.CreateMinimizer("Minuit2", "")
        minimizer.SetMaxFunctionCalls(10000000)
        minimizer.SetMaxIterations(1000000)
        minimizer.SetTolerance(0.0001)
        minimizer.SetPrintLevel(0)
       
        #fct = ROOT.Math.Functor()
        chi2 = MakeChi2(hist,cov)
        
        minimizer.SetFunction(chi2)
        minimizer.SetVariable(0,"A",0.35,0.02)
        minimizer.SetVariable(1,"N",hist.Integral(),hist.Integral()*1e-4)
        minimizer.Minimize()
        
        #err = numpy.zeros((1,1))
    	#minimizer.GetCovMatrix(err) 
        #print minimizer.X()[0],	minimizer.Errors()[0]
        #print minimizer.X()[1],	minimizer.Errors()[1]
        return minimizer.X()[0],	minimizer.Errors()[0]
        
    def fitDistributionNorm(self,hist,cov):
        
        minimizer = ROOT.Math.Factory.CreateMinimizer("Minuit2", "")
        minimizer.SetMaxFunctionCalls(10000000)
        minimizer.SetMaxIterations(1000000)
        minimizer.SetTolerance(0.0001)
        minimizer.SetPrintLevel(0)
       
        #fct = ROOT.Math.Functor()
        chi2 = MakeChi2Norm(hist,cov)
        
        minimizer.SetFunction(chi2)
        minimizer.SetVariable(0,"A",0.35,0.02)
        minimizer.Minimize()
        
        #err = numpy.zeros((1,1))
    	#minimizer.GetCovMatrix(err) 
        return minimizer.X()[0], minimizer.Errors()[0]
        
