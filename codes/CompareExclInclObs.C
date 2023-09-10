/**********************************************************************
 Created on : 16/11/2021
 Purpose    : Compare the observables for inclusive and exclusive sets.
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
#include <fstream>

using namespace std;

int CompareExclInclObs(bool isBtag = 1, bool isMu = 1, int htype = 8)
{
  void SetHistStyle(TH1F *h1, Color_t color, int width, int style);

  // ///////////////////////////////////////////////////////////////////////////////////////////  
  int year = 2016;
  //float luminosity[3] = {35.9, 41.5, 59.7};
  int decay_ch = 1; //1: dilep, 2:hadronic, 3:semileptonic
  
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
  
  const char *basedir = "/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna";  
  const char* dir = "grid_v36_Syst/CBA_Skim_Syst_lowreso";
  
  const char* datafile = (isMu) ? Form("root_files/%s/%d/all_DataMu.root",dir,year) : Form("root_files/%s/%d/all_DataEle.root",dir,year) ;  
  TFile *fin_nanoexcl_data = TFile::Open(datafile);
  TH1F *hNanoexclData = (TH1F *)fin_nanoexcl_data->Get(((isMu) ? Form("DataMu/base/Iso/%s",histname.c_str()) : Form("DataEle/base/Iso/%s",histname.c_str())));

  TFile *fin_nanoexcl = TFile::Open(Form("root_files/%s/%d/all_TTbar_full.root",dir,year));
  TH1F *hNanoexclTTbar = (TH1F *)fin_nanoexcl->Get(Form("TTbar/base/Iso/%s",histname.c_str()));

  TFile *fin_nanoincl = TFile::Open(Form("root_files/%s/%d/all_TTbar_TTPinclusive.root",dir,year));
  TH1F *hNanoinclTTbar = (TH1F *)fin_nanoincl->Get(Form("TTbar/base/Iso/%s",histname.c_str()));
  TString histoname = hNanoinclTTbar->GetName();
  if(histoname.Contains("mjj"))
    hNanoinclTTbar->Rebin(50);

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
  float lower_minY = 0.85; float lower_maxY = 1.1;     //y-axis range of lower pad
  
  // 0:leppt, 1:jetpt, 2:metpt, 3:lepeta, 4:jeteta, 5:lepphi, 6:jetphi, 7:metphi, 8:njet, 9:nbjet, 10:mjj
  float upper_minX = 0.0; float upper_maxX = 500.0;
  //if(htype>=0 and htype<=2){
  if(htype==1){
    upper_minX = 0.0; upper_maxX = 700.0;   //x-axis range
  }else if(htype>=3 and htype<=7){
    upper_minX = -5.0; upper_maxX = 5.0;   //x-axis range
  }else if(htype==8){
    upper_minX = 0.0; upper_maxX = 20.0;   //x-axis range
  }else if(htype==9){
    upper_minX = 0.0; upper_maxX = 10.0;   //x-axis range
  }else if(htype==10){
    upper_minX = 0.0; upper_maxX = 180.0;   //x-axis range
  }
  ///////////////////////////////////////////////////////////////////////////////////////////////////
  
  TH1F *hNanoRatio = (TH1F *)hNanoinclTTbar->Clone("incl/excl");
  hNanoRatio->Divide(hNanoexclTTbar);
  hNanoRatio->SetTitle("");
  
  SetHistStyle(hNanoinclTTbar, kRed, 3, 1);
  SetHistStyle(hNanoexclTTbar, kBlue, 3, 1);
  SetHistStyle(hNanoRatio, kBlack, 3, 1);
  
  hNanoRatio->GetXaxis()->SetRangeUser(upper_minX, upper_maxX);
  hNanoRatio->GetXaxis()->SetTitle(upper_pad_xaxis_title.c_str());
  hNanoRatio->GetYaxis()->SetTitle("inclusive/exclusive");
  hNanoRatio->SetMinimum(lower_minY); hNanoRatio->SetMaximum(lower_maxY);

  hNanoexclTTbar->GetXaxis()->SetRangeUser(upper_minX, upper_maxX);
  hNanoexclTTbar->GetXaxis()->SetTitle(upper_pad_xaxis_title.c_str());
  hNanoexclTTbar->GetYaxis()->SetTitle("Entries/bin");
  hNanoexclTTbar->SetMinimum(upper_minY); hNanoexclTTbar->SetMaximum(upper_maxY);  

  TVirtualPad *p1 = 0x0;
  TLegend *leg21 = new TLegend(0.36,0.78,0.99,0.93);
  leg21->AddEntry(hNanoinclTTbar, "inclusive" ,"lp");
  leg21->AddEntry(hNanoexclTTbar, "exclusive" ,"lp");
  TLegend *leg22 = new TLegend(0.6,0.7,0.99,0.95);
  leg22->AddEntry(hNanoRatio, "inclusive / exclusive" ,"lp");
  TCanvas *c2 = new TCanvas("c2","c2",13,47,1102,554);
  c2->Divide(2,1);
  {
    p1 = c2->cd(1);
    //p1->SetPad(0.01,0.01,0.49,0.99);
    p1->SetLeftMargin(0.15);
    p1->SetRightMargin(0.04);
    p1->SetLogy();
    hNanoexclTTbar->Draw("hist");
    hNanoinclTTbar->Draw("hist sames");

    double incl_err, excl_err;
    double integral_incl = hNanoinclTTbar->IntegralAndError(hNanoinclTTbar->FindBin(upper_minX), hNanoinclTTbar->FindBin(upper_maxX), incl_err);
    double integral_excl = hNanoexclTTbar->IntegralAndError(hNanoexclTTbar->FindBin(upper_minX), hNanoexclTTbar->FindBin(upper_maxX), excl_err);
    double ratio = 100.*integral_incl/integral_excl;
    double ratio_err = ratio * TMath::Sqrt(pow(incl_err/integral_incl,2) + pow(excl_err/integral_excl,2));
    cout<<" Ratio_ttbar : (" << ratio << " +/- " << ratio_err  << ") %"<< endl;
    leg21->AddEntry((TObject*)0, Form("Ratio (in/ex) : (%5.2lf #pm %5.2lf)\%%",ratio,ratio_err) ,"");
    leg21->Draw();
  }
  {
    p1 = c2->cd(2);
    p1->SetLeftMargin(0.15);
    p1->SetRightMargin(0.04);
    hNanoRatio->Draw("hist");
    //leg22->Draw();
    gStyle->SetOptStat(kFALSE);
  }
  
  string outputpdf = Form("figs/Week_Work_Report/2021-11-19/InclByExcl/%d/hist%s.pdf",year,histname.c_str());
  c2->SaveAs(outputpdf.c_str());
  c2->SaveAs("output.pdf");
  
  return true;
}

void SetHistStyle(TH1F *h1, Color_t color, int width, int style)
{
  h1->SetLineColor(color);
  h1->SetLineWidth(width);
  h1->SetLineStyle(style);
  return;
}
