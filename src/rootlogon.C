{
  
  TString hostname = gSystem->HostName();
  TString basePath = gSystem->pwd();
  cout <<"Hostname : " << hostname.Data() << endl;
  
  if (gSystem->Load(Form("%s/libweight.so",basePath.Data())) == -1)
    return -1;
  else
    Printf("Loaded libweight.so");
  
  gSystem->SetIncludePath(Form("-I%s",basePath.Data())) ;

  if (gSystem->Load("SkimAna_C.so") == -1){
    Printf("SkimAna_C.so not found try complib.sh ");
    return -1;
  }else{
    Printf("Loaded SkimAna_C.so");
  }


  return 0;
}
