/**********************************************************************
 Created on : 01/06/2021
 Purpose    : Read the Kinematic fit info from KinTree
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


int ReadKinTree()
{
  Float_t	_chi2 = 0 ;
  Int_t			 _nJet = 0 ;
  std::vector<float>	 *_jetDeepB = 0 ;
  double  _bjlepDeepCSV = 0, _bjhadDeepCSV = 0, _cjhadDeepCSV = 0, _sjhadDeepCSV = 0;  
  int		_bjlep_id = 0 ;
  int		_bjhad_id = 0 ;
  int		_cjhad_id = 0 ;
  int		_sjhad_id = 0 ;

  TBranch	 *br_chi2 = 0 ;
  TBranch	 *br_nJet = 0 ;
  TBranch	 *br_jetDeepB = 0 ;
  TBranch        *br_bjlepDeepCSV = 0 ; 
  TBranch        *br_bjhadDeepCSV = 0;
  TBranch        *br_cjhadDeepCSV = 0;
  TBranch        *br_sjhadDeepCSV = 0;  
  TBranch        *br_bjlep_id = 0 ;
  TBranch        *br_bjhad_id = 0 ;
  TBranch        *br_cjhad_id = 0 ;
  TBranch        *br_sjhad_id = 0 ;

  TFile *fin	= TFile::Open(Form("root://se01.indiacms.res.in:1094//cms/store/user/idas/Output/cms-hcs-run2/CBA_Skim/2016/singleTop_tree_10of15.root"));
  //TFile *fin	= TFile::Open(Form("/Data/CMS-Analysis/NanoAOD-Analysis/Git_KinFit_Skim/KinFit_Skim/CBA_Skim/HplusM120_tree_1of1.root"));
  //TFile *fin	= TFile::Open(Form("/Data/CMS-Analysis/NanoAOD-Analysis/Git_KinFit_Skim/KinFit_Skim/CBA_Skim/TTbar_tree_1of1.root"));
  cout<<"filename : " << fin->GetName() << endl;
  TTree *tr	= (TTree*)fin->Get("Kinfit_Reco");

  tr->SetBranchAddress("chi2"	, &_chi2		, &br_chi2		);  
  tr->SetBranchAddress("nJet"	, &_nJet		, &br_nJet		);  
  tr->SetBranchAddress("jetDeepB"	, &_jetDeepB		, &br_jetDeepB		);  
  tr->SetBranchAddress("bjlepDeepCSV"	, &_bjlepDeepCSV	, &br_bjlepDeepCSV     	);  
  tr->SetBranchAddress("bjhadDeepCSV"	, &_bjhadDeepCSV	, &br_bjhadDeepCSV     	);  
  tr->SetBranchAddress("cjhadDeepCSV"	, &_cjhadDeepCSV	, &br_cjhadDeepCSV     	);  
  tr->SetBranchAddress("sjhadDeepCSV"	, &_sjhadDeepCSV	, &br_sjhadDeepCSV     	);  
  tr->SetBranchAddress("bjlep_id"	, &_bjlep_id	        , &br_bjlep_id     	);  
  tr->SetBranchAddress("bjhad_id"	, &_bjhad_id	        , &br_bjhad_id     	);  
  tr->SetBranchAddress("cjhad_id"	, &_cjhad_id	        , &br_cjhad_id     	);  
  tr->SetBranchAddress("sjhad_id"	, &_sjhad_id	        , &br_sjhad_id     	);  

  
  cout << "Total Entries : " << tr->GetEntries() << endl;
  //for (Long64_t ievent = 0 ; ievent < tr->GetEntries() ; ievent++ ) {    
  for (Long64_t ievent = 0 ; ievent < 20000 ; ievent++ ) {    
    
    tr->GetEntry(ievent) ;
    //if(_nJet==4){
    cout<<"iEvent : " << ievent << ", nJet "<<_nJet << ", chi2 : "<<_chi2<<endl;
      cout<<"\t _bjlepDeepCSV : " << _bjlepDeepCSV 
	  <<", _bjhadDeepCSV : "<< _bjhadDeepCSV
	  <<", _cjhadDeepCSV : "<< _cjhadDeepCSV
	  <<", _sjhadDeepCSV : "<< _sjhadDeepCSV
	  <<endl;
      cout<<"\t jet:bjlep: " << _jetDeepB->at(_bjlep_id) 
	  <<", jet:bjhad: "<< _jetDeepB->at(_bjhad_id) 
	  <<", jet:cjhad: "<< _jetDeepB->at(_cjhad_id) 
	  <<", jet:sjhad: "<< _jetDeepB->at(_sjhad_id) 
	  <<endl;
      
      //}
    
  }//event loop
  
  
  // TFile *fout = new TFile(Form("output_%s.root",sample.c_str()),"recreate");
  // fout->Close();
  // delete fout;

  fin->Close();
  delete fin;

  return true;
}
