#!/bin/bash
#To be run on remote machine
#Take input arguments as an array
myArray=( "$@" )
#Array: Size=$#, an element=$1, all element = $@

export SCRAM_ARCH=slc7_amd64_gcc10
export CMSVER=CMSSW_12_3_6

printf "Start Running Histogramming at ";/bin/date
printf "Worker node hostname ";/bin/hostname
printf "Worker node OS " ; lsb_release -d
printf "SCRAM :  ${SCRAM_ARCH}\n"
printf "CMSSW :  ${CMSVER}\n"

if [ -z ${_CONDOR_SCRATCH_DIR} ] ; then 
    echo "Running Interactively" ; 
else
    echo "Running In Batch"
    echo ${_CONDOR_SCRATCH_DIR}

    source /cvmfs/cms.cern.ch/cmsset_default.sh
    scramv1 project $CMSVER
    cd $CMSVER/src
    eval `scramv1 runtime -sh`
    cd ../..
    
fi
tar --strip-components=1 -zxf CBA_Skim.tar.gz
#Run for Base, Signal region
#./complib.sh
echo "All arguements: "$@
echo "Number of arguements: "$#
year=$1
sample=$2
input=$3
index=$4
syst=$5

#time root -l -b -q run.C\(\""sample=${sample}|year=${year}|input=${input}|index=${index}|syst=${syst}|aod=nano|run=prod"\"\)

if [ "$sample" = "DataMu" -o "$sample" = "DataEle" ]; then
    time ./SkimAnaData $sample $year $input $index $syst
else
    time ./SkimAna $sample $year $input $index $syst
fi


printf "Done Histogramming at ";/bin/date
#---------------------------------------------
#Copy the ouput root files
#---------------------------------------------
# condorOutDir=/eos/user/s/savarghe/Indra_Da/Output/cms-hcs-run2/CBA_kfoffset
# condorOutDir1=/eos/user/i/idas/Output/cms-hcs-run2/CBA_kfoffset
# condorOutDir2=/cms/store/user/idas/Output/cms-hcs-run2/KinTreeUL/CBA_kfoffset
# condorOutDir3=/eos/user/d/dugad/idas/Output/cms-hcs-run2/CBA_kfoffset
# condorOutDir4=/eos/user/a/anayak/HplusAnalysisRun2/idas/Output/cms-hcs-run2/CBA_kfoffset
condorOutDir=/eos/user/s/savarghe/Indra_Da/Output/cms-hcs-run2/CBA_kfoffset/post
condorOutDir1=/eos/user/i/idas/Output/cms-hcs-run2/CBA_kfoffset/post
condorOutDir2=/cms/store/user/idas/Output/cms-hcs-run2/KinTreeUL/CBA_kfoffset/post
condorOutDir3=/eos/user/d/dugad/idas/Output/cms-hcs-run2/CBA_kfoffset/post
condorOutDir4=/eos/user/a/anayak/HplusAnalysisRun2/idas/Output/cms-hcs-run2/CBA_kfoffset/post

if [ -z ${_CONDOR_SCRATCH_DIR} ] ; then
    echo "Running Interactively" ;
else
    #xrdcp -f ${sample}_tree_*.root root://se01.indiacms.res.in:1094/${condorOutDir}/${year} 
    xrdcp -f ${sample}_tree_*.root root://eosuser.cern.ch/${condorOutDir}/${year}
    xrdcp -f ${sample}_hist_*.root root://eosuser.cern.ch/${condorOutDir1}/${year}
    xrdcp -f ${sample}_bjet_*.root root://eosuser.cern.ch/${condorOutDir3}/${year}
    xrdcp -f ${sample}_tree_*.root root://eosuser.cern.ch/${condorOutDir4}/${year}
    # xrdcp -f ${sample}_tree_*.root root://se01.indiacms.res.in:1094/${condorOutDir2}/${year}
    echo "Cleanup"
    rm -rf $CMSVER
    rm *.root
fi
printf "Done ";/bin/date
