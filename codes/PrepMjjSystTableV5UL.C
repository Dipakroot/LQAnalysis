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
#include <TROOT.h>
#include <TRatioPlot.h>

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>

using namespace std;

const char *sampleType[] = {
                            // "HminusM080", "HminusM090", "HminusM100", "HminusM110", 
			    // "HminusM120", "HminusM130", "HminusM140", "HminusM150", 
			    // "HminusM155", "HminusM160",  
			    // "HplusM080", "HplusM090", "HplusM100", "HplusM110", 
			    // "HplusM120", "HplusM130", "HplusM140", "HplusM150", 
			    // "HplusM155", "HplusM160",  
			    "HplmiM080", "HplmiM090", "HplmiM100", "HplmiM110", 
			    "HplmiM120", "HplmiM130", "HplmiM140", "HplmiM150", 
			    "HplmiM155", "HplmiM160",  
			    "TTbar", "singleTop", "Wjets", "DYjets", "VBFusion", 
			    "MCQCDMu", "MCQCDEle", "QCDdd", "QCDdd",
			    "DataMu", "DataEle"};

int PrepMjjSystTableV5UL(int year = 2017)
{
  string GetInclusive(string, int, bool, int, bool, bool, char, double *, double *);
  string GetDifferential(string rowtitle, int ifile, bool inc, int year, bool isKFL, bool isInc, char cType);
  
  bool forPaper = false;
  double muTot[3],eleTot[3];

  //int year = 2018;
  
  ofstream outFile;
  outFile.open(Form("syst/mjjTable_%d.tex",year));
  outFile<<"\\documentclass[]{article}"<<endl;
  outFile<<"\\usepackage{amsmath}"<<endl;
  outFile<<"\\usepackage{array}"<<endl;
  outFile<<"\\usepackage{multirow}"<<endl;
  outFile<<"\\usepackage{graphicx}"<<endl;
  outFile<<"\\usepackage{adjustbox}"<<endl;
  outFile<<"\\usepackage{pdflscape}"<<endl;
  outFile<<"\\usepackage[cm]{fullpage}"<<endl;
  outFile<<"\\begin{document}"<<endl;
  outFile<<""<<endl;
  outFile<<""<<endl;
  

  bool isKFL = true;
  bool isInc = true;
  char cType = 'L';
  string tab1_caption = "Event yield for inclusive category.";
  string tab2_caption = "Systematic and statistical uncertainties in \\% for muon (electron) channel for inclusive category. ";
  string nEvents = "";
  if(forPaper) nEvents = "$N_{events}  \\pm unc$";
  else nEvents = "$N_{events} \\pm stat \\pm sys$";
  //Inclusive Mjj
  outFile<<"\\begin{table}"<<endl;
  outFile<<"\\begin{center}"<<endl;
  outFile<<"\\begin{adjustbox}{width=\\textwidth}"<<endl;
  outFile<<"\\begin{tabular}{cccc}"<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<"\\bf{Process}& "<<nEvents<<" & "<<nEvents<<"\\\\ "<<endl;
  outFile<<" & $\\mu$ + jets &  e + jets\\\\"<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<"\\hline "<<endl;
  
  //CalcSystTable(1);
  int ifile = 1;
  int ifileData = -1;
  //GetInclusive("$m_{H^-}=80$ GeV", 1);
  outFile<<GetInclusive("$H^{+} + H^{-} (m=80$ GeV)", ifile++, false, year, isKFL, isInc, cType, muTot, eleTot)<<endl;
  outFile<<GetInclusive("$H^{+} + H^{-} (m=90$ GeV)", ifile++, false, year, isKFL, isInc, cType, muTot, eleTot)<<endl;
  outFile<<GetInclusive("$H^{+} + H^{-} (m=100$ GeV)", ifile++, false, year, isKFL, isInc, cType, muTot, eleTot)<<endl;
  outFile<<GetInclusive("$H^{+} + H^{-} (m=110$ GeV)", ifile++, false, year, isKFL, isInc, cType, muTot, eleTot)<<endl;
  outFile<<GetInclusive("$H^{+} + H^{-} (m=120$ GeV)", ifile++, false, year, isKFL, isInc, cType, muTot, eleTot)<<endl;
  outFile<<GetInclusive("$H^{+} + H^{-} (m=130$ GeV)", ifile++, false, year, isKFL, isInc, cType, muTot, eleTot)<<endl;
  outFile<<GetInclusive("$H^{+} + H^{-} (m=140$ GeV)", ifile++, false, year, isKFL, isInc, cType, muTot, eleTot)<<endl;
  outFile<<GetInclusive("$H^{+} + H^{-} (m=150$ GeV)", ifile++, false, year, isKFL, isInc, cType, muTot, eleTot)<<endl;
  outFile<<GetInclusive("$H^{+} + H^{-} (m=155$ GeV)", ifile++, false, year, isKFL, isInc, cType, muTot, eleTot)<<endl;
  outFile<<GetInclusive("$H^{+} + H^{-} (m=160$ GeV)", ifile++, false, year, isKFL, isInc, cType, muTot, eleTot)<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<GetInclusive("SM $t\\bar{t}$ + jets", ifile++, false, year, isKFL, isInc, cType, muTot, eleTot)<<endl;
  outFile<<GetInclusive("Single ~t", ifile++, false, year, isKFL, isInc, cType, muTot, eleTot)<<endl;
  outFile<<GetInclusive("W + jets", ifile++, false, year, isKFL, isInc, cType, muTot, eleTot)<<endl;
  outFile<<GetInclusive("$Z/\\gamma$ + jets", ifile++, false, year, isKFL, isInc, cType, muTot, eleTot)<<endl;
  outFile<<GetInclusive("VV", ifile++, false, year, isKFL, isInc, cType, muTot, eleTot)<<endl;
  outFile<<GetInclusive("MC QCD", ifile++, true, year, isKFL, isInc, cType, muTot, eleTot)<<endl; ifile++ ;
  outFile<<GetInclusive("DD QCD", ifile++, true, year, isKFL, isInc, cType, muTot, eleTot)<<endl; ifile++ ;
  outFile<<"\\hline "<<endl;
  outFile<<GetInclusive("All background", ifile, true, year, isKFL, isInc, cType, muTot, eleTot)<<endl; ifileData = ifile;
  outFile<<"\\hline "<<endl;
  outFile<<GetInclusive("Data", ifile++, true, year, isKFL, isInc, cType, muTot, eleTot)<<endl;  ifile++ ;
  outFile<<"\\hline "<<endl;
  outFile<<GetInclusive("Data/Bkg", ifileData, true, year, isKFL, isInc, cType, muTot, eleTot)<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<"\\end{tabular}"<<endl;
  //outFile<<"\\caption{"<<tab1_caption<<"}"<<endl;
  outFile<<"\\label{tab:eventYieldInc}"<<endl;
  outFile<<"\\end{adjustbox}"<<endl;
  outFile<<"\\end{center}"<<endl;
  outFile<<"\\end{table}"<<endl;
  outFile<<"\\pagebreak"<<endl;
  outFile<<"\\newpage"<<endl;
  outFile<<""<<endl;
  outFile<<""<<endl;
  

  ifile = 1;
  outFile<<"\\begin{table}"<<endl;
  outFile<<"\\begin{center}"<<endl;
  outFile<<"\\begin{adjustbox}{width=\\textwidth}"<<endl;
  outFile<<"\\scriptsize{"<<endl;
  ///outFile<<"\\footnotesize\\setlength{\\tabcolsep}{0.3pt}"<<endl;
  outFile<<"\\begin{tabular}{  cccc cccc ccc}"<<endl;
  outFile<<"\\multicolumn{5}{c}{ } \\\\"<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<"Process & {\\rotatebox{90}{Pileup} } & {\\rotatebox{90}{Lepton }} & {\\rotatebox{90}{b \\& c tagging 1}}  & {\\rotatebox{90}{b \\& c tagging 2}}  & { \\rotatebox{90}{b \\& c tagging 3} } & {\\rotatebox{90}{Prefire }} & {\\rotatebox{90}{JEC}  } & { \\rotatebox{90}{JER}  } & { \\rotatebox{90}{Norm} }  & {\\rotatebox{90}{Statistical}  }  \\\\ "<<endl;

  //pu, mu, btagb, btagl, prefire, jec, jer, norm
  outFile<<"\\hline "<<endl;
  outFile<<GetDifferential("$H^{+} + H^{-} (m=80$ GeV)", ifile++, false, year, isKFL, isInc, cType)<<endl;
  outFile<<GetDifferential("$H^{+} + H^{-} (m=90$ GeV)", ifile++, false, year, isKFL, isInc, cType)<<endl;
  outFile<<GetDifferential("$H^{+} + H^{-} (m=100$ GeV)", ifile++, false, year, isKFL, isInc, cType)<<endl;
  outFile<<GetDifferential("$H^{+} + H^{-} (m=110$ GeV)", ifile++, false, year, isKFL, isInc, cType)<<endl;
  outFile<<GetDifferential("$H^{+} + H^{-} (m=120$ GeV)", ifile++, false, year, isKFL, isInc, cType)<<endl;
  outFile<<GetDifferential("$H^{+} + H^{-} (m=130$ GeV)", ifile++, false, year, isKFL, isInc, cType)<<endl;
  outFile<<GetDifferential("$H^{+} + H^{-} (m=140$ GeV)", ifile++, false, year, isKFL, isInc, cType)<<endl;
  outFile<<GetDifferential("$H^{+} + H^{-} (m=150$ GeV)", ifile++, false, year, isKFL, isInc, cType)<<endl;
  outFile<<GetDifferential("$H^{+} + H^{-} (m=155$ GeV)", ifile++, false, year, isKFL, isInc, cType)<<endl;
  outFile<<GetDifferential("$H^{+} + H^{-} (m=160$ GeV)", ifile++, false, year, isKFL, isInc, cType)<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<GetDifferential("SM $t\\bar{t}$ + jets", ifile++, false, year, isKFL, isInc, cType)<<endl;
  outFile<<GetDifferential("Single ~t", ifile++, false, year, isKFL, isInc, cType)<<endl;
  outFile<<GetDifferential("W + jets", ifile++, false, year, isKFL, isInc, cType)<<endl;
  outFile<<GetDifferential("$Z/\\gamma$ + jets", ifile++, false, year, isKFL, isInc, cType)<<endl;
  outFile<<GetDifferential("VV", ifile++, false, year, isKFL, isInc, cType)<<endl; ifile = ifile+2;
  outFile<<GetDifferential("DD QCD", ifile++, true, year, isKFL, isInc, cType)<<endl; ifile++ ;
  outFile<<"\\hline "<<endl;  
  outFile<<"\\hline "<<endl;
  outFile<<"\\end{tabular}"<<endl;
  outFile<<"}"<<endl;
  outFile<<"\\end{adjustbox}"<<endl;
  outFile<<"\\end{center}"<<endl;
  //outFile<<"\\caption{"+tab2_caption+"}"<<endl;
  outFile<<"\\end{table}"<<endl;


  //////////////////////////////////////////////////////////////////////////////////////////////////
  //exclusive loose charm
  //////////////////////////////////////////////////////////////////////////////////////////////////

  isKFL = false;
  isInc = false;
  cType = 'L';
  tab1_caption = "Event yield for exclusive loose charm tagging category.";
  tab2_caption = "Systematic and statistical uncertainties in \\% for muon (electron) channel for exclusive loose charm tagging category. ";
  
  nEvents = "";
  if(forPaper) nEvents = "$N_{events}  \\pm unc$";
  else nEvents = "$N_{events} \\pm stat \\pm sys$";
  //Exclusive Mjj
  outFile<<"\\begin{table}"<<endl;
  outFile<<"\\begin{center}"<<endl;
  outFile<<"\\begin{adjustbox}{width=\\textwidth}"<<endl;
  outFile<<"\\begin{tabular}{cccc}"<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<"\\bf{Process}& "<<nEvents<<" & "<<nEvents<<"\\\\ "<<endl;
  outFile<<" & $\\mu$ + jets &  e + jets\\\\"<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<"\\hline "<<endl;
  
  //CalcSystTable(1);
  ifile = 1;
  //GetInclusive("$H^{+} + H^{-} (m=80$ GeV)", 1);
  outFile<<GetInclusive("$H^{+} + H^{-} (m=80$ GeV)", ifile++, false, year, isKFL, isInc, cType, muTot, eleTot)<<endl;
  outFile<<GetInclusive("$H^{+} + H^{-} (m=90$ GeV)", ifile++, false, year, isKFL, isInc, cType, muTot, eleTot)<<endl;
  outFile<<GetInclusive("$H^{+} + H^{-} (m=100$ GeV)", ifile++, false, year, isKFL, isInc, cType, muTot, eleTot)<<endl;
  outFile<<GetInclusive("$H^{+} + H^{-} (m=110$ GeV)", ifile++, false, year, isKFL, isInc, cType, muTot, eleTot)<<endl;
  outFile<<GetInclusive("$H^{+} + H^{-} (m=120$ GeV)", ifile++, false, year, isKFL, isInc, cType, muTot, eleTot)<<endl;
  outFile<<GetInclusive("$H^{+} + H^{-} (m=130$ GeV)", ifile++, false, year, isKFL, isInc, cType, muTot, eleTot)<<endl;
  outFile<<GetInclusive("$H^{+} + H^{-} (m=140$ GeV)", ifile++, false, year, isKFL, isInc, cType, muTot, eleTot)<<endl;
  outFile<<GetInclusive("$H^{+} + H^{-} (m=150$ GeV)", ifile++, false, year, isKFL, isInc, cType, muTot, eleTot)<<endl;
  outFile<<GetInclusive("$H^{+} + H^{-} (m=155$ GeV)", ifile++, false, year, isKFL, isInc, cType, muTot, eleTot)<<endl;
  outFile<<GetInclusive("$H^{+} + H^{-} (m=160$ GeV)", ifile++, false, year, isKFL, isInc, cType, muTot, eleTot)<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<GetInclusive("SM $t\\bar{t}$ + jets", ifile++, false, year, isKFL, isInc, cType, muTot, eleTot)<<endl;
  outFile<<GetInclusive("Single ~t", ifile++, false, year, isKFL, isInc, cType, muTot, eleTot)<<endl;
  outFile<<GetInclusive("W + jets", ifile++, false, year, isKFL, isInc, cType, muTot, eleTot)<<endl;
  outFile<<GetInclusive("$Z/\\gamma$ + jets", ifile++, false, year, isKFL, isInc, cType, muTot, eleTot)<<endl;
  outFile<<GetInclusive("VV", ifile++, false, year, isKFL, isInc, cType, muTot, eleTot)<<endl;
  outFile<<GetInclusive("MC QCD", ifile++, true, year, isKFL, isInc, cType, muTot, eleTot)<<endl; ifile++ ;
  outFile<<GetInclusive("DD QCD", ifile++, true, year, isKFL, isInc, cType, muTot, eleTot)<<endl; ifile++ ;
  outFile<<"\\hline "<<endl;
  outFile<<GetInclusive("All background", ifile, true, year, isKFL, isInc, cType, muTot, eleTot)<<endl; 
  outFile<<"\\hline "<<endl;
  outFile<<GetInclusive("Data", ifile++, true, year, isKFL, isInc, cType, muTot, eleTot)<<endl; ifile++ ;
  outFile<<"\\hline "<<endl;
  outFile<<GetInclusive("Data/Bkg", ifileData, true, year, isKFL, isInc, cType, muTot, eleTot)<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<"\\end{tabular}"<<endl;
  //outFile<<"\\caption{"<<tab1_caption<<"}"<<endl;
  outFile<<"\\label{tab:eventYieldInc}"<<endl;
  outFile<<"\\end{adjustbox}"<<endl;
  outFile<<"\\end{center}"<<endl;
  outFile<<"\\end{table}"<<endl;
  outFile<<"\\pagebreak"<<endl;
  outFile<<"\\newpage"<<endl;
  outFile<<""<<endl;
  outFile<<""<<endl;
  

  ifile = 1;
  outFile<<"\\begin{table}"<<endl;
  outFile<<"\\begin{center}"<<endl;
  outFile<<"\\begin{adjustbox}{width=\\textwidth}"<<endl;
  outFile<<"\\scriptsize{"<<endl;
  ///outFile<<"\\footnotesize\\setlength{\\tabcolsep}{0.3pt}"<<endl;
  outFile<<"\\begin{tabular}{  cccc cccc ccc}"<<endl;
  outFile<<"\\multicolumn{5}{c}{ } \\\\"<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<"Process & {\\rotatebox{90}{Pileup} } & {\\rotatebox{90}{Lepton }} & {\\rotatebox{90}{b \\& c tagging 1}}  & {\\rotatebox{90}{b \\& c tagging 2}}  & { \\rotatebox{90}{b \\& c tagging 3} } & {\\rotatebox{90}{Prefire }} & {\\rotatebox{90}{JEC}  } & { \\rotatebox{90}{JER}  } & { \\rotatebox{90}{Norm} }  & {\\rotatebox{90}{Statistical}  }  \\\\ "<<endl;

  //pu, mu, btagb, btagl, prefire, jec, jer, norm
  outFile<<"\\hline "<<endl;
  outFile<<GetDifferential("$H^{+} + H^{-} (m=80$ GeV)", ifile++, false, year, isKFL, isInc, cType)<<endl;
  outFile<<GetDifferential("$H^{+} + H^{-} (m=90$ GeV)", ifile++, false, year, isKFL, isInc, cType)<<endl;
  outFile<<GetDifferential("$H^{+} + H^{-} (m=100$ GeV)", ifile++, false, year, isKFL, isInc, cType)<<endl;
  outFile<<GetDifferential("$H^{+} + H^{-} (m=110$ GeV)", ifile++, false, year, isKFL, isInc, cType)<<endl;
  outFile<<GetDifferential("$H^{+} + H^{-} (m=120$ GeV)", ifile++, false, year, isKFL, isInc, cType)<<endl;
  outFile<<GetDifferential("$H^{+} + H^{-} (m=130$ GeV)", ifile++, false, year, isKFL, isInc, cType)<<endl;
  outFile<<GetDifferential("$H^{+} + H^{-} (m=140$ GeV)", ifile++, false, year, isKFL, isInc, cType)<<endl;
  outFile<<GetDifferential("$H^{+} + H^{-} (m=150$ GeV)", ifile++, false, year, isKFL, isInc, cType)<<endl;
  outFile<<GetDifferential("$H^{+} + H^{-} (m=155$ GeV)", ifile++, false, year, isKFL, isInc, cType)<<endl;
  outFile<<GetDifferential("$H^{+} + H^{-} (m=160$ GeV)", ifile++, false, year, isKFL, isInc, cType)<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<GetDifferential("SM $t\\bar{t}$ + jets", ifile++, false, year, isKFL, isInc, cType)<<endl;
  outFile<<GetDifferential("Single ~t", ifile++, false, year, isKFL, isInc, cType)<<endl;
  outFile<<GetDifferential("W + jets", ifile++, false, year, isKFL, isInc, cType)<<endl;
  outFile<<GetDifferential("$Z/\\gamma$ + jets", ifile++, false, year, isKFL, isInc, cType)<<endl;
  outFile<<GetDifferential("VV", ifile++, false, year, isKFL, isInc, cType)<<endl;ifile = ifile+2;
  outFile<<GetDifferential("DD QCD", ifile++, true, year, isKFL, isInc, cType)<<endl; ifile++ ;
  outFile<<"\\hline "<<endl;  
  outFile<<"\\hline "<<endl;
  outFile<<"\\end{tabular}"<<endl;
  outFile<<"}"<<endl;
  outFile<<"\\end{adjustbox}"<<endl;
  outFile<<"\\end{center}"<<endl;
  //outFile<<"\\caption{"+tab2_caption+"}"<<endl;
  outFile<<"\\end{table}"<<endl;
  /////////////////////////////////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////////////////////////
  //exclusive medium charm
  //////////////////////////////////////////////////////////////////////////////////////////////////

  isKFL = false;
  isInc = false;
  cType = 'M';
  tab1_caption = "Event yield for exclusive medium charm tagging category.";
  tab2_caption = "Systematic and statistical uncertainties in \\% for muon (electron) channel for exclusive medium charm tagging category. ";
  
  nEvents = "";
  if(forPaper) nEvents = "$N_{events}  \\pm unc$";
  else nEvents = "$N_{events} \\pm stat \\pm sys$";
  //Exclusive Mjj
  outFile<<"\\begin{table}"<<endl;
  outFile<<"\\begin{center}"<<endl;
  outFile<<"\\begin{adjustbox}{width=\\textwidth}"<<endl;
  outFile<<"\\begin{tabular}{cccc}"<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<"\\bf{Process}& "<<nEvents<<" & "<<nEvents<<"\\\\ "<<endl;
  outFile<<" & $\\mu$ + jets &  e + jets\\\\"<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<"\\hline "<<endl;
  
  //CalcSystTable(1);
  ifile = 1;
  //GetInclusive("$H^{+} + H^{-} (m=80$ GeV)", 1);
  outFile<<GetInclusive("$H^{+} + H^{-} (m=80$ GeV)", ifile++, false, year, isKFL, isInc, cType, muTot, eleTot)<<endl;
  outFile<<GetInclusive("$H^{+} + H^{-} (m=90$ GeV)", ifile++, false, year, isKFL, isInc, cType, muTot, eleTot)<<endl;
  outFile<<GetInclusive("$H^{+} + H^{-} (m=100$ GeV)", ifile++, false, year, isKFL, isInc, cType, muTot, eleTot)<<endl;
  outFile<<GetInclusive("$H^{+} + H^{-} (m=110$ GeV)", ifile++, false, year, isKFL, isInc, cType, muTot, eleTot)<<endl;
  outFile<<GetInclusive("$H^{+} + H^{-} (m=120$ GeV)", ifile++, false, year, isKFL, isInc, cType, muTot, eleTot)<<endl;
  outFile<<GetInclusive("$H^{+} + H^{-} (m=130$ GeV)", ifile++, false, year, isKFL, isInc, cType, muTot, eleTot)<<endl;
  outFile<<GetInclusive("$H^{+} + H^{-} (m=140$ GeV)", ifile++, false, year, isKFL, isInc, cType, muTot, eleTot)<<endl;
  outFile<<GetInclusive("$H^{+} + H^{-} (m=150$ GeV)", ifile++, false, year, isKFL, isInc, cType, muTot, eleTot)<<endl;
  outFile<<GetInclusive("$H^{+} + H^{-} (m=155$ GeV)", ifile++, false, year, isKFL, isInc, cType, muTot, eleTot)<<endl;
  outFile<<GetInclusive("$H^{+} + H^{-} (m=160$ GeV)", ifile++, false, year, isKFL, isInc, cType, muTot, eleTot)<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<GetInclusive("SM $t\\bar{t}$ + jets", ifile++, false, year, isKFL, isInc, cType, muTot, eleTot)<<endl;
  outFile<<GetInclusive("Single ~t", ifile++, false, year, isKFL, isInc, cType, muTot, eleTot)<<endl;
  outFile<<GetInclusive("W + jets", ifile++, false, year, isKFL, isInc, cType, muTot, eleTot)<<endl;
  outFile<<GetInclusive("$Z/\\gamma$ + jets", ifile++, false, year, isKFL, isInc, cType, muTot, eleTot)<<endl;
  outFile<<GetInclusive("VV", ifile++, false, year, isKFL, isInc, cType, muTot, eleTot)<<endl;
  outFile<<GetInclusive("MC QCD", ifile++, true, year, isKFL, isInc, cType, muTot, eleTot)<<endl; ifile++ ;
  outFile<<GetInclusive("DD QCD", ifile++, true, year, isKFL, isInc, cType, muTot, eleTot)<<endl; ifile++ ;
  outFile<<"\\hline "<<endl;
  outFile<<GetInclusive("All background", ifile, true, year, isKFL, isInc, cType, muTot, eleTot)<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<GetInclusive("Data", ifile++, true, year, isKFL, isInc, cType, muTot, eleTot)<<endl; ifile++ ;
  outFile<<"\\hline "<<endl;
  outFile<<GetInclusive("Data/Bkg", ifileData, true, year, isKFL, isInc, cType, muTot, eleTot)<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<"\\end{tabular}"<<endl;
  //outFile<<"\\caption{"<<tab1_caption<<"}"<<endl;
  outFile<<"\\label{tab:eventYieldInc}"<<endl;
  outFile<<"\\end{adjustbox}"<<endl;
  outFile<<"\\end{center}"<<endl;
  outFile<<"\\end{table}"<<endl;
  outFile<<"\\pagebreak"<<endl;
  outFile<<"\\newpage"<<endl;
  outFile<<""<<endl;
  outFile<<""<<endl;
  

  ifile = 1;
  outFile<<"\\begin{table}"<<endl;
  outFile<<"\\begin{center}"<<endl;
  outFile<<"\\begin{adjustbox}{width=\\textwidth}"<<endl;
  outFile<<"\\scriptsize{"<<endl;
  ///outFile<<"\\footnotesize\\setlength{\\tabcolsep}{0.3pt}"<<endl;
  outFile<<"\\begin{tabular}{  cccc cccc ccc}"<<endl;
  outFile<<"\\multicolumn{5}{c}{ } \\\\"<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<"Process & {\\rotatebox{90}{Pileup} } & {\\rotatebox{90}{Lepton }} & {\\rotatebox{90}{b \\& c tagging 1}}  & {\\rotatebox{90}{b \\& c tagging 2}}  & { \\rotatebox{90}{b \\& c tagging 3} } & {\\rotatebox{90}{Prefire }} & {\\rotatebox{90}{JEC}  } & { \\rotatebox{90}{JER}  } & { \\rotatebox{90}{Norm} }  & {\\rotatebox{90}{Statistical}  }  \\\\ "<<endl;

  //pu, mu, btagb, btagl, prefire, jec, jer, norm
  outFile<<"\\hline "<<endl;
  outFile<<GetDifferential("$H^{+} + H^{-} (m=80$ GeV)", ifile++, false, year, isKFL, isInc, cType)<<endl;
  outFile<<GetDifferential("$H^{+} + H^{-} (m=90$ GeV)", ifile++, false, year, isKFL, isInc, cType)<<endl;
  outFile<<GetDifferential("$H^{+} + H^{-} (m=100$ GeV)", ifile++, false, year, isKFL, isInc, cType)<<endl;
  outFile<<GetDifferential("$H^{+} + H^{-} (m=110$ GeV)", ifile++, false, year, isKFL, isInc, cType)<<endl;
  outFile<<GetDifferential("$H^{+} + H^{-} (m=120$ GeV)", ifile++, false, year, isKFL, isInc, cType)<<endl;
  outFile<<GetDifferential("$H^{+} + H^{-} (m=130$ GeV)", ifile++, false, year, isKFL, isInc, cType)<<endl;
  outFile<<GetDifferential("$H^{+} + H^{-} (m=140$ GeV)", ifile++, false, year, isKFL, isInc, cType)<<endl;
  outFile<<GetDifferential("$H^{+} + H^{-} (m=150$ GeV)", ifile++, false, year, isKFL, isInc, cType)<<endl;
  outFile<<GetDifferential("$H^{+} + H^{-} (m=155$ GeV)", ifile++, false, year, isKFL, isInc, cType)<<endl;
  outFile<<GetDifferential("$H^{+} + H^{-} (m=160$ GeV)", ifile++, false, year, isKFL, isInc, cType)<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<GetDifferential("SM $t\\bar{t}$ + jets", ifile++, false, year, isKFL, isInc, cType)<<endl;
  outFile<<GetDifferential("Single ~t", ifile++, false, year, isKFL, isInc, cType)<<endl;
  outFile<<GetDifferential("W + jets", ifile++, false, year, isKFL, isInc, cType)<<endl;
  outFile<<GetDifferential("$Z/\\gamma$ + jets", ifile++, false, year, isKFL, isInc, cType)<<endl;
  outFile<<GetDifferential("VV", ifile++, false, year, isKFL, isInc, cType)<<endl; ifile = ifile + 2;
  outFile<<GetDifferential("DD QCD", ifile++, true, year, isKFL, isInc, cType)<<endl; ifile++ ;
  outFile<<"\\hline "<<endl;  
  outFile<<"\\hline "<<endl;
  outFile<<"\\end{tabular}"<<endl;
  outFile<<"}"<<endl;
  outFile<<"\\end{adjustbox}"<<endl;
  outFile<<"\\end{center}"<<endl;
  //outFile<<"\\caption{"+tab2_caption+"}"<<endl;
  outFile<<"\\end{table}"<<endl;
  /////////////////////////////////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////////////////////////
  //exclusive tight charm
  //////////////////////////////////////////////////////////////////////////////////////////////////

  isKFL = false;
  isInc = false;
  cType = 'T';
  tab1_caption = "Event yield for exclusive tight charm tagging category.";
  tab2_caption = "Systematic and statistical uncertainties in \\% for muon (electron) channel for exclusive tight charm tagging category. ";
  
  nEvents = "";
  if(forPaper) nEvents = "$N_{events}  \\pm unc$";
  else nEvents = "$N_{events} \\pm stat \\pm sys$";
  //Exclusive Mjj
  outFile<<"\\begin{table}"<<endl;
  outFile<<"\\begin{center}"<<endl;
  outFile<<"\\begin{adjustbox}{width=\\textwidth}"<<endl;
  outFile<<"\\begin{tabular}{cccc}"<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<"\\bf{Process}& "<<nEvents<<" & "<<nEvents<<"\\\\ "<<endl;
  outFile<<" & $\\mu$ + jets &  e + jets\\\\"<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<"\\hline "<<endl;
  
  //CalcSystTable(1);
  ifile = 1;
  //GetInclusive("$H^{+} + H^{-} (m=80$ GeV)", 1);
  outFile<<GetInclusive("$H^{+} + H^{-} (m=80$ GeV)", ifile++, false, year, isKFL, isInc, cType, muTot, eleTot)<<endl;
  outFile<<GetInclusive("$H^{+} + H^{-} (m=90$ GeV)", ifile++, false, year, isKFL, isInc, cType, muTot, eleTot)<<endl;
  outFile<<GetInclusive("$H^{+} + H^{-} (m=100$ GeV)", ifile++, false, year, isKFL, isInc, cType, muTot, eleTot)<<endl;
  outFile<<GetInclusive("$H^{+} + H^{-} (m=110$ GeV)", ifile++, false, year, isKFL, isInc, cType, muTot, eleTot)<<endl;
  outFile<<GetInclusive("$H^{+} + H^{-} (m=120$ GeV)", ifile++, false, year, isKFL, isInc, cType, muTot, eleTot)<<endl;
  outFile<<GetInclusive("$H^{+} + H^{-} (m=130$ GeV)", ifile++, false, year, isKFL, isInc, cType, muTot, eleTot)<<endl;
  outFile<<GetInclusive("$H^{+} + H^{-} (m=140$ GeV)", ifile++, false, year, isKFL, isInc, cType, muTot, eleTot)<<endl;
  outFile<<GetInclusive("$H^{+} + H^{-} (m=150$ GeV)", ifile++, false, year, isKFL, isInc, cType, muTot, eleTot)<<endl;
  outFile<<GetInclusive("$H^{+} + H^{-} (m=155$ GeV)", ifile++, false, year, isKFL, isInc, cType, muTot, eleTot)<<endl;
  outFile<<GetInclusive("$H^{+} + H^{-} (m=160$ GeV)", ifile++, false, year, isKFL, isInc, cType, muTot, eleTot)<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<GetInclusive("SM $t\\bar{t}$ + jets", ifile++, false, year, isKFL, isInc, cType, muTot, eleTot)<<endl;
  outFile<<GetInclusive("Single ~t", ifile++, false, year, isKFL, isInc, cType, muTot, eleTot)<<endl;
  outFile<<GetInclusive("W + jets", ifile++, false, year, isKFL, isInc, cType, muTot, eleTot)<<endl;
  outFile<<GetInclusive("$Z/\\gamma$ + jets", ifile++, false, year, isKFL, isInc, cType, muTot, eleTot)<<endl;
  outFile<<GetInclusive("VV", ifile++, false, year, isKFL, isInc, cType, muTot, eleTot)<<endl;
  outFile<<GetInclusive("MC QCD", ifile++, true, year, isKFL, isInc, cType, muTot, eleTot)<<endl; ifile++ ;
  outFile<<GetInclusive("DD QCD", ifile++, true, year, isKFL, isInc, cType, muTot, eleTot)<<endl; ifile++ ;
  outFile<<"\\hline "<<endl;
  outFile<<GetInclusive("All background", ifile, true, year, isKFL, isInc, cType, muTot, eleTot)<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<GetInclusive("Data", ifile++, true, year, isKFL, isInc, cType, muTot, eleTot)<<endl; ifile++ ;
  outFile<<"\\hline "<<endl;
  outFile<<GetInclusive("Data/Bkg", ifileData, true, year, isKFL, isInc, cType, muTot, eleTot)<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<"\\end{tabular}"<<endl;
  //outFile<<"\\caption{"<<tab1_caption<<"}"<<endl;
  outFile<<"\\label{tab:eventYieldInc}"<<endl;
  outFile<<"\\end{adjustbox}"<<endl;
  outFile<<"\\end{center}"<<endl;
  outFile<<"\\end{table}"<<endl;
  outFile<<"\\pagebreak"<<endl;
  outFile<<"\\newpage"<<endl;
  outFile<<""<<endl;
  outFile<<""<<endl;
  

  ifile = 1;
  outFile<<"\\begin{table}"<<endl;
  outFile<<"\\begin{center}"<<endl;
  outFile<<"\\begin{adjustbox}{width=\\textwidth}"<<endl;
  outFile<<"\\scriptsize{"<<endl;
  ///outFile<<"\\footnotesize\\setlength{\\tabcolsep}{0.3pt}"<<endl;
  outFile<<"\\begin{tabular}{  cccc cccc ccc}"<<endl;
  outFile<<"\\multicolumn{5}{c}{ } \\\\"<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<"Process & {\\rotatebox{90}{Pileup} } & {\\rotatebox{90}{Lepton }} & {\\rotatebox{90}{b \\& c tagging 1}}  & {\\rotatebox{90}{b \\& c tagging 2}}  & { \\rotatebox{90}{b \\& c tagging 3} } & {\\rotatebox{90}{Prefire }} & {\\rotatebox{90}{JEC}  } & { \\rotatebox{90}{JER}  } & { \\rotatebox{90}{Norm} }  & {\\rotatebox{90}{Statistical}  }  \\\\ "<<endl;

  //pu, mu, btagb, btagl, prefire, jec, jer, norm
  outFile<<"\\hline "<<endl;
  outFile<<GetDifferential("$H^{+} + H^{-} (m=80$ GeV)", ifile++, false, year, isKFL, isInc, cType)<<endl;
  outFile<<GetDifferential("$H^{+} + H^{-} (m=90$ GeV)", ifile++, false, year, isKFL, isInc, cType)<<endl;
  outFile<<GetDifferential("$H^{+} + H^{-} (m=100$ GeV)", ifile++, false, year, isKFL, isInc, cType)<<endl;
  outFile<<GetDifferential("$H^{+} + H^{-} (m=110$ GeV)", ifile++, false, year, isKFL, isInc, cType)<<endl;
  outFile<<GetDifferential("$H^{+} + H^{-} (m=120$ GeV)", ifile++, false, year, isKFL, isInc, cType)<<endl;
  outFile<<GetDifferential("$H^{+} + H^{-} (m=130$ GeV)", ifile++, false, year, isKFL, isInc, cType)<<endl;
  outFile<<GetDifferential("$H^{+} + H^{-} (m=140$ GeV)", ifile++, false, year, isKFL, isInc, cType)<<endl;
  outFile<<GetDifferential("$H^{+} + H^{-} (m=150$ GeV)", ifile++, false, year, isKFL, isInc, cType)<<endl;
  outFile<<GetDifferential("$H^{+} + H^{-} (m=155$ GeV)", ifile++, false, year, isKFL, isInc, cType)<<endl;
  outFile<<GetDifferential("$H^{+} + H^{-} (m=160$ GeV)", ifile++, false, year, isKFL, isInc, cType)<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<GetDifferential("SM $t\\bar{t}$ + jets", ifile++, false, year, isKFL, isInc, cType)<<endl;
  outFile<<GetDifferential("Single ~t", ifile++, false, year, isKFL, isInc, cType)<<endl;
  outFile<<GetDifferential("W + jets", ifile++, false, year, isKFL, isInc, cType)<<endl;
  outFile<<GetDifferential("$Z/\\gamma$ + jets", ifile++, false, year, isKFL, isInc, cType)<<endl;
  outFile<<GetDifferential("VV", ifile++, false, year, isKFL, isInc, cType)<<endl; ifile = ifile + 2;
  outFile<<GetDifferential("DD QCD", ifile++, true, year, isKFL, isInc, cType)<<endl; ifile++ ;
  outFile<<"\\hline "<<endl;  
  outFile<<"\\hline "<<endl;
  outFile<<"\\end{tabular}"<<endl;
  outFile<<"}"<<endl;
  outFile<<"\\end{adjustbox}"<<endl;
  outFile<<"\\end{center}"<<endl;
  //outFile<<"\\caption{"+tab2_caption+"}"<<endl;
  outFile<<"\\end{table}"<<endl;
  /////////////////////////////////////////////////////////////////////////////////////////////////////////

  outFile<<"\\end{document}"<<endl;
  outFile.close();
  
  return true;
}

