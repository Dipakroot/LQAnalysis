/**********************************************************************
 Created on : 24/08/2021
 Purpose    : Estimate the DD QCD multijet
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
#include <TRatioPlot.h>
#include <TPaveText.h>
#include <TROOT.h>
#include <TChain.h>
#include <TLorentzVector.h>

#include <TRooH1D.h>
#include <Utils.h>
#include <apps/TRooABCD.h>

#include <iostream>
#include <fstream>

using namespace std;

int icounter = 0;
Float_t MinX = 4.0;
Float_t MaxX = -4.0;

float defaultRatioYmin = -4.0;
float defaultRatioYmax = 4.0;

string denoYaxis = "RegD/RegC";
string xTitle = "";

// typedef struct datatree{
//   int reg;
//   double mjj;
// }datatree;

int QCDDDLHD(int year = 2016, bool isBtag = 0, bool isMu = 1, int htype = 10)
{
  void ReadTree(string, int, vector<pair<int,double>>&);
  
  // Setters
  int SetGlobalStyle(void);
  int SetStatMarkerStyle(TGraphErrors *&, Color_t, Style_t, Size_t);
  int SetStatMarkerStyle(TH1F *&, Color_t, Style_t, Size_t);
  int SetStatMarkerStyle(TH1D *&, Color_t, Style_t, Size_t);
  int SetSysMarkerStyle(TGraphErrors *&, Color_t, Style_t);
  int SetCanvasStyle(TCanvas *&);
  int SetLegendStyle(TLegend *&);
  int PrintHSeparator(void);

  int CalcRatio(TH1D*& hDataEff, TH1D*& hSimEff, TH1D*& hRatio);
  int PlotRatioCanvas(TCanvas*& c1, TH1D*& hData, TH1D*& hSim,  TH1D*& hDByS);
  
  void makeHistoPositive(TH1D *, bool);
  double getStatUnc(TH1D *, double);

  ///////////////////////////////////////////////////////////////////////////////////////////////  
  //int year = 2016;
  
  float luminosity[3] = {35.9, 41.5, 59.8};

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
  else if (htype==11)
    histname = (isMu) ? "_ct_IncL_mjj_mu" : "_ct_IncL_mjj_ele" ;  
  else if (htype==12)
    histname = (isMu) ? "_ct_IncM_mjj_mu" : "_ct_IncM_mjj_ele" ;  
  else if (htype==13)
    histname = (isMu) ? "_ct_IncT_mjj_mu" : "_ct_IncT_mjj_ele" ;  
  else if (htype==14)
    histname = (isMu) ? "_ct_ExcL_mjj_mu" : "_ct_ExcL_mjj_ele" ;  
  else if (htype==15)
    histname = (isMu) ? "_ct_ExcM_mjj_mu" : "_ct_ExcM_mjj_ele" ;  
  else if (htype==16)
    histname = (isMu) ? "_ct_ExcT_mjj_mu" : "_ct_ExcT_mjj_ele" ;  
  else if (htype==17)
    histname = (isMu) ? "_ct_Exc0_mjj_mu" : "_ct_ExcL_mjj_ele" ;  

  string histname_RegA = histname ;
  string histname_RegB = histname + "_noniso";
  string histname_RegC = histname + "_noniso_lmet";
  string histname_RegD = histname + "_lmet";
  
  string outputpdf = Form("ffigs/Week_Work_Report/2022-09-01/%d/DD/hist%s.pdf",year,histname.c_str());
  //const char* dir = "grid_v32_Syst/CBA_Skim_Syst_jet_tightID";
  //const char* dir = "grid_v40_Syst/CBA_ctagv2-CombHist";
  //const char* dir = "grid_v33_Syst/CBA_Skim_Syst_EqPAGAug02";
  const char* dir = "grid_v40_Syst/CBA_gdjsoncorr-CombHist";
  
  const char* datafile = (isMu) ? Form("root_files/%s/%d/all_DataMu.root",dir,year) : Form("root_files/%s/%d/all_DataEle.root",dir,year) ;
  const char* qcdfile = (isMu) ? Form("root_files/%s/%d/all_MCQCDMu.root",dir,year) : Form("root_files/%s/%d/all_MCQCDEle.root",dir,year) ;
  TFile *fin_nano_data	= TFile::Open(datafile);
  TFile *fin_nano_sig = 0x0 ;
  //if(year == 2016)
    fin_nano_sig	= TFile::Open(Form("root_files/%s/%d/all_HplusM120.root",dir,year));
  TFile *fin_nano_ttbar = TFile::Open(Form("root_files/%s/%d/all_TTbar.root",dir,year));
  TFile *fin_nano_stop	= TFile::Open(Form("root_files/%s/%d/all_singleTop.root",dir,year));
  TFile *fin_nano_wjets	= TFile::Open(Form("root_files/%s/%d/all_Wjets.root",dir,year));
  TFile *fin_nano_dyjets = TFile::Open(Form("root_files/%s/%d/all_DYjets.root",dir,year));
  TFile *fin_nano_vbf	= TFile::Open(Form("root_files/%s/%d/all_VBFusion.root",dir,year));
  TFile *fin_nano_qcd	= TFile::Open(qcdfile);
  
  ///////////////////////////////////////// Get  the histograms from files //////////////////////////////// 
  TH1D *hcf_RegA_data	= (TH1D *)fin_nano_data->Get(((isMu) ? Form("DataMu/base/Iso/%s",histname_RegA.c_str()) : Form("DataEle/base/Iso/%s",histname_RegA.c_str())));
  TH1D *hcf_RegA_sig = 0x0 ;
  //if(year == 2016)
    hcf_RegA_sig	= (TH1D *)fin_nano_sig->Get(Form("HplusM120/base/Iso/%s",histname_RegA.c_str()));
  TH1D *hcf_RegA_ttbar	= (TH1D *)fin_nano_ttbar->Get(Form("TTbar/base/Iso/%s",histname_RegA.c_str()));
  TH1D *hcf_RegA_stop	= (TH1D *)fin_nano_stop->Get(Form("singleTop/base/Iso/%s",histname_RegA.c_str())); 
  TH1D *hcf_RegA_wjets	= (TH1D *)fin_nano_wjets->Get(Form("Wjets/base/Iso/%s",histname_RegA.c_str()));
  TH1D *hcf_RegA_dyjets	= (TH1D *)fin_nano_dyjets->Get(Form("DYjets/base/Iso/%s",histname_RegA.c_str()));
  TH1D *hcf_RegA_vbf	= (TH1D *)fin_nano_vbf->Get(Form("VBFusion/base/Iso/%s",histname_RegA.c_str()));
  TH1D *hcf_RegA_qcd	= (TH1D *)fin_nano_qcd->Get(((isMu) ? Form("MCQCDMu/base/Iso/%s",histname_RegA.c_str()) : Form("MCQCDEle/base/Iso/%s",histname_RegA.c_str())));  
  

  TH1D *hcf_RegB_data	= (TH1D *)fin_nano_data->Get(((isMu) ? Form("DataMu/base/NonIso/%s",histname_RegB.c_str()) : Form("DataEle/base/NonIso/%s",histname_RegB.c_str())));
  TH1D *hcf_RegB_sig = 0x0 ;
  //if(year == 2016)
    hcf_RegB_sig	= (TH1D *)fin_nano_sig->Get(Form("HplusM120/base/NonIso/%s",histname_RegB.c_str()));
  TH1D *hcf_RegB_ttbar	= (TH1D *)fin_nano_ttbar->Get(Form("TTbar/base/NonIso/%s",histname_RegB.c_str()));
  TH1D *hcf_RegB_stop	= (TH1D *)fin_nano_stop->Get(Form("singleTop/base/NonIso/%s",histname_RegB.c_str())); 
  TH1D *hcf_RegB_wjets	= (TH1D *)fin_nano_wjets->Get(Form("Wjets/base/NonIso/%s",histname_RegB.c_str()));
  TH1D *hcf_RegB_dyjets	= (TH1D *)fin_nano_dyjets->Get(Form("DYjets/base/NonIso/%s",histname_RegB.c_str()));
  TH1D *hcf_RegB_vbf	= (TH1D *)fin_nano_vbf->Get(Form("VBFusion/base/NonIso/%s",histname_RegB.c_str()));
  TH1D *hcf_RegB_qcd	= (TH1D *)fin_nano_qcd->Get(((isMu) ? Form("MCQCDMu/base/NonIso/%s",histname_RegB.c_str()) : Form("MCQCDEle/base/NonIso/%s",histname_RegB.c_str())));  
  
  TH1D *hcf_RegC_data	= (TH1D *)fin_nano_data->Get(((isMu) ? Form("DataMu/base/NonIsoLowMET/%s",histname_RegC.c_str()) : Form("DataEle/base/NonIsoLowMET/%s",histname_RegC.c_str())));
  TH1D *hcf_RegC_sig = 0x0 ;
  //if(year == 2016)
    hcf_RegC_sig	= (TH1D *)fin_nano_sig->Get(Form("HplusM120/base/NonIsoLowMET/%s",histname_RegC.c_str()));
  TH1D *hcf_RegC_ttbar	= (TH1D *)fin_nano_ttbar->Get(Form("TTbar/base/NonIsoLowMET/%s",histname_RegC.c_str()));
  TH1D *hcf_RegC_stop	= (TH1D *)fin_nano_stop->Get(Form("singleTop/base/NonIsoLowMET/%s",histname_RegC.c_str())); 
  TH1D *hcf_RegC_wjets	= (TH1D *)fin_nano_wjets->Get(Form("Wjets/base/NonIsoLowMET/%s",histname_RegC.c_str()));
  TH1D *hcf_RegC_dyjets	= (TH1D *)fin_nano_dyjets->Get(Form("DYjets/base/NonIsoLowMET/%s",histname_RegC.c_str()));
  TH1D *hcf_RegC_vbf	= (TH1D *)fin_nano_vbf->Get(Form("VBFusion/base/NonIsoLowMET/%s",histname_RegC.c_str()));
  TH1D *hcf_RegC_qcd	= (TH1D *)fin_nano_qcd->Get(((isMu) ? Form("MCQCDMu/base/NonIsoLowMET/%s",histname_RegC.c_str()) : Form("MCQCDEle/base/NonIsoLowMET/%s",histname_RegC.c_str()))); 
  
  TH1D *hcf_RegD_data	= (TH1D *)fin_nano_data->Get(((isMu) ? Form("DataMu/base/LowMET/%s",histname_RegD.c_str()) : Form("DataEle/base/LowMET/%s",histname_RegD.c_str())));
  TH1D *hcf_RegD_sig = 0x0 ;
  //if(year == 2016)
    hcf_RegD_sig	= (TH1D *)fin_nano_sig->Get(Form("HplusM120/base/LowMET/%s",histname_RegD.c_str()));
  TH1D *hcf_RegD_ttbar	= (TH1D *)fin_nano_ttbar->Get(Form("TTbar/base/LowMET/%s",histname_RegD.c_str()));
  TH1D *hcf_RegD_stop	= (TH1D *)fin_nano_stop->Get(Form("singleTop/base/LowMET/%s",histname_RegD.c_str())); 
  TH1D *hcf_RegD_wjets	= (TH1D *)fin_nano_wjets->Get(Form("Wjets/base/LowMET/%s",histname_RegD.c_str()));
  TH1D *hcf_RegD_dyjets	= (TH1D *)fin_nano_dyjets->Get(Form("DYjets/base/LowMET/%s",histname_RegD.c_str()));
  TH1D *hcf_RegD_vbf	= (TH1D *)fin_nano_vbf->Get(Form("VBFusion/base/LowMET/%s",histname_RegD.c_str()));
  TH1D *hcf_RegD_qcd	= (TH1D *)fin_nano_qcd->Get(((isMu) ? Form("MCQCDMu/base/LowMET/%s",histname_RegD.c_str()) : Form("MCQCDEle/base/LowMET/%s",histname_RegD.c_str()))); 


  // TH1D *hcf_RegB_data	= (TH1D *)fin_nano_data->Get(histname_RegB.c_str());
  // TH1D *hcf_RegB_sig = 0x0 ;
  // if(year == 2016)
  //   hcf_RegB_sig	= (TH1D *)fin_nano_sig->Get(histname_RegB.c_str());
  // TH1D *hcf_RegB_ttbar	= (TH1D *)fin_nano_ttbar->Get(histname_RegB.c_str());
  // TH1D *hcf_RegB_stop	= (TH1D *)fin_nano_stop->Get(histname_RegB.c_str()); 
  // TH1D *hcf_RegB_wjets	= (TH1D *)fin_nano_wjets->Get(histname_RegB.c_str());
  // TH1D *hcf_RegB_dyjets	= (TH1D *)fin_nano_dyjets->Get(histname_RegB.c_str());
  // TH1D *hcf_RegB_vbf	= (TH1D *)fin_nano_vbf->Get(histname_RegB.c_str());
  // TH1D *hcf_RegB_qcd	= (TH1D *)fin_nano_qcd->Get(histname_RegB.c_str());
  
  // TH1D *hcf_RegC_data	= (TH1D *)fin_nano_data->Get(histname_RegC.c_str());
  // TH1D *hcf_RegC_sig = 0x0 ;
  // if(year == 2016)
  //   hcf_RegC_sig	= (TH1D *)fin_nano_sig->Get(histname_RegC.c_str());
  // TH1D *hcf_RegC_ttbar	= (TH1D *)fin_nano_ttbar->Get(histname_RegC.c_str());
  // TH1D *hcf_RegC_stop	= (TH1D *)fin_nano_stop->Get(histname_RegC.c_str()); 
  // TH1D *hcf_RegC_wjets	= (TH1D *)fin_nano_wjets->Get(histname_RegC.c_str());
  // TH1D *hcf_RegC_dyjets	= (TH1D *)fin_nano_dyjets->Get(histname_RegC.c_str());
  // TH1D *hcf_RegC_vbf	= (TH1D *)fin_nano_vbf->Get(histname_RegC.c_str());
  // TH1D *hcf_RegC_qcd	= (TH1D *)fin_nano_qcd->Get(histname_RegC.c_str());
  
  // TH1D *hcf_RegD_data	= (TH1D *)fin_nano_data->Get(histname_RegD.c_str());
  // TH1D *hcf_RegD_sig = 0x0 ;
  // if(year == 2016)
  //   hcf_RegD_sig	= (TH1D *)fin_nano_sig->Get(histname_RegD.c_str());
  // TH1D *hcf_RegD_ttbar	= (TH1D *)fin_nano_ttbar->Get(histname_RegD.c_str());
  // TH1D *hcf_RegD_stop	= (TH1D *)fin_nano_stop->Get(histname_RegD.c_str()); 
  // TH1D *hcf_RegD_wjets	= (TH1D *)fin_nano_wjets->Get(histname_RegD.c_str());
  // TH1D *hcf_RegD_dyjets	= (TH1D *)fin_nano_dyjets->Get(histname_RegD.c_str());
  // TH1D *hcf_RegD_vbf	= (TH1D *)fin_nano_vbf->Get(histname_RegD.c_str());
  // TH1D *hcf_RegD_qcd	= (TH1D *)fin_nano_qcd->Get(histname_RegD.c_str());
  ////////////////////////////////End of getting the histograms from files //////////////////////////////// 
  
  //////////////////////////////// Add the MCs but MCQCD /////////////////////////////////////////////////
  //All MC but MCQCD
  TH1D *hcf_RegA_bkg = (TH1D *)hcf_RegA_ttbar->Clone("RegA_bkg");
  hcf_RegA_bkg->Add(hcf_RegA_stop);
  hcf_RegA_bkg->Add(hcf_RegA_wjets);
  hcf_RegA_bkg->Add(hcf_RegA_dyjets);
  hcf_RegA_bkg->Add(hcf_RegA_vbf);

  TH1D *hcf_RegB_bkg = (TH1D *)hcf_RegB_ttbar->Clone("RegB_bkg");
  hcf_RegB_bkg->Add(hcf_RegB_stop);
  hcf_RegB_bkg->Add(hcf_RegB_wjets);
  hcf_RegB_bkg->Add(hcf_RegB_dyjets);
  hcf_RegB_bkg->Add(hcf_RegB_vbf);

  TH1D *hcf_RegC_bkg = (TH1D *)hcf_RegC_ttbar->Clone("RegC_bkg");
  hcf_RegC_bkg->Add(hcf_RegC_stop);
  hcf_RegC_bkg->Add(hcf_RegC_wjets);
  hcf_RegC_bkg->Add(hcf_RegC_dyjets);
  hcf_RegC_bkg->Add(hcf_RegC_vbf);
  
  TH1D *hcf_RegD_bkg = (TH1D *)hcf_RegD_ttbar->Clone("RegD_bkg");
  hcf_RegD_bkg->Add(hcf_RegD_stop);
  hcf_RegD_bkg->Add(hcf_RegD_wjets);
  hcf_RegD_bkg->Add(hcf_RegD_dyjets);
  hcf_RegD_bkg->Add(hcf_RegD_vbf);
  /////////////////////////////////////////////////////////////////////////////////////////////////////////

  if(htype>=10 and htype<=17){
    hcf_RegA_bkg->Rebin(50);
    hcf_RegA_data->Rebin(50);
    hcf_RegB_bkg->Rebin(50);
    hcf_RegB_data->Rebin(50);
    hcf_RegC_bkg->Rebin(50);
    hcf_RegC_data->Rebin(50);
    hcf_RegD_bkg->Rebin(50);
    hcf_RegD_data->Rebin(50);
    //Later addition
    hcf_RegA_qcd->Rebin(50);
    hcf_RegB_qcd->Rebin(50);
    hcf_RegC_qcd->Rebin(50);
    hcf_RegD_qcd->Rebin(50);    
  }

  //////////////////////////////// Get the QCD for regions ////////////////////////////////////////////////
  TH1D *hcf_RegD_QCD = (TH1D *)hcf_RegD_data->Clone("RegD_QCD");
  hcf_RegD_QCD->Add(hcf_RegD_bkg, -1);
  makeHistoPositive(hcf_RegD_QCD, false) ;
    
  TH1D *hcf_RegC_QCD = (TH1D *)hcf_RegC_data->Clone("RegC_QCD");
  hcf_RegC_QCD->Add(hcf_RegC_bkg, -1);
  makeHistoPositive(hcf_RegC_QCD, false) ;

  TH1D *hcf_RegB_QCD = (TH1D *)hcf_RegB_data->Clone("RegB_QCD");
  hcf_RegB_QCD->Add(hcf_RegB_bkg, -1);
  makeHistoPositive(hcf_RegB_QCD, false) ;

  TH1D *hcf_RegA_QCD = (TH1D *)hcf_RegA_data->Clone("RegA_QCD");
  hcf_RegA_QCD->Add(hcf_RegA_bkg, -1);
  makeHistoPositive(hcf_RegA_QCD, false) ;
  /////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  //////////////////////////////// Calculate the QCD SF ///////////////////////////////////////////////////
  double intDiffC   = hcf_RegC_QCD->Integral();
  double errDiffC   = getStatUnc(hcf_RegC_QCD, 0.0);
  double intDiffD   = hcf_RegD_QCD->Integral();
  double errDiffD   = getStatUnc(hcf_RegD_QCD, 0.0);
  //Ratio of (Data-MC) from RegionD and RegionC
  double SF = intDiffD/intDiffC;
  double tmpD = errDiffD/intDiffD;
  double tmpC = errDiffC/intDiffC;
  double SF_error = SF*sqrt(tmpD*tmpD + tmpC*tmpC);
  printf("SF(%s) : %5.4lf +/- %5.4lf\n",histname.c_str(),SF,SF_error);
  /////////////////////////////////////////////////////////////////////////////////////////////////////////

  
  // /////////////////////////////// Modify the Region B result //////////////////////////////////////////////
  // double sError = 0.0;
  // double  norm = hcf_RegB_QCD->IntegralAndError(1, hcf_RegB_QCD->GetNbinsX(), sError);
  // //cout<<"intB = "<<norm<<", intB_err = "<<sError<<endl;
  // double tot_bin_cont = 0.0;
  // double tot_bin_err = 0.0;
  // for(int ibin=1; ibin<hcf_RegB_QCD->GetNbinsX(); ibin++){
  //     double bin_cont = hcf_RegB_QCD->GetBinContent(ibin);
  //     double bin_err = hcf_RegB_QCD->GetBinError(ibin);
  //     double new_bin_cont = SF*bin_cont;
  //     double new_bin_err = sqrt(pow(bin_cont*SF_error, 2) + pow(bin_err*SF, 2));
  //     tot_bin_cont = tot_bin_cont + new_bin_cont;
  //     tot_bin_err = tot_bin_err + new_bin_err*new_bin_err;
  //     hcf_RegA_QCD->SetBinContent(ibin, new_bin_cont);
  //     hcf_RegA_QCD->SetBinError(ibin, new_bin_err);
  //   }
  // hcf_RegA_bkg->Add(hcf_RegA_QCD);
  // //cout<<"tot_bin_cont= "<<tot_bin_cont<<", tot_bin_err = "<<sqrt(tot_bin_err)<<endl;
  // /////////////////////////////////////////////////////////////////////////////////////////////////////////


  ///////////////////////////////////////// ABCD demo example /////////////////////////////////////////////////
  double minHist = hcf_RegD_QCD->GetXaxis()->GetBinLowEdge(1);
  double maxHist = hcf_RegD_QCD->GetXaxis()->GetBinUpEdge(hcf_RegD_QCD->GetNbinsX());
  int nBins = hcf_RegD_QCD->GetNbinsX();
  
  RooRealVar mjj("mjj","mjj",0,400);
  
  //Define a signal and background histogram for each region
  const char* regionLabels[4] = {"A","B","C","D"};
  TRooH1D* s[4]; TRooH1D* b[4];
  
  for(int i=0;i<4;i++) {
    s[i] = new TRooH1D(Form("s_%s",regionLabels[i]),Form("region %s signal",regionLabels[i]),mjj,nBins);s[i]->SetFillColor(kRed);         //CHANGE NUMBER OF BINS HERE!
    b[i] = new TRooH1D(Form("b_%s",regionLabels[i]),Form("region %s background",regionLabels[i]),mjj,nBins);b[i]->SetFillColor(kCyan);    //CHANGE NUMBER OF BINS HERE!
  }
  
  //Set the signal 'yield' in each region
  for(int i =0; i < 4; i ++) {
    for(int k =1; k <=nBins ; k ++) {
      if(i==0 or i==3){
  	if(i==0){
  	  s[i]->SetBinContent(k, hcf_RegA_bkg->GetBinContent(k)) ;
  	  s[i]->SetBinError(k, hcf_RegA_bkg->GetBinError(k));
  	  b[i]->SetBinContent(k, hcf_RegA_qcd->GetBinContent(k)) ;
  	  b[i]->SetBinError(k, hcf_RegA_qcd->GetBinError(k)) ;
  	}else{
  	  s[i]->SetBinContent(k, hcf_RegC_bkg->GetBinContent(k)) ;
  	  s[i]->SetBinError(k, hcf_RegC_bkg->GetBinError(k)) ;
  	  b[i]->SetBinContent(k, hcf_RegC_qcd->GetBinContent(k)) ;
  	  b[i]->SetBinError(k, hcf_RegC_qcd->GetBinError(k)) ;
  	}
      }else{
  	if(i==1){
  	  s[i]->SetBinContent(k, hcf_RegB_bkg->GetBinContent(k)) ;
  	  s[i]->SetBinError(k, hcf_RegB_bkg->GetBinError(k)) ;
  	  b[i]->SetBinContent(k, hcf_RegB_qcd->GetBinContent(k)) ;
  	  b[i]->SetBinError(k, hcf_RegB_qcd->GetBinError(k)) ;
  	}else{
  	  s[i]->SetBinContent(k, hcf_RegD_bkg->GetBinContent(k)) ;
  	  s[i]->SetBinError(k, hcf_RegD_bkg->GetBinError(k)) ;
  	  b[i]->SetBinContent(k, hcf_RegD_qcd->GetBinContent(k)) ;
  	  b[i]->SetBinError(k, hcf_RegD_qcd->GetBinError(k)) ;
  	}
      }
      if( s[i]->GetBinContent(k)<0) s[i]->SetBinContent(k, 0) ;
      if( b[i]->GetBinContent(k)<1) b[i]->SetBinContent(k, 1) ;
    }//k-loop on bins    
  }
  
  // s[0]->SetBinContent(1,94.2786);s[1]->SetBinContent(1,2.456);
  // s[2]->SetBinContent(1,0.12);s[3]->SetBinContent(1,1.02);
  
  // //Statistical uncertainties can be added like this:
  // s[0]->SetBinError(1,3.3);s[1]->SetBinError(1,2.2);
  // s[2]->SetBinError(1,0.05);s[3]->SetBinError(1,0.44);
  
  // //A systematic uncertainty can be added by defining a 
  // //nuisance parameter, and making s depend on it, like this:
  
  // RooRealVar syst_np("syst_np","Systematic nuisance parameter",0,-5,5);
  // syst_np.setStringAttribute("constraintType","normal"); //means syst_np = 0 +/- 1
  
  // for(int i=0;i<4;i++) s[i]->addParameter(syst_np);
  
  // syst_np = 1;  //corresponds to the up-fluctuation values
  // s[0]->SetBinContent(1,96.);s[1]->SetBinContent(2,3.);
  // s[2]->SetBinContent(1,0.10);s[3]->SetBinContent(1,0.5);
  // syst_np = -1; //now set the down-fluctuations
  // s[0]->SetBinContent(1,96.);s[1]->SetBinContent(1,3.);
  // s[2]->SetBinContent(1,0.10);s[3]->SetBinContent(1,0.5);
  
  // syst_np = 0; //just reset to nominal, for convenience
  
  //normFactor for signal .. will be determined by fit
  RooRealVar mu("mu","mu",1,0,100);
   for(int i=0;i<4;i++) s[i]->addNormFactor(mu);
  
  // //example of global scale factor with uncertainty .. a 10% lumi uncertainty
  // RooRealVar lumi("lumi","lumi",1,0,2);
  // lumi.setStringAttribute("constraintType","gaussian(1,0.1)");
  // for(int i=0;i<4;i++) s[i]->addNormFactor(lumi);
  
  
  //Background is to be determined by fitting to data
  //But we will need add 'shapeFactors' (bin-specific normFactors) 
  //which will ensure that A/B = C/D 
  
  //all bkg bins will be determined by shapeFactors
  //for(int i=0;i<4;i++) b[i]->SetBinContent(1,1);

  //shapeFactors for bkg
  for(int i=1;i<=b[0]->GetXaxis()->GetNbins();i++) {
    RooRealVar* bkg_A = new RooRealVar(Form("bkg_A_bin%d",i),Form("Background in region A, bin %d",i),1,0,100); //bkg in signal region is a free parameter
    b[0]->addShapeFactor(i, *bkg_A);
    RooRealVar* tBA = new RooRealVar(Form("tBA_bin%d",i),Form("Transfer factor (A->B), bin %d",i),1,0,1000);
    b[1]->addShapeFactor(i, *tBA);
    RooRealVar* bkg_C = new RooRealVar(Form("bkg_C_bin%d",i),Form("Background in region D, bin %d",i),1,0,100); //bkg in region D is a free parameter
    b[2]->addShapeFactor(i, *bkg_C);
    b[3]->addShapeFactor(i, *tBA);
  }
  
  b[1]->addNormFactor( *b[0] ); //makes region B = tBA*bkg_A
  b[3]->addNormFactor( *b[2] ); //makes region D = tBA*bkg_C
  
  // //Combine s and b into 4 stacks
  // //and draw them too ...
  
  TCanvas c("Prefit","Prefit distributions");
  c.Divide(2,2);
  
  TRooHStack* h[4];
  for(int i=0;i<4;i++) {
    h[i] = new TRooHStack(Form("h_%s",regionLabels[i]),Form("signal+background in region %s",regionLabels[i]));h[i]->SetLineColor(kBlue);
    h[i]->Add(b[i]);h[i]->Add(s[i]);
    c.cd(i+1);
    h[i]->SetMinimum(0);//h[i]->SetMaximum(120);
    h[i]->Draw("e3005"); //draws with shaded error bar
  }  
  c.SaveAs(Form("prefit_%d.pdf",year));
  // //data
  
  // //create a RooCategory to say which region the event has landed in
  RooCategory cat("region","region");
  for(int i=0;i<4;i++) cat.defineType(regionLabels[i]); 
  
  RooRealVar ww("weightVar","weightVar",1);
  RooDataSet data("data","data",RooArgSet(mjj,ww,cat),"weightVar");
  vector<pair<int,double>> dataArray;
  ReadTree("DataMu", year, dataArray); int reg = -1;
  for(unsigned int idata = 0; idata < dataArray.size() ; idata++){
    reg = dataArray.at(idata).first ;
    mjj = dataArray.at(idata).second ;
    if(reg==0) cat.setLabel("A");
    if(reg==1) cat.setLabel("B");
    if(reg==2) cat.setLabel("C");
    if(reg==3) cat.setLabel("D");
    data.add(RooArgSet(mjj,cat),1);//events in signal region ... 
  }
  
  
  //now we construct a RooSimultaneous to perform a simultaneous fit of our 4 TRooHStacks to the data
  //To do that, we need to build the model for each TRooHStack
  
  RooArgList models;
  for(int i=0;i<4;i++) models.add( *TRooFit::BuildModel(*h[i],data) ); //adds the nuisance parameter constraint terms to each model (stack)

  RooSimultaneous model("model","model",models,cat);
  
  //RooWorkspace w; w.import(model);
  
  RooFitResult* r = model.fitTo(data,RooFit::Save());
  
  //Draw the postfit distributions
  TCanvas c2("Postfit","Postfit distributions");
  c2.Divide(2,2);
  
  for(int i=0;i<4;i++) {
    c2.cd(i+1);
    h[i]->Draw("e3005"); //draw post-fit state
    TH1* data_hist = (TH1*)s[0]->GetHist(0)->Clone(Form("data_%s",regionLabels[i])); //clones one of the source histograms to get same binning
    data_hist->Reset();
    data.fillHistogram( data_hist, mjj, Form("region==%d",i) );
    data_hist->SetMarkerStyle(20); data_hist->Draw("same");
    
    c2.cd(i+1); //draw on the prefit too
    data_hist->Draw("same");
    
  }
  c2.SaveAs(Form("postfit_%d.pdf",year));
  
  TCanvas cc("Pull","Nuisance Parameter Fit Pulls");
  TRooFitResult fr(r); 
  fr.Draw(); //draw the nuisance parameter pull plot
  cc.SaveAs(Form("pull_%d.pdf",year));
  
  std::cout << "bkg in signal region:" << b[0]->GetBinContent(1) << " +/- " << b[0]->GetBinError(1) << std::endl;
  std::cout << "signal in region:" << s[0]->GetBinContent(1) << " +/- " << s[0]->GetBinError(1) << std::endl;

  ///////////////////////////////////////// ABCD demo example /////////////////////////////////////////////////
  
  // ///////////////////////////////////////// ABCD tutorial /////////////////////////////////////////////////
  // double minHist = hcf_RegD_QCD->GetXaxis()->GetBinLowEdge(1);
  // double maxHist = hcf_RegD_QCD->GetXaxis()->GetBinUpEdge(hcf_RegD_QCD->GetNbinsX());
  // int nBins = hcf_RegD_QCD->GetNbinsX();
  // const char* regions[4] = {"A","B","C","D"};

  // //TRooABCD follows : A/B == C/D contrary to our case of A/B = D/C so in the input we have to swap D and C.
  
  // TH1* h_data[4];
  // TH1* h_signal[4];
  // for(int i=0;i<4;i++) {
  //   h_data[i] = new TH1D(Form("data_%s",regions[i]),Form("data_%s",regions[i]),nBins,minHist,maxHist);
  //   h_signal[i] = new TH1D(Form("sig_%s",regions[i]),Form("sig_%s",regions[i]),nBins,minHist,maxHist);
  // }
  // for(int i =0; i < 4; i ++) {
  //   for(int k =1; k <=nBins ; k ++) {
  //     if(i==0 or i==3){
  // 	if(i==0){
  // 	  h_data[i]->SetBinContent(k, hcf_RegA_QCD->GetBinContent(k)) ;
  // 	  h_data[i]->SetBinError(k, hcf_RegA_QCD->GetBinError(k));
  // 	  h_signal[i]->SetBinContent(k, hcf_RegA_qcd->GetBinContent(k)) ;
  // 	  h_signal[i]->SetBinError(k, hcf_RegA_qcd->GetBinError(k)) ;
  // 	}else{
  // 	  h_data[i]->SetBinContent(k, hcf_RegC_QCD->GetBinContent(k)) ;
  // 	  h_data[i]->SetBinError(k, hcf_RegC_QCD->GetBinError(k)) ;
  // 	  h_signal[i]->SetBinContent(k, hcf_RegC_qcd->GetBinContent(k)) ;
  // 	  h_signal[i]->SetBinError(k, hcf_RegC_qcd->GetBinError(k)) ;
  // 	}
  //     }else{
  // 	if(i==1){
  // 	  h_data[i]->SetBinContent(k, hcf_RegB_QCD->GetBinContent(k)) ;
  // 	  h_data[i]->SetBinError(k, hcf_RegB_QCD->GetBinError(k)) ;
  // 	  h_signal[i]->SetBinContent(k, hcf_RegB_qcd->GetBinContent(k)) ;
  // 	  h_signal[i]->SetBinError(k, hcf_RegB_qcd->GetBinError(k)) ;
  // 	}else{
  // 	  h_data[i]->SetBinContent(k, hcf_RegD_QCD->GetBinContent(k)) ;
  // 	  h_data[i]->SetBinError(k, hcf_RegD_QCD->GetBinError(k)) ;
  // 	  h_signal[i]->SetBinContent(k, hcf_RegD_qcd->GetBinContent(k)) ;
  // 	  h_signal[i]->SetBinError(k, hcf_RegD_qcd->GetBinError(k)) ;
  // 	}
  //     }
  //     if( h_data[i]->GetBinContent(k)<0) h_data[i]->SetBinContent(k, 0) ;
  //     if( h_signal[i]->GetBinContent(k)<1) h_signal[i]->SetBinContent(k, 1) ;
  //   }//k-loop on bins
    
  // }
  // TRooABCD abcd("abcd","my abcd");
  
  // //add data for regions B C and D
  // //if we wanted to unblind, we would 'AddData' with region A (i=0) too
  // for(int i=0;i<4;i++) {
  //   abcd.AddData(i,h_data[i]);
  // }
  // //if we want to add signal shape we do the following
  
  // //add signal
  // for(int i=0;i<4;i++) {
  //   abcd.AddSignal(i,h_signal[i]);
  // }
  
  // //if we want to use asimov data (corresponding to mu=0) in the signal region we do:
  // abcd.AddAsimovData(0,0 /*signal strength*/);
  
  // //if we want this to be a validation, we can add 'signal region' data, will be displayed in blue
  // //will not be used in the fit but will be used in computing the pvalues
  // //abcd.AddValidationData(0,h_data[0]);
  
  // //if we want to add a relative uncertainty  of e.g. 4% to bkg prediction in region A
  // //we add a scale factor with value 1 and uncert = 0.04 to region 0
  // //abcd.AddBkgScaleFactor(0, 1.0, 0.043); //adds a 4.3% uncert to bkg prediction in region A
  
  
  // //You can exclude parameters from the fit by setting them constant
  // //By default, m1 is constant, which is the transfer factor gradient parameter
  // //abcd.GetParameter("m1")->setConstant(false); //switches on linear transfer factor model
  // //abcd.GetParameter("m1")->setStringAttribute("fixedValue","0"); //will add a systematic variation corresponding to fixing m1=0
  // //abcd.GetParameter("mu")->setVal(0);abcd.GetParameter("mu")->setConstant(true); //disable signal

  // abcd.Draw(); //draws the state of the model before running the fit

  // // TRooFitResult* result = abcd.Fit(); //fit function will draw postfit results
  
  // // TCanvas pullPlot; result->Draw(); //to draw the pull plot of constrained parameters (on its own canvas)
  
  // // //compare the result to simple ABCD arithmetic method prediction
  // // double NB = abcd.GetDataHistogram(1)->Integral();
  // // double NC = abcd.GetDataHistogram(2)->Integral();
  // // double ND = abcd.GetDataHistogram(3)->Integral();
  // // double simplePrediction = NB * NC/ND;
  // // double simplePredictionError = sqrt( pow(NC/ND,2)*NB + pow(NB/ND,2)*NC + pow(NB*NC/(ND*ND),2)*ND ); //standard error propagation
  // // cout << "simple Prediction = " << simplePrediction << " +/- " << simplePredictionError 
  // //      << " vs TRooABCD = " << abcd.GetBkgIntegral(0) << " +/- " << abcd.GetBkgIntegralError(0) << std::endl;

  
  // ///////////////////////////////////////// ABCD tutorial /////////////////////////////////////////////////
  
  // ///////////////////////////////////////// Basic likelihood display  /////////////////////////////////////////////////
  // double minHist = hcf_RegD_QCD->GetXaxis()->GetBinLowEdge(1);
  // double maxHist = hcf_RegD_QCD->GetXaxis()->GetBinUpEdge(hcf_RegD_QCD->GetNbinsX());
  // int nBins = hcf_RegD_QCD->GetNbinsX();
  
  // RooRealVar mass( "mjj" , "mjj" , minHist, maxHist ) ; // a RooFit continuous variable with range //cLeft to aRight
  // TRooH1D *b[4] ; // will point to the four TRooH1D we will create
  // const char *regionLabels[4] = {"A" , "B" , "C",  "D"} ; //in clock-wise
  // // A | B
  // // D | C

  // for(int i =0; i < 4; i ++) {
  //   b[i] = new TRooH1D( Form ( "b_%s" , regionLabels[i] ) ,
  // 			Form ( "Region %s bkg" , regionLabels[i]) ,
  // 			mass , nBins , minHist, maxHist ) ;

  //   for(int k =1; k <=nBins ; k ++) {
  //     if(i==0 or i==3){
  // 	if(i==0)
  // 	  b[i]->SetBinContent(k, hcf_RegA_data->GetBinContent(k)) ;
  // 	else
  // 	  b[i]->SetBinContent(k, hcf_RegD_data->GetBinContent(k)) ;
  //     }else{
  // 	RooRealVar *sf = new RooRealVar( Form ( "sf_%s_bin%d", regionLabels[i], k ),
  // 					 Form ( "sf_%s_bin%d", regionLabels[i], k ), 1, 0, 2) ;
  // 	if(i==1)
  // 	  b[i]->SetBinContent(k, hcf_RegB_data->GetBinContent(k)) ;
  // 	else
  // 	  b[i]->SetBinContent(k, hcf_RegC_data->GetBinContent(k)) ;
  // 	b[i]->addShapeFactor(k, *sf) ;
  //     }
  //     if( b[i]->GetBinContent(k)<0) b[i]->SetBinContent(k, 0) ;
  //   }//k-loop on bins

    
  //   b[i]->SetFillColor( kCyan ) ;
  //   b[i]->setFloor( true ) ; // prevents value of this histogram being less than 0
  // }
  // // RooRealVar m( "m" , "#tilde{m}" , SF, 0 , 1 ) ;
  // // b[0]->addNormFactor(m);
  // // b[3]->addNormFactor(m);
  
  // TCanvas c("Prefit", "Prefit distributions", 800, 600) ;
  // c.Divide(2, 2);
  // for(int i =0; i <4; i ++) {
  //   c.cd(i+1);
  //   if(i==0){
  //     b[0]->Draw() ;
  //     hcf_RegA_data->Draw("e1p sames");
  //   }else if(i==1){
  //     b[1]->Draw() ;
  //     hcf_RegB_data->Draw("e1p sames");
  //   }else if(i==2){
  //     b[3]->Draw() ;
  //     hcf_RegD_data->Draw("e1p sames");     
  //   }else if(i==3){
  //     b[2]->Draw() ;
  //     hcf_RegC_data->Draw("e1p sames");      
  //   }
  //   // if(i!=1) hdata[i]->Draw("e1p sames");
  //   if(i==0){
  //     // print the TRooH1D integral ( i.e. prediction ) in signal region
  //     TText t ;
  //     double bkgErr ;
  //     double bkgPredicition = b[i]->IntegralAndError( bkgErr ) ;
  //     t.DrawTextNDC( 0.4, 0.8, Form( "Predicted = %g +/- %g ", bkgPredicition, bkgErr ) ) ;
  //   }
  // }
  // c.SaveAs("result.pdf");

  // ////////////////////////////////////////////////////////////////////////////////////////////////////////////

  // hcf_RegA_data->SetMarkerStyle(kFullCircle);
  // hcf_RegA_data->SetMarkerColor(kBlack);
  // hcf_RegA_data->SetMarkerSize(1.2);
  
  // if(year == 2016){
  //   hcf_RegA_sig->SetLineStyle(kDashed);
  //   hcf_RegA_sig->SetLineColor(kRed);
  //   hcf_RegA_sig->SetLineWidth(2);
  // }

  // hcf_RegA_ttbar->SetFillColor(kCyan+1);
  
  // hcf_RegA_stop->SetFillColor(kViolet);

  // hcf_RegA_wjets->SetFillColor(kYellow+1);

  // hcf_RegA_dyjets->SetFillColor(kOrange+1);
  
  // hcf_RegA_vbf->SetFillColor(kGreen+2);

  // hcf_RegA_QCD->SetFillColor(kBlue);
  
  // THStack *hs = new THStack("hs","");
  // hs->Add(hcf_RegA_vbf);
  // hs->Add(hcf_RegA_dyjets);
  // hs->Add(hcf_RegA_wjets);
  // hs->Add(hcf_RegA_QCD);
  // hs->Add(hcf_RegA_stop);
  // hs->Add(hcf_RegA_ttbar);


  // TH1D *hData = (TH1D*)hcf_RegA_data->Clone("hData"); 
  // hData->SetTitle("");
  // TH1D *hMC = (TH1D*)hcf_RegA_bkg->Clone("hMC"); 
  // ///////////////////////////////////////////////////////////////////////////////////////////  
  // const char *hist_num_title = "Data";
  // const char *hist_den_title = "All Bkg";

  // const char *canvas_title = "NanoAOD vs MiniAOD"; //canvas and pad title
  
  // string upper_pad_yaxis_title,upper_pad_xaxis_title,lower_pad_yaxis_title,lower_pad_xaxis_title;
  
  // // 0:leppt, 1:jetpt, 2:metpt, 3:lepeta, 4:jeteta, 5:lepphi, 6:jetphi, 7:metphi, 8:njet, 9:nbjet, 10:mjj
  
  // if(htype==0){
  //   if(isMu){
  //     upper_pad_yaxis_title = "Events / bin"; upper_pad_xaxis_title = "p_{T}^{#mu} (GeV)"; // upper pad axis titles
  //     lower_pad_yaxis_title = "#frac{Data}{Bkg}"; lower_pad_xaxis_title = "p_{T}^{#mu} (GeV)"; // lower pad axis titles
  //   }else{
  //     upper_pad_yaxis_title = "Events / bin"; upper_pad_xaxis_title = "p_{T}^{#it{e}} (GeV)"; // upper pad axis titles
  //     lower_pad_yaxis_title = "#frac{Data}{Bkg}"; lower_pad_xaxis_title = "p_{T}^{#it{e}} (GeV)"; // lower pad axis titles
  //   }
  // }else if(htype==1){
  //   upper_pad_yaxis_title = "Events / bin"; upper_pad_xaxis_title = "p_{T}^{jets} (GeV)"; // upper pad axis titles
  //   lower_pad_yaxis_title = "#frac{Data}{Bkg}"; lower_pad_xaxis_title = "p_{T}^{jets} (GeV)"; // lower pad axis titles
  // }else if(htype==2){
  //   upper_pad_yaxis_title = "Events / bin"; upper_pad_xaxis_title = "p_{T}^{miss} (GeV)"; // upper pad axis titles
  //   lower_pad_yaxis_title = "#frac{Data}{Bkg}"; lower_pad_xaxis_title = "p_{T}^{miss} (GeV)"; // lower pad axis titles
  // }else if(htype==3){
  //   if(isMu){
  //     upper_pad_yaxis_title = "Events / bin"; upper_pad_xaxis_title = "#eta^{#mu}"; // upper pad axis titles
  //     lower_pad_yaxis_title = "#frac{Data}{Bkg}"; lower_pad_xaxis_title = "#eta^{#mu}"; // lower pad axis titles
  //   }else{
  //     upper_pad_yaxis_title = "Events / bin"; upper_pad_xaxis_title = "#eta^{#it{e}}"; // upper pad axis titles
  //     lower_pad_yaxis_title = "#frac{Data}{Bkg}"; lower_pad_xaxis_title = "#eta^{#it{e}}"; // lower pad axis titles
  //   }
  // }else if(htype==4){
  //    upper_pad_yaxis_title = "Events / bin"; upper_pad_xaxis_title = "#eta^{jets}"; // upper pad axis titles
  //    lower_pad_yaxis_title = "#frac{Data}{Bkg}"; lower_pad_xaxis_title = "#eta^{jets}"; // lower pad axis titles
  // }else if(htype==5){
  //   if(isMu){
  //     upper_pad_yaxis_title = "Events / bin"; upper_pad_xaxis_title = "#phi^{#mu}"; // upper pad axis titles
  //     lower_pad_yaxis_title = "#frac{Data}{Bkg}"; lower_pad_xaxis_title = "#phi^{#mu}"; // lower pad axis titles
  //   }else{
  //     upper_pad_yaxis_title = "Events / bin"; upper_pad_xaxis_title = "#phi^{#it{e}}"; // upper pad axis titles
  //     lower_pad_yaxis_title = "#frac{Data}{Bkg}"; lower_pad_xaxis_title = "#phi^{#it{e}}"; // lower pad axis titles
  //   }
  // }else if(htype==6){
  //   upper_pad_yaxis_title = "Events / bin"; upper_pad_xaxis_title = "#phi^{jets}"; // upper pad axis titles
  //   lower_pad_yaxis_title = "#frac{Data}{Bkg}"; lower_pad_xaxis_title = "#phi^{jets}"; // lower pad axis titles
  // }else if(htype==7){
  //   upper_pad_yaxis_title = "Events / bin"; upper_pad_xaxis_title = "#phi^{miss}"; // upper pad axis titles
  //   lower_pad_yaxis_title = "#frac{Data}{Bkg}"; lower_pad_xaxis_title = "#phi^{miss}"; // lower pad axis titles
  // }else if(htype==8){
  //   upper_pad_yaxis_title = "Events / bin"; upper_pad_xaxis_title = "N^{jets}"; // upper pad axis titles
  //   lower_pad_yaxis_title = "#frac{Data}{Bkg}"; lower_pad_xaxis_title = "N^{jets}"; // lower pad axis titles
  // }else if(htype==9){
  //   upper_pad_yaxis_title = "Events / bin"; upper_pad_xaxis_title = "N^{#it{b} jets}"; // upper pad axis titles
  //   lower_pad_yaxis_title = "#frac{Data}{Bkg}"; lower_pad_xaxis_title = "N^{#it{b} jets}"; // lower pad axis titles
  // }else if(htype>=10 and htype<=17){
  //   upper_pad_yaxis_title = "Events / bin"; upper_pad_xaxis_title = "m_{jj} (GeV)"; // upper pad axis titles
  //   lower_pad_yaxis_title = "#frac{Data}{Bkg}"; lower_pad_xaxis_title = "m_{jj} (GeV)"; // lower pad axis titles
  // }
  // xTitle = upper_pad_xaxis_title;
  
  // float upper_minY = 1.0e-1; float upper_maxY = 5.e7;  //y-axis range of upper pad
  // //float upper_minY = 1.0e-1; float upper_maxY = 5.e12;  //y-axis range of upper pad
  // float lower_minY = 0.5; float lower_maxY = 1.5;     //y-axis range of lower pad
  
  // // 0:leppt, 1:jetpt, 2:metpt, 3:lepeta, 4:jeteta, 5:lepphi, 6:jetphi, 7:metphi, 8:njet, 9:nbjet, 10:mjj
  // float upper_minX = 0.0; float upper_maxX = 500.0;
  // if(htype>=0 and htype<=2){
  //   upper_minX = 0.0; upper_maxX = 500.0;   //x-axis range
  // }else if(htype>=3 and htype<=7){
  //   upper_minX = -5.0; upper_maxX = 5.0;   //x-axis range
  // }else if(htype==8){
  //   upper_minX = 0.0; upper_maxX = 16.0;   //x-axis range
  // }else if(htype==9){
  //   upper_minX = 0.0; upper_maxX = 10.0;   //x-axis range
  // }else if(htype==10){
  //   upper_minX = 0.0; upper_maxX = 200.0;   //x-axis range
  // }
  
  // float integral_min = upper_minX; float integral_max = upper_maxX; // for integral calculation
  // //float integral_min = 4.0; float integral_max = upper_maxX; // for integral calculation
  // MinX = upper_minX;   MaxX = upper_maxX;
  
  // //float legend_pos[4] = {0.5, 0.65, 0.88, 0.86};
  // float legend_pos1[4] = {0.38, 0.70, 0.54, 0.86};
  // float legend_pos2[4] = {0.55, 0.70, 0.71, 0.86};
  // float legend_pos3[4] = {0.72, 0.70, 0.88, 0.86};
  // ///////////////////////////////////////////////////////////////////////////////////////////  

  // gStyle->SetOptStat(0);
  // //Ranges
  // hData->SetMaximum(upper_maxY);
  // hData->SetMinimum(upper_minY);
  // hData->GetXaxis()->SetRangeUser(upper_minX, upper_maxX);
  // hMC->GetXaxis()->SetRangeUser(upper_minX, upper_maxX);
  // //hData->GetXaxis()->SetRange(hData->FindBin(upper_minX), hData->FindBin(upper_maxX));
  // //hMC->GetXaxis()->SetRange(upper_minX, upper_maxX);
  // //axis Titles
  // hData->GetXaxis()->SetTitle(upper_pad_xaxis_title.c_str());
  // hData->GetYaxis()->SetTitle(upper_pad_yaxis_title.c_str());
  // //Now add style and color
  // SetStatMarkerStyle(hData, kBlack, kFullCircle, 1);
  // SetStatMarkerStyle(hMC, kBlue, kFullSquare, 0.1);  
  
  // float canvas_scale = 1;
  // int canvas_width = TMath::Nint(canvas_scale*900) ;
  // int canvas_height = TMath::Nint(canvas_scale*800) ;
  // // auto c1 = new TCanvas("c1", canvas_title, canvas_width, canvas_height);
  // // //auto rp = new TRatioPlot(hData, hMC, "divsym");
  // // auto rp = new TRatioPlot(hData, hMC, "divsym");
  // // //auto rp = new TRatioPlot(hs, hData, "divsym");
  // // rp->SetH1DrawOpt("e1");
  // // rp->SetH2DrawOpt("hist");
  // // c1->SetTicks(1, 1);
  // // //rp->GetLowerRefYaxis()->SetMaximum(1.4);
  // // rp->Draw();
  // // gPad->Modified(); gPad->Update(); // make sure it’s really (re)drawn
  // // TPad *p = rp->GetUpperPad();
  // // p->cd();
  // // // //hData->Draw("e1p");
  // // hs->Draw("same hist");
  // // if(year == 2016)
  // //   hcf_RegA_sig->Draw("same hist");
  // // hData->Draw("e1p same");

  // // TLegend *leg1 = p->BuildLegend();
  // // for(int i = 0 ; i < 10 ; i++)
  // //   leg1->DeleteEntry() ;// This is to delete default title of hData
  // // leg1->AddEntry(hData, Form("%s",hist_num_title) ,"lp");
  // // leg1->AddEntry(hMC, Form("%s",hist_den_title) ,"lp");
  // // leg1->AddEntry(hcf_RegA_ttbar, Form("#it{t}#bar{#it{t}}") ,"f");

  // // TLegend *leg2 = p->BuildLegend();
  // // for(int i = 0 ; i < 10 ; i++)
  // //   leg2->DeleteEntry() ;// This is to delete default title of hData  
  // // leg2->AddEntry(hcf_RegA_stop, Form("Single #it{t}") ,"f");
  // // leg2->AddEntry(hcf_RegA_wjets, Form("#it{W} + jets") ,"f");
  // // leg2->AddEntry(hcf_RegA_dyjets, Form("#it{Z}/#gamma + jets") ,"f");
  
  // // TLegend *leg3 = p->BuildLegend();
  // // for(int i = 0 ; i < 10 ; i++)
  // //   leg3->DeleteEntry() ;// This is to delete default title of hData  
  // // leg3->AddEntry(hcf_RegA_vbf, Form("VV") ,"f");
  // // leg3->AddEntry(hcf_RegA_QCD, Form("QCD") ,"f");
  // // if(year == 2016)
  // //   leg3->AddEntry(hcf_RegA_sig, Form("m_{H^{+}} = 120 GeV") ,"l");

  // // leg1->SetX1(legend_pos1[0]); leg1->SetY1(legend_pos1[1]); 
  // // leg1->SetX2(legend_pos1[2]); leg1->SetY2(legend_pos1[3]); 

  // // leg2->SetX1(legend_pos2[0]); leg2->SetY1(legend_pos2[1]); 
  // // leg2->SetX2(legend_pos2[2]); leg2->SetY2(legend_pos2[3]); 

  // // leg3->SetX1(legend_pos3[0]); leg3->SetY1(legend_pos3[1]); 
  // // leg3->SetX2(legend_pos3[2]); leg3->SetY2(legend_pos3[3]); 
  
  // // SetLegendStyle(leg1);
  // // SetLegendStyle(leg2);
  // // SetLegendStyle(leg3);

  // // leg1->Draw();
  // // leg2->Draw();
  // // leg3->Draw();

  // TPaveText *t1 = new TPaveText(0.60,0.91,0.90,0.98,"NDC");
  // t1->SetFillStyle(0);
  // t1->SetBorderSize(0);
  // t1->SetTextFont(42);
  // t1->SetTextSize(.05); 
  // t1->SetMargin(0.1);
  // t1->AddText(Form("%3.1f fb^{-1} (13 TeV)",luminosity[year%2016]));
  // // t1->Draw();
  
  // TPaveText *t2 = new TPaveText(0.08, 0.78, 0.36, 0.86,"NDC");
  // t2->SetFillStyle(0);
  // t2->SetBorderSize(0);
  // t2->SetTextFont(42);
  // t2->SetTextSize(.05); 
  // t2->SetMargin(0.1);
  // if(isBtag and isMu)
  //   t2->AddText("BTag: (#mu + jets)");
  // if(isBtag and !isMu)
  //   t2->AddText("BTag: (#it{e} + jets)");
  // if(!isBtag and isMu)
  //   t2->AddText("KinFit: (#mu + jets)");
  // if(!isBtag and !isMu)
  //   t2->AddText("KinFit: (#it{e} + jets)");
  // // t2->Draw();

  // // //rp->GetLowYaxis()->SetNdivisions(402);
  // // rp->GetLowYaxis()->SetNdivisions(406);
  // // rp->GetLowerRefYaxis()->SetTitle(lower_pad_yaxis_title.c_str());
  // // rp->GetLowerRefXaxis()->SetTitleOffset(1.2);
  // // //rp->GetLowerRefYaxis()->SetTitleSize(4.1);
  // // rp->GetUpperRefYaxis()->SetTitle(upper_pad_yaxis_title.c_str());
  // // rp->GetLowerRefYaxis()->SetRangeUser(lower_minY, lower_maxY);
  // // rp->GetUpperPad()->SetLogy();
  // // // rp->GetUpperPad()->SetTickX();
  // // // rp->GetUpperPad()->SetTickY();
  // // p->Modified(); p->Update();

  // // c1->Update();
  // // c1->SaveAs(outputpdf.c_str());
  // // c1->SaveAs("plot.pdf");


  // ///////////////////////////////////////////////////////////////////////////
  // hcf_RegD_QCD->SetLineColor(kRed);
  // hcf_RegC_QCD->SetLineColor(kBlue);
  // hcf_RegD_QCD->SetMarkerColor(kRed);
  // hcf_RegC_QCD->SetMarkerColor(kBlue);

  // hcf_RegD_QCD->Scale(1./hcf_RegD_QCD->Integral());
  // hcf_RegC_QCD->Scale(1./hcf_RegC_QCD->Integral());
  // hcf_RegD_QCD->SetTitle("");
  // hcf_RegC_QCD->SetTitle("");
  
  // TH1D *h1byh2 = 0x0;

  // TCanvas* c2 = 0x0;
  // CalcRatio(hcf_RegD_QCD, hcf_RegC_QCD, h1byh2);
  // PlotRatioCanvas(c2, hcf_RegD_QCD, hcf_RegC_QCD, h1byh2);
  // t1->Draw();
  // t2->Draw();
  // ///////////////////////////////////////////////////////////////////////////

  // ///////////////////////////////////////////////////////////////////////////
  // // hcf_RegA_QCD->SetLineColor(kRed);
  // // hcf_RegB_QCD->SetLineColor(kBlue);
  // // hcf_RegA_QCD->SetMarkerColor(kRed);
  // // hcf_RegB_QCD->SetMarkerColor(kBlue);

  // // // hcf_RegA_QCD->Scale(1./hcf_RegD_QCD->Integral());
  // // // hcf_RegB_QCD->Scale(1./hcf_RegC_QCD->Integral());
  // // hcf_RegA_QCD->SetTitle("");
  // // hcf_RegB_QCD->SetTitle("");
  
  // // TH1D *h1byh2 = 0x0;

  // // TCanvas* c2 = 0x0;
  // // CalcRatio(hcf_RegA_QCD, hcf_RegB_QCD, h1byh2);
  // // PlotRatioCanvas(c2, hcf_RegA_QCD, hcf_RegB_QCD, h1byh2);
  // // t1->Draw();
  // // t2->Draw();
  // ///////////////////////////////////////////////////////////////////////////
  
  // c2->SaveAs(outputpdf.c_str());
  

  // string lepname = (isMu)? "\\mu" : "e" ;
  // string color = (isMu)? "red" : "blue" ;
  // string levelname = "";
  // if(isBtag){
  //   levelname = "BTag";
  // }else{
  //   if(htype==14)
  //     levelname = "Exclusive loose";
  //   else if(htype==15)
  //     levelname = "Exclusive medium";
  //   else if(htype==16)
  //     levelname = "Exclusive tight";
  //   else
  //     levelname = "KF";
  // }

  // printf("\\begin{tabular}{c c c c c}\n");
  // printf("\\hline\n");
  // printf("\\multicolumn{5}{>{\\color{%s}\\columncolor[gray]{0.8}}c}{ %s : ($%s$ + jets) for %d } \\\\\\hline \n",color.c_str(),levelname.c_str(),lepname.c_str(),year);
  // printf("Process & Region-A & Region-B & Region-C & Region-D \\\\ \n");
  // printf("        & (Iso,High MET) & (non-iso,High MET) & (non-iso, Low MET) &  (Iso,Low MET) \\\\\\hline \n");
  // printf("MC QCD  & $%2.0lf\\pm%2.0lf$ & $%2.0lf\\pm%2.0lf$ & $%2.0lf\\pm%2.0lf$ & $%2.0lf\\pm%2.0lf$ \\\\ \\hline \n",
  //        hcf_RegA_qcd->Integral(), getStatUnc(hcf_RegA_qcd, 0.0), hcf_RegB_qcd->Integral(), getStatUnc(hcf_RegB_qcd, 0.0),
  //        hcf_RegC_qcd->Integral(), getStatUnc(hcf_RegC_qcd, 0.0), hcf_RegD_qcd->Integral(), getStatUnc(hcf_RegD_qcd, 0.0));
  // printf("$t\\bar{t}$ + jets   & $%2.0lf\\pm%2.0lf$ & $%2.0lf\\pm%2.0lf$ & $%2.0lf\\pm%2.0lf$ & $%2.0lf\\pm%2.0lf$ \\\\\n",
  //        hcf_RegA_ttbar->Integral(), getStatUnc(hcf_RegA_ttbar, 0.0), hcf_RegB_ttbar->Integral(), getStatUnc(hcf_RegB_ttbar, 0.0),
  //        hcf_RegC_ttbar->Integral(), getStatUnc(hcf_RegC_ttbar, 0.0), hcf_RegD_ttbar->Integral(), getStatUnc(hcf_RegD_ttbar, 0.0));
  // printf("Single $t$   & $%2.0lf\\pm%2.0lf$ & $%2.0lf\\pm%2.0lf$ & $%2.0lf\\pm%2.0lf$ & $%2.0lf\\pm%2.0lf$ \\\\\n",
  //        hcf_RegA_stop->Integral(), getStatUnc(hcf_RegA_stop, 0.0), hcf_RegB_stop->Integral(), getStatUnc(hcf_RegB_stop, 0.0),
  //        hcf_RegC_stop->Integral(), getStatUnc(hcf_RegC_stop, 0.0), hcf_RegD_stop->Integral(), getStatUnc(hcf_RegD_stop, 0.0));
  // printf("W + jets  & $%2.0lf\\pm%2.0lf$ & $%2.0lf\\pm%2.0lf$ & $%2.0lf\\pm%2.0lf$ & $%2.0lf\\pm%2.0lf$ \\\\\n",
  //        hcf_RegA_wjets->Integral(), getStatUnc(hcf_RegA_wjets, 0.0), hcf_RegB_wjets->Integral(), getStatUnc(hcf_RegB_wjets, 0.0),
  //        hcf_RegC_wjets->Integral(), getStatUnc(hcf_RegC_wjets, 0.0), hcf_RegD_wjets->Integral(), getStatUnc(hcf_RegD_wjets, 0.0));
  // printf("Z/$\\gamma$ + jets  & $%2.0lf\\pm%2.0lf$ & $%2.0lf\\pm%2.0lf$ & $%2.0lf\\pm%2.0lf$ & $%2.0lf\\pm%2.0lf$ \\\\\n",
  //        hcf_RegA_dyjets->Integral(), getStatUnc(hcf_RegA_dyjets, 0.0), hcf_RegB_dyjets->Integral(), getStatUnc(hcf_RegB_dyjets, 0.0),
  //        hcf_RegC_dyjets->Integral(), getStatUnc(hcf_RegC_dyjets, 0.0), hcf_RegD_dyjets->Integral(), getStatUnc(hcf_RegD_dyjets, 0.0));
  // printf("VV  & $%2.0lf\\pm%2.0lf$ & $%2.0lf\\pm%2.0lf$ & $%2.0lf\\pm%2.0lf$ & $%2.0lf\\pm%2.0lf$ \\\\ \\hline \n",
  //        hcf_RegA_vbf->Integral(), getStatUnc(hcf_RegA_vbf, 0.0), hcf_RegB_vbf->Integral(), getStatUnc(hcf_RegB_vbf, 0.0),
  //        hcf_RegC_vbf->Integral(), getStatUnc(hcf_RegC_vbf, 0.0), hcf_RegD_vbf->Integral(), getStatUnc(hcf_RegD_vbf, 0.0));
  // printf("Non QCD  & $%2.0lf\\pm%2.0lf$ & $%2.0lf\\pm%2.0lf$ & $%2.0lf\\pm%2.0lf$ & $%2.0lf\\pm%2.0lf$ \\\\ \\hline \n",
  //        hcf_RegA_bkg->Integral(), getStatUnc(hcf_RegA_bkg, 0.0), hcf_RegB_bkg->Integral(), getStatUnc(hcf_RegB_bkg, 0.0),
  //        hcf_RegC_bkg->Integral(), getStatUnc(hcf_RegC_bkg, 0.0), hcf_RegD_bkg->Integral(), getStatUnc(hcf_RegD_bkg, 0.0));
  // printf("Data  & $%2.0lf\\pm%2.0lf$ & $%2.0lf\\pm%2.0lf$ & $%2.0lf\\pm%2.0lf$ & $%2.0lf\\pm%2.0lf$ \\\\ \\hline\n",
  //        hcf_RegA_data->Integral(), getStatUnc(hcf_RegA_data, 0.0), hcf_RegB_data->Integral(), getStatUnc(hcf_RegB_data, 0.0),
  //        hcf_RegC_data->Integral(), getStatUnc(hcf_RegC_data, 0.0), hcf_RegD_data->Integral(), getStatUnc(hcf_RegD_data, 0.0));
  // printf("\\end{tabular}\n");
    
  return true;
}

