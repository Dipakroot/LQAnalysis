/**********************************************************************
 Created on : 01/06/2021
 Purpose    : Read the Kinematic fit info from KinTree
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


int KinTreeMjj()
{
  TH1F *mjj = new TH1F("mjj","mjj (Inclussive)", 250, 0., 250.);
  TH1F *mjj_cut1 = new TH1F("mjj_cut1","mjj (#chi^2 < 50.)", 250, 0., 250.);
  TH1F *mjj_cut2 = new TH1F("mjj_cut2","mjj (#chi^2 < 20.)", 250, 0., 250.);
  TH1F *mjj_cut3 = new TH1F("mjj_cut3","mjj (#chi^2 < 8.)", 250, 0., 250.);
  
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
  Double_t bTagWeight;
  Bool_t singleMu;
  Bool_t singleEle;
  Bool_t muonIsoCut;
  Bool_t isLowMET;
  Double_t weight, mjjKF;

  // TFile *fin	= TFile::Open("/Data/root_files/KFFiles/BeforeOffSet/TTbar_Before_OffSet.root");
  // TFile *finhist      = TFile::Open("/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/grid_v39_Syst/CBA_KFTest1/2017/all_TTbar.root");

  // TFile *fin	= TFile::Open("/Data/root_files/KFFiles/ApresOffSet/TTbar_Apres_OffSet.root");
  // TFile *finhist      = TFile::Open("/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/grid_v39_Syst/CBA_KFTest2/2017/all_TTbar.root");
  
  // TFile *fin	= TFile::Open("/Data/CMS-Analysis/NanoAOD-Analysis/Git_KinFit_Skim/KinFit_Skim/CBA_Skim/TTbar_tree_base_1of2.root");
  // TFile *finhist      = TFile::Open("/Data/CMS-Analysis/NanoAOD-Analysis/Git_KinFit_Skim/KinFit_Skim/CBA_Skim/TTbar_hist_base_1of2.root");

  // TFile *fin	= TFile::Open("/eos/user/s/savarghe/Indra_Da/Output/cms-hcs-run2/CBA_KFTest1/2017/TTbar_Before_OffSet.root");
  // TFile *finhist      = TFile::Open("/eos/user/i/idas/Output/cms-hcs-run2/CBA_KFTest1/2017/all/all_TTbar.root");


  // TFile *fin	= TFile::Open("/eos/user/s/savarghe/Indra_Da/Output/cms-hcs-run2/CBA_KFTest2/2017/TTbar_Apres_NegOffSet.root");
  // TFile *finhist      = TFile::Open("/eos/user/i/idas/Output/cms-hcs-run2/CBA_KFTest2/2017/all/all_TTbar.root");

  // TFile *fin	= TFile::Open("/eos/user/s/savarghe/Indra_Da/Output/cms-hcs-run2/CBA_KFTest3/2017/TTbar_Apres_PosOffSet.root");
  // TFile *finhist      = TFile::Open("/eos/user/i/idas/Output/cms-hcs-run2/CBA_KFTest3/2017/all/all_TTbar.root");

  // TFile *fin	= TFile::Open("/eos/user/s/savarghe/Indra_Da/Output/cms-hcs-run2/CBA_KFTest1/2017/HplusM160_tree_base_1of1.root");
  // TFile *finhist      = TFile::Open("/eos/user/i/idas/Output/cms-hcs-run2/CBA_KFTest1/2017/HplusM160_hist_base_1of1.root");

  TFile *fin	= TFile::Open("/eos/user/s/savarghe/Indra_Da/Output/cms-hcs-run2/CBA_KFTest2/2017/HplusM160_tree_base_1of1.root");
  TFile *finhist      = TFile::Open("/eos/user/i/idas/Output/cms-hcs-run2/CBA_KFTest2/2017/HplusM160_hist_base_1of1.root");

  cout<<"filename : " << fin->GetName() << endl;
  TTree *tr	= (TTree*)fin->Get("Kinfit_Reco");
  // TH1F *hMjjSaved = (TH1F *)finhist->Get("TTbar/base/Iso/_kb_mjj_mu");
  // TH1F *hChi2Min1 = (TH1F *)finhist->Get("TTbar/base/Iso/hMinChi2_mu");
  // TH1F *hChi2Min2 = (TH1F *)finhist->Get("TTbar/base/Iso/h2MinChi2_mu");
  // TH1F *hChi2Min3 = (TH1F *)finhist->Get("TTbar/base/Iso/h3MinChi2_mu");
  // TH1F *hChi2Min4 = (TH1F *)finhist->Get("TTbar/base/Iso/h4MinChi2_mu");
  // TH1F *hChi2Min5 = (TH1F *)finhist->Get("TTbar/base/Iso/h5MinChi2_mu");

  TH1F *hMjjSaved = (TH1F *)finhist->Get("HplusM160/base/Iso/_kb_mjj_mu");
  TH1F *hChi2Min1 = (TH1F *)finhist->Get("HplusM160/base/Iso/hMinChi2_mu");
  TH1F *hChi2Min2 = (TH1F *)finhist->Get("HplusM160/base/Iso/h2MinChi2_mu");
  TH1F *hChi2Min3 = (TH1F *)finhist->Get("HplusM160/base/Iso/h3MinChi2_mu");
  TH1F *hChi2Min4 = (TH1F *)finhist->Get("HplusM160/base/Iso/h4MinChi2_mu");
  TH1F *hChi2Min5 = (TH1F *)finhist->Get("HplusM160/base/Iso/h5MinChi2_mu");
  
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
  tr->SetBranchAddress("bTagWeight"	, &bTagWeight);
  tr->SetBranchAddress("singleMu"	, &singleMu);
  tr->SetBranchAddress("singleEle"	, &singleEle);
  tr->SetBranchAddress("muonIsoCut"	, &muonIsoCut);
  tr->SetBranchAddress("isLowMET"	, &isLowMET);

  TLorentzVector chad, shad, met;
  
  cout << "Total Entries : " << tr->GetEntries() << endl;
  for (Long64_t ievent = 0 ; ievent < tr->GetEntries() ; ievent++ ) {    
  //for (Long64_t ievent = 0 ; ievent < 20000 ; ievent++ ) {    
    
    tr->GetEntry(ievent) ;
    if(ievent%1000000==0)
      cout<<"iEvent : " << ievent << ", chi2 : "<<chi2<<endl;
    chad.SetPtEtaPhiE(jetChadPt, jetChadEta, jetChadPhi, jetChadEn);
    shad.SetPtEtaPhiE(jetShadPt, jetShadEta, jetShadPhi, jetShadEn);
    met.SetXYZM(metPx, metPy, metPz, 0.0);

    weight = sampleWeight*prefireWeight*PUWeight*muEffWeight*bTagWeight;
    mjjKF = (chad+shad).M();
    //if(singleMu and !singleEle and muonIsoCut and !isLowMET){
    if(singleMu and !singleEle and muonIsoCut and met.Pt()>20.0){
      mjj->Fill(mjjKF,weight);
      if(chi2<50.) mjj_cut1->Fill(mjjKF,weight);
      if(chi2<20.) mjj_cut2->Fill(mjjKF,weight);
      if(chi2<8.) mjj_cut3->Fill(mjjKF,weight);
    }
  }//event loop
  fin->Close();
  delete fin;
  
  hMjjSaved->SetLineColor(kBlue);
  mjj->SetLineColor(kRed);
  mjj->SetLineWidth(2);
  mjj_cut1->SetLineColor(kBlue);
  mjj_cut1->SetLineWidth(2);
  mjj_cut2->SetLineColor(kGreen);
  mjj_cut2->SetLineWidth(2);
  mjj_cut3->SetLineColor(kMagenta);
  mjj_cut3->SetLineWidth(2);

  gStyle->SetOptStat(1112111);
  gStyle->SetOptFit(11);
  
  TF1 *fn = new TF1("fn","gaus",60.,100.);
  TCanvas *c1 = new TCanvas("c1","c1");
  mjj->Draw("hist");
  mjj_cut1->Draw("hist sames");
  mjj_cut2->Draw("hist sames");
  mjj_cut3->Draw("hist sames");
  //hMjjSaved->Draw("hist sames");
  mjj->Fit("fn","LR");
  mjj_cut1->Fit("fn","LR");
  mjj_cut2->Fit("fn","LR");
  mjj_cut3->Fit("fn","LR");
  //hMjjSaved->Fit("fn","LR");
  
  hChi2Min1->SetLineColor(kRed);
  hChi2Min1->SetLineWidth(2);
  hChi2Min2->SetLineColor(kBlue);
  hChi2Min2->SetLineWidth(2);
  hChi2Min3->SetLineColor(kGreen);
  hChi2Min3->SetLineWidth(2);
  hChi2Min4->SetLineColor(kMagenta);
  hChi2Min4->SetLineWidth(2);
  hChi2Min5->SetLineColor(kOrange+1);
  hChi2Min5->SetLineWidth(2);
  
  TCanvas *c2 = new TCanvas("c2","c2");
  hChi2Min1->Draw();
  hChi2Min2->Draw("sames");
  hChi2Min3->Draw("sames");
  hChi2Min4->Draw("sames");
  hChi2Min5->Draw("sames");

  TFile *fout = new TFile(Form("output.root"),"recreate");
  mjj->Write();
  mjj_cut1->Write();
  mjj_cut2->Write();
  mjj_cut3->Write();
  hMjjSaved->Write();
  c1->Write();
  c2->Write();
  fout->Close();
  delete fout;


  return true;
}
