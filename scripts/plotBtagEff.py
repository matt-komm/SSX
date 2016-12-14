#!/usr/bin/python

import ROOT
import numpy
import scipy.optimize
import random
import math
import os
import re
from optparse import OptionParser
parser = OptionParser()
(options, args) = parser.parse_args()

ROOT.gROOT.Reset()
ROOT.gROOT.SetBatch(True)
ROOT.gStyle.SetOptStat(0)
ROOT.gStyle.SetOptFit(0)
ROOT.gROOT.Reset()
ROOT.gROOT.SetStyle("Plain")
ROOT.gStyle.SetOptStat(0)
ROOT.gStyle.SetOptFit(1111)
ROOT.gStyle.SetPadTopMargin(0.08)
ROOT.gStyle.SetPadLeftMargin(0.13)
ROOT.gStyle.SetPadRightMargin(0.26)
ROOT.gStyle.SetPadBottomMargin(0.15)
ROOT.gStyle.SetMarkerSize(0.16)
ROOT.gStyle.SetHistLineWidth(1)
ROOT.gStyle.SetStatFontSize(0.025)
ROOT.gStyle.SetLabelSize(0.055, "XYZ")

ROOT.gStyle.SetOptFit()
ROOT.gStyle.SetOptStat(0)

# For the canvas:
ROOT.gStyle.SetCanvasBorderMode(0)
ROOT.gStyle.SetCanvasColor(ROOT.kWhite)
ROOT.gStyle.SetCanvasDefH(600) #Height of canvas
ROOT.gStyle.SetCanvasDefW(600) #Width of canvas
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
ROOT.gStyle.SetHistLineColor(1)
ROOT.gStyle.SetHistLineStyle(0)
ROOT.gStyle.SetHistLineWidth(1)
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

ROOT.gStyle.SetHatchesSpacing(0.5)
ROOT.gStyle.SetHatchesLineWidth(2)

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
ROOT.gStyle.SetTitleSize(32, "XYZ")
# ROOT.gStyle.SetTitleXSize(Float_t size = 0.02) # Another way to set the size?
# ROOT.gStyle.SetTitleYSize(Float_t size = 0.02)
ROOT.gStyle.SetTitleXOffset(1.135)
#ROOT.gStyle.SetTitleYOffset(1.2)
ROOT.gStyle.SetTitleOffset(1.32, "YZ") # Another way to set the Offset

# For the axis labels:

ROOT.gStyle.SetLabelColor(1, "XYZ")
ROOT.gStyle.SetLabelFont(43, "XYZ")
ROOT.gStyle.SetLabelOffset(0.0077, "XYZ")
ROOT.gStyle.SetLabelSize(28, "XYZ")
#ROOT.gStyle.SetLabelSize(0.04, "XYZ")

# For the axis:

ROOT.gStyle.SetAxisColor(1, "XYZ")
ROOT.gStyle.SetAxisColor(1, "XYZ")
ROOT.gStyle.SetStripDecimals(True)
ROOT.gStyle.SetTickLength(0.03, "Y")
ROOT.gStyle.SetTickLength(0.05, "X")
ROOT.gStyle.SetNdivisions(505, "X")
ROOT.gStyle.SetNdivisions(512, "Y")

ROOT.gStyle.SetPadTickX(1)  # To get tick marks on the opposite side of the frame
ROOT.gStyle.SetPadTickY(1)

# Change for log plots:
ROOT.gStyle.SetOptLogx(0)
ROOT.gStyle.SetOptLogy(0)
ROOT.gStyle.SetOptLogz(0)

#ROOT.gStyle.SetPalette(1) #(1,0)

# another top group addition
ROOT.gStyle.SetHatchesSpacing(1.0)
ROOT.gStyle.SetHatchesLineWidth(2)

# Postscript options:
#ROOT.gStyle.SetPaperSize(20., 20.)
#ROOT.gStyle.SetPaperSize(ROOT.TStyle.kA4)
#ROOT.gStyle.SetPaperSize(27., 29.7)
#ROOT.gStyle.SetPaperSize(27., 29.7)
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

