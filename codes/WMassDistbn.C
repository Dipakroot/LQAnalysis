/**********************************************************************
 Created on : 13/11/2021
 Purpose    : Study the fraction of events for semileptonic, hadronic and 
              dileptonic channel for powheg processes. The following code 
              will not produce desired result for Madgraph production.

// First create the input file as
// for i in `dasgoclient --query='file dataset=/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8/RunIISummer16NanoAODv6-PUMoriond17_Nano25Oct2019_102X_mcRun2_asymptotic_v7-v2/NANOAODSIM status=*'` ; do echo root://cms-xrd-global.cern.ch/$i >> input/files.txt ; done
// Then run on the input/files.txt

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


int WMassDistbn(int index = 1, string inputfile = "input/files_ttbar_inclusive.txt", double xss = 831.76)
{
  
  bool HasFoundTopology(UInt_t& nGenPart_, Int_t GenPart_pdgId_[], Int_t GenPart_genPartIdxMother_[], 
			Float_t GenPart_pt_[], Float_t GenPart_eta_[], Float_t GenPart_phi_[], Float_t GenPart_mass_[],
			int GrandMomPDG/*top*/, int MomPDG/*H+ or W+*/, int Daughter1_PDG/*c*/, int Daughter2_PDG/*s_bar*/, 
			int& Wpid);
  bool	HasFoundTopology(std::vector<int> , std::vector<int> , std::vector<int>&);

  // crossSections["TTbarPowheg"]		=  {831.76, 831.76, 831.76};  //ttbar NNLO (http://inspirehep.net/search?p=find+eprint+1112.5675)
  // crossSections["TTbarPowheg_Dilepton"]       =  { 87.315, 87.315, 87.315};
  // crossSections["TTbarPowheg_Semilept"]       =  {364.352,364.352,364.352};
  // crossSections["TTbarPowheg_Hadronic"]       =  {380.095,380.095,380.095};

  ifstream fin0(Form("%s",inputfile.c_str()));
  string s0;
  double totalEvents = 0;
  while(getline(fin0,s0)){    
    TFile *file = TFile::Open(s0.c_str(),"read");
    TH1D *hEvents = (TH1D*) file->Get("hEvents");
    double nofMCEvents = hEvents->GetEntries()/2.0;
    totalEvents += nofMCEvents;
    file->Close();
    delete file;
  }
  fin0.close();
  double lumi = 35921.87;
  //double xss = 831.76;
  //double xss = 364.352;
  double sampleWt = lumi * xss / totalEvents ;
  printf("Total Events : %10.1lf, wt : %lf\n",totalEvents, sampleWt);

  TChain *chain = new TChain("Events");
  
  ifstream fin(inputfile.c_str());
  string s;
  string inputname = inputfile.substr(inputfile.find_last_of("/")+1,inputfile.find_last_of(".")-inputfile.find_last_of("/")-1);
  cout << "input filename name : " << inputname << endl;
  int i = 1;
  while(getline(fin,s)){
    //if(i==index){
      cout << "Processing for index : " << index << " and file : " <<  s << endl;
      chain->Add(s.c_str());
      //}
    i++;
  }
  fin.close();
  cout << "Total Events : " << chain->GetEntries() << endl;
  
  TH1D *hEvtCount = new TH1D("hEvtCount","hEvtCount",10,0.,10.);
  TH1D *hDilepton = new TH1D("hDilepton","hDilepton",10,0.,10.);
  TH1D *hHadronic = new TH1D("hHadronic","hHadronic",10,0.,10.);
  TH1D *hSemiLept = new TH1D("hSemiLept","hSemiLept",20,0.,20.);
  TH1D *hWMass_US = new TH1D("hWMass_US","hWMass_US", 160, 0., 160.);
  TH1D *hWMass_Wt = new TH1D("hWMass_Wt","hWMass_Wt", 160, 0., 160.);
  
  UInt_t	nLHEPart_;    
  Float_t	LHEPart_pt_[50];
  Float_t	LHEPart_eta_[50];
  Float_t	LHEPart_phi_[50];
  Float_t	LHEPart_mass_[50];
  Int_t		LHEPart_pdgId_[50];
  
  UInt_t    nGenPart_;
  Float_t   GenPart_pt_[300];
  Float_t   GenPart_eta_[300];
  Float_t   GenPart_phi_[300];
  Float_t   GenPart_mass_[300];
  Int_t     GenPart_genPartIdxMother_[300];
  Int_t     GenPart_pdgId_[300];
  Int_t     GenPart_status_[300];
  Int_t     GenPart_statusFlags_[300];
  std::vector<int>      _genPDGID ;
  std::vector<int>      _genMomIdx;
  std::vector<int>      hF_partid ; 

  chain->SetBranchAddress("nLHEPart", &nLHEPart_);
  chain->SetBranchAddress("LHEPart_pt", &LHEPart_pt_);
  chain->SetBranchAddress("LHEPart_eta", &LHEPart_eta_);
  chain->SetBranchAddress("LHEPart_phi", &LHEPart_phi_);
  chain->SetBranchAddress("LHEPart_mass", &LHEPart_mass_);
  chain->SetBranchAddress("LHEPart_pdgId", &LHEPart_pdgId_);

  chain->SetBranchAddress("nGenPart", &nGenPart_);
  chain->SetBranchAddress("GenPart_pt", &GenPart_pt_);
  chain->SetBranchAddress("GenPart_eta", &GenPart_eta_);
  chain->SetBranchAddress("GenPart_phi", &GenPart_phi_);
  chain->SetBranchAddress("GenPart_mass", &GenPart_mass_);
  chain->SetBranchAddress("GenPart_genPartIdxMother", &GenPart_genPartIdxMother_);
  chain->SetBranchAddress("GenPart_pdgId", &GenPart_pdgId_);
  chain->SetBranchAddress("GenPart_status", &GenPart_status_);
  chain->SetBranchAddress("GenPart_statusFlags", &GenPart_statusFlags_);

  // chain->SetBranchAddress("GenPart_genPartIdxMother", &_genMomIdx);
  // chain->SetBranchAddress("GenPart_pdgId", &_genPDGID);

  Long64_t nofSemiLeptonic = 0 , nofHadronic = 0 , nofDileptonic = 0 ;
  Long64_t nofDiEle = 0, nofDiMu = 0, nofDiTau = 0, nofEleMu = 0, nofEleTau = 0, nofMuTau = 0;   
  Long64_t nofHadcs = 0, nofHadFourSep = 0, nofHadTwoOneOne = 0, nofHadTwoTwo = 0;
  Long64_t nofcsMu = 0, nofcsEle = 0, nofcsTau = 0, nofSlMu = 0, nofSlEle = 0, nofSlTau = 0, nofSlcs = 0, nofSlud = 0, nofSluc = 0, nofSlus = 0, nofSlds = 0, nofSldc = 0;
  
  Long64_t nofHFcs = 0, nofHFud = 0, nofHFus = 0, nofHFdc = 0;
  
  for (Long64_t ievent = 0 ; ievent < chain->GetEntries() ; ievent++ ) {
  //for (Long64_t ievent = 0 ; ievent < 10 ; ievent++ ) {
    
    chain->GetEntry(ievent);

    if(ievent%100000==0)//Print after 10K or one or 10 million
      printf("Processing Event : %lld of total : %lld\n",ievent,chain->GetEntries());

    bool isOne_u = false, isOne_d = false, isOne_c = false, isOne_s = false;
    bool isTwo_u = false, isTwo_d = false, isTwo_c = false, isTwo_s = false;
    // bool isThree_u = false, isThree_d = false, isThree_c = false, isThree_s = false;
    // bool isFour_u = false, isFour_d = false, isFour_c = false, isFour_s = false;
    bool isOne_e = false, isOne_m = false, isOne_t = false;
    bool isTwo_e = false, isTwo_m = false, isTwo_t = false;
    bool isOne_nu_e = false, isOne_nu_m = false, isOne_nu_t = false;
    bool isTwo_nu_e = false, isTwo_nu_m = false, isTwo_nu_t = false;

    for (unsigned int imc = (nLHEPart_-4) ; imc < nLHEPart_ ; imc++ ){      //Check the last four particles

      // if(ievent < 1000){
      // 	TParticlePDG *partPDG = TDatabasePDG::Instance()->GetParticle(LHEPart_pdgId_[imc]);
	
      // 	if(!partPDG){
      // 	  printf("\t LHE : %03d, PDG : %5d ( noPDGname), (Pt, Eta, Phi, Mass) = (%5.2f, %5.2f, %5.2f, %5.2f)\n", 
      // 		 imc, LHEPart_pdgId_[imc], LHEPart_pt_[imc], 
      // 		 LHEPart_eta_[imc] , LHEPart_phi_[imc], LHEPart_mass_[imc]);
	
      // 	}else{
      // 	  printf("\t LHE : %03d, PDG : %5d (%7s), (Pt, Eta, Phi, Mass) = (%5.2f, %5.2f, %5.2f, %5.2f)\n", 
      // 		 imc, LHEPart_pdgId_[imc], partPDG->GetName(), LHEPart_pt_[imc],
      // 		 LHEPart_eta_[imc] , LHEPart_phi_[imc], LHEPart_mass_[imc]);
      // 	}
      // }

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
      nofDileptonic++ ;
      //printf("Event type : dileptonic\n");

      if(isTwo_nu_e and isTwo_e) nofDiEle++;
      if(isTwo_nu_m and isTwo_m) nofDiMu++;
      if(isTwo_nu_t and isTwo_t) nofDiTau++;

      if(isOne_e and isOne_nu_e and isOne_m and isOne_nu_m) nofEleMu++;
      if(isOne_e and isOne_nu_e and isOne_t and isOne_nu_t) nofEleTau++;
      if(isOne_m and isOne_nu_m and isOne_t and isOne_nu_t) nofMuTau++;
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
	nofHadronic++;
	//printf("Event type : hadronic\n");

	if(isFourHadron1 or (isTwo_u and isOne_c and isOne_s) or (isTwo_d and isOne_c and isOne_s) or (isTwo_c and isOne_d and isOne_s) or (isTwo_c and isTwo_s)) nofHadcs++;
	if(isFourHadron1) nofHadFourSep++;
	if(isFourHadron2 or isFourHadron3 or isFourHadron4 or isFourHadron5) nofHadTwoOneOne++;
	if(isFourHadron6) nofHadTwoTwo++;
      }
    }

    if(!isDilepton and !isHadronic){
      bool isOneLepton = (isOne_e and isOne_nu_e) or (isOne_m and isOne_nu_m) or (isOne_t and isOne_nu_t);
      bool isOneHadron = (isOne_u and isOne_d) or (isOne_u and isOne_c) or (isOne_u and isOne_s) or (isOne_d and isOne_c) or (isOne_d and isOne_s) or (isOne_c and isOne_s) ;
      if(isOneLepton and isOneLepton){
	isSemilepton = true;
	nofSemiLeptonic++;
	//printf("Event type : semileptonic\n");

	if((isOne_c and isOne_s) and (isOne_e and isOne_nu_e)) nofcsEle++;
	if((isOne_c and isOne_s) and (isOne_m and isOne_nu_m)) nofcsMu++;
	if((isOne_c and isOne_s) and (isOne_t and isOne_nu_t)) nofcsTau++;
	
	if(isOne_e and isOne_nu_e) nofSlEle++;
	if(isOne_m and isOne_nu_m) nofSlMu++;
	if(isOne_t and isOne_nu_t) nofSlTau++;
	if(isOne_c and isOne_s) nofSlcs++;
	if(isOne_u and isOne_d) nofSlud++;
	if(isOne_u and isOne_c) nofSluc++;
	if(isOne_u and isOne_s) nofSlus++;
	if(isOne_d and isOne_s) nofSlds++;
	if(isOne_d and isOne_c) nofSldc++;
      }
    }

    if(isSemilepton){
      int momPDG = 24 ;
      int Wpid = 0.0;
      
      // _genPDGID.clear(); _genMomIdx.clear(); hF_partid.clear();
      // for (unsigned int imc = 0 ; imc < nGenPart_ ; imc++ ){      
      // 	_genPDGID.push_back(GenPart_pdgId_[imc]);
      // 	_genMomIdx.push_back(GenPart_genPartIdxMother_[imc]);
      // }
      // if(HasFoundTopology(_genPDGID, _genMomIdx, hF_partid)){
      // 	//printf("Processing event : %lld\n",ievent);
      // 	//nofHFcs++;
      // }
      if(HasFoundTopology(nGenPart_, GenPart_pdgId_, GenPart_genPartIdxMother_, GenPart_pt_, GenPart_eta_, GenPart_phi_, GenPart_mass_, 6, momPDG, 4, 3, Wpid)){
	
	//printf("Processing event : %lld, W at : %d\n",ievent,Wpid);
	nofHFcs++;
	hWMass_US->Fill(GenPart_mass_[Wpid]);
	hWMass_Wt->Fill(GenPart_mass_[Wpid],sampleWt);

	// for (unsigned int imc = 0 ; imc < 30 ; imc++ ){      
	//   TParticlePDG *partPDG = TDatabasePDG::Instance()->GetParticle(GenPart_pdgId_[imc]);
	//   if(!partPDG){
	//     printf("\t id : %03d, PDG : %5d ( noPDGname), status : %2d, (Pt, Eta, Phi, Mass) = (%5.2f, %5.2f, %5.2f, %5.2f), Mother-id : %03d\n", 
	// 	   imc, GenPart_pdgId_[imc], GenPart_status_[imc], GenPart_pt_[imc], 
	// 	   GenPart_eta_[imc] , GenPart_phi_[imc], GenPart_mass_[imc], GenPart_genPartIdxMother_[imc]
	// 	   );
	//   }else{
	//     printf("\t id : %03d, PDG : %5d (%7s), status : %2d, (Pt, Eta, Phi, Mass) = (%5.2f, %5.2f, %5.2f, %5.2f), Mother-id : %03d\n", 
	// 	   imc, GenPart_pdgId_[imc], partPDG->GetName(), GenPart_status_[imc], GenPart_pt_[imc],
	// 	   GenPart_eta_[imc] , GenPart_phi_[imc], GenPart_mass_[imc], GenPart_genPartIdxMother_[imc]
	// 	   );
	//   }
	// }// mc particle loop
      }
      if(HasFoundTopology(nGenPart_, GenPart_pdgId_, GenPart_genPartIdxMother_, GenPart_pt_, GenPart_eta_, GenPart_phi_, GenPart_mass_, 6, momPDG, 2, 1, Wpid)){
	nofHFud++;
	hWMass_US->Fill(GenPart_mass_[Wpid]);
	hWMass_Wt->Fill(GenPart_mass_[Wpid],sampleWt);
      }
      if(HasFoundTopology(nGenPart_, GenPart_pdgId_, GenPart_genPartIdxMother_, GenPart_pt_, GenPart_eta_, GenPart_phi_, GenPart_mass_, 6, momPDG, 2, 3, Wpid)){
	nofHFus++;
	hWMass_US->Fill(GenPart_mass_[Wpid]);
	hWMass_Wt->Fill(GenPart_mass_[Wpid],sampleWt);
      }
      if(HasFoundTopology(nGenPart_, GenPart_pdgId_, GenPart_genPartIdxMother_, GenPart_pt_, GenPart_eta_, GenPart_phi_, GenPart_mass_, 6, momPDG, 1, 4, Wpid)){
	nofHFdc++;
	hWMass_US->Fill(GenPart_mass_[Wpid]);
	hWMass_Wt->Fill(GenPart_mass_[Wpid],sampleWt);
      }
    }

    if(!isDilepton and !isHadronic and !isSemilepton){
      printf("Not identified Event : %lld\n",ievent);
      for (unsigned int imc = 0 ; imc < nLHEPart_ ; imc++ ){      
 
	TParticlePDG *partPDG = TDatabasePDG::Instance()->GetParticle(LHEPart_pdgId_[imc]);
      
	if(!partPDG){
	  printf("\t LHE : %03d, PDG : %5d ( noPDGname), (Pt, Eta, Phi, Mass) = (%5.2f, %5.2f, %5.2f, %5.2f)\n", 
		 imc, LHEPart_pdgId_[imc], LHEPart_pt_[imc], 
		 LHEPart_eta_[imc] , LHEPart_phi_[imc], LHEPart_mass_[imc]);
	
	}else{
	  printf("\t LHE : %03d, PDG : %5d (%7s), (Pt, Eta, Phi, Mass) = (%5.2f, %5.2f, %5.2f, %5.2f)\n", 
		 imc, LHEPart_pdgId_[imc], partPDG->GetName(), LHEPart_pt_[imc],
		 LHEPart_eta_[imc] , LHEPart_phi_[imc], LHEPart_mass_[imc]);
	}
      }//LHEPart loop
    }//not (dilepton or semilepton or hadronic) channel 

  }//event loop;
  
  Long64_t totalIdentified = nofSemiLeptonic + nofHadronic + nofDileptonic ;
  printf("\nTotal Events : %lld\n",chain->GetEntries());
  printf("Total Identified : %lld\n\n",totalIdentified);

  printf("Total dileptonic : %lld\n",nofDileptonic);
  printf("Total hadronic : %lld\n",nofHadronic);
  printf("Total semileptonic : %lld\n\n",nofSemiLeptonic);
  printf("Total semileptonic cs : %lld\n",nofSlcs);
  printf("Total semileptonic ud : %lld\n",nofSlud);
  printf("Total semileptonic uc : %lld\n",nofSluc);
  printf("Total semileptonic us : %lld\n",nofSlus);
  printf("Total semileptonic dc : %lld\n",nofSldc);
  printf("Total semileptonic ds : %lld\n\n",nofSlds);
  printf("Total genpart cs : %lld\n",nofHFcs);
  printf("Total genpart ud : %lld\n",nofHFud);
  printf("Total genpart us : %lld\n",nofHFus);
  printf("Total genpart dc : %lld\n\n",nofHFdc);
  
  /////////////////// Event Histogram ////////////////////////////
  hEvtCount->SetBinContent(1,chain->GetEntries());
  hEvtCount->SetBinContent(2,totalIdentified);
  hEvtCount->SetBinContent(3,chain->GetEntries()-totalIdentified);
  hEvtCount->SetBinContent(4,nofDileptonic);
  hEvtCount->SetBinContent(5,nofHadronic);
  hEvtCount->SetBinContent(6,nofSemiLeptonic);
  
  hEvtCount->GetXaxis()->SetBinLabel(1,"Total Events");
  hEvtCount->GetXaxis()->SetBinLabel(2,"Total Identified");
  hEvtCount->GetXaxis()->SetBinLabel(3,"Total missed");
  hEvtCount->GetXaxis()->SetBinLabel(4,"nofDileptonic");
  hEvtCount->GetXaxis()->SetBinLabel(5,"nofHadronic");
  hEvtCount->GetXaxis()->SetBinLabel(6,"nofSemiLeptonic");

  /////////////////// Dilepton Histogram ////////////////////////////
  //Long64_t nofDiEle = 0, nofDiMu = 0, nofDiTau = 0, nofEleMu = 0, nofEleTau = 0, nofMuTau = 0;   
  hDilepton->SetBinContent(1,nofDileptonic);
  hDilepton->SetBinContent(2,nofDiEle);
  hDilepton->SetBinContent(3,nofDiMu);
  hDilepton->SetBinContent(4,nofDiTau);
  hDilepton->SetBinContent(5,nofEleMu);
  hDilepton->SetBinContent(6,nofEleTau);
  hDilepton->SetBinContent(7,nofMuTau);

  hDilepton->GetXaxis()->SetBinLabel(1,"nofDileptonic");
  hDilepton->GetXaxis()->SetBinLabel(2,"nofDiEle");
  hDilepton->GetXaxis()->SetBinLabel(3,"nofDiMu");
  hDilepton->GetXaxis()->SetBinLabel(4,"nofDiTau");
  hDilepton->GetXaxis()->SetBinLabel(5,"nofEleMu");
  hDilepton->GetXaxis()->SetBinLabel(6,"nofEleTau");
  hDilepton->GetXaxis()->SetBinLabel(7,"nofMuTau");
  
  /////////////////// Hadron Histogram ////////////////////////////
  //Long64_t nofHadcs = 0, nofHadFourSep = 0, nofHadTwoOneOne = 0, nofHadTwoTwo = 0;
  hHadronic->SetBinContent(1,nofHadronic);
  hHadronic->SetBinContent(2,nofHadcs);
  hHadronic->SetBinContent(3,nofHadFourSep);
  hHadronic->SetBinContent(4,nofHadTwoOneOne);
  hHadronic->SetBinContent(5,nofHadTwoTwo);

  hHadronic->GetXaxis()->SetBinLabel(1,"nofHadronic");
  hHadronic->GetXaxis()->SetBinLabel(2,"nofHadcs");
  hHadronic->GetXaxis()->SetBinLabel(3,"nofHadFourSep");
  hHadronic->GetXaxis()->SetBinLabel(4,"nofHadTwoOneOne");
  hHadronic->GetXaxis()->SetBinLabel(5,"nofHadTwoTwo");
  
  /////////////////// Semilepton Histogram ////////////////////////////
  //Long64_t nofcsMu = 0, nofcsEle = 0, nofcsTau = 0, nofSlMu = 0, nofSlEle = 0, nofSlTau = 0, nofSlcs = 0 ;
  hSemiLept->SetBinContent(1,nofSemiLeptonic);
  hSemiLept->SetBinContent(2,nofcsEle);
  hSemiLept->SetBinContent(3,nofcsMu);
  hSemiLept->SetBinContent(4,nofcsTau);
  hSemiLept->SetBinContent(5,nofSlEle);
  hSemiLept->SetBinContent(6,nofSlMu);
  hSemiLept->SetBinContent(7,nofSlTau);
  hSemiLept->SetBinContent(8,nofSlcs);
  hSemiLept->SetBinContent(9,nofSlud);
  hSemiLept->SetBinContent(10,nofSluc);
  hSemiLept->SetBinContent(11,nofSlus);
  hSemiLept->SetBinContent(12,nofSlds);
  hSemiLept->SetBinContent(13,nofSldc);

  
  hSemiLept->GetXaxis()->SetBinLabel(1,"nofSemiLeptonic");
  hSemiLept->GetXaxis()->SetBinLabel(2,"nofcsEle");
  hSemiLept->GetXaxis()->SetBinLabel(3,"nofcsMu");
  hSemiLept->GetXaxis()->SetBinLabel(4,"nofcsTau");
  hSemiLept->GetXaxis()->SetBinLabel(5,"nofSlEle");
  hSemiLept->GetXaxis()->SetBinLabel(6,"nofSlMu");
  hSemiLept->GetXaxis()->SetBinLabel(7,"nofSlTau");
  hSemiLept->GetXaxis()->SetBinLabel(8,"nofSlcs");
  hSemiLept->GetXaxis()->SetBinLabel(9,"nofSlud");
  hSemiLept->GetXaxis()->SetBinLabel(10,"nofSluc");
  hSemiLept->GetXaxis()->SetBinLabel(11,"nofSlus");
  hSemiLept->GetXaxis()->SetBinLabel(12,"nofSlds");
  hSemiLept->GetXaxis()->SetBinLabel(13,"nofSldc");

  if(totalIdentified == chain->GetEntries()) {
    double total_CS = 831.76;
    printf("Dileptonic CS : %lf\n",total_CS*double(nofDileptonic)/chain->GetEntries());
    printf("Hadronic CS : %lf\n",total_CS*double(nofHadronic)/chain->GetEntries());
    printf("Semileptonic CS : %lf\n\n",total_CS*double(nofSemiLeptonic)/chain->GetEntries());
  }
  
  delete chain;

  TFile *fout = TFile::Open(Form("EventCount_%s_%02d.root",inputname.c_str(),index),"recreate");
  hEvtCount->Write();
  hDilepton->Write();
  hHadronic->Write();
  hSemiLept->Write();
  hWMass_US->Write();
  hWMass_Wt->Write();
  fout->Close();
  delete fout;

  return true;
}


