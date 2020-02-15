#!/usr/bin/python

import ROOT
import numpy
import random
import math
import os
import datetime
import re
from optparse import OptionParser

cvscale = 1.0

ROOT.gROOT.SetBatch(True)
ROOT.gStyle.SetOptStat(0)
ROOT.gStyle.SetOptFit(0)
ROOT.gROOT.SetStyle("Plain")
ROOT.gStyle.SetOptStat(0)
ROOT.gStyle.SetOptFit(1111)
ROOT.gStyle.SetPadTopMargin(0.08)
ROOT.gStyle.SetPadLeftMargin(0.13)
ROOT.gStyle.SetPadRightMargin(0.26)
ROOT.gStyle.SetPadBottomMargin(0.15)
ROOT.gStyle.SetStatFontSize(0.025)

ROOT.gStyle.SetOptFit()
ROOT.gStyle.SetOptStat(0)

# For the canvas:
ROOT.gStyle.SetCanvasBorderMode(0)
ROOT.gStyle.SetCanvasColor(ROOT.kWhite)
ROOT.gStyle.SetCanvasDefH(700) #Height of canvas
ROOT.gStyle.SetCanvasDefW(800) #Width of canvas
ROOT.gStyle.SetCanvasDefX(0)   #POsition on screen
ROOT.gStyle.SetCanvasDefY(0)

# For the Pad:
ROOT.gStyle.SetPadBorderMode(0)
# ROOT.gStyle.SetPadBorderSize(Width_t size = 1)
ROOT.gStyle.SetPadColor(ROOT.kWhite)
#ROOT.gStyle.SetPadGridX(True)
#ROOT.gStyle.SetPadGridY(True)
ROOT.gStyle.SetGridColor(ROOT.kBlack)
ROOT.gStyle.SetGridStyle(2)
ROOT.gStyle.SetGridWidth(1)

# For the frame:

ROOT.gStyle.SetFrameBorderMode(0)
ROOT.gStyle.SetFrameBorderSize(0)
ROOT.gStyle.SetFrameFillColor(0)
ROOT.gStyle.SetFrameFillStyle(0)
ROOT.gStyle.SetFrameLineColor(1)
ROOT.gStyle.SetFrameLineStyle(1)
ROOT.gStyle.SetFrameLineWidth(0)

# For the histo:
# ROOT.gStyle.SetHistFillColor(1)
# ROOT.gStyle.SetHistFillStyle(0)
# ROOT.gStyle.SetLegoInnerR(Float_t rad = 0.5)
# ROOT.gStyle.SetNumberContours(Int_t number = 20)

ROOT.gStyle.SetEndErrorSize(2)
#ROOT.gStyle.SetErrorMarker(20)
ROOT.gStyle.SetErrorX(0.)

ROOT.gStyle.SetMarkerStyle(20)
#ROOT.gStyle.SetMarkerStyle(20)

#For the fit/function:
ROOT.gStyle.SetOptFit(1)
ROOT.gStyle.SetFitFormat("5.4g")
ROOT.gStyle.SetFuncColor(2)
ROOT.gStyle.SetFuncStyle(1)
ROOT.gStyle.SetFuncWidth(1)

#For the date:
ROOT.gStyle.SetOptDate(0)
# ROOT.gStyle.SetDateX(Float_t x = 0.01)
# ROOT.gStyle.SetDateY(Float_t y = 0.01)

# For the statistics box:
ROOT.gStyle.SetOptFile(0)
ROOT.gStyle.SetOptStat(0) # To display the mean and RMS:   SetOptStat("mr")
ROOT.gStyle.SetStatColor(ROOT.kWhite)
ROOT.gStyle.SetStatFont(42)
ROOT.gStyle.SetStatFontSize(0.025)
ROOT.gStyle.SetStatTextColor(1)
ROOT.gStyle.SetStatFormat("6.4g")
ROOT.gStyle.SetStatBorderSize(1)
ROOT.gStyle.SetStatH(0.1)
ROOT.gStyle.SetStatW(0.15)

ROOT.gStyle.SetHatchesSpacing(0.8/math.sqrt(cvscale))
ROOT.gStyle.SetHatchesLineWidth(int(2*cvscale))