ROOT.gStyle.SetPaintTextFormat("4.1f")
ROOT.gStyle.SetPalette(1)
#ROOT.gStyle.SetPaintTextFormat("7.4f")


rootObj = []

def findBestChi2(fct,guess,xvalues,yvalues,yerrors):

    def chi2(x):
        chi2Sum = 0.0
        N=0
        for i in range(len(yvalues)):
            if yerrors[i]==0.0:
                continue
            N+=1
            chi2Sum+=(fct(xvalues[i],x)-yvalues[i])**2/yerrors[i]**2
            
        return chi2Sum/N if N>0 else 0.01
        
    return scipy.optimize.minimize(chi2, guess, method='BFGS')


def getEfficiency(nominatorHist, denominatorHist):
    N = nominatorHist.GetNbinsX()
    valueX = numpy.zeros(N)
    valueMean = numpy.zeros(N)
    valueUp = numpy.zeros(N)
    valueDown = numpy.zeros(N)
    valueErr = numpy.zeros(N)
    
    maxEff=0.0
    
    for ibin in range(N):
        valueX[ibin] = nominatorHist.GetBinCenter(ibin+1)
        n = int(nominatorHist.GetBinContent(ibin+1))
        d = int(denominatorHist.GetBinContent(ibin+1))
        if d>0:
            valueMean[ibin]=1.*n/d
            valueUp[ibin] = ROOT.TEfficiency.ClopperPearson(d, n, 0.683, True)-valueMean[ibin]
            valueDown[ibin] = valueMean[ibin]-ROOT.TEfficiency.ClopperPearson(d, n, 0.683, False)
            valueErr[ibin]= 0.5*(valueUp[ibin]+valueDown[ibin])
            maxEff=max(maxEff,valueMean[ibin])
            
    graph = ROOT.TGraphAsymmErrors(N, valueX, valueMean, numpy.zeros(N), numpy.zeros(N), valueDown, valueUp)
    
    ibin=0
    '''
    ranges=[]
    while ibin<N:
        for jbin in range(ibin+1,N):
            chi2 = findBestChi2(lambda x,p: p, (0.5), valueX[ibin:jbin],valueMean[ibin:jbin],valueErr[ibin:jbin])
            
            if (chi2.fun>1.0) or (len(ranges)==0 or math.fabs(ranges[-1][2]-chi2.x[0])/chi2.x[0]>0.1):
                #ranges.append([ibin,jbin])
                #ibin=jbin
                #print jbin
                break
                
        ranges.append([valueX[ibin],valueX[jbin],chi2.x[0]])
        ibin=jbin+1
        #print jbin
        #break
        
    for r in ranges:
        print "%+03.2f - %+03.2f: %03.2f" %(r[0],r[1],r[2])
    '''
    rootObj.append(graph)
    return graph, maxEff
    
def getEfficiency2D(nominatorHist, denominatorHist):
    histEff = nominatorHist.Clone(nominatorHist.GetName()+"eff"+str(random.random()))
    rootObj.append(histEff)
    for ibin in range(histEff.GetNbinsX()):
        for jbin in range(histEff.GetNbinsY()):
            n = nominatorHist.GetBinContent(ibin+1,jbin+1)
            d = denominatorHist.GetBinContent(ibin+1,jbin+1)
            if d>40 and n>1:
                histEff.SetBinContent(ibin+1,jbin+1,n/d)
            else:
                for altBin in reversed(range(jbin+1)):
                    n = 0.5*nominatorHist.GetBinContent(ibin+1,altBin+1)+0.25*nominatorHist.GetBinContent(ibin,altBin+1)+0.25*nominatorHist.GetBinContent(ibin+2,altBin+1)
                    d = 0.5*denominatorHist.GetBinContent(ibin+1,altBin+1)+0.25*denominatorHist.GetBinContent(ibin,altBin+1)+0.25*denominatorHist.GetBinContent(ibin+2,altBin+1)
                    if d>20 and n>0:
                        histEff.SetBinContent(ibin+1,jbin+1,n/d)
                        break
                        
    return histEff
    
