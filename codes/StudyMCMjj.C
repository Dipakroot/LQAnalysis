/**********************************************************************
 Created on : 29/05/2022
 Purpose    : To study the mjj distribution in MC

// First create the input files as
// for i in `dasgoclient --query='file dataset=/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8/RunIISummer16NanoAODv6-PUMoriond17_Nano25Oct2019_102X_mcRun2_asymptotic_v7-v2/NANOAODSIM status=*'` ; do echo root://cms-xrd-global.cern.ch/$i >> input/files.txt ; done
// Then run on the input file lists.

 Author     : Indranil Das, Visiting Fellow
 Email      : indranil.das@cern.ch | indra.ehep@gmail.com
**********************************************************************/
#if !defined(__CINT__) || defined(__MAKECINT__)

#include <TROOT.h>
#include <TChain.h>
#include <TEntryList.h>
#include <TFile.h>
#include <TProofOutputFile.h>
#include <TSelector.h>
#include <vector>

#include "TH2.h"
#include "TF1.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TPaveStats.h"
#include "TMath.h"
#include "TProof.h"

#include "TParticlePDG.h"
#include "TDatabasePDG.h"

#include "TLorentzVector.h"
#include "TVector3.h"
#include "TLegend.h"
#include "TAxis.h"

#include <fstream>

using namespace std;

#endif

int icounter = 0;
int iccounter = 0;
int ipcounter = 0;

Float_t MinX = 0.;
Float_t MaxX = 20.;

float defaultRatioYmin = 0.1;
float defaultRatioYmax = 2.0;
const int nofPtBins = 10;
float ptBin[nofPtBins+1] = {10., 20., 30., 40., 50., 75., 100., 150., 200., 400., 800.};
TH1F *hptBin = new TH1F("hptBin", "ptbin finder", nofPtBins, ptBin);

