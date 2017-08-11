import os
import ROOT
import re
import sys
import argparse

parser = argparse.ArgumentParser(description='')
parser.add_argument('--ch', dest='channel', action='store',default='',help='name')
parser.add_argument('--ver', dest='ver', action='store',default='4',help='version')
parser.add_argument('--name', dest='name', action='store',default='',help='name')
parser.add_argument('--cfg', dest='cfg', action='store',default='',help='config')
parser.add_argument('--mix', dest='mix',default='0.01',help='mixing of CR regions')
args = parser.parse_args()

print "train BDT with name: ",args.name
print "train with configuration: ",args.cfg

basePathTrainingBackgroundList = []
basePathTestingBackgroundList = []
basePathTrainingSignalList = []
basePathTestingSignalList = []

if args.channel == "mu":
    basePathTrainingBackgroundList.append("/nfs/user/mkomm/SSX13/backgroundMC/mu"+args.ver)
    basePathTestingBackgroundList.append("/nfs/user/mkomm/SSX13/backgroundMC/mu"+args.ver)
    basePathTrainingSignalList.append("/nfs/user/mkomm/SSX13/backgroundMC/mu"+args.ver)
    basePathTestingSignalList.append("/nfs/user/mkomm/SSX13/backgroundMC/mu"+args.ver)
elif args.channel == "ele":
    basePathTrainingBackgroundList.append("/nfs/user/mkomm/SSX13/backgroundMC/ele"+args.ver)
    basePathTestingBackgroundList.append("/nfs/user/mkomm/SSX13/backgroundMC/ele"+args.ver)
    basePathTrainingSignalList.append("/nfs/user/mkomm/SSX13/backgroundMC/ele"+args.ver)
    basePathTestingSignalList.append("/nfs/user/mkomm/SSX13/backgroundMC/ele"+args.ver)
elif args.channel == "comb":
    basePathTrainingBackgroundList.append("/nfs/user/mkomm/SSX13/backgroundMC/mu"+args.ver)
    basePathTestingBackgroundList.append("/nfs/user/mkomm/SSX13/backgroundMC/mu"+args.ver)
    basePathTrainingSignalList.append("/nfs/user/mkomm/SSX13/backgroundMC/mu"+args.ver)
    basePathTestingSignalList.append("/nfs/user/mkomm/SSX13/backgroundMC/mu"+args.ver)
    basePathTrainingBackgroundList.append("/nfs/user/mkomm/SSX13/backgroundMC/ele"+args.ver)
    basePathTestingBackgroundList.append("/nfs/user/mkomm/SSX13/backgroundMC/ele"+args.ver)
    basePathTrainingSignalList.append("/nfs/user/mkomm/SSX13/backgroundMC/ele"+args.ver)
    basePathTestingSignalList.append("/nfs/user/mkomm/SSX13/backgroundMC/ele"+args.ver)

rootFilesTrain=[]
rootFilesTest=[]

matchTrainingBackground = re.compile("^backgroundMC_train[0-9]+.root$")
matchTestingBackground = re.compile("^backgroundMC_test[0-9]+.root$")

matchTrainingSignal = re.compile("^backgroundMC_train[0-9]+.root$")
matchTestingSignal = re.compile("^backgroundMC_test[0-9]+.root$")

for basePathTrainingBackground in basePathTrainingBackgroundList:
    for f in os.listdir(basePathTrainingBackground):
        if matchTrainingBackground.match(f):
            rootFilesTrain.append(os.path.join(basePathTrainingBackground,f))
        
for basePathTestingBackground in basePathTestingBackgroundList:
    for f in os.listdir(basePathTestingBackground):
        if  matchTestingBackground.match(f):
            rootFilesTest.append(os.path.join(basePathTestingBackground,f))
         
#rootFilesTrain = rootFilesTrain[:20]   
#rootFilesTest = rootFilesTest[:20]
        
for basePathTrainingSignal in basePathTrainingSignalList:
    for f in os.listdir(basePathTrainingSignal):
        if matchTrainingSignal.match(f):
            rootFilesTrain.append(os.path.join(basePathTrainingSignal,f))
        
for basePathTestingSignal in basePathTestingSignalList:
    for f in os.listdir(basePathTestingSignal):
        if  matchTestingSignal.match(f):
            rootFilesTest.append(os.path.join(basePathTestingSignal,f))
        
#rootFilesTrain = rootFilesTrain[:20]   
#rootFilesTest = rootFilesTest[:20]
       
