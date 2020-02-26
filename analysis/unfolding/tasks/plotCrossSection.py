#!/usr/bin/python

import ROOT
import numpy
import random
import math
import sys
import os
import json
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
#ROOT.gStyle.SetPalette(1)
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
    color=ROOT.TColor(newColor.colorindex,min(red,1.),min(green,1.),min(blue,1.))
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
                'key':'amcatnlo4f',
                "legend":"aMC@NLO 4FS",#kern[-0.5]{ }+#kern[-0.5]{ }Pythia#kern[-0.6]{ }8"
            },
            {
                "name":"ST_t-channel_5f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1_GEN_v180904",
                "color":newColor(0.99,0.7,0.1),
                "style":11,
                "width":3,
                'key':'amcatnlo5f',
                "legend":"aMC@NLO 5FS",#kern[-0.5]{ }+#kern[-0.5]{ }Pythia#kern[-0.6]{ }8"
            }
        ]
        
        result = []
        
        for prediction in predictions:
            histsInc = []
            histsPos = []
            histsNeg = []
            for channel in channels:
                outputFolderGen = self.module("Response").getOutputFolder(channel,unfoldingName,"nominal")
                genMCFileName = os.path.join(outputFolderGen,"genpredictions_"+unfoldingLevel+".root")
                rootFile = ROOT.TFile(genMCFileName)
                if not rootFile.IsOpen():
                    self._logger.critical("Cannot find prediction file '"+genMCFileName+"'")
                    sys.exit(1)
                
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
                    
                histsInc.append(histInc)
                histsPos.append(histPos)
                histsNeg.append(histNeg)
            
            if len(channels)==1:  
                result.append({
                    0:histsInc[0],1:histsPos[0],-1:histsNeg[0],"legend":prediction["legend"],'key':prediction["key"]
                })
            else:
                combGenBinning = self.module("Unfolding").getGenBinning("comb")
                globalBinMap = self.module("Unfolding").buildGlobalGenBinMap()
                histIncComb = ROOT.TH1F("histCombInc"+prediction["name"]+str(random.random()),"",len(combGenBinning)-1,combGenBinning)
                histIncComb.SetDirectory(0)
                histPosComb = ROOT.TH1F("histCombPos"+prediction["name"]+str(random.random()),"",len(combGenBinning)-1,combGenBinning)
                histPosComb.SetDirectory(0)
                histNegComb = ROOT.TH1F("histCombNeg"+prediction["name"]+str(random.random()),"",len(combGenBinning)-1,combGenBinning)
                histNegComb.SetDirectory(0)
                
                for h in [histIncComb,histPosComb,histNegComb]:
                    h.SetLineColor(prediction["color"].GetNumber())
                    h.SetLineStyle(prediction["style"])
                    h.SetLineWidth(prediction["width"])
                
                for ichannel, channel in enumerate(channels):
                    for channelBin,globalBin in globalBinMap[channel].iteritems():
                        histIncComb.SetBinContent(
                            globalBin+1,
                            histsInc[ichannel].GetBinContent(channelBin+1)+\
                            histIncComb.GetBinContent(globalBin+1)
                        )
                        histPosComb.SetBinContent(
                            globalBin+1,
                            histsPos[ichannel].GetBinContent(channelBin+1)+\
                            histPosComb.GetBinContent(globalBin+1)
                        )
                        histNegComb.SetBinContent(
                            globalBin+1,
                            histsNeg[ichannel].GetBinContent(channelBin+1)+\
                            histNegComb.GetBinContent(globalBin+1)
                        )
                self.module("Unfolding").applyEfficiencyCorrection1D(histIncComb)
                self.module("Unfolding").applyEfficiencyCorrection1D(histPosComb)
                self.module("Unfolding").applyEfficiencyCorrection1D(histNegComb)
                result.append({
                    0:histIncComb,1:histPosComb,-1:histNegComb,"legend":prediction["legend"],'key':prediction["key"]
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
        variationsTotalAlphaSPos = [0.,0.]
        variationsTotalAlphaSNeg = [0.,0.]
        for ibin in range(hist.GetNbinsX()):
            variations = numpy.zeros(len(uncertaintiesPDF))
            for ik,k in enumerate(uncertaintiesPDF):
                posV = pdfVariationsPos[k].GetBinContent(ibin+1)*scalePos
                negV = pdfVariationsNeg[k].GetBinContent(ibin+1)*scaleNeg
                variations[ik] = posV/(posV+negV)
                variationsTotalPDFPos[ik] += posV
                variationsTotalPDFNeg[ik] += negV
                #print ibin,ik,posV,negV
                
            alphasDownPos = pdfVariationsPos[uncertaintiesAlphaS[0]].GetBinContent(ibin+1)#*scalePos
            alphasUpPos = pdfVariationsPos[uncertaintiesAlphaS[1]].GetBinContent(ibin+1)#*scalePos
            
            alphasDownNeg = pdfVariationsNeg[uncertaintiesAlphaS[0]].GetBinContent(ibin+1)#*scaleNeg
            alphasUpNeg = pdfVariationsNeg[uncertaintiesAlphaS[1]].GetBinContent(ibin+1)#*scaleNeg
            
            variationsTotalAlphaSPos[0]+=alphasDownPos
            variationsTotalAlphaSPos[1]+=alphasUpPos
            
            variationsTotalAlphaSNeg[0]+=alphasDownNeg
            variationsTotalAlphaSNeg[1]+=alphasUpNeg
            
            alphaSUp = alphasUpPos/(alphasUpPos+alphasUpNeg)
            alphaSDown = alphasDownPos/(alphasDownPos+alphasDownNeg)
                
            mean = numpy.mean(variations)
            alphaS = max(math.fabs(alphaSUp-mean),math.fabs(alphaSDown-mean))
            std = numpy.std(variations)
            totalErr = math.sqrt(std**2+alphaS**2)
            
            hist.SetBinContent(ibin+1,mean)
            hist.SetBinError(ibin+1,totalErr)
            

        meanAlt = numpy.mean(variationsTotalPDFPos/variationsTotalPDFNeg)
        alphaS = max(
            math.fabs(variationsTotalAlphaSPos[0]/variationsTotalAlphaSNeg[0]-meanAlt),
            math.fabs(variationsTotalAlphaSPos[1]/variationsTotalAlphaSNeg[1]-meanAlt),
        )
        stdAlt = numpy.std(variationsTotalPDFPos/variationsTotalPDFNeg)
        print "total",meanAlt,'+-',stdAlt,'+-',alphaS,"=",meanAlt,'+-',math.sqrt(stdAlt**2+alphaS**2)
        
    def calculateChi2(self,measuredHist,genHist,cov,isNorm=False):
        chi2 = 0.
        chi2noCorr = 0.
        
        covnoCorr = numpy.zeros(cov.shape)
        for i in range(cov.shape[0]):
            covnoCorr[i,i]=cov[i,i]
        
        if isNorm:
            #cannot invert norm => singular as expected; so throw last bin away
            covInv = numpy.linalg.inv(cov[:-1,:-1])
            covnoCorrInv = numpy.linalg.inv(covnoCorr[:-1,:-1])
        else:
            covInv = numpy.linalg.inv(cov)
            covnoCorrInv = numpy.linalg.inv(covnoCorr)
            
        N = (genHist.GetNbinsX()-1) if isNorm else genHist.GetNbinsX() 
        
        for ibin in range(N):
            for jbin in range(N):
                '''
                print ibin,jbin,
                print (genHist.GetBinContent(ibin+1)-measuredHist.GetBinContent(ibin+1))/measuredHist.GetBinContent(ibin+1),
                print (genHist.GetBinContent(jbin+1)-measuredHist.GetBinContent(jbin+1))/measuredHist.GetBinContent(jbin+1),
                print math.sqrt(cov[ibin,jbin]/measuredHist.GetBinContent(ibin+1)/measuredHist.GetBinContent(jbin+1)) if cov[ibin,jbin]>0 else cov[ibin,jbin]/math.sqrt(cov[ibin,ibin]*cov[jbin,jbin]),
                print (genHist.GetBinContent(ibin+1)-measuredHist.GetBinContent(ibin+1))\
                       *covInv[ibin,jbin]\
                       *(genHist.GetBinContent(jbin+1)-measuredHist.GetBinContent(jbin+1)),
                print (genHist.GetBinContent(ibin+1)-measuredHist.GetBinContent(ibin+1))\
                       *covnoCorrInv[ibin,jbin]\
                       *(genHist.GetBinContent(jbin+1)-measuredHist.GetBinContent(jbin+1))
                '''
                chi2+=(genHist.GetBinContent(ibin+1)-measuredHist.GetBinContent(ibin+1))\
                       *covInv[ibin,jbin]\
                       *(genHist.GetBinContent(jbin+1)-measuredHist.GetBinContent(jbin+1))
                if ibin==jbin:
                    chi2noCorr+=(genHist.GetBinContent(ibin+1)-measuredHist.GetBinContent(ibin+1))\
                       *covnoCorrInv[ibin,jbin]\
                       *(genHist.GetBinContent(jbin+1)-measuredHist.GetBinContent(jbin+1))
        return chi2/N,chi2noCorr/N

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
        
        profiledResultSyst = {}
        for profSystName in ['QCD*Excl','TopBkg*Excl','WZjets*Excl','enExcl','puExcl','resExcl','uncExcl','btagExcl','ltagExcl','muEffExcl','eleEffExcl','muMultiExcl','eleMultiIsoExcl','eleMultiVetoExcl','twExcl','dyExcl']:
            profiledFolderSyst = self.module("Utils").getOutputFolder("unfolding/"+unfoldingName+"/"+unfoldingLevel+"/"+profSystName)
            rootFileProfiledSyst = ROOT.TFile(os.path.join(profiledFolderSyst,channelName+"_result.root"))
            profiledResultSyst[profSystName] = self.getResult(rootFileProfiledSyst)
            rootFileProfiledSyst.Close()
        
        nominalFolder = self.module("Utils").getOutputFolder("unfolding/"+unfoldingName+"/"+unfoldingLevel+"/nominal")
        rootFileNominal = ROOT.TFile(os.path.join(nominalFolder,channelName+"_result.root"))
        nominalResult = self.getResult(rootFileNominal)
        rootFileNominal.Close()
        
        allExclFolder = self.module("Utils").getOutputFolder("unfolding/"+unfoldingName+"/"+unfoldingLevel+"/allExcl")
        rootFileAllExcl = ROOT.TFile(os.path.join(allExclFolder,channelName+"_result.root"))
        allExclResult = self.getResult(rootFileAllExcl)
        rootFileAllExcl.Close()
        
        
        #this is a reflection of the stat uncertainty only
        histSumNominal,covSumNominal = self.module("Unfolding").calculateSum(
            nominalResult["unfolded_pos"],
            nominalResult["unfolded_neg"],
            nominalResult["covarianceUnfolded"]
        )
        #this is a reflection of the stat uncertainty only
        histRatioNominal,covRatioNominal = self.module("Unfolding").calculateRatio(
            nominalResult["unfolded_pos"],
            nominalResult["unfolded_neg"],
            nominalResult["covarianceUnfolded"]
        )
        
        
        
        xtitleWOUnit = self.module("Unfolding").getUnfoldingLevel().capitalize()+"-level "+self.module("Unfolding").getUnfoldingVariableName()
        ytitleSumWOUnit = "d#kern[-0.6]{ }#sigma#kern[-0.5]{ }#lower[0.2]{#scale[1.3]{/}}#kern[-0.8]{ }d#kern[-0.6]{ }"+self.module("Unfolding").getUnfoldingSymbol()+""
        ytitleSumNormWOUnit = "1#kern[-0.5]{ }#lower[0.2]{#scale[1.3]{/}}#kern[-0.8]{ }#sigma#kern[-0.7]{ }#kern[-0.5]{ }#times#kern[-0.3]{ }d#kern[-0.6]{ }#sigma#kern[-0.5]{ }#lower[0.2]{#scale[1.3]{/}}#kern[-0.8]{ }d#kern[-0.6]{ }"+self.module("Unfolding").getUnfoldingSymbol()+""
        
        ytitleRatioWOUnit = "(d#kern[-0.6]{ }#sigma#kern[-0.7]{ }#lower[0.3]{#scale[0.8]{t}}#kern[-0.5]{ }/#kern[-0.8]{ }d#kern[-0.6]{ }"+self.module("Unfolding").getUnfoldingSymbol()+")"
        ytitleRatioWOUnit += "#kern[-0.5]{ }#lower[0.2]{#scale[1.3]{/}}#kern[-0.8]{ }"
        ytitleRatioWOUnit += "(d#kern[-0.6]{ }#sigma#kern[-0.7]{ }#lower[0.3]{#scale[0.8]{t+t#lower[-0.87]{#kern[-1.0]{-}}}}#kern[-0.5]{ }/#kern[-0.8]{ }d#kern[-0.6]{ }"+self.module("Unfolding").getUnfoldingSymbol()+")"
        
        unit = self.module("Unfolding").getUnfoldingVariableUnit()
        
        logy = unfoldingName=="pt" or unfoldingName=="lpt" or unfoldingName=="wpt"
        if unit!="":
            xtitle = xtitleWOUnit+" ("+unit+")"
            ytitleSum = ytitleSumWOUnit+" (pb#kern[-0.2]{ }/#kern[-0.5]{ }"+unit+")"
            ytitleSumNorm = ytitleSumNormWOUnit+" (1#kern[-0.2]{ }/#kern[-0.5]{ }"+unit+")"
            ytitleRatio = ytitleRatioWOUnit
        else:
            ytitleSum = ytitleSumWOUnit+" (pb)"
            xtitle = xtitleWOUnit
            ytitleSumNorm = ytitleSumNormWOUnit
            ytitleRatio = ytitleRatioWOUnit
        
        sysResults = []
        sysCov = []
        for isys,sys in enumerate(sorted(systematics)):
            results = {-1:{},1:{},0:{}}
            covDict = {}
            #self._logger.info(str(isys)+": "+sys)
            if sys.find("topMass")>=0:
                sysFolder = self.module("Utils").getOutputFolder("unfolding/"+unfoldingName+"/"+unfoldingLevel+"/"+sys+"Up")
                rootFile = ROOT.TFile(os.path.join(sysFolder,channelName+"_result.root"))
                result = self.getResult(rootFile)
                results[-1]["Up"]=result["unfolded_neg"]
                results[1]["Up"]=result["unfolded_pos"]
                results[-1]["Down"] = result["unfolded_neg"].Clone(result["unfolded_neg"].GetName()+"Down")
                results[1]["Down"] = result["unfolded_pos"].Clone(result["unfolded_pos"].GetName()+"Down")
                covDict["Up"] = result["covarianceUnfolded"]
                
                results[-1]["Down"].SetDirectory(0)
                results[1]["Down"].SetDirectory(0)
                covDict["Down"] = result["covarianceUnfolded"].Clone(result["covarianceUnfolded"].GetName()+"Down")
                covDict["Down"].SetDirectory(0)
                
                for ibin in range(results[-1]["Down"].GetNbinsX()): 
                    cneg = nominalResult["unfolded_neg"].GetBinContent(ibin+1)
                    cpos = nominalResult["unfolded_pos"].GetBinContent(ibin+1)

                    uneg = result["unfolded_neg"].GetBinContent(ibin+1)
                    upos = result["unfolded_pos"].GetBinContent(ibin+1)
                    
                    #increase unc from 0.5 -> 1. GeV
                    uneg = cneg+2.*(uneg-cneg)
                    upos = cpos+2.*(upos-cpos)
                    
                    results[-1]["Up"].SetBinContent(ibin+1,uneg)
                    results[1]["Up"].SetBinContent(ibin+1,upos)
                    
                    dneg = cneg-0.5*(uneg-cneg)
                    dpos = cpos-0.5*(upos-cpos)
                    
                    results[-1]["Down"].SetBinContent(ibin+1,dneg)
                    results[1]["Down"].SetBinContent(ibin+1,dpos)
                    
            elif sys.find("pdfFull")>=0:
                envelopePos = []
                envelopeNeg = []
                envelopeCov = []
                for lhe in range(2001,2103):
                    sysFolder = self.module("Utils").getOutputFolder("unfolding/"+unfoldingName+"/"+unfoldingLevel+"/lheWeight_%i"%lhe)
                    rootFile = ROOT.TFile(os.path.join(sysFolder,channelName+"_result.root"))
                    result = self.getResult(rootFile)
                    N = result["unfolded_neg"].GetNbinsX()
                    binPos = numpy.zeros(N)
                    binNeg = numpy.zeros(N)
                    binCov = numpy.zeros((2*N,2*N))
                    for ibin in range(N):
                        binPos[ibin] = result["unfolded_pos"].GetBinContent(ibin+1)
                        binNeg[ibin] = result["unfolded_neg"].GetBinContent(ibin+1)
                    for ibin in range(2*N):
                        for jbin in range(2*N):
                            binCov[ibin,jbin] = result["covarianceUnfolded"].GetBinContent(ibin+1,jbin+1)
                    envelopePos.append(binPos)
                    envelopeNeg.append(binNeg)
                    envelopeCov.append(binCov)
                    
                envelopePos = numpy.stack(envelopePos,axis=0)
                envelopeNeg = numpy.stack(envelopeNeg,axis=0)
                envelopeCov = numpy.stack(envelopeCov,axis=0)
                
                centerPos = numpy.mean(envelopePos,axis=0)
                centerNeg = numpy.mean(envelopeNeg,axis=0)
                centerCov = numpy.mean(envelopeCov,axis=0)
                
                sigPos = numpy.std(envelopePos,axis=0)
                sigNeg = numpy.std(envelopeNeg,axis=0)
                sigCov = numpy.std(envelopeCov,axis=0)
                
                
                results[-1]['Up']=nominalResult["unfolded_neg"].Clone(nominalResult["unfolded_neg"].GetName()+"pdfFullUp")
                results[-1]['Up'].SetDirectory(0)
                
                results[-1]['Down']=nominalResult["unfolded_neg"].Clone(nominalResult["unfolded_neg"].GetName()+"pdfFullDown")
                results[-1]['Down'].SetDirectory(0)
                
                results[1]['Up']=nominalResult["unfolded_pos"].Clone(nominalResult["unfolded_pos"].GetName()+"pdfFullUp")
                results[1]['Up'].SetDirectory(0)
                
                results[1]['Down']=nominalResult["unfolded_pos"].Clone(nominalResult["unfolded_pos"].GetName()+"pdfFullDown")
                results[1]['Down'].SetDirectory(0)
                
                covDict["Up"]=nominalResult["covarianceUnfolded"].Clone(nominalResult["covarianceUnfolded"].GetName()+"pdfFullUp")
                covDict["Up"].SetDirectory(0)
                
                covDict["Down"]=nominalResult["covarianceUnfolded"].Clone(nominalResult["covarianceUnfolded"].GetName()+"pdfFullDown")
                covDict["Down"].SetDirectory(0)
                
                for ibin in range(N):
                    results[-1]['Up'].SetBinContent(ibin+1,centerNeg[ibin]+sigNeg[ibin])
                    results[-1]['Down'].SetBinContent(ibin+1,centerNeg[ibin]-sigNeg[ibin])
                    results[1]['Up'].SetBinContent(ibin+1,centerPos[ibin]+sigPos[ibin])
                    results[1]['Down'].SetBinContent(ibin+1,centerPos[ibin]-sigPos[ibin])
                
                for ibin in range(2*N):
                    for jbin in range(2*N):
                        covDict["Up"].SetBinContent(ibin+1,jbin+1,centerCov[ibin,jbin]+sigCov[ibin,jbin])
                        covDict["Down"].SetBinContent(ibin+1,jbin+1,centerCov[ibin,jbin]-sigCov[ibin,jbin])
                
            elif sys.find("tchanColor")>=0:
                for ccvar in ["tchanGluonMove","tchanErdOn","tchanGluonMoveErdOn"]:
                    sysFolder = self.module("Utils").getOutputFolder("unfolding/"+unfoldingName+"/"+unfoldingLevel+"/"+ccvar)
                    rootFile = ROOT.TFile(os.path.join(sysFolder,channelName+"_result.root"))
                    result = self.getResult(rootFile)
                    if not results[-1].has_key("Down"):
                        results[-1]["Down"] = result["unfolded_neg"].Clone(result["unfolded_neg"].GetName()+"tchanColorDown")
                        results[-1]["Down"].SetDirectory(0)
                        
                        results[1]["Down"] = result["unfolded_pos"].Clone(result["unfolded_pos"].GetName()+"tchanColorDown")
                        results[1]["Down"].SetDirectory(0)
                        
                        results[-1]["Up"] = result["unfolded_neg"].Clone(result["unfolded_neg"].GetName()+"tchanColorUp")
                        results[-1]["Up"].SetDirectory(0)
                        
                        results[1]["Up"] = result["unfolded_pos"].Clone(result["unfolded_pos"].GetName()+"tchanColorUp")
                        results[1]["Up"].SetDirectory(0)
                        
                        covDict["Up"] = result["covarianceUnfolded"].Clone(result["covarianceUnfolded"].GetName()+"tchanColorUp")
                        covDict["Up"].SetDirectory(0)
                        covDict["Down"] = result["covarianceUnfolded"].Clone(result["covarianceUnfolded"].GetName()+"tchanColorDown")
                        covDict["Down"].SetDirectory(0)
                        
                    for ibin in range(results[-1]["Down"].GetNbinsX()):
                        results[-1]["Up"].SetBinContent(
                            ibin+1,
                            max(result["unfolded_neg"].GetBinContent(ibin+1),results[-1]["Up"].GetBinContent(ibin+1))
                        )
                        results[-1]["Down"].SetBinContent(
                            ibin+1,
                            min(result["unfolded_neg"].GetBinContent(ibin+1),results[-1]["Down"].GetBinContent(ibin+1))
                        )
                        results[1]["Up"].SetBinContent(
                            ibin+1,
                            max(result["unfolded_pos"].GetBinContent(ibin+1),results[1]["Up"].GetBinContent(ibin+1))
                        )
                        results[1]["Down"].SetBinContent(
                            ibin+1,
                            min(result["unfolded_pos"].GetBinContent(ibin+1),results[1]["Down"].GetBinContent(ibin+1))
                        )
                        
            elif sys.find("ttbarColor")>=0:
                for ccvar in ["ttbarGluonMove","ttbarErdOn","ttbarGluonMoveErdOn"]:
                    sysFolder = self.module("Utils").getOutputFolder("unfolding/"+unfoldingName+"/"+unfoldingLevel+"/"+ccvar)
                    rootFile = ROOT.TFile(os.path.join(sysFolder,channelName+"_result.root"))
                    result = self.getResult(rootFile)
                    if not results[-1].has_key("Down"):
                        results[-1]["Down"] = result["unfolded_neg"].Clone(result["unfolded_neg"].GetName()+"ttbarColorDown")
                        results[-1]["Down"].SetDirectory(0)
                        
                        results[1]["Down"] = result["unfolded_pos"].Clone(result["unfolded_pos"].GetName()+"ttbarColorDown")
                        results[1]["Down"].SetDirectory(0)
                        
                        results[-1]["Up"] = result["unfolded_neg"].Clone(result["unfolded_neg"].GetName()+"ttbarColorUp")
                        results[-1]["Up"].SetDirectory(0)
                        
                        results[1]["Up"] = result["unfolded_pos"].Clone(result["unfolded_pos"].GetName()+"ttbarColorUp")
                        results[1]["Up"].SetDirectory(0)
                        
                        covDict["Up"] = result["covarianceUnfolded"].Clone(result["covarianceUnfolded"].GetName()+"ttbarColorUp")
                        covDict["Up"].SetDirectory(0)
                        covDict["Down"] = result["covarianceUnfolded"].Clone(result["covarianceUnfolded"].GetName()+"ttbarColorDown")
                        covDict["Down"].SetDirectory(0)
                        
                    for ibin in range(results[-1]["Down"].GetNbinsX()):
                        results[-1]["Up"].SetBinContent(
                            ibin+1,
                            max(result["unfolded_neg"].GetBinContent(ibin+1),results[-1]["Up"].GetBinContent(ibin+1))
                        )
                        results[-1]["Down"].SetBinContent(
                            ibin+1,
                            min(result["unfolded_neg"].GetBinContent(ibin+1),results[-1]["Down"].GetBinContent(ibin+1))
                        )
                        results[1]["Up"].SetBinContent(
                            ibin+1,
                            max(result["unfolded_pos"].GetBinContent(ibin+1),results[1]["Up"].GetBinContent(ibin+1))
                        )
                        results[1]["Down"].SetBinContent(
                            ibin+1,
                            min(result["unfolded_pos"].GetBinContent(ibin+1),results[1]["Down"].GetBinContent(ibin+1))
                        )
                '''
                elif sys.find("lumi")>=0:
                    lumiScale = 0.025
                
                    results[-1]['Up']=nominalResult["unfolded_neg"].Clone(nominalResult["unfolded_neg"].GetName()+"lumiUp")
                    results[-1]['Up'].SetDirectory(0)
                    results[-1]['Up'].Scale(1.+lumiScale)
                    
                    results[-1]['Down']=nominalResult["unfolded_neg"].Clone(nominalResult["unfolded_neg"].GetName()+"lumiDown")
                    results[-1]['Down'].SetDirectory(0)
                    results[-1]['Down'].Scale(1.-lumiScale)
                    
                    results[1]['Up']=nominalResult["unfolded_pos"].Clone(nominalResult["unfolded_pos"].GetName()+"lumiUp")
                    results[1]['Up'].SetDirectory(0)
                    results[1]['Up'].Scale(1.+lumiScale)
                    
                    results[1]['Down']=nominalResult["unfolded_pos"].Clone(nominalResult["unfolded_pos"].GetName()+"lumiDown")
                    results[1]['Down'].SetDirectory(0)
                    results[1]['Down'].Scale(1.-lumiScale)
                    
                    covDict["Up"]=nominalResult["covarianceUnfolded"].Clone(nominalResult["covarianceUnfolded"].GetName()+"lumiUp")
                    covDict["Up"].SetDirectory(0)
                    
                    covDict["Down"]=nominalResult["covarianceUnfolded"].Clone(nominalResult["covarianceUnfolded"].GetName()+"lumiDown")
                    covDict["Down"].SetDirectory(0)
                '''
            else:
                for v in ["Up","Down"]:
                    sysFolder = self.module("Utils").getOutputFolder("unfolding/"+unfoldingName+"/"+unfoldingLevel+"/"+sys+v)
                    rootFile = ROOT.TFile(os.path.join(sysFolder,channelName+"_result.root"))
                    result = self.getResult(rootFile)
                    results[-1][v]=result["unfolded_neg"]
                    results[1][v]=result["unfolded_pos"]
                    covDict[v]=result["covarianceUnfolded"]
                    
            sysCov.append(covDict)
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
         
            
        self.module("Unfolding").symmetrizeSystPerCharge(
            {1:nominalResult["unfolded_pos"],-1:nominalResult["unfolded_neg"]},
            sysResults
        )
        

        
        for isys,sys in enumerate(sorted(systematics)):
            for v in ["Up","Down"]:
                histSystSum,covSystSum = self.module("Unfolding").calculateSum(
                    sysResults[isys][1][v],
                    sysResults[isys][-1][v],
                    sysCov[isys][v]
                )
                histSystRatio,covSystRatio = self.module("Unfolding").calculateRatio(
                    sysResults[isys][1][v],
                    sysResults[isys][-1][v],
                    sysCov[isys][v]
                )
                sysResults[isys][0][v] = {"hist":histSystSum,"cov":covSystSum,"ratio":histSystRatio,"ratioCov":covSystRatio}
            
            nominalResultSum = nominalResult["nominalGen_pos"].Clone(nominalResult["nominalGen_pos"].GetName()+sys+str(random.random()))
            nominalResultSum.Add(nominalResult["nominalGen_neg"])
            self.module("Drawing").plotEnvelopeHistogram(
                nominalResultSum,histSumNominal,sysResults[isys][0]["Up"]["hist"],sysResults[isys][0]["Down"]["hist"],
                os.path.join(outputFolder,self.module("Samples").getChannelName(channels)+"_sum_"+sys),
                title=self.module("Samples").getPlotTitle(channels,0)+"#kern[-0.5]{ }+#kern[-0.5]{ }jets",
                xaxis=xtitle,yaxis=ytitleSum,logy=logy,
                normalizeByCrossSection=True
            )
            
        
        '''
        self.module("Unfolding").symmetrizeSystSum(
            histSumNominal,
            sysResults
        )
        '''
        for isys,sys in enumerate(sorted(systematics)):
            self.module("Drawing").plotEnvelopeHistogram(
                nominalResult["nominalGen_pos"],nominalResult["unfolded_pos"],sysResults[isys][1]["Up"],sysResults[isys][1]["Down"],
                os.path.join(outputFolder,self.module("Samples").getChannelName(channels)+"_possym_"+sys),
                title=self.module("Samples").getPlotTitle(channels,1)+"#kern[-0.5]{ }+#kern[-0.5]{ }jets",
                xaxis=xtitle,yaxis=ytitleSum,logy=logy,
                normalizeByCrossSection=True
            )
            
            
            self.module("Drawing").plotEnvelopeHistogram(
                nominalResult["nominalGen_neg"],nominalResult["unfolded_neg"],sysResults[isys][-1]["Up"],sysResults[isys][-1]["Down"],
                os.path.join(outputFolder,self.module("Samples").getChannelName(channels)+"_negsym_"+sys),
                title=self.module("Samples").getPlotTitle(channels,-1)+"#kern[-0.5]{ }+#kern[-0.5]{ }jets",
                xaxis=xtitle,yaxis=ytitleSum,logy=logy,
                normalizeByCrossSection=True
            )
            
            self.module("Drawing").plotEnvelopeHistogram(
                nominalResultSum,histSumNominal,sysResults[isys][0]["Up"]["hist"],sysResults[isys][0]["Down"]["hist"],
                os.path.join(outputFolder,self.module("Samples").getChannelName(channels)+"_sumsym_"+sys),
                title=self.module("Samples").getPlotTitle(channels,0)+"#kern[-0.5]{ }+#kern[-0.5]{ }jets",
                xaxis=xtitle,yaxis=ytitleSum,logy=logy,
                normalizeByCrossSection=True
            )
            
        
        genBinning = self.module("Unfolding").getGenBinning(channelName)
        
        
        
        
        ### total xsec ###
        #this is a reflection of the stat uncertainty only
        histSumNominal,covSumNominal = self.module("Unfolding").calculateSum(
            nominalResult["unfolded_pos"],
            nominalResult["unfolded_neg"],
            nominalResult["covarianceUnfolded"]
        )
        histSumAllExcl,covSumAllExcl = self.module("Unfolding").calculateSum(
            allExclResult["unfolded_pos"],
            allExclResult["unfolded_neg"],
            allExclResult["covarianceUnfolded"]
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
        
        
        
        for ibin in range(len(genBinning)-1):
            for jbin in range(len(genBinning)-1):
                covSumTotal[ibin][jbin]+=(0.025*histSumTotal.GetBinContent(ibin+1))*(0.025*histSumTotal.GetBinContent(jbin+1))
            histSumTotal.SetBinError(
                ibin+1,
                math.sqrt(histSumTotal.GetBinError(ibin+1)**2+(0.025*histSumTotal.GetBinContent(ibin+1))**2)
            )
        
        covSumNominalCorrelation = self.module("Utils").calculateCorrelationsNumpy(covSumNominal)
        self.module("Drawing").drawHistogramMatrix(
            covSumNominalCorrelation,
            os.path.join(outputFolder,self.module("Samples").getChannelName(channels)+"_nominal_correlation"), 
            xaxis="unfolded "+self.module("Unfolding").getUnfoldingVariableName(),
            yaxis="unfolded "+self.module("Unfolding").getUnfoldingVariableName(),
            zaxis="correlation",
            title=self.module("Samples").getPlotTitle(channels)+"#kern[-0.5]{ }+#kern[-0.5]{ }jets"
        )
        
        covSumProfiledCorrelation = self.module("Utils").calculateCorrelationsNumpy(covSumProfiled)
        self.module("Drawing").drawHistogramMatrix(
            covSumProfiledCorrelation,
            os.path.join(outputFolder,self.module("Samples").getChannelName(channels)+"_profiled_correlation"), 
            xaxis="unfolded "+self.module("Unfolding").getUnfoldingVariableName(),
            yaxis="unfolded "+self.module("Unfolding").getUnfoldingVariableName(),
            zaxis="correlation",
            title=self.module("Samples").getPlotTitle(channels)+"#kern[-0.5]{ }+#kern[-0.5]{ }jets"
        )
        
        covSumTotalCorrelation = self.module("Utils").calculateCorrelationsNumpy(covSumTotal)
        self.module("Drawing").drawHistogramMatrix(
            covSumTotalCorrelation,
            os.path.join(outputFolder,self.module("Samples").getChannelName(channels)+"_total_correlation"), 
            xaxis="unfolded "+self.module("Unfolding").getUnfoldingVariableName(),
            yaxis="unfolded "+self.module("Unfolding").getUnfoldingVariableName(),
            zaxis="correlation",
            title=self.module("Samples").getPlotTitle(channels)+"#kern[-0.5]{ }+#kern[-0.5]{ }jets"
        )
        
        
        ### normalized xsec ###
        #this is a reflection of the stat uncertainty only
        histSumNominalNorm,covSumNominalNorm = self.module("Unfolding").calculateSumNorm(
            nominalResult["unfolded_pos"],
            nominalResult["unfolded_neg"],
            nominalResult["covarianceUnfolded"]
        )
        histSumAllExclNorm,covSumAllExclNorm = self.module("Unfolding").calculateSumNorm(
            allExclResult["unfolded_pos"],
            allExclResult["unfolded_neg"],
            allExclResult["covarianceUnfolded"]
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
        histRatioAllExcl,covRatioAllExcl = self.module("Unfolding").calculateRatio(
            allExclResult["unfolded_pos"],
            allExclResult["unfolded_neg"],
            allExclResult["covarianceUnfolded"]
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
        
        histSumProfiledSystDict = {}
        histSumNormProfiledSystDict = {}
        histRatioProfiledSystDict = {}
        for profSystName in profiledResultSyst.keys():
            histSumProfiledSyst,covSumProfiledSyst = self.module("Unfolding").calculateSum(
                profiledResultSyst[profSystName]["unfolded_pos"],
                profiledResultSyst[profSystName]["unfolded_neg"],
                profiledResultSyst[profSystName]["covarianceUnfolded"]
            )
            histSumProfiledSystDict[profSystName] = {"hist":histSumProfiledSyst, "cov":covSumProfiledSyst}
        
            histSumProfiledNormSyst,covSumProfiledNormSyst = self.module("Unfolding").calculateSumNorm(
                profiledResultSyst[profSystName]["unfolded_pos"],
                profiledResultSyst[profSystName]["unfolded_neg"],
                profiledResultSyst[profSystName]["covarianceUnfolded"]
            )
            histSumNormProfiledSystDict[profSystName] = {"hist":histSumProfiledNormSyst, "cov":covSumProfiledNormSyst}
        
            histRatioProfiledSyst,covRatioProfiledSyst = self.module("Unfolding").calculateRatio(
                profiledResultSyst[profSystName]["unfolded_pos"],
                profiledResultSyst[profSystName]["unfolded_neg"],
                profiledResultSyst[profSystName]["covarianceUnfolded"]
            )
            histRatioProfiledSystDict[profSystName] = {"hist":histRatioProfiledSyst, "cov":covRatioProfiledSyst}
            
            
        
        for ibin in range(histSumProfiledNorm.GetNbinsX()):
            if math.fabs(histSumProfiled.GetBinError(ibin+1)-math.sqrt(covSumProfiled[ibin][ibin]))/histSumProfiled.GetBinError(ibin+1)>0.0001:
                self._logger.critical("Covariance matrix and histogram error do not agree! "+str(histSumProfiled.GetBinError(ibin+1))+" vs. "+str(math.sqrt(covSumProfiled[ibin][ibin])))
                sys.exit(1)
            if math.fabs(histSumTotal.GetBinError(ibin+1)-math.sqrt(covSumTotal[ibin][ibin]))/histSumTotal.GetBinError(ibin+1)>0.0001:
                self._logger.critical("Covariance matrix and histogram error do not agree! "+str(histSumTotal.GetBinError(ibin+1))+" vs. "+str(math.sqrt(covSumTotal[ibin][ibin])))
                sys.exit(1)
            if math.fabs(histSumProfiledNorm.GetBinError(ibin+1)-math.sqrt(covSumProfiledNorm[ibin][ibin]))/histSumProfiledNorm.GetBinError(ibin+1)>0.0001:
                self._logger.critical("Covariance matrix and histogram error do not agree! "+str(histSumProfiledNorm.GetBinError(ibin+1))+" vs. "+str(math.sqrt(covSumProfiledNorm[ibin][ibin])))
                sys.exit(1)
            if math.fabs(histSumTotalNorm.GetBinError(ibin+1)-math.sqrt(covSumTotalNorm[ibin][ibin]))/histSumTotalNorm.GetBinError(ibin+1)>0.0001:
                self._logger.critical("Covariance matrix and histogram error do not agree! "+str(histSumTotalNorm.GetBinError(ibin+1))+" vs. "+str(math.sqrt(covSumTotalNorm[ibin][ibin])))
                sys.exit(1)
        
        
        self.module("Drawing").plotCompareHistogram(nominalResult["nominalGen_pos"],
            [nominalResult["unfolded_pos"],profiledResult["unfolded_pos"],profiledResult["unfolded_pos"]],
            os.path.join(outputFolder,self.module("Samples").getChannelName(channels)+"_"+self.module("Samples").getChargeName(1)+"_compareHist"),
            title=self.module("Samples").getPlotTitle(channels,1)+"#kern[-0.5]{ }+#kern[-0.5]{ }jets",xaxis=xtitle,yaxis=ytitleSum,logy=unfoldingName=="pt" or unfoldingName=="lpt" or unfoldingName=="wpt",normalizeByCrossSection=True
        )
        
        self.module("Drawing").plotCompareHistogram(nominalResult["nominalGen_neg"],
            [nominalResult["unfolded_neg"],profiledResult["unfolded_neg"],profiledResult["unfolded_neg"]],
            os.path.join(outputFolder,self.module("Samples").getChannelName(channels)+"_"+self.module("Samples").getChargeName(-1)+"_compareHist"),
            title=self.module("Samples").getPlotTitle(channels,-1)+"#kern[-0.5]{ }+#kern[-0.5]{ }jets",xaxis=xtitle,yaxis=ytitleSum,logy=unfoldingName=="pt" or unfoldingName=="lpt" or unfoldingName=="wpt",normalizeByCrossSection=True
        )
        
        self.module("Drawing").plotCompareHistogram(nominalResult["nominalGen_inc"],
            [histSumNominal,histSumProfiled,histSumTotal],
            os.path.join(outputFolder,self.module("Samples").getChannelName(channels)+"_"+self.module("Samples").getChargeName(0)+"_compareHist"),
            title=self.module("Samples").getPlotTitle(channels,0)+"#kern[-0.5]{ }+#kern[-0.5]{ }jets",xaxis=xtitle,yaxis=ytitleSum,logy=unfoldingName=="pt" or unfoldingName=="lpt" or unfoldingName=="wpt",normalizeByCrossSection=True
        ) 
        
        self.module("Utils").normalizeByCrossSection(histSumNominal)
        self.module("Utils").normalizeByCrossSection(histSumProfiled)
        self.module("Utils").normalizeByCrossSection(histSumAllExcl)
        self.module("Utils").normalizeByCrossSection(histSumTotal)
        
        self.module("Utils").normalizeCovByCrossSection2D(genBinning,covSumNominal)
        self.module("Utils").normalizeCovByCrossSection2D(genBinning,covSumProfiled)
        self.module("Utils").normalizeCovByCrossSection2D(genBinning,covSumAllExcl)
        self.module("Utils").normalizeCovByCrossSection2D(genBinning,covSumTotal)
        
        genHistSum = nominalResult["nominalGen_inc"]
        genHistSumNorm = genHistSum.Clone(genHistSum.GetName()+"norm")
        genHistSumNorm.Scale(1./genHistSumNorm.Integral())
        
        self.module("Utils").normalizeByCrossSection(genHistSum)
        genHistRatio = nominalResult["ratioGen"]
        
        genHistSums = [
            {"name":"powheg4fs","hist":genHistSum, "legend":"POWHEG 4FS"},#kern[-0.5]{ }+#kern[-0.5]{ }Pythia#kern[-0.6]{ }8"}
        ]
        genHistSumsNorm = [
            {"name":"powheg4fs","hist":genHistSumNorm, "legend":"POWHEG 4FS"},#kern[-0.5]{ }+#kern[-0.5]{ }Pythia#kern[-0.6]{ }8"}
        ]
        
        genPredictions = self.getPredictions(channels,unfoldingName,unfoldingLevel)
        for pred in genPredictions:

            genPrediction = pred[0].Clone(pred[0].GetName()+str(random.random()))
            self.module("Utils").normalizeByCrossSection(genPrediction)
            genHistSums.append({
                "name":pred["key"],"hist":genPrediction,"legend":pred["legend"]
            })
            genPredictionNorm = pred[0].Clone(pred[0].GetName()+"norm")
            genPredictionNorm.Scale(1./genPredictionNorm.Integral())
            self.module("Utils").normalizeByBinWidth(genPredictionNorm)
            genHistSumsNorm.append({
                "name":pred["key"],"hist":genPredictionNorm,"legend":pred["legend"]
            })
            
            
        sysDictNames = {
            "pdf":"PDF",
            "pdfFull":"PDF",
            "pdftch":"PDF $t$-ch.",
            "pdfBkg":"PDF bkg.",
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
        
        self.module("Utils").createFolder("final/"+channelName)
        finalFolder = self.module("Utils").getOutputFolder("final/"+channelName)
        
        if (unfoldingName=="cos" or unfoldingName=="cosTau") and unfoldingLevel=="parton":
            asymSysSummaryDict = {}
        
        
            asymmetryGen = self.module("Asymmetry").calculateAsymmetry(genHistSumNorm)
            asymmetryStat = self.module("Asymmetry").fitDistribution(histSumAllExcl,covSumAllExcl)
            asymmetryStatNoCorr = self.module("Asymmetry").fitDistribution(histSumAllExcl,covSumAllExcl,ignoreCorr=True)
            asymmetryProfiled = self.module("Asymmetry").fitDistribution(histSumProfiled,covSumProfiled)
            asymmetryProfiledNoCorr = self.module("Asymmetry").fitDistribution(histSumProfiled,covSumProfiled,ignoreCorr=True)
            asymmetryTotal = self.module("Asymmetry").fitDistribution(histSumTotal,covSumTotal)
            asymmetryTotalNoCorr = self.module("Asymmetry").fitDistribution(histSumTotal,covSumTotal,ignoreCorr=True)
            
            
            asymSysSummaryDict['gen'] = asymmetryGen
            asymSysSummaryDict['stat'] = asymmetryStat[1]/asymmetryStat[0]*asymmetryProfiled[0]
            asymSysSummaryDict['prof'] = asymmetryProfiled[1]
            asymSysSummaryDict['total'] = asymmetryTotal[1]
            asymSysSummaryDict['central'] = asymmetryTotal[0]
            
            asymUncProf2 = 0.
            for profSystName in profiledResultSyst.keys():
                histSumProfiledSyst,covSumProfiledSyst = self.module("Unfolding").calculateSum(
                    profiledResultSyst[profSystName]["unfolded_pos"],
                    profiledResultSyst[profSystName]["unfolded_neg"],
                    profiledResultSyst[profSystName]["covarianceUnfolded"]
                )
                
                self.module("Utils").normalizeByCrossSection(histSumProfiledSyst)
                self.module("Utils").normalizeCovByCrossSection2D(genBinning,covSumProfiledSyst)
                
                asySystInc = self.module("Asymmetry").fitDistribution(
                    histSumProfiledSyst,
                    covSumProfiledSyst,
                )
                unc2 = max(0,asymmetryProfiled[1]**2-(asySystInc[1]/asySystInc[0]*asymmetryProfiled[0])**2)
                
                asymUncProf2 += unc2
                self._logger.info("Meas. syst (%30s): %5.2f+-%5.2f, only: +-%5.2f"%(
                    profSystName,
                    100.*asySystInc[0],100.*asySystInc[1],
                    100.*math.sqrt(unc2)
                ))
                
                asymSysSummaryDict[profSystName] = math.sqrt(unc2)
                      
            self._logger.info("Meas. syst (%30s): +-%5.2f, fit: +-%5.2f"%(
                "Prof sum",
                100.*math.sqrt(asymUncProf2+asymmetryStat[1]**2),
                100.*asymmetryProfiled[1]
            ))
            
            asymUnc2 = (asymmetryProfiled[1])**2
            for isys,sys in enumerate(sorted(systematics)):
                
                #this is the envelope of all systematics
                histSumAsymSystExcl,covSumAsymSystExcl = self.module("Unfolding").calculateSum(
                    profiledResult["unfolded_pos"],
                    profiledResult["unfolded_neg"],
                    profiledResult["covarianceUnfolded"],
                    {1:nominalResult["unfolded_pos"],-1:nominalResult["unfolded_neg"]},
                    #sysResults[isys:isys+1]
                    sysResults[:isys]+sysResults[isys+1:]
                )
                histSumAsymSystIncl,covSumAsymSystIncl = self.module("Unfolding").calculateSum(
                    profiledResult["unfolded_pos"],
                    profiledResult["unfolded_neg"],
                    profiledResult["covarianceUnfolded"],
                    {1:nominalResult["unfolded_pos"],-1:nominalResult["unfolded_neg"]},
                    sysResults[isys:isys+1]
                    #sysResults[:isys]+sysResults[isys+1:]
                )
                self.module("Utils").normalizeByCrossSection(histSumAsymSystExcl)
                self.module("Utils").normalizeCovByCrossSection2D(genBinning,covSumAsymSystExcl)
                
                self.module("Utils").normalizeByCrossSection(histSumAsymSystIncl)
                self.module("Utils").normalizeCovByCrossSection2D(genBinning,covSumAsymSystIncl)
                
                asySystExcl = self.module("Asymmetry").fitDistribution(
                    histSumAsymSystExcl,
                    covSumAsymSystExcl
                )
                asySystIncl = self.module("Asymmetry").fitDistribution(
                    histSumAsymSystIncl,
                    covSumAsymSystIncl
                )
                maxSystAsymExcl2=max((asymmetryTotal[1])**2-(asySystExcl[1])**2,0)
                maxSystAsymIncl2=max((asySystIncl[1])**2-(asymmetryProfiled[1])**2,0)
                maxSystAsym2 = max(maxSystAsymExcl2,maxSystAsymIncl2)
                asymUnc2+=maxSystAsym2
                
                asymSysSummaryDict[sys] = math.sqrt(maxSystAsym2)
                
                self._logger.info("Meas. syst (%30s): %5.2f+-%5.2f/%5.2f+-%5.2f, max=%5.2f"%(
                    sysDictNames[sys],
                    100.*asySystExcl[0],100.*asySystExcl[1],
                    100.*asySystIncl[0],100.*asySystIncl[1],
                    100.*math.sqrt(maxSystAsym2))
                )
                
            self._logger.info("Gen asymmetry:                   %5.3f"%(asymmetryGen))
            self._logger.info("Meas. asymmetry (stat):          %5.2f+-%5.2f"%(100.*asymmetryStat[0],100.*asymmetryStat[1]))
            self._logger.info("Meas. asymmetry (stat, no corr): %5.2f+-%5.2f"%(100.*asymmetryStatNoCorr[0],100.*asymmetryStatNoCorr[1]))
            self._logger.info("Meas. asymmetry (prof):           %5.2f+-%5.2f"%(100.*asymmetryProfiled[0],100.*asymmetryProfiled[1]))
            self._logger.info("Meas. asymmetry (prof, no corr):  %5.2f+-%5.2f"%(100.*asymmetryProfiledNoCorr[0],100.*asymmetryProfiledNoCorr[1]))
            self._logger.info("Meas. asymmetry (tot):           %5.2f+-%5.2f"%(100.*asymmetryTotal[0],100.*asymmetryTotal[1]))
            self._logger.info("Meas. asymmetry (tot, no corr):  %5.2f+-%5.2f"%(100.*asymmetryTotalNoCorr[0],100.*asymmetryTotalNoCorr[1]))
            
            self._logger.info("Exp. unc: +-%5.2f"%(100.*math.sqrt(max((asymmetryProfiled[1]/asymmetryProfiled[0])**2-(asymmetryStat[1]/asymmetryStat[0])**2,0)*asymmetryTotal[0])))
            self._logger.info("Tot summed unc: +-%5.2f, summed/tot-1: +%5.2f%%"%(
                100.*math.sqrt(asymUnc2),
                100.*math.sqrt(asymUnc2)/asymmetryTotal[1]-100.
            ))
            
            with open(os.path.join(finalFolder,unfoldingName+"_"+unfoldingLevel+"_"+channelName+"_asymSysSummary.json"),'w') as fasymSysSummary:
                json.dump(asymSysSummaryDict, fasymSysSummary, ensure_ascii=True, check_circular=True, allow_nan=True, cls=None, indent=4, sort_keys=True)
        
        
        self.module("Utils").normalizeByBinWidth(histSumNominalNorm)
        self.module("Utils").normalizeByBinWidth(histSumProfiledNorm)
        self.module("Utils").normalizeByBinWidth(histSumAllExclNorm)
        self.module("Utils").normalizeByBinWidth(histSumTotalNorm)
        self.module("Utils").normalizeByBinWidth(genHistSumNorm)
        
        self.module("Utils").normalizeCovByBinWidth(genBinning,covSumNominalNorm)
        self.module("Utils").normalizeCovByBinWidth(genBinning,covSumProfiledNorm)
        self.module("Utils").normalizeCovByBinWidth(genBinning,covSumAllExclNorm)
        self.module("Utils").normalizeCovByBinWidth(genBinning,covSumTotalNorm)
        
        for profSystName in profiledResultSyst.keys():
            self.module("Utils").normalizeByCrossSection(histSumProfiledSystDict[profSystName]['hist'])
            self.module("Utils").normalizeCovByCrossSection2D(genBinning,histSumProfiledSystDict[profSystName]['cov'])
            
            self.module("Utils").normalizeByBinWidth(histSumNormProfiledSystDict[profSystName]['hist'])
            self.module("Utils").normalizeCovByBinWidth(genBinning,histSumNormProfiledSystDict[profSystName]['cov'])

  
        sysSummaryDict = {"sum":{},"norm":{},"ratio":{},"binning":list(genBinning),"unit":unit}
                

        sysSummaryDict['sum']['central'] = [histSumTotal.GetBinContent(ibin+1) for ibin in range(len(genBinning)-1)]
        sysSummaryDict['norm']['central'] = [histSumTotalNorm.GetBinContent(ibin+1) for ibin in range(len(genBinning)-1)]
        sysSummaryDict['ratio']['central'] = [histRatioTotal.GetBinContent(ibin+1) for ibin in range(len(genBinning)-1)]
            
  
        totalSystSum2 = numpy.zeros(len(genBinning)-1)
        totalSystSumNorm2 = numpy.zeros(len(genBinning)-1)
        totalSystRatio2 = numpy.zeros(len(genBinning)-1)
        
        profSystSum2 = numpy.zeros(len(genBinning)-1)
        profSystSumNorm2 = numpy.zeros(len(genBinning)-1)
        profSystRatio2 = numpy.zeros(len(genBinning)-1)

        
        print "Profiled breakdown (sum/norm/ratio)","="*50
        print "%20s: "%("Stat"),
        
  
        for ibin in range(len(genBinning)-1):
            nominalSum = histSumAllExcl.GetBinContent(ibin+1)
            nominalNorm = histSumAllExclNorm.GetBinContent(ibin+1)
            nominalRatio = histRatioAllExcl.GetBinContent(ibin+1)
            
            profSum = histSumProfiled.GetBinContent(ibin+1)
            profNorm = histSumProfiledNorm.GetBinContent(ibin+1)
            profRatio = histRatioProfiled.GetBinContent(ibin+1)
        
            nominalSumErr = histSumAllExcl.GetBinError(ibin+1)/nominalSum*profSum
            nominalNormErr = histSumAllExclNorm.GetBinError(ibin+1)/nominalNorm*profNorm
            nominalRatioErr = histRatioAllExcl.GetBinError(ibin+1)/nominalRatio*profRatio
            
            profSystSum2[ibin]+=nominalSumErr**2
            profSystSumNorm2[ibin]+=nominalNormErr**2
            profSystRatio2[ibin]+=nominalRatioErr**2
            
            
            print "%6.1f/%6.1f/%6.1f  "%(
                100.*(nominalSumErr/profSum),
                100.*(nominalNormErr/profNorm),
                100.*(nominalRatioErr/profRatio),
            ),
        print
        
        for profSystName in sorted(profiledResultSyst.keys()):
            print "%20s: "%profSystName,
            
            sysSummaryDict['sum'][profSystName] = [0]*(len(genBinning)-1)
            sysSummaryDict['norm'][profSystName] = [0]*(len(genBinning)-1)
            sysSummaryDict['ratio'][profSystName] = [0]*(len(genBinning)-1)
            
            for ibin in range(len(genBinning)-1):
                profSum = histSumProfiled.GetBinContent(ibin+1)
                profNorm = histSumProfiledNorm.GetBinContent(ibin+1)
                profRatio = histRatioProfiled.GetBinContent(ibin+1)
            
                profSumErr = histSumProfiled.GetBinError(ibin+1)
                profNormErr = histSumProfiledNorm.GetBinError(ibin+1)
                profRatioErr = histRatioProfiled.GetBinError(ibin+1)
                
                systSumErr = histSumProfiledSystDict[profSystName]['hist'].GetBinError(ibin+1)/histSumProfiledSystDict[profSystName]['hist'].GetBinContent(ibin+1)*profSum
                systNormErr = histSumNormProfiledSystDict[profSystName]['hist'].GetBinError(ibin+1)/histSumNormProfiledSystDict[profSystName]['hist'].GetBinContent(ibin+1)*profNorm
                systRatioErr = histRatioProfiledSystDict[profSystName]['hist'].GetBinError(ibin+1)/histRatioProfiledSystDict[profSystName]['hist'].GetBinContent(ibin+1)*profRatio
                
                profSystSum2[ibin]+=max(0,profSumErr**2-systSumErr**2)
                profSystSumNorm2[ibin]+=max(0,profNormErr**2-systNormErr**2)
                profSystRatio2[ibin]+=max(0,profRatioErr**2-systRatioErr**2)
                
                sysSummaryDict['sum'][profSystName][ibin] = math.sqrt(max(0,profSumErr**2-systSumErr**2))
                sysSummaryDict['norm'][profSystName][ibin] = math.sqrt(max(0,profNormErr**2-systNormErr**2))
                sysSummaryDict['ratio'][profSystName][ibin] = math.sqrt(max(0,profRatioErr**2-systRatioErr**2))
                
                
                print "%6.1f/%6.1f/%6.1f  "%(
                    100.*(math.sqrt(max(0,profSumErr**2-systSumErr**2))/profSum),
                    100.*(math.sqrt(max(0,profNormErr**2-systNormErr**2))/profNorm),
                    100.*(math.sqrt(max(0,profRatioErr**2-systRatioErr**2))/profRatio),
                ),
            print
            
            
        print "%20s: "%("Prof (sum)"),
        for ibin in range(len(genBinning)-1):
            profSum = histSumProfiled.GetBinContent(ibin+1)
            profNorm = histSumProfiledNorm.GetBinContent(ibin+1)
            profRatio = histRatioProfiled.GetBinContent(ibin+1)
        
            profSumErr = histSumProfiled.GetBinError(ibin+1)
            profNormErr = histSumProfiledNorm.GetBinError(ibin+1)
            profRatioErr = histRatioProfiled.GetBinError(ibin+1)
            print "%6.1f/%6.1f/%6.1f  "%(
                100.*(math.sqrt(profSystSum2[ibin])/profSum),
                100.*(math.sqrt(profSystSumNorm2[ibin])/profNorm),
                100.*(math.sqrt(profSystRatio2[ibin])/profRatio),
            ),
        print
        print "%20s: "%("Prof"),
        for ibin in range(len(genBinning)-1):
            profSum = histSumProfiled.GetBinContent(ibin+1)
            profNorm = histSumProfiledNorm.GetBinContent(ibin+1)
            profRatio = histRatioProfiled.GetBinContent(ibin+1)
        
            profSumErr = histSumProfiled.GetBinError(ibin+1)
            profNormErr = histSumProfiledNorm.GetBinError(ibin+1)
            profRatioErr = histRatioProfiled.GetBinError(ibin+1)
            print "%6.1f/%6.1f/%6.1f  "%(
                100.*(profSumErr/profSum),
                100.*(profNormErr/profNorm),
                100.*(profRatioErr/profRatio),
            ),
        print
  

        for ibin in range(len(genBinning)-1):
            profErr = histSumProfiled.GetBinError(ibin+1)
            profErrNorm = histSumProfiledNorm.GetBinError(ibin+1)
            profRatioErr = histRatioProfiled.GetBinError(ibin+1)

                
            totalSystSum2[ibin]+=profErr**2
            totalSystSumNorm2[ibin]+=profErrNorm**2
            totalSystRatio2[ibin]+=profRatioErr**2
            
        
        sysSummaryDict['sum']['stat'] = [histSumAllExcl.GetBinError(ibin+1) for ibin in range(len(genBinning)-1)]
        sysSummaryDict['norm']['stat'] = [histSumAllExclNorm.GetBinError(ibin+1) for ibin in range(len(genBinning)-1)]
        sysSummaryDict['ratio']['stat'] = [histRatioAllExcl.GetBinError(ibin+1) for ibin in range(len(genBinning)-1)]
        
        sysSummaryDict['sum']['prof'] = [histSumProfiled.GetBinError(ibin+1) for ibin in range(len(genBinning)-1)]
        sysSummaryDict['norm']['prof'] = [histSumProfiledNorm.GetBinError(ibin+1) for ibin in range(len(genBinning)-1)]
        sysSummaryDict['ratio']['prof'] = [histRatioProfiled.GetBinError(ibin+1) for ibin in range(len(genBinning)-1)]
        
            
        
        
        for isys,sys in enumerate(sorted(systematics)):
            
            
            sysHistUp = sysResults[isys][0]["Up"]["hist"]
            sysHistDown = sysResults[isys][0]["Down"]["hist"]
            
            sysHistUpNorm = sysHistUp.Clone(sysHistUp.GetName()+"norm")
            sysHistDownNorm = sysHistDown.Clone(sysHistDown.GetName()+"norm")
            
            
            self.module("Utils").normalizeByCrossSection(sysHistUp)
            self.module("Utils").normalizeByCrossSection(sysHistDown)

            sysHistUpNorm.Scale(1./sysHistUpNorm.Integral())
            sysHistDownNorm.Scale(1./sysHistDownNorm.Integral())
                
            self.module("Utils").normalizeByBinWidth(sysHistUpNorm)
            self.module("Utils").normalizeByBinWidth(sysHistDownNorm)
            
            
            
            sysSummaryDict['sum'][sys] = []
            sysSummaryDict['norm'][sys] = []
            sysSummaryDict['ratio'][sys] = []
                
            for ibin in range(len(genBinning)-1):
                relUp = math.fabs(
                    sysHistUp.GetBinContent(ibin+1)-\
                    histSumNominal.GetBinContent(ibin+1)
                )/histSumTotal.GetBinContent(ibin+1)
                relDown = math.fabs(
                    sysHistDown.GetBinContent(ibin+1)-\
                    histSumNominal.GetBinContent(ibin+1)
                )/histSumTotal.GetBinContent(ibin+1)

                relUpNorm = math.fabs(
                    sysHistUpNorm.GetBinContent(ibin+1)-\
                    histSumNominalNorm.GetBinContent(ibin+1)
                )/histSumTotalNorm.GetBinContent(ibin+1)
                relDownNorm = math.fabs(
                    sysHistDownNorm.GetBinContent(ibin+1)-\
                    histSumNominalNorm.GetBinContent(ibin+1)
                )/histSumTotalNorm.GetBinContent(ibin+1)

                relUpRatio = math.fabs(
                    sysResults[isys][0]["Up"]["ratio"].GetBinContent(ibin+1)-\
                    histRatioNominal.GetBinContent(ibin+1)
                )/histRatioTotal.GetBinContent(ibin+1)
                relDownRatio = math.fabs(
                    sysResults[isys][0]["Down"]["ratio"].GetBinContent(ibin+1)-\
                    histRatioNominal.GetBinContent(ibin+1)
                )/histRatioTotal.GetBinContent(ibin+1)

                sysSummaryDict['sum'][sys].append(max(relUp,relDown)*histSumTotal.GetBinContent(ibin+1))
                sysSummaryDict['norm'][sys].append(max(relUpNorm,relDownNorm)*histSumTotalNorm.GetBinContent(ibin+1))
                sysSummaryDict['ratio'][sys].append(max(relUpRatio,relDownRatio)*histRatioTotal.GetBinContent(ibin+1))
            
                totalSystSum2[ibin]+=(max(relUp,relDown)*histSumTotal.GetBinContent(ibin+1))**2
                totalSystSumNorm2[ibin]+=(max(relUpNorm,relDownNorm)*histSumTotalNorm.GetBinContent(ibin+1))**2
                totalSystRatio2[ibin]+=(max(relUpRatio,relDownRatio)*histRatioTotal.GetBinContent(ibin+1))**2
     
            
        sysSummaryDict['sum']['lumi'] = []
        sysSummaryDict['norm']['lumi'] = []
        sysSummaryDict['ratio']['lumi'] = []

        for ibin in range(len(genBinning)-1):
            sysSummaryDict['sum']['lumi'].append(0.025*histSumTotal.GetBinContent(ibin+1))
            sysSummaryDict['norm']['lumi'].append(0.)
            sysSummaryDict['ratio']['lumi'].append(0.)
            
            totalSystSum2[ibin] += (0.025*histSumTotal.GetBinContent(ibin+1))**2
        
                
        for ibin in range(len(genBinning)-1):
  
            self._logger.info("Total sum/norm/ratio rel. deviation bin%i: %7.2f%% / %7.2f%% / %7.2f%%"%(
                ibin+1,
                100.*math.sqrt(totalSystSum2[ibin])/(histSumTotal.GetBinError(ibin+1))-100.,
                100.*math.sqrt(totalSystSumNorm2[ibin])/(histSumTotalNorm.GetBinError(ibin+1))-100.,
                100.*math.sqrt(totalSystRatio2[ibin])/histRatioTotal.GetBinError(ibin+1)-100.
            ))
            
        sysSummaryDict['sum']['total'] = [histSumTotal.GetBinError(ibin+1) for ibin in range(len(genBinning)-1)]
        sysSummaryDict['norm']['total'] = [histSumTotalNorm.GetBinError(ibin+1) for ibin in range(len(genBinning)-1)]
        sysSummaryDict['ratio']['total'] = [histRatioTotal.GetBinError(ibin+1) for ibin in range(len(genBinning)-1)]
            
  
        

        
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
                yminTest = min([genHistSum["hist"].GetBinContent(ibin+1),histSumTotal.GetBinContent(ibin+1)-histSumTotal.GetBinError(ibin+1)])
                if yminTest>0:
                    ymin = min(ymin,yminTest)
                ymax = max([ymax,genHistSum["hist"].GetBinContent(ibin+1),histSumTotal.GetBinContent(ibin+1)+histSumTotal.GetBinError(ibin+1)])
            for genHistSumNorm in genHistSumsNorm:
                yminNormTest = min([genHistSumNorm["hist"].GetBinContent(ibin+1),histSumTotalNorm.GetBinContent(ibin+1)-histSumTotalNorm.GetBinError(ibin+1)])
                if yminNormTest>0:
                    yminNorm=min(yminNorm,yminNormTest)
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
        
        
            
        
        print "NNPDF",
        genHistsRatioNNPDF30 = genHistRatio.Clone(genHistRatio.GetName()+"nnpdf")
        #genHistsRatioNNPDF30.SetLineColor(newColor(1.,0.76,0.32).GetNumber())
        genHistsRatioNNPDF30.SetLineColor(newColor(243./255,168./255,27./255).GetNumber())
        genHistsRatioNNPDF30.SetFillColor(newColor(1.,0.96,0.62).GetNumber())
        
        genHistsRatioNNPDF30.SetLineStyle(1)
        genHistsRatioNNPDF30.SetLineWidth(2)
        genHistsRatioNNPDF30.SetFillStyle(1001)
        
        self.applyLHEVariations(
            genHistsRatioNNPDF30,
            unfoldingName,
            channels,
            unfoldingLevel,
            range(2001,2101),
            [2101,2102],
            scalePos=134.3/136.02,
            scaleNeg=80.7/80.95
        )
        
        print "MMHT",
        genHistsRatioMMHT14 = genHistRatio.Clone(genHistRatio.GetName()+"mh")
        #genHistsRatioMMHT14.SetLineColor(newColor(211./255,28./255,230./255).GetNumber())
        genHistsRatioMMHT14.SetLineColor(newColor(179./255,34./255,195./255).GetNumber())
        genHistsRatioMMHT14.SetFillColor(newColor(221./255,190./255,240./255).GetNumber())
        genHistsRatioMMHT14.SetLineStyle(3)
        genHistsRatioMMHT14.SetLineWidth(3)
        genHistsRatioMMHT14.SetFillStyle(1001)
        
        self.applyLHEVariations(
            genHistsRatioMMHT14,
            unfoldingName,
            channels,
            unfoldingLevel,
            range(4001,4052),
            [4053,4055],
            scalePos=138.3/136.02,
            scaleNeg=83.5/80.95
        )
        
        print "CT10",
        genHistsRatioCT10 = genHistRatio.Clone(genHistRatio.GetName()+"ct")
        #genHistsRatioCT10.SetLineColor(newColor(83./255,131./255,241./255).GetNumber())
        genHistsRatioCT10.SetLineColor(newColor(38./255,92./255,217./255).GetNumber())
        genHistsRatioCT10.SetFillColor(newColor(153./255,191./255,241./255).GetNumber())
        genHistsRatioCT10.SetLineStyle(11)
        genHistsRatioCT10.SetLineWidth(2)
        genHistsRatioCT10.SetFillStyle(1001)
        
        self.applyLHEVariations(
            genHistsRatioCT10,
            unfoldingName,
            channels,
            unfoldingLevel,
            range(3001,3053),
            [3054,3055],
            scalePos=135.2/136.02,
            scaleNeg=79.3/80.95
        )
        
        
        
        #choose suitable res range for plot
        resRanges = [0.23,0.46,1.]
        resRange = resRanges[-1]
        rangeMax = 0
        for ibin in range(histSumTotal.GetNbinsX()):
            c = histSumTotal.GetBinContent(ibin+1)
            e = histSumTotal.GetBinError(ibin+1)*1.3
            g = 0
            for genHistSum in genHistSums:
                g = max(g,math.fabs(genHistSum["hist"].GetBinContent(ibin+1)/c-1))
            rangeMax = max([rangeMax,e/c,g])
        print "Plot max res range: ",rangeMax
        for r in resRanges:
            if rangeMax<r:
                resRange = r
                break
                
        #choose suitable res range for plot normalized
        resRangeNorm = resRanges[-1]
        rangeMaxNorm = 0
        for ibin in range(histSumTotalNorm.GetNbinsX()):
            c = histSumTotalNorm.GetBinContent(ibin+1)
            e = histSumTotalNorm.GetBinError(ibin+1)*1.3
            g = 0
            for genHistSumNorm in genHistSumsNorm:
                g = max(g,math.fabs(genHistSumNorm["hist"].GetBinContent(ibin+1)/c-1))
            rangeMaxNorm = max([rangeMaxNorm,e/c,g])
        print "Plot max res range: ",rangeMaxNorm
        for r in resRanges:
            if rangeMaxNorm<r:
                resRangeNorm = r
                break
        
        
        #choose suitable res range for ratio
        resRangesRatio = [0.11,0.23,0.48]
        resRangeRatio = resRangesRatio[-1]
        rangeMaxRatio = 0
        for ibin in range(histRatioTotal.GetNbinsX()):
            c = histRatioTotal.GetBinContent(ibin+1)
            e = histRatioTotal.GetBinError(ibin+1)*1.3
            rangeMaxRatio = max(rangeMaxRatio,e/c)
        print "Ratio max res range: ",rangeMaxRatio
        for r in resRangesRatio:
            if rangeMaxRatio<r:
                resRangeRatio = r
                break
            
        
        resRange = 0.46
        resRangeNorm = 0.46
        resRangeRatio = 0.23
        
            
        if unfoldingName=="lpt" or unfoldingName=="y":
            legendPos = "RU"
        elif unfoldingName=="cos" or unfoldingName=="cosTau":
            if unfoldingLevel == "particle":
                legendPos = "RD"
            else:
                legendPos = "LU"
        else:
            legendPos = "LD"
        
        
            
        genHistsRatio = [
            {"name":"nnpdf","hist":genHistsRatioNNPDF30,"legend":"NNPDF#kern[-0.2]{ }3.0 NLO"},
            {"name":"ct","hist":genHistsRatioCT10,"legend":"CT#kern[-0.4]{ }10 NLO"},
            {"name":"mmht","hist":genHistsRatioMMHT14,"legend":"MMHT#kern[-0.4]{ }14 NLO"},
            
        ]
        
        covUnit = "pb#lower[-0.7]{#scale[0.7]{2}}"
        covUnitNorm = ""
        if unit!="":
            covUnit += "#kern[-0.6]{ }GeV#lower[-0.7]{#scale[0.7]{-2}}"
            covUnitNorm += "#kern[-0.6]{ }GeV#lower[-0.7]{#scale[0.7]{-2}}"
        
        self.module("Drawing").plotCovariance(
            covSumTotal, 
            os.path.join(finalFolder,unfoldingName+"_"+unfoldingLevel+"_"+channelName+"_covTotal"), 
            channelName,
            xaxis=xtitle,
            yaxis=xtitle,
            zaxis="Var#lower[0.07]{#scale[1.2]{(}}"+ytitleSumWOUnit+"#lower[0.07]{#scale[1.2]{)}}",
            unit=covUnit,
            title=self.module("Samples").getChannelTitle(channels,0)+"#kern[-0.4]{ }+#kern[-0.4]{ }jets",
            addtitle="35.9#kern[-0.2]{ }fb#lower[-0.7]{#scale[0.7]{-1}} (13#kern[-0.3]{ }TeV)",
        )
        
        self.module("Drawing").plotCovariance(
            covSumTotalNorm, 
            os.path.join(finalFolder,unfoldingName+"_"+unfoldingLevel+"_"+channelName+"_covTotalNorm"), 
            channelName,
            xaxis=xtitle,
            yaxis=xtitle,
            zaxis="Var#lower[0.07]{#scale[1.2]{(}}"+ytitleSumNormWOUnit+"#lower[0.07]{#scale[1.2]{)}}",
            unit=covUnitNorm,
            title=self.module("Samples").getChannelTitle(channels,0)+"#kern[-0.4]{ }+#kern[-0.4]{ }jets",
            addtitle="35.9#kern[-0.2]{ }fb#lower[-0.7]{#scale[0.7]{-1}} (13#kern[-0.3]{ }TeV)",
        )
        
        self.module("Drawing").plotCovariance(
            covRatioTotal, 
            os.path.join(finalFolder,unfoldingName+"_"+unfoldingLevel+"_"+channelName+"_covRatio"), 
            channelName,
            xaxis=xtitle,
            yaxis=xtitle,
            zaxis="Var#lower[0.07]{#scale[1.2]{(}}"+ytitleRatioWOUnit+"#lower[0.07]{#scale[1.2]{)}}",
            unit=covUnitNorm,
            title=self.module("Samples").getChannelTitle(channels,0)+"#kern[-0.4]{ }+#kern[-0.4]{ }jets",
            addtitle="35.9#kern[-0.2]{ }fb#lower[-0.7]{#scale[0.7]{-1}} (13#kern[-0.3]{ }TeV)",
        )

        
        self.module("Drawing").plotCrossSection(
            genHistSums,histSumProfiled,histSumTotal,ymin,ymax,logy,ytitleSum,xtitle,
            "35.9#kern[-0.2]{ }fb#lower[-0.7]{#scale[0.7]{-1}} (13#kern[-0.3]{ }TeV)",
            self.module("Samples").getChannelTitle(channels,0)+"#kern[-0.4]{ }+#kern[-0.4]{ }jets",
            legendPos,resRange,
            os.path.join(finalFolder,unfoldingName+"_"+unfoldingLevel+"_"+channelName+"_sum")
        )  
        
        self.module("Drawing").plotCrossSection(
            genHistSumsNorm,histSumProfiledNorm,histSumTotalNorm,yminNorm,ymaxNorm,logy,ytitleSumNorm,xtitle,
            "35.9#kern[-0.2]{ }fb#lower[-0.7]{#scale[0.7]{-1}} (13#kern[-0.3]{ }TeV)",
            self.module("Samples").getChannelTitle(channels,0)+"#kern[-0.4]{ }+#kern[-0.4]{ }jets",
            legendPos,resRangeNorm,
            os.path.join(finalFolder,unfoldingName+"_"+unfoldingLevel+"_"+channelName+"_sumnorm")
        ) 
        
        ymin = 0.15 if channelName=="comb" else 0.
        ymax = 0.85 if channelName=="comb" else 1.
        
        centerY = False
        if unfoldingName=="pt" or unfoldingName=="lpt" or unfoldingName=="wpt":
            centerY = True
            ytitleRatio = "   "+ytitleRatio
        
        self.module("Drawing").plotCrossSection(
            genHistsRatio,histRatioProfiled,histRatioTotal,ymin,ymax,0,ytitleRatio,xtitle,
            "35.9#kern[-0.2]{ }fb#lower[-0.7]{#scale[0.7]{-1}} (13#kern[-0.3]{ }TeV)",
            self.module("Samples").getChannelTitle(channels,0)+"#kern[-0.4]{ }+#kern[-0.4]{ }jets",
            "LD",resRangeRatio,
            os.path.join(finalFolder,unfoldingName+"_"+unfoldingLevel+"_"+channelName+"_ratio"),
            fillGen=True,
            centerY=centerY
        )  
        
        print '-'*10,"sum",'-'*30
        sysSummaryDict['sum']['gen'] = {}
        for genHistSum in genHistSums:
            chi2,chi2noCorr = self.calculateChi2(histSumTotal,genHistSum["hist"],covSumTotal,isNorm=False)
            print "%30s: %6.2f (no corr: %.2f)"%(genHistSum["legend"],chi2,chi2noCorr)
            
            sysSummaryDict['sum']['gen'][genHistSum["name"]] = {
                'pred':[genHistSum["hist"].GetBinContent(ibin+1) for ibin in range(len(genBinning)-1)],
                'chi2':chi2,
                'chi2noCorr':chi2noCorr
            }
                       
                       
        print '-'*10,"norm",'-'*30
        sysSummaryDict['norm']['gen'] = {}
        for genHistSumNorm in genHistSumsNorm:
            chi2,chi2noCorr = self.calculateChi2(histSumTotalNorm,genHistSumNorm["hist"],covSumTotalNorm,isNorm=True)
            print "%30s: %6.2f (no corr: %.2f)"%(genHistSumNorm["legend"],chi2,chi2noCorr)
            
            sysSummaryDict['norm']['gen'][genHistSumNorm["name"]] = {
                'pred':[genHistSumNorm["hist"].GetBinContent(ibin+1) for ibin in range(len(genBinning)-1)],
                'chi2':chi2,
                'chi2noCorr':chi2noCorr
            }
            
        print '-'*10,"ratio",'-'*30
        sysSummaryDict['ratio']['gen'] = {}
        for genHistRatio in genHistsRatio:
            chi2,chi2noCorr = self.calculateChi2(histRatioTotal,genHistRatio["hist"],covRatioTotal,isNorm=False)
            print "%30s: %6.3f (no corr: %.3f)"%(genHistRatio["legend"],chi2,chi2noCorr)
        
            sysSummaryDict['ratio']['gen'][genHistRatio["name"]] = {
                'pred':[genHistRatio["hist"].GetBinContent(ibin+1) for ibin in range(len(genBinning)-1)],
                'chi2':chi2,
                'chi2noCorr':chi2noCorr
            }
        
        with open(os.path.join(finalFolder,unfoldingName+"_"+unfoldingLevel+"_"+channelName+"_sysSummary.json"),'w') as fsysSummary:
            json.dump(sysSummaryDict, fsysSummary, ensure_ascii=True, check_circular=True, allow_nan=True, cls=None, indent=4, sort_keys=True)
        
        rootHepData = ROOT.TFile(
            os.path.join(finalFolder,unfoldingName+"_"+unfoldingLevel+"_"+channelName+"_hepdata.root"),
            "RECREATE"
        )
        
        covSumTotalHist = self.module("Drawing").makeCovHist(covSumTotal,genBinning)
        covSumTotalNormHist = self.module("Drawing").makeCovHist(covSumTotalNorm,genBinning)
        covSumRatioHist = self.module("Drawing").makeCovHist(covRatioTotal,genBinning)
        
        histSumProfiled.SetName("xsec_exponly")
        histSumProfiled.SetDirectory(rootHepData)
        histSumTotal.SetName("xsec_total")
        histSumTotal.SetDirectory(rootHepData)
        covSumTotalHist.SetName("xsec_cov")
        covSumTotalHist.SetDirectory(rootHepData)
        
        histSumProfiledNorm.SetName("xsecnorm_exponly")
        histSumProfiledNorm.SetDirectory(rootHepData)
        histSumTotalNorm.SetName("xsecnorm_total")
        histSumTotalNorm.SetDirectory(rootHepData)
        covSumTotalNormHist.SetName("xsecnorm_cov")
        covSumTotalNormHist.SetDirectory(rootHepData)
        
        histRatioProfiled.SetName("ratio_exponly")
        histRatioProfiled.SetDirectory(rootHepData)
        histRatioTotal.SetName("ratio_total")
        histRatioTotal.SetDirectory(rootHepData)
        covSumRatioHist.SetName("ratio_cov")
        covSumRatioHist.SetDirectory(rootHepData)
        
        rootHepData.Write()
        rootHepData.Close()