int StudyMCMjj()
{
  int CalcRatio(TH1F*& hSimEff, TH1F*& hDataEff, TH1F*& hRatio);
  int PlotCanvas(TH1F*& hSimEff, TH1F*& hDataEff, TH1F*& hRatio);
  void ReadTree(TList*& list, string signal, int year);
  
  const int nofSamples = 2;
  // const char *signals[] = {"inclusive", "Semilept"};
  // int year = 2016;
  //const char *signals[] = {"TuneCUETP8M2T4", "TuneCP5"};
  const char *signals[] = {"TuneCP5", "TuneCUETP8M2T4"};
  int year = 2016;
  // const char *signals[] = {"TuneCH3", "TuneCP5"};
  // int year = 2017;
  //const char *infiles[] = {"fl_inclusive_TuneCUETP8M2T4.txt", "fl_semilept_TuneCP5.txt"};
  
  TList *list  = new TList();
  TH1F *hNGenjets[nofSamples], *hLHEMjj[nofSamples], *hGPMjj[nofSamples], *hGJMjj[nofSamples], *hRJMjj[nofSamples];
  TH1F *hGJPt[nofSamples], *hGJEta[nofSamples], *hGJPhi[nofSamples], *hGJMass[nofSamples];
  TH1F *hNDiffGenjets[nofSamples][nofPtBins], *hGJDiffPt[nofSamples][nofPtBins], *hGJDiffEta[nofSamples][nofPtBins], *hGJDiffPhi[nofSamples][nofPtBins], *hGJDiffMass[nofSamples][nofPtBins];
  TH1F *hRJPt[nofSamples], *hRJPtHLTPF[nofSamples], *hRJPtHLTCalo[nofSamples];

  for(int isample = 0 ; isample < nofSamples ; isample++ ){
    string signal = signals[isample];
    //string infile = infiles[isample];

    hNGenjets[isample] = new TH1F(Form("_NGenJets_%s",signal.data()),Form("%s : NgenJets ",signal.c_str()), 20, 0., 20.);
    hLHEMjj[isample] = new TH1F(Form("_hLHEMjj_%s",signal.data()),Form("%s : hLHEMjj ",signal.c_str()), 160, 40., 120.);
    hGJMjj[isample] = new TH1F(Form("_hGJMjj_%s",signal.data()),Form("%s : hGJMjj ",signal.c_str()), 160, 40., 120.);
    hGPMjj[isample] = new TH1F(Form("_hGPMjj_%s",signal.data()),Form("%s : hGPMjj ",signal.c_str()), 160, 40., 120.);
    hRJMjj[isample] = new TH1F(Form("_hRJMjj_%s",signal.data()),Form("%s : hRJMjj ",signal.c_str()), 160, 40., 120.);
    // hLHEMjj[isample] = new TH1F(Form("_hLHEMjj_%s",signal.data()),Form("%s : hLHEMjj ",signal.c_str()), 16, 40., 120.);
    // hGJMjj[isample] = new TH1F(Form("_hGJMjj_%s",signal.data()),Form("%s : hGJMjj ",signal.c_str()), 16, 40., 120.);
    // hGPMjj[isample] = new TH1F(Form("_hGPMjj_%s",signal.data()),Form("%s : hGPMjj ",signal.c_str()), 16, 40., 120.);
    // hRJMjj[isample] = new TH1F(Form("_hRJMjj_%s",signal.data()),Form("%s : hRJMjj ",signal.c_str()), 16, 40., 120.);
    
    hGJPt[isample] = new TH1F(Form("_hGJPt_%s",signal.data()),Form("%s : hGJPt ",signal.c_str()), 160, 0., 800.);
    hGJEta[isample] = new TH1F(Form("_hGJEta_%s",signal.data()),Form("%s : hGJEta ",signal.c_str()), 200, -5., 5.);
    hGJPhi[isample] = new TH1F(Form("_hGJPhi_%s",signal.data()),Form("%s : hGJPhi ",signal.c_str()), 80, -4., 4.);
    hGJMass[isample] = new TH1F(Form("_hGJMass_%s",signal.data()),Form("%s : hGJMass ",signal.c_str()), 100, 0., 100.);
    for(int ipt = 0 ; ipt < nofPtBins ; ipt++ ){
      hNDiffGenjets[isample][ipt] = new TH1F(Form("_hNGenjets_%s_%d",signal.data(),ipt),Form("%s (%02.1f-%02.1f) : NgenJets ",signal.c_str(),ptBin[ipt],ptBin[ipt+1]), 20, 0., 20.);
      hGJDiffPt[isample][ipt] = new TH1F(Form("_hGJPt_%s_%d",signal.data(),ipt),Form("%s (%02.1f-%02.1f) :  hGJPt ",signal.c_str(),ptBin[ipt],ptBin[ipt+1]), 160, 0., 800.);
      hGJDiffEta[isample][ipt] = new TH1F(Form("_hGJEta_%s_%d",signal.data(),ipt),Form("%s (%02.1f-%02.1f) :  hGJEta ",signal.c_str(),ptBin[ipt],ptBin[ipt+1]), 200, -5., 5.);
      hGJDiffPhi[isample][ipt] = new TH1F(Form("_hGJPhi_%s_%d",signal.data(),ipt),Form("%s (%02.1f-%02.1f) :  hGJPhi ",signal.c_str(),ptBin[ipt],ptBin[ipt+1]), 80, -4., 4.);
      hGJDiffMass[isample][ipt] = new TH1F(Form("_hGJMass_%s_%d",signal.data(),ipt),Form("%s (%02.1f-%02.1f) :  hGJMass ",signal.c_str(),ptBin[ipt],ptBin[ipt+1]), 100, 0., 100.);
    }

    hRJPt[isample] = new TH1F(Form("_hRJPt_%s",signal.data()),Form("%s : hRJPt ",signal.c_str()), 160, 0., 800.);
    hRJPtHLTPF[isample] = new TH1F(Form("_hRJPtHLTPF_%s",signal.data()),Form("%s : hRJPtHLTPF ",signal.c_str()), 160, 0., 800.);
    hRJPtHLTCalo[isample] = new TH1F(Form("_hRJPtHLTCalo_%s",signal.data()),Form("%s : hRJPtHLTCalo ",signal.c_str()), 160, 0., 800.);

    list->Add(hNGenjets[isample]);
    list->Add(hLHEMjj[isample]);
    list->Add(hGJMjj[isample]);
    list->Add(hGPMjj[isample]);
    list->Add(hRJMjj[isample]);

    list->Add(hGJPt[isample]);
    list->Add(hGJEta[isample]);
    list->Add(hGJPhi[isample]);
    list->Add(hGJMass[isample]);
    for(int ipt = 0 ; ipt < nofPtBins ; ipt++ ){
      list->Add(hNDiffGenjets[isample][ipt]);
      list->Add(hGJDiffPt[isample][ipt]);
      list->Add(hGJDiffEta[isample][ipt]);
      list->Add(hGJDiffPhi[isample][ipt]);
      list->Add(hGJDiffMass[isample][ipt]);
    }
    list->Add(hRJPt[isample]);
    list->Add(hRJPtHLTPF[isample]);
    list->Add(hRJPtHLTCalo[isample]);

    ReadTree(list, signal, year);
    
    hNGenjets[isample]->Scale(1/hNGenjets[isample]->Integral());
    hLHEMjj[isample]->Scale(1/hLHEMjj[isample]->Integral());
    hGJMjj[isample]->Scale(1/hGJMjj[isample]->Integral());
    hGPMjj[isample]->Scale(1/hGPMjj[isample]->Integral());
    hRJMjj[isample]->Scale(1/hRJMjj[isample]->Integral());

    hGJPt[isample]->Scale(1/hGJPt[isample]->Integral());
    hGJEta[isample]->Scale(1/hGJEta[isample]->Integral());
    hGJPhi[isample]->Scale(1/hGJPhi[isample]->Integral());
    hGJMass[isample]->Scale(1/hGJMass[isample]->Integral());
    for(int ipt = 0 ; ipt < nofPtBins ; ipt++ ){
      // list->Add(hNDiffGenjets[isample][ipt]);
      // list->Add(hGJDiffPt[isample]);
      // list->Add(hGJDiffEta[isample]);
      // list->Add(hGJDiffPhi[isample]);
      // list->Add(hGJDiffMass[isample]);
      hNDiffGenjets[isample][ipt]->Scale(1/hNDiffGenjets[isample][ipt]->Integral());
      hGJDiffPt[isample][ipt]->Scale(1/hGJDiffPt[isample][ipt]->Integral());
      hGJDiffEta[isample][ipt]->Scale(1/hGJDiffEta[isample][ipt]->Integral());
      hGJDiffPhi[isample][ipt]->Scale(1/hGJDiffPhi[isample][ipt]->Integral());
      hGJDiffMass[isample][ipt]->Scale(1/hGJDiffMass[isample][ipt]->Integral());
    }

    hRJPt[isample]->Scale(1/hRJPt[isample]->Integral());
    hRJPtHLTPF[isample]->Scale(1/hRJPtHLTPF[isample]->Integral());
    hRJPtHLTCalo[isample]->Scale(1/hRJPtHLTCalo[isample]->Integral());
  }//samples loop
  

  TH1F *h1byh2_1;
  CalcRatio(hNGenjets[0],hNGenjets[1],h1byh2_1);
  PlotCanvas(hNGenjets[0],hNGenjets[1],h1byh2_1);

  TH1F *h1byh2_2;
  CalcRatio(hLHEMjj[0],hLHEMjj[1],h1byh2_2);
  PlotCanvas(hLHEMjj[0],hLHEMjj[1],h1byh2_2);

  TH1F *h1byh2_3;
  CalcRatio(hGPMjj[0],hGPMjj[1],h1byh2_3);
  PlotCanvas(hGPMjj[0],hGPMjj[1],h1byh2_3);

  TH1F *h1byh2_4;
  CalcRatio(hGJMjj[0],hGJMjj[1],h1byh2_4);
  PlotCanvas(hGJMjj[0],hGJMjj[1],h1byh2_4);

  TH1F *h1byh2_41;
  CalcRatio(hRJMjj[0],hRJMjj[1],h1byh2_41);
  PlotCanvas(hRJMjj[0],hRJMjj[1],h1byh2_41);

  TH1F *h1byh2_5;
  CalcRatio(hGJPt[0],hGJPt[1],h1byh2_5);
  PlotCanvas(hGJPt[0],hGJPt[1],h1byh2_5);

  TH1F *h1byh2_6;
  CalcRatio(hGJEta[0],hGJEta[1],h1byh2_6);
  PlotCanvas(hGJEta[0],hGJEta[1],h1byh2_6);

  TH1F *h1byh2_7;
  CalcRatio(hGJPhi[0],hGJPhi[1],h1byh2_7);
  PlotCanvas(hGJPhi[0],hGJPhi[1],h1byh2_7);

  TH1F *h1byh2_8;
  CalcRatio(hGJMass[0],hGJMass[1],h1byh2_8);
  PlotCanvas(hGJMass[0],hGJMass[1],h1byh2_8);

  TFile *fout = new TFile("root_files/test/output.root", "recreate");
  TCanvas *canvas1 = 0x0;
  for(int ic=0;ic<iccounter;ic++){
    canvas1 = (TCanvas *)gROOT->GetListOfCanvases()->FindObject(Form("c_%d",ic));
    canvas1->Write();
  }

  for(int isample = 0 ; isample < nofSamples ; isample++ ){
    for(int ipt = 0 ; ipt < nofPtBins ; ipt++ )
      hNDiffGenjets[isample][ipt]->Write();
    for(int ipt = 0 ; ipt < nofPtBins ; ipt++ )
      hGJDiffPt[isample][ipt]->Write();
    for(int ipt = 0 ; ipt < nofPtBins ; ipt++ )
      hGJDiffEta[isample][ipt]->Write();
    for(int ipt = 0 ; ipt < nofPtBins ; ipt++ )
      hGJDiffPhi[isample][ipt]->Write();
    for(int ipt = 0 ; ipt < nofPtBins ; ipt++ )
      hGJDiffMass[isample][ipt]->Write();
    hRJPt[isample]->Write();
    hRJPtHLTPF[isample]->Write();
    hRJPtHLTCalo[isample]->Write();
  }//samples loop
  cout << "Output file : " << fout->GetName() << endl;
  fout->Close();
  delete fout;

  
  
  return true;
}
int CalcRatio(TH1F*& hDataEff, TH1F*& hSimEff, TH1F*& hRatio)
{

  hSimEff->Sumw2();
  hDataEff->Sumw2();

  // cout<<"Data Integral = " << hDataEff->Integral() << endl;
  // cout<<"Sim Integral = " << hSimEff->Integral() << endl;
  // float integral_ratio = hDataEff->Integral() / hSimEff->Integral() ;
  // hDataEff->Scale(1./integral_ratio);

  hRatio = (TH1F*)hDataEff->Clone(Form("hRatio_%d",icounter++));
  hRatio->SetTitle("");
  hRatio->Divide(hSimEff);
  
  // for(int ibin = 1; ibin < hDataEff->GetNbinsX() ; ibin++){
  //   float ratio = hDataEff->GetBinContent(ibin) / hSimEff->GetBinContent(ibin);
  //   if(finitef(ratio)==0) continue;
  //   printf("bin : %03d, Data : %6.4f, Sim  : %6.4f, Ratio : %6.4f\n",ibin,
  // 	   hDataEff->GetBinContent(ibin), hSimEff->GetBinContent(ibin), ratio);
  //   hRatio->SetBinContent(ibin,ratio);
  // }
  
  
  return true;
}


