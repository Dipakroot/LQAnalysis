for year in 2016 2017 2018
do
    for bjet in 0 
    do
	for isMu in 0 1
	do
	    for i in `seq 0 9`
	    do
		root -l -b -q codes/QCDDDAll.C+\($year,$bjet,$isMu,$i\)
	    done
	done
    done
done
