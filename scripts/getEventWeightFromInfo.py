#!/usr/bin/python

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


parser = OptionParser()
(options, args) = parser.parse_args()

baseFolder = "/storage/data/cms/store/user/mkomm/SSX"
print "looking for files: ",baseFolder+"/*"+args[0]+"*"

stopForError = False

rootFileMatch = re.compile("info_[0-9]+.root")
rootFiles = {}
pxlioFileMatch = re.compile("output_[0-9]+.pxlio")
pxlioFiles = {}
for folder in os.listdir(baseFolder):
    if folder.find(args[0])!=-1:
        #print "searching in ...",folder
        for dirpath, dirnames, filenames in os.walk(os.path.join(baseFolder,folder)):
            #print dirpath
            if dirpath.endswith("crab_SSX"): #this also checks data
                if len(dirnames)>1:
                    print "\t"+warn("WARNING")+": found multiple output folders in ",dirpath," ",dirnames
                    stopForError=True
            for f in filenames:
                if rootFileMatch.match(f):
                    if not rootFiles.has_key(folder):
                        rootFiles[folder]=[]
                    rootFiles[folder].append(os.path.join(dirpath,f))
                if pxlioFileMatch.match(f):
                    if not pxlioFiles.has_key(folder):
                        pxlioFiles[folder]=[]
                    pxlioFiles[folder].append(os.path.join(dirpath,f))
                    

for folder in rootFiles.keys(): #this loop will not go over data
    print "found ",len(rootFiles[folder]),"/",len(pxlioFiles[folder])," info/pxlio files in ",folder
    if len(rootFiles[folder])!=len(pxlioFiles[folder]):
        print "\t"+warn("WARNING")+": uneven number of info/root files"
        pxlioIds = []
        rootIds = []
        for f in rootFiles[folder]:
            rootIds.append(int(f.rsplit("_",1)[1].split(".",1)[0]))
        for f in pxlioFiles[folder]:
            pxlioIds.append(int(f.rsplit("_",1)[1].split(".",1)[0]))
        missingPxlio = set(rootIds)
        missingPxlio -= set(pxlioIds)
        print "\tmissing pxlio: ",missingPxlio
        missingRoot = set(pxlioIds)
        missingRoot -= set(rootIds)
        print "\tmissing root: ",missingRoot
        stopForError=True

if stopForError:
    print "EXIT due to file mismatch"
    sys.exit(-1)
    
    
xsecDB = {
    "DYJetsToLL_M-10to50":18610.0,
    "DY1JetsToLL_M-10to50":725.0, #LO MadGraph from MCM
    "DY2JetsToLL_M-10to50":394.5, #LO MadGraph from MCM
    "DY3JetsToLL_M-10to50":96.47, #LO MadGraph from MCM
    "DY4JetsToLL_M-10to50":34.84, #LO MadGraph from MCM
    
    "DYJetsToLL_M-50": 1921.8*3,
    
    "QCD_Pt-20toInf_MuEnrichedPt15": 866600000 * 0.00044,
    
    "QCD_Pt-15to20_MuEnrichedPt5":1273190000,  #LO MadGraph from MCM
    "QCD_Pt-20to30_MuEnrichedPt5":558528000,  #LO MadGraph from MCM
    "QCD_Pt-30to50_MuEnrichedPt5":139803000,  #LO MadGraph from MCM
    "QCD_Pt-50to80_MuEnrichedPt5":19222500,  #LO MadGraph from MCM
    "QCD_Pt-80to120_MuEnrichedPt5":2758420,  #LO MadGraph from MCM
    "QCD_Pt-120to170_MuEnrichedPt5":469797,  #LO MadGraph from MCM
    "QCD_Pt-170to300_MuEnrichedPt5":117989,  #LO MadGraph from MCM
    "QCD_Pt-300to470_MuEnrichedPt5":7820.25,  #LO MadGraph from MCM
    "QCD_Pt-470to600_MuEnrichedPt5":645.5,  #LO MadGraph from MCM
    "QCD_Pt-600to800_MuEnrichedPt5":187.11,  #LO MadGraph from MCM
    "QCD_Pt-800to1000_MuEnrichedPt5":32.35,  #LO MadGraph from MCM
    "QCD_Pt-1000toInf_MuEnrichedPt5":10.43, #LO MadGraph from MCM
     
    "ST_t-channel_4f": 80.95+136.02,
    "ST_t-channel_antitop_4f": 80.95,
    "ST_t-channel_top_4f": 136.02,
    
    "ST_t-channel_5f": 80.95+136.02,
    "ST_t-channel_antitop_5f": 80.95,
    "ST_t-channel_top_5f": 136.02,
    
    "ST_tW_antitop": 35.6,
    "ST_tW_top": 35.6,
    
    "WJetsToLNu":20508.9*3,
    
    "TT": 831.76,
    "TTJets": 831.76,
}

def findXsec(name):
    #find largest match
    match = ""
    for process in xsecDB.keys():
        if (len(process)>len(match)) and (name.find(process)!=-1):
            match = process
    if len(match)==0:
        return "? //WARNING, xsec not found"
    return str(xsecDB[match])+" // xsec for process '"+match+"'"

for folder in sorted(rootFiles.keys()):
    #print "reading ... ",folder
    
    nEvents = 0
    sumPosWeight = 0
    sumNegWeight = 0
    for f in rootFiles[folder]:
        rootFile = ROOT.TFile(f)
        hist = rootFile.Get("eventAndPuInfo/genweight")
        wSum = math.fabs(hist.GetBinContent(1))+math.fabs(hist.GetBinContent(2))
        eSum = hist.GetEntries()
        w = eSum/wSum
        nEvents+=eSum
        sumPosWeight +=round(math.fabs(hist.GetBinContent(2))*w)
        sumNegWeight +=round(math.fabs(hist.GetBinContent(1))*w)

    tab = "    "
    print tab+"{\""+folder.rsplit("_v",1)[0]+"\","
    print tab+tab+"{"
    print tab+tab+tab+"//total="+str(nEvents)+" eff="+str(sumPosWeight)+" - "+str(sumNegWeight)+" = "+str(sumPosWeight-sumNegWeight)
    print tab+tab+tab+str(sumPosWeight-sumNegWeight)+","
    print tab+tab+tab+findXsec(folder.rsplit("_v",1)[0])
    print tab+tab+"}"
    print tab+"},"
    #print "\tentries = ",nEvents
    #print "\tpos = ",sumPosWeight
    #print "\tneg = ",sumNegWeight
    #print "\teff = ",sumPosWeight-sumNegWeight