bool HasFoundTopology(UInt_t& nGenPart_, Int_t GenPart_pdgId_[], Int_t GenPart_genPartIdxMother_[],
		      Float_t GenPart_pt_[], Float_t GenPart_eta_[], Float_t GenPart_phi_[], Float_t GenPart_mass_[],
		      int GrandMomPDG/*top*/, int MomPDG/*H+ or W+*/, int Daughter1_PDG/*c*/, int Daughter2_PDG/*s_bar*/, int& Wpid)
{
  
  // printf("\nNpart : %u\n",nGenPart_);
  // for (unsigned int imc = 0 ; imc < nGenPart_ ; imc++ ){      
  //   TParticlePDG *partPDG = TDatabasePDG::Instance()->GetParticle(GenPart_pdgId_[imc]);
  //   if(!partPDG){
  //     printf("\t id : %03d, PDG : %5d ( noPDGname), (Pt, Eta, Phi, Mass) = (%5.2f, %5.2f, %5.2f, %5.2f), Mother-id : %03d\n", 
  // 	     imc, GenPart_pdgId_[imc], GenPart_pt_[imc], 
  // 	     GenPart_eta_[imc] , GenPart_phi_[imc], GenPart_mass_[imc], GenPart_genPartIdxMother_[imc]
  // 	     );
  //   }else{
  // 	printf("\t id : %03d, PDG : %5d (%7s), (Pt, Eta, Phi, Mass) = (%5.2f, %5.2f, %5.2f, %5.2f), Mother-id : %03d\n", 
  // 	       imc, GenPart_pdgId_[imc], partPDG->GetName(), GenPart_pt_[imc],
  // 	       GenPart_eta_[imc] , GenPart_phi_[imc], GenPart_mass_[imc], GenPart_genPartIdxMother_[imc]
  // 	       );
  //   }
  // }
  // printf("\n");

  int pid_d1	= -9999;
  int ppid_d1	= -9999;
  int pid_d2	= -9999;
  int ppid_d2	= -9999;
  int pid_mom	= -9999;
  int ppid_mom	= -9999;
  int pid_gmom	= -9999;
  
  bool hasFound = false;
  for(int imc = int(nGenPart_) - 1 ; imc >= 2 ; imc-- ){ // 2 since the first two partciles are colliding particles
    
    if(GenPart_genPartIdxMother_[imc] < 0 or GenPart_genPartIdxMother_[imc] > (int(nGenPart_) - 1)) continue;
    int ppidPDG = GenPart_pdgId_[GenPart_genPartIdxMother_[imc]] ;
    
    if(abs(GenPart_pdgId_[imc])==Daughter1_PDG and abs(ppidPDG)==MomPDG){
      pid_d1 = imc;
      ppid_d1 = GenPart_genPartIdxMother_[imc];
      //cout<<"1 : Charm found" << endl;
    }
    
    if(abs(GenPart_pdgId_[imc])==Daughter2_PDG and abs(ppidPDG)==MomPDG){
      pid_d2 = imc;
      ppid_d2 = GenPart_genPartIdxMother_[imc];
      //cout<<"2 : Sbar found" << endl;
    }
    
    if(abs(GenPart_pdgId_[imc])==MomPDG and abs(ppidPDG)==GrandMomPDG and ppid_d1==ppid_d2 and imc==ppid_d2){
      pid_mom	= imc;
      ppid_mom	= GenPart_genPartIdxMother_[imc];
      Wpid = imc;
      //cout<<"3 : W found decaying to cs" << endl;
      hasFound = true;
    }else if(abs(GenPart_pdgId_[imc])==MomPDG and abs(ppidPDG)==MomPDG and ppid_d1==ppid_d2 and imc==ppid_d2){
      pid_mom	= imc;
      ppid_mom	= GenPart_genPartIdxMother_[imc];
      Wpid = imc;
      //cout<<"3 : W found decaying to cs coming from W" << endl;
      hasFound = true;
    }
      
    // } else if(abs(GenPart_pdgId_[imc])==MomPDG and abs(ppidPDG)==GrandMomPDG){
    //   pid_mom	= imc;
    //   ppid_mom	= GenPart_genPartIdxMother_[imc];
    //} else if(GenPart_pdgId_[imc]==GrandMomPDG and ppid_mom==imc){
    //   pid_gmom = imc;
    //   hasFound = true;
    //   cout<<"4 : top found" << endl;
    // }
  }
  
  
  return hasFound;
}