int CalcRatio(TH1D*& hDataEff, TH1D*& hSimEff, TH1D*& hRatio)
{

  // hDataEff->Sumw2();
  // hSimEff->Sumw2();
  
  hRatio = (TH1D*)hDataEff->Clone(Form("hRatio_%d",icounter++));
  hRatio->SetTitle("");
  hRatio->Divide(hSimEff);

  
  return true;
}


int PlotRatioCanvas(TCanvas*& c1, TH1D*& hData, TH1D*& hSim,  TH1D*& hDByS)
{
  
  // Float_t MinX = -4.5;
  // Float_t MaxX = -2.0;

  // Float_t MinX = 6.0;
  // Float_t MaxX = 12.0;

  // Float_t MinX = hData->GetMinimum();
  // Float_t MaxX = hData->GetMaximum();  

  hData->SetMarkerStyle(kFullCircle);
  hData->SetMarkerColor(kRed);

  hSim->SetMarkerStyle(kFullSquare);
  hSim->SetMarkerColor(kBlue);

  hDByS->SetMarkerStyle(kFullTriangleUp);
  hDByS->SetMarkerColor(kMagenta);

  //gStyle->SetOptStat(1001111);
  gStyle->SetOptStat(0);
  
  TLegend *legend1=new TLegend(0.39162,0.6771911,0.642121,0.8745237);
  legend1->SetFillColor(0);
  legend1->SetTextFont(22);
  legend1->SetTextSize(0.047);
  legend1->SetBorderSize(0);
  legend1->AddEntry(hData,Form("%s",hData->GetName()),"lpe");
  legend1->AddEntry(hSim,Form("%s",hSim->GetName()),"lpe");
  legend1->AddEntry(hDByS,Form("%s",hDByS->GetName()),"lpe");
  //legend1->AddEntry(hDByS,Form("Ratio = %5.4f #pm %5.4f",hDByS->GetBinContent(1),hDByS->GetBinError(1)),"lpe");
  //legend1->AddEntry(hDByS,Form("Max Diff = %5.4f",hDByS->GetBinContent(1)),"lpe");
  //legend1->AddEntry(hDByS,Form("Max Diff = %5.4f",hDByS->GetBinContent(2)),"lpe");


  hSim->SetMinimum(0.0);
  //hSim->SetMaximum(2.0*hSim->GetBinContent(hSim->FindBin(80.)));
  
  c1 = new TCanvas(Form("c_%d",icounter), Form("c_%d",icounter),0,0,1000,800);
  c1->Range(0,0,1,1);
  c1->SetFillColor(0);
  c1->SetBorderMode(0);
  c1->SetBorderSize(2);
  c1->SetFrameBorderMode(0);
  icounter++;
   
  TPad *c1_1 = new TPad(Form("pad_%d",icounter), Form("pad_%d",icounter),0.01,0.01,0.99,0.33);
  c1_1->Draw();
  c1_1->cd();
  //c1_1->SetOptStat(kFALSE);
  c1_1->SetTopMargin(0.01);
  c1_1->SetBottomMargin(0.3);
  c1_1->SetRightMargin(0.1);
  c1_1->SetFillStyle(0);
  c1_1->SetFillColor(0);
  c1_1->SetTickx();
  c1_1->SetTicky();
  c1_1->SetGridy();
  icounter++;

  c1_1->SetTopMargin(0.03276794);

  hDByS->SetAxisRange(MinX,MaxX);
  hDByS->Draw("e1p");
  
  hDByS->SetMinimum(defaultRatioYmin);
  hDByS->SetMaximum(defaultRatioYmax);
  //hDByS->GetYaxis()->SetNdivisions(2);
  hDByS->GetYaxis()->SetNdivisions(5);
  //hDByS->SetTitle(";"+xTitle+";"+yTitle2);
  hDByS->GetXaxis()->SetTitleSize(0.12);
  hDByS->GetXaxis()->SetLabelSize(0.12);
  hDByS->GetXaxis()->SetLabelOffset(0.016);
  hDByS->GetYaxis()->SetLabelSize(0.11);
  hDByS->GetYaxis()->SetTitleSize(0.10);
  hDByS->GetYaxis()->SetTitleOffset(0.30);
  //hDByS->GetYaxis()->SetTitle(Form("Data/Sim"));
  //hDByS->GetYaxis()->SetTitle(Form("Red/Blue"));
  //hDByS->GetYaxis()->SetTitle(Form("CUETP8M2T4/CP5"));
  hDByS->GetYaxis()->SetTitle(denoYaxis.c_str());
  //hDByS->GetXaxis()->SetTitle(Form("p_{T} GeV/c"));
  hDByS->GetXaxis()->SetTitle(xTitle.c_str());
  //hDByS->GetXaxis()->SetTitle(Form("y"));
  hDByS->GetYaxis()->SetTickLength(0.01);
  
  c1->cd();

  TPad *c1_2 = new TPad(Form("pad_%d",icounter), Form("pad_%d",icounter),0.01,0.33,0.99,0.99);
  c1_2->Draw(); 
  c1_2->cd();
  c1_2->SetTopMargin(0.1);
  c1_2->SetBottomMargin(0.01);
  c1_2->SetRightMargin(0.1);
  c1_2->SetFillStyle(0);
  c1_2->SetFillColor(0);
  c1_2->SetTickx();
  c1_2->SetTicky();
  //c1_2->SetLogy();
  icounter++;
  
  c1_2->SetBottomMargin(0.04571135);

  hSim->SetMaximum(2*hSim->GetBinContent(hSim->GetMaximumBin()));
  hSim->SetMinimum(-0.05);
  
  hSim->SetAxisRange(MinX,MaxX);
  hSim->Draw("e1p");
  hData->Draw("e1p sames");
  //hSim->GetXaxis()->SetTitle("p_{T} GeV/c");
  //hSim->GetYaxis()->SetTitle(Form("Counts per %2.0f MeV/c^{2}",1000.0*hSim->GetBinWidth(3)));
  hSim->GetYaxis()->SetTitle("DD QCD (normalized to unity)");
  hSim->SetLabelSize(0.0);
  hSim->GetXaxis()->SetTitleSize(0.00);
  hSim->GetYaxis()->SetLabelSize(0.05);
  hSim->GetYaxis()->SetTitleSize(0.05);
  hSim->GetYaxis()->SetTitleOffset(1.0);
  hSim->GetYaxis()->SetTickLength(0.01);
  
  legend1->Draw();
  
  c1->Update();

  
  return true;

}


