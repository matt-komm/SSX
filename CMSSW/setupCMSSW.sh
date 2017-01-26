#!/bin/bash

STOP=""

VARS=""

function addVar
{
    VARS=$VARS" "$1"="$2
}

function execute 
{
    if [ -z "$STOP" ]; then
        echo -n $@ " ... "
        out=$(eval $@ 2>&1)
        ret=$?

        if [ $ret -eq 0 ]; then
            echo "ok"
        else
            echo "error"
            STOP=$out
        fi
    fi
}

cd $BASEDIR/CMSSW

export SCRAM_ARCH=slc6_amd64_gcc530
addVar SCRAM_ARCH $SCRAM_ARCH

CMSSWVERSION="CMSSW_8_0_24"

execute "scramv1 project CMSSW $CMSSWVERSION"
cd $CMSSWVERSION/src

eval `scramv1 runtime -sh`
execute "git cms-init"

#https://twiki.cern.ch/twiki/bin/viewauth/CMS/CutBasedElectronIdentificationRun2#Working_points_for_2016_data_for
execute "git cms-merge-topic ikrav:egm_id_80X_v1"

#https://twiki.cern.ch/twiki/bin/viewauth/CMS/MissingETUncertaintyPrescription#Instructions_for_8_0_X_X_20_for
execute "git cms-merge-topic cms-met:METRecipe_8020"

#https://twiki.cern.ch/twiki/bin/view/CMS/EGMRegression
#execute "git cms-merge-topic rafaellopesdesa:Regression80XEgammaAnalysis_v2"

#execute "scram b -j10"
#cd $CMSSW_BASE/external/$SCRAM_ARCH
#execute "git clone https://github.com/ikrav/RecoEgamma-ElectronIdentification.git data/RecoEgamma/ElectronIdentification/data"
#cd data/RecoEgamma/ElectronIdentification/data
#execute "checkout egm_id_80X_v1"

execute "git clone -b CMSSW_8024 https://github.com/matt-komm/EDM2PXLIO.git"
execute "git reset EDM2PXLIO"
execute "git clone https://github.com/matt-komm/Pxl.git"
execute "git reset Pxl"

ln -s ../../UserCode
ln -s ../../crab

execute "scram b -j10"

cd $BASEDIR

