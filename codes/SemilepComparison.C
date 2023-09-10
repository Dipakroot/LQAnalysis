/**********************************************************************
 Created on : 25/11/2021
 Purpose    : Compare Chi2 for data and TTbar semilep cases
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

int SemilepComparison()
{
  void SetHistStyle(TH1F *h1, Color_t color, int width, int style);
  
  //const char *inpath = "/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/proof_v37_SlStudy/CBA_Skim_Syst_SlStudy1/2016";
  
  //TFile *fin_incl = TFile::Open(Form("%s/all_TTbar_inclusive_sl_proof.root",inpath));
  //TFile *fin_incl = TFile::Open(Form("%s/all_TTbar_inclusive_sl_proof_chi2cut8.root",inpath));
  //TFile *fin_incl = TFile::Open(Form("%s/all_TTbar_inclusive_sl_proof_chi2cut8_oldreso.root",inpath));

  const char *inpath = "/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/grid_v37_Syst/CBA_Skim_Syst_SlStudy5/2016";
  TFile *fin_incl = TFile::Open(Form("%s/all_TTbarincl.root",inpath));
  // TH1F *hMin1_incl_mu = (TH1F *)fin_incl->Get("TTbar/base/Iso/hMinChi2_mu");
  // TH1F *hMin2_incl_mu = (TH1F *)fin_incl->Get("TTbar/base/Iso/h2MinChi2_mu");
  // TH1F *hMin3_incl_mu = (TH1F *)fin_incl->Get("TTbar/base/Iso/h3MinChi2_mu");
  // TH1F *hMin4_incl_mu = (TH1F *)fin_incl->Get("TTbar/base/Iso/h4MinChi2_mu");
  // TH1F *hMin1_incl_ele = (TH1F *)fin_incl->Get("TTbar/base/Iso/hMinChi2_ele");
  // TH1F *hMin2_incl_ele = (TH1F *)fin_incl->Get("TTbar/base/Iso/h2MinChi2_ele");
  // TH1F *hMin3_incl_ele = (TH1F *)fin_incl->Get("TTbar/base/Iso/h3MinChi2_ele");
  // TH1F *hMin4_incl_ele = (TH1F *)fin_incl->Get("TTbar/base/Iso/h4MinChi2_ele");

  TH1F *hMin1_incl_mu = (TH1F *)fin_incl->Get("TTbarincl/base/Iso/hMinChi2_mu");
  TH1F *hMin2_incl_mu = (TH1F *)fin_incl->Get("TTbarincl/base/Iso/h2MinChi2_mu");
  TH1F *hMin3_incl_mu = (TH1F *)fin_incl->Get("TTbarincl/base/Iso/h3MinChi2_mu");
  TH1F *hMin4_incl_mu = (TH1F *)fin_incl->Get("TTbarincl/base/Iso/h4MinChi2_mu");
  TH1F *hMin1_incl_ele = (TH1F *)fin_incl->Get("TTbarincl/base/Iso/hMinChi2_ele");
  TH1F *hMin2_incl_ele = (TH1F *)fin_incl->Get("TTbarincl/base/Iso/h2MinChi2_ele");
  TH1F *hMin3_incl_ele = (TH1F *)fin_incl->Get("TTbarincl/base/Iso/h3MinChi2_ele");
  TH1F *hMin4_incl_ele = (TH1F *)fin_incl->Get("TTbarincl/base/Iso/h4MinChi2_ele");
  
  //TFile *fin_excl = TFile::Open(Form("%s/all_TTbar_exclusive_sl.root",inpath));
  //TFile *fin_excl = TFile::Open(Form("%s/all_TTbar_sl_proof_chi2cut8.root",inpath));
  //TFile *fin_excl = TFile::Open(Form("%s/all_TTbar_sl_proof_chi2cut8_oldreso.root",inpath));

  TFile *fin_excl = TFile::Open(Form("%s/all_TTbar.root",inpath));
  TH1F *hMin1_excl_mu = (TH1F *)fin_excl->Get("TTbar/base/Iso/hMinChi2_mu");
  TH1F *hMin2_excl_mu = (TH1F *)fin_excl->Get("TTbar/base/Iso/h2MinChi2_mu");
  TH1F *hMin3_excl_mu = (TH1F *)fin_excl->Get("TTbar/base/Iso/h3MinChi2_mu");
  TH1F *hMin4_excl_mu = (TH1F *)fin_excl->Get("TTbar/base/Iso/h4MinChi2_mu");
  TH1F *hMin1_excl_ele = (TH1F *)fin_excl->Get("TTbar/base/Iso/hMinChi2_ele");
  TH1F *hMin2_excl_ele = (TH1F *)fin_excl->Get("TTbar/base/Iso/h2MinChi2_ele");
  TH1F *hMin3_excl_ele = (TH1F *)fin_excl->Get("TTbar/base/Iso/h3MinChi2_ele");
  TH1F *hMin4_excl_ele = (TH1F *)fin_excl->Get("TTbar/base/Iso/h4MinChi2_ele");

  TFile *fin_data = TFile::Open(Form("%s/all_DataMu.root",inpath));
  TH1F *hMin1_data_mu = (TH1F *)fin_data->Get("DataMu/base/Iso/hMinChi2_mu");
  TH1F *hMin2_data_mu = (TH1F *)fin_data->Get("DataMu/base/Iso/h2MinChi2_mu");
  TH1F *hMin3_data_mu = (TH1F *)fin_data->Get("DataMu/base/Iso/h3MinChi2_mu");
  TH1F *hMin4_data_mu = (TH1F *)fin_data->Get("DataMu/base/Iso/h4MinChi2_mu");
  TFile *fin_data_ele = TFile::Open(Form("%s/all_DataEle.root",inpath));
  TH1F *hMin1_data_ele = (TH1F *)fin_data_ele->Get("DataEle/base/Iso/hMinChi2_ele");
  TH1F *hMin2_data_ele = (TH1F *)fin_data_ele->Get("DataEle/base/Iso/h2MinChi2_ele");
  TH1F *hMin3_data_ele = (TH1F *)fin_data_ele->Get("DataEle/base/Iso/h3MinChi2_ele");
  TH1F *hMin4_data_ele = (TH1F *)fin_data_ele->Get("DataEle/base/Iso/h4MinChi2_ele");
  
  SetHistStyle(hMin1_incl_mu, kRed, 2, 1);
  SetHistStyle(hMin2_incl_mu, kBlue, 2, 1);
  SetHistStyle(hMin3_incl_mu, kGreen+2, 2, 1);
  SetHistStyle(hMin4_incl_mu, kMagenta, 2, 1);
  SetHistStyle(hMin1_excl_mu, kRed, 2, 1);
  SetHistStyle(hMin2_excl_mu, kBlue, 2, 1);
  SetHistStyle(hMin3_excl_mu, kGreen+2, 2, 1);
  SetHistStyle(hMin4_excl_mu, kMagenta, 2, 1);
  SetHistStyle(hMin1_data_mu, kRed, 2, 1);
  SetHistStyle(hMin2_data_mu, kBlue, 2, 1);
  SetHistStyle(hMin3_data_mu, kGreen+2, 2, 1);
  SetHistStyle(hMin4_data_mu, kMagenta, 2, 1);


  TCanvas *c1 = new TCanvas("c1","c1 #chi^2 for inclusive in #mu + jets");
  hMin1_incl_mu->Draw();
  hMin2_incl_mu->Draw("sames");
  hMin3_incl_mu->Draw("sames");
  hMin4_incl_mu->Draw("sames");

  TCanvas *c2 = new TCanvas("c2","c2 #chi^2 for exclusive in #mu + jets");
  hMin1_excl_mu->Draw();
  hMin2_excl_mu->Draw("sames");
  hMin3_excl_mu->Draw("sames");
  hMin4_excl_mu->Draw("sames");

  TCanvas *c3 = new TCanvas("c3","c3 #chi^2 for data in #mu + jets");
  hMin1_data_mu->Draw();
  hMin2_data_mu->Draw("sames");
  hMin3_data_mu->Draw("sames");
  hMin4_data_mu->Draw("sames");

  SetHistStyle(hMin1_incl_ele, kRed, 2, 1);
  SetHistStyle(hMin2_incl_ele, kBlue, 2, 1);
  SetHistStyle(hMin3_incl_ele, kGreen+2, 2, 1);
  SetHistStyle(hMin4_incl_ele, kMagenta, 2, 1);
  SetHistStyle(hMin1_excl_ele, kRed, 2, 1);
  SetHistStyle(hMin2_excl_ele, kBlue, 2, 1);
  SetHistStyle(hMin3_excl_ele, kGreen+2, 2, 1);
  SetHistStyle(hMin4_excl_ele, kMagenta, 2, 1);
  SetHistStyle(hMin1_data_ele, kRed, 2, 1);
  SetHistStyle(hMin2_data_ele, kBlue, 2, 1);
  SetHistStyle(hMin3_data_ele, kGreen+2, 2, 1);
  SetHistStyle(hMin4_data_ele, kMagenta, 2, 1);

  // TCanvas *c1_1 = new TCanvas("c1_1","c1_1 #chi^2 for inclusive in e + jets");
  // hMin1_incl_ele->Draw();
  // hMin2_incl_ele->Draw("sames");
  // hMin3_incl_ele->Draw("sames");
  // hMin4_incl_ele->Draw("sames");

  // TCanvas *c2_1 = new TCanvas("c2_1","c2_1 #chi^2 for exclusive in e + jets");
  // hMin1_excl_ele->Draw();
  // hMin2_excl_ele->Draw("sames");
  // hMin3_excl_ele->Draw("sames");
  // hMin4_excl_ele->Draw("sames");

  // TCanvas *c3_1 = new TCanvas("c3_1","c3_1 #chi^2 for data in e + jets");
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
