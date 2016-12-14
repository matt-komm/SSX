### Skeleton for countEventWeight.py
# created by VISPA
# Sun Jul 19 21:55:29 2015
# -*- coding: utf-8 -*-

from pxl import core, modules
import random
#import numpy
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
        module.addOption("output", "", "eff.root",modules.OptionDescription.USAGE_FILE_SAVE)
        
        self.workingpoints = {
            "loose": {
                "value": -0.715,
            },
            "medium": {
                "value": 0.185,
            },
            "tight": {
                "value": 0.875
            }
        }
        
        self.flavors = [
            "b",
            "c",
            "other"
        ]
        
        self.sampleHist = ROOT.TH2F("sampleHist"+str(random.random()),"",100,-5,5,300,0,600)
        self.sampleHist.SetDirectory(0)

    def beginJob(self, parameters=None):
        ''' Executed before the first object comes in '''
        self._logger.log(core.LOG_LEVEL_INFO, "Begin job")
        self._outputFile=self.__module.getOption("output")

        for wp in self.workingpoints.keys():
            for flavor in self.flavors:
                self.workingpoints[wp][flavor]={}

    def beginRun(self):
        ''' Executed before each run '''
        pass

    def process(self, object, sink):
        ''' Executed on every object '''
        event = core.toEvent(object)
        if not event:
            return "out"
        process = event.getUserRecord("ProcessName")
        weight=1.0
        for eventView in event.getEventViews():
            if eventView.getName()=="Generated":
                weight=eventView.getUserRecord("genweight")
            if eventView.getName()=="Reconstructed":
                for particle in eventView.getParticles():
                    if (particle.getName()=="SelectedJet") or (particle.getName()=="SelectedBJet"):
                        flavor="other"
                        if particle.hasUserRecord("partonFlavour"):
                            pdgId = particle.getUserRecord("partonFlavour")
                            if math.fabs(pdgId)==5:
                                flavor="b"
                            elif math.fabs(pdgId)==4:
                                flavor="c"
                        csvValue = particle.getUserRecord("pfCombinedMVAV2BJetTags")
                        
                        for wp in self.workingpoints.keys():
                            if not self.workingpoints[wp][flavor].has_key(process):
                                self.workingpoints[wp][flavor][process]={}
                                trueHist = self.sampleHist.Clone()
                                trueHist.SetDirectory(0)
                                trueHist.SetName("true__"+flavor+"__"+wp+"__"+process)
                                self.workingpoints[wp][flavor][process]["true"]=trueHist
                                taggedHist = self.sampleHist.Clone()
                                taggedHist.SetDirectory(0)
                                taggedHist.SetName("tagged__"+flavor+"__"+wp+"__"+process)
                                self.workingpoints[wp][flavor][process]["tagged"]=taggedHist
                                    
                            self.workingpoints[wp][flavor][process]["true"].Fill(particle.getEta(),particle.getPt())
                            if self.workingpoints[wp]["value"]<csvValue:
                                self.workingpoints[wp][flavor][process]["tagged"].Fill(particle.getEta(),particle.getPt())
                            
        
        

        # return the name of the source
        return "out"

    def endRun(self):
        ''' Executed after each run '''
        pass

    def endJob(self):
        ''' Executed after the last object '''
        self._logger.log(core.LOG_LEVEL_INFO, "End job")
        f = ROOT.TFile(self._outputFile,"RECREATE")
        for wp in self.workingpoints.keys():  
            for flavor in self.flavors:
                for process in self.workingpoints[wp][flavor].keys():
                    self.workingpoints[wp][flavor][process]["true"].SetDirectory(f)
                    self.workingpoints[wp][flavor][process]["true"].Write()
                    self.workingpoints[wp][flavor][process]["tagged"].SetDirectory(f)
                    self.workingpoints[wp][flavor][process]["tagged"].Write()
        f.Close()
        
        
