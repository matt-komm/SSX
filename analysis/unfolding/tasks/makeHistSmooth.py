from defaultModules.Module import Module

import logging
import ROOT
import copy
import math
import os
import sys
import random
from ModelClasses import *

class SmoothHistograms(Module.getClass("Program")):
    def __init__(self,options=[]):
        Module.__init__(self,options)
        self._logger = logging.getLogger(__file__)
        self._logger.setLevel(logging.DEBUG)
        
    def smoothFFTPerRange(self,hist,start,end):
        arr = numpy.zeros((end-start)+1,dtype=numpy.complex64)
        for ibin in range(end-start+1):
            arr[ibin]=hist.GetBinContent(start+ibin+1)
        print arr
        smooth = numpy.fft.fft(arr)
        smooth[-1]*=0.8
        arr = numpy.fft.ifft(smooth)
        print arr
        for ibin in range(end-start+1):
            hist.SetBinContent(start+ibin+1,numpy.real(arr[ibin]))
            
    def smoothAvgPerRange(self,hist,start,end,w=0.2):
        arr = numpy.zeros((end-start+1))
        
        for ibin in range(1,end-start):
            c1 = hist.GetBinContent(start+ibin+1-1)
            c2 = hist.GetBinContent(start+ibin+1+0)
            c3 = hist.GetBinContent(start+ibin+1+1)
            
            e1 = hist.GetBinError(start+ibin+1-1)
            e2 = hist.GetBinError(start+ibin+1+0)
            e3 = hist.GetBinError(start+ibin+1+1)
            
            arr[ibin]=(w*c1/e1+(1-2*w)*c2/e2+w*c3/e3)/(w/e1+(1-2*w)/e2+w/e3)
        
        arr[0]=((1-w)*hist.GetBinContent(start+1)/hist.GetBinError(start+1)+\
                w*hist.GetBinContent(start+2)/hist.GetBinError(start+2))/\
                ((1-w)/hist.GetBinError(start+1)+w/hist.GetBinError(start+2))
        arr[-1]=((1-w)*hist.GetBinContent(end+1)/hist.GetBinError(end+1)+\
                w*hist.GetBinContent(end)/hist.GetBinError(end))/\
                ((1-w)/hist.GetBinError(end+1)+w/hist.GetBinError(end))

        for ibin in range(end-start+1):
            hist.SetBinContent(start+ibin+1,arr[ibin])
            
    def smooth(self,hist,region,w=0.1,i=10):
        #0..3 //mtsmoothAvgPerRangew
        #4..11 //BDT ttw
        #12..15 //BDT tch
        for _ in range(i):
            if region=="2j1t":
                for r in [
                    [0,3],
                    [4,11],
                    [12,15]
                ]:
                    self.smoothAvgPerRange(hist,16+r[0],16+r[1],w)
                    self.smoothAvgPerRange(hist,15-r[1],15-r[0],w)
            elif region=="3j2t":
                self.smoothAvgPerRange(hist,0,4,w)
                self.smoothAvgPerRange(hist,5,9,w)
            
    def execute(self):
        #mu,ele,comb
        channel = self.getOption("channel")
        channelName = self.module("Samples").getChannelName([channel])
        self._logger.info("make fit for: "+str(channel))
        # channel,sysName,binList,[up,down]
        histogramsPerChannelAndUncertainty = {}
        
        unfoldingName = self.module("Unfolding").getUnfoldingName()
        systematics = self.getOption("systematics").split(",") if len(self.getOption("systematics"))>0 else []
        self._logger.info("systematics: "+str(systematics))
        
        
        #maps channel bins to global bins for combinations
        if unfoldingName!="inc":
            binMap = self.module("Unfolding").buildGlobalRecoBinMap()
            
        histogramsPerChannelAndUncertainty={}
        histogramsPerChannelAndUncertainty["nominal"]={}
        if unfoldingName=="inc":
            histogramsPerChannelAndUncertainty["nominal"]["binInc"] = \
                self.module("ThetaModel").getHistsFromFiles(channel,unfoldingName,-1,"nominal")
            
        else:
            nbins = len(self.module("Unfolding").getRecoBinning(channel))-1

            for ibin in range(nbins):
                histogramsPerChannelAndUncertainty["nominal"]["bin"+str(1+binMap[channel][ibin])] = \
                    self.module("ThetaModel").getHistsFromFiles(channel,unfoldingName,ibin,"nominal")
                
        for sysName in systematics:
            histogramsPerChannelAndUncertainty[sysName]={}
            if unfoldingName=="inc":
                histogramsPerChannelAndUncertainty[sysName]["binInc"] = [
                    self.module("ThetaModel").getHistsFromFiles(channel,unfoldingName,-1,sysName+"Up"),
                    self.module("ThetaModel").getHistsFromFiles(channel,unfoldingName,-1,sysName+"Down")
                ]
            else:
                nbins = len(self.module("Unfolding").getRecoBinning(channel))-1
                for ibin in range(nbins):
                    histogramsPerChannelAndUncertainty[sysName]["bin"+str(1+binMap[channel][ibin])] = [
                        self.module("ThetaModel").getHistsFromFiles(channel,unfoldingName,ibin,sysName+"Up"),
                        self.module("ThetaModel").getHistsFromFiles(channel,unfoldingName,ibin,sysName+"Down")
                    ]
                    

        for binName in sorted(histogramsPerChannelAndUncertainty["nominal"].keys()):
            for obsName in sorted(histogramsPerChannelAndUncertainty["nominal"][binName].keys()):
                for compName in sorted(histogramsPerChannelAndUncertainty["nominal"][binName][obsName].keys()):
                    if compName=="data":
                        continue
                    histNominal = histogramsPerChannelAndUncertainty["nominal"][binName][obsName][compName]["hist"]
                    #histNominalSmooth = histNominal.Clone(histNominal.GetName()+binName+obsName+compName+sysName+"smooth"+str(random.random()))
                    #for ibin in range(histNominal.GetNbinsX()+2):
                    #    histNominalSmooth.SetBinError(ibin,1.)
                    #self.smooth(histNominalSmooth,region=obsName,w=0.05)
                    
                    for sysName in systematics:
                        histUp = histogramsPerChannelAndUncertainty[sysName][binName][0][obsName][compName]["hist"]
                        histDown = histogramsPerChannelAndUncertainty[sysName][binName][1][obsName][compName]["hist"]
                        
                        histUp.SetLineColor(ROOT.kOrange+7)
                        histDown.SetLineColor(ROOT.kAzure+4)
                        
                        histRelUp = histUp.Clone(histUp.GetName()+binName+obsName+compName+sysName+"rel"+str(random.random()))
                        histRelDown = histDown.Clone(histDown.GetName()+binName+obsName+compName+sysName+"rel"+str(random.random()))
                        
                        histUpSmooth = histUp.Clone(histUp.GetName()+binName+obsName+compName+sysName+"smooth"+str(random.random()))
                        histDownSmooth = histDown.Clone(histDown.GetName()+binName+obsName+compName+sysName+"smooth"+str(random.random()))
                       

                        for ibin in range(histNominal.GetNbinsX()+2):
                            cNom = histNominal.GetBinContent(ibin)
                            eNom = histNominal.GetBinError(ibin)
                            cUp = histUp.GetBinContent(ibin)
                            eUp = histUp.GetBinError(ibin)
                            cDown = histDown.GetBinContent(ibin)
                            eDown = histDown.GetBinError(ibin)
                            
                            
                            
                            if eUp<0.00001:
                                eUp=1
                            if eDown<0.00001:
                                eDown=1
                            if cNom<0.001:
                                cNom = 0.001
                                
                            sigUp = math.fabs(cUp-cNom)/eUp
                            sigDown = math.fabs(cUp-cDown)/eDown
                                
                            if sigUp<1:
                                cUp = cNom
                                if sigDown>1 and cDown/cNom<1:
                                    cUp = cNom+math.fabs(cDown-cNom)
                                if sigDown>1 and cDown/cNom>1:
                                    cUp = cNom-math.fabs(cDown-cNom)
                            
