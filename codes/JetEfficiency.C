/**********************************************************************
 Created on : 12/10/2022
 Purpose    : Study the efficiency of Jet reconstruction
 Author     : Indranil Das, Visiting Fellow, TIFR
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

#include "TParticlePDG.h"
#include "TDatabasePDG.h"

#include "TLorentzVector.h"
#include "TVector3.h"

#include "TEfficiency.h"

int JetEfficiency()
{

  TFile *fin = TFile::Open("/run/media/indra/DHEP_Storage_3/Data/NanoAOD/Skim_NanoAODUL/2016/TTbarPowheg_Semilept_postVFP_Skim_NanoAOD_1of27.root");
  // //TFile *fin = TFile::Open("/run/media/indra/DHEP_Storage_3/Data/NanoAOD/Skim_NanoAODUL/2016/Wjets_postVFP_Skim_NanoAOD_5of13.root");
  // //TFile *fin = TFile::Open("/run/media/indra/DHEP_Storage_3/Data/NanoAOD/Raw_NanoAOD/2016/TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8__RunIISummer20UL16NanoAODv9__106X_mcRun2_asymptotic_v17-v1__120000__38728C1E-8B09-954D-8F53-FD7D939FFFBE.root");
  TTree *tree = (TTree *)fin->Get("Events");


  
  UInt_t    nGenJet_;  
  Float_t   GenJet_pt_[100];
  Float_t   GenJet_eta_[100];
  Float_t   GenJet_phi_[100];
  Float_t   GenJet_mass_[100];
  Int_t   GenJet_partonFlavour_[100];
  Int_t   GenJet_hadronFlavour_[100];
  Bool_t  HLT_AK4CaloJet30_;
  Bool_t  HLT_AK4CaloJet40_;
  Bool_t  HLT_AK4CaloJet50_;
  Bool_t  HLT_AK4CaloJet80_;
  Bool_t  HLT_AK4CaloJet100_;

  // Jet
  UInt_t          nJet_;
  Float_t         jetPt_[200];
  Float_t         jetEta_[200];
  Float_t         jetPhi_[200];
  Float_t         jetMass_[200];
  Int_t           jetHadFlvr_[200];
  Int_t           jetPartFlvr_[200];
  Int_t           jetGenJetIdx_[200];

  
  ///////////////////////////////////////////////////////////////////////////
  tree->SetBranchStatus("*",0);
  // // /////////////////////////////////////////////////////////////////////////////
  // tree->SetBranchStatus("HLT_AK4CaloJet30",1);
  // tree->SetBranchAddress("HLT_AK4CaloJet30", &HLT_AK4CaloJet30_);

  // tree->SetBranchStatus("HLT_AK4CaloJet40",1);
  // tree->SetBranchAddress("HLT_AK4CaloJet40", &HLT_AK4CaloJet40_);

  // tree->SetBranchStatus("HLT_AK4CaloJet50",1);
  // tree->SetBranchAddress("HLT_AK4CaloJet50", &HLT_AK4CaloJet50_);

  // tree->SetBranchStatus("HLT_AK4CaloJet80",1);
  // tree->SetBranchAddress("HLT_AK4CaloJet80", &HLT_AK4CaloJet80_);

  // tree->SetBranchStatus("HLT_AK4CaloJet100",1);
  // tree->SetBranchAddress("HLT_AK4CaloJet100", &HLT_AK4CaloJet100_);

  // /////////////////////////////////////////////////////////////////////////////
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

  TH1F **hGenPt,**hRecPt, **hDelR; 
  TEfficiency **hEff;
  int nFlav = 7;
  hGenPt = new TH1F*[nFlav];
  hRecPt = new TH1F*[nFlav];
  hDelR = new TH1F*[nFlav];
  hEff = new TEfficiency*[nFlav];
  for(int ifl=0;ifl<nFlav;ifl++){
    TParticlePDG *partPDG = TDatabasePDG::Instance()->GetParticle(ifl);
    if(ifl==0) partPDG->SetTitle("undefined");
    if(ifl!=(nFlav-1)){
      hGenPt[ifl] = new TH1F(Form("hGenPt_%d",ifl),Form("GenJetPt for GenFlav : %d(%s quark)",ifl,partPDG->GetName()), 1000, 0., 100.);
      hRecPt[ifl] = new TH1F(Form("hRecPt_%d",ifl),Form("RecJetPt for GenFlav : %d(%s quark)",ifl,partPDG->GetName()), 1000, 0., 100.);
      hDelR[ifl] = new TH1F(Form("hDelR_%d",ifl),Form("DelR for GenFlav : %d(%s quark)",ifl,partPDG->GetName()), 100, 0., 1.0);
      hEff[ifl] = new TEfficiency(Form("hEff_%d",ifl),Form("Efficiency for GenFlav : %d(%s quark);#it{p}_{T} GeV/#it{c};#epsilon",ifl,partPDG->GetName()), 1000, 0., 100.);
    }else{
      hGenPt[ifl] = new TH1F(Form("hGenPt_%d",ifl),Form("GenJetPt for GenFlav : 21(gluon)"), 1000, 0., 100.);
      hRecPt[ifl] = new TH1F(Form("hRecPt_%d",ifl),Form("RecJetPt for GenFlav : 21(gluon)"), 1000, 0., 100.);
      hDelR[ifl] = new TH1F(Form("hDelR_%d",ifl),Form("DelR for GenFlav : 21(gluon)"), 100, 0., 1.0);
      hEff[ifl] = new TEfficiency(Form("hEff_%d",ifl),Form("Efficiency for GenFlav : 21(gluon);#it{p}_{T} GeV/#it{c};#epsilon"), 1000, 0., 100.);
    }
    //The default Statistic option is frequentist
    //kFCP (=0)(default): using the Clopper-Pearson interval (recommended by PDG) sets kIsBayesian = false see also ClopperPearson
    //One can try alternate Bayesian using the uniform prior as below
    //hEff[ifl]->SetStatisticOption(TEfficiency::kBUniform); //kBUniform (=6) : using a uniform prior sets kIsBayesian = true, fBeta_alpha = 1 and fBeta_beta = 1 see also Bayesian
    // See details at https://root.cern.ch/doc/master/classTEfficiency.html
  }

  
  TLorentzVector jetR, jetG; 
  float etaMin = 1.5, etaMax = 3.0; //corresponding to HGCAL

  cout << "Total Events : " <<  tree->GetEntries() << endl;
  for(int ievent=0; ievent<tree->GetEntries(); ievent++){
    
    tree->GetEntry(ievent);
    if(ievent%1000==0)
      printf("Processing Event : %d, nof GenJets : %u\n",ievent,nGenJet_);
    
    //if(HLT_AK4CaloJet30_ or HLT_AK4CaloJet40_ or HLT_AK4CaloJet50_ or HLT_AK4CaloJet80_ or HLT_AK4CaloJet100_){

      for(int genJetId = 0; genJetId < int(nGenJet_); ++genJetId){
	double jetEta = TMath::Abs(GenJet_eta_[genJetId]);
	if(jetEta<=etaMin or jetEta>=etaMax) continue;
      
	bool isMatch = false; float delR = 0.0;
	int flav = TMath::Abs(GenJet_partonFlavour_[genJetId]);
	//double recPt = 0.0;
	for(int jetInd = 0; jetInd < int(nJet_); ++jetInd){
	  int genIdx = int(jetGenJetIdx_[jetInd]);
	  if(genIdx==genJetId){
	    isMatch = true;
	    jetG.SetPtEtaPhiM(GenJet_pt_[genJetId], GenJet_eta_[genJetId] , GenJet_phi_[genJetId], GenJet_mass_[genJetId]);
	    jetR.SetPtEtaPhiM(jetPt_[jetInd], jetEta_[jetInd] , jetPhi_[jetInd], jetMass_[jetInd]);
	    delR = jetR.DeltaR(jetG);
	    if(flav!=21)
	      hRecPt[flav]->Fill(jetPt_[jetInd]);
	    else
	      hRecPt[(nFlav-1)]->Fill(jetPt_[jetInd]);
	  }//if Recojet matches with the current JenGet
	}//loop over Recojet
	//bool isEff = isMatch; //Default
	bool isEff = (delR<0.2) and isMatch; //Formal and Documented
	if(flav!=21){
	  hGenPt[flav]->Fill(GenJet_pt_[genJetId]);
	  hEff[flav]->Fill(isEff, GenJet_pt_[genJetId]);
	  if(isEff) hDelR[flav]->Fill(delR);
	}else{
	  hGenPt[(nFlav-1)]->Fill(GenJet_pt_[genJetId]);
	  hEff[(nFlav-1)]->Fill(isEff, GenJet_pt_[genJetId]);
	  if(isEff) hDelR[(nFlav-1)]->Fill(delR);
	}
      }//loop over genJet

      //}//HLT AK4 Calo condn

  }//event loop
  
  cout << "GetStatOption : " << hEff[0]->GetStatisticOption() << endl;

  TCanvas *c1 = new TCanvas("c1","c1");
  c1->Divide(4,2);
  for(int ifl=0;ifl<nFlav;ifl++){
    c1->cd(ifl+1);
    c1->cd(ifl+1)->SetGridx();
    c1->cd(ifl+1)->SetGridy();
    hEff[ifl]->Draw();
    //hEff[ifl]->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  }

  TCanvas *c2 = new TCanvas("c2","c2");
  c2->Divide(4,2);
  for(int ifl=0;ifl<nFlav;ifl++){
    c2->cd(ifl+1);
    c2->cd(ifl+1)->SetLogy();
    hDelR[ifl]->Draw();
    hDelR[ifl]->GetXaxis()->SetTitle("#DeltaR(recoJet,genJet)");
  }

  TFile *fout = new TFile("output.root","recreate");
  for(int ifl=0;ifl<nFlav;ifl++){
    hEff[ifl]->Write();
    hDelR[ifl]->Write();
  }
  return true;
}

