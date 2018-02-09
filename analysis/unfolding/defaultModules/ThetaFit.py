from Module import Module

import logging
import ROOT
import subprocess
import math
import os
import json
import csv
import sys

class ThetaFit(Module):
    def __init__(self,options=[]):
        Module.__init__(self,options)
        self._logger = logging.getLogger(__file__)
        self._logger.setLevel(logging.DEBUG)
        self.fitResult = None
        
    def run(self,fullPath,retry=3):
        i = 0
        exitcode = -1
        while (exitcode!=0 and i<retry):
            self._logger.info("run fit model: "+fullPath)
            p = subprocess.Popen(["theta", fullPath],
                #shell=True,
                stdout=subprocess.PIPE,
                stderr=subprocess.PIPE,
            )
            while True:
                nextline = p.stdout.readline()
                if nextline == '' and p.poll() != None:
                    break
            exitcode = p.returncode
            if exitcode!=0:
                self._logger.error("Theta exits with error code: "+str(p.returncode)+" after "+str(i+1)+"/"+str(retry)+" try")
            i+=1
        if exitcode!=0:
            self._logger.critical("Theta exits with error code: "+str(exitcode)+" after "+str(retry)+" retries")
            sys.exit(1)
        self._logger.info("Theta run successful: "+str(exitcode))
            
    def checkFitResult(self,fullPath,modelName="fit"):
        if os.path.exists(fullPath):
            self._logger.info("fit result already exists: "+fullPath)
            return self.module("ThetaFit").readFitResult(modelName,fileName)
        return None
                
    def parseFitResult(self,fullPath,parameterDict,modelName="fit"):
        f = ROOT.TFile(fullPath)
        tree = f.Get("products")
        if tree==None or tree.GetEntries()==0:
            raise Exception("No fit result produced")
        tree.GetEntry(0)
        
        Npar = len(parameterDict.keys())
        
        result = {"parameters":{}}
        for parameterName in sorted(parameterDict.keys()):
            if (not hasattr(tree,modelName+"__"+parameterName)) or (not hasattr(tree,modelName+"__"+parameterName+"_error")):
                raise Exception("No fitted values found for '"+modelName+"__"+parameterName+"'")
            prior = self.module("ThetaModel").getMeanAndUncertainty(parameterDict[parameterName])
            result["parameters"][parameterName]={
                "mean_fit":getattr(tree,modelName+"__"+parameterName),
                "unc_fit":getattr(tree,modelName+"__"+parameterName+"_error"),
                "mean_prior":prior[0],
                "unc_prior":prior[1]
            }
            
        if (not hasattr(tree,modelName+"__covariance")):
            raise Exception("No fitted covariance matrix found for '"+modelName+"__covariance'")

        cov = getattr(tree,modelName+"__covariance")
        
        covariances = ROOT.TH2D("covariance","",Npar,0,Npar,Npar,0,Npar)
        covariances.SetDirectory(0)
        correlations = ROOT.TH2D("correlations","",Npar,0,Npar,Npar,0,Npar)
        correlations.SetDirectory(0)
        
        #result["covariances"]={"hist":covariances,"values":{}}
        #result["correlations"]={"hist":correlations,"values":{}}
        
        #store only plain values for saving to file
        result["covariances"]={"values":{}}
        result["correlations"]={"values":{}}
        
        for ibin,ibinLabel in enumerate(sorted(parameterDict.keys())):
            for jbin,jbinLabel in enumerate(sorted(parameterDict.keys())):
                ijthetaBin = ibin*Npar+jbin
                iithetaBin = ibin*Npar+ibin
                jjthetaBin = jbin*Npar+jbin
                covij = cov.GetBinContent(ijthetaBin+1,1)
                covii = cov.GetBinContent(iithetaBin+1,1)
                covjj = cov.GetBinContent(jjthetaBin+1,1)
                corrij = 0 
                if covii>0 and covjj>0:
                    corrij = covij/math.sqrt(covii*covjj)
                    correlations.SetBinContent(ibin+1,jbin+1,corrij)
                else:
                    correlations.SetBinContent(ibin+1,jbin+1,0.0)
                covariances.SetBinContent(ibin+1,jbin+1,covij)
                
                if not result["covariances"]["values"].has_key(ibinLabel):
                    result["covariances"]["values"][ibinLabel]={}
                    result["correlations"]["values"][ibinLabel]={}
                if not result["covariances"]["values"].has_key(jbinLabel):
                    result["covariances"]["values"][jbinLabel]={}
                    result["correlations"]["values"][jbinLabel]={}
                result["covariances"]["values"][ibinLabel][jbinLabel]=covij
                result["covariances"]["values"][jbinLabel][ibinLabel]=covij
                result["correlations"]["values"][ibinLabel][jbinLabel]=corrij
                result["correlations"]["values"][jbinLabel][ibinLabel]=corrij
                    
        
        for ibin, binLabel in enumerate(sorted(parameterDict.keys())):
            covariances.GetXaxis().SetBinLabel(ibin+1,binLabel)
            covariances.GetYaxis().SetBinLabel(ibin+1,binLabel)
            correlations.GetXaxis().SetBinLabel(ibin+1,binLabel)
            correlations.GetYaxis().SetBinLabel(ibin+1,binLabel)
        
        
        if (not hasattr(tree,modelName+"__nll")):
            raise Exception("No NLL value found for '"+modelName+"__nll'")
        result["nll"]=getattr(tree,modelName+"__nll")

        f.Close()
        
        return result
        
    def saveFitResult(self,fullPath,fitResult):
        f = open(fullPath,"w")
        json.dump(fitResult,f)
        f.close()
        f = open(fullPath+".yields","w")
        for p in sorted(fitResult["parameters"].keys()):
            f.write("%30s: %6.3f +- %6.3f\n"%(p,fitResult["parameters"][p]["mean_fit"],fitResult["parameters"][p]["unc_fit"]))
        f.close()
    def loadFitResult(self,fullPath):
        f = open(fullPath)
        fitResult = json.load(f)
        f.close()
        return fitResult
        
    
        
   
        
        
        
