/**********************************************************************
 Created on : 24/05/2022
 Purpose    : Read the Jet information from skim file.
 Author     : Indranil Das, Visiting Fellow
 Email      : indranil.das@cern.ch | indra.ehep@gmail.com
**********************************************************************/
#if !defined(__CINT__) || defined(__MAKECINT__)

#include <TROOT.h>
#include <TChain.h>
#include <TEntryList.h>
#include <TFile.h>
#include <TProofOutputFile.h>
#include <TSelector.h>
#include <vector>

#include "TH2.h"
#include "TF1.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TPaveStats.h"
#include "TMath.h"
#include "TProof.h"

#include "TParticlePDG.h"
#include "TDatabasePDG.h"

#include "TLorentzVector.h"
#include "TVector3.h"

#include <fstream>

using namespace std;

#endif

int ReadJetInfoSkim(string infile = "/Data/root_files/AOD_files/NanoAODUL/2017/HminusM120_Skim_NanoAOD.root")
//int ReadJetInfoSkim(string infile = "/Data/root_files/AOD_files/NanoAODUL/2017/TTbarPowheg_Semilept_Skim_NanoAOD_1of59.root")
//int ReadJetInfoSkim(string infile = "/Data/root_files/AOD_files/NanoAODUL/2017/Data_SingleMu_c_Skim_NanoAOD_2of23.root")
//int ReadJetInfoSkim(string infile = "/Data/root_files/AOD_files/NanoAODUL/2017/Data_SingleEle_c_Skim_NanoAOD_1of12.root")
{
  //25 for muon, 34 for electron
  TH1F *hJetPt = new TH1F("hJetPt","hJetPt : HminusM120 (2017) Eta+JetID+PUJetID+njetGT4+ptcutGT25+eventVeto25",100,0,100);
  
  TFile *fin = TFile::Open(infile.c_str());
  cout<<"Reading from file : "<< fin->GetName() << endl;

  TTree *tr = (TTree *)fin->Get("Events");
  
  UInt_t          nJet_;
  Float_t         jetPt_[200];
  Float_t         jetEta_[200];
  Float_t         jetPhi_[200];
  Float_t         jetMass_[200];
  Int_t           jetID_[200];
  Int_t           jetPUID_[200];

  tr->SetBranchAddress("nJet", &nJet_);
  tr->SetBranchAddress("Jet_pt", &jetPt_);
  tr->SetBranchAddress("Jet_eta", &jetEta_);
  tr->SetBranchAddress("Jet_phi", &jetPhi_);
  tr->SetBranchAddress("Jet_mass", &jetMass_);
  tr->SetBranchAddress("Jet_jetId", &jetID_);
  tr->SetBranchAddress("Jet_puId", &jetPUID_);
  
  //for(int ievent = 0 ; ievent < 10000; ievent++){
  for(int ievent = 0 ; ievent < tr->GetEntries() ; ievent++){
    
    tr->GetEntry(ievent);
    
    if(ievent%100000==0)
      printf("Processing %d of %lld\n", ievent, tr->GetEntries());

    int nJetGT4 = 0;
    bool isLowJetPt = false;
    for(int jetInd = 0; jetInd < int(nJet_) and int(nJet_) <= 200 ; ++jetInd){ //200 is the array size for jets as defined in EventTree 
      double pt = jetPt_[jetInd];
      double eta = jetEta_[jetInd];
      bool jetID_pass = (jetID_[jetInd]>=2 and (jetPUID_[jetInd]>=1 or pt>=50.0)) ; //lwp
      // Original condition
      // bool jetPresel = (pt >= jet_Pt_cut &&
      // 			TMath::Abs(eta) <= jet_Eta_cut &&
      // 			jetID_pass &&
      // 			passDR_lep_jet
      // 			);
      bool jetPresel = (pt >= 25.0 && TMath::Abs(eta) <= 2.4 && jetID_pass);
      
      if(jetPresel) nJetGT4++ ;

      if(pt < 25.)
      	isLowJetPt = true;
    }
    
    if(isLowJetPt) continue;
    if(nJetGT4 < 4) continue;
      
    for(int jetInd = 0; jetInd < int(nJet_) and int(nJet_) <= 200 ; ++jetInd){ //200 is the array size for jets as defined in EventTree 
      double pt = jetPt_[jetInd];
      double eta = jetEta_[jetInd];
      bool jetID_pass = (jetID_[jetInd]>=2 and (jetPUID_[jetInd]>=1 or pt>=50.0)) ; //lwp
      // if(TMath::Abs(eta) <= 2.4)
      // 	hJetPt->Fill(pt);
      if(jetID_pass && TMath::Abs(eta) <= 2.4 && pt>25.0)
	hJetPt->Fill(pt);
    }
    
  }//event loop
 
  fin->Close();
  delete fin;

  hJetPt->GetXaxis()->SetTitle("p_{T} GeV/c");
  hJetPt->GetYaxis()->SetTitle("Entries");
  hJetPt->Scale(1./hJetPt->Integral());
  
  TFile *fout = new TFile("Pt_uncut_8_HminusM120_evtVeto.root","recreate");
  hJetPt->Write();
  fout->Close();
  delete fout;

  TCanvas *c1 = new TCanvas("c1","c1");
  hJetPt->Draw();
  

  return true;
} 

