#!/usr/bin/env python
import os
import subprocess
from optparse import OptionParser
import re
import stat
import json
import random
import shutil
import sys

from string import Template

import pxl
import pxl.core
import pxl.modules
import pxl.xml
import pxl.hep
      

if __name__=="__main__":
    parser = OptionParser()
    parser.add_option("--out", default="", dest="out")
    parser.add_option("-t", dest="hours", default="4")
    parser.add_option("--addoption", default=None, dest="addoption")
    (options, args) = parser.parse_args()
    
    outputFolder=options.out
    pluginManager=pxl.core.PluginManager()
    pluginManager.loadPluginsFromDirectory(os.path.join(os.environ['HOME'],".pxl-3.5","plugins"))
    
    
    analysisFiles = []
    for dirpath, dirnames, filenames in os.walk(outputFolder):
        for filename in filenames:
            if filename.endswith(".xml"):   
                analysisImporter=pxl.xml.AnalysisXmlImport()
                inputFolder = os.path.join(outputFolder,dirpath)
                analysisFile =os.path.join(inputFolder,filename)
                analysisImporter.open(analysisFile)
                analysis = pxl.modules.Analysis()
                analysisImporter.parseInto(analysis)
                analysisImporter.close()
                moduleList = analysis.getModules()
                for m in moduleList:
                    opts = m.getOptionDescriptions()
                    for op in opts:
                        if op.usage==op.USAGE_FILE_SAVE:
                            if (m.getType()=="RootTreeWriter") or (m.getType()=="File Output") or op.name=="output":
                                outputFile = os.path.join(inputFolder,m.getOption(op.name))
                                if not os.path.exists(outputFile):
                                    print "Missing output: ",outputFile," from analysis ",os.path.join(inputFolder,filename)
                                    if not analysisFile in analysisFiles:
                                        analysisFiles.append(analysisFile)
                                    
    
    if len(analysisFiles)==0:
        print "Nothing to rerun!"
        sys.exit(0)
        
    filein = open(os.path.join(os.path.dirname(os.path.realpath(__file__)),"slurm_cfg.tmpl"))
    genScript = Template(filein.read())
    
    xmlList = ""
    for analysisFile in analysisFiles:
        xmlList+="    ['"+analysisFile+"'],\n"
    
    generated = genScript.substitute({
        "JOBNAME":os.path.basename(args[0]).rsplit(".")[0],
        "HOURS":"%02i"%int(options.hours),
        "MINUTES":"00",
        "EXEC":"pxlrun",
        "RAM":"2500",
        "SCRIPTNAME":"rerunJob.sh",
        "ARGLIST":"'XMLANAYLSIS'",
        "ARGSTOJOB":"$XMLANAYLSIS",
        "JOBARGLIST":xmlList,
        "DOSTAGEOUT":"True",
        "STAGEOUTFILES":"'*.root*'",
        "EXTARGS":"{}"
    })
    
    fileout = open(os.path.join(outputFolder,"slurm_rerun_cfg.py"),"w")
    fileout.write(generated)
        
    filein.close()
    fileout.close()
       


        

