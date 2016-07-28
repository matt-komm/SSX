#!/usr/bin/python

import sys
from optparse import OptionParser
import json
from itertools import groupby
from operator import itemgetter

#create input file with e.g.
#brilcalc lumi -b "STABLE BEAMS" --normtag=/afs/cern.ch/user/l/lumipro/public/normtag_file/normtag_DATACERT.json -i crab/processedLumis.json --byls --output-style csv -o lumiInfo.csv

parser = OptionParser()
parser.add_option("-i", dest="infile",action="store")
parser.add_option("-n", dest="N", type=int, default=5,help="number of output files")

(options, args) = parser.parse_args()

#run:fill,    ls,  time,              beamstatus,   E(GeV), delivered(/ub), recorded(/ub), avgpu, source
#273158:4915, 3:3, 05/11/16 20:43:22, STABLE BEAMS, 6500,4  8357.445,       34.504,        25.1,  PXL

instRunLumiList = []

totalInstLumi = 0.0

inputFile = open(options.infile)
for line in inputFile:
    if line.startswith("#"):
        continue
    lineSplit = line.split(",")
    if len(lineSplit)!=9:
        print "Error - cannot parse line: ",line
        sys.exit(1)
    run = int(lineSplit[0].split(":")[0])
    ls = int(lineSplit[1].split(":")[0])
    instLumi = float(lineSplit[6])
    totalInstLumi+=instLumi
    
    instRunLumiList.append([instLumi,run,ls])
    
print "total read lumi: ",totalInstLumi

instRunLumiList=sorted(instRunLumiList, cmp=lambda x,y: int((x[0]-y[0])*100))

print "min inst. lumi: ",instRunLumiList[0][0]
print "max inst. lumi: ",instRunLumiList[-1][0]

splittedList = [[]]
currentLumiBatchSum = 0.0
for lumiEntry in instRunLumiList:
    if (currentLumiBatchSum)>(totalInstLumi/options.N):
        splittedList.append([])
        currentLumiBatchSum=0
    currentLumiBatchSum+=lumiEntry[0]
    splittedList[-1].append(lumiEntry)
    
for ilist,subList in enumerate(splittedList):
    subSum = 0.0
    runlumidict={}
    for entry in subList:
        subSum+=entry[0]
        if not runlumidict.has_key(entry[1]):
            runlumidict[entry[1]]=[]
        runlumidict[entry[1]].append(entry[2])
    print "lumi=",subSum,", N(LS)=",len(subList),", instL=",subList[0][0],"-",subList[-1][0]
    
    
    resultJSON = {}
    for run in sorted(runlumidict.keys()):
        resultJSON[str(run)]=[]
        runlumidict[run].sort()
        
        for k, g in groupby(enumerate(runlumidict[run]), lambda (i, x): i-x):
            m= map(itemgetter(1), g)
            resultJSON[str(run)].append([m[0],m[-1]])
        
    
    outfile = open(options.infile.rsplit(".",1)[0]+str(ilist)+".json","w")
    #outfile.write("#lumi="+str(subSum)+", N(LS)="+str(len(subList))+", instL="+str(subList[0][0])+"-"+str(subList[-1][0])+"\n")
    json.dump(resultJSON, outfile)
    outfile.close()
    
    
    
    