int PlotCanvas(TH1F*& hData, TH1F*& hSim,  TH1F*& hDByS)
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

  //gStyle->SetOptStat(0);
  
  TLegend *legend1=new TLegend(0.1731481,0.209068,0.5388889,0.4622166);
  legend1->SetFillColor(0);
  legend1->SetTextFont(22);
  legend1->SetTextSize(0.07);
  legend1->SetBorderSize(0);
  legend1->AddEntry(hData,Form("%s",hData->GetName()),"lpe");
  legend1->AddEntry(hSim,Form("%s",hSim->GetName()),"lpe");
  legend1->AddEntry(hDByS,Form("%s",hDByS->GetName()),"lpe");
  //legend1->AddEntry(hDByS,Form("Ratio = %5.4f #pm %5.4f",hDByS->GetBinContent(1),hDByS->GetBinError(1)),"lpe");
  //legend1->AddEntry(hDByS,Form("Max Diff = %5.4f",hDByS->GetBinContent(1)),"lpe");
  //legend1->AddEntry(hDByS,Form("Max Diff = %5.4f",hDByS->GetBinContent(2)),"lpe");


  // hSim->SetMinimum(0.0);
  // hSim->SetMaximum(2.0*hSim->GetBinContent(1));
  
  TCanvas *c1 = new TCanvas(Form("c_%d",iccounter), Form("c_%d",iccounter),0,0,1000,800);
  c1->Range(0,0,1,1);
  c1->SetFillColor(0);
  c1->SetBorderMode(0);
  c1->SetBorderSize(2);
  c1->SetFrameBorderMode(0);
  iccounter++;

  TPad *c1_1 = new TPad(Form("pad_%d",ipcounter), Form("pad_%d",ipcounter),0.01,0.01,0.99,0.33);
  c1_1->Draw();
  c1_1->cd();
  c1_1->SetTopMargin(0.01);
  c1_1->SetBottomMargin(0.3);
  c1_1->SetRightMargin(0.1);
  c1_1->SetFillStyle(0);
  c1_1->SetFillColor(0);
  c1_1->SetTickx();
  c1_1->SetTicky();
  c1_1->SetGridy();
  ipcounter++;

  c1_1->SetTopMargin(0.03276794);

  //hDByS->SetAxisRange(MinX,MaxX);
  hDByS->Draw("e1p");
  
  hDByS->SetMinimum(defaultRatioYmin);
  hDByS->SetMaximum(defaultRatioYmax);
  //hDByS->GetYaxis()->SetNdivisions(2);
  hDByS->GetYaxis()->SetNdivisions(5);
  //hDByS->SetTitle(";"+xTitle+";"+yTitle2);
  hDByS->GetXaxis()->SetTitleSize(0.14);
  hDByS->GetXaxis()->SetLabelSize(0.14);
  hDByS->GetXaxis()->SetLabelOffset(0.016);
  hDByS->GetYaxis()->SetLabelSize(0.11);
  hDByS->GetYaxis()->SetTitleSize(0.14);
  hDByS->GetYaxis()->SetTitleOffset(0.34);
  hDByS->GetYaxis()->SetTitle(Form("Data/Sim"));
  //hDByS->GetXaxis()->SetTitle(Form("p_{T} GeV/c"));
  hDByS->GetXaxis()->SetTitle(Form("arb"));
  //hDByS->GetXaxis()->SetTitle(Form("y"));
  hDByS->GetYaxis()->SetTickLength(0.01);
  
  c1->cd();

  TPad *c1_2 = new TPad(Form("pad_%d",ipcounter), Form("pad_%d",ipcounter),0.01,0.33,0.99,0.99);
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
  ipcounter++;

  c1_2->SetBottomMargin(0.04571135);

  //hSim->SetAxisRange(MinX,MaxX);
  hSim->Draw("e1p");
  hData->Draw("e1p sames");
  //hSim->GetXaxis()->SetTitle("p_{T} GeV/c");
  //hSim->GetYaxis()->SetTitle(Form("Counts per %2.0f MeV/c^{2}",1000.0*hSim->GetBinWidth(3)));
  hSim->GetYaxis()->SetTitle("Counts");
  hSim->SetLabelSize(0.0);
  hSim->GetXaxis()->SetTitleSize(0.00);
  hSim->GetYaxis()->SetLabelSize(0.07);
  hSim->GetYaxis()->SetTitleSize(0.05);
  hSim->GetYaxis()->SetTitleOffset(1.0);
  hSim->GetYaxis()->SetTickLength(0.01);
  
  legend1->Draw();
  
  c1->Update();

  
  return true;

}

