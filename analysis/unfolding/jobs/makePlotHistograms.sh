#!/bin/bash
#
#SBATCH --partition=cp3
#SBATCH --qos=cp3
#SBATCH --workdir=/home/ucl/cp3/mkomm/SSX/analysis/unfolding/jobs
#SBATCH --time=1-16:00
#SBATCH --mem-per-cpu=1000
#SBATCH --array=1-106
#SBATCH --output=/dev/null
#SBATCH --error=/dev/null
#SBATCH --job-name=plotHists

#==================================================================================

# This variable keeps the exit code with which the batch script will exit.
exitCode=0
exitCodeMeaning=""

function updateExitCode() {
    [[ ${exitCode} -ne 0 ]] || exitCode=${1}
}

#==================================================================================
# Change directory to the job's scratch directory
#==================================================================================

if [[ -d "${LOCALSCRATCH}" ]]
then
    cd "${LOCALSCRATCH}" || updateExitCode 100
else
    echo "Local scratch directory does not exist."
    updateExitCode 100
fi

#==================================================================================
# Redirect stdout and stderr to local file(s)
#==================================================================================

writeLogsOnWN=true
separateStdoutStderrLogs=true
stdoutFilename="log_plotHists${SLURM_ARRAY_TASK_ID}.out"
stderrFilename="log_plotHists${SLURM_ARRAY_TASK_ID}.err"

if [[ "${writeLogsOnWN}" == "true" ]]
then
    # Redirect stdout and stderr to local file(s).
    if [[ "${separateStdoutStderrLogs}" == "true" ]]
    then
        exec 1> "${stdoutFilename}" 2> "${stderrFilename}"
    else
        exec 1> "${stdoutFilename}" 2>&1
    fi
fi

echo "======== Starting job (`date`) ========"
echo "Job id: ${SLURM_JOB_ID}"
echo "List of nodes allocated to the job: ${SLURM_JOB_NODELIST}"
echo "Batch node: ${SLURMD_NODENAME}"
echo "Working directory: `pwd`"

#==================================================================================
# Read the job input arguments (if any) and run the payload
#==================================================================================

