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
                "legend":"aMC@NLO 4FS",#kern[-0.5]{ }+#kern[-0.5]{ }Pythia#kern[-0.6]{ }8"
            },
            {
                "name":"ST_t-channel_5f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1_GEN_v180904",
                "color":newColor(0.99,0.7,0.1),
                "style":11,
                "width":3,
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
                    0:histsInc[0],1:histsPos[0],-1:histsNeg[0],"legend":prediction["legend"]
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
                    0:histIncComb,1:histPosComb,-1:histNegComb,"legend":prediction["legend"]
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
        ytitleSum = "d#kern[-0.6]{ }#sigma#kern[-0.5]{ }#lower[0.2]{#scale[1.3]{/}}#kern[-0.8]{ }d#kern[-0.6]{ }"+self.module("Unfolding").getUnfoldingSymbol()+""
        ytitleSumNorm = "1#kern[-0.5]{ }#lower[0.2]{#scale[1.3]{/}}#kern[-0.8]{ }#sigma#kern[-0.5]{ }#times#kern[-0.3]{ }d#kern[-0.6]{ }#sigma#kern[-0.5]{ }#lower[0.2]{#scale[1.3]{/}}#kern[-0.8]{ }d#kern[-0.6]{ }"+self.module("Unfolding").getUnfoldingSymbol()+""
        ytitleRatio = "d#kern[-0.6]{ }(#sigma#lower[0.3]{#scale[0.8]{#kern[-0.5]{ }t}}#kern[-0.5]{ }/#sigma#lower[0.3]{#scale[0.8]{#kern[-0.5]{ }t+#bar{t}}}#kern[-0.5]{ })#kern[-0.5]{ }#lower[0.2]{#scale[1.3]{/}}#kern[-0.8]{ }d#kern[-0.6]{ }"+self.module("Unfolding").getUnfoldingSymbol()+""
        unit = self.module("Unfolding").getUnfoldingVariableUnit()
        logy = unfoldingName=="pt" or unfoldingName=="lpt" or unfoldingName=="wpt"
        if unit!="":
            xtitle = xtitleWOUnit+" ("+unit+")"
            ytitleSum += " (pb#kern[-0.5]{ }/#kern[-0.5]{ }"+unit+")"
            ytitleSumNorm += " (1#kern[-0.5]{ }/#kern[-0.5]{ }"+unit+")"
            ytitleRatio += " (1#kern[-0.5]{ }/#kern[-0.5]{ }"+unit+")"
        else:
            ytitleSum += " (pb)"
            xtitle = xtitleWOUnit
        
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
                    
                    dneg = cneg-0.5*(uneg-cneg)
                    dpos = cpos-0.5*(upos-cpos)
                    
                    results[-1]["Down"].SetBinContent(ibin+1,dneg)
                    results[1]["Down"].SetBinContent(ibin+1,dpos)
                    
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
            if sys.find("topMass")>=0:
                histSystSum,covSystSum = self.module("Unfolding").calculateSum(
                    sysResults[isys][1]["Up"],
                    sysResults[isys][-1]["Up"],
                    sysCov[isys]["Up"]
                )
                histSystRatio,covSystRatio = self.module("Unfolding").calculateRatio(
                    sysResults[isys][1]["Up"],
                    sysResults[isys][-1]["Up"],
                    sysCov[isys]["Up"]
                )
                sysResults[isys][0]["Up"] = {"hist":histSystSum,"cov":covSystSum,"ratio":histSystRatio,"ratioCov":covSystRatio}
        
                histSystSumDown = histSystSum.Clone(histSystSum.GetName()+"sumDown")
                histSystSumDown.SetDirectory(0)
                
                histSystRatioDown = histSystRatio.Clone(histSystRatio.GetName()+"ratioDown")
                histSystRatioDown.SetDirectory(0)
                
                for ibin in range(histSumNominal.GetNbinsX()):
                    csum = histSumNominal.GetBinContent(ibin+1)
                    usum = histSystSum.GetBinContent(ibin+1)
                    dsum = csum-0.5*(usum-csum)
                    histSystSumDown.SetBinContent(ibin+1,dsum)
                    
                    cratio = histRatioNominal.GetBinContent(ibin+1)
                    uratio = histSystRatio.GetBinContent(ibin+1)
                    dratio = cratio-0.5*(uratio-cratio)
                    histSystRatioDown.SetBinContent(ibin+1,dratio)
                    
                
                sysResults[isys][0]["Down"] = {"hist":histSystSumDown,"cov":numpy.copy(covSystSum),"ratio":histSystRatioDown,"ratioCov":numpy.copy(covSystRatio)}
                
            else:
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
            {"hist":genHistSum, "legend":"POWHEG 4FS"},#kern[-0.5]{ }+#kern[-0.5]{ }Pythia#kern[-0.6]{ }8"}
        ]
        genHistSumsNorm = [
            {"hist":genHistSumNorm, "legend":"POWHEG 4FS"},#kern[-0.5]{ }+#kern[-0.5]{ }Pythia#kern[-0.6]{ }8"}
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
            
        if (unfoldingName=="cos" or unfoldingName=="cosTau") and unfoldingLevel=="parton":
            asymmetryGen = self.module("Asymmetry").calculateAsymmetry(genHistSumNorm)
            asymmetryStat = self.module("Asymmetry").fitDistribution(histSumNominal,covSumNominal)
            asymmetryStatNoCorr = self.module("Asymmetry").fitDistribution(histSumNominal,covSumNominal,ignoreCorr=True)
            asymmetryProfiled = self.module("Asymmetry").fitDistribution(histSumProfiled,covSumProfiled)
            asymmetryProfiledNoCorr = self.module("Asymmetry").fitDistribution(histSumProfiled,covSumProfiled,ignoreCorr=True)
            asymmetryTotal = self.module("Asymmetry").fitDistribution(histSumTotal,covSumTotal)
            asymmetryTotalNoCorr = self.module("Asymmetry").fitDistribution(histSumTotal,covSumTotal,ignoreCorr=True)
            
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
                maxSystAsymExcl2=max((asymmetryTotal[1])**2-(asySystExcl[1]/asySystExcl[0]*asymmetryTotal[0])**2,0)
                maxSystAsymIncl2=max((asySystIncl[1]/asySystIncl[0]*asymmetryProfiled[0])**2-(asymmetryProfiled[1])**2,0)
                maxSystAsym2 = max(maxSystAsymExcl2,maxSystAsymIncl2)
                asymUnc2+=maxSystAsym2
                
                self._logger.info("Meas. syst (%30s): %5.2f+-%5.2f/%5.2f+-%5.2f, d=%5.2f"%(
                    sysDictNames[sys],
                    100.*asySystExcl[0],100.*asySystExcl[1],
                    100.*asySystIncl[0],100.*asySystIncl[1],
                    100.*math.sqrt(maxSystAsym2))
                )
                '''
                asyUp = self.module("Asymmetry").fitDistribution(
                    sysResults[isys][0]["Up"]["hist"],
                    sysResults[isys][0]["Up"]["cov"],ignoreCorr=True
                )
                asyDown = self.module("Asymmetry").fitDistribution(
                    sysResults[isys][0]["Down"]["hist"],
                    sysResults[isys][0]["Down"]["cov"],ignoreCorr=True
                )
                maxSystAsym = max(
                    math.fabs(asyUp[0]-asymmetryStat[0]),
                    math.fabs(asyDown[0]-asymmetryStat[0])
                )
                
                
                print "%20s, %5.3f,%5.3f, d=%5.3f"%(sysDictNames[sys],asyUp[0]-asymmetryStat[0],asyDown[0]-asymmetryStat[0],maxSystAsym)
                
                asymUnc2+=maxSystAsym**2
                #break
                '''
            self._logger.info("Gen asymmetry:                   %5.3f"%(asymmetryGen))
            self._logger.info("Meas. asymmetry (stat):          %5.2f+-%5.2f"%(100.*asymmetryStat[0],100.*asymmetryStat[1]))
            self._logger.info("Meas. asymmetry (stat, no corr): %5.2f+-%5.2f"%(100.*asymmetryStatNoCorr[0],100.*asymmetryStatNoCorr[1]))
            self._logger.info("Meas. asymmetry (exp):           %5.2f+-%5.2f"%(100.*asymmetryProfiled[0],100.*asymmetryProfiled[1]))
            self._logger.info("Meas. asymmetry (exp, no corr):  %5.2f+-%5.2f"%(100.*asymmetryProfiledNoCorr[0],100.*asymmetryProfiledNoCorr[1]))
            self._logger.info("Meas. asymmetry (tot):           %5.2f+-%5.2f"%(100.*asymmetryTotal[0],100.*asymmetryTotal[1]))
            self._logger.info("Meas. asymmetry (tot, no corr):  %5.2f+-%5.2f"%(100.*asymmetryTotalNoCorr[0],100.*asymmetryTotalNoCorr[1]))
            
            self._logger.info("Exp. unc: +-%5.2f"%(100.*math.sqrt(max((asymmetryProfiled[1]/asymmetryProfiled[0])**2-(asymmetryStat[1]/asymmetryStat[0])**2,0)*asymmetryTotal[0])))
            self._logger.info("Tot summed unc: +-%5.2f"%(100.*math.sqrt(asymUnc2)))
        
        self.module("Utils").normalizeByBinWidth(histSumProfiledNorm)
        self.module("Utils").normalizeByBinWidth(histSumTotalNorm)
        self.module("Utils").normalizeByBinWidth(genHistSumNorm)
        
        self.module("Utils").normalizeCovByBinWidth(genBinning,covSumProfiledNorm)
        self.module("Utils").normalizeCovByBinWidth(genBinning,covSumTotalNorm)
        
        chi2Total = 0.
        chi2Norm = 0.
        chi2Ratio = 0.
        
        covSumTotalInv = numpy.linalg.inv(covSumTotal)
        #cannot invert norm => singular as expected; so throw last bin away
        covSumTotalNormInv = numpy.linalg.inv(covSumTotalNorm[:-1,:-1])
        covRatioTotalInv = numpy.linalg.inv(covRatioTotal)
        
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
            
            
            for jbin in range(histSumProfiledNorm.GetNbinsX()):
                chi2Total+=(genHistSum.GetBinContent(ibin+1)-histSumTotal.GetBinContent(ibin+1))*covSumTotalInv[ibin,jbin]*(genHistSum.GetBinContent(jbin+1)-histSumTotal.GetBinContent(jbin+1))
                chi2Ratio+=(genHistRatio.GetBinContent(ibin+1)-histRatioTotal.GetBinContent(ibin+1))*covRatioTotalInv[ibin,jbin]*(genHistRatio.GetBinContent(jbin+1)-histRatioTotal.GetBinContent(jbin+1))
                #throw last bin away
                if ibin<(histSumProfiledNorm.GetNbinsX()-1) and jbin<(histSumProfiledNorm.GetNbinsX()-1):
                    chi2Norm+=(genHistSumNorm.GetBinContent(ibin+1)-histSumTotalNorm.GetBinContent(ibin+1))*covSumTotalNormInv[ibin,jbin]*(genHistSumNorm.GetBinContent(jbin+1)-histSumTotalNorm.GetBinContent(jbin+1))
 
        print "chi2/ndof: total=%.3f, norm=%.3f, ratio=%.3f"%(
            chi2Total/histSumProfiledNorm.GetNbinsX(),
            chi2Norm/(histSumProfiledNorm.GetNbinsX()-1),
            chi2Ratio/histSumProfiledNorm.GetNbinsX()
        ) 
 
                
        tabSys=""#\\hline\n"
        tabSysRatio=""#\\hline\n"
        if unit!="":
            tabSys+= "%25s "%("Bin range / "+unit)
            tabSysRatio+= "%20s"%("Bin range / "+unit)
        else:
            tabSys+= "%25s "%("Bin range ")
            tabSysRatio+= "%25s "%("Bin range ")
        for ibin in range(len(genBinning)-1):
            binStart = genBinning[ibin]
            binEnd = genBinning[ibin+1]
            if math.log10(genBinning[-1])>=2:
                tabSys+= "& $[%4.0f;%4.0f]$ "%(binStart,binEnd)
                tabSysRatio+= "& $[%4.0f;%4.0f]$ "%(binStart,binEnd)
            else:
                tabSys+= "& $[%4.2f;%4.2f]$ "%(binStart,binEnd)
                tabSysRatio+= "& $[%4.2f;%4.2f]$ "%(binStart,binEnd)
        tabSys+= "\\\\\n"
        tabSys+="\\hline\n"
        tabSysRatio+= "\\\\\n"
        tabSysRatio+="\\hline\n"
        
        if unit!="":
            tabSys+= "%25s "%("Central value (pb/"+unit+")")
            tabSysRatio+= "%25s "%("Central value (1/"+unit+")")
        else:
            tabSys+= "%25s "%("Central value (pb)")
            tabSysRatio+= "%25s "%("Central value")
        for ibin in range(len(genBinning)-1):
            value = histSumTotal.GetBinContent(ibin+1)
            if math.log10(value)>3 or math.log10(value)<3:
                tabSys+= ("& $%4.2e}$"%(histSumTotal.GetBinContent(ibin+1))).replace("e","\\cdot 10^{")
            elif math.log10(value)>0:
                tabSys+= ("& $%4.1f}$"%(histSumTotal.GetBinContent(ibin+1)))
            else:
                tabSys+= ("& $%5.3f}$"%(histSumTotal.GetBinContent(ibin+1)))
            tabSysRatio+= ("& $%6.3f$"%(histRatioTotal.GetBinContent(ibin+1)))
                
        tabSys+= "\\\\\n"
        tabSysRatio+= "\\\\\n"
        
        tabSys+= "%25s "%("Stat.")
        tabSysRatio+= "%25s "%("Stat.")
        for ibin in range(len(genBinning)-1):
            tabSys+= "& $\\pm%6.1f$\\%%"%(100.*histSumNominal.GetBinError(ibin+1)/histSumNominal.GetBinContent(ibin+1))
            tabSysRatio+= "& $\\pm%6.3f$"%(histRatioNominal.GetBinError(ibin+1))
        tabSys+= "\\\\\n"
        tabSysRatio+= "\\\\\n"
        
        totalSystSum2 = numpy.zeros(len(genBinning)-1)
        totalSystRatio2 = numpy.zeros(len(genBinning)-1)
        '''
        tabSys+= "%20s"%("Stat.+Exp.")
        for ibin in range(len(genBinning)-1):
            tabSys+= "& $\\pm%6.1f$\\%%"%(100.*histSumProfiled.GetBinError(ibin+1)/histSumProfiled.GetBinContent(ibin+1))
            totalSystSum2[ibin]+=(histSumProfiled.GetBinError(ibin+1)/histSumProfiled.GetBinContent(ibin+1))**2
        '''
        
        
        tabSys+= "%25s "%("Exp.")
        tabSysRatio+= "%25s "%("Exp.")
        for ibin in range(len(genBinning)-1):
            statErr = histSumNominal.GetBinError(ibin+1)/histSumNominal.GetBinContent(ibin+1)
            profErr = histSumProfiled.GetBinError(ibin+1)/histSumProfiled.GetBinContent(ibin+1)
            if profErr>statErr:
                tabSys+= "& $\\pm%6.1f$\\%%"%(100.*math.sqrt(profErr**2-statErr**2))
            else:
                tabSys+= "&    %6s   "%("-")
            totalSystSum2[ibin]+=(histSumProfiled.GetBinError(ibin+1)/histSumProfiled.GetBinContent(ibin+1))**2
            
            statRatioErr = histRatioNominal.GetBinError(ibin+1)
            profRatioErr = histRatioProfiled.GetBinError(ibin+1)
            if profErr>statErr:
                tabSysRatio+= "& $\\pm%6.3f$"%(math.sqrt(profRatioErr**2-statRatioErr**2))
            else:
                tabSysRatio+= "&    %6s   "%("-")
            totalSystRatio2[ibin]+=profRatioErr**2
    
            
        tabSys+= "\\\\\n"
        tabSysRatio+= "\\\\\n"
        
        
        for isys,sys in enumerate(sorted(systematics)):
            tabSys+= "%25s "%(sysDictNames[sys])
            tabSysRatio+= "%25s "%(sysDictNames[sys])
            for ibin in range(len(genBinning)-1):
                relUp = math.fabs(
                    sysResults[isys][0]["Up"]["hist"].GetBinContent(ibin+1)-\
                    histSumNominal.GetBinContent(ibin+1)
                )/histSumNominal.GetBinContent(ibin+1)
                relDown = math.fabs(
                    sysResults[isys][0]["Down"]["hist"].GetBinContent(ibin+1)-\
                    histSumNominal.GetBinContent(ibin+1)
                )/histSumNominal.GetBinContent(ibin+1)
                totalSystSum2[ibin] += max(relUp,relDown)**2
                tabSys+= "& $\\pm%6.1f$\\%%"%(100.*max(relUp,relDown))
                
                
                relUpRatio = math.fabs(
                    sysResults[isys][0]["Up"]["ratio"].GetBinContent(ibin+1)-\
                    histRatioNominal.GetBinContent(ibin+1)
                )#/histRatioNominal.GetBinContent(ibin+1)
                relDownRatio = math.fabs(
                    sysResults[isys][0]["Down"]["ratio"].GetBinContent(ibin+1)-\
                    histRatioNominal.GetBinContent(ibin+1)
                )#/histRatioNominal.GetBinContent(ibin+1)
                totalSystRatio2[ibin]+=max(relUpRatio,relDownRatio)**2
                tabSysRatio+= "& $\\pm%6.3f$"%(max(relUpRatio,relDownRatio))
            
            tabSys+= "\\\\\n"
            tabSysRatio+= "\\\\\n"
            
        tabSys+= "%25s "%("Luminosity")
        for ibin in range(len(genBinning)-1):
            lumiSyst = 0.025#*histSumTotal.GetBinContent(ibin+1)
            tabSys+= "& $\\pm%6.1f$\\%%"%(100.*0.025)
            totalSystSum2[ibin] += lumiSyst**2
        tabSys+= "\\\\\n"
            
            
        tabSys+= "\\hline\n"
        tabSys+= "%25s "%("Total")
        tabSysRatio+= "\\hline\n"
        tabSysRatio+= "%25s "%("Total")
        
        for ibin in range(len(genBinning)-1):
            tabSys+= "& $\\pm%6.1f$\\%%"%(100.*histSumTotal.GetBinError(ibin+1)/histSumTotal.GetBinContent(ibin+1))
            self._logger.info("Total sum/ratio rel. deviation bin%i: %7.2f%% / %7.2f%%"%(
                ibin+1,
                100.*math.sqrt(totalSystSum2[ibin])/(histSumTotal.GetBinError(ibin+1)/histSumTotal.GetBinContent(ibin+1))-100.,
                100.*math.sqrt(totalSystRatio2[ibin])/histRatioTotal.GetBinError(ibin+1)-100.
            ))
        
            tabSysRatio+= "& $\\pm%6.3f$"%(histRatioTotal.GetBinError(ibin+1))#/histRatioTotal.GetBinContent(ibin+1))
        tabSys+= "\\\\\n"
        tabSys+="\\hline\n"
        tabSysRatio+= "\\\\\n"
        tabSysRatio+="\\hline\n"
        
        self.module("Utils").createFolder("final/"+channelName)
        finalFolder = self.module("Utils").getOutputFolder("final/"+channelName)

        
        
        fTabSys = open(os.path.join(finalFolder,unfoldingName+"_"+unfoldingLevel+"_"+channelName+"_sum.tex"),"w")
        fTabSys.write(tabSys)
        fTabSys.close()
        
        fTabSysRatio = open(os.path.join(finalFolder,unfoldingName+"_"+unfoldingLevel+"_"+channelName+"_ratio.tex"),"w")
        fTabSysRatio.write(tabSysRatio)
        fTabSysRatio.close()
        
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
        genHistsRatioNNPDF30.SetLineColor(newColor(83./255,131./255,241./255).GetNumber())
        genHistsRatioNNPDF30.SetFillColor(newColor(153./255,191./255,241./255).GetNumber())
        
        genHistsRatioNNPDF30.SetLineColor(newColor(1.,0.76,0.32).GetNumber())
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
        genHistsRatioMMHT14.SetLineColor(newColor(211./255,28./255,230./255).GetNumber())
        genHistsRatioMMHT14.SetFillColor(newColor(221./255,190./255,240./255).GetNumber())
        genHistsRatioMMHT14.SetLineStyle(1)
        genHistsRatioMMHT14.SetLineWidth(2)
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
        genHistsRatioCT10.SetLineColor(newColor(83./255,131./255,241./255).GetNumber())
        genHistsRatioCT10.SetFillColor(newColor(153./255,191./255,241./255).GetNumber())
        genHistsRatioCT10.SetLineStyle(1)
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
            
            
        if unfoldingName=="lpt" or unfoldingName=="y":
            legendPos = "RU"
        elif unfoldingName=="cos" or unfoldingName=="cosTau":
            legendPos = "RD"
        else:
            legendPos = "LD"
        
        
            
        genHistsRatio = [
            {"hist":genHistsRatioNNPDF30,"legend":"NNPDF#kern[-0.5]{ }3.0 NLO"},
            {"hist":genHistsRatioCT10,"legend":"CT#kern[-0.5]{ }10 NLO"},
            {"hist":genHistsRatioMMHT14,"legend":"MMHT#kern[-0.5]{ }14 NLO"},
            
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
            zaxis="Covariance",
            unit=covUnit,
            title=self.module("Samples").getChannelTitle(channels,0)+"#kern[-0.5]{ }+#kern[-0.5]{ }jets",
            addtitle="36#kern[-0.5]{ }fb#lower[-0.7]{#scale[0.7]{-1}} (13TeV)"
        )
        
        self.module("Drawing").plotCovariance(
            covSumTotalNorm, 
            os.path.join(finalFolder,unfoldingName+"_"+unfoldingLevel+"_"+channelName+"_covTotalNorm"), 
            channelName,
            xaxis=xtitle,
            yaxis=xtitle,
            zaxis="Covariance",
            unit=covUnitNorm,
            title=self.module("Samples").getChannelTitle(channels,0)+"#kern[-0.5]{ }+#kern[-0.5]{ }jets",
            addtitle="36#kern[-0.5]{ }fb#lower[-0.7]{#scale[0.7]{-1}} (13TeV)"
        )
        
        self.module("Drawing").plotCovariance(
            covRatioTotal, 
            os.path.join(finalFolder,unfoldingName+"_"+unfoldingLevel+"_"+channelName+"_covRatio"), 
            channelName,
            xaxis=xtitle,
            yaxis=xtitle,
            zaxis="Covariance",
            unit=covUnitNorm,
            title=self.module("Samples").getChannelTitle(channels,0)+"#kern[-0.5]{ }+#kern[-0.5]{ }jets",
            addtitle="36#kern[-0.5]{ }fb#lower[-0.7]{#scale[0.7]{-1}} (13TeV)"
        )
        
        print "Sum uncertainties"
        for i in range(histSumTotal.GetNbinsX()):
            print histSumTotal.GetBinError(i+1),math.sqrt(covSumTotal[i,i])
        print "Norm uncertainties"
        for i in range(histSumTotalNorm.GetNbinsX()):
            print histSumTotalNorm.GetBinError(i+1),math.sqrt(covSumTotalNorm[i,i])
        print "Ratio uncertainties"
        for i in range(histRatioTotal.GetNbinsX()):
            print histRatioTotal.GetBinError(i+1),math.sqrt(covRatioTotal[i,i])
            
        
        self.module("Drawing").plotCrossSection(
            genHistSums,histSumProfiled,histSumTotal,ymin,ymax,logy,ytitleSum,xtitle,
            self.module("Samples").getChannelTitle(channels,0)+"#kern[-0.5]{ }+#kern[-0.5]{ }jets, 36#kern[-0.5]{ }fb#lower[-0.7]{#scale[0.7]{-1}} (13TeV)",
            legendPos,resRange,
            os.path.join(finalFolder,unfoldingName+"_"+unfoldingLevel+"_"+channelName+"_sum")
        )  
        
        self.module("Drawing").plotCrossSection(
            genHistSumsNorm,histSumProfiledNorm,histSumTotalNorm,yminNorm,ymaxNorm,logy,ytitleSumNorm,xtitle,
            self.module("Samples").getChannelTitle(channels,0)+"#kern[-0.5]{ }+#kern[-0.5]{ }jets, 36#kern[-0.5]{ }fb#lower[-0.7]{#scale[0.7]{-1}} (13TeV)",
            legendPos,resRangeNorm,
            os.path.join(finalFolder,unfoldingName+"_"+unfoldingLevel+"_"+channelName+"_sumnorm")
        ) 
        
        ymin = 0.25 if channelName=="comb" else 0.
        ymax = 0.85 if channelName=="comb" else 1.
        
        centerY = False
        if unfoldingName=="pt" or unfoldingName=="lpt" or unfoldingName=="wpt":
            centerY = True
            ytitleRatio = "   "+ytitleRatio
        
        self.module("Drawing").plotCrossSection(
            genHistsRatio,histRatioProfiled,histRatioTotal,ymin,ymax,0,ytitleRatio,xtitle,
            self.module("Samples").getChannelTitle(channels,0)+"#kern[-0.5]{ }+#kern[-0.5]{ }jets, 36#kern[-0.5]{ }fb#lower[-0.7]{#scale[0.7]{-1}} (13TeV)",
            "LD",resRangeRatio,
            os.path.join(finalFolder,unfoldingName+"_"+unfoldingLevel+"_"+channelName+"_ratio"),
            fillGen=True,
            centerY=centerY
        )  
        