print "found: ",len(rootFilesTrain)," (train) & ",len(rootFilesTest)," (test) files"

ROOT.gSystem.Load("$HOME/SSX/PxlModules/build/internal/TMVA/libTMVA.so")

ROOT.TMVA.Tools.Instance()
f = ROOT.TFile(args.name+".root","RECREATE")
factory = ROOT.TMVA.Factory("test",f,"!V:Color=False:AnalysisType=Classification")

backgroundTrainChains=[]
backgroundTestChains=[]

signalTrainChains=[]
signalTestChains=[]

wjetsCut = "((formva==1)&&(Reconstructed_1__muoncat==0 || Reconstructed_1__elecat==0) && (Reconstructed_1__nSelectedJet==2))"
ttbarCut = "((formva==1)&&(Reconstructed_1__muoncat==0 || Reconstructed_1__elecat==0) && (Reconstructed_1__nSelectedBJetTight==1))"

for background in [
    ["WJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8",0.25,wjetsCut],
    ["WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_ext",0.25,wjetsCut],
    ["WToLNu_0J_13TeV-amcatnloFXFX-pythia8_ext",0.5,wjetsCut],
    ["WToLNu_1J_13TeV-amcatnloFXFX-pythia8",0.5,wjetsCut],
    ["WToLNu_2J_13TeV-amcatnloFXFX-pythia8_ext",0.5,wjetsCut],
]:
    chainTrain = ROOT.TChain(background[0])
    backgroundTrainChains.append(chainTrain)
    for rootFile in rootFilesTrain:
        f = ROOT.TFile(rootFile)
        if f.Get(background[0]):
            chainTrain.AddFile(rootFile)
        f.Close()
    #print "Training:",background[0],chainTrain.GetEntries()
    if chainTrain.GetEntries()>10:
        factory.AddTree(chainTrain,"Background",background[1],ROOT.TCut(background[2]),ROOT.TMVA.Types.kTraining)
    else:
        pass
        #print "WARNING: too few events -> skip"
    
    chainTest = ROOT.TChain(background[0])
    backgroundTestChains.append(chainTest)
    for rootFile in rootFilesTest:
        f = ROOT.TFile(rootFile)
        if f.Get(background[0]):
            chainTest.AddFile(rootFile)
        f.Close()
    #print "Testing:",background[0],chainTest.GetEntries()
    if chainTest.GetEntries()>10:
        factory.AddTree(chainTest,"Background",background[1],ROOT.TCut(background[2]),ROOT.TMVA.Types.kTesting)
    else:
        pass
        #print "WARNING: too few events -> skip"
        
for signal in [
    ["TT_TuneCUETP8M2T4_13TeV-powheg-pythia8",1.0,ttbarCut],
]:
    chainTrain = ROOT.TChain(signal[0])
    signalTrainChains.append(chainTrain)
    for rootFile in rootFilesTrain:
        f = ROOT.TFile(rootFile)
        if f.Get(signal[0]):
            chainTrain.AddFile(rootFile)
        f.Close()
    #print "Training:",signal[0],chainTrain.GetEntries()
    factory.AddTree(chainTrain,"Signal",signal[1],ROOT.TCut(signal[2]),ROOT.TMVA.Types.kTraining)
    
    chainTest = ROOT.TChain(signal[0])
    signalTestChains.append(chainTest)
    for rootFile in rootFilesTest:
        f = ROOT.TFile(rootFile)
        if f.Get(signal[0]):
            chainTest.AddFile(rootFile)
        f.Close()
    #print "Testing:",signal[0],chainTest.GetEntries()
    factory.AddTree(chainTest,"Signal",signal[1],ROOT.TCut(signal[2]),ROOT.TMVA.Types.kTesting)


leptonSelection = "((Reconstructed_1__passMuVeto==1)&&(Reconstructed_1__passEleVeto==1)"
if args.channel=="mu":
    leptonSelection +="&&(Reconstructed_1__muoncat==0))"
elif args.channel=="ele":
    leptonSelection +="&&(Reconstructed_1__elecat==0))"
elif args.channel=="comb":
    leptonSelection +="&&(Reconstructed_1__muoncat==0 || Reconstructed_1__elecat==0))"
else:
    print "No channel selected!"
    sys.exit(1)

