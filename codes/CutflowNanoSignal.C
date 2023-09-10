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

int CutflowNanoSignal()
{  
  
  int year = 2018;
  bool isMu = 0;
  bool isHplus = 1;
  const char* cutflow = (isMu) ? "_cutflow_mu" : "_cutflow_ele";
  const char* cutflowUS = (isMu) ? "_cutflowUS_mu" : "_cutflowUS_ele";
  
  //const char* dir = "grid_v39_Syst/CBA_KFNewReso";
  //const char* dir = "grid_v39_Syst/CBA_CTagM/pre";
  //const char* dir = "grid_v39_Syst/CBA_CTagM";
  //const char* dir = "grid_v39_Syst/CBA_ModSigCS";
  //const char* dir = "grid_v39_Syst/CBA_AllButBC";
  const char* dir = "grid_v39_Syst/CBA_GeneratorWt";
  
  int mpoint[10] = {80, 90, 100, 110, 120, 130, 140, 150, 155, 160};
  string htype = "";
  if(isHplus)
    htype = "HplusM";
  else
    htype = "HminusM";
  for(int imass=0;imass<10;imass++){
    string mval = "";
    if(isHplus)
      mval = Form("$m_{H^+} = %d$ GeV",mpoint[imass]);
    else
      mval = Form("$m_{H^-} = %d$ GeV",mpoint[imass]);

    //cout << fname << endl;
    TFile *fin_nano_sig = TFile::Open(Form("root_files/%s/%d/all_%s%03d.root",dir,year,htype.c_str(),mpoint[imass]));
    TH1D *hcf_nano_sig = (TH1D *)fin_nano_sig->Get(Form("%s%03d/base/Iso/%s",htype.c_str(),mpoint[imass],cutflow));
    //hcf_nano_sig->SetBinContent(1,0.0);

    printf("%s & ",mval.data());
    for (int ibin=2;ibin<=hcf_nano_sig->GetNbinsX();ibin++){
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
    printf("\n");
  }
  
  // const char* datafile = (isMu) ? Form("root_files/%s/%d/all_DataMu.root",dir,year) : Form("root_files/%s/%d/all_DataEle.root",dir,year) ;
  // const char* qcdfile = (isMu) ? Form("root_files/%s/%d/all_MCQCDMu.root",dir,year) : Form("root_files/%s/%d/all_MCQCDEle.root",dir,year) ;
  // TFile *fin_nano_data	= TFile::Open(datafile);
  // TFile *fin_nano_sig = 0x0 ;
  // if(year == 2016)
  //   fin_nano_sig	= TFile::Open(Form("root_files/%s/%d/all_HplusM120.root",dir,year));
  // TFile *fin_nano_ttbar = TFile::Open(Form("root_files/%s/%d/all_TTbar.root",dir,year));
  // TFile *fin_nano_stop	= TFile::Open(Form("root_files/%s/%d/all_singleTop.root",dir,year));
  // TFile *fin_nano_wjets	= TFile::Open(Form("root_files/%s/%d/all_Wjets.root",dir,year));
  // TFile *fin_nano_dyjets = TFile::Open(Form("root_files/%s/%d/all_DYjets.root",dir,year));
  // TFile *fin_nano_vbf	= TFile::Open(Form("root_files/%s/%d/all_VBFusion.root",dir,year));
  // TFile *fin_nano_qcd	= TFile::Open(qcdfile);
  // TFile *fin_mini_qcd	= TFile::Open("/Data/CMS-Software/local/CMSSW_8_0_28/src/Analysis/stack/HIG-18-021_PRD_Histograms_Ele/all_QCD.root");
  

  // TH1D *hcf_nano_data	= (TH1D *)fin_nano_data->Get(((isMu) ? Form("DataMu/base/Iso/%s",cutflowUS) : Form("DataEle/base/Iso/%s",cutflowUS)));
  // TH1D *hcf_nano_sig = 0x0 ;
  // if(year == 2016)
  //   hcf_nano_sig	= (TH1D *)fin_nano_sig->Get(Form("HplusM120/base/Iso/%s",cutflow));
  // TH1D *hcf_nano_ttbar	= (TH1D *)fin_nano_ttbar->Get(Form("TTbar/base/Iso/%s",cutflow));
  // TH1D *hcf_nano_stop	= (TH1D *)fin_nano_stop->Get(Form("singleTop/base/Iso/%s",cutflow)); 
  // TH1D *hcf_nano_wjets	= (TH1D *)fin_nano_wjets->Get(Form("Wjets/base/Iso/%s",cutflow));
  // TH1D *hcf_nano_dyjets	= (TH1D *)fin_nano_dyjets->Get(Form("DYjets/base/Iso/%s",cutflow));
  // TH1D *hcf_nano_vbf	= (TH1D *)fin_nano_vbf->Get(Form("VBFusion/base/Iso/%s",cutflow));
  // TH1D *hcf_nano_qcd	= (TH1D *)fin_nano_qcd->Get(((isMu) ? Form("MCQCDMu/base/Iso/%s",cutflow) : Form("MCQCDEle/base/Iso/%s",cutflow)));
  // TH1F *hcf_mini_qcd	= (TH1F *)fin_mini_qcd->Get("base/Iso/cutflow");
  // // TH1D *hcf_nano_qcd	= (TH1D *)hcf_nano_vbf->Clone("hcf_nano_qcd");
  // // for (int ibin=2;ibin<hcf_nano_qcd->GetNbinsX();ibin++)
  // //   hcf_nano_qcd->SetBinContent(ibin, hcf_mini_qcd->GetBinContent(ibin-1));
  

  // // hcf_nano_data->SetBinContent(2,hcf_nano_data->GetBinContent(0));
  // // hcf_nano_sig->SetBinContent(2,hcf_nano_sig->GetBinContent(0));
  // // hcf_nano_ttbar->SetBinContent(2,hcf_nano_ttbar->GetBinContent(0));
  // // hcf_nano_stop->SetBinContent(2,hcf_nano_stop->GetBinContent(0));
  // // hcf_nano_wjets->SetBinContent(2,hcf_nano_wjets->GetBinContent(0));
  // // hcf_nano_dyjets->SetBinContent(2,hcf_nano_dyjets->GetBinContent(0));
  // // hcf_nano_vbf->SetBinContent(2,hcf_nano_vbf->GetBinContent(0));

  // //cout << "Wjets  : " << hcf_nano_wjets->GetBinContent(1) << endl;
  
  // hcf_nano_data->SetBinContent(1,0.0);
  // if(year == 2016)
  //   hcf_nano_sig->SetBinContent(1,0.0);
  // hcf_nano_ttbar->SetBinContent(1,0.0);
  // hcf_nano_stop->SetBinContent(1,0.0);
  // hcf_nano_wjets->SetBinContent(1,0.0);
  // hcf_nano_dyjets->SetBinContent(1,0.0);
  // hcf_nano_vbf->SetBinContent(1,0.0);
  // hcf_nano_qcd->SetBinContent(1,0.0);
  
  // TH1D *hcf_nano_bkg = (TH1D *)hcf_nano_ttbar->Clone("Bkg");
  // hcf_nano_bkg->Add(hcf_nano_stop);
  // hcf_nano_bkg->Add(hcf_nano_wjets);
  // hcf_nano_bkg->Add(hcf_nano_dyjets);
  // hcf_nano_bkg->Add(hcf_nano_vbf);
  // hcf_nano_bkg->Add(hcf_nano_qcd);
  
  // int WeightedCounts(int, string, TH1D *, TH1D *, TH1D *, TH1D *, TH1D *, TH1D *, TH1D *, TH1D *, TH1D *);
  // WeightedCounts(year, cutflow, hcf_nano_data, hcf_nano_bkg, hcf_nano_sig, hcf_nano_ttbar, hcf_nano_stop, hcf_nano_wjets, hcf_nano_dyjets, hcf_nano_vbf, hcf_nano_qcd);
  
  // hcf_nano_data->SetMarkerStyle(kFullCircle);
  // hcf_nano_data->SetMarkerColor(kBlack);
  // hcf_nano_data->SetMarkerSize(1.2);
  
  // if(year == 2016){
  //   hcf_nano_sig->SetLineStyle(kDashed);
  //   hcf_nano_sig->SetLineColor(kRed);
  //   hcf_nano_sig->SetLineWidth(2);
  // }

  // hcf_nano_ttbar->SetFillColor(kCyan+1);
  
  // hcf_nano_stop->SetFillColor(kViolet);

  // hcf_nano_wjets->SetFillColor(kYellow);

  // hcf_nano_dyjets->SetFillColor(kOrange+1);
  
  // hcf_nano_vbf->SetFillColor(kGreen+2);

  // hcf_nano_qcd->SetFillColor(kRed);
  
  // THStack *hs = new THStack("hs","");
  // hs->Add(hcf_nano_vbf);
  // hs->Add(hcf_nano_dyjets);
  // hs->Add(hcf_nano_wjets);
  // hs->Add(hcf_nano_qcd);
  // hs->Add(hcf_nano_stop);
  // hs->Add(hcf_nano_ttbar);

  // TLegend *leg = new TLegend(0.6962751,0.5611814,0.8925501,0.8924051);
  // leg->SetFillColor(10);
  // leg->AddEntry(hcf_nano_data, Form("Data") ,"lp");
  // leg->AddEntry(hcf_nano_ttbar, Form("#it{t}#bar{#it{t}}") ,"f");
  // leg->AddEntry(hcf_nano_stop, Form("Single #it{t}") ,"f");
  // leg->AddEntry(hcf_nano_wjets, Form("#it{W} + jets") ,"f");
  // leg->AddEntry(hcf_nano_dyjets, Form("#it{Z}/#gamma + jets") ,"f");
  // leg->AddEntry(hcf_nano_vbf, Form("VV") ,"f");
  // leg->AddEntry(hcf_nano_qcd, Form("QCD") ,"f");
  // if(year == 2016)
  //   leg->AddEntry(hcf_nano_sig, Form("m_{H^{+}} = 120 GeV") ,"l");
  
  // const char *cutnames[10] = {"Trigger", Form("Nof #mu = 1"), "No. of jets #geq 4", "MET #geq 20 GeV", "No. of #it{b}-jets #geq 2", "KinFit Sel.", "", "" ,"",""};
  // for (int ibin=2;ibin<hcf_nano_data->GetNbinsX();ibin++){
  //   hcf_nano_data->GetXaxis()->SetBinLabel(ibin, cutnames[ibin-2]);
  // }

  // hcf_nano_data->SetMinimum(1.0e-1);
  // hcf_nano_data->SetMaximum(1.0e12);
  // //hcf_nano_data->SetMaximum(1.0e9);
  

  // TCanvas *c1 = new TCanvas("c1","c1");
  // gStyle->SetOptStat(0);
  // gStyle->SetOptTitle(0);
  // c1->SetLogy();
  // c1->SetTickx();
  // c1->SetTicky();
  // hcf_nano_data->Draw("e1p");
  // hs->Draw("same hist");
  // // hcf_nano_qcd->Draw("same hist");
  // // hcf_nano_ttbar->Draw("same hist");
  // // hcf_nano_stop->Draw("same hist");
  // // hcf_nano_wjets->Draw("same hist");
  // // hcf_nano_dyjets->Draw("same hist");
  // // hcf_nano_vbf->Draw("same hist");
  // //hcf_nano_stop->Draw("same hist");
  // if(year == 2016)
  //   hcf_nano_sig->Draw("same hist");
  // hcf_nano_data->Draw("e1p same");
  // leg->Draw();
  // c1->Update();

  return true;
}

int WeightedCounts(int year, string cutflow, TH1D *hcf_nano_data, TH1D *hcf_nano_bkg, TH1D *hcf_nano_sig, TH1D *hcf_nano_ttbar, 
		   TH1D *hcf_nano_stop,TH1D *hcf_nano_wjets, TH1D *hcf_nano_dyjets, TH1D *hcf_nano_vbf, TH1D *hcf_nano_qcd)
{
  TFile *fin = 0x0;
  TH1F *hMAODCF = 0x0;

  bool isDetail = 0 ;
  
  if (isDetail){

    // TFile *fin = TFile::Open("/Data/CMS-Software/local/CMSSW_8_0_28/src/Analysis/stack/HIG-18-021_PRD_Histograms_Ele/all_Hplus120.root");
    // TH1F *hMAODCF = (TH1F *)fin->Get("base/Iso/cutflow");
    // // printf("Signal Integral & ");
    // // for (int ibin=2;ibin<hcf_nano_sig->GetNbinsX();ibin++){
    // //   if(hcf_nano_sig->GetBinContent(ibin)>0.0 and hcf_nano_sig->GetBinContent(ibin+1)>0.0){
    // // 	if(hcf_nano_sig->GetBinContent(ibin)>1e6){
    // // 	  printf("%.4e (%.4e, %4.2f\\%%)& ",hcf_nano_sig->GetBinContent(ibin), hMAODCF->GetBinContent(ibin-1), 
    // // 		 100.*(hcf_nano_sig->GetBinContent(ibin)-hMAODCF->GetBinContent(ibin-1))/hMAODCF->GetBinContent(ibin-1));
    // // 	}else{
    // // 	  printf("%.1f (%.1f, %4.2f\\%%)& ",hcf_nano_sig->GetBinContent(ibin), hMAODCF->GetBinContent(ibin-1),
    // // 		 100.*(hcf_nano_sig->GetBinContent(ibin)-hMAODCF->GetBinContent(ibin-1))/hMAODCF->GetBinContent(ibin-1));
    // // 	}
    // //   }else if(hcf_nano_sig->GetBinContent(ibin)>0.0 and TMath::AreEqualAbs(hcf_nano_sig->GetBinContent(ibin+1),0.0,1.e-5)){
    // // 	printf("%.1f (%.1f, %4.2f\\%%)\\\\\\hline ",hcf_nano_sig->GetBinContent(ibin), hMAODCF->GetBinContent(ibin-1),
    // // 	       100.*(hcf_nano_sig->GetBinContent(ibin)-hMAODCF->GetBinContent(ibin-1))/hMAODCF->GetBinContent(ibin-1));
    // //   }
    // // }
    // hMAODCF->Delete();
    // fin->Close();
    // delete fin;
    // printf("\n");

    fin = TFile::Open("/Data/CMS-Software/local/CMSSW_8_0_28/src/Analysis/stack/HIG-18-021_PRD_Histograms_Mu/all_TTJetsP.root");
    hMAODCF = (TH1F *)fin->Get("base/Iso/cutflow");
    // fin = TFile::Open(Form("/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/grid_v36_Syst/CBA_Skim_Syst_btagCSV/%d/all_TTbar.root",year));
    // hMAODCF  = (TH1D *)fin->Get(Form("TTbar/base/Iso/%s",cutflow.c_str()));
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
    // fin = TFile::Open(Form("/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/grid_v36_Syst/CBA_Skim_Syst_btagCSV/%d/all_singleTop.root",year));
    // hMAODCF  = (TH1D *)fin->Get(Form("singleTop/base/Iso/%s",cutflow.c_str()));
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
    // fin = TFile::Open(Form("/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/grid_v36_Syst/CBA_Skim_Syst_btagCSV/%d/all_Wjets.root",year));
    // hMAODCF  = (TH1D *)fin->Get(Form("Wjets/base/Iso/%s",cutflow.c_str()));
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
    // fin = TFile::Open(Form("/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/grid_v36_Syst/CBA_Skim_Syst_btagCSV/%d/all_DYjets.root",year));
    // hMAODCF  = (TH1D *)fin->Get(Form("DYjets/base/Iso/%s",cutflow.c_str()));
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
    // fin = TFile::Open(Form("/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/grid_v36_Syst/CBA_Skim_Syst_btagCSV/%d/all_VBFusion.root",year));
    // hMAODCF  = (TH1D *)fin->Get(Form("VBFusion/base/Iso/%s",cutflow.c_str()));
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
    
    // int lastbin = 7 ;
    // TFile *finQCD = TFile::Open("/Data/CMS-Software/local/CMSSW_8_0_28/src/Analysis/stack/HIG-18-021_PRD_Histograms_Mu/all_QCD.root");
    // hMAODCF = (TH1F *)finQCD->Get("base/Iso/cutflow");
    // // TH1F *hMiniBkg = (TH1F *)hMAODCF->Clone("MiniAOD_Bkg");
    // // fin = TFile::Open(Form("/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/grid_v36_Syst/CBA_Skim_Syst_btagCSV/%d/all_MCQCDMu.root",year));
    // // hMAODCF  = (TH1D *)fin->Get(Form("MCQCDMu/base/Iso/%s",cutflow.c_str()));
    // printf("MC QCD & ");
    // //for (int ibin=2;ibin<hcf_nano_qcd->GetNbinsX();ibin++){
    // for (int ibin=2;ibin<lastbin;ibin++){
    //   if(hcf_nano_qcd->GetBinContent(ibin)>0.0 and hcf_nano_qcd->GetBinContent(ibin+1)>0.0){
    // 	if(hcf_nano_qcd->GetBinContent(ibin)>1e6){
    // 	  printf("%.4e (%.4e, %4.2f\\%%)& ",hcf_nano_qcd->GetBinContent(ibin), hMAODCF->GetBinContent(ibin-1), 
    // 		 100.*(hcf_nano_qcd->GetBinContent(ibin)-hMAODCF->GetBinContent(ibin-1))/hMAODCF->GetBinContent(ibin-1));
    // 	}else{
    // 	  printf("%.1f (%.1f, %4.2f\\%%)& ",hcf_nano_qcd->GetBinContent(ibin), hMAODCF->GetBinContent(ibin-1),
    // 		 100.*(hcf_nano_qcd->GetBinContent(ibin)-hMAODCF->GetBinContent(ibin-1))/hMAODCF->GetBinContent(ibin-1));
    // 	}
    //   }else if((hcf_nano_qcd->GetBinContent(ibin)>0.0 and TMath::AreEqualAbs(hcf_nano_qcd->GetBinContent(ibin+1),0.0,1.e-5))){
    // 	printf("%.1f (%.1f, %4.2f\\%%)\\\\\\hline ",hcf_nano_qcd->GetBinContent(ibin), hMAODCF->GetBinContent(ibin-1),
    // 	       100.*(hcf_nano_qcd->GetBinContent(ibin)-hMAODCF->GetBinContent(ibin-1))/hMAODCF->GetBinContent(ibin-1));
    //   }
    // }
    // hMAODCF->Delete();
    // fin->Close();
    // delete fin;
    // printf("\n");

    // // TFile *finMC = TFile::Open("/Data/CMS-Software/local/CMSSW_8_0_28/src/Analysis/stack/HIG-18-021_PRD_Histograms_Ele/all_MC.root");
    // // hMAODCF = (TH1F *)finMC->Get("base/Iso/cutflow");
    // // hMiniBkg->Add(hMAODCF);
    // // printf("ALL BKG & ");
    // // //for (int ibin=2;ibin<hcf_nano_bkg->GetNbinsX();ibin++){
    // // for (int ibin=2;ibin<lastbin;ibin++){
    // //   if(hcf_nano_bkg->GetBinContent(ibin)>0.0 and hcf_nano_bkg->GetBinContent(ibin+1)>0.0  and ibin<=lastbin-2){
    // // 	if(hcf_nano_bkg->GetBinContent(ibin)>1e6){
    // // 	  printf("%.4e (%.4e, %4.2f\\%%)& ",hcf_nano_bkg->GetBinContent(ibin), hMiniBkg->GetBinContent(ibin-1), 
    // // 		 100.*(hcf_nano_bkg->GetBinContent(ibin)-hMiniBkg->GetBinContent(ibin-1))/hMiniBkg->GetBinContent(ibin-1));
    // // 	}else{
    // // 	  printf("%.1f (%.1f, %4.2f\\%%)& ",hcf_nano_bkg->GetBinContent(ibin), hMiniBkg->GetBinContent(ibin-1),
    // // 		 100.*(hcf_nano_bkg->GetBinContent(ibin)-hMiniBkg->GetBinContent(ibin-1))/hMiniBkg->GetBinContent(ibin-1));
    // // 	}
    // //   }else if((hcf_nano_bkg->GetBinContent(ibin)>0.0 and TMath::AreEqualAbs(hcf_nano_bkg->GetBinContent(ibin+1),0.0,1.e-5))  or ibin==lastbin-1){
    // // 	printf("%.1f (%.1f, %4.2f\\%%)\\\\\\hline ",hcf_nano_bkg->GetBinContent(ibin), hMiniBkg->GetBinContent(ibin-1),
    // // 	       100.*(hcf_nano_bkg->GetBinContent(ibin)-hMiniBkg->GetBinContent(ibin-1))/hMiniBkg->GetBinContent(ibin-1));
    // //   }
    // // }
    // // hMAODCF->Delete();
    // // printf("\n");

    
    fin = TFile::Open("/Data/CMS-Software/local/CMSSW_8_0_28/src/Analysis/stack/HIG-18-021_PRD_Histograms_Mu/all_Data.root");
    hMAODCF = (TH1F *)fin->Get("base/Iso/cutflow");
    // fin = TFile::Open(Form("/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/grid_v36_Syst/CBA_Skim_Syst_btagCSV/%d/all_DataMu.root",year));
    // hMAODCF  = (TH1D *)fin->Get(Form("DataMu/base/Iso/%s",cutflow.c_str()));
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
    hMAODCF->Delete();
    fin->Close();
    delete fin;
    printf("\n");

    // printf("Data/Bkg & ");
    // for (int ibin=2;ibin<hcf_nano_data->GetNbinsX();ibin++){
    //   if(hcf_nano_data->GetBinContent(ibin)>0.0 and hcf_nano_data->GetBinContent(ibin+1)>0.0){
    // 	  printf("%.4f (%.4f, %4.2f\\%%)& ",hcf_nano_data->GetBinContent(ibin)/hcf_nano_bkg->GetBinContent(ibin), 
    // 		 hMAODCF->GetBinContent(ibin-1)/hMiniBkg->GetBinContent(ibin-1),
    // 		 100.*(hcf_nano_data->GetBinContent(ibin)/hcf_nano_bkg->GetBinContent(ibin) - hMAODCF->GetBinContent(ibin-1)/hMiniBkg->GetBinContent(ibin-1))*hMiniBkg->GetBinContent(ibin-1)/hMAODCF->GetBinContent(ibin-1));
    //   }else if(hcf_nano_data->GetBinContent(ibin)>0.0 and TMath::AreEqualAbs(hcf_nano_data->GetBinContent(ibin+1),0.0,1.e-5)){
    // 	printf("%.4f (%.4f, %4.2f\\%%)\\\\\\hline ",hcf_nano_data->GetBinContent(ibin)/hcf_nano_bkg->GetBinContent(ibin), 
    // 	       hMAODCF->GetBinContent(ibin-1)/hMiniBkg->GetBinContent(ibin-1),
    // 	       100.*(hcf_nano_data->GetBinContent(ibin)/hcf_nano_bkg->GetBinContent(ibin) - hMAODCF->GetBinContent(ibin-1)/hMiniBkg->GetBinContent(ibin-1))*hMiniBkg->GetBinContent(ibin-1)/hMAODCF->GetBinContent(ibin-1));
    //   }
    // }
    // printf("\n");




    // hMAODCF->Delete();
    // fin->Close();
    // delete fin;
    
    // finMC->Close();
    // delete finMC;

    // finQCD->Close();
    // delete finQCD;



  }else{

    if(year==2016){
      TFile *fin = TFile::Open("/Data/CMS-Software/local/CMSSW_8_0_28/src/Analysis/stack/HIG-18-021_PRD_Histograms_Ele/all_Hplus120.root");
      TH1F *hMAODCF = (TH1F *)fin->Get("base/Iso/cutflow");
      printf("Signal Integral & ");
      for (int ibin=2;ibin<hcf_nano_sig->GetNbinsX();ibin++){
	if(ibin==8) continue;
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
      if(ibin==8) continue;
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
      if(ibin==8) continue;
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
      if(ibin==8) continue;
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
      if(ibin==8) continue;
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
      if(ibin==8) continue;
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
      if(ibin==8) continue;
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
      if(ibin==8) continue;
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
      if(ibin==8) continue;
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
      if(ibin==8) continue;
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
