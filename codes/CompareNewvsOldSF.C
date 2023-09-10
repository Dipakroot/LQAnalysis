/**********************************************************************
 Created on : 11/01/2022
 Purpose    : Compare the histograms from old and new SF files
 Author     : Indranil Das, Visiting Fellow
 Email      : indranil.das@cern.ch | indra.ehep@gmail.com
**********************************************************************/

#include <TH1.h>
#include <TF1.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TAxis.h>
#include <TStyle.h>
#include <TMath.h>
#include <TKey.h>
#include <TPaveStats.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TAttMarker.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

#include "../interface/PUReweight.h"

using namespace std;

//Global variables
string inpathLRR = "/Data/CMS-Analysis/NanoAOD-Analysis/Git_KinFit_Skim/KinFit_Skim/CBA_Skim/weight";
//string infileLRRWt = "/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/grid_v36_Syst/CBA_Skim_Syst_btagCSV/2016/all_TTbar.root";
//string infileLRRWt = "/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/grid_v39_Syst/Leg_muMedID/2016/all_TTbar.root";
string infileLRRWt = "/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/grid_v39_Syst/CBA_KinFit_ULv9/pre/2016/all_TTbar.root";

string inpathUL = "/Data/CMS-Analysis/NanoAOD-Analysis/Git_KinFit_Skim/KinFit_Skim/CBA_Skim/weightUL";
//string infileULWt = "/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/grid_v39_Syst/ULv9_miniAOD_med_prompt/2016/all_TTbar.root";
//string infileULWt = "/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/grid_v39_Syst/ULv9_PAG_med_noprompt/2016/all_TTbar.root";
//string infileULWt = "/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/grid_v39_Syst/ULv9_Nmu_t5_mediumPromptID/2016/all_TTbar.root";
//string infileULWt = "/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/grid_v39_Syst/ULv9_Nmu_t6_IsSolvedMuon/2016/all_TTbar.root";
string infileULWt = "/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/grid_v39_Syst/CBA_KinFit_ULv9/post/2016/all_TTbar.root";

TFile *finLRR_Wt = TFile::Open(infileLRRWt.c_str());
TFile *finUL_Wt = TFile::Open(infileULWt.c_str());

int CompareNewvsOldSF()
{
  int ReadPileupSF(void);
  int ReadSampleWt(void);
  int ReadPrefireWt(void);
  int ReadMuEffWt(void);
  int ReadEleEffWt(void);
  int ReadBTagWt(void);

  ReadPileupSF();
  ReadSampleWt();
  ReadPrefireWt();
  ReadMuEffWt();
  ReadEleEffWt();
  ReadBTagWt();
  
  return 0;
}

int ReadBTagWt(void)
{
  
  TH1D *hLRR_BTagWt = (TH1D *)finLRR_Wt->Get("TTbar/base/Iso/_btagWeight_1a");
  hLRR_BTagWt->SetLineWidth(2);

  TH1D *hUL_BTagWt = (TH1D *)finUL_Wt->Get("TTbar/base/Iso/_btagWeight_1a");
  hUL_BTagWt->SetLineColor(kRed);
  hUL_BTagWt->SetLineWidth(2);

  TLegend *legBTagWt = new TLegend(0.64,0.77,0.98,0.94);
  legBTagWt->SetFillColor(10);
  // legBTagWt->AddEntry(hLRR_BTagWt, "BTag weight of Legacy ReReco" ,"lp");
  // legBTagWt->AddEntry(hUL_BTagWt, "BTag weight of UltraLegacy" ,"lp");
  legBTagWt->AddEntry(hLRR_BTagWt, "BTag weight of PreVFP" ,"lp");
  legBTagWt->AddEntry(hUL_BTagWt, "BTag weight of PostVFP" ,"lp");
  hUL_BTagWt->SetTitle("BTag weight");
  hUL_BTagWt->GetXaxis()->SetRangeUser(-0.5,4.);
  TCanvas *c1_BTagWt = new TCanvas("c1_BTagWt","c1_BTagWt");
  hUL_BTagWt->Draw();
  hLRR_BTagWt->Draw("sames");
  hUL_BTagWt->GetXaxis()->SetTitle("btag weight");
  hUL_BTagWt->GetYaxis()->SetTitle("Entries");
  legBTagWt->Draw();
  c1_BTagWt->SetLogy();
  c1_BTagWt->Update();

  return true;
}

