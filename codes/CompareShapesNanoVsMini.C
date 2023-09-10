/**********************************************************************
 Created on : 10/11/2021
 Purpose    : Compare the shapes of Nano vs Mini AOD
 Author     : Indranil Das, Visiting Fellow
 Email      : indranil.das@cern.ch | indra.ehep@gmail.com
**********************************************************************/
#include <TH1.h>
#include <THStack.h>
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
#include <TAttLine.h>
#include <TGraphAsymmErrors.h>

#include <TRatioPlot.h>

#include <iostream>

using namespace std;

int CompareShapesNanoVsMini()
{
  TPad* PlotRatio(TH1F *h1, TH1F *h2, const char *cname, bool isLog);
  void SetHistStyle(TH1F *h1, Color_t color, int width, int style);

  TFile *fin_nanoexcl = TFile::Open("root_files/test/Shapes_hcs_13TeV_mu___kb_mjj_mu_WH80_exclusive.root");
  TH1F *hNanoexclData = (TH1F *)fin_nanoexcl->Get("data_obs");
  TH1F *hNanoexclTTbar = (TH1F *)fin_nanoexcl->Get("ttbar");
  TH1F *hNanoexclStop = (TH1F *)fin_nanoexcl->Get("stop");
  TH1F *hNanoexclWjet = (TH1F *)fin_nanoexcl->Get("wjet");
  TH1F *hNanoexclZjet = (TH1F *)fin_nanoexcl->Get("zjet");
  TH1F *hNanoexclVV = (TH1F *)fin_nanoexcl->Get("vv");
  TH1F *hNanoexclQCD = (TH1F *)fin_nanoexcl->Get("qcd");
  
  TH1F *hNanoexclMC = (TH1F *)hNanoexclTTbar->Clone("hMCNanoexcl");
  // hNanoexclMC->Add(hNanoexclStop);
  // hNanoexclMC->Add(hNanoexclWjet);
  // hNanoexclMC->Add(hNanoexclZjet);
  // hNanoexclMC->Add(hNanoexclVV);
  //hNanoexclMC->Add(hNanoexclQCD);
  
  TFile *fin_nanoexcl_data = TFile::Open("/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/grid_v36_Syst/CBA_Skim_Syst_lowreso/2016/all_DataEle.root");
  TH1F *hNanoexclData_ch = (TH1F *)fin_nanoexcl_data->Get("DataEle/base/Iso/_kb_mjj_ele");
  TFile *fin_nanoexcl_dl = TFile::Open("/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/grid_v36_Syst/CBA_Skim_Syst_lowreso/2016/all_TTbar_iter1_Dilep.root");
  TFile *fin_nanoexcl_hd = TFile::Open("/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/grid_v36_Syst/CBA_Skim_Syst_lowreso/2016/all_TTbar_iter1_Hadron.root");
  TFile *fin_nanoexcl_sl = TFile::Open("/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/grid_v36_Syst/CBA_Skim_Syst_lowreso/2016/all_TTbar_iter1_Semilept.root");
  TH1F *hNanoexclTTbar_dl = (TH1F *)fin_nanoexcl_dl->Get("TTbar/base/Iso/_kb_mjj_ele");
  TH1F *hNanoexclTTbar_hd = (TH1F *)fin_nanoexcl_hd->Get("TTbar/base/Iso/_kb_mjj_ele");
  TH1F *hNanoexclTTbar_sl = (TH1F *)fin_nanoexcl_sl->Get("TTbar/base/Iso/_kb_mjj_ele");

  TFile *fin_nanoincl = TFile::Open("root_files/test/Shapes_hcs_13TeV_mu___kb_mjj_mu_WH80_inclusive.root");
  TH1F *hNanoinclData = (TH1F *)fin_nanoincl->Get("data_obs");
  TH1F *hNanoinclTTbar = (TH1F *)fin_nanoincl->Get("ttbar");
  TH1F *hNanoinclStop = (TH1F *)fin_nanoincl->Get("stop");
  TH1F *hNanoinclWjet = (TH1F *)fin_nanoincl->Get("wjet");
  TH1F *hNanoinclZjet = (TH1F *)fin_nanoincl->Get("zjet");
  TH1F *hNanoinclVV = (TH1F *)fin_nanoincl->Get("vv");
  TH1F *hNanoinclQCD = (TH1F *)fin_nanoincl->Get("qcd");
  
  TH1F *hNanoinclMC = (TH1F *)hNanoinclTTbar->Clone("hMCNanoincl");
  // hNanoinclMC->Add(hNanoinclStop);
  // hNanoinclMC->Add(hNanoinclWjet);
  // hNanoinclMC->Add(hNanoinclZjet);
  // hNanoinclMC->Add(hNanoinclVV);
  //hNanoinclMC->Add(hNanoinclQCD);

  TFile *fin_nanoincl_ch = TFile::Open("/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/grid_v36_Syst/CBA_Skim_Syst_lowreso/2016/all_TTbar_split_inclusive.root");
  TH1F *hNanoinclTTbar_dl = (TH1F *)fin_nanoincl_ch->Get("TTbar/base/Iso/_kb_mjj_ele");
  TH1F *hNanoinclTTbar_hd = (TH1F *)fin_nanoincl_ch->Get("TTbar/base/Iso/_kb_mjj_ele1");
  TH1F *hNanoinclTTbar_sl = (TH1F *)fin_nanoincl_ch->Get("TTbar/base/Iso/_kb_mjj_ele2");

  TFile *fin_nanoexcl_data_2017 = TFile::Open("/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/grid_v36_Syst/CBA_Skim_Syst_lowreso/2017/all_DataMu.root");
  TH1F *hNanoexclData_2017 = (TH1F *)fin_nanoexcl_data_2017->Get("DataMu/base/Iso/_kb_mjj_mu");
  TFile *fin_nanoincl_ttbar_2017 = TFile::Open("/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/grid_v36_Syst/CBA_Skim_Syst_lowreso/2017/all_TTbar.root");
  TH1F *hNanoexclTTbar_2017 = (TH1F *)fin_nanoincl_ttbar_2017->Get("TTbar/base/Iso/_kb_mjj_mu");

  TFile *fin_nanoexcl_data_2018 = TFile::Open("/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/grid_v36_Syst/CBA_Skim_Syst_lowreso/2018/all_DataMu.root");
  TH1F *hNanoexclData_2018 = (TH1F *)fin_nanoexcl_data_2018->Get("DataMu/base/Iso/_kb_mjj_mu");
  TFile *fin_nanoincl_ttbar_2018 = TFile::Open("/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/grid_v36_Syst/CBA_Skim_Syst_lowreso/2018/all_TTbar.root");
  TH1F *hNanoexclTTbar_2018 = (TH1F *)fin_nanoincl_ttbar_2018->Get("TTbar/base/Iso/_kb_mjj_mu");
  
  TFile *fin_nanoexcl_data_2016 = TFile::Open("/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/grid_v36_Syst/CBA_Skim_Syst_lowreso/2016/all_DataMu.root");
  TH1F *hNanoexclData_2016 = (TH1F *)fin_nanoexcl_data_2016->Get("DataMu/base/Iso/_kb_mjj_mu");
  TFile *fin_nanoexcl_ttcomb_2016 = TFile::Open("/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/grid_v36_Syst/CBA_Skim_Syst_lowreso/2016/base_TTbar_2016_ttbar_combination.root");
  TH1F *hNanoexclTTbarComb_2016 = (TH1F *)fin_nanoexcl_ttcomb_2016->Get("TTbar/base/Iso/_kb_mjj_mu");
  TFile *fin_nanoexcl_mixedincl_2016 = TFile::Open("/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/grid_v36_Syst/CBA_Skim_Syst_lowreso/2016/base_TTbar_2016_mixedincl1.root");
  TH1F *hNanoexclmixedincl_2016 = (TH1F *)fin_nanoexcl_ttcomb_2016->Get("TTbar/base/Iso/_kb_mjj_mu");
  
  TFile *fin_mini = TFile::Open("/Data/CMS-Software/local/CMSSW_10_2_13/src/Analysis/limit/local/mu/Cat1_Inc/Mass80/Shapes_hcs_13TeV_mu_KinFit_mjj_kfit_WH80.root");
  TH1F *hMiniData = (TH1F *)fin_mini->Get("data_obs");
  TH1F *hMiniTTbar = (TH1F *)fin_mini->Get("ttbar");
  TH1F *hMiniStop = (TH1F *)fin_mini->Get("stop");
  TH1F *hMiniWjet = (TH1F *)fin_mini->Get("wjet");
  TH1F *hMiniZjet = (TH1F *)fin_mini->Get("zjet");
  TH1F *hMiniVV = (TH1F *)fin_mini->Get("vv");
  TH1F *hMiniQCD = (TH1F *)fin_mini->Get("qcd");
  
  TH1F *hMiniMC = (TH1F *)hMiniTTbar->Clone("hMCMini");
  // hMiniMC->Add(hMiniStop);
  // hMiniMC->Add(hMiniWjet);
  // hMiniMC->Add(hMiniZjet);
  // hMiniMC->Add(hMiniVV);
  //hMiniMC->Add(hMiniQCD);

  cout<<"hDataNano(Exl) Binwidth " << hNanoexclData->GetBinWidth(2) << ", Integral : " << hNanoexclData->Integral() <<endl;  
  cout<<"hDataNano(Inc) Binwidth " << hNanoinclData->GetBinWidth(2) << ", Integral : " << hNanoinclData->Integral() <<endl;  
  cout<<"hMiniNano Binwidth " << hMiniData->GetBinWidth(2) << ", Integral : " << hMiniData->Integral() <<endl;  

  // Mini Vs Nano comparison
  // TH1F *hDataRatio = (TH1F *)hMiniData->Clone("data ratio (M/N)");
  // hDataRatio->Sumw2();
  // hDataRatio->Divide(hNanoData);
  // hDataRatio->SetTitle("");
  
  // TH1F *hMCRatio = (TH1F *)hMiniMC->Clone("mc ratio (M/N)");
  // hMCRatio->Sumw2();
  // hMCRatio->Divide(hNanoMC);
  // hMCRatio->SetTitle("");
  
  // TH1F *hDataMCRatio = (TH1F *)hDataRatio->Clone("data ratio / mc ratio");
  // hDataMCRatio->Sumw2();
  // hDataMCRatio->Divide(hMCRatio);
  

  // TCanvas *c1 = new TCanvas("c1","c1");
  // hDataRatio->Draw();

  // TCanvas *c2 = new TCanvas("c2","c2");
  // hMCRatio->Draw();

  // TCanvas *c3 = new TCanvas("c3","c3");
  // hDataMCRatio->Draw();

  
  TH1F *hMiniRatio = (TH1F *)hMiniData->Clone("data/mc (Mini 2016)");
  hMiniRatio->Divide(hMiniMC);
  hMiniRatio->SetTitle("");
  TH1F *hNanoexclRatio = (TH1F *)hNanoexclData->Clone("data/mc (Nanoexcl 2016)");
  hNanoexclRatio->Divide(hNanoexclMC);
  hNanoexclRatio->SetTitle("");
  TH1F *hNanoinclRatio = (TH1F *)hNanoinclData->Clone("data/mc (Nanoincl 2016)");
  hNanoinclRatio->Divide(hNanoinclMC);
  hNanoinclRatio->SetTitle("");
  
  TH1F *hNanoexclRatio_2017 = (TH1F *)hNanoexclData_2017->Clone("data/mc (Nanoexcl 2017)");
  hNanoexclRatio_2017->Divide(hNanoexclTTbar_2017);
  hNanoexclRatio_2017->SetTitle("");
  TH1F *hNanoexclRatio_2018 = (TH1F *)hNanoexclData_2018->Clone("data/mc (Nanoexcl 2018)");
  hNanoexclRatio_2018->Divide(hNanoexclTTbar_2018);
  hNanoexclRatio_2018->SetTitle("");
  TH1F *hNanoexclRatioTTComb = (TH1F *)hNanoexclData_2016->Clone("data/mc (Nanoexcl ttcomb 2016)");
  hNanoexclRatioTTComb->Divide(hNanoexclTTbarComb_2016);
  hNanoexclRatioTTComb->SetTitle("");
  TH1F *hNanoexclRatiomixedincl = (TH1F *)hNanoexclData_2016->Clone("data/mc (Nanoexcl ttcomb 2016)");
  hNanoexclRatiomixedincl->Divide(hNanoexclmixedincl_2016);
  hNanoexclRatiomixedincl->SetTitle("");

  
  
  hMiniRatio->SetLineColor(kRed);
  hNanoexclRatio->SetLineColor(kBlue);
  hNanoinclRatio->SetLineColor(kGreen);
  hMiniRatio->SetLineWidth(3);
  hNanoexclRatio->SetLineWidth(3);
  hNanoinclRatio->SetLineWidth(3);

  //SetHistStyle(hNanoexclRatio_2017, kBlack, 3, 1);
  SetHistStyle(hNanoexclRatio_2018, kMagenta, 3, 1);
  SetHistStyle(hNanoexclRatioTTComb, kOrange+2, 3, 1);
  SetHistStyle(hNanoexclRatiomixedincl, kBlack, 3, 1);
  
  
  TH1F *hNanoinclRatio_dl = (TH1F *)hNanoexclData_ch->Clone("data/mc (Nanoincl dl)");
  hNanoinclRatio_dl->Divide(hNanoinclTTbar_dl);
  hNanoinclRatio_dl->SetTitle("");
  TH1F *hNanoinclRatio_hd = (TH1F *)hNanoexclData_ch->Clone("data/mc (Nanoincl hd)");
  hNanoinclRatio_hd->Divide(hNanoinclTTbar_hd);
  hNanoinclRatio_hd->SetTitle("");
  TH1F *hNanoinclRatio_sl = (TH1F *)hNanoexclData_ch->Clone("data/mc (Nanoincl sl)");
  hNanoinclRatio_sl->Divide(hNanoinclTTbar_sl);
  hNanoinclRatio_sl->SetTitle("");

  TH1F *hNanoexclRatio_dl = (TH1F *)hNanoexclData_ch->Clone("data/mc (Nanoexcl dl)");
  hNanoexclRatio_dl->Divide(hNanoexclTTbar_dl);
  hNanoexclRatio_dl->SetTitle("");
  TH1F *hNanoexclRatio_hd = (TH1F *)hNanoexclData_ch->Clone("data/mc (Nanoexcl hd)");
  hNanoexclRatio_hd->Divide(hNanoexclTTbar_hd);
  hNanoexclRatio_hd->SetTitle("");
  TH1F *hNanoexclRatio_sl = (TH1F *)hNanoexclData_ch->Clone("data/mc (Nanoexcl sl)");
  hNanoexclRatio_sl->Divide(hNanoexclTTbar_sl);
  hNanoexclRatio_sl->SetTitle("");

  SetHistStyle(hNanoexclData_ch, kGreen, 3, 1);
  SetHistStyle(hNanoinclTTbar_dl, kRed, 3, 1);
  SetHistStyle(hNanoinclTTbar_hd, kRed, 3, 1);
  SetHistStyle(hNanoinclTTbar_sl, kRed, 3, 1);
  SetHistStyle(hNanoexclTTbar_dl, kBlue, 3, 1);
  SetHistStyle(hNanoexclTTbar_hd, kBlue, 3, 1);
  SetHistStyle(hNanoexclTTbar_sl, kBlue, 3, 1);

  SetHistStyle(hNanoinclRatio_dl, kRed, 3, 1);
  SetHistStyle(hNanoinclRatio_hd, kRed, 3, 1);
  SetHistStyle(hNanoinclRatio_sl, kRed, 3, 1);
  SetHistStyle(hNanoexclRatio_dl, kBlue, 3, 1);
  SetHistStyle(hNanoexclRatio_hd, kBlue, 3, 1);
  SetHistStyle(hNanoexclRatio_sl, kBlue, 3, 1);

  
  TLegend *leg1 = new TLegend(0.6,0.7,0.99,0.95);
  leg1->AddEntry(hMiniRatio, "inclusive MiniAOD" ,"lp");
  leg1->AddEntry(hNanoexclRatio, "exclusive NanoAOD" ,"lp");
  leg1->AddEntry(hNanoinclRatio, "inclusive NanoAOD" ,"lp");
  hMiniRatio->SetMinimum(0.5); hMiniRatio->SetMaximum(1.5); 
  TCanvas *c1 = new TCanvas("c1","c1");
  hMiniRatio->Draw("hist");
  hNanoexclRatio->Draw("sames hist");
  hNanoinclRatio->Draw("sames hist");
  // //hNanoexclRatio_2017->Draw("sames hist");
  // hNanoexclRatio_2018->Draw("sames hist");
  // hNanoexclRatioTTComb->Draw("sames hist");
  hNanoexclRatiomixedincl->Draw("sames hist");
  leg1->Draw();
  hMiniRatio->GetXaxis()->SetTitle("m_{jj} (GeV)");
  hMiniRatio->GetYaxis()->SetTitle("Data/t#bar{t} (Entries/bin)");

  TVirtualPad *p1 = 0x0;
  TLegend *leg21 = new TLegend(0.6,0.7,0.99,0.95);
  leg21->AddEntry(hNanoexclData_ch, "Data" ,"lp");
  leg21->AddEntry(hNanoinclTTbar_dl, "inclusive dileptonic" ,"lp");
  leg21->AddEntry(hNanoexclTTbar_dl, "exclusive dileptonic" ,"lp");
  TLegend *leg22 = new TLegend(0.6,0.7,0.99,0.95);
  leg22->AddEntry(hNanoinclRatio_dl, "inclusive dileptonic" ,"lp");
  leg22->AddEntry(hNanoexclRatio_dl, "exclusive dileptonic" ,"lp");
  TCanvas *c2 = new TCanvas("c2","c2",13,47,1102,554);
  c2->Divide(2,1);
  {
    p1 = c2->cd(1);
    //p1->SetPad(0.01,0.01,0.49,0.99);
    p1->SetLeftMargin(0.15);
    p1->SetRightMargin(0.04);
    hNanoexclData_ch->Draw("hist");
    hNanoinclTTbar_dl->Draw("hist sames");
    hNanoexclTTbar_dl->Draw("hist sames");
    leg21->Draw();
    hNanoexclData_ch->GetXaxis()->SetTitle("m_{jj} (GeV)");
    hNanoexclData_ch->GetYaxis()->SetTitle("Entries/bin");
  }
  {
    c2->cd(2);
    hNanoinclRatio_dl->Draw("hist");
    hNanoexclRatio_dl->Draw("sames hist");
    leg22->Draw();
    hNanoinclRatio_dl->GetXaxis()->SetTitle("m_{jj} (GeV)");
    hNanoinclRatio_dl->GetYaxis()->SetTitle("Data/t#bar{t} (Entries/bin)");
  }

  TLegend *leg31 = new TLegend(0.6,0.7,0.99,0.95);
  leg31->AddEntry(hNanoexclData_ch, "Data" ,"lp");
  leg31->AddEntry(hNanoinclTTbar_hd, "inclusive hadronic" ,"lp");
  leg31->AddEntry(hNanoexclTTbar_hd, "exclusive hadronic" ,"lp");
  TLegend *leg32 = new TLegend(0.6,0.7,0.99,0.95);
  leg32->AddEntry(hNanoinclRatio_hd, "inclusive hadronic" ,"lp");
  leg32->AddEntry(hNanoexclRatio_hd, "exclusive hadronic" ,"lp");
  TCanvas *c3 = new TCanvas("c3","c3",13,47,1102,554);
  c3->Divide(2,1);
  {
    p1 = c3->cd(1);
    //p1->SetPad(0.01,0.01,0.49,0.99);
    p1->SetLeftMargin(0.15);
    p1->SetRightMargin(0.04);
    hNanoexclData_ch->Draw("hist");
    hNanoinclTTbar_hd->Draw("hist sames");
    hNanoexclTTbar_hd->Draw("hist sames");
    leg31->Draw();
    hNanoexclData_ch->GetXaxis()->SetTitle("m_{jj} (GeV)");
    hNanoexclData_ch->GetYaxis()->SetTitle("Entries/bin");
  }
  {
    p1 = c3->cd(2);
    p1->SetLeftMargin(0.15);
    p1->SetRightMargin(0.04);
    hNanoinclRatio_hd->Draw("hist");
    hNanoexclRatio_hd->Draw("sames hist");
    leg32->Draw();
    hNanoinclRatio_hd->GetXaxis()->SetTitle("m_{jj} (GeV)");
    hNanoinclRatio_hd->GetYaxis()->SetTitle("Data/t#bar{t} (Entries/bin)");
  }
  
  TLegend *leg41 = new TLegend(0.6,0.7,0.99,0.95);
  leg41->AddEntry(hNanoexclData_ch, "Data" ,"lp");
  leg41->AddEntry(hNanoinclTTbar_sl, "inclusive semileptonic" ,"lp");
  leg41->AddEntry(hNanoexclTTbar_sl, "exclusive semileptonic" ,"lp");
  TLegend *leg42 = new TLegend(0.6,0.7,0.99,0.95);
  leg42->AddEntry(hNanoinclRatio_sl, "inclusive semileptonic" ,"lp");
  leg42->AddEntry(hNanoexclRatio_sl, "exclusive semileptonic" ,"lp");
  TCanvas *c4 = new TCanvas("c4","c4",13,47,1102,554);
  c4->Divide(2,1);
  {
    p1 = c4->cd(1);
    //p1->SetPad(0.01,0.01,0.49,0.99);
    p1->SetLeftMargin(0.15);
    p1->SetRightMargin(0.04);
    hNanoexclData_ch->Draw("hist");
    hNanoinclTTbar_sl->Draw("hist sames");
    hNanoexclTTbar_sl->Draw("hist sames");
    leg41->Draw();
    hNanoexclData_ch->GetXaxis()->SetTitle("m_{jj} (GeV)");
    hNanoexclData_ch->GetYaxis()->SetTitle("Entries/bin");
  }
  {
    p1 = c4->cd(2);
    p1->SetLeftMargin(0.15);
    p1->SetRightMargin(0.04);
    hNanoinclRatio_sl->Draw("hist");
    hNanoexclRatio_sl->Draw("sames hist");
    leg42->Draw();
    hNanoinclRatio_sl->GetXaxis()->SetTitle("m_{jj} (GeV)");
    hNanoinclRatio_sl->GetYaxis()->SetTitle("Data/t#bar{t} (Entries/bin)");
    hNanoinclRatio_sl->SetMinimum(0.5); hNanoinclRatio_sl->SetMaximum(1.8); 
  }




  // PlotRatio(hNanoexclRatio, hMiniRatio, "c4", false);
  // PlotRatio(hNanoinclRatio, hMiniRatio, "c4", false);

  // PlotRatio( hMiniRatio, hNanoexclRatio, "c4", false);
  // PlotRatio( hMiniRatio, hNanoinclRatio, "c4", false);
  
  
  
  return true;
}

