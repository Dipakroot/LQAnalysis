/**********************************************************************
 Created on : 15/03/2022
 Purpose    : Signal over backgound studies
 Author     : Indranil Das, Visiting Fellow
 Email      : indranil.das@cern.ch | indra.ehep@gmail.com
**********************************************************************/
#include <TH1.h>
#include <TF1.h>
#include <TFile.h>
#include <TTree.h>
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
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

// #include "TParticlePDG.h"
// #include "TDatabasePDG.h"

// #include "TLorentzVector.h"
// #include "TVector3.h"

int SignalEtBackground()
{
  
  TH1F *hMiniSig;
  int GetMiniSig(TH1F*& hSig, int mass);
  TH1F *hMiniBkg;
  int GetMiniBkg(TH1F*& hBkg);

  TH1F *hULSig;
  int GetULSig(TH1F*& hSig, int mass);
  TH1F *hULBkg;
  int GetULBkg(TH1F*& hBkg);
  
  int DecorateGraph(TGraph *&, Color_t, Style_t, Size_t);

  const int nPointsMini = 8;
  int massMini[nPointsMini] = {80, 90, 100, 120, 140, 150, 155, 160}; 
  TGraph *grSByBMini = new TGraph(nPointsMini);
  TGraph *grSBySqrtBMini = new TGraph(nPointsMini);
  TGraph *grSBySPlusBMini = new TGraph(nPointsMini);
  TGraph *grSBySqrtSPlusBMini = new TGraph(nPointsMini);
  GetMiniBkg(hMiniBkg);
  for(int im=0;im<nPointsMini;im++){
    GetMiniSig(hMiniSig, massMini[im]);
    hMiniSig->Scale(1/0.12155);
    grSByBMini->SetPoint(im, float(massMini[im]), hMiniSig->Integral()/hMiniBkg->Integral() );
    grSBySqrtBMini->SetPoint(im, float(massMini[im]), hMiniSig->Integral()/TMath::Sqrt(hMiniBkg->Integral()) );
    grSBySPlusBMini->SetPoint(im, float(massMini[im]), hMiniSig->Integral()/(hMiniBkg->Integral()+hMiniSig->Integral()) );
    grSBySqrtSPlusBMini->SetPoint(im, float(massMini[im]), hMiniSig->Integral()/TMath::Sqrt(hMiniBkg->Integral()+hMiniSig->Integral()) );
  }
  DecorateGraph(grSByBMini, kRed, kFullCircle, 1.2);
  DecorateGraph(grSBySqrtBMini, kRed, kFullCircle, 1.2);
  DecorateGraph(grSBySPlusBMini, kRed, kFullCircle, 1.2);
  DecorateGraph(grSBySqrtSPlusBMini, kRed, kFullCircle, 1.2);

  const int nPointsUL = 10;
  int massUL[nPointsUL] = {80, 90, 100, 110, 120, 130, 140, 150, 155, 160}; 
  TGraph *grSByBUL = new TGraph(nPointsUL);
  TGraph *grSBySqrtBUL = new TGraph(nPointsUL);
  TGraph *grSBySPlusBUL = new TGraph(nPointsUL);
  TGraph *grSBySqrtSPlusBUL = new TGraph(nPointsUL);
  GetULBkg(hULBkg);
  for(int im=0;im<nPointsUL;im++){
    GetULSig(hULSig, massUL[im]);
    grSByBUL->SetPoint(im, float(massUL[im]), hULSig->Integral()/hULBkg->Integral() );
    grSBySqrtBUL->SetPoint(im, float(massUL[im]), hULSig->Integral()/TMath::Sqrt(hULBkg->Integral()) );
    grSBySPlusBUL->SetPoint(im, float(massUL[im]), hULSig->Integral()/(hULBkg->Integral()+hULSig->Integral()) );
    grSBySqrtSPlusBUL->SetPoint(im, float(massUL[im]), hULSig->Integral()/TMath::Sqrt(hULBkg->Integral()+hULSig->Integral()) );
  }
  DecorateGraph(grSByBUL, kBlue, kFullSquare, 1.5);
  DecorateGraph(grSBySqrtBUL, kBlue, kFullSquare, 1.5);
  DecorateGraph(grSBySPlusBUL, kBlue, kFullSquare, 1.5);
  DecorateGraph(grSBySqrtSPlusBUL, kBlue, kFullSquare, 1.5);
  
  // cout <<"Getting Histo 2 : " << hMiniSig->Integral() << endl; 
  // cout <<"Getting Histo 2 : " << hMiniBkg->Integral() << endl; 
  // cout <<"Getting Histo UL 2 : " << hULSig->Integral() << endl; 
  // cout <<"Getting Histo UL 2 : " << hULBkg->Integral() << endl; 
  
  grSByBUL->SetMinimum(0.0);
  grSByBUL->SetMaximum(1.0);
  TCanvas *c1 = new TCanvas("c1","c1");
  c1->SetTickx();
  c1->SetTicky();
  grSByBUL->Draw("AP");
  grSByBMini->Draw("P");
  grSByBUL->GetXaxis()->SetTitle("m_{H^+} (GeV)");
  grSByBUL->GetYaxis()->SetTitle("S/B");

  grSBySqrtBUL->SetMinimum(0.0);
  //grSBySqrtBUL->SetMaximum(1.0);
  TCanvas *c2 = new TCanvas("c2","c2");
  c2->SetTickx();
  c2->SetTicky();
  grSBySqrtBUL->Draw("AP");
  grSBySqrtBMini->Draw("P");
  grSBySqrtBUL->GetXaxis()->SetTitle("m_{H^+} (GeV)");
  grSBySqrtBUL->GetYaxis()->SetTitle("S/#sqrt{B}");

  grSBySPlusBUL->SetMinimum(0.0);
  grSBySPlusBUL->SetMaximum(1.0);
  TCanvas *c3 = new TCanvas("c3","c3");
  c3->SetTickx();
  c3->SetTicky();
  grSBySPlusBUL->Draw("AP");
  grSBySPlusBMini->Draw("P");
  grSBySPlusBUL->GetXaxis()->SetTitle("m_{H^+} (GeV)");
  grSBySPlusBUL->GetYaxis()->SetTitle("S/(S+B)");

  grSBySqrtSPlusBUL->SetMinimum(0.0);
  //grSBySqrtSPlusBUL->SetMaximum(1.0);
  TCanvas *c4 = new TCanvas("c4","c4");
  c4->SetTickx();
  c4->SetTicky();
  grSBySqrtSPlusBUL->Draw("AP");
  grSBySqrtSPlusBMini->Draw("P");
  grSBySqrtSPlusBUL->GetXaxis()->SetTitle("m_{H^+} (GeV)");
  grSBySqrtSPlusBUL->GetYaxis()->SetTitle("S/#sqrt{(S+B)}");
  
  return true;
}

