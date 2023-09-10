/**********************************************************************
 Created on : 23/01/2022
 Purpose    : Read the KinFit object resolution
 Author     : Indranil Das, Visiting Fellow
 Email      : indranil.das@cern.ch | indra.ehep@gmail.com
**********************************************************************/
#include <TH1.h>
#include <TH2.h>
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

#include "TParticlePDG.h"
#include "TDatabasePDG.h"

#include "TLorentzVector.h"
#include "TVector3.h"


// const Int_t nMuEtaBins = 25;
// Float_t muEtaBin[26] = {0.0, 0.100, 0.200, 0.300, 0.400, 
// 			0.500, 0.600, 0.700, 0.800, 0.900, 
// 			1.000, 1.100, 1.200, 1.300, 1.400, 
// 			1.500, 1.600, 1.700, 1.800, 1.900, 
// 			2.000, 2.100, 2.200, 2.300, 2.4,
// 			2.5};
  
// const Int_t nEleEtaBins = 24;
// Float_t eleEtaBin[25] = {0.0, 0.174, 0.261, 0.348, 0.435, 
// 			 0.522, 0.609, 0.696, 0.783, 0.870, 
// 			 0.957, 1.044, 1.131, 1.218, 1.305, 
// 			 1.392, 1.479, 1.653, 1.740, 1.830, 
// 			 1.930, 2.043, 2.172, 2.322, 2.5};
  
// const Int_t nJetEtaBins = 26;
// Float_t jetEtaBin[27] = {0.0, 0.087, 0.174, 0.261, 0.348, 
// 			   0.435, 0.522, 0.609, 0.696, 0.783, 
// 			   0.870, 0.957, 1.044, 1.131, 1.218, 
// 			   1.305, 1.392, 1.479, 1.566, 1.653, 
// 			   1.740, 1.830, 1.930, 2.043, 2.172, 
// 			   2.322, 2.5};

const Int_t nMuEtaBins = 50;
Float_t muEtaBin[51] = {-2.500, 
			-2.400, -2.300, -2.200, -2.100, -2.000, 
			-1.900, -1.800, -1.700, -1.600, -1.500, 
			-1.400, -1.300, -1.200, -1.100, -1.000, 
			-0.900, -0.800, -0.700, -0.600, -0.500, 
			-0.400, -0.300, -0.200, -0.100, 
			0.0, 
			0.100, 0.200, 0.300, 0.400, 
			0.500, 0.600, 0.700, 0.800, 0.900, 
			1.000, 1.100, 1.200, 1.300, 1.400, 
			1.500, 1.600, 1.700, 1.800, 1.900, 
			2.000, 2.100, 2.200, 2.300, 2.4,
			2.5};
const Int_t nEleEtaBins = 48;
Float_t eleEtaBin[49] = { -2.500, -2.322, -2.172, -2.043, -1.930, 
			  -1.830, -1.740, -1.653, -1.479, -1.392, 
			  -1.305, -1.218, -1.131, -1.044, -0.957, 
			  -0.870, -0.783, -0.696, -0.609, -0.522, 
			  -0.435, -0.348, -0.261, -0.174, 
			  0.0, 0.174, 0.261, 0.348, 0.435, 
			  0.522, 0.609, 0.696, 0.783, 0.870, 
			  0.957, 1.044, 1.131, 1.218, 1.305, 
			  1.392, 1.479, 1.653, 1.740, 1.830, 
			  1.930, 2.043, 2.172, 2.322, 2.5};
  
const Int_t nJetEtaBins = 52;
Float_t jetEtaBin[53] = {-2.500, -2.322, 
			 -2.172, -2.043, -1.930, -1.830, -1.740, 
			 -1.653, -1.566, -1.479, -1.392, -1.305, 
			 -1.218, -1.131, -1.044, -0.957, -0.870, 
			 -0.783, -0.696, -0.609, -0.522, -0.435, 
			 -0.348, -0.261, -0.174, -0.087, 
			 0.0, 0.087, 0.174, 0.261, 0.348, 
			 0.435, 0.522, 0.609, 0.696, 0.783, 
			 0.870, 0.957, 1.044, 1.131, 1.218, 
			 1.305, 1.392, 1.479, 1.566, 1.653, 
			 1.740, 1.830, 1.930, 2.043, 2.172, 
			 2.322, 2.5};
  
// const Int_t nETBins = 19;
// Float_t ETBin[20] = {20., 30., 40., 50., 60.,
// 		     70., 80., 90., 100., 120.,
// 		     140., 160., 180., 200., 240., 
// 		     280., 320., 360., 400., 500.};

// const Int_t nJetEtaBins = 1;
// Float_t jetEtaBin[2] = {0.435, 0.783};

  const Int_t nETBins = 37;
  Float_t ETBin[38] = {25., 30., 35., 40., 45., 50., 55., 60., 65., 70., 75., 80., 85., 90., 95., 100.,  
                       110., 120., 130., 140., 150., 160., 170., 180., 190., 200.,
	               220., 240., 260., 280., 300.,
	               330., 360., 390., 420.,
                       440., 480., 520.}; 

  // const Int_t nETBins = 29;
  // Float_t ETBin[30] = {20., 30., 40., 50., 60.,
  //                      70., 80., 90., 100., 110.,
  //                      120., 130., 140., 150., 160., 
  //                      170., 180., 190., 200., 210.,
  // 		       220., 230., 240., 250., 260.,
  // 		       270., 280., 290., 300., 310};

TH1F *hBJetETReso[nJetEtaBins][nETBins], *hLJetETReso[nJetEtaBins][nETBins], *hBJetEtaReso[nJetEtaBins][nETBins], *hLJetEtaReso[nJetEtaBins][nETBins], *hBJetPhiReso[nJetEtaBins][nETBins], *hLJetPhiReso[nJetEtaBins][nETBins];
TH1F *hBJetPtReso[nJetEtaBins][nETBins], *hLJetPtReso[nJetEtaBins][nETBins], *hBJetEnReso[nJetEtaBins][nETBins], *hLJetEnReso[nJetEtaBins][nETBins];
TH1F *hBJetETResult[nJetEtaBins], *hLJetETResult[nJetEtaBins], *hBJetEtaResult[nJetEtaBins], *hLJetEtaResult[nJetEtaBins], *hBJetPhiResult[nJetEtaBins], *hLJetPhiResult[nJetEtaBins];
TH1F *hBJetETResultNF[nJetEtaBins], *hLJetETResultNF[nJetEtaBins], *hBJetEtaResultNF[nJetEtaBins], *hLJetEtaResultNF[nJetEtaBins], *hBJetPhiResultNF[nJetEtaBins], *hLJetPhiResultNF[nJetEtaBins];
TH1F *hBJetPtResultNF[nJetEtaBins], *hLJetPtResultNF[nJetEtaBins], *hBJetEnResultNF[nJetEtaBins], *hLJetEnResultNF[nJetEtaBins];

double BJetETPar[nJetEtaBins][3],BJetETParErr[nJetEtaBins][3], LJetETPar[nJetEtaBins][3], LJetETParErr[nJetEtaBins][3];
double BJetEtaPar[nJetEtaBins][2],BJetEtaParErr[nJetEtaBins][2], LJetEtaPar[nJetEtaBins][2], LJetEtaParErr[nJetEtaBins][2];
double BJetPhiPar[nJetEtaBins][2],BJetPhiParErr[nJetEtaBins][2], LJetPhiPar[nJetEtaBins][2], LJetPhiParErr[nJetEtaBins][2];

TF1 *fnET, *fnEta, *fnPhi;
TF1 *fnETMu, *fnEtaMu, *fnPhiMu;
TF1 *fnETEle, *fnEtaEle, *fnPhiEle;
TF1 *fnETMET, *fnPhiMET;

TH1F *hMuETReso[nMuEtaBins][nETBins], *hMuEtaReso[nMuEtaBins][nETBins], *hMuPhiReso[nMuEtaBins][nETBins];
TH1F *hMuPtReso[nMuEtaBins][nETBins], *hMuEnReso[nMuEtaBins][nETBins];
TH1F *hMuETResult[nMuEtaBins], *hMuEtaResult[nMuEtaBins], *hMuPhiResult[nMuEtaBins];
TH1F *hMuETResultNF[nMuEtaBins], *hMuEtaResultNF[nMuEtaBins], *hMuPhiResultNF[nMuEtaBins];
TH1F *hMuPtResultNF[nMuEtaBins], *hMuEnResultNF[nMuEtaBins];

double MuETPar[nMuEtaBins][2],MuETParErr[nMuEtaBins][2];
double MuEtaPar[nMuEtaBins][3],MuEtaParErr[nMuEtaBins][3];
double MuPhiPar[nMuEtaBins][3],MuPhiParErr[nMuEtaBins][3];

TH1F *hEleETReso[nEleEtaBins][nETBins], *hEleEtaReso[nEleEtaBins][nETBins], *hElePhiReso[nEleEtaBins][nETBins];
TH1F *hElePtReso[nMuEtaBins][nETBins], *hEleEnReso[nMuEtaBins][nETBins];
TH1F *hEleETResult[nEleEtaBins], *hEleEtaResult[nEleEtaBins], *hElePhiResult[nEleEtaBins];
TH1F *hEleETResultNF[nEleEtaBins], *hEleEtaResultNF[nEleEtaBins], *hElePhiResultNF[nEleEtaBins];
TH1F *hElePtResultNF[nEleEtaBins], *hEleEnResultNF[nEleEtaBins];

double EleETPar[nEleEtaBins][2],EleETParErr[nEleEtaBins][2];
double EleEtaPar[nEleEtaBins][3],EleEtaParErr[nEleEtaBins][3];
double ElePhiPar[nEleEtaBins][3],ElePhiParErr[nEleEtaBins][3];

TH1F *hMETETReso[nETBins], *hMETPhiReso[nETBins];
TH1F *hMETPtReso[nETBins];
TH1F *hMETETResultNF, *hMETPhiResultNF;
TH1F *hMETPtResultNF;

int udscResolution(double et, double eta, double& resEt, double& resEta, double& resPhi);
int bjetResolution(double et, double eta, double& resEt, double& resEta, double& resPhi);
int muonResolution(double et, double eta, double& resEt, double& resEta, double& resPhi);
int elecResolution(double et, double eta, double& resEt, double& resEta, double& resPhi);
int metResolution(double et, double& resEt, double& resEta, double& resPhi);

