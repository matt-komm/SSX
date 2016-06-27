### Skeleton for topBMatcher.py
# created by VISPA
# Thu Jul 16 16:52:07 2015
# -*- coding: utf-8 -*-

from pxl import core, modules

import math
import ROOT
import random

ROOT.gROOT.SetBatch(True)
ROOT.gStyle.SetOptStat(0)
ROOT.gStyle.SetTitleSize(0.052,"XYZ")
ROOT.gStyle.SetLabelSize(0.04,"XYZ")
ROOT.gStyle.SetTitleOffset(1.1,"Y")
ROOT.gStyle.SetPadBottomMargin(0.11)
ROOT.gStyle.SetPadLeftMargin(0.12)
ROOT.gStyle.SetPadTickX(1)  # To get tick marks on the opposite side of the frame
ROOT.gStyle.SetPadTickY(1)

ROOT.gStyle.SetPadGridX(True)
ROOT.gStyle.SetPadGridY(True)
ROOT.gStyle.SetGridColor(ROOT.kBlack)
ROOT.gStyle.SetGridStyle(2)
ROOT.gStyle.SetGridWidth(1)

ROOT.gStyle.SetPadTopMargin(0.07)
ROOT.gStyle.SetPadRightMargin(0.03)

class Example(modules.PythonModule):

    def __init__(self):
        ''' Initialize private variables '''
        modules.PythonModule.__init__(self)
        # self._exampleVariable = startValue

    def initialize(self, module):
        ''' Initialize module sinks, sources and options '''
        self.__module = module
        self._logger = core.Logger(self.__module.getName())

        module.addSink("in", "Input port")
        module.addSource("out", "Output port")
        
        module.addOption("eventview", "", "SingleTop")
        module.addOption("bjet", "", "BJet")

    def beginJob(self, parameters=None):
        ''' Executed before the first object comes in '''
        self._logger.log(core.LOG_LEVEL_INFO, "Begin job")
        self._eventViewName=self.__module.getOption("eventview")
        self._bjetName=self.__module.getOption("bjet")
        
        self._nAll={}
        self._nMatch={}

        for ijet in range(2,4):
            self._nAll[ijet]={}
            self._nMatch[ijet]={}
            for bjet in range(0,3):
                eta=3.0
                if bjet==0:
                    eta=5.0
                self._nAll[ijet][bjet]={"n":0, "pt":ROOT.TH1F("allpt_"+str(ijet)+"_"+str(bjet),";b-jet pT / GeV;efficiency (#Delta R<0.3)",30,0,350), "eta":ROOT.TH1F("alleta_"+str(ijet)+"_"+str(bjet),";b-jet |#eta|;efficiency (#Delta R<0.3)",30,0,eta)}
                self._nAll[ijet][bjet]["pt"].Sumw2()
                self._nAll[ijet][bjet]["eta"].Sumw2()
                self._nMatch[ijet][bjet]={"n":0, "pt":ROOT.TH1F("matchpt_"+str(ijet)+"_"+str(bjet),";b-jet pT / GeV;efficiency (#Delta R<0.3)",30,0,350), "eta":ROOT.TH1F("matcheta_"+str(ijet)+"_"+str(bjet),";b-jet |#eta|;efficiency (#Delta R<0.3)",30,0,eta)}
                self._nMatch[ijet][bjet]["pt"].Sumw2()
                self._nMatch[ijet][bjet]["eta"].Sumw2()
    def beginRun(self):
        ''' Executed before each run '''
        pass

    def process(self, object):
        ''' Executed on every object '''
        event = core.toEvent(object)
        recoB=None
        genB=None
        
        njets=0
        nbjets=0
        for eventView in event.getEventViews():
            if eventView.getName()==self._eventViewName:
                for particle in eventView.getParticles():
                    if particle.getName()==self._bjetName:
                        recoB=particle

            if eventView.getName()=="Reconstructed":
                njets=eventView.getUserRecord("nSelectedJet")
                nbjets=eventView.getUserRecord("nSelectedBJet")
                
            if eventView.getName()=="Generated":
                for particle in eventView.getParticles():
                    if math.fabs(particle.getPdgNumber())==5:
                        top = particle.getMother()
                        if math.fabs(top.getPdgNumber())==6:
                            genB=particle
                            
        
        if recoB and genB:
            self._nAll[njets][nbjets]["n"]+=1
            self._nAll[njets][nbjets]["pt"].Fill(recoB.getPt())
            self._nAll[njets][nbjets]["eta"].Fill(recoB.getEta())
            dR=recoB.getVector().deltaR(genB.getVector())
            if dR<0.3:
                self._nMatch[njets][nbjets]["n"]+=1
                self._nMatch[njets][nbjets]["pt"].Fill(recoB.getPt())
                self._nMatch[njets][nbjets]["eta"].Fill(recoB.getEta())
                
        # return the name of the source
        return "out"

    def endRun(self):
        ''' Executed after each run '''
        pass

    def endJob(self):
        ''' Executed after the last object '''
        self._logger.log(core.LOG_LEVEL_INFO, "End job")
        


        
        for ijet in range(2,4):
            for bjet in range(0,3):
                print ijet,"jets, ",bjet,"bjets"
                print "\tall: ",self._nAll[ijet][bjet]["n"]
                print "\tmatched: ",self._nMatch[ijet][bjet]["n"]
                
                cv = ROOT.TCanvas("cv"+str(random.random()),"",800,600)
                
                self._nMatch[ijet][bjet]["pt"].Divide(self._nAll[ijet][bjet]["pt"])
                self._nMatch[ijet][bjet]["pt"].SetMarkerStyle(20)
                self._nMatch[ijet][bjet]["pt"].SetMarkerSize(1.2)
                self._nMatch[ijet][bjet]["pt"].GetYaxis().SetRangeUser(0,1.1)
                self._nMatch[ijet][bjet]["pt"].Draw("PE")
                
                pText=ROOT.TPaveText(0.6,0.935,0.97,0.99,"NDC")
                pText.SetTextFont(42)
                pText.SetFillColor(0)
                pText.AddText(str(ijet)+" jet, "+str(bjet)+" b-tag")
                pText.Draw("Same")
                
                pTextEff=ROOT.TPaveText(0.13,0.935,0.5,0.99,"NDC")
                pTextEff.SetTextFont(42)
                pTextEff.SetFillColor(0)
                effText = "<efficiency>=%3.1f%%" % (100.0*self._nMatch[ijet][bjet]["n"]/self._nAll[ijet][bjet]["n"])
                pTextEff.AddText(effText)
                pTextEff.Draw("Same")
                cv.Update()
                cv.Print("matching_topdecay_"+str(ijet)+"j"+str(bjet)+"t_pt.pdf")
                
                
                cv = ROOT.TCanvas("cv"+str(random.random()),"",800,600)
                self._nMatch[ijet][bjet]["eta"].Divide(self._nAll[ijet][bjet]["eta"])
                self._nMatch[ijet][bjet]["eta"].SetMarkerStyle(20)
                self._nMatch[ijet][bjet]["eta"].SetMarkerSize(1.2)
                self._nMatch[ijet][bjet]["eta"].GetYaxis().SetRangeUser(0,1.1)
                self._nMatch[ijet][bjet]["eta"].Draw("PE")
                
                pText=ROOT.TPaveText(0.6,0.935,0.97,0.99,"NDC")
                pText.SetTextFont(42)
                pText.SetFillColor(0)
                pText.AddText(str(ijet)+" jet, "+str(bjet)+" b-tag")
                pText.Draw("Same")
                
                
                pTextEff=ROOT.TPaveText(0.13,0.935,0.5,0.99,"NDC")
                pTextEff.SetTextFont(42)
                pTextEff.SetFillColor(0)
                effText = "<efficiency>=%3.1f%%" % (100.0*self._nMatch[ijet][bjet]["n"]/self._nAll[ijet][bjet]["n"])
                pTextEff.AddText(effText)
                pTextEff.Draw("Same")
                cv.Update()
                cv.Print("matching_topdecay_"+str(ijet)+"j"+str(bjet)+"t_eta.pdf")
                
                #cv.WaitPrimitive()
                
