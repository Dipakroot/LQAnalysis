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


int CShapeCalibStudy(string inputfile = "input/inlap/2016/post/TTbar_2016.txt")
{
  TH1F *FSRup = new TH1F("FSRup","FSRup/down", 500, 0., 50.);
  TH1F *FSRdown = new TH1F("FSRdown","FSRup/down", 500, 0., 50.);
  TH2F *hbjetCTag = new TH2F("hbjetCTag","hbjetCTag",200,0.,1.,200,0.,1.);
  TH2F *hcjetCTag = new TH2F("hcjetCTag","hcjetCTag",200,0.,1.,200,0.,1.);
  TH2F *hljetCTag = new TH2F("hljetCTag","hljetCTag",200,0.,1.,200,0.,1.);

  TH1F *hbjetCvsLCTag = new TH1F("hbjetCvsLCTag","hbjetCvsLCTag",200,0.,1.);
  TH1F *hbjetCvsBCTag = new TH1F("hbjetCvsLCTag","hbjetCvsBCTag",200,0.,1.);
  TH1F *hcjetCvsLCTag = new TH1F("hcjetCvsLCTag","hcjetCvsLCTag",200,0.,1.);
  TH1F *hcjetCvsBCTag = new TH1F("hcjetCvsLCTag","hcjetCvsBCTag",200,0.,1.);
  TH1F *hljetCvsLCTag = new TH1F("hljetCvsLCTag","hljetCvsLCTag",200,0.,1.);
  TH1F *hljetCvsBCTag = new TH1F("hljetCvsLCTag","hljetCvsBCTag",200,0.,1.);

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

  chain->SetBranchStatus("*",0);
  
  chain->SetBranchStatus("PSWeight",1);
  chain->SetBranchAddress("PSWeight", &PSWeight_);
	
  chain->SetBranchStatus("nPSWeight",1);
  chain->SetBranchAddress("nPSWeight", &nPSWeight_);

  UInt_t          nJet_;
  Float_t         jetPt_[200];
  Float_t         jetEta_[200];
  Float_t         jetPhi_[200];
  Float_t         jetMass_[200];
  Int_t           jetID_[200];
  Int_t           jetPUID_[200];
  Float_t         jetBtagDeepFlavB_[200];
  Float_t         jetBtagDeepFlavCvB_[200];
  Float_t         jetBtagDeepFlavCvL_[200];
  Int_t           jetHadFlvr_[200];
  Int_t           jetPartFlvr_[200];
  
  chain->SetBranchStatus("nJet",1);
  chain->SetBranchAddress("nJet", &nJet_);
  
  chain->SetBranchStatus("Jet_pt",1);
  chain->SetBranchAddress("Jet_pt", &jetPt_);

  chain->SetBranchStatus("Jet_eta",1);
  chain->SetBranchAddress("Jet_eta", &jetEta_);
	
  chain->SetBranchStatus("Jet_phi",1);
  chain->SetBranchAddress("Jet_phi", &jetPhi_);

  chain->SetBranchStatus("Jet_mass",1);
  chain->SetBranchAddress("Jet_mass", &jetMass_);

  chain->SetBranchStatus("Jet_jetId",1);
  chain->SetBranchAddress("Jet_jetId", &jetID_);

  chain->SetBranchStatus("Jet_puId",1);
  chain->SetBranchAddress("Jet_puId", &jetPUID_);

  chain->SetBranchStatus("Jet_btagDeepFlavB",1);
  chain->SetBranchAddress("Jet_btagDeepFlavB", &jetBtagDeepFlavB_);
  
  chain->SetBranchStatus("Jet_btagDeepFlavCvB",1);
  chain->SetBranchAddress("Jet_btagDeepFlavCvB", &jetBtagDeepFlavCvB_);
  
  chain->SetBranchStatus("Jet_btagDeepFlavCvL",1);
  chain->SetBranchAddress("Jet_btagDeepFlavCvL", &jetBtagDeepFlavCvL_);

  chain->SetBranchStatus("Jet_partonFlavour",1);
  chain->SetBranchAddress("Jet_partonFlavour", &jetPartFlvr_);
  
  chain->SetBranchStatus("Jet_hadronFlavour",1);
  chain->SetBranchAddress("Jet_hadronFlavour", &jetHadFlvr_);

  //double pt,eta;
  double jetCvsLtag;
  double jetCvsBtag;
  int jetFlavor;
  
  Long64_t desired_max = 2500000000;
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
    
    for(int jetInd = 0; jetInd < int(nJet_) and int(nJet_) <= 200 ; ++jetInd){ //200 is the array size for jets as defined in EventTree
      
      //Applied for UL
      bool jetID_pass = (jetID_[jetInd]>=2 and (jetPUID_[jetInd]>=1 or jetPt_[jetInd]>=50.0)) ; //lwp
      //tight PU
      //bool jetID_pass = (tree->jetID_[jetInd]>=2 and (tree->jetPUID_[jetInd]>=7 or pt>=50.0)) ; //twp
      //TLV only
      //bool jetID_pass = (tree->jetID_[jetInd]>=6 and (tree->jetPUID_[jetInd]>=1 or pt>=50.0)) ; //twp
      //Tightmost test
      //bool jetID_pass = (tree->jetID_[jetInd]>=6 and (tree->jetPUID_[jetInd]>=7 or pt>=50.0)) ; //twp
      
      if(jetPt_[jetInd] < 20.0 or TMath::Abs(jetEta_[jetInd]) > 2.5 or !jetID_pass) continue;
      jetFlavor = TMath::Abs(jetHadFlvr_[jetInd]);
      jetCvsLtag = jetBtagDeepFlavCvL_[jetInd] ;
      jetCvsBtag = jetBtagDeepFlavCvB_[jetInd] ;
      
      if (jetFlavor == 5){
	hbjetCTag->Fill(jetCvsLtag, jetCvsBtag);
	hbjetCvsBCTag->Fill(jetCvsBtag);
	hbjetCvsLCTag->Fill(jetCvsLtag);
      }else if (jetFlavor == 4){
	hcjetCTag->Fill(jetCvsLtag, jetCvsBtag);
	hcjetCvsBCTag->Fill(jetCvsBtag);
	hcjetCvsLCTag->Fill(jetCvsLtag);
      }else{
	hljetCTag->Fill(jetCvsLtag, jetCvsBtag);
	hljetCvsBCTag->Fill(jetCvsBtag);
	hljetCvsLCTag->Fill(jetCvsLtag);
      }
      
    }
    
  }//event loop

  FSRup->SetLineColor(kBlue);
  FSRdown->SetLineColor(kRed);
  TCanvas *c1 = new TCanvas("c1","c1");
  c1->SetLogy();
  FSRup->Draw();
  FSRdown->Draw("sames");
  FSRup->GetXaxis()->SetTitle("FSR weight");
  c1->Update();

  hbjetCTag->SetLineColor(kRed);
  hbjetCTag->SetMarkerColor(kRed);
  hcjetCTag->SetLineColor(kGreen+1);
  hcjetCTag->SetMarkerColor(kGreen+1);
  hljetCTag->SetLineColor(kBlue);
  hljetCTag->SetMarkerColor(kBlue);
  hbjetCTag->GetXaxis()->SetTitle("CvsL");
  hbjetCTag->GetYaxis()->SetTitle("CvsB");
  hcjetCTag->GetXaxis()->SetTitle("CvsL");
  hcjetCTag->GetYaxis()->SetTitle("CvsB");
  hljetCTag->GetXaxis()->SetTitle("CvsL");
  hljetCTag->GetYaxis()->SetTitle("CvsB");

  TCanvas *c2 = new TCanvas("c2","c2");
  c2->Divide(2,2);
  c2->cd(1);
  hbjetCTag->Draw();
  c2->cd(2);
  hcjetCTag->Draw();
  c2->cd(3);
  hljetCTag->Draw();
  c2->cd(4);
  hbjetCTag->Draw();
  hcjetCTag->Draw("sames");
  hljetCTag->Draw("sames");

  TCanvas *c3 = new TCanvas("c3","c3");
  hbjetCTag->Draw();
  hcjetCTag->Draw("sames");
  hljetCTag->Draw("sames");

  hbjetCvsBCTag->SetLineColor(kRed);
  hbjetCvsLCTag->SetLineColor(kRed);
  hcjetCvsBCTag->SetLineColor(kGreen+1);
  hcjetCvsLCTag->SetLineColor(kGreen+1);
  hljetCvsBCTag->SetLineColor(kBlue);
  hljetCvsLCTag->SetLineColor(kBlue);

  hbjetCvsBCTag->SetLineWidth(3);
  hcjetCvsBCTag->SetLineWidth(3);
  hljetCvsBCTag->SetLineWidth(3);
  hbjetCvsLCTag->SetLineStyle(kDotted);
  hcjetCvsLCTag->SetLineStyle(kDotted);
  hljetCvsLCTag->SetLineStyle(kDotted);
  hbjetCvsLCTag->SetLineWidth(3);
  hcjetCvsLCTag->SetLineWidth(3);
  hljetCvsLCTag->SetLineWidth(3);

  TCanvas *c4 = new TCanvas("c4","c4");
  c4->Divide(3,2);
  c4->cd(1);
  hbjetCvsBCTag->Draw();
  c4->cd(2);
  hcjetCvsBCTag->Draw();
  c4->cd(3);
  hljetCvsBCTag->Draw();
  c4->cd(4);
  hbjetCvsLCTag->Draw();
  c4->cd(5);
  hcjetCvsLCTag->Draw();
  c4->cd(6);
  hljetCvsLCTag->Draw();
  
  TFile *fout = new TFile("root_files/test/output.root","recreate");
  FSRup->Write();
  FSRdown->Write();
  hbjetCTag->Write();
  hcjetCTag->Write();
  hljetCTag->Write();
  c1->Write();
  c2->Write();
  c3->Write();
  c4->Write();
  fout->Close();
  delete fout;
  
  return true;
}
