#!/bin/bash

basedir=$PWD

#inputdir=/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/grid_v39_Syst/CBA_CTagDD
#inputdir=/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/grid_v40_Syst/CBA_CTagnPUJetID
#inputdir=/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/grid_v40_Syst/CBA_muFmuRFSRDo
#inputdir=/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/grid_v40_Syst/CBA_ctagv2pulwp-CombHist
#inputdir=$basedir/root_files/grid_v40_Syst/CBA_yearend22
#inputdir=$basedir/root_files/grid_v40_Syst/CBA_notoppt
inputdir=$basedir/root_files/grid_v40_Syst/CBA_elereliso30-CombHist


years="2016 2017 2018"
#years="2018"

for year in $years
do
    for mass in 080 090 100 110 120 130 140 150 155 160 
    #for mass in 120 130 140 150 155 160 
    do
	echo Processing for year $year and mass $mass
	root -l -q -b codes/ModifyTopDirName.C\(\""$inputdir/$year/all_HplusM${mass}.root"\",\""HplusM${mass}"\",\""HplmiM${mass}_1.root"\",\""HplmiM${mass}"\"\) > /tmp/out.log 2>&1
	root -l -q -b codes/ModifyTopDirName.C\(\""$inputdir/$year/all_HminusM${mass}.root"\",\""HminusM${mass}"\",\""HplmiM${mass}_2.root"\",\""HplmiM${mass}"\"\) >> /tmp/out.log 2>&1
	hadd HplmiM${mass}.root HplmiM${mass}_1.root HplmiM${mass}_2.root >> /tmp/out.log 2>&1
	rm HplmiM${mass}_1.root HplmiM${mass}_2.root
	mv HplmiM${mass}.root $inputdir/$year/all_HplmiM${mass}.root
	if [ "${mass}" = "080" ] ; then
	    cd $inputdir/$year
	    ln -s all_HplusM${mass}.root all_HplusM80.root
	    ln -s all_HminusM${mass}.root all_HminusM80.root
	    ln -s all_HplmiM${mass}.root all_HplmiM80.root
	    cd $basedir
	fi
	if [ "${mass}" = "090" ] ; then
	    cd $inputdir/$year
	    ln -s all_HplusM${mass}.root all_HplusM90.root
	    ln -s all_HminusM${mass}.root all_HminusM90.root
	    ln -s all_HplmiM${mass}.root all_HplmiM90.root
	    cd $basedir
	fi
    done
done

# Alternatively one can use commands like below to fuse the files
# rootcp all_HplusM080.root:HplusM080 /tmp/all_HplusM080.root:HplmiM080
# rootcp all_HminuM080.root:HminusM080 /tmp/all_HminusM080.root:HplmiM080
# hadd all_HplmiM080.root /tmp/all_HplusM080.root /tmp/all_HminusM080.root
