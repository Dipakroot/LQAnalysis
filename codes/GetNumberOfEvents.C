/**********************************************************************
 Created on : 16/11/2021
 Purpose    : Read number of unscaled MC events of NanoAOD
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
#include <TGraphAsymmErrors.h>

#include <TRatioPlot.h>

#include <iostream>
#include <fstream>

using namespace std;

int GetNumberOfEvents(string infile = "input/files_ttbar_inclusive.txt")
{
  ifstream fin(Form("%s",infile.c_str()));
  string s;
  double totalEvents = 0;
  int ifile = 0;
  while(getline(fin,s)){
    
    //Info("GetNumberofEvents", "filename : %s", s.c_str());
    string sample = s.substr(s.find_last_of("/")+1,s.size());    
    if(sample.find("_ext4_Skim") != string::npos)
      sample = sample.substr(0,sample.find("_ext4_Skim"));
    else if (sample.find("_ext3_Skim") != string::npos)
      sample = sample.substr(0,sample.find("_ext3_Skim"));
    else if (sample.find("_ext2_Skim") != string::npos)
      sample = sample.substr(0,sample.find("_ext2_Skim"));
    else if (sample.find("_ext1_Skim") != string::npos)
      sample = sample.substr(0,sample.find("_ext1_Skim"));
    else if (sample.find("_Skim") != string::npos)
      sample = sample.substr(0,sample.find("_Skim"));
    
    TFile *file = TFile::Open(s.c_str(),"read");
    TH1D *hEvents = (TH1D*) file->Get("hEvents");
    double nofMCEvents = hEvents->GetEntries()/2.0;
    totalEvents += nofMCEvents;
    printf("File : %d:%s, %lf, %10.1lf\n",ifile,s.c_str(),nofMCEvents,totalEvents);

    file->Close();
    delete file;
    ifile++;
  }
  printf("Total Events : %10.1lf\n",totalEvents);

  return true;
}