int ReadKFMean(int year = 2017)
{

  int PrintBJet(void);
  int PrintLJet(void);
  int PlotBJet(void);
  int PlotLJet(void);

  int PlotMu(void);
  int PlotEle(void);
  int PlotMET(void);
  
  //string infile = "/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/proof_v41_KFObjects/2016/pre/TTbar_KFObjectsReso_2016.root"; //It is all merged, wrong naming
  //string infile = "/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/proof_v41_KFObjects/2016/post/TTbar_KFObjectsReso_2016.root"; //It is all merged, wrong naming
  //string infile = "/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/proof_v41_KFObjects/2017/AllBkg_KFObjectsReso_2017.root";
  string infile = Form("/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/proof_v41_KFObjects/%d/AllBkg_KFObjectsReso_%d.root",year,year);
  //string infile = Form("/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/proof_v41_KFObjects/%d_post/AllBkg_KFObjectsReso_%d.root",year,year);
  
  TH2F *hBJetETDiff = new TH2F("hBJetETDiff","hBJetETDiff",nJetEtaBins,jetEtaBin,nETBins,ETBin);
  TH2F *hBJetEtaDiff = new TH2F("hBJetEtaDiff","hBJetEtaDiff",nJetEtaBins,jetEtaBin,nETBins,ETBin);
  TH2F *hBJetPhiDiff = new TH2F("hBJetPhiDiff","hBJetPhiDiff",nJetEtaBins,jetEtaBin,nETBins,ETBin);
  TH2F *hBJetPtDiff = new TH2F("hBJetPtDiff","hBJetPtDiff",nJetEtaBins,jetEtaBin,nETBins,ETBin);
  TH2F *hBJetEnDiff = new TH2F("hBJetEnDiff","hBJetEnDiff",nJetEtaBins,jetEtaBin,nETBins,ETBin);

  TH2F *hLJetETDiff = new TH2F("hLJetETDiff","hLJetETDiff",nJetEtaBins,jetEtaBin,nETBins,ETBin);
  TH2F *hLJetEtaDiff = new TH2F("hLJetEtaDiff","hLJetEtaDiff",nJetEtaBins,jetEtaBin,nETBins,ETBin);
  TH2F *hLJetPhiDiff = new TH2F("hLJetPhiDiff","hLJetPhiDiff",nJetEtaBins,jetEtaBin,nETBins,ETBin);
  TH2F *hLJetPtDiff = new TH2F("hLJetPtDiff","hLJetPtDiff",nJetEtaBins,jetEtaBin,nETBins,ETBin);
  TH2F *hLJetEnDiff = new TH2F("hLJetEnDiff","hLJetEnDiff",nJetEtaBins,jetEtaBin,nETBins,ETBin);

  TH2F *hMuETDiff = new TH2F("hMuETDiff","hMuETDiff",nMuEtaBins,muEtaBin,nETBins,ETBin);
  TH2F *hMuEtaDiff = new TH2F("hMuEtaDiff","hMuEtaDiff",nMuEtaBins,muEtaBin,nETBins,ETBin);
  TH2F *hMuPhiDiff = new TH2F("hMuPhiDiff","hMuPhiDiff",nMuEtaBins,muEtaBin,nETBins,ETBin);
  TH2F *hMuPtDiff = new TH2F("hMuPtDiff","hMuPtDiff",nJetEtaBins,jetEtaBin,nETBins,ETBin);
  TH2F *hMuEnDiff = new TH2F("hMuEnDiff","hMuEnDiff",nJetEtaBins,jetEtaBin,nETBins,ETBin);

  TH2F *hEleETDiff = new TH2F("hEleETDiff","hEleETDiff",nEleEtaBins,eleEtaBin,nETBins,ETBin);
  TH2F *hEleEtaDiff = new TH2F("hEleEtaDiff","hEleEtaDiff",nEleEtaBins,eleEtaBin,nETBins,ETBin);
  TH2F *hElePhiDiff = new TH2F("hElePhiDiff","hElePhiDiff",nEleEtaBins,eleEtaBin,nETBins,ETBin);
  TH2F *hElePtDiff = new TH2F("hElePtDiff","hElePtDiff",nJetEtaBins,jetEtaBin,nETBins,ETBin);
  TH2F *hEleEnDiff = new TH2F("hEleEnDiff","hEleEnDiff",nJetEtaBins,jetEtaBin,nETBins,ETBin);

  TH1F *hMETETDiff = new TH1F("hMETETDiff","hMETETDiff",nETBins,ETBin);
  TH1F *hMETPhiDiff = new TH1F("hMETPhiDiff","hMETPhiDiff",nETBins,ETBin);
  TH1F *hMETPtDiff = new TH1F("hMETPtDiff","hMETPtDiff",nETBins,ETBin);
  
  TFile *fin = TFile::Open(infile.c_str());
  
  ///////////////////////////////////////// Jets ////////////////////////////////////////////////////////////////////////////////////////////////////////
  for(int ieta=0;ieta<nJetEtaBins;ieta++){

    hBJetETResult[ieta] = new TH1F(Form("hBJetETResult_%d",ieta),Form("hBJetETResult for #eta : (%3.3f - %3.3f)",jetEtaBin[ieta],jetEtaBin[ieta+1]), nETBins, ETBin);
    hLJetETResult[ieta] = new TH1F(Form("hLJetETResult_%d",ieta),Form("hLJetETResult for #eta : (%3.3f - %3.3f)",jetEtaBin[ieta],jetEtaBin[ieta+1]), nETBins, ETBin);
    hBJetEtaResult[ieta] = new TH1F(Form("hBJetEtaResult_%d",ieta),Form("hBJetEtaResult for #eta : (%3.3f - %3.3f)",jetEtaBin[ieta],jetEtaBin[ieta+1]), nETBins, ETBin);
    hLJetEtaResult[ieta] = new TH1F(Form("hLJetEtaResult_%d",ieta),Form("hLJetEtaResult for #eta : (%3.3f - %3.3f)",jetEtaBin[ieta],jetEtaBin[ieta+1]), nETBins, ETBin);
    hBJetPhiResult[ieta] = new TH1F(Form("hBJetPhiResult_%d",ieta),Form("hBJetPhiResult for #eta : (%3.3f - %3.3f)",jetEtaBin[ieta],jetEtaBin[ieta+1]), nETBins, ETBin);
    hLJetPhiResult[ieta] = new TH1F(Form("hLJetPhiResult_%d",ieta),Form("hLJetPhiResult for #eta : (%3.3f - %3.3f)",jetEtaBin[ieta],jetEtaBin[ieta+1]), nETBins, ETBin);

    hBJetETResultNF[ieta] = new TH1F(Form("hBJetETResultNF_%d",ieta),Form("hBJetETResultNF for #eta : (%3.3f - %3.3f)",jetEtaBin[ieta],jetEtaBin[ieta+1]), nETBins, ETBin);
    hLJetETResultNF[ieta] = new TH1F(Form("hLJetETResultNF_%d",ieta),Form("hLJetETResultNF for #eta : (%3.3f - %3.3f)",jetEtaBin[ieta],jetEtaBin[ieta+1]), nETBins, ETBin);
    hBJetEtaResultNF[ieta] = new TH1F(Form("hBJetEtaResultNF_%d",ieta),Form("hBJetEtaResultNF for #eta : (%3.3f - %3.3f)",jetEtaBin[ieta],jetEtaBin[ieta+1]), nETBins, ETBin);
    hLJetEtaResultNF[ieta] = new TH1F(Form("hLJetEtaResultNF_%d",ieta),Form("hLJetEtaResultNF for #eta : (%3.3f - %3.3f)",jetEtaBin[ieta],jetEtaBin[ieta+1]), nETBins, ETBin);
    hBJetPhiResultNF[ieta] = new TH1F(Form("hBJetPhiResultNF_%d",ieta),Form("hBJetPhiResultNF for #eta : (%3.3f - %3.3f)",jetEtaBin[ieta],jetEtaBin[ieta+1]), nETBins, ETBin);
    hLJetPhiResultNF[ieta] = new TH1F(Form("hLJetPhiResultNF_%d",ieta),Form("hLJetPhiResultNF for #eta : (%3.3f - %3.3f)",jetEtaBin[ieta],jetEtaBin[ieta+1]), nETBins, ETBin);
    hBJetPtResultNF[ieta] = new TH1F(Form("hBJetPtResultNF_%d",ieta),Form("hBJetPtResultNF for #eta : (%3.3f - %3.3f)",jetEtaBin[ieta],jetEtaBin[ieta+1]), nETBins, ETBin);
    hLJetPtResultNF[ieta] = new TH1F(Form("hLJetPtResultNF_%d",ieta),Form("hLJetPtResultNF for #eta : (%3.3f - %3.3f)",jetEtaBin[ieta],jetEtaBin[ieta+1]), nETBins, ETBin);
    hBJetEnResultNF[ieta] = new TH1F(Form("hBJetEnResultNF_%d",ieta),Form("hBJetEnResultNF for #eta : (%3.3f - %3.3f)",jetEtaBin[ieta],jetEtaBin[ieta+1]), nETBins, ETBin);
    hLJetEnResultNF[ieta] = new TH1F(Form("hLJetEnResultNF_%d",ieta),Form("hLJetEnResultNF for #eta : (%3.3f - %3.3f)",jetEtaBin[ieta],jetEtaBin[ieta+1]), nETBins, ETBin);
    
    for(int iet=0;iet<nETBins;iet++){
      hBJetETReso[ieta][iet] = (TH1F *)fin->Get(Form("hBJetETReso_%d_%d",ieta,iet));
      hLJetETReso[ieta][iet] = (TH1F *)fin->Get(Form("hLJetETReso_%d_%d",ieta,iet)); 
      hBJetEtaReso[ieta][iet] = (TH1F *)fin->Get(Form("hBJetEtaReso_%d_%d",ieta,iet));
      hLJetEtaReso[ieta][iet] = (TH1F *)fin->Get(Form("hLJetEtaReso_%d_%d",ieta,iet));
      hBJetPhiReso[ieta][iet] = (TH1F *)fin->Get(Form("hBJetPhiReso_%d_%d",ieta,iet)); 
      hLJetPhiReso[ieta][iet] = (TH1F *)fin->Get(Form("hLJetPhiReso_%d_%d",ieta,iet)); 
      hBJetPtReso[ieta][iet] = (TH1F *)fin->Get(Form("hBJetPtReso_%d_%d",ieta,iet));
      hLJetPtReso[ieta][iet] = (TH1F *)fin->Get(Form("hLJetPtReso_%d_%d",ieta,iet)); 
      hBJetEnReso[ieta][iet] = (TH1F *)fin->Get(Form("hBJetEnReso_%d_%d",ieta,iet));
      hLJetEnReso[ieta][iet] = (TH1F *)fin->Get(Form("hLJetEnReso_%d_%d",ieta,iet)); 
    }//et
  }//eta
  
  TF1 *fn = new TF1("fn","gaus",hBJetETReso[0][0]->GetXaxis()->GetBinCenter(1),
  		    hBJetETReso[0][0]->GetXaxis()->GetBinCenter(hBJetETReso[0][0]->GetNbinsX()));
  for(int ieta=0;ieta<nJetEtaBins;ieta++){
    for(int iet=0;iet<nETBins;iet++){
      fn->SetRange(hBJetETReso[0][0]->GetXaxis()->GetBinCenter(1),hBJetETReso[0][0]->GetXaxis()->GetBinCenter(hBJetETReso[0][0]->GetNbinsX()));
      fn->SetParameters(1,0,1);
      hBJetETReso[ieta][iet]->Fit("fn","NQLR");
      hBJetETResult[ieta]->SetBinContent(iet+1,fn->GetParameter(1));
      hBJetETResult[ieta]->SetBinError(iet+1,fn->GetParError(1));
      hBJetETResultNF[ieta]->SetBinContent(iet+1,hBJetETReso[ieta][iet]->GetMean());
      hBJetETResultNF[ieta]->SetBinError(iet+1,hBJetETReso[ieta][iet]->GetMeanError());
      hBJetETDiff->SetBinContent(ieta+1, iet+1, hBJetETReso[ieta][iet]->GetMean());
      hBJetETDiff->SetBinError(ieta+1, iet+1, hBJetETReso[ieta][iet]->GetMeanError());
      //hBJetETResErr->SetBinContent(ieta+1, iet+1, hBJetETReso[ieta][iet]->GetMeanError());

      fn->SetParameters(1,0,1);
      hLJetETReso[ieta][iet]->Fit("fn","NQLR");
      hLJetETResult[ieta]->SetBinContent(iet+1,fn->GetParameter(1));
      hLJetETResult[ieta]->SetBinError(iet+1,fn->GetParError(1));
      hLJetETResultNF[ieta]->SetBinContent(iet+1,hLJetETReso[ieta][iet]->GetMean());
      hLJetETResultNF[ieta]->SetBinError(iet+1,hLJetETReso[ieta][iet]->GetMeanError());
      hLJetETDiff->SetBinContent(ieta+1, iet+1, hLJetETReso[ieta][iet]->GetMean());
      hLJetETDiff->SetBinError(ieta+1, iet+1, hLJetETReso[ieta][iet]->GetMeanError());
      //hLJetETResErr->SetBinContent(ieta+1, iet+1, hLJetETReso[ieta][iet]->GetMeanError());

      fn->SetRange(hBJetEtaReso[0][0]->GetXaxis()->GetBinCenter(1),hBJetEtaReso[0][0]->GetXaxis()->GetBinCenter(hBJetEtaReso[0][0]->GetNbinsX()));
      fn->SetParameters(1,0,1);
      hBJetEtaReso[ieta][iet]->Fit("fn","NQLR");
      hBJetEtaResult[ieta]->SetBinContent(iet+1,fn->GetParameter(1));
      hBJetEtaResult[ieta]->SetBinError(iet+1,fn->GetParError(1));
      hBJetEtaResultNF[ieta]->SetBinContent(iet+1,hBJetEtaReso[ieta][iet]->GetMean());
      hBJetEtaResultNF[ieta]->SetBinError(iet+1,hBJetEtaReso[ieta][iet]->GetMeanError());
      hBJetEtaDiff->SetBinContent(ieta+1, iet+1, hBJetEtaReso[ieta][iet]->GetMean());
      hBJetEtaDiff->SetBinError(ieta+1, iet+1, hBJetEtaReso[ieta][iet]->GetMeanError());
      //hBJetEtaResErr->SetBinContent(ieta+1, iet+1, hBJetEtaReso[ieta][iet]->GetMeanError());      

      fn->SetParameters(1,0,10);
      hLJetEtaReso[ieta][iet]->Fit("fn","NQLR");
      hLJetEtaResult[ieta]->SetBinContent(iet+1,fn->GetParameter(1));
      hLJetEtaResult[ieta]->SetBinError(iet+1,fn->GetParError(1));
      hLJetEtaResultNF[ieta]->SetBinContent(iet+1,hLJetEtaReso[ieta][iet]->GetMean());
      hLJetEtaResultNF[ieta]->SetBinError(iet+1,hLJetEtaReso[ieta][iet]->GetMeanError());
      hLJetEtaDiff->SetBinContent(ieta+1, iet+1, hLJetEtaReso[ieta][iet]->GetMean());
      hLJetEtaDiff->SetBinError(ieta+1, iet+1, hLJetEtaReso[ieta][iet]->GetMeanError());
      //hLJetEtaResErr->SetBinContent(ieta+1, iet+1, hLJetEtaReso[ieta][iet]->GetMeanError());
      
      fn->SetRange(hBJetPhiReso[0][0]->GetXaxis()->GetBinCenter(1),hBJetPhiReso[0][0]->GetXaxis()->GetBinCenter(hBJetPhiReso[0][0]->GetNbinsX()));
      fn->SetParameters(1,0,1);
      hBJetPhiReso[ieta][iet]->Fit("fn","NQLR");
      hBJetPhiResult[ieta]->SetBinContent(iet+1,fn->GetParameter(1));
      hBJetPhiResult[ieta]->SetBinError(iet+1,fn->GetParError(1));
      hBJetPhiResultNF[ieta]->SetBinContent(iet+1,hBJetPhiReso[ieta][iet]->GetMean());
      hBJetPhiResultNF[ieta]->SetBinError(iet+1,hBJetPhiReso[ieta][iet]->GetMeanError());
      hBJetPhiDiff->SetBinContent(ieta+1, iet+1, hBJetPhiReso[ieta][iet]->GetMean());
      hBJetPhiDiff->SetBinError(ieta+1, iet+1, hBJetPhiReso[ieta][iet]->GetMeanError());
      //hBJetPhiResErr->SetBinContent(ieta+1, iet+1, hBJetPhiReso[ieta][iet]->GetMeanError());

      fn->SetParameters(1,0,1);
      hLJetPhiReso[ieta][iet]->Fit("fn","NQLR");
      hLJetPhiResult[ieta]->SetBinContent(iet+1,fn->GetParameter(1));
      hLJetPhiResult[ieta]->SetBinError(iet+1,fn->GetParError(1));
      hLJetPhiResultNF[ieta]->SetBinContent(iet+1,hLJetPhiReso[ieta][iet]->GetMean());
      hLJetPhiResultNF[ieta]->SetBinError(iet+1,hLJetPhiReso[ieta][iet]->GetMeanError());
      hLJetPhiDiff->SetBinContent(ieta+1, iet+1, hLJetPhiReso[ieta][iet]->GetMean());
      hLJetPhiDiff->SetBinError(ieta+1, iet+1, hLJetPhiReso[ieta][iet]->GetMeanError());
      //hLJetPhiResErr->SetBinContent(ieta+1, iet+1, hLJetPhiReso[ieta][iet]->GetMeanError());


      hBJetPtResultNF[ieta]->SetBinContent(iet+1,hBJetPtReso[ieta][iet]->GetMean());
      hBJetPtResultNF[ieta]->SetBinError(iet+1,hBJetPtReso[ieta][iet]->GetMeanError());
      hBJetEnResultNF[ieta]->SetBinContent(iet+1,hBJetEnReso[ieta][iet]->GetMean());
      hBJetEnResultNF[ieta]->SetBinError(iet+1,hBJetEnReso[ieta][iet]->GetMeanError());
      hBJetPtDiff->SetBinContent(ieta+1, iet+1, hBJetPtReso[ieta][iet]->GetMean());
      hBJetPtDiff->SetBinError(ieta+1, iet+1, hBJetPtReso[ieta][iet]->GetMeanError());
      hBJetEnDiff->SetBinContent(ieta+1, iet+1, hBJetEnReso[ieta][iet]->GetMean());
      hBJetEnDiff->SetBinError(ieta+1, iet+1, hBJetEnReso[ieta][iet]->GetMeanError());

      hLJetPtResultNF[ieta]->SetBinContent(iet+1,hLJetPtReso[ieta][iet]->GetMean());
      hLJetPtResultNF[ieta]->SetBinError(iet+1,hLJetPtReso[ieta][iet]->GetMeanError());
      hLJetEnResultNF[ieta]->SetBinContent(iet+1,hLJetEnReso[ieta][iet]->GetMean());
      hLJetEnResultNF[ieta]->SetBinError(iet+1,hLJetEnReso[ieta][iet]->GetMeanError());
      hLJetPtDiff->SetBinContent(ieta+1, iet+1, hLJetPtReso[ieta][iet]->GetMean());
      hLJetPtDiff->SetBinError(ieta+1, iet+1, hLJetPtReso[ieta][iet]->GetMeanError());
      hLJetEnDiff->SetBinContent(ieta+1, iet+1, hLJetEnReso[ieta][iet]->GetMean());
      hLJetEnDiff->SetBinError(ieta+1, iet+1, hLJetEnReso[ieta][iet]->GetMeanError());
    }//et
  }//eta
  

  fnET = new TF1("fnET","TMath::Sqrt( TMath::Power([0],2) + TMath::Power([1]/TMath::Sqrt(x),2) + TMath::Power([2]/x,2) ) ",
  		      hBJetETResult[0]->GetXaxis()->GetBinLowEdge(1),
  		      hBJetETResult[0]->GetXaxis()->GetBinUpEdge(hBJetETResult[0]->GetNbinsX()));  
  fnEta = new TF1("fnEta","TMath::Sqrt( TMath::Power([0],2) + TMath::Power([1]/x,2) ) ",
  		       hBJetEtaResult[0]->GetXaxis()->GetBinLowEdge(1),
  		       hBJetEtaResult[0]->GetXaxis()->GetBinUpEdge(hBJetEtaResult[0]->GetNbinsX()));
  fnPhi = new TF1("fnPhi","TMath::Sqrt( TMath::Power([0],2) + TMath::Power([1]/x,2) ) ",
  		       hBJetPhiResult[0]->GetXaxis()->GetBinLowEdge(1),
  		       hBJetPhiResult[0]->GetXaxis()->GetBinUpEdge(hBJetPhiResult[0]->GetNbinsX()));
  

  for(int ieta=0;ieta<nJetEtaBins;ieta++){
    fnET->SetParameters(1.0, 1.0, 1.0);
    hBJetETResult[ieta]->Fit("fnET","NQLR");
    fnET->GetParameters(BJetETPar[ieta]);
    BJetETParErr[ieta][0] = fnET->GetParError(0); BJetETParErr[ieta][1] = fnET->GetParError(1); BJetETParErr[ieta][2] = fnET->GetParError(2);
    //printf("ieta %d : (%5.2f +/- %5.2f), (%5.2f +/- %5.2f), (%5.2f +/- %5.2f) \n",ieta,BJetETPar[ieta][0],BJetETParErr[ieta][0],BJetETPar[ieta][1],BJetETParErr[ieta][1],BJetETPar[ieta][2],BJetETParErr[ieta][2]);

    fnET->SetParameters(1.0, 1.0, 1.0);
    hLJetETResult[ieta]->Fit("fnET","NQLR");
    fnET->GetParameters(LJetETPar[ieta]);
    LJetETParErr[ieta][0] = fnET->GetParError(0); LJetETParErr[ieta][1] = fnET->GetParError(1); LJetETParErr[ieta][2] = fnET->GetParError(2);

    fnEta->SetParameters(1.0, 1.0);
    hBJetEtaResult[ieta]->Fit("fnEta","NQLR");
    fnEta->GetParameters(BJetEtaPar[ieta]);
    BJetEtaParErr[ieta][0] = fnEta->GetParError(0); BJetEtaParErr[ieta][1] = fnEta->GetParError(1); 
    //printf("ieta %d : (%5.2f +/- %5.2f), (%5.2f +/- %5.2f)\n",ieta,BJetEtaPar[ieta][0],BJetEtaParErr[ieta][0],BJetEtaPar[ieta][1],BJetEtaParErr[ieta][1]);

    fnEta->SetParameters(1.0, 1.0);
    hLJetEtaResult[ieta]->Fit("fnEta","NQLR");
    fnEta->GetParameters(LJetEtaPar[ieta]);
    LJetEtaParErr[ieta][0] = fnEta->GetParError(0); LJetEtaParErr[ieta][1] = fnEta->GetParError(1); 

    fnPhi->SetParameters(1.0, 1.0);
    hBJetPhiResult[ieta]->Fit("fnPhi","NQLR");
    fnPhi->GetParameters(BJetPhiPar[ieta]);
    BJetPhiParErr[ieta][0] = fnPhi->GetParError(0); BJetPhiParErr[ieta][1] = fnPhi->GetParError(1); 
    //printf("ieta %d : (%5.2f +/- %5.2f), (%5.2f +/- %5.2f)\n",ieta,BJetPhiPar[ieta][0],BJetPhiParErr[ieta][0],BJetPhiPar[ieta][1],BJetPhiParErr[ieta][1]);
    
    fnPhi->SetParameters(1.0, 1.0);
    hLJetPhiResult[ieta]->Fit("fnPhi","NQLR");
    fnPhi->GetParameters(LJetPhiPar[ieta]);
    LJetPhiParErr[ieta][0] = fnPhi->GetParError(0); LJetPhiParErr[ieta][1] = fnPhi->GetParError(1); 
  }
  
  // PrintBJet();
  // PrintLJet();
  
  PlotBJet();
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  ///////////////////////////////////////// Muon ////////////////////////////////////////////////////////////////////////////////////////////////////////
  for(int ieta=0;ieta<nMuEtaBins;ieta++){
    
    hMuETResult[ieta] = new TH1F(Form("hMuETResult_%d",ieta),Form("hMuETResult for #eta : (%3.3f - %3.3f)",muEtaBin[ieta],muEtaBin[ieta+1]), nETBins, ETBin);
    hMuEtaResult[ieta] = new TH1F(Form("hMuEtaResult_%d",ieta),Form("hMuEtaResult for #eta : (%3.3f - %3.3f)",muEtaBin[ieta],muEtaBin[ieta+1]), nETBins, ETBin);
    hMuPhiResult[ieta] = new TH1F(Form("hMuPhiResult_%d",ieta),Form("hMuPhiResult for #eta : (%3.3f - %3.3f)",muEtaBin[ieta],muEtaBin[ieta+1]), nETBins, ETBin);

    hMuETResultNF[ieta] = new TH1F(Form("hMuETResultNF_%d",ieta),Form("hMuETResultNF for #eta : (%3.3f - %3.3f)",muEtaBin[ieta],muEtaBin[ieta+1]), nETBins, ETBin);
    hMuEtaResultNF[ieta] = new TH1F(Form("hMuEtaResultNF_%d",ieta),Form("hMuEtaResultNF for #eta : (%3.3f - %3.3f)",muEtaBin[ieta],muEtaBin[ieta+1]), nETBins, ETBin);
    hMuPhiResultNF[ieta] = new TH1F(Form("hMuPhiResultNF_%d",ieta),Form("hMuPhiResultNF for #eta : (%3.3f - %3.3f)",muEtaBin[ieta],muEtaBin[ieta+1]), nETBins, ETBin);
    hMuPtResultNF[ieta] = new TH1F(Form("hMuPtResultNF_%d",ieta),Form("hMuPtResultNF for #eta : (%3.3f - %3.3f)",muEtaBin[ieta],muEtaBin[ieta+1]), nETBins, ETBin);
    hMuEnResultNF[ieta] = new TH1F(Form("hMuEnResultNF_%d",ieta),Form("hMuEnResultNF for #eta : (%3.3f - %3.3f)",muEtaBin[ieta],muEtaBin[ieta+1]), nETBins, ETBin);

    for(int iet=0;iet<nETBins;iet++){
      hMuETReso[ieta][iet] = (TH1F *)fin->Get(Form("hMuETReso_%d_%d",ieta,iet));
      hMuEtaReso[ieta][iet] = (TH1F *)fin->Get(Form("hMuEtaReso_%d_%d",ieta,iet));
      hMuPhiReso[ieta][iet] = (TH1F *)fin->Get(Form("hMuPhiReso_%d_%d",ieta,iet)); 
      hMuPtReso[ieta][iet] = (TH1F *)fin->Get(Form("hMuPtReso_%d_%d",ieta,iet));
      hMuEnReso[ieta][iet] = (TH1F *)fin->Get(Form("hMuEnReso_%d_%d",ieta,iet));
    }//et
  }//eta
  
  for(int ieta=0;ieta<nMuEtaBins;ieta++){
    for(int iet=0;iet<nETBins;iet++){
      fn->SetRange(hMuETReso[0][0]->GetXaxis()->GetBinCenter(1),hMuETReso[0][0]->GetXaxis()->GetBinCenter(hMuETReso[0][0]->GetNbinsX()));
      fn->SetParameters(1,0,.001);
      hMuETReso[ieta][iet]->Fit("fn","NQLR");
      hMuETResult[ieta]->SetBinContent(iet+1,fn->GetParameter(1));
      hMuETResult[ieta]->SetBinError(iet+1,fn->GetParError(1));
      hMuETResultNF[ieta]->SetBinContent(iet+1,hMuETReso[ieta][iet]->GetMean());
      hMuETResultNF[ieta]->SetBinError(iet+1,hMuETReso[ieta][iet]->GetMeanError());
      hMuETDiff->SetBinContent(ieta+1, iet+1, hMuETReso[ieta][iet]->GetMean());
      hMuETDiff->SetBinError(ieta+1, iet+1, hMuETReso[ieta][iet]->GetMeanError());
      //hMuETResErr->SetBinContent(ieta+1, iet+1, hMuETReso[ieta][iet]->GetMeanError());

      fn->SetRange(hMuEtaReso[0][0]->GetXaxis()->GetBinCenter(1),hMuEtaReso[0][0]->GetXaxis()->GetBinCenter(hMuEtaReso[0][0]->GetNbinsX()));
      fn->SetParameters(1,0,.001);
      hMuEtaReso[ieta][iet]->Fit("fn","NQLR");
      hMuEtaResult[ieta]->SetBinContent(iet+1,fn->GetParameter(1));
      hMuEtaResult[ieta]->SetBinError(iet+1,fn->GetParError(1));
      hMuEtaResultNF[ieta]->SetBinContent(iet+1,hMuEtaReso[ieta][iet]->GetMean());
      hMuEtaResultNF[ieta]->SetBinError(iet+1,hMuEtaReso[ieta][iet]->GetMeanError());
      hMuEtaDiff->SetBinContent(ieta+1, iet+1, hMuEtaReso[ieta][iet]->GetMean());
      hMuEtaDiff->SetBinError(ieta+1, iet+1, hMuEtaReso[ieta][iet]->GetMeanError());
      //hMuEtaResErr->SetBinContent(ieta+1, iet+1, hMuEtaReso[ieta][iet]->GetMeanError());
      
      fn->SetRange(hMuPhiReso[0][0]->GetXaxis()->GetBinCenter(1),hMuPhiReso[0][0]->GetXaxis()->GetBinCenter(hMuPhiReso[0][0]->GetNbinsX()));
      fn->SetParameters(1,0,.001);
      hMuPhiReso[ieta][iet]->Fit("fn","NQLR");
      hMuPhiResult[ieta]->SetBinContent(iet+1,fn->GetParameter(1));
      hMuPhiResult[ieta]->SetBinError(iet+1,fn->GetParError(1));
      hMuPhiResultNF[ieta]->SetBinContent(iet+1,hMuPhiReso[ieta][iet]->GetMean());
      hMuPhiResultNF[ieta]->SetBinError(iet+1,hMuPhiReso[ieta][iet]->GetMeanError());
      hMuPhiDiff->SetBinContent(ieta+1, iet+1, hMuPhiReso[ieta][iet]->GetMean());
      hMuPhiDiff->SetBinError(ieta+1, iet+1, hMuPhiReso[ieta][iet]->GetMeanError());
      //hMuPhiResErr->SetBinContent(ieta+1, iet+1, hMuPhiReso[ieta][iet]->GetMeanError());


      hMuPtResultNF[ieta]->SetBinContent(iet+1,hMuPtReso[ieta][iet]->GetMean());
      hMuPtResultNF[ieta]->SetBinError(iet+1,hMuPtReso[ieta][iet]->GetMeanError());
      hMuEnResultNF[ieta]->SetBinContent(iet+1,hMuEnReso[ieta][iet]->GetMean());
      hMuEnResultNF[ieta]->SetBinError(iet+1,hMuEnReso[ieta][iet]->GetMeanError());    
      hMuPtDiff->SetBinContent(ieta+1, iet+1, hMuPtReso[ieta][iet]->GetMean());
      hMuPtDiff->SetBinError(ieta+1, iet+1, hMuPtReso[ieta][iet]->GetMeanError());
      hMuEnDiff->SetBinContent(ieta+1, iet+1, hMuEnReso[ieta][iet]->GetMean());
      hMuEnDiff->SetBinError(ieta+1, iet+1, hMuEnReso[ieta][iet]->GetMeanError());

    }//et
  }//eta
  

  fnETMu = new TF1("fnETMu","[0] + [1]*x",
  		   hMuETResult[0]->GetXaxis()->GetBinLowEdge(1),
  		   hMuETResult[0]->GetXaxis()->GetBinUpEdge(hMuETResult[0]->GetNbinsX()));  
  fnEtaMu = new TF1("fnEtaMu","TMath::Sqrt( TMath::Power([0],2) + TMath::Power([1]/TMath::Sqrt(x),2) + TMath::Power([2]/x,2) ) ",
  		    hMuEtaResult[0]->GetXaxis()->GetBinLowEdge(1),
  		    hMuEtaResult[0]->GetXaxis()->GetBinUpEdge(hMuEtaResult[0]->GetNbinsX()));
  fnPhiMu = new TF1("fnPhiMu","TMath::Sqrt( TMath::Power([0],2) + TMath::Power([1]/TMath::Sqrt(x),2) + TMath::Power([2]/x,2) ) ",
  		    hMuPhiResult[0]->GetXaxis()->GetBinLowEdge(1),
  		    hMuPhiResult[0]->GetXaxis()->GetBinUpEdge(hMuPhiResult[0]->GetNbinsX()));
  

  for(int ieta=0;ieta<nMuEtaBins;ieta++){
    fnETMu->SetParameters(1.0, 1.0, 1.0);
    hMuETResult[ieta]->Fit("fnETMu","NQLR");
    fnETMu->GetParameters(MuETPar[ieta]);
    MuETParErr[ieta][0] = fnETMu->GetParError(0); MuETParErr[ieta][1] = fnETMu->GetParError(1);
    //printf("ieta %d : (%5.2f +/- %5.2f), (%5.2f +/- %5.2f), (%5.2f +/- %5.2f) \n",ieta,MuETPar[ieta][0],MuETParErr[ieta][0],MuETPar[ieta][1],MuETParErr[ieta][1],MuETPar[ieta][2],MuETParErr[ieta][2]);

    fnEtaMu->SetParameters(1.0, 1.0);
    hMuEtaResult[ieta]->Fit("fnEtaMu","NQLR");
    fnEtaMu->GetParameters(MuEtaPar[ieta]);
    MuEtaParErr[ieta][0] = fnEtaMu->GetParError(0); MuEtaParErr[ieta][1] = fnEtaMu->GetParError(1); MuEtaParErr[ieta][2] = fnEtaMu->GetParError(2);
    //printf("ieta %d : (%5.2f +/- %5.2f), (%5.2f +/- %5.2f)\n",ieta,MuEtaPar[ieta][0],MuEtaParErr[ieta][0],MuEtaPar[ieta][1],MuEtaParErr[ieta][1]);

    fnPhiMu->SetParameters(1.0, 1.0);
    hMuPhiResult[ieta]->Fit("fnPhiMu","NQLR");
    fnPhiMu->GetParameters(MuPhiPar[ieta]);
    MuPhiParErr[ieta][0] = fnPhiMu->GetParError(0); MuPhiParErr[ieta][1] = fnPhiMu->GetParError(1); MuPhiParErr[ieta][2] = fnPhiMu->GetParError(2);
    //printf("ieta %d : (%5.2f +/- %5.2f), (%5.2f +/- %5.2f)\n",ieta,MuPhiPar[ieta][0],MuPhiParErr[ieta][0],MuPhiPar[ieta][1],MuPhiParErr[ieta][1]);
    
  }

  PlotMu();
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  ///////////////////////////////////////// Electron ////////////////////////////////////////////////////////////////////////////////////////////////////////
  for(int ieta=0;ieta<nEleEtaBins;ieta++){
    
    hEleETResult[ieta] = new TH1F(Form("hEleETResult_%d",ieta),Form("hEleETResult for #eta : (%3.3f - %3.3f)",eleEtaBin[ieta],eleEtaBin[ieta+1]), nETBins, ETBin);
    hEleEtaResult[ieta] = new TH1F(Form("hEleEtaResult_%d",ieta),Form("hEleEtaResult for #eta : (%3.3f - %3.3f)",eleEtaBin[ieta],eleEtaBin[ieta+1]), nETBins, ETBin);
    hElePhiResult[ieta] = new TH1F(Form("hElePhiResult_%d",ieta),Form("hElePhiResult for #eta : (%3.3f - %3.3f)",eleEtaBin[ieta],eleEtaBin[ieta+1]), nETBins, ETBin);

    hEleETResultNF[ieta] = new TH1F(Form("hEleETResultNF_%d",ieta),Form("hEleETResultNF for #eta : (%3.3f - %3.3f)",eleEtaBin[ieta],eleEtaBin[ieta+1]), nETBins, ETBin);
    hEleEtaResultNF[ieta] = new TH1F(Form("hEleEtaResultNF_%d",ieta),Form("hEleEtaResultNF for #eta : (%3.3f - %3.3f)",eleEtaBin[ieta],eleEtaBin[ieta+1]), nETBins, ETBin);
    hElePhiResultNF[ieta] = new TH1F(Form("hElePhiResultNF_%d",ieta),Form("hElePhiResultNF for #eta : (%3.3f - %3.3f)",eleEtaBin[ieta],eleEtaBin[ieta+1]), nETBins, ETBin);
    hElePtResultNF[ieta] = new TH1F(Form("hElePtResultNF_%d",ieta),Form("hElePtResultNF for #eta : (%3.3f - %3.3f)",eleEtaBin[ieta],eleEtaBin[ieta+1]), nETBins, ETBin);
    hEleEnResultNF[ieta] = new TH1F(Form("hEleEnResultNF_%d",ieta),Form("hEleEnResultNF for #eta : (%3.3f - %3.3f)",eleEtaBin[ieta],eleEtaBin[ieta+1]), nETBins, ETBin);

    for(int iet=0;iet<nETBins;iet++){
      hEleETReso[ieta][iet] = (TH1F *)fin->Get(Form("hEleETReso_%d_%d",ieta,iet));
      hEleEtaReso[ieta][iet] = (TH1F *)fin->Get(Form("hEleEtaReso_%d_%d",ieta,iet));
      hElePhiReso[ieta][iet] = (TH1F *)fin->Get(Form("hElePhiReso_%d_%d",ieta,iet)); 
      hElePtReso[ieta][iet] = (TH1F *)fin->Get(Form("hElePtReso_%d_%d",ieta,iet));
      hEleEnReso[ieta][iet] = (TH1F *)fin->Get(Form("hEleEnReso_%d_%d",ieta,iet));
    }//et
  }//eta
  
  for(int ieta=0;ieta<nEleEtaBins;ieta++){
    for(int iet=0;iet<nETBins;iet++){
      fn->SetRange(hEleETReso[0][0]->GetXaxis()->GetBinCenter(1),hEleETReso[0][0]->GetXaxis()->GetBinCenter(hEleETReso[0][0]->GetNbinsX()));
      fn->SetParameters(1,0,.001);
      hEleETReso[ieta][iet]->Fit("fn","NQLR");
      hEleETResult[ieta]->SetBinContent(iet+1,fn->GetParameter(1));
      hEleETResult[ieta]->SetBinError(iet+1,fn->GetParError(1));
      hEleETResultNF[ieta]->SetBinContent(iet+1,hEleETReso[ieta][iet]->GetMean());
      hEleETResultNF[ieta]->SetBinError(iet+1,hEleETReso[ieta][iet]->GetMeanError());
      hEleETDiff->SetBinContent(ieta+1, iet+1, hEleETReso[ieta][iet]->GetMean());
      hEleETDiff->SetBinError(ieta+1, iet+1, hEleETReso[ieta][iet]->GetMeanError());
      //hEleETResErr->SetBinContent(ieta+1, iet+1, hEleETReso[ieta][iet]->GetMeanError());
      
      fn->SetRange(hEleEtaReso[0][0]->GetXaxis()->GetBinCenter(1),hEleEtaReso[0][0]->GetXaxis()->GetBinCenter(hEleEtaReso[0][0]->GetNbinsX()));
      fn->SetParameters(1,0,.001);
      hEleEtaReso[ieta][iet]->Fit("fn","NQLR");
      hEleEtaResult[ieta]->SetBinContent(iet+1,fn->GetParameter(1));
      hEleEtaResult[ieta]->SetBinError(iet+1,fn->GetParError(1));
      hEleEtaResultNF[ieta]->SetBinContent(iet+1,hEleEtaReso[ieta][iet]->GetMean());
      hEleEtaResultNF[ieta]->SetBinError(iet+1,hEleEtaReso[ieta][iet]->GetMeanError());
      hEleEtaDiff->SetBinContent(ieta+1, iet+1, hEleEtaReso[ieta][iet]->GetMean());
      hEleEtaDiff->SetBinError(ieta+1, iet+1, hEleEtaReso[ieta][iet]->GetMeanError());
      //hEleEtaResErr->SetBinContent(ieta+1, iet+1, hEleEtaReso[ieta][iet]->GetMeanError());
      
      fn->SetRange(hElePhiReso[0][0]->GetXaxis()->GetBinCenter(1),hElePhiReso[0][0]->GetXaxis()->GetBinCenter(hElePhiReso[0][0]->GetNbinsX()));
      fn->SetParameters(1,0,.001);
      hElePhiReso[ieta][iet]->Fit("fn","NQLR");
      hElePhiResult[ieta]->SetBinContent(iet+1,fn->GetParameter(1));
      hElePhiResult[ieta]->SetBinError(iet+1,fn->GetParError(1));
      hElePhiResultNF[ieta]->SetBinContent(iet+1,hElePhiReso[ieta][iet]->GetMean());
      hElePhiResultNF[ieta]->SetBinError(iet+1,hElePhiReso[ieta][iet]->GetMeanError());
      hElePhiDiff->SetBinContent(ieta+1, iet+1, hElePhiReso[ieta][iet]->GetMean());
      hElePhiDiff->SetBinError(ieta+1, iet+1, hElePhiReso[ieta][iet]->GetMeanError());
      //hElePhiResErr->SetBinContent(ieta+1, iet+1, hElePhiReso[ieta][iet]->GetMeanError());
      
      hElePtResultNF[ieta]->SetBinContent(iet+1,hElePtReso[ieta][iet]->GetMean());
      hElePtResultNF[ieta]->SetBinError(iet+1,hElePtReso[ieta][iet]->GetMeanError());
      hEleEnResultNF[ieta]->SetBinContent(iet+1,hEleEnReso[ieta][iet]->GetMean());
      hEleEnResultNF[ieta]->SetBinError(iet+1,hEleEnReso[ieta][iet]->GetMeanError());    
      hElePtDiff->SetBinContent(ieta+1, iet+1, hElePtReso[ieta][iet]->GetMean());
      hElePtDiff->SetBinError(ieta+1, iet+1, hElePtReso[ieta][iet]->GetMeanError());
      hEleEnDiff->SetBinContent(ieta+1, iet+1, hEleEnReso[ieta][iet]->GetMean());
      hEleEnDiff->SetBinError(ieta+1, iet+1, hEleEnReso[ieta][iet]->GetMeanError());

    }//et
  }//eta
  

  fnETEle = new TF1("fnETEle","[0] + [1]*x",
  		   hEleETResult[0]->GetXaxis()->GetBinLowEdge(1),
  		   hEleETResult[0]->GetXaxis()->GetBinUpEdge(hEleETResult[0]->GetNbinsX()));  
  fnEtaEle = new TF1("fnEtaEle","TMath::Sqrt( TMath::Power([0],2) + TMath::Power([1]/TMath::Sqrt(x),2) + TMath::Power([2]/x,2) ) ",
  		    hEleEtaResult[0]->GetXaxis()->GetBinLowEdge(1),
  		    hEleEtaResult[0]->GetXaxis()->GetBinUpEdge(hEleEtaResult[0]->GetNbinsX()));
  fnPhiEle = new TF1("fnPhiEle","TMath::Sqrt( TMath::Power([0],2) + TMath::Power([1]/TMath::Sqrt(x),2) + TMath::Power([2]/x,2) ) ",
  		    hElePhiResult[0]->GetXaxis()->GetBinLowEdge(1),
  		    hElePhiResult[0]->GetXaxis()->GetBinUpEdge(hElePhiResult[0]->GetNbinsX()));
  

  for(int ieta=0;ieta<nEleEtaBins;ieta++){
    fnETEle->SetParameters(1.0, 1.0, 1.0);
    hEleETResult[ieta]->Fit("fnETEle","NQLR");
    fnETEle->GetParameters(EleETPar[ieta]);
    EleETParErr[ieta][0] = fnETEle->GetParError(0); EleETParErr[ieta][1] = fnETEle->GetParError(1);
    //printf("ieta %d : (%5.2f +/- %5.2f), (%5.2f +/- %5.2f), (%5.2f +/- %5.2f) \n",ieta,EleETPar[ieta][0],EleETParErr[ieta][0],EleETPar[ieta][1],EleETParErr[ieta][1],EleETPar[ieta][2],EleETParErr[ieta][2]);

    fnEtaEle->SetParameters(1.0, 1.0);
    hEleEtaResult[ieta]->Fit("fnEtaEle","NQLR");
    fnEtaEle->GetParameters(EleEtaPar[ieta]);
    EleEtaParErr[ieta][0] = fnEtaEle->GetParError(0); EleEtaParErr[ieta][1] = fnEtaEle->GetParError(1); EleEtaParErr[ieta][2] = fnEtaEle->GetParError(2);
    //printf("ieta %d : (%5.2f +/- %5.2f), (%5.2f +/- %5.2f)\n",ieta,EleEtaPar[ieta][0],EleEtaParErr[ieta][0],EleEtaPar[ieta][1],EleEtaParErr[ieta][1]);

    fnPhiEle->SetParameters(1.0, 1.0);
    hElePhiResult[ieta]->Fit("fnPhiEle","NQLR");
    fnPhiEle->GetParameters(ElePhiPar[ieta]);
    ElePhiParErr[ieta][0] = fnPhiEle->GetParError(0); ElePhiParErr[ieta][1] = fnPhiEle->GetParError(1); ElePhiParErr[ieta][2] = fnPhiEle->GetParError(2);
    //printf("ieta %d : (%5.2f +/- %5.2f), (%5.2f +/- %5.2f)\n",ieta,ElePhiPar[ieta][0],ElePhiParErr[ieta][0],ElePhiPar[ieta][1],ElePhiParErr[ieta][1]);
    
  }
  PlotEle();
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  ///////////////////////////////////////// MET ////////////////////////////////////////////////////////////////////////////////////////////////////////
  hMETETResultNF = new TH1F("hMETETResultNF","hMETETResultNF", nETBins, ETBin);
  hMETPhiResultNF = new TH1F("hMETPhiResultNF","hMETPhiResultNF", nETBins, ETBin);    
  hMETPtResultNF = new TH1F("hMETPtResultNF","hMETPtResultNF", nETBins, ETBin);
  for(int iet=0;iet<nETBins;iet++){
    hMETETReso[iet] = (TH1F *)fin->Get(Form("hMETETReso_%d",iet));
    hMETPhiReso[iet] = (TH1F *)fin->Get(Form("hMETPhiReso_%d",iet)); 
    hMETPtReso[iet] = (TH1F *)fin->Get(Form("hMETPtReso_%d",iet));

    hMETETResultNF->SetBinContent(iet+1,hMETETReso[iet]->GetMean());
    hMETETResultNF->SetBinError(iet+1,hMETETReso[iet]->GetMeanError());
    hMETETDiff->SetBinContent(iet+1, hMETETReso[iet]->GetMean());
    hMETETDiff->SetBinError(iet+1, hMETETReso[iet]->GetMeanError());

    hMETPhiResultNF->SetBinContent(iet+1,hMETPhiReso[iet]->GetMean());
    hMETPhiResultNF->SetBinError(iet+1,hMETPhiReso[iet]->GetMeanError());
    hMETPhiDiff->SetBinContent(iet+1, hMETPhiReso[iet]->GetMean());
    hMETPhiDiff->SetBinError(iet+1, hMETPhiReso[iet]->GetMeanError());
    
    hMETPtResultNF->SetBinContent(iet+1,hMETPtReso[iet]->GetMean());
    hMETPtResultNF->SetBinError(iet+1,hMETPtReso[iet]->GetMeanError());
    hMETPtDiff->SetBinContent(iet+1, hMETPtReso[iet]->GetMean());
    hMETPtDiff->SetBinError(iet+1, hMETPtReso[iet]->GetMeanError());
    
  }//et
  PlotMET();
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////////////////////////////Check Histo values///////////////////////////////////////////////
  int ieta = 2;
  for(int iet=0;iet<nETBins;iet++){
    printf("value 1: %f +/- %f, value 2: %f +/- %f, diff: %f +/- %f\n",hBJetEtaResultNF[ieta]->GetBinContent(iet+1), hBJetEtaResultNF[ieta]->GetBinError(iet+1), 
	   hBJetEtaDiff->GetBinContent(ieta+1, iet+1), hBJetEtaDiff->GetBinError(ieta+1, iet+1), 
  	   hBJetEtaDiff->GetBinContent(ieta+1, iet+1)-hBJetEtaResultNF[ieta]->GetBinContent(iet+1),
	   hBJetEtaDiff->GetBinError(ieta+1, iet+1)-hBJetEtaResultNF[ieta]->GetBinError(iet+1)
	   );
  }
  //////////////////////////////////////// Save Histograms /////////////////////////////////////////////////////
  TFile *fout = new TFile(Form("KinFitDiff_%d.root",year),"recreate");
  hBJetETDiff->Write();
  hBJetEtaDiff->Write();
  hBJetPhiDiff->Write();
  hLJetETDiff->Write();
  hLJetEtaDiff->Write();
  hLJetPhiDiff->Write();
  hMuETDiff->Write();
  hMuEtaDiff->Write();
  hMuPhiDiff->Write();
  hEleETDiff->Write();
  hEleEtaDiff->Write();
  hElePhiDiff->Write();
  hMETETDiff->Write();
  hMETPhiDiff->Write();
  
  hBJetPtDiff->Write();
  hBJetPtDiff->Write();
  hBJetEnDiff->Write();
  hBJetEnDiff->Write();
  hLJetPtDiff->Write();
  hLJetPtDiff->Write();
  hLJetEnDiff->Write();
  hLJetEnDiff->Write();
  hMuPtDiff->Write();
  hMuPtDiff->Write();
  hMuEnDiff->Write();
  hMuEnDiff->Write();
  hElePtDiff->Write();
  hElePtDiff->Write();
  hEleEnDiff->Write();
  hEleEnDiff->Write();
  hMETPtDiff->Write();
  hMETPtDiff->Write();
  
  // hBJetETResErr->Write(); 
  // hBJetEtaResErr->Write(); 
  // hBJetPhiResErr->Write(); 
  // hLJetETResErr->Write(); 
  // hLJetEtaResErr->Write(); 
  // hLJetPhiResErr->Write(); 
  // hMuETResErr->Write(); 
  // hMuEtaResErr->Write(); 
  // hMuPhiResErr->Write(); 
  // hEleETResErr->Write(); 
  // hEleEtaResErr->Write(); 
  // hElePhiResErr->Write(); 
  fout->Close();
  delete fout;
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////
  fin->Close();
  delete fin;
  
  return true;
}

