{
  gStyle->SetOptStat(1001111);
  TString hostname = gSystem->HostName();
  TString basePath = "";
  if(hostname.BeginsWith("Indra-Rjn"))
    basePath = "/Data/Software/TRooFit";
  else if(hostname.BeginsWith("dhep-inlap"))
    basePath = "/Data/Software/TRooFit";
  else if(hostname.BeginsWith("lxplus"))
    basePath = "/afs/cern.ch/user/i/idas/CMS-Analysis/NanoAOD-Analysis";
  else if(hostname.BeginsWith("ui"))
    basePath = "/home/idas/Software/TRooFit";
  else if(hostname.BeginsWith("lnx3"))
    basePath = "/Data/Software/TRooFit";
  Printf("Base Path is : %s",basePath.Data());
  
  if (gSystem->Load(Form("%s/lib/libTRooFit.so",basePath.Data())) == -1)
    return -1;
  else
    Printf("Loaded libTRooFit.so");
  
  gSystem->SetIncludePath(Form("-I%s/include/TRooFit",basePath.Data())) ;
  
  //gSystem->Load("/lib/libTRooFit.so");
  //gSystem->AddIncludePath("-I/Data/Software/TRooFit/include/TRooFit");
}