string GetDifferential(string rowtitle, int ifile, bool inc, int year, bool isKFL, bool isInc, char cType)
{
  int CalcSystTable(int ifile, bool isMu, double output[], double error_percnt[], int year, bool isKFL, bool isIncl, char cType);
  
  const int  nofSyst = 10;
  
  double muOut[3];
  double eleOut[3];
  double muErr[11]; //nofSyst + stat
  double eleErr[11]; //nofSyst + stat
  
  for(int i=0;i<11;i++) muErr[i] = eleErr[i] = 0.0 ;
  for(int i=0;i<3;i++) muOut[i] = eleOut[i] = 0.0 ;
  CalcSystTable(ifile, 1, muOut, muErr,year, isKFL, isInc, cType);
  ifile = (inc) ? ifile+1 : ifile ;
  CalcSystTable(ifile, 0, eleOut, eleErr,year, isKFL, isInc, cType);
  
  string combined = "";
  cout<<"Diff sample " << sampleType[ifile-1] <<", RowTitle : " << rowtitle << endl;
  string sampleName = sampleType[ifile-1];
  if(sampleName.find("QCDdd")==string::npos){
    combined = rowtitle + " & " + Form("$%3.2f(%3.2f)$",muErr[0],eleErr[0]) 
      + " & " + Form("$%3.2f(%3.2f)$",muErr[1],eleErr[1]) 
      + " & " + Form("$%3.2f(%3.2f)$",muErr[2],eleErr[2]) 
      + " & " + Form("$%3.2f(%3.2f)$",muErr[3],eleErr[3]) 
      + " & " + Form("$%3.2f(%3.2f)$",muErr[4],eleErr[4]) 
      + " & " + Form("$%3.2f(%3.2f)$",muErr[5],eleErr[5]) 
      + " & " + Form("$%3.2f(%3.2f)$",muErr[6],eleErr[6]) 
      + " & " + Form("$%3.2f(%3.2f)$",muErr[7],eleErr[7]) 
      + " & " + Form("$%3.2f(%3.2f)$",muErr[8],eleErr[8]) 
      + " & " + Form("$%3.2f(%3.2f)$",muErr[9],eleErr[9]) 
      // + " & " + Form("$%3.2f(%3.2f)$",muErr[10],eleErr[10]) 
      +"\\\\";
  }else{
    combined = rowtitle 
      + " & " + "--"
      + " & " + "--"
      + " & " + "--"
      + " & " + "--"
      + " & " + "--"
      + " & " + "--"
      + " & " + "--"
      + " & " + "--"
      + " & " + Form("$%3.2f(%3.2f)$",100.*muOut[2]/muOut[0],100.*eleOut[2]/eleOut[0]) 
      + " & " + Form("$%3.2f(%3.2f)$",100.*muOut[1]/muOut[0],100.*eleOut[1]/eleOut[0]) 
      // + " & " + Form("$%3.2f(%3.2f)$",muErr[10],eleErr[10]) 
      +"\\\\";
  }

  //cout << combined << endl;

  return combined;
}