int PrintBJet(void)
{
  printf("int KinFit::bjetResolution(double et, double eta, double& resEt, double& resEta, double& resPhi)\n");
  printf("{\n");
  printf("\n");
  printf("\t double abseta = fabs(eta) ;\n");
  printf("\n");
  for(int ieta=0;ieta<nJetEtaBins;ieta++){
    if(ieta==0)
      printf("\t if (%4.3f <= abseta and abseta < %4.3f) {\n",jetEtaBin[ieta],jetEtaBin[ieta+1]);
    else
      printf("\t else if (%4.3f <= abseta and abseta < %4.3f) {\n",jetEtaBin[ieta],jetEtaBin[ieta+1]);
    printf("\t\t resEt   = et * ( TMath::Sqrt( TMath::Power(%7.5f,2) + TMath::Power(%7.5f/TMath::Sqrt(et),2) + TMath::Power(%7.5f/et,2) ) ) / 100.  ;\n",
	   BJetETPar[ieta][0],BJetETPar[ieta][1],BJetETPar[ieta][2]);
    printf("\t\t resEta  =  TMath::Sqrt( TMath::Power(%7.5f,2) + TMath::Power(%7.5f/et,2) )  ;\n",BJetEtaPar[ieta][0],BJetEtaPar[ieta][1]);
    printf("\t\t resPhi  =  TMath::Sqrt( TMath::Power(%7.5f,2) + TMath::Power(%7.5f/et,2) )  ;\n",BJetPhiPar[ieta][0],BJetPhiPar[ieta][1]);
    printf("\t }\n");
  }
  printf("\n");
  printf("\t return true ;\n");
  printf("\n");
  printf("}\n");
  printf("\n");

  return true;
}

