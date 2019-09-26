from CP3SlurmUtils.Configuration import Configuration
import os
import re

config = Configuration()

#--------------------------------------------------------------------------------
# 1. SLURM sbatch command options
#--------------------------------------------------------------------------------

config.sbatch_partition = 'cp3'
config.sbatch_qos = 'cp3'
config.sbatch_workdir = '/home/ucl/cp3/mkomm/SSX/analysis/unfolding/jobs'
config.sbatch_time = '0-6:00'
config.sbatch_mem = '1000'

config.sbatch_output = '/dev/null'
config.sbatch_error = '/dev/null'

config.sbatch_additionalOptions = ["--job-name=fitHists"]


config.inputSandboxContent = []
config.inputSandboxDir = config.sbatch_workdir
config.inputSandboxFilename = ''

config.batchScriptsDir = config.sbatch_workdir

config.batchScriptsFilename = 'makeFitHistograms.sh'

config.stageout = False

config.stageoutFiles = []#['*.root','weights/*.*']

config.writeLogsOnWN = True

config.separateStdoutStderrLogs = True

config.stdoutFilename = "log_fitHists${SLURM_ARRAY_TASK_ID}.out"
config.stderrFilename = "log_fitHists${SLURM_ARRAY_TASK_ID}.err"
config.stageoutLogs = True

config.stageoutLogsDir = config.sbatch_workdir + '/log'

config.useJobArray = True

config.numJobs = None


config.inputParamsNames = ['ARGS']
scriptfile = '$HOME/SSX/analysis/unfolding/driver.py'

config.inputParams = []

setupBins = {
    "setup/TopPtParton":{"ele":5,"mu":5},
    "setup/TopYParton":{"ele":5,"mu":5},
    "setup/LeptonPtParton":{"ele":4,"mu":5},
    "setup/LeptonEtaParton":{"ele":3,"mu":5},
    "setup/TopCosParton":{"ele":6,"mu":6},
    "setup/WCosParton":{"ele":6,"mu":6},
    "setup/WPtParton":{"ele":5,"mu":5},
}


for channel in ["mu","ele"]:
        '''
        #nominal/inclusive
        config.inputParams.append([
            "-m tasks/makeFitHistograms -c channel:"+channel+" -c bin:-1"
        ])
        
        #for 2j0t wjets
        config.inputParams.append([
            "-m setup/Wjets -m tasks/makeFitHistograms -c channel:"+channel+" -c bin:-1"
        ])
        
        for unfoldingSetup in sorted(setupBins.keys()):
            for ibin in range(setupBins[unfoldingSetup][channel]):
                config.inputParams.append([
                    "-m tasks/makeFitHistograms -m "+unfoldingSetup+" -c channel:"+channel+" -c bin:"+str(ibin)
                ])
        
        for systModule in [
            "systematics/twDown",
            "systematics/twUp",
            "systematics/dyDown",
            "systematics/dyUp",
            "systematics/muEffDown",
            "systematics/muEffUp",
            "systematics/eleEffDown",
            "systematics/eleEffUp",
            "systematics/btagDown",
            "systematics/btagUp",
            "systematics/ltagDown",
            "systematics/ltagUp",
            "systematics/enDown",
            "systematics/enUp",
            "systematics/resDown",
            "systematics/resUp",
            "systematics/puDown",
            "systematics/puUp",
            "systematics/uncDown",
            "systematics/uncUp",
            "systematics/muMultiDown",
            "systematics/muMultiUp",
            "systematics/eleMultiIsoDown",
            "systematics/eleMultiIsoUp",
            "systematics/eleMultiVetoDown",
            "systematics/eleMultiVetoUp",
            
            "systematics/topMassDown",
            "systematics/topMassUp",
            
            "systematics/ttbarPtUp",
            "systematics/ttbarPtDown",
            
            "systematics/pdfUp",
            "systematics/pdfDown",
            
            "systematics/tchanHdampPSUp",
            "systematics/tchanHdampPSDown",
            
            "systematics/ttbarHdampPSDown",
            "systematics/ttbarHdampPSUp",
            "systematics/ttbarScaleISRPSDown",
            "systematics/ttbarScaleISRPSUp",
            "systematics/ttbarScaleFSRPSDown",
            "systematics/ttbarScaleFSRPSUp",
            "systematics/ttbarUEDown",
            "systematics/ttbarUEUp",
            
            "systematics/tchanHdampPSDown",
            "systematics/tchanHdampPSUp",
            "systematics/tchanScalePSDown",
            "systematics/tchanScalePSUp",
            
            #"systematics/tchanScaleTmpl -c qscale:ND",
            #"systematics/tchanScaleTmpl -c qscale:NU",
            #"systematics/tchanScaleTmpl -c qscale:DN",
            #"systematics/tchanScaleTmpl -c qscale:UN",
            "systematics/tchanScaleTmpl -c qscale:Up",
            "systematics/tchanScaleTmpl -c qscale:Down",
            
            #"systematics/ttbarScaleTmpl -c qscale:ND",
            #"systematics/ttbarScaleTmpl -c qscale:NU",
            #"systematics/ttbarScaleTmpl -c qscale:DN",
            #"systematics/ttbarScaleTmpl -c qscale:UN",
            "systematics/ttbarScaleTmpl -c qscale:Up",
            "systematics/ttbarScaleTmpl -c qscale:Down",
            
            #"systematics/wjetsScaleTmpl -c qscale:ND",
            #"systematics/wjetsScaleTmpl -c qscale:NU",
            #"systematics/wjetsScaleTmpl -c qscale:DN",
            #"systematics/wjetsScaleTmpl -c qscale:UN",
            "systematics/wjetsScaleTmpl -c qscale:Up",
            "systematics/wjetsScaleTmpl -c qscale:Down",
        ]:
        '''
        for systModule in [
            "systematics/tchanGluonMove",
            "systematics/tchanErdOn",
            "systematics/tchanGluonMoveErdOn",
            
            "systematics/ttbarGluonMove",
            "systematics/ttbarErdOn",
            "systematics/ttbarGluonMoveErdOn",
            
            "systematics/bfracCentral",
            "systematics/bfracUp",
            "systematics/bfracDown",
            "systematics/bfracPeterson",
        ]:
            #'''
            #sys/inclusive
            config.inputParams.append([
                "-m tasks/makeFitHistograms -m "+systModule+" -c channel:"+channel+" -c bin:-1"
            ])
            #'''
            #for 2j0t wjets
            config.inputParams.append([
                "-m setup/Wjets -m tasks/makeFitHistograms -m "+systModule+" -c channel:"+channel+" -c bin:-1"
            ])
            #'''
            #sys/binned per obs
            for unfoldingSetup in sorted(setupBins.keys()):
                for ibin in range(setupBins[unfoldingSetup][channel]):
                    config.inputParams.append([
                        "-m tasks/makeFitHistograms -m "+unfoldingSetup+" -m "+systModule+" -c channel:"+channel+" -c bin:"+str(ibin)
                    ])
            #'''
            
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
cd $HOME/SSX/analysis/unfolding
echo "------------ env -----------"
env | sort
echo "------------ dir -----------"
pwd
ls -lh
echo "------------ job -----------"
unset DISPLAY
echo "executing: python "driver.py $ARGS
python driver.py $ARGS
echo "done executing: python "driver.py $ARGS
"""
