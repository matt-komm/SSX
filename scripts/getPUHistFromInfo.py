import ROOT
import os

parser = OptionParser()
(options, args) = parser.parse_args()

baseFolder = "/storage/data/cms/store/user/mkomm/SSX"
print "looking for files: ",baseFolder+"/*"+args[0]+"*"

rootFiles = {}
for folder in os.listdir(baseFolder):
    if folder.find(args[0])!=-1:
        #print "searching in ...",folder
        for dirpath, dirnames, filenames in os.walk(os.path.join(baseFolder,folder)):
            for f in filenames:
                if f.find("info")!=-1:
                    if not rootFiles.has_key(folder):
                        rootFiles[folder]=[]
                    rootFiles[folder].append(os.path.join(dirpath,f))
                    
for folder in rootFiles.keys():
    print "found ",len(rootFiles[folder])," in ",folder

puHist = ROOT.TH1F("nTrueInteractions1D","nTrueInteractions1D",52,0,52)
puHist.Sumw2()
puHist.SetDirectory(0)

for folder in rootFiles.keys():
    for i,f in enumerate(rootFiles[folder]):
        rootFile = ROOT.TFile(f)
        hist = rootFile.Get("eventAndPuInfo/nTrueInteractions1")
        for ibin in range(hist.GetNbinsX()):
            cbin = puHist.FindBin(hist.GetBinCenter(ibin+1))
            puHist.SetBinContent(ibin+1,puHist.GetBinContent(ibin+1)+hist.GetBinContent(ibin+1))

        rootFile.Close()
        print i,"/",len(rootFiles),puHist.Integral()

puHist.Scale(1.0/puHist.Integral())
outputFile = ROOT.TFile("pu.root","RECREATE")
puHist.SetDirectory(outputFile)
puHist.Write()
outputFile.Close()

