/**********************************************************************
 Created on : 01/08/2021
 Purpose    : Read the MC information from skim file.
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

#include <fstream>

using namespace std;

#endif

//int ReadMCInfoSkim(string infile = "/run/media/indra/DHEP_Storage_1/Data/NanoAOD/Skim_NanoAOD/2016/HplusM120_Skim_NanoAOD.root")
//int ReadMCInfoSkim(string infile = "/run/media/indra/DHEP_Storage_1/Data/NanoAOD/Skim_NanoAOD/2016/TTbarPowheg_Semilept_Skim_NanoAOD_20of21.root")
int TopPhiDiff(string infile = "/Data/root_files/AOD_files/NanoAODUL/2016/TTbarPowheg_Semilept_postVFP_Skim_NanoAOD_1of27.root")
//ReadMCInfoSkim()
{
  
  bool ishplus = 0; //Use this switch to run for hplus or ttbar
  TH1F *hWPlus = new TH1F("hWPlus","hWPlus",250,0,250);
  TH1F *hWMinus = new TH1F("hWMinus","hWMinus",250,0,250);
  TH1F *hDelPhi = new TH1F("hDelPhi","hDelPhi",100,-5.0,5.0);

  int momPDG = (ishplus) ? 37 : 24 ; //hplus or W+
  // string infile;
  // if(ishplus)
  //   infile = "root://se01.indiacms.res.in:1094//cms/store/user/idas/Output/cms-hcs-run2/Skim_NanoAOD/2016/HplusM120_Skim_NanoAOD.root";
  // else
  //   infile = "root://se01.indiacms.res.in:1094//cms/store/user/idas/Output/cms-hcs-run2/Skim_NanoAOD/2016/TTbarPowheg_Semilept_Skim_NanoAOD_1of21.root";
  
  bool HasFoundTopology(UInt_t& nGenPart_, Int_t GenPart_pdgId_[], Int_t GenPart_genPartIdxMother_[], 
			Float_t GenPart_pt_[], Float_t GenPart_eta_[], Float_t GenPart_phi_[], Float_t GenPart_mass_[],
			int GrandMomPDG/*top*/, int MomPDG/*H+ or W+*/, int Daughter1_PDG/*c*/, int Daughter2_PDG/*s_bar*/, 
			double& cosTheta/*cosine theta*/);
  
  TFile *fin = TFile::Open(infile.c_str());
  cout<<"Reading from file : "<< fin->GetName() << endl;

  TTree *tr = (TTree *)fin->Get("Events");
  
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

  UInt_t    nLHEPart_;    
  Float_t   LHEPart_pt_[100];
  Float_t   LHEPart_eta_[100];
  Float_t   LHEPart_phi_[100];
  Float_t   LHEPart_mass_[100];
  Int_t   LHEPart_pdgId_[100];

  tr->SetBranchStatus("*",0);

  tr->SetBranchStatus("nGenPart",1);
  tr->SetBranchStatus("GenPart_pt",1);
  tr->SetBranchStatus("GenPart_eta",1);
  tr->SetBranchStatus("GenPart_phi",1);
  tr->SetBranchStatus("GenPart_mass",1);
  tr->SetBranchStatus("GenPart_genPartIdxMother",1);
  tr->SetBranchStatus("GenPart_pdgId",1);
  tr->SetBranchStatus("GenPart_status",1);
  tr->SetBranchStatus("GenPart_statusFlags",1);

  tr->SetBranchAddress("nGenPart", &nGenPart_);
  tr->SetBranchAddress("GenPart_pt", &GenPart_pt_);
  tr->SetBranchAddress("GenPart_eta", &GenPart_eta_);
  tr->SetBranchAddress("GenPart_phi", &GenPart_phi_);
  tr->SetBranchAddress("GenPart_mass", &GenPart_mass_);
  tr->SetBranchAddress("GenPart_genPartIdxMother", &GenPart_genPartIdxMother_);
  tr->SetBranchAddress("GenPart_pdgId", &GenPart_pdgId_);
  tr->SetBranchAddress("GenPart_status", &GenPart_status_);
  tr->SetBranchAddress("GenPart_statusFlags", &GenPart_statusFlags_);

  // tr->SetBranchStatus("nGenJet",1);
  // tr->SetBranchStatus("GenJet_pt",1);
  // tr->SetBranchStatus("GenJet_eta",1);
  // tr->SetBranchStatus("GenJet_phi",1);
  // tr->SetBranchStatus("GenJet_mass",1);
  // tr->SetBranchAddress("nGenJet", &nGenJet_);
  // tr->SetBranchAddress("GenJet_pt", &GenJet_pt_);
  // tr->SetBranchAddress("GenJet_eta", &GenJet_eta_);
  // tr->SetBranchAddress("GenJet_phi", &GenJet_phi_);
  // tr->SetBranchAddress("GenJet_mass", &GenJet_mass_);

  tr->SetBranchStatus("nLHEPart",1);
  tr->SetBranchStatus("LHEPart_pt",1);
  tr->SetBranchStatus("LHEPart_eta",1);
  tr->SetBranchStatus("LHEPart_phi",1);
  tr->SetBranchStatus("LHEPart_mass",1);
  tr->SetBranchStatus("LHEPart_pdgId",1);

  tr->SetBranchAddress("nLHEPart", &nLHEPart_);
  tr->SetBranchAddress("LHEPart_pt", &LHEPart_pt_);
  tr->SetBranchAddress("LHEPart_eta", &LHEPart_eta_);
  tr->SetBranchAddress("LHEPart_phi", &LHEPart_phi_);
  tr->SetBranchAddress("LHEPart_mass", &LHEPart_mass_);
  tr->SetBranchAddress("LHEPart_pdgId", &LHEPart_pdgId_);
  
  double cosTheta = -1000.;  
  
  TH1F *hCostheta ;
  if(ishplus)
    hCostheta = new TH1F("hCostheta","m_{H^{+}} = 120 GeV", 80, -2.0, 2.0);
  else
    hCostheta = new TH1F("hCostheta","SM t#bar{t}", 80, -2.0, 2.0);
  
  TLorentzVector top,tbar;
  
  //for(int ievent = 0 ; ievent < 5; ievent++){
  for(int ievent = 0 ; ievent < tr->GetEntries() ; ievent++){
    
    tr->GetEntry(ievent);
    
    if(ievent%100000==0)
      printf("Processing Event : %03d (total:%lld)(%4.2f\%)\n",ievent,tr->GetEntries(), 100.*ievent/tr->GetEntries());
    
    for (unsigned int imc = 0 ; imc < nLHEPart_ ; imc++ ){      
      //for (unsigned int imc = 0 ; imc < 30 ; imc++ ){      
      TParticlePDG *partPDG = TDatabasePDG::Instance()->GetParticle(LHEPart_pdgId_[imc]);
      // if(!partPDG){
      // 	printf("\t LHE : %03d, PDG : %5d ( noPDGname), (Pt, Eta, Phi, Mass) = (%5.2f, %5.2f, %5.2f, %5.2f)\n", 
      // 	       imc, LHEPart_pdgId_[imc], LHEPart_pt_[imc], 
      // 	       LHEPart_eta_[imc] , LHEPart_phi_[imc], LHEPart_mass_[imc]);
      // }else{
      // 	printf("\t LHE : %03d, PDG : %5d (%7s), (Pt, Eta, Phi, Mass) = (%5.2f, %5.2f, %5.2f, %5.2f)\n", 
      // 	       imc, LHEPart_pdgId_[imc], partPDG->GetName(), LHEPart_pt_[imc],
      // 	       LHEPart_eta_[imc] , LHEPart_phi_[imc], LHEPart_mass_[imc]);
      // }
    }// mc particle loop
    
    int nofTop = 0, nofTbar = 0;
    int nofWplus = 0, nofWminus = 0;
    int index_top = -1, index_tbar = -1;
    int first_top = -1, first_tbar = -1;
    // int nofPromptGluon = 0;
    // for (unsigned int imc = 0 ; imc < nGenPart_ ; imc++ ){      
    //   if(GenPart_pdgId_[imc]==21 and nofPromptGluon==0 and GenPart_genPartIdxMother_[imc]==0){
    // 	hPtPromptGluon->Fill(GenPart_pt_[imc]);
    // 	nofPromptGluon++;
    //   }
    // }
    
    //for (unsigned int imc = 0 ; imc < nGenPart_ ; imc++ ){
    
    for (unsigned int imc = 0 ; imc < 15 ; imc++ ){      
      TParticlePDG *partPDG = TDatabasePDG::Instance()->GetParticle(GenPart_pdgId_[imc]);
      //if(nofPromptGluon==0){
      // if(!partPDG){
      // 	printf("\t id : %03d, PDG : %5d ( noPDGname), status : %2d, (Pt, Eta, Phi, Mass) = (%5.2f, %5.2f, %5.2f, %5.2f), Mother-id : %03d\n", 
      // 	       imc, GenPart_pdgId_[imc], GenPart_status_[imc], GenPart_pt_[imc], 
      // 	       GenPart_eta_[imc] , GenPart_phi_[imc], GenPart_mass_[imc], GenPart_genPartIdxMother_[imc]
      // 	       );
      // }else{
      // 	printf("\t id : %03d, PDG : %5d (%7s), status : %2d, (Pt, Eta, Phi, Mass) = (%5.2f, %5.2f, %5.2f, %5.2f), Mother-id : %03d\n", 
      // 	       imc, GenPart_pdgId_[imc], partPDG->GetName(), GenPart_status_[imc], GenPart_pt_[imc],
      // 	       GenPart_eta_[imc] , GenPart_phi_[imc], GenPart_mass_[imc], GenPart_genPartIdxMother_[imc]
      // 	       );
      // }
      //}
      
      if(GenPart_pdgId_[imc]==24 and nofWplus==0 and abs(GenPart_pdgId_[GenPart_genPartIdxMother_[imc]])==6) {
	hWPlus->Fill(GenPart_mass_[imc]);
	nofWplus++;
	index_top = GenPart_genPartIdxMother_[imc];
      }
      if(GenPart_pdgId_[imc]==-24 and nofWminus==0 and abs(GenPart_pdgId_[GenPart_genPartIdxMother_[imc]])==6) {
	hWMinus->Fill(GenPart_mass_[imc]);
	nofWminus++;
	index_tbar = GenPart_genPartIdxMother_[imc];
      }

      if(GenPart_pdgId_[imc]==6 and nofTop == 0) {
	first_top = imc;
	nofTop++;
      }
      if(GenPart_pdgId_[imc]==-6 and nofTbar == 0) {
	first_tbar = imc;
	nofTbar++;
      }

    }// mc particle loop
    
    if(nofWplus==1 and nofWminus==1){
      top.SetPtEtaPhiM(GenPart_pt_[index_top], GenPart_eta_[index_top] , GenPart_phi_[index_top], GenPart_mass_[index_top]);
      tbar.SetPtEtaPhiM(GenPart_pt_[index_tbar], GenPart_eta_[index_tbar] , GenPart_phi_[index_tbar], GenPart_mass_[index_tbar]);
      // printf("\t top : (Pt, Eta, Phi, Mass) = (%5.2f, %5.2f, %5.2f, %5.2f), Mother-id : %03d\n", GenPart_pt_[index_top],
      // 	     GenPart_eta_[index_top] , GenPart_phi_[index_top], GenPart_mass_[index_top], GenPart_genPartIdxMother_[index_top]);
      // printf("\t tbar : (Pt, Eta, Phi, Mass) = (%5.2f, %5.2f, %5.2f, %5.2f), Mother-id : %03d\n", GenPart_pt_[index_tbar],
      // 	     GenPart_eta_[index_tbar] , GenPart_phi_[index_tbar], GenPart_mass_[index_tbar], GenPart_genPartIdxMother_[index_tbar]);
      // float phidiff = TMath::Abs(GenPart_phi_[index_top] - GenPart_phi_[index_tbar]);
      // float delphi = top.DeltaPhi(tbar);
      // printf("\t phidiff : %f, delphi : %f\n",phidiff,delphi);
      hDelPhi->Fill(TMath::Abs(top.DeltaPhi(tbar)));
    }
    
    // if(nofTop==1 and nofTbar==1){
    //   top.SetPtEtaPhiM(GenPart_pt_[first_top], GenPart_eta_[first_top] , GenPart_phi_[first_top], GenPart_mass_[first_top]);
    //   tbar.SetPtEtaPhiM(GenPart_pt_[first_tbar], GenPart_eta_[first_tbar] , GenPart_phi_[first_tbar], GenPart_mass_[first_tbar]);
    //   hDelPhi->Fill(TMath::Abs(top.DeltaPhi(tbar)));
    // }
      
  }//event loop
  
  fin->Close();
  delete fin;
  
  // TCanvas *c1 = new TCanvas("c1","c1");
  // c1->Divide(2,1);
  // c1->cd(1);
  // hWPlus->Draw();
  // hWPlus->GetXaxis()->SetTitle("mass (GeV)");
  // hWPlus->GetYaxis()->SetTitle("Entries");
  // c1->cd(2);
  // hWMinus->Draw();
  // hWMinus->GetXaxis()->SetTitle("mass (GeV)");
  // hWMinus->GetYaxis()->SetTitle("Entries");
  
  TCanvas *c2 = new TCanvas("c2","c2");
  hDelPhi->Draw();

  

  TFile *fout = TFile::Open("root_files/test/Kinout.root","recreate");
  // hTTbar->Write();
  hDelPhi->Write();
  fout->Close();
  delete fout;

  return true;
} 

