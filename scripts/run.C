//int run(const char* opt = "sample=HplusM120|year=2016|input=input/inlap/2016/HplusM120_2016.txt|index=0|run=prod|mode=proof|workers=4|syst=base|aod=nano|trs=no") // sample = data, bkg, signal
int run(const char* opt = "sample=MCQCDEle|year=2018|input=input/inlap/2018/MCQCDEle_2018.txt|index=0|run=prod|mode=proof|workers=1|syst=base|aod=nano|trs=no") // sample = data, bkg, signal
{
  
  bool isproof  = false ;
  
  TString options(opt);
  TChain *chain = new TChain("Events");
  
  Ssiz_t from = 0;
  TString tok;
  TString op(opt);
  TString filename = ""; 
  TString mode = ""; 
  int workers = 3;
  TString run = ""; 
  // Now analyze the arguments
  while (op.Tokenize(tok , from , "|")) {
    if(tok.BeginsWith("input"))
      filename = ((TObjString *) (tok.Tokenize("="))->At(1))->GetString();
    if(tok.BeginsWith("mode"))
      mode = ((TObjString *) (tok.Tokenize("="))->At(1))->GetString();
    if(tok.BeginsWith("workers"))
      workers = (((TObjString *) (tok.Tokenize("="))->At(1))->GetString()).Atoi();
    if(tok.BeginsWith("run"))
      run = ((TObjString *) (tok.Tokenize("="))->At(1))->GetString();
  }
  if(mode.BeginsWith("proof"))
    isproof = true;
  
  cout << "Input filename: " << filename << endl;
  ifstream fin(filename.Data());
 
  int idx = 0; 
  string s;
  while(getline(fin,s)){
    //cout << s << endl;
    chain->Add(s.c_str());
    idx++;
  }
  cout <<" Total files "<<idx<<endl; 
  options += Form("|total=%d",idx);
  
  if(isproof){
    TProof *p = TProof::Open(Form("workers=%d",workers));
    p->ClearPackages();
    p->UploadPackage("loadpackages.par");
    p->EnablePackage("loadpackages");
    chain->SetProof();
  }
  
  if(run == "prod")
    chain->Process("SkimAna.C++", options.Data() );    
  else
    chain->Process("SkimAna.C++", options.Data(), 1000 );    
  
  return true;
}