string GetInclusive(string rowtitle, int ifile, bool inc, int year, bool isKFL, bool isInc, char cType, double *muTot, double *eleTot)
{
  int CalcSystTable(int ifile, bool isMu, double output[], double error_percnt[], int year, bool isKFL, bool isIncl, char cType);
  
  const int  nofSyst = 8;
  double muOut[3];
  double eleOut[3];
  double error_percnt[11]; //nofSyst + stat

  cout<<"Inclusive sample " << sampleType[ifile-1] <<", RowTitle : " << rowtitle << endl;
  string sampleName = sampleType[ifile-1];

  for(int i=0;i<11;i++) error_percnt[i] = 0.0 ;
  for(int i=0;i<3;i++) muOut[i] = eleOut[i] = 0.0 ;
  CalcSystTable(ifile, 1, muOut, error_percnt,year, isKFL, isInc, cType);
  ifile = (inc) ? ifile+1 : ifile ;
  for(int i=0;i<11;i++) error_percnt[i] = 0.0 ;
  CalcSystTable(ifile, 0, eleOut, error_percnt,year, isKFL, isInc, cType);
  
  
  string combined = "";
  
  if(rowtitle.find("All")==string::npos){
    if(rowtitle == "Data" or rowtitle == "MC QCD"){
      combined = rowtitle +" & "+ Form("$%1.0f \\pm %1.0f(%1.1f\\%)$",muOut[0],muOut[1],100.*muOut[1]/muOut[0]) 
	+" & "+ Form("$%1.0f \\pm %1.0f(%1.1f\\%)$",eleOut[0],eleOut[1],100.*eleOut[1]/eleOut[0]) +"\\\\";
    }else if(rowtitle == "Data/Bkg"){
      combined = rowtitle +" & "+ Form("$%5.4f$",muOut[0]/muTot[0]) 
	+" & "+ Form("$%5.4f$",eleOut[0]/eleTot[0]) +"\\\\";      
    }else{
      combined = rowtitle +" & "+ Form("$%1.0f \\pm %1.0f(%1.1f\\%) \\pm %1.0f(%1.1f\\%)$",muOut[0],muOut[1],100.*muOut[1]/muOut[0],muOut[2],100.*muOut[2]/muOut[0]) 
	+" & "+ Form("$%1.0f \\pm %1.0f(%1.1f\\%) \\pm %1.0f(%1.1f\\%)$",eleOut[0],eleOut[1],100.*eleOut[1]/eleOut[0],eleOut[2],100.0*eleOut[2]/eleOut[0]) +"\\\\";
    }
  }else{
    combined = rowtitle +" & "+ Form("$%1.0f \\pm %1.0f(%1.1f\\%) \\pm %1.0f(%1.1f\\%)$",muTot[0],sqrt(muTot[1]),100.*sqrt(muTot[1])/muTot[0],sqrt(muTot[2]),100.*sqrt(muTot[2])/muTot[0]) 
      +" & "+ Form("$%1.0f \\pm %1.0f(%1.1f\\%) \\pm %1.0f(%1.1f\\%)$",eleTot[0],sqrt(eleTot[1]),100.*sqrt(eleTot[1])/eleTot[0],sqrt(eleTot[2]),100.0*sqrt(eleTot[2])/eleTot[0]) +"\\\\";    
  }
  
  if(sampleName.find("TTbar")!=string::npos){
    muTot[0] = muOut[0];
    muTot[1] = muOut[1]*muOut[1];
    muTot[2] = muOut[2]*muOut[2];
    
    eleTot[0] = eleOut[0];
    eleTot[1] = eleOut[1]*eleOut[1];
    eleTot[2] = eleOut[2]*eleOut[2];
  }else if(rowtitle != "Data" and rowtitle.find("All")==string::npos and sampleName.find("MCQCD")==string::npos){
    muTot[0] += muOut[0];
    muTot[1] += muOut[1]*muOut[1];
    muTot[2] += muOut[2]*muOut[2];

    eleTot[0] += eleOut[0];
    eleTot[1] += eleOut[1]*eleOut[1];
    eleTot[2] += eleOut[2]*eleOut[2];
  }
  //cout << combined << endl;

  return combined;
}

