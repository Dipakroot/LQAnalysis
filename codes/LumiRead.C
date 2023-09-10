/**********************************************************************
 Created on : 21/10/2022
 Purpose    : Read run number and associated lumi blocks
 Author     : Indranil Das, Visiting Fellow
 Email      : indranil.das@cern.ch | indra.ehep@gmail.com
**********************************************************************/
int LumiRead()
{
  TFile *fin = TFile::Open("/Data/root_files/AOD_files/NanoAODUL/2016/Data_SingleMu_c_preVFP_Skim_NanoAOD_1of5.root");
  TTree *tree = (TTree *)fin->Get("Events");

  unsigned int run,lumi;

  tree->SetBranchStatus("*",0);

  tree->SetBranchStatus("run",1);
  tree->SetBranchAddress("run", &run);

  tree->SetBranchStatus("luminosityBlock",1);
  tree->SetBranchAddress("luminosityBlock", &lumi);

  cout << "Total Events : " <<  tree->GetEntries() << endl;
  //for(int ievent=0; ievent<tree->GetEntries(); ievent++){
  for(int ievent=0; ievent<200000; ievent++){
    
    tree->GetEntry(ievent);
    //if(ievent%100==0)
    printf("Processing Event : %d,  run : %u, lumiBlock : %u\n",ievent,run,lumi);

    
  }

  return true;
}
