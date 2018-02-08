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
config.sbatch_time = '0-2:00'
config.sbatch_mem = '1000'

config.sbatch_output = '/dev/null'
config.sbatch_error = '/dev/null'

config.sbatch_additionalOptions = ["--job-name=responsePDFHists"]


config.inputSandboxContent = []
config.inputSandboxDir = config.sbatch_workdir
config.inputSandboxFilename = ''

config.batchScriptsDir = config.sbatch_workdir

config.batchScriptsFilename = 'makeResponsePDFHistograms.sh'

config.stageout = False

config.stageoutFiles = []#['*.root','weights/*.*']

config.writeLogsOnWN = True

config.separateStdoutStderrLogs = True

config.stdoutFilename = "log_responsePDFHists${SLURM_ARRAY_TASK_ID}.out"
config.stderrFilename = "log_responsePDFHists${SLURM_ARRAY_TASK_ID}.err"
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
    
    "setup/TopPtParticle":{"ele":5,"mu":5},
    "setup/TopYParticle":{"ele":5,"mu":5},
    "setup/LeptonPtParticle":{"ele":4,"mu":5},
    "setup/LeptonEtaParticle":{"ele":3,"mu":5},
    "setup/TopCosParticle":{"ele":6,"mu":6},
    "setup/WCosParticle":{"ele":6,"mu":6},
    "setup/WPtParticle":{"ele":5,"mu":5},
}


for channel in ["mu","ele"]:
    for charge in [-1,0,1]:
        for unfoldingSetup in sorted(setupBins.keys()):       
            
            for lheWeight in range(2001,2103):
        
                #sys
                config.inputParams.append([
                    "-m tasks/makeResponseHistograms -m "+unfoldingSetup+" -m systematics/lheWeight -c lheWeight:"+str(lheWeight)+" -c channel:"+channel+" -c charge:"+str(charge)
                ])
            
            
                
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
