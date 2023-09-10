/**********************************************************************
 Created on : 10/08/2021
 Purpose    : Event counts as checked in on file
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

#include <iostream>

using namespace std;

int EventCountsOneFile(const char *infile = "")
{
  
  bool isMu = 1;
  int ftype = 0;// 0 for total, 1 for 5of12, 2 for 6of12
  
  // const char* cutflow = (isMu) ? "_cutflow_mu" : "_cutflow_ele";
  // const char* cutflowUS = (isMu) ? "_cutflowUS_mu" : "_cutflowUS_ele";

  const char* cutflow = (isMu) ? "_cutflow_mu" : "_cutflow_ele";
  const char* cutflowUS = (isMu) ? "_cutflowUS_mu" : "_cutflowUS_ele";

  TFile *fin_nano_data	= 0x0;//TFile::Open(infile);
  fin_nano_data	= TFile::Open(infile);

  TH1D *hcf_nano_data	= (TH1D *)fin_nano_data->Get(Form("TTbar/base/Iso/%s",cutflow));
  cout<<"Processing : " << fin_nano_data->GetName() << endl;

  printf("%s & ",hcf_nano_data->GetName());
  for (int ibin=2;ibin<hcf_nano_data->GetNbinsX();ibin++){
    if(hcf_nano_data->GetBinContent(ibin)>0.0 and hcf_nano_data->GetBinContent(ibin+1)>0.0){
      if(hcf_nano_data->GetBinContent(ibin)>1e6){
	printf("%.4e & ",hcf_nano_data->GetBinContent(ibin)); 
      }else{
	printf("%.1f & ",hcf_nano_data->GetBinContent(ibin));
      }
    }else if(hcf_nano_data->GetBinContent(ibin)>0.0 and TMath::AreEqualAbs(hcf_nano_data->GetBinContent(ibin+1),0.0,1.e-5)){
      printf("%.1f \\\\\\hline ",hcf_nano_data->GetBinContent(ibin));
    }
  }
  printf("\n");
  
  fin_nano_data->Close();
  delete fin_nano_data;

  return true;
}
