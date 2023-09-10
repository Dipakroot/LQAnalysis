/**********************************************************************
 Created on : 24/10/2022
 Purpose    : Read the Muon Branch elements
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
#include <TEfficiency.h>

using namespace std;

#endif


int ReadMuBranch(const char *infile="TTbarPowheg_Dilepton_postVFP_Skim_NanoAOD_1of10.root")
{
  
  TH1F *hRelIso_Incl = new TH1F("hRelIso_Incl","hRelIso_Incl", 100000, -0.1, 3.9);
  TH1F *hRelIso_veto = new TH1F("hRelIso_veto","hRelIso_veto", 10000, -1., 49.);
  TH1F *hRelIso_loose = new TH1F("hRelIso_loose","hRelIso_loose", 10000, -1., 49.);
  TH1F *hRelIso_medium = new TH1F("hRelIso_medium","hRelIso_medium", 10000, -1., 49.);
  TH1F *hRelIso_iso_medium = new TH1F("hRelIso_iso_medium","hRelIso_iso_medium", 10000, -1., 49.);
  TH1F *hRelIso_noniso_medium = new TH1F("hRelIso_noniso_medium","hRelIso_noniso_medium", 10000, -1., 49.);
  TH1F *hRelIso_medium_lmet = new TH1F("hRelIso_medium_lmet","hRelIso_medium_lmet", 10000, -1., 49.);
  TH1F *hRelIso_iso_medium_lmet = new TH1F("hRelIso_iso_medium_lmet","hRelIso_iso_medium_lmet", 100000, -0.2, 0.2 );
  TH1F *hRelIso_noniso_medium_lmet = new TH1F("hRelIso_noniso_medium_lmet","hRelIso_noniso_medium_lmet", 10000, -1., 49.);
  TH1F *hRelIso_medium_hmet = new TH1F("hRelIso_medium_hmet","hRelIso_medium_hmet", 10000, -1., 49.);
  TH1F *hRelIso_iso_medium_hmet = new TH1F("hRelIso_iso_medium_hmet","hRelIso_iso_medium_hmet", 100000, -0.2, 0.2 );
  TH1F *hRelIso_noniso_medium_hmet = new TH1F("hRelIso_noniso_medium_hmet","hRelIso_noniso_medium_hmet", 10000, -1., 49.);
  TH1F *hRelIso_tight = new TH1F("hRelIso_tight","hRelIso_tight", 10000, -1., 49.);
  TEfficiency *hEffPt = new TEfficiency("hEffPt","Efficiency;#it{p}_{T} GeV/#it{c};#epsilon", 100, 0., 100.);
  TH1F *hPt = new TH1F("hPt","hPt", 100, -1., 99.);
  
  TFile *fin = TFile::Open(infile);
  TTree *tr = (TTree *)fin->Get("Events");
  
  tr->SetCacheSize(500*1024*1024);
  tr->SetBranchStatus("*",0);
  
  unsigned int run;
  tr->SetBranchStatus("run",1);
  tr->SetBranchAddress("run",&run);
  
  UInt_t  nMuon_;
  tr->SetBranchStatus("nMuon",1);
  tr->SetBranchAddress("nMuon", &(nMuon_));
  
  Float_t muPFRelIso_[20];
  tr->SetBranchStatus("Muon_pfRelIso03_all",1);
  tr->SetBranchAddress("Muon_pfRelIso03_all", &(muPFRelIso_));
  
  Bool_t muisGlobal_[20];
  tr->SetBranchStatus("Muon_isGlobal",1); 
  tr->SetBranchAddress("Muon_isGlobal", &(muisGlobal_));
  
  Bool_t mulooseId_[20];
  tr->SetBranchStatus("Muon_looseId",1); 
  tr->SetBranchAddress("Muon_looseId", &(mulooseId_));

  Bool_t mumediumId_[20];
  tr->SetBranchStatus("Muon_mediumId",1); 
  tr->SetBranchAddress("Muon_mediumId", &(mumediumId_));

  Bool_t mutightId_[20];
  tr->SetBranchStatus("Muon_tightId",1); 
  tr->SetBranchAddress("Muon_tightId", &(mutightId_));

  Float_t muPt_[20];
  tr->SetBranchStatus("Muon_pt",1); 
  tr->SetBranchAddress("Muon_pt", &(muPt_));

  Float_t muEta_[20];
  tr->SetBranchStatus("Muon_eta",1); 
  tr->SetBranchAddress("Muon_eta", &(muEta_));

  Float_t muDxy_[20];
  tr->SetBranchStatus("Muon_dxy",1); 
  tr->SetBranchAddress("Muon_dxy", &(muDxy_));

  Float_t muDz_[20];
  tr->SetBranchStatus("Muon_dz",1); 
  tr->SetBranchAddress("Muon_dz", &(muDz_));

  Float_t MET_pt;
  tr->SetBranchStatus("MET_pt",1); 
  tr->SetBranchAddress("MET_pt", &(MET_pt));

  UChar_t mumvId_[20];
  tr->SetBranchStatus("Muon_mvaId",1); 
  tr->SetBranchAddress("Muon_mvaId", &(mumvId_));
    
  cout << "Total Entries : " << tr->GetEntries() << endl;
  for(Long64_t ievent=0;ievent<tr->GetEntries();ievent++){
  //for(Long64_t ievent=0;ievent<100000;ievent++){

    for(int ib = 0 ; ib < 20 ; ib++)
      muPFRelIso_[ib] = -0.1;
    
    tr->GetEntry(ievent);
    for(unsigned int imu = 0 ; imu < nMuon_ ; imu++){
      if(ievent%100000==0)
	printf("event : %lld, imu : %u, isGlobal : %d, relIso_all : %f\n", ievent, imu, muisGlobal_[imu], muPFRelIso_[imu]);

      //approx-ana-cut
      if(muPt_[imu] < 26. or TMath::Abs(muEta_[imu]) >= 2.4 or muDxy_[imu] > 0.2 or muDz_[imu] > 0.5 or nMuon_ > 1) continue ;
	
      hRelIso_Incl->Fill(muPFRelIso_[imu]);
      
      if(muisGlobal_[imu]) //veto
	hRelIso_veto->Fill(muPFRelIso_[imu]);
      if(mulooseId_[imu]) //looseid
	hRelIso_loose->Fill(muPFRelIso_[imu]);

      hEffPt->Fill( (mumediumId_[imu]), muPt_[imu]);
      if(mumediumId_[imu]) {//medium ID
	hRelIso_medium->Fill(muPFRelIso_[imu]);
	hPt->Fill(muPt_[imu]);
	if(muPFRelIso_[imu]<0.15) 
	  hRelIso_iso_medium->Fill(muPFRelIso_[imu]);
	else
	  hRelIso_noniso_medium->Fill(muPFRelIso_[imu]);
      }
      if(MET_pt < 20.0){
	if(mumediumId_[imu]) {//medium ID
	  if(muPFRelIso_[imu]<0.15)
	    hRelIso_iso_medium_lmet->Fill(muPFRelIso_[imu]);
	  else
	    hRelIso_noniso_medium_lmet->Fill(muPFRelIso_[imu]);
	}
      }else {
	if(mumediumId_[imu]) {//medium ID
	  if(muPFRelIso_[imu]<0.15)
	    hRelIso_iso_medium_hmet->Fill(muPFRelIso_[imu]);
	  else
	    hRelIso_noniso_medium_hmet->Fill(muPFRelIso_[imu]);
	}
      }      
      if(mutightId_[imu])
	hRelIso_tight->Fill(muPFRelIso_[imu]);
      
      // ////////////////// MVA //////////////////////////////////////////
      // if(muisGlobal_[imu]) //veto
      // 	hRelIso_veto->Fill(muPFRelIso_[imu]);
      // if(mumvId_[imu]>=1) //looseid
      // 	hRelIso_loose->Fill(muPFRelIso_[imu]);

      // hEffPt->Fill((mumvId_[imu]>=2), muPt_[imu]);
      // if(mumvId_[imu]>=2) {//medium ID
      // 	hRelIso_medium->Fill(muPFRelIso_[imu]);
      // 	hPt->Fill(muPt_[imu]);
      // 	if(muPFRelIso_[imu]<0.15) 
      // 	  hRelIso_iso_medium->Fill(muPFRelIso_[imu]);
      // 	else
      // 	  hRelIso_noniso_medium->Fill(muPFRelIso_[imu]);
      // }
      // if(MET_pt < 20.0){
      // 	if(mumvId_[imu]>=2) {//medium ID
      // 	  if(muPFRelIso_[imu]<0.15)
      // 	    hRelIso_iso_medium_lmet->Fill(muPFRelIso_[imu]);
      // 	  else
      // 	    hRelIso_noniso_medium_lmet->Fill(muPFRelIso_[imu]);
      // 	}
      // }else{
      // 	if(mumvId_[imu]>=2) {//medium ID
      // 	  if(muPFRelIso_[imu]<0.15)
      // 	    hRelIso_iso_medium_hmet->Fill(muPFRelIso_[imu]);
      // 	  else
      // 	    hRelIso_noniso_medium_hmet->Fill(muPFRelIso_[imu]);
      // 	}
      // }
      // if(mumvId_[imu]>=3)
      // 	hRelIso_tight->Fill(muPFRelIso_[imu]);
      

    }//mu loop
  }//event loop
  
  hRelIso_Incl->GetXaxis()->SetTitle("Muon_pfRelIso03_all");
  hRelIso_veto->GetXaxis()->SetTitle("Muon_pfRelIso03_all");
  hRelIso_loose->GetXaxis()->SetTitle("Muon_pfRelIso03_all");
  hRelIso_medium->GetXaxis()->SetTitle("Muon_pfRelIso03_all");
  hRelIso_iso_medium->GetXaxis()->SetTitle("Muon_pfRelIso03_all");
  hRelIso_noniso_medium->GetXaxis()->SetTitle("Muon_pfRelIso03_all");
  hRelIso_medium_lmet->GetXaxis()->SetTitle("Muon_pfRelIso03_all");
  hRelIso_iso_medium_lmet->GetXaxis()->SetTitle("Muon_pfRelIso03_all");
  hRelIso_noniso_medium_lmet->GetXaxis()->SetTitle("Muon_pfRelIso03_all");
  hRelIso_medium_hmet->GetXaxis()->SetTitle("Muon_pfRelIso03_all");
  hRelIso_iso_medium_hmet->GetXaxis()->SetTitle("Muon_pfRelIso03_all");
  hRelIso_noniso_medium_hmet->GetXaxis()->SetTitle("Muon_pfRelIso03_all");
  hRelIso_tight->GetXaxis()->SetTitle("Muon_pfRelIso03_all");
  hPt->GetXaxis()->SetTitle("Muon_pt");
  
  TCanvas *c1 = new TCanvas("c1","c1",1200,800);
  c1->Divide(2,2);
  c1->cd(1);
  c1->cd(1)->SetLogy();
  hRelIso_veto->Draw();
  c1->cd(2);
  c1->cd(2)->SetLogy();
  hRelIso_loose->Draw();
  c1->cd(3);
  c1->cd(3)->SetLogy();
  hRelIso_medium->Draw();
  c1->cd(4);
  c1->cd(4)->SetLogy();
  hRelIso_tight->Draw();

  TCanvas *c2 = new TCanvas("c2","c2",1200,800);
  c2->SetLogy();
  hRelIso_Incl->Draw();

  TCanvas *c3 = new TCanvas("c3","c3",1200,800);
  c3->Divide(2,1);
  c3->cd(1);
  c3->cd(1)->SetLogy();
  hRelIso_iso_medium->Draw();
  c3->cd(2)->SetLogy();
  hRelIso_noniso_medium->Draw();
  
  TCanvas *c4 = new TCanvas("c4","c4",1200,800);
  c4->Divide(2,2);
  c4->cd(1)->SetLogy();
  hRelIso_iso_medium_hmet->Draw();
  c4->cd(2)->SetLogy();
  hRelIso_noniso_medium_hmet->Draw();
  c4->cd(3)->SetLogy();
  hRelIso_iso_medium_lmet->Draw();
  c4->cd(4)->SetLogy();
  hRelIso_noniso_medium_lmet->Draw();

  TCanvas *c5 = new TCanvas("c5","c5",1200,800);
  c5->Divide(2,1);
  c5->cd(1);
  hPt->Draw();
  c5->cd(2);
  hEffPt->Draw();


  TFile *fout = new TFile("output.root","recreate");
  c1->Write();
  c2->Write();
  c3->Write();
  c4->Write();
  c5->Write();
  fout->Close();
  
  //delete fin;
  return true;
}