if [[ ${exitCode} -eq 0 ]]
then
    echo "==== Starting read of input parameters for job's payload (`date`) ===="
    inputParams=(
    "-m tasks/makePlotHistograms -c channel:mu -c bin:-1"
    "-m tasks/makePlotHistograms -m systematics/twDown -c channel:mu -c bin:-1"
    "-m tasks/makePlotHistograms -m systematics/twUp -c channel:mu -c bin:-1"
    "-m tasks/makePlotHistograms -m systematics/dyDown -c channel:mu -c bin:-1"
    "-m tasks/makePlotHistograms -m systematics/dyUp -c channel:mu -c bin:-1"
    "-m tasks/makePlotHistograms -m systematics/muEffDown -c channel:mu -c bin:-1"
    "-m tasks/makePlotHistograms -m systematics/muEffUp -c channel:mu -c bin:-1"
    "-m tasks/makePlotHistograms -m systematics/eleEffDown -c channel:mu -c bin:-1"
    "-m tasks/makePlotHistograms -m systematics/eleEffUp -c channel:mu -c bin:-1"
    "-m tasks/makePlotHistograms -m systematics/btagDown -c channel:mu -c bin:-1"
    "-m tasks/makePlotHistograms -m systematics/btagUp -c channel:mu -c bin:-1"
    "-m tasks/makePlotHistograms -m systematics/ltagDown -c channel:mu -c bin:-1"
    "-m tasks/makePlotHistograms -m systematics/ltagUp -c channel:mu -c bin:-1"
    "-m tasks/makePlotHistograms -m systematics/enDown -c channel:mu -c bin:-1"
    "-m tasks/makePlotHistograms -m systematics/enUp -c channel:mu -c bin:-1"
    "-m tasks/makePlotHistograms -m systematics/resDown -c channel:mu -c bin:-1"
    "-m tasks/makePlotHistograms -m systematics/resUp -c channel:mu -c bin:-1"
    "-m tasks/makePlotHistograms -m systematics/puDown -c channel:mu -c bin:-1"
    "-m tasks/makePlotHistograms -m systematics/puUp -c channel:mu -c bin:-1"
    "-m tasks/makePlotHistograms -m systematics/uncDown -c channel:mu -c bin:-1"
    "-m tasks/makePlotHistograms -m systematics/uncUp -c channel:mu -c bin:-1"
    "-m tasks/makePlotHistograms -m systematics/muMultiDown -c channel:mu -c bin:-1"
    "-m tasks/makePlotHistograms -m systematics/muMultiUp -c channel:mu -c bin:-1"
    "-m tasks/makePlotHistograms -m systematics/eleMultiIsoDown -c channel:mu -c bin:-1"
    "-m tasks/makePlotHistograms -m systematics/eleMultiIsoUp -c channel:mu -c bin:-1"
    "-m tasks/makePlotHistograms -m systematics/eleMultiVetoDown -c channel:mu -c bin:-1"
    "-m tasks/makePlotHistograms -m systematics/eleMultiVetoUp -c channel:mu -c bin:-1"
    "-m tasks/makePlotHistograms -m systematics/topMassDown -c channel:mu -c bin:-1"
    "-m tasks/makePlotHistograms -m systematics/topMassUp -c channel:mu -c bin:-1"
    "-m tasks/makePlotHistograms -m systematics/ttbarPtUp -c channel:mu -c bin:-1"
    "-m tasks/makePlotHistograms -m systematics/ttbarPtDown -c channel:mu -c bin:-1"
    "-m tasks/makePlotHistograms -m systematics/pdfUp -c channel:mu -c bin:-1"
    "-m tasks/makePlotHistograms -m systematics/pdfDown -c channel:mu -c bin:-1"
    "-m tasks/makePlotHistograms -m systematics/tchanHdampPSUp -c channel:mu -c bin:-1"
    "-m tasks/makePlotHistograms -m systematics/tchanHdampPSDown -c channel:mu -c bin:-1"
    "-m tasks/makePlotHistograms -m systematics/ttbarHdampPSDown -c channel:mu -c bin:-1"
    "-m tasks/makePlotHistograms -m systematics/ttbarHdampPSUp -c channel:mu -c bin:-1"
    "-m tasks/makePlotHistograms -m systematics/ttbarScaleISRPSDown -c channel:mu -c bin:-1"
    "-m tasks/makePlotHistograms -m systematics/ttbarScaleISRPSUp -c channel:mu -c bin:-1"
    "-m tasks/makePlotHistograms -m systematics/ttbarScaleFSRPSDown -c channel:mu -c bin:-1"
    "-m tasks/makePlotHistograms -m systematics/ttbarScaleFSRPSUp -c channel:mu -c bin:-1"
    "-m tasks/makePlotHistograms -m systematics/ttbarUEDown -c channel:mu -c bin:-1"
    "-m tasks/makePlotHistograms -m systematics/ttbarUEUp -c channel:mu -c bin:-1"
    "-m tasks/makePlotHistograms -m systematics/tchanHdampPSDown -c channel:mu -c bin:-1"
    "-m tasks/makePlotHistograms -m systematics/tchanHdampPSUp -c channel:mu -c bin:-1"
    "-m tasks/makePlotHistograms -m systematics/tchanScalePSDown -c channel:mu -c bin:-1"
    "-m tasks/makePlotHistograms -m systematics/tchanScalePSUp -c channel:mu -c bin:-1"
    "-m tasks/makePlotHistograms -m systematics/tchanScaleTmpl -c qscale:Up -c channel:mu -c bin:-1"
    "-m tasks/makePlotHistograms -m systematics/tchanScaleTmpl -c qscale:Down -c channel:mu -c bin:-1"
    "-m tasks/makePlotHistograms -m systematics/ttbarScaleTmpl -c qscale:Up -c channel:mu -c bin:-1"
    "-m tasks/makePlotHistograms -m systematics/ttbarScaleTmpl -c qscale:Down -c channel:mu -c bin:-1"
    "-m tasks/makePlotHistograms -m systematics/wjetsScaleTmpl -c qscale:Up -c channel:mu -c bin:-1"
    "-m tasks/makePlotHistograms -m systematics/wjetsScaleTmpl -c qscale:Down -c channel:mu -c bin:-1"
    "-m tasks/makePlotHistograms -c channel:ele -c bin:-1"
    "-m tasks/makePlotHistograms -m systematics/twDown -c channel:ele -c bin:-1"
    "-m tasks/makePlotHistograms -m systematics/twUp -c channel:ele -c bin:-1"
    "-m tasks/makePlotHistograms -m systematics/dyDown -c channel:ele -c bin:-1"
    "-m tasks/makePlotHistograms -m systematics/dyUp -c channel:ele -c bin:-1"
    "-m tasks/makePlotHistograms -m systematics/muEffDown -c channel:ele -c bin:-1"
    "-m tasks/makePlotHistograms -m systematics/muEffUp -c channel:ele -c bin:-1"
    "-m tasks/makePlotHistograms -m systematics/eleEffDown -c channel:ele -c bin:-1"
    "-m tasks/makePlotHistograms -m systematics/eleEffUp -c channel:ele -c bin:-1"
    "-m tasks/makePlotHistograms -m systematics/btagDown -c channel:ele -c bin:-1"
    "-m tasks/makePlotHistograms -m systematics/btagUp -c channel:ele -c bin:-1"
    "-m tasks/makePlotHistograms -m systematics/ltagDown -c channel:ele -c bin:-1"
    "-m tasks/makePlotHistograms -m systematics/ltagUp -c channel:ele -c bin:-1"
    "-m tasks/makePlotHistograms -m systematics/enDown -c channel:ele -c bin:-1"
    "-m tasks/makePlotHistograms -m systematics/enUp -c channel:ele -c bin:-1"
    "-m tasks/makePlotHistograms -m systematics/resDown -c channel:ele -c bin:-1"
    "-m tasks/makePlotHistograms -m systematics/resUp -c channel:ele -c bin:-1"
    "-m tasks/makePlotHistograms -m systematics/puDown -c channel:ele -c bin:-1"
    "-m tasks/makePlotHistograms -m systematics/puUp -c channel:ele -c bin:-1"
    "-m tasks/makePlotHistograms -m systematics/uncDown -c channel:ele -c bin:-1"
    "-m tasks/makePlotHistograms -m systematics/uncUp -c channel:ele -c bin:-1"
    "-m tasks/makePlotHistograms -m systematics/muMultiDown -c channel:ele -c bin:-1"
    "-m tasks/makePlotHistograms -m systematics/muMultiUp -c channel:ele -c bin:-1"
    "-m tasks/makePlotHistograms -m systematics/eleMultiIsoDown -c channel:ele -c bin:-1"
    "-m tasks/makePlotHistograms -m systematics/eleMultiIsoUp -c channel:ele -c bin:-1"
    "-m tasks/makePlotHistograms -m systematics/eleMultiVetoDown -c channel:ele -c bin:-1"
    "-m tasks/makePlotHistograms -m systematics/eleMultiVetoUp -c channel:ele -c bin:-1"
    "-m tasks/makePlotHistograms -m systematics/topMassDown -c channel:ele -c bin:-1"
    "-m tasks/makePlotHistograms -m systematics/topMassUp -c channel:ele -c bin:-1"
    "-m tasks/makePlotHistograms -m systematics/ttbarPtUp -c channel:ele -c bin:-1"
    "-m tasks/makePlotHistograms -m systematics/ttbarPtDown -c channel:ele -c bin:-1"
    "-m tasks/makePlotHistograms -m systematics/pdfUp -c channel:ele -c bin:-1"
    "-m tasks/makePlotHistograms -m systematics/pdfDown -c channel:ele -c bin:-1"
    "-m tasks/makePlotHistograms -m systematics/tchanHdampPSUp -c channel:ele -c bin:-1"
    "-m tasks/makePlotHistograms -m systematics/tchanHdampPSDown -c channel:ele -c bin:-1"
    "-m tasks/makePlotHistograms -m systematics/ttbarHdampPSDown -c channel:ele -c bin:-1"
    "-m tasks/makePlotHistograms -m systematics/ttbarHdampPSUp -c channel:ele -c bin:-1"
    "-m tasks/makePlotHistograms -m systematics/ttbarScaleISRPSDown -c channel:ele -c bin:-1"
    "-m tasks/makePlotHistograms -m systematics/ttbarScaleISRPSUp -c channel:ele -c bin:-1"
    "-m tasks/makePlotHistograms -m systematics/ttbarScaleFSRPSDown -c channel:ele -c bin:-1"
    "-m tasks/makePlotHistograms -m systematics/ttbarScaleFSRPSUp -c channel:ele -c bin:-1"
    "-m tasks/makePlotHistograms -m systematics/ttbarUEDown -c channel:ele -c bin:-1"
    "-m tasks/makePlotHistograms -m systematics/ttbarUEUp -c channel:ele -c bin:-1"
    "-m tasks/makePlotHistograms -m systematics/tchanHdampPSDown -c channel:ele -c bin:-1"
    "-m tasks/makePlotHistograms -m systematics/tchanHdampPSUp -c channel:ele -c bin:-1"
    "-m tasks/makePlotHistograms -m systematics/tchanScalePSDown -c channel:ele -c bin:-1"
    "-m tasks/makePlotHistograms -m systematics/tchanScalePSUp -c channel:ele -c bin:-1"
    "-m tasks/makePlotHistograms -m systematics/tchanScaleTmpl -c qscale:Up -c channel:ele -c bin:-1"
    "-m tasks/makePlotHistograms -m systematics/tchanScaleTmpl -c qscale:Down -c channel:ele -c bin:-1"
    "-m tasks/makePlotHistograms -m systematics/ttbarScaleTmpl -c qscale:Up -c channel:ele -c bin:-1"
    "-m tasks/makePlotHistograms -m systematics/ttbarScaleTmpl -c qscale:Down -c channel:ele -c bin:-1"
    "-m tasks/makePlotHistograms -m systematics/wjetsScaleTmpl -c qscale:Up -c channel:ele -c bin:-1"
    "-m tasks/makePlotHistograms -m systematics/wjetsScaleTmpl -c qscale:Down -c channel:ele -c bin:-1"
    )
    jobInputParams="${inputParams[${SLURM_ARRAY_TASK_ID}-1]}"
    export ARGS=`echo -e "${jobInputParams}" | awk -F' <sep> ' '{print $1}'`
    echo "ARGS = ${ARGS}"
    echo "==== Finished read of input parameters for job's payload (`date`) ===="
