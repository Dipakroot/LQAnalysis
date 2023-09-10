/**********************************************************************
 Created on : 30/07/2021
 Purpose    : Plot the Pt, Eta, Phi comparison plots
 Author     : Indranil Das, Visiting Fellow
 Email      : indranil.das@cern.ch | indra.ehep@gmail.com
**********************************************************************/
#if !defined(__CINT__) || defined(__MAKECINT__)
#include <stdio.h>
#include <fstream>
#include <string>
#include <TF1.h>
#include "TF1.h"
#include "TH1.h"
#include "TH2.h"
#include <THStack.h>
#include "TCanvas.h"
#include "TList.h"
#include "TMath.h"
#include "TLatex.h"
#include "TStyle.h"
#include <TROOT.h>
#include <TGraphErrors.h>
#include <TLegend.h>
#include <TLine.h>
#include <TLatex.h>
#include <iostream>
#include <TFile.h>
#include <TRatioPlot.h>
#include <TPaveText.h>
#endif

int PAGPlotsAug2All(bool isBtag = 1, bool isMu = 1, int htype = 0)
{
  // Setters
  int SetGlobalStyle(void);
  int SetStatMarkerStyle(TGraphErrors *&, Color_t, Style_t, Size_t);
  int SetStatMarkerStyle(TH1F *&, Color_t, Style_t, Size_t);
  int SetStatMarkerStyle(TH1D *&, Color_t, Style_t, Size_t);
  int SetSysMarkerStyle(TGraphErrors *&, Color_t, Style_t);
  int SetCanvasStyle(TCanvas *&);
  int SetLegendStyle(TLegend *&);
  int PrintHSeparator(void);


  // ///////////////////////////////////////////////////////////////////////////////////////////  
  int year = 2016;
  float luminosity[3] = {35.9, 41.5, 59.7};

  // bool isMu = 1; // 1 muon, 0 ele
  // bool isBtag = 1 ; // 1 btag, 0 kinfit
  // int htype = 0 ; // 0:leppt, 1:jetpt, 2:metpt, 3:lepeta, 4:jeteta, 5:lepphi, 6:jetphi, 7:metphi, 8:njet, 9:nbjet, 10:mjj
    
  const char* cutflow = (isMu) ? "_cutflow_mu" : "_cutflow_ele";
  const char* cutflowUS = (isMu) ? "_cutflowUS_mu" : "_cutflowUS_ele";
  const char* leppt = (isMu) ? "_lb_pt_mu" : "_lb_pt_ele";
  string histname;
  histname += (isBtag) ? "_lb" : "_kb" ; 

  if(htype==0)
    histname += (isMu) ? "_pt_mu" : "_pt_ele" ;  
  else if (htype==1)
    histname += (isMu) ? "_pt_mu_jets" : "_pt_ele_jets" ;  
  else if (htype==2)
    histname += (isMu) ? "_pt_mu_met" : "_pt_ele_met" ;  
  else if(htype==3)
    histname += (isMu) ? "_eta_mu" : "_eta_ele" ;  
  else if (htype==4)
    histname += (isMu) ? "_eta_mu_jets" : "_eta_ele_jets" ;
  else if(htype==5)
    histname += (isMu) ? "_phi_mu" : "_phi_ele" ;  
  else if (htype==6)
    histname += (isMu) ? "_phi_mu_jets" : "_phi_ele_jets" ;  
  else if (htype==7)
    histname += (isMu) ? "_phi_mu_met" : "_phi_ele_met" ;  
  else if (htype==8)
    histname += (isMu) ? "_njet_mu" : "_njet_ele" ;  
  else if (htype==9)
    histname += (isMu) ? "_nbjet_mu" : "_nbjet_ele" ;  
  else if (htype==10)
    histname += (isMu) ? "_mjj_mu" : "_mjj_ele" ;  
  
  cout << "Histname : " << histname << endl;
  
  string outputpdf = Form("figs/Week_Work_Report/2021-11-05/%d/MCQCD/hist%s.pdf",year,histname.c_str());
  const char* dir = "grid_v31_Syst/CBA_Skim_Syst_MedID";
  
  const char *basedir = "/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna";  
  const char* datafile = (isMu) ? Form("root_files/%s/%d/all_DataMu.root",dir,year) : Form("root_files/%s/%d/all_DataEle.root",dir,year) ;
  const char* qcdfile = (isMu) ? Form("root_files/%s/%d/all_MCQCDMu.root",dir,year) : Form("root_files/%s/%d/all_MCQCDEle.root",dir,year) ;
  TFile *fin_nano_data	= TFile::Open(datafile);
  TFile *fin_nano_sig = 0x0 ;
  if(year == 2016)
    fin_nano_sig	= TFile::Open(Form("root_files/%s/%d/all_HplusM120.root",dir,year));
  TFile *fin_nano_ttbar = TFile::Open(Form("root_files/%s/%d/all_TTbar.root",dir,year));
  TFile *fin_nano_stop	= TFile::Open(Form("root_files/%s/%d/all_singleTop.root",dir,year));
  TFile *fin_nano_wjets	= TFile::Open(Form("root_files/%s/%d/all_Wjets.root",dir,year));
  TFile *fin_nano_dyjets = TFile::Open(Form("root_files/%s/%d/all_DYjets.root",dir,year));
  TFile *fin_nano_vbf	= TFile::Open(Form("root_files/%s/%d/all_VBFusion.root",dir,year));
  TFile *fin_nano_qcd	= TFile::Open(qcdfile);
  
  TH1D *hcf_nano_data	= (TH1D *)fin_nano_data->Get(((isMu) ? Form("DataMu/base/Iso/%s",histname.c_str()) : Form("DataEle/base/Iso/%s",histname.c_str())));
  TH1D *hcf_nano_sig = 0x0 ;
  if(year == 2016)
    hcf_nano_sig	= (TH1D *)fin_nano_sig->Get(Form("HplusM120/base/Iso/%s",histname.c_str()));
  TH1D *hcf_nano_ttbar	= (TH1D *)fin_nano_ttbar->Get(Form("TTbar/base/Iso/%s",histname.c_str()));
  TH1D *hcf_nano_stop	= (TH1D *)fin_nano_stop->Get(Form("singleTop/base/Iso/%s",histname.c_str())); 
  TH1D *hcf_nano_wjets	= (TH1D *)fin_nano_wjets->Get(Form("Wjets/base/Iso/%s",histname.c_str()));
  TH1D *hcf_nano_dyjets	= (TH1D *)fin_nano_dyjets->Get(Form("DYjets/base/Iso/%s",histname.c_str()));
  TH1D *hcf_nano_vbf	= (TH1D *)fin_nano_vbf->Get(Form("VBFusion/base/Iso/%s",histname.c_str()));
  TH1D *hcf_nano_qcd	= (TH1D *)fin_nano_qcd->Get(((isMu) ? Form("MCQCDMu/base/Iso/%s",histname.c_str()) : Form("MCQCDEle/base/Iso/%s",histname.c_str())));
  
  TH1D *hcf_nano_bkg = (TH1D *)hcf_nano_ttbar->Clone("Bkg");
  hcf_nano_bkg->Add(hcf_nano_stop);
  hcf_nano_bkg->Add(hcf_nano_wjets);
  hcf_nano_bkg->Add(hcf_nano_dyjets);
  hcf_nano_bkg->Add(hcf_nano_vbf);
  hcf_nano_bkg->Add(hcf_nano_qcd);

  hcf_nano_data->SetMarkerStyle(kFullCircle);
  hcf_nano_data->SetMarkerColor(kBlack);
  hcf_nano_data->SetMarkerSize(1.2);
  
  if(year == 2016){
    hcf_nano_sig->SetLineStyle(kDashed);
    hcf_nano_sig->SetLineColor(kRed);
    hcf_nano_sig->SetLineWidth(2);
  }

  hcf_nano_ttbar->SetFillColor(kCyan+1);
  
  hcf_nano_stop->SetFillColor(kViolet);

  hcf_nano_wjets->SetFillColor(kYellow+1);

  hcf_nano_dyjets->SetFillColor(kOrange+1);
  
  hcf_nano_vbf->SetFillColor(kGreen+2);

  hcf_nano_qcd->SetFillColor(kBlue);
  
  THStack *hs = new THStack("hs","");
  hs->Add(hcf_nano_vbf);
  hs->Add(hcf_nano_dyjets);
  hs->Add(hcf_nano_wjets);
  hs->Add(hcf_nano_qcd);
  hs->Add(hcf_nano_stop);
  hs->Add(hcf_nano_ttbar);


  TH1D *hData = (TH1D*)hcf_nano_data->Clone("hData"); 
  hData->SetTitle("");
  TH1D *hMC = (TH1D*)hcf_nano_bkg->Clone("hMC"); 
  ///////////////////////////////////////////////////////////////////////////////////////////  
  const char *hist_num_title = "Data";
  const char *hist_den_title = "All Bkg";

  const char *canvas_title = "NanoAOD vs MiniAOD"; //canvas and pad title
 
  string upper_pad_yaxis_title,upper_pad_xaxis_title,lower_pad_yaxis_title,lower_pad_xaxis_title;

  // 0:leppt, 1:jetpt, 2:metpt, 3:lepeta, 4:jeteta, 5:lepphi, 6:jetphi, 7:metphi, 8:njet, 9:nbjet, 10:mjj
  
  if(htype==0){
    if(isMu){
      upper_pad_yaxis_title = "Events / bin"; upper_pad_xaxis_title = "p_{T}^{#mu} (GeV)"; // upper pad axis titles
      lower_pad_yaxis_title = "#frac{Data}{Bkg}"; lower_pad_xaxis_title = "p_{T}^{#mu} (GeV)"; // lower pad axis titles
    }else{
      upper_pad_yaxis_title = "Events / bin"; upper_pad_xaxis_title = "p_{T}^{#it{e}} (GeV)"; // upper pad axis titles
      lower_pad_yaxis_title = "#frac{Data}{Bkg}"; lower_pad_xaxis_title = "p_{T}^{#it{e}} (GeV)"; // lower pad axis titles
    }
  }else if(htype==1){
    upper_pad_yaxis_title = "Events / bin"; upper_pad_xaxis_title = "p_{T}^{jets} (GeV)"; // upper pad axis titles
    lower_pad_yaxis_title = "#frac{Data}{Bkg}"; lower_pad_xaxis_title = "p_{T}^{jets} (GeV)"; // lower pad axis titles
  }else if(htype==2){
    upper_pad_yaxis_title = "Events / bin"; upper_pad_xaxis_title = "p_{T}^{miss} (GeV)"; // upper pad axis titles
    lower_pad_yaxis_title = "#frac{Data}{Bkg}"; lower_pad_xaxis_title = "p_{T}^{miss} (GeV)"; // lower pad axis titles
  }else if(htype==3){
    if(isMu){
      upper_pad_yaxis_title = "Events / bin"; upper_pad_xaxis_title = "#eta^{#mu}"; // upper pad axis titles
      lower_pad_yaxis_title = "#frac{Data}{Bkg}"; lower_pad_xaxis_title = "#eta^{#mu}"; // lower pad axis titles
    }else{
      upper_pad_yaxis_title = "Events / bin"; upper_pad_xaxis_title = "#eta^{#it{e}}"; // upper pad axis titles
      lower_pad_yaxis_title = "#frac{Data}{Bkg}"; lower_pad_xaxis_title = "#eta^{#it{e}}"; // lower pad axis titles
    }
  }else if(htype==4){
     upper_pad_yaxis_title = "Events / bin"; upper_pad_xaxis_title = "#eta^{jets}"; // upper pad axis titles
     lower_pad_yaxis_title = "#frac{Data}{Bkg}"; lower_pad_xaxis_title = "#eta^{jets}"; // lower pad axis titles
  }else if(htype==5){
    if(isMu){
      upper_pad_yaxis_title = "Events / bin"; upper_pad_xaxis_title = "#phi^{#mu}"; // upper pad axis titles
      lower_pad_yaxis_title = "#frac{Data}{Bkg}"; lower_pad_xaxis_title = "#phi^{#mu}"; // lower pad axis titles
    }else{
      upper_pad_yaxis_title = "Events / bin"; upper_pad_xaxis_title = "#phi^{#it{e}}"; // upper pad axis titles
      lower_pad_yaxis_title = "#frac{Data}{Bkg}"; lower_pad_xaxis_title = "#phi^{#it{e}}"; // lower pad axis titles
    }
  }else if(htype==6){
    upper_pad_yaxis_title = "Events / bin"; upper_pad_xaxis_title = "#phi^{jets}"; // upper pad axis titles
    lower_pad_yaxis_title = "#frac{Data}{Bkg}"; lower_pad_xaxis_title = "#phi^{jets}"; // lower pad axis titles
  }else if(htype==7){
    upper_pad_yaxis_title = "Events / bin"; upper_pad_xaxis_title = "#phi^{miss}"; // upper pad axis titles
    lower_pad_yaxis_title = "#frac{Data}{Bkg}"; lower_pad_xaxis_title = "#phi^{miss}"; // lower pad axis titles
  }else if(htype==8){
    upper_pad_yaxis_title = "Events / bin"; upper_pad_xaxis_title = "N^{jets}"; // upper pad axis titles
    lower_pad_yaxis_title = "#frac{Data}{Bkg}"; lower_pad_xaxis_title = "N^{jets}"; // lower pad axis titles
  }else if(htype==9){
    upper_pad_yaxis_title = "Events / bin"; upper_pad_xaxis_title = "N^{#it{b} jets}"; // upper pad axis titles
    lower_pad_yaxis_title = "#frac{Data}{Bkg}"; lower_pad_xaxis_title = "N^{#it{b} jets}"; // lower pad axis titles
  }else if(htype==10){
    upper_pad_yaxis_title = "Events / bin"; upper_pad_xaxis_title = "m_{jj} (GeV)"; // upper pad axis titles
    lower_pad_yaxis_title = "#frac{Data}{Bkg}"; lower_pad_xaxis_title = "m_{jj} (GeV)"; // lower pad axis titles
  }

  float upper_minY = 1.0e-1; float upper_maxY = 5.e7;  //y-axis range of upper pad
  //float upper_minY = 1.0e-1; float upper_maxY = 5.e12;  //y-axis range of upper pad
  float lower_minY = 0.5; float lower_maxY = 1.5;     //y-axis range of lower pad
  
  // 0:leppt, 1:jetpt, 2:metpt, 3:lepeta, 4:jeteta, 5:lepphi, 6:jetphi, 7:metphi, 8:njet, 9:nbjet, 10:mjj
  float upper_minX = 0.0; float upper_maxX = 500.0;
  if(htype>=0 and htype<=2){
    upper_minX = 0.0; upper_maxX = 500.0;   //x-axis range
  }else if(htype>=3 and htype<=7){
    upper_minX = -5.0; upper_maxX = 5.0;   //x-axis range
  }else if(htype==8){
    upper_minX = 0.0; upper_maxX = 16.0;   //x-axis range
  }else if(htype==9){
    upper_minX = 0.0; upper_maxX = 10.0;   //x-axis range
  }else if(htype==10){
    upper_minX = 0.0; upper_maxX = 200.0;   //x-axis range
  }

  float integral_min = upper_minX; float integral_max = upper_maxX; // for integral calculation
  //float integral_min = 4.0; float integral_max = upper_maxX; // for integral calculation

  //float legend_pos[4] = {0.5, 0.65, 0.88, 0.86};
  float legend_pos1[4] = {0.38, 0.70, 0.54, 0.86};
  float legend_pos2[4] = {0.55, 0.70, 0.71, 0.86};
  float legend_pos3[4] = {0.72, 0.70, 0.88, 0.86};
  ///////////////////////////////////////////////////////////////////////////////////////////  

  gStyle->SetOptStat(0);
  //Ranges
  hData->SetMaximum(upper_maxY);
  hData->SetMinimum(upper_minY);
  hData->GetXaxis()->SetRangeUser(upper_minX, upper_maxX);
  hMC->GetXaxis()->SetRangeUser(upper_minX, upper_maxX);
  //hData->GetXaxis()->SetRange(hData->FindBin(upper_minX), hData->FindBin(upper_maxX));
  //hMC->GetXaxis()->SetRange(upper_minX, upper_maxX);
  //axis Titles
  hData->GetXaxis()->SetTitle(upper_pad_xaxis_title.c_str());
  hData->GetYaxis()->SetTitle(upper_pad_yaxis_title.c_str());
  //Now add style and color
  SetStatMarkerStyle(hData, kBlack, kFullCircle, 1);
  SetStatMarkerStyle(hMC, kBlue, kFullSquare, 0.1);  
  
  float canvas_scale = 1;
  int canvas_width = TMath::Nint(canvas_scale*900) ;
  int canvas_height = TMath::Nint(canvas_scale*800) ;
  auto c1 = new TCanvas("c1", canvas_title, canvas_width, canvas_height);
  //auto rp = new TRatioPlot(hData, hMC, "divsym");
  auto rp = new TRatioPlot(hData, hMC, "divsym");
  //auto rp = new TRatioPlot(hs, hData, "divsym");
  rp->SetH1DrawOpt("e1");
  rp->SetH2DrawOpt("hist");
  c1->SetTicks(1, 1);
  //rp->GetLowerRefYaxis()->SetMaximum(1.4);
  rp->Draw();
  gPad->Modified(); gPad->Update(); // make sure it’s really (re)drawn
  TPad *p = rp->GetUpperPad();
  p->cd();
  // //hData->Draw("e1p");
  hs->Draw("same hist");
  if(year == 2016)
    hcf_nano_sig->Draw("same hist");
  hData->Draw("e1p same");

  TLegend *leg1 = p->BuildLegend();
  for(int i = 0 ; i < 10 ; i++)
    leg1->DeleteEntry() ;// This is to delete default title of hData
  leg1->AddEntry(hData, Form("%s",hist_num_title) ,"lp");
  leg1->AddEntry(hMC, Form("%s",hist_den_title) ,"lp");
  leg1->AddEntry(hcf_nano_ttbar, Form("#it{t}#bar{#it{t}}") ,"f");

  TLegend *leg2 = p->BuildLegend();
  for(int i = 0 ; i < 10 ; i++)
    leg2->DeleteEntry() ;// This is to delete default title of hData  
  leg2->AddEntry(hcf_nano_stop, Form("Single #it{t}") ,"f");
  leg2->AddEntry(hcf_nano_wjets, Form("#it{W} + jets") ,"f");
  leg2->AddEntry(hcf_nano_dyjets, Form("#it{Z}/#gamma + jets") ,"f");

  TLegend *leg3 = p->BuildLegend();
  for(int i = 0 ; i < 10 ; i++)
    leg3->DeleteEntry() ;// This is to delete default title of hData  
  leg3->AddEntry(hcf_nano_vbf, Form("VV") ,"f");
  leg3->AddEntry(hcf_nano_qcd, Form("QCD") ,"f");
  if(year == 2016)
    leg3->AddEntry(hcf_nano_sig, Form("m_{H^{+}} = 120 GeV") ,"l");

  leg1->SetX1(legend_pos1[0]); leg1->SetY1(legend_pos1[1]); 
  leg1->SetX2(legend_pos1[2]); leg1->SetY2(legend_pos1[3]); 

  leg2->SetX1(legend_pos2[0]); leg2->SetY1(legend_pos2[1]); 
  leg2->SetX2(legend_pos2[2]); leg2->SetY2(legend_pos2[3]); 

  leg3->SetX1(legend_pos3[0]); leg3->SetY1(legend_pos3[1]); 
  leg3->SetX2(legend_pos3[2]); leg3->SetY2(legend_pos3[3]); 

  SetLegendStyle(leg1);
  SetLegendStyle(leg2);
  SetLegendStyle(leg3);

  leg1->Draw();
  leg2->Draw();
  leg3->Draw();

  TPaveText *t1 = new TPaveText(0.60,0.91,0.90,0.98,"NDC");
  t1->SetFillStyle(0);
  t1->SetBorderSize(0);
  t1->SetTextFont(42);
  t1->SetTextSize(.05); 
  t1->SetMargin(0.1);
  t1->AddText(Form("%3.1f fb^{-1} (%d) (13 TeV)",luminosity[year%2016],year));
  t1->Draw();
  
  TPaveText *t2 = new TPaveText(0.08, 0.78, 0.36, 0.86,"NDC");
  t2->SetFillStyle(0);
  t2->SetBorderSize(0);
  t2->SetTextFont(42);
  t2->SetTextSize(.05); 
  t2->SetMargin(0.1);
  if(isBtag and isMu)
    t2->AddText("BTag: (#mu + jets)");
  if(isBtag and !isMu)
    t2->AddText("BTag: (#it{e} + jets)");
  if(!isBtag and isMu)
    t2->AddText("KinFit: (#mu + jets)");
  if(!isBtag and !isMu)
    t2->AddText("KinFit: (#it{e} + jets)");
  t2->Draw();

  //rp->GetLowYaxis()->SetNdivisions(402);
  rp->GetLowYaxis()->SetNdivisions(406);
  rp->GetLowerRefYaxis()->SetTitle(lower_pad_yaxis_title.c_str());
  rp->GetLowerRefXaxis()->SetTitleOffset(1.2);
  //rp->GetLowerRefYaxis()->SetTitleSize(4.1);
  rp->GetUpperRefYaxis()->SetTitle(upper_pad_yaxis_title.c_str());
  rp->GetLowerRefYaxis()->SetRangeUser(lower_minY, lower_maxY);
  rp->GetUpperPad()->SetLogy();
  // rp->GetUpperPad()->SetTickX();
  // rp->GetUpperPad()->SetTickY();
  p->Modified(); p->Update();

  c1->Update();
  c1->SaveAs(outputpdf.c_str());
  c1->SaveAs("plot.pdf");

  
  return true; 
}

