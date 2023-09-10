/**********************************************************************
 Created on : 12/09/2021
 Purpose    : Prepare Mjj syst table (Inspired by Ravindra's code)
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

#include <TRatioPlot.h>

#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

int PrepMjjSystTable()
{
  string GetInclusive(string, int, bool);
  string GetDifferential(string rowtitle, int ifile, bool inc);

  bool forPaper = false;
  
  ofstream outFile;
  outFile.open("mjjTable.tex");
  outFile<<"\\documentclass[]{article}"<<endl;
  outFile<<"\\usepackage{amsmath}"<<endl;
  outFile<<"\\usepackage{array}"<<endl;
  outFile<<"\\usepackage{multirow}"<<endl;
  outFile<<"\\usepackage{graphicx}"<<endl;
  outFile<<"\\usepackage[cm]{fullpage}"<<endl;
  outFile<<"\\begin{document}"<<endl;
  outFile<<""<<endl;
  outFile<<""<<endl;
  
  string nEvents = "";
  if(forPaper) nEvents = "$N_{events}  \\pm unc$";
  else nEvents = "$N_{events} \\pm stat \\pm sys$";
  //Inclusive Mjj
  outFile<<"\\begin{table}"<<endl;
  outFile<<"\\begin{center}"<<endl;
  outFile<<"\\begin{tabular}{cccc}"<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<"\\bf{Process}& "<<nEvents<<" & "<<nEvents<<"\\\\ "<<endl;
  outFile<<" & $\\mu$ + jets &  e + jets\\\\"<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<"\\hline "<<endl;
  
  //CalcSystTable(1);
  int ifile = 1;
  //GetInclusive("$m_{H^+}=80$ GeV", 1);
  outFile<<GetInclusive("$m_{H^+}=80$ GeV", ifile++, false)<<endl;
  outFile<<GetInclusive("$m_{H^+}=90$ GeV", ifile++, false)<<endl;
  outFile<<GetInclusive("$m_{H^+}=100$ GeV", ifile++, false)<<endl;
  outFile<<GetInclusive("$m_{H^+}=120$ GeV", ifile++, false)<<endl;
  outFile<<GetInclusive("$m_{H^+}=140$ GeV", ifile++, false)<<endl;
  outFile<<GetInclusive("$m_{H^+}=150$ GeV", ifile++, false)<<endl;
  outFile<<GetInclusive("$m_{H^+}=155$ GeV", ifile++, false)<<endl;
  outFile<<GetInclusive("$m_{H^+}=160$ GeV", ifile++, false)<<endl;
  outFile<<"\\hline "<<endl;
  //outFile<<GetInclusive("SM $t\\bar{t}$ + jets", ifile++, false)<<endl;
  ifile++;
  outFile<<GetInclusive("Single ~t", ifile++, false)<<endl;
  outFile<<GetInclusive("W + jets", ifile++, false)<<endl;
  outFile<<GetInclusive("$Z/\\gamma$ + jets", ifile++, false)<<endl;
  outFile<<GetInclusive("VV", ifile++, false)<<endl;
  outFile<<GetInclusive("MC QCD", ifile++, true)<<endl; ifile++ ;
  // outFile<<"\\hline "<<endl;
  // outFile<<GetInclusive("Data", ifile++, true)<<endl; ifile++ ;
  // outFile<<getRowInc("All background"              , fMuBkg, fEleBkg, "mjj_kfit")<<endl;
  // outFile<<"\\hline "<<endl;
  // outFile<<getRowInc("Data"                 , fMuData, fEleData, "mjj_kfit")<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<"\\end{tabular}"<<endl;
  outFile<<"\\caption{Event yield for inclusive category.}"<<endl;
  outFile<<"\\label{tab:eventYieldInc}"<<endl;
  outFile<<"\\end{center}"<<endl;
  outFile<<"\\end{table}"<<endl;
  outFile<<"\\pagebreak"<<endl;
  outFile<<"\\newpage"<<endl;
  outFile<<""<<endl;
  outFile<<""<<endl;
  
  // //Inclusive CTagL
  // outFile<<"\\begin{table}"<<endl;
  // outFile<<"\\begin{center}"<<endl;
  // outFile<<"\\begin{tabular}{cccc}"<<endl;
  // outFile<<"\\hline "<<endl;
  // outFile<<"\\hline "<<endl;
  // outFile<<"\\bf{Process}& "<<nEvents<<" & "<<nEvents<<"\\\\"<<endl;
  // outFile<<" & $\\mu$ + jets &  e + jets\\\\"<<endl;
  // outFile<<"\\hline "<<endl;
  // outFile<<"\\hline "<<endl;
  // outFile<<getRowInc("$m_{H^+}=80$ GeV", fMuWH80, fEleWH80, "mjj_kfit_CTagIncL")<<endl;
  // outFile<<getRowInc("$m_{H^+}=90$ GeV", fMuWH90, fEleWH90, "mjj_kfit_CTagIncL")<<endl;
  // outFile<<getRowInc("$m_{H^+}=100$ GeV", fMuWH100, fEleWH100, "mjj_kfit_CTagIncL")<<endl;
  // outFile<<getRowInc("$m_{H^+}=120$ GeV", fMuWH120, fEleWH120, "mjj_kfit_CTagIncL")<<endl;
  // outFile<<getRowInc("$m_{H^+}=140$ GeV", fMuWH140, fEleWH140, "mjj_kfit_CTagIncL")<<endl;
  // outFile<<getRowInc("$m_{H^+}=150$ GeV", fMuWH150, fEleWH150, "mjj_kfit_CTagIncL")<<endl;
  // outFile<<getRowInc("$m_{H^+}=155$ GeV", fMuWH155, fEleWH155, "mjj_kfit_CTagIncL")<<endl;
  // outFile<<getRowInc("$m_{H^+}=160$ GeV", fMuWH160, fEleWH160, "mjj_kfit_CTagIncL")<<endl;
  // outFile<<"\\hline "<<endl;
  // outFile<<getRowInc("SM $t\\bar{t}$ + jets", fMuTT, fEleTT, "mjj_kfit_CTagIncL")<<endl;
  // outFile<<getRowInc("Single ~t"            , fMuST, fEleST, "mjj_kfit_CTagIncL")<<endl;
  // outFile<<getRowInc("QCD multijet"                  , fMuQCD, fEleQCD, "mjj_kfit_CTagIncL")<<endl;
  // outFile<<getRowInc("W + jets"             , fMuWJ, fEleWJ, "mjj_kfit_CTagIncL")<<endl;
  // outFile<<getRowInc("$Z/\\gamma$ + jets"   , fMuDY, fEleDY, "mjj_kfit_CTagIncL")<<endl;
  // outFile<<getRowInc("VV"                   , fMuVV, fEleVV, "mjj_kfit_CTagIncL")<<endl;
  // outFile<<"\\hline "<<endl;
  // outFile<<getRowInc("All background"              , fMuBkg, fEleBkg, "mjj_kfit_CTagIncL")<<endl;
  // outFile<<"\\hline "<<endl;
  // outFile<<getRowInc("Data"                 , fMuData, fEleData, "mjj_kfit_CTagIncL")<<endl;
  // outFile<<"\\hline "<<endl;
  // outFile<<"\\end{tabular}"<<endl;
  // outFile<<"\\caption{Event yield for inclusive loose charm category.}"<<endl;
  // outFile<<"\\label{tab:eventYieldCTagInc}"<<endl;
  // outFile<<"\\end{center}"<<endl;
  // outFile<<"\\end{table}"<<endl;
  // outFile<<""<<endl;
  // outFile<<""<<endl;

  ifile = 1;
  string tableName = "Systematic and statistical uncertainties in \\% for muon (electron) channel. ";
  outFile<<"\\begin{table}"<<endl;
  outFile<<"\\begin{center}"<<endl;
  outFile<<"\\scriptsize{"<<endl;
  ///outFile<<"\\footnotesize\\setlength{\\tabcolsep}{0.3pt}"<<endl;
  outFile<<"\\begin{tabular}{  c c c c c c c c c c c c c c}"<<endl;
  outFile<<"\\multicolumn{5}{c}{ } \\\\"<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<"Process & {\\rotatebox{90}{Pileup} } & {\\rotatebox{90}{Lepton }} & {\\rotatebox{90}{btag b-jet}}  & { \\rotatebox{90}{btag l-jet} } & {\\rotatebox{90}{Prefire }} & {\\rotatebox{90}{JEC}  } & { \\rotatebox{90}{JER}  } & { \\rotatebox{90}{Norm} }  & {\\rotatebox{90}{Statistical}  }  \\\\ "<<endl;

  //pu, mu, btagb, btagl, prefire, jec, jer, norm
  outFile<<"\\hline "<<endl;
  outFile<<GetDifferential("$m_{H^+}=80$ GeV", ifile++, false)<<endl;
  outFile<<GetDifferential("$m_{H^+}=90$ GeV", ifile++, false)<<endl;
  outFile<<GetDifferential("$m_{H^+}=100$ GeV", ifile++, false)<<endl;
  outFile<<GetDifferential("$m_{H^+}=120$ GeV", ifile++, false)<<endl;
  outFile<<GetDifferential("$m_{H^+}=140$ GeV", ifile++, false)<<endl;
  outFile<<GetDifferential("$m_{H^+}=150$ GeV", ifile++, false)<<endl;
  outFile<<GetDifferential("$m_{H^+}=155$ GeV", ifile++, false)<<endl;
  outFile<<GetDifferential("$m_{H^+}=160$ GeV", ifile++, false)<<endl;
  outFile<<"\\hline "<<endl;
  // // outFile<<GetDifferential("SM $t\\bar{t}$ + jets", ifile++, false)<<endl;
  ifile++;
  outFile<<GetDifferential("Single ~t", ifile++, false)<<endl;
  outFile<<GetDifferential("W + jets", ifile++, false)<<endl;
  outFile<<GetDifferential("$Z/\\gamma$ + jets", ifile++, false)<<endl;
  outFile<<GetDifferential("VV", ifile++, false)<<endl;
  outFile<<GetDifferential("MC QCD", ifile++, true)<<endl; ifile++ ;
  outFile<<"\\hline "<<endl;  
  outFile<<"\\hline "<<endl;
  outFile<<"\\end{tabular}"<<endl;
  outFile<<"}"<<endl;
  outFile<<"\\end{center}"<<endl;
  outFile<<"\\caption{"+tableName+"}"<<endl;
  outFile<<"\\end{table}"<<endl;
  
  outFile<<"\\end{document}"<<endl;
  outFile.close();
  
  return true;
}

string GetDifferential(string rowtitle, int ifile, bool inc)
{
  int CalcSystTable(int ifile, bool isMu, double output[], double error_percnt[]);
  
  const int  nofSyst = 10;
  
  double muOut[3];
  double eleOut[3];
  double muErr[11]; //nofSyst + stat
  double eleErr[11]; //nofSyst + stat
  
  CalcSystTable(ifile, 1, muOut, muErr);
  ifile = (inc) ? ifile+1 : ifile ;
  CalcSystTable(ifile, 0, eleOut, eleErr);
  
  string combined = rowtitle + " & " + Form("$%2.1f(%2.1f)$",muErr[0],eleErr[0]) 
    + " & " + Form("$%2.1f(%2.1f)$",muErr[1],eleErr[1]) 
    + " & " + Form("$%2.1f(%2.1f)$",muErr[2],eleErr[2]) 
    + " & " + Form("$%2.1f(%2.1f)$",muErr[3],eleErr[3]) 
    + " & " + Form("$%2.1f(%2.1f)$",muErr[4],eleErr[4]) 
    + " & " + Form("$%2.1f(%2.1f)$",muErr[5],eleErr[5]) 
    + " & " + Form("$%2.1f(%2.1f)$",muErr[6],eleErr[6]) 
    + " & " + Form("$%2.1f(%2.1f)$",muErr[7],eleErr[7]) 
    + " & " + Form("$%2.1f(%2.1f)$",muErr[8],eleErr[8]) 
    // + " & " + Form("$%2.1f(%2.1f)$",muErr[9],eleErr[9]) 
    // + " & " + Form("$%2.1f(%2.1f)$",muErr[10],eleErr[10]) 
    +"\\\\";

  //cout << combined << endl;

  return combined;
}

string GetInclusive(string rowtitle, int ifile, bool inc)
{
  int CalcSystTable(int ifile, bool isMu, double output[], double error_percnt[]);
  
  const int  nofSyst = 8;
  double muOut[3];
  double eleOut[3];
  double error_percnt[11]; //nofSyst + stat

  CalcSystTable(ifile, 1, muOut, error_percnt);
  ifile = (inc) ? ifile+1 : ifile ;
  CalcSystTable(ifile, 0, eleOut, error_percnt);
  
  string combined = rowtitle +" & "+ Form("$%1.0f \\pm %1.0f(%1.1f\\%) \\pm %1.0f(%1.1f\\%)$",muOut[0],muOut[1],100.*muOut[1]/muOut[0],muOut[2],100.*muOut[2]/muOut[0]) 
    +" & "+ Form("$%1.0f \\pm %1.0f(%1.1f\\%) \\pm %1.0f(%1.1f\\%)$",eleOut[0],eleOut[1],100.*eleOut[1]/eleOut[0],eleOut[2],100.0*eleOut[2]/eleOut[0]) +"\\\\";
  //cout << combined << endl;

  return combined;
}

int CalcSystTable(int isample, bool isMu, double output[], double error_percnt[])
{
  
  int PlotRatio(TH1D *h1, TH1D *h2, const char *cname);
  double CalcSysError(TH1D *, TH1D *, TH1D *);
  
  const char *samples_2016[] = {"HplusM080", "HplusM090", "HplusM100", "HplusM120", 
				"HplusM140", "HplusM150", "HplusM155", "HplusM160",  
				"TTbar", "singleTop", "Wjets", "DYjets", "VBFusion", 
				"MCQCDMu", "MCQCDEle", "DataMu", "DataEle"};
  
  const float norm_mu_syst[] = {6.1, 6.1, 6.1, 6.1,
				6.1, 6.1, 6.1, 6.1,
                                6.1, 5.0, 5.0, 4.5,
                                4.0, 10.};

  const float norm_ele_syst[] = {6.1, 6.1, 6.1, 6.1,
				6.1, 6.1, 6.1, 6.1,
                                6.1, 5.0, 5.0, 4.5,
				 4.0, 10.};
  
  const char *syst_2016[] = {"base", 
			     "puup", "pudown", "mueffup", "mueffdown", 
			     "eleeffup", "eleeffdown",  "jecup", "jecdown", 
			     "jerup", "jerdown", "btagbup", "btagbdown", 
			     "btaglup", "btagldown", "prefireup", "prefiredown",
                             "pdfup", "pdfdown", "q2fup", "q2down",
			     "isrup", "isrdown", "fsrup", "fsrdown"};


  const char *systname_2016[] = {"nominal", 
				 "pileup up", "pileup down", "muon efficiency up", "muon efficiency down", 
				 "electron efficiency up", "electron efficiency down",  "jet energy correction up", "jet energy correction down", 
				 "jet energy resolution up", "jet energy resolution down", "btag b-quark up", "btag b-quark down", 
				 "btag l-quark up", "btag l-quark down", "prefire up", "prefire down",
				 "PDF up", "PDF down", "renormalization up", "renormalization down",
				 "ISR up", "ISR down", "FSR up", "FSR down"};
  
  //const char *inputdir = "/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/grid_v28_Syst/CBA_Skim_Syst" ;
  const char *inputdir = "/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/grid_v30_Syst/CBA_Skim_Syst_MDPt" ;
  //const char *inputdir = "/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/grid_v30_Syst/CBA_Skim_Syst_MDtune" ;
  //const char *inputdir = "/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/grid_v36_Syst/CBA_Skim_Syst_lowreso" ;
  
  //int isample = 17; 
  isample--;
  //bool isMu = 1 ;
  int ibase = 1; ibase--; 
  
  const char *histname = (isMu) ? "_kb_mjj_mu" : "_kb_mjj_ele"  ;
  
  TFile *finBase = 0x0 ; 
  TFile *finSysUp = 0x0;
  TFile *finSysDown = 0x0;

  finBase = TFile::Open(Form("%s/2016/%s_%s.root",inputdir,samples_2016[isample],syst_2016[ibase])); 

  cout<<"Openning file : "<< finBase->GetName() << endl;
  TH1D *hBase = (TH1D *)finBase->Get(histname);
  //cout<<"and get histo : " << hBase->GetName() << endl;

  //const int  sysidlist[] = (isMu) ? {2, 4, 10, 12, 14, 16, 18, 20, 22, 24} : {2, 6, 10, 12, 14, 16, 18, 20, 22, 24};
  
  const int  nofSyst = 8;
  // const int  sysidlistMu[nofSyst] = {2, 4, 12, 14, 16, 10, 18, 20, 22, 24};
  // const int  sysidlistEle[nofSyst] = {2, 6, 12, 14, 16, 10, 18, 20, 22, 24};
  const int  sysidlistMu[nofSyst] = {2, 4, 12, 14, 16, 8, 10, 10};
  const int  sysidlistEle[nofSyst] = {2, 6, 12, 14, 16, 8, 10, 10};
  double error[nofSyst];
  double error_percent[nofSyst];
  
  const int nSystGroups = 8 ; //pileup, lepton, btag-b, btag-l, prefire, jec, jer, normalization
  const char*  syst_group_name[] = {"Pileup", "Lepton", "btag-b", "btag-l", "Prefire", "JEC", "JER", "Norm"};

  double syst_Error[nSystGroups];

  double syst_Error_Percent[nSystGroups];

  int isyst = 0;
  double totSys = 0.0;

  double stat_Error = 0.0;
  double Norm = hBase->IntegralAndError(1,hBase->GetNbinsX(),stat_Error); 
  if(isample>=15){
    output[0] = Norm;
    output[1] = stat_Error ;
    output[2] = 0 ;
    return true;
  }

  //cout << "Processing for : "<<samples_2016[isample] << "nof Syst : " << nofSyst << endl;
  
  for(int idx = 0 ; idx < nofSyst ; idx++){
    
    int isysup = (isMu) ? sysidlistMu[idx] : sysidlistEle[idx] ; 
    int isysdown = isysup ;
    isysup--; 

    const char *histnameup = (isysup<=16) ? Form("%s",histname) :  Form("%s_%s",histname,syst_2016[isysup]) ;
    const char *histnamedown = (isysdown<=17) ? Form("%s",histname) :  Form("%s_%s",histname,syst_2016[isysdown]) ;
    
    if(isysup<=16)
      finSysUp = TFile::Open(Form("%s/2016/%s_%s.root",inputdir,samples_2016[isample],syst_2016[isysup])); 
    else
      finSysUp = finBase;
    
    if(isysdown<=17)
      finSysDown = TFile::Open(Form("%s/2016/%s_%s.root",inputdir,samples_2016[isample],syst_2016[isysdown])); 
    else
      finSysDown = finBase;
    
    TH1D *hSysUp = (TH1D *)finSysUp->Get(histnameup);
    TH1D *hSysDown = (TH1D *)finSysDown->Get(histnamedown);
    
    error[idx] = CalcSysError(hSysUp, hBase, hSysDown);
   
    if(idx<(nofSyst-1)){
      error_percent[idx] = 100.*error[idx]/Norm ;
    }else{
      error_percent[idx] =  (isMu) ?  norm_mu_syst[isample] : norm_ele_syst[isample] ;
      error[idx] = Norm*error_percent[idx]/100. ;
    }

    if(idx<6){
      syst_Error[isyst] = error[idx];
      syst_Error_Percent[isyst] = 100.*syst_Error[isyst]/Norm ;
      isyst++;
    }
    
    totSys += error[idx]*error[idx];
    // cout << "isample : "<<isample << "idx : " << idx << ", ibase : "<<ibase << ", isysup : "<< isysup << ", isysdown : " << isysdown << endl;
    // printf("SystType : %30s, Norm : %f, stat : %5.4f(%3.2f\%), sys : %5.4f(%3.2f\%)\n",systname_2016[isysup], Norm, stat_Error, 100.*stat_Error/Norm, error[idx], error_percent[idx]);

    error_percnt[idx] = error_percent[idx]; 
  }
  error_percnt[nofSyst] = 100.*stat_Error/Norm;

  syst_Error[isyst] = 0;
  for(int idx = 6 ; idx < nofSyst ; idx++){
    syst_Error[isyst] += error[idx]*error[idx] ;
  }
  syst_Error[isyst] = TMath::Sqrt(syst_Error[isyst]);
  syst_Error_Percent[isyst] = 100.*syst_Error[isyst]/Norm ;
  isyst++;

  totSys = TMath::Sqrt(totSys);
  double totSys_percent = 100.*totSys/Norm;
  const char *totsys = "Total Systematics";
  //printf("SystType : %30s, Norm : %f, stat : %5.4f(%3.2f\%), sys : %5.4f(%3.2f\%)\n",totsys, Norm, stat_Error, 100.*stat_Error/Norm, totSys, totSys_percent);

  output[0] = Norm;
  output[1] = stat_Error ;
  output[2] = totSys ;
  
  finSysUp->Close();
  finSysDown->Close();
  finBase->Close();

  // delete finSysUp;
  // delete finSysDown;
  // delete finBase;

  return true;
}

double CalcSysError(TH1D *hSysUp, TH1D *hBase, TH1D *hSysDown)
{
  double valUp    = hSysUp->Integral();
  double valBase  = hBase->Integral();
  double valDown  = hSysDown->Integral();

  double sys = TMath::Max(fabs(valUp - valBase), fabs(valBase - valDown));

  return sys;
}

int PlotRatio(TH1D *h1, TH1D *h2, const char *cname)
{

  TCanvas *canvas = (TCanvas *)gROOT->GetListOfCanvases()->FindObject(cname);
  
  if(!canvas){
    TCanvas *c = new TCanvas(cname, cname, 800, 800);
 
    // Upper plot will be in pad1
    TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
    pad1->SetBottomMargin(0.01); // Upper and lower plot are joined
    //pad1->SetGridx();         // Vertical grid
    pad1->Draw();             // Draw the upper pad: pad1
    pad1->cd();               // pad1 becomes the current pad
    pad1->SetTickx();
    pad1->SetTicky();
    h1->SetStats(0);          // No statistics on upper plot
    h1->Draw("hist");               // Draw h1
    h2->Draw("hist same");         // Draw h2 on top of h1
 
#if ROOT_VERSION_CODE >= ROOT_VERSION(6,8,0)
    // Avoid the first label (0) to be clipped.
    TAxis *axis = h1->GetYaxis();
    axis->ChangeLabel(1, -1, -1, -1, -1, -1, " ");
    axis->SetLabelFont(43); // Absolute font size in pixel (precision 3)
    axis->SetLabelSize(15);
#else
    // Do not draw the Y axis label on the upper plot and redraw a small
    // axis instead, in order to avoid the first label (0) to be clipped.
    h1->GetYaxis()->SetLabelSize(0.);
    TGaxis *axis = new TGaxis( -5, 20, -5, 220, 20,220,510,"");
    axis->SetLabelFont(43); // Absolute font size in pixel (precision 3)
    axis->SetLabelSize(15);
    axis->Draw();
#endif
 
    // lower plot will be in pad
    c->cd();          // Go back to the main canvas before defining pad2
    TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
    pad2->SetTopMargin(0.1);
    pad2->SetBottomMargin(0.2);
    //pad2->SetGridx(); // vertical grid
    pad2->SetGridy(); // vertical grid
    pad2->Draw();
    pad2->cd();       // pad2 becomes the current pad
    pad2->SetTickx();
    pad2->SetTicky();
 
    // Define the ratio plot
    TH1F *h3 = (TH1F*)h1->Clone("h3");
    h3->SetLineColor(h1->GetLineColor());
    h3->SetMinimum(0.2);  // Define Y ..
    h3->SetMaximum(1.8); // .. range
    h3->Sumw2();
    h3->SetStats(0);      // No statistics on lower plot
    h3->Divide(h2);
    //h3->SetMarkerStyle(21);
    h3->Draw("ep");       // Draw the ratio plot
 
    // h1 settings
    //h1->SetLineColor(kBlue+1);
    //h1->SetLineWidth(2);
 
    // Y axis h1 plot settings
    h1->GetYaxis()->SetTitle(Form("Entries / %1.0f GeV",h1->GetBinWidth(2)));
    h1->GetYaxis()->SetTitleSize(20);
    h1->GetYaxis()->SetTitleFont(43);
    h1->GetYaxis()->SetTitleOffset(1.55);
 
    // h2 settings
    //h2->SetLineColor(kRed);
    //h2->SetLineWidth(2);
 
    // Ratio plot (h3) settings
    h3->SetTitle(""); // Remove the ratio title
 
    // Y axis ratio plot settings
    h3->GetYaxis()->SetTitle("#frac{unc}{nominal}");
    h3->GetYaxis()->SetNdivisions(505);
    h3->GetYaxis()->SetTitleSize(20);
    h3->GetYaxis()->SetTitleFont(43);
    h3->GetYaxis()->SetTitleOffset(1.55);
    h3->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
    h3->GetYaxis()->SetLabelSize(15);
 
    // X axis ratio plot settings
    h3->GetXaxis()->SetTitle("m_{jj} (GeV)");
    h3->GetXaxis()->SetTitleSize(20);
    h3->GetXaxis()->SetTitleFont(43);
    h3->GetXaxis()->SetTitleOffset(3.2);
    h3->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
    h3->GetXaxis()->SetLabelSize(15);
    
    pad1->cd();

    cout<<" nof canvas primitives " << c->GetListOfPrimitives()->GetEntries() << endl ;
    
  }else {

    TPad *pad1 = (TPad *)canvas->GetListOfPrimitives()->FindObject("pad1") ;
    pad1->cd();
    
    h1->Draw("hist same");             
    h2->Draw("hist same");         
    
    TPad *pad2 = (TPad *)canvas->GetListOfPrimitives()->FindObject("pad2") ;
    pad2->cd();
    

    TH1F *h3 = (TH1F*)h1->Clone("h3");
    h3->SetLineColor(h1->GetLineColor());
    h3->Sumw2();
    h3->SetStats(0);      // No statistics on lower plot
    h3->Divide(h2);
    h3->Draw("ep same");       // Draw the ratio plot
    
    pad1->cd();
  }

  return true;
}
