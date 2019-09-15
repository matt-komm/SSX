#!/usr/bin/env python

import os
import math
import re
import sys
import ROOT
from optparse import OptionParser

class bcolors:
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKGREEN = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'
    
def warn(s):
    return bcolors.WARNING+s+bcolors.ENDC

def err(s):
    return bcolors.FAIL+s+bcolors.ENDC

parser = OptionParser()
(options, args) = parser.parse_args()

baseFolder = "/storage/data/cms/store/user/mkomm/SSX"
print "looking for files: ",baseFolder+"/*"+args[0]+"*"

stopForError = False

rootFileMatch = re.compile("info_[0-9]+.root")
rootFiles = {}
pxlioFileMatch = re.compile("output_[0-9]+.pxlio")
pxlioFiles = {}

N = len(os.listdir(baseFolder))

for ifolder,folder in enumerate(os.listdir(baseFolder)):
    #print dirpath
    sys.stdout.write(folder+ " ... \r")
    sys.stdout.flush()

    if folder.find(args[0])!=-1:
        #print "searching in ...",folder
        
        for dirpath, dirnames, filenames in os.walk(os.path.join(baseFolder,folder)):
            
            
            if dirpath.endswith("crab_SSX"): #this also checks data
                if len(dirnames)>1:
                    print "\t"+warn("WARNING")+": found multiple output folders in ",dirpath," ",dirnames
                    stopForError=True
            if dirpath.endswith("failed") and len(dirnames)>0:
                print "\t"+warn("WARNING")+": found failed folder in ",dirpath," with content ",dirnames
            for f in filenames:
                if rootFileMatch.match(f):
                    if not rootFiles.has_key(folder):
                        rootFiles[folder]=[]
                    rootFiles[folder].append(os.path.join(dirpath,f))
                if pxlioFileMatch.match(f):
                    if not pxlioFiles.has_key(folder):
                        pxlioFiles[folder]=[]
                    pxlioFiles[folder].append(os.path.join(dirpath,f))

                    
print "\rfinished looping"

for folder in sorted(rootFiles.keys()): #this loop will not go over data
    print "found ",len(rootFiles[folder]),"/",len(pxlioFiles[folder])," info/pxlio files in ",folder
    if len(rootFiles[folder])!=len(pxlioFiles[folder]):
        print "\t"+warn("WARNING")+": uneven number of info/root files"
        pxlioIds = []
        rootIds = []
        for f in rootFiles[folder]:
            i = int(f.rsplit("_",1)[1].split(".",1)[0])
            if i in rootIds:
                print "Double counting root file: ",f
            rootIds.append(i)
        for f in pxlioFiles[folder]:
            i = int(f.rsplit("_",1)[1].split(".",1)[0])
            if i in pxlioIds:
                print "Double counting pxlio file: ",f
            pxlioIds.append(i)
        missingPxlio = set(rootIds)
        missingPxlio -= set(pxlioIds)
        print "\tmissing pxlio: ",missingPxlio
        missingRoot = set(pxlioIds)
        missingRoot -= set(rootIds)
        print "\tmissing root: ",missingRoot
        stopForError=True
        
        
print
for folder in sorted(pxlioFiles.keys()): #this loop will not go over data
    if (rootFiles.has_key(folder)):
        continue
    print "found ",len(pxlioFiles[folder])," pxlio files in ",folder
    pxlioIds = []
    for f in pxlioFiles[folder]:
        pxlioIds.append(int(f.rsplit("_",1)[1].split(".",1)[0]))
    pxlioIds.sort()
    missingIds = []
    for i,id in enumerate(pxlioIds):
        if (1+i+len(missingIds))!=id:
            missingIds.extend(range(1+i+len(missingIds),id))
    if len(missingIds)>0:
        print "\t"+warn("WARNING")+": likely missing files  "+str(missingIds)
        print "\texisting+missing files = "+str( len(pxlioFiles[folder])+len(missingIds))


if stopForError:
    print "EXIT due to file mismatch"
    #sys.exit(-1)
    
WtoLeptons = 0.1086
    
