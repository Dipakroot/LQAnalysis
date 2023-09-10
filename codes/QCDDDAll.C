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

#include <iostream>

using namespace std;

int icounter = 0;
Float_t MinX = 4.0;
Float_t MaxX = -4.0;

float defaultRatioYmin = -4.0;
float defaultRatioYmax = 4.0;

string denoYaxis = "RegD/RegC";
string xTitle = "";


int QCDDDAll(int year = 2016, bool isBtag = 0, bool isMu = 1, int htype = 10)
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

  int CalcRatio(TH1D*& hDataEff, TH1D*& hSimEff, TH1D*& hRatio);
  int PlotRatioCanvas(TCanvas*& c1, TH1D*& hData, TH1D*& hSim,  TH1D*& hDByS);
  
  void makeHistoPositive(TH1D *, bool);
  double getStatUnc(TH1D *, double);

  ///////////////////////////////////////////////////////////////////////////////////////////////  
  //int year = 2016;
  
  float luminosity[3] = {36.3, 41.5, 59.8};

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

  if(histname.find("_ct_")!=string::npos){
    string histname1 = (isBtag) ? "_lb" : "_kb" ;   
    histname1 += (isMu) ? "_mjj_mu" : "_mjj_ele" ;  
    histname_RegC = histname1 + "_noniso_lmet";
    histname_RegD = histname1 + "_lmet";
    
    // cout << "histname : " << histname <<  ", Reg A " << histname_RegA << ", Reg B "<< histname_RegB << endl;
    // cout << "histname1 : " << histname1 <<  ", Reg C " << histname_RegC << ", Reg D "<< histname_RegD << endl;
  }
  
  string outputpdf = Form("tt/figs/Week_Work_Report/2023-01-26/DD/%d/hist%s.pdf",year,histname.c_str());
  //string outputpdf = Form("tt/figs/Week_Work_Report/2022-11-24/DD/%d/hist%s.pdf",year,histname.c_str());
  //string outputpdf = Form("ffigs/Week_Work_Report/2022-09-01/%d/DD/hist%s.pdf",year,histname.c_str());
  //const char* dir = "grid_v32_Syst/CBA_Skim_Syst_jet_tightID";
  //const char* dir = "grid_v40_Syst/CBA_ctagv2-CombHist";
  //const char* dir = "grid_v33_Syst/CBA_Skim_Syst_EqPAGAug02";
  //const char* dir = "grid_v40_Syst/CBA_gdjsoncorr-CombHist";
  //const char* dir = "grid_v40_Syst/CBA_gdjsoncorr-CombHist/post";
  //const char* dir = "grid_v40_Syst/CBA_elemva80-CombHist";
  //const char* dir = "grid_v40_Syst/CBA_elereliso-CombHist";
  const char* dir = "grid_v40_Syst/CBA_elereliso30-CombHist";
  
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
  }

  //////////////////////////////// Get the QCD for regions ////////////////////////////////////////////////
  TH1D *hcf_RegD_QCD = (TH1D *)hcf_RegD_data->Clone("RegD_QCD");
  hcf_RegD_QCD->Add(hcf_RegD_bkg, -1);
  //hist->Scale(1./hist->Integral()); //Apply the following for normalized shape
  makeHistoPositive(hcf_RegD_QCD, false) ;
  
  TH1D *hcf_RegC_QCD = (TH1D *)hcf_RegC_data->Clone("RegC_QCD");
  hcf_RegC_QCD->Add(hcf_RegC_bkg, -1);
  //hist->Scale(1./hist->Integral()); //Apply the following for normalized shape
  makeHistoPositive(hcf_RegC_QCD, false) ;

  TH1D *hcf_RegB_QCD = (TH1D *)hcf_RegB_data->Clone("RegB_QCD");
  hcf_RegB_QCD->Add(hcf_RegB_bkg, -1);
  //hist->Scale(1./hist->Integral()); //Apply the following for normalized shape
  makeHistoPositive(hcf_RegB_QCD, false) ;
  
  TH1D *hcf_RegA_QCD = (TH1D *)hcf_RegA_data->Clone("RegA_QCD");
  hcf_RegA_QCD->Add(hcf_RegA_bkg, -1);
  //hist->Scale(1./hist->Integral()); //Apply the following for normalized shape
  makeHistoPositive(hcf_RegA_QCD, false) ;
  /////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  //////////////////////////////// Calculate the QCD SF ///////////////////////////////////////////////////
  // double intDiffC   = hcf_RegC_QCD->Integral();
  // double errDiffC   = getStatUnc(hcf_RegC_QCD, 0.0);
  // double intDiffD   = hcf_RegD_QCD->Integral();
  // double errDiffD   = getStatUnc(hcf_RegD_QCD, 0.0);
  
  double intDiffC   = TMath::Abs(hcf_RegC_QCD->Integral());
  double errDiffC   = TMath::Abs(getStatUnc(hcf_RegC_QCD, 0.0));
  double intDiffD   = TMath::Abs(hcf_RegD_QCD->Integral());
  double errDiffD   = TMath::Abs(getStatUnc(hcf_RegD_QCD, 0.0));
  
  //Ratio of (Data-MC) from RegionD and RegionC
  // double SF = intDiffD/intDiffC;
  // double tmpD = errDiffD/intDiffD;
  // double tmpC = errDiffC/intDiffC;
  double SF = intDiffD/intDiffC;
  if(TMath::AreEqualAbs(intDiffD,0.0,1.e-5) or TMath::AreEqualAbs(intDiffC,0.0,1.e-5)){ //in case hit zero use absolute instead of (Data-MC) this only influencens the control plot of MET pt
    double num = TMath::Max(TMath::Abs(hcf_RegD_data->Integral()-hcf_RegD_bkg->Integral()),1.0);
    double deno = TMath::Max(TMath::Abs(hcf_RegC_data->Integral()-hcf_RegC_bkg->Integral()),1.0);
    SF = num/deno;
  }
  double tmpD = errDiffD/intDiffD;
  if(TMath::AreEqualAbs(intDiffD,0.0,1.e-5)) //in case hit zero use Data only instead of (Data-MC) this only influcens the control plot of MET pt
    tmpD = getStatUnc(hcf_RegD_data, 0.0)/hcf_RegD_data->Integral();
  
  double tmpC = errDiffC/intDiffC;
  if(TMath::AreEqualAbs(intDiffC,0.0,1.e-5)) //in case hit zero use Data only instead of (Data-MC) this only influcens the control plot of MET pt
    tmpC = getStatUnc(hcf_RegC_data, 0.0)/hcf_RegC_data->Integral();
  double SF_error = SF*sqrt(tmpD*tmpD + tmpC*tmpC);
  printf("SF(%s,%d) : %5.4lf \\pm %5.4lf\n",histname.c_str(),year,SF,SF_error);
  /////////////////////////////////////////////////////////////////////////////////////////////////////////

  /////////////////////////////// Modify the Region B result //////////////////////////////////////////////
  double sError = 0.0;
  double  norm = hcf_RegB_QCD->IntegralAndError(1, hcf_RegB_QCD->GetNbinsX(), sError);
  cout<<"intB = "<<norm<<", intB_err = "<<sError<<endl;
  double tot_bin_cont = 0.0;
  double tot_bin_err = 0.0;
  for(int ibin=1; ibin<hcf_RegB_QCD->GetNbinsX(); ibin++){
      double bin_cont = hcf_RegB_QCD->GetBinContent(ibin);
      double bin_err = hcf_RegB_QCD->GetBinError(ibin);
      double new_bin_cont = SF*bin_cont;
      double new_bin_err = sqrt(pow(bin_cont*SF_error, 2) + pow(bin_err*SF, 2));
      tot_bin_cont = tot_bin_cont + new_bin_cont;
      tot_bin_err = tot_bin_err + new_bin_err*new_bin_err;
      hcf_RegA_QCD->SetBinContent(ibin, new_bin_cont);
      hcf_RegA_QCD->SetBinError(ibin, new_bin_err);
  }
  hcf_RegA_bkg->Add(hcf_RegA_QCD);

  // hcf_RegA_bkg->Add(hcf_RegA_QCD);
  // if(htype>=10 and htype<=17){
  //   int rebin = 50;
  //   hcf_RegA_QCD->Rebin(rebin);
  // }

  cout<<"tot_bin_cont= "<<tot_bin_cont<<", tot_bin_err = "<<sqrt(tot_bin_err)<<endl;
  /////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  hcf_RegA_data->SetMarkerStyle(kFullCircle);
  hcf_RegA_data->SetMarkerColor(kBlack);
  hcf_RegA_data->SetMarkerSize(1.2);
  
  if(year == 2016){
    hcf_RegA_sig->SetLineStyle(kDashed);
    hcf_RegA_sig->SetLineColor(kRed);
    hcf_RegA_sig->SetLineWidth(2);
  }

  hcf_RegA_ttbar->SetFillColor(kCyan+1);
  
  hcf_RegA_stop->SetFillColor(kViolet);

  hcf_RegA_wjets->SetFillColor(kYellow+1);

  hcf_RegA_dyjets->SetFillColor(kOrange+1);
  
  hcf_RegA_vbf->SetFillColor(kGreen+2);

  hcf_RegA_QCD->SetFillColor(kBlue);
  
  THStack *hs = new THStack("hs","");
  hs->Add(hcf_RegA_vbf);
  hs->Add(hcf_RegA_dyjets);
  hs->Add(hcf_RegA_wjets);
  hs->Add(hcf_RegA_QCD);
  hs->Add(hcf_RegA_stop);
  hs->Add(hcf_RegA_ttbar);


  TH1D *hData = (TH1D*)hcf_RegA_data->Clone("hData"); 
  hData->SetTitle("");
  TH1D *hMC = (TH1D*)hcf_RegA_bkg->Clone("hMC"); 
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
  }else if(htype>=10 and htype<=17){
    upper_pad_yaxis_title = "Events / bin"; upper_pad_xaxis_title = "m_{jj} (GeV)"; // upper pad axis titles
    lower_pad_yaxis_title = "#frac{Data}{Bkg}"; lower_pad_xaxis_title = "m_{jj} (GeV)"; // lower pad axis titles
  }
  xTitle = upper_pad_xaxis_title;
  
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
  MinX = upper_minX;   MaxX = upper_maxX;
  
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
  // auto c1 = new TCanvas("c1", canvas_title, canvas_width, canvas_height);
  // //auto rp = new TRatioPlot(hData, hMC, "divsym");
  // auto rp = new TRatioPlot(hData, hMC, "divsym");
  // //auto rp = new TRatioPlot(hs, hData, "divsym");
  // rp->SetH1DrawOpt("e1");
  // rp->SetH2DrawOpt("hist");
  // c1->SetTicks(1, 1);
  // //rp->GetLowerRefYaxis()->SetMaximum(1.4);
  // rp->Draw();
  // gPad->Modified(); gPad->Update(); // make sure it’s really (re)drawn
  // TPad *p = rp->GetUpperPad();
  // p->cd();
  // // //hData->Draw("e1p");
  // hs->Draw("same hist");
  // if(year == 2016)
  //   hcf_RegA_sig->Draw("same hist");
  // hData->Draw("e1p same");

  // TLegend *leg1 = p->BuildLegend();
  // for(int i = 0 ; i < 10 ; i++)
  //   leg1->DeleteEntry() ;// This is to delete default title of hData
  // leg1->AddEntry(hData, Form("%s",hist_num_title) ,"lp");
  // leg1->AddEntry(hMC, Form("%s",hist_den_title) ,"lp");
  // leg1->AddEntry(hcf_RegA_ttbar, Form("#it{t}#bar{#it{t}}") ,"f");

  // TLegend *leg2 = p->BuildLegend();
  // for(int i = 0 ; i < 10 ; i++)
  //   leg2->DeleteEntry() ;// This is to delete default title of hData  
  // leg2->AddEntry(hcf_RegA_stop, Form("Single #it{t}") ,"f");
  // leg2->AddEntry(hcf_RegA_wjets, Form("#it{W} + jets") ,"f");
  // leg2->AddEntry(hcf_RegA_dyjets, Form("#it{Z}/#gamma + jets") ,"f");
  
  // TLegend *leg3 = p->BuildLegend();
  // for(int i = 0 ; i < 10 ; i++)
  //   leg3->DeleteEntry() ;// This is to delete default title of hData  
  // leg3->AddEntry(hcf_RegA_vbf, Form("VV") ,"f");
  // leg3->AddEntry(hcf_RegA_QCD, Form("QCD") ,"f");
  // if(year == 2016)
  //   leg3->AddEntry(hcf_RegA_sig, Form("m_{H^{+}} = 120 GeV") ,"l");

  // leg1->SetX1(legend_pos1[0]); leg1->SetY1(legend_pos1[1]); 
  // leg1->SetX2(legend_pos1[2]); leg1->SetY2(legend_pos1[3]); 

  // leg2->SetX1(legend_pos2[0]); leg2->SetY1(legend_pos2[1]); 
  // leg2->SetX2(legend_pos2[2]); leg2->SetY2(legend_pos2[3]); 

  // leg3->SetX1(legend_pos3[0]); leg3->SetY1(legend_pos3[1]); 
  // leg3->SetX2(legend_pos3[2]); leg3->SetY2(legend_pos3[3]); 
  
  // SetLegendStyle(leg1);
  // SetLegendStyle(leg2);
  // SetLegendStyle(leg3);

  // leg1->Draw();
  // leg2->Draw();
  // leg3->Draw();

  TPaveText *t1 = new TPaveText(0.60,0.91,0.90,0.98,"NDC");
  t1->SetFillStyle(0);
  t1->SetBorderSize(0);
  t1->SetTextFont(42);
  t1->SetTextSize(.05); 
  t1->SetMargin(0.1);
  t1->AddText(Form("%3.1f fb^{-1} (13 TeV)",luminosity[year%2016]));
  // t1->Draw();
  
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
  // t2->Draw();

  // //rp->GetLowYaxis()->SetNdivisions(402);
  // rp->GetLowYaxis()->SetNdivisions(406);
  // rp->GetLowerRefYaxis()->SetTitle(lower_pad_yaxis_title.c_str());
  // rp->GetLowerRefXaxis()->SetTitleOffset(1.2);
  // //rp->GetLowerRefYaxis()->SetTitleSize(4.1);
  // rp->GetUpperRefYaxis()->SetTitle(upper_pad_yaxis_title.c_str());
  // rp->GetLowerRefYaxis()->SetRangeUser(lower_minY, lower_maxY);
  // rp->GetUpperPad()->SetLogy();
  // // rp->GetUpperPad()->SetTickX();
  // // rp->GetUpperPad()->SetTickY();
  // p->Modified(); p->Update();

  // c1->Update();
  // c1->SaveAs(outputpdf.c_str());
  // c1->SaveAs("plot.pdf");


  ///////////////////////////////////////////////////////////////////////////
  hcf_RegD_QCD->SetLineColor(kRed);
  hcf_RegC_QCD->SetLineColor(kBlue);
  hcf_RegD_QCD->SetMarkerColor(kRed);
  hcf_RegC_QCD->SetMarkerColor(kBlue);

  // hcf_RegD_QCD->Scale(1./hcf_RegD_QCD->Integral());
  // hcf_RegC_QCD->Scale(1./hcf_RegC_QCD->Integral());
  hcf_RegD_QCD->SetTitle("");
  hcf_RegC_QCD->SetTitle("");
  
  TH1D *h1byh2 = 0x0;
  
  TCanvas* c2 = 0x0;
  CalcRatio(hcf_RegD_QCD, hcf_RegC_QCD, h1byh2);
  PlotRatioCanvas(c2, hcf_RegD_QCD, hcf_RegC_QCD, h1byh2);
  t1->Draw();
  t2->Draw();
  ///////////////////////////////////////////////////////////////////////////

  ///////////////////////////////////////////////////////////////////////////
  // hcf_RegA_QCD->SetLineColor(kRed);
  // hcf_RegB_QCD->SetLineColor(kBlue);
  // hcf_RegA_QCD->SetMarkerColor(kRed);
  // hcf_RegB_QCD->SetMarkerColor(kBlue);

  // // hcf_RegA_QCD->Scale(1./hcf_RegD_QCD->Integral());
  // // hcf_RegB_QCD->Scale(1./hcf_RegC_QCD->Integral());
  // hcf_RegA_QCD->SetTitle("");
  // hcf_RegB_QCD->SetTitle("");
  
  // TH1D *h1byh2 = 0x0;

  // TCanvas* c2 = 0x0;
  // CalcRatio(hcf_RegA_QCD, hcf_RegB_QCD, h1byh2);
  // PlotRatioCanvas(c2, hcf_RegA_QCD, hcf_RegB_QCD, h1byh2);
  // t1->Draw();
  // t2->Draw();
  ///////////////////////////////////////////////////////////////////////////
  
  c2->SaveAs(outputpdf.c_str());
  

  string lepname = (isMu)? "\\mu" : "e" ;
  string color = (isMu)? "red" : "blue" ;
  string levelname = "";
  if(isBtag){
    levelname = "BTag";
  }else{
    if(htype==14)
      levelname = "Exclusive loose";
    else if(htype==15)
      levelname = "Exclusive medium";
    else if(htype==16)
      levelname = "Exclusive tight";
    else
      levelname = "KF";
  }

  printf("\\begin{tabular}{c c c c c}\n");
  printf("\\hline\n");
  printf("\\multicolumn{5}{>{\\color{%s}\\columncolor[gray]{0.8}}c}{ %s : ($%s$ + jets) for %d } \\\\\\hline \n",color.c_str(),levelname.c_str(),lepname.c_str(),year);
  printf("Process & Region-A & Region-B & Region-C & Region-D \\\\ \n");
  printf("        & (Iso,High MET) & (non-iso,High MET) & (non-iso, Low MET) &  (Iso,Low MET) \\\\\\hline \n");
  printf("MC QCD  & $%2.0lf\\pm%2.0lf$ & $%2.0lf\\pm%2.0lf$ & $%2.0lf\\pm%2.0lf$ & $%2.0lf\\pm%2.0lf$ \\\\ \\hline \n",
         hcf_RegA_qcd->Integral(), getStatUnc(hcf_RegA_qcd, 0.0), hcf_RegB_qcd->Integral(), getStatUnc(hcf_RegB_qcd, 0.0),
         hcf_RegC_qcd->Integral(), getStatUnc(hcf_RegC_qcd, 0.0), hcf_RegD_qcd->Integral(), getStatUnc(hcf_RegD_qcd, 0.0));
  printf("$t\\bar{t}$ + jets   & $%2.0lf\\pm%2.0lf$ & $%2.0lf\\pm%2.0lf$ & $%2.0lf\\pm%2.0lf$ & $%2.0lf\\pm%2.0lf$ \\\\\n",
         hcf_RegA_ttbar->Integral(), getStatUnc(hcf_RegA_ttbar, 0.0), hcf_RegB_ttbar->Integral(), getStatUnc(hcf_RegB_ttbar, 0.0),
         hcf_RegC_ttbar->Integral(), getStatUnc(hcf_RegC_ttbar, 0.0), hcf_RegD_ttbar->Integral(), getStatUnc(hcf_RegD_ttbar, 0.0));
  printf("Single $t$   & $%2.0lf\\pm%2.0lf$ & $%2.0lf\\pm%2.0lf$ & $%2.0lf\\pm%2.0lf$ & $%2.0lf\\pm%2.0lf$ \\\\\n",
         hcf_RegA_stop->Integral(), getStatUnc(hcf_RegA_stop, 0.0), hcf_RegB_stop->Integral(), getStatUnc(hcf_RegB_stop, 0.0),
         hcf_RegC_stop->Integral(), getStatUnc(hcf_RegC_stop, 0.0), hcf_RegD_stop->Integral(), getStatUnc(hcf_RegD_stop, 0.0));
  printf("W + jets  & $%2.0lf\\pm%2.0lf$ & $%2.0lf\\pm%2.0lf$ & $%2.0lf\\pm%2.0lf$ & $%2.0lf\\pm%2.0lf$ \\\\\n",
         hcf_RegA_wjets->Integral(), getStatUnc(hcf_RegA_wjets, 0.0), hcf_RegB_wjets->Integral(), getStatUnc(hcf_RegB_wjets, 0.0),
         hcf_RegC_wjets->Integral(), getStatUnc(hcf_RegC_wjets, 0.0), hcf_RegD_wjets->Integral(), getStatUnc(hcf_RegD_wjets, 0.0));
  printf("Z/$\\gamma$ + jets  & $%2.0lf\\pm%2.0lf$ & $%2.0lf\\pm%2.0lf$ & $%2.0lf\\pm%2.0lf$ & $%2.0lf\\pm%2.0lf$ \\\\\n",
         hcf_RegA_dyjets->Integral(), getStatUnc(hcf_RegA_dyjets, 0.0), hcf_RegB_dyjets->Integral(), getStatUnc(hcf_RegB_dyjets, 0.0),
         hcf_RegC_dyjets->Integral(), getStatUnc(hcf_RegC_dyjets, 0.0), hcf_RegD_dyjets->Integral(), getStatUnc(hcf_RegD_dyjets, 0.0));
  printf("VV  & $%2.0lf\\pm%2.0lf$ & $%2.0lf\\pm%2.0lf$ & $%2.0lf\\pm%2.0lf$ & $%2.0lf\\pm%2.0lf$ \\\\ \\hline \n",
         hcf_RegA_vbf->Integral(), getStatUnc(hcf_RegA_vbf, 0.0), hcf_RegB_vbf->Integral(), getStatUnc(hcf_RegB_vbf, 0.0),
         hcf_RegC_vbf->Integral(), getStatUnc(hcf_RegC_vbf, 0.0), hcf_RegD_vbf->Integral(), getStatUnc(hcf_RegD_vbf, 0.0));
  printf("Non QCD  & $%2.0lf\\pm%2.0lf$ & $%2.0lf\\pm%2.0lf$ & $%2.0lf\\pm%2.0lf$ & $%2.0lf\\pm%2.0lf$ \\\\ \\hline \n",
         hcf_RegA_bkg->Integral(), getStatUnc(hcf_RegA_bkg, 0.0), hcf_RegB_bkg->Integral(), getStatUnc(hcf_RegB_bkg, 0.0),
         hcf_RegC_bkg->Integral(), getStatUnc(hcf_RegC_bkg, 0.0), hcf_RegD_bkg->Integral(), getStatUnc(hcf_RegD_bkg, 0.0));
  printf("Data  & $%2.0lf\\pm%2.0lf$ & $%2.0lf\\pm%2.0lf$ & $%2.0lf\\pm%2.0lf$ & $%2.0lf\\pm%2.0lf$ \\\\ \\hline\n",
         hcf_RegA_data->Integral(), getStatUnc(hcf_RegA_data, 0.0), hcf_RegB_data->Integral(), getStatUnc(hcf_RegB_data, 0.0),
         hcf_RegC_data->Integral(), getStatUnc(hcf_RegC_data, 0.0), hcf_RegD_data->Integral(), getStatUnc(hcf_RegD_data, 0.0));
  printf("\\end{tabular}\n");
    
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
  hDByS->SetMarkerColor(kGreen+1);
  hDByS->SetLineColor(kGreen+1);

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

  hSim->SetMaximum(4*hSim->GetBinContent(hSim->GetMaximumBin()));
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

  //hist->Scale(1./hist->Integral());
  
  for(int ibin=1; ibin<hist->GetNbinsX(); ibin++){
    double binCont = hist->GetBinContent(ibin);
    //cout<<"Name : "<< hist->GetName() <<", center : " << hist->GetBinCenter(ibin) << ", bincontent : " << binCont << endl ;
    if(binCont<0.0){
      hist->SetBinContent(ibin, 1.e-5);
      //hist->SetBinContent(ibin, 0.0);
      //hist->SetBinError(ibin, 0.0);
      if(setErrorZero) hist->SetBinError(ibin, 1.e-5);
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