def drawGraph(graphs,varName,titles,yAxis="",maxEff=1.0):
    cv = ROOT.TCanvas("cv_dist"+str(random.random()),"",800,600)
    cv.SetPad(0.0, 0.0, 1.0, 1.0)
    cv.SetFillStyle(4000)


    cv.SetBorderMode(0)
    cv.SetGridx(False)
    cv.SetGridy(False)


    #For the frame:
    cv.SetFrameBorderMode(0)
    cv.SetFrameBorderSize(1)
    cv.SetFrameFillColor(0)
    cv.SetFrameFillStyle(0)
    cv.SetFrameLineColor(1)
    cv.SetFrameLineStyle(1)
    cv.SetFrameLineWidth(1)

    # Margins:
    cv.SetLeftMargin(0.14)
    cv.SetRightMargin(0.205)
    cv.SetTopMargin(0.08)
    cv.SetBottomMargin(0.135)

    # For the Global title:
    cv.SetTitle("")

    # For the axis:
    cv.SetTickx(1)  # To get tick marks on the opposite side of the frame
    cv.SetTicky(1)
    
    
    axis=ROOT.TH2F("axis"+str(random.random()),";"+varName+";"+yAxis,50,graphs[0].GetXaxis().GetXmin(),graphs[0].GetXaxis().GetXmax(),50,0.0,1.25*maxEff)
    axis.GetYaxis().SetNdivisions(508)
    axis.GetXaxis().SetNdivisions(508)
    axis.GetXaxis().SetTickLength(0.015/(1-cv.GetLeftMargin()-cv.GetRightMargin()))
    axis.GetYaxis().SetTickLength(0.015/(1-cv.GetTopMargin()-cv.GetBottomMargin()))
    axis.GetYaxis().SetNoExponent(True)
    axis.Draw("AXIS")
    
    legend = ROOT.TLegend(0.8,0.9,0.99,0.9-0.075*len(graphs))
    legend.SetFillColor(ROOT.kWhite)
    legend.SetBorderSize(0)
    legend.SetTextFont(43)
    legend.SetTextSize(24)
    
    for i,graph in enumerate(graphs):
        graph.Draw("PE")
        '''
        fit = ROOT.TF1("fit"+str(random.random()),"[0]*ROOT::Math::landau_pdf(x,[1],[2])+gaus(3)+[6]")
        #const
        fit.SetParameter(0,0.5)
        fit.SetParLimits(0, 0, 2)
        #mean
        fit.SetParameter(1,120)
        fit.SetParLimits(1, 0, 300)
        #sigma
        fit.SetParameter(2,10)
        fit.SetParLimits(2, 1, 200)
        #const
        fit.SetParameter(3,0.25)
        fit.SetParLimits(3, 0, 2)
        #mean
        fit.SetParameter(4,140)
        fit.SetParLimits(4, 0, 300)
        #sigma
        fit.SetParameter(5,10)
        fit.SetParLimits(5, 1, 200)
        #const
        fit.SetParameter(6,0.1)
        fit.SetParLimits(6, 0, 1)
         
        graph.Fit(fit,"EM")
        '''
        legend.AddEntry(graph,titles[i],"P")
    
    ROOT.gPad.RedrawAxis()

    

    legend.Draw("Same")
        
    pSample=ROOT.TPaveText(cv.GetLeftMargin()+0.025,0.94,cv.GetLeftMargin()+0.025,0.94,"NDC")
    pSample.SetFillColor(ROOT.kWhite)
    pSample.SetBorderSize(0)
    pSample.SetTextFont(43)
    pSample.SetTextSize(30)
    pSample.SetTextAlign(11)
    pSample.AddText(sampleDict[sample]["title"])
    pSample.Draw("Same")


    pCMS=ROOT.TPaveText(cv.GetLeftMargin()+0.025,0.85,cv.GetLeftMargin()+0.025,0.85,"NDC")
    pCMS.SetFillColor(ROOT.kWhite)
    pCMS.SetBorderSize(0)
    pCMS.SetTextFont(63)
    pCMS.SetTextSize(30)
    pCMS.SetTextAlign(11)
    pCMS.AddText("CMS")
    pCMS.Draw("Same")

    pPreliminary=ROOT.TPaveText(cv.GetLeftMargin()+0.115,0.85,cv.GetLeftMargin()+0.115,0.85,"NDC")
    pPreliminary.SetFillColor(ROOT.kWhite)
    pPreliminary.SetBorderSize(0)
    pPreliminary.SetTextFont(53)
    pPreliminary.SetTextSize(30)
    pPreliminary.SetTextAlign(11)
    pPreliminary.AddText("Simulation")
    pPreliminary.Draw("Same")
    
    
    

    legend.Draw("Same")

    cv.Update()

    cv.WaitPrimitive()