int PrintHSeparator(void){
  for (int i=0;i<130;i++) 
    printf("="); 
  cout << endl;
  return true;
}

int SetLegendStyle(TLegend *& leg)
{
  
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->SetTextFont(42);
  leg->SetTextSize(.04); 
  leg->SetMargin(0.1);
  leg->SetEntrySeparation(0.2);
  
  return true;
}

int SetCanvasStyle(TCanvas *& canvas)
{

  canvas->SetFillColor(0);
  canvas->SetBorderMode(0);
  canvas->SetBorderSize(2);
  canvas->SetLogy();
  canvas->SetTickx(1);
  canvas->SetTicky(1);
  canvas->SetLeftMargin(0.1178707);
  canvas->SetRightMargin(0.02471483);
  canvas->SetTopMargin(0.02941176);
  canvas->SetBottomMargin(0.1221719);
  canvas->SetFrameBorderMode(0);
  canvas->SetFrameBorderMode(0);

  // canvas->SetFillColor(0);
  // canvas->SetBorderMode(0);
  // canvas->SetBorderSize(2);
  // canvas->SetLeftMargin(0.10);
  // canvas->SetRightMargin(0.03);
  // canvas->SetTopMargin(0.03);
  // canvas->SetBottomMargin(0.12);
  // canvas->SetFrameBorderMode(0);
  // canvas->SetLogy();
  // canvas->SetTickx();
  // canvas->SetTicky();
  
  return 0;
}

