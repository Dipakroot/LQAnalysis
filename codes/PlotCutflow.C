/**********************************************************************
 Created on : 14/06/2021
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

int PlotCutflow()
{
  
  // TFile *fin_nano_data	= TFile::Open("root_files/lxplus_proof_v14/DataMu_weights.root");
  // TFile *fin_nano_sig	= TFile::Open("root_files/lxplus_proof_v14/HplusM120_weights.root");
  // TFile *fin_nano_ttbar = TFile::Open("root_files/lxplus_proof_v14/TTbar_weights.root");
  //TFile *fin_nano_stop	= TFile::Open("root_files/lxplus_proof_v14/singleTop_weights.root");
  // TFile *fin_nano_wjets	= TFile::Open("root_files/lxplus_proof_v14/Wjets_weights.root");
  // TFile *fin_nano_dyjets = TFile::Open("root_files/lxplus_proof_v14/DYjets_weights.root");
  // TFile *fin_nano_vbf	= TFile::Open("root_files/lxplus_proof_v14/VBFusion_weights.root");
  
  //TFile *fin_nano_data	= TFile::Open("root_files/lxplus_v16/DataMu_weights.root");
  //TFile *fin_nano_sig	= TFile::Open("root_files/lxplus_v16/HplusM120_weights.root");
  //TFile *fin_nano_ttbar = TFile::Open("root_files/lxplus_v16/TTbar_weights.root");
  //TFile *fin_nano_stop	= TFile::Open("root_files/lxplus_v16/singleTop_weights.root");
  //TFile *fin_nano_wjets	= TFile::Open("root_files/lxplus_v16/Wjets_weights.root");
  //TFile *fin_nano_dyjets = TFile::Open("root_files/lxplus_v16/DYjets_weights.root");
  //TFile *fin_nano_vbf	= TFile::Open("root_files/lxplus_v16/VBFusion_weights.root");

  // // 3sigma cut w/o VC
  // TFile *fin_nano_data	= TFile::Open("root_files/lxplus_v20/DataMu_weights.root");
  // TFile *fin_nano_sig	= TFile::Open("root_files/lxplus_v20/HplusM120_weights.root");
  // TFile *fin_nano_ttbar = TFile::Open("root_files/lxplus_v20/TTbar_weights.root");
  // TFile *fin_nano_stop	= TFile::Open("root_files/lxplus_v20/singleTop_weights.root");
  // TFile *fin_nano_wjets	= TFile::Open("root_files/lxplus_v20/Wjets_weights.root");
  // TFile *fin_nano_dyjets = TFile::Open("root_files/lxplus_v20/DYjets_weights.root");
  // TFile *fin_nano_vbf	= TFile::Open("root_files/lxplus_v20/VBFusion_weights.root");

  // // 3sigma cut wt VC
  // TFile *fin_nano_data	= TFile::Open("root_files/lxplus_proof_v20_wtvc/DataMu_weights.root");
  // TFile *fin_nano_sig	= TFile::Open("root_files/lxplus_proof_v20_wtvc/HplusM120_weights.root");
  // TFile *fin_nano_ttbar = TFile::Open("root_files/lxplus_proof_v20_wtvc/TTbar_weights.root");
  // TFile *fin_nano_stop	= TFile::Open("root_files/lxplus_proof_v20_wtvc/singleTop_weights.root");
  // TFile *fin_nano_wjets	= TFile::Open("root_files/lxplus_proof_v20_wtvc/Wjets_weights.root");
  // TFile *fin_nano_dyjets = TFile::Open("root_files/lxplus_proof_v20_wtvc/DYjets_weights.root");
  // TFile *fin_nano_vbf	= TFile::Open("root_files/lxplus_proof_v20_wtvc/VBFusion_weights.root");

  // // // default cut wt VC
  // TFile *fin_nano_data	= TFile::Open("root_files/lxplus_proof_v21_wtvc/DataMu_weights.root");
  // TFile *fin_nano_sig	= TFile::Open("root_files/lxplus_proof_v21_wtvc/HplusM120_weights.root");
  // TFile *fin_nano_ttbar = TFile::Open("root_files/lxplus_proof_v21_wtvc/TTbar_weights.root");
  // TFile *fin_nano_stop	= TFile::Open("root_files/lxplus_proof_v21_wtvc/singleTop_weights.root");
  // TFile *fin_nano_wjets	= TFile::Open("root_files/lxplus_proof_v21_wtvc/Wjets_weights.root");
  // TFile *fin_nano_dyjets = TFile::Open("root_files/lxplus_proof_v21_wtvc/DYjets_weights.root");
  // TFile *fin_nano_vbf	= TFile::Open("root_files/lxplus_proof_v21_wtvc/VBFusion_weights.root");

  // // // default cut no VC
  // TFile *fin_nano_data	= TFile::Open("root_files/lxplus_proof_v21_novc/DataMu_weights.root");
  // TFile *fin_nano_sig	= TFile::Open("root_files/lxplus_proof_v21_novc/HplusM120_weights.root");
  // TFile *fin_nano_ttbar = TFile::Open("root_files/lxplus_proof_v21_novc/TTbar_weights.root");
  // //TFile *fin_nano_stop	= TFile::Open("root_files/lxplus_proof_v21_novc/singleTop_weights.root");
  // //TFile *fin_nano_stop	= TFile::Open("root_files/test_weights_6a8608_default.root");
  // TFile *fin_nano_stop	= TFile::Open("root_files/test_weights_9129abb_default.root");
  // TFile *fin_nano_wjets	= TFile::Open("root_files/lxplus_proof_v21_novc/Wjets_weights.root");
  // TFile *fin_nano_dyjets = TFile::Open("root_files/lxplus_proof_v21_novc/DYjets_weights.root");
  // TFile *fin_nano_vbf	= TFile::Open("root_files/lxplus_proof_v21_novc/VBFusion_weights.root");

  // // With b-jet correction efficiency file of default NanoAOD
  // TFile *fin_nano_data	= TFile::Open("root_files/lxplus_proof_v23/DataMu_weights.root");
  // TFile *fin_nano_sig	= TFile::Open("root_files/lxplus_proof_v23/HplusM120_weights.root");
  // TFile *fin_nano_ttbar = TFile::Open("root_files/lxplus_proof_v23/TTbar_weights.root");
  // TFile *fin_nano_stop	= TFile::Open("root_files/lxplus_proof_v23/singleTop_weights.root");
  // TFile *fin_nano_wjets	= TFile::Open("root_files/lxplus_proof_v23/Wjets_weights.root");
  // TFile *fin_nano_dyjets = TFile::Open("root_files/lxplus_proof_v23/DYjets_weights.root");
  // TFile *fin_nano_vbf	= TFile::Open("root_files/lxplus_proof_v23/VBFusion_weights.root");

  // // With b-jet correction efficiency file of miniAOD per sample
  // TFile *fin_nano_data	= TFile::Open("root_files/lxplus_proof_v23/DataMu_weights.root");
  // TFile *fin_nano_sig	= TFile::Open("root_files/local_v23/HplusM120_weights.root");
  // TFile *fin_nano_ttbar = TFile::Open("root_files/local_v23/TTbar_weights.root");
  // TFile *fin_nano_stop	= TFile::Open("root_files/local_v23/singleTop_weights.root");
  // TFile *fin_nano_wjets	= TFile::Open("root_files/local_v23/Wjets_weights.root");
  // TFile *fin_nano_dyjets = TFile::Open("root_files/local_v23/DYjets_weights.root");
  // TFile *fin_nano_vbf	= TFile::Open("root_files/local_v23/VBFusion_weights.root");
  // // With b-jet correction efficiency file of miniAOD per channel
  //TFile *fin_nano_wjets	= TFile::Open("root_files/local_v23/Wjets_weights_new.root");
  //TFile *fin_nano_dyjets = TFile::Open("root_files/local_v23/DYjets_weights_new.root");

  // // With b-jet correction efficiency file of NanoAOD per sample
  // TFile *fin_nano_data	= TFile::Open("root_files/lxplus_proof_v23/DataMu_weights.root");
  // TFile *fin_nano_sig	= TFile::Open("root_files/lxplus_proof_v24_sample/HplusM120_weights.root");
  // TFile *fin_nano_ttbar = TFile::Open("root_files/lxplus_proof_v24_sample/TTbar_weights.root");
  // TFile *fin_nano_stop	= TFile::Open("root_files/lxplus_proof_v24_sample/singleTop_weights.root");
  // TFile *fin_nano_wjets	= TFile::Open("root_files/lxplus_proof_v24_sample/Wjets_weights.root");
  // TFile *fin_nano_dyjets = TFile::Open("root_files/lxplus_proof_v24_sample/DYjets_weights.root");
  // TFile *fin_nano_vbf	= TFile::Open("root_files/lxplus_proof_v24_sample/VBFusion_weights.root");

  // // // With b-jet correction efficiency file of NanoAOD per channel
  // TFile *fin_nano_data	= TFile::Open("root_files/lxplus_proof_v23/DataMu_weights.root");
  // TFile *fin_nano_sig	= TFile::Open("root_files/lxplus_proof_v24_channel/HplusM120_weights.root");
  // TFile *fin_nano_ttbar = TFile::Open("root_files/lxplus_proof_v24_channel/TTbar_weights.root");
  // TFile *fin_nano_stop	= TFile::Open("root_files/lxplus_proof_v24_channel/singleTop_weights.root");
  // TFile *fin_nano_wjets	= TFile::Open("root_files/lxplus_proof_v24_channel/Wjets_weights.root");
  // TFile *fin_nano_dyjets = TFile::Open("root_files/lxplus_proof_v24_channel/DYjets_weights.root");
  // TFile *fin_nano_vbf	= TFile::Open("root_files/lxplus_proof_v24_channel/VBFusion_weights.root");

  // // With b-jet correction efficiency file of NanoAOD per sample and wt top ptwt
  // TFile *fin_nano_data	= TFile::Open("root_files/lxplus_proof_v23/DataMu_weights.root");
  // TFile *fin_nano_sig	= TFile::Open("root_files/lxplus_proof_v24_topptwt/HplusM120_weights.root");
  // TFile *fin_nano_ttbar = TFile::Open("root_files/lxplus_proof_v24_topptwt/TTbar_weights.root");
  // TFile *fin_nano_stop	= TFile::Open("root_files/lxplus_proof_v24_topptwt/singleTop_weights.root");
  // TFile *fin_nano_wjets	= TFile::Open("root_files/lxplus_proof_v24_topptwt/Wjets_weights.root");
  // TFile *fin_nano_dyjets = TFile::Open("root_files/lxplus_proof_v24_topptwt/DYjets_weights.root");
  // TFile *fin_nano_vbf	= TFile::Open("root_files/lxplus_proof_v24_topptwt/VBFusion_weights.root");

  // // With b-jet correction efficiency file of NanoAOD per sample + top ptwt + METJER correction 
  // TFile *fin_nano_data	= TFile::Open("root_files/lxplus_proof_v25/DataMu_weights.root");
  // TFile *fin_nano_sig	= TFile::Open("root_files/lxplus_proof_v25/HplusM120_weights.root");
  // TFile *fin_nano_ttbar = TFile::Open("root_files/lxplus_proof_v25/TTbar_weights.root");
  // TFile *fin_nano_stop	= TFile::Open("root_files/lxplus_proof_v25/singleTop_weights.root");
  // TFile *fin_nano_wjets	= TFile::Open("root_files/lxplus_proof_v25/Wjets_weights.root");
  // TFile *fin_nano_dyjets = TFile::Open("root_files/lxplus_proof_v25/DYjets_weights.root");
  // TFile *fin_nano_vbf	= TFile::Open("root_files/lxplus_proof_v25/VBFusion_weights.root");
  // TFile *fin_mini_qcd	= TFile::Open("root_files/lxplus_proof_v25/all_QCD.root");

  // Skim level ana
  // TFile *fin_nano_data	= TFile::Open("root_files/local_v26/DataMu_weight.root");
  // TFile *fin_nano_sig	= TFile::Open("root_files/local_v26/HplusM120_weight.root");
  // TFile *fin_nano_ttbar = TFile::Open("root_files/local_v26/TTbar_weight.root");
  // TFile *fin_nano_stop	= TFile::Open("root_files/local_v26/singleTop_weight.root");
  // TFile *fin_nano_wjets	= TFile::Open("root_files/local_v26/Wjets_weight.root");
  // TFile *fin_nano_dyjets = TFile::Open("root_files/local_v26/DYjets_weight.root");
  // TFile *fin_nano_vbf	= TFile::Open("root_files/local_v26/VBFusion_weight.root");
  // TFile *fin_nano_qcd	= TFile::Open("root_files/local_v26/MCQCD_weight.root");
  // TFile *fin_mini_qcd	= TFile::Open("../CutFlow/root_files/lxplus_proof_v25/all_QCD.root");
  
  TFile *fin_nano_data	= TFile::Open("root_files/local_v26_Ele/DataMu_weight.root");
  TFile *fin_nano_sig	= TFile::Open("root_files/local_v26_Ele/HplusM120_weight.root");
  TFile *fin_nano_ttbar = TFile::Open("root_files/local_v26_Ele/TTbar_weight.root");
  TFile *fin_nano_stop	= TFile::Open("root_files/local_v26_Ele/singleTop_weight.root");
  //TFile *fin_nano_stop	= TFile::Open("../tmp_test/singleTop_weight_2016.root");
  TFile *fin_nano_wjets	= TFile::Open("root_files/local_v26_Ele/Wjets_weight.root");
  TFile *fin_nano_dyjets = TFile::Open("root_files/local_v26_Ele/DYjets_weight.root");
  TFile *fin_nano_vbf	= TFile::Open("root_files/local_v26_Ele/VBFusion_weight.root");
  TFile *fin_nano_qcd	= TFile::Open("root_files/local_v26_Ele/MCQCDMu_weight.root");
  TFile *fin_mini_qcd	= TFile::Open("/Data/CMS-Software/local/CMSSW_8_0_28/src/Analysis/stack/HIG-18-021_PRD_Histograms_Mu/all_QCD.root");


  TH1D *hcf_nano_data	= (TH1D *)fin_nano_data->Get("_cutflow_mu");
  TH1D *hcf_nano_sig	= (TH1D *)fin_nano_sig->Get("_cutflow_mu");
  TH1D *hcf_nano_ttbar	= (TH1D *)fin_nano_ttbar->Get("_cutflow_mu");
  TH1D *hcf_nano_stop	= (TH1D *)fin_nano_stop->Get("_cutflow_mu"); 
  TH1D *hcf_nano_wjets	= (TH1D *)fin_nano_wjets->Get("_cutflow_mu");
  TH1D *hcf_nano_dyjets	= (TH1D *)fin_nano_dyjets->Get("_cutflow_mu");
  TH1D *hcf_nano_vbf	= (TH1D *)fin_nano_vbf->Get("_cutflow_mu");
  TH1D *hcf_nano_qcd	= (TH1D *)fin_nano_qcd->Get("_cutflow_mu");
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

  hcf_nano_data->SetBinContent(1,0.0);
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
  
  int WeightedCounts(TH1D *, TH1D *, TH1D *, TH1D *, TH1D *, TH1D *, TH1D *, TH1D *, TH1D *);
  WeightedCounts(hcf_nano_data, hcf_nano_bkg, hcf_nano_sig, hcf_nano_ttbar, hcf_nano_stop, hcf_nano_wjets, hcf_nano_dyjets, hcf_nano_vbf, hcf_nano_qcd);

  hcf_nano_data->SetMarkerStyle(kFullCircle);
  hcf_nano_data->SetMarkerColor(kBlack);
  hcf_nano_data->SetMarkerSize(1.2);
  
  hcf_nano_sig->SetLineStyle(kDashed);
  hcf_nano_sig->SetLineColor(kRed);
  hcf_nano_sig->SetLineWidth(2);
  
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

  leg->AddEntry(hcf_nano_sig, Form("m_{H^{+}} = 120 GeV") ,"l");
  
  const char *cutnames[10] = {"Trigger", Form("Nof #mu = 1"), "No. of jets #geq 4", "MET #geq 20 GeV", "No. of #it{b}-jets #geq 2", "", "", "" ,"",""};
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
  hcf_nano_sig->Draw("same hist");
  hcf_nano_data->Draw("e1p same");
  leg->Draw();
  c1->Update();

  return true;
}

int WeightedCounts(TH1D *hcf_nano_data, TH1D *hcf_nano_bkg, TH1D *hcf_nano_sig, TH1D *hcf_nano_ttbar, 
		   TH1D *hcf_nano_stop,TH1D *hcf_nano_wjets, TH1D *hcf_nano_dyjets, TH1D *hcf_nano_vbf, TH1D *hcf_nano_qcd)
{
  
  bool isDetail = 1 ;
  
  if (isDetail){

    TFile *fin = TFile::Open("/Data/CMS-Software/local/CMSSW_8_0_28/src/Analysis/stack/HIG-18-021_PRD_Histograms_Mu/all_Hplus120.root");
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

    fin = TFile::Open("/Data/CMS-Software/local/CMSSW_8_0_28/src/Analysis/stack/HIG-18-021_PRD_Histograms_Mu/all_TTJetsP.root");
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
  
    fin = TFile::Open("/Data/CMS-Software/local/CMSSW_8_0_28/src/Analysis/stack/HIG-18-021_PRD_Histograms_Mu/all_ST.root");
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

    fin = TFile::Open("/Data/CMS-Software/local/CMSSW_8_0_28/src/Analysis/stack/HIG-18-021_PRD_Histograms_Mu/all_WJets.root");
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


    fin = TFile::Open("/Data/CMS-Software/local/CMSSW_8_0_28/src/Analysis/stack/HIG-18-021_PRD_Histograms_Mu/all_DY.root");
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

    fin = TFile::Open("/Data/CMS-Software/local/CMSSW_8_0_28/src/Analysis/stack/HIG-18-021_PRD_Histograms_Mu/all_VV.root");
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
    TFile *finQCD = TFile::Open("/Data/CMS-Software/local/CMSSW_8_0_28/src/Analysis/stack/HIG-18-021_PRD_Histograms_Mu/all_QCD.root");
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

    TFile *finMC = TFile::Open("/Data/CMS-Software/local/CMSSW_8_0_28/src/Analysis/stack/HIG-18-021_PRD_Histograms_Mu/all_MC.root");
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

    
    fin = TFile::Open("/Data/CMS-Software/local/CMSSW_8_0_28/src/Analysis/stack/HIG-18-021_PRD_Histograms_Mu/all_Data.root");
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
    TFile *fin = TFile::Open("/Data/CMS-Software/local/CMSSW_8_0_28/src/Analysis/stack/HIG-18-021_PRD_Histograms_Ele/all_Hplus120.root");
    TH1F *hMAODCF = (TH1F *)fin->Get("base/Iso/cutflow");
    printf("Signal Integral & ");
    for (int ibin=2;ibin<hcf_nano_sig->GetNbinsX();ibin++){
      if(hcf_nano_sig->GetBinContent(ibin)>0.0 and hcf_nano_sig->GetBinContent(ibin+1)>0.0){
	if(hcf_nano_sig->GetBinContent(ibin)>1e6){
	  printf("%.4e (%4.2f\\%%)& ",hcf_nano_sig->GetBinContent(ibin), 
		 100.*(hcf_nano_sig->GetBinContent(ibin)-hMAODCF->GetBinContent(ibin-1))/hMAODCF->GetBinContent(ibin-1));
	}else{
	  printf("%.1f (%4.2f\\%%)& ",hcf_nano_sig->GetBinContent(ibin),
		 100.*(hcf_nano_sig->GetBinContent(ibin)-hMAODCF->GetBinContent(ibin-1))/hMAODCF->GetBinContent(ibin-1));
	}
      }else if(hcf_nano_sig->GetBinContent(ibin)>0.0 and TMath::AreEqualAbs(hcf_nano_sig->GetBinContent(ibin+1),0.0,1.e-5)){
	printf("%.1f (%4.2f\\%%)\\\\\\hline ",hcf_nano_sig->GetBinContent(ibin),
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
	  printf("%.4e (%4.2f\\%%)& ",hcf_nano_ttbar->GetBinContent(ibin), 
		 100.*(hcf_nano_ttbar->GetBinContent(ibin)-hMAODCF->GetBinContent(ibin-1))/hMAODCF->GetBinContent(ibin-1));
	}else{
	  printf("%.1f (%4.2f\\%%)& ",hcf_nano_ttbar->GetBinContent(ibin),
		 100.*(hcf_nano_ttbar->GetBinContent(ibin)-hMAODCF->GetBinContent(ibin-1))/hMAODCF->GetBinContent(ibin-1));
	}
      }else if(hcf_nano_ttbar->GetBinContent(ibin)>0.0 and TMath::AreEqualAbs(hcf_nano_ttbar->GetBinContent(ibin+1),0.0,1.e-5)){
	printf("%.1f (%4.2f\\%%)\\\\\\hline ",hcf_nano_ttbar->GetBinContent(ibin),
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
	  printf("%.4e (%4.2f\\%%)& ",hcf_nano_stop->GetBinContent(ibin), 
		 100.*(hcf_nano_stop->GetBinContent(ibin)-hMAODCF->GetBinContent(ibin-1))/hMAODCF->GetBinContent(ibin-1));
	}else{
	  printf("%.1f (%4.2f\\%%)& ",hcf_nano_stop->GetBinContent(ibin),
		 100.*(hcf_nano_stop->GetBinContent(ibin)-hMAODCF->GetBinContent(ibin-1))/hMAODCF->GetBinContent(ibin-1));
	}
      }else if(hcf_nano_stop->GetBinContent(ibin)>0.0 and TMath::AreEqualAbs(hcf_nano_stop->GetBinContent(ibin+1),0.0,1.e-5)){
	printf("%.1f (%4.2f\\%%)\\\\\\hline ",hcf_nano_stop->GetBinContent(ibin),
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
	  printf("%.4e (%4.2f\\%%)& ",hcf_nano_wjets->GetBinContent(ibin), 
		 100.*(hcf_nano_wjets->GetBinContent(ibin)-hMAODCF->GetBinContent(ibin-1))/hMAODCF->GetBinContent(ibin-1));
	}else{
	  printf("%.1f (%4.2f\\%%)& ",hcf_nano_wjets->GetBinContent(ibin),
		 100.*(hcf_nano_wjets->GetBinContent(ibin)-hMAODCF->GetBinContent(ibin-1))/hMAODCF->GetBinContent(ibin-1));
	}
      }else if(hcf_nano_wjets->GetBinContent(ibin)>0.0 and TMath::AreEqualAbs(hcf_nano_wjets->GetBinContent(ibin+1),0.0,1.e-5)){
	printf("%.1f (%4.2f\\%%)\\\\\\hline ",hcf_nano_wjets->GetBinContent(ibin),
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
	  printf("%.4e (%4.2f\\%%)& ",hcf_nano_dyjets->GetBinContent(ibin), 
		 100.*(hcf_nano_dyjets->GetBinContent(ibin)-hMAODCF->GetBinContent(ibin-1))/hMAODCF->GetBinContent(ibin-1));
	}else{
	  printf("%.1f (%4.2f\\%%)& ",hcf_nano_dyjets->GetBinContent(ibin),
		 100.*(hcf_nano_dyjets->GetBinContent(ibin)-hMAODCF->GetBinContent(ibin-1))/hMAODCF->GetBinContent(ibin-1));
	}
      }else if(hcf_nano_dyjets->GetBinContent(ibin)>0.0 and TMath::AreEqualAbs(hcf_nano_dyjets->GetBinContent(ibin+1),0.0,1.e-5)){
	printf("%.1f (%4.2f\\%%)\\\\\\hline ",hcf_nano_dyjets->GetBinContent(ibin),
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
	  printf("%.4e (%4.2f\\%%)& ",hcf_nano_vbf->GetBinContent(ibin), 
		 100.*(hcf_nano_vbf->GetBinContent(ibin)-hMAODCF->GetBinContent(ibin-1))/hMAODCF->GetBinContent(ibin-1));
	}else{
	  printf("%.1f (%4.2f\\%%)& ",hcf_nano_vbf->GetBinContent(ibin),
		 100.*(hcf_nano_vbf->GetBinContent(ibin)-hMAODCF->GetBinContent(ibin-1))/hMAODCF->GetBinContent(ibin-1));
	}
      }else if(hcf_nano_vbf->GetBinContent(ibin)>0.0 and TMath::AreEqualAbs(hcf_nano_vbf->GetBinContent(ibin+1),0.0,1.e-5)){
	printf("%.1f (%4.2f\\%%)\\\\\\hline ",hcf_nano_vbf->GetBinContent(ibin),
	       100.*(hcf_nano_vbf->GetBinContent(ibin)-hMAODCF->GetBinContent(ibin-1))/hMAODCF->GetBinContent(ibin-1));
      }
    }
    hMAODCF->Delete();
    fin->Close();
    delete fin;
    printf("\n");


    fin = TFile::Open("/Data/CMS-Software/local/CMSSW_8_0_28/src/Analysis/stack/HIG-18-021_PRD_Histograms_Ele/all_MC.root");
    hMAODCF = (TH1F *)fin->Get("base/Iso/cutflow");
    printf("ALL MC & ");
    for (int ibin=2;ibin<hcf_nano_bkg->GetNbinsX();ibin++){
      if(hcf_nano_bkg->GetBinContent(ibin)>0.0 and hcf_nano_bkg->GetBinContent(ibin+1)>0.0){
	if(hcf_nano_bkg->GetBinContent(ibin)>1e6){
	  printf("%.4e (%4.2f\\%%)& ",hcf_nano_bkg->GetBinContent(ibin), 
		 100.*(hcf_nano_bkg->GetBinContent(ibin)-hMAODCF->GetBinContent(ibin-1))/hMAODCF->GetBinContent(ibin-1));
	}else{
	  printf("%.1f (%4.2f\\%%)& ",hcf_nano_bkg->GetBinContent(ibin),
		 100.*(hcf_nano_bkg->GetBinContent(ibin)-hMAODCF->GetBinContent(ibin-1))/hMAODCF->GetBinContent(ibin-1));
	}
      }else if(hcf_nano_bkg->GetBinContent(ibin)>0.0 and TMath::AreEqualAbs(hcf_nano_bkg->GetBinContent(ibin+1),0.0,1.e-5)){
	printf("%.1f (%4.2f\\%%)\\\\\\hline ",hcf_nano_bkg->GetBinContent(ibin),
	       100.*(hcf_nano_bkg->GetBinContent(ibin)-hMAODCF->GetBinContent(ibin-1))/hMAODCF->GetBinContent(ibin-1));
      }
    }
    hMAODCF->Delete();
    fin->Close();
    delete fin;
    printf("\n");

    fin = TFile::Open("/Data/CMS-Software/local/CMSSW_8_0_28/src/Analysis/stack/HIG-18-021_PRD_Histograms_Ele/all_Data.root");
    hMAODCF = (TH1F *)fin->Get("base/Iso/cutflow");
    printf("Data & ");
    for (int ibin=2;ibin<hcf_nano_data->GetNbinsX();ibin++){
      if(hcf_nano_data->GetBinContent(ibin)>0.0 and hcf_nano_data->GetBinContent(ibin+1)>0.0){
	if(hcf_nano_data->GetBinContent(ibin)>1e6){
	  printf("%.4e (%4.2f\\%%)& ",hcf_nano_data->GetBinContent(ibin), 
		 100.*(hcf_nano_data->GetBinContent(ibin)-hMAODCF->GetBinContent(ibin-1))/hMAODCF->GetBinContent(ibin-1));
	}else{
	  printf("%.1f (%4.2f\\%%)& ",hcf_nano_data->GetBinContent(ibin),
		 100.*(hcf_nano_data->GetBinContent(ibin)-hMAODCF->GetBinContent(ibin-1))/hMAODCF->GetBinContent(ibin-1));
	}
      }else if(hcf_nano_data->GetBinContent(ibin)>0.0 and TMath::AreEqualAbs(hcf_nano_data->GetBinContent(ibin+1),0.0,1.e-5)){
	printf("%.1f (%4.2f\\%%)\\\\\\hline ",hcf_nano_data->GetBinContent(ibin),
	       100.*(hcf_nano_data->GetBinContent(ibin)-hMAODCF->GetBinContent(ibin-1))/hMAODCF->GetBinContent(ibin-1));
      }
    }
    hMAODCF->Delete();
    fin->Close();
    delete fin;
    printf("\n");

  }
   
  return true;
}
