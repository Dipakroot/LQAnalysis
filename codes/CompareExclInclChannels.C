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

int CompareExclInclChannels(bool isBtag = 1, bool isMu = 1, int htype = 8)
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
  TH1F *hNanoexclData_ch = (TH1F *)fin_nanoexcl_data->Get(((isMu) ? Form("DataMu/base/Iso/%s",histname.c_str()) : Form("DataEle/base/Iso/%s",histname.c_str())));
  TFile *fin_nanoexcl_dl = TFile::Open(Form("root_files/%s/%d/all_TTbar_iter1_Dilep.root",dir,year));
  TFile *fin_nanoexcl_hd = TFile::Open(Form("root_files/%s/%d/all_TTbar_iter1_Hadron.root",dir,year));
  TFile *fin_nanoexcl_sl = TFile::Open(Form("root_files/%s/%d/all_TTbar_iter1_Semilept.root",dir,year));
  TH1F *hNanoexclTTbar_dl = (TH1F *)fin_nanoexcl_dl->Get(Form("TTbar/base/Iso/%s",histname.c_str()));
  TH1F *hNanoexclTTbar_hd = (TH1F *)fin_nanoexcl_hd->Get(Form("TTbar/base/Iso/%s",histname.c_str()));
  TH1F *hNanoexclTTbar_sl = (TH1F *)fin_nanoexcl_sl->Get(Form("TTbar/base/Iso/%s",histname.c_str()));
  
  TFile *fin_nanoincl_ch = TFile::Open(Form("root_files/%s/%d/base_TTbar_inclusive_proof.root",dir,year));
  TH1F *hNanoinclTTbar_dl = (TH1F *)fin_nanoincl_ch->Get(Form("TTbar/base/Iso/%s",histname.c_str()));
  TH1F *hNanoinclTTbar_hd = (TH1F *)fin_nanoincl_ch->Get(Form("TTbar/base/Iso/%s1",histname.c_str()));
  TH1F *hNanoinclTTbar_sl = (TH1F *)fin_nanoincl_ch->Get(Form("TTbar/base/Iso/%s2",histname.c_str()));
  
  // TString histoname = hNanoinclTTbar->GetName();
  // if(histoname.Contains("mjj"))
  //   hNanoinclTTbar->Rebin(50);
  
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
  
  TH1F *hNanoRatio_dl = (TH1F *)hNanoinclTTbar_dl->Clone("incl/excl");
  hNanoRatio_dl->Divide(hNanoexclTTbar_dl);
  hNanoRatio_dl->SetTitle("");
  TH1F *hNanoRatio_hd = (TH1F *)hNanoinclTTbar_hd->Clone("incl/excl");
  hNanoRatio_hd->Divide(hNanoexclTTbar_hd);
  hNanoRatio_hd->SetTitle("");
  TH1F *hNanoRatio_sl = (TH1F *)hNanoinclTTbar_sl->Clone("incl/excl");
  hNanoRatio_sl->Divide(hNanoexclTTbar_sl);
  hNanoRatio_sl->SetTitle("");


  SetHistStyle(hNanoexclData_ch, kGreen, 3, 1);
  hNanoexclData_ch->SetMarkerColor(kBlack);
  hNanoexclData_ch->SetMarkerSize(1.5);
  hNanoexclData_ch->SetMarkerStyle(kFullCircle);
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

  SetHistStyle(hNanoRatio_dl, kBlack, 3, 1);
  SetHistStyle(hNanoRatio_hd, kBlack, 3, 1);
  SetHistStyle(hNanoRatio_sl, kBlack, 3, 1);
  
  hNanoexclData_ch->SetMaximum(upper_maxY);
  hNanoexclData_ch->SetMinimum(upper_minY);
  hNanoexclData_ch->GetXaxis()->SetRangeUser(upper_minX, upper_maxX);

  // hNanoinclRatio_dl->SetMaximum(upper_maxY);
  // hNanoinclRatio_dl->SetMinimum(upper_minY);
  hNanoinclRatio_dl->GetXaxis()->SetRangeUser(upper_minX, upper_maxX);
  hNanoinclRatio_hd->GetXaxis()->SetRangeUser(upper_minX, upper_maxX);
  hNanoinclRatio_sl->GetXaxis()->SetRangeUser(upper_minX, upper_maxX);
  hNanoexclRatio_dl->GetXaxis()->SetRangeUser(upper_minX, upper_maxX);
  hNanoexclRatio_hd->GetXaxis()->SetRangeUser(upper_minX, upper_maxX);
  hNanoexclRatio_sl->GetXaxis()->SetRangeUser(upper_minX, upper_maxX);

  hNanoexclData_ch->GetXaxis()->SetTitle(upper_pad_xaxis_title.c_str());
  hNanoexclData_ch->GetYaxis()->SetTitle(upper_pad_yaxis_title.c_str());

  hNanoinclRatio_dl->GetXaxis()->SetTitle(upper_pad_xaxis_title.c_str());
  hNanoinclRatio_dl->GetYaxis()->SetTitle(Form("data/t#bar{t} (%s)",upper_pad_yaxis_title.c_str()));
  hNanoinclRatio_hd->GetXaxis()->SetTitle(upper_pad_xaxis_title.c_str());
  hNanoinclRatio_hd->GetYaxis()->SetTitle(Form("data/t#bar{t} (%s)",upper_pad_yaxis_title.c_str()));
  hNanoinclRatio_sl->GetXaxis()->SetTitle(upper_pad_xaxis_title.c_str());
  hNanoinclRatio_sl->GetYaxis()->SetTitle(Form("data/t#bar{t} (%s)",upper_pad_yaxis_title.c_str()));
  
  hNanoRatio_dl->GetXaxis()->SetRangeUser(upper_minX, upper_maxX);
  hNanoRatio_dl->GetXaxis()->SetTitle(upper_pad_xaxis_title.c_str());
  hNanoRatio_dl->SetMinimum(lower_minY); hNanoRatio_dl->SetMaximum(lower_maxY);
  hNanoRatio_dl->GetYaxis()->SetTitle("inclusive/exclusive");
  hNanoRatio_hd->GetXaxis()->SetRangeUser(upper_minX, upper_maxX);
  hNanoRatio_hd->GetXaxis()->SetTitle(upper_pad_xaxis_title.c_str());
  hNanoRatio_hd->SetMinimum(lower_minY); hNanoRatio_hd->SetMaximum(lower_maxY);
  hNanoRatio_hd->GetYaxis()->SetTitle("inclusive/exclusive");
  hNanoRatio_sl->GetXaxis()->SetRangeUser(upper_minX, upper_maxX);
  hNanoRatio_sl->GetXaxis()->SetTitle(upper_pad_xaxis_title.c_str());
  hNanoRatio_sl->GetYaxis()->SetTitle("inclusive/exclusive");
  hNanoRatio_sl->SetMinimum(lower_minY); hNanoRatio_sl->SetMaximum(lower_maxY);

  hNanoexclTTbar_dl->GetXaxis()->SetRangeUser(upper_minX, upper_maxX);
  hNanoexclTTbar_dl->GetXaxis()->SetTitle(upper_pad_xaxis_title.c_str());
  hNanoexclTTbar_dl->GetYaxis()->SetTitle("Entries/bin");
  hNanoexclTTbar_dl->SetMinimum(upper_minY); hNanoexclTTbar_dl->SetMaximum(upper_maxY);
  hNanoexclTTbar_hd->GetXaxis()->SetRangeUser(upper_minX, upper_maxX);
  hNanoexclTTbar_hd->GetXaxis()->SetTitle(upper_pad_xaxis_title.c_str());
  hNanoexclTTbar_hd->GetYaxis()->SetTitle("Entries/bin");
  hNanoexclTTbar_hd->SetMinimum(upper_minY); hNanoexclTTbar_hd->SetMaximum(upper_maxY);
  hNanoexclTTbar_sl->GetXaxis()->SetRangeUser(upper_minX, upper_maxX);
  hNanoexclTTbar_sl->GetXaxis()->SetTitle(upper_pad_xaxis_title.c_str());
  hNanoexclTTbar_sl->GetYaxis()->SetTitle("Entries/bin");
  hNanoexclTTbar_sl->SetMinimum(upper_minY); hNanoexclTTbar_sl->SetMaximum(upper_maxY);

  TVirtualPad *p1 = 0x0;
  // TLegend *leg21 = new TLegend(0.6,0.7,0.99,0.95);
  // leg21->AddEntry(hNanoexclData_ch, "Data" ,"lp");
  // leg21->AddEntry(hNanoinclTTbar_dl, "inclusive dileptonic" ,"lp");
  // leg21->AddEntry(hNanoexclTTbar_dl, "exclusive dileptonic" ,"lp");
  // TLegend *leg22 = new TLegend(0.6,0.7,0.99,0.95);
  // leg22->AddEntry(hNanoinclRatio_dl, "inclusive dileptonic" ,"lp");
  // leg22->AddEntry(hNanoexclRatio_dl, "exclusive dileptonic" ,"lp");
  // TCanvas *c2 = new TCanvas("c2","c2",13,47,1102,554);
  // c2->Divide(2,1);
  // {
  //   p1 = c2->cd(1);
  //   //p1->SetPad(0.01,0.01,0.49,0.99);
  //   p1->SetLeftMargin(0.15);
  //   p1->SetRightMargin(0.04);
  //   p1->SetLogy();
  //   hNanoexclData_ch->Draw("hist e1p");
  //   hNanoinclTTbar_dl->Draw("hist sames");
  //   hNanoexclTTbar_dl->Draw("hist sames");
  //   double incl_err, excl_err;
  //   double integral_incl = hNanoinclTTbar_dl->IntegralAndError(hNanoinclTTbar_dl->FindBin(upper_minX), hNanoinclTTbar_dl->FindBin(upper_maxX), incl_err);
  //   double integral_excl = hNanoexclTTbar_dl->IntegralAndError(hNanoexclTTbar_dl->FindBin(upper_minX), hNanoexclTTbar_dl->FindBin(upper_maxX), excl_err);
  //   double ratio = 100.*integral_incl/integral_excl;
  //   double ratio_err = ratio * TMath::Sqrt(pow(incl_err/integral_incl,2) + pow(excl_err/integral_excl,2));
  //   cout<<" Ratio_dl_ttbar : (" << ratio << " +/- " << ratio_err  << ") %"<< endl;
  //   leg21->AddEntry((TObject*)0, Form("Ratio(in/ex) : %5.2lf #pm %5.2lf",ratio,ratio_err) ,"");
  //   leg21->Draw();
  // }
  // {
  //   c2->cd(2);
  //   hNanoinclRatio_dl->Draw("hist");
  //   hNanoexclRatio_dl->Draw("sames hist");
  //   double incl_err, excl_err;
  //   double integral_incl = hNanoinclRatio_dl->IntegralAndError(hNanoinclRatio_dl->FindBin(upper_minX), hNanoinclRatio_dl->FindBin(upper_maxX), incl_err);
  //   double integral_excl = hNanoexclRatio_dl->IntegralAndError(hNanoexclRatio_dl->FindBin(upper_minX), hNanoexclRatio_dl->FindBin(upper_maxX), excl_err);
  //   double ratio = 100.*integral_excl/integral_incl;
  //   double ratio_err = ratio * TMath::Sqrt(pow(incl_err/integral_incl,2) + pow(excl_err/integral_excl,2));
  //   cout<<" Ratio_dl : (" << ratio << " +/- " << ratio_err  << ") %"<< endl;
  //   leg22->AddEntry((TObject*)0, Form("Ratio(ex/in) : %5.2lf #pm %5.2lf",ratio,ratio_err) ,"");
  //   leg22->Draw();
  // }

  // TLegend *leg31 = new TLegend(0.6,0.7,0.99,0.95);
  // leg31->AddEntry(hNanoexclData_ch, "Data" ,"lp");
  // leg31->AddEntry(hNanoinclTTbar_hd, "inclusive hadronic" ,"lp");
  // leg31->AddEntry(hNanoexclTTbar_hd, "exclusive hadronic" ,"lp");
  // TLegend *leg32 = new TLegend(0.6,0.7,0.99,0.95);
  // leg32->AddEntry(hNanoinclRatio_hd, "inclusive hadronic" ,"lp");
  // leg32->AddEntry(hNanoexclRatio_hd, "exclusive hadronic" ,"lp");
  // TCanvas *c3 = new TCanvas("c3","c3",13,47,1102,554);
  // c3->Divide(2,1);
  // {
  //   p1 = c3->cd(1);
  //   p1->SetLeftMargin(0.15);
  //   p1->SetRightMargin(0.04);
  //   p1->SetLogy();
  //   hNanoexclData_ch->Draw("hist e1p");
  //   hNanoinclTTbar_hd->Draw("hist sames");
  //   hNanoexclTTbar_hd->Draw("hist sames");
  //   double incl_err, excl_err;
  //   double integral_incl = hNanoinclTTbar_hd->IntegralAndError(hNanoinclTTbar_hd->FindBin(upper_minX), hNanoinclTTbar_hd->FindBin(upper_maxX), incl_err);
  //   double integral_excl = hNanoexclTTbar_hd->IntegralAndError(hNanoexclTTbar_hd->FindBin(upper_minX), hNanoexclTTbar_hd->FindBin(upper_maxX), excl_err);
  //   double ratio = 100.*integral_incl/integral_excl;
  //   double ratio_err = ratio * TMath::Sqrt(pow(incl_err/integral_incl,2) + pow(excl_err/integral_excl,2));
  //   cout<<" Ratio_hd_ttbar : (" << ratio << " +/- " << ratio_err  << ") %"<< endl;
  //   leg31->AddEntry((TObject*)0, Form("Ratio(in/ex) : %5.2lf #pm %5.2lf",ratio,ratio_err) ,"");
  //   leg31->Draw();
  // }
  // {
  //   p1 = c3->cd(2);
  //   p1->SetLeftMargin(0.15);
  //   p1->SetRightMargin(0.04);
  //   hNanoinclRatio_hd->Draw("hist");
  //   hNanoexclRatio_hd->Draw("sames hist");
  //   double incl_err, excl_err;
  //   double integral_incl = hNanoinclRatio_hd->IntegralAndError(hNanoinclRatio_hd->FindBin(upper_minX), hNanoinclRatio_hd->FindBin(upper_maxX), incl_err);
  //   double integral_excl = hNanoexclRatio_hd->IntegralAndError(hNanoexclRatio_hd->FindBin(upper_minX), hNanoexclRatio_hd->FindBin(upper_maxX), excl_err);
  //   double ratio = 100.*integral_excl/integral_incl;
  //   double ratio_err = ratio * TMath::Sqrt(pow(incl_err/integral_incl,2) + pow(excl_err/integral_excl,2));
  //   cout<<" Ratio_hd : (" << ratio << " +/- " << ratio_err  << ") %"<< endl;
  //   leg32->AddEntry((TObject*)0, Form("Ratio(ex/in) : %5.2lf #pm %5.2lf",ratio,ratio_err) ,"");
  //   leg32->Draw();
  // }


  // TLegend *leg41 = new TLegend(0.6,0.7,0.99,0.95);
  // leg41->AddEntry(hNanoexclData_ch, "Data" ,"lp");
  // leg41->AddEntry(hNanoinclTTbar_sl, "inclusive semileptonic" ,"lp");
  // leg41->AddEntry(hNanoexclTTbar_sl, "exclusive semileptonic" ,"lp");
  // TLegend *leg42 = new TLegend(0.6,0.7,0.99,0.95);
  // leg42->AddEntry(hNanoinclRatio_sl, "inclusive semileptonic" ,"lp");
  // leg42->AddEntry(hNanoexclRatio_sl, "exclusive semileptonic" ,"lp");
  // TCanvas *c4 = new TCanvas("c4","c4",13,47,1102,554);
  // c4->Divide(2,1);
  // {
  //   p1 = c4->cd(1);
  //   p1->SetLeftMargin(0.15);
  //   p1->SetRightMargin(0.04);
  //   p1->SetLogy();
  //   hNanoexclData_ch->Draw("hist e1p");
  //   hNanoinclTTbar_sl->Draw("hist sames");
  //   hNanoexclTTbar_sl->Draw("hist sames");
  //   double incl_err, excl_err;
  //   double integral_incl = hNanoinclTTbar_sl->IntegralAndError(hNanoinclTTbar_sl->FindBin(upper_minX), hNanoinclTTbar_sl->FindBin(upper_maxX), incl_err);
  //   double integral_excl = hNanoexclTTbar_sl->IntegralAndError(hNanoexclTTbar_sl->FindBin(upper_minX), hNanoexclTTbar_sl->FindBin(upper_maxX), excl_err);
  //   double ratio = 100.*integral_incl/integral_excl;
  //   double ratio_err = ratio * TMath::Sqrt(pow(incl_err/integral_incl,2) + pow(excl_err/integral_excl,2));
  //   cout<<" Ratio_sl_ttbar : (" << ratio << " +/- " << ratio_err  << ") %"<< endl;
  //   leg41->AddEntry((TObject*)0, Form("Ratio(in/ex) : %5.2lf #pm %5.2lf",ratio,ratio_err) ,"");
  //   leg41->Draw();
  // }
  // {
  //   p1 = c4->cd(2);
  //   p1->SetLeftMargin(0.15);
  //   p1->SetRightMargin(0.04);
  //   hNanoinclRatio_sl->Draw("hist");
  //   hNanoexclRatio_sl->Draw("sames hist");
  //   double incl_err, excl_err;
  //   double integral_incl = hNanoinclRatio_sl->IntegralAndError(hNanoinclRatio_sl->FindBin(upper_minX), hNanoinclRatio_sl->FindBin(upper_maxX), incl_err);
  //   double integral_excl = hNanoexclRatio_sl->IntegralAndError(hNanoexclRatio_sl->FindBin(upper_minX), hNanoexclRatio_sl->FindBin(upper_maxX), excl_err);
  //   double ratio = 100.*integral_excl/integral_incl;
  //   double ratio_err = ratio * TMath::Sqrt(pow(incl_err/integral_incl,2) + pow(excl_err/integral_excl,2));
  //   cout<<" Ratio_sl : (" << ratio << " +/- " << ratio_err  << ") %"<< endl;
  //   leg42->AddEntry((TObject*)0, Form("Ratio(ex/in) : %5.2lf #pm %5.2lf",ratio,ratio_err) ,"");
  //   leg42->Draw();
  //   hNanoinclRatio_sl->SetMinimum(0.5); hNanoinclRatio_sl->SetMaximum(3.0); 
  // }


  TLegend *leg51 = new TLegend(0.36,0.78,0.99,0.93);
  leg51->AddEntry(hNanoinclTTbar_dl, "inclusive dilepton" ,"lp");
  leg51->AddEntry(hNanoexclTTbar_dl, "exclusive dilepton" ,"lp");
  TCanvas *c5 = new TCanvas("c5","c5",13,47,1102,554);
  c5->Divide(2,1);
  {
    p1 = c5->cd(1);
    //p1->SetPad(0.01,0.01,0.49,0.99);
    p1->SetLeftMargin(0.15);
    p1->SetRightMargin(0.04);
    p1->SetLogy();
    hNanoexclTTbar_dl->Draw("hist");
    hNanoinclTTbar_dl->Draw("hist sames");

    double incl_err, excl_err;
    double integral_incl = hNanoinclTTbar_dl->IntegralAndError(hNanoinclTTbar_dl->FindBin(upper_minX), hNanoinclTTbar_dl->FindBin(upper_maxX), incl_err);
    double integral_excl = hNanoexclTTbar_dl->IntegralAndError(hNanoexclTTbar_dl->FindBin(upper_minX), hNanoexclTTbar_dl->FindBin(upper_maxX), excl_err);
    double ratio = 100.*integral_incl/integral_excl;
    double ratio_err = ratio * TMath::Sqrt(pow(incl_err/integral_incl,2) + pow(excl_err/integral_excl,2));
    cout<<" Ratio_ttbar dl : (" << ratio << " +/- " << ratio_err  << ") %"<< endl;
    leg51->AddEntry((TObject*)0, Form("Ratio (in/ex) : (%5.2lf #pm %5.2lf)\%%",ratio,ratio_err) ,"");
    leg51->Draw();
  }
  {
    p1 = c5->cd(2);
    p1->SetLeftMargin(0.15);
    p1->SetRightMargin(0.04);
    hNanoRatio_dl->Draw("hist");
    gStyle->SetOptStat(kFALSE);
  }

  TLegend *leg61 = new TLegend(0.36,0.78,0.99,0.93);
  leg61->AddEntry(hNanoinclTTbar_hd, "inclusive hadronic" ,"lp");
  leg61->AddEntry(hNanoexclTTbar_hd, "exclusive hadronic" ,"lp");
  TCanvas *c6 = new TCanvas("c6","c6",13,47,1102,554);
  c6->Divide(2,1);
  {
    p1 = c6->cd(1);
    //p1->SetPad(0.01,0.01,0.49,0.99);
    p1->SetLeftMargin(0.15);
    p1->SetRightMargin(0.04);
    p1->SetLogy();
    hNanoexclTTbar_hd->Draw("hist");
    hNanoinclTTbar_hd->Draw("hist sames");

    double incl_err, excl_err;
    double integral_incl = hNanoinclTTbar_hd->IntegralAndError(hNanoinclTTbar_hd->FindBin(upper_minX), hNanoinclTTbar_hd->FindBin(upper_maxX), incl_err);
    double integral_excl = hNanoexclTTbar_hd->IntegralAndError(hNanoexclTTbar_hd->FindBin(upper_minX), hNanoexclTTbar_hd->FindBin(upper_maxX), excl_err);
    double ratio = 100.*integral_incl/integral_excl;
    double ratio_err = ratio * TMath::Sqrt(pow(incl_err/integral_incl,2) + pow(excl_err/integral_excl,2));
    cout<<" Ratio_ttbar hd : (" << ratio << " +/- " << ratio_err  << ") %"<< endl;
    leg61->AddEntry((TObject*)0, Form("Ratio (in/ex) : (%5.2lf #pm %5.2lf)\%%",ratio,ratio_err) ,"");
    leg61->Draw();
  }
  {
    p1 = c6->cd(2);
    p1->SetLeftMargin(0.15);
    p1->SetRightMargin(0.04);
    hNanoRatio_hd->Draw("hist");
    gStyle->SetOptStat(kFALSE);
  }
  
  TLegend *leg71 = new TLegend(0.36,0.78,0.99,0.93);
  leg71->AddEntry(hNanoinclTTbar_sl, "inclusive semilepton" ,"lp");
  leg71->AddEntry(hNanoexclTTbar_sl, "exclusive semilepton" ,"lp");
  TCanvas *c7 = new TCanvas("c7","c7",13,47,1102,554);
  c7->Divide(2,1);
  {
    p1 = c7->cd(1);
    //p1->SetPad(0.01,0.01,0.49,0.99);
    p1->SetLeftMargin(0.15);
    p1->SetRightMargin(0.04);
    p1->SetLogy();
    hNanoexclTTbar_sl->Draw("hist");
    hNanoinclTTbar_sl->Draw("hist sames");

    double incl_err, excl_err;
    double integral_incl = hNanoinclTTbar_sl->IntegralAndError(hNanoinclTTbar_sl->FindBin(upper_minX), hNanoinclTTbar_sl->FindBin(upper_maxX), incl_err);
    double integral_excl = hNanoexclTTbar_sl->IntegralAndError(hNanoexclTTbar_sl->FindBin(upper_minX), hNanoexclTTbar_sl->FindBin(upper_maxX), excl_err);
    double ratio = 100.*integral_incl/integral_excl;
    double ratio_err = ratio * TMath::Sqrt(pow(incl_err/integral_incl,2) + pow(excl_err/integral_excl,2));
    cout<<" Ratio_ttbar sl : (" << ratio << " +/- " << ratio_err  << ") %"<< endl;
    leg71->AddEntry((TObject*)0, Form("Ratio (in/ex) : (%5.2lf #pm %5.2lf)\%%",ratio,ratio_err) ,"");
    leg71->Draw();
  }
  {
    p1 = c7->cd(2);
    p1->SetLeftMargin(0.15);
    p1->SetRightMargin(0.04);
    hNanoRatio_sl->Draw("hist");
    gStyle->SetOptStat(kFALSE);
  }
  
  string outputpdf = Form("figs/Week_Work_Report/2021-11-19/CompareExlIncl/%d/hist%s_sl.pdf",year,histname.c_str());
  // c4->SaveAs(outputpdf.c_str());

  // outputpdf = Form("figs/Week_Work_Report/2021-11-19/CompareExlIncl/%d/hist%s_hd.pdf",year,histname.c_str());
  // c3->SaveAs(outputpdf.c_str());
  
  // outputpdf = Form("figs/Week_Work_Report/2021-11-19/CompareExlIncl/%d/hist%s_dl.pdf",year,histname.c_str());
  // c2->SaveAs(outputpdf.c_str());
  // c2->SaveAs("output.pdf");

  outputpdf = Form("figs/Week_Work_Report/2021-11-19/CompareExlIncl/%d/hist_inclexcl_%s_dl.pdf",year,histname.c_str());
  c5->SaveAs(outputpdf.c_str());
  outputpdf = Form("figs/Week_Work_Report/2021-11-19/CompareExlIncl/%d/hist_inclexcl_%s_hd.pdf",year,histname.c_str());
  c6->SaveAs(outputpdf.c_str());
  outputpdf = Form("figs/Week_Work_Report/2021-11-19/CompareExlIncl/%d/hist_inclexcl_%s_sl.pdf",year,histname.c_str());
  c7->SaveAs(outputpdf.c_str());
  c7->SaveAs("output.pdf");
  
  return true;
}

void SetHistStyle(TH1F *h1, Color_t color, int width, int style)
{
  h1->SetLineColor(color);
  h1->SetLineWidth(width);
  h1->SetLineStyle(style);
  return;
}
