#!/bin/bash

#First create the list of log files that reports a broken job using 
#grep -i break *.stderr | cut -d ':' -f 1 > fl_list.txt

while read fname 
do 
    # echo ====== $fname ===== 
    arg=`grep "ExecSerial>: starting SkimAna" $fname | cut -d ':' -f 5` 
    #echo $arg 
    # The above will result : 
    # sample=DataMu|year=2017|input=input/eos/2017/DataMu_2017.txt|index=47|syst=base|aod=nano|run=prod|trs=no|total=86
    sample=`echo $arg | cut -d '|' -f 1 | cut -d '=' -f 2` 
    year=`echo $arg | cut -d '|' -f 2 | cut -d '=' -f 2` 
    input=`echo $arg | cut -d '|' -f 3 | cut -d '=' -f 2` 
    index=`echo $arg | cut -d '|' -f 4 | cut -d '=' -f 2` 
    syst=`echo $arg | cut -d '|' -f 5 | cut -d '=' -f 2` 
    echo 
    echo Arguments  = $year $sample $input $index $syst 
    echo Queue 1
    #echo
done < fl_list.txt