weight = "(100.*mcweight/testing_frac)*((genweight<0)*(-1)+(genweight>0)*1)"
selection2j1t = "(Reconstructed_1__nSelectedJet==2)*(Reconstructed_1__nSelectedBJetTight==1)"
selection2j0t = "(Reconstructed_1__nSelectedJet==2)*(Reconstructed_1__nSelectedBJetTight==0)"
#selection3j0t = "(Reconstructed_1__nSelectedJet==3)*(Reconstructed_1__nSelectedBJetTight==0)"
selection3j1t = "(Reconstructed_1__nSelectedJet==3)*(Reconstructed_1__nSelectedBJetTight==1)"
#selection3j2t = "(Reconstructed_1__nSelectedJet==3)*(Reconstructed_1__nSelectedBJetTight==2)"
jetSelection = "(1.0*"+selection2j1t+"+"+args.mix+"*"+selection2j0t+"+"+args.mix+"*"+selection3j1t+")"

factory.SetSignalWeightExpression(leptonSelection+"*"+weight+"*"+jetSelection)
factory.SetBackgroundWeightExpression(leptonSelection+"*"+weight+"*"+jetSelection)

factory.AddVariable("SingleTop_1__Top_1__Mass")
factory.AddVariable("SingleTop_1__C")
factory.AddVariable("SingleTop_1__cosTheta_wH")
factory.AddVariable("SingleTop_1__Dijet_1__dR")
#factory.AddVariable("SingleTop_1__fox_1_logpz")
factory.AddVariable("SingleTop_1__TightLepton_BJet_dEta")
factory.AddVariable("Reconstructed_1__MET_1__Pt")
#factory.AddVariable("SingleTop_1__Shat_1__Mass")
#factory.AddVariable("SingleTop_1__Shat_1__Pt") #mismodeled
#factory.AddVariable("SingleTop_1__Dijet_1__Pt")


#factory.AddVariable("SingleTop_1__Dijet_1__Mass")
#factory.AddVariable("SingleTop_1__fox_2_psum")
#factory.AddVariable("SingleTop_1__fox_3_logpz")
#factory.AddVariable("SingleTop_1__absLEta")
#factory.AddVariable("Reconstructed_1__MET_1__Pt")

#factory.AddVariable("SingleTop_1__Shat_1__Pt")
#factory.AddVariable("SingleTop_1__sphericity")


#factory.AddVariable("Reconstructed_1__TightMuon_1__Pt")
#factory.AddVariable("SingleTop_1__mtw_beforePz")
#factory.AddVariable("SingleTop_1__Top_1__Mass")
#factory.AddVariable("SingleTop_1__BJet_TightMuon_dEta")

#factory.AddVariable("SingleTop_1__TightMuon_MET_dPhi")
#factory.AddVariable("SingleTop_1__LightJet_1__Pt")
#factory.AddVariable("SingleTop_1__absLEta")

#factory.AddVariable("SingleTop_1__Shat_1__Mass")
#factory.AddVariable("Reconstructed_1__fox_1_eta")
#factory.AddVariable("Reconstructed_1__fox_1_logpz")
#factory.AddVariable("Reconstructed_1__isotropy")
#factory.AddVariable("Reconstructed_1__nSelectedLooseJet")
#factory.AddVariable("SingleTop_1__LightJet_1__n90")
#factory.AddVariable("SingleTop_1__LightJet_1__pfCombinedInclusiveSecondaryVertexV2BJetTags_binned")
#


cut = ROOT.TCut("((formva==1)&&"+leptonSelection+"&&("+selection2j1t+"||"+selection2j0t+"||"+selection3j1t+"))")
factory.PrepareTrainingAndTestTree(cut,"")

#factory.BookMethod(ROOT.TMVA.Types.kBDT,"BDT_adaboost04_minnode010_maxvar3_ntree1000_invboost","BoostType=AdaBoost:AdaBoostBeta=0.4:PruneStrength=7:SeparationType=CrossEntropy:MaxDepth=3:nCuts=40:NodePurityLimit=0.5:NTrees=1000:MinNodeSize=1%:NegWeightTreatment=InverseBoostNegWeights")
#factory.BookMethod(ROOT.TMVA.Types.kBDT,"BDT_gradboost04_minnode010_maxvar3_ntree1000_pray","BoostType=Grad:Shrinkage=0.4:PruneStrength=7:SeparationType=CrossEntropy:MaxDepth=3:nCuts=40:NodePurityLimit=0.5:NTrees=1000:MinNodeSize=1%:NegWeightTreatment=Pray")

factory.BookMethod(ROOT.TMVA.Types.kBDT,args.name,args.cfg)

factory.TrainAllMethods()
factory.TestAllMethods()
factory.EvaluateAllMethods()














