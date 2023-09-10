num=46
echo -n "Number : $num"
echo ""
echo -n "Year (2016/2017/2018): "
read year;
echo -n "channel (1 for muon, any other for electron): "
read ch;

for i in $(seq 2 $num)
do
   if [ $(expr $i % 2) == 0 ]
   then
       echo $i
       root -l -q -b codes/UpDownBaseCompare.C+\($ch,$year,$i\)
       #sleep 2
   fi
done