int SetGlobalStyle(void)
{
  //----------------
  // // drawing options
  int font = 42;
	
  gStyle->SetOptStat(0);
  gROOT->SetStyle("Plain");
  gStyle->SetCanvasBorderMode(0);
  gStyle->SetCanvasColor(kWhite);
  gStyle->SetFrameBorderMode(0);
  gStyle->SetFrameFillColor(kWhite);
  gStyle->SetPalette(1);
  gStyle->SetTextFont(font);
  gStyle->SetLabelFont(font,"x");
  gStyle->SetTitleFont(font,"x");
  gStyle->SetLabelFont(font,"y");
  gStyle->SetTitleFont(font,"y");
	
  if (1){ // extracted from pwg2 ref
    gStyle->SetFrameBorderMode(0);
    gStyle->SetFrameFillColor(0);
    gStyle->SetCanvasBorderMode(0);
    gStyle->SetPadBorderMode(0);
    gStyle->SetPadColor(10);
    gStyle->SetCanvasColor(10);
    gStyle->SetTitleFillColor(10);
    gStyle->SetTitleBorderSize(1);
    gStyle->SetStatColor(10);
    gStyle->SetStatBorderSize(1);
    gStyle->SetLegendBorderSize(1);
    //
    gStyle->SetDrawBorder(0);
    gStyle->SetTextFont(font);
    gStyle->SetStatFont(font);
    gStyle->SetStatFontSize(0.05);
    gStyle->SetStatX(0.97);
    gStyle->SetStatY(0.98);
    gStyle->SetStatH(0.03);
    gStyle->SetStatW(0.3);
    gStyle->SetTickLength(0.02,"y");
    gStyle->SetEndErrorSize(3);
    gStyle->SetLabelSize(0.042,"xyz");
    gStyle->SetLabelFont(font,"xyz");
    gStyle->SetLabelOffset(0.003,"xyz");
    gStyle->SetTitleFont(font,"xyz");
    gStyle->SetTitleOffset(1.35,"xyz");
    gStyle->SetTitleSize(0.042,"xyz");
    gStyle->SetMarkerSize(1);
    gStyle->SetPalette(1,0);
  }
  gROOT->ForceStyle();
  gStyle->SetEndErrorSize(0);

  // int font = 42;
  // gROOT->SetStyle("Plain");
  // gStyle->SetPalette(1); 
  // gStyle->SetFrameBorderMode(0);
  // gStyle->SetFrameFillColor(0);
  // gStyle->SetCanvasBorderMode(0);
  // gStyle->SetPadBorderMode(0);
  // gStyle->SetPadColor(10);
  // gStyle->SetCanvasColor(10);
  // gStyle->SetTitleFillColor(10);
  // gStyle->SetTitleBorderSize(1);
  // gStyle->SetStatColor(10);
  // gStyle->SetStatBorderSize(1);
  // gStyle->SetLegendBorderSize(1);
  // gStyle->SetDrawBorder(0);
  // gStyle->SetTextFont(font);
  // gStyle->SetStatFont(font);
  // gStyle->SetStatFontSize(0.05);
  // gStyle->SetStatX(0.97);
  // gStyle->SetStatY(0.98);
  // gStyle->SetStatH(0.03);
  // gStyle->SetStatW(0.3);
  // gStyle->SetPadTickX(1);
  // gStyle->SetPadTickY(1);
  // gStyle->SetTickLength(0.02,"y");
  // gStyle->SetEndErrorSize(3);
  // gStyle->SetLabelSize(0.05,"xyz");
  // gStyle->SetLabelFont(font,"xyz"); 
  // gStyle->SetLabelOffset(0.01,"xyz");
  // gStyle->SetTitleFont(font,"xyz");
  // gStyle->SetTitleOffset(1.2,"x"); 
  // gStyle->SetTitleOffset(1.2,"y");  
  // gStyle->SetTitleSize(0.05,"xyz");  
  // gStyle->SetMarkerSize(1.3); 
  // gStyle->SetPalette(1,0); 
  // gROOT->ForceStyle();
  // gStyle->SetOptStat(0);
  // gStyle->SetOptTitle(0);
  // gStyle->SetEndErrorSize(0);

  return 0;
}