//_____________________________________________________________________________
bool SelectTTbarChannel(Int_t nLHEPart_, Int_t *LHEPart_pdgId_, int *slType){

    bool isOne_u = false, isOne_d = false, isOne_c = false, isOne_s = false;
    bool isTwo_u = false, isTwo_d = false, isTwo_c = false, isTwo_s = false;
    bool isOne_e = false, isOne_m = false, isOne_t = false;
    bool isTwo_e = false, isTwo_m = false, isTwo_t = false;
    bool isOne_nu_e = false, isOne_nu_m = false, isOne_nu_t = false;
    bool isTwo_nu_e = false, isTwo_nu_m = false, isTwo_nu_t = false;
    
    for (int imc = (nLHEPart_-4) ; imc < nLHEPart_ ; imc++ ){      //Check the last four particles


      if(abs(LHEPart_pdgId_[imc])==1 and isOne_d) isTwo_d = true; // Two must be above one lepton/parton condition
      if(abs(LHEPart_pdgId_[imc])==1 and !isOne_d) isOne_d = true;
      if(abs(LHEPart_pdgId_[imc])==2 and isOne_u) isTwo_u = true;
      if(abs(LHEPart_pdgId_[imc])==2 and !isOne_u) isOne_u = true;
      if(abs(LHEPart_pdgId_[imc])==3 and isOne_s) isTwo_s = true;
      if(abs(LHEPart_pdgId_[imc])==3 and !isOne_s) isOne_s = true;
      if(abs(LHEPart_pdgId_[imc])==4 and isOne_c) isTwo_c = true;
      if(abs(LHEPart_pdgId_[imc])==4 and !isOne_c) isOne_c = true;

      if(abs(LHEPart_pdgId_[imc])==11 and isOne_e) isTwo_e = true;
      if(abs(LHEPart_pdgId_[imc])==11 and !isOne_e) isOne_e = true;
      if(abs(LHEPart_pdgId_[imc])==13 and isOne_m) isTwo_m = true;
      if(abs(LHEPart_pdgId_[imc])==13 and !isOne_m) isOne_m = true;
      if(abs(LHEPart_pdgId_[imc])==15 and isOne_t) isTwo_t = true;
      if(abs(LHEPart_pdgId_[imc])==15 and !isOne_t) isOne_t = true;


      if(abs(LHEPart_pdgId_[imc])==12 and isOne_nu_e) isTwo_nu_e = true;
      if(abs(LHEPart_pdgId_[imc])==12 and !isOne_nu_e) isOne_nu_e = true;
      if(abs(LHEPart_pdgId_[imc])==14 and isOne_nu_m) isTwo_nu_m = true;
      if(abs(LHEPart_pdgId_[imc])==14 and !isOne_nu_m) isOne_nu_m = true;
      if(abs(LHEPart_pdgId_[imc])==16 and isOne_nu_t) isTwo_nu_t = true;
      if(abs(LHEPart_pdgId_[imc])==16 and !isOne_nu_t) isOne_nu_t = true;

      
      
    }// mc particle loop
    
    bool isSemilepton = false, isDilepton = false, isHadronic = false;

    bool isSameFlavlepton = (isTwo_nu_e and isTwo_e) or (isTwo_nu_m and isTwo_m) or (isTwo_nu_t and isTwo_t) ;
    bool isDiffFlavlepton = (isOne_e and isOne_nu_e and isOne_m and isOne_nu_m) 
                              or (isOne_e and isOne_nu_e and isOne_t and isOne_nu_t) 
                              or (isOne_m and isOne_nu_m and isOne_t and isOne_nu_t);
    if(isSameFlavlepton or isDiffFlavlepton){
      isDilepton = true;
      //_kFType = 11;
      // nofDileptonic++ ;
      //printf("Event type : dileptonic\n");
    }

    if(!isDilepton){
      bool isFourHadron1 = isOne_u and isOne_d and isOne_c and isOne_s;
      bool isFourHadron2 = (isTwo_u and isOne_d and isOne_c) or (isTwo_u and isOne_d and isOne_s) or (isTwo_u and isOne_c and isOne_s) ;
      bool isFourHadron3 = (isTwo_d and isOne_u and isOne_c) or (isTwo_d and isOne_u and isOne_s) or (isTwo_d and isOne_c and isOne_s) ;
      bool isFourHadron4 = (isTwo_c and isOne_u and isOne_d) or (isTwo_c and isOne_u and isOne_s) or (isTwo_c and isOne_d and isOne_s) ;
      bool isFourHadron5 = (isTwo_s and isOne_u and isOne_d) or (isTwo_s and isOne_u and isOne_c) or (isTwo_s and isOne_d and isOne_c) ;
      bool isFourHadron6 = (isTwo_u and isTwo_d) or (isTwo_u and isTwo_c) or (isTwo_u and isTwo_s) or (isTwo_d and isTwo_c) or (isTwo_d and isTwo_s) or (isTwo_c and isTwo_s);
      if(isFourHadron1 or isFourHadron2 or isFourHadron3 or isFourHadron4 or isFourHadron5 or isFourHadron6){
	isHadronic = true;
	//_kFType = 12;
	// nofHadronic++;
	//printf("Event type : hadronic\n");
      }
    }
    
    if(!isDilepton and !isHadronic){
      bool isOneLepton = (isOne_e and isOne_nu_e) or (isOne_m and isOne_nu_m) or (isOne_t and isOne_nu_t);
      bool isOneHadron = (isOne_u and isOne_d) or (isOne_u and isOne_c) or (isOne_u and isOne_s) or (isOne_d and isOne_c) or (isOne_d and isOne_s) or (isOne_c and isOne_s) ;
      if(isOneLepton and isOneLepton){
	isSemilepton = true;
	//_kFType = 13;
	
	// if((isOne_c and isOne_s) and (isOne_e and isOne_nu_e)) nofcsEle++;
	// if((isOne_c and isOne_s) and (isOne_m and isOne_nu_m)) nofcsMu++;
	// if((isOne_c and isOne_s) and (isOne_t and isOne_nu_t)) nofcsTau++;
	
	//enum SlType { kSlEle, kSlMu, kSlTau, kSlcs, kSlud, kSlus,  kSldc};
	// if(isOne_e and isOne_nu_e) slType = kSlEle;
	// if(isOne_m and isOne_nu_m) slType = kSlMu;
	// if(isOne_t and isOne_nu_t) slType = kSlTau;
	// if(isOne_c and isOne_s) slType = kSlcs;
	// if(isOne_u and isOne_d) slType = kSlud;
	// if(isOne_u and isOne_s) slType = kSlus;
	// if(isOne_d and isOne_c) slType = kSldc;
	
	// if(isOne_e and isOne_nu_e) slType[0] = 11;
	// if(isOne_m and isOne_nu_m) slType[0] = 13;
	// if(isOne_t and isOne_nu_t) slType[0] = 15;
	// if(isOne_c and isOne_s) slType[1] = 34;
	// if(isOne_u and isOne_d) slType[1] = 12;
	// if(isOne_u and isOne_s) slType[1] = 23;
	// if(isOne_d and isOne_c) slType[1] = 14;
	
	
	slType[0] = (isOne_e and isOne_nu_e) ? 1 : 0;
	slType[1] = (isOne_m and isOne_nu_m) ? 1 : 0;
	slType[2] = (isOne_t and isOne_nu_t) ? 1 : 0;
	slType[3] = (isOne_c and isOne_s) ? 1 : 0;
	slType[4] = (isOne_u and isOne_d) ? 1 : 0;
	slType[5] = (isOne_u and isOne_s) ? 1 : 0;
	slType[6] = (isOne_d and isOne_c) ? 1 : 0;
	
	// nofSemiLeptonic++;
	//printf("Event type : semileptonic\n");
      }
    }
    
    return isSemilepton;
}