void makeHistoPositive(TH1D *hist, bool setErrorZero = false){
  for(int ibin=1; ibin<hist->GetNbinsX(); ibin++){
    double binCont = hist->GetBinContent(ibin);
    if(binCont<0){
      hist->SetBinContent(ibin, 0);
      if(setErrorZero) hist->SetBinError(ibin, 0);
    }
  }
}

double getStatUnc(TH1D* hCentral, double sError = 0.0){
  double  norm = hCentral->IntegralAndError(1, hCentral->GetNbinsX(), sError);
  //double statUnc = (norm > 0) ? 1 + (fabs(sError)/norm) : 1.00;
  double statUnc = sError;
  return statUnc;
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


// void makeDataset( TString fname, TString tname, TString outfname ) {

//   RooWorkspace *w = new RooWorkspace("w","w");

//   w->factory( "Dst_M[1950.,2070.]" );
//   w->factory( "D0_M[1810.,1920.]" );
//   w->factory( "D0_LTIME_ps[0.00,5.]" );

//   RooArgSet *observables = new RooArgSet();
//   observables->add( *w->var("Dst_M") );
//   observables->add( *w->var("D0_M") );
//   observables->add( *w->var("D0_LTIME_ps") );
//   w->defineSet("observables", *observables);

//   w->var("Dst_M")->setBins(240);
//   w->var("D0_M")->setBins(220);
//   w->var("D0_LTIME_ps")->setBins(200);

//   double Dst_M = -999.;
//   double D0_M = -999.;
//   double D0_LTIME_ps = -999.;

//   TFile *tf = TFile::Open(fname);
//   TTree *tree = (TTree*)tf->Get(tname);

//   tree->SetBranchAddress( "Dst_M", &Dst_M );
//   tree->SetBranchAddress( "D0_M" , &D0_M );
//   tree->SetBranchAddress( "D0_LTIME_ps", &D0_LTIME_ps );

//   RooDataSet *data = new RooDataSet("Data","Data",*observables);
//   RooDataHist *dataH = new RooDataHist("DataHist","Data",*observables);

//   for ( int ev=0; ev<tree->GetEntries(); ev++) {

//     tree->GetEntry(ev);

//     if ( ev%10000 == 0 ) cout << ev << " / " << tree->GetEntries() << endl;

//     if ( Dst_M < w->var("Dst_M")->getMin() || Dst_M > w->var("Dst_M")->getMax() ) continue;
//     if ( D0_M < w->var("D0_M")->getMin() || D0_M > w->var("D0_M")->getMax() ) continue;
//     if ( D0_LTIME_ps < w->var("D0_LTIME_ps")->getMin() || D0_LTIME_ps > w->var("D0_LTIME_ps")->getMax() ) continue;

//     w->var("Dst_M")->setVal(Dst_M);
//     w->var("D0_M")->setVal(D0_M);
//     w->var("D0_LTIME_ps")->setVal(D0_LTIME_ps);

//     data->add( *observables );
//     dataH->add( *observables );

//   }
//   tf->Close();

//   w->import(*data);
//   w->import(*dataH);

//   w->writeToFile(outfname);

// }

void ReadTree(string signal, int year, vector<pair<int,double>>& dataArray)
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
  
  string inpath_tree = Form("/run/media/indra/DHEP_Storage_3/Data/NanoAOD/KinFit/CBA_gdjsoncorr/%d",year);
  //string inpath_tree = Form("/home/idas/t3store3/root_files/KinTree/CBA_gdjsoncorr/%d",year);
  string treelist = Form("/tmp/fl_tree_list_%d.txt",year);
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

  tr->SetCacheSize(100*1024*1024);
  tr->SetBranchStatus("*",0);

  tr->SetBranchStatus("chi2"		, 1);
  tr->SetBranchStatus("ndf"		, 1);
  tr->SetBranchStatus("jetBlepPt"	, 1);
  tr->SetBranchStatus("jetBlepEta"	, 1);
  tr->SetBranchStatus("jetBhadPt"	, 1);
  tr->SetBranchStatus("jetBhadEta"	, 1);
  tr->SetBranchStatus("jetChadPt"	, 1);
  tr->SetBranchStatus("jetChadEta"	, 1);
  tr->SetBranchStatus("jetChadPhi"	, 1);
  tr->SetBranchStatus("jetChadEnergy"	, 1);
  tr->SetBranchStatus("jetShadPt"	, 1);
  tr->SetBranchStatus("jetShadEta"	, 1);
  tr->SetBranchStatus("jetShadPhi"	, 1);
  tr->SetBranchStatus("jetShadEnergy"	, 1);
  tr->SetBranchStatus("metPx"		, 1);
  tr->SetBranchStatus("metPy"		, 1);
  tr->SetBranchStatus("metPz"		, 1);
  
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

  tr->SetBranchStatus("singleMu"	, 1);
  tr->SetBranchStatus("singleEle"	, 1);
  tr->SetBranchStatus("muonIsoCut"	, 1);
  tr->SetBranchStatus("isLowMET"	, 1);

  // tr->SetBranchAddress("sampleWeight"	, &sampleWeight);
  // tr->SetBranchAddress("prefireWeight"	, &prefireWeight);
  // tr->SetBranchAddress("PUWeight"	, &PUWeight);
  // tr->SetBranchAddress("muEffWeight"	, &muEffWeight);
  // tr->SetBranchAddress("puJetIDWeight"	, &puJetIDWeight);
  // tr->SetBranchAddress("bTagWeight"	, &bTagWeight);
  // tr->SetBranchAddress("cTagLWeight"	, &cTagLWeight);
  // tr->SetBranchAddress("cTagMWeight"	, &cTagMWeight);
  // tr->SetBranchAddress("cTagTWeight"	, &cTagTWeight);
  tr->SetBranchAddress("singleMu"	, &singleMu);
  tr->SetBranchAddress("singleEle"	, &singleEle);
  tr->SetBranchAddress("muonIsoCut"	, &muonIsoCut);
  tr->SetBranchAddress("isLowMET"	, &isLowMET);
  // tr->SetBranchAddress("isCTagged"	, &isCTagged);
  // tr->SetBranchAddress("isKFValid"	, &isKFValid);
  // tr->SetBranchAddress("hasKFMu"	, &hasKFMu);
  // tr->SetBranchAddress("hasKFEle"	, &hasKFEle);
  // tr->SetBranchAddress("count_cJetsIncL"	, &count_cJetsIncL);
  // tr->SetBranchAddress("count_cJetsIncM"	, &count_cJetsIncM);
  // tr->SetBranchAddress("count_cJetsIncT"	, &count_cJetsIncT);

  TLorentzVector chad, shad, met;
  
  int reg;
  cout << "Sample : " << signal << ", Total Entries : " << tr->GetEntries() << endl;
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
    
    if(singleMu and !singleEle){
      if(!isLowMET)
	reg = (muonIsoCut) ? 0 : 1;
      else
	reg = (muonIsoCut) ? 2 : 3;
      dataArray.push_back( make_pair(reg, mjjKF) );
    }
  }//event loop
  
  delete tr;
}
