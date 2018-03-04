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
        
   
        
    def execute(self):
        channels = self.getOption("channels").split(",")
        channelName = self.module("Samples").getChannelName(channels)
        plotName = self.getOption("plot").split(",")
    
        sets = {
            "tChannel": {
                "hists": ["tChannel_pos","tChannel_neg"],
                "fill":newColor(0.98,0.1,0.1),
                "title":"#it{t}-channel",
            },
            "TopBkg": {
                "hists":["TopBkg_pos","TopBkg_neg"],
                "fill":newColor(0.98,0.77,0.05),
                "title":"tt#lower[-0.87]{#kern[-0.89]{-}}/tW",
            },
            "WZjets": {
                "hists": ["WZjets_pos","WZjets_neg"],
                "fill":newColor(0.25,0.8,0.25),
                "title":"W/Z+jets",
            },
            "QCD": {
                "hists": ["QCD_"+plotName[0]+"_pos","QCD_"+plotName[0]+"_neg"],
                "fill":ROOT.gROOT.GetColor(ROOT.kGray),
                "title":"Multijet",
            },
        }
        for s in sets.keys():
            sets[s]["line"] = getDarkerColor(sets[s]["fill"])
        componentDict = {
            "tChannel_pos":["tChannel_pos"],
            "tChannel_neg":["tChannel_neg"],
            "TopBkg_pos":["TopBkg"],
            "TopBkg_neg":["TopBkg","TopBkg_ratio"],
            "WZjets_pos":["WZjets"],
            "WZjets_neg":["WZjets","WZjets_ratio"],
            "QCD_"+plotName[0]+"_pos":["QCD_"+plotName[0]],
            "QCD_"+plotName[0]+"_neg":["QCD_"+plotName[0],"QCD_"+plotName[0]+"_ratio"]
        }
        
    
    
        
        
        xtitle = ""
        ytitle = ""
        logy = 0
        norm = 0
        legendPos = "R"
        cut = ""
        for histSetup in self.module("Plots").getHistSetups("ele"): #only interested in xaxis title
            if histSetup["obsname"]==plotName[0] and histSetup["name"]==plotName[1]:
                xtitle = histSetup["xtitle"]
                ytitle = histSetup["ytitle"]
                logy = histSetup["logy"]
                norm = histSetup["normalize"]
                legendPos = histSetup["legendPos"]
                cut = histSetup["cut"]
        
        systematicsProfiled = [] if self.getOption("profiled")==None else self.getOption("profiled").split(",")
        systematicsExtern = [] if self.getOption("extern")==None else self.getOption("extern").split(",")
    
        unfoldingName = self.module("Unfolding").getUnfoldingName()
        if unfoldingName!="inc":
            self._logger.critical("Can only produce distributions inclusively")
            sys.exit(1)

        
        histogramsPerChannelComponentAndUncertainty = {}
        
        uncertainties = ["nominal"]
        for sysName in systematicsProfiled+systematicsExtern:
            uncertainties.append(sysName+"Up")
            uncertainties.append(sysName+"Down")
        
        stackList = ["QCD","WZjets","TopBkg","tChannel"]
        
        fitOutput = os.path.join(
            self.module("Utils").getOutputFolder("fit/profiled"),
            self.module("ThetaModel").getFitFileName(channels,unfoldingName,"profiled")
        )
        fitResult = self.module("ThetaFit").loadFitResult(fitOutput+".json")
        
        for channel in channels:
            histogramsPerChannelComponentAndUncertainty[channel] = {}
            for uncertainty in uncertainties:
                
                histFilePath = self.module("Utils").getHistogramFile(
                    plotName[1],
                    channel,
                    unfoldingName,
                    -1,
                    uncertainty
                )
                rootFile = ROOT.TFile(histFilePath)
                if (not rootFile):
                    self._logger.critical("File '"+histFilePath+"' not found")
                    sys.exit(1)
                for compName in componentDict.keys():
                    histName = self.module("ThetaModel").getHistogramName(
                        plotName[0],
                        compName,
                        unfoldingName,
                        -1,
                        uncertainty
                    )
                    hist = rootFile.Get(histName)
                    if (not hist):
                        self._logger.critical("Histogram '"+histName+"' not found in file '"+histFilePath+"'")
                        sys.exit(1)
                        
                    hist = hist.Clone(hist.GetName()+str(random.random()))
                    
                    #normalize the histograms of these uncertainties to their nominal value
                    if uncertainty in ["eleMultiIso","eleMultiVeto","muMulti","tw","dy"]:
                        hist.Scale(histogramsPerChannelComponentAndUncertainty[channel][compName]["nominal"].Integral()/hist.Integral())
                    
                    for sfName in componentDict[compName]:
                        sfName+="_binInc"
                        if compName.find("QCD")>=0:
                            sfName+="_"+channel
                        sfValue = fitResult["parameters"][sfName]["mean_fit"]
                        hist.Scale(sfValue)
                    if not histogramsPerChannelComponentAndUncertainty[channel].has_key(compName):
                        histogramsPerChannelComponentAndUncertainty[channel][compName] = {uncertainty: hist}
                        histogramsPerChannelComponentAndUncertainty[channel][compName][uncertainty].SetDirectory(0)  
                    else:
                        histogramsPerChannelComponentAndUncertainty[channel][compName][uncertainty].Add(hist)
                rootFile.Close()
                
            histFilePath = self.module("Utils").getHistogramFile(
                plotName[1],
                channel,
                unfoldingName,
                -1,
                "nominal"
            )
            rootFile = ROOT.TFile(histFilePath)
            if (not rootFile):
                self._logger.critical("File '"+histFilePath+"' not found")
                sys.exit(1)

            histName = self.module("ThetaModel").getHistogramName(
                plotName[0],
                "data",
                unfoldingName,
                -1,
                ""
            )
            hist = rootFile.Get(histName)
            if (not hist):
                self._logger.critical("Histogram '"+histName+"' not found in file '"+histFilePath+"'")
                sys.exit(1)
                
            hist = hist.Clone(hist.GetName()+str(random.random()))
            if not histogramsPerChannelComponentAndUncertainty[channel].has_key("data"):
                histogramsPerChannelComponentAndUncertainty[channel]["data"] =  hist
                histogramsPerChannelComponentAndUncertainty[channel]["data"].SetDirectory(0)  
            else:
                histogramsPerChannelComponentAndUncertainty[channel]["data"].Add(hist)
                

                
        cv = ROOT.TCanvas("cv","",800,700)
        stack = []
        
        for stackName in stackList:
        
            
            
            histSum = None
            for channel in channels:
                for compName in sets[stackName]["hists"]:
                    if histSum == None:
                        histSum = histogramsPerChannelComponentAndUncertainty[channel][compName]["nominal"].Clone(
                            histogramsPerChannelComponentAndUncertainty[channel][compName]["nominal"].GetName()+"sum"
                        )
                    else:
                        histSum.Add(histogramsPerChannelComponentAndUncertainty[channel][compName]["nominal"])
            histSum.SetFillColor(sets[stackName]["fill"].GetNumber())
            histSum.SetLineWidth(2)
            histSum.SetLineColor(sets[stackName]["line"].GetNumber())
            if norm:
                self.module("Utils").normalizeByBinWidth(histSum)
            stack.append({
                "hist":histSum,
                "title":sets[stackName]["title"]
            })
        totalMCSum = stack[0]["hist"].Clone(stack[0]["hist"].GetName()+"mcsum")
        for i in range(1,len(stack)):
            totalMCSum.Add(stack[i]["hist"])
            
        dataSum = None
        for channel in channels:
            if dataSum==None:
                dataSum = histogramsPerChannelComponentAndUncertainty[channel]["data"].Clone(
                    histogramsPerChannelComponentAndUncertainty[channel]["data"].GetName()+"sum"
                )
            else:
                dataSum.Add(histogramsPerChannelComponentAndUncertainty[channel]["data"])
        if norm:
            self.module("Utils").normalizeByBinWidth(dataSum)
            

        ymin = 1000000000
        for ibin in range(dataSum.GetNbinsX()):
            c = dataSum.GetBinContent(ibin+1)
            if c>0:
                ymin = min(ymin,c)
        ymax = max([totalMCSum.GetMaximum(),dataSum.GetMaximum()])
                   
        if logy:
            ymin = math.exp((1-0.4*numpy.sign(ymin-1))*math.log10(ymin))
            ymax = math.exp(0.3*(math.log(ymax)-math.log(ymin))+math.log(ymax))
        else:
            ymax = 1.3*ymax
            ymin = 0
            
        self.module("Utils").createFolder("dists/"+channelName)
        finalFolder = self.module("Utils").getOutputFolder("dists/"+channelName)
            
        lumi = "e/#mu#kern[-0.2]{ }+#kern[-0.2]{ }2#kern[-0.5]{ }jets#kern[-0.3]{ }1#kern[-0.5]{ }b-tag, 36#kern[-0.5]{ }fb#lower[-0.7]{#scale[0.7]{-1}} (13TeV)"
        self.module("Drawing").plotDistribution(
            stack,dataSum,ymin,ymax,logy,ytitle,xtitle,cut,legendPos,lumi,
            os.path.join(finalFolder,plotName[1])
        )
            
                
                
            


