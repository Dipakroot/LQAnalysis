/**********************************************************************
 Created on : 25/05/2021
 Purpose    : Read the mass histogram
 Author     : Shashi-ji
 Email      : 
**********************************************************************/
#include <TH1.h>
#include <TH1F.h>
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

#include <string>
#include <vector>
#include <sstream>  //istringstream
#include <iostream> // cout
#include <fstream>  // ifstream

using namespace std;

void readmasshisto_v02(){
  int nhist =17;
  char fin_name[100];
  char inpF[150], outF[150], lineStr[100], tmp[5];
  char hname[100], npdf_s[100], npdf_m[100], npdf_e[100];
  TH1F *Hist[20];
  TH1F *nAHist[20], *nBHist[20], *nCHist[20];



  //jMjjkF_xx are dijet invariant mass distributions
  //hMjjkF_01 is a histogram with idx=0: It contains entries with just E>0 cut

  //hMjjkF_02 is a histogram with idx=1: It contains entries with E>0 && preceding cuts

  //hMjjkF_03, idx=02: Pt_Muon>30 GeV with preceding cuts
  //hMjjkF_04, idx=03: Pt_bHad>30 GeV with preceding cuts
  //hMjjkF_05, idx=04: Pt_bLep>30 GeV with preceding cuts

  //hMjjkF_06, idx=05: Pt_SoftJet1>30 GeV with preceding cuts
  //hMjjkF_07, idx=06: Pt_SoftJet2>30 GeV with preceding cuts
  //hMjjkF_08, idx=07: Pt_MET>20 GeV with preceding cuts
  //hMjjkF_09, idx=08: delR_bHad<0.2 GeV with preceding cuts
  //hMjjkF_10, idx=09: delR_SoftJet1<0.2 GeV with preceding cuts
  //hMjjkF_11, idx=10: delR_SoftJet2<0.2 GeV with preceding cuts
  //hMjjkF_12, idx=11: delR_bLep<0.2 GeV with preceding cuts
  //hMjjkF_13, idx=12: delR_Muon<0.2 GeV with preceding cuts
  //hMjjkF_14, idx=13: pT ratio cut for MET with preceding cuts
  //hMjjkF_15, idx=14: pT ratio cut for bHad with preceding cuts

  //hMjjkF_16, idx=15: pT ratio cut for SoftJet1 with preceding cuts

  //hMjjkF_17, idx=16: pT ratio cut for SoftJet2 with preceding cuts


  //hMjjkF_02 is taken as baseline histogram 

  //5 clusters:  1 + 3 + 10 + 1 + 1 

  //Uncomment following lines when you process ttbar data sample
  //sprintf(fin_name, "result_m172.6_chi2020_pt020-10000_h01-h17.root");
  //sprintf(fin_name, "result_m172.6_chi2020_pt020-10000_ttbar_wt_btagwt_correction.root");
  sprintf(fin_name, "/Data/CMS-Analysis/NanoAOD-Analysis/KineFit/proof_2/root_files/result_m172.6_chi2020_pt020-10000_ttbar_wt_btagwt_correction.root");
  sprintf(npdf_s, "Indra_TTbar_wt_cor.pdf(");
  sprintf(npdf_m, "Indra_TTbar_wt_cor.pdf");
  sprintf(npdf_e, "Indra_TTbar_wt_cor.pdf)");
  TFile *fout = TFile::Open("Indra_TTbar_wt_cor.root","RECREATE");
  float xmin=60., xmax=100.;
  float x1R=0.,   x2R=200.;



  //Uncomment following lines when you process single top data sample
  //sprintf(fin_name, "result_m172.6_chi2020_pt020-10000_h01-h17_stop-t.root");  
  //sprintf(npdf_s, "Indra_Single_Top.pdf(");
  //sprintf(npdf_m, "Indra_Single_Top.pdf");
  //sprintf(npdf_e, "Indra_Single_Top.pdf)");
  //TFile *fout = TFile::Open("Indra_Single_Top.root","RECREATE");
  //float xmin=60., xmax=140.;
  //float x1R=0.,   x2R=300.;

  cout << fin_name << endl;
  TFile *fin = TFile::Open(fin_name);
  if(!fin){
    cerr<< "File : " << fin_name << " can not be opened." << endl;
  }
  TCanvas *c1 = new TCanvas("c1","c1",13,47,884,508);

  int   nMax[20], nBin[20];
  float BinV[20], hMean[20], hRMS[20];
  for(int i=0; i<20; i++){
    nMax[i]=0; nBin[i]=0;
    BinV[i]=0; hMean[i]=0; hRMS[i]=0;
  }

  for(int ih=0; ih<nhist; ih++){
    int ihist = ih+1;
    sprintf(hname, "hMjjkF_%02d", ihist);
    Hist[ih]  = (TH1F * )fin->Get(hname);
    Hist[ih]->GetXaxis()->SetTitle("Mw_{jj} (GeV)");
    nMax[ih]  = Hist[ih]->GetMaximum();
    //if(nMax[ih]<1000)continue;  //t-tabr
    if(nMax[ih]<50)continue;  //Single top
    nBin[ih]  = Hist[ih]->GetMaximumBin();
    BinV[ih]  = Hist[ih]->GetBinCenter(nBin[ih]);
    hMean[ih] = Hist[ih]->GetMean();
    hRMS[ih]  = Hist[ih]->GetRMS();
  }

  
  for(int ih=0; ih<nhist; ih++){
    float scaleA = 25000.0/nMax[ih];
    float scaleB = 1./nMax[ih];
    nAHist[ih] = (TH1F *)Hist[ih]->Clone();    nAHist[ih]->Scale(scaleA);
    nBHist[ih] = (TH1F *)Hist[ih]->Clone();    nBHist[ih]->Scale(scaleB);
  }

  float Ratio[20][80], Xval[20][80];
  int nPt[20];
  for(int ih=0; ih<20; ih++){
    nPt[ih]=0;
    for(int ibin=0; ibin<80; ibin++){Ratio[ih][ibin]=0.0; Xval[ih][ibin]=0.0;}
  }

  int nBins = nAHist[1]->GetNbinsX();
  for(int ih=0; ih<nhist; ih++){
    float xxA, yy0, yyA;
    int nR=0;
    for(int ibin=1; ibin<nBins; ibin++){
      float ratio=0;
      xxA = nAHist[ih]->GetBinCenter(ibin);
      yy0 = nAHist[1]->GetBinContent(ibin);
      yyA = nAHist[ih]->GetBinContent(ibin);
      if(yyA>1.0)ratio = yy0/yyA;
      if(ratio>0.1){Xval[ih][nR]=xxA; Ratio[ih][nR]=ratio; nR++;}
    }
    nPt[ih]=nR;
  }

  fout->cd();
  //Assign names to new histograms
  for(int ih=0; ih<nhist; ih++){
    int ihist = ih+1;
    float xxA = nAHist[ih]->GetBinCenter(16);
    int nE = nAHist[ih]->GetEntries();
    if(nE>10){
      sprintf(hname, "nA_MjjkF_%02d", ihist);  nAHist[ih]->SetName(hname);
      sprintf(hname, "nB_MjjkF_%02d", ihist);  nBHist[ih]->SetName(hname);
      nAHist[ih]->Write();
      nBHist[ih]->Write();
    }
  }


  gStyle->SetOptFit();
  Hist[1]->SetLineColor(2);		Hist[1]->Fit("gaus",  "", "", xmin, xmax);
  Hist[5]->SetLineColor(9);		Hist[5]->Fit("gaus",  "", "", xmin, xmax);
  Hist[6]->SetLineColor(4);		Hist[6]->Fit("gaus",  "", "", xmin, xmax);
  Hist[7]->SetLineColor(11);	Hist[7]->Fit("gaus",  "", "", xmin, xmax);
  Hist[13]->SetLineColor(6);	Hist[13]->Fit("gaus", "", "", xmin, xmax);
  Hist[15]->SetLineColor(7);	Hist[15]->Fit("gaus", "", "", xmin, xmax);
  Hist[16]->SetLineColor(8);	Hist[16]->Fit("gaus", "", "", xmin, xmax);
  Hist[1]->GetXaxis()->SetRangeUser(x1R, x2R);

  nBHist[1]->SetLineColor(2);	nBHist[1]->Fit("gaus",  "", "", xmin, xmax);
  nBHist[5]->SetLineColor(9);	nBHist[5]->Fit("gaus",  "", "", xmin, xmax);
  nBHist[6]->SetLineColor(4);	nBHist[6]->Fit("gaus",  "", "", xmin, xmax);
  nBHist[7]->SetLineColor(11);	nBHist[7]->Fit("gaus",  "", "", xmin, xmax);
  nBHist[13]->SetLineColor(6);	nBHist[13]->Fit("gaus", "", "", xmin, xmax);
  nBHist[15]->SetLineColor(7);	nBHist[15]->Fit("gaus", "", "", xmin, xmax);
  nBHist[16]->SetLineColor(8);	nBHist[16]->Fit("gaus", "", "", xmin, xmax);
  nBHist[1]->GetXaxis()->SetRangeUser(x1R, x2R);


  c1->Clear();
  Hist[1]->Draw();                c1->Update();
  TPaveStats *stats2 = (TPaveStats*)Hist[1]->GetListOfFunctions()->FindObject("stats");
  stats2->SetName("h02stats");    stats2->SetTextColor(2);
  stats2->SetX1NDC(.1);           stats2->SetX2NDC(.3);
  stats2->SetY1NDC(.7);           stats2->SetY2NDC(.9);

  Hist[5]->Draw("sames");         c1->Update();
  TPaveStats *stats3 = (TPaveStats*)Hist[5]->GetListOfFunctions()->FindObject("stats");
  stats3->SetName("h03stats");    stats3->SetTextColor(9);
  stats3->SetX1NDC(.1);           stats3->SetX2NDC(.3);
  stats3->SetY1NDC(.5);           stats3->SetY2NDC(.7);

  Hist[6]->Draw("sames");         c1->Update();
  TPaveStats *stats4 = (TPaveStats*)Hist[6]->GetListOfFunctions()->FindObject("stats");
  stats4->SetName("h04stats");    stats4->SetTextColor(4);
  stats4->SetX1NDC(.1);           stats4->SetX2NDC(.3);
  stats4->SetY1NDC(.3);           stats4->SetY2NDC(.5);

  Hist[7]->Draw("sames");         c1->Update();
  TPaveStats *stats5 = (TPaveStats*)Hist[7]->GetListOfFunctions()->FindObject("stats");
  stats5->SetName("h05stats");    stats5->SetTextColor(11);
  stats5->SetX1NDC(.5);           stats5->SetX2NDC(.7);
  stats5->SetY1NDC(.7);           stats5->SetY2NDC(.9);

  Hist[13]->Draw("sames");        c1->Update();
  TPaveStats *stats6 = (TPaveStats*)Hist[13]->GetListOfFunctions()->FindObject("stats");
  stats6->SetName("h06stats");    stats6->SetTextColor(6);
  stats6->SetX1NDC(.5);           stats6->SetX2NDC(.7);
  stats6->SetY1NDC(.5);           stats6->SetY2NDC(.7);

  Hist[15]->Draw("sames");        c1->Update();
  TPaveStats *stats7 = (TPaveStats*)Hist[15]->GetListOfFunctions()->FindObject("stats");
  stats7->SetName("h07stats");    stats7->SetTextColor(6);
  stats7->SetX1NDC(.7);           stats7->SetX2NDC(.9);
  stats7->SetY1NDC(.7);           stats7->SetY2NDC(.9);
  c1->Modified(); c1->Update();  c1->SaveAs(npdf_s);


  c1->Clear();
  nBHist[1]->Draw();              c1->Update();
  stats2 = (TPaveStats*)nBHist[1]->GetListOfFunctions()->FindObject("stats");
  stats2->SetX1NDC(.1);           stats2->SetX2NDC(.3);
  stats2->SetY1NDC(.7);           stats2->SetY2NDC(.9);

  nBHist[5]->Draw("sames");       c1->Update();
  stats3 = (TPaveStats*)nBHist[5]->GetListOfFunctions()->FindObject("stats");
  stats3->SetX1NDC(.1);           stats3->SetX2NDC(.3);
  stats3->SetY1NDC(.5);           stats3->SetY2NDC(.7);

  nBHist[6]->Draw("sames");       c1->Update();
  stats4 = (TPaveStats*)nBHist[6]->GetListOfFunctions()->FindObject("stats");
  stats4->SetX1NDC(.1);           stats4->SetX2NDC(.3);
  stats4->SetY1NDC(.3);           stats4->SetY2NDC(.5);

  nBHist[7]->Draw("sames");       c1->Update();
  stats5 = (TPaveStats*)nBHist[7]->GetListOfFunctions()->FindObject("stats");
  stats5->SetX1NDC(.5);           stats5->SetX2NDC(.7);
  stats5->SetY1NDC(.7);           stats5->SetY2NDC(.9);

  nBHist[13]->Draw("sames");      c1->Update();
  stats6 = (TPaveStats*)nBHist[13]->GetListOfFunctions()->FindObject("stats");
  stats6->SetX1NDC(.5);           stats6->SetX2NDC(.7);
  stats6->SetY1NDC(.5);           stats6->SetY2NDC(.7);

  nBHist[15]->Draw("sames");      c1->Update();
  stats7 = (TPaveStats*)nBHist[15]->GetListOfFunctions()->FindObject("stats");
  stats7->SetX1NDC(.7);           stats7->SetX2NDC(.9);
  stats7->SetY1NDC(.7);           stats7->SetY2NDC(.9);
  c1->Modified(); c1->Update();   c1->SaveAs(npdf_m);

  TGraph *gRatio[20];  TGraph *gCutFlow;  TGraph *gNCutFlow;  
  TGraph *gMean;  TGraph *gRMS;

  for(int ih=0; ih<nhist; ih++){
    int ihist = ih+1;
    int nE = nAHist[ih]->GetEntries();
    int np = nPt[ih];
    float xx[80], yy[80];
    if(nE>10 && np>10){
      for(int i=0; i<np; i++){xx[i]=Xval[ih][i]; yy[i]=Ratio[ih][i];}
      gRatio[ih] = new TGraph(np, xx, yy);
      sprintf(hname, "gMjjkF_%02d", ihist);
      gRatio[ih]->SetName(hname);
      int imarker=ih+20;
      if(ih>14)imarker=ih+5;
      gRatio[ih]->SetMarkerStyle(imarker);
      gRatio[ih]->GetYaxis()->SetRangeUser(0.8, 2.0);
      cout << "Graph_IDx = " << ih << "    Hist_Enrties = " << nE;
      cout << "       nPoints = " << np << "       gr_name = " << hname << endl;
    }
  }
  gRatio[1]->GetXaxis()->SetTitle("diJet Mass (GeV)");  
  gRatio[1]->GetYaxis()->SetTitle("Ratio w.r.t. Chi2<20");

  gRatio[1]->SetTitle("TTbar: Ratio w.r.t. Chi2<20");
  //gRatio[1]->SetTitle("Single Top: Ratio w.r.t. Chi2<20");

  c1->Clear();              c1->cd();      c1->SetGridx();  c1->SetGridy();
  gRatio[1]->Draw("AP");
  for(int ih=2; ih<nhist; ih++){
    int nE = nAHist[ih]->GetEntries();
    int np = nPt[ih];
    if(nE<10 || np<10 || ih==1)continue;
    gRatio[ih]->DrawClone("P");
  }
  c1->Update();  c1->SaveAs(npdf_m);
  
  float xCut[20], yPt[20], Norm_yPt[20];
  int nE0 = nAHist[1]->GetEntries();
  for(int ih=0; ih<nhist; ih++){
    xCut[ih]=0; yPt[ih]=0; Norm_yPt[ih]=0;
    int nE = nAHist[ih]->GetEntries();
    if(nE>100){
      xCut[ih]=ih+1;  yPt[ih]=nE; Norm_yPt[ih] = (float)nE/nE0;
      //cout << ih+1 << "   nE = " << nE << "  nE0 = " << nE0 << endl;
    }
  }

  gCutFlow = new TGraph(17, xCut, yPt);
  gCutFlow->GetXaxis()->SetTitle("Cut Number");  
  gCutFlow->GetYaxis()->SetTitle("Total Entries in the Histogram");
  gCutFlow->SetMarkerStyle(21);  gCutFlow->SetName("CutFlow");
  gCutFlow->GetXaxis()->SetRangeUser(1.5, 18);

  gNCutFlow = new TGraph(17, xCut, Norm_yPt);
  gNCutFlow->GetXaxis()->SetTitle("Cut Number");  
  gNCutFlow->GetYaxis()->SetTitle("Normalised Total Entries in the Histogram");
  gNCutFlow->SetMarkerStyle(21);  gCutFlow->SetName("CutFlow");
  gNCutFlow->GetXaxis()->SetRangeUser(1.5, 18);
  gNCutFlow->GetYaxis()->SetRangeUser(0.3, 1.1);  

  gMean = new TGraph(17, xCut, hMean);
  gMean->GetXaxis()->SetTitle("Cut Number");  
  gMean->GetYaxis()->SetTitle("Mw Mean Mass of Histogram (GeV)");
  gMean->SetMarkerStyle(21);  gMean->SetName("gMeanMw");

  gRMS = new TGraph(17, xCut, hRMS);
  gRMS->GetXaxis()->SetTitle("Cut Number");  
  gRMS->GetYaxis()->SetTitle("Mw RMS Mass of Histogram (GeV)");
  gRMS->SetMarkerStyle(21);  gCutFlow->SetName("gMeanM");
  
  //TTBar
  //gCutFlow->GetYaxis()->SetRangeUser(200000, 350000);
  gCutFlow->SetTitle("TTbar: Cut Flow Graph");
  gNCutFlow->SetTitle("TTbar: Normalised Cut Flow Graph");
  gMean->SetTitle("TTbar: Cut Flow Mw_Mean_Mass");
  gRMS->SetTitle("TTbar: Cut Flow of Mw_RMS Mass");


  //Single Top
  //gCutFlow->GetYaxis()->SetRangeUser(4000, 14000);
  //gCutFlow->SetTitle("Single Top: Cut Flow Graph");
  //gNCutFlow->SetTitle("Single Top: Normalised Cut Flow Graph");
  //gMean->SetTitle("Single Top: Cut Flow Mw_Mean_Mass");
  //gRMS->SetTitle("Single Top: Cut Flow of Mw_RMS Mass");

  c1->Clear(); c1->cd();  c1->SetGridx();  c1->SetGridy();
  gCutFlow->Draw("AP");   c1->Update();    c1->SaveAs(npdf_m);

  c1->Clear(); c1->cd();  c1->SetGridx();  c1->SetGridy();
  gNCutFlow->Draw("AP");  c1->Update();    c1->SaveAs(npdf_m);

  c1->Clear(); c1->cd();  c1->SetGridx();  c1->SetGridy();
  gMean->Draw("AP");      c1->Update();    c1->SaveAs(npdf_m);

  c1->Clear(); c1->cd();  c1->SetGridx();  c1->SetGridy();
  gRMS->Draw("AP");       c1->Update();    c1->SaveAs(npdf_e);

  fout->Close();


  /*
  gStyle->SetOptStat("ourmen");
  h1->GetYaxis()->SetTitle(Form("Counts per %3.1f GeV/c^{2}",h1->GetBinWidth(3)));
  TCanvas *c1 = new TCanvas("c1","c1",13,47,884,508);
  */

}