int PrintLJet(void)
{
  printf("int KinFit::udscResolution(double et, double eta, double& resEt, double& resEta, double& resPhi)\n");
  printf("{\n");
  printf("\n");
  printf("\t double abseta = fabs(eta) ;\n");
  printf("\n");
  for(int ieta=0;ieta<nJetEtaBins;ieta++){
    if(ieta==0)
      printf("\t if (%4.3f <= abseta and abseta < %4.3f) {\n",jetEtaBin[ieta],jetEtaBin[ieta+1]);
    else
      printf("\t else if (%4.3f <= abseta and abseta < %4.3f) {\n",jetEtaBin[ieta],jetEtaBin[ieta+1]);
    printf("\t\t resEt   = et * ( TMath::Sqrt( TMath::Power(%7.5f,2) + TMath::Power(%7.5f/TMath::Sqrt(et),2) + TMath::Power(%7.5f/et,2) ) ) / 100.  ;\n",
	   LJetETPar[ieta][0],LJetETPar[ieta][1],LJetETPar[ieta][2]);
    printf("\t\t resEta  =  TMath::Sqrt( TMath::Power(%7.5f,2) + TMath::Power(%7.5f/et,2) )  ;\n",LJetEtaPar[ieta][0],LJetEtaPar[ieta][1]);
    printf("\t\t resPhi  =  TMath::Sqrt( TMath::Power(%7.5f,2) + TMath::Power(%7.5f/et,2) )  ;\n",LJetPhiPar[ieta][0],LJetPhiPar[ieta][1]);
    printf("\t}\n");
  }
  printf("\n");
  printf("\t return true ;\n");
  printf("\n");
  printf("}\n");
  printf("\n");

  return true;
}

int PlotBJet(void)
{
  //Obtained from Shashi-ji's code
  //////////////////////////////////////////////////////
  char npdf_s[100], npdf_m[100], npdf_e[100];
  sprintf(npdf_s, "BJetPlotsDiff.pdf(");
  sprintf(npdf_m, "BJetPlotsDiff.pdf");
  sprintf(npdf_e, "BJetPlotsDiff.pdf)");
  //////////////////////////////////////////////////////

  TF1 *fnETb = (TF1 *)fnET->Clone("fnETb");
  TF1 *fnETl = (TF1 *)fnET->Clone("fnETl");
  TLegend *legETReso = new TLegend(0.689399,0.6868657,0.9799666,0.9402985);

  fnETb->SetLineColor(kRed);
  fnETl->SetLineColor(kBlue);
  fnETb->SetLineWidth(2);
  fnETl->SetLineWidth(2);

  int nstep = 1000;
  float step = (ETBin[nETBins] - ETBin[0]) / float(nstep) ;
  double resBET, resBEta, resBPhi;
  double resLET, resLEta, resLPhi;
  TGraph *grBET[nJetEtaBins], *grBEta[nJetEtaBins], *grBPhi[nJetEtaBins];
  TGraph *grLET[nJetEtaBins], *grLEta[nJetEtaBins], *grLPhi[nJetEtaBins];
  for(int ieta=0;ieta<nJetEtaBins;ieta++){
    grBET[ieta] = new TGraph(nstep);
    grBEta[ieta] = new TGraph(nstep);
    grBPhi[ieta] = new TGraph(nstep);
    grLET[ieta] = new TGraph(nstep);
    grLEta[ieta] = new TGraph(nstep);
    grLPhi[ieta] = new TGraph(nstep);
    double eta = 0.5*(jetEtaBin[ieta] + jetEtaBin[ieta+1]);
    for(int is=0;is<nstep; is++){
      double et = ETBin[0] + is*step ; 
      bjetResolution(et, eta, resBET, resBEta, resBPhi);
      udscResolution(et, eta, resLET, resLEta, resLPhi);
      grBET[ieta]->SetPoint(is, et, resBET);
      grBEta[ieta]->SetPoint(is, et, resBEta);
      grBPhi[ieta]->SetPoint(is, et, resBPhi);
      grLET[ieta]->SetPoint(is, et, resLET);
      grLEta[ieta]->SetPoint(is, et, resLEta);
      grLPhi[ieta]->SetPoint(is, et, resLPhi);
    }
    grBET[ieta]->SetLineColor(kGreen+1);
    grBET[ieta]->SetLineWidth(2);
    grBEta[ieta]->SetLineColor(kGreen+1);
    grBEta[ieta]->SetLineWidth(2);
    grBPhi[ieta]->SetLineColor(kGreen+1);
    grBPhi[ieta]->SetLineWidth(2);
    grLET[ieta]->SetLineColor(kBlack);
    grLET[ieta]->SetLineWidth(2);
    grLET[ieta]->SetLineStyle(2);
    grLEta[ieta]->SetLineColor(kBlack);
    grLEta[ieta]->SetLineWidth(2);
    grLEta[ieta]->SetLineStyle(2);
    grLPhi[ieta]->SetLineColor(kBlack);
    grLPhi[ieta]->SetLineWidth(2);
    grLPhi[ieta]->SetLineStyle(2);
  }//eta loop
  
  TCanvas *c50[nJetEtaBins];
  for(int ieta=0;ieta<nJetEtaBins;ieta++){
    fnETb->SetParameters(BJetETPar[ieta]);
    fnETl->SetParameters(LJetETPar[ieta]);  
    hBJetETResultNF[ieta]->SetLineColor(kRed); hBJetETResultNF[ieta]->SetLineWidth(2); 
    hLJetETResultNF[ieta]->SetLineColor(kBlue); hLJetETResultNF[ieta]->SetLineWidth(2); 
    hBJetETResultNF[ieta]->SetMarkerStyle(kFullCircle); hBJetETResultNF[ieta]->SetMarkerColor(kRed); hBJetETResultNF[ieta]->SetMarkerSize(2);
    hLJetETResultNF[ieta]->SetMarkerStyle(kFullSquare); hLJetETResultNF[ieta]->SetMarkerColor(kBlue); hLJetETResultNF[ieta]->SetMarkerSize(2);
    
    hBJetPtResultNF[ieta]->SetLineColor(kGreen+1); hBJetPtResultNF[ieta]->SetLineWidth(2); 
    hBJetPtResultNF[ieta]->SetMarkerStyle(kFullStar); hBJetPtResultNF[ieta]->SetMarkerColor(kGreen+1); hBJetPtResultNF[ieta]->SetMarkerSize(3);
    hBJetEnResultNF[ieta]->SetLineColor(kYellow+3); hBJetEnResultNF[ieta]->SetLineWidth(2); 
    hBJetEnResultNF[ieta]->SetMarkerStyle(kFullCross); hBJetEnResultNF[ieta]->SetMarkerColor(kYellow+3); hBJetEnResultNF[ieta]->SetMarkerSize(3);

    hLJetPtResultNF[ieta]->SetLineColor(kBlack); hLJetPtResultNF[ieta]->SetLineWidth(2); 
    hLJetPtResultNF[ieta]->SetMarkerStyle(kFullDiamond); hLJetPtResultNF[ieta]->SetMarkerColor(kBlack); hLJetPtResultNF[ieta]->SetMarkerSize(3);
    hLJetEnResultNF[ieta]->SetLineColor(kMagenta); hLJetEnResultNF[ieta]->SetLineWidth(2); 
    hLJetEnResultNF[ieta]->SetMarkerStyle(kFullTriangleUp); hLJetEnResultNF[ieta]->SetMarkerColor(kMagenta); hLJetEnResultNF[ieta]->SetMarkerSize(3);

    //legETReso->Reset();
    legETReso->Clear();
    legETReso->SetFillColor(10);
    legETReso->AddEntry(hBJetETResultNF[ieta], "bjet: ET Mean" ,"lp");
    legETReso->AddEntry(hLJetETResultNF[ieta], "ljet: ET Mean" ,"lp");
    // legETReso->AddEntry(hBJetPtResultNF[ieta], "bjet: Pt Mean" ,"lp");
    // legETReso->AddEntry(hLJetPtResultNF[ieta], "ljet: Pt Mean" ,"lp");
    // legETReso->AddEntry(hBJetEnResultNF[ieta], "bjet: En Mean" ,"lp");
    // legETReso->AddEntry(hLJetEnResultNF[ieta], "ljet: En Mean" ,"lp");
    // legETReso->AddEntry(grBET[ieta], "bjet: MiniAOD 2016" ,"l");
    // legETReso->AddEntry(grLET[ieta], "ljet: MiniAOD 2016" ,"l");
    // legETReso->AddEntry(fnETb, "#sqrt{ a^{2} + b^{2}/x + c^{2}/x^{2} }" ,"f");
    // legETReso->AddEntry(fnETl, "#sqrt{ a^{2} + b^{2}/x + c^{2}/x^{2} }" ,"f");
    // legETReso->AddEntry((TObject*)0, Form("bjet a : %5.3f +/- %5.3f(%5.3f\%)",fnETb->GetParameter(0), fnETb->GetParError(0), 100.*fnETb->GetParError(0)/fnETb->GetParameter(0)) ,"");
    // legETReso->AddEntry((TObject*)0, Form("bjet b : %5.3f +/- %5.3f(%5.3f\%)",fnETb->GetParameter(1), fnETb->GetParError(1), 100.*fnETb->GetParError(1)/fnETb->GetParameter(1)) ,"");
    // legETReso->AddEntry((TObject*)0, Form("bjet c : %5.3f +/- %5.3f(%5.3f\%)",fnETb->GetParameter(2), fnETb->GetParError(2), 100.*fnETb->GetParError(2)/fnETb->GetParameter(2)) ,"");
    // legETReso->AddEntry((TObject*)0, Form("ljet a : %5.3f +/- %5.3f(%5.3f\%)",fnETl->GetParameter(0), fnETl->GetParError(0), 100.*fnETl->GetParError(0)/fnETl->GetParameter(0)) ,"");
    // legETReso->AddEntry((TObject*)0, Form("ljet b : %5.3f +/- %5.3f(%5.3f\%)",fnETl->GetParameter(1), fnETl->GetParError(1), 100.*fnETl->GetParError(1)/fnETl->GetParameter(1)) ,"");
    // legETReso->AddEntry((TObject*)0, Form("ljet c : %5.3f +/- %5.3f(%5.3f\%)",fnETl->GetParameter(2), fnETl->GetParError(2), 100.*fnETl->GetParError(2)/fnETl->GetParameter(2)) ,"");
    hBJetETResultNF[ieta]->SetMinimum(-10.0);
    hBJetETResultNF[ieta]->SetMaximum(25.0);
    c50[ieta] = new TCanvas(Form("c50_%d",ieta),Form("c50_%d",ieta),1200,800);
    hBJetETResultNF[ieta]->Draw("ep");
    hLJetETResultNF[ieta]->Draw("ep sames");
    // hBJetPtResultNF[ieta]->Draw("ep sames");
    // hBJetEnResultNF[ieta]->Draw("ep sames");
    // hLJetPtResultNF[ieta]->Draw("ep sames");
    // hLJetEnResultNF[ieta]->Draw("ep sames");
    // fnETb->Draw("same");
    // fnETl->Draw("same");
    // grBET[ieta]->Draw("C sames");
    // grLET[ieta]->Draw("C sames");
    legETReso->Draw();
    hBJetETResultNF[ieta]->GetXaxis()->SetTitle("E_{T} (GeV)");
    //hBJetETResultNF[ieta]->GetYaxis()->SetTitle("Relative E_{T} resolution (%)");
    //hBJetETResultNF[ieta]->GetYaxis()->SetTitle("<#DeltaE_{T}>, <#Deltap_{T}>, <#DeltaE>");
    //hBJetETResultNF[ieta]->GetYaxis()->SetTitle("<(Rec_{E_{T}} - Gen_{E_{T}}> (GeV)");
    hBJetETResultNF[ieta]->GetYaxis()->SetTitle("Mean of #DeltaE_{T} (GeV)");
    if(ieta==0)
      c50[ieta]->SaveAs(npdf_s);
    else
      c50[ieta]->SaveAs(npdf_m);
  }


  TF1 *fnEtab = (TF1 *)fnEta->Clone("fnEtab");
  TF1 *fnEtal = (TF1 *)fnEta->Clone("fnEtal");
  TLegend *legEtaReso = new TLegend(0.689399,0.7568657,0.9799666,0.9402985);

  fnEtab->SetLineColor(kRed);
  fnEtal->SetLineColor(kBlue);
  fnEtab->SetLineWidth(2);
  fnEtal->SetLineWidth(2);
  
  TCanvas *c51[nJetEtaBins];
  for(int ieta=0;ieta<nJetEtaBins;ieta++){
    fnEtab->SetParameters(BJetEtaPar[ieta]);
    fnEtal->SetParameters(LJetEtaPar[ieta]);  
    hBJetEtaResultNF[ieta]->SetLineColor(kRed); hBJetEtaResultNF[ieta]->SetLineWidth(2); 
    hLJetEtaResultNF[ieta]->SetLineColor(kBlue); hLJetEtaResultNF[ieta]->SetLineWidth(2); 
    hBJetEtaResultNF[ieta]->SetMarkerStyle(kFullCircle); hBJetEtaResultNF[ieta]->SetMarkerColor(kRed); hBJetEtaResultNF[ieta]->SetMarkerSize(2);
    hLJetEtaResultNF[ieta]->SetMarkerStyle(kFullSquare); hLJetEtaResultNF[ieta]->SetMarkerColor(kBlue); hLJetEtaResultNF[ieta]->SetMarkerSize(2);
    //legEtaReso->Reset();
    legEtaReso->Clear();
    legEtaReso->SetFillColor(10);
    legEtaReso->AddEntry(hBJetEtaResultNF[ieta], "bjet: Mean" ,"lp");
    legEtaReso->AddEntry(hLJetEtaResultNF[ieta], "ljet: Mean" ,"lp");
    // legEtaReso->AddEntry(grBEta[ieta], "bjet : MiniAOD 2016" ,"l");
    // legEtaReso->AddEntry(grLEta[ieta], "ljet : MiniAOD 2016" ,"l");
    // legEtaReso->AddEntry(fnEtab, "#sqrt{ a^{2} + b^{2}/x^{2} }" ,"f");
    // legEtaReso->AddEntry(fnEtal, "#sqrt{ a^{2} + b^{2}/x^{2} }" ,"f");
    // legEtaReso->AddEntry((TObject*)0, Form("bjet a : %5.3f +/- %5.3f(%5.3f\%)",fnEtab->GetParameter(0), fnEtab->GetParError(0), 100.*fnEtab->GetParError(0)/fnEtab->GetParameter(0)) ,"");
    // legEtaReso->AddEntry((TObject*)0, Form("bjet b : %5.3f +/- %5.3f(%5.3f\%)",fnEtab->GetParameter(1), fnEtab->GetParError(1), 100.*fnEtab->GetParError(1)/fnEtab->GetParameter(1)) ,"");
    // legEtaReso->AddEntry((TObject*)0, Form("ljet a : %5.3f +/- %5.3f(%5.3f\%)",fnEtal->GetParameter(0), fnEtal->GetParError(0), 100.*fnEtal->GetParError(0)/fnEtal->GetParameter(0)) ,"");
    // legEtaReso->AddEntry((TObject*)0, Form("ljet b : %5.3f +/- %5.3f(%5.3f\%)",fnEtal->GetParameter(1), fnEtal->GetParError(1), 100.*fnEtal->GetParError(1)/fnEtal->GetParameter(1)) ,"");
    hBJetEtaResultNF[ieta]->SetMinimum(-0.04);
    hBJetEtaResultNF[ieta]->SetMaximum(0.07);
    c51[ieta] = new TCanvas(Form("c51_%d",ieta),Form("c51_%d",ieta),1200,800);
    hBJetEtaResultNF[ieta]->Draw("ep");
    hLJetEtaResultNF[ieta]->Draw("ep sames");
    // fnEtab->Draw("same");
    // fnEtal->Draw("same");
    // grBEta[ieta]->Draw("C sames");
    // grLEta[ieta]->Draw("C sames");
    legEtaReso->Draw();
    hBJetEtaResultNF[ieta]->GetXaxis()->SetTitle("E_{T} (GeV)");
    hBJetEtaResultNF[ieta]->GetYaxis()->SetTitle("<#Delta#eta>");
    c51[ieta]->SaveAs(npdf_m);
  }

  TF1 *fnPhib = (TF1 *)fnPhi->Clone("fnPhib");
  TF1 *fnPhil = (TF1 *)fnPhi->Clone("fnPhil");
  TLegend *legPhiReso = new TLegend(0.689399,0.7568657,0.9799666,0.9402985);

  fnPhib->SetLineColor(kRed);
  fnPhil->SetLineColor(kBlue);
  fnPhib->SetLineWidth(2);
  fnPhil->SetLineWidth(2);
  
  TCanvas *c52[nJetEtaBins];
  for(int ieta=0;ieta<nJetEtaBins;ieta++){
    fnPhib->SetParameters(BJetPhiPar[ieta]);
    fnPhil->SetParameters(LJetPhiPar[ieta]);  
    hBJetPhiResultNF[ieta]->SetLineColor(kRed); hBJetPhiResultNF[ieta]->SetLineWidth(2); 
    hLJetPhiResultNF[ieta]->SetLineColor(kBlue); hLJetPhiResultNF[ieta]->SetLineWidth(2); 
    hBJetPhiResultNF[ieta]->SetMarkerStyle(kFullCircle); hBJetPhiResultNF[ieta]->SetMarkerColor(kRed); hBJetPhiResultNF[ieta]->SetMarkerSize(2);
    hLJetPhiResultNF[ieta]->SetMarkerStyle(kFullSquare); hLJetPhiResultNF[ieta]->SetMarkerColor(kBlue); hLJetPhiResultNF[ieta]->SetMarkerSize(2);
    //legPhiReso->Reset();
    legPhiReso->Clear();
    legPhiReso->SetFillColor(10);
    legPhiReso->AddEntry(hBJetPhiResultNF[ieta], "bjet: Mean" ,"lp");
    legPhiReso->AddEntry(hLJetPhiResultNF[ieta], "ljet: Mean" ,"lp");
    // legPhiReso->AddEntry(grBPhi[ieta], "bjet : MiniAOD 2016" ,"l");
    // legPhiReso->AddEntry(grLPhi[ieta], "ljet : MiniAOD 2016" ,"l");

    // legPhiReso->AddEntry(fnPhib, "#sqrt{ a^{2} + b^{2}/x^{2} }" ,"f");
    // legPhiReso->AddEntry(fnPhil, "#sqrt{ a^{2} + b^{2}/x^{2} }" ,"f");
    // legPhiReso->AddEntry((TObject*)0, Form("bjet a : %5.3f +/- %5.3f(%5.3f\%)",fnPhib->GetParameter(0), fnPhib->GetParError(0), 100.*fnPhib->GetParError(0)/fnPhib->GetParameter(0)) ,"");
    // legPhiReso->AddEntry((TObject*)0, Form("bjet b : %5.3f +/- %5.3f(%5.3f\%)",fnPhib->GetParameter(1), fnPhib->GetParError(1), 100.*fnPhib->GetParError(1)/fnPhib->GetParameter(1)) ,"");
    // legPhiReso->AddEntry((TObject*)0, Form("ljet a : %5.3f +/- %5.3f(%5.3f\%)",fnPhil->GetParameter(0), fnPhil->GetParError(0), 100.*fnPhil->GetParError(0)/fnPhil->GetParameter(0)) ,"");
    // legPhiReso->AddEntry((TObject*)0, Form("ljet b : %5.3f +/- %5.3f(%5.3f\%)",fnPhil->GetParameter(1), fnPhil->GetParError(1), 100.*fnPhil->GetParError(1)/fnPhil->GetParameter(1)) ,"");
    hBJetPhiResultNF[ieta]->SetMinimum(-0.07);
    hBJetPhiResultNF[ieta]->SetMaximum(0.07);
    c52[ieta] = new TCanvas(Form("c52_%d",ieta),Form("c52_%d",ieta),1200,800);
    hBJetPhiResultNF[ieta]->Draw("ep");
    hLJetPhiResultNF[ieta]->Draw("ep sames");
    // fnPhib->Draw("same");
    // fnPhil->Draw("same");
    // grBPhi[ieta]->Draw("C sames");
    // grLPhi[ieta]->Draw("C sames");
    legPhiReso->Draw();
    hBJetPhiResultNF[ieta]->GetXaxis()->SetTitle("E_{T} (GeV)");
    hBJetPhiResultNF[ieta]->GetYaxis()->SetTitle("<#Delta#phi>");
    if(ieta==(nJetEtaBins-1))
      c52[ieta]->SaveAs(npdf_e);
    else
      c52[ieta]->SaveAs(npdf_m);
  }



  return true;
}

