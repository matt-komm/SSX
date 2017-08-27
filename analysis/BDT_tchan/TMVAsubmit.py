from CP3SlurmUtils.Configuration import Configuration
import os
import re

config = Configuration()

#--------------------------------------------------------------------------------
# 1. SLURM sbatch command options
#--------------------------------------------------------------------------------

config.sbatch_partition = 'cp3'
config.sbatch_qos = 'cp3'
config.sbatch_workdir = '/nfs/user/mkomm/SSX13/BDT_tchan'
config.sbatch_time = '0-10:00'
config.sbatch_mem = '8000'

config.sbatch_output = '/dev/null'
config.sbatch_error = '/dev/null'

config.sbatch_additionalOptions = ["--job-name=BDTtch"]


config.inputSandboxContent = []
config.inputSandboxDir = config.sbatch_workdir
config.inputSandboxFilename = ''

config.batchScriptsDir = config.sbatch_workdir

config.batchScriptsFilename = 'runJob.sh'

config.stageout = False

config.stageoutFiles = []#['*.root','weights/*.*']

config.writeLogsOnWN = True

config.separateStdoutStderrLogs = True

config.stdoutFilename = "log${SLURM_ARRAY_TASK_ID}.out"
config.stderrFilename = "log${SLURM_ARRAY_TASK_ID}.err"
config.stageoutLogs = True

config.stageoutLogsDir = config.sbatch_workdir + '/log'

config.useJobArray = True

config.numJobs = None

config.inputParamsNames = ['TMVA_SCRIPTFILE','TMVA_NAME','TMVA_CH','TMVA_CFG','TMVA_MIX','TMVA_QCDMIX']

scriptfile = '$HOME/SSX/analysis/BDT_tchan/TMVATraining.py'

config.inputParams = []
'''
config.inputParams = [
    [scriptfile,'BDTmu_tch_adaboost04_minnode010_maxvar3_nCuts50_ntree600_invboost','mu','BoostType=AdaBoost:AdaBoostBeta=0.4:SeparationType=CrossEntropy:MaxDepth=3:nCuts=50:NodePurityLimit=0.5:NTrees=600:MinNodeSize=1.0%:NegWeightTreatment=InverseBoostNegWeights:DoBoostMonitor=True'],
    [scriptfile,'BDTmu_tch_adaboost04_minnode005_maxvar3_nCuts50_ntree600_invboost','mu','BoostType=AdaBoost:AdaBoostBeta=0.4:SeparationType=CrossEntropy:MaxDepth=3:nCuts=50:NodePurityLimit=0.5:NTrees=600:MinNodeSize=0.5%:NegWeightTreatment=InverseBoostNegWeights:DoBoostMonitor=True'],
    [scriptfile,'BDTmu_tch_adaboost04_minnode005_maxvar5_nCuts50_ntree600_invboost','mu','BoostType=AdaBoost:AdaBoostBeta=0.4:SeparationType=CrossEntropy:MaxDepth=5:nCuts=50:NodePurityLimit=0.5:NTrees=600:MinNodeSize=0.5%:NegWeightTreatment=InverseBoostNegWeights:DoBoostMonitor=True'],
    [scriptfile,'BDTmu_tch_adaboost04_minnode001_maxvar5_nCuts50_ntree600_invboost','mu','BoostType=AdaBoost:AdaBoostBeta=0.4:SeparationType=CrossEntropy:MaxDepth=5:nCuts=50:NodePurityLimit=0.5:NTrees=600:MinNodeSize=0.1%:NegWeightTreatment=InverseBoostNegWeights:DoBoostMonitor=True'],
    [scriptfile,'BDTmu_tch_adaboost04_minnode001_maxvar5_nCuts100_ntree600_invboost','mu','BoostType=AdaBoost:AdaBoostBeta=0.4:SeparationType=CrossEntropy:MaxDepth=5:nCuts=100:NodePurityLimit=0.5:NTrees=600:MinNodeSize=0.1%:NegWeightTreatment=InverseBoostNegWeights:DoBoostMonitor=True'],

    [scriptfile,'BDTele_tch_adaboost04_minnode010_maxvar3_nCuts50_ntree600_invboost','ele','BoostType=AdaBoost:AdaBoostBeta=0.4:SeparationType=CrossEntropy:MaxDepth=3:nCuts=50:NodePurityLimit=0.5:NTrees=600:MinNodeSize=1.0%:NegWeightTreatment=InverseBoostNegWeights:DoBoostMonitor=True'],
    [scriptfile,'BDTele_tch_adaboost04_minnode005_maxvar3_nCuts50_ntree600_invboost','ele','BoostType=AdaBoost:AdaBoostBeta=0.4:SeparationType=CrossEntropy:MaxDepth=3:nCuts=50:NodePurityLimit=0.5:NTrees=600:MinNodeSize=0.5%:NegWeightTreatment=InverseBoostNegWeights:DoBoostMonitor=True'],
    [scriptfile,'BDTele_tch_adaboost04_minnode005_maxvar5_nCuts50_ntree600_invboost','ele','BoostType=AdaBoost:AdaBoostBeta=0.4:SeparationType=CrossEntropy:MaxDepth=5:nCuts=50:NodePurityLimit=0.5:NTrees=600:MinNodeSize=0.5%:NegWeightTreatment=InverseBoostNegWeights:DoBoostMonitor=True'],
    [scriptfile,'BDTele_tch_adaboost04_minnode001_maxvar5_nCuts50_ntree600_invboost','ele','BoostType=AdaBoost:AdaBoostBeta=0.4:SeparationType=CrossEntropy:MaxDepth=5:nCuts=50:NodePurityLimit=0.5:NTrees=600:MinNodeSize=0.1%:NegWeightTreatment=InverseBoostNegWeights:DoBoostMonitor=True'],
    [scriptfile,'BDTele_tch_adaboost04_minnode001_maxvar5_nCuts100_ntree600_invboost','ele','BoostType=AdaBoost:AdaBoostBeta=0.4:SeparationType=CrossEntropy:MaxDepth=5:nCuts=100:NodePurityLimit=0.5:NTrees=600:MinNodeSize=0.1%:NegWeightTreatment=InverseBoostNegWeights:DoBoostMonitor=True'],
]
'''