# ROOT.gStyle.SetStaROOT.TStyle(Style_t style = 1001)
# ROOT.gStyle.SetStatX(Float_t x = 0)
# ROOT.gStyle.SetStatY(Float_t y = 0)


#ROOT.gROOT.ForceStyle(True)
#end modified

# For the Global title:

ROOT.gStyle.SetOptTitle(0)

# ROOT.gStyle.SetTitleH(0) # Set the height of the title box
# ROOT.gStyle.SetTitleW(0) # Set the width of the title box
#ROOT.gStyle.SetTitleX(0.35) # Set the position of the title box
#ROOT.gStyle.SetTitleY(0.986) # Set the position of the title box
# ROOT.gStyle.SetTitleStyle(Style_t style = 1001)
#ROOT.gStyle.SetTitleBorderSize(0)

# For the axis titles:
ROOT.gStyle.SetTitleColor(1, "XYZ")
ROOT.gStyle.SetTitleFont(43, "XYZ")
ROOT.gStyle.SetTitleSize(35*cvscale, "XYZ")
# ROOT.gStyle.SetTitleXSize(Float_t size = 0.02) # Another way to set the size?
# ROOT.gStyle.SetTitleYSize(Float_t size = 0.02)
ROOT.gStyle.SetTitleXOffset(1.135)
#ROOT.gStyle.SetTitleYOffset(1.2)
ROOT.gStyle.SetTitleOffset(1.32, "YZ") # Another way to set the Offset

# For the axis labels:

ROOT.gStyle.SetLabelColor(1, "XYZ")
ROOT.gStyle.SetLabelFont(43, "XYZ")
ROOT.gStyle.SetLabelOffset(0.0105, "X")
ROOT.gStyle.SetLabelOffset(0.0087, "YZ")
ROOT.gStyle.SetLabelSize(32*cvscale, "XYZ")
#ROOT.gStyle.SetLabelSize(0.04, "XYZ")

# For the axis:

ROOT.gStyle.SetAxisColor(1, "XYZ")
ROOT.gStyle.SetAxisColor(1, "XYZ")
ROOT.gStyle.SetStripDecimals(True)
ROOT.gStyle.SetTickLength(0.03, "Y")
ROOT.gStyle.SetTickLength(0.05, "X")
ROOT.gStyle.SetNdivisions(1005, "X")
ROOT.gStyle.SetNdivisions(506, "Y")

ROOT.gStyle.SetPadTickX(1)  # To get tick marks on the opposite side of the frame
ROOT.gStyle.SetPadTickY(1)

# Change for log plots:
ROOT.gStyle.SetOptLogx(0)
ROOT.gStyle.SetOptLogy(0)
ROOT.gStyle.SetOptLogz(0)

#ROOT.gStyle.SetPalette(1) #(1,0)

# another top group addition

# Postscript options:
#ROOT.gStyle.SetPaperSize(20., 20.)
#ROOT.gStyle.SetPaperSize(ROOT.TStyle.kA4)
#ROOT.gStyle.SetPaperSize(27., 29.7)
#ROOT.gStyle.SetPaperSize(27., 29.7)
ROOT.gStyle.SetPaperSize(8.0*1.6*cvscale,6.5*1.6*cvscale)
ROOT.TGaxis.SetMaxDigits(3)
ROOT.gStyle.SetLineScalePS(2)

# ROOT.gStyle.SetLineStyleString(Int_t i, const char* text)
# ROOT.gStyle.SetHeaderPS(const char* header)
# ROOT.gStyle.SetTitlePS(const char* pstitle)
#ROOT.gStyle.SetColorModelPS(1)

# ROOT.gStyle.SetBarOffset(Float_t baroff = 0.5)
# ROOT.gStyle.SetBarWidth(Float_t barwidth = 0.5)
# ROOT.gStyle.SetPaintTextFormat(const char* format = "g")
# ROOT.gStyle.SetPalette(Int_t ncolors = 0, Int_t* colors = 0)
# ROOT.gStyle.SetTimeOffset(Double_t toffset)
# ROOT.gStyle.SetHistMinimumZero(kTRUE)
ROOT.gStyle.SetPalette(1)
ROOT.gStyle.SetPaintTextFormat("7.4f")





