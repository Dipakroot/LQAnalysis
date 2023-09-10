/**********************************************************************
 Created on : 10/09/2022
 Purpose    : Integrated lumi of runs
 Author     : Indranil Das, Visiting Fellow
 Email      : indranil.das@cern.ch | indra.ehep@gmail.com
**********************************************************************/
//year=2016; for fname in `ls data_era/runList_${year}*`; do sample=`echo $fname | cut -d 'D' -f 2` ; echo sample : D$sample , fname : $fname ;  while read run ; do grep " $run:" Lumi_UL${year}.csv ; done < $fname ; done

//year=2016; for fname in `ls data_era/Lumi_${year}*`; do sample=`echo $fname | cut -d 'S' -f 2` ; sample=`echo $sample | cut -d '.' -f 1`; Lumi=`root -l -b -q SumTotLumi.C\(\""$fname"\"\) | grep IntLumi | cut -d ':' -f 2`; echo S$sample $Lumi  ; done


int SumTotLumi(const char *infile="DataLumi_2016_mu.txt")
{
  ifstream fin(infile);
  string s;
  double totlumi = 0.0;
  double lumi = 0.0;
  double dlumi = 0.0;
  int run, fill,nls, ncms;
  char date[8], time[8];
  int firstRun, lastRun;
  int i = 0;
  while(getline(fin,s)){
    //cout << "size : " << s.size() << endl;
    if(s.size()>70){
      //cout << s << endl;
      sscanf((const char*)s.c_str(),"| %d:%d | %s %s | %d | %d | %lf | %lf |",&run,&fill,date,time,&nls,&ncms,&dlumi,&lumi);
      totlumi += lumi;
      if(i==0)
	firstRun = run;
      i++;
      lastRun = run;
      //printf("%d : %10.9lf : %10.9lf\n",run,lumi,totlumi);
    }
  }
  //cout<<"IntLumi : " << totlumi<<endl;
  printf("IntLumi : %3.2lf %d-%d\n",totlumi,firstRun,lastRun);
  return true;
}
