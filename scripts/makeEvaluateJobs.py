#!/usr/bin/env python
import os
import subprocess
from optparse import OptionParser
import re
import stat
import shutil
import numpy

from string import Template

parser = OptionParser()
parser.add_option("-i","--inputFolder",dest="inputs",action="append", default=[])
parser.add_option("-c","--channel", dest="channel",default="mu")
parser.add_option("-b","--batch", dest="batch",default=1)
(options, args) = parser.parse_args()

rootFiles=[]

basedirSignalMC = "/nfs/user/mkomm/SSX13/signalMC/"+options.channel
matchSignalMC = re.compile("^signalMC[A-Za-z_]*[0-9]+.root$")

basedirBackgroundMC = "/nfs/user/mkomm/SSX13/backgroundMC/"+options.channel
matchBackgroundMC = re.compile("^backgroundMC[A-Za-z_]*[0-9]+.root$")

basedirData = "/nfs/user/mkomm/SSX13/data/"+options.channel
matchData = re.compile("^data[0-9]+.root$")

for f in os.listdir(basedirSignalMC):
    if matchSignalMC.match(f) and f.find("veto")<0:
        rootFiles.append(os.path.join(basedirSignalMC,f))

for f in os.listdir(basedirBackgroundMC):
    if matchBackgroundMC.match(f) and f.find("veto")<0:
        rootFiles.append(os.path.join(basedirBackgroundMC,f))

for f in os.listdir(basedirData):
    if matchData.match(f) and f.find("veto")<0:
        rootFiles.append(os.path.join(basedirData,f))
        
print "found ",len(rootFiles)," root files"

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
    filein = open(os.path.join(os.path.dirname(os.path.realpath(__file__)),"slurm_cfg.tmpl"))
    genScript = Template(filein.read())

    jobArgList = ""
    for f in rootFilesBatch:
        args = "['"+f+"','"+weightArgs+"','"+f+".friend'],\n"
        jobArgList+=args
        


    generated = genScript.substitute({
        "JOBNAME":"mva_"+options.channel+"_"+str(ibatch+1),
        "HOURS":"00",
        "MINUTES":"30",
        "EXEC":"$HOME/SSX/PxlModules/build/scripts/evaluateTMVA/evaluateTMVA",
        "ARGLIST":"'FILE','WEIGHTS','OUTPUT'",
        "ARGSTOJOB":"--file $FILE $WEIGHTS $OUTPUT",
        "JOBARGLIST":jobArgList,
        "SCRIPTNAME":"tmva_"+options.channel+"_"+str(ibatch+1)+".sh",
        "DOSTAGEOUT":"False",
        "STAGEOUTFILES":""
    })

    fileout = open("slurm_tmva_"+options.channel+"_"+str(ibatch+1)+".py","w")
    fileout.write(generated)
        
    filein.close()
    fileout.close()
    print "Generated: ","slurm_tmva_"+options.channel+"_"+str(ibatch+1)+".py"

    
    
    

