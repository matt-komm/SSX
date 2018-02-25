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
        ytitleRatio = "d#kern[-0.5]{ }(#sigma#lower[0.3]{#scale[0.8]{#kern[-0.5]{ }t}}#kern[-0.5]{ }/#sigma#lower[0.3]{#scale[0.8]{#kern[-0.5]{ }t+#bar{t}}}#kern[-0.5]{ })#kern[-0.5]{ }#lower[0.2]{#scale[1.3]{#/}}#kern[-2]{ }d#kern[-0.5]{ }"+self.module("Unfolding").getUnfoldingVariableName()+""
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
        
        self.module("Drawing").plotCompareHistogram(nominalResult["nominalGen_inc"],
            [histSumNominal,histSumProfiled,histSumTotal],
            os.path.join(outputFolder,self.module("Samples").getChannelName(channels)+"_"+self.module("Samples").getChargeName(0)+"_compareHist"),
            title=self.module("Samples").getPlotTitle(channels,0)+"#kern[-0.5]{ }+#kern[-0.5]{ }jets",xaxis=xtitle,yaxis=ytitleSum,logy=unfoldingName=="pt" or unfoldingName=="lpt" or unfoldingName=="wpt",normalizeByCrossSection=True
        ) 
        
        self.module("Utils").normalizeByCrossSection(histSumProfiled)
        self.module("Utils").normalizeByCrossSection(histSumTotal)
        genHistSum = nominalResult["nominalGen_inc"]
        self.module("Utils").normalizeByCrossSection(genHistSum)
        
        
        
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
        
        
        ROOT.gStyle.SetPaperSize(8.0*1.35*cvscale,7.5*1.35*cvscale)
        ROOT.TGaxis.SetMaxDigits(3)
        ROOT.gStyle.SetLineScalePS(2)
        
        cv = ROOT.TCanvas("cvSum"+str(random.random()),"",800,750)
        cv.Divide(1,2,0,0)
        cv.GetPad(1).SetPad(0.0, 0.0, 1.0, 1.0)
        cv.GetPad(1).SetFillStyle(4000)
        cv.GetPad(2).SetPad(0.0, 0.00, 1.0,1.0)
        cv.GetPad(2).SetFillStyle(4000)
        
        cvxmin=0.14
        cvxmax=0.96
        cvymin=0.13
        cvymax=0.93
        resHeight=0.37
        
        rootObj =[]
        for i in range(1,3):
            #for the canvas:
            cv.GetPad(i).SetBorderMode(0)
            cv.GetPad(i).SetGridx(False)
            cv.GetPad(i).SetGridy(False)


            #For the frame:
            cv.GetPad(i).SetFrameBorderMode(0)
            cv.GetPad(i).SetFrameBorderSize(1)
            cv.GetPad(i).SetFrameFillColor(0)
            cv.GetPad(i).SetFrameFillStyle(0)
            cv.GetPad(i).SetFrameLineColor(1)
            cv.GetPad(i).SetFrameLineStyle(1)
            cv.GetPad(i).SetFrameLineWidth(int(1*cvscale))

            # Margins:
            cv.GetPad(i).SetLeftMargin(cvxmin)
            cv.GetPad(i).SetRightMargin(1-cvxmax)
            
            # For the Global title:
            cv.GetPad(i).SetTitle("")
            
            # For the axis:
            cv.GetPad(i).SetTickx(1)  # To get tick marks on the opposite side of the frame
            cv.GetPad(i).SetTicky(1)

            # Change for log plots:
            cv.GetPad(i).SetLogx(0)
            cv.GetPad(i).SetLogy(0)
            cv.GetPad(i).SetLogz(0)
        
        
        
        cv.GetPad(2).SetTopMargin(1-cvymax)
        cv.GetPad(2).SetBottomMargin(resHeight)
        cv.GetPad(1).SetTopMargin(1-resHeight)
        cv.GetPad(1).SetBottomMargin(cvymin)
        
        cv.GetPad(2).SetLogy(logy)
        
        cv.cd(2)
        
        ymin = 100000
        ymax = -10000
        for ibin in range(histSumTotal.GetNbinsX()):
            ymin = min(ymin,histSumTotal.GetBinContent(ibin+1)-histSumTotal.GetBinError(ibin+1))
            ymax = max(ymax,histSumTotal.GetBinContent(ibin+1)+histSumTotal.GetBinError(ibin+1))
            
        if logy:
            ymin = 0.7*ymin
            ymax = math.log(1.35*math.exp(ymax+1))-1.
        else:
            ymax = 1.1*ymax
            ymin = 0
        
        axis = ROOT.TH2F("axis"+str(random.random()),";;",
            50,genBinning[0],genBinning[-1],
            50,ymin,ymax
        )
        axis.GetXaxis().SetTitle("")
        axis.GetYaxis().SetTitle(ytitleSum)
        axis.GetXaxis().SetTickLength(0.015/(1-cv.GetPad(2).GetLeftMargin()-cv.GetPad(2).GetRightMargin()))
        axis.GetYaxis().SetTickLength(0.015/(1-cv.GetPad(2).GetTopMargin()-cv.GetPad(2).GetBottomMargin()))
        axis.GetXaxis().SetLabelFont(43)
        axis.GetXaxis().SetLabelSize(0)
        axis.GetYaxis().SetLabelFont(43)
        axis.GetYaxis().SetLabelSize(34)
        axis.GetXaxis().SetTitleFont(43)
        axis.GetXaxis().SetTitleSize(38)
        axis.GetYaxis().SetTitleFont(43)
        axis.GetYaxis().SetTitleSize(38)
        axis.GetYaxis().SetNoExponent(True)
        axis.GetYaxis().SetTitleOffset(1.4)
        axis.Draw("AXIS")
        
        genHistSum.Draw("HISTSAME")
        histSumTotal.Draw("PESAME")
        for ibin in range(histSumTotal.GetNbinsX()):
            c = histSumTotal.GetBinCenter(ibin+1)
            w = (genBinning[-1]-genBinning[0])*0.012
            n = histSumTotal.GetBinContent(ibin+1)
            rel_sys = histSumProfiled.GetBinError(ibin+1)/histSumProfiled.GetBinContent(ibin+1)
            u = (1.+rel_sys)*n
            d = (1.-rel_sys)*n
            lineUp = ROOT.TLine(c-w,u,c+w,u)
            rootObj.append(lineUp)
            lineUp.SetLineColor(ROOT.kBlack)
            lineUp.SetLineWidth(1)
            lineUp.Draw("SameL")
            lineDown = ROOT.TLine(c-w,d,c+w,d)
            rootObj.append(lineDown)
            lineDown.SetLineColor(ROOT.kBlack)
            lineDown.SetLineWidth(1)
            lineDown.Draw("SameL")
            
            
        #histSumProfiled.Draw("PESAME")
        
        pCMS=ROOT.TPaveText(cvxmin,0.95,cvxmin,0.95,"NDC")
        pCMS.SetFillColor(ROOT.kWhite)
        pCMS.SetBorderSize(0)
        pCMS.SetTextFont(63)
        pCMS.SetTextSize(39)
        pCMS.SetTextAlign(11)
        pCMS.AddText("CMS")
        pCMS.Draw("Same")
        '''
        pPreliminary=ROOT.TPaveText(cvxmin+0.025+0.1,cvymax-0.065,cvxmin+0.025+0.1,cvymax-0.065,"NDC")
        pPreliminary.SetFillColor(ROOT.kWhite)
        pPreliminary.SetBorderSize(0)
        pPreliminary.SetTextFont(53)
        pPreliminary.SetTextSize(35)
        pPreliminary.SetTextAlign(11)
        pPreliminary.AddText("Preliminary")
        pPreliminary.Draw("Same")
        '''
        pLumi=ROOT.TPaveText(cvxmax,0.95,cvxmax,0.95,"NDC")
        pLumi.SetFillColor(ROOT.kWhite)
        pLumi.SetBorderSize(0)
        pLumi.SetTextFont(43)
        pLumi.SetTextSize(39)
        pLumi.SetTextAlign(31)
        pLumi.AddText(self.module("Samples").getPlotTitle(channels,0)+"#kern[-0.5]{ }+#kern[-0.5]{ }jets, 36#kern[-0.5]{ }fb#lower[-0.7]{#scale[0.7]{-1}} (13TeV)")
        pLumi.Draw("Same")
        
        if unfoldingName=="lpt":
            legend = ROOT.TLegend(0.54,cvymax-0.02,cvxmax-0.13,cvymax-0.02-0.067*2)
        elif unfoldingName=="cos":
            legend = ROOT.TLegend(cvxmin+0.02,cvymax-0.02,cvxmin+0.35,cvymax-0.02-0.067*2)
        else:
            legend = ROOT.TLegend(cvxmin+0.02,resHeight+0.03,cvxmin+0.35,resHeight+0.03+0.067*2)
        #legend = ROOT.TLegend(0.54,resHeight+0.03,cvxmax-0.13,resHeight+0.03+0.067*2)
        legend.SetFillColor(0)
        legend.SetFillStyle(0)
        legend.SetBorderSize(0)
        legend.SetTextFont(43)
        legend.SetTextSize(33)
        legend.AddEntry(histSumTotal,"Data","PE")
        legend.AddEntry(genHistSum,"POWHEG#kern[-0.5]{ }+#kern[-0.5]{ }Pythia#kern[-0.6]{ }8","L")
        legend.Draw("Same")
        
        cv.cd(1)
        if unfoldingName=="pt" or unfoldingName=="cos":
            resRange = 1.
        else:
            resRange = 0.48
        axisRes=ROOT.TH2F("axisRes"+str(random.random()),";;Pred./Data",50,genBinning[0],genBinning[-1],50,1-resRange,1+resRange)
        axisRes.GetYaxis().SetNdivisions(406)
        axisRes.GetXaxis().SetTitle(xtitle)
        axisRes.GetXaxis().SetTickLength(0.017/(1-cv.GetPad(1).GetLeftMargin()-cv.GetPad(1).GetRightMargin()))
        axisRes.GetYaxis().SetTickLength(0.015/(1-cv.GetPad(1).GetTopMargin()-cv.GetPad(1).GetBottomMargin()))
        axisRes.GetXaxis().SetLabelFont(43)
        axisRes.GetXaxis().SetLabelSize(34)
        axisRes.GetYaxis().SetLabelFont(43)
        axisRes.GetYaxis().SetLabelSize(34)
        axisRes.GetXaxis().SetTitleFont(43)
        axisRes.GetXaxis().SetTitleSize(38)
        axisRes.GetYaxis().SetTitleFont(43)
        axisRes.GetYaxis().SetTitleSize(38)
        axisRes.GetYaxis().SetNoExponent(True)
        axisRes.GetYaxis().SetTitleOffset(1.4)
        axisRes.Draw("AXIS")
        
        
        axisLine = ROOT.TF1("axisLine"+str(random.random()),"1",genBinning[0],genBinning[-1])
        axisLine.SetLineColor(ROOT.kBlack)
        axisLine.SetLineWidth(1)
        axisLine.Draw("SameL")
        
        histSumTotalRes = histSumTotal.Clone(histSumTotal.GetName()+"res")
        histSumProfiledRes = histSumProfiled.Clone(histSumProfiled.GetName()+"res")
        genHistSumRes = genHistSum.Clone(genHistSum.GetName()+"res")
        
        for ibin in range(histSumTotal.GetNbinsX()):
            histSumTotalRes.SetBinContent(ibin+1,
                histSumTotal.GetBinContent(ibin+1)/histSumTotal.GetBinContent(ibin+1)
            )
            histSumTotalRes.SetBinError(ibin+1,
                histSumTotal.GetBinError(ibin+1)/histSumTotal.GetBinContent(ibin+1)
            )
            histSumProfiledRes.SetBinContent(ibin+1,
                histSumProfiled.GetBinContent(ibin+1)/histSumTotal.GetBinContent(ibin+1)
            )
            histSumProfiledRes.SetBinError(ibin+1,
                histSumProfiled.GetBinError(ibin+1)/histSumTotal.GetBinContent(ibin+1)
            )
            genHistSumRes.SetBinContent(ibin+1,
                genHistSum.GetBinContent(ibin+1)/histSumTotal.GetBinContent(ibin+1)
            )
            genHistSumRes.SetBinError(ibin+1,
                genHistSum.GetBinError(ibin+1)/histSumTotal.GetBinContent(ibin+1)
            )
            
            
        genHistSumRes.Draw("HISTSame")
        histSumTotalRes.Draw("PLSame")
        for ibin in range(histSumTotal.GetNbinsX()):
            c = histSumTotalRes.GetBinCenter(ibin+1)
            w = (genBinning[-1]-genBinning[0])*0.012
            n = histSumTotalRes.GetBinContent(ibin+1)
            rel_sys = histSumProfiledRes.GetBinError(ibin+1)/histSumProfiledRes.GetBinContent(ibin+1)
            u = (1.+rel_sys)*n
            d = (1.-rel_sys)*n
            lineUp = ROOT.TLine(c-w,u,c+w,u)
            rootObj.append(lineUp)
            lineUp.SetLineColor(ROOT.kBlack)
            lineUp.SetLineWidth(1)
            lineUp.Draw("SameL")
            lineDown = ROOT.TLine(c-w,d,c+w,d)
            rootObj.append(lineDown)
            lineDown.SetLineColor(ROOT.kBlack)
            lineDown.SetLineWidth(1)
            lineDown.Draw("SameL")
        
        
        
        ROOT.gPad.RedrawAxis()
        

        hidePave=ROOT.TPaveText(cvxmin-0.065,resHeight-0.035,cvxmin-0.005,resHeight+0.028,"NDC")
        hidePave.SetFillColor(ROOT.kWhite)
        hidePave.SetFillStyle(1001)
        hidePave.Draw("Same")
        
        
        cv.Print(os.path.join(outputFolder,unfoldingName+"_"+unfoldingLevel+"_"+channelName+"_sum.pdf"))
        
        '''
        if logy:
            axis=ROOT.TH2F("axis"+str(random.random()),";"+variableTitle+";Events / bin",50,binarray[0],binarray[-1],50,math.exp(0.85*math.log(min([sumHistMC.GetMinimum(0.5),sumHistData.GetMinimum(0.5)]))),math.exp(1.43*math.log(max([sumHistMC.GetMaximum(),sumHistData.GetMaximum(),1.0]))))
        else:
            axis=ROOT.TH2F("axis"+str(random.random()),";"+variableTitle+";Events / bin",50,binarray[0],binarray[-1],50,0.0,1.43*max([sumHistMC.GetMaximum(),sumHistData.GetMaximum(),1.0]))


        axis.GetXaxis().SetLabelSize(0)
        axis.GetXaxis().SetTitle("")
        axis.GetXaxis().SetTickLength(0.015/(1-cv.GetPad(2).GetLeftMargin()-cv.GetPad(2).GetRightMargin()))
        axis.GetYaxis().SetTickLength(0.015/(1-cv.GetPad(2).GetTopMargin()-cv.GetPad(2).GetBottomMargin()))
        #axis.GetYaxis().SetNoExponent(True)
        axis.Draw("AXIS")
        
        
        if logy:
            cv.GetPad(2).SetLogy(1)
        if logx:
            cv.GetPad(2).SetLogx(1)
            cv.GetPad(1).SetLogx(1)
        ROOT.gStyle.SetLineWidth(int(1*cvscale))
        ROOT.gPad.RedrawAxis()
        
        legend = ROOT.TLegend(0.745,cvymax,0.99,cvymax-0.08*len(legendEntries))
       
        legend.SetFillColor(ROOT.kWhite)
        legend.SetBorderSize(0)
        legend.SetTextFont(43)
        legend.SetTextSize(34*cvscale)
        
        for entry in reversed(legendEntries):
            legend.AddEntry(entry[0],entry[1],entry[2])
        
        
        pCMS=ROOT.TPaveText(cvxmin+0.025,cvymax-0.065,cvxmin+0.025,cvymax-0.065,"NDC")
        pCMS.SetFillColor(ROOT.kWhite)
        pCMS.SetBorderSize(0)
        pCMS.SetTextFont(63)
        pCMS.SetTextSize(32*cvscale)
        pCMS.SetTextAlign(11)
        pCMS.AddText("CMS")
        pCMS.Draw("Same")
        
        pPreliminary=ROOT.TPaveText(cvxmin+0.025+0.1,cvymax-0.065,cvxmin+0.025+0.1,cvymax-0.065,"NDC")
        pPreliminary.SetFillColor(ROOT.kWhite)
        pPreliminary.SetBorderSize(0)
        pPreliminary.SetTextFont(53)
        pPreliminary.SetTextSize(32*cvscale)
        pPreliminary.SetTextAlign(11)
        pPreliminary.AddText("Preliminary")
        pPreliminary.Draw("Same")
    
        
        pCut=ROOT.TPaveText(cvxmin+0.025,cvymax-0.06-0.07,cvxmin+0.025,cvymax-0.06-0.07,"NDC")
        pCut.SetFillStyle(0)
        pCut.SetBorderSize(0)
        pCut.SetTextFont(43)
        pCut.SetTextSize(32*cvscale)
        pCut.SetTextAlign(11)
        pCut.AddText(qcd[2])
        pCut.Draw("Same")
        
        
        pLumi=ROOT.TPaveText(cvxmax,0.94,cvxmax,0.94,"NDC")
        pLumi.SetFillColor(ROOT.kWhite)
        pLumi.SetBorderSize(0)
        pLumi.SetTextFont(43)
        pLumi.SetTextSize(34)
        pLumi.SetTextAlign(31)
        pLumi.AddText(channelInfo["label"]+"#kern[-0.5]{ }+#kern[-0.5]{ }"+category[1]+", 36#kern[-0.5]{ }fb#lower[-0.7]{#scale[0.7]{-1}} (13TeV)")
        pLumi.Draw("Same")
        
       
        cv.cd(1)
        axisRes=None
        if unit!="":
            axisRes=ROOT.TH2F("axisRes"+str(random.random()),";"+variableTitle+" ("+unit+");Data/MC",50,binarray[0],binarray[-1],50,0.6,1.4)
        else:
            axisRes=ROOT.TH2F("axisRes"+str(random.random()),";"+variableTitle+";Data/MC",50,binarray[0],binarray[-1],50,0.6,1.4)
        axisRes.GetYaxis().SetNdivisions(406)
        axisRes.GetXaxis().SetTickLength(0.025/(1-cv.GetPad(1).GetLeftMargin()-cv.GetPad(1).GetRightMargin()))
        axisRes.GetYaxis().SetTickLength(0.015/(1-cv.GetPad(1).GetTopMargin()-cv.GetPad(1).GetBottomMargin()))

        axisRes.Draw("AXIS")
        
        rootObj=[]
        
        for ibin in range(sumHistData.GetNbinsX()):
            c = sumHistMC.GetBinCenter(ibin+1)
            w = sumHistMC.GetBinWidth(ibin+1)
            m = sumHistMC.GetBinContent(ibin+1)
                
            if m>0.0:
                h = min(sumHistMC.GetBinError(ibin+1)/m,0.399)
                box = ROOT.TBox(c-0.5*w,1-h,c+0.5*w,1+h)
                box.SetFillStyle(3345)
                box.SetLineColor(ROOT.kGray+1)
                box.SetFillColor(ROOT.kGray)
                box.SetLineWidth(int(2*cvscale))
                rootObj.append(box)
                box.Draw("SameF")
                box2 = ROOT.TBox(c-0.5*w,1-h,c+0.5*w,1+h)
                box2.SetFillStyle(0)
                box2.SetLineColor(ROOT.kGray+1)
                box2.SetFillColor(ROOT.kGray)
                box2.SetLineWidth(int(2*cvscale))
                rootObj.append(box2)
                box2.Draw("SameL")
        if len(rootObj)>0:
            legend.AddEntry(rootObj[0],"MC stat.","F")
            
            
       
        
        axisLine = ROOT.TF1("axisLine"+str(random.random()),"1",binarray[0],binarray[-1])
        axisLine.SetLineColor(ROOT.kBlack)
        axisLine.SetLineWidth(int(1*cvscale))
        axisLine.Draw("SameL")
        ROOT.gStyle.SetLineWidth(int(1*cvscale))
        ROOT.gPad.RedrawAxis()
        

        hidePave=ROOT.TPaveText(cvxmin-0.06,resHeight-0.028,cvxmin-0.005,resHeight+0.028,"NDC")
        hidePave.SetFillColor(ROOT.kWhite)
        hidePave.SetFillStyle(1001)
        hidePave.Draw("Same")
        '''
           