int CalcSystTable(int isample, bool isMu, double output[], double error_percnt[], int year, bool isKFL = false, bool isIncl = true, char cType = 'L')
{
  
  int PlotRatio(TH1D *h1, TH1D *h2, const char *cname);
  double CalcSysError(TH1D *, TH1D *, TH1D *);
  
  bool isVerbose = 1;
  
  const char *sample[] = {
                          // "HminusM080", "HminusM090", "HminusM100", "HminusM110", 
			  // "HminusM120", "HminusM130", "HminusM140", "HminusM150", 
			  // "HminusM155", "HminusM160",  
			  // "HplusM080", "HplusM090", "HplusM100", "HplusM110", 
			  // "HplusM120", "HplusM130", "HplusM140", "HplusM150", 
			  // "HplusM155", "HplusM160",  
                          "HplmiM080", "HplmiM090", "HplmiM100", "HplmiM110", 
			  "HplmiM120", "HplmiM130", "HplmiM140", "HplmiM150", 
			   "HplmiM155", "HplmiM160",  
			  "TTbar", "singleTop", "Wjets", "DYjets", "VBFusion", 
			  "MCQCDMu", "MCQCDEle","QCDdd", "QCDdd", 
			  "DataMu", "DataEle"};
  
  const float norm_mu_syst[] = {6.1, 6.1, 6.1, 6.1,
				6.1, 6.1, 6.1, 6.1,
				6.1, 6.1,
				6.1, 6.1, 6.1, 6.1,
				6.1, 6.1, 6.1, 6.1,
				6.1, 6.1,
                                6.1, 5.0, 5.0, 4.5, 4.0, 
                                10.};

  const float norm_ele_syst[] = {6.1, 6.1, 6.1, 6.1,
				 6.1, 6.1, 6.1, 6.1,
				 6.1, 6.1,
				 6.1, 6.1, 6.1, 6.1,
				 6.1, 6.1, 6.1, 6.1,
				 6.1, 6.1,
				 6.1, 5.0, 5.0, 4.5, 4.0,
				 10.};
  
  const char *systDir[] = {"base", 
  			     "puup", "pudown", "mueffup", "mueffdown", 
  			     "eleeffup", "eleeffdown",  "jecup", "jecdown", 
  			     "jerup", "jerdown", "btagbup", "btagbdown", 
  			     "btaglup", "btagldown", "prefireup", "prefiredown",
                             "pdfup", "pdfdown", "q2fup", "q2down",
  			     "isrup", "isrdown", "fsrup", "fsrdown",
                             "bctag1up", "bctag1down", "bctag2up", "bctag2down",
  			     "bctag3up", "bctag3down"};
  // const char *systDir[] = {"base", 
  // 			     "puup", "pudown", "mueffup", "mueffdown", 
  // 			     "eleeffup", "eleeffdown",  "jecup", "jecdown", 
  // 			     "jerup", "jerdown", "bcintpup", "bcintpdown", 
  // 			     "bcextpup", "bcextpdown", "prefireup", "prefiredown",
  //                            "pdfup", "pdfdown", "q2fup", "q2down",
  // 			     "isrup", "isrdown", "fsrup", "fsrdown",
  //                            "bcstatup", "bcstatdown", "bclhemufup", "bclhemufdown",
  // 			     "bclhemurup", "bclhemurdown"};


  const char *systname[] = {"nominal", 
				 "pileup up", "pileup down", "muon efficiency up", "muon efficiency down", 
				 "electron efficiency up", "electron efficiency down",  "jet energy correction up", "jet energy correction down", 
				 "jet energy resolution up", "jet energy resolution down", "btag b-quark up", "btag b-quark down", 
				 "btag l-quark up", "btag l-quark down", "prefire up", "prefire down",
				 "PDF up", "PDF down", "renormalization up", "renormalization down",
				 "ISR up", "ISR down", "FSR up", "FSR down",
                                 "bctag1up", "bctag1down", "bctag2up", "bctag2down",
			         "bctag3up", "bctag3down"};

  
  //const char *inputdir = "/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/grid_v39_Syst/CBA_KFNewReso" ;
  //const char *inputdir = "/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/grid_v39_Syst/CBA_1718_Resubmit" ;
  //const char *inputdir = "/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/grid_v39_Syst/CBA_CTagM" ;
  //const char *inputdir = "/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/grid_v39_Syst/CBA_GeneratorWt" ;
  //const char *inputdir = "/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/grid_v39_Syst/CBA_CTagDD" ;
  //const char *inputdir = "/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/grid_v40_Syst/CBA_ctagv2-CombHist" ;
  const char *inputdir = "/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/grid_v40_Syst/CBA_bctag123" ;

  //int isample = 17; 
  isample--;
  //bool isMu = 1 ;
  int ibase = 1; ibase--; 
  
  string histname = "";
  if(isKFL)
    histname = (isMu) ? Form("%s/%s/Iso/_kb_mjj_mu",sample[isample],systDir[ibase]) : Form("%s/%s/Iso/_kb_mjj_ele",sample[isample],systDir[ibase])  ;
  else{
    if(isIncl){
      if(cType=='L')
	histname = (isMu) ? Form("%s/%s/Iso/_ct_IncL_mjj_mu",sample[isample],systDir[ibase]) : Form("%s/%s/Iso/_ct_IncL_mjj_ele",sample[isample],systDir[ibase])  ;
      else if(cType=='M')
	histname = (isMu) ? Form("%s/%s/Iso/_ct_IncM_mjj_mu",sample[isample],systDir[ibase]) : Form("%s/%s/Iso/_ct_IncM_mjj_ele",sample[isample],systDir[ibase])  ;
      else if(cType=='T')
	histname = (isMu) ? Form("%s/%s/Iso/_ct_IncT_mjj_mu",sample[isample],systDir[ibase]) : Form("%s/%s/Iso/_ct_IncT_mjj_ele",sample[isample],systDir[ibase])  ;
    }else{
      if(cType=='L')
	histname = (isMu) ? Form("%s/%s/Iso/_ct_ExcL_mjj_mu",sample[isample],systDir[ibase]) : Form("%s/%s/Iso/_ct_ExcL_mjj_ele",sample[isample],systDir[ibase])  ;
      else if(cType=='M')
	histname = (isMu) ? Form("%s/%s/Iso/_ct_ExcM_mjj_mu",sample[isample],systDir[ibase]) : Form("%s/%s/Iso/_ct_ExcM_mjj_ele",sample[isample],systDir[ibase])  ;
      else if(cType=='T')
	histname = (isMu) ? Form("%s/%s/Iso/_ct_ExcT_mjj_mu",sample[isample],systDir[ibase]) : Form("%s/%s/Iso/_ct_ExcT_mjj_ele",sample[isample],systDir[ibase])  ;
    }//incl or excl
  }//ctag level

  string histiso20 = "";
  if(isKFL)
    histiso20 = (isMu) ? Form("%s/iso20/Iso/_kb_mjj_mu",sample[isample]) : Form("%s/iso20/Iso/_kb_mjj_ele",sample[isample])  ;
  else{
    if(isIncl){
      if(cType=='L')
	histiso20 = (isMu) ? Form("%s/iso20/Iso/_ct_IncL_mjj_mu",sample[isample]) : Form("%s/iso20/Iso/_ct_IncL_mjj_ele",sample[isample])  ;
      else if(cType=='M')
	histiso20 = (isMu) ? Form("%s/iso20/Iso/_ct_IncM_mjj_mu",sample[isample]) : Form("%s/iso20/Iso/_ct_IncM_mjj_ele",sample[isample])  ;
      else if(cType=='T')
	histiso20 = (isMu) ? Form("%s/iso20/Iso/_ct_IncT_mjj_mu",sample[isample]) : Form("%s/iso20/Iso/_ct_IncT_mjj_ele",sample[isample])  ;
    }else{
      if(cType=='L')
	histiso20 = (isMu) ? Form("%s/iso20/Iso/_ct_ExcL_mjj_mu",sample[isample]) : Form("%s/iso20/Iso/_ct_ExcL_mjj_ele",sample[isample])  ;
      else if(cType=='M')
	histiso20 = (isMu) ? Form("%s/iso20/Iso/_ct_ExcM_mjj_mu",sample[isample]) : Form("%s/iso20/Iso/_ct_ExcM_mjj_ele",sample[isample])  ;
      else if(cType=='T')
	histiso20 = (isMu) ? Form("%s/iso20/Iso/_ct_ExcT_mjj_mu",sample[isample]) : Form("%s/iso20/Iso/_ct_ExcT_mjj_ele",sample[isample])  ;
    }//incl or excl
  }//ctag level
  

  TFile *finBase = TFile::Open(Form("%s/%d/all_%s.root",inputdir,year,sample[isample])); 
  
  if(isVerbose)
    cout<<"Openning file : "<< finBase->GetName() << endl;
  TH1D *hBase = (TH1D *)finBase->Get(histname.c_str());
  if(isVerbose)
    cout<<"and get histo : " << histname.c_str() << endl;
  string baseFileName = finBase->GetName();
  
  TH1D *hIso20 = (TH1D *)finBase->Get(histiso20.c_str());

  const int  nofSyst = 9;
  const int  sysidlistMu[nofSyst] = {2, 4, 26, 28, 30, 16, 8, 10, 10};
  const int  sysidlistEle[nofSyst] = {2, 6, 26, 28, 30, 16, 8, 10, 10};
  double error[nofSyst];
  double error_percent[nofSyst];
  
  const int nSystGroups = 9 ; //pileup, lepton, btag-b, btag-l, prefire, jec, jer, normalization
  //const char*  syst_group_name[] = {"Pileup", "Lepton", "btag-b", "btag-l", "Prefire", "JEC", "JER", "Norm"};
  const char*  syst_group_name[] = {"Pileup", "Lepton", "b & c tagging-1", "b & c tagging-2", "b & c tagging-3", "Prefire", "JEC", "JER", "Norm"};
  
  double syst_Error[nSystGroups];

  double syst_Error_Percent[nSystGroups];

  int isyst = 0;
  double totSys = 0.0;
  
  double stat_Error = 0.0;
  double Norm = hBase->IntegralAndError(1,hBase->GetNbinsX(),stat_Error); 
  double stat_Error_iso20 = 0.0;
  double Norm_iso20 = 0.0;
  if(baseFileName.find("all_QCDdd")!=string::npos or baseFileName.find("all_Data")!=string::npos)
    Norm_iso20 = hIso20->IntegralAndError(1,hIso20->GetNbinsX(),stat_Error_iso20); 

  //The following line is for DD row.
  //if(isample>=13){
  if(baseFileName.find("all_QCDdd")!=string::npos or baseFileName.find("all_Data")!=string::npos or baseFileName.find("all_MCQCD")!=string::npos){
  //if(isample>=13){
    output[0] = Norm;
    output[1] = stat_Error ;
    if(baseFileName.find("all_QCDdd")!=string::npos)
      output[2] = TMath::Abs(Norm-Norm_iso20) ;
    else
      output[2] = 0 ;
    return true;
  }
  
  if(isVerbose)
    cout << "isample : " << isample << ", Processing for : "<<sample[isample] << ", nof Syst : " << nofSyst << endl;
  
  for(int idx = 0 ; idx < nofSyst ; idx++){
    
    int isysup = (isMu) ? sysidlistMu[idx] : sysidlistEle[idx] ; 
    int isysdown = isysup ;
    isysup--; 
    
    string systName = systname[isysup];

    string histnameup;
    if(isKFL)
      histnameup = (isMu) ? Form("%s/%s/Iso/_kb_mjj_mu",sample[isample],systDir[isysup]) : Form("%s/%s/Iso/_kb_mjj_ele",sample[isample],systDir[isysup])  ;
    else{
      if(isIncl){
	if(cType=='L')
	  histnameup = (isMu) ? Form("%s/%s/Iso/_ct_IncL_mjj_mu",sample[isample],systDir[isysup]) : Form("%s/%s/Iso/_ct_IncL_mjj_ele",sample[isample],systDir[isysup])  ;
	else if(cType=='M')
	  histnameup = (isMu) ? Form("%s/%s/Iso/_ct_IncM_mjj_mu",sample[isample],systDir[isysup]) : Form("%s/%s/Iso/_ct_IncM_mjj_ele",sample[isample],systDir[isysup])  ;
	else if(cType=='T')
	  histnameup = (isMu) ? Form("%s/%s/Iso/_ct_IncT_mjj_mu",sample[isample],systDir[isysup]) : Form("%s/%s/Iso/_ct_IncT_mjj_ele",sample[isample],systDir[isysup])  ;
      }else{
	if(cType=='L')
	  histnameup = (isMu) ? Form("%s/%s/Iso/_ct_ExcL_mjj_mu",sample[isample],systDir[isysup]) : Form("%s/%s/Iso/_ct_ExcL_mjj_ele",sample[isample],systDir[isysup])  ;
	else if(cType=='M')
	  histnameup = (isMu) ? Form("%s/%s/Iso/_ct_ExcM_mjj_mu",sample[isample],systDir[isysup]) : Form("%s/%s/Iso/_ct_ExcM_mjj_ele",sample[isample],systDir[isysup])  ;
	else if(cType=='T')
	  histnameup = (isMu) ? Form("%s/%s/Iso/_ct_ExcT_mjj_mu",sample[isample],systDir[isysup]) : Form("%s/%s/Iso/_ct_ExcT_mjj_ele",sample[isample],systDir[isysup])  ;
      }//incl or excl
    }//ctag level

    string histnamedown;
    if(isKFL)
      histnamedown = (isMu) ? Form("%s/%s/Iso/_kb_mjj_mu",sample[isample],systDir[isysdown]) : Form("%s/%s/Iso/_kb_mjj_ele",sample[isample],systDir[isysdown])  ;
    else{
      if(isIncl){
	if(cType=='L')
	  histnamedown = (isMu) ? Form("%s/%s/Iso/_ct_IncL_mjj_mu",sample[isample],systDir[isysdown]) : Form("%s/%s/Iso/_ct_IncL_mjj_ele",sample[isample],systDir[isysdown])  ;
	else if(cType=='M')
	  histnamedown = (isMu) ? Form("%s/%s/Iso/_ct_IncM_mjj_mu",sample[isample],systDir[isysdown]) : Form("%s/%s/Iso/_ct_IncM_mjj_ele",sample[isample],systDir[isysdown])  ;
	else if(cType=='T')
	  histnamedown = (isMu) ? Form("%s/%s/Iso/_ct_IncT_mjj_mu",sample[isample],systDir[isysdown]) : Form("%s/%s/Iso/_ct_IncT_mjj_ele",sample[isample],systDir[isysdown])  ;
      }else{
	if(cType=='L')
	  histnamedown = (isMu) ? Form("%s/%s/Iso/_ct_ExcL_mjj_mu",sample[isample],systDir[isysdown]) : Form("%s/%s/Iso/_ct_ExcL_mjj_ele",sample[isample],systDir[isysdown])  ;
	else if(cType=='M')
	  histnamedown = (isMu) ? Form("%s/%s/Iso/_ct_ExcM_mjj_mu",sample[isample],systDir[isysdown]) : Form("%s/%s/Iso/_ct_ExcM_mjj_ele",sample[isample],systDir[isysdown])  ;
	else if(cType=='T')
	  histnamedown = (isMu) ? Form("%s/%s/Iso/_ct_ExcT_mjj_mu",sample[isample],systDir[isysdown]) : Form("%s/%s/Iso/_ct_ExcT_mjj_ele",sample[isample],systDir[isysdown])  ;
      }//incl or excl
    }//ctag level
    
    
    TH1D *hSysUp = (TH1D *)finBase->Get(histnameup.c_str());
    TH1D *hSysDown = (TH1D *)finBase->Get(histnamedown.c_str());
    cout <<"Hello there 1 " << histnameup << ", " << histnamedown << endl;
    error[idx] = CalcSysError(hSysUp, hBase, hSysDown);
    if(idx<(nofSyst-1)){
      error_percent[idx] = 100.*error[idx]/Norm ;
    }else{ // This is only for normalization which is predefined
      error_percent[idx] =  (isMu) ?  norm_mu_syst[isample] : norm_ele_syst[isample] ;
      error[idx] = Norm*error_percent[idx]/100. ;
    }
    
    //////////////////////////////////////////////////////
    //// The following lines for testing only//////////////
    if(idx<6){
      syst_Error[isyst] = error[idx];
      syst_Error_Percent[isyst] = 100.*syst_Error[isyst]/Norm ;
      isyst++;
    }
    //// The above lines for testing only//////////////////
    //////////////////////////////////////////////////////
    
    ///////////////////////////////////////////////////////////////////////////////
    //The following line for total/inclusive sys error adding for all controbutions
    totSys += error[idx]*error[idx];
    // cout << "\t isample : "<<isample << "idx : " << idx << ", ibase : "<<ibase << ", isysup : "<< isysup << ", isysdown : " << isysdown << endl;
    if(isVerbose)
      printf("\t SystType : %10s, Norm : %f, stat : %5.4f(%3.2f\%), sys : %5.4f(%3.2f\%)\n",systname[isysup], Norm, stat_Error, 100.*stat_Error/Norm, error[idx], error_percent[idx]);
    ///////////////////////////////////////////////////////////////////////////////
    
    //////////////////////////////////////////////
    //This is main output for differential results
    error_percnt[idx] = error_percent[idx]; 
    //////////////////////////////////////////////
  }
  error_percnt[nofSyst] = 100.*stat_Error/Norm;
  
  //////////////////////////////////////////////////////
  //// The following lines for testing only//////////////
  syst_Error[isyst] = 0;
  for(int idx = 6 ; idx < nofSyst ; idx++){
    syst_Error[isyst] += error[idx]*error[idx] ;
  }
  syst_Error[isyst] = TMath::Sqrt(syst_Error[isyst]);
  syst_Error_Percent[isyst] = 100.*syst_Error[isyst]/Norm ;
  isyst++;
  //// The above lines for testing only//////////////////
  //////////////////////////////////////////////////////
  
  //////////////////////////////////////////////////////////////////////////////////
  //The following line for total/inclusive sys error adding for all controbutions
  totSys = TMath::Sqrt(totSys);
  //////////////////////////////////////////////////////////////////////////////////
  double totSys_percent = 100.*totSys/Norm;
  const char *totsys = "Total Systematics";
  if(isVerbose)
    printf("SystType : %30s, Norm : %f, stat : %5.4f(%3.2f\%), sys : %5.4f(%3.2f\%)\n",totsys, Norm, stat_Error, 100.*stat_Error/Norm, totSys, totSys_percent);
  
  //////////////////////////////////////////////////////////////////////////////////
  //The following 3 lines for total/inclusive sys error adding for all controbutions
  output[0] = Norm;
  output[1] = stat_Error ;
  output[2] = totSys ;
  //////////////////////////////////////////////////////////////////////////////////

  finBase->Close();

  delete finBase;
  

  
  return true;
}