int SetStatMarkerStyle(TGraphErrors*& grDataSt, Color_t color, Style_t style, Size_t markerSize)
{
  grDataSt->SetFillColor(1);
  grDataSt->SetLineColor(color);
  grDataSt->SetLineWidth(2);
  grDataSt->SetMarkerColor(color);
  grDataSt->SetMarkerStyle(style);
  grDataSt->SetMarkerSize(markerSize);

  return 0;
}

int SetSysMarkerStyle(TGraphErrors*& grDataSy, Color_t color, Style_t style)
{
  grDataSy->SetFillStyle(0);
  grDataSy->SetLineColor(color);
  grDataSy->SetLineWidth(2);
  grDataSy->SetMarkerColor(0);
  grDataSy->SetMarkerStyle(style);
  grDataSy->SetMarkerSize(2);


  return 0;
}


int SetStatMarkerStyle(TH1F*& h1, Color_t color, Style_t style, Size_t markerSize)
{
  h1->SetLineColor(color);
  h1->SetLineWidth(1);
  h1->SetMarkerColor(color);
  h1->SetMarkerStyle(style);
  h1->SetMarkerSize(markerSize);
  
  return true;
}

int SetStatMarkerStyle(TH1D*& h1, Color_t color, Style_t style, Size_t markerSize)
{
  h1->SetLineColor(color);
  h1->SetLineWidth(1);
  h1->SetMarkerColor(color);
  h1->SetMarkerStyle(style);
  h1->SetMarkerSize(markerSize);
  
  return true;
}
