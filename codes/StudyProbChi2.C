/**********************************************************************
 Created on : 07/03/2022
 Purpose    : Study the prob chi2
 Author     : Indranil Das, Visiting Fellow
 Email      : indranil.das@cern.ch | indra.ehep@gmail.com
**********************************************************************/
#if !defined(__CINT__) || defined(__MAKECINT__)

#include <TROOT.h>
#include <TChain.h>
#include <TEntryList.h>
#include <TFile.h>
//#include <TProofOutputFile.h>
#include <TSelector.h>
#include <vector>

#include "TH2.h"
#include "TF1.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TPaveStats.h"
#include "TMath.h"
//#include "TProof.h"

#include "TParticlePDG.h"
#include "TDatabasePDG.h"

#include "TLorentzVector.h"
#include "TVector3.h"

#include "TGraph.h"
#include "TLegend.h"

#include <fstream>

using namespace std;

#endif


int StudyProbChi2()
{
  //int ProbChi2(void);
  int ProbSig(void);

  //ProbChi2();
  ProbSig();

  return true;
}

int ProbSig(void)
{

  // TH1F *hProb = new TH1F("hProb","hProb",200, -0.5, 1.5);
  // TProfile *probDelRRecKF = new TProfile("probDelRRecKF","probDelRRecKF",200, -0.5, 1.5, 0., 0.6);
  
  const int nPoints = 100;
  TGraph *grS1ByB = new TGraph(nPoints);
  TGraph *grS2ByB = new TGraph(nPoints);
  TGraph *grS3ByB = new TGraph(nPoints);
  TGraph *grS4ByB = new TGraph(nPoints);
  TGraph *grS5ByB = new TGraph(nPoints);
  TGraph *grBReso = new TGraph(nPoints);
  TGraph *grSReso = new TGraph(nPoints);
  TGraph *grBEff = new TGraph(nPoints);
  TH1F *mjj[nPoints], *mjjS1[nPoints], *mjjS2[nPoints], *mjjS3[nPoints], *mjjS4[nPoints], *mjjS5[nPoints];
  for(int ip=0;ip<nPoints;ip++){
    mjj[ip] = new TH1F(Form("mjj_%02d",ip),Form("mjj_%02d",ip), 250, 0., 250.);
    mjjS1[ip] = new TH1F(Form("mjjS1_%02d",ip),Form("mjjS1_%02d",ip), 250, 0., 250.);
    mjjS2[ip] = new TH1F(Form("mjjS2_%02d",ip),Form("mjjS2_%02d",ip), 250, 0., 250.);
    mjjS3[ip] = new TH1F(Form("mjjS3_%02d",ip),Form("mjjS3_%02d",ip), 250, 0., 250.);
    mjjS4[ip] = new TH1F(Form("mjjS4_%02d",ip),Form("mjjS4_%02d",ip), 250, 0., 250.);
    mjjS5[ip] = new TH1F(Form("mjjS5_%02d",ip),Form("mjjS5_%02d",ip), 250, 0., 250.);
  }
  TH1F *ptB = new TH1F("ptB","ptB", 35, 0., 700.);
  TH1F *ptS1 = new TH1F("ptS1","ptS1", 35, 0., 700.);
  TH1F *ptS2 = new TH1F("ptS2","ptS2", 35, 0., 700.);
  TH1F *ptS3 = new TH1F("ptS3","ptS3", 35, 0., 700.);
  TH1F *ptS4 = new TH1F("ptS4","ptS4", 35, 0., 700.);
  TH1F *ptS5 = new TH1F("ptS5","ptS5", 35, 0., 700.);

  Double_t	prob;
  Float_t	jetChadPt, jetChadEta, jetChadPhi, jetChadEn;
  Float_t	jetShadPt, jetShadEta, jetShadPhi, jetShadEn;
  Float_t	metPx, metPy, metPz;
  Double_t	sampleWeight, prefireWeight, PUWeight, muEffWeight, bTagWeight;
  Bool_t	singleMu, singleEle, muonIsoCut, isLowMET;
  Double_t	weight;
  
  Double_t	probS1;
  Float_t	jetChadPtS1, jetChadEtaS1, jetChadPhiS1, jetChadEnS1;
  Float_t	jetShadPtS1, jetShadEtaS1, jetShadPhiS1, jetShadEnS1;
  Float_t	metPxS1, metPyS1, metPzS1;
  Double_t	sampleWeightS1, prefireWeightS1, PUWeightS1, muEffWeightS1, bTagWeightS1;
  Bool_t	singleMuS1, singleEleS1, muonIsoCutS1, isLowMETS1;
  Double_t	weightS1;
  
  Double_t	probS2;
  Float_t	jetChadPtS2, jetChadEtaS2, jetChadPhiS2, jetChadEnS2;
  Float_t	jetShadPtS2, jetShadEtaS2, jetShadPhiS2, jetShadEnS2;
  Float_t	metPxS2, metPyS2, metPzS2;
  Double_t	sampleWeightS2, prefireWeightS2, PUWeightS2, muEffWeightS2, bTagWeightS2;
  Bool_t	singleMuS2, singleEleS2, muonIsoCutS2, isLowMETS2;
  Double_t	weightS2;
  
  Double_t	probS3;
  Float_t	jetChadPtS3, jetChadEtaS3, jetChadPhiS3, jetChadEnS3;
  Float_t	jetShadPtS3, jetShadEtaS3, jetShadPhiS3, jetShadEnS3;
  Float_t	metPxS3, metPyS3, metPzS3;
  Double_t	sampleWeightS3, prefireWeightS3, PUWeightS3, muEffWeightS3, bTagWeightS3;
  Bool_t	singleMuS3, singleEleS3, muonIsoCutS3, isLowMETS3;
  Double_t	weightS3;
  
  Double_t	probS4;
  Float_t	jetChadPtS4, jetChadEtaS4, jetChadPhiS4, jetChadEnS4;
  Float_t	jetShadPtS4, jetShadEtaS4, jetShadPhiS4, jetShadEnS4;
  Float_t	metPxS4, metPyS4, metPzS4;
  Double_t	sampleWeightS4, prefireWeightS4, PUWeightS4, muEffWeightS4, bTagWeightS4;
  Bool_t	singleMuS4, singleEleS4, muonIsoCutS4, isLowMETS4;
  Double_t	weightS4;
  
  Double_t	probS5;
  Float_t	jetChadPtS5, jetChadEtaS5, jetChadPhiS5, jetChadEnS5;
  Float_t	jetShadPtS5, jetShadEtaS5, jetShadPhiS5, jetShadEnS5;
  Float_t	metPxS5, metPyS5, metPzS5;
  Double_t	sampleWeightS5, prefireWeightS5, PUWeightS5, muEffWeightS5, bTagWeightS5;
  Bool_t	singleMuS5, singleEleS5, muonIsoCutS5, isLowMETS5;
  Double_t	weightS5;
  
  
  TChain *tr	= new TChain("Kinfit_Reco");
  TChain *trS1	= new TChain("Kinfit_Reco");
  TChain *trS2	= new TChain("Kinfit_Reco");
  TChain *trS3	= new TChain("Kinfit_Reco");
  TChain *trS4	= new TChain("Kinfit_Reco");
  TChain *trS5	= new TChain("Kinfit_Reco");
  
  string infile_tree = "input/files_ttbar.txt"; string bkgname = "SM t#bar{t}";
  //string infile_tree = "input/files_stop.txt"; string bkgname = "single #it{t}";
  //string infile_tree = "input/files_wjets.txt"; string bkgname = "W + jets";
  //string infile_tree = "input/files_dyjets.txt"; string bkgname = "Z/#gamma + jets";
  //string infile_tree = "input/files_vv.txt"; string bkgname = "VV";
  //string infile_tree = "input/files_qcdmu.txt"; string bkgname = "MC QCD";
  //string infile_tree = "input/files_allbkg.txt"; string bkgname = "All Bkg";
  ifstream fin(infile_tree);
  string s;
  while(getline(fin,s)){
    cout << "Add file " << s << endl;
    tr->Add(s.c_str());
  }
  fin.close();

  infile_tree = "input/files_hplusM080.txt";
  fin.open(infile_tree);
  while(getline(fin,s)){
    cout << "Add file " << s << endl;
    trS1->Add(s.c_str());
  }
  fin.close();

  infile_tree = "input/files_hplusM100.txt";
  fin.open(infile_tree);
  while(getline(fin,s)){
    cout << "Add file " << s << endl;
    trS2->Add(s.c_str());
  }
  fin.close();

  infile_tree = "input/files_hplusM120.txt";
  fin.open(infile_tree);
  while(getline(fin,s)){
    cout << "Add file " << s << endl;
    trS3->Add(s.c_str());
  }
  fin.close();

  infile_tree = "input/files_hplusM140.txt";
  fin.open(infile_tree);
  while(getline(fin,s)){
    cout << "Add file " << s << endl;
    trS4->Add(s.c_str());
  }
  fin.close();

  infile_tree = "input/files_hplusM160.txt";
  fin.open(infile_tree);
  while(getline(fin,s)){
    cout << "Add file " << s << endl;
    trS5->Add(s.c_str());
  }
  fin.close();
  
  /////////////// TTbar tree Branches /////////////////////////
  tr->SetBranchAddress("prob"		, &prob);
  tr->SetBranchAddress("jetChadPt"	, &jetChadPt);
  tr->SetBranchAddress("jetChadEta"	, &jetChadEta);
  tr->SetBranchAddress("jetChadPhi"	, &jetChadPhi);
  tr->SetBranchAddress("jetChadEnergy"	, &jetChadEn);
  tr->SetBranchAddress("jetShadPt"	, &jetShadPt);
  tr->SetBranchAddress("jetShadEta"	, &jetShadEta);
  tr->SetBranchAddress("jetShadPhi"	, &jetShadPhi);
  tr->SetBranchAddress("jetShadEnergy"	, &jetShadEn);
  tr->SetBranchAddress("metPx"		, &metPx);
  tr->SetBranchAddress("metPy"		, &metPy);
  tr->SetBranchAddress("metPz"		, &metPz);

  tr->SetBranchAddress("sampleWeight"	, &sampleWeight);
  tr->SetBranchAddress("prefireWeight"	, &prefireWeight);
  tr->SetBranchAddress("PUWeight"	, &PUWeight);
  tr->SetBranchAddress("muEffWeight"	, &muEffWeight);
  tr->SetBranchAddress("bTagWeight"	, &bTagWeight);
  tr->SetBranchAddress("singleMu"	, &singleMu);
  tr->SetBranchAddress("singleEle"	, &singleEle);
  tr->SetBranchAddress("muonIsoCut"	, &muonIsoCut);
  tr->SetBranchAddress("isLowMET"	, &isLowMET);
  /////////////////////////////////////////////////////////////

  /////////////// Signal 1 tree Branches /////////////////////////
  trS1->SetBranchAddress("prob"		, &probS1);
  trS1->SetBranchAddress("jetChadPt"	, &jetChadPtS1);
  trS1->SetBranchAddress("jetChadEta"	, &jetChadEtaS1);
  trS1->SetBranchAddress("jetChadPhi"	, &jetChadPhiS1);
  trS1->SetBranchAddress("jetChadEnergy"	, &jetChadEnS1);
  trS1->SetBranchAddress("jetShadPt"	, &jetShadPtS1);
  trS1->SetBranchAddress("jetShadEta"	, &jetShadEtaS1);
  trS1->SetBranchAddress("jetShadPhi"	, &jetShadPhiS1);
  trS1->SetBranchAddress("jetShadEnergy"	, &jetShadEnS1);
  trS1->SetBranchAddress("metPx"		, &metPxS1);
  trS1->SetBranchAddress("metPy"		, &metPyS1);
  trS1->SetBranchAddress("metPz"		, &metPzS1);
  trS1->SetBranchAddress("sampleWeight"	, &sampleWeightS1);
  trS1->SetBranchAddress("prefireWeight"	, &prefireWeightS1);
  trS1->SetBranchAddress("PUWeight"	, &PUWeightS1);
  trS1->SetBranchAddress("muEffWeight"	, &muEffWeightS1);
  trS1->SetBranchAddress("bTagWeight"	, &bTagWeightS1);
  trS1->SetBranchAddress("singleMu"	, &singleMuS1);
  trS1->SetBranchAddress("singleEle"	, &singleEleS1);
  trS1->SetBranchAddress("muonIsoCut"	, &muonIsoCutS1);
  trS1->SetBranchAddress("isLowMET"	, &isLowMETS1);
  /////////////////////////////////////////////////////////////

  /////////////// Signal 2 tree Branches /////////////////////////
  trS2->SetBranchAddress("prob"		, &probS2);
  trS2->SetBranchAddress("jetChadPt"	, &jetChadPtS2);
  trS2->SetBranchAddress("jetChadEta"	, &jetChadEtaS2);
  trS2->SetBranchAddress("jetChadPhi"	, &jetChadPhiS2);
  trS2->SetBranchAddress("jetChadEnergy"	, &jetChadEnS2);
  trS2->SetBranchAddress("jetShadPt"	, &jetShadPtS2);
  trS2->SetBranchAddress("jetShadEta"	, &jetShadEtaS2);
  trS2->SetBranchAddress("jetShadPhi"	, &jetShadPhiS2);
  trS2->SetBranchAddress("jetShadEnergy"	, &jetShadEnS2);
  trS2->SetBranchAddress("metPx"		, &metPxS2);
  trS2->SetBranchAddress("metPy"		, &metPyS2);
  trS2->SetBranchAddress("metPz"		, &metPzS2);
  trS2->SetBranchAddress("sampleWeight"	, &sampleWeightS2);
  trS2->SetBranchAddress("prefireWeight"	, &prefireWeightS2);
  trS2->SetBranchAddress("PUWeight"	, &PUWeightS2);
  trS2->SetBranchAddress("muEffWeight"	, &muEffWeightS2);
  trS2->SetBranchAddress("bTagWeight"	, &bTagWeightS2);
  trS2->SetBranchAddress("singleMu"	, &singleMuS2);
  trS2->SetBranchAddress("singleEle"	, &singleEleS2);
  trS2->SetBranchAddress("muonIsoCut"	, &muonIsoCutS2);
  trS2->SetBranchAddress("isLowMET"	, &isLowMETS2);
  /////////////////////////////////////////////////////////////

  /////////////// Signal 3 tree Branches /////////////////////////
  trS3->SetBranchAddress("prob"		, &probS3);
  trS3->SetBranchAddress("jetChadPt"	, &jetChadPtS3);
  trS3->SetBranchAddress("jetChadEta"	, &jetChadEtaS3);
  trS3->SetBranchAddress("jetChadPhi"	, &jetChadPhiS3);
  trS3->SetBranchAddress("jetChadEnergy"	, &jetChadEnS3);
  trS3->SetBranchAddress("jetShadPt"	, &jetShadPtS3);
  trS3->SetBranchAddress("jetShadEta"	, &jetShadEtaS3);
  trS3->SetBranchAddress("jetShadPhi"	, &jetShadPhiS3);
  trS3->SetBranchAddress("jetShadEnergy"	, &jetShadEnS3);
  trS3->SetBranchAddress("metPx"		, &metPxS3);
  trS3->SetBranchAddress("metPy"		, &metPyS3);
  trS3->SetBranchAddress("metPz"		, &metPzS3);
  trS3->SetBranchAddress("sampleWeight"	, &sampleWeightS3);
  trS3->SetBranchAddress("prefireWeight"	, &prefireWeightS3);
  trS3->SetBranchAddress("PUWeight"	, &PUWeightS3);
  trS3->SetBranchAddress("muEffWeight"	, &muEffWeightS3);
  trS3->SetBranchAddress("bTagWeight"	, &bTagWeightS3);
  trS3->SetBranchAddress("singleMu"	, &singleMuS3);
  trS3->SetBranchAddress("singleEle"	, &singleEleS3);
  trS3->SetBranchAddress("muonIsoCut"	, &muonIsoCutS3);
  trS3->SetBranchAddress("isLowMET"	, &isLowMETS3);
  /////////////////////////////////////////////////////////////

  /////////////// Signal 4 tree Branches /////////////////////////
  trS4->SetBranchAddress("prob"		, &probS4);
  trS4->SetBranchAddress("jetChadPt"	, &jetChadPtS4);
  trS4->SetBranchAddress("jetChadEta"	, &jetChadEtaS4);
  trS4->SetBranchAddress("jetChadPhi"	, &jetChadPhiS4);
  trS4->SetBranchAddress("jetChadEnergy"	, &jetChadEnS4);
  trS4->SetBranchAddress("jetShadPt"	, &jetShadPtS4);
  trS4->SetBranchAddress("jetShadEta"	, &jetShadEtaS4);
  trS4->SetBranchAddress("jetShadPhi"	, &jetShadPhiS4);
  trS4->SetBranchAddress("jetShadEnergy"	, &jetShadEnS4);
  trS4->SetBranchAddress("metPx"		, &metPxS4);
  trS4->SetBranchAddress("metPy"		, &metPyS4);
  trS4->SetBranchAddress("metPz"		, &metPzS4);
  trS4->SetBranchAddress("sampleWeight"	, &sampleWeightS4);
  trS4->SetBranchAddress("prefireWeight"	, &prefireWeightS4);
  trS4->SetBranchAddress("PUWeight"	, &PUWeightS4);
  trS4->SetBranchAddress("muEffWeight"	, &muEffWeightS4);
  trS4->SetBranchAddress("bTagWeight"	, &bTagWeightS4);
  trS4->SetBranchAddress("singleMu"	, &singleMuS4);
  trS4->SetBranchAddress("singleEle"	, &singleEleS4);
  trS4->SetBranchAddress("muonIsoCut"	, &muonIsoCutS4);
  trS4->SetBranchAddress("isLowMET"	, &isLowMETS4);
  /////////////////////////////////////////////////////////////

  /////////////// Signal 5 tree Branches /////////////////////////
  trS5->SetBranchAddress("prob"		, &probS5);
  trS5->SetBranchAddress("jetChadPt"	, &jetChadPtS5);
  trS5->SetBranchAddress("jetChadEta"	, &jetChadEtaS5);
  trS5->SetBranchAddress("jetChadPhi"	, &jetChadPhiS5);
  trS5->SetBranchAddress("jetChadEnergy"	, &jetChadEnS5);
  trS5->SetBranchAddress("jetShadPt"	, &jetShadPtS5);
  trS5->SetBranchAddress("jetShadEta"	, &jetShadEtaS5);
  trS5->SetBranchAddress("jetShadPhi"	, &jetShadPhiS5);
  trS5->SetBranchAddress("jetShadEnergy"	, &jetShadEnS5);
  trS5->SetBranchAddress("metPx"		, &metPxS5);
  trS5->SetBranchAddress("metPy"		, &metPyS5);
  trS5->SetBranchAddress("metPz"		, &metPzS5);
  trS5->SetBranchAddress("sampleWeight"	, &sampleWeightS5);
  trS5->SetBranchAddress("prefireWeight"	, &prefireWeightS5);
  trS5->SetBranchAddress("PUWeight"	, &PUWeightS5);
  trS5->SetBranchAddress("muEffWeight"	, &muEffWeightS5);
  trS5->SetBranchAddress("bTagWeight"	, &bTagWeightS5);
  trS5->SetBranchAddress("singleMu"	, &singleMuS5);
  trS5->SetBranchAddress("singleEle"	, &singleEleS5);
  trS5->SetBranchAddress("muonIsoCut"	, &muonIsoCutS5);
  trS5->SetBranchAddress("isLowMET"	, &isLowMETS5);
  /////////////////////////////////////////////////////////////

  TLorentzVector chad, shad, met;
  
  cout << "Total Entries (MC) : " << tr->GetEntries() << endl;
  cout << "Total Entries (Signal) : " << trS1->GetEntries() << endl;
  
  double step = 1.0/nPoints;
  double xProb, mjjKF ;
  
  for (Long64_t ievent = 0 ; ievent < tr->GetEntries() ; ievent++ ) {    
  //for (Long64_t ievent = 0 ; ievent < 20000 ; ievent++ ) {    
    
    tr->GetEntry(ievent) ;
    if(ievent%1000000==0)
      cout<<"iEvent : " << ievent << ", prob : "<<prob<<endl;
    chad.SetPtEtaPhiE(jetChadPt, jetChadEta, jetChadPhi, jetChadEn);
    shad.SetPtEtaPhiE(jetShadPt, jetShadEta, jetShadPhi, jetShadEn);
    met.SetXYZM(metPx, metPy, metPz, 0.0);
    
    weight = sampleWeight*prefireWeight*PUWeight*muEffWeight*bTagWeight;
    mjjKF = (chad+shad).M();
    
    //if((chad+shad).Pt()<200.0) continue ;
    
    if(singleMu and !singleEle and muonIsoCut and met.Pt()>20.0){
      ptB->Fill((chad+shad).Pt(),weight);
      for(int ip=0;ip<nPoints;ip++){
	xProb = ip*step ; 
	if(prob>=xProb)
	  mjj[ip]->Fill(mjjKF,weight);
      }
      
    }//SingleMu condn
  }//event loop
  
  ///////////////////// Signal 1 loop //////////////////////////////////
  for (Long64_t ievent = 0 ; ievent < trS1->GetEntries() ; ievent++ ) {    
    trS1->GetEntry(ievent) ;
    if(ievent%1000000==0)
      cout<<"iEvent : " << ievent << ", probS1 : "<<probS1<<endl;
    chad.SetPtEtaPhiE(jetChadPtS1, jetChadEtaS1, jetChadPhiS1, jetChadEnS1);
    shad.SetPtEtaPhiE(jetShadPtS1, jetShadEtaS1, jetShadPhiS1, jetShadEnS1);
    met.SetXYZM(metPxS1, metPyS1, metPzS1, 0.0);
    
    weightS1 = sampleWeightS1*prefireWeightS1*PUWeightS1*muEffWeightS1*bTagWeightS1;
    mjjKF = (chad+shad).M();
    
    if(singleMuS1 and !singleEleS1 and muonIsoCutS1 and met.Pt()>20.0){
      ptS1->Fill((chad+shad).Pt(),weightS1);
      for(int ip=0;ip<nPoints;ip++){
	xProb = ip*step ; 
	if(probS1>=xProb)
	  mjjS1[ip]->Fill(mjjKF,weightS1);
      }
    }//SingleMu condn
  }//event loop
  //////////////////////////////////////////////////////////////////////////

  ///////////////////// Signal 2 loop //////////////////////////////////
  for (Long64_t ievent = 0 ; ievent < trS2->GetEntries() ; ievent++ ) {    
    trS2->GetEntry(ievent) ;
    if(ievent%1000000==0)
      cout<<"iEvent : " << ievent << ", probS2 : "<<probS2<<endl;
    chad.SetPtEtaPhiE(jetChadPtS2, jetChadEtaS2, jetChadPhiS2, jetChadEnS2);
    shad.SetPtEtaPhiE(jetShadPtS2, jetShadEtaS2, jetShadPhiS2, jetShadEnS2);
    met.SetXYZM(metPxS2, metPyS2, metPzS2, 0.0);
    
    weightS2 = sampleWeightS2*prefireWeightS2*PUWeightS2*muEffWeightS2*bTagWeightS2;
    mjjKF = (chad+shad).M();
    
    if(singleMuS2 and !singleEleS2 and muonIsoCutS2 and met.Pt()>20.0){
      ptS2->Fill((chad+shad).Pt(),weightS2);
      for(int ip=0;ip<nPoints;ip++){
	xProb = ip*step ; 
	if(probS2>=xProb)
	  mjjS2[ip]->Fill(mjjKF,weightS2);
      }
    }//SingleMu condn
  }//event loop
  //////////////////////////////////////////////////////////////////////////

  ///////////////////// Signal 3 loop //////////////////////////////////
  for (Long64_t ievent = 0 ; ievent < trS3->GetEntries() ; ievent++ ) {    
    trS3->GetEntry(ievent) ;
    if(ievent%1000000==0)
      cout<<"iEvent : " << ievent << ", probS3 : "<<probS3<<endl;
    chad.SetPtEtaPhiE(jetChadPtS3, jetChadEtaS3, jetChadPhiS3, jetChadEnS3);
    shad.SetPtEtaPhiE(jetShadPtS3, jetShadEtaS3, jetShadPhiS3, jetShadEnS3);
    met.SetXYZM(metPxS3, metPyS3, metPzS3, 0.0);
    
    weightS3 = sampleWeightS3*prefireWeightS3*PUWeightS3*muEffWeightS3*bTagWeightS3;
    mjjKF = (chad+shad).M();
    
    if(singleMuS3 and !singleEleS3 and muonIsoCutS3 and met.Pt()>20.0){
      ptS3->Fill((chad+shad).Pt(),weightS3);
      for(int ip=0;ip<nPoints;ip++){
	xProb = ip*step ; 
	if(probS3>=xProb)
	  mjjS3[ip]->Fill(mjjKF,weightS3);
      }
    }//SingleMu condn
  }//event loop
  //////////////////////////////////////////////////////////////////////////

  ///////////////////// Signal 4 loop //////////////////////////////////
  for (Long64_t ievent = 0 ; ievent < trS4->GetEntries() ; ievent++ ) {    
    trS4->GetEntry(ievent) ;
    if(ievent%1000000==0)
      cout<<"iEvent : " << ievent << ", probS4 : "<<probS4<<endl;
    chad.SetPtEtaPhiE(jetChadPtS4, jetChadEtaS4, jetChadPhiS4, jetChadEnS4);
    shad.SetPtEtaPhiE(jetShadPtS4, jetShadEtaS4, jetShadPhiS4, jetShadEnS4);
    met.SetXYZM(metPxS4, metPyS4, metPzS4, 0.0);
    
    weightS4 = sampleWeightS4*prefireWeightS4*PUWeightS4*muEffWeightS4*bTagWeightS4;
    mjjKF = (chad+shad).M();
    
    if(singleMuS4 and !singleEleS4 and muonIsoCutS4 and met.Pt()>20.0){
      ptS4->Fill((chad+shad).Pt(),weightS4);
      for(int ip=0;ip<nPoints;ip++){
	xProb = ip*step ; 
	if(probS4>=xProb)
	  mjjS4[ip]->Fill(mjjKF,weightS4);
      }
    }//SingleMu condn
  }//event loop
  //////////////////////////////////////////////////////////////////////////

  ///////////////////// Signal 5 loop //////////////////////////////////
  for (Long64_t ievent = 0 ; ievent < trS5->GetEntries() ; ievent++ ) {    
    trS5->GetEntry(ievent) ;
    if(ievent%1000000==0)
      cout<<"iEvent : " << ievent << ", probS5 : "<<probS5<<endl;
    chad.SetPtEtaPhiE(jetChadPtS5, jetChadEtaS5, jetChadPhiS5, jetChadEnS5);
    shad.SetPtEtaPhiE(jetShadPtS5, jetShadEtaS5, jetShadPhiS5, jetShadEnS5);
    met.SetXYZM(metPxS5, metPyS5, metPzS5, 0.0);
    
    weightS5 = sampleWeightS5*prefireWeightS5*PUWeightS5*muEffWeightS5*bTagWeightS5;
    mjjKF = (chad+shad).M();
    
    if(singleMuS5 and !singleEleS5 and muonIsoCutS5 and met.Pt()>20.0){
      ptS5->Fill((chad+shad).Pt(),weightS5);
      for(int ip=0;ip<nPoints;ip++){
	xProb = ip*step ; 
	if(probS5>=xProb)
	  mjjS5[ip]->Fill(mjjKF,weightS5);
      }
    }//SingleMu condn
  }//event loop
  //////////////////////////////////////////////////////////////////////////

  
  for(int ip=0;ip<nPoints;ip++){
    xProb = ip*step ; 

    grS1ByB->SetPoint(ip, xProb, mjjS1[ip]->Integral()/(mjjS1[ip]->Integral() + mjj[ip]->Integral()));
    grS2ByB->SetPoint(ip, xProb, mjjS2[ip]->Integral()/(mjjS2[ip]->Integral() + mjj[ip]->Integral()));
    grS3ByB->SetPoint(ip, xProb, mjjS3[ip]->Integral()/(mjjS3[ip]->Integral() + mjj[ip]->Integral()));
    grS4ByB->SetPoint(ip, xProb, mjjS4[ip]->Integral()/(mjjS4[ip]->Integral() + mjj[ip]->Integral()));
    grS5ByB->SetPoint(ip, xProb, mjjS5[ip]->Integral()/(mjjS5[ip]->Integral() + mjj[ip]->Integral()));

    // grS1ByB->SetPoint(ip, xProb, mjjS1[ip]->Integral()/(mjj[ip]->Integral()));
    // grS2ByB->SetPoint(ip, xProb, mjjS2[ip]->Integral()/(mjj[ip]->Integral()));
    // grS3ByB->SetPoint(ip, xProb, mjjS3[ip]->Integral()/(mjj[ip]->Integral()));
    // grS4ByB->SetPoint(ip, xProb, mjjS4[ip]->Integral()/(mjj[ip]->Integral()));
    // grS5ByB->SetPoint(ip, xProb, mjjS5[ip]->Integral()/(mjj[ip]->Integral()));

    // grBReso->SetPoint(ip, xProb, mjj[ip]->GetRMS());
    // grSReso->SetPoint(ip, xProb, mjjS1[ip]->GetRMS());

    grBReso->SetPoint(ip, xProb, mjj[ip]->GetMean());
    grSReso->SetPoint(ip, xProb, mjjS1[ip]->GetMean());

    grBEff->SetPoint(ip, xProb, 0.8*mjj[ip]->Integral()/mjj[0]->Integral());
    //printf("x : %3.2f, S : %5.4f, B : %5.4f\n",xProb, mjjS1[ip]->Integral(),mjj[ip]->Integral());
    //grSByB->SetPoint(ip, mjjS[ip]->Integral()/mjj[ip]->Integral());
  }
  
  grBReso->SetMarkerStyle(kFullCircle);
  grSReso->SetMarkerStyle(kFullSquare);
  grBReso->SetMarkerColor(kRed);
  grSReso->SetMarkerColor(kBlue);
  grBReso->SetMinimum(0.0);
  grBReso->SetMaximum(100.0);
  TCanvas *c1 = new TCanvas("c1","c1");
  grBReso->Draw("AP");
  grSReso->Draw("P");
  
  grS1ByB->SetMarkerStyle(kFullCircle);
  grS2ByB->SetMarkerStyle(kFullSquare);
  grS3ByB->SetMarkerStyle(kFullCross);
  grS4ByB->SetMarkerStyle(kFullDiamond);
  grS5ByB->SetMarkerStyle(kFullStar);

  grS1ByB->SetMarkerColor(kRed);
  grS2ByB->SetMarkerColor(kBlue);
  grS3ByB->SetMarkerColor(kGreen);
  grS4ByB->SetMarkerColor(kBlack);
  grS5ByB->SetMarkerColor(kMagenta);
  
  grS1ByB->SetMarkerSize(1.2);
  grS2ByB->SetMarkerSize(1.0);
  grS3ByB->SetMarkerSize(1.2);
  grS4ByB->SetMarkerSize(1.5);
  grS5ByB->SetMarkerSize(1.5);
  TLegend *leg1 = new TLegend(0.414956,0.7284866,0.9794721,0.9406528,NULL,"brNDC");
  leg1->AddEntry(grS1ByB, Form("S/(S+B) with S = (m_{H^{+}} = 80 GeV) and B = %s",bkgname.c_str()) ,"lp");
  leg1->AddEntry(grS2ByB, Form("S/(S+B) with S = (m_{H^{+}} = 100 GeV) and B = %s",bkgname.c_str()) ,"lp");
  leg1->AddEntry(grS3ByB, Form("S/(S+B) with S = (m_{H^{+}} = 120 GeV) and B = %s",bkgname.c_str()) ,"lp");
  leg1->AddEntry(grS4ByB, Form("S/(S+B) with S = (m_{H^{+}} = 140 GeV) and B = %s",bkgname.c_str()) ,"lp");
  leg1->AddEntry(grS5ByB, Form("S/(S+B) with S = (m_{H^{+}} = 160 GeV) and B = %s",bkgname.c_str()) ,"lp");

  // leg1->AddEntry(grS1ByB, Form("S/B with S = (m_{H^{+}} = 80 GeV) and B = %s",bkgname.c_str()) ,"lp");
  // leg1->AddEntry(grS2ByB, Form("S/B with S = (m_{H^{+}} = 100 GeV) and B = %s",bkgname.c_str()) ,"lp");
  // leg1->AddEntry(grS3ByB, Form("S/B with S = (m_{H^{+}} = 120 GeV) and B = %s",bkgname.c_str()) ,"lp");
  // leg1->AddEntry(grS4ByB, Form("S/B with S = (m_{H^{+}} = 140 GeV) and B = %s",bkgname.c_str()) ,"lp");
  // leg1->AddEntry(grS5ByB, Form("S/B with S = (m_{H^{+}} = 160 GeV) and B = %s",bkgname.c_str()) ,"lp");
  grS1ByB->SetMinimum(0.0);
  grS1ByB->SetMaximum(1.5);
  TCanvas *c2 = new TCanvas("c2","c2");
  grS1ByB->Draw("AP");
  grS2ByB->Draw("P");
  grS3ByB->Draw("P");
  grS4ByB->Draw("P");
  grS5ByB->Draw("P");
  leg1->Draw();
  grS1ByB->GetXaxis()->SetTitle("Prob #chi^{2}");
  grS1ByB->GetYaxis()->SetTitle("S/(S+B)");
  //grS1ByB->GetYaxis()->SetTitle("S/B");
  c2->SetTickx();
  c2->SetTicky();

  // grBEff->SetMarkerStyle(kFullCircle);
  // TCanvas *c3 = new TCanvas("c3","c3");
  // grBEff->Draw("AP");
  
  // ptS1->Scale(1./ptS1->Integral());
  // ptS2->Scale(1./ptS2->Integral());
  // ptS3->Scale(1./ptS3->Integral());
  // ptS4->Scale(1./ptS4->Integral());
  // ptS5->Scale(1./ptS5->Integral());
  // ptB->Scale(1./ptB->Integral());
  // ptB->SetLineColor(kGray);
  // ptS1->SetLineColor(kRed);
  // ptS2->SetLineColor(kBlue);
  // ptS3->SetLineColor(kGreen);
  // ptS4->SetLineColor(kBlack);
  // ptS5->SetLineColor(kMagenta);


  // TCanvas *c4 = new TCanvas("c4","c4");
  // ptB->Draw("hist");
  // ptS1->Draw("hist sames");
  // ptS2->Draw("hist sames");
  // ptS3->Draw("hist sames");
  // ptS4->Draw("hist sames");
  // ptS5->Draw("hist sames");
  
  grS1ByB->SetName("grS1ByB");
  grS1ByB->SetTitle("");
  grBReso->SetName("grBReso");
  grBReso->SetTitle("grBReso");
  grSReso->SetName("grSReso");
  grSReso->SetTitle("grSReso");
  grBEff->SetName("grBEff");
  grBEff->SetTitle("grBEff");
  
  TFile *fout = new TFile(Form("output.root"),"recreate");
  for(int ip=0;ip<nPoints;ip++)
    mjjS1[ip]->Write();
  for(int ip=0;ip<nPoints;ip++)
    mjj[ip]->Write();
  ptB->Write();
  ptS1->Write();
  grS1ByB->Write();
  grS2ByB->Write();
  grS3ByB->Write();
  grS4ByB->Write();
  grS5ByB->Write();
  grBReso->Write();
  grSReso->Write();
  grBEff->Write();
  c2->Write();
  
  // fout->Close();
  // delete fout;

  return true;
}

