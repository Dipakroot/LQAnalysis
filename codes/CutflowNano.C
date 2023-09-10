/**********************************************************************
 Created on : 25/07/2021
 Purpose    : Plot the cut flow histogram
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

#include <iostream>

using namespace std;

int CutflowNano()
{
  
  
  int year = 2017;
  bool isMu = 1;
  const char* cutflow = (isMu) ? "_cutflow_mu" : "_cutflow_ele";
  const char* cutflowUS = (isMu) ? "_cutflowUS_mu" : "_cutflowUS_ele";
  
  const char* dir = "proof_v26_PAGAug2";
  //const char* dir = "proof_v26_KinFit";
  //const char* dir = "proof_v26_DifflPlots";
  //const char* dir = "proof_v26_btagL";
  //const char* dir = "proof_v26_btagT";
  //const char* dir = "proof_v26_NanoAOD";
  const char* datafile = (isMu) ? Form("root_files/%s/%d/DataMu_weight_%d.root",dir,year,year) : Form("root_files/%s/%d/DataEle_weight_%d.root",dir,year,year) ;
  const char* qcdfile = (isMu) ? Form("root_files/%s/%d/MCQCDMu_weight_%d.root",dir,year,year) : Form("root_files/%s/%d/MCQCDEle_weight_%d.root",dir,year,year) ;
  TFile *fin_nano_data	= TFile::Open(datafile);
  TFile *fin_nano_sig = 0x0 ;
  if(year == 2016)
    fin_nano_sig	= TFile::Open(Form("root_files/%s/%d/HplusM120_weight_%d.root",dir,year,year));
  TFile *fin_nano_ttbar = TFile::Open(Form("root_files/%s/%d/TTbar_weight_%d.root",dir,year,year));
  TFile *fin_nano_stop	= TFile::Open(Form("root_files/%s/%d/singleTop_weight_%d.root",dir,year,year));
  TFile *fin_nano_wjets	= TFile::Open(Form("root_files/%s/%d/Wjets_weight_%d.root",dir,year,year));
  TFile *fin_nano_dyjets = TFile::Open(Form("root_files/%s/%d/DYjets_weight_%d.root",dir,year,year));
  TFile *fin_nano_vbf	= TFile::Open(Form("root_files/%s/%d/VBFusion_weight_%d.root",dir,year,year));
  TFile *fin_nano_qcd	= TFile::Open(qcdfile);
  TFile *fin_mini_qcd	= TFile::Open("/Data/CMS-Software/local/CMSSW_8_0_28/src/Analysis/stack/HIG-18-021_PRD_Histograms_Ele/all_QCD.root");

  // // MiniAOD Final
  // const char* dir = "local_v26_Ele";
  // const char* datafile = (isMu) ? Form("root_files/%s/DataMu_weight.root",dir) : Form("root_files/%s/DataEle_weight.root",dir) ;
  // const char* qcdfile = (isMu) ? Form("root_files/%s/MCQCDMu_weight.root",dir) : Form("root_files/%s/MCQCDEle_weight.root",dir) ;
  // TFile *fin_nano_data	= TFile::Open(datafile);
  // TFile *fin_nano_sig	= TFile::Open("root_files/local_v26_Ele/HplusM120_weight.root");
  // TFile *fin_nano_ttbar = TFile::Open("root_files/local_v26_Ele/TTbar_weight.root");
  // TFile *fin_nano_stop	= TFile::Open("root_files/local_v26_Ele/singleTop_weight.root");
  // TFile *fin_nano_wjets	= TFile::Open("root_files/local_v26_Ele/Wjets_weight.root");
  // //TFile *fin_nano_wjets	= TFile::Open("root_files/local_v26_Ele/Wjets_weight_2016.root");
  // TFile *fin_nano_dyjets = TFile::Open("root_files/local_v26_Ele/DYjets_weight.root");
  // TFile *fin_nano_vbf	= TFile::Open("root_files/local_v26_Ele/VBFusion_weight.root");
  // TFile *fin_nano_qcd	= TFile::Open(qcdfile);
  // TFile *fin_mini_qcd	= TFile::Open("/Data/CMS-Software/local/CMSSW_8_0_28/src/Analysis/stack/HIG-18-021_PRD_Histograms_Ele/all_QCD.root");


  TH1D *hcf_nano_data	= (TH1D *)fin_nano_data->Get(cutflowUS);
  TH1D *hcf_nano_sig = 0x0 ;
  if(year == 2016)
    hcf_nano_sig	= (TH1D *)fin_nano_sig->Get(cutflow);
  TH1D *hcf_nano_ttbar	= (TH1D *)fin_nano_ttbar->Get(cutflow);
  TH1D *hcf_nano_stop	= (TH1D *)fin_nano_stop->Get(cutflow); 
  TH1D *hcf_nano_wjets	= (TH1D *)fin_nano_wjets->Get(cutflow);
  TH1D *hcf_nano_dyjets	= (TH1D *)fin_nano_dyjets->Get(cutflow);
  TH1D *hcf_nano_vbf	= (TH1D *)fin_nano_vbf->Get(cutflow);
  TH1D *hcf_nano_qcd	= (TH1D *)fin_nano_qcd->Get(cutflow);
  TH1F *hcf_mini_qcd	= (TH1F *)fin_mini_qcd->Get("base/Iso/cutflow");
  // TH1D *hcf_nano_qcd	= (TH1D *)hcf_nano_vbf->Clone("hcf_nano_qcd");
  // for (int ibin=2;ibin<hcf_nano_qcd->GetNbinsX();ibin++)
  //   hcf_nano_qcd->SetBinContent(ibin, hcf_mini_qcd->GetBinContent(ibin-1));
  

  // hcf_nano_data->SetBinContent(2,hcf_nano_data->GetBinContent(0));
  // hcf_nano_sig->SetBinContent(2,hcf_nano_sig->GetBinContent(0));
  // hcf_nano_ttbar->SetBinContent(2,hcf_nano_ttbar->GetBinContent(0));
  // hcf_nano_stop->SetBinContent(2,hcf_nano_stop->GetBinContent(0));
  // hcf_nano_wjets->SetBinContent(2,hcf_nano_wjets->GetBinContent(0));
  // hcf_nano_dyjets->SetBinContent(2,hcf_nano_dyjets->GetBinContent(0));
  // hcf_nano_vbf->SetBinContent(2,hcf_nano_vbf->GetBinContent(0));

  //cout << "Wjets  : " << hcf_nano_wjets->GetBinContent(1) << endl;
  
  hcf_nano_data->SetBinContent(1,0.0);
  if(year == 2016)
    hcf_nano_sig->SetBinContent(1,0.0);
  hcf_nano_ttbar->SetBinContent(1,0.0);
  hcf_nano_stop->SetBinContent(1,0.0);
  hcf_nano_wjets->SetBinContent(1,0.0);
  hcf_nano_dyjets->SetBinContent(1,0.0);
  hcf_nano_vbf->SetBinContent(1,0.0);
  hcf_nano_qcd->SetBinContent(1,0.0);
  
  TH1D *hcf_nano_bkg = (TH1D *)hcf_nano_ttbar->Clone("Bkg");
  hcf_nano_bkg->Add(hcf_nano_stop);
  hcf_nano_bkg->Add(hcf_nano_wjets);
  hcf_nano_bkg->Add(hcf_nano_dyjets);
  hcf_nano_bkg->Add(hcf_nano_vbf);
  hcf_nano_bkg->Add(hcf_nano_qcd);
  
  int WeightedCounts(int, TH1D *, TH1D *, TH1D *, TH1D *, TH1D *, TH1D *, TH1D *, TH1D *, TH1D *);
  WeightedCounts(year, hcf_nano_data, hcf_nano_bkg, hcf_nano_sig, hcf_nano_ttbar, hcf_nano_stop, hcf_nano_wjets, hcf_nano_dyjets, hcf_nano_vbf, hcf_nano_qcd);
  
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

  hcf_nano_wjets->SetFillColor(kYellow);

  hcf_nano_dyjets->SetFillColor(kOrange+1);
  
  hcf_nano_vbf->SetFillColor(kGreen+2);

  hcf_nano_qcd->SetFillColor(kRed);
  
  THStack *hs = new THStack("hs","");
  hs->Add(hcf_nano_vbf);
  hs->Add(hcf_nano_dyjets);
  hs->Add(hcf_nano_wjets);
  hs->Add(hcf_nano_qcd);
  hs->Add(hcf_nano_stop);
  hs->Add(hcf_nano_ttbar);

  TLegend *leg = new TLegend(0.6962751,0.5611814,0.8925501,0.8924051);
  leg->SetFillColor(10);
  leg->AddEntry(hcf_nano_data, Form("Data") ,"lp");
  leg->AddEntry(hcf_nano_ttbar, Form("#it{t}#bar{#it{t}}") ,"f");
  leg->AddEntry(hcf_nano_stop, Form("Single #it{t}") ,"f");
  leg->AddEntry(hcf_nano_wjets, Form("#it{W} + jets") ,"f");
  leg->AddEntry(hcf_nano_dyjets, Form("#it{Z}/#gamma + jets") ,"f");
  leg->AddEntry(hcf_nano_vbf, Form("VV") ,"f");
  leg->AddEntry(hcf_nano_qcd, Form("QCD") ,"f");
  if(year == 2016)
    leg->AddEntry(hcf_nano_sig, Form("m_{H^{+}} = 120 GeV") ,"l");
  
  const char *cutnames[10] = {"Trigger", Form("Nof #mu = 1"), "No. of jets #geq 4", "MET #geq 20 GeV", "No. of #it{b}-jets #geq 2", "KinFit Sel.", "", "" ,"",""};
  for (int ibin=2;ibin<hcf_nano_data->GetNbinsX();ibin++){
    hcf_nano_data->GetXaxis()->SetBinLabel(ibin, cutnames[ibin-2]);
  }

  hcf_nano_data->SetMinimum(1.0e-1);
  hcf_nano_data->SetMaximum(1.0e12);
  //hcf_nano_data->SetMaximum(1.0e9);
  

  TCanvas *c1 = new TCanvas("c1","c1");
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  c1->SetLogy();
  c1->SetTickx();
  c1->SetTicky();
  hcf_nano_data->Draw("e1p");
  hs->Draw("same hist");
  // hcf_nano_qcd->Draw("same hist");
  // hcf_nano_ttbar->Draw("same hist");
  // hcf_nano_stop->Draw("same hist");
  // hcf_nano_wjets->Draw("same hist");
  // hcf_nano_dyjets->Draw("same hist");
  // hcf_nano_vbf->Draw("same hist");
  //hcf_nano_stop->Draw("same hist");
  if(year == 2016)
    hcf_nano_sig->Draw("same hist");
  hcf_nano_data->Draw("e1p same");
  leg->Draw();
  c1->Update();

  return true;
}

int WeightedCounts(int year, TH1D *hcf_nano_data, TH1D *hcf_nano_bkg, TH1D *hcf_nano_sig, TH1D *hcf_nano_ttbar, 
		   TH1D *hcf_nano_stop,TH1D *hcf_nano_wjets, TH1D *hcf_nano_dyjets, TH1D *hcf_nano_vbf, TH1D *hcf_nano_qcd)
{
  
  bool isDetail = 0 ;
  
  if (isDetail){

    TFile *fin = TFile::Open("/Data/CMS-Software/local/CMSSW_8_0_28/src/Analysis/stack/HIG-18-021_PRD_Histograms_Ele/all_Hplus120.root");
    TH1F *hMAODCF = (TH1F *)fin->Get("base/Iso/cutflow");
    printf("Signal Integral & ");
    for (int ibin=2;ibin<hcf_nano_sig->GetNbinsX();ibin++){
      if(hcf_nano_sig->GetBinContent(ibin)>0.0 and hcf_nano_sig->GetBinContent(ibin+1)>0.0){
	if(hcf_nano_sig->GetBinContent(ibin)>1e6){
	  printf("%.4e (%.4e, %4.2f\\%%)& ",hcf_nano_sig->GetBinContent(ibin), hMAODCF->GetBinContent(ibin-1), 
		 100.*(hcf_nano_sig->GetBinContent(ibin)-hMAODCF->GetBinContent(ibin-1))/hMAODCF->GetBinContent(ibin-1));
	}else{
	  printf("%.1f (%.1f, %4.2f\\%%)& ",hcf_nano_sig->GetBinContent(ibin), hMAODCF->GetBinContent(ibin-1),
		 100.*(hcf_nano_sig->GetBinContent(ibin)-hMAODCF->GetBinContent(ibin-1))/hMAODCF->GetBinContent(ibin-1));
	}
      }else if(hcf_nano_sig->GetBinContent(ibin)>0.0 and TMath::AreEqualAbs(hcf_nano_sig->GetBinContent(ibin+1),0.0,1.e-5)){
	printf("%.1f (%.1f, %4.2f\\%%)\\\\\\hline ",hcf_nano_sig->GetBinContent(ibin), hMAODCF->GetBinContent(ibin-1),
	       100.*(hcf_nano_sig->GetBinContent(ibin)-hMAODCF->GetBinContent(ibin-1))/hMAODCF->GetBinContent(ibin-1));
      }
    }
    hMAODCF->Delete();
    fin->Close();
    delete fin;
    printf("\n");

    fin = TFile::Open("/Data/CMS-Software/local/CMSSW_8_0_28/src/Analysis/stack/HIG-18-021_PRD_Histograms_Ele/all_TTJetsP.root");
    hMAODCF = (TH1F *)fin->Get("base/Iso/cutflow");
    printf("SM $t\\bar{t}$ & ");
    for (int ibin=2;ibin<hcf_nano_ttbar->GetNbinsX();ibin++){
      if(hcf_nano_ttbar->GetBinContent(ibin)>0.0 and hcf_nano_ttbar->GetBinContent(ibin+1)>0.0){
	if(hcf_nano_ttbar->GetBinContent(ibin)>1e6){
	  printf("%.4e (%.4e, %4.2f\\%%)& ",hcf_nano_ttbar->GetBinContent(ibin), hMAODCF->GetBinContent(ibin-1), 
		 100.*(hcf_nano_ttbar->GetBinContent(ibin)-hMAODCF->GetBinContent(ibin-1))/hMAODCF->GetBinContent(ibin-1));
	}else{
	  printf("%.1f (%.1f, %4.2f\\%%)& ",hcf_nano_ttbar->GetBinContent(ibin), hMAODCF->GetBinContent(ibin-1),
		 100.*(hcf_nano_ttbar->GetBinContent(ibin)-hMAODCF->GetBinContent(ibin-1))/hMAODCF->GetBinContent(ibin-1));
	}
      }else if(hcf_nano_ttbar->GetBinContent(ibin)>0.0 and TMath::AreEqualAbs(hcf_nano_ttbar->GetBinContent(ibin+1),0.0,1.e-5)){
	printf("%.1f (%.1f, %4.2f\\%%)\\\\\\hline ",hcf_nano_ttbar->GetBinContent(ibin), hMAODCF->GetBinContent(ibin-1),
	       100.*(hcf_nano_ttbar->GetBinContent(ibin)-hMAODCF->GetBinContent(ibin-1))/hMAODCF->GetBinContent(ibin-1));
      }
    }
    hMAODCF->Delete();
    fin->Close();
    delete fin;
    printf("\n");
  
    fin = TFile::Open("/Data/CMS-Software/local/CMSSW_8_0_28/src/Analysis/stack/HIG-18-021_PRD_Histograms_Ele/all_ST.root");
    hMAODCF = (TH1F *)fin->Get("base/Iso/cutflow");
    printf("Single $t$ & ");
    for (int ibin=2;ibin<hcf_nano_stop->GetNbinsX();ibin++){
      if(hcf_nano_stop->GetBinContent(ibin)>0.0 and hcf_nano_stop->GetBinContent(ibin+1)>0.0){
	if(hcf_nano_stop->GetBinContent(ibin)>1e6){
	  printf("%.4e (%.4e, %4.2f\\%%)& ",hcf_nano_stop->GetBinContent(ibin), hMAODCF->GetBinContent(ibin-1), 
		 100.*(hcf_nano_stop->GetBinContent(ibin)-hMAODCF->GetBinContent(ibin-1))/hMAODCF->GetBinContent(ibin-1));
	}else{
	  printf("%.1f (%.1f, %4.2f\\%%)& ",hcf_nano_stop->GetBinContent(ibin), hMAODCF->GetBinContent(ibin-1),
		 100.*(hcf_nano_stop->GetBinContent(ibin)-hMAODCF->GetBinContent(ibin-1))/hMAODCF->GetBinContent(ibin-1));
	}
      }else if(hcf_nano_stop->GetBinContent(ibin)>0.0 and TMath::AreEqualAbs(hcf_nano_stop->GetBinContent(ibin+1),0.0,1.e-5)){
	printf("%.1f (%.1f, %4.2f\\%%)\\\\\\hline ",hcf_nano_stop->GetBinContent(ibin), hMAODCF->GetBinContent(ibin-1),
	       100.*(hcf_nano_stop->GetBinContent(ibin)-hMAODCF->GetBinContent(ibin-1))/hMAODCF->GetBinContent(ibin-1));
      }
    }
    hMAODCF->Delete();
    fin->Close();
    delete fin;
    printf("\n");

    fin = TFile::Open("/Data/CMS-Software/local/CMSSW_8_0_28/src/Analysis/stack/HIG-18-021_PRD_Histograms_Ele/all_WJets.root");
    hMAODCF = (TH1F *)fin->Get("base/Iso/cutflow");
    printf("W + jets & ");
    for (int ibin=2;ibin<hcf_nano_wjets->GetNbinsX();ibin++){
      if(hcf_nano_wjets->GetBinContent(ibin)>0.0 and hcf_nano_wjets->GetBinContent(ibin+1)>0.0){
	if(hcf_nano_wjets->GetBinContent(ibin)>1e6){
	  printf("%.4e (%.4e, %4.2f\\%%)& ",hcf_nano_wjets->GetBinContent(ibin), hMAODCF->GetBinContent(ibin-1), 
		 100.*(hcf_nano_wjets->GetBinContent(ibin)-hMAODCF->GetBinContent(ibin-1))/hMAODCF->GetBinContent(ibin-1));
	}else{
	  printf("%.1f (%.1f, %4.2f\\%%)& ",hcf_nano_wjets->GetBinContent(ibin), hMAODCF->GetBinContent(ibin-1),
		 100.*(hcf_nano_wjets->GetBinContent(ibin)-hMAODCF->GetBinContent(ibin-1))/hMAODCF->GetBinContent(ibin-1));
	}
      }else if(hcf_nano_wjets->GetBinContent(ibin)>0.0 and TMath::AreEqualAbs(hcf_nano_wjets->GetBinContent(ibin+1),0.0,1.e-5)){
	printf("%.1f (%.1f, %4.2f\\%%)\\\\\\hline ",hcf_nano_wjets->GetBinContent(ibin), hMAODCF->GetBinContent(ibin-1),
	       100.*(hcf_nano_wjets->GetBinContent(ibin)-hMAODCF->GetBinContent(ibin-1))/hMAODCF->GetBinContent(ibin-1));
      }
    }
    hMAODCF->Delete();
    fin->Close();
    delete fin;
    printf("\n");


    fin = TFile::Open("/Data/CMS-Software/local/CMSSW_8_0_28/src/Analysis/stack/HIG-18-021_PRD_Histograms_Ele/all_DY.root");
    hMAODCF = (TH1F *)fin->Get("base/Iso/cutflow");
    printf("Z/$\\gamma$ + jets & ");
    for (int ibin=2;ibin<hcf_nano_dyjets->GetNbinsX();ibin++){
      if(hcf_nano_dyjets->GetBinContent(ibin)>0.0 and hcf_nano_dyjets->GetBinContent(ibin+1)>0.0){
	if(hcf_nano_dyjets->GetBinContent(ibin)>1e6){
	  printf("%.4e (%.4e, %4.2f\\%%)& ",hcf_nano_dyjets->GetBinContent(ibin), hMAODCF->GetBinContent(ibin-1), 
		 100.*(hcf_nano_dyjets->GetBinContent(ibin)-hMAODCF->GetBinContent(ibin-1))/hMAODCF->GetBinContent(ibin-1));
	}else{
	  printf("%.1f (%.1f, %4.2f\\%%)& ",hcf_nano_dyjets->GetBinContent(ibin), hMAODCF->GetBinContent(ibin-1),
		 100.*(hcf_nano_dyjets->GetBinContent(ibin)-hMAODCF->GetBinContent(ibin-1))/hMAODCF->GetBinContent(ibin-1));
	}
      }else if(hcf_nano_dyjets->GetBinContent(ibin)>0.0 and TMath::AreEqualAbs(hcf_nano_dyjets->GetBinContent(ibin+1),0.0,1.e-5)){
	printf("%.1f (%.1f, %4.2f\\%%)\\\\\\hline ",hcf_nano_dyjets->GetBinContent(ibin), hMAODCF->GetBinContent(ibin-1),
	       100.*(hcf_nano_dyjets->GetBinContent(ibin)-hMAODCF->GetBinContent(ibin-1))/hMAODCF->GetBinContent(ibin-1));
      }
    }
    hMAODCF->Delete();
    fin->Close();
    delete fin;
    printf("\n");

    fin = TFile::Open("/Data/CMS-Software/local/CMSSW_8_0_28/src/Analysis/stack/HIG-18-021_PRD_Histograms_Ele/all_VV.root");
    hMAODCF = (TH1F *)fin->Get("base/Iso/cutflow");
    printf("VV & ");
    for (int ibin=2;ibin<hcf_nano_vbf->GetNbinsX();ibin++){
      if(hcf_nano_vbf->GetBinContent(ibin)>0.0 and hcf_nano_vbf->GetBinContent(ibin+1)>0.0){
	if(hcf_nano_vbf->GetBinContent(ibin)>1e6){
	  printf("%.4e (%.4e, %4.2f\\%%)& ",hcf_nano_vbf->GetBinContent(ibin), hMAODCF->GetBinContent(ibin-1), 
		 100.*(hcf_nano_vbf->GetBinContent(ibin)-hMAODCF->GetBinContent(ibin-1))/hMAODCF->GetBinContent(ibin-1));
	}else{
	  printf("%.1f (%.1f, %4.2f\\%%)& ",hcf_nano_vbf->GetBinContent(ibin), hMAODCF->GetBinContent(ibin-1),
		 100.*(hcf_nano_vbf->GetBinContent(ibin)-hMAODCF->GetBinContent(ibin-1))/hMAODCF->GetBinContent(ibin-1));
	}
      }else if(hcf_nano_vbf->GetBinContent(ibin)>0.0 and TMath::AreEqualAbs(hcf_nano_vbf->GetBinContent(ibin+1),0.0,1.e-5)){
	printf("%.1f (%.1f, %4.2f\\%%)\\\\\\hline ",hcf_nano_vbf->GetBinContent(ibin), hMAODCF->GetBinContent(ibin-1),
	       100.*(hcf_nano_vbf->GetBinContent(ibin)-hMAODCF->GetBinContent(ibin-1))/hMAODCF->GetBinContent(ibin-1));
      }
    }
    hMAODCF->Delete();
    fin->Close();
    delete fin;
    printf("\n");

    int lastbin = 7 ;
    TFile *finQCD = TFile::Open("/Data/CMS-Software/local/CMSSW_8_0_28/src/Analysis/stack/HIG-18-021_PRD_Histograms_Ele/all_QCD.root");
    hMAODCF = (TH1F *)finQCD->Get("base/Iso/cutflow");
    TH1F *hMiniBkg = (TH1F *)hMAODCF->Clone("MiniAOD_Bkg");
    printf("MiniAOD QCD & ");
    //for (int ibin=2;ibin<hcf_nano_qcd->GetNbinsX();ibin++){
    for (int ibin=2;ibin<lastbin;ibin++){
      if(hcf_nano_qcd->GetBinContent(ibin)>0.0 and hcf_nano_qcd->GetBinContent(ibin+1)>0.0 and ibin<=lastbin-2){
	if(hcf_nano_qcd->GetBinContent(ibin)>1e6){
	  printf("%.4e (%.4e, %4.2f\\%%)& ",hcf_nano_qcd->GetBinContent(ibin), hMAODCF->GetBinContent(ibin-1), 
		 100.*(hcf_nano_qcd->GetBinContent(ibin)-hMAODCF->GetBinContent(ibin-1))/hMAODCF->GetBinContent(ibin-1));
	}else{
	  printf("%.1f (%.1f, %4.2f\\%%)& ",hcf_nano_qcd->GetBinContent(ibin), hMAODCF->GetBinContent(ibin-1),
		 100.*(hcf_nano_qcd->GetBinContent(ibin)-hMAODCF->GetBinContent(ibin-1))/hMAODCF->GetBinContent(ibin-1));
	}
      }else if((hcf_nano_qcd->GetBinContent(ibin)>0.0 and TMath::AreEqualAbs(hcf_nano_qcd->GetBinContent(ibin+1),0.0,1.e-5)) or ibin==lastbin-1){
	printf("%.1f (%.1f, %4.2f\\%%)\\\\\\hline ",hcf_nano_qcd->GetBinContent(ibin), hMAODCF->GetBinContent(ibin-1),
	       100.*(hcf_nano_qcd->GetBinContent(ibin)-hMAODCF->GetBinContent(ibin-1))/hMAODCF->GetBinContent(ibin-1));
      }
    }
    hMAODCF->Delete();
    printf("\n");

    TFile *finMC = TFile::Open("/Data/CMS-Software/local/CMSSW_8_0_28/src/Analysis/stack/HIG-18-021_PRD_Histograms_Ele/all_MC.root");
    hMAODCF = (TH1F *)finMC->Get("base/Iso/cutflow");
    hMiniBkg->Add(hMAODCF);
    printf("ALL BKG & ");
    //for (int ibin=2;ibin<hcf_nano_bkg->GetNbinsX();ibin++){
    for (int ibin=2;ibin<lastbin;ibin++){
      if(hcf_nano_bkg->GetBinContent(ibin)>0.0 and hcf_nano_bkg->GetBinContent(ibin+1)>0.0  and ibin<=lastbin-2){
	if(hcf_nano_bkg->GetBinContent(ibin)>1e6){
	  printf("%.4e (%.4e, %4.2f\\%%)& ",hcf_nano_bkg->GetBinContent(ibin), hMiniBkg->GetBinContent(ibin-1), 
		 100.*(hcf_nano_bkg->GetBinContent(ibin)-hMiniBkg->GetBinContent(ibin-1))/hMiniBkg->GetBinContent(ibin-1));
	}else{
	  printf("%.1f (%.1f, %4.2f\\%%)& ",hcf_nano_bkg->GetBinContent(ibin), hMiniBkg->GetBinContent(ibin-1),
		 100.*(hcf_nano_bkg->GetBinContent(ibin)-hMiniBkg->GetBinContent(ibin-1))/hMiniBkg->GetBinContent(ibin-1));
	}
      }else if((hcf_nano_bkg->GetBinContent(ibin)>0.0 and TMath::AreEqualAbs(hcf_nano_bkg->GetBinContent(ibin+1),0.0,1.e-5))  or ibin==lastbin-1){
	printf("%.1f (%.1f, %4.2f\\%%)\\\\\\hline ",hcf_nano_bkg->GetBinContent(ibin), hMiniBkg->GetBinContent(ibin-1),
	       100.*(hcf_nano_bkg->GetBinContent(ibin)-hMiniBkg->GetBinContent(ibin-1))/hMiniBkg->GetBinContent(ibin-1));
      }
    }
    hMAODCF->Delete();
    printf("\n");

    
    fin = TFile::Open("/Data/CMS-Software/local/CMSSW_8_0_28/src/Analysis/stack/HIG-18-021_PRD_Histograms_Ele/all_Data.root");
    hMAODCF = (TH1F *)fin->Get("base/Iso/cutflow");
    printf("Data & ");
    for (int ibin=2;ibin<hcf_nano_data->GetNbinsX();ibin++){
      if(hcf_nano_data->GetBinContent(ibin)>0.0 and hcf_nano_data->GetBinContent(ibin+1)>0.0){
	if(hcf_nano_data->GetBinContent(ibin)>1e6){
	  printf("%.4e (%.4e, %4.2f\\%%)& ",hcf_nano_data->GetBinContent(ibin), hMAODCF->GetBinContent(ibin-1), 
		 100.*(hcf_nano_data->GetBinContent(ibin)-hMAODCF->GetBinContent(ibin-1))/hMAODCF->GetBinContent(ibin-1));
	}else{
	  printf("%.1f (%.1f, %4.2f\\%%)& ",hcf_nano_data->GetBinContent(ibin), hMAODCF->GetBinContent(ibin-1),
		 100.*(hcf_nano_data->GetBinContent(ibin)-hMAODCF->GetBinContent(ibin-1))/hMAODCF->GetBinContent(ibin-1));
	}
      }else if(hcf_nano_data->GetBinContent(ibin)>0.0 and TMath::AreEqualAbs(hcf_nano_data->GetBinContent(ibin+1),0.0,1.e-5)){
	printf("%.1f (%.1f, %4.2f\\%%)\\\\\\hline ",hcf_nano_data->GetBinContent(ibin), hMAODCF->GetBinContent(ibin-1),
	       100.*(hcf_nano_data->GetBinContent(ibin)-hMAODCF->GetBinContent(ibin-1))/hMAODCF->GetBinContent(ibin-1));
      }
    }
    printf("\n");

    printf("Data/Bkg & ");
    for (int ibin=2;ibin<hcf_nano_data->GetNbinsX();ibin++){
      if(hcf_nano_data->GetBinContent(ibin)>0.0 and hcf_nano_data->GetBinContent(ibin+1)>0.0){
	  printf("%.4f (%.4f, %4.2f\\%%)& ",hcf_nano_data->GetBinContent(ibin)/hcf_nano_bkg->GetBinContent(ibin), 
		 hMAODCF->GetBinContent(ibin-1)/hMiniBkg->GetBinContent(ibin-1),
		 100.*(hcf_nano_data->GetBinContent(ibin)/hcf_nano_bkg->GetBinContent(ibin) - hMAODCF->GetBinContent(ibin-1)/hMiniBkg->GetBinContent(ibin-1))*hMiniBkg->GetBinContent(ibin-1)/hMAODCF->GetBinContent(ibin-1));
      }else if(hcf_nano_data->GetBinContent(ibin)>0.0 and TMath::AreEqualAbs(hcf_nano_data->GetBinContent(ibin+1),0.0,1.e-5)){
	printf("%.4f (%.4f, %4.2f\\%%)\\\\\\hline ",hcf_nano_data->GetBinContent(ibin)/hcf_nano_bkg->GetBinContent(ibin), 
	       hMAODCF->GetBinContent(ibin-1)/hMiniBkg->GetBinContent(ibin-1),
	       100.*(hcf_nano_data->GetBinContent(ibin)/hcf_nano_bkg->GetBinContent(ibin) - hMAODCF->GetBinContent(ibin-1)/hMiniBkg->GetBinContent(ibin-1))*hMiniBkg->GetBinContent(ibin-1)/hMAODCF->GetBinContent(ibin-1));
      }
    }
    printf("\n");




    hMAODCF->Delete();
    fin->Close();
    delete fin;
    
    finMC->Close();
    delete finMC;

    finQCD->Close();
    delete finQCD;



  }else{

    if(year==2016){
      TFile *fin = TFile::Open("/Data/CMS-Software/local/CMSSW_8_0_28/src/Analysis/stack/HIG-18-021_PRD_Histograms_Ele/all_Hplus120.root");
      TH1F *hMAODCF = (TH1F *)fin->Get("base/Iso/cutflow");
      printf("Signal Integral & ");
      for (int ibin=2;ibin<hcf_nano_sig->GetNbinsX();ibin++){
	if(hcf_nano_sig->GetBinContent(ibin)>0.0 and hcf_nano_sig->GetBinContent(ibin+1)>0.0){
	  if(hcf_nano_sig->GetBinContent(ibin)>1e6){
	    printf("%.4e & ",hcf_nano_sig->GetBinContent(ibin));
	  }else{
	    printf("%.1f & ",hcf_nano_sig->GetBinContent(ibin));
	  }
	}else if(hcf_nano_sig->GetBinContent(ibin)>0.0 and TMath::AreEqualAbs(hcf_nano_sig->GetBinContent(ibin+1),0.0,1.e-5)){
	  printf("%.1f \\\\\\hline ",hcf_nano_sig->GetBinContent(ibin));

	}
      }
      hMAODCF->Delete();
      fin->Close();
      delete fin;
      printf("\n");
    }

    TFile *fin = TFile::Open("/Data/CMS-Software/local/CMSSW_8_0_28/src/Analysis/stack/HIG-18-021_PRD_Histograms_Ele/all_TTJetsP.root");
    TH1F *hMAODCF = (TH1F *)fin->Get("base/Iso/cutflow");
    printf("SM $t\\bar{t}$ & ");
    for (int ibin=2;ibin<hcf_nano_ttbar->GetNbinsX();ibin++){
      if(hcf_nano_ttbar->GetBinContent(ibin)>0.0 and hcf_nano_ttbar->GetBinContent(ibin+1)>0.0){
	if(hcf_nano_ttbar->GetBinContent(ibin)>1e6){
	  printf("%.4e & ",hcf_nano_ttbar->GetBinContent(ibin)); 
	}else{
	  printf("%.1f & ",hcf_nano_ttbar->GetBinContent(ibin));
	}
      }else if(hcf_nano_ttbar->GetBinContent(ibin)>0.0 and TMath::AreEqualAbs(hcf_nano_ttbar->GetBinContent(ibin+1),0.0,1.e-5)){
	printf("%.1f \\\\",hcf_nano_ttbar->GetBinContent(ibin));
      }
    }
    hMAODCF->Delete();
    fin->Close();
    delete fin;
    printf("\n");
  
    fin = TFile::Open("/Data/CMS-Software/local/CMSSW_8_0_28/src/Analysis/stack/HIG-18-021_PRD_Histograms_Ele/all_ST.root");
    hMAODCF = (TH1F *)fin->Get("base/Iso/cutflow");
    printf("Single $t$ & ");
    for (int ibin=2;ibin<hcf_nano_stop->GetNbinsX();ibin++){
      if(hcf_nano_stop->GetBinContent(ibin)>0.0 and hcf_nano_stop->GetBinContent(ibin+1)>0.0){
	if(hcf_nano_stop->GetBinContent(ibin)>1e6){
	  printf("%.4e & ",hcf_nano_stop->GetBinContent(ibin)); 
	}else{
	  printf("%.1f & ",hcf_nano_stop->GetBinContent(ibin));
	}
      }else if(hcf_nano_stop->GetBinContent(ibin)>0.0 and TMath::AreEqualAbs(hcf_nano_stop->GetBinContent(ibin+1),0.0,1.e-5)){
	printf("%.1f \\\\ ",hcf_nano_stop->GetBinContent(ibin));
      }
    }
    hMAODCF->Delete();
    fin->Close();
    delete fin;
    printf("\n");

    fin = TFile::Open("/Data/CMS-Software/local/CMSSW_8_0_28/src/Analysis/stack/HIG-18-021_PRD_Histograms_Ele/all_WJets.root");
    hMAODCF = (TH1F *)fin->Get("base/Iso/cutflow");
    printf("W + jets & ");
    for (int ibin=2;ibin<hcf_nano_wjets->GetNbinsX();ibin++){
      if(hcf_nano_wjets->GetBinContent(ibin)>0.0 and hcf_nano_wjets->GetBinContent(ibin+1)>0.0){
	if(hcf_nano_wjets->GetBinContent(ibin)>1e6){
	  printf("%.4e & ",hcf_nano_wjets->GetBinContent(ibin)); 
	}else{
	  printf("%.1f & ",hcf_nano_wjets->GetBinContent(ibin));
	}
      }else if(hcf_nano_wjets->GetBinContent(ibin)>0.0 and TMath::AreEqualAbs(hcf_nano_wjets->GetBinContent(ibin+1),0.0,1.e-5)){
	printf("%.1f \\\\ ",hcf_nano_wjets->GetBinContent(ibin));
      }
    }
    hMAODCF->Delete();
    fin->Close();
    delete fin;
    printf("\n");


    fin = TFile::Open("/Data/CMS-Software/local/CMSSW_8_0_28/src/Analysis/stack/HIG-18-021_PRD_Histograms_Ele/all_DY.root");
    hMAODCF = (TH1F *)fin->Get("base/Iso/cutflow");
    printf("Z/$\\gamma$ + jets & ");
    for (int ibin=2;ibin<hcf_nano_dyjets->GetNbinsX();ibin++){
      if(hcf_nano_dyjets->GetBinContent(ibin)>0.0 and hcf_nano_dyjets->GetBinContent(ibin+1)>0.0){
	if(hcf_nano_dyjets->GetBinContent(ibin)>1e6){
	  printf("%.4e & ",hcf_nano_dyjets->GetBinContent(ibin)); 
	}else{
	  printf("%.1f & ",hcf_nano_dyjets->GetBinContent(ibin));
	}
      }else if(hcf_nano_dyjets->GetBinContent(ibin)>0.0 and TMath::AreEqualAbs(hcf_nano_dyjets->GetBinContent(ibin+1),0.0,1.e-5)){
	printf("%.1f \\\\ ",hcf_nano_dyjets->GetBinContent(ibin));
      }
    }
    hMAODCF->Delete();
    fin->Close();
    delete fin;
    printf("\n");

    fin = TFile::Open("/Data/CMS-Software/local/CMSSW_8_0_28/src/Analysis/stack/HIG-18-021_PRD_Histograms_Ele/all_VV.root");
    hMAODCF = (TH1F *)fin->Get("base/Iso/cutflow");
    printf("VV & ");
    for (int ibin=2;ibin<hcf_nano_vbf->GetNbinsX();ibin++){
      if(hcf_nano_vbf->GetBinContent(ibin)>0.0 and hcf_nano_vbf->GetBinContent(ibin+1)>0.0){
	if(hcf_nano_vbf->GetBinContent(ibin)>1e6){
	  printf("%.4e & ",hcf_nano_vbf->GetBinContent(ibin)); 
	}else{
	  printf("%.1f & ",hcf_nano_vbf->GetBinContent(ibin));
	}
      }else if(hcf_nano_vbf->GetBinContent(ibin)>0.0 and TMath::AreEqualAbs(hcf_nano_vbf->GetBinContent(ibin+1),0.0,1.e-5)){
	printf("%.1f \\\\ ",hcf_nano_vbf->GetBinContent(ibin));
      }
    }
    hMAODCF->Delete();
    fin->Close();
    delete fin;
    printf("\n");

    int lastbin = 7 ;
    TFile *finQCD = TFile::Open("/Data/CMS-Software/local/CMSSW_8_0_28/src/Analysis/stack/HIG-18-021_PRD_Histograms_Ele/all_QCD.root");
    hMAODCF = (TH1F *)finQCD->Get("base/Iso/cutflow");
    TH1F *hMiniBkg = (TH1F *)hMAODCF->Clone("MiniAOD_Bkg");
    printf("MC QCD & ");
    for (int ibin=2;ibin<hcf_nano_qcd->GetNbinsX();ibin++){
    //for (int ibin=2;ibin<lastbin;ibin++){
      if(hcf_nano_qcd->GetBinContent(ibin)>0.0 and hcf_nano_qcd->GetBinContent(ibin+1)>0.0){
	if(hcf_nano_qcd->GetBinContent(ibin)>1e6){
	  printf("%.4e & ",hcf_nano_qcd->GetBinContent(ibin));
	}else{
	  printf("%.1f & ",hcf_nano_qcd->GetBinContent(ibin));
	}
      }else if(hcf_nano_qcd->GetBinContent(ibin)>0.0 and TMath::AreEqualAbs(hcf_nano_qcd->GetBinContent(ibin+1),0.0,1.e-5)){
	printf("%.1f \\\\\\hline ",hcf_nano_qcd->GetBinContent(ibin));
      }
    }
    hMAODCF->Delete();
    printf("\n");

    // fin = TFile::Open("/Data/CMS-Software/local/CMSSW_8_0_28/src/Analysis/stack/HIG-18-021_PRD_Histograms_Ele/all_MC.root");
    // hMAODCF = (TH1F *)fin->Get("base/Iso/cutflow");
    // printf("ALL MC & ");
    // for (int ibin=2;ibin<hcf_nano_bkg->GetNbinsX();ibin++){
    //   if(hcf_nano_bkg->GetBinContent(ibin)>0.0 and hcf_nano_bkg->GetBinContent(ibin+1)>0.0){
    // 	if(hcf_nano_bkg->GetBinContent(ibin)>1e6){
    // 	  printf("%.4e & ",hcf_nano_bkg->GetBinContent(ibin)); 
    // 	}else{
    // 	  printf("%.1f & ",hcf_nano_bkg->GetBinContent(ibin));
    // 	}
    //   }else if(hcf_nano_bkg->GetBinContent(ibin)>0.0 and TMath::AreEqualAbs(hcf_nano_bkg->GetBinContent(ibin+1),0.0,1.e-5)){
    // 	printf("%.1f \\\\\\hline ",hcf_nano_bkg->GetBinContent(ibin));
    //   }
    // }
    // hMAODCF->Delete();
    // fin->Close();
    // delete fin;
    // printf("\n");

    printf("ALL BKG & ");
    for (int ibin=2;ibin<hcf_nano_bkg->GetNbinsX();ibin++){
    //for (int ibin=2;ibin<lastbin;ibin++){
      if(hcf_nano_bkg->GetBinContent(ibin)>0.0 and hcf_nano_bkg->GetBinContent(ibin+1)>0.0){
	if(hcf_nano_bkg->GetBinContent(ibin)>1e6){
	  printf("%.4e & ",hcf_nano_bkg->GetBinContent(ibin));
	}else{
	  printf("%.1f & ",hcf_nano_bkg->GetBinContent(ibin));
	}
      }else if(hcf_nano_bkg->GetBinContent(ibin)>0.0 and TMath::AreEqualAbs(hcf_nano_bkg->GetBinContent(ibin+1),0.0,1.e-5)){
	printf("%.1f \\\\\\hline ",hcf_nano_bkg->GetBinContent(ibin));
      }
    }
    printf("\n");

    fin = TFile::Open("/Data/CMS-Software/local/CMSSW_8_0_28/src/Analysis/stack/HIG-18-021_PRD_Histograms_Ele/all_Data.root");
    hMAODCF = (TH1F *)fin->Get("base/Iso/cutflow");
    printf("Data & ");
    for (int ibin=2;ibin<hcf_nano_data->GetNbinsX();ibin++){
      if(hcf_nano_data->GetBinContent(ibin)>0.0 and hcf_nano_data->GetBinContent(ibin+1)>0.0){
	if(hcf_nano_data->GetBinContent(ibin)>1e6){
	  printf("%.4e & ",hcf_nano_data->GetBinContent(ibin)); 
	}else{
	  printf("%.1f & ",hcf_nano_data->GetBinContent(ibin));
	}
      }else if(hcf_nano_data->GetBinContent(ibin)>0.0 and TMath::AreEqualAbs(hcf_nano_data->GetBinContent(ibin+1),0.0,1.e-5)){
	printf("%.1f \\\\\\hline ",hcf_nano_data->GetBinContent(ibin));
      }
    }
    hMAODCF->Delete();
    fin->Close();
    delete fin;
    printf("\n");

    printf("Data/Bkg & ");
    for (int ibin=2;ibin<hcf_nano_data->GetNbinsX();ibin++){
      if(hcf_nano_data->GetBinContent(ibin)>0.0 and hcf_nano_data->GetBinContent(ibin+1)>0.0){
	printf("%.4f & ",hcf_nano_data->GetBinContent(ibin)/hcf_nano_bkg->GetBinContent(ibin));
      }else if(hcf_nano_data->GetBinContent(ibin)>0.0 and TMath::AreEqualAbs(hcf_nano_data->GetBinContent(ibin+1),0.0,1.e-5)){
	printf("%.4f \\\\\\hline ",hcf_nano_data->GetBinContent(ibin)/hcf_nano_bkg->GetBinContent(ibin));
      }
    }
    printf("\n");

  }
   
  return true;
}
