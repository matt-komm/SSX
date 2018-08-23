#!/usr/bin/python

import ROOT
import numpy
import random
import math
import sys
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

ROOT.gStyle.SetLineStyleString(11,"30 15")
ROOT.gStyle.SetLineStyleString(12,"10 10")



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
        
    def getPredictions(self,channels,unfoldingName,unfoldingLevel):
        
        
        predictions = [
            {
                "name":"ST_t-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1",
                "color":newColor(0.1,0.6,0.95),
                "style":2,
                "width":4,
                "legend":"aMC@NLO#kern[-0.6]{ }4FS",#kern[-0.5]{ }+#kern[-0.5]{ }Pythia#kern[-0.6]{ }8"
            },
            {
                "name":"ST_t-channel_5f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1_GEN_v180731",
                "color":newColor(0.99,0.7,0.1),
                "style":11,
                "width":3,
                "legend":"aMC@NLO#kern[-0.6]{ }5FS",#kern[-0.5]{ }+#kern[-0.5]{ }Pythia#kern[-0.6]{ }8"
            }
        ]
        
        result = []
        #TODO: this is a dirty hack -> uses muon for combined as well!!! does not work for fiducial!!!
        if len(channels)==1:
            channel = channels[0]
        else:
            channel = "mu"
        
        outputFolderGen = self.module("Response").getOutputFolder(channel,unfoldingName,"nominal")
        genMCFileName = os.path.join(outputFolderGen,"genpredictions_"+unfoldingLevel+".root")
        rootFile = ROOT.TFile(genMCFileName)
        for prediction in predictions:
            histInc = rootFile.Get(prediction["name"]).Clone(prediction["name"]+str(random.random()))
            histInc.SetDirectory(0)
            histPos = rootFile.Get(prediction["name"]+"_pos").Clone(prediction["name"]+str(random.random()))
            histPos.SetDirectory(0)
            histNeg = rootFile.Get(prediction["name"]+"_neg").Clone(prediction["name"]+str(random.random()))
            histNeg.SetDirectory(0)
            for h in [histInc,histPos,histNeg]:
                h.SetLineColor(prediction["color"].GetNumber())
                h.SetLineStyle(prediction["style"])
                h.SetLineWidth(prediction["width"])
            result.append({
                0:histInc,1:histPos,-1:histNeg,"legend":prediction["legend"]
            })
        
                
        return result
        
        
    def applyLHEVariations(self,hist,unfoldingName,channels,unfoldingLevel,rangesPDF,rangesAlphaS,scalePos=1.,scaleNeg=1.):
        uncertaintiesPDF = []
        for r in rangesPDF:
            uncertaintiesPDF.append("lheWeight_%i"%r)
        uncertaintiesAlphaS = []
        for r in rangesAlphaS:
            uncertaintiesAlphaS.append("lheWeight_%i"%r)
        responseMatrices = self.module("Response").gatherResponse(
            unfoldingName,
            unfoldingLevel,
            channels,
            uncertainties=uncertaintiesPDF+uncertaintiesAlphaS
        )
        if len(channels)==2:
            responseMatrices = self.module("Response").combineResponseMatrices(responseMatrices)
        channelName = self.module("Samples").getChannelName(channels)
        
        pdfVariationsPos = {}
        pdfVariationsNeg = {}
        
        for unc in uncertaintiesPDF+uncertaintiesAlphaS:
            posHist = responseMatrices[channelName][1][unc]
            negHist = responseMatrices[channelName][-1][unc]
                               
        
            pdfVariationsPos[unc] = responseMatrices[channelName][1][unc].ProjectionX(responseMatrices[channelName][1][unc].GetName()+unc+str(random.random()))
            pdfVariationsNeg[unc] = responseMatrices[channelName][-1][unc].ProjectionX(responseMatrices[channelName][-1][unc].GetName()+unc+str(random.random()))
 
        variationsTotalPDFPos = numpy.zeros(len(uncertaintiesPDF))
        variationsTotalPDFNeg = numpy.zeros(len(uncertaintiesPDF))
        for ibin in range(hist.GetNbinsX()):
            variations = numpy.zeros(len(uncertaintiesPDF))
            for ik,k in enumerate(uncertaintiesPDF):
                posV = pdfVariationsPos[k].GetBinContent(ibin+1)*scalePos
                negV = pdfVariationsNeg[k].GetBinContent(ibin+1)*scaleNeg
                variations[ik] = posV/(posV+negV)
                variationsTotalPDFPos[ik] += posV
                variationsTotalPDFNeg[ik] += negV
                #print ibin,ik,posV,negV
            mean = numpy.mean(variations)
            std = numpy.std(variations)
            
            print ibin,hist.GetBinContent(ibin+1),mean,std
            print "   ",
            for ik,k in enumerate(uncertaintiesAlphaS):
                posV = pdfVariationsPos[k].GetBinContent(ibin+1)*scalePos
                negV = pdfVariationsNeg[k].GetBinContent(ibin+1)*scaleNeg
                print "%i=%6.4f, "%(ik,(posV/(posV+negV)-mean)),
            print
            
            hist.SetBinContent(ibin+1,mean)
            hist.SetBinError(ibin+1,std)
            

        meanAlt = numpy.mean(variationsTotalPDFPos/variationsTotalPDFNeg)
        stdAlt = numpy.std(variationsTotalPDFPos/variationsTotalPDFNeg)
        envUp = max(variationsTotalPDFPos/variationsTotalPDFNeg)-meanAlt
        envDown = min(variationsTotalPDFPos/variationsTotalPDFNeg)-meanAlt
        print "total",meanAlt,stdAlt,envUp,envDown
        print "   ",
        for ik,k in enumerate(uncertaintiesAlphaS):
            posV = 0
            negV = 0
            for ibin in range(hist.GetNbinsX()):
                posV += pdfVariationsPos[k].GetBinContent(ibin+1)*scalePos
                negV += pdfVariationsNeg[k].GetBinContent(ibin+1)*scaleNeg
            print "%i=%6.4f, "%(ik,(posV/(posV+negV)-mean)),
        print
             
        
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
        
        
        xtitle = self.module("Unfolding").getUnfoldingLevel().capitalize()+"-level "+self.module("Unfolding").getUnfoldingVariableName()
        ytitleSum = "d#kern[-0.5]{ }#sigma#kern[-0.5]{ }#lower[0.2]{#scale[1.3]{/}}#kern[-0.8]{ }d#kern[-0.5]{ }"+self.module("Unfolding").getUnfoldingSymbol()+""
        ytitleSumNorm = "1#kern[-0.5]{ }#lower[0.2]{#scale[1.3]{/}}#kern[-0.8]{ }#sigma#kern[-0.5]{ }#times#kern[-0.3]{ }d#kern[-0.5]{ }#sigma#kern[-0.5]{ }#lower[0.2]{#scale[1.3]{/}}#kern[-0.8]{ }d#kern[-0.5]{ }"+self.module("Unfolding").getUnfoldingSymbol()+""
        ytitleRatio = "d#kern[-0.5]{ }(#sigma#lower[0.3]{#scale[0.8]{#kern[-0.5]{ }t}}#kern[-0.5]{ }/#sigma#lower[0.3]{#scale[0.8]{#kern[-0.5]{ }t+#bar{t}}}#kern[-0.5]{ })#kern[-0.5]{ }#lower[0.2]{#scale[1.3]{/}}#kern[-0.8]{ }d#kern[-0.5]{ }"+self.module("Unfolding").getUnfoldingSymbol()+""
        unit = self.module("Unfolding").getUnfoldingVariableUnit()
        logy = unfoldingName=="pt" or unfoldingName=="lpt" or unfoldingName=="wpt"
        if unit!="":
            xtitle += " ("+unit+")"
            ytitleSum += " (pb#kern[-0.5]{ }/#kern[-0.5]{ }"+unit+")"
            ytitleSumNorm += " (1#kern[-0.5]{ }/#kern[-0.5]{ }"+unit+")"
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
        
        
        #add lumi uncertainty of 2.5%
        profiledResult["covarianceUnfolded"].Scale(1.025**2)
        
        
        ### total xsec ###
        #this is a reflection of the stat uncertainty only
        histSumNominal,covSumNominal = self.module("Unfolding").calculateSum(
            nominalResult["unfolded_pos"],
            nominalResult["unfolded_neg"],
            nominalResult["covarianceUnfolded"]
        )
        #this includes also the profiled exp. systematics
        histSumProfiled,covSumProfiled = self.module("Unfolding").calculateSum(
            profiledResult["unfolded_pos"],
            profiledResult["unfolded_neg"],
            profiledResult["covarianceUnfolded"]
        )
        #this is the envelope of all systematics
        histSumTotal,covSumTotal = self.module("Unfolding").calculateSum(
            profiledResult["unfolded_pos"],
            profiledResult["unfolded_neg"],
            profiledResult["covarianceUnfolded"],
            {1:nominalResult["unfolded_pos"],-1:nominalResult["unfolded_neg"]},
            sysResults
        )
        
        
        ### normalized xsec ###
        #this is a reflection of the stat uncertainty only
        histSumNominalNorm,covSumNominalNorm = self.module("Unfolding").calculateSumNorm(
            nominalResult["unfolded_pos"],
            nominalResult["unfolded_neg"],
            nominalResult["covarianceUnfolded"]
        )
        #this includes also the profiled exp. systematics
        histSumProfiledNorm,covSumProfiledNorm = self.module("Unfolding").calculateSumNorm(
            profiledResult["unfolded_pos"],
            profiledResult["unfolded_neg"],
            profiledResult["covarianceUnfolded"]
        )
        #this is the envelope of all systematics
        histSumTotalNorm,covSumTotalNorm = self.module("Unfolding").calculateSumNorm(
            profiledResult["unfolded_pos"],
            profiledResult["unfolded_neg"],
            profiledResult["covarianceUnfolded"],
            {1:nominalResult["unfolded_pos"],-1:nominalResult["unfolded_neg"]},
            sysResults
        )
        
        
        ### ratio xsec ###
        #this is a reflection of the stat uncertainty only
        histRatioNominal,covRatioNominal = self.module("Unfolding").calculateRatio(
            nominalResult["unfolded_pos"],
            nominalResult["unfolded_neg"],
            nominalResult["covarianceUnfolded"]
        )
        #this includes also the profiled exp. systematics
        histRatioProfiled,covRatioProfiled = self.module("Unfolding").calculateRatio(
            profiledResult["unfolded_pos"],
            profiledResult["unfolded_neg"],
            profiledResult["covarianceUnfolded"]
        )
        #this is the envelope of all systematics
        histRatioTotal,covRatioTotal = self.module("Unfolding").calculateRatio(
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
        
        self.module("Utils").normalizeCovByCrossSection2D(genBinning,covSumProfiled)
        self.module("Utils").normalizeCovByCrossSection2D(genBinning,covSumTotal)
        
        genHistSum = nominalResult["nominalGen_inc"]
        genHistSumNorm = genHistSum.Clone(genHistSum.GetName()+"norm")
        genHistSumNorm.Scale(1./genHistSumNorm.Integral())
        
        self.module("Utils").normalizeByCrossSection(genHistSum)
        genHistRatio = nominalResult["ratioGen"]
        
        genHistSums = [
            {"hist":genHistSum, "legend":"POWHEG#kern[-0.6]{ }4FS"},#kern[-0.5]{ }+#kern[-0.5]{ }Pythia#kern[-0.6]{ }8"}
        ]
        genHistSumsNorm = [
            {"hist":genHistSumNorm, "legend":"POWHEG#kern[-0.6]{ }4FS"},#kern[-0.5]{ }+#kern[-0.5]{ }Pythia#kern[-0.6]{ }8"}
        ]
        
        genPredictions = self.getPredictions(channels,unfoldingName,unfoldingLevel)
        for pred in genPredictions:
            
                
            genPrediction = pred[0].Clone(pred[0].GetName()+str(random.random()))
            self.module("Utils").normalizeByCrossSection(genPrediction)
            genHistSums.append({
                "hist":genPrediction,"legend":pred["legend"]
            })
            genPredictionNorm = pred[0].Clone(pred[0].GetName()+"norm")
            genPredictionNorm.Scale(1./genPredictionNorm.Integral())
            self.module("Utils").normalizeByBinWidth(genPredictionNorm)
            genHistSumsNorm.append({
                "hist":genPredictionNorm,"legend":pred["legend"]
            })
        
        self.module("Utils").normalizeByBinWidth(histSumProfiledNorm)
        self.module("Utils").normalizeByBinWidth(histSumTotalNorm)
        self.module("Utils").normalizeByBinWidth(genHistSumNorm)
        
        self.module("Utils").normalizeCovByBinWidth(genBinning,covSumProfiledNorm)
        self.module("Utils").normalizeCovByBinWidth(genBinning,covSumTotalNorm)
        
        
        for ibin in range(histSumProfiledNorm.GetNbinsX()):
            if math.fabs(histSumProfiled.GetBinError(ibin+1)-math.sqrt(covSumProfiled[ibin][ibin]))/histSumProfiled.GetBinError(ibin+1)>0.0001:
                self._logger.critical("Covariance matrix and histogram error do not agree!")
                sys.exit(1)
            if math.fabs(histSumTotal.GetBinError(ibin+1)-math.sqrt(covSumTotal[ibin][ibin]))/histSumTotal.GetBinError(ibin+1)>0.0001:
                self._logger.critical("Covariance matrix and histogram error do not agree!")
                sys.exit(1)
            if math.fabs(histSumProfiledNorm.GetBinError(ibin+1)-math.sqrt(covSumProfiledNorm[ibin][ibin]))/histSumProfiledNorm.GetBinError(ibin+1)>0.0001:
                self._logger.critical("Covariance matrix and histogram error do not agree!")
                sys.exit(1)
            if math.fabs(histSumTotalNorm.GetBinError(ibin+1)-math.sqrt(covSumTotalNorm[ibin][ibin]))/histSumTotalNorm.GetBinError(ibin+1)>0.0001:
                self._logger.critical("Covariance matrix and histogram error do not agree!")
                sys.exit(1)
        
        if (unfoldingName=="cos" or unfoldingName=="cosTau") and unfoldingLevel=="parton":
            asymmetryGen = self.module("Asymmetry").calculateAsymmetry(genHistSumNorm)
            asymmetryStat = self.module("Asymmetry").fitDistribution(histSumNominal,covSumNominal)
            asymmetryProfiled = self.module("Asymmetry").fitDistribution(histSumProfiled,covSumProfiled)
            asymmetryTotal = self.module("Asymmetry").fitDistribution(histSumTotal,covSumTotal)
            
            self._logger.info("Gen asymmetry: %5.3f"%(asymmetryGen))
            self._logger.info("Meas. asymmetry (stat): %5.3f+-%5.3f"%(asymmetryStat[0],asymmetryStat[1]))
            self._logger.info("Meas. asymmetry (exp): %5.3f+-%5.3f"%(asymmetryProfiled[0],asymmetryProfiled[1]))
            self._logger.info("Meas. asymmetry (tot): %5.3f+-%5.3f"%(asymmetryTotal[0],asymmetryTotal[1]))
        
        #tabSys= "\\hline\n"
        if unit!="":
            tabSys= "%20s"%("Bin range / "+unit)
        else:
            tabSys= "%20s"%("Bin range ")
        for ibin in range(len(genBinning)-1):
            binStart = genBinning[ibin]
            binEnd = genBinning[ibin+1]
            if math.log10(genBinning[-1])>=2:
                tabSys+= "& $[%4.0f;%4.0f]$ "%(binStart,binEnd)
            else:
                tabSys+= "& $[%4.2f;%4.2f]$ "%(binStart,binEnd)
        tabSys+= "\\\\\\hline\n"
        
        if unit!="":
            tabSys+= "%20s"%("Central value (pb/"+unit+")")
        else:
            tabSys+= "%20s"%("Central value (pb)")
        for ibin in range(len(genBinning)-1):
            value = histSumTotal.GetBinContent(ibin+1)
            if math.log10(value)>3 or math.log10(value)<3:
                tabSys+= ("& $%4.2e}$"%(histSumTotal.GetBinContent(ibin+1))).replace("e","\\cdot 10^{")
            elif math.log10(value)>0:
                tabSys+= ("& $%4.1f}$"%(histSumTotal.GetBinContent(ibin+1)))
            else:
                tabSys+= ("& $%5.3f}$"%(histSumTotal.GetBinContent(ibin+1)))
        tabSys+= "\\\\\n"
        
        tabSys+= "%20s"%("Stat.-only")
        for ibin in range(len(genBinning)-1):
            tabSys+= "& $\\pm%6.1f$\\%%"%(100.*histSumNominal.GetBinError(ibin+1)/histSumNominal.GetBinContent(ibin+1))
        tabSys+= "\\\\\n"
        
        tabSys+= "%20s"%("Stat.+Exp.")
        for ibin in range(len(genBinning)-1):
            tabSys+= "& $\\pm%6.1f$\\%%"%(100.*histSumProfiled.GetBinError(ibin+1)/histSumProfiled.GetBinContent(ibin+1))
        tabSys+= "\\\\\n"
        
        sysDictNames = {
            "pdf":"PDF",
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
            "wjetsScaleME":"\\wjets ME scale"
        }
        
        binSum2 = numpy.zeros(len(genBinning)-1)
        for isys,sys in enumerate(sorted(systematics)):
            tabSys+= "%20s"%(sysDictNames[sys])
            for ibin in range(len(genBinning)-1):
                relUp = math.fabs(
                    sysResults[isys][-1]["Up"].GetBinContent(ibin+1)+\
                    sysResults[isys][1]["Up"].GetBinContent(ibin+1)-\
                    histSumNominal.GetBinContent(ibin+1)
                )/histSumNominal.GetBinContent(ibin+1)
                relDown = math.fabs(
                    sysResults[isys][-1]["Down"].GetBinContent(ibin+1)+\
                    sysResults[isys][1]["Down"].GetBinContent(ibin+1)-\
                    histSumNominal.GetBinContent(ibin+1)
                )/histSumNominal.GetBinContent(ibin+1)
                binSum2[ibin] += max(relUp,relDown)**2
                tabSys+= "& $\\pm%6.1f$\\%%"%(100.*max(relUp,relDown))
            tabSys+= "\\\\\n"
        tabSys+= "\\hline\n"
        tabSys+= "%20s"%("Total")
        for ibin in range(len(genBinning)-1):
            tabSys+= "& $\\pm%6.1f$\\%%"%(100.*histSumTotal.GetBinError(ibin+1)/histSumTotal.GetBinContent(ibin+1))
        tabSys+= "\\\\\\hline\n"
        
        self.module("Utils").createFolder("final/"+channelName)
        finalFolder = self.module("Utils").getOutputFolder("final/"+channelName)

        
        
        fTabSys = open(os.path.join(finalFolder,unfoldingName+"_"+unfoldingLevel+"_"+channelName+"_sum.tex"),"w")
        fTabSys.write(tabSys)
        fTabSys.close()
        '''
        print "%20s"%("Sum2"),
        for ibin in range(len(genBinning)-1):
            err2 = binSum2[ibin]+(histSumProfiled.GetBinError(ibin+1)/histSumProfiled.GetBinContent(ibin+1))**2
            print "& $\\pm%6.1f$%%"%(100.*math.sqrt(err2)),
        print "\\\\"
        '''
        
        
        histSumProfiled.SetMarkerStyle(20)
        histSumProfiled.SetLineWidth(2)
        histSumProfiled.SetMarkerSize(1.)
        
        histSumProfiledNorm.SetMarkerStyle(20)
        histSumProfiledNorm.SetLineWidth(2)
        histSumProfiledNorm.SetMarkerSize(1.)
        
        
        histSumTotal.SetMarkerStyle(20)
        histSumTotal.SetLineWidth(1)
        histSumTotal.SetLineColor(ROOT.kBlack)
        histSumTotal.SetMarkerColor(ROOT.kBlack)
        histSumTotal.SetMarkerSize(1.2)
        
        histSumTotalNorm.SetMarkerStyle(20)
        histSumTotalNorm.SetLineWidth(1)
        histSumTotalNorm.SetLineColor(ROOT.kBlack)
        histSumTotalNorm.SetMarkerColor(ROOT.kBlack)
        histSumTotalNorm.SetMarkerSize(1.2)
        
        
        #genColor = newColor(72./255,123./255,234./255)
        #genColor = newColor(226./255,128./255,22./255)
        #211, 42, 42
        genColor = newColor(224./255,50./255,50./255)
        genHistSum.SetLineColor(genColor.GetNumber())
        genHistSum.SetLineWidth(2)
        genHistSumNorm.SetLineColor(genColor.GetNumber())
        genHistSumNorm.SetLineWidth(2)
        
        
        histRatioProfiled.SetMarkerStyle(20)
        histRatioProfiled.SetLineWidth(2)
        histRatioProfiled.SetMarkerSize(1.)
        
        histRatioTotal.SetMarkerStyle(20)
        histRatioTotal.SetLineWidth(1)
        histRatioTotal.SetLineColor(ROOT.kBlack)
        histRatioTotal.SetMarkerColor(ROOT.kBlack)
        histRatioTotal.SetMarkerSize(1.2)
        
        genHistRatio.SetLineColor(genColor.GetNumber())
        genHistRatio.SetLineWidth(2)
        genHistRatio.SetFillStyle(1001)
        
        
        ymin = 100000
        ymax = -10000
        
        yminNorm = 100000
        ymaxNorm = -10000
        for ibin in range(histSumTotal.GetNbinsX()):
            for genHistSum in genHistSums:
                ymin = min([ymin,genHistSum["hist"].GetBinContent(ibin+1),histSumTotal.GetBinContent(ibin+1)-histSumTotal.GetBinError(ibin+1)])
                ymax = max([ymax,genHistSum["hist"].GetBinContent(ibin+1),histSumTotal.GetBinContent(ibin+1)+histSumTotal.GetBinError(ibin+1)])
            for genHistSumNorm in genHistSumsNorm:
                yminNorm = min([yminNorm,genHistSumNorm["hist"].GetBinContent(ibin+1),histSumTotalNorm.GetBinContent(ibin+1)-histSumTotalNorm.GetBinError(ibin+1)])
                ymaxNorm = max([ymaxNorm,genHistSumNorm["hist"].GetBinContent(ibin+1),histSumTotalNorm.GetBinContent(ibin+1)+histSumTotalNorm.GetBinError(ibin+1)])
            
        if logy:
            ymin = 10**math.floor(math.log10(0.7*ymin))
            ymax = math.exp(0.15*(math.log(ymax)-math.log(ymin))+math.log(ymax))
            
            yminNorm = 10**math.floor(math.log10(0.7*yminNorm))
            ymaxNorm = math.exp(0.15*(math.log(ymaxNorm)-math.log(yminNorm))+math.log(ymaxNorm))
        else:
            ymax = 1.1*ymax
            ymin = 0
            
            ymaxNorm = 1.1*ymaxNorm
            yminNorm = 0
        
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
        
            
            
            
        if unfoldingName=="lpt" or unfoldingName=="y":
            legendPos = "RU"
        elif unfoldingName=="cos" or unfoldingName=="cosTau":
            legendPos = "RD"
        else:
            legendPos = "LD"
            
            
        genHistsRatioMMHT14 = genHistRatio.Clone(genHistRatio.GetName()+"mh")
        #genHistsRatioMMHT14.SetLineColor(newColor(0,0.84,0.91).GetNumber())
        genHistsRatioMMHT14.SetLineColor(newColor(1.,0.76,0.32).GetNumber())
        genHistsRatioMMHT14.SetLineStyle(1)
        genHistsRatioMMHT14.SetLineWidth(3)
        genHistsRatioMMHT14.SetFillStyle(1001)
        self.applyLHEVariations(
            genHistsRatioMMHT14,
            unfoldingName,
            channels,
            unfoldingLevel,
            range(4001,4098),
            [],
            scalePos=138.3/136.02,
            scaleNeg=83.5/80.95
        )
            
        genHistsRatioNNPDF30 = genHistRatio.Clone(genHistRatio.GetName()+"nnpdf")
        #genHistsRatioNNPDF30.SetLineColor(newColor(0.13,0.13,0.93).GetNumber())
        genHistsRatioNNPDF30.SetLineColor(newColor(0.95,0.20,0.27).GetNumber())
        genHistsRatioNNPDF30.SetLineStyle(1)
        genHistsRatioNNPDF30.SetLineWidth(3)
        genHistsRatioNNPDF30.SetFillStyle(1001)
        self.applyLHEVariations(
            genHistsRatioNNPDF30,
            unfoldingName,
            channels,
            unfoldingLevel,
            range(2001,2102),
            range(2102,2106),
            scalePos=1.,
            scaleNeg=1.
        )
        
        genHistsRatioCT14 = genHistRatio.Clone(genHistRatio.GetName()+"ct")
        #genHistsRatioCT14.SetLineColor(newColor(0.82,0.45,0.89).GetNumber())
        genHistsRatioCT14.SetLineColor(newColor(0.65,0.36,0.85).GetNumber())
        genHistsRatioCT14.SetLineStyle(1)
        genHistsRatioCT14.SetLineWidth(3)
        genHistsRatioCT14.SetFillStyle(1001)
        self.applyLHEVariations(
            genHistsRatioCT14,
            unfoldingName,
            channels,
            unfoldingLevel,
            range(3001,3056),
            [],
            scalePos=135.2/136.02,
            scaleNeg=79.3/80.95
        )
        
        
            
        genHistsRatio = [
            {"hist":genHistsRatioMMHT14,"legend":"MMHT#kern[-0.6]{ }14"},
            {"hist":genHistsRatioNNPDF30,"legend":"NNPDF#kern[-0.6]{ }3.0"},
            {"hist":genHistsRatioCT14,"legend":"CT#kern[-0.6]{ }14"},
            
        ]
        
        
        
        self.module("Drawing").plotCrossSection(
            genHistSums,histSumProfiled,histSumTotal,ymin,ymax,logy,ytitleSum,xtitle,
            self.module("Samples").getPlotTitle(channels,0)+"#kern[-0.5]{ }+#kern[-0.5]{ }jets, 36#kern[-0.5]{ }fb#lower[-0.7]{#scale[0.7]{-1}} (13TeV)",
            legendPos,resRange,
            os.path.join(finalFolder,unfoldingName+"_"+unfoldingLevel+"_"+channelName+"_sum")
        )  
        
        self.module("Drawing").plotCrossSection(
            genHistSumsNorm,histSumProfiledNorm,histSumTotalNorm,yminNorm,ymaxNorm,logy,ytitleSumNorm,xtitle,
            self.module("Samples").getPlotTitle(channels,0)+"#kern[-0.5]{ }+#kern[-0.5]{ }jets, 36#kern[-0.5]{ }fb#lower[-0.7]{#scale[0.7]{-1}} (13TeV)",
            legendPos,resRange,
            os.path.join(finalFolder,unfoldingName+"_"+unfoldingLevel+"_"+channelName+"_sumnorm")
        ) 
        
        ymin = 0.25 if channelName=="comb" else 0.2
        ymax = 0.8 if channelName=="comb" else 1.1
        self.module("Drawing").plotCrossSection(
            genHistsRatio,histRatioProfiled,histRatioTotal,ymin,ymax,0,ytitleRatio,xtitle,
            self.module("Samples").getPlotTitle(channels,0)+"#kern[-0.5]{ }+#kern[-0.5]{ }jets, 36#kern[-0.5]{ }fb#lower[-0.7]{#scale[0.7]{-1}} (13TeV)",
            "LD",0.48,
            os.path.join(finalFolder,unfoldingName+"_"+unfoldingLevel+"_"+channelName+"_ratio"),
            fillGen=True
        )    
        




