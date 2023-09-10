import itertools
import os
import sys
import subprocess
import time

#IMPORT MODULES FROM OTHER DIR

samples_2016 = ["TTbar", "DataMu", "singleTop", "Wjets", "DYjets", "VBFusion", "MCQCDMu", "MCQCDEle", "DataEle",# "HplusM120"]
                "HplusM080", "HplusM090", "HplusM100", "HplusM110", "HplusM120", "HplusM130", "HplusM140", "HplusM150", "HplusM155", "HplusM160",
                "HminusM080", "HminusM090", "HminusM100", "HminusM110", "HminusM120", "HminusM130", "HminusM140", "HminusM150", "HminusM155", "HminusM160"]
samples_2017 = ["TTbar", "DataMu", "singleTop", "Wjets", "DYjets", "VBFusion", "MCQCDMu", "MCQCDEle", "DataEle",# "HplusM120"]
                "HplusM080", "HplusM090", "HplusM100", "HplusM110", "HplusM120", "HplusM130", "HplusM140", "HplusM150", "HplusM155", "HplusM160",
                "HminusM080", "HminusM090", "HminusM100", "HminusM110", "HminusM120", "HminusM130", "HminusM140", "HminusM150", "HminusM155", "HminusM160"]
samples_2018 = ["TTbar", "DataMu", "singleTop", "Wjets", "DYjets", "VBFusion", "MCQCDMu", "MCQCDEle", "DataEle",# "HplusM120"]
                "HplusM080", "HplusM090", "HplusM100", "HplusM110", "HplusM120", "HplusM130", "HplusM140", "HplusM150", "HplusM155", "HplusM160",
                "HminusM080", "HminusM090", "HminusM100", "HminusM110", "HminusM120", "HminusM130", "HminusM140", "HminusM150", "HminusM155", "HminusM160"]


syst_2016 = ["base", "jecup", "jecdown", "jerup", "jerdown", "iso20", "metup", "metdown"]
syst_2017 = ["base", "jecup", "jecdown", "jerup", "jerdown", "iso20", "metup", "metdown"]
syst_2018 = ["base", "jecup", "jecdown", "jerup", "jerdown", "iso20", "metup", "metdown"]

syst_long_2016 = ["base", "jecup", "jecdown", "jerup", "jerdown", "iso20", "metup", "metdown", "cp5up", "cp5down", "hdampup", "hdampdown", "mtopup", "mtopdown"]
syst_long_2017 = ["base", "jecup", "jecdown", "jerup", "jerdown", "iso20", "metup", "metdown", "cp5up", "cp5down", "hdampup", "hdampdown", "mtopup", "mtopdown"]
syst_long_2018 = ["base", "jecup", "jecdown", "jerup", "jerdown", "iso20", "metup", "metdown", "cp5up", "cp5down", "hdampup", "hdampdown", "mtopup", "mtopdown"]


# samples_2016 = ["TTbar"]
# samples_2017 = ["TTbar"]
# samples_2018 = ["TTbar"]

# syst_long_2016 = ["mtopup", "mtopdown"]
# syst_long_2017 = ["mtopup", "mtopdown"]
# syst_long_2018 = ["mtopup", "mtopdown"]


tunedict = {
    "cp5up" : "CP5up_TTbar",
    "cp5down" : "CP5down_TTbar",
    "hdampup" : "hdampup_TTbar",
    "hdampdown" : "hdampdown_TTbar",
    "mtopup" : "mtopup_TTbar",
    "mtopdown" : "mtopdown_TTbar"
}

jdlDir = 'tmpLog_kfoffset_2'
if not os.path.exists("%s/log"%jdlDir):
    os.makedirs("%s/log"%jdlDir)
condorLogDir = "log"
tarFile = "%s/CBA_Skim.tar.gz"%jdlDir
if os.path.exists(tarFile):
	os.system("rm %s"%tarFile)
