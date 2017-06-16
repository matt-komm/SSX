#!/usr/bin/env python
import os
import subprocess
from optparse import OptionParser
import re
import stat
import shutil
import numpy
import sys

from string import Template

parser = OptionParser()
parser.add_option("-i","--inputFolder",dest="inputs",action="append", default=[])
parser.add_option("-b","--batch", dest="batch",default=1)
parser.add_option("-o","--out", dest="out")
(options, args) = parser.parse_args()

rootFiles=[]

matchSignalMC = re.compile("^signalMC[A-Za-z_]*[0-9]+.root$")
matchBackgroundMC = re.compile("^backgroundMC[A-Za-z_]*[0-9]+.root$")
matchData = re.compile("^data[0-9]+.root$")

for f in os.listdir(options.out):
    if matchSignalMC.match(f) and f.find("veto")<0:
        if os.path.exists(os.path.join(options.out,f+".friend")):
            continue
        rootFiles.append(os.path.join(options.out,f))

for f in os.listdir(options.out):
    if matchBackgroundMC.match(f) and f.find("veto")<0:
        if os.path.exists(os.path.join(options.out,f+".friend")):
            continue
        rootFiles.append(os.path.join(options.out,f))

for f in os.listdir(options.out):
    if matchData.match(f) and f.find("veto")<0:
        if os.path.exists(os.path.join(options.out,f+".friend")):
            continue
        rootFiles.append(os.path.join(options.out,f))
        
print "found ",len(rootFiles)," root files"

if len(rootFiles)==0:
    sys.exit(1)

'''
for i in range(300):
    if (os.path.join(options.out,"signalMC"+str(i)+".root") not in rootFiles):
        print "missing ",os.path.join(options.out,"signalMC"+str(i)+".root")
    if (os.path.join(options.out,"signalMC_train"+str(i)+".root") not in rootFiles):
        print "missing ",os.path.join(options.out,"signalMC_train"+str(i)+".root")
    if (os.path.join(options.out,"signalMC_test"+str(i)+".root") not in rootFiles):
        print "missing ",os.path.join(options.out,"signalMC_test"+str(i)+".root")
'''

weightFiles = []
weightMatch = re.compile("[A-Za-z_0-9.\-]+.weights.xml")

weightArgs = ""

for inputFolder in options.inputs:
    for f in os.listdir(inputFolder):
        if weightMatch.match(f):
            weightFiles.append(os.path.abspath(os.path.join(inputFolder,f)))
            weightArgs+="-i "+os.path.abspath(os.path.join(inputFolder,f))+" "
print "found ",len(weightFiles)," weight files"


rootFileBatches = numpy.array_split(rootFiles,int(options.batch))

for ibatch, rootFilesBatch in enumerate(rootFileBatches):
    if len(rootFilesBatch)==0:
        continue

    filein = open(os.path.join(os.path.dirname(os.path.realpath(__file__)),"slurm_cfg.tmpl"))
    genScript = Template(filein.read())

    jobArgList = ""
    for f in rootFilesBatch:
        args = "['"+f+"','"+weightArgs+"','"+os.path.basename(f)+".friend'],\n"
        jobArgList+=args
        
    mangeling = options.out
    mangeling = mangeling.rsplit("/",4)
    jobName = "mva_"+mangeling[2]+"_"+mangeling[3]
    scriptName = "mvaEvaluate"
    outFileName = os.path.join(options.out,"slurm_tmva")
    
    if (len(rootFileBatches)>1):
        jobName +="_"+str(ibatch+1)
        scriptName +="_"+str(ibatch+1)
        outFileName +="_"+str(ibatch+1)


    generated = genScript.substitute({
        "JOBNAME": jobName,
        "HOURS":"06",
        "MINUTES":"00",
        "RAM":"2548",
        "EXEC":"$HOME/SSX/PxlModules/build/scripts/evaluateTMVA/evaluateTMVA",
        "ARGLIST":"'FILE','WEIGHTS','OUTPUT'",
        "ARGSTOJOB":"--file $FILE $WEIGHTS $OUTPUT",
        "JOBARGLIST":jobArgList,
        "SCRIPTNAME":scriptName+".sh",
        "DOSTAGEOUT":"True",
        "STAGEOUTFILES":"'*.root.friend'"
    })

    

    fileout = open(outFileName+".py","w")
    fileout.write(generated)
        
    filein.close()
    fileout.close()
    print "Generated: ",outFileName+".py"

    
    
    