bool HasFoundTopology(std::vector<int> _genPDGID, std::vector<int> _genMomIdx, std::vector<int>& hF_partid)
 {
      
   bool hF_muP = false, hF_mu = false, hF_eleP = false, hF_ele = false;
   int  pid_muP = -9999, pid_mu = -9999, pid_eleP = -9999, pid_ele = -9999;
   int  ppid_muP = -9999, ppid_mu = -9999, ppid_eleP = -9999, ppid_ele = -9999;

   bool hF_nu_muP = false, hF_nu_mu = false, hF_nu_eleP = false, hF_nu_ele = false;
   int  pid_nu_muP = -9999, pid_nu_mu = -9999, pid_nu_eleP = -9999, pid_nu_ele = -9999;
   int  ppid_nu_muP = -9999, ppid_nu_mu = -9999, ppid_nu_eleP = -9999, ppid_nu_ele = -9999;

   bool hF_b = false, hF_b_bar = false;
   int  pid_b = -9999, pid_b_bar = -9999;
   int  ppid_b = -9999, ppid_b_bar = -9999;

   bool hF_lep_W_plus = false, hF_lep_W_minus = false;
   int  pid_lep_W_plus = -9999, pid_lep_W_minus = -9999;
   int  ppid_lep_W_plus = -9999, ppid_lep_W_minus = -9999;
   
   bool hF_lep_top = false, hF_lep_top_bar = false;
   
   // The output list of indices of leptonic particles
   int pid_lep_top = -9999;
   int pid_lep_b = -9999;
   int pid_lep_W = -9999;
   int pid_lep_leption = -9999;
   int pid_lep_neutrino = -9999;
   
   bool hF_c = false, hF_c_bar = false, hF_s = false, hF_s_bar = false;
   int  pid_c = -9999, pid_c_bar = -9999, pid_s = -9999, pid_s_bar = -9999;
   int  ppid_c = -9999, ppid_c_bar = -9999, ppid_s = -9999, ppid_s_bar = -9999;
   
   bool hF_had_W_plus = false, hF_had_W_minus = false;
   int  pid_had_W_plus = -9999, pid_had_W_minus = -9999;
   int  ppid_had_W_plus = -9999, ppid_had_W_minus = -9999;
   
   bool hF_had_top = false, hF_had_top_bar = false;

   int pid_had_top = -9999;
   int pid_had_b = -9999;
   int pid_had_W = -9999;
   int pid_had_charm = -9999;
   int pid_had_strange = -9999;
   
   for(int imc = int(_genPDGID.size()) - 1 ; imc >= 2 ; imc-- ){ // 2 since the first two partciles are colliding particles
     
     int pidPDG = _genPDGID.at(imc);
     if(_genMomIdx.at(imc) < 0 or _genMomIdx.at(imc) > (int(_genPDGID.size()) - 1)) continue;
     int ppidPDG = _genPDGID.at(_genMomIdx.at(imc));
     
     TParticlePDG *partPDG = TDatabasePDG::Instance()->GetParticle(pidPDG);
     TParticlePDG *parentPDG = TDatabasePDG::Instance()->GetParticle(ppidPDG);
    
     if(!partPDG) continue;
     if(!parentPDG) continue;
     
     // Check for muon from W
     ///////////////////////////////////////////////////////////
     if((pidPDG == 13 and ppidPDG == -24) 
	//or hF_mu
	){ // mu-, W- // The or condition is to include the cases  mu --> mu in the particle list due to bug (?)
       hF_mu = true;
       pid_mu = imc;
       ppid_mu = _genMomIdx.at(imc);
     }
     if((pidPDG == -13 and ppidPDG == 24)){ // mu+, W+
       hF_muP = true;
       pid_muP = imc;
       ppid_muP = _genMomIdx.at(imc);
     }
     if((pidPDG == 11 and ppidPDG == -24)){ // e-, W-
       hF_ele = true;
       pid_ele = imc;
       ppid_ele = _genMomIdx.at(imc);
     }
     if((pidPDG == -11 and ppidPDG == 24)){ // e+, W+
       hF_eleP = true;
       pid_eleP = imc;
       ppid_eleP = _genMomIdx.at(imc);
     }
     ///////////////////////////////////////////////////////////

     // Check for nutrino from W
     ///////////////////////////////////////////////////////////
     if((pidPDG == 14 and ppidPDG == 24)){ // nu_mu, W+
       hF_nu_mu = true;
       pid_nu_mu = imc;
       ppid_nu_mu = _genMomIdx.at(imc);
     }
     if((pidPDG == -14 and ppidPDG == -24)){ // mu_mu_bar, W-
       hF_nu_muP = true;
       pid_nu_muP = imc;
       ppid_nu_muP = _genMomIdx.at(imc);
     }
     
     if((pidPDG == 12 and ppidPDG == 24)){ // nu_e, W+
       hF_nu_ele = true;
       pid_nu_ele = imc;
       ppid_nu_ele = _genMomIdx.at(imc);
     }
     if((pidPDG == -12 and ppidPDG == -24)){ // nu_e_bar, W-
       hF_nu_eleP = true;
       pid_nu_eleP = imc;
       ppid_nu_eleP = _genMomIdx.at(imc);
     }
     ///////////////////////////////////////////////////////////

     // Check for b or b_bar from top
     ///////////////////////////////////////////////////////////
     if((pidPDG == 5 and ppidPDG == 6) or (pidPDG == 5 and ppidPDG == 5)){ // b, t and b, not enforcong top parent
       hF_b = true;
       pid_b = imc;
       ppid_b = _genMomIdx.at(imc);
     }

     //if((pidPDG == -5 and ppidPDG == -6)){ // b_bar, t_bar
     if((pidPDG == -5 and ppidPDG == -6) or (pidPDG == -5 and ppidPDG == -5)){ // b_bar, not enfocing t_bar parent
       hF_b_bar = true;
       pid_b_bar = imc;
       ppid_b_bar = _genMomIdx.at(imc);
     }
     ///////////////////////////////////////////////////////////
     
     // Check for W+ or W- leptonic decay
     ///////////////////////////////////////////////////////////
     if((pidPDG == 24 and imc == ppid_muP and hF_muP and hF_nu_mu and imc == ppid_nu_mu and ppidPDG == 6) 
	or
	(pidPDG == 24 and imc == ppid_muP and hF_muP and hF_nu_mu and imc == ppid_nu_mu and ppidPDG == 24) 
	or 
	(pidPDG == 24 and imc == ppid_eleP and hF_eleP and hF_nu_ele and imc == ppid_nu_ele and ppidPDG == 6) 
	or
	(pidPDG == 24 and imc == ppid_eleP and hF_eleP and hF_nu_ele and imc == ppid_nu_ele and ppidPDG == 24) 
	or 
	(hF_lep_W_plus and pidPDG == 24 and ppidPDG == 6)
	or
	(hF_lep_W_plus and pidPDG == 24 and ppidPDG == 24)
	){       
       hF_lep_W_plus = true;
       pid_lep_W_plus = imc;
       ppid_lep_W_plus = _genMomIdx.at(imc);

       if(imc == ppid_muP and imc == ppid_nu_mu){
	 pid_lep_leption  = pid_muP ;
	 pid_lep_neutrino = pid_nu_mu;
       }
       if(imc == ppid_eleP and imc == ppid_nu_ele){
	 pid_lep_leption  = pid_eleP ;
	 pid_lep_neutrino = pid_nu_ele;
       }
       
     }

     if((pidPDG == -24 and imc == ppid_mu and hF_mu and hF_nu_muP and imc == ppid_nu_muP and ppidPDG == -6) 
	or
	(pidPDG == -24 and imc == ppid_mu and hF_mu and hF_nu_muP and imc == ppid_nu_muP and ppidPDG == -24) 
	or 
	(pidPDG == -24 and imc == ppid_ele and hF_ele and hF_nu_eleP and imc == ppid_nu_eleP and ppidPDG == -6) 
	or
	(pidPDG == -24 and imc == ppid_ele and hF_ele and hF_nu_eleP and imc == ppid_nu_eleP and ppidPDG == -24) 
	or 
	(hF_lep_W_minus and pidPDG == -24 and ppidPDG == -6)
	or
	(hF_lep_W_minus and pidPDG == -24 and ppidPDG == -24)){       
       hF_lep_W_minus = true;
       pid_lep_W_minus = imc;
       ppid_lep_W_minus = _genMomIdx.at(imc);

       if(imc == ppid_mu and imc == ppid_nu_muP){
	 pid_lep_leption  = pid_mu ;
	 pid_lep_neutrino = pid_nu_muP;
       }
       if(imc == ppid_ele and imc == ppid_nu_eleP){
	 pid_lep_leption  = pid_ele ;
	 pid_lep_neutrino = pid_nu_eleP;
       }

     }
     ///////////////////////////////////////////////////////////

     // Check for leptonic top decay
     ///////////////////////////////////////////////////////////
     if((pidPDG == 6 and imc == ppid_lep_W_plus and imc ==  ppid_b and hF_lep_W_plus and hF_b and ppidPDG == 6)
	or
	(pidPDG == 6 and imc == ppid_lep_W_plus and imc ==  ppid_b and hF_lep_W_plus and hF_b and _genMomIdx.at(imc) == 0)
	or
	(hF_lep_top and pidPDG == 6 and ppidPDG == 6)
	or
	(hF_lep_top and pidPDG == 6 and _genMomIdx.at(imc) == 0)
	){
       hF_lep_top       = true;
       pid_lep_top      = imc;
       pid_lep_b        = pid_b;
       pid_lep_W        = pid_lep_W_plus;
     }

     if((pidPDG == -6 and imc == ppid_lep_W_minus and imc ==  ppid_b_bar and hF_lep_W_minus and hF_b_bar and ppidPDG == -6)
	or
	(pidPDG == -6 and imc == ppid_lep_W_minus and imc ==  ppid_b_bar and hF_lep_W_minus and hF_b_bar and _genMomIdx.at(imc) == 0)
	or
	(hF_lep_top_bar and pidPDG == -6 and ppidPDG == -6)
	or
	(hF_lep_top_bar and pidPDG == -6 and _genMomIdx.at(imc) == 0)
	){
       hF_lep_top_bar   = true;
       pid_lep_top      = imc;
       pid_lep_b        = pid_b_bar;
       pid_lep_W        = pid_lep_W_minus;
     }
     ///////////////////////////////////////////////////////////


     // Check for charm from W
     ///////////////////////////////////////////////////////////
     if(pidPDG == 4 and ppidPDG == 24){ // Charm from W+ 
       hF_c = true;
       pid_c = imc;
       ppid_c = _genMomIdx.at(imc);
     }
     if((pidPDG == -4 and ppidPDG == -24)){ // charm_bar from W-
       hF_c_bar = true;
       pid_c_bar = imc;
       ppid_c_bar = _genMomIdx.at(imc);
     }
     ///////////////////////////////////////////////////////////

     // Check for strange from W
     ///////////////////////////////////////////////////////////
     if(pidPDG == 3 and ppidPDG == -24){ // strange from W- 
       hF_s = true;
       pid_s = imc;
       ppid_s = _genMomIdx.at(imc);
     }
     if((pidPDG == -3 and ppidPDG == 24)){ // strange_bar from W
       hF_s_bar = true;
       pid_s_bar = imc;
       ppid_s_bar = _genMomIdx.at(imc);
     }
     ///////////////////////////////////////////////////////////

     
     // Check for W+ or W- hadronic decay
     ///////////////////////////////////////////////////////////
     if((pidPDG == 24 and imc == ppid_c and hF_c and hF_s_bar and imc == ppid_s_bar and ppidPDG == 24) 
	or
	(pidPDG == 24 and imc == ppid_c and hF_c and hF_s_bar and imc == ppid_s_bar and ppidPDG == 6) 
	or 
	(hF_had_W_plus and pidPDG == 24 and ppidPDG == 24)
	or
	(hF_had_W_plus and pidPDG == 24 and ppidPDG == 6)
	){       

       hF_had_W_plus = true;
       pid_had_W_plus = imc;
       ppid_had_W_plus = _genMomIdx.at(imc);
       
       if(imc == ppid_c and imc == ppid_s_bar){
	 pid_had_charm  = pid_c ;
	 pid_had_strange = pid_s_bar;
       }
       
     }
     
     if((pidPDG == -24 and imc == ppid_c_bar and hF_c_bar and hF_s and imc == ppid_s and ppidPDG == -24) 
	or
	(pidPDG == -24 and imc == ppid_c_bar and hF_c_bar and hF_s and imc == ppid_s and ppidPDG == -6) 
	or 
	(hF_had_W_minus and pidPDG == -24 and ppidPDG == -24)
	or
	(hF_had_W_minus and pidPDG == -24 and ppidPDG == -6)
	){       

       hF_had_W_minus = true;
       pid_had_W_minus = imc;
       ppid_had_W_minus = _genMomIdx.at(imc);
       
       if(imc == ppid_c_bar and imc == ppid_s){
	 pid_had_charm  = pid_c_bar ;
	 pid_had_strange = pid_s ;
       }
       
     }
     ///////////////////////////////////////////////////////////
     
     // Check for had top decay
     ///////////////////////////////////////////////////////////
     if((pidPDG == 6 and imc == ppid_had_W_plus and imc ==  ppid_b and hF_had_W_plus and hF_b and ppidPDG == 6)
	or
	(pidPDG == 6 and imc == ppid_had_W_plus and imc ==  ppid_b and hF_had_W_plus and hF_b and _genMomIdx.at(imc) == 0)
	or
	(hF_had_top and pidPDG == 6 and ppidPDG == 6)
	or
	(hF_had_top and pidPDG == 6 and _genMomIdx.at(imc) == 0)
	){
       hF_had_top       = true;
       pid_had_top      = imc;
       pid_had_b        = pid_b;
       pid_had_W        = pid_had_W_plus;
     }
     
     if((pidPDG == -6 and imc == ppid_had_W_minus and imc ==  ppid_b_bar and hF_had_W_minus and hF_b_bar and ppidPDG == -6)
	or
	(pidPDG == -6 and imc == ppid_had_W_minus and imc ==  ppid_b_bar and hF_had_W_minus and hF_b_bar and _genMomIdx.at(imc) == 0)
	or
	(hF_had_top_bar and pidPDG == -6 and ppidPDG == -6)
	or
	(hF_had_top_bar and pidPDG == -6 and _genMomIdx.at(imc) == 0)
	){
       hF_had_top_bar   = true;
       pid_had_top      = imc;
       pid_had_b        = pid_b_bar;
       pid_had_W        = pid_had_W_minus;
     }
     ///////////////////////////////////////////////////////////
     //printf("\t\t imc : %03d, PDG : %5d (%10s), mother id : %3d\n",imc,_genPDGID.at(imc),partPDG->GetName(),_genMomIdx.at(imc));
   }
   
   hF_partid.clear();
   hF_partid.push_back(pid_lep_top) ;
   hF_partid.push_back(pid_lep_b) ;
   hF_partid.push_back(pid_lep_W) ;
   hF_partid.push_back(pid_lep_leption) ;
   hF_partid.push_back(pid_lep_neutrino) ;

   hF_partid.push_back(pid_had_top) ;
   hF_partid.push_back(pid_had_b) ;
   hF_partid.push_back(pid_had_W) ;
   hF_partid.push_back(pid_had_charm) ;
   hF_partid.push_back(pid_had_strange) ;
   
   if( (hF_lep_top and hF_had_top_bar) || (hF_lep_top_bar and hF_had_top) )
     return true;
   
   // if( hF_lep_top || hF_lep_top_bar )
   //   return true;
   
   return false;
 }
