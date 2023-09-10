/**********************************************************************
 Created on : 16/07/2022
 Purpose    : Prepare the histograms for analysis
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


int KinFitPurity()
{
  TH1F *mjj = new TH1F("mjj","mjj (Inclussive)", 2400, 0., 240.);
  TH1F *mjj_cut1 = new TH1F("mjj_cut1","mjj (Inclusive reweight)", 2400, 0., 240.);
  TH1F *mjj_cut2 = new TH1F("mjj_cut2","mjj (InclRw+passed ttbar #delta#phi > 2.0)", 2400, 0., 240.);
  TH1F *mjj_cut3 = new TH1F("mjj_cut3","mjj (InclRw+failed ttbar #delta#phi > 2.0)", 2400, 0., 240.);
  TH1F *mjj_cut4 = new TH1F("mjj_cut4","mjj (InclRw+#chi^{2} < 1.)", 2400, 0., 240.);
  TH1F *hDelPhi = new TH1F("hDelPhi","hDelPhi",100,-5.0,5.0);
  
  Double_t  chi2;
  Double_t  prob;
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
  Float_t   lepPt;
  Float_t   lepEta;
  Float_t   lepPhi;
  Float_t   lepEn;
  Float_t   jetBhadPt;
  Float_t   jetBhadEta;
  Float_t   jetBhadPhi;
  Float_t   jetBhadEn;
  Float_t   jetBlepPt;
  Float_t   jetBlepEta;
  Float_t   jetBlepPhi;
  Float_t   jetBlepEn;
  Int_t     nJet;
  
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

  Int_t kFType;
  bool found_GJ1_lhe;
  bool found_GJ2_lhe;
  bool found_cjhad_lhe;
  bool found_sjhad_lhe;
  Float_t   lhe1Pt;
  Float_t   lhe1Eta;
  Float_t   lhe1Phi;
  Float_t   lhe1En;
  Float_t   lhe2Pt;
  Float_t   lhe2Eta;
  Float_t   lhe2Phi;
  Float_t   lhe2En;
  Int_t lhe1PDG;
  Int_t lhe2PDG;
  Int_t chadPDG;
  Int_t shadPDG;
  
  string sig = "TTbar";
  string syst = "base";
  //string sample_extn = "CBA_CTagShapeCalib";
  //string sample_extn = "CBA_TTbarSLKFEff";
  string sample_extn = "CBA_TTbarSLKFEffDR4";
  //string sample_extn = "CBA_TTbarSLKFEffDR1MR";
  //string sample_extn = "CBA_TTbarSLKFEffDRVar";
  //string sample_extn = "CBA_TTbarSLKFEffDR4PECons";
  string input_path = "/run/media/indra/DHEP_Storage_3/Data/NanoAOD/KinFit/"+sample_extn+"/post/2016/";
  string input_file_list = "/tmp/histbuild_fl.txt";
  string input_hist_file = "root_files/grid_v40_Syst/"+sample_extn+"/post/all_TTbar.root";
  string command  = Form("find %s -name \"%s_tree_%s\*.root\" > %s",input_path.c_str(), sig.c_str(), syst.c_str(), input_file_list.c_str());
  cout << command << endl;
  system(command.c_str());

  TChain *tr = new TChain("Kinfit_Reco");
  ifstream fin(input_file_list.c_str());
  string s;
  string inputname = input_file_list.substr(input_file_list.find_last_of("/")+1,input_file_list.find_last_of(".")-input_file_list.find_last_of("/")-1);
  cout << "input filename name : " << inputname << endl;
  int i = 1;
  while(getline(fin,s)){
    cout << "Adding file with index : " << i << " and filename : " <<  s << endl;
    tr->Add(s.c_str());
    i++;
  }
  fin.close();
  cout << "Total Files : " << i-1 << ", Events : " << tr->GetEntries() << endl;
  
  TFile *finhist      = TFile::Open(input_hist_file.c_str());
  TH1D *hWtBefore = (TH1D *)finhist->Get(Form("%s/%s/Iso/_wt_before",sig.c_str(),syst.c_str()));
  TH1D *hWtAfter =  (TH1D *)finhist->Get(Form("%s/%s/Iso/_wt_after",sig.c_str(),syst.c_str()));
  TH1F *hMjjSaved = (TH1F *)finhist->Get(Form("%s/%s/Iso/_kb_mjj_mu",sig.c_str(),syst.c_str()));
  
  // hWtBefore->SetLineColor(kRed);
  // hWtBefore->SetMarkerColor(kRed);
  // new TCanvas();
  // hWtBefore->Draw("hist");
  // hWtAfter->Draw("hist sames");
    
  // cout<<"filename : " << fin->GetName() << endl;
  // TTree *tr	= (TTree*)fin->Get("Kinfit_Reco");

  // TH1F *hMjjSaved = (TH1F *)finhist->Get("HplusM160/base/Iso/_kb_mjj_mu");
  // TH1F *hChi2Min1 = (TH1F *)finhist->Get("HplusM160/base/Iso/hMinChi2_mu");
  // TH1F *hChi2Min2 = (TH1F *)finhist->Get("HplusM160/base/Iso/h2MinChi2_mu");
  // TH1F *hChi2Min3 = (TH1F *)finhist->Get("HplusM160/base/Iso/h3MinChi2_mu");
  // TH1F *hChi2Min4 = (TH1F *)finhist->Get("HplusM160/base/Iso/h4MinChi2_mu");
  // TH1F *hChi2Min5 = (TH1F *)finhist->Get("HplusM160/base/Iso/h5MinChi2_mu");
  
  tr->SetBranchAddress("chi2"		, &chi2);
  tr->SetBranchAddress("prob"		, &prob);
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
  tr->SetBranchAddress("lepPt"	, &lepPt);
  tr->SetBranchAddress("lepEta"	, &lepEta);
  tr->SetBranchAddress("lepPhi"	, &lepPhi);
  tr->SetBranchAddress("lepEnergy"	, &lepEn);
  tr->SetBranchAddress("jetBhadPt"	, &jetBhadPt);
  tr->SetBranchAddress("jetBhadEta"	, &jetBhadEta);
  tr->SetBranchAddress("jetBhadPhi"	, &jetBhadPhi);
  tr->SetBranchAddress("jetBhadEnergy"	, &jetBhadEn);
  tr->SetBranchAddress("jetBlepPt"	, &jetBlepPt);
  tr->SetBranchAddress("jetBlepEta"	, &jetBlepEta);
  tr->SetBranchAddress("jetBlepPhi"	, &jetBlepPhi);
  tr->SetBranchAddress("jetBlepEnergy"	, &jetBlepEn);

  tr->SetBranchAddress("nJet"		, &nJet);

  tr->SetBranchAddress("sampleWeight"	, &sampleWeight);
  tr->SetBranchAddress("prefireWeight"	, &prefireWeight);
  tr->SetBranchAddress("PUWeight"	, &PUWeight);
  tr->SetBranchAddress("muEffWeight"	, &muEffWeight);
  tr->SetBranchAddress("bcTagWeight"	, &bTagWeight);
  tr->SetBranchAddress("singleMu"	, &singleMu);
  tr->SetBranchAddress("singleEle"	, &singleEle);
  tr->SetBranchAddress("muonIsoCut"	, &muonIsoCut);
  tr->SetBranchAddress("isLowMET"	, &isLowMET);
  
  tr->SetBranchAddress("kFType", &kFType);
  tr->SetBranchAddress("found_GJ1_lhe", &found_GJ1_lhe);
  tr->SetBranchAddress("found_GJ2_lhe", &found_GJ2_lhe);
  tr->SetBranchAddress("found_cjhad_lhe", &found_cjhad_lhe);
  tr->SetBranchAddress("found_sjhad_lhe", &found_sjhad_lhe);
  tr->SetBranchAddress("lhe1Pt", &lhe1Pt);
  tr->SetBranchAddress("lhe1Eta", &lhe1Eta);
  tr->SetBranchAddress("lhe1Phi", &lhe1Phi);
  tr->SetBranchAddress("lhe1Energy", &lhe1En);
  tr->SetBranchAddress("lhe2Pt", &lhe2Pt);
  tr->SetBranchAddress("lhe2Eta", &lhe2Eta);
  tr->SetBranchAddress("lhe2Phi", &lhe2Phi);
  tr->SetBranchAddress("lhe2Energy", &lhe2En);
  tr->SetBranchAddress("lhe1PDG", &lhe1PDG);
  tr->SetBranchAddress("lhe2PDG", &lhe2PDG);
  tr->SetBranchAddress("chadPDG", &chadPDG);
  tr->SetBranchAddress("shadPDG", &shadPDG);

  TLorentzVector chad, shad, met, bhad, lep, blep, top, tbar;
  float wt_before, wt_after, wt_ratio;
  Long64_t totSl = 0, totcjhad = 0, totsjhad = 0, totwboson = 0, totgj1 = 0, totgj2 = 0, totgjw = 0;
  cout << "Total Entries : " << tr->GetEntries() << endl;
  for (Long64_t ievent = 0 ; ievent < tr->GetEntries() ; ievent++ ) {    
  //for (Long64_t ievent = 0 ; ievent < 20000 ; ievent++ ) {    
  //for (Long64_t ievent = 0 ; ievent < 5 ; ievent++ ) {
    
    tr->GetEntry(ievent) ;
    if(ievent%1000000==0)
      cout<<"iEvent : " << ievent << ", chi2 : "<<chi2<<endl;
    chad.SetPtEtaPhiE(jetChadPt, jetChadEta, jetChadPhi, jetChadEn);
    shad.SetPtEtaPhiE(jetShadPt, jetShadEta, jetShadPhi, jetShadEn);
    met.SetXYZM(metPx, metPy, metPz, 0.0);
    bhad.SetPtEtaPhiE(jetBhadPt, jetBhadEta, jetBhadPhi, jetBhadEn);
    blep.SetPtEtaPhiE(jetBlepPt, jetBlepEta, jetBlepPhi, jetBlepEn);
    lep.SetPtEtaPhiE(lepPt, lepEta, lepPhi, lepEn);

    top = bhad + chad + shad;
    tbar = blep + lep + met;
    
    wt_before = hWtBefore->GetBinContent(nJet+1);
    wt_after = hWtAfter->GetBinContent(nJet+1);
    wt_ratio = wt_before/wt_after;
    //cout <<"nJet : "<< nJet << ", wt_before : "<<wt_before <<", wt_after : " << wt_after << ", wt_ratio : " << wt_ratio << endl;
    
    weight = sampleWeight*prefireWeight*PUWeight*muEffWeight*bTagWeight;
    mjjKF = (chad+shad).M();
    if(singleMu and !singleEle and muonIsoCut and !isLowMET){
    //if(singleMu and !singleEle and muonIsoCut and met.Pt()>20.0){
      
      // if(TMath::Abs(top.DeltaPhi(tbar))>2.5)
      // 	mjj_cut2->Fill(mjjKF,weight*wt_ratio);
      // //else
	
      // if(chi2<3.) { //chi^2<2 ~= DelPhi>2.7 // chi^2<10 ~= DelPhi>1.5 // chi^2<5 ~= DelPhi>2.2
      // 	mjj_cut4->Fill(mjjKF,weight*wt_ratio);
      // 	hDelPhi->Fill(TMath::Abs(top.DeltaPhi(tbar)));
      // }//else	
      
	      //if(kFType==13 and nJet==5 and chi2<3.0 and TMath::Abs(top.DeltaPhi(tbar))>2.5){
       if(kFType==13){
	 mjj->Fill(mjjKF,weight);
       }
       if(kFType==13 and nJet==4){
	
	mjj_cut1->Fill(mjjKF,weight*wt_ratio);
	
	totSl++;
	if(found_cjhad_lhe) totcjhad++ ;
	if(found_sjhad_lhe) totsjhad++ ;
	if(found_GJ1_lhe) totgj1++ ;
	if(found_GJ2_lhe) totgj2++ ;
	if(found_GJ1_lhe and found_GJ2_lhe) totgjw++;
	if(found_cjhad_lhe and found_sjhad_lhe){
	  totwboson++;
	  mjj_cut3->Fill(mjjKF,weight*wt_ratio);
	}
      }//kfType 13
       
    }
  }//event loop
  printf("Processed : %s\n",sample_extn.c_str());
  printf("Total number of Semileptonic events passed KF : %lld\n",totSl);
  printf("Total number of mathched lhe W-boson found : %lld\n",totwboson);
  printf("Total number of mathched cjhad found : %lld\n",totcjhad);
  printf("Total number of mathched sjhad found : %lld\n",totsjhad);
  printf("Total number of mathched gj1 found : %lld\n",totgj1);
  printf("Total number of mathched gj2 found : %lld\n",totgj2);
  printf("Total number of mathched gjw found : %lld\n",totgjw);
  printf("Inclusive purity : %5.3lf(\%)\n",100.*double(totwboson)/double(totSl));
  printf("WRT GJ purity : %5.3lf(\%)\n",100.*double(totwboson)/double(totgjw));
  
  hMjjSaved->SetLineColor(kBlue);
  mjj->SetLineColor(kRed);
  mjj->SetLineWidth(2);
  mjj_cut1->SetLineColor(kBlue);
  mjj_cut1->SetLineWidth(2);
  mjj_cut2->SetLineColor(kGreen);
  mjj_cut2->SetLineWidth(2);
  mjj_cut3->SetLineColor(kMagenta);
  mjj_cut3->SetLineWidth(2);
  mjj_cut4->SetLineColor(kBlack);
  mjj_cut4->SetLineWidth(2);
  
  gStyle->SetOptStat(1112111);
  // gStyle->SetOptFit(11);
  
  // TF1 *fn = new TF1("fn","gaus",60.,100.);
  TCanvas *c1 = new TCanvas("c1","c1");
  //hMjjSaved->Draw("hist");
  //mjj->Draw("hist sames");
  mjj_cut1->Draw("hist sames");
  // mjj_cut2->Draw("hist sames");
  mjj_cut3->Draw("hist sames");
  //mjj_cut4->Draw("hist sames");
  //hMjjSaved->Draw("hist sames");
  
  // TCanvas *c2 = new TCanvas("c2","c2");
  // hMjjSaved->Draw("hist sames");

  // TCanvas *c3 = new TCanvas("c3","c3");
  // hDelPhi->Draw("hist sames");
  
  TFile *fout = new TFile(Form("root_files/test/output_purity.root"),"recreate");
  mjj->Write();
  mjj_cut1->Write();
  mjj_cut2->Write();
  mjj_cut3->Write();
  mjj_cut4->Write();
  hMjjSaved->Write();
  c1->Write();
  // c2->Write();
  // c3->Write();
  fout->Close();
  delete fout;


  return true;
}
