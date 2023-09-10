/**********************************************************************
 Created on : 19/01/2022
 Purpose    : Jet resolution study using the MC
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

int JetResolution()
{
  bool GetHistoBin(TH2F *, float, float, int&, int&);
  int GetHistoBin(TH1F *h, float et);
  
  TFile *fin = TFile::Open("/Data/root_files/AOD_files/NanoAODUL/2016/TTbarPowheg_Semilept_postVFP_Skim_NanoAOD_1of27.root");

  TTree *tree = (TTree *)fin->Get("Events");
  
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
  
  // Electron
  UInt_t          nEle_;
  Float_t         elePt_[20];
  Float_t         eleEta_[20];
  Float_t         elePhi_[20];
  Int_t           eleCharge_[20];
  Float_t         eleMass_[20];
  Int_t           eleGenIdx_[20];
  
  // Muon
  UInt_t          nMuon_;
  Float_t         muPt_[15];
  Float_t         muEta_[15];
  Float_t         muPhi_[15];
  Int_t           muCharge_[15];
  Float_t         muMass_[15];
  Int_t           muGenIdx_[15];

  // Jet
  UInt_t          nJet_;
  Float_t         jetPt_[200];
  Float_t         jetEta_[200];
  Float_t         jetPhi_[200];
  Float_t         jetMass_[200];
  Int_t           jetHadFlvr_[200];
  Int_t           jetPartFlvr_[200];
  Int_t           jetGenJetIdx_[200];

  //MET
  Float_t  MET_pt_;
  Float_t  MET_phi_;

  Float_t  GenMET_pt_;
  Float_t  GenMET_phi_;

    
  ///////////////////////////////////////////////////////////////////////////
  tree->SetBranchStatus("nGenPart",1);
  tree->SetBranchAddress("nGenPart", &nGenPart_);
	
  tree->SetBranchStatus("GenPart_pt",1);
  tree->SetBranchAddress("GenPart_pt", &GenPart_pt_);
	
  tree->SetBranchStatus("GenPart_eta",1);
  tree->SetBranchAddress("GenPart_eta", &GenPart_eta_);
	
  tree->SetBranchStatus("GenPart_phi",1);
  tree->SetBranchAddress("GenPart_phi", &GenPart_phi_);

  tree->SetBranchStatus("GenPart_mass",1);
  tree->SetBranchAddress("GenPart_mass", &GenPart_mass_);

  tree->SetBranchStatus("GenPart_genPartIdxMother",1);
  tree->SetBranchAddress("GenPart_genPartIdxMother", &GenPart_genPartIdxMother_);
    
  tree->SetBranchStatus("GenPart_pdgId",1);
  tree->SetBranchAddress("GenPart_pdgId", &GenPart_pdgId_);

  tree->SetBranchAddress("GenPart_status", &GenPart_status_);
  tree->SetBranchAddress("GenPart_statusFlags", &GenPart_statusFlags_);
  /////////////////////////////////////////////////////////////////////////////
  tree->SetBranchStatus("nGenJet",1);
  tree->SetBranchAddress("nGenJet", &nGenJet_);
	
  tree->SetBranchStatus("GenJet_pt",1);
  tree->SetBranchAddress("GenJet_pt", &GenJet_pt_);

  tree->SetBranchStatus("GenJet_eta",1);
  tree->SetBranchAddress("GenJet_eta", &GenJet_eta_);

  tree->SetBranchStatus("GenJet_phi",1);
  tree->SetBranchAddress("GenJet_phi", &GenJet_phi_);
 
  tree->SetBranchStatus("GenJet_mass",1);
  tree->SetBranchAddress("GenJet_mass", &GenJet_mass_);

  tree->SetBranchStatus("GenJet_partonFlavour",1);
  tree->SetBranchAddress("GenJet_partonFlavour", &GenJet_partonFlavour_);
	
  tree->SetBranchStatus("GenJet_hadronFlavour",1);
  tree->SetBranchAddress("GenJet_hadronFlavour", &GenJet_hadronFlavour_);
  /////////////////////////////////////////////////////////////////////////////
  tree->SetBranchStatus("nElectron",1);
  tree->SetBranchAddress("nElectron", &nEle_);

  tree->SetBranchStatus("Electron_pt",1);
  tree->SetBranchAddress("Electron_pt", &elePt_);

  tree->SetBranchStatus("Electron_eta",1);
  tree->SetBranchAddress("Electron_eta", &eleEta_);

  tree->SetBranchStatus("Electron_phi",1);
  tree->SetBranchAddress("Electron_phi", &elePhi_);

  tree->SetBranchStatus("Electron_charge",1);
  tree->SetBranchAddress("Electron_charge", &eleCharge_);	

  tree->SetBranchStatus("Electron_mass",1);
  tree->SetBranchAddress("Electron_mass", &eleMass_);

  tree->SetBranchStatus("Electron_mass",1);
  tree->SetBranchAddress("Electron_mass", &eleMass_);

  tree->SetBranchStatus("Electron_genPartIdx",1);
  tree->SetBranchAddress("Electron_genPartIdx", &eleGenIdx_);
  ///////////////////////////////////////////////////////////////////////////
  tree->SetBranchStatus("nMuon",1);
  tree->SetBranchAddress("nMuon", &nMuon_);
	
  tree->SetBranchStatus("Muon_pt",1);
  tree->SetBranchAddress("Muon_pt", &muPt_);

  tree->SetBranchStatus("Muon_eta",1);
  tree->SetBranchAddress("Muon_eta", &muEta_);

  tree->SetBranchStatus("Muon_phi",1);
  tree->SetBranchAddress("Muon_phi", &muPhi_);

  tree->SetBranchStatus("Muon_charge",1);
  tree->SetBranchAddress("Muon_charge", &muCharge_);

  tree->SetBranchStatus("Muon_mass",1);
  tree->SetBranchAddress("Muon_mass", &muMass_);

  tree->SetBranchStatus("Muon_genPartIdx",1);
  tree->SetBranchAddress("Muon_genPartIdx", &muGenIdx_);
  ///////////////////////////////////////////////////////////////////////////
  tree->SetBranchStatus("nJet",1);
  tree->SetBranchAddress("nJet", &nJet_);
 
  tree->SetBranchStatus("Jet_pt",1);
  tree->SetBranchAddress("Jet_pt", &jetPt_);

  tree->SetBranchStatus("Jet_eta",1);
  tree->SetBranchAddress("Jet_eta", &jetEta_);
	
  tree->SetBranchStatus("Jet_phi",1);
  tree->SetBranchAddress("Jet_phi", &jetPhi_);

  tree->SetBranchStatus("Jet_mass",1);
  tree->SetBranchAddress("Jet_mass", &jetMass_);

  tree->SetBranchStatus("Jet_hadronFlavour",1);
  tree->SetBranchAddress("Jet_hadronFlavour", &jetHadFlvr_);
  
  tree->SetBranchStatus("Jet_partonFlavour",1);
  tree->SetBranchAddress("Jet_partonFlavour", &jetPartFlvr_);
  
  tree->SetBranchStatus("Jet_genJetIdx",1);
  tree->SetBranchAddress("Jet_genJetIdx", &jetGenJetIdx_);
  ///////////////////////////////////////////////////////////////////////////

  tree->SetBranchAddress("MET_pt", &MET_pt_);
  tree->SetBranchAddress("MET_phi", &MET_phi_);
  tree->SetBranchAddress("GenMET_pt", &GenMET_pt_);
  tree->SetBranchAddress("GenMET_phi", &GenMET_phi_);
  
  ///////////////////////////////////////////////////////////////////////////
  Int_t nMuEtaBins = 25;
  Float_t muEtaBin[26] = {0.0, 0.100, 0.200, 0.300, 0.400, 
			  0.500, 0.600, 0.700, 0.800, 0.900, 
			  1.000, 1.100, 1.200, 1.300, 1.400, 
			  1.500, 1.600, 1.700, 1.800, 1.900, 
			  2.000, 2.100, 2.200, 2.300, 2.4,
                          2.5};
  
  Int_t nEleEtaBins = 24;
  Float_t eleEtaBin[25] = {0.0, 0.174, 0.261, 0.348, 0.435, 
			   0.522, 0.609, 0.696, 0.783, 0.870, 
			   0.957, 1.044, 1.131, 1.218, 1.305, 
			   1.392, 1.479, 1.653, 1.740, 1.830, 
			   1.930, 2.043, 2.172, 2.322, 2.5};
  
  Int_t nJetEtaBins = 26;
  Float_t jetEtaBin[27] = {0.0, 0.087, 0.174, 0.261, 0.348, 
  			   0.435, 0.522, 0.609, 0.696, 0.783, 
  			   0.870, 0.957, 1.044, 1.131, 1.218, 
  			   1.305, 1.392, 1.479, 1.566, 1.653, 
  			   1.740, 1.830, 1.930, 2.043, 2.172, 
  			   2.322, 2.5};
  
  // Int_t nJetEtaBins = 1;
  // Float_t jetEtaBin[2] = {0.435, 0.783};
  
  Int_t nETBins = 19;
  Float_t ETBin[20] = {20., 30., 40., 50., 60.,
                       70., 80., 90., 100., 120.,
                       140., 160., 180., 200., 240., 
                       280., 320., 360., 400., 500.};
  
  
  TH1F ***hBJetETReso, ***hLJetETReso, ***hBJetEtaReso, ***hLJetEtaReso, ***hBJetPhiReso, ***hLJetPhiReso;
  hBJetETReso = new TH1F**[nJetEtaBins];
  hLJetETReso = new TH1F**[nJetEtaBins];
  hBJetEtaReso = new TH1F**[nJetEtaBins];
  hLJetEtaReso = new TH1F**[nJetEtaBins];
  hBJetPhiReso = new TH1F**[nJetEtaBins];
  hLJetPhiReso = new TH1F**[nJetEtaBins];
  for(int ieta=0;ieta<nJetEtaBins;ieta++){
    hBJetETReso[ieta] = new TH1F*[nETBins];
    hLJetETReso[ieta] = new TH1F*[nETBins];
    hBJetEtaReso[ieta] = new TH1F*[nETBins];
    hLJetEtaReso[ieta] = new TH1F*[nETBins];
    hBJetPhiReso[ieta] = new TH1F*[nETBins];
    hLJetPhiReso[ieta] = new TH1F*[nETBins];
    for(int iet=0;iet<nETBins;iet++){
      hBJetETReso[ieta][iet] = new TH1F(Form("hBJetETReso_%d_%d",ieta,iet),
					Form("hBJetETReso #eta:(%4.3f-%4.3f) E_{T}:(%2.0f-%2.0f) GeV",jetEtaBin[ieta],jetEtaBin[ieta+1],ETBin[iet],ETBin[iet+1]),
					200,-200.,200.);
      hLJetETReso[ieta][iet] = new TH1F(Form("hLJetETReso_%d_%d",ieta,iet),
					Form("hLJetETReso #eta:(%4.3f-%4.3f) E_{T}:(%2.0f-%2.0f) GeV",jetEtaBin[ieta],jetEtaBin[ieta+1],ETBin[iet],ETBin[iet+1]),
					200,-200.,200.);
      hBJetEtaReso[ieta][iet] = new TH1F(Form("hBJetEtaReso_%d_%d",ieta,iet),
					 Form("hBJetEtaReso #eta:(%4.3f-%4.3f) E_{T}:(%2.0f-%2.0f) GeV",jetEtaBin[ieta],jetEtaBin[ieta+1],ETBin[iet],ETBin[iet+1]),
					 200, -0.2, 0.2);
      hLJetEtaReso[ieta][iet] = new TH1F(Form("hLJetEtaReso_%d_%d",ieta,iet),
					 Form("hLJetEtaReso #eta:(%4.3f-%4.3f) E_{T}:(%2.0f-%2.0f) GeV",jetEtaBin[ieta],jetEtaBin[ieta+1],ETBin[iet],ETBin[iet+1]),
					 200, -0.2, 0.2);
      hBJetPhiReso[ieta][iet] = new TH1F(Form("hBJetPhiReso_%d_%d",ieta,iet),
					 Form("hBJetPhiReso #eta:(%4.3f-%4.3f) E_{T}:(%2.0f-%2.0f) GeV",jetEtaBin[ieta],jetEtaBin[ieta+1],ETBin[iet],ETBin[iet+1]),
					 200, -0.2, 0.2);
      hLJetPhiReso[ieta][iet] = new TH1F(Form("hLJetPhiReso_%d_%d",ieta,iet),
					 Form("hLJetPhiReso #eta:(%4.3f-%4.3f) E_{T}:(%2.0f-%2.0f) GeV",jetEtaBin[ieta],jetEtaBin[ieta+1],ETBin[iet],ETBin[iet+1]),
					 200, -0.2, 0.2);
      // hBJetETDelRReso[iet] = new TH1F(Form("hBJetETDelRReso_0_%d",iet),Form("hBJetETDelRReso_0_%d",iet), 200, 0.,1.);
    }
  }
  TH2F *hJetEtaETBin = new TH2F("hJetEtaETBin","hJetEtaETBin", nJetEtaBins, jetEtaBin, nETBins, ETBin);
  
  TH1F ***hMuETReso, ***hMuEtaReso, ***hMuPhiReso;
  hMuETReso = new TH1F**[nMuEtaBins];
  hMuEtaReso = new TH1F**[nMuEtaBins];
  hMuPhiReso = new TH1F**[nMuEtaBins];
  for(int ieta=0;ieta<nMuEtaBins;ieta++){
    hMuETReso[ieta] = new TH1F*[nETBins];
    hMuEtaReso[ieta] = new TH1F*[nETBins];
    hMuPhiReso[ieta] = new TH1F*[nETBins];
    for(int iet=0;iet<nETBins;iet++){
      hMuETReso[ieta][iet] = new TH1F(Form("hMuETReso_%d_%d",ieta,iet),
					Form("hMuETReso #eta:(%4.3f-%4.3f) E_{T}:(%2.0f-%2.0f) GeV",muEtaBin[ieta],muEtaBin[ieta+1],ETBin[iet],ETBin[iet+1]),
					200,-20.,20.);
      hMuEtaReso[ieta][iet] = new TH1F(Form("hMuEtaReso_%d_%d",ieta,iet),
					 Form("hMuEtaReso #eta:(%4.3f-%4.3f) E_{T}:(%2.0f-%2.0f) GeV",muEtaBin[ieta],muEtaBin[ieta+1],ETBin[iet],ETBin[iet+1]),
					 200, -0.01, 0.01);
      hMuPhiReso[ieta][iet] = new TH1F(Form("hMuPhiReso_%d_%d",ieta,iet),
					 Form("hMuPhiReso #eta:(%4.3f-%4.3f) E_{T}:(%2.0f-%2.0f) GeV",muEtaBin[ieta],muEtaBin[ieta+1],ETBin[iet],ETBin[iet+1]),
					 200, -0.01, 0.01);
    }
  }
  TH2F *hMuEtaETBin = new TH2F("hMuEtaETBin","hMuEtaETBin", nMuEtaBins, muEtaBin, nETBins, ETBin);
  
  TH1F ***hEleETReso, ***hEleEtaReso, ***hElePhiReso;
  hEleETReso = new TH1F**[nEleEtaBins];
  hEleEtaReso = new TH1F**[nEleEtaBins];
  hElePhiReso = new TH1F**[nEleEtaBins];
  for(int ieta=0;ieta<nEleEtaBins;ieta++){
    hEleETReso[ieta] = new TH1F*[nETBins];
    hEleEtaReso[ieta] = new TH1F*[nETBins];
    hElePhiReso[ieta] = new TH1F*[nETBins];
    for(int iet=0;iet<nETBins;iet++){
      hEleETReso[ieta][iet] = new TH1F(Form("hEleETReso_%d_%d",ieta,iet),
				       Form("hEleETReso #eta:(%4.3f-%4.3f) E_{T}:(%2.0f-%2.0f) GeV",eleEtaBin[ieta],eleEtaBin[ieta+1],ETBin[iet],ETBin[iet+1]),
				       200,-20.,20.);
      hEleEtaReso[ieta][iet] = new TH1F(Form("hEleEtaReso_%d_%d",ieta,iet),
					Form("hEleEtaReso #eta:(%4.3f-%4.3f) E_{T}:(%2.0f-%2.0f) GeV",eleEtaBin[ieta],eleEtaBin[ieta+1],ETBin[iet],ETBin[iet+1]),
					200, -0.01, 0.01);
      hElePhiReso[ieta][iet] = new TH1F(Form("hElePhiReso_%d_%d",ieta,iet),
					Form("hElePhiReso #eta:(%4.3f-%4.3f) E_{T}:(%2.0f-%2.0f) GeV",eleEtaBin[ieta],eleEtaBin[ieta+1],ETBin[iet],ETBin[iet+1]),
					200, -0.01, 0.01);
    }
  }
  TH2F *hEleEtaETBin = new TH2F("hEleEtaETBin","hEleEtaETBin", nEleEtaBins, eleEtaBin, nETBins, ETBin);
  
  TH1F **hMETETReso, **hMETPhiReso;
  hMETETReso = new TH1F*[nETBins];
  hMETPhiReso = new TH1F*[nETBins];
  for(int iet=0;iet<nETBins;iet++){
    hMETETReso[iet] = new TH1F(Form("hMETETReso_%d",iet),Form("hMETETReso_%d E_{T}:(%2.0f-%2.0f) GeV",iet,ETBin[iet],ETBin[iet+1]),400,-400.,400.);
    hMETPhiReso[iet] = new TH1F(Form("hMETPhiReso_%d",iet),Form("hMETPhiReso_%d E_{T}:(%2.0f-%2.0f) GeV",iet,ETBin[iet],ETBin[iet+1]),200, -2.0, 2.0);
  }
  TH1F *hMETETBin = new TH1F("hMETETBin","hMETETBin", nETBins, ETBin);
  
  TLorentzVector mujetR, mujetG; 
  TLorentzVector elejetR, elejetG; 
  TLorentzVector metR, metG; 
  TLorentzVector bjetR, bjetG; 
  TLorentzVector ljetR, ljetG; 
  float eta, et ;
  int binEta, binET;
  
  cout << "Total Events : " <<  tree->GetEntries() << endl;
  //for(int ievent=0; ievent<tree->GetEntries(); ievent++){
  for(int ievent=0; ievent<200000; ievent++){
  //for(int ievent=0; ievent<10; ievent++){
    
    tree->GetEntry(ievent);
    if(ievent%10000==0)
      printf("Processing Event : %d, nof muons : %u\n",ievent,nMuon_);
    
    bool hasMu = false;
    for(int muInd = 0; muInd < int(nMuon_); ++muInd){
      int genIdx = int(muGenIdx_[muInd]);
      if ( (genIdx>-1) && (genIdx < int(nGenPart_))){
      	unsigned int imc = genIdx ;
	TParticlePDG *partPDG = TDatabasePDG::Instance()->GetParticle(GenPart_pdgId_[imc]);
	TParticlePDG *partPDG_mother = TDatabasePDG::Instance()->GetParticle(GenPart_pdgId_[GenPart_genPartIdxMother_[imc]]);
	if(!partPDG_mother){
	}else{
	  // printf("\tMuon PDG : %5d (%7s), Rec:(%5.2f, %5.2f, %5.2f, %1d, %5.2f), Gen:(%5.2f, %5.2f, %5.2f, %1.0f, %5.2f), Mother : %7s\n", 
	  // 	 GenPart_pdgId_[imc], partPDG->GetName(), 
	  // 	 muPt_[muInd], muEta_[muInd] , muPhi_[muInd], muCharge_[muInd], muMass_[muInd],  
	  // 	 GenPart_pt_[imc], GenPart_eta_[imc] , GenPart_phi_[imc], partPDG->Charge()/3., GenPart_mass_[imc], 
	  // 	 partPDG_mother->GetName());
	  mujetR.SetPtEtaPhiM(muPt_[muInd], muEta_[muInd] , muPhi_[muInd], muMass_[muInd]);
	  mujetG.SetPtEtaPhiM(GenPart_pt_[imc], GenPart_eta_[imc] , GenPart_phi_[imc], GenPart_mass_[imc]);
	  if(mujetR.DeltaR(mujetG) < 0.1 and muCharge_[muInd]==int(partPDG->Charge()/3. and abs(GenPart_pdgId_[imc])==13)){
	    hasMu = true;
	    //cout << "Found muon " << endl;
	  }
	}
      }
    }//muon loop
    
    bool hasEle = false;
    for(int eleInd = 0; eleInd < int(nEle_); ++eleInd){
      int genIdx = int(eleGenIdx_[eleInd]);
      if ( (genIdx>-1) && (genIdx < int(nGenPart_))){
      	unsigned int imc = genIdx ;
    	TParticlePDG *partPDG = TDatabasePDG::Instance()->GetParticle(GenPart_pdgId_[imc]);
    	TParticlePDG *partPDG_mother = TDatabasePDG::Instance()->GetParticle(GenPart_pdgId_[GenPart_genPartIdxMother_[imc]]);
    	if(!partPDG_mother){
    	}else{
    	  // printf("\tElectron : PDG : %5d (%7s), Rec:(%5.2f, %5.2f, %5.2f, %1d, %5.2f), Gen:(%5.2f, %5.2f, %5.2f, %5.2f), Mother : %7s\n", 
    	  // 	 GenPart_pdgId_[imc], partPDG->GetName(), 
    	  // 	 elePt_[eleInd], eleEta_[eleInd] , elePhi_[eleInd], eleCharge_[eleInd], eleMass_[eleInd],  
    	  // 	 GenPart_pt_[imc], GenPart_eta_[imc] , GenPart_phi_[imc], GenPart_mass_[imc], 
    	  // 	 partPDG_mother->GetName());
	  elejetR.SetPtEtaPhiM(elePt_[eleInd], eleEta_[eleInd] , elePhi_[eleInd], eleMass_[eleInd]);
	  elejetG.SetPtEtaPhiM(GenPart_pt_[imc], GenPart_eta_[imc] , GenPart_phi_[imc], GenPart_mass_[imc]);
	  if(elejetR.DeltaR(elejetG) < 0.1 and eleCharge_[eleInd]==int(partPDG->Charge()/3.) and abs(GenPart_pdgId_[imc])==11){
	    hasEle = true;
	    //cout << "Found electron " << endl;
	  }
	  
    	}
      }
    }//electron loop
    
    int nbjet = 0, nljet = 0;
    for(int jetInd = 0; jetInd < int(nJet_); ++jetInd){
      int genIdx = int(jetGenJetIdx_[jetInd]);
      if ( (genIdx>-1) && (genIdx < int(nGenJet_))){
      	unsigned int imc = genIdx ;
    	// printf("\tJet : Rec:(%2d, %5.2f, %5.2f, %5.2f, %5.2f), Gen:(%2d, %5.2f, %5.2f, %5.2f, %5.2f)\n", 
    	//        jetPartFlvr_[jetInd],jetPt_[jetInd], jetEta_[jetInd] , jetPhi_[jetInd], jetMass_[jetInd],  
    	//        GenJet_partonFlavour_[genIdx],GenJet_pt_[genIdx], GenJet_eta_[genIdx] , GenJet_phi_[genIdx], GenJet_mass_[genIdx]);
    	if(jetPartFlvr_[jetInd]==GenJet_partonFlavour_[genIdx] and abs(jetPartFlvr_[jetInd])==5){
    	  bjetR.SetPtEtaPhiM(jetPt_[jetInd], jetEta_[jetInd] , jetPhi_[jetInd], jetMass_[jetInd]);
    	  bjetG.SetPtEtaPhiM(GenJet_pt_[genIdx], GenJet_eta_[genIdx] , GenJet_phi_[genIdx], GenJet_mass_[genIdx]);
	  if(bjetR.DeltaR(bjetG)<0.2)
	    nbjet++;
    	}//b-jet condition
	
    	if(jetPartFlvr_[jetInd]==GenJet_partonFlavour_[genIdx] and ((abs(jetPartFlvr_[jetInd])>=1 and abs(jetPartFlvr_[jetInd])<=4) or abs(jetPartFlvr_[jetInd])==21) ){ //u,d,s,c,g
    	  ljetR.SetPtEtaPhiM(jetPt_[jetInd], jetEta_[jetInd] , jetPhi_[jetInd], jetMass_[jetInd]);
    	  ljetG.SetPtEtaPhiM(GenJet_pt_[genIdx], GenJet_eta_[genIdx] , GenJet_phi_[genIdx], GenJet_mass_[genIdx]);
	  if(ljetR.DeltaR(ljetG)<0.2)
	    nljet++;
    	}//l-jet condition
	
      }//found the corresponding genjet 
    }//jet loop
    
    if((!hasMu and !hasEle) or (nbjet+nljet) < 4 or nbjet < 2) continue;

    // //for (unsigned int imc = 0 ; imc < nGenPart_ ; imc++ ){      
    // for (unsigned int imc = 0 ; imc < 30 ; imc++ ){      
    //   TParticlePDG *partPDG = TDatabasePDG::Instance()->GetParticle(GenPart_pdgId_[imc]);
    //   if(!partPDG){
    // 	printf("\t id : %03d, PDG : %5d ( noPDGname), status : %2d, (Pt, Eta, Phi, Mass) = (%5.2f, %5.2f, %5.2f, %5.2f), Mother-id : %03d\n", 
    // 	       imc, GenPart_pdgId_[imc], GenPart_status_[imc], GenPart_pt_[imc], 
    // 	       GenPart_eta_[imc] , GenPart_phi_[imc], GenPart_mass_[imc], GenPart_genPartIdxMother_[imc]
    // 	       );
    //   }else{
    // 	printf("\t id : %03d, PDG : %5d (%7s), status : %2d, (Pt, Eta, Phi, Mass) = (%5.2f, %5.2f, %5.2f, %5.2f), Mother-id : %03d\n", 
    // 	       imc, GenPart_pdgId_[imc], partPDG->GetName(), GenPart_status_[imc], GenPart_pt_[imc],
    // 	       GenPart_eta_[imc] , GenPart_phi_[imc], GenPart_mass_[imc], GenPart_genPartIdxMother_[imc]
    // 	       );
    //   }
    // }// mc particle loop

    for(int muInd = 0; muInd < int(nMuon_); ++muInd){
      int genIdx = int(muGenIdx_[muInd]);
      if ( (genIdx>-1) && (genIdx < int(nGenPart_))){
      	unsigned int imc = genIdx ;
	TParticlePDG *partPDG = TDatabasePDG::Instance()->GetParticle(GenPart_pdgId_[imc]);
	TParticlePDG *partPDG_mother = TDatabasePDG::Instance()->GetParticle(GenPart_pdgId_[GenPart_genPartIdxMother_[imc]]);
	if(!partPDG_mother){
	}else{
	  // printf("\tMuon PDG : %5d (%7s), Rec:(%5.2f, %5.2f, %5.2f, %1d, %5.2f), Gen:(%5.2f, %5.2f, %5.2f, %1.0f, %5.2f), Mother : %7s\n", 
	  // 	 GenPart_pdgId_[imc], partPDG->GetName(), 
	  // 	 muPt_[muInd], muEta_[muInd] , muPhi_[muInd], muCharge_[muInd], muMass_[muInd],  
	  // 	 GenPart_pt_[imc], GenPart_eta_[imc] , GenPart_phi_[imc], partPDG->Charge()/3., GenPart_mass_[imc], 
	  // 	 partPDG_mother->GetName());
	  mujetR.SetPtEtaPhiM(muPt_[muInd], muEta_[muInd] , muPhi_[muInd], muMass_[muInd]);
	  mujetG.SetPtEtaPhiM(GenPart_pt_[imc], GenPart_eta_[imc] , GenPart_phi_[imc], GenPart_mass_[imc]);
	  if(mujetR.DeltaR(mujetG) < 0.1 and muCharge_[muInd]==int(partPDG->Charge()/3. and abs(GenPart_pdgId_[imc])==13)){

	    eta = abs(muEta_[muInd]);
	    et = mujetR.Et();
	    GetHistoBin(hMuEtaETBin, eta, et, binEta, binET);
	    
	    double etResoPercent = 100.*(et - mujetG.Et())/et;
	    double etaReso = mujetR.Eta() - mujetG.Eta();
	    double phiReso = mujetR.Phi() - mujetG.Phi();

	    hMuETReso[binEta-1][binET-1]->Fill(etResoPercent);
	    hMuEtaReso[binEta-1][binET-1]->Fill(etaReso);
	    hMuPhiReso[binEta-1][binET-1]->Fill(phiReso);
	  }
	}
      }
    }//muon loop

    for(int eleInd = 0; eleInd < int(nEle_); ++eleInd){
      int genIdx = int(eleGenIdx_[eleInd]);
      if ( (genIdx>-1) && (genIdx < int(nGenPart_))){
      	unsigned int imc = genIdx ;
    	TParticlePDG *partPDG = TDatabasePDG::Instance()->GetParticle(GenPart_pdgId_[imc]);
    	TParticlePDG *partPDG_mother = TDatabasePDG::Instance()->GetParticle(GenPart_pdgId_[GenPart_genPartIdxMother_[imc]]);
    	if(!partPDG_mother){
    	}else{
    	  // printf("\tElectron : PDG : %5d (%7s), Rec:(%5.2f, %5.2f, %5.2f, %1d, %5.2f), Gen:(%5.2f, %5.2f, %5.2f, %5.2f), Mother : %7s\n", 
    	  // 	 GenPart_pdgId_[imc], partPDG->GetName(), 
    	  // 	 elePt_[eleInd], eleEta_[eleInd] , elePhi_[eleInd], eleCharge_[eleInd], eleMass_[eleInd],  
    	  // 	 GenPart_pt_[imc], GenPart_eta_[imc] , GenPart_phi_[imc], GenPart_mass_[imc], 
    	  // 	 partPDG_mother->GetName());
	  elejetR.SetPtEtaPhiM(elePt_[eleInd], eleEta_[eleInd] , elePhi_[eleInd], eleMass_[eleInd]);
	  elejetG.SetPtEtaPhiM(GenPart_pt_[imc], GenPart_eta_[imc] , GenPart_phi_[imc], GenPart_mass_[imc]);
	  if(elejetR.DeltaR(elejetG) < 0.1 and eleCharge_[eleInd]==int(partPDG->Charge()/3.) and abs(GenPart_pdgId_[imc])==11){

	    eta = abs(eleEta_[eleInd]);
	    et = elejetR.Et();
	    GetHistoBin(hEleEtaETBin, eta, et, binEta, binET);
	    
	    double etResoPercent = 100.*(et - elejetG.Et())/et;
	    double etaReso = elejetR.Eta() - elejetG.Eta();
	    double phiReso = elejetR.Phi() - elejetG.Phi();

	    hEleETReso[binEta-1][binET-1]->Fill(etResoPercent);
	    hEleEtaReso[binEta-1][binET-1]->Fill(etaReso);
	    hElePhiReso[binEta-1][binET-1]->Fill(phiReso);

	  }
	  
    	}
      }
    }//electron loop
    
    // printf("MET Rec:(%5.2f, %5.2f) Gen:(%5.2f, %5.2f), Reso : (%5.2f,%5.2f)\n",MET_pt_,MET_phi_,GenMET_pt_,GenMET_phi_, 
    // 	   100.*abs(MET_pt_-GenMET_pt_)/MET_pt_, 100.*abs(MET_phi_-GenMET_phi_)/MET_phi_);
    
    metR.SetPtEtaPhiM(MET_pt_, 0.0, MET_phi_, 0.0);
    metG.SetPtEtaPhiM(GenMET_pt_, 0.0, GenMET_phi_, 0.0);
    
    et = metR.Et();
    binET = GetHistoBin(hMETETBin, et);
    double etResoPercent = 100.*(et - metG.Et())/et;
    double phiReso = metR.Phi() - metG.Phi();
    hMETETReso[binET-1]->Fill(etResoPercent);
    hMETPhiReso[binET-1]->Fill(phiReso);

    for(int jetInd = 0; jetInd < int(nJet_); ++jetInd){
      int genIdx = int(jetGenJetIdx_[jetInd]);
      if ( (genIdx>-1) && (genIdx < int(nGenJet_))){
      	unsigned int imc = genIdx ;
    	// printf("\tJet : Rec:(%2d, %5.2f, %5.2f, %5.2f, %5.2f), Gen:(%2d, %5.2f, %5.2f, %5.2f, %5.2f)\n", 
    	//        jetPartFlvr_[jetInd],jetPt_[jetInd], jetEta_[jetInd] , jetPhi_[jetInd], jetMass_[jetInd],  
    	//        GenJet_partonFlavour_[genIdx],GenJet_pt_[genIdx], GenJet_eta_[genIdx] , GenJet_phi_[genIdx], GenJet_mass_[genIdx]);
    	if(jetPartFlvr_[jetInd]==GenJet_partonFlavour_[genIdx] and abs(jetPartFlvr_[jetInd])==5){
    	  bjetR.SetPtEtaPhiM(jetPt_[jetInd], jetEta_[jetInd] , jetPhi_[jetInd], jetMass_[jetInd]);
    	  bjetG.SetPtEtaPhiM(GenJet_pt_[genIdx], GenJet_eta_[genIdx] , GenJet_phi_[genIdx], GenJet_mass_[genIdx]);
    	  eta = abs(jetEta_[jetInd]);
	  et = bjetR.Et();
	  GetHistoBin(hJetEtaETBin, eta, et, binEta, binET);
	  double etResoPercent = 100.*(et - bjetG.Et())/et;
	  double etaReso = bjetR.Eta() - bjetG.Eta();
	  double phiReso = bjetR.Phi() - bjetG.Phi();
	  if(bjetR.DeltaR(bjetG)<0.2){
	    hBJetETReso[binEta-1][binET-1]->Fill(etResoPercent);
	    hBJetEtaReso[binEta-1][binET-1]->Fill(etaReso);
	    hBJetPhiReso[binEta-1][binET-1]->Fill(phiReso);
	  }
	  //hBJetETDelRReso[binET-1]->Fill(bjetR.DeltaR(bjetG));
    	}//b-jet condition
	
    	if(jetPartFlvr_[jetInd]==GenJet_partonFlavour_[genIdx] and ((abs(jetPartFlvr_[jetInd])>=1 and abs(jetPartFlvr_[jetInd])<=4) or abs(jetPartFlvr_[jetInd])==21) ){ //u,d,s,c,g
    	  ljetR.SetPtEtaPhiM(jetPt_[jetInd], jetEta_[jetInd] , jetPhi_[jetInd], jetMass_[jetInd]);
    	  ljetG.SetPtEtaPhiM(GenJet_pt_[genIdx], GenJet_eta_[genIdx] , GenJet_phi_[genIdx], GenJet_mass_[genIdx]);
	  eta = abs(jetEta_[jetInd]);
	  et = ljetR.Et();
	  GetHistoBin(hJetEtaETBin, eta, et, binEta, binET);
	  double etResoPercent = 100.*(et - ljetG.Et())/et;
	  double etaReso = ljetR.Eta() - ljetG.Eta();
	  double phiReso = ljetR.Phi() - ljetG.Phi();
	  if(ljetR.DeltaR(ljetG)<0.2){
	    hLJetETReso[binEta-1][binET-1]->Fill(etResoPercent);
	    hLJetEtaReso[binEta-1][binET-1]->Fill(etaReso);
	    hLJetPhiReso[binEta-1][binET-1]->Fill(phiReso);
	  }
    	}//l-jet condition
	
      }//found the corresponding genjet 
    }//jet loop

    
  }//event loop

  TCanvas *c0 = new TCanvas("c0","c0");
  hBJetETReso[0][0]->Draw();

  TFile *fout = new TFile("root_files/test/Resolution.root","recreate");
  for(int ieta=0;ieta<nJetEtaBins;ieta++)
    for(int iet=0;iet<nETBins;iet++)
      hBJetETReso[ieta][iet]->Write();
  for(int ieta=0;ieta<nJetEtaBins;ieta++)
    for(int iet=0;iet<nETBins;iet++)  
      hLJetETReso[ieta][iet]->Write();
  for(int ieta=0;ieta<nJetEtaBins;ieta++)
    for(int iet=0;iet<nETBins;iet++)
      hBJetEtaReso[ieta][iet]->Write();
  for(int ieta=0;ieta<nJetEtaBins;ieta++)
    for(int iet=0;iet<nETBins;iet++)  
      hLJetEtaReso[ieta][iet]->Write();
  for(int ieta=0;ieta<nJetEtaBins;ieta++)
    for(int iet=0;iet<nETBins;iet++)
      hBJetPhiReso[ieta][iet]->Write();
  for(int ieta=0;ieta<nJetEtaBins;ieta++)
    for(int iet=0;iet<nETBins;iet++)  
      hLJetPhiReso[ieta][iet]->Write();
  for(int ieta=0;ieta<nMuEtaBins;ieta++)
    for(int iet=0;iet<nETBins;iet++)
      hMuETReso[ieta][iet]->Write();
  for(int ieta=0;ieta<nMuEtaBins;ieta++)
    for(int iet=0;iet<nETBins;iet++)
      hMuEtaReso[ieta][iet]->Write();
  for(int ieta=0;ieta<nMuEtaBins;ieta++)
    for(int iet=0;iet<nETBins;iet++)
      hMuPhiReso[ieta][iet]->Write();
  for(int ieta=0;ieta<nEleEtaBins;ieta++)
    for(int iet=0;iet<nETBins;iet++)
      hEleETReso[ieta][iet]->Write();
  for(int ieta=0;ieta<nEleEtaBins;ieta++)
    for(int iet=0;iet<nETBins;iet++)
      hEleEtaReso[ieta][iet]->Write();
  for(int ieta=0;ieta<nEleEtaBins;ieta++)
    for(int iet=0;iet<nETBins;iet++)
      hElePhiReso[ieta][iet]->Write();  
  for(int iet=0;iet<nETBins;iet++)
    hMETETReso[iet]->Write();
  for(int iet=0;iet<nETBins;iet++)
    hMETPhiReso[iet]->Write();
  
  fout->Close();
  delete fout;  
  
  return true;
}

int GetHistoBin(TH1F *h, float et)
{
  double minX = h->GetXaxis()->GetBinCenter(1);
  double maxX = h->GetXaxis()->GetBinCenter(h->GetNbinsX());
  Int_t binX = -1;
  if(et <= minX)
    binX = 1;
  else if(et >= maxX)
    binX = h->GetXaxis()->FindBin(maxX);
  else
    binX = h->GetXaxis()->FindBin(et);
  
  return binX;
}

bool GetHistoBin(TH2F *h, float eta, float et, int& binX, int& binY)
{
  double minX = h->GetXaxis()->GetBinCenter(1);
  double maxX = h->GetXaxis()->GetBinCenter(h->GetNbinsX());
  double minY = h->GetYaxis()->GetBinCenter(1);
  double maxY = h->GetYaxis()->GetBinCenter(h->GetNbinsY());

  binX = -1;
  if(eta <= minX)
    binX = 1;
  else if(eta >= maxX)
    binX = h->GetXaxis()->FindBin(maxX);
  else
    binX = h->GetXaxis()->FindBin(eta);

  binY = -1;
  if(et <= minY)
    binY = 1;
  else if(et >= maxY)
    binY = h->GetYaxis()->FindBin(maxY);
  else
    binY = h->GetYaxis()->FindBin(et);

  return true;
}

// int GetHistoBin(TH1F *h, float et)
// {
//   double minX = h->GetXaxis()->GetBinCenter(1);
//   double maxX = h->GetXaxis()->GetBinCenter(h->GetNbinsX());
//   Int_t binX = -1;
//   if(et <= minX)
//     binX = 1;
//   else if(et >= maxX)
//     binX = h->GetXaxis()->FindBin(maxX);
//   else
//     binX = h->GetXaxis()->FindBin(et);
  
//   return binX;
// }

// int bjetResolution(double et, double eta, double& resEt, double& resEta, double& resPhi)
// {

//   double abseta = fabs(eta) ;


//   if (0.000 <= abseta and abseta < 0.087) {
//     resEt   = et * ( TMath::Sqrt( TMath::Power(0.0686,2) + TMath::Power(1.03/TMath::Sqrt(et),2) + TMath::Power(1.68/et,2) ) )  ;
//     resEta  =  TMath::Sqrt( TMath::Power(0.00605,2) + TMath::Power(1.63/et,2) )  ;
//     resPhi  =  TMath::Sqrt( TMath::Power(0.00787,2) + TMath::Power(1.74/et,2) )  ;
//   }

//   else if (0.087 <= abseta and abseta < 0.174) {
//     resEt   = et * ( TMath::Sqrt( TMath::Power(0.0737,2) + TMath::Power(1.01/TMath::Sqrt(et),2) + TMath::Power(1.74/et,2) ) )  ;
//     resEta  =  TMath::Sqrt( TMath::Power(0.00592,2) + TMath::Power(1.64/et,2) )  ;
//     resPhi  =  TMath::Sqrt( TMath::Power(0.00766,2) + TMath::Power(1.74/et,2) )  ;
//   }

//   else if (0.174 <= abseta and abseta < 0.261) {
//     resEt   = et * ( TMath::Sqrt( TMath::Power(0.0657,2) + TMath::Power(1.07/TMath::Sqrt(et),2) + TMath::Power(5.16e-06/et,2) ) )  ;
//     resEta  =  TMath::Sqrt( TMath::Power(0.00584,2) + TMath::Power(1.65/et,2) )  ;
//     resPhi  =  TMath::Sqrt( TMath::Power(0.00755,2) + TMath::Power(1.74/et,2) )  ;
//   }

//   else if (0.261 <= abseta and abseta < 0.348) {
//     resEt   = et * ( TMath::Sqrt( TMath::Power(0.062,2) + TMath::Power(1.07/TMath::Sqrt(et),2) +  TMath::Power(0.000134/et,2) ) )  ;
//     resEta  =  TMath::Sqrt( TMath::Power(0.00593,2) + TMath::Power(1.65/et,2) )  ;
//     resPhi  =  TMath::Sqrt( TMath::Power(0.00734,2) + TMath::Power(1.74/et,2) )  ;
//   }

//   else if (0.348 <= abseta and abseta < 0.435) {
//     resEt   = et * ( TMath::Sqrt( TMath::Power(0.0605,2) + TMath::Power(1.07/TMath::Sqrt(et),2) + TMath::Power(1.84e-07/et,2) ) )  ;
//     resEta  =  TMath::Sqrt( TMath::Power(0.00584,2) + TMath::Power(1.68/et,2) )  ;
//     resPhi  =  TMath::Sqrt( TMath::Power(0.00734,2) + TMath::Power(1.75/et,2) )  ;
//   }

//   else if (0.435 <= abseta and abseta < 0.522) {
//     resEt   = et * ( TMath::Sqrt( TMath::Power(0.059,2) + TMath::Power(1.08/TMath::Sqrt(et),2) + TMath::Power(9.06e-09/et,2) ) )  ;
//     resEta  =  TMath::Sqrt( TMath::Power(0.00646,2) + TMath::Power(1.67/et,2) )  ;
//     resPhi  =  TMath::Sqrt( TMath::Power(0.00767,2) + TMath::Power(1.74/et,2) )  ;
//   }

//   else if (0.522 <= abseta and abseta < 0.609) {
//     resEt   = et * ( TMath::Sqrt( TMath::Power(0.0577,2) + TMath::Power(1.08/TMath::Sqrt(et),2) + TMath::Power(5.46e-06/et,2) ) )  ;
//     resEta  =  TMath::Sqrt( TMath::Power(0.00661,2) + TMath::Power(1.67/et,2) )  ;
//     resPhi  =  TMath::Sqrt( TMath::Power(0.00742,2) + TMath::Power(1.75/et,2) )  ;
//   }

//   else if (0.609 <= abseta and abseta < 0.696) {
//     resEt   = et * ( TMath::Sqrt( TMath::Power(0.0525,2) + TMath::Power(1.09/TMath::Sqrt(et),2) + TMath::Power(4.05e-05/et,2) ) )  ;
//     resEta  =  TMath::Sqrt( TMath::Power(0.00724,2) + TMath::Power(1.65/et,2) )  ;
//     resPhi  =  TMath::Sqrt( TMath::Power(0.00771,2) + TMath::Power(1.73/et,2) )  ;
//   }

//   else if (0.696 <= abseta and abseta < 0.783) {
//     resEt   = et * ( TMath::Sqrt( TMath::Power(0.0582,2) + TMath::Power(1.09/TMath::Sqrt(et),2) + TMath::Power(1.17e-05/et,2) ) )  ;
//     resEta  =  TMath::Sqrt( TMath::Power(0.00763,2) + TMath::Power(1.67/et,2) )  ;
//     resPhi  =  TMath::Sqrt( TMath::Power(0.00758,2) + TMath::Power(1.76/et,2) )  ;
//   }

//   else if (0.783 <= abseta and abseta < 0.870) {
//     resEt   = et * ( TMath::Sqrt( TMath::Power(0.0649,2) + TMath::Power(1.08/TMath::Sqrt(et),2) + TMath::Power(7.85e-06/et,2) ) )  ;
//     resEta  =  TMath::Sqrt( TMath::Power(0.00746,2) + TMath::Power(1.7/et,2) )  ;
//     resPhi  =  TMath::Sqrt( TMath::Power(0.00789,2) + TMath::Power(1.75/et,2) )  ;
//   }

//   else if (0.870 <= abseta and abseta < 0.957) {
//     resEt   = et * ( TMath::Sqrt( TMath::Power(0.0654,2) + TMath::Power(1.1/TMath::Sqrt(et),2) + TMath::Power(1.09e-07/et,2) ) )  ;
//     resEta  =  TMath::Sqrt( TMath::Power(0.00807,2) + TMath::Power(1.7/et,2) )  ;
//     resPhi  =  TMath::Sqrt( TMath::Power(0.00802,2) + TMath::Power(1.76/et,2) )  ;
//   }

//   else if (0.957 <= abseta and abseta < 1.044) {
//     resEt   = et * ( TMath::Sqrt( TMath::Power(0.0669,2) + TMath::Power(1.11/TMath::Sqrt(et),2) + TMath::Power(1.87e-06/et,2) ) )  ;
//     resEta  =  TMath::Sqrt( TMath::Power(0.00843,2) + TMath::Power(1.72/et,2) )  ;
//     resPhi  =  TMath::Sqrt( TMath::Power(0.0078,2) + TMath::Power(1.79/et,2) )  ;
//   }

//   else if (1.044 <= abseta and abseta < 1.131) {
//     resEt   = et * ( TMath::Sqrt( TMath::Power(0.0643,2) + TMath::Power(1.15/TMath::Sqrt(et),2) + TMath::Power(2.76e-05/et,2) ) )  ;
//     resEta  =  TMath::Sqrt( TMath::Power(0.00886,2) + TMath::Power(1.74/et,2) )  ;
//     resPhi  =  TMath::Sqrt( TMath::Power(0.00806,2) + TMath::Power(1.82/et,2) )  ;
//   }

//   else if (1.131 <= abseta and abseta < 1.218) {
//     resEt   = et * ( TMath::Sqrt( TMath::Power(0.0645,2) + TMath::Power(1.16/TMath::Sqrt(et),2) + TMath::Power(1.04e-06/et,2) ) )  ;
//     resEta  =  TMath::Sqrt( TMath::Power(0.0101,2) + TMath::Power(1.76/et,2) )  ;
//     resPhi  =  TMath::Sqrt( TMath::Power(0.00784,2) + TMath::Power(1.86/et,2) )  ;
//   }

//   else if (1.218 <= abseta and abseta < 1.305) {
//     resEt   = et * ( TMath::Sqrt( TMath::Power(0.0637,2) + TMath::Power(1.19/TMath::Sqrt(et),2) + TMath::Power(1.08e-07/et,2) ) )  ;
//     resEta  =  TMath::Sqrt( TMath::Power(0.0127,2) + TMath::Power(1.78/et,2) )  ;
//     resPhi  =  TMath::Sqrt( TMath::Power(0.00885,2) + TMath::Power(1.9/et,2) )  ;
//   }

//   else if (1.305 <= abseta and abseta < 1.392) {
//     resEt   = et * ( TMath::Sqrt( TMath::Power(0.0695,2) + TMath::Power(1.21/TMath::Sqrt(et),2) + TMath::Power(5.75e-06/et,2) ) )  ;
//     resEta  =  TMath::Sqrt( TMath::Power(0.0161,2) + TMath::Power(1.73/et,2) )  ;
//     resPhi  =  TMath::Sqrt( TMath::Power(0.0108,2) + TMath::Power(1.93/et,2) )  ;
//   }

//   else if (1.392 <= abseta and abseta < 1.479) {
//     resEt   = et * ( TMath::Sqrt( TMath::Power(0.0748,2) + TMath::Power(1.2/TMath::Sqrt(et),2) + TMath::Power(5.15e-08/et,2) ) )  ;
//     resEta  =  TMath::Sqrt( TMath::Power(0.0122,2) + TMath::Power(1.77/et,2) )  ;
//     resPhi  =  TMath::Sqrt( TMath::Power(0.0112,2) + TMath::Power(2/et,2) )  ;
//   }

//   else if (1.479 <= abseta and abseta < 1.566) {
//     resEt   = et * ( TMath::Sqrt( TMath::Power(0.0624,2) + TMath::Power(1.23/TMath::Sqrt(et),2) + TMath::Power(2.28e-05/et,2) ) )  ;
//     resEta  =  TMath::Sqrt( TMath::Power(0.0123,2) + TMath::Power(1.79/et,2) )  ;
//     resPhi  =  TMath::Sqrt( TMath::Power(0.0102,2) + TMath::Power(2.02/et,2) )  ;
//   }

//   else if (1.566 <= abseta and abseta < 1.653) {
//     resEt   = et * ( TMath::Sqrt( TMath::Power(0.0283,2) + TMath::Power(1.25/TMath::Sqrt(et),2) + TMath::Power(4.79e-07/et,2) ) )  ;
//     resEta  =  TMath::Sqrt( TMath::Power(0.0111,2) + TMath::Power(1.79/et,2) )  ;
//     resPhi  =  TMath::Sqrt( TMath::Power(0.00857,2) + TMath::Power(2.01/et,2) )  ;
//   }

//   else if (1.653 <= abseta and abseta < 1.740) {
//     resEt   = et * ( TMath::Sqrt( TMath::Power(0.0316,2) + TMath::Power(1.21/TMath::Sqrt(et),2) + TMath::Power(5e-05/et,2) ) )  ;
//     resEta  =  TMath::Sqrt( TMath::Power(0.0106,2) + TMath::Power(1.8/et,2) )  ;
//     resPhi  =  TMath::Sqrt( TMath::Power(0.00856,2) + TMath::Power(1.97/et,2) )  ;
//   }

//   else if (1.740 <= abseta and abseta < 1.830) {
//     resEt   = et * ( TMath::Sqrt( TMath::Power(2.29e-07,2) + TMath::Power(1.2/TMath::Sqrt(et),2) + TMath::Power(1.71e-05/et,2) ) )  ;
//     resEta  =  TMath::Sqrt( TMath::Power(0.0115,2) + TMath::Power(1.83/et,2) )  ;
//     resPhi  =  TMath::Sqrt( TMath::Power(0.00761,2) + TMath::Power(1.95/et,2) )  ;
//   }

//   else if (1.830 <= abseta and abseta < 1.930) {
//     resEt   = et * ( TMath::Sqrt( TMath::Power(5.18e-09,2) + TMath::Power(1.14/TMath::Sqrt(et),2) + TMath::Power(1.7/et,2) ) )  ;
//     resEta  =  TMath::Sqrt( TMath::Power(0.012,2) + TMath::Power(1.88/et,2) )  ;
//     resPhi  =  TMath::Sqrt( TMath::Power(0.00721,2) + TMath::Power(1.92/et,2) )  ;
//   }

//   else if (1.930 <= abseta and abseta < 2.043) {
//     resEt   = et * ( TMath::Sqrt( TMath::Power(2.17e-07,2) + TMath::Power(1.09/TMath::Sqrt(et),2) + TMath::Power(2.08/et,2) ) )  ;
//     resEta  =  TMath::Sqrt( TMath::Power(0.0131,2) + TMath::Power(1.91/et,2) )  ;
//     resPhi  =  TMath::Sqrt( TMath::Power(0.00722,2) + TMath::Power(1.86/et,2) )  ;
//   }

//   else if (2.043 <= abseta and abseta < 2.172) {
//     resEt   = et * ( TMath::Sqrt( TMath::Power(3.65e-07,2) + TMath::Power(1.09/TMath::Sqrt(et),2) + TMath::Power(1.63/et,2) ) )  ;
//     resEta  =  TMath::Sqrt( TMath::Power(0.0134,2) + TMath::Power(1.92/et,2) )  ;
//     resPhi  =  TMath::Sqrt( TMath::Power(0.00703,2) + TMath::Power(1.86/et,2) )  ;
//   }

//   else if (2.172 <= abseta and abseta < 2.322) {
//     resEt   = et * ( TMath::Sqrt( TMath::Power(2.02e-07,2) + TMath::Power(1.09/TMath::Sqrt(et),2) + TMath::Power(1.68/et,2) ) )  ;
//     resEta  =  TMath::Sqrt( TMath::Power(0.0132,2) + TMath::Power(1.89/et,2) )  ;
//     resPhi  =  TMath::Sqrt( TMath::Power(0.00845,2) + TMath::Power(1.86/et,2) )  ;
//   }

//   else if (2.322 <= abseta and abseta < 2.500) {
//     resEt   = et * ( TMath::Sqrt( TMath::Power(5.27e-07,2) + TMath::Power(1.12/TMath::Sqrt(et),2) + TMath::Power(1.78/et,2) ) )  ;
//     resEta  =  TMath::Sqrt( TMath::Power(0.0121,2) + TMath::Power(2.28/et,2) )  ;
//     resPhi  =  TMath::Sqrt( TMath::Power(0.00975,2) + TMath::Power(2/et,2) )  ;        
//   }

//   return true;
// }

// int muonResolution(double et, double eta, double& resEt, double& resEta, double& resPhi)
// {

//   double abseta = fabs(eta) ;
  

//   if ( 0.000 <= abseta and abseta < 0.100 ) {
//     resEt   = et * (0.00517 + 0.000143 * et) ;
//     resEta  = TMath::Sqrt( TMath::Power(0.000433,2) + TMath::Power(0.000161/TMath::Sqrt(et),2) + TMath::Power(0.00334/et,2) ) ; 
//     resPhi  = TMath::Sqrt( TMath::Power(7.21e-05,2) + TMath::Power(7e-05/TMath::Sqrt(et),2) + TMath::Power(0.00296/et,2) ) ; 
//   }

//   else if ( 0.100 <= abseta and abseta < 0.200 ) {
//     resEt   = et * (0.00524 + 0.000143 * et); 
//     resEta  = TMath::Sqrt( TMath::Power(0.000381,2) + TMath::Power(0.000473/TMath::Sqrt(et),2) + TMath::Power(0.00259/et,2) ) ; 
//     resPhi  = TMath::Sqrt( TMath::Power(6.79e-05,2) + TMath::Power(0.000245/TMath::Sqrt(et),2) + TMath::Power(0.00274/et,2) ) ; 
//   }

//   else if ( 0.200 <= abseta and abseta < 0.300 ) {
//     resEt   = et * (0.00585 + 0.000138 * et); 
//     resEta  = TMath::Sqrt( TMath::Power(0.000337,2) + TMath::Power(0.000381/TMath::Sqrt(et),2) + TMath::Power(0.0023/et,2) ) ; 
//     resPhi  = TMath::Sqrt( TMath::Power(7.08e-05,2) + TMath::Power(6.75e-05/TMath::Sqrt(et),2) + TMath::Power(0.00307/et,2) ) ; 
//   }

//   else if ( 0.300 <= abseta and abseta < 0.400 ) {
//     resEt   = et * (0.0065 + 0.000133 * et); 
//     resEta  = TMath::Sqrt( TMath::Power(0.000308,2) + TMath::Power(0.000166/TMath::Sqrt(et),2) + TMath::Power(0.00249/et,2) ) ; 
//     resPhi  = TMath::Sqrt( TMath::Power(6.59e-05,2) + TMath::Power(0.000301/TMath::Sqrt(et),2) + TMath::Power(0.00281/et,2) ) ; 
//   }

//   else if ( 0.400 <= abseta and abseta < 0.500 ) {
//     resEt   = et * (0.0071 + 0.000129 * et); 
//     resEta  = TMath::Sqrt( TMath::Power(0.000289,2) + TMath::Power(5.37e-09/TMath::Sqrt(et),2) + TMath::Power(0.00243/et,2) ) ; 
//     resPhi  = TMath::Sqrt( TMath::Power(6.27e-05,2) + TMath::Power(0.000359/TMath::Sqrt(et),2) + TMath::Power(0.00278/et,2) ) ; 
//   }

//   else if ( 0.500 <= abseta and abseta < 0.600 ) {
//     resEt   = et * (0.00721 + 0.00013 * et); 
//     resEta  = TMath::Sqrt( TMath::Power(0.000279,2) + TMath::Power(0.000272/TMath::Sqrt(et),2) + TMath::Power(0.0026/et,2) ) ; 
//     resPhi  = TMath::Sqrt( TMath::Power(6.46e-05,2) + TMath::Power(0.00036/TMath::Sqrt(et),2) + TMath::Power(0.00285/et,2) ) ; 
//   }

//   else if ( 0.600 <= abseta and abseta < 0.700 ) {
//     resEt   = et * (0.00757 + 0.000129 * et); 
//     resEta  = TMath::Sqrt( TMath::Power(0.000282,2) + TMath::Power(3.63e-10/TMath::Sqrt(et),2) + TMath::Power(0.00288/et,2) ) ; 
//     resPhi  = TMath::Sqrt( TMath::Power(6.54e-05,2) + TMath::Power(0.000348/TMath::Sqrt(et),2) + TMath::Power(0.00301/et,2) ) ; 
//   }

//   else if ( 0.700 <= abseta and abseta < 0.800 ) {
//     resEt   = et * (0.0081 + 0.000127 * et); 
//     resEta  = TMath::Sqrt( TMath::Power(0.000265,2) + TMath::Power(0.000609/TMath::Sqrt(et),2) + TMath::Power(0.00212/et,2) ) ; 
//     resPhi  = TMath::Sqrt( TMath::Power(6.2e-05,2) + TMath::Power(0.000402/TMath::Sqrt(et),2) + TMath::Power(0.00304/et,2) ) ; 
//   }

//   else if ( 0.800 <= abseta and abseta < 0.900 ) {
//     resEt   = et * (0.00916 + 0.000131 * et); 
//     resEta  = TMath::Sqrt( TMath::Power(0.000241,2) + TMath::Power(0.000678/TMath::Sqrt(et),2) + TMath::Power(0.00221/et,2) ) ; 
//     resPhi  = TMath::Sqrt( TMath::Power(6.26e-05,2) + TMath::Power(0.000458/TMath::Sqrt(et),2) + TMath::Power(0.0031/et,2) ) ; 
//   }

//   else if ( 0.900 <= abseta and abseta < 1.000 ) {
//     resEt   = et * (0.0108 + 0.000151 * et); 
//     resEta  = TMath::Sqrt( TMath::Power(0.000228,2) + TMath::Power(0.000612/TMath::Sqrt(et),2) + TMath::Power(0.00245/et,2) ) ; 
//     resPhi  = TMath::Sqrt( TMath::Power(7.18e-05,2) + TMath::Power(0.000469/TMath::Sqrt(et),2) + TMath::Power(0.00331/et,2) ) ; 
//   }

//   else if ( 1.000 <= abseta and abseta < 1.100 ) {
//     resEt   = et * (0.0115 + 0.000153 * et); 
//     resEta  = TMath::Sqrt( TMath::Power(0.000217,2) + TMath::Power(0.000583/TMath::Sqrt(et),2) + TMath::Power(0.00307/et,2) ) ; 
//     resPhi  = TMath::Sqrt( TMath::Power(6.98e-05,2) + TMath::Power(0.000507/TMath::Sqrt(et),2) + TMath::Power(0.00338/et,2) ) ; 
//   }

//   else if ( 1.100 <= abseta and abseta < 1.200 ) {
//     resEt   = et * (0.013 + 0.000136 * et); 
//     resEta  = TMath::Sqrt( TMath::Power(0.000195,2) + TMath::Power(0.000751/TMath::Sqrt(et),2) + TMath::Power(0.00282/et,2) ) ; 
//     resPhi  = TMath::Sqrt( TMath::Power(6.21e-05,2) + TMath::Power(0.000584/TMath::Sqrt(et),2) + TMath::Power(0.00345/et,2) ) ; 
//   }

//   else if ( 1.200 <= abseta and abseta < 1.300 ) {
//     resEt   = et * (0.0144 + 0.000131 * et); 
//     resEta  = TMath::Sqrt( TMath::Power(0.000183,2) + TMath::Power(0.000838/TMath::Sqrt(et),2) + TMath::Power(0.00227/et,2) ) ; 
//     resPhi  = TMath::Sqrt( TMath::Power(5.37e-05,2) + TMath::Power(0.000667/TMath::Sqrt(et),2) + TMath::Power(0.00352/et,2) ) ; 
//   }

//   else if ( 1.300 <= abseta and abseta < 1.400 ) {
//     resEt   = et * (0.0149 + 0.000141 * et); 
//     resEta  = TMath::Sqrt( TMath::Power(0.000196,2) + TMath::Power(0.000783/TMath::Sqrt(et),2) + TMath::Power(0.00274/et,2) ) ; 
//     resPhi  = TMath::Sqrt( TMath::Power(5.37e-05,2) + TMath::Power(0.000711/TMath::Sqrt(et),2) + TMath::Power(0.00358/et,2) ) ; 
//   }

//   else if ( 1.400 <= abseta and abseta < 1.500 ) {
//     resEt   = et * (0.014 + 0.000155 * et); 
//     resEta  = TMath::Sqrt( TMath::Power(0.0002,2) + TMath::Power(0.000832/TMath::Sqrt(et),2) + TMath::Power(0.00254/et,2) ) ; 
//     resPhi  = TMath::Sqrt( TMath::Power(5.98e-05,2) + TMath::Power(0.000713/TMath::Sqrt(et),2) + TMath::Power(0.00362/et,2) ) ; 
//   }

//   else if ( 1.500 <= abseta and abseta < 1.600 ) {
//     resEt   = et * (0.0132 + 0.000169 * et); 
//     resEta  = TMath::Sqrt( TMath::Power(0.000205,2) + TMath::Power(0.0007/TMath::Sqrt(et),2) + TMath::Power(0.00304/et,2) ) ; 
//     resPhi  = TMath::Sqrt( TMath::Power(6.21e-05,2) + TMath::Power(0.000781/TMath::Sqrt(et),2) + TMath::Power(0.00348/et,2) ) ; 
//   }

//   else if ( 1.600 <= abseta and abseta < 1.700 ) {
//     resEt   = et * (0.0129 + 0.0002 * et); 
//     resEta  = TMath::Sqrt( TMath::Power(0.000214,2) + TMath::Power(0.000747/TMath::Sqrt(et),2) + TMath::Power(0.00319/et,2) ) ; 
//     resPhi  = TMath::Sqrt( TMath::Power(6.92e-05,2) + TMath::Power(0.000865/TMath::Sqrt(et),2) + TMath::Power(0.00337/et,2) ) ; 
//   }

//   else if ( 1.700 <= abseta and abseta < 1.800 ) {
//     resEt   = et * (0.0135 + 0.000264 * et); 
//     resEta  = TMath::Sqrt( TMath::Power(0.000238,2) + TMath::Power(0.000582/TMath::Sqrt(et),2) + TMath::Power(0.00343/et,2) ) ; 
//     resPhi  = TMath::Sqrt( TMath::Power(9.13e-05,2) + TMath::Power(0.000896/TMath::Sqrt(et),2) + TMath::Power(0.00348/et,2) ) ; 
//   }

//   else if ( 1.800 <= abseta and abseta < 1.900 ) {
//     resEt   = et * (0.0144 + 0.00034 * et); 
//     resEta  = TMath::Sqrt( TMath::Power(0.000263,2) + TMath::Power(0.000721/TMath::Sqrt(et),2) + TMath::Power(0.00322/et,2) ) ; 
//     resPhi  = TMath::Sqrt( TMath::Power(0.000102,2) + TMath::Power(0.000994/TMath::Sqrt(et),2) + TMath::Power(0.00337/et,2) ) ; 
//   }

//   else if ( 1.900 <= abseta and abseta < 2.000 ) {
//     resEt   = et * (0.0147 + 0.000441 * et); 
//     resEta  = TMath::Sqrt( TMath::Power(0.000284,2) + TMath::Power(0.000779/TMath::Sqrt(et),2) + TMath::Power(0.0031/et,2) ) ; 
//     resPhi  = TMath::Sqrt( TMath::Power(0.000123,2) + TMath::Power(0.00108/TMath::Sqrt(et),2) + TMath::Power(0.00315/et,2) ) ; 
//   }

//   else if ( 2.000 <= abseta and abseta < 2.100 ) {
//     resEt   = et * (0.0154 + 0.000604 * et); 
//     resEta  = TMath::Sqrt( TMath::Power(0.000316,2) + TMath::Power(0.000566/TMath::Sqrt(et),2) + TMath::Power(0.00384/et,2) ) ; 
//     resPhi  = TMath::Sqrt( TMath::Power(0.000169,2) + TMath::Power(0.000947/TMath::Sqrt(et),2) + TMath::Power(0.00422/et,2) ) ; 
//   }

//   else if ( 2.100 <= abseta and abseta < 2.200 ) {
//     resEt   = et * (0.0163 + 0.000764 * et); 
//     resEta  = TMath::Sqrt( TMath::Power(0.000353,2) + TMath::Power(0.000749/TMath::Sqrt(et),2) + TMath::Power(0.0038/et,2) ) ; 
//     resPhi  = TMath::Sqrt( TMath::Power(0.000176,2) + TMath::Power(0.00116/TMath::Sqrt(et),2) + TMath::Power(0.00423/et,2) ) ; 
//   }

//   else if ( 2.200 <= abseta and abseta < 2.300 ) {
//     resEt   = et * (0.0173 + 0.000951 * et); 
//     resEta  = TMath::Sqrt( TMath::Power(0.000412,2) + TMath::Power(0.00102/TMath::Sqrt(et),2) + TMath::Power(0.00351/et,2) ) ; 
//     resPhi  = TMath::Sqrt( TMath::Power(0.000207,2) + TMath::Power(0.00115/TMath::Sqrt(et),2) + TMath::Power(0.00469/et,2) ) ; 
//   }

//   else if ( 2.300 <= abseta and abseta < 2.400 ) {
//     resEt   = et * (0.0175 + 0.00126 * et); 
//     resEta  = TMath::Sqrt( TMath::Power(0.000506,2) + TMath::Power(0.000791/TMath::Sqrt(et),2) + TMath::Power(0.0045/et,2) ) ; 
//     resPhi  = TMath::Sqrt( TMath::Power(0.00027,2) + TMath::Power(0.00113/TMath::Sqrt(et),2) + TMath::Power(0.00528/et,2) ) ; 
//   }

//   return true;
// }

// int elecResolution(double et, double eta, double& resEt, double& resEta, double& resPhi)
// {

//   double abseta = fabs(eta) ;


//   if ( 0.000 <= abseta and abseta < 0.174 ) {
//     resEt   = et * TMath::Sqrt( TMath::Power(0.00534,2) + TMath::Power(0.079/TMath::Sqrt(et),2) + TMath::Power(0.163/et,2) ) ; 
//     resEta  = TMath::Sqrt( TMath::Power(0.000452,2) + TMath::Power(0.000285/TMath::Sqrt(et),2) + TMath::Power(0.00376/et,2) ) ; 
//     resPhi  = TMath::Sqrt( TMath::Power(0.000101,2) + TMath::Power(0.0011/TMath::Sqrt(et),2) + TMath::Power(0.00346/et,2) ) ; 
//   }

//   else if ( 0.174 <= abseta and abseta < 0.261 ) {
//     resEt   = et * TMath::Sqrt( TMath::Power(0.00518,2) + TMath::Power(0.0749/TMath::Sqrt(et),2) + TMath::Power(0.227/et,2) ) ; 
//     resEta  = TMath::Sqrt( TMath::Power(0.00038,2) + TMath::Power(0.000571/TMath::Sqrt(et),2) + TMath::Power(0.00276/et,2) ) ; 
//     resPhi  = TMath::Sqrt( TMath::Power(9.3e-05,2) + TMath::Power(0.00115/TMath::Sqrt(et),2) + TMath::Power(0.0035/et,2) ) ; 
//   }

//   else if ( 0.261 <= abseta and abseta < 0.348 ) {
//     resEt   = et * TMath::Sqrt( TMath::Power(0.00332,2) + TMath::Power(0.0879/TMath::Sqrt(et),2) + TMath::Power(0.12/et,2) ) ; 
//     resEta  = TMath::Sqrt( TMath::Power(0.000351,2) + TMath::Power(1.36e-09/TMath::Sqrt(et),2) + TMath::Power(0.00324/et,2) ) ; 
//     resPhi  = TMath::Sqrt( TMath::Power(0.000103,2) + TMath::Power(0.00117/TMath::Sqrt(et),2) + TMath::Power(0.00333/et,2) ) ; 
//   }

//   else if ( 0.348 <= abseta and abseta < 0.435 ) {
//     resEt   = et * TMath::Sqrt( TMath::Power(0.00445,2) + TMath::Power(0.0895/TMath::Sqrt(et),2) + TMath::Power(0.186/et,2) ) ; 
//     resEta  = TMath::Sqrt( TMath::Power(0.000319,2) + TMath::Power(0.00061/TMath::Sqrt(et),2) + TMath::Power(0.00182/et,2) ) ; 
//     resPhi  = TMath::Sqrt( TMath::Power(0.00011,2) + TMath::Power(0.00115/TMath::Sqrt(et),2) + TMath::Power(0.00365/et,2) ) ; 
//   }

//   else if ( 0.435 <= abseta and abseta < 0.522 ) {
//     resEt   = et * TMath::Sqrt( TMath::Power(0.00453,2) + TMath::Power(0.0893/TMath::Sqrt(et),2) + TMath::Power(0.21/et,2) ) ; 
//     resEta  = TMath::Sqrt( TMath::Power(0.000301,2) + TMath::Power(0.000612/TMath::Sqrt(et),2) + TMath::Power(0.00146/et,2) ) ; 
//     resPhi  = TMath::Sqrt( TMath::Power(0.000105,2) + TMath::Power(0.00122/TMath::Sqrt(et),2) + TMath::Power(0.00343/et,2) ) ; 
//   }

//   else if ( 0.522 <= abseta and abseta < 0.609 ) {
//     resEt   = et * TMath::Sqrt( TMath::Power(0.00308,2) + TMath::Power(0.0886/TMath::Sqrt(et),2) + TMath::Power(0.188/et,2) ) ; 
//     resEta  = TMath::Sqrt( TMath::Power(0.000297,2) + TMath::Power(0.000791/TMath::Sqrt(et),2) + TMath::Power(2.09e-08/et,2) ) ; 
//     resPhi  = TMath::Sqrt( TMath::Power(0.000102,2) + TMath::Power(0.00129/TMath::Sqrt(et),2) + TMath::Power(0.00328/et,2) ) ; 
//   }

//   else if ( 0.609 <= abseta and abseta < 0.696 ) {
//     resEt   = et * TMath::Sqrt( TMath::Power(0.00308,2) + TMath::Power(0.0914/TMath::Sqrt(et),2) + TMath::Power(0.182/et,2) ) ; 
//     resEta  = TMath::Sqrt( TMath::Power(0.00032,2) + TMath::Power(0.000329/TMath::Sqrt(et),2) + TMath::Power(0.00325/et,2) ) ; 
//     resPhi  = TMath::Sqrt( TMath::Power(0.000103,2) + TMath::Power(0.00139/TMath::Sqrt(et),2) + TMath::Power(0.00253/et,2) ) ; 
//   }

//   else if ( 0.696 <= abseta and abseta < 0.783 ) {
//     resEt   = et * TMath::Sqrt( TMath::Power(0.00442,2) + TMath::Power(0.0914/TMath::Sqrt(et),2) + TMath::Power(0.231/et,2) ) ; 
//     resEta  = TMath::Sqrt( TMath::Power(0.000309,2) + TMath::Power(0.000821/TMath::Sqrt(et),2) + TMath::Power(0.00119/et,2) ) ; 
//     resPhi  = TMath::Sqrt( TMath::Power(0.000115,2) + TMath::Power(0.00139/TMath::Sqrt(et),2) + TMath::Power(0.00293/et,2) ) ; 
//   }

//   else if ( 0.783 <= abseta and abseta < 0.870 ) {
//     resEt   = et * TMath::Sqrt( TMath::Power(0.00455,2) + TMath::Power(0.0949/TMath::Sqrt(et),2) + TMath::Power(0.335/et,2) ) ; 
//     resEta  = TMath::Sqrt( TMath::Power(0.000293,2) + TMath::Power(0.000767/TMath::Sqrt(et),2) + TMath::Power(0.00211/et,2) ) ; 
//     resPhi  = TMath::Sqrt( TMath::Power(0.000121,2) + TMath::Power(0.00158/TMath::Sqrt(et),2) + TMath::Power(0.00151/et,2) ) ; 
//   }

//   else if ( 0.870 <= abseta and abseta < 0.957 ) {
//     resEt   = et * TMath::Sqrt( TMath::Power(0.00181,2) + TMath::Power(0.102/TMath::Sqrt(et),2) + TMath::Power(0.333/et,2) ) ; 
//     resEta  = TMath::Sqrt( TMath::Power(0.000275,2) + TMath::Power(0.000765/TMath::Sqrt(et),2) + TMath::Power(0.00227/et,2) ) ; 
//     resPhi  = TMath::Sqrt( TMath::Power(0.000128,2) + TMath::Power(0.00169/TMath::Sqrt(et),2) + TMath::Power(1.93e-08/et,2) ) ; 
//   }

//   else if ( 0.957 <= abseta and abseta < 1.044 ) {
//     resEt   = et * TMath::Sqrt( TMath::Power(0.000764,2) + TMath::Power(0.108/TMath::Sqrt(et),2) + TMath::Power(0.42/et,2) ) ; 
//     resEta  = TMath::Sqrt( TMath::Power(0.000274,2) + TMath::Power(0.000622/TMath::Sqrt(et),2) + TMath::Power(0.00299/et,2) ) ; 
//     resPhi  = TMath::Sqrt( TMath::Power(0.000145,2) + TMath::Power(0.00179/TMath::Sqrt(et),2) + TMath::Power(1.69e-08/et,2) ) ; 
//   }

//   else if ( 1.044 <= abseta and abseta < 1.131 ) {
//     resEt   = et * TMath::Sqrt( TMath::Power(0.00114,2) + TMath::Power(0.128/TMath::Sqrt(et),2) + TMath::Power(0.55/et,2) ) ; 
//     resEta  = TMath::Sqrt( TMath::Power(0.000269,2) + TMath::Power(0.000929/TMath::Sqrt(et),2) + TMath::Power(0.00183/et,2) ) ; 
//     resPhi  = TMath::Sqrt( TMath::Power(0.000185,2) + TMath::Power(0.00182/TMath::Sqrt(et),2) + TMath::Power(2.99e-09/et,2) ) ; 
//   }

//   else if ( 1.131 <= abseta and abseta < 1.218 ) {
//     resEt   = et * TMath::Sqrt( TMath::Power(4.14e-09,2) + TMath::Power(0.155/TMath::Sqrt(et),2) + TMath::Power(0.674/et,2) ) ; 
//     resEta  = TMath::Sqrt( TMath::Power(0.000268,2) + TMath::Power(0.000876/TMath::Sqrt(et),2) + TMath::Power(0.00234/et,2) ) ; 
//     resPhi  = TMath::Sqrt( TMath::Power(0.000194,2) + TMath::Power(0.002/TMath::Sqrt(et),2) + TMath::Power(2.39e-08/et,2) ) ; 
//   }

//   else if ( 1.218 <= abseta and abseta < 1.305 ) {
//     resEt   = et * TMath::Sqrt( TMath::Power(8.03e-09,2) + TMath::Power(0.144/TMath::Sqrt(et),2) + TMath::Power(0.8/et,2) ) ; 
//     resEta  = TMath::Sqrt( TMath::Power(0.000258,2) + TMath::Power(0.000782/TMath::Sqrt(et),2) + TMath::Power(0.00246/et,2) ) ; 
//     resPhi  = TMath::Sqrt( TMath::Power(0.000226,2) + TMath::Power(0.00206/TMath::Sqrt(et),2) + TMath::Power(5.88e-08/et,2) ) ; 
//   }

//   else if ( 1.305 <= abseta and abseta < 1.392 ) {
//     resEt   = et * TMath::Sqrt( TMath::Power(0.00842,2) + TMath::Power(0.118/TMath::Sqrt(et),2) + TMath::Power(0.951/et,2) ) ; 
//     resEta  = TMath::Sqrt( TMath::Power(0.000269,2) + TMath::Power(0.000817/TMath::Sqrt(et),2) + TMath::Power(0.00278/et,2) ) ; 
//     resPhi  = TMath::Sqrt( TMath::Power(0.000247,2) + TMath::Power(0.00225/TMath::Sqrt(et),2) + TMath::Power(1.47e-09/et,2) ) ; 
//   }

//   else if ( 1.392 <= abseta and abseta < 1.479 ) {
//     resEt   = et * TMath::Sqrt( TMath::Power(0.00684,2) + TMath::Power(0.144/TMath::Sqrt(et),2) + TMath::Power(0.892/et,2) ) ; 
//     resEta  = TMath::Sqrt( TMath::Power(0.000267,2) + TMath::Power(0.000734/TMath::Sqrt(et),2) + TMath::Power(0.00327/et,2) ) ; 
//     resPhi  = TMath::Sqrt( TMath::Power(0.000234,2) + TMath::Power(0.00233/TMath::Sqrt(et),2) + TMath::Power(4.92e-09/et,2) ) ; 
//   }

//   else if ( 1.479 <= abseta and abseta < 1.653 ) {
//     resEt   = et * TMath::Sqrt( TMath::Power(0.0245,2) + TMath::Power(0.196/TMath::Sqrt(et),2) + TMath::Power(0.555/et,2) ) ; 
//     resEta  = TMath::Sqrt( TMath::Power(0.000268,2) + TMath::Power(0.000757/TMath::Sqrt(et),2) + TMath::Power(0.00295/et,2) ) ; 
//     resPhi  = TMath::Sqrt( TMath::Power(0.00025,2) + TMath::Power(0.00268/TMath::Sqrt(et),2) + TMath::Power(7.5e-09/et,2) ) ; 
//   }

//   else if ( 1.653 <= abseta and abseta < 1.740 ) {
//     resEt   = et * TMath::Sqrt( TMath::Power(0.0174,2) + TMath::Power(0.127/TMath::Sqrt(et),2) + TMath::Power(0.894/et,2) ) ; 
//     resEta  = TMath::Sqrt( TMath::Power(0.000274,2) + TMath::Power(1.77e-09/TMath::Sqrt(et),2) + TMath::Power(0.00435/et,2) ) ; 
//     resPhi  = TMath::Sqrt( TMath::Power(0.000284,2) + TMath::Power(0.00275/TMath::Sqrt(et),2) + TMath::Power(6.56e-09/et,2) ) ; 
//   }

//   else if ( 1.740 <= abseta and abseta < 1.830 ) {
//     resEt   = et * TMath::Sqrt( TMath::Power(0.0144,2) + TMath::Power(0.133/TMath::Sqrt(et),2) + TMath::Power(0.708/et,2) ) ; 
//     resEta  = TMath::Sqrt( TMath::Power(0.000274,2) + TMath::Power(0.00101/TMath::Sqrt(et),2) + TMath::Power(0.000982/et,2) ) ; 
//     resPhi  = TMath::Sqrt( TMath::Power(0.000356,2) + TMath::Power(0.00279/TMath::Sqrt(et),2) + TMath::Power(0.00261/et,2) ) ; 
//   }

//   else if ( 1.830 <= abseta and abseta < 1.930 ) {
//     resEt   = et * TMath::Sqrt( TMath::Power(0.0149,2) + TMath::Power(0.126/TMath::Sqrt(et),2) + TMath::Power(0.596/et,2) ) ; 
//     resEta  = TMath::Sqrt( TMath::Power(0.000299,2) + TMath::Power(0.000686/TMath::Sqrt(et),2) + TMath::Power(0.00341/et,2) ) ; 
//     resPhi  = TMath::Sqrt( TMath::Power(0.000347,2) + TMath::Power(0.00298/TMath::Sqrt(et),2) + TMath::Power(1.02e-08/et,2) ) ; 
//   }

//   else if ( 1.930 <= abseta and abseta < 2.043 ) {
//     resEt   = et * TMath::Sqrt( TMath::Power(0.0143,2) + TMath::Power(0.12/TMath::Sqrt(et),2) + TMath::Power(0.504/et,2) ) ; 
//     resEta  = TMath::Sqrt( TMath::Power(0.000329,2) + TMath::Power(3.05e-10/TMath::Sqrt(et),2) + TMath::Power(0.00439/et,2) ) ; 
//     resPhi  = TMath::Sqrt( TMath::Power(0.000302,2) + TMath::Power(0.00322/TMath::Sqrt(et),2) + TMath::Power(5.22e-08/et,2) ) ; 
//   }

//   else if ( 2.043 <= abseta and abseta < 2.172 ) {
//     resEt   = et * TMath::Sqrt( TMath::Power(0.0162,2) + TMath::Power(0.0965/TMath::Sqrt(et),2) + TMath::Power(0.483/et,2) ) ; 
//     resEta  = TMath::Sqrt( TMath::Power(0.00037,2) + TMath::Power(1.32e-08/TMath::Sqrt(et),2) + TMath::Power(0.00447/et,2) ) ; 
//     resPhi  = TMath::Sqrt( TMath::Power(0.000287,2) + TMath::Power(0.00349/TMath::Sqrt(et),2) + TMath::Power(3e-11/et,2) ) ; 
//   }

//   else if ( 2.172 <= abseta and abseta < 2.322 ) {
//     resEt   = et * TMath::Sqrt( TMath::Power(0.0122,2) + TMath::Power(0.13/TMath::Sqrt(et),2) + TMath::Power(0.207/et,2) ) ; 
//     resEta  = TMath::Sqrt( TMath::Power(0.000442,2) + TMath::Power(4.03e-10/TMath::Sqrt(et),2) + TMath::Power(0.00544/et,2) ) ; 
//     resPhi  = TMath::Sqrt( TMath::Power(0.000214,2) + TMath::Power(0.00436/TMath::Sqrt(et),2) + TMath::Power(2.98e-09/et,2) ) ; 
//   }

//   else if ( 2.322 <= abseta and abseta < 2.500 ) {
//     resEt   = et * TMath::Sqrt( TMath::Power(0.0145,2) + TMath::Power(0.127/TMath::Sqrt(et),2) + TMath::Power(0.0782/et,2) ) ; 
//     resEta  = TMath::Sqrt( TMath::Power(0.000577,2) + TMath::Power(0.000768/TMath::Sqrt(et),2) + TMath::Power(0.00331/et,2) ) ; 
//     resPhi  = TMath::Sqrt( TMath::Power(8.02e-05,2) + TMath::Power(0.00525/TMath::Sqrt(et),2) + TMath::Power(0.00581/et,2) ) ; 
//   }


//   return true;
// }