int PlotMu(void)
{
  //Obtained from Shashi-ji's code
  //////////////////////////////////////////////////////
  char npdf_s[100], npdf_m[100], npdf_e[100];
  sprintf(npdf_s, "MuPlotsDiff.pdf(");
  sprintf(npdf_m, "MuPlotsDiff.pdf");
  sprintf(npdf_e, "MuPlotsDiff.pdf)");
  //////////////////////////////////////////////////////

  TF1 *fnMuET = (TF1 *)fnETMu->Clone("fnMuET");
  fnMuET->SetLineColor(kRed);
  fnMuET->SetLineWidth(2);

  TLegend *legMuReso = new TLegend(0.689399,0.7568657,0.9799666,0.9402985);


  int nstep = 1000;
  float step = (ETBin[nETBins] - ETBin[0]) / float(nstep) ;
  double resET, resEta, resPhi;
  TGraph *grET[nMuEtaBins], *grEta[nMuEtaBins], *grPhi[nMuEtaBins];
  for(int ieta=0;ieta<nMuEtaBins;ieta++){
    grET[ieta] = new TGraph(nstep);
    grEta[ieta] = new TGraph(nstep);
    grPhi[ieta] = new TGraph(nstep);
    double eta = 0.5*(muEtaBin[ieta] + muEtaBin[ieta+1]);
    for(int is=0;is<nstep; is++){
      double et = ETBin[0] + is*step ; 
      muonResolution(et, eta, resET, resEta, resPhi);
      //resET /= et;
      //resET *= 100.0;
      grET[ieta]->SetPoint(is, et, resET);
      grEta[ieta]->SetPoint(is, et, resEta);
      grPhi[ieta]->SetPoint(is, et, resPhi);
    }
    grET[ieta]->SetLineColor(kGreen+2);
    grET[ieta]->SetLineWidth(2);
    grEta[ieta]->SetLineColor(kGreen+2);
    grEta[ieta]->SetLineWidth(2);
    grPhi[ieta]->SetLineColor(kGreen+2);
    grPhi[ieta]->SetLineWidth(2);
  }//eta loop
  
  TCanvas *c100[nMuEtaBins];
  for(int ieta=0;ieta<nMuEtaBins;ieta++){
    hMuETResult[ieta]->SetLineColor(kRed); hMuETResult[ieta]->SetLineWidth(2); 
    hMuETResult[ieta]->SetMarkerStyle(kFullCircle); hMuETResult[ieta]->SetMarkerColor(kRed); hMuETResult[ieta]->SetMarkerSize(2.0);
    hMuETResultNF[ieta]->SetLineColor(kBlue); hMuETResultNF[ieta]->SetLineWidth(2); 
    hMuETResultNF[ieta]->SetMarkerStyle(kFullSquare); hMuETResultNF[ieta]->SetMarkerColor(kBlue); hMuETResultNF[ieta]->SetMarkerSize(2.0);

    hMuPtResultNF[ieta]->SetLineColor(kGreen+1); hMuPtResultNF[ieta]->SetLineWidth(2); 
    hMuPtResultNF[ieta]->SetMarkerStyle(kFullStar); hMuPtResultNF[ieta]->SetMarkerColor(kGreen+1); hMuPtResultNF[ieta]->SetMarkerSize(3);
    hMuEnResultNF[ieta]->SetLineColor(kYellow+3); hMuEnResultNF[ieta]->SetLineWidth(2); 
    hMuEnResultNF[ieta]->SetMarkerStyle(kFullCross); hMuEnResultNF[ieta]->SetMarkerColor(kYellow+3); hMuEnResultNF[ieta]->SetMarkerSize(3);

    legMuReso->Clear();
    legMuReso->SetFillColor(10);
    legMuReso->AddEntry(hMuETResult[ieta], "muon : fitted mean" ,"lp");
    legMuReso->AddEntry(hMuETResultNF[ieta], "muon : Et Mean" ,"lp");
    legMuReso->AddEntry(hMuPtResultNF[ieta], "muon : Pt Mean" ,"lp");
    legMuReso->AddEntry(hMuEnResultNF[ieta], "muon : En Mean" ,"lp");
    //legMuReso->AddEntry(grET[ieta], "muon : MiniAOD 2016" ,"l");
    // legMuReso->AddEntry(fnMuET, "a + b*x" ,"f");
    // legMuReso->AddEntry((TObject*)0, Form("bjet a : %5.3f +/- %5.3f(%5.3f\%)",fnMuET->GetParameter(0), fnMuET->GetParError(0), 100.*fnMuET->GetParError(0)/fnMuET->GetParameter(0)) ,"");
    // legMuReso->AddEntry((TObject*)0, Form("bjet b : %5.3f +/- %5.3f(%5.3f\%)",fnMuET->GetParameter(1), fnMuET->GetParError(1), 100.*fnMuET->GetParError(1)/fnMuET->GetParameter(1)) ,"");
    hMuETResultNF[ieta]->SetMinimum(-10.0);
    hMuETResultNF[ieta]->SetMaximum(50.);
    c100[ieta] = new TCanvas(Form("c100_%d",ieta),Form("c100_%d",ieta),1200,800);
    // hMuETResult[ieta]->Draw("ep");
    // hMuETResultNF[ieta]->Draw("ep sames");
    hMuETResultNF[ieta]->Draw("ep");
    hMuETResult[ieta]->Draw("ep sames");
    hMuPtResultNF[ieta]->Draw("ep sames");
    hMuEnResultNF[ieta]->Draw("ep sames");
    // grET[ieta]->Draw("C sames");
    // fnMuET->Draw("same");
    legMuReso->Draw();
    //hMuETResult[ieta]->GetXaxis()->SetTitle("E_{T} (GeV)");
    // hMuETResult[ieta]->GetYaxis()->SetTitle("Relative E_{T} resolution (%)");
    //hMuETResult[ieta]->GetYaxis()->SetTitle("Absolute E_{T} resolution");
    hMuETResultNF[ieta]->GetXaxis()->SetTitle("E_{T} (GeV)");
    //hMuETResultNF[ieta]->GetYaxis()->SetTitle("Relative E_{T} resolution (%)");
    hMuETResultNF[ieta]->GetYaxis()->SetTitle("<#DeltaE_{T}>");
    if(ieta==0)
      c100[ieta]->SaveAs(npdf_s);
    else
      c100[ieta]->SaveAs(npdf_m);
  }


  TCanvas *c101[nMuEtaBins];
  for(int ieta=0;ieta<nMuEtaBins;ieta++){
    hMuEtaResult[ieta]->SetLineColor(kRed); hMuEtaResult[ieta]->SetLineWidth(2); 
    hMuEtaResult[ieta]->SetMarkerStyle(kFullCircle); hMuEtaResult[ieta]->SetMarkerColor(kRed); hMuEtaResult[ieta]->SetMarkerSize(2.0);
    hMuEtaResultNF[ieta]->SetLineColor(kBlue); hMuEtaResultNF[ieta]->SetLineWidth(2); 
    hMuEtaResultNF[ieta]->SetMarkerStyle(kFullSquare); hMuEtaResultNF[ieta]->SetMarkerColor(kBlue); hMuEtaResultNF[ieta]->SetMarkerSize(2.0);
    legMuReso->Clear();
    legMuReso->SetFillColor(10);
    legMuReso->AddEntry(hMuEtaResult[ieta], "muon : fitted mean" ,"lp");
    legMuReso->AddEntry(hMuEtaResultNF[ieta], "muon : Mean" ,"lp");
    //legMuReso->AddEntry(grEta[ieta], "muon : MiniAOD 2016" ,"l");
    hMuEtaResultNF[ieta]->SetMinimum(-0.004);
    hMuEtaResultNF[ieta]->SetMaximum(0.004);
    c101[ieta] = new TCanvas(Form("c101_%d",ieta),Form("c101_%d",ieta),1200,800);
    // hMuEtaResult[ieta]->Draw("ep");
    // hMuEtaResultNF[ieta]->Draw("ep sames");
    hMuEtaResultNF[ieta]->Draw("ep");
    hMuEtaResult[ieta]->Draw("ep sames");
    // grEta[ieta]->Draw("C sames");
    legMuReso->Draw();
    // hMuEtaResult[ieta]->GetXaxis()->SetTitle("E_{T} (GeV)");
    // hMuEtaResult[ieta]->GetYaxis()->SetTitle("Absolute #eta resolution");
    // hMuEtaResult[ieta]->GetYaxis()->SetTitleOffset(1.4);
    hMuEtaResultNF[ieta]->GetXaxis()->SetTitle("E_{T} (GeV)");
    hMuEtaResultNF[ieta]->GetYaxis()->SetTitle("<#Delta#eta>");
    hMuEtaResultNF[ieta]->GetYaxis()->SetTitleOffset(1.4);

    // if(ieta==nMuEtaBins-1)
    //   c101[ieta]->SaveAs(npdf_e);
    // else
    c101[ieta]->SaveAs(npdf_m);
  }

  TCanvas *c102[nMuEtaBins];
  for(int ieta=0;ieta<nMuEtaBins;ieta++){
    hMuPhiResult[ieta]->SetLineColor(kRed); hMuPhiResult[ieta]->SetLineWidth(2); 
    hMuPhiResult[ieta]->SetMarkerStyle(kFullCircle); hMuPhiResult[ieta]->SetMarkerColor(kRed); hMuPhiResult[ieta]->SetMarkerSize(2.0);
    hMuPhiResultNF[ieta]->SetLineColor(kBlue); hMuPhiResultNF[ieta]->SetLineWidth(2); 
    hMuPhiResultNF[ieta]->SetMarkerStyle(kFullSquare); hMuPhiResultNF[ieta]->SetMarkerColor(kBlue); hMuPhiResultNF[ieta]->SetMarkerSize(2.0);
    legMuReso->Clear();
    legMuReso->SetFillColor(10);
    legMuReso->AddEntry(hMuPhiResult[ieta], "muon : fitted mean" ,"lp");
    legMuReso->AddEntry(hMuPhiResultNF[ieta], "muon : Mean" ,"lp");
    //legMuReso->AddEntry(grPhi[ieta], "muon : MiniAOD 2016" ,"l");
    hMuPhiResultNF[ieta]->SetMinimum(-0.001);
    hMuPhiResultNF[ieta]->SetMaximum(0.005);
    c102[ieta] = new TCanvas(Form("c102_%d",ieta),Form("c102_%d",ieta),1200,800);
    // hMuPhiResult[ieta]->Draw("ep");
    // hMuPhiResultNF[ieta]->Draw("ep sames");
    hMuPhiResultNF[ieta]->Draw("ep");
    hMuPhiResult[ieta]->Draw("ep sames");
    // grPhi[ieta]->Draw("C sames");
    legMuReso->Draw();
    // hMuPhiResult[ieta]->GetXaxis()->SetTitle("E_{T} (GeV)");
    // hMuPhiResult[ieta]->GetYaxis()->SetTitle("Absolute #phi resolution");
    hMuPhiResultNF[ieta]->GetXaxis()->SetTitle("E_{T} (GeV)");
    hMuPhiResultNF[ieta]->GetYaxis()->SetTitle("<#Delta#phi>");
    hMuPhiResultNF[ieta]->GetYaxis()->SetTitleOffset(1.2);
    if(ieta==nMuEtaBins-1)
      c102[ieta]->SaveAs(npdf_e);
    else
      c102[ieta]->SaveAs(npdf_m);
  }

  return true;
}

int PlotEle(void)
{
  //Obtained from Shashi-ji's code
  //////////////////////////////////////////////////////
  char npdf_s[100], npdf_m[100], npdf_e[100];
  sprintf(npdf_s, "ElePlotsDiff.pdf(");
  sprintf(npdf_m, "ElePlotsDiff.pdf");
  sprintf(npdf_e, "ElePlotsDiff.pdf)");
  //////////////////////////////////////////////////////

  TF1 *fnEleET = (TF1 *)fnETEle->Clone("fnEleET");
  fnEleET->SetLineColor(kRed);
  fnEleET->SetLineWidth(2);

  TLegend *legEleReso = new TLegend(0.689399,0.7568657,0.9799666,0.9402985);


  int nstep = 1000;
  float step = (ETBin[nETBins] - ETBin[0]) / float(nstep) ;
  double resET, resEta, resPhi;
  TGraph *grEleET[nEleEtaBins], *grEleEta[nEleEtaBins], *grElePhi[nEleEtaBins];
  for(int ieta=0;ieta<nEleEtaBins;ieta++){
    grEleET[ieta] = new TGraph(nstep);
    grEleEta[ieta] = new TGraph(nstep);
    grElePhi[ieta] = new TGraph(nstep);
    double eta = 0.5*(eleEtaBin[ieta] + eleEtaBin[ieta+1]);
    for(int is=0;is<nstep; is++){
      double et = ETBin[0] + is*step ; 
      elecResolution(et, eta, resET, resEta, resPhi);
      //resET /= et;
      //resET *= 100.0;
      grEleET[ieta]->SetPoint(is, et, resET);
      grEleEta[ieta]->SetPoint(is, et, resEta);
      grElePhi[ieta]->SetPoint(is, et, resPhi);
    }
    grEleET[ieta]->SetLineColor(kGreen+2);
    grEleET[ieta]->SetLineWidth(2);
    grEleEta[ieta]->SetLineColor(kGreen+2);
    grEleEta[ieta]->SetLineWidth(2);
    grElePhi[ieta]->SetLineColor(kGreen+2);
    grElePhi[ieta]->SetLineWidth(2);
  }//eta loop
  
  TCanvas *c200[nEleEtaBins];
  for(int ieta=0;ieta<nEleEtaBins;ieta++){

    hEleETResult[ieta]->SetLineColor(kRed); hEleETResult[ieta]->SetLineWidth(2); 
    hEleETResult[ieta]->SetMarkerStyle(kFullCircle); hEleETResult[ieta]->SetMarkerColor(kRed); hEleETResult[ieta]->SetMarkerSize(2.0);
    hEleETResultNF[ieta]->SetLineColor(kBlue); hEleETResultNF[ieta]->SetLineWidth(2); 
    hEleETResultNF[ieta]->SetMarkerStyle(kFullSquare); hEleETResultNF[ieta]->SetMarkerColor(kBlue); hEleETResultNF[ieta]->SetMarkerSize(2.0);

    hElePtResultNF[ieta]->SetLineColor(kGreen+1); hElePtResultNF[ieta]->SetLineWidth(2); 
    hElePtResultNF[ieta]->SetMarkerStyle(kFullStar); hElePtResultNF[ieta]->SetMarkerColor(kGreen+1); hElePtResultNF[ieta]->SetMarkerSize(3);
    hEleEnResultNF[ieta]->SetLineColor(kYellow+3); hEleEnResultNF[ieta]->SetLineWidth(2); 
    hEleEnResultNF[ieta]->SetMarkerStyle(kFullCross); hEleEnResultNF[ieta]->SetMarkerColor(kYellow+3); hEleEnResultNF[ieta]->SetMarkerSize(3);

    legEleReso->Clear();
    legEleReso->SetFillColor(10);
    legEleReso->AddEntry(hEleETResult[ieta], "elec: fitted mean" ,"lp");
    legEleReso->AddEntry(hEleETResultNF[ieta], "elec: Et Mean" ,"lp");
    legEleReso->AddEntry(hElePtResultNF[ieta], "elec: Pt Mean" ,"lp");
    legEleReso->AddEntry(hEleEnResultNF[ieta], "elec: En Mean" ,"lp");
    //legEleReso->AddEntry(grEleET[ieta], "elec: MiniAOD 2016" ,"l");
    // legEleReso->AddEntry(fnEleET, "a + b*x" ,"f");
    // legEleReso->AddEntry((TObject*)0, Form("bjet a : %5.3f +/- %5.3f(%5.3f\%)",fnEleET->GetParameter(0), fnEleET->GetParError(0), 100.*fnEleET->GetParError(0)/fnEleET->GetParameter(0)) ,"");
    // legEleReso->AddEntry((TObject*)0, Form("bjet b : %5.3f +/- %5.3f(%5.3f\%)",fnEleET->GetParameter(1), fnEleET->GetParError(1), 100.*fnEleET->GetParError(1)/fnEleET->GetParameter(1)) ,"");
    hEleETResultNF[ieta]->SetMinimum(-5.0);
    hEleETResultNF[ieta]->SetMaximum(15.);
    c200[ieta] = new TCanvas(Form("c200_%d",ieta),Form("c200_%d",ieta),1200,800);
    // hEleETResult[ieta]->Draw("ep");
    // hEleETResultNF[ieta]->Draw("ep sames");
    hEleETResultNF[ieta]->Draw("ep");
    hEleETResult[ieta]->Draw("ep sames");
    hElePtResultNF[ieta]->Draw("ep sames");
    hEleEnResultNF[ieta]->Draw("ep sames");
    // grEleET[ieta]->Draw("C sames");
    // fnEleET->Draw("same");
    legEleReso->Draw();
    //hEleETResult[ieta]->GetXaxis()->SetTitle("E_{T} (GeV)");
    // hEleETResult[ieta]->GetYaxis()->SetTitle("Relative E_{T} resolution (%)");
    //hEleETResult[ieta]->GetYaxis()->SetTitle("Absolute E_{T} resolution");
    hEleETResultNF[ieta]->GetXaxis()->SetTitle("E_{T} (GeV)");
    //hEleETResultNF[ieta]->GetYaxis()->SetTitle("Relative E_{T} resolution (%)");
    hEleETResultNF[ieta]->GetYaxis()->SetTitle("<#DeltaE_{T}>");
    if(ieta==0)
      c200[ieta]->SaveAs(npdf_s);
    else
      c200[ieta]->SaveAs(npdf_m);
  }

  TCanvas *c201[nEleEtaBins];
  for(int ieta=0;ieta<nEleEtaBins;ieta++){
    hEleEtaResult[ieta]->SetLineColor(kRed); hEleEtaResult[ieta]->SetLineWidth(2); 
    hEleEtaResult[ieta]->SetMarkerStyle(kFullCircle); hEleEtaResult[ieta]->SetMarkerColor(kRed); hEleEtaResult[ieta]->SetMarkerSize(2.0);
    hEleEtaResultNF[ieta]->SetLineColor(kBlue); hEleEtaResultNF[ieta]->SetLineWidth(2); 
    hEleEtaResultNF[ieta]->SetMarkerStyle(kFullSquare); hEleEtaResultNF[ieta]->SetMarkerColor(kBlue); hEleEtaResultNF[ieta]->SetMarkerSize(2.0);
    legEleReso->Clear();
    legEleReso->SetFillColor(10);
    legEleReso->AddEntry(hEleEtaResult[ieta], "elec:fitted mean" ,"lp");
    legEleReso->AddEntry(hEleEtaResultNF[ieta], "elec:Mean" ,"lp");
    //legEleReso->AddEntry(grEleEta[ieta], "elec:MiniAOD 2016" ,"l");
    hEleEtaResultNF[ieta]->SetMinimum(-0.001);
    hEleEtaResultNF[ieta]->SetMaximum(0.006);
    c201[ieta] = new TCanvas(Form("c201_%d",ieta),Form("c201_%d",ieta),1200,800);
    // hEleEtaResult[ieta]->Draw("ep");
    // hEleEtaResultNF[ieta]->Draw("ep sames");
    hEleEtaResultNF[ieta]->Draw("ep");
    hEleEtaResult[ieta]->Draw("ep sames");
    // grEleEta[ieta]->Draw("C sames");
    legEleReso->Draw();
    // hEleEtaResult[ieta]->GetXaxis()->SetTitle("E_{T} (GeV)");
    // hEleEtaResult[ieta]->GetYaxis()->SetTitle("Absolute #eta resolution");
    // hEleEtaResult[ieta]->GetYaxis()->SetTitleOffset(1.4);
    hEleEtaResultNF[ieta]->GetXaxis()->SetTitle("E_{T} (GeV)");
    hEleEtaResultNF[ieta]->GetYaxis()->SetTitle("<#Delta#eta>");
    hEleEtaResultNF[ieta]->GetYaxis()->SetTitleOffset(1.4);

    // if(ieta==nEleEtaBins-1)
    //   c201[ieta]->SaveAs(npdf_e);
    // else
    c201[ieta]->SaveAs(npdf_m);
  }

  TCanvas *c202[nEleEtaBins];
  for(int ieta=0;ieta<nEleEtaBins;ieta++){
    hElePhiResult[ieta]->SetLineColor(kRed); hElePhiResult[ieta]->SetLineWidth(2); 
    hElePhiResult[ieta]->SetMarkerStyle(kFullCircle); hElePhiResult[ieta]->SetMarkerColor(kRed); hElePhiResult[ieta]->SetMarkerSize(2.0);
    hElePhiResultNF[ieta]->SetLineColor(kBlue); hElePhiResultNF[ieta]->SetLineWidth(2); 
    hElePhiResultNF[ieta]->SetMarkerStyle(kFullSquare); hElePhiResultNF[ieta]->SetMarkerColor(kBlue); hElePhiResultNF[ieta]->SetMarkerSize(2.0);
    legEleReso->Clear();
    legEleReso->SetFillColor(10);
    legEleReso->AddEntry(hElePhiResult[ieta], "elec:fitted mean" ,"lp");
    legEleReso->AddEntry(hElePhiResultNF[ieta], "elec:Mean" ,"lp");
    //legEleReso->AddEntry(grElePhi[ieta], "elec:MiniAOD 2016" ,"l");
    hElePhiResultNF[ieta]->SetMinimum(-0.005);
    hElePhiResultNF[ieta]->SetMaximum(0.01);
    c202[ieta] = new TCanvas(Form("c202_%d",ieta),Form("c202_%d",ieta),1200,800);
    // hElePhiResult[ieta]->Draw("ep");
    // hElePhiResultNF[ieta]->Draw("ep sames");
    hElePhiResultNF[ieta]->Draw("ep");
    hElePhiResult[ieta]->Draw("ep sames");
    // grElePhi[ieta]->Draw("C sames");
    legEleReso->Draw();
    // hElePhiResult[ieta]->GetXaxis()->SetTitle("E_{T} (GeV)");
    // hElePhiResult[ieta]->GetYaxis()->SetTitle("Absolute #phi resolution");
    hElePhiResultNF[ieta]->GetXaxis()->SetTitle("E_{T} (GeV)");
    hElePhiResultNF[ieta]->GetYaxis()->SetTitle("<#Delta#phi>");
    if(ieta==nEleEtaBins-1)
      c202[ieta]->SaveAs(npdf_e);
    else
      c202[ieta]->SaveAs(npdf_m);
  }

  return true;
}