int ReadEleEffWt(void)
{
  
  TH1D *hLRR_EleEffWt = (TH1D *)finLRR_Wt->Get("TTbar/base/Iso/_eleEffWeight");
  hLRR_EleEffWt->SetLineWidth(2);

  TH1D *hUL_EleEffWt = (TH1D *)finUL_Wt->Get("TTbar/base/Iso/_eleEffWeight");
  hUL_EleEffWt->SetLineColor(kRed);
  hUL_EleEffWt->SetLineWidth(2);

  TLegend *legEleWt = new TLegend(0.64,0.77,0.98,0.94);
  legEleWt->SetFillColor(10);
  // legEleWt->AddEntry(hLRR_EleEffWt, "EleEff weight of Legacy ReReco" ,"lp");
  // legEleWt->AddEntry(hUL_EleEffWt, "EleEff weight of UltraLegacy" ,"lp");
  legEleWt->AddEntry(hLRR_EleEffWt, "EleEff weight of PreVFP" ,"lp");
  legEleWt->AddEntry(hUL_EleEffWt, "EleEff weight of PostVFP" ,"lp");
  hUL_EleEffWt->SetTitle("EleEff weight");
  hUL_EleEffWt->GetXaxis()->SetRangeUser(-0.5,2.);
  TCanvas *c1_EleEffWt = new TCanvas("c1_EleEffWt","c1_EleEffWt");
  hUL_EleEffWt->Draw();
  hLRR_EleEffWt->Draw("sames");
  hUL_EleEffWt->GetXaxis()->SetTitle("eleEff weight");
  hUL_EleEffWt->GetYaxis()->SetTitle("Entries");
  legEleWt->Draw();
  c1_EleEffWt->SetLogy();
  c1_EleEffWt->Update();

  return true;
}

int ReadMuEffWt(void)
{
  
  TH1D *hLRR_MuEffWt = (TH1D *)finLRR_Wt->Get("TTbar/base/Iso/_muEffWeight");
  hLRR_MuEffWt->SetLineWidth(2);

  TH1D *hUL_MuEffWt = (TH1D *)finUL_Wt->Get("TTbar/base/Iso/_muEffWeight");
  hUL_MuEffWt->SetLineColor(kRed);
  hUL_MuEffWt->SetLineWidth(2);

  TLegend *legMuWt = new TLegend(0.64,0.77,0.98,0.94);
  legMuWt->SetFillColor(10);
  // legMuWt->AddEntry(hLRR_MuEffWt, "MuEff weight of Legacy ReReco" ,"lp");
  // legMuWt->AddEntry(hUL_MuEffWt, "MuEff weight of UltraLegacy" ,"lp");
  legMuWt->AddEntry(hLRR_MuEffWt, "MuEff weight of PreVFP" ,"lp");
  legMuWt->AddEntry(hUL_MuEffWt, "MuEff weight of PostVFP" ,"lp");
  hUL_MuEffWt->SetTitle("MuEff weight");
  hUL_MuEffWt->GetXaxis()->SetRangeUser(-0.5,2.);
  TCanvas *c1_MuEffWt = new TCanvas("c1_MuEffWt","c1_MuEffWt");
  hUL_MuEffWt->Draw();
  hLRR_MuEffWt->Draw("sames");
  hUL_MuEffWt->GetXaxis()->SetTitle("muEff weight");
  hUL_MuEffWt->GetYaxis()->SetTitle("Entries");
  legMuWt->Draw();
  c1_MuEffWt->SetLogy();
  c1_MuEffWt->Update();

  return true;
}

int ReadPrefireWt(void)
{
  
  TH1D *hLRR_PrefireWt = (TH1D *)finLRR_Wt->Get("TTbar/base/Iso/_prefireWeight");
  hLRR_PrefireWt->SetLineWidth(2);

  TH1D *hUL_PrefireWt = (TH1D *)finUL_Wt->Get("TTbar/base/Iso/_prefireWeight");
  hUL_PrefireWt->SetLineColor(kRed);
  hUL_PrefireWt->SetLineWidth(2);

  TLegend *legPrefireWt = new TLegend(0.64,0.77,0.98,0.94);
  legPrefireWt->SetFillColor(10);
  // legPrefireWt->AddEntry(hLRR_PrefireWt, "Prefire weight of Legacy ReReco" ,"lp");
  // legPrefireWt->AddEntry(hUL_PrefireWt, "Prefire weight of UltraLegacy" ,"lp");
  legPrefireWt->AddEntry(hLRR_PrefireWt, "Prefire weight of PreVFP" ,"lp");
  legPrefireWt->AddEntry(hUL_PrefireWt, "Prefire weight of PostVFP" ,"lp");
  hUL_PrefireWt->SetTitle("Prefire weight");
  hUL_PrefireWt->GetXaxis()->SetRangeUser(-2.,3.);
  TCanvas *c1_PrefireWt = new TCanvas("c1_PrefireWt","c1_PrefireWt");
  hUL_PrefireWt->Draw();
  hLRR_PrefireWt->Draw("sames");
  hUL_PrefireWt->GetXaxis()->SetTitle("prefire weight");
  hUL_PrefireWt->GetYaxis()->SetTitle("Entries");
  legPrefireWt->Draw();
  c1_PrefireWt->SetLogy();
  c1_PrefireWt->Update();

  return true;
}

