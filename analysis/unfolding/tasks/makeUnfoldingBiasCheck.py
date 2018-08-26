from defaultModules.Module import Module

import logging
import ROOT
import copy
import os
import sys
import random
from ModelClasses import *

class RunUnfolding(Module.getClass("Program")):
    def __init__(self,options=[]):
        Module.__init__(self,options)
        self._logger = logging.getLogger(__file__)
        self._logger.setLevel(logging.DEBUG)
        
    def reweightRepsonse(self,hist,slope=0.):
        xmin = hist.GetXaxis().GetXmin()
        xmax = hist.GetXaxis().GetXmax()
        middle = 0.5*(xmin+xmax)
        for ibin in range(hist.GetXaxis().GetNbins()+2):
            for jbin in range(hist.GetYaxis().GetNbins()+2):
                c = hist.GetBinContent(ibin,jbin)
                e = hist.GetBinError(ibin,jbin)
                p = hist.GetXaxis().GetBinCenter(ibin)
                
                w = (2.*(p-middle)/(xmax-xmin))*slope+1.
                hist.SetBinContent(ibin,jbin,c*w)
                hist.SetBinError(ibin,jbin,e*w)
        
    def execute(self):
        #mu,ele
        channels = self.getOption("channels").split(",")
        channelName = self.module("Samples").getChannelName(channels)
        #inc,pt,y,cos
        unfoldingName = self.module("Unfolding").getUnfoldingName()
        fitName = self.module("Unfolding").getFitName()
        if unfoldingName=="inc":
            self._logger.critical("Cannot unfolding inclusive xsec")
            sys.exit(1)
        unfoldingLevel = self.module("Unfolding").getUnfoldingLevel()
        
        
        self.module("Utils").createFolder("unfolding/"+unfoldingName+"/"+unfoldingLevel+"/biascheck")
        outputFolder = self.module("Utils").getOutputFolder("unfolding/"+unfoldingName+"/"+unfoldingLevel+"/biascheck")


        responseMatricesPerChannel = self.module("Response").gatherResponse(
            unfoldingName,
            unfoldingLevel,
            channels,
            uncertainties=[]
        )
        
        if len(channels)==2:
            responseMatricesPerChannel = self.module("Response").combineResponseMatrices(
                responseMatricesPerChannel
            )
        
        #use either per channel or their combination - no need to keep the rest
        responseMatrices = responseMatricesPerChannel[channelName]
        
        
        recoBinning = self.module("Unfolding").getRecoBinning(channelName)
        genBinning = self.module("Unfolding").getGenBinning(channelName)
        binMapReco = self.module("Unfolding").buildGlobalRecoBinMap()[channelName]
        binMapGen = self.module("Unfolding").buildGlobalGenBinMap()[channelName]
        
        responseMatrixNominal = responseMatrices[-1]["nominal"].Clone(responseMatrices[-1]["nominal"].GetName()+"sum")
        responseMatrixNominal.Add(responseMatrices[1]["nominal"])
        
        nominalGenHist = responseMatrixNominal.ProjectionX(responseMatrixNominal.GetName()+"gen"+str(random.random()))

        slopes = numpy.linspace(-0.2,0.2,num=21)
        unfoldedValues = numpy.zeros((nominalGenHist.GetNbinsX(),len(slopes)))
        expectedValues = numpy.zeros((nominalGenHist.GetNbinsX(),len(slopes)))

        for islope,slope in enumerate(slopes):
            reweightedRecoPerCharge = {}
            reweightedGenPerCharge = {}
            
            for charge in [-1,1]:
                reweightedRepsonse = responseMatrices[charge]["nominal"].Clone("reweighed"+str(charge)+str(random.random())+str(slope))
                self.reweightRepsonse(reweightedRepsonse,slope)
                #reweightedRepsonse.Scale(0.5)
                reweightedRecoPerCharge[charge] = reweightedRepsonse.ProjectionY()
                reweightedGenPerCharge[charge] = reweightedRepsonse.ProjectionX()
                
            reweightedReco = reweightedRecoPerCharge[-1].Clone(reweightedRecoPerCharge[-1].GetName()+"sum")
            reweightedReco.Add(reweightedRecoPerCharge[1])
            
            reweightedGen = reweightedGenPerCharge[-1].Clone(reweightedGenPerCharge[-1].GetName()+"sum")
            reweightedGen.Add(reweightedGenPerCharge[1])
                
            reweightedRecoCovariance = ROOT.TH2F(
                "cov"+str(charge)+str(slope)+str(random.random()),"",
                len(recoBinning)-1,recoBinning,len(recoBinning)-1,recoBinning
            )
                
            reweightedRecoCovariance.SetDirectory(0)
            for ibin in range(reweightedRecoCovariance.GetNbinsX()):
                c = reweightedReco.GetBinContent(ibin+1)
                reweightedRecoCovariance.SetBinContent(ibin+1,ibin+1,c)
            
            unfoldedHistReweighted,unfoldedCovarianceReweighted,bestTau = self.module("Unfolding").unfold(
                responseMatrixNominal,
                reweightedReco,
                #regularize only between the two merged histograms
                regularizations=range(1,len(genBinning)-2),
                dataCovariance=reweightedRecoCovariance,
                scanOutput=None,#os.path.join(outputFolder,self.module("Samples").getChannelName(channels)+"_comb_tauScan"),
                fixedTau=1e-10 if (unfoldingName=="lpt" or unfoldingName=="leta") else None
            )
            
            for ibin in range(unfoldedHistReweighted.GetNbinsX()):
                unfolded = unfoldedHistReweighted.GetBinContent(ibin+1)
                expected = reweightedGen.GetBinContent(ibin+1)
                unfoldedValues[ibin][islope]=unfolded
                expectedValues[ibin][islope]=expected
            '''
            self.module("Drawing").plotDataHistogram([reweightedGen,nominalGenHist],unfoldedHistReweighted,
                os.path.join(outputFolder,self.module("Samples").getChannelName(channels)+"_unfoldedHist_biascheck%.2f"%slope),
                xaxis="unfolded "+self.module("Unfolding").getUnfoldingVariableName(),
                title=self.module("Samples").getPlotTitle(channels)+"#kern[-0.5]{ }+#kern[-0.5]{ }jets"
            )
            '''
        cv = ROOT.TCanvas("cvbias"+str(random.random()),"",800,650)
        cv.SetLeftMargin(0.14)
        cv.SetBottomMargin(0.13)
        cv.SetRightMargin(0.18)
        axixBias = ROOT.TH2F(
            "axisbias",";Slope reco level (%); (unfolded-exp.)/exp. (%)",
            50,slopes[0]*100,slopes[-1]*100,
            50,min(numpy.min(unfoldedValues/expectedValues-1)*100,-0.1),max(numpy.max(unfoldedValues/expectedValues-1)*100,0.1)
        )
        axixBias.Draw("AXIS")
        
        legend = ROOT.TLegend(1-cv.GetRightMargin()+0.01,1-cv.GetTopMargin(),0.999,1-cv.GetTopMargin()-0.06*nominalGenHist.GetNbinsX())
        legend.SetBorderSize(0)
        legend.SetFillStyle(0)
        legend.SetTextFont(43)
        legend.SetTextSize(30)
        
        rootObj = []
        for ibin in range(nominalGenHist.GetNbinsX()):
            '''
            graphExpected = ROOT.TGraph(len(slopes),slopes,expectedValues[ibin])
            rootObj.append(graphExpected)
            graphExpected.SetLineWidth(2)
            graphExpected.SetLineStyle(1)
            graphExpected.SetLineColor(ROOT.kGray+1)
            graphExpected.Draw("L")
            
            graphUnfolded = ROOT.TGraph(len(slopes),slopes,unfoldedValues[ibin])
            rootObj.append(graphUnfolded)
            graphUnfolded.SetLineWidth(2)
            graphUnfolded.SetLineStyle(1)
            graphUnfolded.SetLineColor(ROOT.kRed+1)
            graphUnfolded.Draw("L")
            '''
            graphRatio = ROOT.TGraph(len(slopes),slopes*100,(unfoldedValues[ibin]/expectedValues[ibin]-1)*100)
            rootObj.append(graphRatio)
            graphRatio.SetLineWidth((nominalGenHist.GetNbinsX()-ibin)/2*2+1)
            graphRatio.SetLineStyle(1+ibin%3)
            graphRatio.SetLineColor(ROOT.kRed+ibin/2)
            graphRatio.SetMarkerColor(ROOT.kRed+ibin/2)
            graphRatio.SetMarkerStyle(20)
            graphRatio.SetMarkerSize(1.1)
            graphRatio.Draw("L")
            legend.AddEntry(graphRatio,"Bin %i"%(ibin+1),"L")
        
        legend.Draw("Same")
            
        cv.Update()
        cv.Print(os.path.join(outputFolder,self.module("Samples").getChannelName(channels)+"_bias.pdf"))
        cv.Print(os.path.join(outputFolder,self.module("Samples").getChannelName(channels)+"_bias.png"))
        
        
        
        
        