int DecorateGraph(TGraph *& graph, Color_t color, Style_t style, Size_t markerSize)
{
  graph->SetTitle("");

  graph->SetFillColor(1);
  
  graph->SetLineColor(color);
  graph->SetLineWidth(3);

  graph->SetMarkerColor(color);
  graph->SetMarkerStyle(style);
  graph->SetMarkerSize(markerSize);

  return 0;
}


int GetMiniSig(TH1F*& hMiniSig, int mass)
{
  
  string inpath = "/Data/CMS-Analysis/MiniAOD-Analysis/Analysis/MiniAOD_Published/HIG-18-021_PRD_Histograms_Mu";
  TFile *fin = TFile::Open(Form("%s/all_Hplus%d.root",inpath.c_str(),mass));
  //cout <<"Opening file : " << fin->GetName() << endl; 
  hMiniSig = (TH1F *)fin->Get("base/Iso/KinFit/mjj_kfit");
  //cout <<"Getting Histo 1 : " << hMiniSig->GetName() << endl; 
  return true;
}

int GetMiniBkg(TH1F*& hMiniBkg)
{
  //const char *bkgName[] = {"TTJetsP", "ST", "WJets", "DY", "VV"};

  string inpath = "/Data/CMS-Analysis/MiniAOD-Analysis/Analysis/MiniAOD_Published/HIG-18-021_PRD_Histograms_Mu";
  TFile *fin = TFile::Open(Form("%s/all_MC.root",inpath.c_str()));
  //cout <<"Opening file : " << fin->GetName() << endl; 
  hMiniBkg = (TH1F *)fin->Get("base/Iso/KinFit/mjj_kfit");
  //cout <<"Getting Histo 1 : " << hMiniBkg->GetName() << endl; 
  return true;
}

int GetULSig(TH1F*& hULSig, int mass)
{
  
  string inpath = "/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/grid_v39_Syst/CBA_CTagDD/2016/";
  TFile *fin = TFile::Open(Form("%s/all_HplusM%03d.root",inpath.c_str(),mass));
  //cout <<"Opening file : " << fin->GetName() << endl; 
  hULSig = (TH1F *)fin->Get(Form("HplusM%03d/base/Iso/_kb_mjj_mu",mass));
  //cout <<"Getting Histo 1 : " << hULSig->GetName() << endl; 

  return true;
}

int GetULBkg(TH1F*& hULBkg)
{
  const char *bkgName[] = {"TTbar", "singleTop", "Wjets", "DYjets", "VBFusion", "QCDdd"};

  string inpath = "/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/grid_v39_Syst/CBA_CTagDD/2016/";
  for(int ibkg=0;ibkg<6;ibkg++){
    TFile *fin = TFile::Open(Form("%s/all_%s.root",inpath.c_str(),bkgName[ibkg]));
    //cout <<"Opening file : " << fin->GetName() << endl; 
    TH1F *hTemp = (TH1F *)fin->Get(Form("%s/base/Iso/_kb_mjj_mu",bkgName[ibkg]));
    if(ibkg==0)
      hULBkg = (TH1F *)hTemp->Clone("hULBkg");
    else
      hULBkg->Add(hTemp);
  }
  return true;
}