for boost in [0.2,0.4]:
    for minNode in [0.05,0.2,1]:#,1]:
        for maxVar in [3]:#,4]:
            for nCuts in [50]:
                for nTrees in [1000]:
                    for mix in [0.05]:
                        for qcdmix in [0.005]:
                            '''
                            config.inputParams.append([
                                scriptfile,
                                'BDTmu_tch_adaboost%03.0f_minnode%04.0f_maxvar%i_nCuts%i_ntree800_invboost'%(boost*100.,minNode*100.,maxVar,nCuts),
                                'mu',
                                'BoostType=AdaBoost:AdaBoostBeta=%4.2f:'%boost+
                                'SeparationType=CrossEntropy:MaxDepth=%i:'%maxVar+
                                'nCuts=%i:NodePurityLimit=0.5:'%nCuts+
                                'NTrees=800:MinNodeSize=%5.3f%%:'%minNode+
                                'NegWeightTreatment=InverseBoostNegWeights:DoBoostMonitor=True'
                            ])
                            config.inputParams.append([
                                scriptfile,
                                'BDTele_tch_adaboost%03.0f_minnode%04.0f_maxvar%i_nCuts%i_ntree800_invboost'%(boost*100.,minNode*100.,maxVar,nCuts),
                                'ele',
                                'BoostType=AdaBoost:AdaBoostBeta=%4.2f:'%boost+
                                'SeparationType=CrossEntropy:MaxDepth=%i:'%maxVar+
                                'nCuts=%i:NodePurityLimit=0.5:'%nCuts+
                                'NTrees=800:MinNodeSize=%5.3f%%:'%minNode+
                                'NegWeightTreatment=InverseBoostNegWeights:DoBoostMonitor=True'
                            ])
                            '''
                            config.inputParams.append([
                                scriptfile,
                                'BDTcomb_tch_adaboost%03.0f_minnode%04.0f_maxvar%i_nCuts%i_ntree%03i_mix%05i_qcdmix%05i_invboost'%(boost*100.,minNode*100.,maxVar,nCuts,nTrees,mix*10**5,qcdmix*10**5),
                                'comb',
                                'BoostType=AdaBoost:AdaBoostBeta=%4.2f:'%boost+
                                'SeparationType=CrossEntropy:MaxDepth=%i:'%maxVar+
                                'nCuts=%i:NodePurityLimit=0.5:'%nCuts+
                                'NTrees=%03i:'%nTrees+
                                'MinNodeSize=%5.3f%%:'%minNode+
                                'NegWeightTreatment=InverseBoostNegWeights:DoBoostMonitor=True:PruneMethod=CostComplexity:PruneStrength=7',
                                mix,
                                qcdmix
                            ])
                            
                            '''
                            config.inputParams.append([
                                scriptfile,
                                'BDTmu_tch_gradboost%03.0f_minnode%04.0f_maxvar%i_nCuts%i_ntree800_invboost'%(boost*100.,minNode*100.,maxVar,nCuts),
                                'mu',
                                'BoostType=Grad:Shrinkage=%4.2f:'%boost+
                                'SeparationType=CrossEntropy:MaxDepth=%i:'%maxVar+
                                'nCuts=%i:NodePurityLimit=0.5:'%nCuts+
                                'NTrees=800:MinNodeSize=%5.3f%%:'%minNode+
                                'NegWeightTreatment=Pray:DoBoostMonitor=True'
                            ])
                            config.inputParams.append([
                                scriptfile,
                                'BDTele_tch_gradboost%03.0f_minnode%04.0f_maxvar%i_nCuts%i_ntree800_invboost'%(boost*100.,minNode*100.,maxVar,nCuts),
                                'ele',
                                'BoostType=Grad:Shrinkage=%4.2f:'%boost+
                                'SeparationType=CrossEntropy:MaxDepth=%i:'%maxVar+
                                'nCuts=%i:NodePurityLimit=0.5:'%nCuts+
                                'NTrees=800:MinNodeSize=%5.3f%%:'%minNode+
                                'NegWeightTreatment=Pray:DoBoostMonitor=True'
                            ])
                            '''