int PlotMET(void)
{
  //Obtained from Shashi-ji's code
  //////////////////////////////////////////////////////
  char npdf_s[100], npdf_m[100], npdf_e[100];
  sprintf(npdf_s, "METPlotsDiff.pdf(");
  sprintf(npdf_m, "METPlotsDiff.pdf");
  sprintf(npdf_e, "METPlotsDiff.pdf)");
  //////////////////////////////////////////////////////

  // TF1 *fnMETET = (TF1 *)fnETMET->Clone("fnMETET");
  // fnMETET->SetLineColor(kRed);
  // fnMETET->SetLineWidth(2);

  TLegend *legMETReso = new TLegend(0.639399,0.6268657,0.9799666,0.9402985);


  int nstep = 1000;
  float step = (ETBin[nETBins] - ETBin[0]) / float(nstep) ;
  double resET, resEta, resPhi;
  TGraph *grMETET, *grMETPhi;

  grMETET = new TGraph(nstep);
  grMETPhi = new TGraph(nstep);
  for(int is=0;is<nstep; is++){
    double et = ETBin[0] + is*step ; 
    metResolution(et, resET, resEta, resPhi);
    grMETET->SetPoint(is, et, resET);
    grMETPhi->SetPoint(is, et, resPhi);
  }
  grMETET->SetLineColor(kGreen+2);
  grMETET->SetLineWidth(2);
  grMETPhi->SetLineColor(kGreen+2);
  grMETPhi->SetLineWidth(2);
  
  TCanvas *c300;
  hMETETResultNF->SetLineColor(kBlue); hMETETResultNF->SetLineWidth(2); 
  hMETETResultNF->SetMarkerStyle(kFullSquare); hMETETResultNF->SetMarkerColor(kBlue); hMETETResultNF->SetMarkerSize(2.0);
  hMETPtResultNF->SetLineColor(kRed); hMETPtResultNF->SetLineWidth(2); 
  hMETPtResultNF->SetMarkerStyle(kFullCircle); hMETPtResultNF->SetMarkerColor(kRed); hMETPtResultNF->SetMarkerSize(2.0);

  legMETReso->Clear();
  legMETReso->SetFillColor(10);
  //legMETReso->AddEntry(hMETETResult, "Missing E_{T}: fitted sigma" ,"lp");
  legMETReso->AddEntry(hMETETResultNF, "Missing E_{T}: Mean" ,"lp");
  legMETReso->AddEntry(hMETPtResultNF, "Missing p_{T}: Mean" ,"lp");
  //legMETReso->AddEntry(grMETET, "Missing E_{T}: MiniAOD 2016" ,"l");
  hMETETResultNF->SetMinimum(-10.0);
  hMETETResultNF->SetMaximum(50.);
  c300 = new TCanvas("c300","c300",1200,800);
  // hMETETResult->Draw("ep");
  // hMETETResultNF->Draw("ep sames");
  hMETETResultNF->Draw("ep");
  hMETPtResultNF->Draw("ep sames");
  //hMETETResult->Draw("ep sames");
  // grMETET->Draw("C sames");
  // fnMETET->Draw("same");
  legMETReso->Draw();
  hMETETResultNF->GetXaxis()->SetTitle("E_{T} (GeV)");
  //hMETETResultNF->GetYaxis()->SetTitle("Relative E_{T} resolution (%)");
  hMETETResultNF->GetYaxis()->SetTitle("<#DeltaE_{T}>");
  c300->SaveAs(npdf_s);

  TCanvas *c301;
  hMETPhiResultNF->SetLineColor(kBlue); hMETPhiResultNF->SetLineWidth(2); 
  hMETPhiResultNF->SetMarkerStyle(kFullSquare); hMETPhiResultNF->SetMarkerColor(kBlue); hMETPhiResultNF->SetMarkerSize(2.0);
  legMETReso->Clear();
  legMETReso->SetFillColor(10);
  //legMETReso->AddEntry(hMETPhiResult, "Missing E_{T}: fitted sigma" ,"lp");
  legMETReso->AddEntry(hMETPhiResultNF, "Missing E_{T}: Mean" ,"lp");
  //legMETReso->AddEntry(grMETPhi, "Missing E_{T}: MiniAOD 2016" ,"l");
  hMETPhiResultNF->SetMinimum(-1.0);
  hMETPhiResultNF->SetMaximum(1.0);
  c301 = new TCanvas("c301","c301",1200,800);
  // hMETPhiResult->Draw("ep");
  // hMETPhiResultNF->Draw("ep sames");
  hMETPhiResultNF->Draw("ep");
  //hMETPhiResult->Draw("ep sames");
  // grMETPhi->Draw("C sames");
  // fnMETPhi->Draw("same");
  legMETReso->Draw();
  hMETPhiResultNF->GetXaxis()->SetTitle("E_{T} (GeV)");
  //hMETPhiResultNF->GetYaxis()->SetTitle("Relative E_{T} resolution (%)");
  hMETPhiResultNF->GetYaxis()->SetTitle("<#Delta#phi>");
  c301->SaveAs(npdf_e);
  


  return true;
}



int udscResolution(double et, double eta, double& resEt, double& resEta, double& resPhi)
{

  double abseta = fabs(eta) ;
  
  if (0.000 <= abseta  and  abseta < 0.087){
    resEt   = et * (TMath::Sqrt( TMath::Power(0.0591,2) + TMath::Power(1/TMath::Sqrt(et),2) + TMath::Power(0.891/et,2) ) ) ;
    resEta  = TMath::Sqrt( TMath::Power(0.00915,2) + TMath::Power(1.51/et,2) ) ;
    resPhi  = TMath::Sqrt( TMath::Power(0.01,2) + TMath::Power(1.6/et,2) ) ;
  }
    
  else if (0.087 <= abseta  and  abseta < 0.174){
    resEt   = et * (TMath::Sqrt( TMath::Power(0.0619,2) + TMath::Power(0.975/TMath::Sqrt(et),2) + TMath::Power(1.54/et,2) ) ) ;
    resEta  = TMath::Sqrt( TMath::Power(0.00887,2) + TMath::Power(1.53/et,2) ) ;
    resPhi  = TMath::Sqrt( TMath::Power(0.00982,2) + TMath::Power(1.61/et,2) ) ;
  }
    
  else if (0.174 <= abseta  and  abseta < 0.261){
    resEt   = et * (TMath::Sqrt( TMath::Power(0.0574,2) + TMath::Power(1/TMath::Sqrt(et),2) + TMath::Power(1.49e-05/et,2) ) ) ;
    resEta  = TMath::Sqrt( TMath::Power(0.00865,2) + TMath::Power(1.54/et,2)) ;
    resPhi  = TMath::Sqrt( TMath::Power(0.0101,2) + TMath::Power(1.59/et,2)) ;
  }
    
  else if (0.261 <= abseta  and  abseta < 0.348){
    resEt   = et * (TMath::Sqrt( TMath::Power(0.0569,2) + TMath::Power(1.01/TMath::Sqrt(et),2) + TMath::Power(1.22e-07/et,2) ) ) ;
    resEta  = TMath::Sqrt( TMath::Power(0.00867,2) + TMath::Power(1.55/et,2) ) ;
    resPhi  = TMath::Sqrt( TMath::Power(0.00988,2) + TMath::Power(1.6/et,2) ) ;
  }
    
  else if (0.348 <= abseta  and  abseta < 0.435){
    resEt   = et * (TMath::Sqrt( TMath::Power(0.057,2) + TMath::Power(1/TMath::Sqrt(et),2) + TMath::Power(2.17e-08/et,2) ) ) ;
    resEta  = TMath::Sqrt( TMath::Power(0.00907,2) + TMath::Power(1.55/et,2) ) ;
    resPhi  = TMath::Sqrt( TMath::Power(0.0102,2) + TMath::Power(1.59/et,2) ) ;
  }
    
  else if (0.435 <= abseta  and  abseta < 0.522){
    resEt   = et * (TMath::Sqrt( TMath::Power(0.0522,2) + TMath::Power(1.02/TMath::Sqrt(et),2) + TMath::Power(2.64e-05/et,2) ) ) ;
    resEta  = TMath::Sqrt( TMath::Power(0.00844,2) + TMath::Power(1.59/et,2) ) ;
    resPhi  = TMath::Sqrt( TMath::Power(0.00982,2) + TMath::Power(1.6/et,2) ) ;
  }
    
  else if (0.522 <= abseta  and  abseta < 0.609){
    resEt   = et * (TMath::Sqrt( TMath::Power(0.0502,2) + TMath::Power(1.02/TMath::Sqrt(et),2) + TMath::Power(2.6e-06/et,2) ) ) ;
    resEta  = TMath::Sqrt( TMath::Power(0.00915,2) + TMath::Power(1.57/et,2) ) ;
    resPhi  = TMath::Sqrt( TMath::Power(0.00979,2) + TMath::Power(1.6/et,2) ) ;
  }
    
  else if (0.609 <= abseta  and  abseta < 0.696){
    resEt   = et * (TMath::Sqrt( TMath::Power(0.053,2) + TMath::Power(1.03/TMath::Sqrt(et),2) + TMath::Power(4.87e-07/et,2) ) ) ;
    resEta  = TMath::Sqrt( TMath::Power(0.00856,2) + TMath::Power(1.58/et,2) ) ;
    resPhi  = TMath::Sqrt( TMath::Power(0.00925,2) + TMath::Power(1.62/et,2) ) ;
  }
    
  else if (0.696 <= abseta  and  abseta < 0.783){
    resEt   = et * (TMath::Sqrt( TMath::Power(0.051,2) + TMath::Power(1.03/TMath::Sqrt(et),2) + TMath::Power(7.53e-06/et,2) ) ) ;
    resEta  = TMath::Sqrt( TMath::Power(0.00897,2) + TMath::Power(1.58/et,2) ) ;
    resPhi  = TMath::Sqrt( TMath::Power(0.00973,2) + TMath::Power(1.61/et,2) ) ;
  }
    
  else if (0.783 <= abseta  and  abseta < 0.870){
    resEt   = et * (TMath::Sqrt( TMath::Power(0.0549,2) + TMath::Power(1.04/TMath::Sqrt(et),2) + TMath::Power(5.62e-08/et,2) ) ) ;
    resEta  = TMath::Sqrt( TMath::Power(0.0095,2) + TMath::Power(1.6/et,2) ) ;
    resPhi  = TMath::Sqrt( TMath::Power(0.00971,2) + TMath::Power(1.62/et,2) ) ;
  }
    
  else if (0.870 <= abseta  and  abseta < 0.957){
    resEt   = et * (TMath::Sqrt( TMath::Power(0.0544,2) + TMath::Power(1.06/TMath::Sqrt(et),2) + TMath::Power(1.07e-05/et,2) ) ) ;
    resEta  = TMath::Sqrt( TMath::Power(0.00836,2) + TMath::Power(1.65/et,2) ) ;
    resPhi  = TMath::Sqrt( TMath::Power(0.00916,2) + TMath::Power(1.64/et,2) ) ;
  }
    
  else if (0.957 <= abseta  and  abseta < 1.044){
    resEt   = et * (TMath::Sqrt( TMath::Power(0.0519,2) + TMath::Power(1.09/TMath::Sqrt(et),2) + TMath::Power(8.43e-06/et,2) ) ) ;
    resEta  = TMath::Sqrt( TMath::Power(0.00782,2) + TMath::Power(1.68/et,2) ) ;
    resPhi  = TMath::Sqrt( TMath::Power(0.00959,2) + TMath::Power(1.66/et,2) ) ;
  }
    
  else if (1.044 <= abseta  and  abseta < 1.131){
    resEt   = et * (TMath::Sqrt( TMath::Power(0.0539,2) + TMath::Power(1.12/TMath::Sqrt(et),2) + TMath::Power(1.97e-07/et,2) ) ) ;
    resEta  = TMath::Sqrt( TMath::Power(0.0093,2) + TMath::Power(1.65/et,2) ) ;
    resPhi  = TMath::Sqrt( TMath::Power(0.00964,2) + TMath::Power(1.67/et,2) ) ;
  }
    
  else if (1.131 <= abseta  and  abseta < 1.218){
    resEt   = et * (TMath::Sqrt( TMath::Power(0.0492,2) + TMath::Power(1.16/TMath::Sqrt(et),2) + TMath::Power(1.37e-08/et,2) ) ) ;
    resEta  = TMath::Sqrt( TMath::Power(0.00986,2) + TMath::Power(1.69/et,2) ) ;
    resPhi  = TMath::Sqrt( TMath::Power(0.00969,2) + TMath::Power(1.71/et,2) ) ;
  }
    
  else if (1.218 <= abseta  and  abseta < 1.305){
    resEt   = et * (TMath::Sqrt( TMath::Power(0.0489,2) + TMath::Power(1.18/TMath::Sqrt(et),2) + TMath::Power(3.44e-07/et,2) ) ) ;
    resEta  = TMath::Sqrt( TMath::Power(0.0124,2) + TMath::Power(1.72/et,2) ) ;
    resPhi  = TMath::Sqrt( TMath::Power(0.00992,2) + TMath::Power(1.76/et,2) ) ;
  }
    
  else if (1.305 <= abseta  and  abseta < 1.392){
    resEt   = et * (TMath::Sqrt( TMath::Power(0.0414,2) + TMath::Power(1.25/TMath::Sqrt(et),2) + TMath::Power(1.98e-07/et,2) ) ) ;
    resEta  = TMath::Sqrt( TMath::Power(0.0181,2) + TMath::Power(1.63/et,2) ) ;
    resPhi  = TMath::Sqrt( TMath::Power(0.0124,2) + TMath::Power(1.79/et,2) ) ;
  }
    
  else if (1.392 <= abseta  and  abseta < 1.479){
    resEt   = et * (TMath::Sqrt( TMath::Power(0.0373,2) + TMath::Power(1.26/TMath::Sqrt(et),2) + TMath::Power(5.4e-07/et,2) ) ) ;
    resEta  = TMath::Sqrt( TMath::Power(0.0121,2) + TMath::Power(1.69/et,2) ) ;
    resPhi  = TMath::Sqrt( TMath::Power(0.0135,2) + TMath::Power(1.8/et,2) ) ;
  }
    
  else if (1.479 <= abseta  and  abseta < 1.566){
    resEt   = et * (TMath::Sqrt( TMath::Power(0.0125,2) + TMath::Power(1.24/TMath::Sqrt(et),2) + TMath::Power(1e-06/et,2) ) ) ;
    resEta  = TMath::Sqrt( TMath::Power(0.0122,2) + TMath::Power(1.69/et,2) ) ;
    resPhi  = TMath::Sqrt( TMath::Power(0.0107,2) + TMath::Power(1.85/et,2) ) ;
  }
    
  else if (1.566 <= abseta  and  abseta < 1.653){
    resEt   = et * (TMath::Sqrt( TMath::Power(1.37e-07,2) + TMath::Power(1.08/TMath::Sqrt(et),2) + TMath::Power(3.06/et,2) ) ) ;
    resEta  = TMath::Sqrt( TMath::Power(0.00975,2) + TMath::Power(1.69/et,2) ) ;
    resPhi  = TMath::Sqrt( TMath::Power(0.00895,2) + TMath::Power(1.84/et,2) ) ;
  }
    
  else if (1.653 <= abseta  and  abseta < 1.740){
    resEt   = et * (TMath::Sqrt( TMath::Power(2.37e-07,2) + TMath::Power(1.04/TMath::Sqrt(et),2) + TMath::Power(3.01/et,2) ) ) ;
    resEta  = TMath::Sqrt( TMath::Power(0.00881,2) + TMath::Power(1.71/et,2) ) ;
    resPhi  = TMath::Sqrt( TMath::Power(0.00902,2) + TMath::Power(1.81/et,2) ) ;
  }
    
  else if (1.740 <= abseta  and  abseta < 1.830){
    resEt   = et * (TMath::Sqrt( TMath::Power(2.3e-07,2) + TMath::Power(1/TMath::Sqrt(et),2) + TMath::Power(3.1/et,2) ) ) ;
    resEta  = TMath::Sqrt( TMath::Power(0.00938,2) + TMath::Power(1.75/et,2) ) ;
    resPhi  = TMath::Sqrt( TMath::Power(0.00861,2) + TMath::Power(1.79/et,2) ) ;
  }
    
  else if (1.830 <= abseta  and  abseta < 1.930){
    resEt   = et * (TMath::Sqrt( TMath::Power(1.25e-07,2) + TMath::Power(0.965/TMath::Sqrt(et),2) + TMath::Power(3.14/et,2) ) ) ;
    resEta  = TMath::Sqrt( TMath::Power(0.00894,2) + TMath::Power(1.8/et,2)) ;
    resPhi  = TMath::Sqrt( TMath::Power(0.00877,2) + TMath::Power(1.75/et,2)) ;
  }
    
  else if (1.930 <= abseta  and  abseta < 2.043){
    resEt   = et * (TMath::Sqrt( TMath::Power(5.78e-08,2) + TMath::Power(0.924/TMath::Sqrt(et),2) + TMath::Power(3.14/et,2) ) ) ;
    resEta  = TMath::Sqrt( TMath::Power(0.00893,2) + TMath::Power(1.83/et,2) ) ;
    resPhi  = TMath::Sqrt( TMath::Power(0.00791,2) + TMath::Power(1.73/et,2) ) ;
  }
    
  else if (2.043 <= abseta  and  abseta < 2.172){
    resEt   = et * (TMath::Sqrt( TMath::Power(4.25e-08,2) + TMath::Power(0.923/TMath::Sqrt(et),2) + TMath::Power(2.85/et,2) ) ) ;
    resEta  = TMath::Sqrt( TMath::Power(0.0099,2) + TMath::Power(1.82/et,2) ) ;
    resPhi  = TMath::Sqrt( TMath::Power(0.00775,2) + TMath::Power(1.73/et,2) ) ;
  }
    
  else if (2.172 <= abseta  and  abseta < 2.322){
    resEt   = et * (TMath::Sqrt( TMath::Power(0.00601,2) + TMath::Power(0.881/TMath::Sqrt(et),2) + TMath::Power(3.23/et,2) ) ) ;
    resEta  = TMath::Sqrt( TMath::Power(0.00944,2) + TMath::Power(1.8/et,2) ) ;
    resPhi  = TMath::Sqrt( TMath::Power(0.00807,2) + TMath::Power(1.71/et,2) ) ;
  }
    
  else if (2.322 <= abseta  and  abseta < 2.500){
    resEt   = et * (TMath::Sqrt( TMath::Power(4.94e-08,2) + TMath::Power(0.86/TMath::Sqrt(et),2) + TMath::Power(3.56/et,2) ) ) ;
    resEta  = TMath::Sqrt( TMath::Power(0.0103,2) + TMath::Power(2.15/et,2) ) ;
    resPhi  = TMath::Sqrt( TMath::Power(0.0103,2) + TMath::Power(1.81/et,2) ) ;
  }

  return true;
}

