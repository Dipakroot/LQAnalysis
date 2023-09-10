int run(const char* opt = "sample=TTbar|year=2016|input=input/files1.txt|index=0|syst=base|aod=nano|run=prod") // sample = data, bkg, signal
{
  
  bool isproof  = false ;
  
  TString options(opt);
  TChain *chain = new TChain("Events");
  
  Ssiz_t from = 0;
  TString tok;
  TString op(opt);
  TString filename = ""; 
  int index = -1;
  TString run = ""; 
  TString sample = "";
  int year = 0;
  // Now analyze the arguments
  while (op.Tokenize(tok , from , "|")) {
    if(tok.BeginsWith("sample"))
      sample = ((TObjString *) (tok.Tokenize("="))->At(1))->GetString();
    if(tok.BeginsWith("year"))
      year = (((TObjString *) (tok.Tokenize("="))->At(1))->GetString()).Atoi();
    if(tok.BeginsWith("input"))
      filename = ((TObjString *) (tok.Tokenize("="))->At(1))->GetString();
    if(tok.BeginsWith("index"))
      index = (((TObjString *) (tok.Tokenize("="))->At(1))->GetString()).Atoi();
    if(tok.BeginsWith("run"))
      run = ((TObjString *) (tok.Tokenize("="))->At(1))->GetString();
  }
  
  cout << "Input filename: " << filename << endl;
  ifstream fin(filename.Data());
  
  string s;
  int idx = 0;
  TString inputfile = ""; 
  while(getline(fin,s)){
    //cout << s << endl;
    if(idx==index){
      chain->Add(s.c_str());
      inputfile = s.c_str();
    }
    idx++;
  }
  cout <<" Total files "<<idx<<endl; 
  op += Form("|total=%d",idx);

  SkimAna *skim = new SkimAna();
  skim->SetOption(op.Data());
  skim->ExecSerial(inputfile.Data());
  delete skim;
  

  return true;
}

