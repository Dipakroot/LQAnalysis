/**********************************************************************
 Created on : 01/08/2022
 Purpose    : Check the percentage of bin error for different rebinning
 Author     : Indranil Das, Visiting Fellow
 Email      : indranil.das@cern.ch | indra.ehep@gmail.com
**********************************************************************/
#include <TH1D.h>
#include <TFile.h>
#include <TCanvas.h>
#include <iostream>

using namespace std;

int CheckBinError()
{
  const char *syst  = "DataMu" ;
  //const char *syst  = "DataEle" ;
  //const char *syst  = "TTbar" ;
  //const char *syst  = "singleTop" ;
  //const char *syst  = "Wjets" ;
  //const char *syst  = "DYjets" ;
  //const char *syst  = "VBFusion" ;
  //const char *syst  = "MCQCDMu" ;
  //const char *syst  = "MCQCDEle" ;
  //const char *syst  = "QCDdd" ;
  //const char *syst  = "HplusM080" ;
  //const char *syst  = "HminusM080" ;
  
  const char *infile = Form("/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/grid_v40_Syst/CBA_muFmuR/2016/all_%s.root",syst);
  TFile *fin = TFile::Open(infile);
  TH1D *hMjj = (TH1D *)fin->Get(Form("%s/base/Iso/_kb_mjj_mu",syst));
  hMjj->Rebin(10);
  
  float mass = 80.0;
  int  binX = hMjj->GetXaxis()->FindBin(mass);
  cout << "binX " << binX << endl;
  Double_t Bcon = hMjj->GetBinContent(binX);
  Double_t Berr = hMjj->GetBinError(binX);
  Double_t error_percent = 100.*Berr/Bcon;
  cout << "File : " << infile << endl;
  cout << "Content : " << Bcon <<", BinError " << Berr << endl;
  cout << "Error percent : " << error_percent << endl;
  TCanvas *c1 = new TCanvas("c1","c1");
  hMjj->Draw();
  
  return true;
}