<<<<<<< Updated upstream
                            if sigDown<1:
                                cDown = cNom
                                if sigUp>1 and cUp/cNom<1:
                                    cDown = cNom+math.fabs(cUp-cNom)
                                if sigUp>1 and cUp/cNom>1:
                                    cDown = cNom-math.fabs(cUp-cNom)
                                
                                
                            #if math.fabs(sigUp-sigDown)>5:
                                
                            
                            if cNom>0.1:
                                histRelUp.SetBinContent(ibin,cUp/cNom)
                                histRelDown.SetBinContent(ibin,cDown/cNom)
                                
                                histRelUp.SetBinError(ibin,eUp/cNom)
                                histRelDown.SetBinError(ibin,eDown/cNom)
                            else:
                                histRelUp.SetBinContent(ibin,1.)
                                histRelDown.SetBinContent(ibin,1.)
                                #use large error of 100% here
                                histRelUp.SetBinError(ibin,1.)
                                histRelDown.SetBinError(ibin,1.)
                                
                        self._logger.info("Compatible up bins: "+sysName+" "+compName+" "+str(compatibleBinsUp)+"/"+str(histNominal.GetNbinsX()+2))
                        self._logger.info("Compatible down bins: "+sysName+" "+compName+" "+str(compatibleBinsDown)+"/"+str(histNominal.GetNbinsX()+2))
                                   
                        histRelUpSmooth = histRelUp.Clone(histRelUp.GetName()+str(random.random()))
                        histRelDownSmooth = histRelDown.Clone(histRelDown.GetName()+str(random.random()))
                        #self.smooth(histRelUpSmooth,region=obsName)
                        #self.smooth(histRelDownSmooth,region=obsName)
                        
                        for ibin in range(histNominal.GetNbinsX()):
                            cNom = histNominal.GetBinContent(ibin+1)
                            if (compatibleBinsUp>0.8*(histNominal.GetNbinsX()+2) and compatibleBinsDown>0.8*(histNominal.GetNbinsX()+2)):
                                histUpSmooth.SetBinContent(ibin+1,
                                    cNom
                                )
                                histDownSmooth.SetBinContent(ibin+1,
                                    cNom
                                )
                            
                            else:
                                if cNom!=0:
                                    histUpSmooth.SetBinContent(ibin+1,
                                        histRelUpSmooth.GetBinContent(ibin+1)*cNom
                                    )
                                    histDownSmooth.SetBinContent(ibin+1,
                                        histRelDownSmooth.GetBinContent(ibin+1)*cNom
                                    )
                            
                        histogramsPerChannelAndUncertainty[sysName][binName][0][obsName][compName]["histSmooth"] = histUpSmooth
                        histogramsPerChannelAndUncertainty[sysName][binName][1][obsName][compName]["histSmooth"] = histDownSmooth
                       
                        '''
                        cv = ROOT.TCanvas("cv"+binName+obsName+compName+str(random.random()),"",800,600)
                        ymax = max(map(lambda x: x.GetMaximum(),[histNominal,histUp,histDown]))
                        axis = ROOT.TH2F("axis"+binName+obsName+compName+str(random.random()),"",
                            50,histNominal.GetXaxis().GetBinLowEdge(1),histNominal.GetXaxis().GetBinUpEdge(histNominal.GetNbinsX()),
                            50,0.8,1.2*ymax
                        )
                        axis.Draw("AXIS")
                        histNominal.Draw("PESame")
                        #histNominalSmooth.SetLineStyle(2)
                        #histNominalSmooth.Draw("HISTSAME")
                        histUp.Draw("HISTSame")
                        histDown.Draw("HISTSame")
                        
                        histUpSmooth.SetLineStyle(2)
                        histUpSmooth.SetLineWidth(2)
                        histUpSmooth.Draw("HISTSame")
                        
                        histDownSmooth.SetLineWidth(2)
                        histDownSmooth.SetLineStyle(2)
                        histDownSmooth.Draw("HISTSame")
                        
                        cv.Update()
                        cv.Print(obsName+"_"+compName+"_"+binName+"_"+sysName+".png")
                        '''
        
        for sysName in systematics:
            for i,d in enumerate(["Up","Down"]):
                if unfoldingName=="inc":
                    outputFile = self.module("ThetaModel").getHistogramFile(
                        channel,
                        unfoldingName,
                        unfoldingBin=-1,
                        uncertainty=sysName+d,
                        smooth=True
                    )
                    rootFileOutput = ROOT.TFile(
                        outputFile,"RECREATE"
                    )
                    hists = histogramsPerChannelAndUncertainty[sysName]["binInc"][i]
                    for obsName in sorted(hists.keys()):
                        for compName in sorted(hists[obsName].keys()):
                            if compName=="data":
                                hists[obsName][compName]["hist"].SetName(hists[obsName][compName]["name"])
                                hists[obsName][compName]["hist"].SetDirectory(rootFileOutput)
                                hists[obsName][compName]["hist"].Write()
                            else:
                                hists[obsName][compName]["histSmooth"].SetName(hists[obsName][compName]["name"])
                                hists[obsName][compName]["histSmooth"].SetDirectory(rootFileOutput)
                                hists[obsName][compName]["histSmooth"].Write()
                    rootFileOutput.Close()
                    self._logger.info("Write: "+outputFile)
                    
                else:
                    nbins = len(self.module("Unfolding").getRecoBinning(channel))-1

                    for ibin in range(nbins):
                        hists = histogramsPerChannelAndUncertainty["nominal"]["bin"+str(1+binMap[channel][ibin])]
                        binName = "bin"+str(1+binMap[channel][ibin])
                        outputFile = self.module("ThetaModel").getHistogramFile(
                            channel,
                            unfoldingName,
                            unfoldingBin=ibin,
                            uncertainty=sysName+d,
                            smooth=True
                        )
                        rootFileOutput = ROOT.TFile(
                            outputFile,"RECREATE"
                        )
                        hists = histogramsPerChannelAndUncertainty[sysName][binName][i]
                        for obsName in sorted(hists.keys()):
                            for compName in sorted(hists[obsName].keys()):
                                if compName=="data":
                                    hists[obsName][compName]["hist"].SetName(hists[obsName][compName]["name"])
                                    hists[obsName][compName]["hist"].SetDirectory(rootFileOutput)
                                    hists[obsName][compName]["hist"].Write()
                                else:
                                    hists[obsName][compName]["histSmooth"].SetName(hists[obsName][compName]["name"])
                                    hists[obsName][compName]["histSmooth"].SetDirectory(rootFileOutput)
                                    hists[obsName][compName]["histSmooth"].Write()
                        rootFileOutput.Close()
                        self._logger.info("Write: "+outputFile)
            
