from defaultModules.Module import Module

import logging
import ROOT
import copy
import os
import random
from ModelClasses import *

class CheckSys(Module.getClass("Program")):
    def __init__(self,options=[]):
        Module.__init__(self,options)
        self._logger = logging.getLogger(__file__)
        self._logger.setLevel(logging.DEBUG)
        
        
    def applyCanvasStyle(self,cv):
        cv.SetTopMargin(0.1)
        cv.SetBottomMargin(0.2)
        cv.SetLeftMargin(0.15)
        cv.SetRightMargin(0.04)
        
    def applyHistStyle(self,h):
        h.GetXaxis().SetLabelSize(20)
        h.GetYaxis().SetLabelSize(20)
        
        h.GetXaxis().SetTitleSize(20)
        h.GetYaxis().SetTitleSize(20)
        h.GetXaxis().SetTitleOffset(3)
        h.GetYaxis().SetTitleOffset(2.5)
        h.SetTitle("")
        
    def getEnvelope(self,hist1,hist2):
        x = numpy.zeros(4*(hist1.GetNbinsX()))
        y = numpy.zeros(4*(hist1.GetNbinsX()))
        for ibin in range(hist1.GetNbinsX()):
            x[2*ibin] = hist1.GetXaxis().GetBinLowEdge(ibin+1)
            y[2*ibin] = hist1.GetBinContent(ibin+1)
            x[2*ibin+1] = hist1.GetXaxis().GetBinUpEdge(ibin+1)
            y[2*ibin+1] = hist1.GetBinContent(ibin+1)
        
        for ibin in range(hist1.GetNbinsX()):
            x[2*ibin+1+hist1.GetNbinsX()*2] = hist2.GetXaxis().GetBinLowEdge(hist1.GetNbinsX()-ibin)
            y[2*ibin+1+hist1.GetNbinsX()*2] = hist2.GetBinContent(hist1.GetNbinsX()-ibin)
            x[2*ibin+hist1.GetNbinsX()*2] = hist2.GetXaxis().GetBinUpEdge(hist1.GetNbinsX()-ibin)
            y[2*ibin+hist1.GetNbinsX()*2] = hist2.GetBinContent(hist1.GetNbinsX()-ibin)
            
        print x
        print y
        return ROOT.TPolyLine(len(x),x,y)
        
    def execute(self):
        #mu,ele,comb
        channel = self.getOption("channel")
        name = self.getOption("name")
        self._logger.info("make check for: "+str(channel))
        # channel,sysName,binList,[up,down]
        unfoldingName = self.module("Unfolding").getUnfoldingName()
        uncertainties = [] if self.getOption("uncertainties")==None else self.getOption("uncertainties").split(",")
        self._logger.info("Plot uncertainties: "+str(uncertainties))
        
        #maps channel bins to global bins for combinations
        if unfoldingName!="inc":
            binMap = self.module("Unfolding").buildGlobalRecoBinMap()
            
        histogramsPerChannel = {}
        histogramsPerChannelSmooth = {}
        for uncertainty in ["nominal"]+uncertainties:
            histogramsPerChannel[uncertainty] = {}
            histogramsPerChannelSmooth[uncertainty] = {}
            if unfoldingName=="inc":
                histogramsPerChannel[uncertainty]["binInc"] = \
                    self.module("ThetaModel").getHistsFromFiles(channel,unfoldingName,-1,uncertainty) 
                histogramsPerChannelSmooth[uncertainty]["binInc"] = \
                    self.module("ThetaModel").getHistsFromFiles(channel,unfoldingName,-1,uncertainty,smooth=True)
            else:
                nbins = len(self.module("Unfolding").getRecoBinning(channel))-1
                for ibin in range(nbins):
                    histogramsPerChannel[uncertainty]["bin"+str(1+binMap[channel][ibin])] = \
                        self.module("ThetaModel").getHistsFromFiles(channel,unfoldingName,ibin,uncertainty)
                    histogramsPerChannelSmooth[uncertainty]["bin"+str(1+binMap[channel][ibin])] = \
                        self.module("ThetaModel").getHistsFromFiles(channel,unfoldingName,ibin,uncertainty,smooth=True)
                
        nameDict = {
            "unc":"uncl. energy","tw":"tW/t#bar{t} ratio","res":"JER","pu":"pileup","muMulti":"#mu multijet iso. range","muEff":"#mu eff.","ltag":"mistagging eff.","en":"JEC","eleMultiVeto":"e multijet #gamma veto","eleMultiIso":"e multijet iso. range","eleEff":"e efficiency","dy":"W/Z+jet ratio","btag":"b-tagging",
            "ttbarUE": "t#bar{t} UE tune","pdf":"PDF","topMass":"top quark mass","tchanHdampPS":"h#lower[0.3]{#scale[0.7]{damp}}t-ch.","tchanScaleME":"Q scale t-ch.","tchanScalePS":"PS scale t-ch.","ttbarScaleME":"t#bar{t} Q scale","ttbarHdampPS":"d#lower[0.3]{#scale[0.7]{damp}} t#bar{t}","ttbarPt":"t#bar{t} p#lower[0.3]{#scale[0.7]{T}}","ttbarScaleFSRPS":"FSR scale t#bar{t}","ttbarScaleISRPS":"ISR scale t#bar{t}","wjetsScaleME":"Q scale W+jets"
            
        }
        
        self.module("Utils").createFolder("templates/"+channel)
        outputFolder = self.module("Utils").getOutputFolder("templates/"+channel)
        
        for binName in histogramsPerChannel["nominal"].keys():
            for obsName in histogramsPerChannel["nominal"][binName].keys():
                
                histSum = {}
                sumPerCharge = {}
                
                histSumSmooth = {}
                sumPerChargeSmooth = {}
                
                for uncertainty in ["nominal"]+uncertainties:
                    histSum[uncertainty] = None
                    sumPerCharge[uncertainty] = {}
                    
                    histSumSmooth[uncertainty] = None
                    sumPerChargeSmooth[uncertainty] = {}
                    
                    for compName in histogramsPerChannel["nominal"][binName][obsName].keys():
                        if compName=="data":
                            continue
                        compNoCharge = compName.replace("_neg","").replace("_pos","")
                        if not sumPerCharge[uncertainty].has_key(compNoCharge):
                            sumPerCharge[uncertainty][compNoCharge] = histogramsPerChannel[uncertainty][binName][obsName][compName]["hist"].Clone(binName+obsName+compNoCharge+"sum")
                            if histogramsPerChannelSmooth[uncertainty][binName]!=None:
                                sumPerChargeSmooth[uncertainty][compNoCharge] = histogramsPerChannelSmooth[uncertainty][binName][obsName][compName]["hist"].Clone(binName+obsName+compNoCharge+"sum")
                            else:
                                sumPerChargeSmooth[uncertainty][compNoCharge] = histogramsPerChannel[uncertainty][binName][obsName][compName]["hist"].Clone(binName+obsName+compNoCharge+"sum")
                        else:
                            sumPerCharge[uncertainty][compNoCharge].Add(histogramsPerChannel[uncertainty][binName][obsName][compName]["hist"])
                            if histogramsPerChannelSmooth[uncertainty][binName]!=None:
                                sumPerChargeSmooth[uncertainty][compNoCharge].Add(histogramsPerChannelSmooth[uncertainty][binName][obsName][compName]["hist"])
                            else:
                                sumPerChargeSmooth[uncertainty][compNoCharge].Add(histogramsPerChannel[uncertainty][binName][obsName][compName]["hist"])
                        if histSum[uncertainty]==None:
                            histSum[uncertainty] = histogramsPerChannel[uncertainty][binName][obsName][compName]["hist"].Clone(binName+obsName+"sum")
                            if histogramsPerChannelSmooth[uncertainty][binName]!=None:
                                histSumSmooth[uncertainty] = histogramsPerChannelSmooth[uncertainty][binName][obsName][compName]["hist"].Clone(binName+obsName+"sum")
                            else:
                                histSumSmooth[uncertainty] = histogramsPerChannel[uncertainty][binName][obsName][compName]["hist"].Clone(binName+obsName+"sum")
                        else:
                            histSum[uncertainty].Add(histogramsPerChannel[uncertainty][binName][obsName][compName]["hist"])
                            if histogramsPerChannelSmooth[uncertainty][binName]!=None:
                                histSumSmooth[uncertainty].Add(histogramsPerChannelSmooth[uncertainty][binName][obsName][compName]["hist"])
                            else:
                                histSumSmooth[uncertainty].Add(histogramsPerChannel[uncertainty][binName][obsName][compName]["hist"])

                cv = ROOT.TCanvas(binName+obsName+"cv","",800,650)
                cv.SetMargin(0,0,0,0)
                '''
                cv.SetTopMargin(0.15)
                pTitle = ROOT.TPaveText(0.01,0.99,0.99,0.96,"NDC")
                pTitle.SetBorderSize(0)
                pTitle.SetTextFont(42)
                pTitle.AddText(nameDict[name])
                pTitle.Draw("Same")
                pTitleLine = ROOT.TPaveText(0.01,0.959,0.99,0.96,"NDC")
                pTitleLine.SetFillColor(ROOT.kBlack)
                #pTitleLine.Draw("Same")
                '''
                cv.Divide(2,3,0,0)
                for i in range(1,7):
                    self.applyCanvasStyle(cv.GetPad(i))
                
                cv.cd(1)
                
                
                
                
                rootObj = []
                for uncertainty in uncertainties:
                    histSum[uncertainty].Divide(histSum["nominal"])
                    histSum[uncertainty].SetLineStyle(1)
                    histSum[uncertainty].SetLineWidth(2)
                    histSum[uncertainty].SetLineColor(ROOT.kOrange+7)
                    if uncertainty.find("multi"):
                        histSum[uncertainty].Scale(histSum[uncertainty].GetNbinsX()/histSum[uncertainty].Integral())
       
                    
                    histSumSmooth[uncertainty].Divide(histSum["nominal"])
                    histSumSmooth[uncertainty].SetLineStyle(2)
                    histSumSmooth[uncertainty].SetLineColor(ROOT.kBlack)
                    
                    if uncertainty.find("multi"):
                        histSumSmooth[uncertainty].Scale(histSumSmooth[uncertainty].GetNbinsX()/histSumSmooth[uncertainty].Integral())
                    #histSumSmooth[uncertainty].Draw("HISTSame")
                    
                maxRange = max(
                    map(lambda x: 1.1*max(math.fabs(1-x.GetMaximum()),1.1*math.fabs(1-x.GetMinimum())),
                    [histSumSmooth[uncertainties[0]],histSumSmooth[uncertainties[1]]])
                )
                maxRange = 0.025*math.ceil((0.01+maxRange)/0.025)
                    
                axisSum = ROOT.TH2F(
                    "axisSum"+binName+obsName+str(random.random()),
                    ";;sys/nominal",
                    50,
                    histSum["nominal"].GetXaxis().GetBinLowEdge(1),
                    histSum["nominal"].GetXaxis().GetBinUpEdge(histSum["nominal"].GetNbinsX()),
                    50,
                    1-maxRange,
                    1+maxRange
                )
                self.applyHistStyle(axisSum)
                     
                if obsName=="2j1t":
                    axisSum.GetXaxis().SetTitle("fit variable (sum)")
                elif obsName=="3j2t":
                    axisSum.GetXaxis().SetTitle("mT(W) (sum)")
                axisSum.Draw("AXIS")
                
                    
                envelop = self.getEnvelope(histSumSmooth[uncertainties[0]],histSumSmooth[uncertainties[1]])
                envelop.SetFillColor(ROOT.kGray)
                envelop.SetLineColor(ROOT.kGray+1)
                envelop.SetLineWidth(2)
                envelop.SetFillStyle(1001)
                envelop.Draw("F")
                envelop.Draw()
                rootObj.append(envelop)
                
                for uncertainty in uncertainties:
                    histSum[uncertainty].Draw("HISTSame")
                
                
                
                for icomp,compName in enumerate(sorted(sumPerCharge["nominal"].keys())):
                    #if compName.find("QCD")>=0 and compName.find(obsName)<0:
                    #    continue
                    cv.cd(icomp+2)
                    
                    
                    
                    
                    
                    
                    for uncertainty in uncertainties:
                        sumPerCharge[uncertainty][compName].Divide(sumPerCharge["nominal"][compName])
                        sumPerCharge[uncertainty][compName].SetLineStyle(1)
                        sumPerCharge[uncertainty][compName].SetLineWidth(2)
                        sumPerCharge[uncertainty][compName].SetLineColor(ROOT.kOrange+7)
                        #sumPerCharge[uncertainty][compName].Draw("HISTSame")
                        if uncertainty.find("multi"):
                            sumPerCharge[uncertainty][compName].Scale(sumPerCharge[uncertainty][compName].GetNbinsX()/sumPerCharge[uncertainty][compName].Integral())

                        
                        sumPerChargeSmooth[uncertainty][compName].Divide(sumPerCharge["nominal"][compName])
                        sumPerChargeSmooth[uncertainty][compName].SetLineStyle(2)
                        sumPerChargeSmooth[uncertainty][compName].SetLineColor(ROOT.kBlack)
                        #sumPerChargeSmooth[uncertainty][compName].Draw("HISTSame")
                        if uncertainty.find("multi"):
                            sumPerChargeSmooth[uncertainty][compName].Scale(sumPerChargeSmooth[uncertainty][compName].GetNbinsX()/sumPerChargeSmooth[uncertainty][compName].Integral())

                    maxRange = max(
                        map(lambda x: 1.1*max(math.fabs(1-x.GetMaximum()),1.1*math.fabs(1-x.GetMinimum())),
                        [sumPerChargeSmooth[uncertainties[0]][compName],sumPerChargeSmooth[uncertainties[1]][compName]])
                    )
                    maxRange = 0.025*math.ceil((0.01+maxRange)/0.025)

                    axisComp = ROOT.TH2F(
                        "axisSum"+binName+obsName+compName+str(random.random()),
                        ";;sys/nominal",
                        50,
                        histSum["nominal"].GetXaxis().GetBinLowEdge(1),
                        histSum["nominal"].GetXaxis().GetBinUpEdge(histSum["nominal"].GetNbinsX()),
                        50,
                        1.-maxRange,
                        1.+maxRange
                    )
                    rootObj.append(axisComp)
                    self.applyHistStyle(axisComp)
                    
                    if obsName=="2j1t":
                        axisComp.GetXaxis().SetTitle("fit variable ("+compName+")")
                    elif obsName=="3j2t":
                        axisComp.GetXaxis().SetTitle("mT(W) ("+compName+")")
                    axisComp.Draw("AXIS")
                        
                    envelop = self.getEnvelope(sumPerChargeSmooth[uncertainties[0]][compName],sumPerChargeSmooth[uncertainties[1]][compName])
                    envelop.SetFillColor(ROOT.kGray)
                    envelop.SetLineColor(ROOT.kGray+1)
                    envelop.SetLineWidth(2)
                    envelop.SetFillStyle(1001)
                    envelop.Draw("FL")
                    envelop.Draw()
                    rootObj.append(envelop)
                    
                    for uncertainty in uncertainties:
                        sumPerCharge[uncertainty][compName].Draw("HISTESame")
                
                for i in range(6):
                    cv.cd(i+1)
                    ROOT.gPad.RedrawAxis()
                
                cv.Update()
                cv.Print(os.path.join(outputFolder,"shapes_"+str(binName)+"_"+obsName+"_"+name+"_"+channel+".pdf"))
                cv.Print(os.path.join(outputFolder,"shapes_"+str(binName)+"_"+obsName+"_"+name+"_"+channel+".png"))
                    
        