int bjetResolution(double et, double eta, double& resEt, double& resEta, double& resPhi)
{

  double abseta = fabs(eta) ;


  if (0.000 <= abseta and abseta < 0.087) {
    resEt   = et * ( TMath::Sqrt( TMath::Power(0.0686,2) + TMath::Power(1.03/TMath::Sqrt(et),2) + TMath::Power(1.68/et,2) ) )  ;
    resEta  =  TMath::Sqrt( TMath::Power(0.00605,2) + TMath::Power(1.63/et,2) )  ;
    resPhi  =  TMath::Sqrt( TMath::Power(0.00787,2) + TMath::Power(1.74/et,2) )  ;
  }

  else if (0.087 <= abseta and abseta < 0.174) {
    resEt   = et * ( TMath::Sqrt( TMath::Power(0.0737,2) + TMath::Power(1.01/TMath::Sqrt(et),2) + TMath::Power(1.74/et,2) ) )  ;
    resEta  =  TMath::Sqrt( TMath::Power(0.00592,2) + TMath::Power(1.64/et,2) )  ;
    resPhi  =  TMath::Sqrt( TMath::Power(0.00766,2) + TMath::Power(1.74/et,2) )  ;
  }

  else if (0.174 <= abseta and abseta < 0.261) {
    resEt   = et * ( TMath::Sqrt( TMath::Power(0.0657,2) + TMath::Power(1.07/TMath::Sqrt(et),2) + TMath::Power(5.16e-06/et,2) ) )  ;
    resEta  =  TMath::Sqrt( TMath::Power(0.00584,2) + TMath::Power(1.65/et,2) )  ;
    resPhi  =  TMath::Sqrt( TMath::Power(0.00755,2) + TMath::Power(1.74/et,2) )  ;
  }

  else if (0.261 <= abseta and abseta < 0.348) {
    resEt   = et * ( TMath::Sqrt( TMath::Power(0.062,2) + TMath::Power(1.07/TMath::Sqrt(et),2) +  TMath::Power(0.000134/et,2) ) )  ;
    resEta  =  TMath::Sqrt( TMath::Power(0.00593,2) + TMath::Power(1.65/et,2) )  ;
    resPhi  =  TMath::Sqrt( TMath::Power(0.00734,2) + TMath::Power(1.74/et,2) )  ;
  }

  else if (0.348 <= abseta and abseta < 0.435) {
    resEt   = et * ( TMath::Sqrt( TMath::Power(0.0605,2) + TMath::Power(1.07/TMath::Sqrt(et),2) + TMath::Power(1.84e-07/et,2) ) )  ;
    resEta  =  TMath::Sqrt( TMath::Power(0.00584,2) + TMath::Power(1.68/et,2) )  ;
    resPhi  =  TMath::Sqrt( TMath::Power(0.00734,2) + TMath::Power(1.75/et,2) )  ;
  }

  else if (0.435 <= abseta and abseta < 0.522) {
    resEt   = et * ( TMath::Sqrt( TMath::Power(0.059,2) + TMath::Power(1.08/TMath::Sqrt(et),2) + TMath::Power(9.06e-09/et,2) ) )  ;
    resEta  =  TMath::Sqrt( TMath::Power(0.00646,2) + TMath::Power(1.67/et,2) )  ;
    resPhi  =  TMath::Sqrt( TMath::Power(0.00767,2) + TMath::Power(1.74/et,2) )  ;
  }

  else if (0.522 <= abseta and abseta < 0.609) {
    resEt   = et * ( TMath::Sqrt( TMath::Power(0.0577,2) + TMath::Power(1.08/TMath::Sqrt(et),2) + TMath::Power(5.46e-06/et,2) ) )  ;
    resEta  =  TMath::Sqrt( TMath::Power(0.00661,2) + TMath::Power(1.67/et,2) )  ;
    resPhi  =  TMath::Sqrt( TMath::Power(0.00742,2) + TMath::Power(1.75/et,2) )  ;
  }

  else if (0.609 <= abseta and abseta < 0.696) {
    resEt   = et * ( TMath::Sqrt( TMath::Power(0.0525,2) + TMath::Power(1.09/TMath::Sqrt(et),2) + TMath::Power(4.05e-05/et,2) ) )  ;
    resEta  =  TMath::Sqrt( TMath::Power(0.00724,2) + TMath::Power(1.65/et,2) )  ;
    resPhi  =  TMath::Sqrt( TMath::Power(0.00771,2) + TMath::Power(1.73/et,2) )  ;
  }

  else if (0.696 <= abseta and abseta < 0.783) {
    resEt   = et * ( TMath::Sqrt( TMath::Power(0.0582,2) + TMath::Power(1.09/TMath::Sqrt(et),2) + TMath::Power(1.17e-05/et,2) ) )  ;
    resEta  =  TMath::Sqrt( TMath::Power(0.00763,2) + TMath::Power(1.67/et,2) )  ;
    resPhi  =  TMath::Sqrt( TMath::Power(0.00758,2) + TMath::Power(1.76/et,2) )  ;
  }

  else if (0.783 <= abseta and abseta < 0.870) {
    resEt   = et * ( TMath::Sqrt( TMath::Power(0.0649,2) + TMath::Power(1.08/TMath::Sqrt(et),2) + TMath::Power(7.85e-06/et,2) ) )  ;
    resEta  =  TMath::Sqrt( TMath::Power(0.00746,2) + TMath::Power(1.7/et,2) )  ;
    resPhi  =  TMath::Sqrt( TMath::Power(0.00789,2) + TMath::Power(1.75/et,2) )  ;
  }

  else if (0.870 <= abseta and abseta < 0.957) {
    resEt   = et * ( TMath::Sqrt( TMath::Power(0.0654,2) + TMath::Power(1.1/TMath::Sqrt(et),2) + TMath::Power(1.09e-07/et,2) ) )  ;
    resEta  =  TMath::Sqrt( TMath::Power(0.00807,2) + TMath::Power(1.7/et,2) )  ;
    resPhi  =  TMath::Sqrt( TMath::Power(0.00802,2) + TMath::Power(1.76/et,2) )  ;
  }

  else if (0.957 <= abseta and abseta < 1.044) {
    resEt   = et * ( TMath::Sqrt( TMath::Power(0.0669,2) + TMath::Power(1.11/TMath::Sqrt(et),2) + TMath::Power(1.87e-06/et,2) ) )  ;
    resEta  =  TMath::Sqrt( TMath::Power(0.00843,2) + TMath::Power(1.72/et,2) )  ;
    resPhi  =  TMath::Sqrt( TMath::Power(0.0078,2) + TMath::Power(1.79/et,2) )  ;
  }

  else if (1.044 <= abseta and abseta < 1.131) {
    resEt   = et * ( TMath::Sqrt( TMath::Power(0.0643,2) + TMath::Power(1.15/TMath::Sqrt(et),2) + TMath::Power(2.76e-05/et,2) ) )  ;
    resEta  =  TMath::Sqrt( TMath::Power(0.00886,2) + TMath::Power(1.74/et,2) )  ;
    resPhi  =  TMath::Sqrt( TMath::Power(0.00806,2) + TMath::Power(1.82/et,2) )  ;
  }

  else if (1.131 <= abseta and abseta < 1.218) {
    resEt   = et * ( TMath::Sqrt( TMath::Power(0.0645,2) + TMath::Power(1.16/TMath::Sqrt(et),2) + TMath::Power(1.04e-06/et,2) ) )  ;
    resEta  =  TMath::Sqrt( TMath::Power(0.0101,2) + TMath::Power(1.76/et,2) )  ;
    resPhi  =  TMath::Sqrt( TMath::Power(0.00784,2) + TMath::Power(1.86/et,2) )  ;
  }

  else if (1.218 <= abseta and abseta < 1.305) {
    resEt   = et * ( TMath::Sqrt( TMath::Power(0.0637,2) + TMath::Power(1.19/TMath::Sqrt(et),2) + TMath::Power(1.08e-07/et,2) ) )  ;
    resEta  =  TMath::Sqrt( TMath::Power(0.0127,2) + TMath::Power(1.78/et,2) )  ;
    resPhi  =  TMath::Sqrt( TMath::Power(0.00885,2) + TMath::Power(1.9/et,2) )  ;
  }

  else if (1.305 <= abseta and abseta < 1.392) {
    resEt   = et * ( TMath::Sqrt( TMath::Power(0.0695,2) + TMath::Power(1.21/TMath::Sqrt(et),2) + TMath::Power(5.75e-06/et,2) ) )  ;
    resEta  =  TMath::Sqrt( TMath::Power(0.0161,2) + TMath::Power(1.73/et,2) )  ;
    resPhi  =  TMath::Sqrt( TMath::Power(0.0108,2) + TMath::Power(1.93/et,2) )  ;
  }

  else if (1.392 <= abseta and abseta < 1.479) {
    resEt   = et * ( TMath::Sqrt( TMath::Power(0.0748,2) + TMath::Power(1.2/TMath::Sqrt(et),2) + TMath::Power(5.15e-08/et,2) ) )  ;
    resEta  =  TMath::Sqrt( TMath::Power(0.0122,2) + TMath::Power(1.77/et,2) )  ;
    resPhi  =  TMath::Sqrt( TMath::Power(0.0112,2) + TMath::Power(2/et,2) )  ;
  }

  else if (1.479 <= abseta and abseta < 1.566) {
    resEt   = et * ( TMath::Sqrt( TMath::Power(0.0624,2) + TMath::Power(1.23/TMath::Sqrt(et),2) + TMath::Power(2.28e-05/et,2) ) )  ;
    resEta  =  TMath::Sqrt( TMath::Power(0.0123,2) + TMath::Power(1.79/et,2) )  ;
    resPhi  =  TMath::Sqrt( TMath::Power(0.0102,2) + TMath::Power(2.02/et,2) )  ;
  }

  else if (1.566 <= abseta and abseta < 1.653) {
    resEt   = et * ( TMath::Sqrt( TMath::Power(0.0283,2) + TMath::Power(1.25/TMath::Sqrt(et),2) + TMath::Power(4.79e-07/et,2) ) )  ;
    resEta  =  TMath::Sqrt( TMath::Power(0.0111,2) + TMath::Power(1.79/et,2) )  ;
    resPhi  =  TMath::Sqrt( TMath::Power(0.00857,2) + TMath::Power(2.01/et,2) )  ;
  }

  else if (1.653 <= abseta and abseta < 1.740) {
    resEt   = et * ( TMath::Sqrt( TMath::Power(0.0316,2) + TMath::Power(1.21/TMath::Sqrt(et),2) + TMath::Power(5e-05/et,2) ) )  ;
    resEta  =  TMath::Sqrt( TMath::Power(0.0106,2) + TMath::Power(1.8/et,2) )  ;
    resPhi  =  TMath::Sqrt( TMath::Power(0.00856,2) + TMath::Power(1.97/et,2) )  ;
  }

  else if (1.740 <= abseta and abseta < 1.830) {
    resEt   = et * ( TMath::Sqrt( TMath::Power(2.29e-07,2) + TMath::Power(1.2/TMath::Sqrt(et),2) + TMath::Power(1.71e-05/et,2) ) )  ;
    resEta  =  TMath::Sqrt( TMath::Power(0.0115,2) + TMath::Power(1.83/et,2) )  ;
    resPhi  =  TMath::Sqrt( TMath::Power(0.00761,2) + TMath::Power(1.95/et,2) )  ;
  }

  else if (1.830 <= abseta and abseta < 1.930) {
    resEt   = et * ( TMath::Sqrt( TMath::Power(5.18e-09,2) + TMath::Power(1.14/TMath::Sqrt(et),2) + TMath::Power(1.7/et,2) ) )  ;
    resEta  =  TMath::Sqrt( TMath::Power(0.012,2) + TMath::Power(1.88/et,2) )  ;
    resPhi  =  TMath::Sqrt( TMath::Power(0.00721,2) + TMath::Power(1.92/et,2) )  ;
  }

  else if (1.930 <= abseta and abseta < 2.043) {
    resEt   = et * ( TMath::Sqrt( TMath::Power(2.17e-07,2) + TMath::Power(1.09/TMath::Sqrt(et),2) + TMath::Power(2.08/et,2) ) )  ;
    resEta  =  TMath::Sqrt( TMath::Power(0.0131,2) + TMath::Power(1.91/et,2) )  ;
    resPhi  =  TMath::Sqrt( TMath::Power(0.00722,2) + TMath::Power(1.86/et,2) )  ;
  }

  else if (2.043 <= abseta and abseta < 2.172) {
    resEt   = et * ( TMath::Sqrt( TMath::Power(3.65e-07,2) + TMath::Power(1.09/TMath::Sqrt(et),2) + TMath::Power(1.63/et,2) ) )  ;
    resEta  =  TMath::Sqrt( TMath::Power(0.0134,2) + TMath::Power(1.92/et,2) )  ;
    resPhi  =  TMath::Sqrt( TMath::Power(0.00703,2) + TMath::Power(1.86/et,2) )  ;
  }

  else if (2.172 <= abseta and abseta < 2.322) {
    resEt   = et * ( TMath::Sqrt( TMath::Power(2.02e-07,2) + TMath::Power(1.09/TMath::Sqrt(et),2) + TMath::Power(1.68/et,2) ) )  ;
    resEta  =  TMath::Sqrt( TMath::Power(0.0132,2) + TMath::Power(1.89/et,2) )  ;
    resPhi  =  TMath::Sqrt( TMath::Power(0.00845,2) + TMath::Power(1.86/et,2) )  ;
  }

  else if (2.322 <= abseta and abseta < 2.500) {
    resEt   = et * ( TMath::Sqrt( TMath::Power(5.27e-07,2) + TMath::Power(1.12/TMath::Sqrt(et),2) + TMath::Power(1.78/et,2) ) )  ;
    resEta  =  TMath::Sqrt( TMath::Power(0.0121,2) + TMath::Power(2.28/et,2) )  ;
    resPhi  =  TMath::Sqrt( TMath::Power(0.00975,2) + TMath::Power(2/et,2) )  ;        
  }

  return true;
}

