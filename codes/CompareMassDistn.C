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

#include "TLegend.h"

#include <fstream>

using namespace std;

#endif


int CompareMassDistn()
{
  TFile *fin_ttbar_reco = TFile::Open("root_files/test/ttbar_reco_output.root");
  TFile *fin_ttbar_kin = TFile::Open("root_files/test/ttbar_kine_output.root");
  TFile *fin_datamu = TFile::Open("root_files/test/datamu_reco_output.root");
  TFile *fin_dataele = TFile::Open("root_files/test/dataele_reco_output.root");
  
  // TH1F *httbar_reco = (TH1F *)fin_ttbar_reco->Get("hhtopMass");
  // TH1F *httbar_kin = (TH1F *)fin_ttbar_kin->Get("ttbar");
  // TH1F *hdatamu = (TH1F *)fin_datamu->Get("hhtopMass");
  // TH1F *hdataele = (TH1F *)fin_dataele->Get("hhtopMass");

  // TH1F *httbar_reco = (TH1F *)fin_ttbar_reco->Get("hltopMass");
  // TH1F *httbar_kin = (TH1F *)fin_ttbar_kin->Get("ttbar");
  // TH1F *hdatamu = (TH1F *)fin_datamu->Get("hltopMass");
  // TH1F *hdataele = (TH1F *)fin_dataele->Get("hltopMass");

  TH1F *httbar_reco = (TH1F *)fin_ttbar_reco->Get("hlWMass");
  TH1F *httbar_kin = (TH1F *)fin_ttbar_kin->Get("WPlusMinus");
  TH1F *hdatamu = (TH1F *)fin_datamu->Get("hlWMass");
  TH1F *hdataele = (TH1F *)fin_dataele->Get("hlWMass");

  httbar_reco->Scale(1./httbar_reco->Integral());
  httbar_kin->Scale(1./httbar_kin->Integral());
  hdatamu->Scale(1./hdatamu->Integral());
  hdataele->Scale(1./hdataele->Integral());

  httbar_kin->SetLineColor(kRed);
  httbar_reco->SetLineColor(kBlue);
  hdatamu->SetLineColor(kMagenta);
  hdataele->SetLineColor(kGreen);

  httbar_kin->SetLineWidth(3);
  httbar_reco->SetLineWidth(3);
  hdatamu->SetLineWidth(3);
  hdataele->SetLineWidth(3);
  
  TLegend *leg1 = new TLegend(0.414956,0.7284866,0.9794721,0.9406528,NULL,"brNDC");
  // leg1->AddEntry(httbar_reco, "Reco (SM #it{t#bar{t}}) : Top mass using the vector sum of b-jet and two soft jets" ,"lp");
  // leg1->AddEntry(hdatamu, "Reco (Data Muon): Top mass using the vector sum of b-jet and two soft jets" ,"lp");
  leg1->AddEntry(httbar_reco, "Reco (SM #it{t#bar{t}}) : W mass distn using the vector sum of lepton + MET" ,"lp");
  leg1->AddEntry(hdatamu, "Reco (Data Muon): W mass distn using the vector sum of lepton + MET" ,"lp");
  leg1->AddEntry(httbar_kin, "KineTree: W mass distn at MC level" ,"lp");


  httbar_reco->SetMaximum(1.0);
  TCanvas *c1 = new TCanvas("c1","c1");
  httbar_reco->Draw("hist");
  httbar_kin->Draw("hist sames");
  hdatamu->Draw("hist sames");
  leg1->Draw();
  httbar_reco->GetXaxis()->SetTitle("mass (GeV)");
  httbar_reco->GetYaxis()->SetTitle("Prob.");
  //hdataele->Draw("hist sames");

  return true;
}