fi

if [[ ${exitCode} -eq 0 ]]
then
    echo "==== Starting execution of payload (`date`) ===="
    echo "------------------------- Begin payload output ------------------------"
    (
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
    )
    pec=$?
    echo "--------------------------- End payload output ------------------------"
    echo "Payload exit code: ${pec}"
    if [[ ${pec} -ne 0 ]]
    then
        if [[ ${pec} -ge 100 && ${pec} -le 113 ]]
        then
            echo "Payload exit code is in range 100-113, which is reserved for batch script non-payload errors." \
                 "Setting batch script exit code to 103."
            updateExitCode 103
        else
            if [[ ${pec} -lt 79 || ${pec} -gt 99 ]]
            then
                echo "Payload exit code is outside the recommended range for user-defined exit codes: 79-99." \
                     "This is not a problem, but if you are interested in defining/using exit codes for your payload that would not occur outside your payload," \
                     "please consider restricting to that range."
            fi
            updateExitCode ${pec}
            exitCodeMeaning="failure in user's payload"
        fi
    fi
    echo "==== Finished execution of payload (`date`) ===="
fi

#==================================================================================
# Stageout of user files
#==================================================================================

function stageout() {
    local filetype="${1}"
    local files=("")
    local dir=""
    if [[ "${filetype}" == "userfiles" ]]
    then
        files=("${stageoutFiles[@]}")
        dir="${stageoutDir}"
    elif [[ "${filetype}" == "logs" ]]
    then
        files=("${logFiles[@]}")
        dir="${stageoutLogsDir}"
    fi
    if [[ ! -n "${files}" ]]
    then
        echo "No files were specified for stageout."
        return 0
    fi
    if [[ ! -n "${dir}" ]]
    then
        echo "WARNING: The following files were requested for stageout:"
        echo "${files[@]}"
        echo "but no stageout directory was specified where to copy the files."
        echo "Will NOT stage out the files."
        return 0
    fi
    mkdir -p "${dir}"
    if [[ "${filetype}" == "logs" ]]
    then
        cp "${files[@]}" "${dir}/"
        return 0
    fi
    echo "Destination directory: ${dir}"
    if [[ ! -d "${dir}" ]]
    then
        echo "Destination directory does not exist and failed to create it."
        return 1
    fi
    function join_by() { local d=$1; shift; echo -n "$1"; shift; printf "%s" "${@/#/$d}"; }
    patterns=$(join_by "', '" "${files[@]}")
    echo "List of filename patterns to match against: '${patterns}'."
    if [[ ${SLURM_JOB_NUM_NODES} -gt 1 ]]
    then
        execFile="${dir}/stageout-OSB"
        echo "Will create executable file ${execFile} to be run via srun in order to stageout the user files from all allocated worker nodes." 
        if [[ -f "${execFile}" ]]
        then
            echo "A file ${execFile} already exists. Please remove it or rename it."
            return 1
        fi
        cat > "${execFile}" <<EOF
#!/bin/bash

function run_cmd() {
    cmd=("\${@}")
    ec=0
    tmplog=\${LOCALSCRATCH}/$(basename ${execFile}).err
    "\${cmd[@]}" 2> \${tmplog} >/dev/null || ec=1
    while read line
    do
        >&2 echo "\`hostname -f\`: \$line"
    done < \${tmplog};
    rm \${tmplog}
    return \$ec
}

files=("\${@}")
for pattern in "\${files[@]}"
do
    matchingFiles=()
    while IFS=  read -r -d $'\\0'
    do
        matchingFiles+=("\$REPLY")
    done < <(find -mindepth 1 -maxdepth 1 -name "\${pattern}" -print0)
    if [[ \${#matchingFiles[@]} -gt 0 ]]
    then
        for file in "\${matchingFiles[@]}"
        do
            echo "\`hostname -f\`: Copying file \${file/\.\//}"
            run_cmd cp -r "\${file}" "${dir}/"
            if [[ \$? -eq 0 ]]
            then
                echo "\`hostname -f\`: File copied."
            else
                echo "\`hostname -f\`: Failed to copy file."
                exit 1
            fi
        done
    else
        echo "\`hostname -f\`: No files matching pattern '\${pattern}'."
        exit 1
    fi
done
EOF
        chmod 0700 "${execFile}"
        if [[ -x "${execFile}" ]]
        then
            echo "Executable file ${execFile} created."
        else
            echo "Failed to create executable file ${execFile}"
            return 1
        fi
        srun --ntasks-per-node=1 "${execFile}" "${files[@]}"
        ec=$?
        echo "Removing previously created file ${execFile}"
        rm -f "${execFile}"
        return $ec
    else
        for pattern in "${files[@]}"
        do
            matchingFiles=()
            while IFS=  read -r -d $'\0'
            do
                matchingFiles+=("$REPLY")
            done < <(find -mindepth 1 -maxdepth 1 -name "${pattern}" -print0)
            if [[ ${#matchingFiles[@]} -gt 0 ]]
            then
                for file in "${matchingFiles[@]}"
                do
                    echo "Copying file ${file/\.\//} ..."
                    cp -r "${file}" "${dir}/"
                    if [[ $? -eq 0 ]]
                    then
                        echo "File copied."
                    else
                        echo "Failed to copy file."
                        return 1
                    fi
                done
            else
                echo "No files matching pattern '${pattern}'."
                return 1
            fi
        done
    fi
}

stageout=false
stageoutDir="/home/ucl/cp3/mkomm/SSX/analysis/unfolding/jobs"
stageoutFiles=("")

if [[ ${exitCode} -eq 0 ]]
then
    echo "==== Starting stageout of user files (`date`) ===="
    if [[ "${stageout}" == "true" ]]
    then
        stageout userfiles || updateExitCode 104
    else
        echo "Stageout flag is off. Will not stage out any user file."
    fi
    echo "==== Finished stageout of user files (`date`) ===="
fi

#==================================================================================
# Print an exit message
#==================================================================================

echo "======== Finished job (`date`) ========"

exitMsg="Batch script exit code: ${exitCode}"
if [[ ${exitCode} -eq 100 ]]
then
    exitCodeMeaning="failure in changing directory to the job's local scratch directory"
elif [[ ${exitCode} -eq 101 ]]
then
    exitCodeMeaning="failure in environment setup"
elif [[ ${exitCode} -eq 102 ]]
then
    exitCodeMeaning="failure in stagein/unpack of input sandbox"
elif [[ ${exitCode} -eq 103 ]]
then
    exitCodeMeaning="failure in user's payload"
elif [[ ${exitCode} -eq 104 ]]
then
    exitCodeMeaning="failure in stageout of user files"
fi
if [[ -n "${exitCodeMeaning}" ]]
then
    exitMsg+=" (${exitCodeMeaning})"
fi
echo "${exitMsg}"

#==================================================================================
# Stageout the logs and exit
#==================================================================================

stageoutLogs=true
stageoutLogsDir="/home/ucl/cp3/mkomm/SSX/analysis/unfolding/jobs/log"

if [[ "${writeLogsOnWN}" == "true" && "${stageoutLogs}" == "true" ]]
then
    echo "Will stageout the logs before exiting."
    if [[ "${separateStdoutStderrLogs}" == "true" ]]
    then
        logFiles=("${stdoutFilename}" "${stderrFilename}")
    else
        logFiles=("${stdoutFilename}")
    fi
    stageout logs
fi

#==================================================================================

exit ${exitCode}
