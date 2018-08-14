from defaultModules.Module import Module

import logging
import ROOT
import os
import sys

# this generates the histograms (compound variable) for fitting

class GenHistograms(Module.getClass("Program")):
    def __init__(self,options=[]):
        Module.__init__(self,options)
        self._logger = logging.getLogger(__file__)
        self._logger.setLevel(logging.DEBUG)
        
    def execute(self):
        self.module("Samples").loadProcessFileDict(self.module("Utils").getOutputFolder("global/fileDictMu.json"),"mu")
        self.module("Samples").loadProcessFileDict(self.module("Utils").getOutputFolder("global/fileDictEle.json"),"ele")
    
        channel = self.getOption("channel")
        
        unfoldingName = self.module("Unfolding").getUnfoldingName()
        unfoldingLevel = self.module("Unfolding").getUnfoldingLevel()
        
        self._logger.info("Select channel: "+channel)
        self._logger.info("Unfolding name: "+unfoldingName)
        self._logger.info("Unfolding level: "+unfoldingLevel)
        
        outputFolder = self.module("Response").getOutputFolder(channel,unfoldingName,self.module("Utils").getUncertaintyName())
        self.module("Utils").createFolder(outputFolder)
        
        genMCFileName = os.path.join(outputFolder,"genpredictions_"+unfoldingLevel+".root")
        
        if os.path.exists(genMCFileName):
            self._logger.info("Output file '"+genMCFileName+"' already exists! -> skip")
            sys.exit(0)
            
        genBinning = self.module("Unfolding").getGenBinning(channel)
        self._logger.info("Gen binning: "+str(genBinning))
        
        genVariable = self.module("Unfolding").getGenVariable(channel)
        self._logger.info("Gen variable: "+genVariable)
        
        genSelectionPos = self.module("Unfolding").getGenCut(channel)+"*"+self.module("Samples").getGenChargeSelection(1)
        self._logger.info("Gen selection pos: "+genSelectionPos)
        
        genSelectionNeg = self.module("Unfolding").getGenCut(channel)+"*"+self.module("Samples").getGenChargeSelection(-1)
        self._logger.info("Gen selection neg: "+genSelectionNeg)
        
        genWeight = self.module("Unfolding").getGenWeight(channel)
        self._logger.info("Gen weight: "+genWeight)
        
        processSet = {
            #"ST_t-channel_4f_leptonDecays_13TeV-amcatnlo-herwigpp_TuneEE5C":[
            #    "ST_t-channel_4f_leptonDecays_13TeV-amcatnlo-herwigpp_TuneEE5C"
            #],
            "ST_t-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1":[
                "ST_t-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1"
            ],
            "ST_t-channel_5f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1_GEN_v180731":[
                "ST_t-channel_5f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1_GEN_v180731"
            ],
            #"ST_t-channel_4f_inclusiveDecays_13TeV-powhegV2-madspin-herwigpp":[
            #    "ST_t-channel_antitop_4f_inclusiveDecays_13TeV-powhegV2-madspin-herwigpp",
            #    "ST_t-channel_top_4f_inclusiveDecays_13TeV-powhegV2-madspin-herwigpp"
            #]
        }
        
        mcGenFiles = self.module("Files").getMCSignalGen(channel)
        
        histograms = []
        for setName,processes in processSet.iteritems():
            self._logger.info("Projecting: "+setName)
            genPredictionPos = ROOT.TH1F(
                setName+"_pos",
                ";"+self.module("Unfolding").getGenVariable(channel)+";",
                len(genBinning)-1,
                genBinning
            )
            genPredictionNeg = ROOT.TH1F(
                setName+"_neg",
                ";"+self.module("Unfolding").getGenVariable(channel)+";",
                len(genBinning)-1,
                genBinning
            )
            genPredictionPos.SetDirectory(0)
            histograms.append(genPredictionPos)
            genPredictionNeg.SetDirectory(0)
            histograms.append(genPredictionNeg)
           
            for fileName in mcGenFiles:
                for processName in processes:
                    self.module("Utils").getHist1D(genPredictionPos,fileName,processName,genVariable,
                        genWeight+"*"+genSelectionPos+"*(1./veto_frac)"
                    )
                    self.module("Utils").getHist1D(genPredictionNeg,fileName,processName,genVariable,
                        genWeight+"*"+genSelectionNeg+"*(1./veto_frac)"
                    )
                    
            genPredictionInc = genPredictionPos.Clone(setName)
            genPredictionInc.SetDirectory(0)
            histograms.append(genPredictionInc)
            genPredictionInc.Add(genPredictionNeg)
            
        
            self._logger.info(" -> pos entries/xsec: "+str(genPredictionPos.GetEntries())+"/"+str(1.*genPredictionPos.Integral()/self.module("Samples").getLumi())+" pb")
            self._logger.info(" -> neg entries/xsec: "+str(genPredictionNeg.GetEntries())+"/"+str(1.*genPredictionNeg.Integral()/self.module("Samples").getLumi())+" pb")
            self._logger.info(" -> inc entries/xsec: "+str(genPredictionInc.GetEntries())+"/"+str(1.*genPredictionInc.Integral()/self.module("Samples").getLumi())+" pb")
            
        outputFile = ROOT.TFile(genMCFileName,"RECREATE")
        for h in histograms:
            h.SetDirectory(outputFile)
            h.Write()
        outputFile.Write()
        outputFile.Close()
        
        
        
