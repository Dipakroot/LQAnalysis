/**********************************************************************
 Created on : 14/07/2021
 Purpose    : Prepare the btag efficiency histogram.
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

int CreateBtagEff()
{
  //int nofFiles = 3;
  //const char *NthCh[] = {"TTbarPowheg_Dilepton", "TTbarPowheg_Hadronic", "TTbarPowheg_Semilept"};
  // int nofFiles = 4;
  // const char *NthCh[] = {"ST_s_channel", "ST_tbar_channel", "ST_tW_channel", "ST_tbarW_channel"};
  // int nofFiles = 5;
  // const char *NthCh[] = {"Wjets", "W1jets", "W2jets", "W3jets", "W4jets"};  
  // int nofFiles = 5;
  // const char *NthCh[] = {"DYjetsM50_ext1", "DY1jetsM50", "DY2jetsM50", "DY3jetsM50", "DY4jetsM50"};  
  // int nofFiles = 3;
  // const char *NthCh[] = {"WW", "WZ", "ZZ"};  
  int nofFiles = 1;
  const char *NthCh[] = {"HplusM120"};  
  
  TH2D *h2_tot_BTagEff_Denom_b = 0x0;
  TH2D *h2_tot_BTagEff_Denom_c = 0x0;
  TH2D *h2_tot_BTagEff_Denom_udsg = 0x0;
  TH2D *h2_tot_BTagEff_Num_b = 0x0;
  TH2D *h2_tot_BTagEff_Num_c = 0x0;
  TH2D *h2_tot_BTagEff_Num_udsg = 0x0;

  //TFile *fout = new TFile("TTbar_btag_efficiency.root","recreate");
  //TFile *fout = new TFile("singleTop_btag_efficiency.root","recreate");
  //TFile *fout = new TFile("Wjets_btag_efficiency.root","recreate");
  //TFile *fout = new TFile("DYjets_btag_efficiency.root","recreate");
  //TFile *fout = new TFile("VBFusion_btag_efficiency.root","recreate");
  TFile *fout = new TFile("HplusM120_btag_efficiency.root","recreate");
  
  for(int ifile = 0 ; ifile < nofFiles ; ifile++ ){
    TFile *f = TFile::Open(Form("root_files/btag_raw/%s_btag_eff_raw.root",NthCh[ifile]));

    if(!f) continue;

    //TString histPath("myMiniTreeProducer/Jets/");
    TString histPath("");

    TH2D *h2_BTagEff_Denom_b              = (TH2D*)(f->Get(histPath+"h2_BTagEff_Denom_b"));
    TH2D *h2_BTagEff_Denom_c              = (TH2D*)(f->Get(histPath+"h2_BTagEff_Denom_c"));
    TH2D *h2_BTagEff_Denom_udsg           = (TH2D*)(f->Get(histPath+"h2_BTagEff_Denom_udsg"));
    TH2D *h2_BTagEff_Num_bM               = (TH2D*)(f->Get(histPath+"h2_BTagEff_Num_bM"));
    TH2D *h2_BTagEff_Num_cM               = (TH2D*)(f->Get(histPath+"h2_BTagEff_Num_cM"));
    TH2D *h2_BTagEff_Num_udsgM            = (TH2D*)(f->Get(histPath+"h2_BTagEff_Num_udsgM"));
    
    h2_BTagEff_Num_bM->Sumw2();
    h2_BTagEff_Num_cM->Sumw2();
    h2_BTagEff_Num_udsgM->Sumw2();
    h2_BTagEff_Denom_b->Sumw2();
    h2_BTagEff_Denom_c->Sumw2();
    h2_BTagEff_Denom_udsg->Sumw2();

    TH2D *h2_BTagEff_Ratio_b = (TH2D*)h2_BTagEff_Num_bM->Clone(Form("%s_b_efficiency",NthCh[ifile]));
    TH2D *h2_BTagEff_Ratio_c = (TH2D*)h2_BTagEff_Num_cM->Clone(Form("%s_c_efficiency",NthCh[ifile]));
    TH2D *h2_BTagEff_Ratio_udsg = (TH2D*)h2_BTagEff_Num_udsgM->Clone(Form("%s_l_efficiency",NthCh[ifile]));
    h2_BTagEff_Ratio_b->Divide(h2_BTagEff_Denom_b);
    h2_BTagEff_Ratio_c->Divide(h2_BTagEff_Denom_c);
    h2_BTagEff_Ratio_udsg->Divide(h2_BTagEff_Denom_udsg);

    fout->cd();
    h2_BTagEff_Ratio_b->Write();
    h2_BTagEff_Ratio_c->Write();
    h2_BTagEff_Ratio_udsg->Write();


    if(!h2_tot_BTagEff_Denom_b)
      h2_tot_BTagEff_Denom_b = (TH2D *)h2_BTagEff_Denom_b->Clone("h2_tot_BTagEff_Denom_b");
    else
      h2_tot_BTagEff_Denom_b->Add(h2_BTagEff_Denom_b);
    if(!h2_tot_BTagEff_Denom_c)
      h2_tot_BTagEff_Denom_c = (TH2D *)h2_BTagEff_Denom_c->Clone("h2_tot_BTagEff_Denom_c");
    else
      h2_tot_BTagEff_Denom_c->Add(h2_BTagEff_Denom_c);
    if(!h2_tot_BTagEff_Denom_udsg)
      h2_tot_BTagEff_Denom_udsg = (TH2D *)h2_BTagEff_Denom_udsg->Clone("h2_tot_BTagEff_Denom_udsg");
    else
      h2_tot_BTagEff_Denom_udsg->Add(h2_BTagEff_Denom_udsg);
    if(!h2_tot_BTagEff_Num_b)
      h2_tot_BTagEff_Num_b = (TH2D *)h2_BTagEff_Num_bM->Clone("h2_tot_BTagEff_Num_b");
    else
      h2_tot_BTagEff_Num_b->Add(h2_BTagEff_Num_bM);
    if(!h2_tot_BTagEff_Num_c)
      h2_tot_BTagEff_Num_c = (TH2D *)h2_BTagEff_Num_cM->Clone("h2_tot_BTagEff_Num_c");
    else
      h2_tot_BTagEff_Num_c->Add(h2_BTagEff_Num_cM);
    if(!h2_tot_BTagEff_Num_udsg)
      h2_tot_BTagEff_Num_udsg = (TH2D *)h2_BTagEff_Num_udsgM->Clone("h2_tot_BTagEff_Num_udsg");
    else
      h2_tot_BTagEff_Num_udsg->Add(h2_BTagEff_Num_udsgM);

  }
  // h2_tot_BTagEff_Num_b->Sumw2();
  // h2_tot_BTagEff_Num_c->Sumw2();
  // h2_tot_BTagEff_Num_udsg->Sumw2();
  // h2_tot_BTagEff_Denom_b->Sumw2();
  // h2_tot_BTagEff_Denom_c->Sumw2();
  // h2_tot_BTagEff_Denom_udsg->Sumw2();

  TH2D *h2_Ratio_b = (TH2D *)h2_tot_BTagEff_Num_b->Clone("Other_b_efficiency");
  TH2D *h2_Ratio_c = (TH2D *)h2_tot_BTagEff_Num_c->Clone("Other_c_efficiency");
  TH2D *h2_Ratio_l = (TH2D *)h2_tot_BTagEff_Num_udsg->Clone("Other_l_efficiency");

  h2_Ratio_b->Divide(h2_tot_BTagEff_Denom_b);
  h2_Ratio_c->Divide(h2_tot_BTagEff_Denom_c);
  h2_Ratio_l->Divide(h2_tot_BTagEff_Denom_udsg);
  
  fout->cd();
  h2_Ratio_b->Write();
  h2_Ratio_c->Write();
  h2_Ratio_l->Write();
  h2_tot_BTagEff_Num_b->Write();
  h2_tot_BTagEff_Num_c->Write();
  h2_tot_BTagEff_Num_udsg->Write();
  h2_tot_BTagEff_Denom_b->Write();
  h2_tot_BTagEff_Denom_c->Write();
  h2_tot_BTagEff_Denom_udsg->Write();
  fout->Close();
  delete fout;

  
  
  return true;
}
