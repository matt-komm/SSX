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


for folder in sorted(rootFiles.keys()):
    print "reading ... ",folder
    
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

    print "\tentries = ",nEvents
    print "\tpos = ",sumPosWeight
    print "\tneg = ",sumNegWeight
    print "\teff = ",sumPosWeight-sumNegWeight

