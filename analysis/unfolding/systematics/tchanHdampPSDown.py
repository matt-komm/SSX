import ROOT
import math
import numpy
import random
import os

from defaultModules.Module import Module

import logging

class SamplesTchanHdampPSDown(Module.getClass("Samples")):
    def __init__(self,options=[]):
        SamplesTchanHdampPSDown.baseClass.__init__(self,options)
        self._logger = logging.getLogger(__file__)
        self._logger.setLevel(logging.DEBUG)
        
    def getSample(self,name,channel="mu",sys=None):
        mcweightIso = self.module("Samples").getMCWeight(channel)+"*"+self.module("Samples").getEventSelection(channel,iso=True)
        mcweightAntiiso = self.module("Samples").getMCWeight(channel)+"*"+self.module("Samples").getEventSelection(channel,iso=False)
        dataweightIso = self.module("Samples").getDataWeight(channel)+"*"+self.module("Samples").getEventSelection(channel,iso=True)
        dataweightAntiiso = self.module("Samples").getDataWeight(channel)+"*"+self.module("Samples").getEventSelection(channel,iso=False)
        
        if sys==None:
            sys = self.module("Samples").getSystematicPostFix()
        
        sampleDict = {
            "tChannel":
            {
                "processes":[
                    "ST_t-channel_top_4f_hdampdown_inclusiveDecays_13TeV-powhegV2-madspin-pythia8"+sys,
                    "ST_t-channel_antitop_4f_hdampdown_inclusiveDecays_13TeV-powhegV2-madspin-pythia8"+sys
                ],
                "weight":mcweightIso
            },

            "tWChannel":
            {
                "processes":[
                    "ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1"+sys,
                    "ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1"+sys
                ],
                "weight":mcweightIso
            },
            
            "TTJets":
            {
                "processes":[
                    "TT_TuneCUETP8M2T4_13TeV-powheg-pythia8"+sys
                ],
                "weight":mcweightIso+"*(Generated_1__top_pt_rew)"
            },
            
            "WJetsAMC":
            {
                "processes":[
                    "WJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8"+sys
                ],
                "weight":mcweightIso
            },
            
            "WJetsAMCex":
            {
                "processes":[
                    "WToLNu_0J_13TeV-amcatnloFXFX-pythia8"+sys,
                    "WToLNu_1J_13TeV-amcatnloFXFX-pythia8"+sys,
                    "WToLNu_2J_13TeV-amcatnloFXFX-pythia8"+sys,
                ],
                "weight":mcweightIso
            },
            
            
            "DYMG":
            {
                "processes":[
                    "DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8"+sys,
                    "DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8"+sys
                ],
                "weight":mcweightIso
            },
            
            "DYAMC":
            {
                "processes":[
                    "DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8"+sys,
                    "DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8"+sys
                ],
                "weight":mcweightIso
            },
            
            
            "QCDmu":
            {
                "processes":[
                    "QCD_Pt-15to20_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8"+sys,
                    "QCD_Pt-20to30_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8"+sys,
                    "QCD_Pt-30to50_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8"+sys,
                    "QCD_Pt-50to80_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8"+sys,
                    "QCD_Pt-80to120_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8"+sys,
                    "QCD_Pt-120to170_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8"+sys,
                    "QCD_Pt-170to300_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8"+sys,
                    "QCD_Pt-300to470_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8"+sys,
                    "QCD_Pt-470to600_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8"+sys,
                    "QCD_Pt-600to800_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8"+sys,
                    "QCD_Pt-800to1000_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8"+sys,
                    "QCD_Pt-1000toInf_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8"+sys,
                ],
                "weight":mcweightIso
            },
            
            "QCDele":
            {
                "processes":[
                    "QCD_Pt-20to30_EMEnriched_TuneCUETP8M1_13TeV_pythia8"+sys,
                    "QCD_Pt-30to50_EMEnriched_TuneCUETP8M1_13TeV_pythia8"+sys,
                    "QCD_Pt-50to80_EMEnriched_TuneCUETP8M1_13TeV_pythia8"+sys,
                    "QCD_Pt-80to120_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8"+sys,
                    "QCD_Pt-120to170_EMEnriched_TuneCUETP8M1_13TeV_pythia8"+sys,
                    "QCD_Pt-170to300_EMEnriched_TuneCUETP8M1_13TeV_pythia8"+sys,
                    "QCD_Pt-300toInf_EMEnriched_TuneCUETP8M1_13TeV_pythia8"+sys,
                ],
                "weight":mcweightIso
            },
            
            
            "MC_antiiso":
            {
                "processes":[
                    "ST_t-channel_top_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1"+sys,
                    "ST_t-channel_antitop_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1"+sys,
                    "ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1"+sys,
                    "ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1"+sys,
                    "TT_TuneCUETP8M2T4_13TeV-powheg-pythia8"+sys,
                    "WToLNu_0J_13TeV-amcatnloFXFX-pythia8"+sys,
                    "WToLNu_1J_13TeV-amcatnloFXFX-pythia8"+sys,
                    "WToLNu_2J_13TeV-amcatnloFXFX-pythia8"+sys,
                    "DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8"+sys,
                    "DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8"+sys
                ],
                "weight":"(-1)*"+mcweightAntiiso
            },
            
            "data80mu":
            {
                "processes":[
                    "SingleMuon_Run2016B-03Feb2017_ver2-v2",
                    "SingleMuon_Run2016C-03Feb2017-v1",
                    "SingleMuon_Run2016D-03Feb2017-v1",
                    "SingleMuon_Run2016E-03Feb2017-v1",
                    "SingleMuon_Run2016F-03Feb2017-v1",
                    "SingleMuon_Run2016G-03Feb2017-v1",
                    "SingleMuon_Run2016H-03Feb2017_ver2-v1",
                    "SingleMuon_Run2016H-03Feb2017_ver3-v1"
                ],
                
                "weight":dataweightIso
            },
            
            "data80mu_antiiso":
            {
                "processes":[
                    "SingleMuon_Run2016B-03Feb2017_ver2-v2",
                    "SingleMuon_Run2016C-03Feb2017-v1",
                    "SingleMuon_Run2016D-03Feb2017-v1",
                    "SingleMuon_Run2016E-03Feb2017-v1",
                    "SingleMuon_Run2016F-03Feb2017-v1",
                    "SingleMuon_Run2016G-03Feb2017-v1",
                    "SingleMuon_Run2016H-03Feb2017_ver2-v1",
                    "SingleMuon_Run2016H-03Feb2017_ver3-v1"
                ],
                
                "weight":dataweightAntiiso
            },
            
            
            "data80ele":
            {
                "processes":[
                    "SingleElectron_Run2016B-03Feb2017_ver2-v2",
                    "SingleElectron_Run2016C-03Feb2017-v1",
                    "SingleElectron_Run2016D-03Feb2017-v1",
                    "SingleElectron_Run2016E-03Feb2017-v1",
                    "SingleElectron_Run2016F-03Feb2017-v1",
                    "SingleElectron_Run2016G-03Feb2017-v1",
                    "SingleElectron_Run2016H-03Feb2017_ver2-v1",
                    "SingleElectron_Run2016H-03Feb2017_ver3-v1"
                ],
                
                "weight":dataweightIso
            },
            
            "data80ele_antiiso":
            {
                "processes":[
                    "SingleElectron_Run2016B-03Feb2017_ver2-v2",
                    "SingleElectron_Run2016C-03Feb2017-v1",
                    "SingleElectron_Run2016D-03Feb2017-v1",
                    "SingleElectron_Run2016E-03Feb2017-v1",
                    "SingleElectron_Run2016F-03Feb2017-v1",
                    "SingleElectron_Run2016G-03Feb2017-v1",
                    "SingleElectron_Run2016H-03Feb2017_ver2-v1",
                    "SingleElectron_Run2016H-03Feb2017_ver3-v1"
                ],
                
                "weight":dataweightAntiiso
            }
        }
        
        if not sampleDict.has_key(name):
            self._logger.error("Sample dict does not have key '"+name+"'")
            sys.exit(1)
        return sampleDict[name]



class UtilsTchanHdampPSDown(Module.getClass("Utils")):
    def __init__(self,options=[]):
        UtilsTchanHdampPSDown.baseClass.__init__(self,options)
        self._logger = logging.getLogger(__file__)
        self._logger.setLevel(logging.DEBUG)
        
    def getUncertaintyName(self):
        return "tchanHdampPSDown"
        
