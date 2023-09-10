/**********************************************************************
 Created on : 19/02/2022
 Purpose    : Comparison of Tag efficiency 
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
#include <TH2.h>
#include <TH1.h>
#include <TProfile.h>
#include <TRatioPlot.h>

#include <iostream>
#include <fstream>

using namespace std;

int TagEffCompare()
{
  
  string infile_mini = "output/btag_miniAOD.root";
  //string infile_deepcsv = "output/btag_deepcsv.root";
  //string infile_deepcsv = "output/btag_eventcut.root";
  // string infile_deepcsv = "output/btag_njetgeq4.root";
  // string infile_deepjet = "output/btag_deepjet.root";
  // string infile_deepcsv = "output/btag_njetgeq4_2017.root";
  // string infile_deepjet = "output/btag_deepjet_2017.root";
  
  string infile_deepcsv = "/Data/CMS-Analysis/NanoAOD-Analysis/ProcessSkim/root_files/NanoAODUL/btag_deepjet_hadronflavour/2017/TTbar_btag_eff_deepjet_2017.root";
  string infile_deepjet = "/Data/CMS-Analysis/NanoAOD-Analysis/ProcessSkim/root_files/NanoAODUL/btag_deepjet_hadronflavour/2017/AllMC_btag_eff_deepjet_2017.root";
  
  // string infile_deepcsv = "/Data/CMS-Analysis/NanoAOD-Analysis/ProcessSkim/root_files/NanoAODUL/btag_deepjet_hadronflavour/2017/singleTop_btag_eff_deepjet_2017.root";
  // string infile_deepjet = "/Data/CMS-Analysis/NanoAOD-Analysis/ProcessSkim/root_files/NanoAODUL/btag_deepjet_hadronflavour/2017/AllMC_btag_eff_deepjet_2017.root";

  // string infile_deepcsv = "/Data/CMS-Analysis/NanoAOD-Analysis/ProcessSkim/root_files/NanoAODUL/btag_deepjet_hadronflavour/2017/singleTop_btag_eff_deepjet_2017.root";
  // string infile_deepjet = "/Data/CMS-Analysis/NanoAOD-Analysis/ProcessSkim/root_files/NanoAODUL/btag_deepjet_hadronflavour/2017/TTbar_btag_eff_deepjet_2017.root";
  

  float minEta = -2.5, maxEta = 2.5;
  TH2D *h2_BTagEff_b_M=0x0,*h2_BTagEff_c_M=0x0, *h2_BTagEff_l_M=0x0;
  TH2D *h2_CTagEff_b_L=0x0,*h2_CTagEff_c_L=0x0, *h2_CTagEff_l_L=0x0;
  // TH2D *h2_CTagEff_b_L=0x0,*h2_CTagEff_c_L=0x0, *h2_CTagEff_l_L=0x0;
  // TH2D *h2_CTagEff_b_L=0x0,*h2_CTagEff_c_L=0x0, *h2_CTagEff_l_L=0x0;

  TH1D *h1_Mini_BTagEff_b_M=0x0,*h1_Mini_BTagEff_c_M=0x0, *h1_Mini_BTagEff_l_M=0x0;
  TH1D *h1_Mini_CTagEff_b_L=0x0,*h1_Mini_CTagEff_c_L=0x0, *h1_Mini_CTagEff_l_L=0x0;
  // TH1D *h1_Mini_CTagEff_b_L=0x0,*h1_Mini_CTagEff_c_L=0x0, *h1_Mini_CTagEff_l_L=0x0;
  // TH1D *h1_Mini_CTagEff_b_L=0x0,*h1_Mini_CTagEff_c_L=0x0, *h1_Mini_CTagEff_l_L=0x0;

  TH1D *h1_deepcsv_BTagEff_b_M=0x0,*h1_deepcsv_BTagEff_c_M=0x0, *h1_deepcsv_BTagEff_l_M=0x0;
  TH1D *h1_deepcsv_CTagEff_b_L=0x0,*h1_deepcsv_CTagEff_c_L=0x0, *h1_deepcsv_CTagEff_l_L=0x0;

  TH1D *h1_deepjet_BTagEff_b_M=0x0,*h1_deepjet_BTagEff_c_M=0x0, *h1_deepjet_BTagEff_l_M=0x0;
  TH1D *h1_deepjet_CTagEff_b_L=0x0,*h1_deepjet_CTagEff_c_L=0x0, *h1_deepjet_CTagEff_l_L=0x0;

  TFile *fin = TFile::Open(infile_mini.c_str());
  
  h2_BTagEff_b_M              = (TH2D*)(fin->Get("BTag_b_M_efficiency"));
  h2_BTagEff_c_M              = (TH2D*)(fin->Get("BTag_c_M_efficiency"));
  h2_BTagEff_l_M              = (TH2D*)(fin->Get("BTag_l_M_efficiency"));
  
  h2_CTagEff_b_L              = (TH2D*)(fin->Get("CTag_b_L_efficiency"));
  h2_CTagEff_c_L              = (TH2D*)(fin->Get("CTag_c_L_efficiency"));
  h2_CTagEff_l_L              = (TH2D*)(fin->Get("CTag_l_L_efficiency"));
  
  h1_Mini_BTagEff_b_M  = h2_BTagEff_b_M->ProjectionX("h1_Mini_BTagEff_b_M",h2_BTagEff_b_M->GetYaxis()->FindBin(minEta),h2_BTagEff_b_M->GetYaxis()->FindBin(maxEta));
  h1_Mini_BTagEff_c_M  = h2_BTagEff_c_M->ProjectionX("h1_Mini_BTagEff_c_M",h2_BTagEff_c_M->GetYaxis()->FindBin(minEta),h2_BTagEff_c_M->GetYaxis()->FindBin(maxEta));
  h1_Mini_BTagEff_l_M  = h2_BTagEff_l_M->ProjectionX("h1_Mini_BTagEff_l_M",h2_BTagEff_l_M->GetYaxis()->FindBin(minEta),h2_BTagEff_l_M->GetYaxis()->FindBin(maxEta));
  
  h1_Mini_CTagEff_b_L  = h2_CTagEff_b_L->ProjectionX("h1_Mini_CTagEff_b_L",h2_CTagEff_b_L->GetYaxis()->FindBin(minEta),h2_CTagEff_b_L->GetYaxis()->FindBin(maxEta));
  h1_Mini_CTagEff_c_L  = h2_CTagEff_c_L->ProjectionX("h1_Mini_CTagEff_c_L",h2_CTagEff_c_L->GetYaxis()->FindBin(minEta),h2_CTagEff_c_L->GetYaxis()->FindBin(maxEta));
  h1_Mini_CTagEff_l_L  = h2_CTagEff_l_L->ProjectionX("h1_Mini_CTagEff_l_L",h2_CTagEff_l_L->GetYaxis()->FindBin(minEta),h2_CTagEff_l_L->GetYaxis()->FindBin(maxEta));
  
  fin = TFile::Open(infile_deepcsv.c_str());
  
  h2_BTagEff_b_M              = (TH2D*)(fin->Get("BTag_b_M_efficiency"));
  h2_BTagEff_c_M              = (TH2D*)(fin->Get("BTag_c_M_efficiency"));
  h2_BTagEff_l_M              = (TH2D*)(fin->Get("BTag_l_M_efficiency"));
  
  h2_CTagEff_b_L              = (TH2D*)(fin->Get("CTag_b_L_efficiency"));
  h2_CTagEff_c_L              = (TH2D*)(fin->Get("CTag_c_L_efficiency"));
  h2_CTagEff_l_L              = (TH2D*)(fin->Get("CTag_l_L_efficiency"));

  h1_deepcsv_BTagEff_b_M  = h2_BTagEff_b_M->ProjectionX("h1_deepcsv_BTagEff_b_M",h2_BTagEff_b_M->GetYaxis()->FindBin(minEta),h2_BTagEff_b_M->GetYaxis()->FindBin(maxEta));
  h1_deepcsv_BTagEff_c_M  = h2_BTagEff_c_M->ProjectionX("h1_deepcsv_BTagEff_c_M",h2_BTagEff_c_M->GetYaxis()->FindBin(minEta),h2_BTagEff_c_M->GetYaxis()->FindBin(maxEta));
  h1_deepcsv_BTagEff_l_M  = h2_BTagEff_l_M->ProjectionX("h1_deepcsv_BTagEff_l_M",h2_BTagEff_l_M->GetYaxis()->FindBin(minEta),h2_BTagEff_l_M->GetYaxis()->FindBin(maxEta));
  
  h1_deepcsv_CTagEff_b_L  = h2_CTagEff_b_L->ProjectionX("h1_deepcsv_CTagEff_b_L",h2_CTagEff_b_L->GetYaxis()->FindBin(minEta),h2_CTagEff_b_L->GetYaxis()->FindBin(maxEta));
  h1_deepcsv_CTagEff_c_L  = h2_CTagEff_c_L->ProjectionX("h1_deepcsv_CTagEff_c_L",h2_CTagEff_c_L->GetYaxis()->FindBin(minEta),h2_CTagEff_c_L->GetYaxis()->FindBin(maxEta));
  h1_deepcsv_CTagEff_l_L  = h2_CTagEff_l_L->ProjectionX("h1_deepcsv_CTagEff_l_L",h2_CTagEff_l_L->GetYaxis()->FindBin(minEta),h2_CTagEff_l_L->GetYaxis()->FindBin(maxEta));

  fin = TFile::Open(infile_deepjet.c_str());
  
  h2_BTagEff_b_M              = (TH2D*)(fin->Get("BTag_b_M_efficiency"));
  h2_BTagEff_c_M              = (TH2D*)(fin->Get("BTag_c_M_efficiency"));
  h2_BTagEff_l_M              = (TH2D*)(fin->Get("BTag_l_M_efficiency"));
  
  h2_CTagEff_b_L              = (TH2D*)(fin->Get("CTag_b_L_efficiency"));
  h2_CTagEff_c_L              = (TH2D*)(fin->Get("CTag_c_L_efficiency"));
  h2_CTagEff_l_L              = (TH2D*)(fin->Get("CTag_l_L_efficiency"));

  h1_deepjet_BTagEff_b_M  = h2_BTagEff_b_M->ProjectionX("h1_deepjet_BTagEff_b_M",h2_BTagEff_b_M->GetYaxis()->FindBin(minEta),h2_BTagEff_b_M->GetYaxis()->FindBin(maxEta));
  h1_deepjet_BTagEff_c_M  = h2_BTagEff_c_M->ProjectionX("h1_deepjet_BTagEff_c_M",h2_BTagEff_c_M->GetYaxis()->FindBin(minEta),h2_BTagEff_c_M->GetYaxis()->FindBin(maxEta));
  h1_deepjet_BTagEff_l_M  = h2_BTagEff_l_M->ProjectionX("h1_deepjet_BTagEff_l_M",h2_BTagEff_l_M->GetYaxis()->FindBin(minEta),h2_BTagEff_l_M->GetYaxis()->FindBin(maxEta));
  
  h1_deepjet_CTagEff_b_L  = h2_CTagEff_b_L->ProjectionX("h1_deepjet_CTagEff_b_L",h2_CTagEff_b_L->GetYaxis()->FindBin(minEta),h2_CTagEff_b_L->GetYaxis()->FindBin(maxEta));
  h1_deepjet_CTagEff_c_L  = h2_CTagEff_c_L->ProjectionX("h1_deepjet_CTagEff_c_L",h2_CTagEff_c_L->GetYaxis()->FindBin(minEta),h2_CTagEff_c_L->GetYaxis()->FindBin(maxEta));
  h1_deepjet_CTagEff_l_L  = h2_CTagEff_l_L->ProjectionX("h1_deepjet_CTagEff_l_L",h2_CTagEff_l_L->GetYaxis()->FindBin(minEta),h2_CTagEff_l_L->GetYaxis()->FindBin(maxEta));

  int first_bin = h2_BTagEff_b_M->GetYaxis()->FindBin(minEta);
  int last_bin = h2_BTagEff_b_M->GetYaxis()->FindBin(maxEta);
  int nof_bin = last_bin - first_bin + 1;
  cout << "nof_bin : " << nof_bin << endl;
  h1_Mini_BTagEff_b_M->Scale(1/float(nof_bin));
  h1_Mini_BTagEff_c_M->Scale(1/float(nof_bin));
  h1_Mini_BTagEff_l_M->Scale(1/float(nof_bin));
  h1_deepcsv_BTagEff_b_M->Scale(1/float(nof_bin));
  h1_deepcsv_BTagEff_c_M->Scale(1/float(nof_bin));
  h1_deepcsv_BTagEff_l_M->Scale(1/float(nof_bin));
  h1_deepjet_BTagEff_b_M->Scale(1/float(nof_bin));
  h1_deepjet_BTagEff_c_M->Scale(1/float(nof_bin));
  h1_deepjet_BTagEff_l_M->Scale(1/float(nof_bin));

  h1_Mini_BTagEff_b_M->SetLineWidth(3);
  h1_Mini_BTagEff_b_M->SetLineColor(kRed);
  h1_Mini_BTagEff_c_M->SetLineWidth(3);
  h1_Mini_BTagEff_c_M->SetLineColor(kBlue);
  h1_Mini_BTagEff_l_M->SetLineWidth(3);
  h1_Mini_BTagEff_l_M->SetLineColor(kGreen);

  h1_deepcsv_BTagEff_b_M->SetLineWidth(3);
  h1_deepcsv_BTagEff_b_M->SetLineColor(kRed);
  h1_deepcsv_BTagEff_c_M->SetLineWidth(3);
  h1_deepcsv_BTagEff_c_M->SetLineColor(kBlue);
  h1_deepcsv_BTagEff_l_M->SetLineWidth(3);
  h1_deepcsv_BTagEff_l_M->SetLineColor(kGreen);

  h1_deepjet_BTagEff_b_M->SetLineWidth(3);
  h1_deepjet_BTagEff_b_M->SetLineColor(kRed);
  h1_deepjet_BTagEff_c_M->SetLineWidth(3);
  h1_deepjet_BTagEff_c_M->SetLineColor(kBlue);
  h1_deepjet_BTagEff_l_M->SetLineWidth(3);
  h1_deepjet_BTagEff_l_M->SetLineColor(kGreen);

  TLegend *leg1 = new TLegend(0.3194842,0.7531646,0.9799427,0.9240506);
  leg1->SetFillColor(10);
  //leg1->AddEntry(h1_Mini_BTagEff_b_M, "MiniAOD : b quark tagged as b-jet (MWP)" ,"lfp");
  leg1->AddEntry(h1_deepcsv_BTagEff_b_M, "UL eventcut : b quark tagged as b-jet (MWP)" ,"lfp");
  leg1->AddEntry(h1_deepjet_BTagEff_b_M, "UL deepjet : b quark tagged as b-jet (MWP)" ,"lfp");
  //leg1->AddEntry(h1_Mini_BTagEff_c_M, "MiniAOD : c quark tagged as b-jet (MWP)" ,"lfp");
  leg1->AddEntry(h1_deepcsv_BTagEff_c_M, "UL eventcut : c quark tagged as b-jet (MWP)" ,"lfp");
  leg1->AddEntry(h1_deepjet_BTagEff_c_M, "UL deepjet : c quark tagged as b-jet (MWP)" ,"lfp");
  //leg1->AddEntry(h1_Mini_BTagEff_l_M, "MiniAOD : udsg quark tagged as b-jet (MWP)" ,"lfp");
  leg1->AddEntry(h1_deepcsv_BTagEff_l_M, "UL eventcut : udsg quark tagged as b-jet (MWP)" ,"lfp");
  leg1->AddEntry(h1_deepjet_BTagEff_l_M, "UL deepjet : udsg quark tagged as b-jet (MWP)" ,"lfp");

  // h1_Mini_BTagEff_b_M->SetMinimum(0.0);
  // h1_Mini_BTagEff_b_M->SetMaximum(1.4);
  // h1_Mini_BTagEff_b_M->SetTitle(Form("#eta : %3.2f - %3.2f",minEta,maxEta));
  h1_deepcsv_BTagEff_b_M->SetMinimum(0.0);
  h1_deepcsv_BTagEff_b_M->SetMaximum(1.4);
  h1_deepcsv_BTagEff_b_M->SetTitle(Form("#eta : %3.2f - %3.2f",minEta,maxEta));
  TCanvas *c1 = new TCanvas("c1","c1");
  // h1_Mini_BTagEff_b_M->Draw();
  // h1_Mini_BTagEff_c_M->Draw("sames");
  // h1_Mini_BTagEff_l_M->Draw("sames");
  h1_deepcsv_BTagEff_b_M->Draw();
  h1_deepcsv_BTagEff_b_M->Draw("sames");
  h1_deepcsv_BTagEff_c_M->Draw("sames");
  h1_deepcsv_BTagEff_l_M->Draw("sames");
  h1_deepjet_BTagEff_b_M->Draw("hist sames");
  h1_deepjet_BTagEff_c_M->Draw("hist sames");
  h1_deepjet_BTagEff_l_M->Draw("hist sames");
  leg1->Draw();
  h1_Mini_BTagEff_b_M->GetYaxis()->SetTitle("Efficiency");

  ///////////////////////////////////////////////////////////////
  h1_Mini_CTagEff_b_L->Scale(1/float(nof_bin));
  h1_Mini_CTagEff_c_L->Scale(1/float(nof_bin));
  h1_Mini_CTagEff_l_L->Scale(1/float(nof_bin));
  h1_deepcsv_CTagEff_b_L->Scale(1/float(nof_bin));
  h1_deepcsv_CTagEff_c_L->Scale(1/float(nof_bin));
  h1_deepcsv_CTagEff_l_L->Scale(1/float(nof_bin));
  h1_deepjet_CTagEff_b_L->Scale(1/float(nof_bin));
  h1_deepjet_CTagEff_c_L->Scale(1/float(nof_bin));
  h1_deepjet_CTagEff_l_L->Scale(1/float(nof_bin));

  h1_Mini_CTagEff_b_L->SetLineWidth(3);
  h1_Mini_CTagEff_b_L->SetLineColor(kRed);
  h1_Mini_CTagEff_c_L->SetLineWidth(3);
  h1_Mini_CTagEff_c_L->SetLineColor(kBlue);
  h1_Mini_CTagEff_l_L->SetLineWidth(3);
  h1_Mini_CTagEff_l_L->SetLineColor(kGreen);

  h1_deepcsv_CTagEff_b_L->SetLineWidth(3);
  h1_deepcsv_CTagEff_b_L->SetLineColor(kRed);
  h1_deepcsv_CTagEff_c_L->SetLineWidth(3);
  h1_deepcsv_CTagEff_c_L->SetLineColor(kBlue);
  h1_deepcsv_CTagEff_l_L->SetLineWidth(3);
  h1_deepcsv_CTagEff_l_L->SetLineColor(kGreen);

  h1_deepjet_CTagEff_b_L->SetLineWidth(3);
  h1_deepjet_CTagEff_b_L->SetLineColor(kRed);
  h1_deepjet_CTagEff_c_L->SetLineWidth(3);
  h1_deepjet_CTagEff_c_L->SetLineColor(kBlue);
  h1_deepjet_CTagEff_l_L->SetLineWidth(3);
  h1_deepjet_CTagEff_l_L->SetLineColor(kGreen);

  TLegend *leg2 = new TLegend(0.3194842,0.7531646,0.9799427,0.9240506);
  leg2->SetFillColor(10);
  //leg2->AddEntry(h1_Mini_CTagEff_b_L, "MiniAOD : b quark tagged as c-jet (LWP)" ,"lfp");
  leg2->AddEntry(h1_deepcsv_CTagEff_b_L, "UL eventcut : b quark tagged as c-jet (LWP)" ,"lfp");
  leg2->AddEntry(h1_deepjet_CTagEff_b_L, "UL deepjet : b quark tagged as c-jet (LWP)" ,"lfp");
  //leg2->AddEntry(h1_Mini_CTagEff_c_L, "MiniAOD : c quark tagged as c-jet (LWP)" ,"lfp");
  leg2->AddEntry(h1_deepcsv_CTagEff_c_L, "UL eventcut : c quark tagged as c-jet (LWP)" ,"lfp");
  leg2->AddEntry(h1_deepjet_CTagEff_c_L, "UL deepjet : c quark tagged as c-jet (LWP)" ,"lfp");
  //leg2->AddEntry(h1_Mini_CTagEff_l_L, "MiniAOD : udsg quark tagged as c-jet (LWP)" ,"lfp");
  leg2->AddEntry(h1_deepcsv_CTagEff_l_L, "UL eventcut : udsg quark tagged as c-jet (LWP)" ,"lfp");
  leg2->AddEntry(h1_deepjet_CTagEff_l_L, "UL deepjet : udsg quark tagged as c-jet (LWP)" ,"lfp");

  // h1_Mini_CTagEff_b_L->SetMinimum(0.0);
  // h1_Mini_CTagEff_b_L->SetMaximum(1.4);
  // h1_Mini_CTagEff_b_L->SetTitle(Form("#eta : %3.2f - %3.2f",minEta,maxEta));
  h1_deepcsv_CTagEff_b_L->SetMinimum(0.0);
  h1_deepcsv_CTagEff_b_L->SetMaximum(1.4);
  h1_deepcsv_CTagEff_b_L->SetTitle(Form("#eta : %3.2f - %3.2f",minEta,maxEta));
  TCanvas *c2 = new TCanvas("c2","c2");
  // h1_Mini_CTagEff_b_L->Draw();
  // h1_Mini_CTagEff_c_L->Draw("sames");
  // h1_Mini_CTagEff_l_L->Draw("sames");
  h1_deepcsv_CTagEff_b_L->Draw();
  h1_deepcsv_CTagEff_b_L->Draw("sames");
  h1_deepcsv_CTagEff_c_L->Draw("sames");
  h1_deepcsv_CTagEff_l_L->Draw("sames");
  h1_deepjet_CTagEff_b_L->Draw("hist sames");
  h1_deepjet_CTagEff_c_L->Draw("hist sames");
  h1_deepjet_CTagEff_l_L->Draw("hist sames");
  leg2->Draw();
  h1_Mini_CTagEff_b_L->GetYaxis()->SetTitle("Efficiency");
  
  return true;
}
