/**********************************************************************
 Created on : 19/11/2022
 Purpose    : Draw the ratio plots with systematics
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
#include <TROOT.h>
#include <TGraphAsymmErrors.h>

#include <TRatioPlot.h>

#include <iostream>

using namespace std;

double lumi_unc[3] = {0.012, 0.023, 0.025} ;

// //2016 mu
double qcd_frac = 0.0779 ; //One needs to check the QCD contribution from systematics
// //2016 ele
//double qcd_frac = 0.2486 ; //One needs to check the QCD contribution from systematics
int rebin = 50;

int PlotRatioSystematicsV2UL(int year = 2016, bool isBtag = 1, bool isMu = 1, int htype = 10){

  // Setters
  int SetGlobalStyle(void);
  int SetStatMarkerStyle(TGraphErrors *&, Color_t, Style_t, Size_t);
  int SetStatMarkerStyle(TH1F *&, Color_t, Style_t, Size_t);
  int SetStatMarkerStyle(TH1D *&, Color_t, Style_t, Size_t);
  int SetSysMarkerStyle(TGraphErrors *&, Color_t, Style_t);
  int SetCanvasStyle(TCanvas *&);
  int SetLegendStyle(TLegend *&, string histname, bool isBlinded);
  int PrintHSeparator(void);

  TPad *PlotRatio(THStack *hs, TH1D *hsig, TH1D *h1, TH1D *h2, TGraphAsymmErrors *syst, TGraphAsymmErrors *systRatio, const char *cname, bool isLog);
  TPad* Plot(THStack *hs, TH1D *hsig, TH1D *h1, TGraphAsymmErrors *syst, const char *cname, bool isLog);

  TH1D *GetUpDownHistDD(vector<TFile *>, const char *, const char *, string);
  TH1D *GetUpDownHistMC(vector<TFile *>, const char *, const char *, string, bool);  
  TGraphAsymmErrors *SystGraph(int year, string histname, TH1D *hCentral,  TH1D *hQCD, vector<TH1D *> vSystNom, vector<TH1D *> vSystUp, vector<TH1D *> vSystDown, bool isFullGraph = false, bool isRatioGraph = false);
  
  // ///////////////////////////////////////////////////////////////////////////////////////////  
  float luminosity[3] = {36.3, 41.5, 59.8};

  // bool isMu = 1; // 1 muon, 0 ele
  // bool isBtag = 1 ; // 1 btag, 0 kinfit
  // int htype = 0 ; // 0:leppt, 1:jetpt, 2:metpt, 3:lepeta, 4:jeteta, 5:lepphi, 6:jetphi, 7:metphi, 8:njet, 9:nbjet, 10:mjj
    
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
    histname = (isMu) ? "_ct_Exc0_mjj_mu" : "_ct_Exc0_mjj_ele" ;  
  else if (htype==18)
    histname += (isMu) ? "_bjhadBdisc_mu" : "_bjhadBdisc_ele" ;  
  else if (htype==19)
    histname += (isMu) ? "_bjlepBdisc_mu" : "_bjlepBdisc_ele" ;  
  else if (htype==20)
    histname = (isMu) ? "_bjetBdisc_mu" : "_bjetBdisc_ele" ;  
  else if (htype==21)
    histname = (isMu) ? "_bjetNoBCBdisc_mu" : "_bjetNoBCBdisc_ele" ;  

  cout << "Histname : " << histname << endl;

  string outputpdf = Form("figs/Week_Work_Report/2023-01-26/ctrl_plt/%d/hist%s.pdf",year,histname.c_str());
  //string outputpdf = Form("figs/Week_Work_Report/2023-01-16/ctrl_plt/%d/hist%s.pdf",year,histname.c_str());
  //const char* dir = "grid_v31_Syst/CBA_Skim_Syst_MedID";
  //const char* dir = "grid_v32_Syst/CBA_Skim_Syst_jet_tightID";
  //const char* dir = "grid_v35_Syst/CBA_Skim_Syst_jetsmeared";
  //const char* dir = "grid_v35_Syst/CBA_Skim_Syst_jetsmeared_metcorr";
  //const char* dir = "grid_v35_Syst/CBA_Skim_Syst_allDD";
  //const char* dir = "grid_v36_Syst/CBA_Skim_Syst_metMG";
  //const char* dir = "grid_v36_Syst/CBA_Skim_Syst_njet4to8";
  //const char* dir = "grid_v36_Syst/CBA_Skim_Syst_lowreso";
  //const char* dir = "grid_v36_Syst/CBA_Skim_Syst_btagCSV";
  //const char* dir = "grid_v37_Syst/CBA_Skim_Syst_SlStudy2";
  //const char* dir = "grid_v37_Syst/CBA_Skim_Syst_SlStudy3";
  //const char* dir = "grid_v37_Syst/CBA_Skim_Syst_SlStudy3";
  //const char* dir = "grid_v39_Syst/CBA_KFNewReso";
  //const char* dir = "grid_v39_Syst/CBA_1718_Resubmit";
  //const char* dir = "grid_v39_Syst/CBA_CTagM";
  //const char* dir = "grid_v39_Syst/CBA_CTagDD";
  //const char* dir = "grid_v40_Syst/CBA_CTagnPUJetID"; int rebin = 1;
  //const char* dir = "grid_v40_Syst/CBA_BJetSFTests"; int rebin = 1;
  //const char* dir = "grid_v40_Syst/CBA_PtJet30";
  //const char* dir = "grid_v40_Syst/CBA_PtJet25_jetMass0";
  //const char* dir = "grid_v40_Syst/CBA_FSRdown"; int rebin = 1;
  //const char* dir = "grid_v40_Syst/CBA_FSRup"; int rebin = 1;
  //const char* dir = "grid_v40_Syst/CBA_TLV_TPUJetID"; int rebin = 1;
  //const char* dir = "grid_v40_Syst/CBA_TLV_TPUJetID_KFAllJets"; int rebin = 5;
  //const char* dir = "grid_v40_Syst/CBA_TLVTPUKFAFSRDo_MiniReso"; int rebin = 5;
  //const char* dir = "grid_v40_Syst/CBA_TLVTPUKFAFSRDo_NanoReso"; int rebin = 1;
  //const char* dir = "grid_v40_Syst/CBA_TLVTPUKFAFSRDo_NR-GausM"; int rebin = 2;
  //const char* dir = "grid_v40_Syst/CBA_TLVTPUKFAFSRDo_NR-Offset"; int rebin = 2;
  //const char* dir = "grid_v40_Syst/CBA_TLVTPUKFAFSRDo_NROGM"; int rebin = 5;
  //const char* dir = "grid_v40_Syst/CBA_Nom1FSRDo_100MeVBin"; int rebin = 50;
  //const char* dir = "grid_v40_Syst/CBA_Nom1_100MeVBin"; int rebin = 50;
  //const char* dir = "grid_v40_Syst/CBA_CTagShapeCalib";int rebin = 50;
  //const char* dir = "grid_v40_Syst/CBA_CTagValidated"; int rebin = 50;
  //const char* dir = "grid_v40_Syst/CBA_CTagValidated-Hist"; int rebin = 50;
  //const char* dir = "grid_v40_Syst/CBA_CTagReWt-Hist"; int rebin = 50;
  //const char* dir = "grid_v40_Syst/CBA_muFmuR-Hist"; int rebin = 50;
  //const char* dir = "grid_v40_Syst/CBA_ctagv2-wtratio_evtwt"; int rebin = 50;
  //const char* dir = "grid_v40_Syst/CBA_ctagv2-bcwt1"; int rebin = 50;
  //const char* dir = "grid_v40_Syst/CBA_ctagv2pujetidtest"; int rebin = 1;
  //const char* dir = "grid_v40_Syst/CBA_elemva80-CombHist";
  const char* dir = "grid_v40_Syst/CBA_elereliso-CombHist";
  //const char* dir = "grid_v40_Syst/CBA_elereliso30-CombHist"; 
  
  const char *basedir = "/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna";  
  const char* datafile = (isMu) ? Form("root_files/%s/%d/all_DataMu.root",dir,year) : Form("root_files/%s/%d/all_DataEle.root",dir,year) ;
  const char* qcdfile_mc = (isMu) ? Form("root_files/%s/%d/all_MCQCDMu.root",dir,year) : Form("root_files/%s/%d/all_MCQCDEle.root",dir,year) ;
  const char* qcdfile = Form("root_files/%s/%d/all_QCDdd.root",dir,year);
  //const char* qcdfile = Form("%s",qcdfile_mc);
  
  TFile *fin_nano_data	= TFile::Open(datafile);
  TFile *fin_nano_sig	= TFile::Open(Form("root_files/%s/%d/all_HplusM120.root",dir,year));
  TFile *fin_nano_ttbar = TFile::Open(Form("root_files/%s/%d/all_TTbar.root",dir,year));
  TFile *fin_nano_stop	= TFile::Open(Form("root_files/%s/%d/all_singleTop.root",dir,year));
  TFile *fin_nano_wjets	= TFile::Open(Form("root_files/%s/%d/all_Wjets.root",dir,year));
  TFile *fin_nano_dyjets = TFile::Open(Form("root_files/%s/%d/all_DYjets.root",dir,year));
  TFile *fin_nano_vbf	= TFile::Open(Form("root_files/%s/%d/all_VBFusion.root",dir,year));
  TFile *fin_nano_qcd_mc = TFile::Open(qcdfile_mc);
  TFile *fin_nano_qcd	= TFile::Open(qcdfile);
  
  vector<TFile *> files_avmc,files_avdd;
  files_avmc.push_back(fin_nano_ttbar) ; files_avdd.push_back(fin_nano_ttbar);
  files_avmc.push_back(fin_nano_stop) ; files_avdd.push_back(fin_nano_stop);
  files_avmc.push_back(fin_nano_wjets) ; files_avdd.push_back(fin_nano_wjets);
  files_avmc.push_back(fin_nano_dyjets) ; files_avdd.push_back(fin_nano_dyjets);
  files_avmc.push_back(fin_nano_vbf) ; files_avdd.push_back(fin_nano_vbf);
  files_avmc.push_back(fin_nano_qcd_mc) ; files_avdd.push_back(fin_nano_qcd);

  TH1D	*hcf_nano_data	    = (TH1D *)fin_nano_data->Get(((isMu) ? Form("DataMu/base/Iso/%s",histname.c_str()) : Form("DataEle/base/Iso/%s",histname.c_str())));
  TH1D	*hcf_nano_sig	    = (TH1D *)fin_nano_sig->Get(Form("HplusM120/base/Iso/%s",histname.c_str()));
  TH1D	*hcf_nano_ttbar	    = (TH1D *)fin_nano_ttbar->Get(Form("TTbar/base/Iso/%s",histname.c_str()));
  TH1D	*hcf_nano_stop	    = (TH1D *)fin_nano_stop->Get(Form("singleTop/base/Iso/%s",histname.c_str())); 
  TH1D	*hcf_nano_wjets	    = (TH1D *)fin_nano_wjets->Get(Form("Wjets/base/Iso/%s",histname.c_str()));
  TH1D	*hcf_nano_dyjets    = (TH1D *)fin_nano_dyjets->Get(Form("DYjets/base/Iso/%s",histname.c_str()));
  TH1D	*hcf_nano_vbf	    = (TH1D *)fin_nano_vbf->Get(Form("VBFusion/base/Iso/%s",histname.c_str()));
  TH1D	*hcf_nano_qcd_mc    = (TH1D *)fin_nano_qcd_mc->Get(((isMu) ? Form("MCQCDMu/base/Iso/%s",histname.c_str()) : Form("MCQCDEle/base/Iso/%s",histname.c_str())));
  TH1D	*hcf_nano_qcd	    = (TH1D *)fin_nano_qcd->Get(Form("QCDdd/base/Iso/%s",histname.c_str()));
  TH1D	*hcf_nano_qcd_iso20 = (TH1D *)fin_nano_qcd->Get(Form("QCDdd/iso20/Iso/%s",histname.c_str()));

  double stat_Error = 0.0;
  double Norm = hcf_nano_qcd->IntegralAndError(1,hcf_nano_qcd->GetNbinsX(),stat_Error); 
  double stat_Error_iso20 = 0.0;
  double Norm_iso20 = hcf_nano_qcd_iso20->IntegralAndError(1,hcf_nano_qcd_iso20->GetNbinsX(),stat_Error_iso20); 
  qcd_frac = TMath::Abs((Norm-Norm_iso20)/Norm);
  cout << "Iso Syst (in %) : " << qcd_frac*100.0 << endl;
  
  if(histname.find("_mjj_")!=string::npos){
    hcf_nano_data->Rebin(rebin);
    hcf_nano_sig->Rebin(rebin);
    hcf_nano_ttbar->Rebin(rebin);
    hcf_nano_stop->Rebin(rebin);
    hcf_nano_wjets->Rebin(rebin);
    hcf_nano_dyjets->Rebin(rebin);
    hcf_nano_vbf->Rebin(rebin);
    hcf_nano_qcd_mc->Rebin(rebin);
    //hcf_nano_qcd->Rebin(rebin);
  }
  hcf_nano_sig->Scale(0.1211); //Scaledown to not display the original value
  
  // const char *systDir[] = {"base",
  // 			   "puup", "pudown", "mueffup", "mueffdown",                    //2,4
  // 			   "eleeffup", "eleeffdown", "prefireup", "prefiredown",        //6,8
  // 			   "jecup", "jecdown", "jerup", "jerdown",                      //10,12,
  // 			   "pdfup", "pdfdown", "q2up", "q2down",                        //14,16
  // 			   "bclhemurup", "bclhemurdown", "bclhemufup", "bclhemufdown",  //18,20
  // 			   "isrup", "isrdown", "fsrup", "fsrdown",                      //22,24
  // 			   "pujetidup", "pujetiddown", "bcintpup", "bcintpdown",        //26,28
  // 			   "bcextpup", "bcextpdown", "bcxdybup", "bcxdybdown",          //30.32
  // 			   "bcxdycup", "bcxdycdown", "bcxwjcup", "bcxwjcdown",          //34.36
  // 			   "bcstatup", "bcstatdown"                                    //38
  // };

  //"mueffup", "mueffdown", "eleeffup", "eleeffdown",
  //const char *syst[] = {"pu", "jec", "jer", "btagb", "btagl", "prefire", "met"};
  //const char *syst[] = {"pu", "jec", "jer", "bcstat", "bclhemuf", "prefire", "met"};
  const int nSyst = 18;
  const char *syst[] = {   "mueff", "eleeff", "pu", "prefire",
  			   "jec",  "jer", "pdf", "bclhemur", //"q2"
  			   "bclhemuf", "isr", "fsr", "pujetid",
			   "bcintp", "bcextp", "bcxdyb", "bcxdyc",        
  			   "bcxwjc", "bcstat"};
    
  TH1D *hLeptonUp, *hLeptonDown;
  if(isMu){
    hLeptonUp = GetUpDownHistDD(files_avdd,"mueff","up",histname);;
    hLeptonDown = GetUpDownHistDD(files_avdd,"mueff","down",histname);;
  }else{
    hLeptonUp = GetUpDownHistDD(files_avdd,"eleeff","up",histname);;
    hLeptonDown = GetUpDownHistDD(files_avdd,"eleeff","down",histname);;
  }
  vector<TH1D *> vSystUp, vSystDown, vSystNominal;
  vSystUp.push_back(hLeptonUp); vSystDown.push_back(hLeptonDown);
  
  const int nofSyst = nSyst - 2;
  TH1D *hSystUp[nofSyst], *hSystDown[nofSyst];
  for(int isyst = 2 ; isyst<nSyst    ; isyst++){
    if(year==2018 and strcmp(syst[isyst],"prefire")==0) continue;
    hSystUp[isyst-2] = GetUpDownHistDD(files_avdd,syst[isyst],"up",histname);
    hSystDown[isyst-2] = GetUpDownHistDD(files_avdd,syst[isyst],"down",histname);
    vSystUp.push_back(hSystUp[isyst-2]); vSystDown.push_back(hSystDown[isyst-2]);
  }
  
  TH1D *hcf_nano_bkg = (TH1D *)hcf_nano_ttbar->Clone("Bkg");
  hcf_nano_bkg->Add(hcf_nano_stop);
  hcf_nano_bkg->Add(hcf_nano_wjets);
  hcf_nano_bkg->Add(hcf_nano_dyjets);
  hcf_nano_bkg->Add(hcf_nano_vbf);
  hcf_nano_bkg->Add(hcf_nano_qcd);
  //hcf_nano_bkg->Add(hcf_nano_qcd_mc);
  
  hcf_nano_ttbar->SetName(Form("%s_TTbar",hcf_nano_ttbar->GetName()));
  hcf_nano_stop->SetName(Form("%s_Stop",hcf_nano_stop->GetName()));
  hcf_nano_wjets->SetName(Form("%s_Wjets",hcf_nano_wjets->GetName()));
  hcf_nano_dyjets->SetName(Form("%s_DYjets",hcf_nano_dyjets->GetName()));
  hcf_nano_vbf->SetName(Form("%s_VBF",hcf_nano_vbf->GetName()));
  hcf_nano_qcd->SetName(Form("%s_QCD",hcf_nano_qcd->GetName()));
  
  vSystNominal.push_back(hcf_nano_ttbar);
  vSystNominal.push_back(hcf_nano_stop);
  vSystNominal.push_back(hcf_nano_wjets);
  vSystNominal.push_back(hcf_nano_dyjets);
  vSystNominal.push_back(hcf_nano_vbf);
  vSystNominal.push_back(hcf_nano_qcd);
  
  TGraphAsymmErrors *grSystFull = SystGraph(year, histname, hcf_nano_bkg,  hcf_nano_qcd, vSystNominal, vSystUp, vSystDown, true, false);
  TGraphAsymmErrors *grSystRatio = SystGraph(year, histname, hcf_nano_bkg,  hcf_nano_qcd, vSystNominal, vSystUp, vSystDown, false, true);

  hcf_nano_data->SetMarkerStyle(kFullCircle);
  hcf_nano_data->SetMarkerColor(kBlack);
  hcf_nano_data->SetMarkerSize(1.2);
  
  if(year == 2016 or year == 2017 or year == 2018){
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
  hcf_nano_qcd_mc->SetFillColor(kBlue);
  
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
  hMC->SetTitle("");
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

  float upper_minY = 1.0e-1; float upper_maxY = 8.e7;  //y-axis range of upper pad
  //float upper_minY = 1.0e-1; float upper_maxY = 5.e12;  //y-axis range of upper pad
  float lower_minY = 0.0; float lower_maxY = 2.0;     //y-axis range of lower pad
  
  // 0:leppt, 1:jetpt, 2:metpt, 3:lepeta, 4:jeteta, 5:lepphi, 6:jetphi, 7:metphi, 8:njet, 9:nbjet, 10:mjj
  float upper_minX = 0.0; float upper_maxX = 500.0;
  //if(htype>=0 and htype<=2){
  if(htype==1){
    upper_minX = 0.0; upper_maxX = 700.0;   //x-axis range
  }else if(htype>=3 and htype<=4){
    upper_minX = -2.9; upper_maxX = 2.9;   //x-axis range
  }else if(htype>=5 and htype<=7){
    upper_minX = -3.4; upper_maxX = 3.4;   //x-axis range
  }else if(htype==8){
    upper_minX = 0.0; upper_maxX = 20.0;   //x-axis range
  }else if(htype==9){
    upper_minX = 0.0; upper_maxX = 10.0;   //x-axis range
  }else if(htype>=10){
    if(isBtag){
      upper_minX = 0.0; upper_maxX = 450.0;   //x-axis range
    }else{
      upper_minX = 0.0; upper_maxX = 200.0;   //x-axis range
    }
  // }else if(htype==20 or htype==21){
  //   upper_minX = -0.5; upper_maxX = 200.0;   //x-axis range
  }

  float integral_min = upper_minX; float integral_max = upper_maxX; // for integral calculation
  //float integral_min = 4.0; float integral_max = upper_maxX; // for integral calculation

  //float legend_pos[4] = {0.5, 0.65, 0.88, 0.86};
  float legend_pos1[4] = {0.38, 0.75, 0.54, 0.86};
  float legend_pos2[4] = {0.50, 0.75, 0.71, 0.86};
  float legend_pos3[4] = {0.65, 0.70, 0.88, 0.86};
  ///////////////////////////////////////////////////////////////////////////////////////////      

  gStyle->SetOptStat(0);
  //Ranges
  hData->SetMaximum(upper_maxY);
  hData->SetMinimum(upper_minY);
  hData->GetXaxis()->SetRangeUser(upper_minX, upper_maxX);
  //hs->GetXaxis()->SetRangeUser(upper_minX, upper_maxX);
  hMC->SetMaximum(upper_maxY);
  hMC->SetMinimum(upper_minY);
  hMC->GetXaxis()->SetRangeUser(upper_minX, upper_maxX);
  //hMC->GetXaxis()->SetRangeUser(upper_minX, 500.0);
  //hData->GetXaxis()->SetRange(hData->FindBin(upper_minX), hData->FindBin(upper_maxX));
  //hMC->GetXaxis()->SetRange(upper_minX, upper_maxX);
  //axis Titles
  hData->GetXaxis()->SetTitle(upper_pad_xaxis_title.c_str());
  hData->GetYaxis()->SetTitle(upper_pad_yaxis_title.c_str());
  hMC->GetXaxis()->SetTitle(upper_pad_xaxis_title.c_str());
  hMC->GetXaxis()->SetTitle("m_{jj} (GeV)");
  hMC->GetYaxis()->SetTitle(upper_pad_yaxis_title.c_str());
  //Now add style and color
  SetStatMarkerStyle(hData, kBlack, kFullCircle, 1);
  SetStatMarkerStyle(hMC, kBlue, kFullSquare, 0.1);  
  
  float canvas_scale = 1;
  int canvas_width = TMath::Nint(canvas_scale*900) ;
  int canvas_height = TMath::Nint(canvas_scale*800) ;
  
  // Search and replace != with == of  --histname.find("_mjj_")!=string::npos-- for all following occurances to plot unblinded Mjj
  bool mass_plot = (histname.find("_mjj_")!=string::npos);
  //bool mass_plot = (histname.find("_mjj_")==string::npos);
  bool isBlinded = (mass_plot) ; 
  TPad *p = 0x0;
  if(isBlinded){
    p = Plot(hs, hcf_nano_sig, hMC, grSystFull, "c1", true);
    //p = Plot(hs, hcf_nano_sig, hMC, grSystFull, "c1", false);
  }else{
    p = PlotRatio(hs, hcf_nano_sig, hData, hMC, grSystFull, grSystRatio, "c1", true);
    //p = PlotRatio(hs, hcf_nano_sig, hData, hMC, grSystFull, grSystRatio, "c1", false);
  }

  TLegend *leg1 = p->BuildLegend();
  for(int i = 0 ; i < 15 ; i++)
    leg1->DeleteEntry() ;// This is to delete default title of hData
  leg1->AddEntry(hData, Form("%s",hist_num_title) ,"lp");
  leg1->AddEntry(hMC, Form("%s",hist_den_title) ,"lp");
  leg1->AddEntry(hcf_nano_ttbar, Form("#it{t}#bar{#it{t}}") ,"f");

  TLegend *leg2 = p->BuildLegend();
  for(int i = 0 ; i < 15 ; i++)
    leg2->DeleteEntry() ;// This is to delete default title of hData  
  leg2->AddEntry(hcf_nano_stop, Form("Single #it{t}") ,"f");
  leg2->AddEntry(hcf_nano_wjets, Form("#it{W} + jets") ,"f");
  leg2->AddEntry(hcf_nano_dyjets, Form("#it{Z}/#gamma + jets") ,"f");

  TLegend *leg3 = p->BuildLegend();
  for(int i = 0 ; i < 15 ; i++)
    leg3->DeleteEntry() ;// This is to delete default title of hData  
  leg3->AddEntry(hcf_nano_vbf, Form("VV") ,"f");
  leg3->AddEntry(hcf_nano_qcd, Form("QCD") ,"f");
  leg3->AddEntry(grSystFull, Form("Unc") ,"f");

  if(year == 2016 or year == 2017 or year == 2018)
    leg3->AddEntry(hcf_nano_sig, Form("m_{H^{+}} = 120 GeV") ,"l");

  leg1->SetX1(legend_pos1[0]); leg1->SetY1(legend_pos1[1]); 
  leg1->SetX2(legend_pos1[2]); leg1->SetY2(legend_pos1[3]); 

  leg2->SetX1(legend_pos2[0]); leg2->SetY1(legend_pos2[1]); 
  leg2->SetX2(legend_pos2[2]); leg2->SetY2(legend_pos2[3]); 

  leg3->SetX1(legend_pos3[0]); leg3->SetY1(legend_pos3[1]); 
  leg3->SetX2(legend_pos3[2]); leg3->SetY2(legend_pos3[3]); 

  SetLegendStyle(leg1, histname, isBlinded);
  SetLegendStyle(leg2, histname, isBlinded);
  SetLegendStyle(leg3, histname, isBlinded);

  leg1->Draw();
  leg2->Draw();
  leg3->Draw();

  TPaveText *t0 = new TPaveText(0.19,0.91,0.37,0.96,"NDC");
  t0->SetFillStyle(0);
  t0->SetBorderSize(0);
  //t0->SetTextFont(42);
  t0->SetTextSize(.05); 
  if(isBlinded)
    t0->SetTextSize(.035); 
  t0->SetMargin(0.1);
  t0->AddText("CMS Preliminary");
  t0->SetTextAlign(32); //left aligned middle vertically
  t0->Draw();

  TPaveText *t1 = new TPaveText(0.60,0.91,0.95,0.96,"NDC");
  t1->SetFillStyle(0);
  t1->SetBorderSize(0);
  t1->SetTextFont(42);
  t1->SetTextSize(.05); 
  if(isBlinded)
    t1->SetTextSize(.035); 
  t1->SetMargin(0.1);
  t1->AddText(Form("%3.1f fb^{-1} (13 TeV)",luminosity[year%2016]));
  t1->Draw();
  
  TPaveText *t2 = 0x0; 
  if(isBlinded)
    t2 = new TPaveText(0.13, 0.78, 0.39, 0.86,"NDC");
  else
    t2 = new TPaveText(0.13, 0.78, 0.36, 0.86,"NDC");
  t2->SetFillStyle(0);
  t2->SetBorderSize(0);
  t2->SetTextFont(42);
  t2->SetTextSize(.05); 
  if(isBlinded)
    t2->SetTextSize(.035); 
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

  TCanvas *canvas = (TCanvas *)gROOT->GetListOfCanvases()->FindObject("c1");
  canvas->SaveAs(outputpdf.c_str());
  canvas->SaveAs("output.pdf");
  
  return true;
}

TPad* PlotRatio(THStack *hs, TH1D *hsig, TH1D *h1, TH1D *h2,TGraphAsymmErrors *syst, TGraphAsymmErrors *systRatio, const char *cname, bool isLog)
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
    //h1->SetStats(0);          // No statistics on upper plot
    h1->Draw("e1p");               // Draw h1
    //syst->SetFillColorAlpha(kRed,0.7);
    syst->SetFillColor(kRed-7);
    syst->Draw("e2 sames");
    // h2->Draw("hist same");         // Draw h2 on top of h1
    hs->Draw("sames hist");
    // TList *hlist = hs->GetHists();
    // TH1F *ht0 = (TH1F *)hlist->At(0);
    // TH1F *ht1 = (TH1F *)hlist->At(1);
    // TH1F *ht2 = (TH1F *)hlist->At(2);
    // TH1F *ht3 = (TH1F *)hlist->At(3);
    // TH1F *ht4 = (TH1F *)hlist->At(4);
    // TH1F *ht5 = (TH1F *)hlist->At(5);
    // cout << "ht5 name : " << ht5->GetName() << endl;
    // ht0->Draw("sames");
    // ht1->Draw("sames");
    // ht2->Draw("sames");
    // ht3->Draw("sames");
    // ht4->Draw("sames");
    // ht5->Draw("sames");
    h1->Draw("e1p same");               // Draw h1
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
    // h3->SetMinimum(0.2);  // Define Y ..
    // h3->SetMaximum(1.8); // .. range
    // h3->SetMinimum(0.9);  // Define Y ..
    // h3->SetMaximum(1.1); // .. range
    // h3->SetMinimum(0.85);  // Define Y ..
    // h3->SetMaximum(1.12); // .. range
    // h3->SetMinimum(0.4);  // Define Y ..
    // h3->SetMaximum(1.6); // .. range
    // h3->SetMinimum(0.8);  // Define Y ..
    // h3->SetMaximum(1.2); // .. range
    h3->SetMinimum(0.4);  // Define Y ..
    h3->SetMaximum(1.6); // .. range
    //h3->SetMinimum(0.6);  // Define Y ..
    //h3->SetMaximum(1.4); // .. range
    h3->Sumw2();
    h3->SetStats(0);      // No statistics on lower plot
    h3->Divide(h2);
    //h3->SetMarkerStyle(21);
    h3->SetMarkerColor(kBlack);
    //h3->SetFillColor(kRed);
    h3->Draw("p");       // Draw the ratio plot
    //systRatio->SetFillColorAlpha(kRed-9,0.001);
    //systRatio->SetFillColorAlpha(kRed,0.7);
    //systRatio->SetFillColor(kGreen-8);
    systRatio->SetFillColorAlpha(kGreen-8,0.8);
    //systRatio->SetFillStyle(3001);
    systRatio->Draw("e2 sames");
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
    h3->GetYaxis()->SetTitle("#frac{Data}{Bkg}");
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

TPad* Plot(THStack *hs, TH1D *hsig, TH1D *h1, TGraphAsymmErrors *syst, const char *cname, bool isLog)
{

  TCanvas *canvas = (TCanvas *)gROOT->GetListOfCanvases()->FindObject(cname);
  TPad *pad1 = 0x0;

  if(!canvas){
    TCanvas *c = new TCanvas(cname, cname, 800, 800);
 
    // Upper plot will be in pad1
    pad1 = new TPad("pad1", "pad1", 0, 0.01, 1, 1.0);
    pad1->SetBottomMargin(0.1); // Upper and lower plot are joined
    //pad1->SetGridx();         // Vertical grid
    if(isLog) pad1->SetLogy();
    pad1->Draw();             // Draw the upper pad: pad1
    pad1->cd();               // pad1 becomes the current pad
    pad1->SetTickx();
    pad1->SetTicky();
    h1->SetStats(0);          // No statistics on upper plot
    h1->SetTitle("");
    h1->Draw("hist");               // Draw h1
    syst->SetFillColorAlpha(kRed,0.7);
    hs->Draw("hist same");         // Draw hs on top of h1
    syst->Draw("e2 sames");
    //h1->Draw("e1p sames");               // Draw h1
    hsig->Draw("hist sames");               // Draw h1

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
 

    c->cd();          // Go back to the main canvas before defining pad2
 
    // Y axis h1 plot settings
    //h1->GetYaxis()->SetTitle(Form("Entries / %1.0f GeV",h1->GetBinWidth(2)));
    h1->GetYaxis()->SetTitle("Entries / bin");
    h1->GetYaxis()->SetTitleSize(25);
    h1->GetYaxis()->SetTitleFont(43);
    h1->GetYaxis()->SetTitleOffset(1.55);
    h1->GetYaxis()->SetLabelSize(25);

    //h1->GetXaxis()->SetTitleOffset(3.5);
    //h1->GetXaxis()->SetLabelOffset(0.1);
 
    // h2 settings
    //h2->SetLineColor(kRed);
    //h2->SetLineWidth(2);
 
    // Ratio plot (h3) settings
    // h3->SetTitle(""); // Remove the ratio title
 
    // // Y axis ratio plot settings
    // h3->GetYaxis()->SetTitle("#frac{Data}{Bkg}");
    // h3->GetYaxis()->SetNdivisions(505);
    // h3->GetYaxis()->SetTitleSize(25);
    // h3->GetYaxis()->SetTitleFont(43);
    // h3->GetYaxis()->SetTitleOffset(1.3);
    // h3->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
    // h3->GetYaxis()->SetLabelSize(25);
 
    // // X axis ratio plot settings
    // h3->GetXaxis()->SetTitle(h1->GetXaxis()->GetTitle());
    // h3->GetXaxis()->SetTitleSize(25);
    // h3->GetXaxis()->SetTitleFont(43);
    // h3->GetXaxis()->SetTitleOffset(3.6);
    // h3->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
    // h3->GetXaxis()->SetLabelSize(25);
    
    pad1->cd();

    cout<<" nof canvas primitives " << c->GetListOfPrimitives()->GetEntries() << endl ;
    
  }else {

    pad1 = (TPad *)canvas->GetListOfPrimitives()->FindObject("pad1") ;
    pad1->cd();
    
    // h1->Draw("hist same");             
    // h2->Draw("hist same");         
    
    // TPad *pad2 = (TPad *)canvas->GetListOfPrimitives()->FindObject("pad2") ;
    // pad2->cd();
    

    // TH1F *h3 = (TH1F*)h1->Clone("h3");
    // h3->SetLineColor(h1->GetLineColor());
    // h3->Sumw2();
    // h3->SetStats(0);      // No statistics on lower plot
    // h3->Divide(h2);
    // h3->Draw("ep same");       // Draw the ratio plot
    
    pad1->cd();
  }

  return pad1;
}

int PrintHSeparator(void){
  for (int i=0;i<130;i++) 
    printf("="); 
  cout << endl;
  return true;
}

int SetLegendStyle(TLegend *& leg, string histname, bool isBlinded)
{
  
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->SetTextFont(42);
  leg->SetTextSize(.04); 
  if(isBlinded)
    leg->SetTextSize(.03); 
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

/////////////////////////////////////////////////////////////////////////////////////
double errBandUp(int iBin, int year, TH1D *hCentral,  TH1D *hQCD, vector<TH1D *> vSystNom, vector<TH1D *> vSystUp){
  double errUp = 0.0;
  for(unsigned int isys = 0 ; isys < vSystUp.size() ; isys++){
    TH1D *hSyst = vSystUp.at(isys);
    errUp += pow(fabs(hSyst->GetBinContent(iBin+1) - hCentral->GetBinContent(iBin+1)),2) ;
    // if(iBin==41)
    //   cout<<"hSyst : "<<hSyst->GetName()<<", bin value : "<<errUp <<", systTot : "<<hSyst->GetBinContent(iBin+1)<<", centralTot : "<<hCentral->GetBinContent(iBin+1)<<endl;
  }
  // if(iBin==41)
  //   cout<<"step1 : errU value : "<<errUp<<endl;

  if(TMath::Finite(hCentral->GetBinError(iBin+1))!=0)
    errUp += pow(hCentral->GetBinError(iBin+1),2);
  //errUp += pow(hQCD->GetBinError(iBin+1),2);
  
  //The following section is to add the XS normalization uncertainty
  for(unsigned int inom = 0 ; inom < vSystNom.size() ; inom++){
    TH1D *hNom = vSystNom.at(inom);
    TString hname = hNom->GetName();
    if(hNom->GetBinContent(iBin+1)>0.0 and hname.Contains("TTbar"))
      errUp += pow(hNom->GetBinContent(iBin+1)*0.061/2,2);
    if(hNom->GetBinContent(iBin+1)>0.0 and hname.Contains("Stop"))
      errUp += pow(hNom->GetBinContent(iBin+1)*0.05/2,2);
    if(hNom->GetBinContent(iBin+1)>0.0 and hname.Contains("Wjets"))
      errUp += pow(hNom->GetBinContent(iBin+1)*0.05/2,2);
    if(hNom->GetBinContent(iBin+1)>0.0 and hname.Contains("DYjets"))
      errUp += pow(hNom->GetBinContent(iBin+1)*0.045/2,2);
    if(hNom->GetBinContent(iBin+1)>0.0 and hname.Contains("VBF"))
      errUp += pow(hNom->GetBinContent(iBin+1)*0.04/2,2);
    if(hNom->GetBinContent(iBin+1)>0.0 and hname.Contains("QCD"))
      errUp += pow(hNom->GetBinContent(iBin+1)*qcd_frac/2,2);
    // if(iBin==41)
    //   cout<<"hname : "<<hname<<", hNom : "<<hNom->GetName()<<", bin value : "<<errUp<<endl;
  }
  
  // if(iBin==41)
  //   cout<<"before : errU value : "<<errUp<<endl;

  errUp = sqrt(errUp) + 0.5*lumi_unc[year%2016]*hCentral->GetBinContent(iBin+1); //lumi unc added linearly since correlated

  // if(iBin==41)
  //   cout<<"after : errU value : "<<errUp<<endl<<endl;;

  return errUp;
}

double errBandDown(int iBin, int year, TH1D *hCentral,  TH1D *hQCD, vector<TH1D *> vSystNom, vector<TH1D *> vSystDown){
  double errDown = 0.0;
  for(unsigned int isys = 0 ; isys < vSystDown.size() ; isys++){
    TH1D *hSyst = vSystDown.at(isys);
    errDown += pow(fabs(hCentral->GetBinContent(iBin+1) - hSyst->GetBinContent(iBin+1)),2) ;
  }
  if(TMath::Finite(hCentral->GetBinError(iBin+1))!=0)
    errDown += pow(hCentral->GetBinError(iBin+1),2);
  //errDown += pow(hQCD->GetBinError(iBin+1),2);

  //The following section is to add the XS normalization uncertainty
  for(unsigned int inom = 0 ; inom < vSystNom.size() ; inom++){
    TH1D *hNom = vSystNom.at(inom);
    TString hname = hNom->GetName();
    if(hNom->GetBinContent(iBin+1)>0.0 and hname.Contains("TTbar"))
      errDown += pow(hNom->GetBinContent(iBin+1)*0.061/2,2);
    if(hNom->GetBinContent(iBin+1)>0.0 and hname.Contains("Stop"))
      errDown += pow(hNom->GetBinContent(iBin+1)*0.05/2,2);
    if(hNom->GetBinContent(iBin+1)>0.0 and hname.Contains("Wjets"))
      errDown += pow(hNom->GetBinContent(iBin+1)*0.05/2,2);
    if(hNom->GetBinContent(iBin+1)>0.0 and hname.Contains("DYjets"))
      errDown += pow(hNom->GetBinContent(iBin+1)*0.045/2,2);
    if(hNom->GetBinContent(iBin+1)>0.0 and hname.Contains("VBF"))
      errDown += pow(hNom->GetBinContent(iBin+1)*0.04/2,2);
    if(hNom->GetBinContent(iBin+1)>0.0 and hname.Contains("QCD"))
      errDown += pow(hNom->GetBinContent(iBin+1)*qcd_frac/2,2);    
  }  

  errDown = sqrt(errDown) + 0.5*lumi_unc[year%2016]*hCentral->GetBinContent(iBin+1); //lumi unc added linearly since correlated

  return errDown;
}

TGraphAsymmErrors *SystGraph(int year, string histname, TH1D *hCentral,  TH1D *hQCD, vector<TH1D *> vSystNom,  vector<TH1D *> vSystUp, vector<TH1D *> vSystDown, 
			     bool isFullGraph = false, bool isRatioGraph = false){
  
  TGraphAsymmErrors *gr;
  int n1 = hCentral->GetNbinsX(); 
  double *Yval, *errorU, *errorD, *XerrorU, *XerrorD, *Xval ;
  
  Yval = new double[n1]; errorU = new double[n1]; errorD = new double[n1];
  XerrorU=new double[n1]; XerrorD=new double[n1]; Xval=new double[n1];
  
  //cout << "No. of bins= " << n1 << endl;
  int nmax = 0;
  for(int i=0; i<n1; i++){
    if(!(hCentral->GetBinContent(i+1)>0.0)) continue;

    double lowedge = hCentral->GetXaxis()->GetBinLowEdge(i+1);
    double upedge = hCentral->GetXaxis()->GetBinUpEdge(i);
    if(histname.find("eta")!=string::npos and (TMath::Abs(lowedge) > 2.4 or TMath::Abs(upedge) > 2.4)) continue;
    //if(histname.find("met")!=string::npos and histname.find("pt")!=string::npos and TMath::Abs(lowedge) < 20.) continue;
    
    if(isFullGraph){
      Yval[i]   = hCentral->GetBinContent(i+1);
      errorU[i] = errBandUp(i, year, hCentral, hQCD, vSystNom, vSystUp); 
      errorD[i] = errBandDown(i, year, hCentral, hQCD, vSystNom, vSystDown); 
      if(hCentral->GetBinContent(i+1)>0.0) nmax = i+1 ;
      // if(abs(errorD[i]) > 1.0e3)
      // 	cout<<i<<", "<<Yval[i]<<"\t"<<errorU[i]<<"\t"<<errorD[i]<<"\t"<<hCentral->GetBinContent(i+1)<<endl;
	
    }
    if(isRatioGraph){
      Yval[i]   = 1;
      errorU[i] = errBandUp(i, year, hCentral, hQCD, vSystNom, vSystUp); 
      errorD[i] = errBandDown(i, year, hCentral, hQCD, vSystNom, vSystDown);
      //cout<<"bin = "<<i<<endl;
      //cout<<Yval[i]<<"\t"<<errorU[i]<<"\t"<<hCentral->GetBinContent(i+1)<<endl;
      if(hCentral->GetBinContent(i+1)>0.0){ 
	errorU[i] = errorU[i]/hCentral->GetBinContent(i+1) ;
	errorD[i] = errorD[i]/hCentral->GetBinContent(i+1) ;
	nmax = i+1 ;
      }else{
	errorU[i] = 0.0;
	errorD[i] = 0.0;
      }
      // if(abs(errorU[i]) > 1.2 or abs(errorD[i]) > 1.2)
      // 	cout<<i<<", x : "<<hCentral->GetBinCenter(i+1)<<", Y : "<<Yval[i]<<", errU : "<<errorU[i]<<", errD : "<<errorD[i]<<", bintot : "<<hCentral->GetBinContent(i+1)<<endl;
    }
    Xval[i]   = hCentral->GetBinCenter(i+1);
    XerrorU[i]= hCentral->GetBinWidth(i+1)/2;
    XerrorD[i]= hCentral->GetBinWidth(i+1)/2;
  }
  
  gr = new TGraphAsymmErrors(nmax, Xval, Yval, XerrorD, XerrorU, errorD, errorU);
  //delete [] Yval; delete [] errorU; delete [] errorD; delete [] XerrorU; delete [] XerrorD; delete [] Xval;

  return gr;
  
} 

/////////////////////////////////////////////////////////////////////////////////////
//// The following parts are taken from Ravindra's code

// double errBandUp(int iBin, TH1F *hCentral, TH1F *hJESPlus, TH1F *hJERPlus, TH1F *bTagPlus, TH1F *cTagPlus, TH1F* PileupPlus, TH1F *hQCD_dd, double qcd_sf_err){
//   double errUp = sqrt(pow(fabs(hJESPlus->GetBinContent(iBin+1) - hCentral->GetBinContent(iBin+1)),2) + 
// 		  pow(fabs(hJERPlus->GetBinContent(iBin+1) - hCentral->GetBinContent(iBin+1)),2) + 
// 		  pow(fabs(bTagPlus->GetBinContent(iBin+1) - hCentral->GetBinContent(iBin+1)),2) + 
// 		  pow(fabs(cTagPlus->GetBinContent(iBin+1) - hCentral->GetBinContent(iBin+1)),2) + 
// 		  pow(fabs(PileupPlus->GetBinContent(iBin+1) - hCentral->GetBinContent(iBin+1)),2) + 
// 		  pow(hCentral->GetBinError(iBin+1),2)+ pow(qcd_sf_err*hQCD_dd->GetBinContent(iBin+1),2));
//   return errUp;
// }

// double errBandDown(int iBin, TH1F *hCentral, TH1F *hJESMinus, TH1F *hJERMinus, TH1F *bTagMinus, TH1F *cTagMinus, TH1F* PileupMinus, TH1F *hQCD_dd, double qcd_sf_err){
//   double errDown =sqrt(pow(fabs(hCentral->GetBinContent(iBin+1) - hJESMinus->GetBinContent(iBin+1)),2) + 
// 		  pow(fabs(hCentral->GetBinContent(iBin+1) - hJERMinus->GetBinContent(iBin+1)),2) + 
// 		  pow(fabs(hCentral->GetBinContent(iBin+1) - bTagMinus->GetBinContent(iBin+1)),2) + 
// 		  pow(fabs(hCentral->GetBinContent(iBin+1) - cTagMinus->GetBinContent(iBin+1)),2) + 
// 		  pow(fabs(hCentral->GetBinContent(iBin+1) - PileupMinus->GetBinContent(iBin+1)),2) + 
// 		  pow(hCentral->GetBinError(iBin+1),2)+pow(qcd_sf_err*hQCD_dd->GetBinContent(iBin+1),2));
//   return errDown;
// }

// TGraphAsymmErrors *UNCGRAPH(TH1F *hCentral, TH1F *hJESPlus, TH1F *hJESMinus, TH1F *hJERPlus, TH1F *hJERMinus, TH1F *bTagPlus, TH1F *bTagMinus, TH1F *cTagPlus, TH1F *cTagMinus, TH1F* PileupPlus, TH1F* PileupMinus, TH1F* hQCD_dd, double qcd_sf_err, bool isFullGraph = false, bool isRatioGraph = false){
//   TGraphAsymmErrors *gr;
//   int n1 = hCentral->GetNbinsX(); 
//   double *Yval, *errorU, *errorD, *XerrorU, *XerrorD, *Xval ;
//   Yval = new double[n1]; errorU = new double[n1]; errorD = new double[n1];
//   XerrorU=new double[n1]; XerrorD=new double[n1]; Xval=new double[n1];
//   //cout << "No. of bins= " << n1 << endl;
//   for(int i=0; i<n1; i++){
//     if(isFullGraph){
//     Yval[i]   = hCentral->GetBinContent(i+1);
//     errorU[i] = errBandUp(i, hCentral, hJESPlus, hJERPlus, bTagPlus, cTagPlus, PileupPlus, hQCD_dd, qcd_sf_err); 
//     errorD[i] = errBandDown(i, hCentral, hJESMinus, hJERMinus, bTagMinus, cTagMinus, PileupMinus, hQCD_dd, qcd_sf_err); 
//     }
//     if(isRatioGraph){
//     Yval[i]   = 1;
//     errorU[i] = errBandUp(i, hCentral, hJESPlus, hJERPlus, bTagPlus, cTagPlus, PileupPlus, hQCD_dd, qcd_sf_err); 
//     errorD[i] = errBandDown(i, hCentral, hJESMinus, hJERMinus, bTagMinus, cTagMinus, PileupMinus, hQCD_dd, qcd_sf_err); 
//     //cout<<"bin = "<<i<<endl;
//     //cout<<Yval[i]<<"\t"<<errorU[i]<<"\t"<<hCentral->GetBinContent(i+1)<<endl;
//     errorU[i] = errorU[i]/hCentral->GetBinContent(i+1);
//     errorD[i] = errorD[i]/hCentral->GetBinContent(i+1);
//     //cout<<Yval[i]<<"\t"<<errorU[i]<<"\t"<<hCentral->GetBinContent(i+1)<<endl;
//     }
//     Xval[i]   = hCentral->GetBinCenter(i+1);
//     XerrorU[i]= hCentral->GetBinWidth(i+1)/2;
//     XerrorD[i]= hCentral->GetBinWidth(i+1)/2;
//   }
//   gr = new TGraphAsymmErrors(n1, Xval, Yval, XerrorD, XerrorU, errorD, errorU);
//   return gr;
//   delete [] Yval; delete [] errorU; delete [] errorD; delete [] XerrorU; delete [] XerrorD; delete [] Xval;
// } 

// TH1F* addHistoForUnc(TString dir, TString histname, TString sys, bool isDataDrivenQCD = false, double qcd_sf=1){
//   TH1F* hVV = getHisto(fVV, sys+"/Iso", dir, histname); 
//   TH1F* hDY = getHisto(fDY, sys+"/Iso", dir, histname); 
//   TH1F* hQCD_mc = getHisto(fQCD, sys+"/Iso", dir, histname); 
//   TH1F* hWJ = getHisto(fWJ, sys+"/Iso", dir, histname); 
//   TH1F* hST = getHisto(fST, sys+"/Iso", dir, histname); 
//   TH1F* hTT = getHisto(fTT, sys+"/Iso", dir, histname); 
//   TH1F* hAll = (TH1F*)hVV->Clone("hAllMC");
//   hAll->Add(hDY);
//   hAll->Add(hWJ);
//   hAll->Add(hST);
//   hAll->Add(hTT);
//   if(isDataDrivenQCD) hQCD_mc = getDataDrivenQCD(dir, histname, qcd_sf);
//   hAll->Add(hQCD_mc);
//   return hAll;
// }

//// The above parts are taken from Ravindra's code

TH1D *GetUpDownHistDD(vector<TFile *> filelist, const char *syst, const char *updown, string histname)
{
  TH1D *h1 = 0x0;
  TH1D *hcf_nano[filelist.size()] ; //_nano_ttbar->Get(Form("TTbar/base/Iso/%s",histname.c_str()));
  const char *sample[] = {"TTbar", "singleTop", "Wjets", "DYjets", "VBFusion", "QCDdd"};
  
  for(unsigned int ifile=0; ifile < filelist.size() ; ifile++){
    //cout << filelist[ifile]->GetName() << endl; 
    TString fname = filelist[ifile]->GetName();
    for(int isample = 0 ; isample < 6; isample++)
      if(fname.Contains(sample[isample])){
	hcf_nano[ifile]	= (TH1D *)filelist[ifile]->Get(Form("%s/%s%s/Iso/%s",sample[isample],syst,updown,histname.c_str()));
	if(histname.find("_mjj_")!=string::npos and strcmp(sample[isample],"QCDdd")!=0)
	  hcf_nano[ifile]->Rebin(rebin);
      }
  }
  h1 = (TH1D *)hcf_nano[0]->Clone(Form("%s%s",syst,updown));
  for(unsigned int ifile=1; ifile < filelist.size() ; ifile++)
    h1->Add(hcf_nano[ifile]);
  
  return h1;
}

TH1D *GetUpDownHistMC(vector<TFile *> filelist, const char *syst, const char *updown, string histname, bool isMu)
{

  TH1D *h1 = 0x0;
  TH1D *hcf_nano[filelist.size()] ; //_nano_ttbar->Get(Form("TTbar/base/Iso/%s",histname.c_str()));
  const char *sample1[] = {"TTbar", "singleTop", "Wjets", "DYjets", "VBFusion", "MCQCDMu"};
  const char *sample2[] = {"TTbar", "singleTop", "Wjets", "DYjets", "VBFusion", "MCQCDEle"};
  
  for(unsigned int ifile=0; ifile < filelist.size() ; ifile++){
    //cout << filelist[ifile]->GetName() << endl; 
    TString fname = filelist[ifile]->GetName();
    for(int isample = 0 ; isample < 6; isample++){
      const char *sample = (isMu) ? sample1[isample] : sample2[isample] ;
      if(fname.Contains(sample))
	hcf_nano[ifile]	= (TH1D *)filelist[ifile]->Get(Form("%s/%s%s/Iso/%s",sample,syst,updown,histname.c_str()));
    }
  }
  h1 = (TH1D *)hcf_nano[0]->Clone(Form("%s%s",syst,updown));
  for(unsigned int ifile=1; ifile < filelist.size() ; ifile++)
    h1->Add(hcf_nano[ifile]);
  
  return h1;
}
