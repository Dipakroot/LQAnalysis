/**********************************************************************
 Created on : 25/01/2022
 Purpose    : Save all historams of a root into a pdf file
 Author     : Indranil Das, Visiting Fellow
 Email      : indranil.das@cern.ch | indra.ehep@gmail.com
**********************************************************************/
#include <TROOT.h>
#include <string>
#include <iostream>
#include <TFile.h>
#include <TH1.h>
#include <TStyle.h>
#include <TClass.h>
#include <TKey.h>
#include <TLegend.h>
#include <TCanvas.h>

using namespace std;


int Save1DHistoPlots()
{
  const int maxNpages = 12000;
  TH1 *hs[maxNpages];
  int nof_hs = 0;
  TCanvas *c[maxNpages];

  int icanvas = 0;
  //gStyle->SetOptStat("ourmen");
  gStyle->SetOptStat(112211);
  gStyle->SetOptFit(11);

  //TFile *fin = TFile::Open("root_files/test/TTbar_KFObjectsReso_2016.root");
  //TFile *fin = TFile::Open("root_files/test/TTbar_KFObjectsReso_2016_KFCompareReso.root");
  //TFile *fin = TFile::Open("/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/proof_v41_KFObjects/2017/AllBkg_KFObjectsReso_2017.root");
  TFile *fin = TFile::Open("/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/proof_v41_KFObjects/2016/pre/TTbar_KFObjectsReso_2016.root");
  
  int nofHists = 0;
  TIter nextkeyTest(fin->GetListOfKeys());
  TKey *keyTest;
  while ((keyTest = ((TKey*)nextkeyTest())) ) {
    TObject *obj = keyTest->ReadObj();    
    if ( obj->IsA()->InheritsFrom( "TH1" ) ) 
      nofHists++;
  }
  cout << "Total number of hists : " << nofHists << endl;

  TIter nextkey(fin->GetListOfKeys());
  TKey *key;
  while ((key = ((TKey*)nextkey())) ) {
    if(icanvas>=maxNpages) continue;
    TObject *obj = key->ReadObj();
    
    if ( obj->IsA()->InheritsFrom( "TH1" ) ) {
      TH1 *h1 = (TH1*)obj;
      c[icanvas] = new TCanvas(Form("canvas_%d",icanvas),Form("canvas_%d",icanvas));
      h1->Draw();
      h1->Fit("gaus","QL");
      if(icanvas == 0)
      	c[icanvas]->SaveAs("plot.pdf(");
      else if(icanvas == maxNpages-1 or icanvas==nofHists-1)
      	c[icanvas]->SaveAs("plot.pdf)");
      else
      	c[icanvas]->SaveAs("plot.pdf");

      cout<<"Saving canvas for index : " << icanvas << endl;
    }
    icanvas++;
  }

  return true;
}