colors=[]
def newColor(red,green,blue):
    newColor.colorindex+=1
    color=ROOT.TColor(newColor.colorindex,red,green,blue)
    colors.append(color)
    return color
    
newColor.colorindex=301

def getDarkerColor(color):
    darkerColor=newColor(color.GetRed()*0.6,color.GetGreen()*0.6,color.GetBlue()*0.6)
    return darkerColor
    
def rebinHist2D(hist,rangeX,rangeY):
    newHist = ROOT.TH2F(hist.GetName()+"clone"+str(random.random()),"",len(rangeX)-1,rangeX,len(rangeY)-1,rangeY)
    newHist.SetDirectory(0)
    rootObj.append(newHist)
    for ibin in range(hist.GetNbinsX()):
        for jbin in range(hist.GetNbinsY()):
            x = math.fabs(hist.GetXaxis().GetBinCenter(ibin+1))
            y = hist.GetYaxis().GetBinCenter(jbin+1)
            c = hist.GetBinContent(ibin+1,jbin+1)
            newHist.Fill(x,y,c)
    return newHist

processNames = [
    "ST_t-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1_ext",
]


inputFiles = ["btaggingEff.root"]
'''
basedir = "/nfs/user/mkomm/SSX13/selection/signalMC"
matching = re.compile("btaggingEff[0-9]+.root")

for f in os.listdir(basedir):
    if matching.match(f):
        inputFiles.append(os.path.join(basedir,f))

print "found ",len(inputFiles),"input files in ",basedir
'''
flavors = [
    "b",
    "c",
    "other"
]

workingpoints = [
    "tight",
    "medium",
    "loose"
]

hists={}

ptbinning = numpy.array([40.0,55.0,110,150,220,320,450,600])
etabinning = numpy.array([0.0,0.2,0.7,1.4,2.0,2.2,2.3,2.5])



for ifile,inputFile in enumerate(inputFiles):
    rootFile = ROOT.TFile(inputFile)
    print "reading file",ifile+1,"/",len(inputFiles)
    for flavor in flavors:
        hists[flavor]={}
        for workingpoint in workingpoints:
            hists[flavor][workingpoint]={}
            for process in processNames:
                print "\t",flavor,workingpoint,process
            
                taggedHistName = "tagged"+"__"+flavor+"__"+workingpoint+"__"+process
                taggedHist = rootFile.Get(taggedHistName)
                taggedHist.SetDirectory(0)
                
                rebinnedTagged = rebinHist2D(taggedHist,
                    etabinning,
                    ptbinning,
                )

                trueHistName = "true"+"__"+flavor+"__"+workingpoint+"__"+process
                trueHist = rootFile.Get(trueHistName)
                trueHist.SetDirectory(0)
                
                rebinnedTrue= rebinHist2D(trueHist,
                    etabinning,
                    ptbinning,
                )
                
                
                if not hists[flavor][workingpoint].has_key("tagged"):
                    hists[flavor][workingpoint]["tagged"]=rebinnedTagged
                    hists[flavor][workingpoint]["true"]=rebinnedTrue
                else:
                    hists[flavor][workingpoint]["tagged"].Add(rebinnedTagged)
                    hists[flavor][workingpoint]["true"].Add(rebinnedTrue)
    rootFile.Close()
                    
