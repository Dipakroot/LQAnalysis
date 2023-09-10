#!/bin/bash

#samples_2016="HplusM120 DataMu DataEle TTbar singleTop Wjets DYjets VBFusion MCQCDMu MCQCDEle"
samples_2017="DataMu DataEle TTbar singleTop Wjets DYjets VBFusion MCQCDMu MCQCDEle"
samples_2018="DataMu DataEle TTbar singleTop Wjets DYjets VBFusion MCQCDMu MCQCDEle"

samples_2016="HplusM120"
#samples_2017="DataEle"
# samples_2018="TTbar"

#years="2016 2017 2018"
years="2016"

basedir=`pwd`
for year in $years 
do
    samples=samples_$year
    echo year : $year samples : ${!samples}
    #tmpdir=$basedir/../tmp_$(date +%Y-%m-%d__%H%M%S)_${year}
    tmpdir=/tmp/tmp_${year}
    if [ ! -d $tmpdir ] ; then
    	mkdir -p $tmpdir
    else
	rm -rf $tmpdir
	mkdir $tmpdir
    fi
    cp SkimAna.C  SkimAna.h  loadpackages.par run.C $tmpdir/
    cp -r input  $tmpdir/
    cd $tmpdir
    echo basedir : $basedir
    echo current directory : $tmpdir
    for sample in ${!samples}
    do
    	#input=input/files.txt #input has to be relative to $basedir
	input=input/lnx3/${year}/${sample}_${year}.txt #input has to be relative to $basedir
	#input=input/ui/${year}/${sample}_${year}.txt #input has to be relative to $basedir
    	ls -la $input
        if [ "${sample}" = "MCQCDMu" ] || [ "${sample}" = "MCQCDEle" ] ; then
            echo workers = 1
    	    root -l -b -q run.C\(\""sample=$sample|year=$year|input=$input|syst=base|aod=nano|mode=proof|workers=1|run=prod|index=0|trs=no"\"\)
	else
            echo workers = 8
    	    root -l -b -q run.C\(\""sample=$sample|year=$year|input=$input|syst=base|aod=nano|mode=proof|workers=8|run=prod|index=0|trs=no"\"\)
	fi
    done
    cp $tmpdir/*.root $basedir
    cp $tmpdir/*.log $basedir
    cd $basedir
done
