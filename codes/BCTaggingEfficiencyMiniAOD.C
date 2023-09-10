/**********************************************************************
 Created on : 19/02/2022
 Purpose    : BTagging and CTagging efficiency of MiniAOD
 Author     : Indranil Das, Visiting Fellow
 Email      : indranil.das@cern.ch | indra.ehep@gmail.com
**********************************************************************/
#include <TH1.h>
#include <THStack.h>
#include <TF1.h>
#include <TFile.h>
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
#include <TAttLine.h>
#include <TROOT.h>
#include <TH2.h>
#include <TH1.h>
#include <TRatioPlot.h>

#include <iostream>
#include <fstream>

using namespace std;

int BCTaggingEfficiencyMiniAOD()
{
  //string fname = "/run/media/indra/DHEP_Storage_1/Data/MiniAOD/Ravindra-MiniAOD/MuMC_20200307/TTJetsP_MuMC_20200307/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8/TTJetsP_MuMC_20200307/200307_100856/0000/TTJetsP_MuMC_20200307_Ntuple_100.root";
  
  TH2D *h2_BTagEff_Denom_b=0x0,*h2_BTagEff_Denom_c=0x0, *h2_BTagEff_Denom_udsg=0x0;
  TH2D *h2_BTagEff_Num_bM=0x0,*h2_BTagEff_Num_cM=0x0, *h2_BTagEff_Num_udsgM=0x0;
  
  TH2D *h2_CTagEff_Denom_b=0x0,*h2_CTagEff_Denom_c=0x0, *h2_CTagEff_Denom_udsg=0x0;
  TH2D *h2_CTagEff_Num_bL=0x0,*h2_CTagEff_Num_cL=0x0, *h2_CTagEff_Num_udsgL=0x0;
  TH2D *h2_CTagEff_Num_bM=0x0,*h2_CTagEff_Num_cM=0x0, *h2_CTagEff_Num_udsgM=0x0;
  TH2D *h2_CTagEff_Num_bT=0x0,*h2_CTagEff_Num_cT=0x0, *h2_CTagEff_Num_udsgT=0x0;
  
  //string infile = "input/files.txt";
  string infile = "input/filesUL.txt";
  string outfname = "output/btag.root";
  TFile *fout = new TFile(Form("%s",outfname.c_str()),"recreate");    

  //TString histPath("myMiniTreeProducer/Jets/");
  TString histPath("");

  int ifile = 0 ;
  ifstream fread(infile);
  string fname;
  while(getline(fread,fname)){
    cout << "fname : " << fname << endl;
    TFile *fin = TFile::Open(fname.c_str());
    
    if(ifile==0){
      h2_BTagEff_Denom_b              = (TH2D*)(fin->Get(histPath+"h2_BTagEff_Denom_b"));
      h2_BTagEff_Denom_c              = (TH2D*)(fin->Get(histPath+"h2_BTagEff_Denom_c"));
      h2_BTagEff_Denom_udsg           = (TH2D*)(fin->Get(histPath+"h2_BTagEff_Denom_udsg"));
      
      h2_BTagEff_Num_bM               = (TH2D*)(fin->Get(histPath+"h2_BTagEff_Num_bM"));
      h2_BTagEff_Num_cM               = (TH2D*)(fin->Get(histPath+"h2_BTagEff_Num_cM"));
      h2_BTagEff_Num_udsgM            = (TH2D*)(fin->Get(histPath+"h2_BTagEff_Num_udsgM"));

      h2_CTagEff_Denom_b              = (TH2D*)(fin->Get(histPath+"h2_CTagEff_Denom_b"));
      h2_CTagEff_Denom_c              = (TH2D*)(fin->Get(histPath+"h2_CTagEff_Denom_c"));
      h2_CTagEff_Denom_udsg           = (TH2D*)(fin->Get(histPath+"h2_CTagEff_Denom_udsg"));

      h2_CTagEff_Num_bL               = (TH2D*)(fin->Get(histPath+"h2_CTagEff_Num_bL"));
      h2_CTagEff_Num_cL               = (TH2D*)(fin->Get(histPath+"h2_CTagEff_Num_cL"));
      h2_CTagEff_Num_udsgL            = (TH2D*)(fin->Get(histPath+"h2_CTagEff_Num_udsgL"));    

      h2_CTagEff_Num_bM               = (TH2D*)(fin->Get(histPath+"h2_CTagEff_Num_bM"));
      h2_CTagEff_Num_cM               = (TH2D*)(fin->Get(histPath+"h2_CTagEff_Num_cM"));
      h2_CTagEff_Num_udsgM            = (TH2D*)(fin->Get(histPath+"h2_CTagEff_Num_udsgM"));    

      h2_CTagEff_Num_bT               = (TH2D*)(fin->Get(histPath+"h2_CTagEff_Num_bT"));
      h2_CTagEff_Num_cT               = (TH2D*)(fin->Get(histPath+"h2_CTagEff_Num_cT"));
      h2_CTagEff_Num_udsgT            = (TH2D*)(fin->Get(histPath+"h2_CTagEff_Num_udsgT"));    

    }else{

      TH2D *h2_BTagEff_Denom_b_temp              = (TH2D*)(fin->Get(histPath+"h2_BTagEff_Denom_b"));
      TH2D *h2_BTagEff_Denom_c_temp              = (TH2D*)(fin->Get(histPath+"h2_BTagEff_Denom_c"));
      TH2D *h2_BTagEff_Denom_udsg_temp           = (TH2D*)(fin->Get(histPath+"h2_BTagEff_Denom_udsg"));
      
      TH2D *h2_BTagEff_Num_bM_temp               = (TH2D*)(fin->Get(histPath+"h2_BTagEff_Num_bM"));
      TH2D *h2_BTagEff_Num_cM_temp               = (TH2D*)(fin->Get(histPath+"h2_BTagEff_Num_cM"));
      TH2D *h2_BTagEff_Num_udsgM_temp            = (TH2D*)(fin->Get(histPath+"h2_BTagEff_Num_udsgM"));

      TH2D *h2_CTagEff_Denom_b_temp              = (TH2D*)(fin->Get(histPath+"h2_CTagEff_Denom_b"));
      TH2D *h2_CTagEff_Denom_c_temp              = (TH2D*)(fin->Get(histPath+"h2_CTagEff_Denom_c"));
      TH2D *h2_CTagEff_Denom_udsg_temp           = (TH2D*)(fin->Get(histPath+"h2_CTagEff_Denom_udsg"));

      TH2D *h2_CTagEff_Num_bL_temp               = (TH2D*)(fin->Get(histPath+"h2_CTagEff_Num_bL"));
      TH2D *h2_CTagEff_Num_cL_temp               = (TH2D*)(fin->Get(histPath+"h2_CTagEff_Num_cL"));
      TH2D *h2_CTagEff_Num_udsgL_temp            = (TH2D*)(fin->Get(histPath+"h2_CTagEff_Num_udsgL"));    

      TH2D *h2_CTagEff_Num_bM_temp               = (TH2D*)(fin->Get(histPath+"h2_CTagEff_Num_bM"));
      TH2D *h2_CTagEff_Num_cM_temp               = (TH2D*)(fin->Get(histPath+"h2_CTagEff_Num_cM"));
      TH2D *h2_CTagEff_Num_udsgM_temp            = (TH2D*)(fin->Get(histPath+"h2_CTagEff_Num_udsgM"));    

      TH2D *h2_CTagEff_Num_bT_temp               = (TH2D*)(fin->Get(histPath+"h2_CTagEff_Num_bT"));
      TH2D *h2_CTagEff_Num_cT_temp               = (TH2D*)(fin->Get(histPath+"h2_CTagEff_Num_cT"));
      TH2D *h2_CTagEff_Num_udsgT_temp            = (TH2D*)(fin->Get(histPath+"h2_CTagEff_Num_udsgT"));    
      
      h2_BTagEff_Denom_b->Add(h2_BTagEff_Denom_b_temp);
      h2_BTagEff_Denom_c->Add(h2_BTagEff_Denom_c_temp);
      h2_BTagEff_Denom_udsg->Add(h2_BTagEff_Denom_udsg_temp);
      
      h2_BTagEff_Num_bM->Add(h2_BTagEff_Num_bM_temp);
      h2_BTagEff_Num_cM->Add(h2_BTagEff_Num_cM_temp);
      h2_BTagEff_Num_udsgM->Add(h2_BTagEff_Num_udsgM_temp);
      
      h2_CTagEff_Denom_b->Add(h2_CTagEff_Denom_b_temp);
      h2_CTagEff_Denom_c->Add(h2_CTagEff_Denom_c_temp);
      h2_CTagEff_Denom_udsg->Add(h2_CTagEff_Denom_udsg_temp);
      
      h2_CTagEff_Num_bL->Add(h2_CTagEff_Num_bL_temp);
      h2_CTagEff_Num_cL->Add(h2_CTagEff_Num_cL_temp);
      h2_CTagEff_Num_udsgL->Add(h2_CTagEff_Num_udsgL_temp);
      
      h2_CTagEff_Num_bM->Add(h2_CTagEff_Num_bM_temp);
      h2_CTagEff_Num_cM->Add(h2_CTagEff_Num_cM_temp);
      h2_CTagEff_Num_udsgM->Add(h2_CTagEff_Num_udsgM_temp);
      
      h2_CTagEff_Num_bT->Add(h2_CTagEff_Num_bT_temp);
      h2_CTagEff_Num_cT->Add(h2_CTagEff_Num_cT_temp);
      h2_CTagEff_Num_udsgT->Add(h2_CTagEff_Num_udsgT_temp);
      
    }

    //if(ifile==1) break;
    ifile++;
  }
  
  h2_BTagEff_Num_bM->Sumw2();
  h2_BTagEff_Num_cM->Sumw2();
  h2_BTagEff_Num_udsgM->Sumw2();
  h2_BTagEff_Denom_b->Sumw2();
  h2_BTagEff_Denom_c->Sumw2();
  h2_BTagEff_Denom_udsg->Sumw2();
    
  TH2D *h2_BTagEff_Ratio_bM = (TH2D*)h2_BTagEff_Num_bM->Clone("BTag_b_M_efficiency");
  TH2D *h2_BTagEff_Ratio_cM = (TH2D*)h2_BTagEff_Num_cM->Clone("BTag_c_M_efficiency");
  TH2D *h2_BTagEff_Ratio_udsgM = (TH2D*)h2_BTagEff_Num_udsgM->Clone("BTag_l_M_efficiency");
  h2_BTagEff_Ratio_bM->Divide(h2_BTagEff_Denom_b);
  h2_BTagEff_Ratio_cM->Divide(h2_BTagEff_Denom_c);
  h2_BTagEff_Ratio_udsgM->Divide(h2_BTagEff_Denom_udsg);



  h2_CTagEff_Denom_b->Sumw2();
  h2_CTagEff_Denom_c->Sumw2();
  h2_CTagEff_Denom_udsg->Sumw2();

  h2_CTagEff_Num_bL->Sumw2();
  h2_CTagEff_Num_cL->Sumw2();
  h2_CTagEff_Num_udsgL->Sumw2();

  TH2D *h2_CTagEff_Ratio_bL = (TH2D*)h2_CTagEff_Num_bL->Clone("CTag_b_L_efficiency");
  TH2D *h2_CTagEff_Ratio_cL = (TH2D*)h2_CTagEff_Num_cL->Clone("CTag_c_L_efficiency");
  TH2D *h2_CTagEff_Ratio_udsgL = (TH2D*)h2_CTagEff_Num_udsgL->Clone("CTag_l_L_efficiency");
  h2_CTagEff_Ratio_bL->Divide(h2_CTagEff_Denom_b);
  h2_CTagEff_Ratio_cL->Divide(h2_CTagEff_Denom_c);
  h2_CTagEff_Ratio_udsgL->Divide(h2_CTagEff_Denom_udsg);

  h2_CTagEff_Num_bM->Sumw2();
  h2_CTagEff_Num_cM->Sumw2();
  h2_CTagEff_Num_udsgM->Sumw2();
  TH2D *h2_CTagEff_Ratio_bM = (TH2D*)h2_CTagEff_Num_bM->Clone("CTag_b_M_efficiency");
  TH2D *h2_CTagEff_Ratio_cM = (TH2D*)h2_CTagEff_Num_cM->Clone("CTag_c_M_efficiency");
  TH2D *h2_CTagEff_Ratio_udsgM = (TH2D*)h2_CTagEff_Num_udsgM->Clone("CTag_l_M_efficiency");
  h2_CTagEff_Ratio_bM->Divide(h2_CTagEff_Denom_b);
  h2_CTagEff_Ratio_cM->Divide(h2_CTagEff_Denom_c);
  h2_CTagEff_Ratio_udsgM->Divide(h2_CTagEff_Denom_udsg);

  h2_CTagEff_Num_bT->Sumw2();
  h2_CTagEff_Num_cT->Sumw2();
  h2_CTagEff_Num_udsgT->Sumw2();
  TH2D *h2_CTagEff_Ratio_bT = (TH2D*)h2_CTagEff_Num_bT->Clone("CTag_b_T_efficiency");
  TH2D *h2_CTagEff_Ratio_cT = (TH2D*)h2_CTagEff_Num_cT->Clone("CTag_c_T_efficiency");
  TH2D *h2_CTagEff_Ratio_udsgT = (TH2D*)h2_CTagEff_Num_udsgT->Clone("CTag_l_T_efficiency");
  h2_CTagEff_Ratio_bT->Divide(h2_CTagEff_Denom_b);
  h2_CTagEff_Ratio_cT->Divide(h2_CTagEff_Denom_c);
  h2_CTagEff_Ratio_udsgT->Divide(h2_CTagEff_Denom_udsg);
    
  fout->cd();
  h2_BTagEff_Denom_b->Write();
  h2_BTagEff_Denom_c->Write();
  h2_BTagEff_Denom_udsg->Write();
  h2_CTagEff_Denom_b->Write();
  h2_CTagEff_Denom_c->Write();
  h2_CTagEff_Denom_udsg->Write();

  h2_BTagEff_Ratio_bM->Write();
  h2_BTagEff_Ratio_cM->Write();
  h2_BTagEff_Ratio_udsgM->Write();
  h2_CTagEff_Ratio_bL->Write();
  h2_CTagEff_Ratio_cL->Write();
  h2_CTagEff_Ratio_udsgL->Write();
  h2_CTagEff_Ratio_bM->Write();
  h2_CTagEff_Ratio_cM->Write();
  h2_CTagEff_Ratio_udsgM->Write();
  h2_CTagEff_Ratio_bT->Write();
  h2_CTagEff_Ratio_cT->Write();
  h2_CTagEff_Ratio_udsgT->Write();
    
  fout->Close();
  delete fout;
  
  
  return true;
}
