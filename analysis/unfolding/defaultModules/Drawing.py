import logging
import ROOT
import os
import random
import math
import re
import numpy
from Module import Module

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

class Drawing(Module):
    def __init__(self,options=[]):
        Module.__init__(self,options)
        self._logger = logging.getLogger(__file__)
        self._logger.setLevel(logging.DEBUG)
        
    def drawPosterior(self,fitResultDict,outputFile,selection=[],nameDict={},ranges=[-2,2],default=None):
        colors = {"comb":ROOT.kTeal+4,"mu":ROOT.kAzure+2,"ele":ROOT.kOrange+7}
        fitResultSelectedDict = {}
        Nfits = len(fitResultDict.keys())
        parameters = []
        for fitName in fitResultDict.keys():
            fitResultSelectedDict[fitName] = {"parameters": {}}
            if len(selection)==0:
                fitResultSelectedDict[fitName] = fitResultDict[fitName]
                parameters+=fitResultDict[fitName]["parameters"].keys()
            else:
                for ipar,parameterName in enumerate(sorted(fitResultDict[fitName]["parameters"].keys())):
                    for select in selection:
                        regex = re.compile(select.replace("*","[A-Za-z0-9]*"))
                        if regex.match(parameterName):
                            parameters+=[parameterName]
                            fitResultSelectedDict[fitName]["parameters"][parameterName]=fitResultDict[fitName]["parameters"][parameterName]
                            break
        parameters = sorted(list(set(parameters)))
        Npar = len(parameters)
        if Npar==0:
            return
       
        ROOT.gStyle.SetPaintTextFormat("4.0f")
        cv = ROOT.TCanvas("corr","",800,150+Npar*50)
        cv.SetTopMargin(50./(150+Npar*50))
        cv.SetLeftMargin(0.35)
        cv.SetRightMargin(0.04)
        cv.SetBottomMargin(100./(150+Npar*50))
        axis = ROOT.TH2F("axis",";Fit parameter;",50,ranges[0],ranges[1],Npar,0,Npar)
        axis.GetXaxis().SetTickLength(30./(150+Npar*50))
        axis.GetYaxis().SetTickLength(0.02)
        for ipar,parameterName in enumerate(sorted(parameters)):
            pName = parameterName.replace("_"," ")
            if nameDict.has_key(pName):
               pName = nameDict[pName]
            axis.GetYaxis().SetBinLabel(ipar+1,pName)
            
        axis.Draw("AXIS")
        rootObj = []
        for ifit, fitName in enumerate(sorted(fitResultSelectedDict.keys())):
            for ipar,parameterName in enumerate(parameters):
                if not fitResultSelectedDict[fitName]["parameters"].has_key(parameterName):
                    continue
                priorMean = fitResultSelectedDict[fitName]["parameters"][parameterName]["mean_prior"]
                priorUnc = fitResultSelectedDict[fitName]["parameters"][parameterName]["unc_prior"]
                priorBox = ROOT.TBox(
                    max(ranges[0],priorMean-priorUnc),
                    ipar+0.15,
                    min(ranges[1],priorMean+priorUnc),
                    ipar+0.85
                )
                priorBox.SetFillColor(ROOT.kGray)
                rootObj.append(priorBox)
                priorBox.Draw("FSame")
                
        if default!=None:
            defaultLine = ROOT.TLine(default,0,default,Npar)
            defaultLine.SetLineColor(ROOT.kBlack)
            defaultLine.SetLineWidth(2)
            defaultLine.SetLineStyle(2)
            defaultLine.Draw("LSame")
            rootObj.append(defaultLine)
        ROOT.gPad.RedrawAxis()

        for ifit, fitName in enumerate(sorted(fitResultSelectedDict.keys())):
            for ipar,parameterName in enumerate(parameters):
                if not fitResultSelectedDict[fitName]["parameters"].has_key(parameterName):
                    continue
                fitMean = fitResultSelectedDict[fitName]["parameters"][parameterName]["mean_fit"]
                fitUnc = fitResultSelectedDict[fitName]["parameters"][parameterName]["unc_fit"]
                fitLine = ROOT.TLine(
                    max(ranges[0],fitMean-fitUnc),
                    ipar+0.5+0.7*(ifit-(Nfits-1)/2.)/Nfits,
                    min(ranges[1],fitMean+fitUnc),
                    ipar+0.5+0.7*(ifit-(Nfits-1)/2.)/Nfits
                )
                fitLine.SetLineWidth(2)
                fitLine.SetLineColor(colors[fitName])
                rootObj.append(fitLine)
                fitLine.Draw("LSame")
                fitMarker = ROOT.TMarker(
                    fitMean,
                    ipar+0.5+0.7*(ifit-(Nfits-1)/2.)/Nfits,
                    20
                )
                fitMarker.SetMarkerSize(1.3)
                fitMarker.SetMarkerColor(colors[fitName])
                rootObj.append(fitMarker)
                fitMarker.Draw("PSame")
       
        
        
        for ifit, fitName in enumerate(sorted(fitResultSelectedDict.keys())): 
            fitLine = ROOT.TLine(
                ranges[0]+(ifit+0.15)*(ranges[1]-ranges[0])/3.-0.1*(ranges[1]-ranges[0])/3.,
                len(parameters)+0.5,
                ranges[0]+(ifit+0.15)*(ranges[1]-ranges[0])/3.+0.1*(ranges[1]-ranges[0])/3.,
                len(parameters)+0.5,
            )
            fitLine.SetLineWidth(2)
            fitLine.SetLineColor(colors[fitName])
            rootObj.append(fitLine)
            fitLine.Draw("LSame")
            fitMarker = ROOT.TMarker(
                ranges[0]+(ifit+0.15)*(ranges[1]-ranges[0])/3.,
                len(parameters)+0.5,
                20
            )
            fitMarker.SetMarkerSize(1.3)
            fitMarker.SetMarkerColor(colors[fitName])
            rootObj.append(fitMarker)
            fitMarker.Draw("PSame")
            
            pText = ROOT.TPaveText(
                ranges[0]+(ifit+0.15)*(ranges[1]-ranges[0])/3.+0.15*(ranges[1]-ranges[0])/3.,
                len(parameters)+0.5,
                ranges[0]+(ifit+0.15)*(ranges[1]-ranges[0])/3.+0.15*(ranges[1]-ranges[0])/3.,
                len(parameters)+0.5,
            )
            rootObj.append(pText)
            pText.SetFillStyle(0)
            pText.SetTextFont(43)
            pText.SetTextSize(30)
            pText.SetTextAlign(12)
            
            pText.AddText(fitName)
            pText.Draw("Same")
            
        cv.Print(outputFile)
        
    def plotDataHistogram(self,nominalHistA,measuredHistA,output,title="",xaxis="",yaxis="Events",yrange=None,normalizeByBinWidth=False,normalizeByCrossSection=False,logy=False,uncBand=None):
        nominalHists = []
        for h in nominalHistA:
            nominalHists.append(h.Clone())
        measuredHist = measuredHistA.Clone()
        
        if normalizeByBinWidth:
            for i in range(len(nominalHists)):
                self.module("Utils").normalizeByBinWidth(nominalHists[i])
            self.module("Utils").normalizeByBinWidth(measuredHist)
        elif normalizeByCrossSection:
            for i in range(len(nominalHists)):
                xsec = self.module("Utils").normalizeByCrossSection(nominalHists[i])
                self._logger.info("Calculated theo. xsec: "+str(xsec)+" pb")
            self.module("Utils").normalizeByCrossSection(measuredHist)
            
        cvxmin=0.165
        cvxmax=0.96
        cvymin=0.14
        cvymax=0.92
        
        cvHist = ROOT.TCanvas("cvHist","",750,700)
        cvHist.SetLogy(logy)
        cvHist.SetLeftMargin(cvxmin)
        cvHist.SetBottomMargin(cvymin)
        cvHist.SetTopMargin(1-cvymax)
        cvHist.SetRightMargin(1-cvxmax)

        ymin = 0
        ymax = 1.3*max(map(lambda x: x.GetMaximum(),nominalHists+[measuredHist]))
        if logy:
            ymin = 0.4*min(map(lambda x: x.GetMinimum(),nominalHists+[measuredHist]))
            ymax = math.log(1.3*math.exp(ymax+1))-1.
        if yrange:
            ymin = yrange[0]
            ymax = yrange[1]
        
        axis = ROOT.TH2F("axis"+str(random.random()),";"+xaxis+";"+yaxis,
            50,measuredHist.GetXaxis().GetXmin(),measuredHist.GetXaxis().GetXmax(),
            50,ymin,ymax
        )
        axis.GetXaxis().SetTickLength(0.015/(1-cvHist.GetLeftMargin()-cvHist.GetRightMargin()))
        axis.GetYaxis().SetTickLength(0.015/(1-cvHist.GetTopMargin()-cvHist.GetBottomMargin()))
        axis.GetXaxis().SetLabelFont(43)
        axis.GetXaxis().SetLabelSize(32)
        axis.GetYaxis().SetLabelFont(43)
        axis.GetYaxis().SetLabelSize(32)
        axis.GetXaxis().SetTitleFont(43)
        axis.GetXaxis().SetTitleSize(36)
        axis.GetYaxis().SetTitleFont(43)
        axis.GetYaxis().SetTitleSize(36)
        
        axis.GetYaxis().SetTitleOffset(1.6)
        axis.Draw("AXIS")
        
        
        rootObj = []
        
        if uncBand!=None:
            for ibin in range(nominalHist.GetNbinsX()):
                c = nominalHist.GetBinCenter(ibin+1)
                w = nominalHist.GetBinWidth(ibin+1)
                box = ROOT.TBox(c-0.5*w,uncBand[ibin][0],c+0.5*w,uncBand[ibin][2])
                rootObj.append(box)
                box.SetFillStyle(1001)
                box.SetLineColor(ROOT.kOrange+1)
                box.SetFillColor(ROOT.kOrange+1)
                box.Draw("SameF")
        for i in range(len(nominalHists)):
            nominalHists[i].SetLineColor(ROOT.kRed+1)
            nominalHists[i].SetLineWidth(3)
            nominalHists[i].SetLineStyle(i+1)
            nominalHists[i].Draw("HISTSame")
        
        measuredHist.SetLineColor(ROOT.kBlack)
        measuredHist.SetMarkerColor(ROOT.kBlack)
        measuredHist.SetMarkerStyle(20)
        measuredHist.SetLineWidth(2)
        measuredHist.SetMarkerSize(1.5)
        measuredHist.Draw("PESame")
        
        pCMS=ROOT.TPaveText(cvxmin+0.025,cvymax-0.065,cvxmin+0.025,cvymax-0.065,"NDC")
        pCMS.SetFillColor(ROOT.kWhite)
        pCMS.SetBorderSize(0)
        pCMS.SetTextFont(63)
        pCMS.SetTextSize(34)
        pCMS.SetTextAlign(11)
        pCMS.AddText("CMS")
        pCMS.Draw("Same")
        
        pPreliminary=ROOT.TPaveText(cvxmin+0.025+0.1,cvymax-0.065,cvxmin+0.025+0.1,cvymax-0.065,"NDC")
        pPreliminary.SetFillColor(ROOT.kWhite)
        pPreliminary.SetBorderSize(0)
        pPreliminary.SetTextFont(53)
        pPreliminary.SetTextSize(34)
        pPreliminary.SetTextAlign(11)
        pPreliminary.AddText("Preliminary")
        pPreliminary.Draw("Same")
    
        
        pLumi=ROOT.TPaveText(cvxmax,0.94,cvxmax,0.94,"NDC")
        pLumi.SetFillColor(ROOT.kWhite)
        pLumi.SetBorderSize(0)
        pLumi.SetTextFont(43)
        pLumi.SetTextSize(36)
        pLumi.SetTextAlign(31)
        if title!="":
            pLumi.AddText(title+", 36#kern[-0.5]{ }fb#lower[-0.7]{#scale[0.7]{-1}} (13TeV)")
        else:
            pLumi.AddText("36#kern[-0.5]{ }fb#lower[-0.7]{#scale[0.7]{-1}} (13TeV)")
        pLumi.Draw("Same")
        
        cvHist.Print(output+".pdf")
        cvHist.Print(output+".png")
        
    def plotCrossSection(self,genHistSum,histSumProfiled,histSumTotal,ymin,ymax,logy,ytitle,xtitle,lumi,legendPos,resRange,output):
        ROOT.gStyle.SetPaperSize(8.0*1.35,7.0*1.35)
        ROOT.TGaxis.SetMaxDigits(3)
        ROOT.gStyle.SetLineScalePS(2)
        
        cv = ROOT.TCanvas("cvSum"+str(random.random()),"",800,700)
        cv.Divide(1,2,0,0)
        cv.GetPad(1).SetPad(0.0, 0.0, 1.0, 1.0)
        cv.GetPad(1).SetFillStyle(4000)
        cv.GetPad(2).SetPad(0.0, 0.00, 1.0,1.0)
        cv.GetPad(2).SetFillStyle(4000)
        
        cvxmin=0.145
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
            cv.GetPad(i).SetFrameLineWidth(1)

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
        
        
        xmin = genHistSum.GetXaxis().GetBinLowEdge(1)
        xmax = genHistSum.GetXaxis().GetBinUpEdge(genHistSum.GetNbinsX())
        axis = ROOT.TH2F("axis"+str(random.random()),";;",
            50,xmin,xmax,
            50,ymin,ymax
        )
        axis.GetXaxis().SetTitle("")
        axis.GetYaxis().SetTitle(ytitle)
        axis.GetXaxis().SetTickLength(0.015/(1-cv.GetPad(2).GetLeftMargin()-cv.GetPad(2).GetRightMargin()))
        axis.GetYaxis().SetTickLength(0.015/(1-cv.GetPad(2).GetTopMargin()-cv.GetPad(2).GetBottomMargin()))
        axis.GetXaxis().SetLabelFont(43)
        axis.GetXaxis().SetLabelSize(0)
        axis.GetYaxis().SetLabelFont(43)
        axis.GetYaxis().SetLabelSize(33)
        axis.GetXaxis().SetTitleFont(43)
        axis.GetXaxis().SetTitleSize(36)
        axis.GetYaxis().SetTitleFont(43)
        axis.GetYaxis().SetTitleSize(36)
        axis.GetYaxis().SetNoExponent(not logy)
        axis.GetYaxis().SetTitleOffset(1.45)
        axis.Draw("AXIS")
        
        genHistSum.Draw("HISTSAME")
        histSumTotal.Draw("PESAME")
        for ibin in range(histSumTotal.GetNbinsX()):
            c = histSumTotal.GetBinCenter(ibin+1)
            w = (xmax-xmin)*0.008
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
        pCMS.SetTextSize(37)
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
        pLumi.SetTextSize(37)
        pLumi.SetTextAlign(31)
        pLumi.AddText(lumi)
        pLumi.Draw("Same")
        
        
        legendXL = [cvxmin+0.02,cvxmin+0.35]
        legendXR = [0.53,cvxmax-0.12]
        legendYD = [resHeight+0.03,resHeight+0.03+0.058*2]
        legendYU = [cvymax-0.025,cvymax-0.025-0.058*2]
        
        if legendPos[0]=="L":
            legendX = legendXL
        else:
            legendX = legendXR
            
        if legendPos[1]=="D":
            legendY = legendYD
        else:
            legendY = legendYU
            
        legend = ROOT.TLegend(legendX[0],legendY[0],legendX[1],legendY[1])    
        
        #legend = ROOT.TLegend(0.54,resHeight+0.03,cvxmax-0.13,resHeight+0.03+0.067*2)
        legend.SetFillColor(0)
        legend.SetFillStyle(0)
        legend.SetBorderSize(0)
        legend.SetTextFont(43)
        legend.SetTextSize(30)
        legend.AddEntry(histSumTotal,"Data","PE")
        legend.AddEntry(genHistSum,"POWHEG#kern[-0.5]{ }+#kern[-0.5]{ }Pythia#kern[-0.6]{ }8","L")
        legend.Draw("Same")
        
        cv.cd(1)
       
        axisRes=ROOT.TH2F("axisRes"+str(random.random()),";;Pred./Data",50,xmin,xmax,50,1-resRange,1+resRange)
        axisRes.GetYaxis().SetNdivisions(406)
        axisRes.GetXaxis().SetTitle(xtitle)
        axisRes.GetXaxis().SetTickLength(0.017/(1-cv.GetPad(1).GetLeftMargin()-cv.GetPad(1).GetRightMargin()))
        axisRes.GetYaxis().SetTickLength(0.015/(1-cv.GetPad(1).GetTopMargin()-cv.GetPad(1).GetBottomMargin()))
        axisRes.GetXaxis().SetLabelFont(43)
        axisRes.GetXaxis().SetLabelSize(33)
        axisRes.GetYaxis().SetLabelFont(43)
        axisRes.GetYaxis().SetLabelSize(33)
        axisRes.GetXaxis().SetTitleFont(43)
        axisRes.GetXaxis().SetTitleSize(36)
        axisRes.GetYaxis().SetTitleFont(43)
        axisRes.GetYaxis().SetTitleSize(36)
        axisRes.GetYaxis().SetNoExponent(True)
        axisRes.GetYaxis().SetTitleOffset(1.45)
        axisRes.Draw("AXIS")
        
        
        axisLine = ROOT.TF1("axisLine"+str(random.random()),"1",xmin,xmax)
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
            w = (xmax-xmin)*0.008
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
        

        hidePave=ROOT.TPaveText(cvxmin-0.065,resHeight-0.04,cvxmin-0.005,resHeight+0.028,"NDC")
        hidePave.SetFillColor(ROOT.kWhite)
        hidePave.SetFillStyle(1001)
        hidePave.Draw("Same")
        
        
        cv.Print(output+".pdf")
        cv.Print(output+".png")
        
        
    def plotDistribution(self,stack,data,ymin,ymax,logy,ytitle,xtitle,cut,legendPos,resRange,cvxmin,lumi,output):
        ROOT.gStyle.SetPaperSize(8.0*1.35,7.0*1.35)
        ROOT.TGaxis.SetMaxDigits(3)
        ROOT.gStyle.SetLineScalePS(2)
        ROOT.gStyle.SetHatchesSpacing(1.)
        ROOT.gStyle.SetHatchesLineWidth(2)
        
        cv = ROOT.TCanvas("cvSum"+str(random.random()),"",800,700)
        cv.Divide(1,2,0,0)
        cv.GetPad(1).SetPad(0.0, 0.0, 1.0, 1.0)
        cv.GetPad(1).SetFillStyle(4000)
        cv.GetPad(2).SetPad(0.0, 0.00, 1.0,1.0)
        cv.GetPad(2).SetFillStyle(4000)
        
        
        cvxmax=0.96
        cvymin=0.13
        cvymax=0.93
        resHeight=0.32
        
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
            cv.GetPad(i).SetFrameLineWidth(1)

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
        
        
        xmin = data.GetXaxis().GetBinLowEdge(1)
        xmax = data.GetXaxis().GetBinUpEdge(data.GetNbinsX())
        axis = ROOT.TH2F("axis"+str(random.random()),";;",
            50,xmin,xmax,
            50,ymin,ymax
        )
        axis.GetXaxis().SetTitle("")
        axis.GetYaxis().SetTitle(ytitle)
        axis.GetXaxis().SetTickLength(0.015/(1-cv.GetPad(2).GetLeftMargin()-cv.GetPad(2).GetRightMargin()))
        axis.GetYaxis().SetTickLength(0.015/(1-cv.GetPad(2).GetTopMargin()-cv.GetPad(2).GetBottomMargin()))
        axis.GetXaxis().SetLabelFont(43)
        axis.GetXaxis().SetLabelSize(0)
        axis.GetYaxis().SetLabelFont(43)
        axis.GetYaxis().SetLabelSize(33)
        axis.GetXaxis().SetTitleFont(43)
        axis.GetXaxis().SetTitleSize(36)
        axis.GetYaxis().SetTitleFont(43)
        axis.GetYaxis().SetTitleSize(36)
        axis.GetYaxis().SetNoExponent(not logy)
        axis.GetYaxis().SetTitleOffset(1.88*(cvxmin-(1-cvxmax))/(0.185-(1-cvxmax)))
        axis.Draw("AXIS")
        
        
        mcStack = ROOT.THStack()
        for s in stack:
            mcStack.Add(s["hist"],"HIST")
        mcStack.Draw("HISTSame")
        
        mcSum = stack[0]["hist"].Clone(stack[0]["hist"].GetName()+"mcSum")
        for i in range(1,len(stack)):
            #print stack[i]["hist"].GetBinError(1)/stack[i]["hist"].GetBinContent(1)
            mcSum.Add(stack[i]["hist"])

        data.Draw("PESame")
        data.SetMarkerStyle(20)
        data.SetMarkerSize(1.4)
        
        ROOT.gPad.RedrawAxis()
            
        #histSumProfiled.Draw("PESAME")
        
        pCMS=ROOT.TPaveText(cvxmin,0.95,cvxmin,0.95,"NDC")
        pCMS.SetFillColor(ROOT.kWhite)
        pCMS.SetBorderSize(0)
        pCMS.SetTextFont(63)
        pCMS.SetTextSize(37)
        pCMS.SetTextAlign(11)
        pCMS.AddText("CMS")
        pCMS.Draw("Same")
        
        if legendPos=="R":
            pCut=ROOT.TPaveText(cvxmin+0.025,cvymax-0.07,cvxmin+0.025,cvymax-0.07,"NDC")
            pCut.SetTextAlign(11)
        else:
            pCut=ROOT.TPaveText(cvxmax-0.025,cvymax-0.07,cvxmax-0.025,cvymax-0.07,"NDC")
            pCut.SetTextAlign(31)
        pCut.SetFillColor(ROOT.kWhite)
        pCut.SetBorderSize(0)
        pCut.SetTextFont(43)
        pCut.SetTextSize(30)
        pCut.AddText(cut)
        pCut.Draw("Same")
        
        pLumi=ROOT.TPaveText(cvxmax,0.95,cvxmax,0.95,"NDC")
        pLumi.SetFillColor(ROOT.kWhite)
        pLumi.SetBorderSize(0)
        pLumi.SetTextFont(43)
        pLumi.SetTextSize(37)
        pLumi.SetTextAlign(31)
        pLumi.AddText(lumi)
        pLumi.Draw("Same")
        
       
        if legendPos=="R":
            legend = ROOT.TLegend(cvxmax-0.27,cvymax-0.02,cvxmax-0.01,cvymax-0.01-0.058*(len(stack)+2))    
        else:
            legend = ROOT.TLegend(cvxmin+0.03,cvymax-0.02,cvxmin+0.26,cvymax-0.01-0.058*(len(stack)+2))    
        legend.SetFillColor(0)
        legend.SetFillStyle(0)
        legend.SetBorderSize(0)
        legend.SetTextFont(43)
        legend.SetTextSize(30)
        legend.AddEntry(data,"Data","PE")
        for s in reversed(stack):
            legend.AddEntry(s["hist"],s["title"],"F")
        
        
        
        cv.cd(1)
        
        axisRes=ROOT.TH2F("axisRes"+str(random.random()),";;Data/Pred.",50,xmin,xmax,50,1-resRange,1+resRange)
        axisRes.GetYaxis().SetNdivisions(406)
        axisRes.GetXaxis().SetTitle(xtitle)
        axisRes.GetXaxis().SetTickLength(0.017/(1-cv.GetPad(1).GetLeftMargin()-cv.GetPad(1).GetRightMargin()))
        axisRes.GetYaxis().SetTickLength(0.015/(1-cv.GetPad(1).GetTopMargin()-cv.GetPad(1).GetBottomMargin()))
        axisRes.GetXaxis().SetLabelFont(43)
        axisRes.GetXaxis().SetLabelSize(33)
        axisRes.GetYaxis().SetLabelFont(43)
        axisRes.GetYaxis().SetLabelSize(33)
        axisRes.GetXaxis().SetTitleFont(43)
        axisRes.GetXaxis().SetTitleSize(36)
        axisRes.GetYaxis().SetTitleFont(43)
        axisRes.GetYaxis().SetTitleSize(36)
        axisRes.GetYaxis().SetNoExponent(True)
        axisRes.GetYaxis().SetTitleOffset(1.88*(cvxmin-(1-cvxmax))/(0.185-(1-cvxmax)))
        axisRes.Draw("AXIS")
        
        rootObj = []
        dataRes = data.Clone(data.GetName()+"res")
        for ibin in range(data.GetNbinsX()):
            d = data.GetBinContent(ibin+1)
            m = mcSum.GetBinContent(ibin+1)
            e = data.GetBinError(ibin+1)
            c = mcSum.GetBinCenter(ibin+1)
            w = mcSum.GetBinWidth(ibin+1)
            if m>0:
                dataRes.SetBinContent(ibin+1,d/m)
                dataRes.SetBinError(ibin+1,e/m)
                h = min(mcSum.GetBinError(ibin+1)/m,resRange-0.001)
                box = ROOT.TBox(c-0.5*w,1-h,c+0.5*w,1+h)
                box.SetFillStyle(3345)
                box.SetLineColor(ROOT.kGray+1)
                box.SetFillColor(ROOT.kGray)
                box.SetLineWidth(int(2))
                rootObj.append(box)
                box.Draw("SameF")
                box2 = ROOT.TBox(c-0.5*w,1-h,c+0.5*w,1+h)
                box2.SetFillStyle(0)
                box2.SetLineColor(ROOT.kGray+1)
                box2.SetFillColor(ROOT.kGray)
                box2.SetLineWidth(int(2))
                rootObj.append(box2)
                box2.Draw("SameL")
                
            else:
                dataRes.SetBinContent(ibin+1,0)
            
        cv.cd(2)
        legend.AddEntry(box,"Fit unc.","F")
        legend.Draw("Same")
        cv.cd(1)
            
                
        dataRes.Draw("PESame")
        
        axisLine = ROOT.TF1("axisLine"+str(random.random()),"1",xmin,xmax)
        axisLine.SetLineColor(ROOT.kBlack)
        axisLine.SetLineWidth(1)
        axisLine.Draw("SameL")
        
        
        
        
        
        ROOT.gPad.RedrawAxis()
        

        hidePave=ROOT.TPaveText(cvxmin-0.065,resHeight-0.028,cvxmin-0.005,resHeight+0.028,"NDC")
        hidePave.SetFillColor(ROOT.kWhite)
        hidePave.SetFillStyle(1001)
        hidePave.Draw("Same")
        
        
        cv.Print(output+".pdf")
        cv.Print(output+".png")
        
        
    def plotCompareHistogram(self,genHistA,measuredHistsA,output,title="",xaxis="",yaxis="Events",yrange=None,normalizeByBinWidth=False,normalizeByCrossSection=False,logy=False,uncBand=None):
        genHist = genHistA.Clone()
        measuredHists = []
        
        genHist = genHistA.Clone()
        for hist in measuredHistsA:
            measuredHists.append(hist.Clone())

        if normalizeByBinWidth:
            self.module("Utils").normalizeByBinWidth(genHist)
            for hist in measuredHists:
                self.module("Utils").normalizeByBinWidth(hist)
        elif normalizeByCrossSection:
            xsec = self.module("Utils").normalizeByCrossSection(genHist)
            for hist in measuredHists:
                self.module("Utils").normalizeByCrossSection(hist)
            
            self._logger.info("Calculated theo. xsec: "+str(xsec)+" pb")
        
        cvxmin=0.165
        cvxmax=0.96
        cvymin=0.14
        cvymax=0.92
        
        cvHist = ROOT.TCanvas("cvHist","",750,700)
        cvHist.SetLogy(logy)
        cvHist.SetLeftMargin(cvxmin)
        cvHist.SetBottomMargin(cvymin)
        cvHist.SetTopMargin(1-cvymax)
        cvHist.SetRightMargin(1-cvxmax)

        ymin = 0
        ymax = 1.3*max(map(lambda x: x.GetMaximum(),[genHist]+measuredHists))
        if logy:
            ymin = 0.4*min(map(lambda x: x.GetMinimum(),[genHist]+measuredHists))
            ymax = math.log(1.3*math.exp(ymax+1))-1.
        if yrange:
            ymin = yrange[0]
            ymax = yrange[1]
        
        axis = ROOT.TH2F("axis"+str(random.random()),";"+xaxis+";"+yaxis,
            50,genHist.GetXaxis().GetXmin(),genHist.GetXaxis().GetXmax(),
            50,ymin,ymax
        )
        axis.GetXaxis().SetTickLength(0.015/(1-cvHist.GetLeftMargin()-cvHist.GetRightMargin()))
        axis.GetYaxis().SetTickLength(0.015/(1-cvHist.GetTopMargin()-cvHist.GetBottomMargin()))
        axis.GetXaxis().SetLabelFont(43)
        axis.GetXaxis().SetLabelSize(32)
        axis.GetYaxis().SetLabelFont(43)
        axis.GetYaxis().SetLabelSize(32)
        axis.GetXaxis().SetTitleFont(43)
        axis.GetXaxis().SetTitleSize(36)
        axis.GetYaxis().SetTitleFont(43)
        axis.GetYaxis().SetTitleSize(36)
        
        axis.GetYaxis().SetTitleOffset(1.6)
        axis.Draw("AXIS")
        
        
        genHist.SetLineColor(ROOT.kRed+1)
        genHist.SetLineWidth(3)
        genHist.SetLineStyle(1)
        genHist.Draw("HISTSame")
        
        rootObj = []
        
        colors = [ROOT.kViolet,ROOT.kAzure-4,ROOT.kYellow+1]
        for ihist, hist in enumerate(measuredHists):
            for ibin in range(genHist.GetNbinsX()):
                n = hist.GetBinContent(ibin+1)
                w = hist.GetXaxis().GetBinWidth(ibin+1)
                e = hist.GetBinError(ibin+1)
                c = hist.GetBinCenter(ibin+1)
                
                pos = c-0.2*w+(ihist*w*0.4)/(len(measuredHists)-1)
                line = ROOT.TLine(pos,n+e,pos,n-e)
                rootObj.append(line)
                line.SetLineColor(colors[ihist%len(colors)])
                line.Draw("SameL")
                
                marker = ROOT.TMarker(pos,n,20)
                marker.SetMarkerSize(1.3)
                rootObj.append(marker)
                marker.SetMarkerColor(colors[ihist%len(colors)])
                marker.Draw("SameL")
                

        
        
        
        
        pCMS=ROOT.TPaveText(cvxmin+0.025,cvymax-0.065,cvxmin+0.025,cvymax-0.065,"NDC")
        pCMS.SetFillColor(ROOT.kWhite)
        pCMS.SetBorderSize(0)
        pCMS.SetTextFont(63)
        pCMS.SetTextSize(34)
        pCMS.SetTextAlign(11)
        pCMS.AddText("CMS")
        pCMS.Draw("Same")
        
        pPreliminary=ROOT.TPaveText(cvxmin+0.025+0.1,cvymax-0.065,cvxmin+0.025+0.1,cvymax-0.065,"NDC")
        pPreliminary.SetFillColor(ROOT.kWhite)
        pPreliminary.SetBorderSize(0)
        pPreliminary.SetTextFont(53)
        pPreliminary.SetTextSize(34)
        pPreliminary.SetTextAlign(11)
        pPreliminary.AddText("Preliminary")
        pPreliminary.Draw("Same")
    
        
        pLumi=ROOT.TPaveText(cvxmax,0.94,cvxmax,0.94,"NDC")
        pLumi.SetFillColor(ROOT.kWhite)
        pLumi.SetBorderSize(0)
        pLumi.SetTextFont(43)
        pLumi.SetTextSize(36)
        pLumi.SetTextAlign(31)
        if title!="":
            pLumi.AddText(title+", 36#kern[-0.5]{ }fb#lower[-0.7]{#scale[0.7]{-1}} (13TeV)")
        else:
            pLumi.AddText("36#kern[-0.5]{ }fb#lower[-0.7]{#scale[0.7]{-1}} (13TeV)")
        pLumi.Draw("Same")
        
        cvHist.Print(output+".pdf")
        cvHist.Print(output+".png")
        
        
    def plotEnvelopeHistogram(self,genHistA,nominalHistA,upHistA,downHistA,output,title="",xaxis="",yaxis="Events",yrange=None,normalizeByBinWidth=False,normalizeByCrossSection=False,logy=False,uncBand=None):
        genHist = genHistA.Clone()
        nominalHist = nominalHistA.Clone()
        upHist = upHistA.Clone()
        downHist = downHistA.Clone()
        
        if normalizeByBinWidth:
            self.module("Utils").normalizeByBinWidth(genHist)
            self.module("Utils").normalizeByBinWidth(nominalHist)
            self.module("Utils").normalizeByBinWidth(upHist)
            self.module("Utils").normalizeByBinWidth(downHist)
        elif normalizeByCrossSection:
            xsec = self.module("Utils").normalizeByCrossSection(genHist)
            self.module("Utils").normalizeByCrossSection(nominalHist)
            self.module("Utils").normalizeByCrossSection(upHist)
            self.module("Utils").normalizeByCrossSection(downHist)
            
            self._logger.info("Calculated theo. xsec: "+str(xsec)+" pb")
        
        cvxmin=0.165
        cvxmax=0.96
        cvymin=0.14
        cvymax=0.92
        
        cvHist = ROOT.TCanvas("cvHist","",750,700)
        cvHist.SetLogy(logy)
        cvHist.SetLeftMargin(cvxmin)
        cvHist.SetBottomMargin(cvymin)
        cvHist.SetTopMargin(1-cvymax)
        cvHist.SetRightMargin(1-cvxmax)

        ymin = 0
        ymax = 1.3*max(map(lambda x: x.GetMaximum(),[genHist,nominalHist,upHist,downHist]))
        if logy:
            ymin = 0.4*min(map(lambda x: x.GetMinimum(),[genHist,nominalHist,upHist,downHist]))
            ymax = math.log(1.3*math.exp(ymax+1))-1.
        if yrange:
            ymin = yrange[0]
            ymax = yrange[1]
        
        axis = ROOT.TH2F("axis"+str(random.random()),";"+xaxis+";"+yaxis,
            50,nominalHist.GetXaxis().GetXmin(),nominalHist.GetXaxis().GetXmax(),
            50,ymin,ymax
        )
        axis.GetXaxis().SetTickLength(0.015/(1-cvHist.GetLeftMargin()-cvHist.GetRightMargin()))
        axis.GetYaxis().SetTickLength(0.015/(1-cvHist.GetTopMargin()-cvHist.GetBottomMargin()))
        axis.GetXaxis().SetLabelFont(43)
        axis.GetXaxis().SetLabelSize(32)
        axis.GetYaxis().SetLabelFont(43)
        axis.GetYaxis().SetLabelSize(32)
        axis.GetXaxis().SetTitleFont(43)
        axis.GetXaxis().SetTitleSize(36)
        axis.GetYaxis().SetTitleFont(43)
        axis.GetYaxis().SetTitleSize(36)
        
        axis.GetYaxis().SetTitleOffset(1.6)
        axis.Draw("AXIS")
        
        
        rootObj = []
        
        for ibin in range(nominalHist.GetNbinsX()):
            c = nominalHist.GetBinContent(ibin+1)
            s = nominalHist.GetXaxis().GetBinLowEdge(ibin+1)
            u = nominalHist.GetXaxis().GetBinUpEdge(ibin+1)
            e = nominalHist.GetBinError(ibin+1)
            
            box = ROOT.TBox(s,c-e,u,c+e)
            rootObj.append(box)
            box.SetFillStyle(3343)
            box.SetFillColor(ROOT.kGray)
            box.SetLineWidth(2)
            box.Draw("SameF")
            
            line = ROOT.TLine(s,c,u,c)
            rootObj.append(line)
            line.SetLineColor(ROOT.kBlack)
            line.Draw("SameL")

        genHist.SetLineColor(ROOT.kRed+1)
        genHist.SetLineWidth(3)
        genHist.SetLineStyle(1)
        genHist.Draw("HISTSame")
        
        upHist.SetLineColor(ROOT.kViolet)
        upHist.SetMarkerColor(ROOT.kViolet)
        upHist.SetMarkerStyle(22)
        upHist.SetLineWidth(2)
        upHist.SetLineStyle(2)
        upHist.SetMarkerSize(2)
        upHist.Draw("HISTPSame")
        
        downHist.SetLineColor(ROOT.kAzure-4)
        downHist.SetMarkerColor(ROOT.kAzure-4)
        downHist.SetMarkerStyle(23)
        downHist.SetLineWidth(2)
        downHist.SetLineStyle(2)
        downHist.SetMarkerSize(2)
        downHist.Draw("HISTPSame")
        
        
        pCMS=ROOT.TPaveText(cvxmin+0.025,cvymax-0.065,cvxmin+0.025,cvymax-0.065,"NDC")
        pCMS.SetFillColor(ROOT.kWhite)
        pCMS.SetBorderSize(0)
        pCMS.SetTextFont(63)
        pCMS.SetTextSize(34)
        pCMS.SetTextAlign(11)
        pCMS.AddText("CMS")
        pCMS.Draw("Same")
        
        pPreliminary=ROOT.TPaveText(cvxmin+0.025+0.1,cvymax-0.065,cvxmin+0.025+0.1,cvymax-0.065,"NDC")
        pPreliminary.SetFillColor(ROOT.kWhite)
        pPreliminary.SetBorderSize(0)
        pPreliminary.SetTextFont(53)
        pPreliminary.SetTextSize(34)
        pPreliminary.SetTextAlign(11)
        pPreliminary.AddText("Preliminary")
        pPreliminary.Draw("Same")
    
        
        pLumi=ROOT.TPaveText(cvxmax,0.94,cvxmax,0.94,"NDC")
        pLumi.SetFillColor(ROOT.kWhite)
        pLumi.SetBorderSize(0)
        pLumi.SetTextFont(43)
        pLumi.SetTextSize(36)
        pLumi.SetTextAlign(31)
        if title!="":
            pLumi.AddText(title+", 36#kern[-0.5]{ }fb#lower[-0.7]{#scale[0.7]{-1}} (13TeV)")
        else:
            pLumi.AddText("36#kern[-0.5]{ }fb#lower[-0.7]{#scale[0.7]{-1}} (13TeV)")
        pLumi.Draw("Same")
        
        cvHist.Print(output+".pdf")
        cvHist.Print(output+".png")
        
        
        
    def drawHistogramResponseAndEfficiency(self,histMatrix, output, title="",xaxis="",yaxis="",zaxis="transition probability (%)"):
        ROOT.gStyle.SetPaintTextFormat("3.0f")
        cvResponse = ROOT.TCanvas("cvResponse","",800,800)
        cvResponse.Divide(1,2,0,0)
        
        cvResponse.GetPad(1).SetPad(0.0, 0.0, 1.0, 1.0)
        cvResponse.GetPad(1).SetFillStyle(4000)
        cvResponse.GetPad(2).SetPad(0.0, 0.00, 1.0,1.0)
        cvResponse.GetPad(2).SetFillStyle(4000)
        
        cvxmin=0.14
        cvxmax=0.8
        cvymin=0.12
        cvymax=0.92
        resHeight=0.3
            
        for i in range(1,3):
            #for the canvas:
            cvResponse.GetPad(i).SetBorderMode(0)
            cvResponse.GetPad(i).SetGridx(False)
            cvResponse.GetPad(i).SetGridy(False)


            #For the frame:
            cvResponse.GetPad(i).SetFrameBorderMode(0)
            cvResponse.GetPad(i).SetFrameBorderSize(1)
            cvResponse.GetPad(i).SetFrameFillColor(0)
            cvResponse.GetPad(i).SetFrameFillStyle(0)
            cvResponse.GetPad(i).SetFrameLineColor(1)
            cvResponse.GetPad(i).SetFrameLineStyle(1)
            cvResponse.GetPad(i).SetFrameLineWidth(int(1))

            # Margins:
            cvResponse.GetPad(i).SetLeftMargin(cvxmin)
            cvResponse.GetPad(i).SetRightMargin(1-cvxmax)
            
            # For the Global title:
            cvResponse.GetPad(i).SetTitle("")
            
            # For the axis:
            cvResponse.GetPad(i).SetTickx(1)  # To get tick marks on the opposite side of the frame
            cvResponse.GetPad(i).SetTicky(1)

            # Change for log plots:
            cvResponse.GetPad(i).SetLogx(0)
            cvResponse.GetPad(i).SetLogy(0)
            cvResponse.GetPad(i).SetLogz(0)
        
        cvResponse.GetPad(2).SetTopMargin(1-cvymax)
        cvResponse.GetPad(2).SetBottomMargin(resHeight+0.02)
        cvResponse.GetPad(1).SetTopMargin(1-resHeight+0.015)
        cvResponse.GetPad(1).SetBottomMargin(cvymin)
        
        cvResponse.cd(2)
        #histMatrixGenAll = histMatrix.ProjectionX(histMatrix.GetName()+"all",0,-1)
        histMatrixGenSelected = histMatrix.ProjectionX(histMatrix.GetName()+"sel",1,-1)
        
        for ibin in range(histMatrix.GetNbinsX()):
            genSum = histMatrix.GetBinContent(ibin+1,0)
            selSum = 0.0
            for jbin in range(histMatrix.GetNbinsY()):
                c=histMatrix.GetBinContent(ibin+1,jbin+1)
                if c<0.000000000000001:
                    histMatrix.SetBinContent(ibin+1,jbin+1,0.000000000000001)
                selSum+=c
                
            if selSum>0:
                histMatrixGenSelected.SetBinContent(ibin+1,selSum/(genSum+selSum))
            else:
                histMatrixGenSelected.SetBinContent(ibin+1,0)
        
        #histMatrixGenSelected.Divide(histMatrixGenAll)
        histMatrixGenSelected.Scale(100.)
        histMatrixGenSelected.SetLineWidth(2)
        histMatrixGenSelected.SetLineColor(ROOT.kRed+1)
        hist = self.module("Utils").normalizeByTransistionProbability(histMatrix)
        
        histMatrixGenSelected.GetYaxis().SetTickLength(0.03/resHeight)
        histMatrixGenSelected.GetYaxis().Set(50,0,1.2*histMatrixGenSelected.GetMaximum())
        histMatrixGenSelected.GetYaxis().SetRangeUser(0,1.2*histMatrixGenSelected.GetMaximum())
        histMatrixGenSelected.GetYaxis().SetNdivisions(804)
        
        hist.GetXaxis().SetTitle("")
        histMatrixGenSelected.GetXaxis().SetTitle(xaxis)
        histMatrixGenSelected.GetYaxis().SetTitle("eff. (%)")
        hist.GetYaxis().SetTitle(yaxis)
        hist.GetZaxis().SetTitle(zaxis)
        
        
        histMatrixGenSelected.GetXaxis().SetTitleSize(36)
        histMatrixGenSelected.GetYaxis().SetTitleSize(36)
        histMatrixGenSelected.GetXaxis().SetTitleOffset(1.3)
        histMatrixGenSelected.GetYaxis().SetTitleOffset(1.5)
        hist.GetYaxis().SetTitleOffset(1.5)
        hist.GetZaxis().SetTitleOffset(1.5)
        hist.GetYaxis().SetTitleSize(36)
        hist.GetZaxis().SetTitleSize(36)
        
        hist.GetXaxis().SetLabelSize(0)
        histMatrixGenSelected.GetXaxis().SetLabelSize(33)
        histMatrixGenSelected.GetYaxis().SetLabelSize(33)
        hist.GetYaxis().SetLabelSize(33)
        hist.GetZaxis().SetLabelSize(33)

        hist.Scale(100.)
            
        ymax = 1.1*hist.GetMaximum()
        ymin = hist.GetMinimum()
        hist.GetZaxis().Set(50,ymin,ymax)
        hist.GetZaxis().SetRangeUser(ymin,ymax)
        hist.SetMarkerSize(1.9)
        hist.Draw("colz text")
        
        pCMS=ROOT.TPaveText(cvxmin,0.94,cvxmin,0.94,"NDC")
        pCMS.SetFillColor(ROOT.kWhite)
        pCMS.SetBorderSize(0)
        pCMS.SetTextFont(63)
        pCMS.SetTextSize(36)
        pCMS.SetTextAlign(11)
        pCMS.AddText("CMS")
        pCMS.Draw("Same")
        
        pPreliminary=ROOT.TPaveText(cvxmin+0.12,0.94,cvxmin+0.12,0.94,"NDC")
        pPreliminary.SetFillColor(ROOT.kWhite)
        pPreliminary.SetBorderSize(0)
        pPreliminary.SetTextFont(53)
        pPreliminary.SetTextSize(36)
        pPreliminary.SetTextAlign(11)
        pPreliminary.AddText("Simulation")
        pPreliminary.Draw("Same")
        

        pLumi=ROOT.TPaveText(cvxmax,0.94,cvxmax,0.94,"NDC")
        pLumi.SetFillColor(ROOT.kWhite)
        pLumi.SetBorderSize(0)
        pLumi.SetTextFont(43)
        pLumi.SetTextSize(36)
        pLumi.SetTextAlign(31)
        if title!="":
            pLumi.AddText(title)
        pLumi.Draw("Same")
        
        cvResponse.cd(1)
        histMatrixGenSelected.Draw("SameHIST")
        
        cvResponse.Update()
        
        cvResponse.Print(output+".png")
        cvResponse.Print(output+".pdf") 
        
        
    
    def drawHistogramMatrix(self,histMatrix, output, title="", xaxis="",yaxis="",zaxis="",autoscaling=True):
        ROOT.gStyle.SetPaintTextFormat("3.0f")
        cvResponse = ROOT.TCanvas("cvResponse","",800,700)
        cvResponse.SetRightMargin(0.19)
        
        cvResponse.SetLeftMargin(0.14)
        cvResponse.SetBottomMargin(0.125)
        
        hist = histMatrix.Clone(histMatrix.GetName()+"drawing")
        
        hist.GetXaxis().SetTitle(xaxis)
        hist.GetYaxis().SetTitle(yaxis)
        hist.GetZaxis().SetTitle(zaxis)
        
        
        hist.GetXaxis().SetTitleSize(36)
        hist.GetYaxis().SetTitleSize(36)
        hist.GetZaxis().SetTitleSize(36)
        
        hist.GetXaxis().SetLabelSize(33)
        hist.GetYaxis().SetLabelSize(33)
        hist.GetZaxis().SetLabelSize(33)

        order = 0
        if autoscaling:
            order = math.ceil(math.log10(hist.GetMaximum()))-2
            hist.Scale(10**(-order))
            
        ymax = 1.1*hist.GetMaximum()
        ymin = hist.GetMinimum()
        hist.GetZaxis().Set(50,ymin,ymax)
        hist.GetZaxis().SetRangeUser(ymin,ymax)
        hist.SetMarkerSize(1.9)
        hist.Draw("colz text")
        
        pCMS=ROOT.TPaveText(cvResponse.GetLeftMargin(),0.94,cvResponse.GetLeftMargin(),0.94,"NDC")
        pCMS.SetFillColor(ROOT.kWhite)
        pCMS.SetBorderSize(0)
        pCMS.SetTextFont(63)
        pCMS.SetTextSize(36)
        pCMS.SetTextAlign(11)
        pCMS.AddText("CMS")
        pCMS.Draw("Same")
        
        pPreliminary=ROOT.TPaveText(cvResponse.GetLeftMargin()+0.12,0.94,cvResponse.GetLeftMargin()+0.12,0.94,"NDC")
        pPreliminary.SetFillColor(ROOT.kWhite)
        pPreliminary.SetBorderSize(0)
        pPreliminary.SetTextFont(53)
        pPreliminary.SetTextSize(36)
        pPreliminary.SetTextAlign(11)
        pPreliminary.AddText("Simulation")
        pPreliminary.Draw("Same")
        
        pOrder=None
        if autoscaling and order!=0:
            pOrder=ROOT.TPaveText(1-cvResponse.GetRightMargin()+0.1,0.94,1-cvResponse.GetRightMargin()+0.1,0.94,"NDC")
            pOrder.SetFillColor(ROOT.kWhite)
            pOrder.SetBorderSize(0)
            pOrder.SetTextFont(43)
            pOrder.SetTextSize(36)
            pOrder.SetTextAlign(31)
            pOrder.AddText("#times10#lower[-0.7]{#scale[0.7]{%2.0f}}"%(order))
            pOrder.Draw("Same")
            
        pLumi=ROOT.TPaveText(1-cvResponse.GetRightMargin()-0.05,0.94,1-cvResponse.GetRightMargin()-0.05,0.94,"NDC")
        pLumi.SetFillColor(ROOT.kWhite)
        pLumi.SetBorderSize(0)
        pLumi.SetTextFont(43)
        pLumi.SetTextSize(36)
        pLumi.SetTextAlign(31)
        if title!="":
            pLumi.AddText(title)
        pLumi.Draw("Same")
        
        cvResponse.Update()
        
        cvResponse.Print(output+".png")
        cvResponse.Print(output+".pdf")
        
    def drawStabilityPurity(self,histMatrix, output, title="", xaxis=""):
        ROOT.gStyle.SetPaintTextFormat("3.0f")
        cvPS = ROOT.TCanvas("cvPS","",800,700)
        cvPS.SetRightMargin(0.04)
        
        cvPS.SetLeftMargin(0.14)
        cvPS.SetBottomMargin(0.125)
        
        genBinning = numpy.zeros(histMatrix.GetNbinsX()+1)
        for ibin in range(histMatrix.GetNbinsX()+1):
            genBinning[ibin]=histMatrix.GetXaxis().GetBinLowEdge(ibin+1)
        purityHist = ROOT.TH1F("purity"+str(random.random()),"",len(genBinning)-1,genBinning)
        stabilityHist = ROOT.TH1F("stability"+str(random.random()),"",len(genBinning)-1,genBinning)

        
        print "bins: ",
        for recoBin in range(histMatrix.GetNbinsY()):
            c = histMatrix.GetYaxis().GetBinCenter(recoBin+1)
            w = histMatrix.GetYaxis().GetBinWidth(recoBin+1)
            print "[%5.1f; %5.1f]  "%(c-0.5*w,c+0.5*w),
        print
        print "Stability & ",
        for recoBin in range(histMatrix.GetNbinsY()):
            sumGen = 0.0
            for genBin in range(histMatrix.GetNbinsX()):
                sumGen+=histMatrix.GetBinContent(genBin+1,recoBin+1)
            stability = histMatrix.GetBinContent(recoBin+1,recoBin+1)/sumGen
            stabilityHist.SetBinContent(recoBin+1,stability)
            print "%5.0f%% & "%(stability*100.),
        print
        
        print "Purity & ",
        for genBin in range(histMatrix.GetNbinsX()):
            sumReco = 0.0
            for recoBin in range(histMatrix.GetNbinsY()):
                sumReco+=histMatrix.GetBinContent(genBin+1,recoBin+1)
            purity = histMatrix.GetBinContent(genBin+1,genBin+1)/sumReco
            purityHist.SetBinContent(genBin+1,purity)
            print "%5.0f%% & "%(purity*100.),
        print
        
        axis = ROOT.TH2F("axis"+str(random.random()),";"+xaxis+";",50,genBinning[0],genBinning[-1],50,0,1)
        
        axis.GetXaxis().SetTitleSize(36)
        axis.GetYaxis().SetTitleSize(36)
        
        axis.GetXaxis().SetLabelSize(33)
        axis.GetYaxis().SetLabelSize(33)
        axis.Draw("AXIS")

        stabilityHist.SetLineWidth(3)
        stabilityHist.SetLineColor(ROOT.kAzure-5)
        stabilityHist.Draw("SameHIST")
        purityHist.SetLineWidth(3)
        purityHist.SetLineColor(ROOT.kOrange+8)
        purityHist.Draw("SameHIST")
        
        if min(map(lambda x: x.GetMinimum(),[stabilityHist,purityHist]))>0.5:
            legend = ROOT.TLegend(0.35,0.46,0.65,0.35)
        else:
            legend = ROOT.TLegend(0.35,0.84,0.65,0.73)
        legend.SetBorderSize(0)
        legend.SetTextFont(42)
        legend.SetFillColor(ROOT.kWhite)
        legend.AddEntry(stabilityHist,"stability","L")
        legend.AddEntry(purityHist,"purity","L")
        legend.Draw("Same")
        
        pCMS=ROOT.TPaveText(cvPS.GetLeftMargin(),0.94,cvPS.GetLeftMargin(),0.94,"NDC")
        pCMS.SetFillColor(ROOT.kWhite)
        pCMS.SetBorderSize(0)
        pCMS.SetTextFont(63)
        pCMS.SetTextSize(36)
        pCMS.SetTextAlign(11)
        pCMS.AddText("CMS")
        pCMS.Draw("Same")
        
        pPreliminary=ROOT.TPaveText(cvPS.GetLeftMargin()+0.12,0.94,cvPS.GetLeftMargin()+0.12,0.94,"NDC")
        pPreliminary.SetFillColor(ROOT.kWhite)
        pPreliminary.SetBorderSize(0)
        pPreliminary.SetTextFont(53)
        pPreliminary.SetTextSize(36)
        pPreliminary.SetTextAlign(11)
        pPreliminary.AddText("Simulation")
        pPreliminary.Draw("Same")
        
        pTitle=ROOT.TPaveText(1-cvPS.GetRightMargin(),0.94,1-cvPS.GetRightMargin(),0.94,"NDC")
        pTitle.SetFillColor(ROOT.kWhite)
        pTitle.SetBorderSize(0)
        pTitle.SetTextFont(43)
        pTitle.SetTextSize(36)
        pTitle.SetTextAlign(31)
        pTitle.AddText(title)
        pTitle.Draw("Same")

        cvPS.Update()
        
        cvPS.Print(output+".png")
        cvPS.Print(output+".pdf")
        
    '''
    def drawBiasTest(self,unfoldedHist,genHist,varTitle,outputName):
        cvUnfold = ROOT.TCanvas("cvUnfold","",800,700)

        axisUnfolding = ROOT.TH2F("axisUnfolding",";unfolded "+varTitle+";a.u.",50,genHist.GetXaxis().GetXmin(),genHist.GetXaxis().GetXmax(),50,0,1.2*max(unfoldedHist.GetMaximum(),genHist.GetMaximum()))
        axisUnfolding.Draw("AXIS")
        genHist.SetLineColor(ROOT.kAzure-4)
        genHist.SetLineWidth(2)
        genHist.Draw("HISTSame")
        unfoldedHist.SetMarkerSize(1.0)
        unfoldedHist.SetMarkerStyle(20)
        unfoldedHist.SetLineWidth(2)
        unfoldedHist.Draw("SamePE")
        
        pCMS=ROOT.TPaveText(1-cvUnfold.GetRightMargin()-0.25,0.94,1-cvUnfold.GetRightMargin()-0.25,0.94,"NDC")
        pCMS.SetFillColor(ROOT.kWhite)
        pCMS.SetBorderSize(0)
        pCMS.SetTextFont(63)
        pCMS.SetTextSize(30)
        pCMS.SetTextAlign(11)
        pCMS.AddText("CMS")
        pCMS.Draw("Same")
        
        pPreliminary=ROOT.TPaveText(1-cvUnfold.GetRightMargin()-0.165,0.94,1-cvUnfold.GetRightMargin()-0.165,0.94,"NDC")
        pPreliminary.SetFillColor(ROOT.kWhite)
        pPreliminary.SetBorderSize(0)
        pPreliminary.SetTextFont(53)
        pPreliminary.SetTextSize(30)
        pPreliminary.SetTextAlign(11)
        pPreliminary.AddText("Simulation")
        pPreliminary.Draw("Same")
        
        cvUnfold.Print(os.path.join(self.module("Utils").getOutputFolder(),outputName+".png"))
        cvUnfold.Print(os.path.join(self.module("Utils").getOutputFolder(),outputName+".pdf"))
        
        
    def drawDataSubtracted(self,dataHist,recoHist,varTitle,outputName):
        cvData = ROOT.TCanvas("cvData","",800,700)

        axisUnfolding = ROOT.TH2F("axisUnfolding",";reconstructed"+varTitle+";a.u.",50,recoHist.GetXaxis().GetXmin(),recoHist.GetXaxis().GetXmax(),50,0,1.2*max(recoHist.GetMaximum(),dataHist.GetMaximum()))
        axisUnfolding.Draw("AXIS")
        recoHist.SetLineColor(ROOT.kAzure-4)
        recoHist.SetLineWidth(2)
        recoHist.Draw("HISTSame")
        dataHist.SetMarkerSize(1.0)
        dataHist.SetMarkerStyle(20)
        dataHist.SetLineWidth(2)
        dataHist.Draw("SamePE")
        
        pCMS=ROOT.TPaveText(1-cvData.GetRightMargin()-0.25,0.94,1-cvData.GetRightMargin()-0.25,0.94,"NDC")
        pCMS.SetFillColor(ROOT.kWhite)
        pCMS.SetBorderSize(0)
        pCMS.SetTextFont(63)
        pCMS.SetTextSize(30)
        pCMS.SetTextAlign(11)
        pCMS.AddText("CMS")
        pCMS.Draw("Same")
        
        pPreliminary=ROOT.TPaveText(1-cvData.GetRightMargin()-0.165,0.94,1-cvData.GetRightMargin()-0.165,0.94,"NDC")
        pPreliminary.SetFillColor(ROOT.kWhite)
        pPreliminary.SetBorderSize(0)
        pPreliminary.SetTextFont(53)
        pPreliminary.SetTextSize(30)
        pPreliminary.SetTextAlign(11)
        pPreliminary.AddText("Simulation")
        pPreliminary.Draw("Same")
        
        cvData.Print(os.path.join(self.module("Utils").getOutputFolder(),outputName+".png"))
        cvData.Print(os.path.join(self.module("Utils").getOutputFolder(),outputName+".pdf"))
        
    def drawFitCorrelation(self,covariance):
        cvCovariance = ROOT.TCanvas("cvCorrelations","",900,700)
        cvCovariance.SetRightMargin(0.19)
        cvCovariance.SetLeftMargin(0.19)
        covarianceClone = covariance.Clone()
        covarianceClone.SetMarkerSize(1.9)
        ROOT.gStyle.SetPaintTextFormat("3.0f")
        covarianceClone.Scale(100.)
        for i in range(covarianceClone.GetNbinsX()):
            covarianceClone.GetXaxis().SetBinLabel(i+1,""+covarianceClone.GetXaxis().GetBinLabel(i+1).replace("_"," ").replace("QCD","Multijet"))
            covarianceClone.GetYaxis().SetBinLabel(i+1,""+covarianceClone.GetYaxis().GetBinLabel(i+1).replace("_"," ").replace("QCD","Multijet"))
        covarianceClone.GetXaxis().SetLabelOffset(covariance.GetXaxis().GetLabelOffset()*1.6)
        covarianceClone.GetXaxis().SetTitleOffset(1.35)
        covarianceClone.GetZaxis().SetTitle("Correlation (%)")
        covarianceClone.GetZaxis().Set(50,-100,100)
        covarianceClone.GetZaxis().SetRangeUser(-100,100)
        covarianceClone.GetZaxis().SetTitleOffset(1.3)
        covarianceClone.Draw("colz text")
        
        pCMS=ROOT.TPaveText(cvCovariance.GetLeftMargin(),0.94,cvCovariance.GetLeftMargin(),0.94,"NDC")
        pCMS.SetFillColor(ROOT.kWhite)
        pCMS.SetBorderSize(0)
        pCMS.SetTextFont(63)
        pCMS.SetTextSize(34)
        pCMS.SetTextAlign(11)
        pCMS.AddText("CMS")
        pCMS.Draw("Same")
        
        pPreliminary=ROOT.TPaveText(cvCovariance.GetLeftMargin()+0.1,0.94,cvCovariance.GetLeftMargin()+0.1,0.94,"NDC")
        pPreliminary.SetFillColor(ROOT.kWhite)
        pPreliminary.SetBorderSize(0)
        pPreliminary.SetTextFont(53)
        pPreliminary.SetTextSize(34)
        pPreliminary.SetTextAlign(11)
        pPreliminary.AddText("Preliminary")
        pPreliminary.Draw("Same")
        
        cvCovariance.Print(os.path.join(self.module("Utils").getOutputFolder(),"fitCorrelations.pdf"))
        cvCovariance.Print(os.path.join(self.module("Utils").getOutputFolder(),"fitCorrelations.png"))
        
        cvCovariance.Update()
        cvCovariance.WaitPrimitive()
        
    def drawMultiFitResults(self,fitResults,name):
    
        axisRange = {}
        values = {}
        
        ymin = 10
        ymax = -10
        
        xmin = 1000
        xmax = -1000

        for fitResult in fitResults:
            ranges = fitResult["range"]
            for comp in self.module("ThetaModel").getComponentsDict().keys():
                if not axisRange.has_key(comp):
                    axisRange[comp]={"xmin":1000,"xmax":-1000,"ymin":1000,"ymax":-1000}
                    values[comp]=[]
                mean = fitResult["res"][comp]["mean"]
                unc = fitResult["res"][comp]["unc"]
                
                values[comp].append({"mean":mean,"unc":unc,"range":ranges})
                
                xmin=min(xmin,ranges[0])
                xmax=max(xmax,ranges[1])

                ymin=min(ymin,mean-2*unc)
                ymax=max(ymax,mean+2*unc)
                
                
        cvMulti = ROOT.TCanvas("cvMulti"+str(random.random()),"",800,650)
        cvMulti.SetLeftMargin(0.14)
        cvMulti.SetRightMargin(0.24)
        cvMulti.SetBottomMargin(0.13)
        #cvMulti.SetRightMargin(0.17)
        #cvMulti.SetLeftMargin(0.165)
        axis = ROOT.TH2F("axis"+str(random.random()),";"+name.replace("top_pt","top quark p#lower[0.3]{#scale[0.7]{T}} (GeV)").replace("top_y","top quark |y|")+"; Scale factor",
            50,xmin,xmax,
            50,0.,1.8
        )
        axis.GetXaxis().SetTickLength(0.025/(1-cvMulti.GetLeftMargin()-cvMulti.GetRightMargin()))
        axis.GetXaxis().SetNdivisions(1005)
        axis.GetXaxis().SetTitleSize(35)
        axis.GetYaxis().SetTickLength(0.025/(1-cvMulti.GetTopMargin()-cvMulti.GetBottomMargin()))
        axis.GetYaxis().SetTitleSize(35)
        axis.Draw("AXIS")
        
        tf1 = ROOT.TF1("tf1","1",xmin,xmax)
        tf1.SetLineColor(1)
        tf1.Draw("LSame")
                
        rootObj=[]
        
        colors = {
            "tChannel":newColor(1,0.02,0.02),
            "TopBkg":newColor(0.98,0.57,0.05),
            "WZjets":newColor(0.1*0.4,0.95*0.6,0.4*0.4),
            "QCD_2j1t":ROOT.gROOT.GetColor(ROOT.kGray+1),
        }
        
        objs = {}
        
        for icomp,comp in enumerate(values.keys()):
            if comp=="QCD_3j1t" or comp=="QCD_3j2t":
                continue
            for ival,value in enumerate(values[comp][:-1]):
                reRange = (icomp-1.5)*0.003*math.fabs(xmin-xmax)
            
                marker = ROOT.TMarker(
                    0.5*(value["range"][0]+value["range"][1])+reRange,value["mean"],
                    20
                )
                rootObj.append(marker)
                marker.SetMarkerColor(colors[comp].GetNumber())
                marker.SetMarkerSize(1.2)
                marker.Draw("SameP")
            
            
                line = ROOT.TLine(
                    value["range"][0],value["mean"],
                    value["range"][1],value["mean"],
                )
                rootObj.append(line)
                line.SetLineColor(colors[comp].GetNumber())
                line.SetLineWidth(2)
                #line.Draw("SameL")
                
                lineUp = ROOT.TLine(
                    value["range"][0]+reRange,value["mean"]+value["unc"],
                    value["range"][1]-reRange,value["mean"]+value["unc"],
                )
                rootObj.append(lineUp)
                lineUp.SetLineColor(colors[comp].GetNumber())
                lineUp.SetLineWidth(2)
                lineUp.SetLineStyle(1)
                #lineUp.Draw("SameL")
                
                lineDown = ROOT.TLine(
                    value["range"][0]+reRange,value["mean"]-value["unc"],
                    value["range"][1]-reRange,value["mean"]-value["unc"],
                )
                rootObj.append(lineDown)
                lineDown.SetLineColor(colors[comp].GetNumber())
                lineDown.SetLineWidth(2)
                lineDown.SetLineStyle(1)
                #lineDown.Draw("SameL")
                
                lineCenter = ROOT.TLine(
                    0.5*(value["range"][0]+value["range"][1])+reRange,max(value["mean"]-value["unc"],0.0),
                    0.5*(value["range"][0]+value["range"][1])+reRange,min(value["mean"]+value["unc"],2.0),
                )
                rootObj.append(lineCenter)
                lineCenter.SetLineColor(colors[comp].GetNumber())
                lineCenter.SetLineWidth(2)
                lineCenter.Draw("SameL")
                objs[comp]=lineCenter
                
                lineSep = ROOT.TLine(
                    value["range"][1],0.0,
                    value["range"][1],1.8,
                )
                rootObj.append(lineSep)
                lineSep.SetLineColor(ROOT.kBlack)
                lineSep.SetLineWidth(1)
                lineSep.SetLineStyle(2)
                lineSep.Draw("SameL")
                objs["sep"]=lineSep
                
                if (ival+1)<len(values[comp][:-1]):
                    lineNext = ROOT.TLine(
                        0.5*(values[comp][ival]["range"][0]+values[comp][ival]["range"][1])+reRange,values[comp][ival]["mean"],
                        0.5*(values[comp][ival+1]["range"][0]+values[comp][ival+1]["range"][1])+reRange,values[comp][ival+1]["mean"],
                    )
                    rootObj.append(lineNext)
                    lineNext.SetLineColor(colors[comp].GetNumber())
                    lineNext.SetLineWidth(3)
                    lineNext.Draw("SameL")
                    
                    
        ROOT.gPad.RedrawAxis()
                    
        legend = ROOT.TLegend(0.761,0.9,0.99,0.9-0.08*4)
        legend.SetFillStyle(0)
        legend.SetBorderSize(0)
        legend.SetTextFont(43)
        legend.SetTextSize(34)
        legend.AddEntry(objs["tChannel"],"#it{t}-channel","L")
        legend.AddEntry(objs["TopBkg"],"Top bkg.","L")
        legend.AddEntry(objs["WZjets"],"W/Z+jets","L")
        legend.AddEntry(objs["QCD_2j1t"],"Multijet","L")
        
        
            
        pCMS=ROOT.TPaveText(cvMulti.GetLeftMargin(),0.94,cvMulti.GetLeftMargin(),0.94,"NDC")
        pCMS.SetFillColor(ROOT.kWhite)
        pCMS.SetBorderSize(0)
        pCMS.SetTextFont(63)
        pCMS.SetTextSize(34)
        pCMS.SetTextAlign(11)
        pCMS.AddText("CMS")
        pCMS.Draw("Same")
        
        pPreliminary=ROOT.TPaveText(cvMulti.GetLeftMargin()+0.1,0.94,cvMulti.GetLeftMargin()+0.1,0.94,"NDC")
        pPreliminary.SetFillColor(ROOT.kWhite)
        pPreliminary.SetBorderSize(0)
        pPreliminary.SetTextFont(53)
        pPreliminary.SetTextSize(34)
        pPreliminary.SetTextAlign(11)
        pPreliminary.AddText("Preliminary")
        pPreliminary.Draw("Same")
         
        cvMulti.Update()
        cvMulti.Print(os.path.join(self.module("Utils").getOutputFolder(),"multi_"+name+"_nol.C"))
        cvMulti.Print(os.path.join(self.module("Utils").getOutputFolder(),"multi_"+name+"_nol.pdf"))

            
        legend.Draw("Same")
        cvMulti.Update()
        cvMulti.Print(os.path.join(self.module("Utils").getOutputFolder(),"multi_"+name+".C"))
        cvMulti.Print(os.path.join(self.module("Utils").getOutputFolder(),"multi_"+name+".pdf"))

        
    def drawPStest(self,responseMatrix,genBinning,varname,name):
        purityHist = ROOT.TH1F("purity"+str(random.random()),";top quark pT;purity=N(reco. & gen.)/N(reco.)",len(genBinning)-1,genBinning)
        stabilityHist = ROOT.TH1F("stability"+str(random.random()),";top quark pT;stability=N(reco. & gen.)/N(gen.)",len(genBinning)-1,genBinning)
        
        responseMatrixSelectedPStest = responseMatrix.Clone(responseMatrix.GetName()+"RStest")
        responseMatrixSelectedPStest.RebinY(2)
        
        print "bins: ",
        for recoBin in range(responseMatrixSelectedPStest.GetNbinsY()):
            c = responseMatrixSelectedPStest.GetYaxis().GetBinCenter(recoBin+1)
            w = responseMatrixSelectedPStest.GetYaxis().GetBinWidth(recoBin+1)
            print "[%5.1f; %5.1f]  "%(c-0.5*w,c+0.5*w),
        print
        print "Stability & ",
        for recoBin in range(responseMatrixSelectedPStest.GetNbinsY()):
            sumGen = 0.0
            for genBin in range(responseMatrixSelectedPStest.GetNbinsX()):
                sumGen+=responseMatrixSelectedPStest.GetBinContent(genBin+1,recoBin+1)
            stability = responseMatrixSelectedPStest.GetBinContent(recoBin+1,recoBin+1)/sumGen
            stabilityHist.SetBinContent(recoBin+1,stability)
            print "%5.0f%% & "%(stability*100.),
        print
        
        print "Purity & ",
        for genBin in range(responseMatrixSelectedPStest.GetNbinsX()):
            sumReco = 0.0
            for recoBin in range(responseMatrixSelectedPStest.GetNbinsY()):
                sumReco+=responseMatrixSelectedPStest.GetBinContent(genBin+1,recoBin+1)
            purity = responseMatrixSelectedPStest.GetBinContent(genBin+1,genBin+1)/sumReco
            purityHist.SetBinContent(genBin+1,purity)
            print "%5.0f%% & "%(purity*100.),
        print
            
        axis = ROOT.TH2F("axis"+str(random.random()),";"+varname+";",50,genBinning[0],genBinning[-1],50,0.0,1.0)
        cv = ROOT.TCanvas("cvPS"+str(random.random()),"",800,700)
        axis.Draw("AXIS")
        stabilityHist.SetLineWidth(3)
        stabilityHist.SetLineColor(ROOT.kAzure-5)
        stabilityHist.Draw("SAME")
        purityHist.SetLineWidth(3)
        purityHist.SetLineColor(ROOT.kOrange+8)
        purityHist.Draw("SAME")
        
        legend = ROOT.TLegend(0.35,0.35,0.65,0.24)
        legend.SetBorderSize(0)
        legend.SetTextFont(42)
        legend.SetFillColor(ROOT.kWhite)
        legend.AddEntry(stabilityHist,"stability","L")
        legend.AddEntry(purityHist,"purity","L")
        legend.Draw("Same")
        
        cv.Print(os.path.join(self.module("Utils").getOutputFolder(),"PStest_"+name+".pdf"))
        cv.Print(os.path.join(self.module("Utils").getOutputFolder(),"PStest_"+name+".png"))

    def plotHistogram(self,histogram,title,output):
        
        cvHist = ROOT.TCanvas("cvHist","",800,700)
        histogram.GetXaxis().SetTitle(title)
        histogram.Draw()
        
        pCMS=ROOT.TPaveText(1-cvHist.GetRightMargin()-0.25,0.94,1-cvHist.GetRightMargin()-0.25,0.94,"NDC")
        pCMS.SetFillColor(ROOT.kWhite)
        pCMS.SetBorderSize(0)
        pCMS.SetTextFont(63)
        pCMS.SetTextSize(30)
        pCMS.SetTextAlign(11)
        pCMS.AddText("CMS")
        pCMS.Draw("Same")
        
        pPreliminary=ROOT.TPaveText(1-cvHist.GetRightMargin()-0.165,0.94,1-cvHist.GetRightMargin()-0.165,0.94,"NDC")
        pPreliminary.SetFillColor(ROOT.kWhite)
        pPreliminary.SetBorderSize(0)
        pPreliminary.SetTextFont(53)
        pPreliminary.SetTextSize(30)
        pPreliminary.SetTextAlign(11)
        pPreliminary.AddText("Preliminary")
        pPreliminary.Draw("Same")
        
        cvHist.Print(os.path.join(self.module("Utils").getOutputFolder(),output+".pdf"))
        cvHist.Print(os.path.join(self.module("Utils").getOutputFolder(),output+".png"))
        
        
    def plotHistograms(self,histograms,title,output):
        mcStack = ROOT.THStack()
        mcSumHist = None
        for component in self.module("ThetaModel").getComponentsDict():
            compHist = None
            for sampleName in histograms[component]["hists"].keys():
                if compHist==None:
                    compHist = histograms[component]["hists"][sampleName].Clone(component+str(random.random()))
                else:
                    compHist.Add(histograms[component]["hists"][sampleName])
            mcStack.Add(compHist,"HIST")
            
            if mcSumHist==None:
                mcSumHist=compHist.Clone("mcSumHist")
            else:
                mcSumHist.Add(compHist)
            
        dataHist = histograms["data"]["hists"]["data"]
        
        cvPlot = ROOT.TCanvas("cvPlot","",800,700)
        
        axis = ROOT.TH2F("axis",";title;Events",
            50,dataHist.GetXaxis().GetXmin(),dataHist.GetXaxis().GetXmax(),
            50,0.0,1.2*max(dataHist.GetMaximum(),mcSumHist.GetMaximum())
        )
        axis.Draw("AXIS")
        mcStack.Draw("SameHIST")
        dataHist.Draw("SamePE") 
        
        cvPlot.Update()
        cvPlot.WaitPrimitive()
        
        cvPlot.Print(os.path.join(self.module("Utils").getOutputFolder(),output+".png"))
        cvPlot.Print(os.path.join(self.module("Utils").getOutputFolder(),output+".pdf"))
    '''