double CalcSysError(TH1D *hSysUp, TH1D *hBase, TH1D *hSysDown)
{
  // cout<<"upP : " << hSysUp <<", base : " << hBase << ", downP : " << hSysDown << endl;
  // cout<<"upName : " << hSysUp->GetName() <<", base : " << hBase->GetName() << ", downName : " << hSysDown->GetName() << endl;
  
  double valUp    = hSysUp->Integral();
  double valBase  = hBase->Integral();
  double valDown  = hSysDown->Integral();
  
  // cout<<"upVal : " << valUp <<", base : " << valBase << ", downVal : " << valDown << endl;
  
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


// // qcd SF for data-driven QCD
// double MyHPlusDataCardMakerNano::getQcdSF(bool isMu, TString baseDir, TFile* fData, TFile* fTT, TFile* fST, TFile* fWJ, TFile* fDY, TFile* fVV, TString histDir, TString histName){
//   //RegionC = LowMET, NonIso
//   TH1F* hVV_RegC = getHisto(fVV,   "VBFusion/"+baseDir+"/NonIsoLowMET/" , histName+"_noniso_lmet");
//   TH1F* hDY_RegC = getHisto(fDY,   "DYjets/"+baseDir+"/NonIsoLowMET/" , histName+"_noniso_lmet");
//   TH1F* hWJ_RegC = getHisto(fWJ,   "Wjets/"+baseDir+"/NonIsoLowMET/" , histName+"_noniso_lmet");
//   TH1F* hST_RegC = getHisto(fST,   "singleTop/"+baseDir+"/NonIsoLowMET/" , histName+"_noniso_lmet");
//   TH1F* hTT_RegC = getHisto(fTT,   "TTbar/"+baseDir+"/NonIsoLowMET/" , histName+"_noniso_lmet");
//   TH1F* hMC_RegC = (TH1F*)hVV_RegC->Clone("hAllMC_RegC");
//   hMC_RegC->Add(hDY_RegC);
//   hMC_RegC->Add(hWJ_RegC);
//   hMC_RegC->Add(hST_RegC);
//   hMC_RegC->Add(hTT_RegC);
//   TH1F* hData_RegC = (isMu) ? getHisto(fData, "DataMu/"+baseDir+"/NonIsoLowMET/", histName+"_noniso_lmet") : getHisto(fData, "DataEle/"+baseDir+"/NonIsoLowMET/", histName+"_noniso_lmet");
  
//   //RegionD = LowMET, Iso
//   TH1F* hVV_RegD = getHisto(fVV,   "VBFusion/"+baseDir+"/LowMET/" , histName+"_lmet");
//   TH1F* hDY_RegD = getHisto(fDY,   "DYjets/"+baseDir+"/LowMET/" , histName+"_lmet");
//   TH1F* hWJ_RegD = getHisto(fWJ,   "Wjets/"+baseDir+"/LowMET/" , histName+"_lmet");
//   TH1F* hST_RegD = getHisto(fST,   "singleTop/"+baseDir+"/LowMET/" , histName+"_lmet");
//   TH1F* hTT_RegD = getHisto(fTT,   "TTbar/"+baseDir+"/LowMET/" , histName+"_lmet");
//   TH1F* hMC_RegD = (TH1F*)hVV_RegD->Clone("hAllMC_RegD");
//   hMC_RegD->Add(hDY_RegD);
//   hMC_RegD->Add(hWJ_RegD);
//   hMC_RegD->Add(hST_RegD);
//   hMC_RegD->Add(hTT_RegD);
//   TH1F* hData_RegD=  (isMu) ? getHisto(fData, "DataMu/"+baseDir+"/LowMET/", histName+"_lmet") : getHisto(fData, "DataEle/"+baseDir+"/LowMET/", histName+"_lmet");

//   TH1F* hDiffC = (TH1F*)hData_RegC->Clone("hDiffC");
//   hDiffC->Add(hMC_RegC, -1);
//   //If binContent < 0, set it to 0
//   for(int ibin=1; ibin<hDiffC->GetNbinsX(); ibin++){
//     double binCont = hDiffC->GetBinContent(ibin);
//     if(binCont<0){
//       hDiffC->SetBinContent(ibin, 0);
//       //hDiffC->SetBinError(ibin, 0);
//     }
//   }
//   TH1F* hDiffD = (TH1F*)hData_RegD->Clone("hDiffD");
//   hDiffD->Add(hMC_RegD, -1);
//   for(int ibin=1; ibin<hDiffD->GetNbinsX(); ibin++){
//     double binCont = hDiffD->GetBinContent(ibin);
//     if(binCont<0){
//       hDiffD->SetBinContent(ibin, 0);
//       //hDiffD->SetBinError(ibin, 0);
//     }
//   }
//   double intDiffC   = hDiffC->Integral();
//   double intDiffD   = hDiffD->Integral();
//   double ratioDiffDC = intDiffD/intDiffC;
//   return ratioDiffDC;
// }

// double MyHPlusDataCardMakerNano::getQcdDD(bool isMu, TString baseDir, TFile* fData, TFile* fTT, TFile* fST, TFile* fWJ, TFile* fDY, TFile* fVV, TString histDir, TString histName, double qcd_sf=1.0){
//   /* TH1F* hVV = getHisto(fVV,   baseDir+"/NonIso/"+histDir, histName, fTT); */
//   /* TH1F* hDY = getHisto(fDY,   baseDir+"/NonIso/"+histDir, histName, fTT); */
//   /* TH1F* hWJ = getHisto(fWJ,   baseDir+"/NonIso/"+histDir, histName, fTT); */
//   /* TH1F* hST = getHisto(fST,   baseDir+"/NonIso/"+histDir, histName, fTT); */
//   /* TH1F* hTT = getHisto(fTT,   baseDir+"/NonIso/"+histDir, histName, fTT); */
//   /* TH1F* hData= getHisto(fData, baseDir+"/NonIso/"+histDir, histName, fTT); */
  
//   TH1F* hVV = getHisto(fVV,   "VBFusion/"+baseDir+"/NonIso/" , histName+"_noniso");
//   TH1F* hDY = getHisto(fDY,   "DYjets/"+baseDir+"/NonIso/", histName+"_noniso");
//   TH1F* hWJ = getHisto(fWJ,   "Wjets/"+baseDir+"/NonIso/", histName+"_noniso");
//   TH1F* hST = getHisto(fST,   "singleTop/"+baseDir+"/NonIso/", histName+"_noniso");
//   TH1F* hTT = getHisto(fTT,   "TTbar/"+baseDir+"/NonIso/", histName+"_noniso");
//   TH1F* hData= (isMu) ? getHisto(fData,"DataMu/"+baseDir+"/NonIso/", histName+"_noniso") : getHisto(fData,"DataEle/"+baseDir+"/NonIso/", histName+"_noniso");
  
//   TH1F* hOtherMC = (TH1F*)hVV->Clone("hOtherMC");
//   hOtherMC->Add(hDY);
//   hOtherMC->Add(hST);
//   hOtherMC->Add(hWJ);
//   hOtherMC->Add(hTT);
//   TH1F* hQCD = (TH1F*)hData->Clone(histName+"_noniso");
//   hQCD->Add(hOtherMC, -1);
//   //If binContent < 0, set it to 0
//   for(int ibin=1; ibin<hQCD->GetNbinsX(); ibin++){
//     double binCont = hQCD->GetBinContent(ibin);
//     if(binCont<0){
//       hQCD->SetBinContent(ibin, 0);
//       //hQCD->SetBinError(ibin, 0);
//     }
//   }
//   hQCD->Scale(qcd_sf);
//   return hQCD->Integral();
// }

// double MyHPlusDataCardMakerNano::getSysUncQcd(bool isMu, TFile* fData, TFile* fTT, TFile* fST, TFile* fWJ, TFile* fDY, TFile* fVV, TString histDir, TString histName, bool isUncSF){

//   double sf_baseIsoDir = getQcdSF(isMu, "base", fData, fTT, fST, fWJ, fDY, fVV, histDir, histName);
//   double qcd_baseIsoDir = getQcdDD(isMu, "base", fData, fTT, fST, fWJ, fDY, fVV, histDir, histName, sf_baseIsoDir);
//   double sf_baseShiftedIsoDir = getQcdSF(isMu, "iso20", fData, fTT, fST, fWJ, fDY, fVV, histDir, histName);
//   double qcd_baseShiftedIsoDir = getQcdDD(isMu, "iso20", fData, fTT, fST, fWJ, fDY, fVV, histDir, histName, sf_baseShiftedIsoDir);

//   double sf_unc = abs(sf_baseIsoDir - sf_baseShiftedIsoDir)/sf_baseIsoDir;
//   double qcd_unc = sysSF* abs(qcd_baseIsoDir - qcd_baseShiftedIsoDir)/qcd_baseIsoDir;
//   cout<<"-------------------------------------"<<endl;
//   cout<<"sf_baseIsoDir 	      = "<<sf_baseIsoDir<<endl;
//   cout<<"sf_baseShiftedIsoDir = "<<sf_baseShiftedIsoDir<<endl;
//   cout<<"sf_unc               = "<<sf_unc<<endl;
//   cout<<"qcd_baseIsoDir 	   = "<<qcd_baseIsoDir<<endl;
//   cout<<"qcd_baseShiftedIsoDir = "<<qcd_baseShiftedIsoDir<<endl;
//   cout<<"qcd_unc               = "<<qcd_unc<<endl;
//   cout<<"-------------------------------------"<<endl;
//   double unc = 0.0;
//   if(isUncSF) unc = sf_unc;
//   else unc = qcd_unc;
//   return 1+unc;
// }