xsecDB = {
    "DYJetsToLL_M-10to50":18610.0,
    "DY1JetsToLL_M-10to50":725.0, #LO MadGraph from MCM
    "DY2JetsToLL_M-10to50":394.5, #LO MadGraph from MCM
    "DY3JetsToLL_M-10to50":96.47, #LO MadGraph from MCM
    "DY4JetsToLL_M-10to50":34.84, #LO MadGraph from MCM
    
    "DYJetsToLL_M-50": 4895.0, #from HIG-16-017
    "DY1JetsToLL_M-50": 1016.0, #from HIG-16-017
    "DY2JetsToLL_M-50": 331.0, #from HIG-16-017
    "DY3JetsToLL_M-50": 96.0, #from HIG-16-017
    "DY4JetsToLL_M-50": 51.0, #from HIG-16-017
    
    "QCD_Pt-20toInf_MuEnrichedPt15": 720648000 * 0.00042,
    
    "QCD_Pt-15to20_MuEnrichedPt5":1273190000*0.003,  #LO MadGraph from MCM
    "QCD_Pt-20to30_MuEnrichedPt5":558528000*0.0053,  #LO MadGraph from MCM
    "QCD_Pt-30to50_MuEnrichedPt5":139803000*0.01182,  #LO MadGraph from MCM
    "QCD_Pt-50to80_MuEnrichedPt5":19222500*0.02276,  #LO MadGraph from MCM
    "QCD_Pt-80to120_MuEnrichedPt5":2758420*0.03844,  #LO MadGraph from MCM
    "QCD_Pt-120to170_MuEnrichedPt5":469797*0.05362,  #LO MadGraph from MCM
    "QCD_Pt-170to300_MuEnrichedPt5":117989*0.07335,  #LO MadGraph from MCM
    "QCD_Pt-300to470_MuEnrichedPt5":7820.25*0.10196,  #LO MadGraph from MCM
    "QCD_Pt-470to600_MuEnrichedPt5":645.5*0.12242,  #LO MadGraph from MCM
    "QCD_Pt-600to800_MuEnrichedPt5":187.11*0.13412,  #LO MadGraph from MCM
    "QCD_Pt-800to1000_MuEnrichedPt5":32.35*0.14552,  #LO MadGraph from MCM
    "QCD_Pt-1000toInf_MuEnrichedPt5":10.43*0.15544, #LO MadGraph from MCM
    
    "QCD_Pt-15to20_EMEnriched":1279000000*0.0018,
    "QCD_Pt-20to30_EMEnriched":557600000*0.0096,
    "QCD_Pt-30to50_EMEnriched":136000000*0.073,
    "QCD_Pt-50to80_EMEnriched": 19800000*0.146,
    "QCD_Pt-80to120_EMEnriched":2800000*0.125,
    "QCD_Pt-120to170_EMEnriched":477000*0.132,
    "QCD_Pt-170to300_EMEnriched":114000*0.165,
    "QCD_Pt-300toInf_EMEnriched":9000*0.15,
     
    "ST_t-channel_4f_leptonDecays": (80.95+136.02)*3*WtoLeptons,
    "ST_t-channel_antitop_4f_leptonDecays": 80.95*3*WtoLeptons,
    "ST_t-channel_top_4f_leptonDecays": 136.02*3*WtoLeptons,
    
    "ST_t-channel_5f_leptonDecays": (80.95+136.02)*3*WtoLeptons,
    "ST_t-channel_antitop_5f_leptonDecays": 80.95*3*WtoLeptons,
    "ST_t-channel_top_5f_leptonDecays": 136.02*3*WtoLeptons,
     
    "ST_t-channel_4f": 80.95+136.02,
    "ST_t-channel_antitop_4f": 80.95,
    "ST_t-channel_top_4f": 136.02,
    
    "ST_t-channel_5f": 80.95+136.02,
    "ST_t-channel_antitop_5f": 80.95,
    "ST_t-channel_top_5f": 136.02,
    
    "ST_t-channel_eleDecays_13TeV-comphep":(80.95+136.02)*3*WtoLeptons,
    "ST_t-channel_muDecays_13TeV-comphep":(80.95+136.02)*3*WtoLeptons,
    "ST_t-channel_tauDecays_13TeV-comphep":(80.95+136.02)*3*WtoLeptons,
    
    "ST_tW_antitop": 35.6,
    "ST_tW_top": 35.6,
    "ST_tWll": 2*35.6*(3*WtoLeptons)*(3*WtoLeptons),
    
    "WJetsToLNu":20508.9*3,
    
    "WToLNu_0J_13TeV":49670.0, #MCM
    "WToLNu_1J_13TeV":8264.0, #MCM
    "WToLNu_2J_13TeV":3226.0, #MCM 2628
    
    "TT": 831.76,
    "TTJets": 831.76,
    
    "WW":118.7, #https://twiki.cern.ch/twiki/bin/viewauth/CMS/StandardModelCrossSectionsat13TeV
    "WZ":47.13,
    "ZZ":16.523, #https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns#Diboson
}