config.payload = \
"""
echo "------------ start -----------"
echo "Started Job at "`date`
number=$RANDOM
let "number %= 3"
echo "sleeping for ... "$number
sleep $number
echo "HOSTNAME: $HOSTNAME"
echo "HOME: $HOME"
tries=1
until [ "$tries" -gt "20" ] || (ls > /dev/null && ls /storage/data/cms/store/user/mkomm > /dev/null && ls /nfs/user/mkomm > /dev/null && ls $HOME > /dev/null && ls /cvmfs/cp3.uclouvain.be/ > /dev/null)
do
  sleep 10s
  rndsleep=$RANDOM
  let "rndsleep %= 30"
  sleep $rndsleep
  echo "Try again "$tries"/20 "`date`
  let "tries++"
done
if [ "$tries" -gt "20" ]
then
    echo "Mounting problem NOT solved!!! Killing job ..." >&2
    exit 1
else
    echo "Everything seems to be properly mounted."
fi

echo "------------ sourcing -----------"
source $HOME/.bashrc
echo "root: `which root`"
echo "gcc: `which gcc` (version `gcc -dumpversion`)" 
echo "python: `which python`"
cd $HOME/SSX
source setVars.sh
echo "------------ scratch dir -----------"
echo "scratch dir: $LOCALSCRATCH"
cd $LOCALSCRATCH
echo "------------ env -----------"
env | sort
echo "------------ dir -----------"
pwd
ls -lh
echo "------------ job -----------"
echo "executing: python "$TMVA_SCRIPTFILE --name $TMVA_NAME --ch $TMVA_CH --cfg $TMVA_CFG --mix $TMVA_MIX --qcdmix $TMVA_QCDMIX
python $TMVA_SCRIPTFILE --name $TMVA_NAME --ch $TMVA_CH --cfg $TMVA_CFG --mix $TMVA_MIX --qcdmix $TMVA_QCDMIX > $TMVA_NAME".log"
echo "done executing: python "$TMVA_SCRIPTFILE --name $TMVA_NAME --ch $TMVA_CH --cfg $TMVA_CFG --mix $TMVA_MIX --qcdmix $TMVA_QCDMIX
echo "------------ dir -----------"
pwd
for f in `find . | sort`
    do
    echo `du -bh $f`
    done
echo "------------ copy output -----------"
cp -v $LOCALSCRATCH/BDT*.log $SLURM_SUBMIT_DIR/weights/.
cp -v $LOCALSCRATCH/*.root $SLURM_SUBMIT_DIR/weights/.
cp -v $LOCALSCRATCH/weights/* $SLURM_SUBMIT_DIR/weights/.
echo "------------ finished -----------"
"""
