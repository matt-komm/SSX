### Skeleton for neutrinoMatcher.py
# created by VISPA
# Thu Jul 16 14:27:06 2015
# -*- coding: utf-8 -*-

from pxl import core, modules
import math
import ROOT


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
        module.addOption("neutrino", "", "Neutrino")

    def beginJob(self, parameters=None):
        ''' Executed before the first object comes in '''
        self._logger.log(core.LOG_LEVEL_INFO, "Begin job")
        
        self._eventViewName=self.__module.getOption("eventview")
        self._neutrinoName=self.__module.getOption("neutrino")
        
        self._nAll=0
        self._nMatch=0
        self._nReal=0
        self._nPminBest=0
        
        self._hDZ_min=ROOT.TH1F("hDZ_min",";#Delta p_z;",100,0,300)
        self._hDZ_alt=ROOT.TH1F("hDZ_alt",";#Delta p_z;",100,0,300)
        self._hDZ_best=ROOT.TH1F("hDZ_best",";#Delta p_z;",100,0,300)
        

    def beginRun(self):
        ''' Executed before each run '''
        pass

    def process(self, object, sink):
        ''' Executed on every object '''
        event = core.toEvent(object)
        if not event:
            # add handling inconvertible objects here
            return
            
        recoNeutrino=None
        genNeutrino=None
        self._nAll+=1
        for eventView in event.getEventViews():
            if eventView.getName()==self._eventViewName:
                for particle in eventView.getParticles():
                    if particle.getName()==self._neutrinoName:
                        recoNeutrino=particle
            if eventView.getName()=="Generated":
                for particle in eventView.getParticles():
                    if math.fabs(particle.getPdgNumber())==14:
                        wboson = particle.getMother()
                        top = wboson.getMother()
                        if math.fabs(wboson.getPdgNumber())==24 and math.fabs(top.getPdgNumber())==6:
                            genNeutrino=particle
        if recoNeutrino and genNeutrino:
            self._nMatch+=1
            if recoNeutrino.getUserRecord("realsolution"):
                self._nReal+=1
                pzgen = genNeutrino.getPz()
                pz1 = recoNeutrino.getPz()
                pz2 = recoNeutrino.getUserRecord("altSolution")
                self._hDZ_min.Fill(math.fabs(pz1-pzgen))
                self._hDZ_alt.Fill(math.fabs(pz2-pzgen))
                
                
                if math.fabs(pz1-pzgen)<math.fabs(pz2-pzgen):
                    self._nPminBest+=1
                
                    self._hDZ_best.Fill(math.fabs(pz1-pzgen))
                else:
                    self._hDZ_best.Fill(math.fabs(pz2-pzgen))
                            

        # return the name of the source
        return "out"

    def endRun(self):
        ''' Executed after each run '''
        pass

    def endJob(self):
        ''' Executed after the last object '''
        self._logger.log(core.LOG_LEVEL_INFO, "End job")
        
        print "all events: ",self._nAll
        print "matchable neutrino: ",self._nMatch
        print "real solutions: ",self._nReal
        print "min=best solution: ",self._nPminBest
        
        ROOT.gStyle.SetOptStat(0)
        ROOT.gStyle.SetTitleSize(0.05,"XYZ")
        ROOT.gStyle.SetLabelSize(0.038,"XYZ")
        ROOT.gStyle.SetTitleOffset(1.5,"Y")
        ROOT.gStyle.SetPadBottomMargin(0.115)
        ROOT.gStyle.SetPadLeftMargin(0.135)
        
        ROOT.gStyle.SetPadTopMargin(0.03)
        ROOT.gStyle.SetPadRightMargin(0.03)
        
        legend=ROOT.TLegend(0.75,0.92,0.92,0.7)
        legend.SetBorderSize(0)
        legend.SetTextFont(42)
        cv = ROOT.TCanvas("cv","",800,600)
        
        axis=ROOT.TH2F("axis",";#Delta p_{Z} (reco,gen);events",50,0,300,50,0,self._hDZ_best.GetMaximum()*1.1)
        axis.Draw("AXIS")
        
        self._hDZ_min.SetLineColor(ROOT.kGray)
        self._hDZ_min.SetFillColor(ROOT.kGray)
        self._hDZ_min.Draw("Same")
        legend.AddEntry(self._hDZ_min,"min |p_{Z}|","F")
        
        self._hDZ_alt.SetLineColor(ROOT.kBlue)
        self._hDZ_alt.SetLineWidth(3)
        self._hDZ_alt.SetLineStyle(2)
        self._hDZ_alt.Draw("Same")
        legend.AddEntry(self._hDZ_alt,"max |p_{Z}|","L")
        
        self._hDZ_best.SetLineColor(ROOT.kBlack)
        self._hDZ_best.SetLineWidth(2)
        self._hDZ_best.Draw("Same")
        legend.AddEntry(self._hDZ_best,"min #Delta p_{Z}","L")
        
        legend.Draw("Same")
        axis.Draw("GAXIS Same")
        
        cv.Update()
        cv.WaitPrimitive()
        
        
