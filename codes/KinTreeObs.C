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
#include <THStack.h>
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


int KinTreeObs()
{
  
  void SetHist(TH1F*& mjj1, TH1F*& mjj2);
  void ReadTree(TList*& tr, string signal, int year);
  TPad* PlotRatio(THStack *hs, TH1F *hsig, TH1F *h1, TH1F *h2, const char *cname, bool isLog);
  const int nofSamples = 8;
  const char *signals[] = {"TTbar", "singleTop", "MCQCDMu", "Wjets", "DYjets", "VBFusion",  "DataMu", "HminusM080"};
  int year = 2016;
  
  TList *list  = new TList();
  TH1F *hpt_kF[nofSamples], *heta_kF[nofSamples], *hmjj_kF[nofSamples];
  for(int isample = 0 ; isample < nofSamples ; isample++ ){
    string signal = signals[isample];
    hpt_kF[isample] = new TH1F(Form("_kb_pt_mu_jets_%s",signal.data()),Form("%s : hpt_kF",signal.c_str()), 200, -0.1, 0.1);
    
    heta_kF[isample] = new TH1F(Form("_kb_eta_mu_jets_%s",signal.data()),Form("%s : heta_kF",signal.c_str()), 30, -3., 3.);
    
    hmjj_kF[isample] = new TH1F(Form("_kb_mjj_mu_%s",signal.data()),Form("%s : hmjj_kF",signal.c_str()), 36, 0., 180.);
    list->Add(hpt_kF[isample]);

    list->Add(heta_kF[isample]);

    list->Add(hmjj_kF[isample]);
    ReadTree(list, signal, year);
  }
  
  for(int isample = nofSamples-1 ; isample >= 0 ; isample-- ){
    string signal = signals[isample];
    if(signal.find("VBFusion")!=string::npos){
      ((TH1F *) list->FindObject( Form("_kb_pt_mu_jets_%s",signal.data()) ))->SetFillColor(kGreen+2);
      ((TH1F *) list->FindObject( Form("_kb_eta_mu_jets_%s",signal.data()) ))->SetFillColor(kGreen+2);
      ((TH1F *) list->FindObject( Form("_kb_mjj_mu_%s",signal.data()) ))->SetFillColor(kGreen+2);
    }
    if(signal.find("DYjets")!=string::npos) {
      ((TH1F *) list->FindObject( Form("_kb_pt_mu_jets_%s",signal.data()) ))->SetFillColor(kOrange+1);
      ((TH1F *) list->FindObject( Form("_kb_eta_mu_jets_%s",signal.data()) ))->SetFillColor(kOrange+1);
      ((TH1F *) list->FindObject( Form("_kb_mjj_mu_%s",signal.data()) ))->SetFillColor(kOrange+1);
    }
    if(signal.find("Wjets")!=string::npos) {
      ((TH1F *) list->FindObject( Form("_kb_pt_mu_jets_%s",signal.data()) ))->SetFillColor(kYellow+1);
      ((TH1F *) list->FindObject( Form("_kb_eta_mu_jets_%s",signal.data()) ))->SetFillColor(kYellow+1);
      ((TH1F *) list->FindObject( Form("_kb_mjj_mu_%s",signal.data()) ))->SetFillColor(kYellow+1);
    }
    if(signal.find("MCQCDMu")!=string::npos) {
      ((TH1F *) list->FindObject( Form("_kb_pt_mu_jets_%s",signal.data()) ))->SetFillColor(kBlue);
      ((TH1F *) list->FindObject( Form("_kb_eta_mu_jets_%s",signal.data()) ))->SetFillColor(kBlue);
      ((TH1F *) list->FindObject( Form("_kb_mjj_mu_%s",signal.data()) ))->SetFillColor(kBlue);
    }
    if(signal.find("singleTop")!=string::npos) {
      ((TH1F *) list->FindObject( Form("_kb_pt_mu_jets_%s",signal.data()) ))->SetFillColor(kViolet);
      ((TH1F *) list->FindObject( Form("_kb_eta_mu_jets_%s",signal.data()) ))->SetFillColor(kViolet);
      ((TH1F *) list->FindObject( Form("_kb_mjj_mu_%s",signal.data()) ))->SetFillColor(kViolet);
    }
    if(signal.find("TTbar")!=string::npos) {
      ((TH1F *) list->FindObject( Form("_kb_pt_mu_jets_%s",signal.data()) ))->SetFillColor(kCyan+1);
      ((TH1F *) list->FindObject( Form("_kb_eta_mu_jets_%s",signal.data()) ))->SetFillColor(kCyan+1);
      ((TH1F *) list->FindObject( Form("_kb_mjj_mu_%s",signal.data()) ))->SetFillColor(kCyan+1);
    }
    
    if(signal.find("HminusM")!=string::npos or signal.find("HplusM")!=string::npos) {
      ((TH1F *) list->FindObject( Form("_kb_pt_mu_jets_%s",signal.data()) ))->SetLineColor(kRed);
      ((TH1F *) list->FindObject( Form("_kb_eta_mu_jets_%s",signal.data()) ))->SetLineColor(kRed);
      ((TH1F *) list->FindObject( Form("_kb_mjj_mu_%s",signal.data()) ))->SetLineColor(kRed);
    }
    if(signal.find("Data")!=string::npos) {
      ((TH1F *) list->FindObject( Form("_kb_pt_mu_jets_%s",signal.data()) ))->SetMarkerStyle(kFullCircle);
      ((TH1F *) list->FindObject( Form("_kb_eta_mu_jets_%s",signal.data()) ))->SetMarkerStyle(kFullCircle);
      ((TH1F *) list->FindObject( Form("_kb_mjj_mu_%s",signal.data()) ))->SetMarkerStyle(kFullCircle);
    }
  }
  
  TH1F *hbkg_pt = 0x0; 
  TH1F *hbkg_eta = 0x0; 
  TH1F *hbkg_mjj = 0x0; 
  THStack *hs_pt = new THStack("hs_pt","");
  THStack *hs_eta = new THStack("hs_eta","");
  THStack *hs_mjj = new THStack("hs_mjj","");
  for(int isample = nofSamples-1-2 ; isample >= 0 ; isample-- ){
    cout << "isample : " << hmjj_kF[isample]->GetName() << ", Integral : " << hmjj_kF[isample]->Integral() << endl;
    hs_pt->Add(hpt_kF[isample]);
    hs_eta->Add(heta_kF[isample]);
    hs_mjj->Add(hmjj_kF[isample]);
    if(isample == nofSamples-1-2){
      hbkg_pt = (TH1F *)hpt_kF[isample]->Clone("hbkg_pt");
      hbkg_eta = (TH1F *)heta_kF[isample]->Clone("hbkg_eta");
      hbkg_mjj = (TH1F *)hmjj_kF[isample]->Clone("hbkg_mjj");
    }else{
      hbkg_pt->Add(hpt_kF[isample]);
      hbkg_eta->Add(heta_kF[isample]);
      hbkg_mjj->Add(hmjj_kF[isample]);
    }
  }
  
  
  gStyle->SetOptStat(1002111);
  
  PlotRatio(hs_pt, hpt_kF[nofSamples-1], hpt_kF[nofSamples-2], hbkg_pt, "c2", 1);
  // PlotRatio(hs_eta, heta_kF[nofSamples-1], heta_kF[nofSamples-2], hbkg_eta, "c3", 1);
  PlotRatio(hs_mjj, hmjj_kF[nofSamples-1], hmjj_kF[nofSamples-2], hbkg_mjj, "c4", 0);
  
  hbkg_pt->Scale(1/hbkg_pt->Integral());

  TFile *fout = new TFile("output.root", "recreate");
  TCanvas *canvas = (TCanvas *)gROOT->GetListOfCanvases()->FindObject("c4");
  canvas->Write();
  TCanvas *canvas1 = (TCanvas *)gROOT->GetListOfCanvases()->FindObject("c2");
  canvas1->Write();
  hbkg_pt->Write(); //total bkg
  hpt_kF[nofSamples-2]->Write(); //signal
  hpt_kF[nofSamples-1]->Write(); //data
  hbkg_eta->Write();
  heta_kF[nofSamples-2]->Write();
  heta_kF[nofSamples-1]->Write();
  hbkg_mjj->Write();
  hmjj_kF[nofSamples-2]->Write();
  hmjj_kF[nofSamples-1]->Write();
  fout->Close();
  
  delete fout;

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


void ReadTree(TList*& list, string signal, int year)
{
  
  Double_t  chi2;
  Int_t  ndf;
  Float_t   jetBlepPt;
  Float_t   jetBlepEta;
  Float_t   jetBhadPt;
  Float_t   jetBhadEta;
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
  
  string inpath_tree = Form("/run/media/indra/DHEP_Storage_3/Data/NanoAOD/KinFit/CBA_CTagnPUJetID/%d",year);
  string treelist = "/tmp/fl_tree_list.txt";
  string command = Form("find %s -name \"%s_tree_base_*.root\" > %s",inpath_tree.data(),signal.data(),treelist.data());
  system(command.c_str());
  
  cout<<"filepath : " << inpath_tree.data() << endl;
  string flist;
  ifstream fin(treelist);
  TChain *tr	= new TChain("Kinfit_Reco");
  while ( getline(fin,flist)){
    //cout << "Filename : " << flist << endl;
    tr->Add(flist.c_str());
  }
  fin.close();

  tr->SetBranchAddress("chi2"		, &chi2);
  tr->SetBranchAddress("ndf"		, &ndf);
  tr->SetBranchAddress("jetBlepPt"	, &jetBlepPt);
  tr->SetBranchAddress("jetBlepEta"	, &jetBlepEta);
  tr->SetBranchAddress("jetBhadPt"	, &jetBhadPt);
  tr->SetBranchAddress("jetBhadEta"	, &jetBhadEta);
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
  
  float Min_pt = 25.0;
  float Max_eta = 2.4;

  cout << "Signal : " << signal << ", Total Entries : " << tr->GetEntries() << endl;
  for (Long64_t ievent = 0 ; ievent < tr->GetEntries() ; ievent++ ) {    
  //for (Long64_t ievent = 0 ; ievent < tr->GetEntries()/4 ; ievent++ ) {    
    
    tr->GetEntry(ievent) ;
    if(ievent%1000000==0)
      cout<<"iEvent : " << ievent << ", chi2 : "<<chi2<<endl;
    chad.SetPtEtaPhiE(jetChadPt, jetChadEta, jetChadPhi, jetChadEn);
    shad.SetPtEtaPhiE(jetShadPt, jetShadEta, jetShadPhi, jetShadEn);
    met.SetXYZM(metPx, metPy, metPz, 0.0);

    weight = sampleWeight*prefireWeight*PUWeight*muEffWeight*puJetIDWeight*bTagWeight;
    
    mjjKF = (chad+shad).M();
    //bool etaCut = abs(jetShadEta) < 2.4 and 
    bool isPtCut = (jetShadPt > Min_pt and jetChadPt > Min_pt and jetBhadPt > Min_pt and jetBlepPt > Min_pt);
    bool isEtaCut = (abs(jetShadEta) < Max_eta and abs(jetChadEta) < Max_eta and abs(jetBhadEta) < Max_eta and abs(jetBlepEta) < Max_eta);
    if(singleMu and !singleEle and muonIsoCut and !isLowMET and isPtCut and isEtaCut){
    //if(singleMu and !singleEle and muonIsoCut and !isLowMET){
      
      //mjj->Fill(mjjKF,weight);

      // ((TH1F *) list->FindObject( Form("_kb_pt_mu_jets_%s",signal.data()) ))->Fill(jetChadPt, weight);
      // ((TH1F *) list->FindObject( Form("_kb_pt_mu_jets_%s",signal.data()) ))->Fill(jetShadPt, weight);

      ((TH1F *) list->FindObject( Form("_kb_pt_mu_jets_%s",signal.data()) ))->Fill(chad.M(), weight);
      ((TH1F *) list->FindObject( Form("_kb_pt_mu_jets_%s",signal.data()) ))->Fill(shad.M(), weight);
      
      ((TH1F *) list->FindObject( Form("_kb_eta_mu_jets_%s",signal.data()) ))->Fill(jetChadEta, weight);
      ((TH1F *) list->FindObject( Form("_kb_eta_mu_jets_%s",signal.data()) ))->Fill(jetShadEta, weight);

      ((TH1F *) list->FindObject( Form("_kb_mjj_mu_%s",signal.data()) ))->Fill(mjjKF, weight);

      if(isCTagged){
	;
	// // Exclusive c-tagging
  	// if(count_cJetsIncT>0)
  	//   mjj_exclT->Fill(mjjKF,weight*cTagTWeight);
  	// else if(count_cJetsIncM > 0)
  	//   mjj_exclM->Fill(mjjKF,weight*cTagMWeight);
  	// else if(count_cJetsIncL > 0)
  	//   mjj_exclL->Fill(mjjKF,weight*cTagLWeight);
  	// else
  	//   mjj_excl0->Fill(mjjKF,weight);
	
	// // Inclusive c-tagging
  	// if(count_cJetsIncT>0)
  	//   mjj_inclT->Fill(mjjKF,weight*cTagTWeight);
  	// if(count_cJetsIncM>0)
  	//   mjj_inclM->Fill(mjjKF,weight*cTagMWeight);
  	// if(count_cJetsIncL>0)
  	//   mjj_inclL->Fill(mjjKF,weight*cTagLWeight);
  
      }
    }
  }//event loop
  
  printf("%s : Integral %lf\n", signal.c_str(), ((TH1F *) list->FindObject( Form("_kb_mjj_mu_%s",signal.data()) ))->Integral());

  delete tr;
}

//TPad* PlotRatio(THStack *hs, TH1D *hsig, TH1D *h1, TH1D *h2,TGraphAsymmErrors *syst, TGraphAsymmErrors *systRatio, const char *cname, bool isLog)
TPad* PlotRatio(THStack *hs, TH1F *hsig, TH1F *h1, TH1F *h2, const char *cname, bool isLog)
{

  TCanvas *canvas = (TCanvas *)gROOT->GetListOfCanvases()->FindObject(cname);
  TPad *pad1 = 0x0;

  if(!canvas){
    TCanvas *c = new TCanvas(cname, cname, 800, 800);
 
    // Upper plot will be in pad1
    pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
    pad1->SetBottomMargin(0.01); // Upper and lower plot are joined
    //pad1->SetGridx();         // Vertical grid
    if(isLog) pad1->SetLogy();
    pad1->Draw();             // Draw the upper pad: pad1
    pad1->cd();               // pad1 becomes the current pad
    pad1->SetTickx();
    pad1->SetTicky();
    h1->SetStats(0);          // No statistics on upper plot
    h1->Draw("e1p");               // Draw h1
    //syst->SetFillColorAlpha(kRed,0.7);
    // h2->Draw("hist same");         // Draw h2 on top of h1
    hs->Draw("same hist");
    //syst->Draw("e2 sames");
    h1->Draw("e1p sames");               // Draw h1
    hsig->Draw("hist sames");               // Draw hsig

#if ROOT_VERSION_CODE >= ROOT_VERSION(6,8,0)
    // Avoid the first label (0) to be clipped.
    TAxis *axis = h1->GetYaxis();
    axis->ChangeLabel(1, -1, -1, -1, -1, -1, " ");
    axis->SetLabelFont(43); // Absolute font size in pixel (precision 3)
    axis->SetLabelSize(15);
#else
    // Do not draw the Y axis label on the upper plot and redraw a small
    // axis instead, in order to avoid the first label (0) to be clipped.
    h1->GetYaxis()->SetLabelSize(0.);
    TGaxis *axis = new TGaxis( -5, 20, -5, 220, 20,220,510,"");
    axis->SetLabelFont(43); // Absolute font size in pixel (precision 3)
    axis->SetLabelSize(15);
    axis->Draw();
#endif
 
    // lower plot will be in pad2
    c->cd();          // Go back to the main canvas before defining pad2
    TPad *pad2 = new TPad("pad2", "pad2", 0, 0.01, 1, 0.3);
    pad2->SetTopMargin(0.05);
    pad2->SetBottomMargin(0.2);
    pad2->SetGridx(); // vertical grid
    pad2->SetGridy(); // vertical grid
    pad2->Draw();
    pad2->cd();       // pad2 becomes the current pad
    pad2->SetTickx();
    pad2->SetTicky();

    //pad2->Range(-61.81533,0.01758623,562.5978,1.572414);
    //pad2->SetFillColor(0);
    //pad2->SetBorderMode(0);
    //pad2->SetBorderSize(2);
    //pad2->SetGridy();
    //pad2->SetTickx(1);
    //pad2->SetTicky(1);
    pad2->SetTopMargin(0.004657352);
    pad2->SetBottomMargin(0.3102683);
    //pad2->SetFrameBorderMode(0);
    //pad2->SetFrameBorderMode(0);

 
    // Define the ratio plot
    TH1F *h3 = (TH1F*)h1->Clone("h3");
    h3->SetLineColor(h1->GetLineColor());
    h3->SetMinimum(0.9);  // Define Y ..
    h3->SetMaximum(1.2); // .. range
    // h3->SetMinimum(0.93);  // Define Y ..
    // h3->SetMaximum(1.07); // .. range
    // h3->SetMinimum(0.4);  // Define Y ..
    // h3->SetMaximum(1.6); // .. range
    // h3->SetMinimum(0.8);  // Define Y ..
    // h3->SetMaximum(1.2); // .. range
    // h3->SetMinimum(0.5);  // Define Y ..
    // h3->SetMaximum(1.5); // .. range
    h3->Sumw2();
    h3->SetStats(0);      // No statistics on lower plot
    h3->Divide(h2);
    //h3->SetMarkerStyle(21);
    h3->SetMarkerColor(kBlack);
    //h3->SetFillColor(kRed);
    h3->Draw("p");       // Draw the ratio plot
    //systRatio->SetFillColorAlpha(kRed-9,0.001);
    //systRatio->SetFillColorAlpha(kRed,0.7);
    //systRatio->Draw("e2 sames");
    h3->Draw("p sames");       // Draw the ratio plot
    // h1 settings
    //h1->SetLineColor(kBlue+1);
    //h1->SetLineWidth(2);
 
    // Y axis h1 plot settings
    //h1->GetYaxis()->SetTitle(Form("Entries / %1.0f GeV",h1->GetBinWidth(2)));
    h1->GetYaxis()->SetTitle("Entries / bin");
    h1->GetYaxis()->SetTitleSize(25);
    h1->GetYaxis()->SetTitleFont(43);
    h1->GetYaxis()->SetTitleOffset(1.4);
    h1->GetYaxis()->SetLabelSize(25);

    h1->GetXaxis()->SetTitleOffset(3.5);
    h1->GetXaxis()->SetLabelOffset(0.1);
 
    // h2 settings
    //h2->SetLineColor(kRed);
    //h2->SetLineWidth(2);
 
    // Ratio plot (h3) settings
    h3->SetTitle(""); // Remove the ratio title
 
    // Y axis ratio plot settings
    h3->GetYaxis()->SetTitle("#frac{Data}{Bkg}");
    h3->GetYaxis()->SetNdivisions(505);
    h3->GetYaxis()->SetTitleSize(25);
    h3->GetYaxis()->SetTitleFont(43);
    h3->GetYaxis()->SetTitleOffset(1.2);
    h3->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
    h3->GetYaxis()->SetLabelSize(25);
 
    // X axis ratio plot settings
    h3->GetXaxis()->SetTitle(h1->GetXaxis()->GetTitle());
    h3->GetXaxis()->SetTitleSize(25);
    h3->GetXaxis()->SetTitleFont(43);
    h3->GetXaxis()->SetTitleOffset(3.6);
    h3->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
    h3->GetXaxis()->SetLabelSize(25);
    
    pad1->cd();

    cout<<" nof canvas primitives " << c->GetListOfPrimitives()->GetEntries() << endl ;
    
  }else {

    pad1 = (TPad *)canvas->GetListOfPrimitives()->FindObject("pad1") ;
    pad1->cd();
    
    h1->Draw("hist same");             
    h2->Draw("hist same");         
    
    TPad *pad2 = (TPad *)canvas->GetListOfPrimitives()->FindObject("pad2") ;
    pad2->cd();
    

    TH1F *h3 = (TH1F*)h1->Clone("h3");
    h3->SetLineColor(h1->GetLineColor());
    h3->Sumw2();
    h3->SetStats(0);      // No statistics on lower plot
    h3->Divide(h2);
    h3->Draw("ep same");       // Draw the ratio plot
    
    pad1->cd();
  }

  return pad1;
}