os.system("tar -zcvf %s ../../CBA_Skim --exclude condor"%tarFile)
os.system("cp runCBASkim.sh %s/"%jdlDir)
common_command = \
'Universe   = vanilla\n\
should_transfer_files = YES\n\
when_to_transfer_output = ON_EXIT\n\
Transfer_Input_Files = CBA_Skim.tar.gz, runCBASkim.sh\n\
x509userproxy = $ENV(X509_USER_PROXY)\n\
use_x509userproxy = true\n\
+BenchmarkJob = True\n\
#+JobFlavour = "testmatch"\n\
#+MaxRuntime = 41220\n\
+MaxRuntime = 7200\n\
notification = Never\n\
Output = %s/log_$(cluster)_$(process).stdout\n\
Error  = %s/log_$(cluster)_$(process).stderr\n\
Log    = %s/log_$(cluster)_$(process).condor\n\n'%(condorLogDir, condorLogDir, condorLogDir)

#----------------------------------------
#Create jdl files
#----------------------------------------
subFile = open('%s/condorSubmit.sh'%jdlDir,'w')
for year in [2017,2018]:
#for year in [2018]:
#for year in [2017]:
    sampleList = eval("samples_%i"%year)
    jdlName = 'submitJobs_%s.jdl'%(year)
    jdlFile = open('%s/%s'%(jdlDir,jdlName),'w')
    jdlFile.write('Executable =  runCBASkim.sh \n')
    jdlFile.write(common_command)
    condorOutDir="/eos/user/s/savarghe/Indra_Da/Output/cms-hcs-run2/CBA_kfoffset"
    condorOutDir1="/eos/user/i/idas/Output/cms-hcs-run2/CBA_kfoffset"
    condorOutDir2="/cms/store/user/idas/Output/cms-hcs-run2/KinTreeUL/CBA_kfoffset"
    condorOutDir3="/eos/user/d/dugad/idas/Output/cms-hcs-run2/CBA_kfoffset"
    condorOutDir4="/eos/user/a/anayak/HplusAnalysisRun2/idas/Output/cms-hcs-run2/CBA_kfoffset"
    os.system("eos root://eosuser.cern.ch mkdir -p %s/%s"%(condorOutDir, year))
    os.system("eos root://eosuser.cern.ch mkdir -p %s/%s"%(condorOutDir1, year))
    os.system("xrdfs root://se01.indiacms.res.in mkdir -p %s/%s"%(condorOutDir2, year))
    os.system("eos root://eosuser.cern.ch mkdir -p %s/%s"%(condorOutDir3, year))
    os.system("eos root://eosuser.cern.ch mkdir -p %s/%s"%(condorOutDir4, year))
    
    jdlFile.write("X=$(step)\n")
    
    for sample in sampleList:
        
        if sample.find('Data') >=0:
            systList = ["base", "iso20"]
            #systList = ["base"]
        elif sample.find('TTbar') >=0:
            systList = eval("syst_long_%i"%year)
        else:    
            systList = eval("syst_%i"%year)

        for syst in systList:

            if (syst.find('cp5')>=0 or syst.find('hdamp')>=0 or syst.find('mtop')>=0):
                fnamestart = tunedict[syst]
            else:
                fnamestart = sample

            noflines = subprocess.Popen('wc -l ../input/eos/%i/%s_%i.txt | awk \'{print $1}\''%(year,fnamestart,year),shell=True,stdout=subprocess.PIPE).communicate()[0].split('\n')[0]
            nJob = int(noflines)
            print "%s %s %s"%(sample,nJob,syst)
            if nJob==1:
                run_command =  'Arguments  = %s %s input/eos/%i/%s_%i.txt 0 %s \nQueue 1\n\n' %(year, sample, year, fnamestart, year, syst)
            else:
                run_command =  'Arguments  = %s %s input/eos/%i/%s_%i.txt $INT(X) %s \nQueue %i\n\n' %(year, sample, year, fnamestart, year, syst, nJob)
            jdlFile.write(run_command)
            #print "condor_submit jdl/%s"%jdlFile

    subFile.write("condor_submit %s\n"%jdlName)
    jdlFile.close() 
subFile.close()
