/**********************************************************************
 Created on : 05/03/2022
 Purpose    : Test the Chi2 distributions
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

#include "TRandom.h"

#include <fstream>

using namespace std;

#endif


int Chi2Tests()
{
  
  TH1F *hchi2 = new TH1F("hchi2","chi2", 250, 0., 5.);
  TH1F *hchi2ndf = new TH1F("hchi2ndf","chi2ndf", 250, 0., 5.);
  
  TH1F *hchi1df = new TH1F("hchi1df","hchi1df", 250, 0., 5.);
  TH1F *hchi2df = new TH1F("hchi2df","hchi2df", 250, 0., 5.);
  TH1F *hchi3df = new TH1F("hchi3df","hchi3df", 250, 0., 5.);
  
  TH1F *hprob1df = new TH1F("hprob1df","hprob1df", 120, -0.1, 1.1);
  TH1F *hprob2df = new TH1F("hprob2df","hprob2df", 120, -0.1, 1.1);
  TH1F *hprob3df = new TH1F("hprob3df","hprob3df", 120, -0.1, 1.1);
  
  Double_t  chi2;
  Int_t  ndf;
  
  // TFile *fin	= TFile::Open("/home/indra/temp/HminusM120_tree_base_1of1.root");
  
  // cout<<"filename : " << fin->GetName() << endl;
  // TTree *tr	= (TTree*)fin->Get("Kinfit_Reco");
  
  // tr->SetBranchAddress("chi2"		, &chi2);
  // tr->SetBranchAddress("ndf"		, &ndf);

  // cout << "Total Entries : " << tr->GetEntries() << endl;
  // for (Long64_t ievent = 0 ; ievent < tr->GetEntries() ; ievent++ ) {    
  // //for (Long64_t ievent = 0 ; ievent < 10 ; ievent++ ) {    
    
  //   tr->GetEntry(ievent) ;
  //   if(ievent%1000000==0)
  //     cout<<"iEvent : " << ievent << ", chi2 : "<<chi2<<endl;
    
  //   hchi2->Fill(chi2);
  //   hchi2ndf->Fill(chi2*double(ndf));
  //   //cout <<"chi2 : " << chi2 << ", chi2/ndf : " << chi2/double(ndf) << endl;
    
  // }//event loop
  // fin->Close();
  // delete fin;
  
  for (Long64_t ievent = 0 ; ievent < 10000000 ; ievent++ ) {    
    
    double z1 = gRandom->Gaus();
    double z2 = gRandom->Gaus();
    double z3 = gRandom->Gaus();
    
    double prob1 = z1*z1;
    double prob2 = prob1 + z2*z2;
    double prob3 = prob2 + z3*z3;
    
    hchi1df->Fill(prob1);
    hchi2df->Fill(prob2);
    hchi3df->Fill(prob3);

    hprob1df->Fill(TMath::Prob(prob1,1));
    hprob2df->Fill(TMath::Prob(prob2,2));
    hprob3df->Fill(TMath::Prob(prob3,3));
  }
  
  hchi2->SetLineColor(kRed);
  //TF1 *fn = new TF1("fn","gaus",60.,100.);
  TCanvas *c1 = new TCanvas("c1","c1");
  hchi2->Draw("hist");
  //hchi2ndf->Draw("hist sames");
  
  hchi1df->SetLineColor(kRed);
  hchi2df->SetLineColor(kBlue);
  hchi3df->SetLineColor(kGreen);

  TCanvas *c2 = new TCanvas("c2","c2");
  hchi1df->Draw();
  hchi2df->Draw("sames");
  hchi3df->Draw("sames");

  hprob1df->SetLineColor(kRed);
  hprob2df->SetLineColor(kBlue);
  hprob3df->SetLineColor(kGreen);

  TCanvas *c3 = new TCanvas("c3","c3");
  hprob1df->Draw();
  hprob2df->Draw("sames");
  hprob3df->Draw("sames");

  return true;
}