void ReadTree(TList*& list, string signal, int year)
{

  UInt_t    nGenPart_;
  Float_t   GenPart_pt_[300];
  Float_t   GenPart_eta_[300];
  Float_t   GenPart_phi_[300];
  Float_t   GenPart_mass_[300];
  Int_t     GenPart_genPartIdxMother_[300];
  Int_t     GenPart_pdgId_[300];
  Int_t     GenPart_status_[300];
  Int_t     GenPart_statusFlags_[300];

  UInt_t    nGenJet_;    
  Float_t   GenJet_pt_[100];
  Float_t   GenJet_eta_[100];
  Float_t   GenJet_phi_[100];
  Float_t   GenJet_mass_[100];
  Int_t   GenJet_partonFlavour_[100];
  Int_t   GenJet_hadronFlavour_[100];

  UInt_t    nLHEPart_;    
  Float_t   LHEPart_pt_[100];
  Float_t   LHEPart_eta_[100];
  Float_t   LHEPart_phi_[100];
  Float_t   LHEPart_mass_[100];
  Int_t   LHEPart_pdgId_[100];
  
  UInt_t          nJet_;
  Float_t         jetPt_[200];
  Float_t         jetEta_[200];
  Float_t         jetPhi_[200];
  Float_t         jetMass_[200];
  Int_t           jetHadFlvr_[200];
  Int_t           jetPartFlvr_[200];
  Int_t           jetGenJetIdx_[200];
  Float_t         jetRawFactor_[200];
  
  Bool_t   HLT_AK4CaloJet30_;
  Bool_t   HLT_AK4PFJet30_;

  UInt_t nPSWeight_;
  Float_t PSWeight_[200];
  
  int slType[7];
  int totSlType[7];
  for(int itype=0;itype<7;itype++)
    totSlType[itype] = 0;
  
  bool isSemilepton = false, isDilepton = false, isHadronic = false;;
  Long64_t totEvt = 0, totSemilepton = 0;
  TLorentzVector pLHE[2], pGP[2], pGJ[2], pRJ[2], pTemp;
  
  // string inpath_tree = Form("/run/media/indra/DHEP_Storage_3/Data/NanoAOD/Skim_NanoAOD1/%d",year);
  // string treelist = "/tmp/fl_skim_tree_list.txt";
  // string command = Form("find %s -name \"TTbarPowheg_%s_Skim_NanoAOD_*.root\" > %s",inpath_tree.data(),signal.data(),treelist.data());
  // system(command.c_str());

  string inpath_tree = Form("/Data/root_files/AOD_files/NanoAOD_framework/NanoAOD/%d",year);
  string treelist = "/tmp/fl_skim_tree_list.txt";
  string command = Form("find %s -name \"TT*_%s_*.root\" > %s",inpath_tree.data(),signal.data(),treelist.data());
  system(command.c_str());
  
  cout<<"filepath : " << inpath_tree.data() << endl;
  string flist;
  ifstream fin(treelist);
  TChain *tr	= new TChain("Events");
  double totMCEvents = 0;
  while ( getline(fin,flist)){
    //cout << "Filename : " << flist << endl;
    tr->Add(flist.c_str());
    // TFile *fin = TFile::Open(flist.c_str());
    // TH1D *hEvents = (TH1D *)fin->Get("hEvents");
    // totMCEvents += hEvents->GetEntries()/2.0;
  }
  fin.close();

  tr->SetBranchAddress("nGenPart", &nGenPart_);
  tr->SetBranchAddress("GenPart_pt", &GenPart_pt_);
  tr->SetBranchAddress("GenPart_eta", &GenPart_eta_);
  tr->SetBranchAddress("GenPart_phi", &GenPart_phi_);
  tr->SetBranchAddress("GenPart_mass", &GenPart_mass_);
  tr->SetBranchAddress("GenPart_genPartIdxMother", &GenPart_genPartIdxMother_);
  tr->SetBranchAddress("GenPart_pdgId", &GenPart_pdgId_);
  tr->SetBranchAddress("GenPart_status", &GenPart_status_);
  tr->SetBranchAddress("GenPart_statusFlags", &GenPart_statusFlags_);

  tr->SetBranchAddress("nGenJet", &nGenJet_);
  tr->SetBranchAddress("GenJet_pt", &GenJet_pt_);
  tr->SetBranchAddress("GenJet_eta", &GenJet_eta_);
  tr->SetBranchAddress("GenJet_phi", &GenJet_phi_);
  tr->SetBranchAddress("GenJet_mass", &GenJet_mass_);
  tr->SetBranchAddress("GenJet_partonFlavour", &GenJet_partonFlavour_);
  tr->SetBranchAddress("GenJet_hadronFlavour", &GenJet_hadronFlavour_);
  
  tr->SetBranchAddress("nLHEPart", &nLHEPart_);
  tr->SetBranchAddress("LHEPart_pt", &LHEPart_pt_);
  tr->SetBranchAddress("LHEPart_eta", &LHEPart_eta_);
  tr->SetBranchAddress("LHEPart_phi", &LHEPart_phi_);
  tr->SetBranchAddress("LHEPart_mass", &LHEPart_mass_);
  tr->SetBranchAddress("LHEPart_pdgId", &LHEPart_pdgId_);
  
  tr->SetBranchAddress("nJet", &nJet_);
  tr->SetBranchAddress("Jet_pt", &jetPt_);
  tr->SetBranchAddress("Jet_eta", &jetEta_);
  tr->SetBranchAddress("Jet_phi", &jetPhi_);
  tr->SetBranchAddress("Jet_mass", &jetMass_);
  tr->SetBranchAddress("Jet_partonFlavour", &jetPartFlvr_);
  tr->SetBranchAddress("Jet_hadronFlavour", &jetHadFlvr_);
  tr->SetBranchAddress("Jet_genJetIdx", &jetGenJetIdx_);
  tr->SetBranchAddress("Jet_rawFactor", &jetRawFactor_);

  tr->SetBranchAddress("HLT_AK4CaloJet30", &HLT_AK4CaloJet30_);
  tr->SetBranchAddress("HLT_AK4PFJet30", &HLT_AK4PFJet30_);
  
  tr->SetBranchAddress("PSWeight", &PSWeight_);	
  tr->SetBranchAddress("nPSWeight", &nPSWeight_);

  bool isCP5 = false; 
  if(signal=="TuneCP5" or signal=="Semilept")
    isCP5 = true;
  
  cout << "Signal :" << signal << ", Total Entries : " << tr->GetEntries() << endl;
  for(int ievent = 0 ; ievent < tr->GetEntries() ; ievent++){
  //totMCEvents /= 100;
  //for(int ievent = 0 ; ievent < tr->GetEntries()/100 ; ievent++){
  //totMCEvents /= 10;
  //for(int ievent = 0 ; ievent < tr->GetEntries()/10 ; ievent++){
  //for(int ievent = 0 ; ievent < 4 ; ievent++){
    
    //cout<<"\niEvent : " << ievent <<endl;
    if(ievent%10000==0){
      if(isCP5){
	cout<<"iEvent : " << ievent << ", PSWeight[1] " << PSWeight_[1] << ", PSWeight_[3] " << PSWeight_[3] << endl;
      }else{
	cout<<"iEvent : " << ievent <<endl;
      }
    }

    tr->GetEntry(ievent);
    totEvt++;
    isSemilepton = SelectTTbarChannel(nLHEPart_, LHEPart_pdgId_, slType);
    if(!isSemilepton) continue;
    
    
    // for (unsigned int imc = 0 ; imc < nLHEPart_ ; imc++ ){      
    //   TParticlePDG *partPDG = TDatabasePDG::Instance()->GetParticle(LHEPart_pdgId_[imc]);
    //   if(!partPDG)
    // 	printf("\t LHE : %03d, PDG : %5d ( noPDGname), (Pt, Eta, Phi, Mass) = (%5.2f, %5.2f, %5.2f, %5.2f)\n", 
    // 	       imc, LHEPart_pdgId_[imc], LHEPart_pt_[imc], 
    // 	       LHEPart_eta_[imc] , LHEPart_phi_[imc], LHEPart_mass_[imc]);
    //   else
    // 	printf("\t LHE : %03d, PDG : %5d (%7s), (Pt, Eta, Phi, Mass) = (%5.2f, %5.2f, %5.2f, %5.2f)\n", 
    // 	       imc, LHEPart_pdgId_[imc], partPDG->GetName(), LHEPart_pt_[imc],
    // 	       LHEPart_eta_[imc] , LHEPart_phi_[imc], LHEPart_mass_[imc]);
      
    // }// mc particle loop
    
    // // // int nofPromptGluon = 0;
    // // // for (unsigned int imc = 0 ; imc < nGenPart_ ; imc++ ){      
    // // //   if(GenPart_pdgId_[imc]==21 and nofPromptGluon==0 and GenPart_genPartIdxMother_[imc]==0){
    // // // 	nofPromptGluon++;
    // // //   }
    // // // }
    
    // //for (unsigned int imc = 0 ; imc < nGenPart_ ; imc++ ){      
    // for (unsigned int imc = 0 ; imc < 20 ; imc++ ){      
    //   TParticlePDG *partPDG = TDatabasePDG::Instance()->GetParticle(GenPart_pdgId_[imc]);
    //   //if(nofPromptGluon==0){
    //   if(!partPDG)
    // 	printf("\t part : %03d, PDG : %5d ( noPDGname), status : %2d, (Pt, Eta, Phi, Mass) = (%5.2f, %5.2f, %5.2f, %5.2f), Mother-id : %03d\n", 
    // 	       imc, GenPart_pdgId_[imc], GenPart_status_[imc], GenPart_pt_[imc], 
    // 	       GenPart_eta_[imc] , GenPart_phi_[imc], GenPart_mass_[imc], GenPart_genPartIdxMother_[imc]
    // 	       );
    //   else
    // 	printf("\t part : %03d, PDG : %5d (%7s), status : %2d, (Pt, Eta, Phi, Mass) = (%5.2f, %5.2f, %5.2f, %5.2f), Mother-id : %03d\n", 
    // 	       imc, GenPart_pdgId_[imc], partPDG->GetName(), GenPart_status_[imc], GenPart_pt_[imc],
    // 	       GenPart_eta_[imc] , GenPart_phi_[imc], GenPart_mass_[imc], GenPart_genPartIdxMother_[imc]
    // 	       );
    //   //}
    // }
    
    // for (unsigned int imc = 0 ; imc < nGenJet_ ; imc++ ){      
    //   TParticlePDG *partPDG = TDatabasePDG::Instance()->GetParticle(GenJet_partonFlavour_[imc]);
    //   if(!partPDG)
    // 	printf("\t GenJet : %03d, PDG : %5d ( noPDGname), (Pt, Eta, Phi, Mass) = (%5.2f, %5.2f, %5.2f, %5.2f)\n", 
    // 	       imc, GenJet_partonFlavour_[imc], GenJet_pt_[imc], GenJet_eta_[imc] , GenJet_phi_[imc], GenJet_mass_[imc]);
    //   else
    // 	printf("\t GenJet : %03d, PDG : %5d (%7s), (Pt, Eta, Phi, Mass) = (%5.2f, %5.2f, %5.2f, %5.2f)\n", 
    // 	       imc, GenJet_partonFlavour_[imc], partPDG->GetName(), GenJet_pt_[imc], GenJet_eta_[imc] , GenJet_phi_[imc], GenJet_mass_[imc]);
      
    // }


    // for (unsigned int imc = 0 ; imc < nJet_ ; imc++ ){      
    //   TParticlePDG *partPDG = TDatabasePDG::Instance()->GetParticle(jetPartFlvr_[imc]);
    //   if(!partPDG)
    // 	printf("\t RecJet : %03d, PDG : %5d ( noPDGname), Gen : %d, (Pt, Eta, Phi, Mass) = (%5.2f, %5.2f, %5.2f, %5.2f)\n", 
    // 	       imc, jetPartFlvr_[imc], jetGenJetIdx_[imc], jetPt_[imc], jetEta_[imc] , jetPhi_[imc], jetMass_[imc]);
    //   else
    // 	printf("\t RecJet : %03d, PDG : %5d (%7s), Gen : %d, (Pt, Eta, Phi, Mass) = (%5.2f, %5.2f, %5.2f, %5.2f)\n", 
    // 	       imc, jetPartFlvr_[imc], partPDG->GetName(), jetGenJetIdx_[imc], jetPt_[imc], jetEta_[imc] , jetPhi_[imc], jetMass_[imc]);
      
    // }
	       
    int lhePDG[2];
    int nPLHE = 0; lhePDG[0] = -1; lhePDG[1] = -1;
    for (unsigned int imc = nLHEPart_-4 ; imc < nLHEPart_ ; imc++ ){      
      if(abs(LHEPart_pdgId_[imc])>=1 and abs(LHEPart_pdgId_[imc])<=4){
    	pLHE[nPLHE].SetPtEtaPhiM(LHEPart_pt_[imc],LHEPart_eta_[imc] , LHEPart_phi_[imc], LHEPart_mass_[imc]);
    	lhePDG[nPLHE] = LHEPart_pdgId_[imc];
    	nPLHE++;
      }
    }// mc particle loop
    //cout << "nPLHE" << nPLHE << endl;

    // //for (unsigned int imc = 0 ; imc < nGenPart_ ; imc++ ){      
    // for (unsigned int imc = 0 ; imc < 20 ; imc++ ){      
    //   TParticlePDG *partPDG = TDatabasePDG::Instance()->GetParticle(GenPart_pdgId_[imc]);
    //   //if(nofPromptGluon==0){
    //   if(!partPDG)
    // 	printf("\t part : %03d, PDG : %5d ( noPDGname), status : %2d, (Pt, Eta, Phi, Mass) = (%5.2f, %5.2f, %5.2f, %5.2f), Mother-id : %03d\n", 
    // 	       imc, GenPart_pdgId_[imc], GenPart_status_[imc], GenPart_pt_[imc], 
    // 	       GenPart_eta_[imc] , GenPart_phi_[imc], GenPart_mass_[imc], GenPart_genPartIdxMother_[imc]
    // 	       );
    //   else
    // 	printf("\t part : %03d, PDG : %5d (%7s), status : %2d, (Pt, Eta, Phi, Mass) = (%5.2f, %5.2f, %5.2f, %5.2f), Mother-id : %03d\n", 
    // 	       imc, GenPart_pdgId_[imc], partPDG->GetName(), GenPart_status_[imc], GenPart_pt_[imc],
    // 	       GenPart_eta_[imc] , GenPart_phi_[imc], GenPart_mass_[imc], GenPart_genPartIdxMother_[imc]
    // 	       );
    //   //}
    // }

    map<double,int> delRtoID0;
    map<double,int> delRtoID1;
    for (unsigned int imc = 0 ; imc < nGenPart_ ; imc++ ){      
      pTemp.SetPtEtaPhiM(GenPart_pt_[imc], GenPart_eta_[imc] , GenPart_phi_[imc], GenPart_mass_[imc]);
      if(abs(GenPart_pdgId_[imc])==abs(lhePDG[0])){
	delRtoID0.insert( pair<double,int> (pTemp.DeltaR(pLHE[0]), imc) );
	//cout <<"\tFound match 0 for " << imc << endl;
      }
      if(abs(GenPart_pdgId_[imc])==abs(lhePDG[1])){
	delRtoID1.insert( pair<double,int> (pTemp.DeltaR(pLHE[1]), imc) );
	//cout <<"\tFound match 1 for " << imc << endl;
      }
    }

    float DeltaRCut = 0.1;
    map<double, int>::iterator itr_ptr0, itr_ptr1;
    bool hasGPmatchLHE = false;
    if(delRtoID0.size()>0 and delRtoID1.size()>0){
      itr_ptr0 = delRtoID0.begin();
      itr_ptr1 = delRtoID1.begin();
      if(itr_ptr0->second != itr_ptr1->second){
	if(itr_ptr0->first < DeltaRCut and itr_ptr1->first < DeltaRCut ){
	  int imc0 = itr_ptr0->second;
	  int imc1 = itr_ptr1->second;
	  pGP[0].SetPtEtaPhiM(GenPart_pt_[imc0], GenPart_eta_[imc0] , GenPart_phi_[imc0], GenPart_mass_[imc0]);
	  pGP[1].SetPtEtaPhiM(GenPart_pt_[imc1], GenPart_eta_[imc1] , GenPart_phi_[imc1], GenPart_mass_[imc1]);
	  hasGPmatchLHE = true;
	}//DeltaRcut
      }//confirm that both of the imc indices are not same
    }
    

    delRtoID0.clear();
    delRtoID1.clear();
    // map<double,int> delRtoID0;
    // map<double,int> delRtoID1;
    for (unsigned int imc = 0 ; imc < nGenJet_ ; imc++ ){      
      
      //if(GenJet_pt_[imc]<25.0 or abs(GenJet_eta_[imc])<2.4) continue;
      
      pTemp.SetPtEtaPhiM(GenJet_pt_[imc], GenJet_eta_[imc] , GenJet_phi_[imc], GenJet_mass_[imc]);
      if(abs(GenJet_partonFlavour_[imc])==abs(lhePDG[0]) or GenJet_partonFlavour_[imc]==0 or GenJet_partonFlavour_[imc]==21){
	delRtoID0.insert( pair<double,int> (pTemp.DeltaR(pLHE[0]), imc) );
	//cout <<"\tFound match 0 for " << imc << endl;
      }
      if(abs(GenJet_partonFlavour_[imc])==abs(lhePDG[1]) or GenJet_partonFlavour_[imc]==0 or GenJet_partonFlavour_[imc]==21){
	delRtoID1.insert( pair<double,int> (pTemp.DeltaR(pLHE[1]), imc) );
	//cout <<"\tFound match 1 for " << imc << endl;
      }
    }
    // for(map <double, int>::iterator itr_pt = delRtoID0.begin(); itr_pt != delRtoID0.end(); ++itr_pt){
    //   cout << "\t0 : First : " << itr_pt->first << ", second " << itr_pt->second << endl;
    // }
    // for(map <double, int>::iterator itr_pt = delRtoID1.begin(); itr_pt != delRtoID1.end(); ++itr_pt){
    //   cout << "\t1 : First : " << itr_pt->first << ", second " << itr_pt->second << endl;
    // }

    DeltaRCut = 0.1;
    bool hasGJmatchLHE = false;
    int genJetMatch[2];
    genJetMatch[0] = -1; genJetMatch[1] = -1;
    if(delRtoID0.size()>0 and delRtoID1.size()>0){
      itr_ptr0 = delRtoID0.begin();
      itr_ptr1 = delRtoID1.begin();
      if(itr_ptr0->second != itr_ptr1->second){
	if(itr_ptr0->first < DeltaRCut and itr_ptr1->first < DeltaRCut ){
	  int imc0 = itr_ptr0->second;
	  int imc1 = itr_ptr1->second;
	  pGJ[0].SetPtEtaPhiM(GenJet_pt_[imc0], GenJet_eta_[imc0] , GenJet_phi_[imc0], GenJet_mass_[imc0]);
	  pGJ[1].SetPtEtaPhiM(GenJet_pt_[imc1], GenJet_eta_[imc1] , GenJet_phi_[imc1], GenJet_mass_[imc1]);
	  hasGJmatchLHE = true;
	  genJetMatch[0] = imc0;
	  genJetMatch[1] = imc1;
	}//DeltaRcut
      }//confirm that both of the imc indices are not same
    }

    bool hasRJmatchGJ = false;
    bool hasRJmatchGJ0 = false, hasRJmatchGJ1 = false;
    if(hasGJmatchLHE){
      for (unsigned int imc = 0 ; imc < nJet_ ; imc++ ){      
	
	//if(jetPt_[imc]<25.0 or abs(jetEta_[imc])<2.4) continue;

	if(genJetMatch[0]==jetGenJetIdx_[imc]){
	  pRJ[0].SetPtEtaPhiM(jetPt_[imc]*(1-jetRawFactor_[imc]), jetEta_[imc] , jetPhi_[imc], jetMass_[imc]*(1-jetRawFactor_[imc]));
	  hasRJmatchGJ0 = true;
	}
	if(genJetMatch[1]==jetGenJetIdx_[imc]){
	  pRJ[1].SetPtEtaPhiM(jetPt_[imc]*(1-jetRawFactor_[imc]), jetEta_[imc] , jetPhi_[imc], jetMass_[imc]*(1-jetRawFactor_[imc]));
	  hasRJmatchGJ1 = true;
	}
      }
      if(hasRJmatchGJ0 and hasRJmatchGJ1) hasRJmatchGJ = true;
    }
    
    for(int itype=0;itype<7;itype++)
      totSlType[itype] += slType[itype];
    
    ((TH1F *) list->FindObject( Form("_hLHEMjj_%s",signal.data()) ))->Fill((pLHE[0]+pLHE[1]).M());
    if(hasGPmatchLHE) {
      if(isCP5 and nPSWeight_==4)
	((TH1F *) list->FindObject( Form("_hGPMjj_%s",signal.data()) ))->Fill((pGP[0]+pGP[1]).M(), PSWeight_[1]);
      else
	((TH1F *) list->FindObject( Form("_hGPMjj_%s",signal.data()) ))->Fill((pGP[0]+pGP[1]).M());
    }
    //if(hasGJmatchLHE and pGJ[0].M()<5.0 and pGJ[1].M()<5.0){
    if(hasGJmatchLHE){
      ((TH1F *) list->FindObject( Form("_NGenJets_%s",signal.data()) ))->Fill(nGenJet_);

      if(isCP5 and nPSWeight_==4)
	((TH1F *) list->FindObject( Form("_hGJMjj_%s",signal.data()) ))->Fill((pGJ[0]+pGJ[1]).M(), PSWeight_[1]);
      else
	((TH1F *) list->FindObject( Form("_hGJMjj_%s",signal.data()) ))->Fill((pGJ[0]+pGJ[1]).M());

      ((TH1F *) list->FindObject( Form("_hGJPt_%s",signal.data()) ))->Fill(pGJ[0].Pt());
      ((TH1F *) list->FindObject( Form("_hGJPt_%s",signal.data()) ))->Fill(pGJ[1].Pt());

      ((TH1F *) list->FindObject( Form("_hGJEta_%s",signal.data()) ))->Fill(pGJ[0].Eta());
      ((TH1F *) list->FindObject( Form("_hGJEta_%s",signal.data()) ))->Fill(pGJ[1].Eta());

      ((TH1F *) list->FindObject( Form("_hGJPhi_%s",signal.data()) ))->Fill(pGJ[0].Phi());
      ((TH1F *) list->FindObject( Form("_hGJPhi_%s",signal.data()) ))->Fill(pGJ[1].Phi());

      ((TH1F *) list->FindObject( Form("_hGJMass_%s",signal.data()) ))->Fill(pGJ[0].M());
      ((TH1F *) list->FindObject( Form("_hGJMass_%s",signal.data()) ))->Fill(pGJ[1].M());
      
      if(pGJ[0].Pt()>=ptBin[0] and pGJ[0].Pt()<=ptBin[nofPtBins]){
	int ptBin0 = hptBin->GetXaxis()->FindBin(pGJ[0].Pt())-1;
	//cout<<"ptBin0 : " << ptBin0<<endl;
	((TH1F *) list->FindObject( Form("_hNGenjets_%s_%d",signal.data(),ptBin0) ))->Fill(nGenJet_);
	((TH1F *) list->FindObject( Form("_hGJPt_%s_%d",signal.data(),ptBin0) ))->Fill(pGJ[0].Pt());
	((TH1F *) list->FindObject( Form("_hGJEta_%s_%d",signal.data(),ptBin0) ))->Fill(pGJ[0].Eta());
	((TH1F *) list->FindObject( Form("_hGJPhi_%s_%d",signal.data(),ptBin0) ))->Fill(pGJ[0].Phi());
	((TH1F *) list->FindObject( Form("_hGJMass_%s_%d",signal.data(),ptBin0) ))->Fill(pGJ[0].M());
      }
      if(pGJ[1].Pt()>=ptBin[0] and pGJ[1].Pt()<=ptBin[nofPtBins]){
       	int ptBin1 = hptBin->GetXaxis()->FindBin(pGJ[1].Pt())-1;
	//cout<<"ptBin1 : "<< ptBin1 << endl;
	((TH1F *) list->FindObject( Form("_hNGenjets_%s_%d",signal.data(),ptBin1) ))->Fill(nGenJet_);
	((TH1F *) list->FindObject( Form("_hGJPt_%s_%d",signal.data(),ptBin1) ))->Fill(pGJ[1].Pt());
       	((TH1F *) list->FindObject( Form("_hGJEta_%s_%d",signal.data(),ptBin1) ))->Fill(pGJ[1].Eta());
       	((TH1F *) list->FindObject( Form("_hGJPhi_%s_%d",signal.data(),ptBin1) ))->Fill(pGJ[1].Phi());
       	((TH1F *) list->FindObject( Form("_hGJMass_%s_%d",signal.data(),ptBin1) ))->Fill(pGJ[1].M());
      }
    }
    if(hasRJmatchGJ){
      ((TH1F *) list->FindObject( Form("_hRJMjj_%s",signal.data()) ))->Fill((pRJ[0]+pRJ[1]).M());
      ((TH1F *) list->FindObject( Form("_hRJPt_%s",signal.data()) ))->Fill(pRJ[0].Pt());
      ((TH1F *) list->FindObject( Form("_hRJPt_%s",signal.data()) ))->Fill(pRJ[1].Pt());
      if(HLT_AK4CaloJet30_){
	((TH1F *) list->FindObject( Form("_hRJPtHLTCalo_%s",signal.data()) ))->Fill(pRJ[0].Pt());
	((TH1F *) list->FindObject( Form("_hRJPtHLTCalo_%s",signal.data()) ))->Fill(pRJ[1].Pt());
      }
      if(HLT_AK4PFJet30_){
	((TH1F *) list->FindObject( Form("_hRJPtHLTPF_%s",signal.data()) ))->Fill(pRJ[0].Pt());
	((TH1F *) list->FindObject( Form("_hRJPtHLTPF_%s",signal.data()) ))->Fill(pRJ[1].Pt());
      }
    }
    totSemilepton++;

  }// event loop

  // cout << "Signal :" << signal << ", Total MC Events : " << totMCEvents
  //      << ", Total Skim Events : " << totEvt 
  //      << ", Total Semilep Events :" << totSemilepton << ", Fraction : " << double(totSemilepton*1.0/totEvt) << endl;
  // for(int itype=0;itype<7;itype++)
  //   printf("totSlType[%d] = %d, BrFrac : %f, ttbarFrac : %f, ttbarMCfrac : %f\n",itype,totSlType[itype], 
  // 	   totSlType[itype]*1.0/totSemilepton, totSlType[itype]*1.0/totEvt, totSlType[itype]*1.0/totMCEvents);

  //printf("Signal : %s, Total Events : %lld, Total Semilep Events : %lld, Fraction : %lf\n",signal.c_str(),totEvt,totSemilepton, totSemilepton*1.0/totEvt);
  tr->Delete();

  return ;
}