int ProbChi2(void)
{

  // TH1F *hProb = new TH1F("hProb","hProb",200, -0.5, 1.5);
  // TProfile *probDelRRecKF = new TProfile("probDelRRecKF","probDelRRecKF",200, -0.5, 1.5, 0., 0.6);
  
  const int nPoints = 100;
  TGraph *grSByB = new TGraph(nPoints);
  TGraph *grBReso = new TGraph(nPoints);
  TGraph *grSReso = new TGraph(nPoints);
  TGraph *grBEff = new TGraph(nPoints);
  TH1F *mjj[nPoints], *mjjS[nPoints];
  for(int ip=0;ip<nPoints;ip++){
    mjj[ip] = new TH1F(Form("mjj_%02d",ip),Form("mjj_%02d",ip), 250, 0., 250.);
    mjjS[ip] = new TH1F(Form("mjjS_%02d",ip),Form("mjjS_%02d",ip), 250, 0., 250.);
  }
  TH1F *ptB = new TH1F("ptB","ptB", 140, 0., 700.);
  TH1F *ptS = new TH1F("ptS","ptS", 140, 0., 700.);

  Double_t  prob;
  Float_t   jetChadPt, jetChadEta, jetChadPhi, jetChadEn;
  Float_t   jetShadPt, jetShadEta, jetShadPhi, jetShadEn;
  Float_t   metPx, metPy, metPz;

  Double_t sampleWeight, prefireWeight, PUWeight, muEffWeight, bTagWeight;
  Bool_t singleMu, singleEle, muonIsoCut, isLowMET;
  Double_t weight;

  Double_t  probS;
  Float_t   jetChadPtS, jetChadEtaS, jetChadPhiS, jetChadEnS;
  Float_t   jetShadPtS, jetShadEtaS, jetShadPhiS, jetShadEnS;
  Float_t   metPxS, metPyS, metPzS;

  Double_t sampleWeightS, prefireWeightS, PUWeightS, muEffWeightS, bTagWeightS;
  Bool_t singleMuS, singleEleS, muonIsoCutS, isLowMETS;
  Double_t weightS;
  
  TChain *tr	= new TChain("Kinfit_Reco");
  TChain *trS	= new TChain("Kinfit_Reco");
  
  string infile_tree = "input/files_ttbar.txt";
  ifstream fin(infile_tree);
  string s;
  while(getline(fin,s)){
    cout << "Add file " << s << endl;
    tr->Add(s.c_str());
  }
  fin.close();

  infile_tree = "input/files_hplusM160.txt";
  fin.open(infile_tree);
  while(getline(fin,s)){
    cout << "Add file " << s << endl;
    trS->Add(s.c_str());
  }
  fin.close();
  
  /////////////// TTbar tree Branches /////////////////////////
  tr->SetBranchAddress("prob"		, &prob);
  tr->SetBranchAddress("jetChadPt"	, &jetChadPt);
  tr->SetBranchAddress("jetChadEta"	, &jetChadEta);
  tr->SetBranchAddress("jetChadPhi"	, &jetChadPhi);
  tr->SetBranchAddress("jetChadEnergy"	, &jetChadEn);
  tr->SetBranchAddress("jetShadPt"	, &jetShadPt);
  tr->SetBranchAddress("jetShadEta"	, &jetShadEta);
  tr->SetBranchAddress("jetShadPhi"	, &jetShadPhi);
  tr->SetBranchAddress("jetShadEnergy"	, &jetShadEn);
  tr->SetBranchAddress("metPx"		, &metPx);
  tr->SetBranchAddress("metPy"		, &metPy);
  tr->SetBranchAddress("metPz"		, &metPz);

  tr->SetBranchAddress("sampleWeight"	, &sampleWeight);
  tr->SetBranchAddress("prefireWeight"	, &prefireWeight);
  tr->SetBranchAddress("PUWeight"	, &PUWeight);
  tr->SetBranchAddress("muEffWeight"	, &muEffWeight);
  tr->SetBranchAddress("bTagWeight"	, &bTagWeight);
  tr->SetBranchAddress("singleMu"	, &singleMu);
  tr->SetBranchAddress("singleEle"	, &singleEle);
  tr->SetBranchAddress("muonIsoCut"	, &muonIsoCut);
  tr->SetBranchAddress("isLowMET"	, &isLowMET);
  /////////////////////////////////////////////////////////////

  /////////////// Signal tree Branches /////////////////////////
  trS->SetBranchAddress("prob"		, &probS);
  trS->SetBranchAddress("jetChadPt"	, &jetChadPtS);
  trS->SetBranchAddress("jetChadEta"	, &jetChadEtaS);
  trS->SetBranchAddress("jetChadPhi"	, &jetChadPhiS);
  trS->SetBranchAddress("jetChadEnergy"	, &jetChadEnS);
  trS->SetBranchAddress("jetShadPt"	, &jetShadPtS);
  trS->SetBranchAddress("jetShadEta"	, &jetShadEtaS);
  trS->SetBranchAddress("jetShadPhi"	, &jetShadPhiS);
  trS->SetBranchAddress("jetShadEnergy"	, &jetShadEnS);
  trS->SetBranchAddress("metPx"		, &metPxS);
  trS->SetBranchAddress("metPy"		, &metPyS);
  trS->SetBranchAddress("metPz"		, &metPzS);
  trS->SetBranchAddress("sampleWeight"	, &sampleWeightS);
  trS->SetBranchAddress("prefireWeight"	, &prefireWeightS);
  trS->SetBranchAddress("PUWeight"	, &PUWeightS);
  trS->SetBranchAddress("muEffWeight"	, &muEffWeightS);
  trS->SetBranchAddress("bTagWeight"	, &bTagWeightS);
  trS->SetBranchAddress("singleMu"	, &singleMuS);
  trS->SetBranchAddress("singleEle"	, &singleEleS);
  trS->SetBranchAddress("muonIsoCut"	, &muonIsoCutS);
  trS->SetBranchAddress("isLowMET"	, &isLowMETS);
  /////////////////////////////////////////////////////////////

  TLorentzVector chad, shad, met;
  
  cout << "Total Entries (MC) : " << tr->GetEntries() << endl;
  cout << "Total Entries (Signal) : " << trS->GetEntries() << endl;
  
  double step = 1.0/nPoints;
  double xProb, mjjKF ;
  
  for (Long64_t ievent = 0 ; ievent < tr->GetEntries() ; ievent++ ) {    
  //for (Long64_t ievent = 0 ; ievent < 20000 ; ievent++ ) {    
    
    tr->GetEntry(ievent) ;
    if(ievent%1000000==0)
      cout<<"iEvent : " << ievent << ", prob : "<<prob<<endl;
    chad.SetPtEtaPhiE(jetChadPt, jetChadEta, jetChadPhi, jetChadEn);
    shad.SetPtEtaPhiE(jetShadPt, jetShadEta, jetShadPhi, jetShadEn);
    met.SetXYZM(metPx, metPy, metPz, 0.0);
    
    weight = sampleWeight*prefireWeight*PUWeight*muEffWeight*bTagWeight;
    mjjKF = (chad+shad).M();
    
    //if((chad+shad).Pt()<200.0) continue ;
    
    if(singleMu and !singleEle and muonIsoCut and met.Pt()>20.0){
      ptB->Fill((chad+shad).Pt(),weight);
      for(int ip=0;ip<nPoints;ip++){
	xProb = ip*step ; 
	if(prob>=xProb)
	  mjj[ip]->Fill(mjjKF,weight);
      }
      
    }//SingleMu condn
  }//event loop
  
  for (Long64_t ievent = 0 ; ievent < trS->GetEntries() ; ievent++ ) {    
  //for (Long64_t ievent = 0 ; ievent < 20000 ; ievent++ ) {    
    
    trS->GetEntry(ievent) ;
    if(ievent%1000000==0)
      cout<<"iEvent : " << ievent << ", prob : "<<probS<<endl;
    chad.SetPtEtaPhiE(jetChadPtS, jetChadEtaS, jetChadPhiS, jetChadEnS);
    shad.SetPtEtaPhiE(jetShadPtS, jetShadEtaS, jetShadPhiS, jetShadEnS);
    met.SetXYZM(metPxS, metPyS, metPzS, 0.0);
    
    weightS = sampleWeightS*prefireWeightS*PUWeightS*muEffWeightS*bTagWeightS;
    mjjKF = (chad+shad).M();
    
    //if((chad+shad).Pt()<200.0) continue ;

    if(singleMuS and !singleEleS and muonIsoCutS and met.Pt()>20.0){
      ptS->Fill((chad+shad).Pt(),weightS);
      for(int ip=0;ip<nPoints;ip++){
	xProb = ip*step ; 
	if(probS>=xProb)
	  mjjS[ip]->Fill(mjjKF,weightS);
      }
      
    }//SingleMu condn
  }//event loop
  
  for(int ip=0;ip<nPoints;ip++){
    xProb = ip*step ; 
    // if(prob>=xProb)
    //   mjjS[ip]->Fill(mjjKF,weightS);
    grSByB->SetPoint(ip, xProb, mjjS[ip]->Integral()/mjj[ip]->Integral());
    grBReso->SetPoint(ip, xProb, mjj[ip]->GetRMS());
    grSReso->SetPoint(ip, xProb, mjjS[ip]->GetRMS());
    grBEff->SetPoint(ip, xProb, 0.8*mjj[ip]->Integral()/mjj[0]->Integral());
    printf("x : %3.2f, S : %5.4f, B : %5.4f\n",xProb, mjjS[ip]->Integral(),mjj[ip]->Integral());
    //grSByB->SetPoint(ip, mjjS[ip]->Integral()/mjj[ip]->Integral());
  }
  
  grBReso->SetMarkerStyle(kFullCircle);
  grSReso->SetMarkerStyle(kFullSquare);
  grBReso->SetMinimum(0.0);
  grBReso->SetMaximum(50.0);
  TCanvas *c1 = new TCanvas("c1","c1");
  grBReso->Draw("AP");
  grSReso->Draw("P");
  
  grSByB->SetMarkerStyle(kFullCircle);
  TCanvas *c2 = new TCanvas("c2","c2");
  grSByB->Draw("AP");

  grBEff->SetMarkerStyle(kFullCircle);
  TCanvas *c3 = new TCanvas("c3","c3");
  grBEff->Draw("AP");
  
  ptS->Scale(1./ptS->Integral());
  ptB->Scale(1./ptB->Integral());
  ptB->SetLineColor(kBlue);
  ptS->SetLineColor(kRed);
  TCanvas *c4 = new TCanvas("c4","c4");
  ptB->Draw("hist");
  ptS->Draw("hist sames");
  
  grSByB->SetName("grSByB");
  grSByB->SetTitle("grSByB");
  grBReso->SetName("grBReso");
  grBReso->SetTitle("grBReso");
  grSReso->SetName("grSReso");
  grSReso->SetTitle("grSReso");
  grBEff->SetName("grBEff");
  grBEff->SetTitle("grBEff");
  
  TFile *fout = new TFile(Form("output.root"),"recreate");
  for(int ip=0;ip<nPoints;ip++)
    mjjS[ip]->Write();
  for(int ip=0;ip<nPoints;ip++)
    mjj[ip]->Write();
  ptB->Write();
  ptS->Write();
  grSByB->Write();
  grBReso->Write();
  grSReso->Write();
  grBEff->Write();
  
  return true;
}


