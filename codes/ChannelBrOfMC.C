/**********************************************************************
 Created on : 15/11/2021
 Purpose    : Calculate the Br of channels as found from LHEPart histograms.
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

//int ChannelBrOfMC(string infile = "root_files/test/EventCount/EventCount_files_pow_tt_v7.root")//"root_files/test/EventCount/EventCount_ttbar_inclusive_skim.root")
int ChannelBrOfMC(string infile = "root_files/test/EventCount/EventCount_ttbar_inclusive_skim.root")
{
  
  TFile *fin = TFile::Open(infile.c_str());
  
  TH1D *hEvtCount = (TH1D *)fin->Get("hEvtCount");
  TH1D *hDilepton = (TH1D *)fin->Get("hDilepton");
  TH1D *hHadronic = (TH1D *)fin->Get("hHadronic");
  TH1D *hSemiLept = (TH1D *)fin->Get("hSemiLept");
  
  // /////////////////// Event Histogram ////////////////////////////
  // hEvtCount->SetBinContent(1,chain->GetEntries());
  // hEvtCount->SetBinContent(2,totalIdentified);
  // hEvtCount->SetBinContent(3,chain->GetEntries()-totalIdentified);
  // hEvtCount->SetBinContent(4,nofDileptonic);
  // hEvtCount->SetBinContent(5,nofHadronic);
  // hEvtCount->SetBinContent(6,nofSemiLeptonic);
  
  double Total_Events = hEvtCount->GetBinContent(1) ;
  double Total_Found = hEvtCount->GetBinContent(2);
  double Total_Missed = hEvtCount->GetBinContent(3);

  for(int i=0;i<40;i++) printf("//");
  printf("\n");
  printf("Percentage of events correctly identified : %3.1lf %\% \n",100.*Total_Found/Total_Events);
  printf("Percentage of events missed to identify : %3.1lf %\% \n",100.*Total_Missed/Total_Events);
  for(int i=0;i<40;i++) printf("//");
  printf("\n");
  
  if(Total_Found != Total_Events){
    printf("Bye bye\n");
    fin->Close();
    delete fin;
  }

  double nofDileptonic = (!hDilepton) ? hEvtCount->GetBinContent(4) : hDilepton->GetBinContent(1) ;
  double nofHadronic = (!hHadronic) ? hEvtCount->GetBinContent(5) : hHadronic->GetBinContent(1)  ; 
  double nofSemiLeptonic = (!hSemiLept) ?  hEvtCount->GetBinContent(6) : hSemiLept->GetBinContent(1) ; 

  for(int i=0;i<40;i++) printf("//");
  printf("\n");
  if(Total_Found == Total_Events) {
    double total_CS = 831.76;
    printf("Nof Dileptonic events : %.1lf\n",nofDileptonic);
    printf("Nof Hadronic events : %.1lf\n",nofHadronic);
    printf("Nof Semileptonic events : %.1lf\n\n",nofSemiLeptonic);
    for(int i=0;i<40;i++) printf("//");
    printf("\n");
    printf("Dileptonic CS : %lf\n",total_CS*nofDileptonic/Total_Found);
    printf("Hadronic CS : %lf\n",total_CS*nofHadronic/Total_Found);
    printf("Semileptonic CS : %lf\n\n",total_CS*nofSemiLeptonic/Total_Found);
  }
  for(int i=0;i<40;i++) printf("//");
  printf("\n");

  for(int i=0;i<40;i++) printf("//");
  printf("\n");
  printf("Br of dileptonic decay : %3.2lf %\% and fraction : %6.5lf\n",100.*nofDileptonic/Total_Found,nofDileptonic/Total_Found);
  printf("Br of hadronic decay : %3.2lf %\% and fraction : %6.5lf\n",100.*nofHadronic/Total_Found,nofHadronic/Total_Found);
  printf("Br of semileptonic decay : %3.2lf %\% and fraction : %6.5lf\n",100.*nofSemiLeptonic/Total_Found,nofSemiLeptonic/Total_Found);
  for(int i=0;i<40;i++) printf("//");
  printf("\n");
  
  if (!hDilepton or !hHadronic or !hSemiLept){
    printf("Bye bye\n");
    fin->Close();
    delete fin;
  }
   
  // /////////////////// Dilepton Histogram ////////////////////////////
  // //Long64_t nofDiEle = 0, nofDiMu = 0, nofDiTau = 0, nofEleMu = 0, nofEleTau = 0, nofMuTau = 0;   
  // hDilepton->SetBinContent(1,nofDileptonic);
  // hDilepton->SetBinContent(2,nofDiEle);
  // hDilepton->SetBinContent(3,nofDiMu);
  // hDilepton->SetBinContent(4,nofDiTau);
  // hDilepton->SetBinContent(5,nofEleMu);
  // hDilepton->SetBinContent(6,nofEleTau);
  // hDilepton->SetBinContent(7,nofMuTau);
  
  double nofDiEle = hDilepton->GetBinContent(2); double nofDiMu = hDilepton->GetBinContent(3); double nofDiTau = hDilepton->GetBinContent(4);
  double nofEleMu = hDilepton->GetBinContent(5); double nofEleTau = hDilepton->GetBinContent(6); double nofMuTau = hDilepton->GetBinContent(7);   

  for(int i=0;i<40;i++) printf("//");
  printf("\n");
  printf("Percent of dielecton : %3.2lf %\% \n",100.*nofDiEle/nofDileptonic);
  printf("Percent of dimuon : %3.2lf %\% \n",100.*nofDiMu/nofDileptonic);
  printf("Percent of ditau : %3.2lf %\% \n",100.*nofDiTau/nofDileptonic);
  printf("Percent of elemu : %3.2lf %\% \n",100.*nofEleMu/nofDileptonic);
  printf("Percent of eletau : %3.2lf %\% \n",100.*nofEleTau/nofDileptonic);
  printf("Percent of mutau : %3.2lf %\% \n",100.*nofMuTau/nofDileptonic);
  for(int i=0;i<40;i++) printf("//");
  printf("\n");
  
  // /////////////////// Hadron Histogram ////////////////////////////
  // //Long64_t nofHadcs = 0, nofHadFourSep = 0, nofHadTwoOneOne = 0, nofHadTwoTwo = 0;
  // hHadronic->SetBinContent(1,nofHadronic);
  // hHadronic->SetBinContent(2,nofHadcs);
  // hHadronic->SetBinContent(3,nofHadFourSep);
  // hHadronic->SetBinContent(4,nofHadTwoOneOne);
  // hHadronic->SetBinContent(5,nofHadTwoTwo);
  
  double nofHadcs = hHadronic->GetBinContent(2); double nofHadFourSep = hHadronic->GetBinContent(3); 
  double nofHadTwoOneOne = hHadronic->GetBinContent(4); double nofHadTwoTwo = hHadronic->GetBinContent(5);

  for(int i=0;i<40;i++) printf("//");
  printf("\n");
  printf("Percent of hadronic cs : %3.2lf %\% \n",100.*nofHadcs/nofHadronic);
  printf("Percent of foursep : %3.2lf %\% \n",100.*nofHadFourSep/nofHadronic);
  printf("Percent of twooneone : %3.2lf %\% \n",100.*nofHadTwoOneOne/nofHadronic);
  printf("Percent of twotwo : %3.2lf %\% \n",100.*nofHadTwoTwo/nofHadronic);
  for(int i=0;i<40;i++) printf("//");
  printf("\n");
  
  // /////////////////// Semilepton Histogram ////////////////////////////
  // //Long64_t nofcsMu = 0, nofcsEle = 0, nofcsTau = 0, nofSlMu = 0, nofSlEle = 0, nofSlTau = 0, nofSlcs = 0 ;
  // hSemiLept->SetBinContent(1,nofSemiLeptonic);
  // hSemiLept->SetBinContent(2,nofcsEle);
  // hSemiLept->SetBinContent(3,nofcsMu);
  // hSemiLept->SetBinContent(4,nofcsTau);
  // hSemiLept->SetBinContent(5,nofSlEle);
  // hSemiLept->SetBinContent(6,nofSlMu);
  // hSemiLept->SetBinContent(7,nofSlTau);
  // hSemiLept->SetBinContent(8,nofSlcs);
  
  double nofcsEle = hSemiLept->GetBinContent(2); double nofcsMu = hSemiLept->GetBinContent(3); double nofcsTau = hSemiLept->GetBinContent(4);
  double nofSlEle = hSemiLept->GetBinContent(5); double nofSlMu = hSemiLept->GetBinContent(6); double nofSlTau = hSemiLept->GetBinContent(7); 
  double nofSlcs = hSemiLept->GetBinContent(8) ;
  
  for(int i=0;i<40;i++) printf("//");
  printf("\n");
  printf("Percent of semileptonic cs  : %3.2lf %\% \n",100.*nofSlcs/nofSemiLeptonic);
  printf("Percent of sl ele : %3.2lf %\% \n",100.*nofSlEle/nofSemiLeptonic);
  printf("Percent of sl mu : %3.2lf %\% \n",100.*nofSlMu/nofSemiLeptonic);
  printf("Percent of sl tau : %3.2lf %\% \n",100.*nofSlTau/nofSemiLeptonic);
  printf("Percent of sl ele cs : %3.2lf %\% \n",100.*nofcsEle/nofSemiLeptonic);
  printf("Percent of sl mu cs : %3.2lf %\% \n",100.*nofcsMu/nofSemiLeptonic);
  printf("Percent of sl tau cs : %3.2lf %\% \n",100.*nofcsTau/nofSemiLeptonic);
  for(int i=0;i<40;i++) printf("//");
  printf("\n");

  
  fin->Close();
  delete fin;

  return true;
}
