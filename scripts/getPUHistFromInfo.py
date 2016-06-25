import ROOT
import os


baseFolder = "/storage/data/cms/store/user/mkomm/SSX"
print "looking for files: ",baseFolder

rootFiles = {}
for folder in os.listdir(baseFolder):
    #print "searching in ...",folder
    for dirpath, dirnames, filenames in os.walk(os.path.join(baseFolder,folder)):
        for f in filenames:
            if f.find("info")!=-1:
                if not rootFiles.has_key(folder):
                    rootFiles[folder]=[]
                rootFiles[folder].append(os.path.join(dirpath,f))
                    
nFiles = 0
for folder in rootFiles.keys():
    print "found ",len(rootFiles[folder])," in ",folder
    nFiles+=len(rootFiles[folder])

puHist = None

for folder in rootFiles.keys():
    for i,f in enumerate(rootFiles[folder]):
        rootFile = ROOT.TFile(f)
        hist = rootFile.Get("eventAndPuInfo/nTrueInteractions1")
        if (puHist==None):
            puHist = hist.Clone("nTrueInteractions1D")
            puHist.Sumw2()
            puHist.SetDirectory(0)
        else:
            puHist.Add(hist)
        rootFile.Close()
        print i,"/",len(rootFiles[folder]),puHist.Integral()

puHist.Scale(1.0/puHist.Integral())
outputFile = ROOT.TFile("pu.root","RECREATE")
puHist.SetDirectory(outputFile)
puHist.Write()
outputFile.Close()