outputFile = ROOT.TFile("btagging.root","RECREATE")
for flavor in flavors:
    for workingpoint in workingpoints: 
        eff = getEfficiency2D(hists[flavor][workingpoint]["tagged"],hists[flavor][workingpoint]["true"])
        eff.SetMarkerColor(ROOT.kBlack)
        eff.SetMarkerSize(1.25)
        
        eff.SetDirectory(outputFile)
        eff.SetName(flavor+"__"+workingpoint)
        eff.Write()
        
        cv = ROOT.TCanvas("cv_dist"+str(random.random()),"",800,600)
        cv.SetPad(0.0, 0.0, 1.0, 1.0)
        cv.SetFillStyle(4000)


        cv.SetBorderMode(0)
        cv.SetGridx(False)
        cv.SetGridy(False)


        #For the frame:
        cv.SetFrameBorderMode(0)
        cv.SetFrameBorderSize(1)
        cv.SetFrameFillColor(0)
        cv.SetFrameFillStyle(0)
        cv.SetFrameLineColor(1)
        cv.SetFrameLineStyle(1)
        cv.SetFrameLineWidth(1)

        # Margins:
        cv.SetLeftMargin(0.14)
        cv.SetRightMargin(0.205)
        cv.SetTopMargin(0.08)
        cv.SetBottomMargin(0.135)

        # For the Global title:
        cv.SetTitle("")

        # For the axis:
        cv.SetTickx(1)  # To get tick marks on the opposite side of the frame
        cv.SetTicky(1)
        
        
        axis=ROOT.TH2F("axis"+str(random.random()),";|#eta|;p_{T}",50,etabinning[0],etabinning[-1],50,ptbinning[0],ptbinning[-1])
        axis.GetYaxis().SetNdivisions(508)
        axis.GetXaxis().SetNdivisions(508)
        axis.GetXaxis().SetTickLength(0.015/(1-cv.GetLeftMargin()-cv.GetRightMargin()))
        axis.GetYaxis().SetTickLength(0.015/(1-cv.GetTopMargin()-cv.GetBottomMargin()))
        axis.GetYaxis().SetNoExponent(True)
        
        
        #axis.GetZaxis().SetTitle("efficiency")
        axis.Draw("AXIS")
        
        eff.Scale(100.0)
        
        eff.Draw("Same colztext")
        
        '''
        if flavor=="b":
            eff.GetZaxis().SetRangeUser(0,60)
        if flavor=="c":
            eff.GetZaxis().SetRangeUser(0,6)
        if flavor=="other":
            eff.GetZaxis().SetRangeUser(0,7)
        '''
        ROOT.gPad.RedrawAxis()

        pCMS=ROOT.TPaveText(cv.GetLeftMargin()+0.025,0.94,cv.GetLeftMargin()+0.025,0.94,"NDC")
        pCMS.SetFillColor(ROOT.kWhite)
        pCMS.SetBorderSize(0)
        pCMS.SetTextFont(63)
        pCMS.SetTextSize(30)
        pCMS.SetTextAlign(11)
        pCMS.AddText("CMS")
        pCMS.Draw("Same")

        pPreliminary=ROOT.TPaveText(cv.GetLeftMargin()+0.115,0.94,cv.GetLeftMargin()+0.115,0.94,"NDC")
        pPreliminary.SetFillColor(ROOT.kWhite)
        pPreliminary.SetBorderSize(0)
        pPreliminary.SetTextFont(53)
        pPreliminary.SetTextSize(30)
        pPreliminary.SetTextAlign(11)
        pPreliminary.AddText("Simulation")
        pPreliminary.Draw("Same")
        

        cv.Update()

        cv.WaitPrimitive()
        
        
        cv.Print("btagging_"+flavor+"__"+workingpoint+".pdf")
        cv.Print("btagging_"+flavor+"__"+workingpoint+".png")
        
outputFile.Close()      
                

    


