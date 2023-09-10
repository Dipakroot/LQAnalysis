/**********************************************************************
 Created on : 12/05/2022
 Purpose    : Validation of Kintree with respect to the produced histogram
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

#include "TH1F.h"
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


int KinTreeValidation()
{
  void SetHist(TH1F*& mjj1, TH1F*& mjj2);

  string signal = "HminusM120";

  TH1F *mjj = new TH1F("mjj",Form("%s : mjj (Inclusive) [From TTree]",signal.c_str()), 50, 0., 250.);
  TH1F *mjj_exclT = new TH1F("mjj_exclT",Form("%s : mjj (Exclusive Tight) [From TTree]",signal.c_str()), 50, 0., 250.);
  TH1F *mjj_exclM = new TH1F("mjj_exclM",Form("%s : mjj (Exclusive Medium) [From TTree]",signal.c_str()), 50, 0., 250.);
  TH1F *mjj_exclL = new TH1F("mjj_exclL",Form("%s : mjj (Exclusive Loose) [From TTree]",signal.c_str()), 50, 0., 250.);
  TH1F *mjj_excl0 = new TH1F("mjj_excl0",Form("%s : mjj (Exclusive Others) [From TTree]",signal.c_str()), 50, 0., 250.);
  TH1F *mjj_inclT = new TH1F("mjj_inclT",Form("%s : mjj (Inclusive Tight) [From TTree]",signal.c_str()), 50, 0., 250.);
  TH1F *mjj_inclM = new TH1F("mjj_inclM",Form("%s : mjj (Inclusive Medium) [From TTree]",signal.c_str()), 50, 0., 250.);
  TH1F *mjj_inclL = new TH1F("mjj_inclL",Form("%s : mjj (Inclusive Loose) [From TTree]",signal.c_str()), 50, 0., 250.);

  Double_t  chi2;
  Float_t   jetChadPt;
  Float_t   jetChadEta;
  Float_t   jetChadPhi;
  Float_t   jetChadEn;
  Float_t   jetShadPt;
  Float_t   jetShadEta;
  Float_t   jetShadPhi;
  Float_t   jetShadEn;
  Float_t   metPx;
  Float_t   metPy;
  Float_t   metPz;

  Double_t sampleWeight;
  Double_t prefireWeight;
  Double_t PUWeight;
  Double_t muEffWeight;
  Double_t puJetIDWeight;
  Double_t bTagWeight;
  Double_t cTagLWeight;
  Double_t cTagMWeight;
  Double_t cTagTWeight;
  Bool_t singleMu;
  Bool_t singleEle;
  Bool_t muonIsoCut;
  Bool_t isLowMET;
  Bool_t isKFValid;
  Bool_t hasKFMu;
  Bool_t hasKFEle;
  Bool_t isCTagged;
  Int_t count_cJetsIncL;
  Int_t count_cJetsIncM;
  Int_t count_cJetsIncT;

  Double_t weight, mjjKF;

  string inpath_tree = ".";
  string inpath_hist = inpath_tree;
 
  TFile *fin	= TFile::Open(Form("%s/%s_tree_base_1of1.root",inpath_tree.c_str(), signal.c_str()));
  TFile *finhist      = TFile::Open(Form("%s/%s_hist_base_1of1.root",inpath_hist.c_str(), signal.c_str()));
  
  cout<<"filename : " << fin->GetName() << endl;
  TTree *tr	= (TTree*)fin->Get("Kinfit_Reco");
  
  TH1F *hMjjSaved = (TH1F *)finhist->Get(Form("%s/base/Iso/_kb_mjj_mu",signal.c_str()));
  TH1F *hMjjSExclT = (TH1F *)finhist->Get(Form("%s/base/Iso/_ct_ExcT_mjj_mu",signal.c_str()));
  TH1F *hMjjSExclM = (TH1F *)finhist->Get(Form("%s/base/Iso/_ct_ExcM_mjj_mu",signal.c_str()));
  TH1F *hMjjSExclL = (TH1F *)finhist->Get(Form("%s/base/Iso/_ct_ExcL_mjj_mu",signal.c_str()));
  TH1F *hMjjSExcl0 = (TH1F *)finhist->Get(Form("%s/base/Iso/_ct_Exc0_mjj_mu",signal.c_str()));
  TH1F *hMjjSInclT = (TH1F *)finhist->Get(Form("%s/base/Iso/_ct_IncT_mjj_mu",signal.c_str()));
  TH1F *hMjjSInclM = (TH1F *)finhist->Get(Form("%s/base/Iso/_ct_IncM_mjj_mu",signal.c_str()));
  TH1F *hMjjSInclL = (TH1F *)finhist->Get(Form("%s/base/Iso/_ct_IncL_mjj_mu",signal.c_str()));
  hMjjSaved->SetTitle(Form("%s : mjj (Inclusive) [From Hist]",signal.c_str()));
  hMjjSExclT->SetTitle(Form("%s : mjj (Exclusive Tight) [From Hist]",signal.c_str()));
  hMjjSExclM->SetTitle(Form("%s : mjj (Exclusive Medium) [From Hist]",signal.c_str()));
  hMjjSExclL->SetTitle(Form("%s : mjj (Exclusive Loose) [From Hist]",signal.c_str()));
  hMjjSExcl0->SetTitle(Form("%s : mjj (Exclusive Others) [From Hist]",signal.c_str()));
  hMjjSInclT->SetTitle(Form("%s : mjj (Inclusive Tight) [From Hist]",signal.c_str()));
  hMjjSInclM->SetTitle(Form("%s : mjj (Inclusive Medium) [From Hist]",signal.c_str()));
  hMjjSInclL->SetTitle(Form("%s : mjj (Inclusive Loose) [From Hist]",signal.c_str()));

  tr->SetBranchAddress("chi2"		, &chi2);
  tr->SetBranchAddress("jetChadPt"	, &jetChadPt);
  tr->SetBranchAddress("jetChadEta"	, &jetChadEta);
  tr->SetBranchAddress("jetChadPhi"	, &jetChadPhi);
  tr->SetBranchAddress("jetChadEnergy"	, &jetChadEn);
  tr->SetBranchAddress("jetShadPt"	, &jetShadPt);
  tr->SetBranchAddress("jetShadEta"	, &jetShadEta);
  tr->SetBranchAddress("jetShadPhi"	, &jetShadPhi);
  tr->SetBranchAddress("jetShadEnergy"	, &jetShadEn);
  tr->SetBranchAddress("metPx"		, &metPx);
  tr->SetBranchAddress("metPy"		, &metPy);
  tr->SetBranchAddress("metPz"		, &metPz);

  tr->SetBranchAddress("sampleWeight"	, &sampleWeight);
  tr->SetBranchAddress("prefireWeight"	, &prefireWeight);
  tr->SetBranchAddress("PUWeight"	, &PUWeight);
  tr->SetBranchAddress("muEffWeight"	, &muEffWeight);
  tr->SetBranchAddress("puJetIDWeight"	, &puJetIDWeight);
  tr->SetBranchAddress("bTagWeight"	, &bTagWeight);
  tr->SetBranchAddress("cTagLWeight"	, &cTagLWeight);
  tr->SetBranchAddress("cTagMWeight"	, &cTagMWeight);
  tr->SetBranchAddress("cTagTWeight"	, &cTagTWeight);
  tr->SetBranchAddress("singleMu"	, &singleMu);
  tr->SetBranchAddress("singleEle"	, &singleEle);
  tr->SetBranchAddress("muonIsoCut"	, &muonIsoCut);
  tr->SetBranchAddress("isLowMET"	, &isLowMET);
  tr->SetBranchAddress("isCTagged"	, &isCTagged);
  // tr->SetBranchAddress("isKFValid"	, &isKFValid);
  // tr->SetBranchAddress("hasKFMu"	, &hasKFMu);
  // tr->SetBranchAddress("hasKFEle"	, &hasKFEle);
  tr->SetBranchAddress("count_cJetsIncL"	, &count_cJetsIncL);
  tr->SetBranchAddress("count_cJetsIncM"	, &count_cJetsIncM);
  tr->SetBranchAddress("count_cJetsIncT"	, &count_cJetsIncT);

  TLorentzVector chad, shad, met;
  
  cout << "Total Entries : " << tr->GetEntries() << endl;
  for (Long64_t ievent = 0 ; ievent < tr->GetEntries() ; ievent++ ) {    
    
    tr->GetEntry(ievent) ;
    if(ievent%1000000==0)
      cout<<"iEvent : " << ievent << ", chi2 : "<<chi2<<endl;
    chad.SetPtEtaPhiE(jetChadPt, jetChadEta, jetChadPhi, jetChadEn);
    shad.SetPtEtaPhiE(jetShadPt, jetShadEta, jetShadPhi, jetShadEn);
    met.SetXYZM(metPx, metPy, metPz, 0.0);

    weight = sampleWeight*prefireWeight*PUWeight*muEffWeight*puJetIDWeight*bTagWeight;
    mjjKF = (chad+shad).M();
    if(singleMu and !singleEle and muonIsoCut and !isLowMET){
      mjj->Fill(mjjKF,weight);
      if(isCTagged){
	if(count_cJetsIncT>0)
	  mjj_exclT->Fill(mjjKF,weight*cTagTWeight);
	else if(count_cJetsIncM > 0)
	  mjj_exclM->Fill(mjjKF,weight*cTagMWeight);
	else if(count_cJetsIncL > 0)
	  mjj_exclL->Fill(mjjKF,weight*cTagLWeight);
	else
	  mjj_excl0->Fill(mjjKF,weight);

	if(count_cJetsIncT>0)
	  mjj_inclT->Fill(mjjKF,weight*cTagTWeight);
	if(count_cJetsIncM>0)
	  mjj_inclM->Fill(mjjKF,weight*cTagMWeight);
	if(count_cJetsIncL>0)
	  mjj_inclL->Fill(mjjKF,weight*cTagLWeight);
      }
    }
  }//event loop
  fin->Close();
  delete fin;
  

  gStyle->SetOptStat(1112111);
  gStyle->SetOptFit(11);

  SetHist(hMjjSaved,mjj);
  TCanvas *c1 = new TCanvas("c1","c1",3,47,1350,576);
  c1->Divide(2,1);
  c1->cd(1);
  mjj->Draw("hist");
  c1->cd(2);
  hMjjSaved->Draw("hist");

  SetHist(hMjjSInclL, mjj_inclL);
  TCanvas *c2 = new TCanvas("c2","c2",3,47,1350,576);
  c2->Divide(2,1);
  c2->cd(1);
  mjj_inclL->Draw("hist");
  c2->cd(2);
  hMjjSInclL->Draw("hist");

  SetHist(hMjjSInclM, mjj_inclM);
  TCanvas *c3 = new TCanvas("c3","c3",3,47,1350,576);
  c3->Divide(2,1);
  c3->cd(1);
  mjj_inclM->Draw("hist");
  c3->cd(2);
  hMjjSInclM->Draw("hist");

  SetHist(hMjjSInclT, mjj_inclT);
  TCanvas *c4 = new TCanvas("c4","c4",3,47,1350,576);
  c4->Divide(2,1);
  c4->cd(1);
  mjj_inclT->Draw("hist");
  c4->cd(2);
  hMjjSInclT->Draw("hist");

  SetHist(hMjjSExclL, mjj_exclL);
  TCanvas *c5 = new TCanvas("c5","c5",3,47,1350,576);
  c5->Divide(2,1);
  c5->cd(1);
  mjj_exclL->Draw("hist");
  c5->cd(2);
  hMjjSExclL->Draw("hist");

  SetHist(hMjjSExclM, mjj_exclM);
  TCanvas *c6 = new TCanvas("c6","c6",3,47,1350,576);
  c6->Divide(2,1);
  c6->cd(1);
  mjj_exclM->Draw("hist");
  c6->cd(2);
  hMjjSExclM->Draw("hist");

  SetHist(hMjjSExclT, mjj_exclT);
  TCanvas *c7 = new TCanvas("c7","c7",3,47,1350,576);
  c7->Divide(2,1);
  c7->cd(1);
  mjj_exclT->Draw("hist");
  c7->cd(2);
  hMjjSExclT->Draw("hist");

  SetHist(hMjjSExcl0, mjj_excl0);
  TCanvas *c8 = new TCanvas("c8","c8",3,47,1350,576);
  c8->Divide(2,1);
  c8->cd(1);
  mjj_excl0->Draw("hist");
  c8->cd(2);
  hMjjSExcl0->Draw("hist");

  // TFile *fout = new TFile(Form("output.root"),"recreate");
  // mjj->Write();
  // hMjjSaved->Write();
  // c1->Write();
  // fout->Close();
  // delete fout;


  return true;
}

void SetHist(TH1F*& mjj1,TH1F*& mjj2)
{
  mjj1->SetLineColor(kBlue);
  mjj1->SetLineWidth(2);

  mjj2->SetLineColor(kRed);
  mjj2->SetLineWidth(2);

  mjj1->GetXaxis()->SetTitle("m_{jj} (GeV)");
  mjj1->GetYaxis()->SetTitle("Entries");

  mjj2->GetXaxis()->SetTitle("m_{jj} (GeV)");
  mjj2->GetYaxis()->SetTitle("Entries");

}