int ReadSampleWt(void)
{
  TH1D *hLRR_SampleWt = (TH1D *)finLRR_Wt->Get("TTbar/base/Iso/_sampleWeight");
  hLRR_SampleWt->SetLineWidth(2);

  TH1D *hUL_SampleWt = (TH1D *)finUL_Wt->Get("TTbar/base/Iso/_sampleWeight");
  hUL_SampleWt->SetLineColor(kRed);
  hUL_SampleWt->SetLineWidth(2);

  TLegend *legSampleWt = new TLegend(0.64,0.77,0.98,0.94);
  legSampleWt->SetFillColor(10);
  // legSampleWt->AddEntry(hLRR_SampleWt, "Modified luminosity weight of Legacy ReReco" ,"lp");
  // legSampleWt->AddEntry(hUL_SampleWt, "Modified luminosity weight of UltraLegacy" ,"lp");
  legSampleWt->AddEntry(hLRR_SampleWt, "Modified luminosity weight of PreVFP" ,"lp");
  legSampleWt->AddEntry(hUL_SampleWt, "Modified luminosity weight of PostVFP" ,"lp");
  hUL_SampleWt->SetTitle("Sample weight (LumiSF*event->genWeight_)");
  hUL_SampleWt->GetXaxis()->SetRangeUser(-1.,1.);
  TCanvas *c1_SampleWt = new TCanvas("c1_SampleWt","c1_SampleWt");
  hUL_SampleWt->Draw();
  hLRR_SampleWt->Draw("sames");
  hUL_SampleWt->GetXaxis()->SetTitle("sample weight");
  hUL_SampleWt->GetYaxis()->SetTitle("Entries");
  legSampleWt->Draw();
  c1_SampleWt->SetLogy();
  c1_SampleWt->Update();

  return true;
}

int ReadPileupSF(void)
{
  TFile *finLRR_PU = TFile::Open(Form("%s/PileupSF/Data_2016BCDGH_Pileup.root",inpathLRR.c_str()));
  TFile *finUL_PU = TFile::Open(Form("%s/PileupSF/PileupHistogram-UL2016-100bins_withVar.root",inpathUL.c_str()));
  
  //Interesting to read https://hypernews.cern.ch/HyperNews/CMS/get/physics-validation/3689/1/1/1/1/1/1.html

  TH1D *hLRR_PU = (TH1D *)finLRR_PU->Get("pileup");
  TH1D *hLRR_PUWt = (TH1D *)finLRR_Wt->Get("TTbar/base/Iso/_PUWeight");
  hLRR_PUWt->Rebin(8);
  hLRR_PU->SetLineWidth(2);
  hLRR_PUWt->SetLineWidth(2);

  TH1D *hUL_PU = (TH1D *)finUL_PU->Get("pileup");
  TH1D *hUL_PUWt = (TH1D *)finUL_Wt->Get("TTbar/base/Iso/_PUWeight");
  hUL_PUWt->Rebin(8);
  hUL_PU->SetLineColor(kRed);
  hUL_PUWt->SetLineColor(kRed);
  hUL_PU->SetLineWidth(2);
  hUL_PUWt->SetLineWidth(2);
  
  TLegend *legPU = new TLegend(0.64,0.77,0.98,0.94);
  legPU->SetFillColor(10);
  legPU->AddEntry(hLRR_PU, "Pileup SF of Legacy ReReco" ,"lp");
  legPU->AddEntry(hUL_PU, "Pileup SF of UltraLegacy" ,"lp");
  hLRR_PU->SetTitle("Pileup SF");
  TCanvas *c1_PU = new TCanvas("c1_PU","c1_PU");
  hLRR_PU->Draw("hist");
  hUL_PU->Draw("sames");
  hLRR_PU->GetXaxis()->SetTitle("Poisson mean of the pileup distribution (Pileup_nTrueInt)");
  hLRR_PU->GetYaxis()->SetTitle("Entries");
  legPU->Draw();
  c1_PU->SetLogy();
  c1_PU->Update();

  TLegend *legPUWt = new TLegend(0.64,0.77,0.98,0.94);
  legPUWt->SetFillColor(10);
  legPUWt->AddEntry(hLRR_PUWt, "Pileup weight of Legacy ReReco" ,"lp");
  legPUWt->AddEntry(hUL_PUWt, "Pileup weight of UltraLegacy" ,"lp");
  hUL_PUWt->SetTitle("Pileup weight");
  hUL_PUWt->GetXaxis()->SetRangeUser(-2.,4.);
  TCanvas *c1_PUWt = new TCanvas("c1_PUWt","c1_PUWt");
  hUL_PUWt->Draw();
  hLRR_PUWt->Draw("sames");
  hUL_PUWt->GetXaxis()->SetTitle("PU weight");
  hUL_PUWt->GetYaxis()->SetTitle("Entries");
  legPUWt->Draw();
  c1_PUWt->SetLogy();
  c1_PUWt->Update();

  return true;
}
