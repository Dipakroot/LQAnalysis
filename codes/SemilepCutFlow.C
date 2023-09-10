/**********************************************************************
 Created on : 25/11/2021
 Purpose    : Cutflow fot various sub decay channel of semileptonic decay of W
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

int SemilepCutFlow()
{
  void SetHistStyle(TH1F *h1, Color_t color, int width, int style);
  
  const char *inpath = "/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/proof_v37_SlStudy/CBA_Skim_Syst_SlStudy1/2016";
  // TFile *fin_incl = TFile::Open(Form("%s/all_TTbar_inclusive_sl_proof.root",inpath));  
  // TFile *fin_excl = TFile::Open(Form("%s/all_TTbar_exclusive_sl.root",inpath));
  TFile *fin_incl = TFile::Open(Form("%s/all_TTbar_inclusive_sl_proof_chi2cut8.root",inpath));  
  TFile *fin_excl = TFile::Open(Form("%s/all_TTbar_sl_proof_chi2cut8.root",inpath));
  // const char *inpath = "/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/grid_v37_Syst/CBA_Skim_Syst_SlStudy2/2016";
  // TFile *fin_incl = TFile::Open(Form("%s/all_TTbarincl.root",inpath));  
  // TFile *fin_excl = TFile::Open(Form("%s/all_TTbar.root",inpath));
  
  TFile *fin_data = TFile::Open(Form("%s/all_DataMu.root",inpath));
  TFile *fin_data_ele = TFile::Open(Form("%s/all_DataEle.root",inpath));
  
  TH1F *hCF_incl_slcs_mu = (TH1F *)fin_incl->Get("TTbar/base/Iso/_cutflow_nofSlcs_mu");
  TH1F *hCF_incl_slud_mu = (TH1F *)fin_incl->Get("TTbar/base/Iso/_cutflow_nofSlud_mu");
  TH1F *hCF_incl_slus_mu = (TH1F *)fin_incl->Get("TTbar/base/Iso/_cutflow_nofSlus_mu");
  TH1F *hCF_incl_sldc_mu = (TH1F *)fin_incl->Get("TTbar/base/Iso/_cutflow_nofSldc_mu");

  // TH1F *hCF_incl_slcs_mu = (TH1F *)fin_incl->Get("TTbarincl/base/Iso/_cutflow_nofSlcs_mu");
  // TH1F *hCF_incl_slud_mu = (TH1F *)fin_incl->Get("TTbarincl/base/Iso/_cutflow_nofSlud_mu");
  // TH1F *hCF_incl_slus_mu = (TH1F *)fin_incl->Get("TTbarincl/base/Iso/_cutflow_nofSlus_mu");
  // TH1F *hCF_incl_sldc_mu = (TH1F *)fin_incl->Get("TTbarincl/base/Iso/_cutflow_nofSldc_mu");

  TH1F *hCF_excl_slcs_mu = (TH1F *)fin_excl->Get("TTbar/base/Iso/_cutflow_nofSlcs_mu");
  TH1F *hCF_excl_slud_mu = (TH1F *)fin_excl->Get("TTbar/base/Iso/_cutflow_nofSlud_mu");
  TH1F *hCF_excl_slus_mu = (TH1F *)fin_excl->Get("TTbar/base/Iso/_cutflow_nofSlus_mu");
  TH1F *hCF_excl_sldc_mu = (TH1F *)fin_excl->Get("TTbar/base/Iso/_cutflow_nofSldc_mu");
  
  for(int ibin=1;ibin<hCF_incl_slcs_mu->GetNbinsX();ibin++){
    if(hCF_incl_slcs_mu->GetBinContent(ibin) <= 0.0 or hCF_excl_slcs_mu->GetBinContent(ibin) <= 0.0) continue;
    printf("bin : %01d, slcs Ratio (ex/in): %lf\n",ibin,hCF_excl_slcs_mu->GetBinContent(ibin)/hCF_incl_slcs_mu->GetBinContent(ibin));
  }

  for(int ibin=1;ibin<hCF_incl_slud_mu->GetNbinsX();ibin++){
    if(hCF_incl_slud_mu->GetBinContent(ibin) <= 0.0 or hCF_excl_slud_mu->GetBinContent(ibin) <= 0.0) continue;
    printf("bin : %01d, ud Ratio (ex/in): %lf\n",ibin,hCF_excl_slud_mu->GetBinContent(ibin)/hCF_incl_slud_mu->GetBinContent(ibin));
  }

  for(int ibin=1;ibin<hCF_incl_slus_mu->GetNbinsX();ibin++){
    if(hCF_incl_slus_mu->GetBinContent(ibin) <= 0.0 or hCF_excl_slus_mu->GetBinContent(ibin) <= 0.0) continue;
    printf("bin : %01d, slus Ratio (ex/in): %lf\n",ibin,hCF_excl_slus_mu->GetBinContent(ibin)/hCF_incl_slus_mu->GetBinContent(ibin));
  }
  
  for(int ibin=1;ibin<hCF_incl_sldc_mu->GetNbinsX();ibin++){
    if(hCF_incl_sldc_mu->GetBinContent(ibin) <= 0.0 or hCF_excl_sldc_mu->GetBinContent(ibin) <= 0.0) continue;
    printf("bin : %01d, dc Ratio (ex/in): %lf\n",ibin,hCF_excl_sldc_mu->GetBinContent(ibin)/hCF_incl_sldc_mu->GetBinContent(ibin));
  }

  // SetHistStyle(hMin1_incl_mu, kRed, 2, 1);
  // SetHistStyle(hMin2_incl_mu, kBlue, 2, 1);
  // SetHistStyle(hMin3_incl_mu, kGreen+2, 2, 1);
  // SetHistStyle(hMin4_incl_mu, kMagenta, 2, 1);
  // SetHistStyle(hMin1_excl_mu, kRed, 2, 1);
  // SetHistStyle(hMin2_excl_mu, kBlue, 2, 1);
  // SetHistStyle(hMin3_excl_mu, kGreen+2, 2, 1);
  // SetHistStyle(hMin4_excl_mu, kMagenta, 2, 1);
  // SetHistStyle(hMin1_data_mu, kRed, 2, 1);
  // SetHistStyle(hMin2_data_mu, kBlue, 2, 1);
  // SetHistStyle(hMin3_data_mu, kGreen+2, 2, 1);
  // SetHistStyle(hMin4_data_mu, kMagenta, 2, 1);


  // TCanvas *c1 = new TCanvas("c1","c1");
  // hMin1_incl_mu->Draw();
  // hMin2_incl_mu->Draw("sames");
  // hMin3_incl_mu->Draw("sames");
  // hMin4_incl_mu->Draw("sames");

  // TCanvas *c2 = new TCanvas("c2","c2");
  // hMin1_excl_mu->Draw();
  // hMin2_excl_mu->Draw("sames");
  // hMin3_excl_mu->Draw("sames");
  // hMin4_excl_mu->Draw("sames");

  // TCanvas *c3 = new TCanvas("c3","c3");
  // hMin1_data_mu->Draw();
  // hMin2_data_mu->Draw("sames");
  // hMin3_data_mu->Draw("sames");
  // hMin4_data_mu->Draw("sames");

  // SetHistStyle(hMin1_incl_ele, kRed, 2, 1);
  // SetHistStyle(hMin2_incl_ele, kBlue, 2, 1);
  // SetHistStyle(hMin3_incl_ele, kGreen+2, 2, 1);
  // SetHistStyle(hMin4_incl_ele, kMagenta, 2, 1);
  // SetHistStyle(hMin1_excl_ele, kRed, 2, 1);
  // SetHistStyle(hMin2_excl_ele, kBlue, 2, 1);
  // SetHistStyle(hMin3_excl_ele, kGreen+2, 2, 1);
  // SetHistStyle(hMin4_excl_ele, kMagenta, 2, 1);
  // SetHistStyle(hMin1_data_ele, kRed, 2, 1);
  // SetHistStyle(hMin2_data_ele, kBlue, 2, 1);
  // SetHistStyle(hMin3_data_ele, kGreen+2, 2, 1);
  // SetHistStyle(hMin4_data_ele, kMagenta, 2, 1);

  // TCanvas *c1_1 = new TCanvas("c1_1","c1_1");
  // hMin1_incl_ele->Draw();
  // hMin2_incl_ele->Draw("sames");
  // hMin3_incl_ele->Draw("sames");
  // hMin4_incl_ele->Draw("sames");

  // TCanvas *c2_1 = new TCanvas("c2_1","c2_1");
  // hMin1_excl_ele->Draw();
  // hMin2_excl_ele->Draw("sames");
  // hMin3_excl_ele->Draw("sames");
  // hMin4_excl_ele->Draw("sames");

  // TCanvas *c3_1 = new TCanvas("c3_1","c3_1");
  // hMin1_data_ele->Draw();
  // hMin2_data_ele->Draw("sames");
  // hMin3_data_ele->Draw("sames");
  // hMin4_data_ele->Draw("sames");
  
  return true;
}

void SetHistStyle(TH1F *h1, Color_t color, int width, int style)
{
  h1->SetLineColor(color);
  h1->SetLineWidth(width);
  h1->SetLineStyle(style);
  return;
}