def findXsec(name):
    #find largest match
    match = ""
    for process in xsecDB.keys():
        if (len(process)>len(match)) and (name.find(process)!=-1):
            match = process
    if len(match)==0:
        return "? //"+warn("WARNING")+", xsec not found"
    return [str(xsecDB[match])+" // xsec for process '"+match+"'",xsecDB[match]]
    
    
eventWeights = {}

for folder in sorted(rootFiles.keys()):
    #print "reading ... ",folder
    
    nEvents = 0
    weightedSumPos = 0
    weightedSumNeg = 0
    
    weightedGenSum = 0.0

    for f in rootFiles[folder]:
        rootFile = ROOT.TFile(f)
        retry = 0
        while (not rootFile and retry < 20):
            rootFile = ROOT.TFile(f)
            time.sleep(1+retry)
            retry+=1
        if (not rootFile):
            print err("ERROR"),"Cannot read file",f,"-> skipping"
            continue
        hist = rootFile.Get("eventAndPuInfo/genweight")
        
        weightedSumNeg += math.fabs(hist.GetBinContent(1))
        weightedSumPos += math.fabs(hist.GetBinContent(2))
        nEvents += hist.GetEntries()
        
        weightedGenSum+=hist.GetBinContent(1)+hist.GetBinContent(2)

    avgWeight = nEvents/(weightedSumNeg+weightedSumPos)
    sumPosWeight = round(weightedSumPos*avgWeight)
    sumNegWeight = round(weightedSumNeg*avgWeight)

    tab = "    "
    '''
    print tab+"{\""+folder.rsplit("_v",1)[0]+"\","
    print tab+tab+"new SimpleWeightInfo("
    print tab+tab+tab+"//total="+str(nEvents)+" eff="+str(sumPosWeight)+" - "+str(sumNegWeight)+" = "+str(sumPosWeight-sumNegWeight)
    print tab+tab+tab+str(sumPosWeight-sumNegWeight)+","
    print tab+tab+tab+findXsec(folder.rsplit("_v",1)[0])[0]
    print tab+tab+")"
    print tab+"},"
    '''
    processName = folder.rsplit("_v",1)[0]
    if processName.find('_ext')>=0:
        processName = processName[0:processName.find('_ext')]
        
    if not eventWeights.has_key(processName):
        eventWeights[processName]={"total":0,"pos":0,"neg":0,"sum":0}
    eventWeights[processName]["total"]+=nEvents
    eventWeights[processName]["pos"]+=sumPosWeight
    eventWeights[processName]["neg"]+=sumNegWeight
    eventWeights[processName]["sum"]+=weightedGenSum
    
for process in sorted(eventWeights.keys()):

    weights = eventWeights[process]
    print tab+"{\""+process+"\","
    print tab+tab+"new SimpleWeightInfo("
    print tab+tab+tab+"//xtotal="+str(weights["total"])+" eff="+str(weights["pos"])+" - "+str(weights["neg"])+" = "+str(weights["pos"]-weights["neg"])
    print tab+tab+tab+str(weights["sum"])+", //xsec from weight = ",str(weights["sum"]/weights["total"])
    print tab+tab+tab+findXsec(process)[0]
    print tab+tab+")"
    print tab+"},"
    
    
    #print "\tentries = ",nEvents
    #print "\tpos = ",sumPosWeight
    #print "\tneg = ",sumNegWeight
    #print "\teff = ",sumPosWeight-sumNegWeight


