year=$1

awk -v RS= '{print > ("mjj-" NR ".txt")}' mjjTable_${year}.tex

for i in `seq 2 9`
do
    fname=mjj-${i}.txt
    fout=mjj-${year}-${i}.txt 
    start=`grep adjustbox -n $fname | grep begin | cut -d ':' -f 1`
    stop=`grep adjustbox -n $fname | grep end | cut -d ':' -f 1`
    echo $fname : start:stop $start : $stop
    diff=`echo $stop-$start+1|bc -l`
    head -n $stop $fname | tail -n $diff > $fout
done

mv mjj-${year}-2.txt sec07_eventYield_Inc_${year}.tex
mv mjj-${year}-4.txt sec07_eventYield_ExcL_${year}.tex
mv mjj-${year}-6.txt sec07_eventYield_ExcM_${year}.tex
mv mjj-${year}-8.txt sec07_eventYield_ExcT_${year}.tex

mv mjj-${year}-3.txt sec07_syst_Inc_${year}.tex
mv mjj-${year}-5.txt sec07_syst_ExcL_${year}.tex
mv mjj-${year}-7.txt sec07_syst_ExcM_${year}.tex
mv mjj-${year}-9.txt sec07_syst_ExcT_${year}.tex

rm mjj-*.txt