void SetHistStyle(TH1F *h1, Color_t color, int width, int style)
{
  h1->SetLineColor(color);
  h1->SetLineWidth(width);
  h1->SetLineStyle(style);
  return;
}

//TPad* PlotRatio(THStack *hs, TH1F *h1, TH1F *h2,TGraphAsymmErrors *syst, TGraphAsymmErrors *systRatio, const char *cname, bool isLog)
TPad* PlotRatio(TH1F *h1, TH1F *h2, const char *cname, bool isLog)
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
    //hs->Draw("same hist");
    //syst->Draw("e2 sames");
    h1->Draw("e1p sames");               // Draw h1

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
    //pad2->SetGridx(); // vertical grid
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
    h3->SetMinimum(0.2);  // Define Y ..
    h3->SetMaximum(1.8); // .. range
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
    h1->GetYaxis()->SetTitleOffset(1.55);
    h1->GetYaxis()->SetLabelSize(25);

    h1->GetXaxis()->SetTitleOffset(3.5);
    h1->GetXaxis()->SetLabelOffset(0.1);
 
    // h2 settings
    //h2->SetLineColor(kRed);
    //h2->SetLineWidth(2);
 
    // Ratio plot (h3) settings
    h3->SetTitle(""); // Remove the ratio title
 
    // Y axis ratio plot settings
    h3->GetYaxis()->SetTitle("#frac{ex or inc}{mini}");
    h3->GetYaxis()->SetNdivisions(505);
    h3->GetYaxis()->SetTitleSize(25);
    h3->GetYaxis()->SetTitleFont(43);
    h3->GetYaxis()->SetTitleOffset(1.3);
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

