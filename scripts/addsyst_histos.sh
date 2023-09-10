# /**********************************************************************
#  Created on : 31/08/2021
#  Purpose    : Add systematics histos
#  Author     : Indranil Das, Visiting Fellow
#  Email      : indranil.das@cern.ch | indra.ehep@gmail.com
# **********************************************************************/

#samples_2016="DataMu DataEle"
samples_2016="DataMu DataEle HplusM080 HplusM090 HplusM100 HplusM120 HplusM140 HplusM150 HplusM155 HplusM160 TTbar singleTop Wjets DYjets VBFusion MCQCDMu MCQCDEle"
#samples_2016="HplusM080 HplusM090 HplusM100 HplusM140 HplusM150 HplusM155 HplusM160 HplusM120 TTbar singleTop Wjets DYjets VBFusion MCQCDMu MCQCDEle"

syst_2016="base jecup jecdown jerup jerdown"
syst_base="base"
#syst_2016="base puup pudown mueffup mueffdown eleeffup eleeffdown jecup jecdown jerup jerdown btagbup btagbdown btaglup btagldown prefireup prefiredown"
#syst_2016="base puup pudown mueffup mueffdown eleeffup eleeffdown jerup jerdown btagbup btagbdown btaglup btagldown prefireup prefiredown"


#inputdir="/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/grid_v28_Syst/CBA_Skim_Syst"
#inputdir="/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/grid_v30_Syst/CBA_Skim_Syst_MDtune"
#inputdir="/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/grid_v30_Syst/CBA_Skim_Syst_MDPt"
inputdir="/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/grid_v31_Syst/CBA_Skim_Syst_MedID"

years="2016"

basedir=`pwd`
for year in $years
do
    noffiles=`ls $inputdir/$year/source | wc -l`
    echo total number of files $noffiles
    samples=samples_$year
    echo year : $year samples : ${!samples}
    for sample in ${!samples}
    do
	systs=""
	if [[ $sample == *"Data"* ]]; then
	    echo "It's there!" $sample
	    systs=syst_base
	else
	    echo "Sample is " $sample
	    systs=syst_$year
	fi
	for syst in ${!systs}
	do
	    noffiles=`ls $inputdir/$year/source/${sample}_hist_${syst}*.root | wc -l`
	    flist=`ls $inputdir/$year/source/${sample}_hist_${syst}*.root`
	    echo -e "\t ${syst} has nof files ${noffiles}"
	    if [ -f /tmp/fl.txt ] ; then
		rm /tmp/fl.txt
	    fi
	    for file in ${flist} ; do
		echo -e "\t ${file}" >> /tmp/fl.txt
	    done
	    sh ~/scripts/addhisto_file.sh /tmp/fl.txt
	    cp histo_merged.root $inputdir/$year/${sample}_${syst}.root
	    mv histo_merged.root /tmp/
	done
    done
done
