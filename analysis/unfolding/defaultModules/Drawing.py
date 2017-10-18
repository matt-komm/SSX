import logging
import ROOT
import os
import random
import math
import re
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
        
    def drawPosterior(self,fitResult,outputFile,selection=[],ranges=[-2,2],default=None):
        
        fitResultSelected = {"parameters": {}}
        if len(selection)==0:
            fitResultSelected = fitResult
        else:
            for ipar,parameterName in enumerate(sorted(fitResult["parameters"].keys())):
                for select in selection:
                    regex = re.compile(select.replace("*","[A-Za-z0-9]*"))
                    if regex.match(parameterName):
                        fitResultSelected["parameters"][parameterName]=fitResult["parameters"][parameterName]
                        break
        
        Npar = len(fitResultSelected["parameters"].keys())
            
        ROOT.gStyle.SetPaintTextFormat("4.0f")
        cv = ROOT.TCanvas("corr","",800,400+Npar*25)
        cv.SetLeftMargin(0.35)
        cv.SetRightMargin(0.04)
        cv.SetBottomMargin(100./(400+Npar*25))
        axis = ROOT.TH2F("axis",";Parameter;",50,ranges[0],ranges[1],Npar,0,Npar)
        axis.GetXaxis().SetTickLength(30./(400+Npar*25))
        axis.GetYaxis().SetTickLength(0.02)
        for ipar,parameterName in enumerate(sorted(fitResultSelected["parameters"].keys())):
            axis.GetYaxis().SetBinLabel(ipar+1,parameterName.replace("_"," "))
            
        axis.Draw("AXIS")
        rootObj = []
        for ipar,parameterName in enumerate(sorted(fitResultSelected["parameters"].keys())):
            priorMean = fitResultSelected["parameters"][parameterName]["mean_prior"]
            priorUnc = fitResultSelected["parameters"][parameterName]["unc_prior"]
            priorBox = ROOT.TBox(max(ranges[0],priorMean-priorUnc),ipar+0.25,min(ranges[1],priorMean+priorUnc),ipar+0.75)
            priorBox.SetFillColor(ROOT.kGray)
            rootObj.append(priorBox)
            priorBox.Draw("FSame")
            
        if default!=None:
            defaultLine = ROOT.TLine(default,0,default,Npar)
            defaultLine.SetLineColor(ROOT.kOrange+7)
            defaultLine.SetLineWidth(2)
            defaultLine.Draw("LSame")
            rootObj.append(defaultLine)
        ROOT.gPad.RedrawAxis()

        for ipar,parameterName in enumerate(sorted(fitResultSelected["parameters"].keys())):
            fitMean = fitResultSelected["parameters"][parameterName]["mean_fit"]
            fitUnc = fitResultSelected["parameters"][parameterName]["unc_fit"]
            fitLine = ROOT.TLine(max(ranges[0],fitMean-fitUnc),ipar+0.5,min(ranges[1],fitMean+fitUnc),ipar+0.5)
            fitLine.SetLineWidth(1)
            rootObj.append(fitLine)
            fitLine.Draw("LSame")
            fitMarker = ROOT.TMarker(fitMean,ipar+0.5,20)
            fitMarker.SetMarkerSize(1.3)
            rootObj.append(fitMarker)
            fitMarker.Draw("PSame")
       
        cv.Print(outputFile)
        
        
    def plotDataHistogram(self,nominalHist,measuredHist,title,output):
        
        cvHist = ROOT.TCanvas("cvHist","",800,700)
        axis = ROOT.TH2F("axis"+str(random.random()),";"+title+";Events",
            50,nominalHist.GetXaxis().GetXmin(),nominalHist.GetXaxis().GetXmax(),
            50,0.,1.3*max(nominalHist.GetMaximum(),measuredHist.GetMaximum())
        )
        axis.Draw("AXIS")
        
        nominalHist.SetLineColor(ROOT.kRed+1)
        nominalHist.SetLineWidth(3)
        nominalHist.SetFillStyle(0)
        nominalHist.Draw("HISTSame")
        
        measuredHist.SetLineColor(ROOT.kBlack)
        measuredHist.SetMarkerColor(ROOT.kBlack)
        measuredHist.SetMarkerStyle(20)
        measuredHist.SetLineWidth(2)
        measuredHist.SetMarkerSize(1.5)
        measuredHist.Draw("PESame")
        
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
        
        cvHist.Print(output+".pdf")
        cvHist.Print(output+".png")
        
    '''
    def drawResponseMatrix(self,responseMatrix, varTitle, outputName):
        ROOT.gStyle.SetPaintTextFormat("3.0f")
        cvResponse = ROOT.TCanvas("cvResponse","",800,700)
        cvResponse.SetRightMargin(0.19)
        cvResponse.SetLeftMargin(0.14)
        cvResponse.SetBottomMargin(0.125)
        responseMatrixNorm = self.module("Utils").normalizeByTransistionProbability(responseMatrix)
        responseMatrixNorm.GetXaxis().SetTitle("Parton-level "+varTitle)
        responseMatrixNorm.GetYaxis().SetTitle("Reconstructed "+varTitle)
        responseMatrixNorm.GetZaxis().SetTitle("Transition probability (%)")
        
        
        responseMatrixNorm.GetXaxis().SetTitleSize(36)
        responseMatrixNorm.GetYaxis().SetTitleSize(36)
        responseMatrixNorm.GetZaxis().SetTitleSize(36)
        
        responseMatrixNorm.GetXaxis().SetLabelSize(33)
        responseMatrixNorm.GetYaxis().SetLabelSize(33)
        responseMatrixNorm.GetZaxis().SetLabelSize(33)
        
        responseMatrixNorm.Scale(100.0)
        responseMatrixNorm.SetMarkerSize(1.9)
        responseMatrixNorm.GetZaxis().Set(50,0,50)
        responseMatrixNorm.GetZaxis().SetRangeUser(0,50)
        #responseMatrixNorm.SetMarkerColor(ROOT.kWhite)
        responseMatrixNorm.Draw("colz text")
        
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
        
        cvResponse.Update()
        
        cvResponse.Print(os.path.join(self.module("Utils").getOutputFolder(),outputName+".png"))
        cvResponse.Print(os.path.join(self.module("Utils").getOutputFolder(),outputName+".pdf"))
        
        
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

