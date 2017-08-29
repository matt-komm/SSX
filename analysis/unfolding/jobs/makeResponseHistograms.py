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

config.sbatch_additionalOptions = ["--job-name=responseHists"]


config.inputSandboxContent = []
config.inputSandboxDir = config.sbatch_workdir
config.inputSandboxFilename = ''

config.batchScriptsDir = config.sbatch_workdir

config.batchScriptsFilename = 'makeResponseHistograms.sh'

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


config.inputParamsNames = ['ARGS']
scriptfile = '$HOME/SSX/analysis/unfolding/driver.py'

config.inputParams = []


for channel in ["mu","ele"]:
    for charge in [-1,0,1]:
        for unfoldingSetup in ["setup/TopPtParton","setup/TopYParton","setup/TopCosParton"]:
            config.inputParams.append([
                "-m tasks/makeResponseHistograms -m "+unfoldingSetup+" -c channel:"+channel+" -c charge:"+str(charge)
            ])
            
            for systModule in [
                "systematics/btagDown",
                "systematics/btagUp",
                "systematics/ltagDown",
                "systematics/ltagUp",
                "systematics/enDown",
                "systematics/enUp",
                "systematics/puDown",
                "systematics/puUp",
            ]:
        
                #sys
                config.inputParams.append([
                    "-m tasks/makeResponseHistograms -m "+systModule+" -m "+unfoldingSetup+" -c channel:"+channel+" -c charge:"+str(charge)
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