colors=[]
def hex2rgb(value):
    """Return (red, green, blue) for the color given as #rrggbb."""
    value = value.lstrip('#')
    lv = len(value)
    return tuple(int(value[i:i + lv // 3], 16)/255.0 for i in range(0, lv, lv // 3))

def newColor(red,green,blue):
    newColor.colorindex+=1
    color=ROOT.TColor(newColor.colorindex,red,green,blue)
    colors.append(color)
    return color
    
newColor.colorindex=301

def getDarkerColor(color):
    darkerColor=newColor(color.GetRed()*0.6,color.GetGreen()*0.6,color.GetBlue()*0.6)
    return darkerColor



from defaultModules.Module import Module

import logging
import ROOT
import copy
import os
import sys
import random
from ModelClasses import *

class IncCrossSection(Module.getClass("Program")):
    def __init__(self,options=[]):
        Module.__init__(self,options)
        self._logger = logging.getLogger(__file__)
        self._logger.setLevel(logging.DEBUG)
        
    def getResult(self,f):
        result = {}
        for charge in [-1,1]:
            for h in [
                #["nominalReco_"+self.module("Samples").getChargeName(charge)],
                #["measuredReco_"+self.module("Samples").getChargeName(charge)],
                ["nominalGen_"+self.module("Samples").getChargeName(charge)],
                ["unfolded_"+self.module("Samples").getChargeName(charge)],
            ]:
                result[h[0]]=f.Get(h[0])
                if (not result[h[0]]):
                    self._logger.critical("Histogram '"+h[0]+"' not found in file '"+str(f)+"'")
                    sys.exit(1)
                result[h[0]].Clone(h[0]+str(random.random()))
                result[h[0]].SetDirectory(0)
        for h in [
            ["covarianceReco"],
            ["covarianceUnfolded"],
            ["ratioUnfolded"],
            ["ratioGen"],
        ]:            
            result[h[0]]=f.Get(h[0])
            if (not result[h[0]]):
                self._logger.critical("Histogram '"+h[0]+"' not found in file '"+str(f)+"'")
                sys.exit(1)
            result[h[0]].Clone(h[0]+str(random.random()))
            result[h[0]].SetDirectory(0)
        return result
        
    def getFitResult(self,channels,unfoldingName,folder):
        fitOutput = os.path.join(
            self.module("Utils").getOutputFolder("fit/"+folder),
            self.module("ThetaModel").getFitFileName(channels,unfoldingName,folder)
        )
        return self.module("ThetaFit").loadFitResult(fitOutput+".json")
        
    def blue(self):
        pass
        
    def calculate(self,fct,means,cov,toys=10000):
        dicedResult = numpy.zeros(toys)
        for itoy in range(toys):
            diced = numpy.random.multivariate_normal(means,cov)
            dicedResult[itoy] = fct(diced)
        return numpy.mean(dicedResult),numpy.std(dicedResult)
        
    def execute(self):
        channels = self.getOption("channels").split(",")
        unfoldingLevel = self.getOption("level")
        channelName = self.module("Samples").getChannelName(channels)
        
        unfoldingName = "pt" #use angle here since it is contained in [-1;1] to get acceptance
        
        systematics = [] if self.getOption("systematics")==None else self.getOption("systematics").split(",")
        NSYS = len(systematics)
    
        #nominalFolder = self.module("Utils").getOutputFolder("unfolding/"+unfoldingName+"/"+unfoldingLevel+"/profiled")
        #rootFileNominal = ROOT.TFile(os.path.join(nominalFolder,channelName+"_result.root"))
        #nominalResult = self.getResult(rootFileNominal)
        #rootFileNominal.Close()
        
        '''
        nominalHistPos = nominalResult["nominalGen_pos"]
        nominalHistPos.Scale(1./self.module("Samples").getLumi())
        nominalXsecPos = nominalHistPos.Integral()
        
        nominalHistNeg = nominalResult["nominalGen_neg"]
        nominalHistNeg.Scale(1./self.module("Samples").getLumi())
        nominalXsecNeg = nominalHistNeg.Integral()
        
        nominalHist = nominalResult["nominalGen_inc"]
        nominalHist.Scale(1./self.module("Samples").getLumi())
        nominalXsec = nominalHist.Integral()
        '''
        if unfoldingLevel=="parton":
            #disregard lepton selection
            nominalXsec = 216.99
            
            nominalXsecPos = 136.02 
            nominalXsecNeg = 80.95
        
        print "nominal pos/neg/inc/ratio",nominalXsecPos,nominalXsecNeg,nominalXsec,nominalXsecPos/nominalXsecNeg
        fitResultStat = self.getFitResult(channels,"inc","nominal") 
        fitResultProfiled = self.getFitResult(channels,"inc","profiled")
        
        #print fitResultProfiled["parameters"]["tChannel_pos_binInc"]["mean_fit"],fitResultProfiled["parameters"]["tChannel_neg_binInc"]["mean_fit"]
        meansStat = [
            nominalXsecPos*fitResultStat["parameters"]["tChannel_pos_binInc"]["mean_fit"],
            nominalXsecNeg*fitResultStat["parameters"]["tChannel_neg_binInc"]["mean_fit"]
        ]
        covarianceStat = [
            [
                nominalXsecPos*nominalXsecPos*fitResultStat["covariances"]["values"]["tChannel_pos_binInc"]["tChannel_pos_binInc"],
                nominalXsecPos*nominalXsecNeg*fitResultStat["covariances"]["values"]["tChannel_pos_binInc"]["tChannel_neg_binInc"],
            ],[
                nominalXsecPos*nominalXsecNeg*fitResultStat["covariances"]["values"]["tChannel_pos_binInc"]["tChannel_neg_binInc"],
                nominalXsecNeg*nominalXsecNeg*fitResultStat["covariances"]["values"]["tChannel_neg_binInc"]["tChannel_neg_binInc"]
            ]
        ]
        
        f = open("incCrossSection.tex",'w')
        
        f.write("%20s & %10s & %10s \\\\\n"%("","\\$sigma(\\mathrm{t}+\\bar{\\mathrm{t}})$/pb","\\$sigma(\\mathrm{t})/sigma(\\bar{\\mathrm{t}})$"))
        
        correlationStat = covarianceStat[0][1]/math.sqrt(covarianceStat[0][0]*covarianceStat[1][1])
        incMeanStat,incStdStat = self.calculate(lambda x: x[0]+x[1],meansStat,covarianceStat)
        ratioMeanStat,ratioStdStat = self.calculate(lambda x: x[0]/x[1],meansStat,covarianceStat)

        
       
        
        meansProfiled = [
            nominalXsecPos*fitResultProfiled["parameters"]["tChannel_pos_binInc"]["mean_fit"],
            nominalXsecNeg*fitResultProfiled["parameters"]["tChannel_neg_binInc"]["mean_fit"]
        ]
        covarianceProfiled = [
            [
                nominalXsecPos*nominalXsecPos*fitResultProfiled["covariances"]["values"]["tChannel_pos_binInc"]["tChannel_pos_binInc"],
                nominalXsecPos*nominalXsecNeg*fitResultProfiled["covariances"]["values"]["tChannel_pos_binInc"]["tChannel_neg_binInc"],
            ],[
                nominalXsecPos*nominalXsecNeg*fitResultProfiled["covariances"]["values"]["tChannel_pos_binInc"]["tChannel_neg_binInc"],
                nominalXsecNeg*nominalXsecNeg*fitResultProfiled["covariances"]["values"]["tChannel_neg_binInc"]["tChannel_neg_binInc"]
            ]
        ]
        correlationProfiled = covarianceProfiled[0][1]/math.sqrt(covarianceProfiled[0][0]*covarianceProfiled[1][1])
        incMeanProfiled,incStdProfiled = self.calculate(lambda x: x[0]+x[1],meansProfiled,covarianceProfiled)
        ratioMeanProfiled,ratioStdProfiled = self.calculate(lambda x: x[0]/x[1],meansProfiled,covarianceProfiled)
        
        print "profiled",incMeanProfiled,ratioMeanProfiled
        
        f.write("%20s & %7.1f & %7.3f \\\\\n"%("",incMeanProfiled,ratioMeanProfiled))

        f.write("%20s & $\\pm% 5.1f$\\%% & $\\pm% 5.3f$ \\\\\n"%("Stat.-only",incStdStat/incMeanStat*100.,ratioStdStat))
        f.write("%20s & $\\pm% 5.1f$\\%% & $\\pm% 5.3f$ \\\\\n"%("Stat.+Exp.",incStdProfiled/incMeanProfiled*100.,ratioStdProfiled))
        
        
        '''
        print "pos",meansProfiled[0],math.sqrt(covarianceProfiled[0][0])
        print "neg",meansProfiled[1],math.sqrt(covarianceProfiled[1][1])
        print "corr",correlationProfiled
        print "-----------"
        print "inc",incMeanProfiled,incStdProfiled
        print "ratio",ratioMeanProfiled,ratioStdProfiled
        print "-----------"
        '''
        nameDict = {
            "pdf":"PDF",
            "pdfFull":"PDF",
            "tchanHdampPS":"$t$-ch. $h_\\mathrm{damp}$",
            "tchanScaleME":"$t$-ch. ME scale",
            "tchanScalePS":"$t$-ch. PS scale",
            "topMass":"Top mass",
            "ttbarHdampPS":"\\ttbar $h_\\mathrm{damp}$",
            "ttbarPt":"\\ttbar \\pt rew.",
            "ttbarScaleFSRPS":"\\ttbar FSR PS scale",
            "ttbarScaleISRPS":"\\ttbar ISR PS scale",
            "ttbarScaleME":"\\ttbar ME scale",
            "ttbarUE":"\\ttbar UE tune",
            "wjetsScaleME":"\\wjets ME scale",
            "tchanColor":"$t$-ch. color reconnection",
            "ttbarColor":"\\ttbar color reconnection",
            "bfrac":"b fragmentation",
            "lumi":"Luminosity"
        }
        
        sysResults = []
        
        totalInc = incStdProfiled**2
        totalRatio = ratioStdProfiled**2
        
        for isys,sys in enumerate(sorted(systematics)):
            results = {-1:{},1:{}}
            
            sysRatio = 0
            sysInc = 0
            
            
            if sys.find("tchanColor")>=0:
                for ccvar in ["tchanGluonMove","tchanErdOn","tchanGluonMoveErdOn"]:
                    sysFolder = self.module("Utils").getOutputFolder("unfolding/"+unfoldingName+"/"+unfoldingLevel+"/"+ccvar)
                    rootFile = ROOT.TFile(os.path.join(sysFolder,channelName+"_result.root"))
                    result = self.getResult(rootFile)
                    fitResultSys = self.getFitResult(channels,"inc",ccvar)
                    results[-1][ccvar]=result["nominalGen_neg"].Integral()/self.module("Samples").getLumi()
                    results[1][ccvar]=result["nominalGen_pos"].Integral()/self.module("Samples").getLumi()
                    
                    
                    if unfoldingLevel=="parton":
                        #disregard lepton selection
                        results[1][ccvar] = nominalXsecPos 
                        results[-1][ccvar] = nominalXsecNeg
                        
                    
                    meansSys = [
                        results[1][ccvar]*fitResultSys["parameters"]["tChannel_pos_binInc"]["mean_fit"],
                        results[-1][ccvar]*fitResultSys["parameters"]["tChannel_neg_binInc"]["mean_fit"]
                    ]
                    covarianceSys = [
                        [
                            results[1][ccvar]*results[1][ccvar]*fitResultSys["covariances"]["values"]["tChannel_pos_binInc"]["tChannel_pos_binInc"],
                            results[1][ccvar]*results[-1][ccvar]*fitResultSys["covariances"]["values"]["tChannel_pos_binInc"]["tChannel_neg_binInc"],
                        ],[
                            results[1][ccvar]*results[-1][ccvar]*fitResultSys["covariances"]["values"]["tChannel_pos_binInc"]["tChannel_neg_binInc"],
                            results[-1][ccvar]*results[-1][ccvar]*fitResultSys["covariances"]["values"]["tChannel_neg_binInc"]["tChannel_neg_binInc"]
                        ]
                    ]
                    correlationSys = covarianceSys[0][1]/math.sqrt(covarianceSys[0][0]*covarianceSys[1][1])
                    incMeanSys,incStdSys = self.calculate(lambda x: x[0]+x[1],meansSys,covarianceProfiled)
                    ratioMeanSys,ratioStdSys = self.calculate(lambda x: x[0]/x[1],meansSys,covarianceSys)
                    
                    print ccvar,incMeanSys,ratioMeanSys
                    
                    sysInc = max(sysInc,math.fabs(incMeanSys-incMeanProfiled))
                    sysRatio = max(sysRatio,math.fabs(ratioMeanSys-ratioMeanProfiled))
            elif sys.find("ttbarColor")>=0:
                for ccvar in ["ttbarGluonMove","ttbarErdOn","ttbarGluonMoveErdOn"]:
                    sysFolder = self.module("Utils").getOutputFolder("unfolding/"+unfoldingName+"/"+unfoldingLevel+"/"+ccvar)
                    rootFile = ROOT.TFile(os.path.join(sysFolder,channelName+"_result.root"))
                    result = self.getResult(rootFile)
                    fitResultSys = self.getFitResult(channels,"inc",ccvar)
                    results[-1][ccvar]=result["nominalGen_neg"].Integral()/self.module("Samples").getLumi()
                    results[1][ccvar]=result["nominalGen_pos"].Integral()/self.module("Samples").getLumi()
                    
                    
                    if unfoldingLevel=="parton":
                        #disregard lepton selection
                        results[1][ccvar] = nominalXsecPos 
                        results[-1][ccvar] = nominalXsecNeg
                        
                    
                    meansSys = [
                        results[1][ccvar]*fitResultSys["parameters"]["tChannel_pos_binInc"]["mean_fit"],
                        results[-1][ccvar]*fitResultSys["parameters"]["tChannel_neg_binInc"]["mean_fit"]
                    ]
                    covarianceSys = [
                        [
                            results[1][ccvar]*results[1][ccvar]*fitResultSys["covariances"]["values"]["tChannel_pos_binInc"]["tChannel_pos_binInc"],
                            results[1][ccvar]*results[-1][ccvar]*fitResultSys["covariances"]["values"]["tChannel_pos_binInc"]["tChannel_neg_binInc"],
                        ],[
                            results[1][ccvar]*results[-1][ccvar]*fitResultSys["covariances"]["values"]["tChannel_pos_binInc"]["tChannel_neg_binInc"],
                            results[-1][ccvar]*results[-1][ccvar]*fitResultSys["covariances"]["values"]["tChannel_neg_binInc"]["tChannel_neg_binInc"]
                        ]
                    ]
                    correlationSys = covarianceSys[0][1]/math.sqrt(covarianceSys[0][0]*covarianceSys[1][1])
                    incMeanSys,incStdSys = self.calculate(lambda x: x[0]+x[1],meansSys,covarianceProfiled)
                    ratioMeanSys,ratioStdSys = self.calculate(lambda x: x[0]/x[1],meansSys,covarianceSys)
                    
                    print ccvar,incMeanSys,ratioMeanSys
                    
                    sysInc = max(sysInc,math.fabs(incMeanSys-incMeanProfiled))
                    sysRatio = max(sysRatio,math.fabs(ratioMeanSys-ratioMeanProfiled))
                    
            elif sys.find("topMass")>=0:
                sysFolder = self.module("Utils").getOutputFolder("unfolding/"+unfoldingName+"/"+unfoldingLevel+"/"+sys+"Up")
                rootFile = ROOT.TFile(os.path.join(sysFolder,channelName+"_result.root"))
                result = self.getResult(rootFile)
                fitResultSys = self.getFitResult(channels,"inc",sys+"Up")
                results[-1]['Up']=result["nominalGen_neg"].Integral()/self.module("Samples").getLumi()
                results[1]['Up']=result["nominalGen_pos"].Integral()/self.module("Samples").getLumi()
                
                
                if unfoldingLevel=="parton":
                    #disregard lepton selection
                    results[1]['Up'] = nominalXsecPos 
                    results[-1]['Up'] = nominalXsecNeg
                    
                
                meansSys = [
                    results[1]['Up']*fitResultSys["parameters"]["tChannel_pos_binInc"]["mean_fit"],
                    results[-1]['Up']*fitResultSys["parameters"]["tChannel_neg_binInc"]["mean_fit"]
                ]
                covarianceSys = [
                    [
                        results[1]['Up']*results[1]['Up']*fitResultSys["covariances"]["values"]["tChannel_pos_binInc"]["tChannel_pos_binInc"],
                        results[1]['Up']*results[-1]['Up']*fitResultSys["covariances"]["values"]["tChannel_pos_binInc"]["tChannel_neg_binInc"],
                    ],[
                        results[1]['Up']*results[-1]['Up']*fitResultSys["covariances"]["values"]["tChannel_pos_binInc"]["tChannel_neg_binInc"],
                        results[-1]['Up']*results[-1]['Up']*fitResultSys["covariances"]["values"]["tChannel_neg_binInc"]["tChannel_neg_binInc"]
                    ]
                ]
                correlationSys = covarianceSys[0][1]/math.sqrt(covarianceSys[0][0]*covarianceSys[1][1])
                incMeanSys,incStdSys = self.calculate(lambda x: x[0]+x[1],meansSys,covarianceProfiled)
                ratioMeanSys,ratioStdSys = self.calculate(lambda x: x[0]/x[1],meansSys,covarianceSys)
                
                print sys+'Up',incMeanSys,ratioMeanSys
                
                sysInc = max(sysInc,math.fabs(incMeanSys-incMeanProfiled))
                sysRatio = max(sysRatio,math.fabs(ratioMeanSys-ratioMeanProfiled))
                
            else:
                for v in ["Up","Down"]:
                    sysFolder = self.module("Utils").getOutputFolder("unfolding/"+unfoldingName+"/"+unfoldingLevel+"/"+sys+v)
                    rootFile = ROOT.TFile(os.path.join(sysFolder,channelName+"_result.root"))
                    result = self.getResult(rootFile)
                    fitResultSys = self.getFitResult(channels,"inc",sys+v)
                    results[-1][v]=result["nominalGen_neg"].Integral()/self.module("Samples").getLumi()
                    results[1][v]=result["nominalGen_pos"].Integral()/self.module("Samples").getLumi()
                    
                    
                    if unfoldingLevel=="parton":
                        #disregard lepton selection
                        results[1][v] = nominalXsecPos 
                        results[-1][v] = nominalXsecNeg
                        
                    
                    meansSys = [
                        results[1][v]*fitResultSys["parameters"]["tChannel_pos_binInc"]["mean_fit"],
                        results[-1][v]*fitResultSys["parameters"]["tChannel_neg_binInc"]["mean_fit"]
                    ]
                    covarianceSys = [
                        [
                            results[1][v]*results[1][v]*fitResultSys["covariances"]["values"]["tChannel_pos_binInc"]["tChannel_pos_binInc"],
                            results[1][v]*results[-1][v]*fitResultSys["covariances"]["values"]["tChannel_pos_binInc"]["tChannel_neg_binInc"],
                        ],[
                            results[1][v]*results[-1][v]*fitResultSys["covariances"]["values"]["tChannel_pos_binInc"]["tChannel_neg_binInc"],
                            results[-1][v]*results[-1][v]*fitResultSys["covariances"]["values"]["tChannel_neg_binInc"]["tChannel_neg_binInc"]
                        ]
                    ]
                    correlationSys = covarianceSys[0][1]/math.sqrt(covarianceSys[0][0]*covarianceSys[1][1])
                    incMeanSys,incStdSys = self.calculate(lambda x: x[0]+x[1],meansSys,covarianceProfiled)
                    ratioMeanSys,ratioStdSys = self.calculate(lambda x: x[0]/x[1],meansSys,covarianceSys)
                    
                    print sys+v,incMeanSys,ratioMeanSys
                    
                    sysInc = max(sysInc,math.fabs(incMeanSys-incMeanProfiled))
                    sysRatio = max(sysRatio,math.fabs(ratioMeanSys-ratioMeanProfiled))
                    
                    
            totalInc+=sysInc**2
            totalRatio+=sysRatio**2
                
            f.write("%20s & $\\pm %5.1f$\\%% & $\\pm %5.3f$ \\\\\n"%(nameDict[sys],sysInc/incMeanProfiled*100.,sysRatio))
            
            #fitResultProfiled = self.getFitResult(channels,"inc","profiled")
        
        f.write("%20s & $\\pm%5.1f$\\%% & $\\pm%5.3f$ \\\\\n"%("Total",math.sqrt(totalInc)/incMeanProfiled*100.,math.sqrt(totalRatio)))
        f.close()

