from CRABAPI.RawCommand import crabCommand
from httplib import HTTPException
from CRABClient.UserUtilities import config

from optparse import OptionParser
import os

def submit(config,*args,**kwargs):
    try:
        crabCommand('submit', config = config)
    except HTTPException, hte:
        print hte.headers
        
def status(task,*args,**kwargs):
    try:
        crabCommand('status', task,'--verboseErrors')
    except HTTPException, hte:
        print hte.headers
        
def kill(task,*args,**kwargs):
    try:
        crabCommand('kill', task)
    except HTTPException, hte:
        print hte.headers

def getlog(task,*args,**kwargs):
    try:
        crabCommand('getlog', task)
    except HTTPException, hte:
        print hte.headers        

if __name__=="__main__":

    parser = OptionParser()
    parser.add_option("--datasetID", dest="datasetID",
                      help="dataset")

    (options, args) = parser.parse_args()

    config = config()

    config.General.requestName = 'SSX'
    config.General.transferOutputs = True
    config.General.transferLogs = False

    config.JobType.pluginName = 'Analysis'
    config.JobType.psetName = 'EDM2PXLIO/analysis16.py'
    config.JobType.pyCfgParams = []
    config.JobType.outputFiles = ["output.pxlio","info.root"]
    #config.JobType.outputFiles = ["output.pxlio"]
    config.JobType.inputFiles=[
        #"Spring16_25nsV3_DATA.db",
        #"Spring16_25nsV3_MC.db"
        #"Summer15_50nsV4_UncertaintySources_AK4PFchs.txt"
    ]
    config.JobType.maxJobRuntimeMin=360 #=6h

    config.Data.inputDBS = 'global'
    config.Data.splitting = 'FileBased'
    #config.Data.splitting = 'LumiBased'
    #config.Data.lumiMask = '/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions16/13TeV/Cert_271036-276811_13TeV_PromptReco_Collisions16_JSON_NoL1T.txt' #ICHEP
    #config.Data.runRange='254833-254833'
    config.Data.unitsPerJob = 4
    #config.Data.ignoreLocality = True #use to circumvent crab/dbs bug with open data blocks (while its being writing)
    config.Data.allowNonValidInputDataset = True #allows to use nonvalid sets


    config.Data.publication = False



    config.Site.storageSite = "T2_BE_UCL"
    '''
    config.Site.whitelist = [
        'T2_BE_UCL','T2_BE_IIHE' #BE
        'T2_DE_DESY', #DE
        'T2_CH_CERN',
        'T2_IT_Legnaro','T2_IT_Rome', #IT
        'T2_ES_CIEMAT', #ES
        'T2_US_UCSD','T2_US_Wisconsin', #US
    ]
    '''

    mc80Xv2 = [
        '/ST_t-channel_top_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM',
        '/ST_t-channel_antitop_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM',
        
        '/ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v2/MINIAODSIM',
        '/ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM',
        
        '/TT_TuneCUETP8M1_13TeV-powheg-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext4-v1/MINIAODSIM',
        
        '/WJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM',
        '/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM',
    
        '/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM',
        '/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM',
        
        '/QCD_Pt-20toInf_MuEnrichedPt15_TuneCUETP8M1_13TeV_pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM',   
    ]
    
    data80X = [
        '/SingleMuon/Run2016B-PromptReco-v2/MINIAOD',
        '/SingleMuon/Run2016C-PromptReco-v2/MINIAOD',
        '/SingleMuon/Run2016D-PromptReco-v2/MINIAOD',
        '/SingleMuon/Run2016E-PromptReco-v2/MINIAOD'
    ]
    
    dataset=mc80Xv2[int(args[0])]
    #dataset=data80X[int(args[0])]
    processName = dataset.split("/")[1]
    #processName = dataset.split("/")[1]+"_"+dataset.split("/")[2]
    if dataset.split("/")[2].find("_ext")!=-1:
        processName+="_ext"

    jobName = processName+'_v161117'
    
    print "submitting... ",jobName
    #status(os.path.join(os.getcwd(),"crab",jobName,"crab_"+config.General.requestName))
    
    if not os.path.isdir(os.path.join(os.getcwd(),"crab",jobName)):
    
        config.General.workArea = "crab/"+jobName
        config.Data.inputDataset=dataset
        #config.JobType.pyCfgParams=['processName='+processName,'noGen=True','noLHE=True']
        config.JobType.pyCfgParams=['processName='+processName,'addPL=True','noLHE=False','noFilter=True']
        #config.JobType.pyCfgParams=['processName='+processName,'isData=True','onlyFiltered=True']
        config.Data.outLFNDirBase='/store/user/mkomm/'+config.General.requestName+"/"+jobName
        submit(config)
    else:
        print "job folder already exists!"
    