int MassDist()
{
  TH1F *mjj = new TH1F("mjj","mjj (Inclussive)", 50, 0., 250.);
  TH1F *mjj_cut1 = new TH1F("mjj_cut1","mjj (#chi^2 < 50.)", 50, 0., 250.);
  TH1F *mjj_cut2 = new TH1F("mjj_cut2","mjj (#chi^2 < 20.)", 50, 0., 250.);
  TH1F *mjj_cut3 = new TH1F("mjj_cut3","mjj (#chi^2 < 8.)", 50, 0., 250.);
  
  TH1F *hhtopMass = new TH1F("hhtopMass","htopMass", 500, 0., 500.);
  TH1F *hltopMass = new TH1F("hltopMass","ltopMass", 500, 0., 500.);
  TH1F *hlWMass = new TH1F("hlWMass","lWMass", 500, 0., 500.);
  
  Double_t  chi2;
  
  Float_t   jetChadPt;
  Float_t   jetChadEta;
  Float_t   jetChadPhi;  
  Float_t   jetChadEn;

  Float_t   jetShadPt;
  Float_t   jetShadEta;
  Float_t   jetShadPhi;
  Float_t   jetShadEn;

  Float_t   metPx;
  Float_t   metPy;
  Float_t   metPz;
  
  Float_t   jetBhadPt;
  Float_t   jetBhadEta;
  Float_t   jetBhadPhi;  
  Float_t   jetBhadEn;

  Float_t   jetBlepPt;
  Float_t   jetBlepEta;
  Float_t   jetBlepPhi;
  Float_t   jetBlepEn;

  Float_t   lepPt;
  Float_t   lepEta;
  Float_t   lepPhi;
  Float_t   lepEn;

  Double_t sampleWeight;
  Double_t prefireWeight;
  Double_t PUWeight;
  Double_t muEffWeight;
  Double_t bTagWeight;
  Bool_t singleMu;
  Bool_t singleEle;
  Bool_t muonIsoCut;
  Bool_t isLowMET;
  Double_t weight, mjjKF;
  Double_t htopMass,ltopMass,lWMass;

  //TFile *finhist      = TFile::Open("/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/grid_v39_Syst/CBA_ProbChi2/2018/all_HplusM120.root");
  //TFile *finhist      = TFile::Open("/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/grid_v39_Syst/CBA_ProbChi2/2018/all_TTbar.root");
  //TFile *finhist      = TFile::Open("/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/grid_v39_Syst/CBA_ProbChi2/2018/all_DataMu.root");
  TFile *finhist      = TFile::Open("/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/grid_v39_Syst/CBA_ProbChi2/2018/all_DataEle.root");
  cout<<"filename : " << finhist->GetName() << endl;
  
  TChain *tr	= new TChain("Kinfit_Reco");
  //string infile_tree = "input/files_hplusM120.txt";
  //string infile_tree = "input/files_ttbar.txt";
  //string infile_tree = "input/files_datamu.txt";
  string infile_tree = "input/files_dataele.txt";
  ifstream fin(infile_tree);
  string s;
  while(getline(fin,s)){
    cout << "Add file " << s << endl;
    tr->Add(s.c_str());
  }
  fin.close();
  
  // TH1F *hMjjSaved = (TH1F *)finhist->Get("TTbar/base/Iso/_kb_mjj_mu");
  // TH1F *hChi2Min1 = (TH1F *)finhist->Get("TTbar/base/Iso/hMinChi2_mu");
  // TH1F *hChi2Min2 = (TH1F *)finhist->Get("TTbar/base/Iso/h2MinChi2_mu");
  // TH1F *hChi2Min3 = (TH1F *)finhist->Get("TTbar/base/Iso/h3MinChi2_mu");
  // TH1F *hChi2Min4 = (TH1F *)finhist->Get("TTbar/base/Iso/h4MinChi2_mu");
  // TH1F *hChi2Min5 = (TH1F *)finhist->Get("TTbar/base/Iso/h5MinChi2_mu");
  
  // TH1F *hMjjSaved = (TH1F *)finhist->Get("HplusM120/base/Iso/_kb_mjj_mu");
  // TH1F *hChi2Min1 = (TH1F *)finhist->Get("HplusM120/base/Iso/hMinChi2_mu");
  // TH1F *hChi2Min2 = (TH1F *)finhist->Get("HplusM120/base/Iso/h2MinChi2_mu");
  // TH1F *hChi2Min3 = (TH1F *)finhist->Get("HplusM120/base/Iso/h3MinChi2_mu");
  // TH1F *hChi2Min4 = (TH1F *)finhist->Get("HplusM120/base/Iso/h4MinChi2_mu");
  // TH1F *hChi2Min5 = (TH1F *)finhist->Get("HplusM120/base/Iso/h5MinChi2_mu");
  
  // TH1F *hMjjSaved = (TH1F *)finhist->Get("DataMu/base/Iso/_kb_mjj_mu");
  // TH1F *hChi2Min1 = (TH1F *)finhist->Get("DataMu/base/Iso/hMinChi2_mu");
  // TH1F *hChi2Min2 = (TH1F *)finhist->Get("DataMu/base/Iso/h2MinChi2_mu");
  // TH1F *hChi2Min3 = (TH1F *)finhist->Get("DataMu/base/Iso/h3MinChi2_mu");
  // TH1F *hChi2Min4 = (TH1F *)finhist->Get("DataMu/base/Iso/h4MinChi2_mu");
  // TH1F *hChi2Min5 = (TH1F *)finhist->Get("DataMu/base/Iso/h5MinChi2_mu");
  
  TH1F *hMjjSaved = (TH1F *)finhist->Get("DataEle/base/Iso/_kb_mjj_mu");
  TH1F *hChi2Min1 = (TH1F *)finhist->Get("DataEle/base/Iso/hMinChi2_mu");
  TH1F *hChi2Min2 = (TH1F *)finhist->Get("DataEle/base/Iso/h2MinChi2_mu");
  TH1F *hChi2Min3 = (TH1F *)finhist->Get("DataEle/base/Iso/h3MinChi2_mu");
  TH1F *hChi2Min4 = (TH1F *)finhist->Get("DataEle/base/Iso/h4MinChi2_mu");
  TH1F *hChi2Min5 = (TH1F *)finhist->Get("DataEle/base/Iso/h5MinChi2_mu");
  
  tr->SetBranchAddress("chi2"		, &chi2);
  tr->SetBranchAddress("jetChadPt"	, &jetChadPt);
  tr->SetBranchAddress("jetChadEta"	, &jetChadEta);
  tr->SetBranchAddress("jetChadPhi"	, &jetChadPhi);
  tr->SetBranchAddress("jetChadEnergy"	, &jetChadEn);
  tr->SetBranchAddress("jetShadPt"	, &jetShadPt);
  tr->SetBranchAddress("jetShadEta"	, &jetShadEta);
  tr->SetBranchAddress("jetShadPhi"	, &jetShadPhi);
  tr->SetBranchAddress("jetShadEnergy"	, &jetShadEn);
  tr->SetBranchAddress("metPx"		, &metPx);
  tr->SetBranchAddress("metPy"		, &metPy);
  tr->SetBranchAddress("metPz"		, &metPz);
  tr->SetBranchAddress("jetBhadPt"	, &jetBhadPt);
  tr->SetBranchAddress("jetBhadEta"	, &jetBhadEta);
  tr->SetBranchAddress("jetBhadPhi"	, &jetBhadPhi);
  tr->SetBranchAddress("jetBhadEnergy"	, &jetBhadEn);
  tr->SetBranchAddress("jetBlepPt"	, &jetBlepPt);
  tr->SetBranchAddress("jetBlepEta"	, &jetBlepEta);
  tr->SetBranchAddress("jetBlepPhi"	, &jetBlepPhi);
  tr->SetBranchAddress("jetBlepEnergy"	, &jetBlepEn);
  tr->SetBranchAddress("lepPt"	, &lepPt);
  tr->SetBranchAddress("lepEta"	, &lepEta);
  tr->SetBranchAddress("lepPhi"	, &lepPhi);
  tr->SetBranchAddress("lepEnergy"	, &lepEn);

  tr->SetBranchAddress("sampleWeight"	, &sampleWeight);
  tr->SetBranchAddress("prefireWeight"	, &prefireWeight);
  tr->SetBranchAddress("PUWeight"	, &PUWeight);
  tr->SetBranchAddress("muEffWeight"	, &muEffWeight);
  tr->SetBranchAddress("bTagWeight"	, &bTagWeight);
  tr->SetBranchAddress("singleMu"	, &singleMu);
  tr->SetBranchAddress("singleEle"	, &singleEle);
  tr->SetBranchAddress("muonIsoCut"	, &muonIsoCut);
  tr->SetBranchAddress("isLowMET"	, &isLowMET);

  TLorentzVector chad, shad, met, bhad, blep, lep;
  
  cout << "Total Entries : " << tr->GetEntries() << endl;
  for (Long64_t ievent = 0 ; ievent < tr->GetEntries() ; ievent++ ) {    
  //for (Long64_t ievent = 0 ; ievent < 20000 ; ievent++ ) {    
    
    tr->GetEntry(ievent) ;
    if(ievent%1000000==0)
      cout<<"iEvent : " << ievent << ", chi2 : "<<chi2<<endl;
    chad.SetPtEtaPhiE(jetChadPt, jetChadEta, jetChadPhi, jetChadEn);
    shad.SetPtEtaPhiE(jetShadPt, jetShadEta, jetShadPhi, jetShadEn);
    met.SetXYZM(metPx, metPy, metPz, 0.0);
    bhad.SetPtEtaPhiE(jetBhadPt, jetBhadEta, jetBhadPhi, jetBhadEn);
    blep.SetPtEtaPhiE(jetBlepPt, jetBlepEta, jetBlepPhi, jetBlepEn);
    lep.SetPtEtaPhiE(lepPt, lepEta, lepPhi, lepEn);

    weight = sampleWeight*prefireWeight*PUWeight*muEffWeight*bTagWeight;
    mjjKF = (chad+shad).M();
    htopMass = (chad+shad+bhad).M();
    ltopMass = (met+lep+blep).M();
    lWMass = (met+lep).M();
    //if(singleMu and !singleEle and muonIsoCut and !isLowMET){
    if(singleMu and !singleEle and muonIsoCut and met.Pt()>20.0){
      mjj->Fill(mjjKF,weight);
      if(chi2<50.) mjj_cut1->Fill(mjjKF,weight);
      if(chi2<20.) mjj_cut2->Fill(mjjKF,weight);
      if(chi2<8.) mjj_cut3->Fill(mjjKF,weight);
      hhtopMass->Fill(htopMass,weight);
      hltopMass->Fill(ltopMass,weight);
      hlWMass->Fill(lWMass,weight);
    }
  }//event loop
  

  hMjjSaved->SetLineColor(kBlue);
  mjj->SetLineColor(kRed);
  mjj->SetLineWidth(2);
  mjj_cut1->SetLineColor(kBlue);
  mjj_cut1->SetLineWidth(2);
  mjj_cut2->SetLineColor(kGreen);
  mjj_cut2->SetLineWidth(2);
  mjj_cut3->SetLineColor(kMagenta);
  mjj_cut3->SetLineWidth(2);

  gStyle->SetOptStat(1112111);
  gStyle->SetOptFit(11);
  
  TF1 *fn = new TF1("fn","gaus",60.,100.);
  TCanvas *c1 = new TCanvas("c1","c1");
  mjj->Draw("hist");
  mjj_cut1->Draw("hist sames");
  mjj_cut2->Draw("hist sames");
  mjj_cut3->Draw("hist sames");
  hMjjSaved->Draw("hist sames");
  mjj->Fit("fn","LR");
  mjj_cut1->Fit("fn","LR");
  mjj_cut2->Fit("fn","LR");
  mjj_cut3->Fit("fn","LR");
  hMjjSaved->Fit("fn","LR");
  
  hChi2Min1->SetLineColor(kRed);
  hChi2Min1->SetLineWidth(2);
  hChi2Min2->SetLineColor(kBlue);
  hChi2Min2->SetLineWidth(2);
  hChi2Min3->SetLineColor(kGreen);
  hChi2Min3->SetLineWidth(2);
  hChi2Min4->SetLineColor(kMagenta);
  hChi2Min4->SetLineWidth(2);
  hChi2Min5->SetLineColor(kOrange+1);
  hChi2Min5->SetLineWidth(2);
  
  TCanvas *c2 = new TCanvas("c2","c2");
  hChi2Min1->Draw();
  hChi2Min2->Draw("sames");
  hChi2Min3->Draw("sames");
  hChi2Min4->Draw("sames");
  hChi2Min5->Draw("sames");

  hhtopMass->SetLineColor(kRed);
  hltopMass->SetLineColor(kBlue);
  hlWMass->SetLineColor(kGreen);

  TCanvas *c3 = new TCanvas("c3","c3");
  hlWMass->Draw("hist ");
  hhtopMass->Draw("hist sames");
  hltopMass->Draw("hist sames");
  hlWMass->Draw("hist sames");
  
  TFile *fout = new TFile(Form("output.root"),"recreate");
  mjj->Write();
  mjj_cut1->Write();
  mjj_cut2->Write();
  mjj_cut3->Write();
  hMjjSaved->Write();
  hhtopMass->Write();
  hltopMass->Write();
  hlWMass->Write();
  c1->Write();
  c2->Write();
  fout->Close();
  delete fout;
  
  return true;
}