int muonResolution(double et, double eta, double& resEt, double& resEta, double& resPhi)
{

  double abseta = fabs(eta) ;
  

  if ( 0.000 <= abseta and abseta < 0.100 ) {
    resEt   = et * (0.00517 + 0.000143 * et) ;
    resEta  = TMath::Sqrt( TMath::Power(0.000433,2) + TMath::Power(0.000161/TMath::Sqrt(et),2) + TMath::Power(0.00334/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(7.21e-05,2) + TMath::Power(7e-05/TMath::Sqrt(et),2) + TMath::Power(0.00296/et,2) ) ; 
  }

  else if ( 0.100 <= abseta and abseta < 0.200 ) {
    resEt   = et * (0.00524 + 0.000143 * et); 
    resEta  = TMath::Sqrt( TMath::Power(0.000381,2) + TMath::Power(0.000473/TMath::Sqrt(et),2) + TMath::Power(0.00259/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(6.79e-05,2) + TMath::Power(0.000245/TMath::Sqrt(et),2) + TMath::Power(0.00274/et,2) ) ; 
  }

  else if ( 0.200 <= abseta and abseta < 0.300 ) {
    resEt   = et * (0.00585 + 0.000138 * et); 
    resEta  = TMath::Sqrt( TMath::Power(0.000337,2) + TMath::Power(0.000381/TMath::Sqrt(et),2) + TMath::Power(0.0023/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(7.08e-05,2) + TMath::Power(6.75e-05/TMath::Sqrt(et),2) + TMath::Power(0.00307/et,2) ) ; 
  }

  else if ( 0.300 <= abseta and abseta < 0.400 ) {
    resEt   = et * (0.0065 + 0.000133 * et); 
    resEta  = TMath::Sqrt( TMath::Power(0.000308,2) + TMath::Power(0.000166/TMath::Sqrt(et),2) + TMath::Power(0.00249/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(6.59e-05,2) + TMath::Power(0.000301/TMath::Sqrt(et),2) + TMath::Power(0.00281/et,2) ) ; 
  }

  else if ( 0.400 <= abseta and abseta < 0.500 ) {
    resEt   = et * (0.0071 + 0.000129 * et); 
    resEta  = TMath::Sqrt( TMath::Power(0.000289,2) + TMath::Power(5.37e-09/TMath::Sqrt(et),2) + TMath::Power(0.00243/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(6.27e-05,2) + TMath::Power(0.000359/TMath::Sqrt(et),2) + TMath::Power(0.00278/et,2) ) ; 
  }

  else if ( 0.500 <= abseta and abseta < 0.600 ) {
    resEt   = et * (0.00721 + 0.00013 * et); 
    resEta  = TMath::Sqrt( TMath::Power(0.000279,2) + TMath::Power(0.000272/TMath::Sqrt(et),2) + TMath::Power(0.0026/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(6.46e-05,2) + TMath::Power(0.00036/TMath::Sqrt(et),2) + TMath::Power(0.00285/et,2) ) ; 
  }

  else if ( 0.600 <= abseta and abseta < 0.700 ) {
    resEt   = et * (0.00757 + 0.000129 * et); 
    resEta  = TMath::Sqrt( TMath::Power(0.000282,2) + TMath::Power(3.63e-10/TMath::Sqrt(et),2) + TMath::Power(0.00288/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(6.54e-05,2) + TMath::Power(0.000348/TMath::Sqrt(et),2) + TMath::Power(0.00301/et,2) ) ; 
  }

  else if ( 0.700 <= abseta and abseta < 0.800 ) {
    resEt   = et * (0.0081 + 0.000127 * et); 
    resEta  = TMath::Sqrt( TMath::Power(0.000265,2) + TMath::Power(0.000609/TMath::Sqrt(et),2) + TMath::Power(0.00212/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(6.2e-05,2) + TMath::Power(0.000402/TMath::Sqrt(et),2) + TMath::Power(0.00304/et,2) ) ; 
  }

  else if ( 0.800 <= abseta and abseta < 0.900 ) {
    resEt   = et * (0.00916 + 0.000131 * et); 
    resEta  = TMath::Sqrt( TMath::Power(0.000241,2) + TMath::Power(0.000678/TMath::Sqrt(et),2) + TMath::Power(0.00221/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(6.26e-05,2) + TMath::Power(0.000458/TMath::Sqrt(et),2) + TMath::Power(0.0031/et,2) ) ; 
  }

  else if ( 0.900 <= abseta and abseta < 1.000 ) {
    resEt   = et * (0.0108 + 0.000151 * et); 
    resEta  = TMath::Sqrt( TMath::Power(0.000228,2) + TMath::Power(0.000612/TMath::Sqrt(et),2) + TMath::Power(0.00245/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(7.18e-05,2) + TMath::Power(0.000469/TMath::Sqrt(et),2) + TMath::Power(0.00331/et,2) ) ; 
  }

  else if ( 1.000 <= abseta and abseta < 1.100 ) {
    resEt   = et * (0.0115 + 0.000153 * et); 
    resEta  = TMath::Sqrt( TMath::Power(0.000217,2) + TMath::Power(0.000583/TMath::Sqrt(et),2) + TMath::Power(0.00307/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(6.98e-05,2) + TMath::Power(0.000507/TMath::Sqrt(et),2) + TMath::Power(0.00338/et,2) ) ; 
  }

  else if ( 1.100 <= abseta and abseta < 1.200 ) {
    resEt   = et * (0.013 + 0.000136 * et); 
    resEta  = TMath::Sqrt( TMath::Power(0.000195,2) + TMath::Power(0.000751/TMath::Sqrt(et),2) + TMath::Power(0.00282/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(6.21e-05,2) + TMath::Power(0.000584/TMath::Sqrt(et),2) + TMath::Power(0.00345/et,2) ) ; 
  }

  else if ( 1.200 <= abseta and abseta < 1.300 ) {
    resEt   = et * (0.0144 + 0.000131 * et); 
    resEta  = TMath::Sqrt( TMath::Power(0.000183,2) + TMath::Power(0.000838/TMath::Sqrt(et),2) + TMath::Power(0.00227/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(5.37e-05,2) + TMath::Power(0.000667/TMath::Sqrt(et),2) + TMath::Power(0.00352/et,2) ) ; 
  }

  else if ( 1.300 <= abseta and abseta < 1.400 ) {
    resEt   = et * (0.0149 + 0.000141 * et); 
    resEta  = TMath::Sqrt( TMath::Power(0.000196,2) + TMath::Power(0.000783/TMath::Sqrt(et),2) + TMath::Power(0.00274/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(5.37e-05,2) + TMath::Power(0.000711/TMath::Sqrt(et),2) + TMath::Power(0.00358/et,2) ) ; 
  }

  else if ( 1.400 <= abseta and abseta < 1.500 ) {
    resEt   = et * (0.014 + 0.000155 * et); 
    resEta  = TMath::Sqrt( TMath::Power(0.0002,2) + TMath::Power(0.000832/TMath::Sqrt(et),2) + TMath::Power(0.00254/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(5.98e-05,2) + TMath::Power(0.000713/TMath::Sqrt(et),2) + TMath::Power(0.00362/et,2) ) ; 
  }

  else if ( 1.500 <= abseta and abseta < 1.600 ) {
    resEt   = et * (0.0132 + 0.000169 * et); 
    resEta  = TMath::Sqrt( TMath::Power(0.000205,2) + TMath::Power(0.0007/TMath::Sqrt(et),2) + TMath::Power(0.00304/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(6.21e-05,2) + TMath::Power(0.000781/TMath::Sqrt(et),2) + TMath::Power(0.00348/et,2) ) ; 
  }

  else if ( 1.600 <= abseta and abseta < 1.700 ) {
    resEt   = et * (0.0129 + 0.0002 * et); 
    resEta  = TMath::Sqrt( TMath::Power(0.000214,2) + TMath::Power(0.000747/TMath::Sqrt(et),2) + TMath::Power(0.00319/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(6.92e-05,2) + TMath::Power(0.000865/TMath::Sqrt(et),2) + TMath::Power(0.00337/et,2) ) ; 
  }

  else if ( 1.700 <= abseta and abseta < 1.800 ) {
    resEt   = et * (0.0135 + 0.000264 * et); 
    resEta  = TMath::Sqrt( TMath::Power(0.000238,2) + TMath::Power(0.000582/TMath::Sqrt(et),2) + TMath::Power(0.00343/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(9.13e-05,2) + TMath::Power(0.000896/TMath::Sqrt(et),2) + TMath::Power(0.00348/et,2) ) ; 
  }

  else if ( 1.800 <= abseta and abseta < 1.900 ) {
    resEt   = et * (0.0144 + 0.00034 * et); 
    resEta  = TMath::Sqrt( TMath::Power(0.000263,2) + TMath::Power(0.000721/TMath::Sqrt(et),2) + TMath::Power(0.00322/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(0.000102,2) + TMath::Power(0.000994/TMath::Sqrt(et),2) + TMath::Power(0.00337/et,2) ) ; 
  }

  else if ( 1.900 <= abseta and abseta < 2.000 ) {
    resEt   = et * (0.0147 + 0.000441 * et); 
    resEta  = TMath::Sqrt( TMath::Power(0.000284,2) + TMath::Power(0.000779/TMath::Sqrt(et),2) + TMath::Power(0.0031/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(0.000123,2) + TMath::Power(0.00108/TMath::Sqrt(et),2) + TMath::Power(0.00315/et,2) ) ; 
  }

  else if ( 2.000 <= abseta and abseta < 2.100 ) {
    resEt   = et * (0.0154 + 0.000604 * et); 
    resEta  = TMath::Sqrt( TMath::Power(0.000316,2) + TMath::Power(0.000566/TMath::Sqrt(et),2) + TMath::Power(0.00384/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(0.000169,2) + TMath::Power(0.000947/TMath::Sqrt(et),2) + TMath::Power(0.00422/et,2) ) ; 
  }

  else if ( 2.100 <= abseta and abseta < 2.200 ) {
    resEt   = et * (0.0163 + 0.000764 * et); 
    resEta  = TMath::Sqrt( TMath::Power(0.000353,2) + TMath::Power(0.000749/TMath::Sqrt(et),2) + TMath::Power(0.0038/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(0.000176,2) + TMath::Power(0.00116/TMath::Sqrt(et),2) + TMath::Power(0.00423/et,2) ) ; 
  }

  else if ( 2.200 <= abseta and abseta < 2.300 ) {
    resEt   = et * (0.0173 + 0.000951 * et); 
    resEta  = TMath::Sqrt( TMath::Power(0.000412,2) + TMath::Power(0.00102/TMath::Sqrt(et),2) + TMath::Power(0.00351/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(0.000207,2) + TMath::Power(0.00115/TMath::Sqrt(et),2) + TMath::Power(0.00469/et,2) ) ; 
  }

  else if ( 2.300 <= abseta and abseta < 2.400 ) {
    resEt   = et * (0.0175 + 0.00126 * et); 
    resEta  = TMath::Sqrt( TMath::Power(0.000506,2) + TMath::Power(0.000791/TMath::Sqrt(et),2) + TMath::Power(0.0045/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(0.00027,2) + TMath::Power(0.00113/TMath::Sqrt(et),2) + TMath::Power(0.00528/et,2) ) ; 
  }

  return true;
}

int elecResolution(double et, double eta, double& resEt, double& resEta, double& resPhi)
{

  double abseta = fabs(eta) ;


  if ( 0.000 <= abseta and abseta < 0.174 ) {
    resEt   = et * TMath::Sqrt( TMath::Power(0.00534,2) + TMath::Power(0.079/TMath::Sqrt(et),2) + TMath::Power(0.163/et,2) ) ; 
    resEta  = TMath::Sqrt( TMath::Power(0.000452,2) + TMath::Power(0.000285/TMath::Sqrt(et),2) + TMath::Power(0.00376/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(0.000101,2) + TMath::Power(0.0011/TMath::Sqrt(et),2) + TMath::Power(0.00346/et,2) ) ; 
  }

  else if ( 0.174 <= abseta and abseta < 0.261 ) {
    resEt   = et * TMath::Sqrt( TMath::Power(0.00518,2) + TMath::Power(0.0749/TMath::Sqrt(et),2) + TMath::Power(0.227/et,2) ) ; 
    resEta  = TMath::Sqrt( TMath::Power(0.00038,2) + TMath::Power(0.000571/TMath::Sqrt(et),2) + TMath::Power(0.00276/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(9.3e-05,2) + TMath::Power(0.00115/TMath::Sqrt(et),2) + TMath::Power(0.0035/et,2) ) ; 
  }

  else if ( 0.261 <= abseta and abseta < 0.348 ) {
    resEt   = et * TMath::Sqrt( TMath::Power(0.00332,2) + TMath::Power(0.0879/TMath::Sqrt(et),2) + TMath::Power(0.12/et,2) ) ; 
    resEta  = TMath::Sqrt( TMath::Power(0.000351,2) + TMath::Power(1.36e-09/TMath::Sqrt(et),2) + TMath::Power(0.00324/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(0.000103,2) + TMath::Power(0.00117/TMath::Sqrt(et),2) + TMath::Power(0.00333/et,2) ) ; 
  }

  else if ( 0.348 <= abseta and abseta < 0.435 ) {
    resEt   = et * TMath::Sqrt( TMath::Power(0.00445,2) + TMath::Power(0.0895/TMath::Sqrt(et),2) + TMath::Power(0.186/et,2) ) ; 
    resEta  = TMath::Sqrt( TMath::Power(0.000319,2) + TMath::Power(0.00061/TMath::Sqrt(et),2) + TMath::Power(0.00182/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(0.00011,2) + TMath::Power(0.00115/TMath::Sqrt(et),2) + TMath::Power(0.00365/et,2) ) ; 
  }

  else if ( 0.435 <= abseta and abseta < 0.522 ) {
    resEt   = et * TMath::Sqrt( TMath::Power(0.00453,2) + TMath::Power(0.0893/TMath::Sqrt(et),2) + TMath::Power(0.21/et,2) ) ; 
    resEta  = TMath::Sqrt( TMath::Power(0.000301,2) + TMath::Power(0.000612/TMath::Sqrt(et),2) + TMath::Power(0.00146/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(0.000105,2) + TMath::Power(0.00122/TMath::Sqrt(et),2) + TMath::Power(0.00343/et,2) ) ; 
  }

  else if ( 0.522 <= abseta and abseta < 0.609 ) {
    resEt   = et * TMath::Sqrt( TMath::Power(0.00308,2) + TMath::Power(0.0886/TMath::Sqrt(et),2) + TMath::Power(0.188/et,2) ) ; 
    resEta  = TMath::Sqrt( TMath::Power(0.000297,2) + TMath::Power(0.000791/TMath::Sqrt(et),2) + TMath::Power(2.09e-08/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(0.000102,2) + TMath::Power(0.00129/TMath::Sqrt(et),2) + TMath::Power(0.00328/et,2) ) ; 
  }

  else if ( 0.609 <= abseta and abseta < 0.696 ) {
    resEt   = et * TMath::Sqrt( TMath::Power(0.00308,2) + TMath::Power(0.0914/TMath::Sqrt(et),2) + TMath::Power(0.182/et,2) ) ; 
    resEta  = TMath::Sqrt( TMath::Power(0.00032,2) + TMath::Power(0.000329/TMath::Sqrt(et),2) + TMath::Power(0.00325/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(0.000103,2) + TMath::Power(0.00139/TMath::Sqrt(et),2) + TMath::Power(0.00253/et,2) ) ; 
  }

  else if ( 0.696 <= abseta and abseta < 0.783 ) {
    resEt   = et * TMath::Sqrt( TMath::Power(0.00442,2) + TMath::Power(0.0914/TMath::Sqrt(et),2) + TMath::Power(0.231/et,2) ) ; 
    resEta  = TMath::Sqrt( TMath::Power(0.000309,2) + TMath::Power(0.000821/TMath::Sqrt(et),2) + TMath::Power(0.00119/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(0.000115,2) + TMath::Power(0.00139/TMath::Sqrt(et),2) + TMath::Power(0.00293/et,2) ) ; 
  }

  else if ( 0.783 <= abseta and abseta < 0.870 ) {
    resEt   = et * TMath::Sqrt( TMath::Power(0.00455,2) + TMath::Power(0.0949/TMath::Sqrt(et),2) + TMath::Power(0.335/et,2) ) ; 
    resEta  = TMath::Sqrt( TMath::Power(0.000293,2) + TMath::Power(0.000767/TMath::Sqrt(et),2) + TMath::Power(0.00211/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(0.000121,2) + TMath::Power(0.00158/TMath::Sqrt(et),2) + TMath::Power(0.00151/et,2) ) ; 
  }

  else if ( 0.870 <= abseta and abseta < 0.957 ) {
    resEt   = et * TMath::Sqrt( TMath::Power(0.00181,2) + TMath::Power(0.102/TMath::Sqrt(et),2) + TMath::Power(0.333/et,2) ) ; 
    resEta  = TMath::Sqrt( TMath::Power(0.000275,2) + TMath::Power(0.000765/TMath::Sqrt(et),2) + TMath::Power(0.00227/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(0.000128,2) + TMath::Power(0.00169/TMath::Sqrt(et),2) + TMath::Power(1.93e-08/et,2) ) ; 
  }

  else if ( 0.957 <= abseta and abseta < 1.044 ) {
    resEt   = et * TMath::Sqrt( TMath::Power(0.000764,2) + TMath::Power(0.108/TMath::Sqrt(et),2) + TMath::Power(0.42/et,2) ) ; 
    resEta  = TMath::Sqrt( TMath::Power(0.000274,2) + TMath::Power(0.000622/TMath::Sqrt(et),2) + TMath::Power(0.00299/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(0.000145,2) + TMath::Power(0.00179/TMath::Sqrt(et),2) + TMath::Power(1.69e-08/et,2) ) ; 
  }

  else if ( 1.044 <= abseta and abseta < 1.131 ) {
    resEt   = et * TMath::Sqrt( TMath::Power(0.00114,2) + TMath::Power(0.128/TMath::Sqrt(et),2) + TMath::Power(0.55/et,2) ) ; 
    resEta  = TMath::Sqrt( TMath::Power(0.000269,2) + TMath::Power(0.000929/TMath::Sqrt(et),2) + TMath::Power(0.00183/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(0.000185,2) + TMath::Power(0.00182/TMath::Sqrt(et),2) + TMath::Power(2.99e-09/et,2) ) ; 
  }

  else if ( 1.131 <= abseta and abseta < 1.218 ) {
    resEt   = et * TMath::Sqrt( TMath::Power(4.14e-09,2) + TMath::Power(0.155/TMath::Sqrt(et),2) + TMath::Power(0.674/et,2) ) ; 
    resEta  = TMath::Sqrt( TMath::Power(0.000268,2) + TMath::Power(0.000876/TMath::Sqrt(et),2) + TMath::Power(0.00234/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(0.000194,2) + TMath::Power(0.002/TMath::Sqrt(et),2) + TMath::Power(2.39e-08/et,2) ) ; 
  }

  else if ( 1.218 <= abseta and abseta < 1.305 ) {
    resEt   = et * TMath::Sqrt( TMath::Power(8.03e-09,2) + TMath::Power(0.144/TMath::Sqrt(et),2) + TMath::Power(0.8/et,2) ) ; 
    resEta  = TMath::Sqrt( TMath::Power(0.000258,2) + TMath::Power(0.000782/TMath::Sqrt(et),2) + TMath::Power(0.00246/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(0.000226,2) + TMath::Power(0.00206/TMath::Sqrt(et),2) + TMath::Power(5.88e-08/et,2) ) ; 
  }

  else if ( 1.305 <= abseta and abseta < 1.392 ) {
    resEt   = et * TMath::Sqrt( TMath::Power(0.00842,2) + TMath::Power(0.118/TMath::Sqrt(et),2) + TMath::Power(0.951/et,2) ) ; 
    resEta  = TMath::Sqrt( TMath::Power(0.000269,2) + TMath::Power(0.000817/TMath::Sqrt(et),2) + TMath::Power(0.00278/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(0.000247,2) + TMath::Power(0.00225/TMath::Sqrt(et),2) + TMath::Power(1.47e-09/et,2) ) ; 
  }

  else if ( 1.392 <= abseta and abseta < 1.479 ) {
    resEt   = et * TMath::Sqrt( TMath::Power(0.00684,2) + TMath::Power(0.144/TMath::Sqrt(et),2) + TMath::Power(0.892/et,2) ) ; 
    resEta  = TMath::Sqrt( TMath::Power(0.000267,2) + TMath::Power(0.000734/TMath::Sqrt(et),2) + TMath::Power(0.00327/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(0.000234,2) + TMath::Power(0.00233/TMath::Sqrt(et),2) + TMath::Power(4.92e-09/et,2) ) ; 
  }

  else if ( 1.479 <= abseta and abseta < 1.653 ) {
    resEt   = et * TMath::Sqrt( TMath::Power(0.0245,2) + TMath::Power(0.196/TMath::Sqrt(et),2) + TMath::Power(0.555/et,2) ) ; 
    resEta  = TMath::Sqrt( TMath::Power(0.000268,2) + TMath::Power(0.000757/TMath::Sqrt(et),2) + TMath::Power(0.00295/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(0.00025,2) + TMath::Power(0.00268/TMath::Sqrt(et),2) + TMath::Power(7.5e-09/et,2) ) ; 
  }

  else if ( 1.653 <= abseta and abseta < 1.740 ) {
    resEt   = et * TMath::Sqrt( TMath::Power(0.0174,2) + TMath::Power(0.127/TMath::Sqrt(et),2) + TMath::Power(0.894/et,2) ) ; 
    resEta  = TMath::Sqrt( TMath::Power(0.000274,2) + TMath::Power(1.77e-09/TMath::Sqrt(et),2) + TMath::Power(0.00435/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(0.000284,2) + TMath::Power(0.00275/TMath::Sqrt(et),2) + TMath::Power(6.56e-09/et,2) ) ; 
  }

  else if ( 1.740 <= abseta and abseta < 1.830 ) {
    resEt   = et * TMath::Sqrt( TMath::Power(0.0144,2) + TMath::Power(0.133/TMath::Sqrt(et),2) + TMath::Power(0.708/et,2) ) ; 
    resEta  = TMath::Sqrt( TMath::Power(0.000274,2) + TMath::Power(0.00101/TMath::Sqrt(et),2) + TMath::Power(0.000982/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(0.000356,2) + TMath::Power(0.00279/TMath::Sqrt(et),2) + TMath::Power(0.00261/et,2) ) ; 
  }

  else if ( 1.830 <= abseta and abseta < 1.930 ) {
    resEt   = et * TMath::Sqrt( TMath::Power(0.0149,2) + TMath::Power(0.126/TMath::Sqrt(et),2) + TMath::Power(0.596/et,2) ) ; 
    resEta  = TMath::Sqrt( TMath::Power(0.000299,2) + TMath::Power(0.000686/TMath::Sqrt(et),2) + TMath::Power(0.00341/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(0.000347,2) + TMath::Power(0.00298/TMath::Sqrt(et),2) + TMath::Power(1.02e-08/et,2) ) ; 
  }

  else if ( 1.930 <= abseta and abseta < 2.043 ) {
    resEt   = et * TMath::Sqrt( TMath::Power(0.0143,2) + TMath::Power(0.12/TMath::Sqrt(et),2) + TMath::Power(0.504/et,2) ) ; 
    resEta  = TMath::Sqrt( TMath::Power(0.000329,2) + TMath::Power(3.05e-10/TMath::Sqrt(et),2) + TMath::Power(0.00439/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(0.000302,2) + TMath::Power(0.00322/TMath::Sqrt(et),2) + TMath::Power(5.22e-08/et,2) ) ; 
  }

  else if ( 2.043 <= abseta and abseta < 2.172 ) {
    resEt   = et * TMath::Sqrt( TMath::Power(0.0162,2) + TMath::Power(0.0965/TMath::Sqrt(et),2) + TMath::Power(0.483/et,2) ) ; 
    resEta  = TMath::Sqrt( TMath::Power(0.00037,2) + TMath::Power(1.32e-08/TMath::Sqrt(et),2) + TMath::Power(0.00447/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(0.000287,2) + TMath::Power(0.00349/TMath::Sqrt(et),2) + TMath::Power(3e-11/et,2) ) ; 
  }

  else if ( 2.172 <= abseta and abseta < 2.322 ) {
    resEt   = et * TMath::Sqrt( TMath::Power(0.0122,2) + TMath::Power(0.13/TMath::Sqrt(et),2) + TMath::Power(0.207/et,2) ) ; 
    resEta  = TMath::Sqrt( TMath::Power(0.000442,2) + TMath::Power(4.03e-10/TMath::Sqrt(et),2) + TMath::Power(0.00544/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(0.000214,2) + TMath::Power(0.00436/TMath::Sqrt(et),2) + TMath::Power(2.98e-09/et,2) ) ; 
  }

  else if ( 2.322 <= abseta and abseta < 2.500 ) {
    resEt   = et * TMath::Sqrt( TMath::Power(0.0145,2) + TMath::Power(0.127/TMath::Sqrt(et),2) + TMath::Power(0.0782/et,2) ) ; 
    resEta  = TMath::Sqrt( TMath::Power(0.000577,2) + TMath::Power(0.000768/TMath::Sqrt(et),2) + TMath::Power(0.00331/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(8.02e-05,2) + TMath::Power(0.00525/TMath::Sqrt(et),2) + TMath::Power(0.00581/et,2) ) ; 
  }


  return true;
}


int metResolution(double et, double& resEt, double& resEta, double& resPhi)
{
  
  //summer 2011
  /* resEt   = et * TMath::Sqrt( TMath::Power(0.0351,2) + TMath::Power(0/TMath::Sqrt(et),2) + TMath::Power(20.288/et,2) ) ; */
  /* resEta  = TMath::Sqrt( TMath::Power(0,2) + TMath::Power(0/TMath::Sqrt(et),2) + TMath::Power(0/et,2) ) ; */
  /* resPhi  = TMath::Sqrt( TMath::Power(0,2) + TMath::Power(1.1664/TMath::Sqrt(et),2) + TMath::Power(3.579/et,2)) ; */

  //fall 2011
  resEt   = et * TMath::Sqrt( TMath::Power(0.0337,2) + TMath::Power(0.888/TMath::Sqrt(et),2) + TMath::Power(19.6/et,2) ) ;
  resEta  = TMath::Sqrt( TMath::Power(0,2) + TMath::Power(0/TMath::Sqrt(et),2) + TMath::Power(0/et,2) ) ;
  resPhi  = TMath::Sqrt( TMath::Power(1.28e-08,2) + TMath::Power(1.45/TMath::Sqrt(et),2) + TMath::Power(1.03/et,2) );
  
  return true;
}
