from Module import Module

import logging
import ROOT
import json
import sys

class Samples(Module):
    def __init__(self,options=[]):
        Module.__init__(self,options)
        self._logger = logging.getLogger(__file__)
        self._logger.setLevel(logging.DEBUG)
        self._processDict = {}
        self._processDict["mu"] = {}
        self._processDict["ele"] = {}
        
    def getChargeName(self,charge):
        if charge == 0:
            return "inc"
        elif charge == -1:
            return "neg"
        elif charge == 1:
            return "pos"
        else:
            self._logger.critical("charge '"+str(charge)+"' invalid")
            raise Exception("charge '"+str(charge)+"' invalid")
        
    def getRecoCharge(self):
        return "SingleTop_1__TightLepton_1__Charge"
        
    def getRecoChargeSelection(self,charge):
        if charge == 0:
            return "1"
        elif charge == -1 or charge == 1:
            return "("+self.module("Samples").getRecoCharge()+"=="+str(charge)+")"
        else:
            self._logger.critical("charge '"+str(charge)+"' invalid")
            raise Exception("charge '"+str(charge)+"' invalid")
        

    #lepton charge and parton and particle are the same!
    def getGenCharge(self):
        return "Parton_1__Lepton_1__Charge"
        
    def getGenChargeSelection(self,charge):
        if charge == 0:
            return "1"
        elif charge == -1 or charge == 1:
            return "("+self.module("Samples").getGenCharge()+"=="+str(charge)+")"
        else:
            self._logger.critical("charge '"+str(charge)+"' invalid")
            raise Exception("charge '"+str(charge)+"' invalid")
            

    def getMuMCWeight(self):
        return "(testing==1)*(1./testing_frac)*(Reconstructed_1__btagging_nominal*Reconstructed_1__PU69000_weight*Reconstructed_1__muISO_SF_nominal*Reconstructed_1__muID_SF_nominal*Reconstructed_1__muTRIGGER_SF_nominal)"
        
    def getMuDataWeight(self):
        return "1"
        
    def getMuIsoSelection(self):
        return "(Reconstructed_1__IsoMu24_vALL==1)*(Reconstructed_1__muoncat==0)"
        
    def getMuAntiisoSelection(self):
        return "(Reconstructed_1__IsoMu24_vALL==1)*(Reconstructed_1__muoncat==2)"
        
        
    def getEleMCWeight(self):
        return "(testing==1)*(1./testing_frac)*(Reconstructed_1__btagging_nominal*Reconstructed_1__PU69000_weight*Reconstructed_1__eleRECO_SF_nominal*Reconstructed_1__eleID_SF_nominal)"
        
    def getEleDataWeight(self):
        return "1"
        
    def getEleIsoSelection(self):
        return "(Reconstructed_1__EleTight32_vALL==1)*(Reconstructed_1__elecat==0)*(abs(SingleTop_1__TightLepton_1__superClusterEta)<1.479)"
        
    def getEleAntiisoSelection(self):
        return "(Reconstructed_1__EleTight32_vALL==1)*(Reconstructed_1__elecat==2)*(SingleTop_1__TightLepton_1__effAreaRelIso<0.8)*(abs(SingleTop_1__TightLepton_1__superClusterEta)<1.479)"
        
 
    def getLumi(self):
        return "35.822*1000.0"
        
        
    def getGenWeight(self):
        return "genweight*"+self.module("Samples").getLumi()+"*mcweight"
        
        
    def getMCWeight(self,channel):
        return self.module("Samples").getGenWeight()+"*"+self.module("Samples").getMCWeightReco(channel)
        
    def getMCWeightReco(self,channel):
        
        if channel=="mu":
            return self.module("Samples").getMuMCWeight()
        elif channel=="ele":
            return self.module("Samples").getEleMCWeight()
        else:
            self._logger.critical("Channel '"+channel+"' invalid")
            sys.exit(1)
        
            
    def getDataWeight(self,channel):
        dataweight = "(Reconstructed_1__passMuVeto==1)*(Reconstructed_1__passEleVeto==1)"
        
        if channel=="mu":
            dataweight+="*"+self.module("Samples").getMuDataWeight()
        elif channel=="ele":
            dataweight+="*"+self.module("Samples").getEleDataWeight()
        else:
            self._logger.critical("Channel '"+channel+"' invalid")
            raise Exception("Channel '"+channel+"' invalid")
            
        return dataweight
        
        
    def getEventSelection(self,channel,iso=True):
        selection = "(Reconstructed_1__passMuVeto==1)*(Reconstructed_1__passEleVeto==1)"
        
        if channel=="mu":
            if iso:
                selection+="*"+self.module("Samples").getMuIsoSelection()
            else:
                selection+="*"+self.module("Samples").getMuAntiisoSelection()
        elif channel=="ele":
            if iso:
                selection+="*"+self.module("Samples").getEleIsoSelection()
            else:
                selection+="*"+self.module("Samples").getEleAntiisoSelection()
        else:
            self._logger.critical("Channel '"+channel+"' invalid")
            raise Exception("Channel '"+channel+"' invalid")
            
        return selection
        

    def getNjets(self,njets):
        return "(Reconstructed_1__nSelectedJet=="+str(njets)+")"
        
    def getNbjets(self,nbjets):
        return "(Reconstructed_1__nSelectedBJetTight=="+str(nbjets)+")"
        
        
    def getSystematicPostFix(self):
        return ""
        
        
    def makeProcessFileDict(self,channel):
        rootFiles = self.module("Files").getMCSignal(channel,requireFriends=True)
        rootFiles += self.module("Files").getMCBackground(channel,requireFriends=True)
        rootFiles += self.module("Files").getDataFiles(channel,requireFriends=True)
        
        filesPerProcessMap = {}

        for rootFile in rootFiles:
            f = ROOT.TFile(rootFile[0])
            processSet = set()
            for k in f.GetListOfKeys():
                processSet.add(k.GetName())
            f.Close()
            
            for process in processSet:
                if not filesPerProcessMap.has_key(process):
                    filesPerProcessMap[process]=[]
                filesPerProcessMap[process].append(rootFile)
        self._processDict[channel] = filesPerProcessMap
               
    def saveProcessFileDict(self,output,channel):
        if len(self._processDict[channel].keys())==0:
            self._logger.error("Process dict for channel '"+channel+"' is empty -> skip saving")
        else:
            outFile = open(output,"w")
            outFile.write(json.dumps(self._processDict[channel], sort_keys=True,indent=4, separators=(',', ': ')))
            outFile.close()
        
    def loadProcessFileDict(self,fileName,channel):
        inFile = open(fileName,"r")
        self._processDict[channel] = json.load(inFile)
        inFile.close()
        if len(self._processDict[channel].keys())==0:
            self._logger.critical("Loaded process dict for channel '"+channel+"' from '"+fileName+"' is empty")
            raise Exception("Loaded process dict for channel '"+channel+"' from '"+fileName+"' is empty")
        else:
            self._logger.info("Successfully loaded process dict for channel '"+channel+"' from '"+fileName+"' with '"+str(len(self._processDict[channel].keys()))+"' processes")
    
    def getProcessFiles(self,processName,channel):
        if self._processDict[channel] == None:
            self.module("Samples").makeProcessFileDict(channel)
        if not self._processDict[channel].has_key(processName):
            self._logger.error("Cannot find process '"+processName+"' for channel '"+channel+"' -> skip")
            return []
        return self._processDict[channel][processName]
        
        
    def getSetHist1D(self,hist,setName,channel,variableName,weight,addUnderOverflows=False):
        setDict = self.module("Samples").getSet(setName,channel)
        setWeight = setDict["weight"]
        for sampleName in setDict["samples"]:
            self.module("Samples").getSampleHist1D(hist,sampleName,channel,variableName,weight+"*"+setWeight,addUnderOverflows)
        
        
    def getSampleHist1D(self,hist,sampleName,channel,variableName,weight,addUnderOverflows=False):
        sampleDict = self.module("Samples").getSample(sampleName,channel)
        sampleWeight = sampleDict["weight"]
        for processName in sampleDict["processes"]:
            for fileName in self.module("Samples").getProcessFiles(processName,channel):
                self.module("Utils").getHist1D(hist,fileName,processName,variableName,weight+"*"+sampleWeight,addUnderOverflows)
        
        
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
                    "ST_t-channel_top_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1"+sys,
                    "ST_t-channel_antitop_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1"+sys
                ],
                "weight":mcweightIso
            },

            "tWChannel":
            {
                "processes":[
                    "ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1_ext"+sys,
                    "ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1_ext"+sys
                ],
                "weight":mcweightIso
            },
            
            "TTJets":
            {
                "processes":[
                    "TT_TuneCUETP8M2T4_13TeV-powheg-pythia8"+sys
                ],
                "weight":mcweightIso
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
                    "WToLNu_0J_13TeV-amcatnloFXFX-pythia8_ext"+sys,
                    "WToLNu_1J_13TeV-amcatnloFXFX-pythia8"+sys,
                    "WToLNu_2J_13TeV-amcatnloFXFX-pythia8_ext"+sys,
                ],
                "weight":mcweightIso
            },
            
            
            "DYMG":
            {
                "processes":[
                    "DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_ext"+sys,
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
                    "QCD_Pt-170to300_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8_ext"+sys,
                    "QCD_Pt-300to470_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8_ext"+sys,
                    "QCD_Pt-470to600_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8_ext"+sys,
                    "QCD_Pt-600to800_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8_ext"+sys,
                    "QCD_Pt-800to1000_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8_ext"+sys,
                    "QCD_Pt-1000toInf_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8"+sys,
                ],
                "weight":mcweightIso
            },
            
            "QCDele":
            {
                "processes":[
                    "QCD_Pt-20to30_EMEnriched_TuneCUETP8M1_13TeV_pythia8"+sys,
                    "QCD_Pt-30to50_EMEnriched_TuneCUETP8M1_13TeV_pythia8_ext"+sys,
                    "QCD_Pt-50to80_EMEnriched_TuneCUETP8M1_13TeV_pythia8_ext"+sys,
                    "QCD_Pt-80to120_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8_ext"+sys,
                    "QCD_Pt-120to170_EMEnriched_TuneCUETP8M1_13TeV_pythia8_ext"+sys,
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
                    "ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1_ext"+sys,
                    "ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1_ext"+sys,
                    "TT_TuneCUETP8M2T4_13TeV-powheg-pythia8"+sys,
                    "WToLNu_0J_13TeV-amcatnloFXFX-pythia8_ext"+sys,
                    "WToLNu_1J_13TeV-amcatnloFXFX-pythia8"+sys,
                    "WToLNu_2J_13TeV-amcatnloFXFX-pythia8_ext"+sys,
                    "DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_ext"+sys,
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
        
    
    def getSet(self,name,channel="mu"):
        sets = {
            "tChannel": {
                "samples": ["tChannel"],
                "weight":"1",
                #"color":newColor(1,0.02,0.02),
                "title":"#it{t}-channel",
            },
            "tWChannel": {
                "samples": ["tWChannel"],
                "weight":"1",
                #"color":newColor(0.98,0.77,0.05),
                "title":"tW",
            },
            "TTJets": {
                "samples": ["TTJets"],
                "weight":"1",
                #"color":newColor(0.98,0.57,0.05),
                "title":"t#bar{t}",
            },
            "WJetsMG": {
                "samples": ["WJetsMG"],
                "weight":"1",
                #"color":ROOT.gROOT.GetColor(ROOT.kGreen-2),
                "title":"W+jets",
                #"addtitle":"(MadGraph)",
            },
            "WJetsMGBF": {
                "samples": ["WJetsMG"],
                "weight":"(Reconstructed_1__nBFlavorSelectedJet>0)",
                #"color":ROOT.gROOT.GetColor(ROOT.kGreen+2),
                "title":"W+bX",
                "addtitle":"(MadGraph)",
            },
            "WJetsMGCF": {
                "samples": ["WJetsMG"],
                "weight":"(Reconstructed_1__nBFlavorSelectedJet==0)*(Reconstructed_1__nCFlavorSelectedJet>0)",
                #"color":ROOT.gROOT.GetColor(ROOT.kGreen-3),
                "title":"W+cX",
                #"addtitle":"(MadGraph)",
            },
            "WJetsMGLF": {
                "samples": ["WJetsMG"],
                "weight":"(Reconstructed_1__nBFlavorSelectedJet==0)*(Reconstructed_1__nCFlavorSelectedJet==0)",
                #"color":ROOT.gROOT.GetColor(ROOT.kGreen-7),
                "title":"W+LF",
                #"addtitle":"(MadGraph)",
            },
            
            "WJetsAMCBF": {
                "samples": ["WJetsAMC"],
                "weight":"(Reconstructed_1__nBFlavorSelectedJet>0)",
                #"color":ROOT.gROOT.GetColor(ROOT.kGreen+2),
                "title":"W+bX",
                #"addtitle":"(aMC@NLO)",
                "addtitle":"(inclusive)",
            },
            "WJetsAMCCF": {
                "samples": ["WJetsAMC"],
                "weight":"(Reconstructed_1__nBFlavorSelectedJet==0)*(Reconstructed_1__nCFlavorSelectedJet>0)",
                #"color":ROOT.gROOT.GetColor(ROOT.kGreen-3),
                "title":"W+cX",
                #"addtitle":"(MadGraph)",
            },
            "WJetsAMCLF": {
                "samples": ["WJetsAMC"],
                "weight":"(Reconstructed_1__nBFlavorSelectedJet==0)*(Reconstructed_1__nCFlavorSelectedJet==0)",
                #"color":ROOT.gROOT.GetColor(ROOT.kGreen-7),
                "title":"W+LF",
                #"addtitle":"(MadGraph)",
            },
            "WJetsAMC": {
                "samples": ["WJetsAMC"],
                "weight":"1",
                #"color":ROOT.gROOT.GetColor(ROOT.kGreen-2),
                "title":"W+jets",
                "addtitle":"(inclusive)",
            },
            
            "WJetsAMCexBF": {
                "samples": ["WJetsAMCex"],
                "weight":"(Reconstructed_1__nBFlavorSelectedJet>0)",
                #"color":ROOT.gROOT.GetColor(ROOT.kGreen+2),
                "title":"W+bX",
                "addtitle":"(exclusive)",
                #"addtitle":"(aMC@NLO)",
            },
            "WJetsAMCexCF": {
                "samples": ["WJetsAMCex"],
                "weight":"(Reconstructed_1__nBFlavorSelectedJet==0)*(Reconstructed_1__nCFlavorSelectedJet>0)",
                #"color":ROOT.gROOT.GetColor(ROOT.kGreen-3),
                "title":"W+cX",
                #"addtitle":"(MadGraph)",
            },
            "WJetsAMCexHF": {
                "samples": ["WJetsAMCex"],
                "weight":"(Reconstructed_1__nBFlavorSelectedJet>0 || Reconstructed_1__nCFlavorSelectedJet>0)",
                #"color":newColor(0.1*0.4,0.95*0.6,0.4*0.4),
                "title":"W+HF",
                #"addtitle":"(MadGraph)",
            },
            
            "WJetsAMCexLF": {
                "samples": ["WJetsAMCex"],
                "weight":"(Reconstructed_1__nBFlavorSelectedJet==0)*(Reconstructed_1__nCFlavorSelectedJet==0)",
                #"color":newColor(0.1,0.95,0.4),
                "title":"W+LF",
            },
            "WJetsAMCex": {
                "samples": ["WJetsAMCex"],
                "weight":"1",
                "color":ROOT.gROOT.GetColor(ROOT.kGreen-2),
                "title":"W+jets",
                "addtitle":"(exclusive)",
            },
            
            "DYMG": {
                "samples": ["DYMG"],
                "weight":"1",
                #"color":newColor(0.1,0.35,0.85),
                "title":"Z/#gamma+jets",
                #"addtitle":"(MadGraph)",
            },
            "DYAMC": {
                "samples": ["DYAMC"],
                "weight":"1",
                #"color":newColor(0.1,0.35,0.85),
                "title":"Z/#gamma+jets",
                #"addtitle":"(aMC@NLO)",
            },
            
            "QCD_MC": {
                "samples": [],
                "weight":"1",
                #"color":ROOT.gROOT.GetColor(ROOT.kGray),
                "title":"Multijet"# MC #lower[-0.06]{#scale[0.85]{#times#frac{1}{5}}}",
            },
            "QCD_DD": {
                "samples": [],
                "weight":"1",
                #"color":ROOT.gROOT.GetColor(ROOT.kGray),
                "title":"Multijet"# MC #lower[-0.06]{#scale[0.85]{#times#frac{1}{5}}}",
            },
            "data": {
                "samples": [],
                "weight":"1",
                #"color":ROOT.gROOT.GetColor(ROOT.kBlack),
                "title":"Data",
            }
        }

        if channel=="mu":
            sets["QCD_MC"]["samples"].append("QCDmu")
            sets["QCD_DD"]["samples"].append("data80mu_antiiso")
            sets["QCD_DD"]["samples"].append("MC_antiiso")
            sets["data"]["samples"].append("data80mu")
        elif channel=="ele":
            sets["QCD_MC"]["samples"].append("QCDele")
            sets["QCD_DD"]["samples"].append("data80ele_antiiso")
            sets["QCD_DD"]["samples"].append("MC_antiiso")
            sets["data"]["samples"].append("data80ele")
        else:
            self._logger.error("Channel '"+channel+"' invalid")
            sys.exit(1)

        if not sets.has_key(name):
            self._logger.error("Set dict does not have key '"+name+"'")
            sys.exit(1)
        return sets[name]
        

