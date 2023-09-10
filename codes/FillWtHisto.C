/**********************************************************************
 Created on : 15/07/2022
 Purpose    : Fill wt histogram
 Author     : Indranil Das, Visiting Fellow
 Email      : indranil.das@cern.ch | indra.ehep@gmail.com
**********************************************************************/
#if !defined(__CINT__) || defined(__MAKECINT__)

#include <TROOT.h>
#include <TChain.h>
#include <TEntryList.h>
#include <TFile.h>
//#include <TProofOutputFile.h>
#include <TSelector.h>
#include <vector>

#include "TH2.h"
#include "TF1.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TPaveStats.h"
#include "TMath.h"
//#include "TProof.h"

#include "TParticlePDG.h"
#include "TDatabasePDG.h"

#include "TLorentzVector.h"
#include "TVector3.h"

#include <fstream>

using namespace std;

#endif


int FillWtHisto(string inputfile = "input/inlap/2016/TTbar_2016.txt")
{
  TH1F *FSRup = new TH1F("FSRup","FSRup/down", 500, 0., 50.);
  TH1F *FSRdown = new TH1F("FSRdown","FSRup/down", 500, 0., 50.);
  
  TChain *chain = new TChain("Events");
  ifstream fin(inputfile.c_str());
  string s;
  string inputname = inputfile.substr(inputfile.find_last_of("/")+1,inputfile.find_last_of(".")-inputfile.find_last_of("/")-1);
  cout << "input filename name : " << inputname << endl;
  int i = 1;
  while(getline(fin,s)){
    //if(i==index){
    cout << "Adding file with index : " << i << " and filename : " <<  s << endl;
    chain->Add(s.c_str());
    //}
    i++;
  }
  fin.close();
  cout << "Total Events : " << chain->GetEntries() << endl;

  UInt_t nPSWeight_;
  Float_t PSWeight_[200];

  chain->SetBranchStatus("PSWeight",1);
  chain->SetBranchAddress("PSWeight", &PSWeight_);
	
  chain->SetBranchStatus("nPSWeight",1);
  chain->SetBranchAddress("nPSWeight", &nPSWeight_);

  Long64_t desired_max = 25000000;
  Long64_t max = (chain->GetEntries()<desired_max) ? chain->GetEntries() : desired_max ;
  
  //for (Long64_t ievent = 0 ; ievent < chain->GetEntries() ; ievent++ ) {
  for (Long64_t ievent = 0 ; ievent < max ; ievent++ ) {
    
    chain->GetEntry(ievent);

    if(ievent%100000==0){//Print after 10K or one or 10 million
      //printf("Processing Event : %lld of total : %lld\n",ievent,chain->GetEntries());
      printf("Processing Event : %lld of total : %lld (%4.2lf\%)\n",ievent,max,100.*double(ievent)/double(max));
    }
    FSRup->Fill(PSWeight_[1]);
    FSRdown->Fill(PSWeight_[3]);
  }

  FSRup->SetLineColor(kBlue);
  FSRdown->SetLineColor(kRed);
  TCanvas *c1 = new TCanvas("c1","c1");
  c1->SetLogy();
  FSRup->Draw();
  FSRdown->Draw("sames");
  c1->Update();
  
  return true;
}
