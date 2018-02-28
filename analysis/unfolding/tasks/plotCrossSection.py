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

class PlotCrossSection(Module.getClass("Program")):
    def __init__(self,options=[]):
        Module.__init__(self,options)
        self._logger = logging.getLogger(__file__)
        self._logger.setLevel(logging.DEBUG)
        
    def getResult(self,f):
        result = {}
        for charge in [-1,1]:
            for h in [
                ["nominalReco_"+self.module("Samples").getChargeName(charge)],
                ["measuredReco_"+self.module("Samples").getChargeName(charge)],
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
            ["nominalGen_"+self.module("Samples").getChargeName(0)],
            ["unfolded_"+self.module("Samples").getChargeName(0)],
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
        
    def execute(self):
        unfoldingName = self.module("Unfolding").getUnfoldingName()
        channels = self.getOption("channels").split(",")
        channelName = self.module("Samples").getChannelName(channels)
        unfoldingLevel = self.module("Unfolding").getUnfoldingLevel()
        
        systematics = [] if self.getOption("systematics")==None else self.getOption("systematics").split(",")
        NSYS = len(systematics)
    
    
        self.module("Utils").createFolder("plots/"+unfoldingName+"/"+unfoldingLevel)
        outputFolder = self.module("Utils").getOutputFolder("plots/"+unfoldingName+"/"+unfoldingLevel)
        
        profiledFolder = self.module("Utils").getOutputFolder("unfolding/"+unfoldingName+"/"+unfoldingLevel+"/profiled")
        rootFileProfiled = ROOT.TFile(os.path.join(profiledFolder,channelName+"_result.root"))
        profiledResult = self.getResult(rootFileProfiled)
        rootFileProfiled.Close()
        
        nominalFolder = self.module("Utils").getOutputFolder("unfolding/"+unfoldingName+"/"+unfoldingLevel+"/nominal")
        rootFileNominal = ROOT.TFile(os.path.join(nominalFolder,channelName+"_result.root"))
        nominalResult = self.getResult(rootFileNominal)
        rootFileNominal.Close()
        
        
        xtitle = self.module("Unfolding").getUnfoldingLevel().capitalize()+" "+self.module("Unfolding").getUnfoldingVariableName()
        ytitleSum = "d#kern[-0.5]{ }#sigma#kern[-0.5]{ }#lower[0.2]{#scale[1.3]{#/}}#kern[-2]{ }d#kern[-0.5]{ }"+self.module("Unfolding").getUnfoldingSymbol()+""
        ytitleRatio = "d#kern[-0.5]{ }(#sigma#lower[0.3]{#scale[0.8]{#kern[-0.5]{ }t}}#kern[-0.5]{ }/#sigma#lower[0.3]{#scale[0.8]{#kern[-0.5]{ }t+#bar{t}}}#kern[-0.5]{ })#kern[-0.5]{ }#lower[0.2]{#scale[1.3]{#/}}#kern[-2]{ }d#kern[-0.5]{ }"+self.module("Unfolding").getUnfoldingSymbol()+""
        unit = self.module("Unfolding").getUnfoldingVariableUnit()
        logy = unfoldingName=="pt" or unfoldingName=="lpt" or unfoldingName=="wpt"
        if unit!="":
            xtitle += " ("+unit+")"
            ytitleSum += " (pb#kern[-0.5]{ }/#kern[-0.5]{ }"+unit+")"
            ytitleRatio += " (1#kern[-0.5]{ }/#kern[-0.5]{ }"+unit+")"
        else:
            ytitleSum += " (pb)"
        
        sysResults = []
        for isys,sys in enumerate(sorted(systematics)):
            results = {-1:{},1:{}}
            
            for v in ["Up","Down"]:
                sysFolder = self.module("Utils").getOutputFolder("unfolding/"+unfoldingName+"/"+unfoldingLevel+"/"+sys+v)
                rootFile = ROOT.TFile(os.path.join(sysFolder,channelName+"_result.root"))
                result = self.getResult(rootFile)
                results[-1][v]=result["unfolded_neg"]
                results[1][v]=result["unfolded_pos"]
            sysResults.append(results)
            
            self.module("Drawing").plotEnvelopeHistogram(
                nominalResult["nominalGen_pos"],nominalResult["unfolded_pos"],results[1]["Up"],results[1]["Down"],
                os.path.join(outputFolder,self.module("Samples").getChannelName(channels)+"_pos_"+sys),
                title=self.module("Samples").getPlotTitle(channels,1)+"#kern[-0.5]{ }+#kern[-0.5]{ }jets",
                xaxis=xtitle,yaxis=ytitleSum,logy=logy,
                normalizeByCrossSection=True
            )
            
            
            self.module("Drawing").plotEnvelopeHistogram(
                nominalResult["nominalGen_neg"],nominalResult["unfolded_neg"],results[-1]["Up"],results[-1]["Down"],
                os.path.join(outputFolder,self.module("Samples").getChannelName(channels)+"_neg_"+sys),
                title=self.module("Samples").getPlotTitle(channels,-1)+"#kern[-0.5]{ }+#kern[-0.5]{ }jets",
                xaxis=xtitle,yaxis=ytitleSum,logy=logy,
                normalizeByCrossSection=True
            )
            
        
        genBinning = self.module("Unfolding").getGenBinning(channelName)
        
        #this is a reflection of the stat uncertainty only
        histSumNominal = self.module("Unfolding").calculateSum(
            nominalResult["unfolded_pos"],
            nominalResult["unfolded_neg"],
            nominalResult["covarianceUnfolded"]
        )
        #this includes also the profiled exp. systematics
        histSumProfiled = self.module("Unfolding").calculateSum(
            profiledResult["unfolded_pos"],
            profiledResult["unfolded_neg"],
            profiledResult["covarianceUnfolded"]
        )
        #this is the envelope of all systematics
        histSumTotal = self.module("Unfolding").calculateSum(
            profiledResult["unfolded_pos"],
            profiledResult["unfolded_neg"],
            profiledResult["covarianceUnfolded"],
            {1:nominalResult["unfolded_pos"],-1:nominalResult["unfolded_neg"]},
            sysResults
        )
        
        #TODO: add lumi uncertainty!!!!!!
        
        #this is a reflection of the stat uncertainty only
        histRatioNominal = self.module("Unfolding").calculateRatio(
            nominalResult["unfolded_pos"],
            nominalResult["unfolded_neg"],
            nominalResult["covarianceUnfolded"]
        )
        #this includes also the profiled exp. systematics
        histRatioProfiled = self.module("Unfolding").calculateRatio(
            profiledResult["unfolded_pos"],
            profiledResult["unfolded_neg"],
            profiledResult["covarianceUnfolded"]
        )
        #this is the envelope of all systematics
        histRatioTotal = self.module("Unfolding").calculateRatio(
            profiledResult["unfolded_pos"],
            profiledResult["unfolded_neg"],
            profiledResult["covarianceUnfolded"],
            {1:nominalResult["unfolded_pos"],-1:nominalResult["unfolded_neg"]},
            sysResults
        )
        
        self.module("Drawing").plotCompareHistogram(nominalResult["nominalGen_inc"],
            [histSumNominal,histSumProfiled,histSumTotal],
            os.path.join(outputFolder,self.module("Samples").getChannelName(channels)+"_"+self.module("Samples").getChargeName(0)+"_compareHist"),
            title=self.module("Samples").getPlotTitle(channels,0)+"#kern[-0.5]{ }+#kern[-0.5]{ }jets",xaxis=xtitle,yaxis=ytitleSum,logy=unfoldingName=="pt" or unfoldingName=="lpt" or unfoldingName=="wpt",normalizeByCrossSection=True
        ) 
        
        self.module("Utils").normalizeByCrossSection(histSumProfiled)
        self.module("Utils").normalizeByCrossSection(histSumTotal)
        genHistSum = nominalResult["nominalGen_inc"]
        self.module("Utils").normalizeByCrossSection(genHistSum)
        genHistRatio = nominalResult["ratioGen"]
        
        
        
        
        
        histSumProfiled.SetMarkerStyle(20)
        histSumProfiled.SetLineWidth(2)
        histSumProfiled.SetMarkerSize(1.)
        
        histSumTotal.SetMarkerStyle(20)
        histSumTotal.SetLineWidth(1)
        histSumTotal.SetLineColor(ROOT.kBlack)
        histSumTotal.SetMarkerColor(ROOT.kBlack)
        histSumTotal.SetMarkerSize(1.2)
        
        genHistSum.SetLineColor(ROOT.kOrange+7)
        genHistSum.SetLineWidth(2)
        
        
        
        histRatioProfiled.SetMarkerStyle(20)
        histRatioProfiled.SetLineWidth(2)
        histRatioProfiled.SetMarkerSize(1.)
        
        histRatioTotal.SetMarkerStyle(20)
        histRatioTotal.SetLineWidth(1)
        histRatioTotal.SetLineColor(ROOT.kBlack)
        histRatioTotal.SetMarkerColor(ROOT.kBlack)
        histRatioTotal.SetMarkerSize(1.2)
        
        genHistRatio.SetLineColor(ROOT.kOrange+7)
        genHistRatio.SetLineWidth(2)
        
        
        ymin = 100000
        ymax = -10000
        for ibin in range(histSumTotal.GetNbinsX()):
            ymin = min(ymin,histSumTotal.GetBinContent(ibin+1)-histSumTotal.GetBinError(ibin+1))
            ymax = max(ymax,histSumTotal.GetBinContent(ibin+1)+histSumTotal.GetBinError(ibin+1))
            
        if logy:
            ymin = 10**math.floor(math.log10(0.7*ymin))
            ymax = math.exp(0.15*(math.log(ymax)-math.log(ymin))+math.log(ymax))
        else:
            ymax = 1.1*ymax
            ymin = 0
        
        resRanges = [0.46,1.]
        
        resRange = resRanges[-1]
        rangeMax = 0
        for ibin in range(histSumTotal.GetNbinsX()):
            c = histSumTotal.GetBinContent(ibin+1)
            e = histSumTotal.GetBinError(ibin+1)
            rangeMax = max(rangeMax,e/c)
        for r in resRanges:
            if rangeMax<r:
                resRange = r
                break
        
            
            
            
        if unfoldingName=="lpt":
            legendPos = "RU"
        elif unfoldingName=="cos":
            legendPos = "LU"
        else:
            legendPos = "LD"
            
            
        self.module("Utils").createFolder("final/"+channelName)
        finalFolder = self.module("Utils").getOutputFolder("final/"+channelName)

        
        self.module("Drawing").plotCrossSection(
            genHistSum,histSumProfiled,histSumTotal,ymin,ymax,logy,ytitleSum,xtitle,
            self.module("Samples").getPlotTitle(channels,0)+"#kern[-0.5]{ }+#kern[-0.5]{ }jets, 36#kern[-0.5]{ }fb#lower[-0.7]{#scale[0.7]{-1}} (13TeV)",
            legendPos,resRange,
            os.path.join(finalFolder,unfoldingName+"_"+unfoldingLevel+"_"+channelName+"_sum")
        )   
        
        self.module("Drawing").plotCrossSection(
            genHistRatio,histRatioProfiled,histRatioTotal,0.2,1.,0,ytitleRatio,xtitle,
            self.module("Samples").getPlotTitle(channels,0)+"#kern[-0.5]{ }+#kern[-0.5]{ }jets, 36#kern[-0.5]{ }fb#lower[-0.7]{#scale[0.7]{-1}} (13TeV)",
            "LD",0.48,
            os.path.join(finalFolder,unfoldingName+"_"+unfoldingLevel+"_"+channelName+"_ratio")
        )    
 




