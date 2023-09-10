/**********************************************************************
 Created on : 22/02/2023
 Purpose    : Prepare Mjj syst table for paper draft
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
#include <string>

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

int PrepMjjSystTableV8UL(int year = 2016)
{
  string GetInclusive(string, int, bool, int, bool, bool, char, double *, double *);
  string GetDifferential(string rowtitle, int ifile, bool inc, int year, bool isKFL, bool isInc, char cType, bool ismu);
  
  bool forPaper = true;
  double muTot[3],eleTot[3];
  double muTotL[3],eleTotL[3],muTotM[3],eleTotM[3],muTotT[3],eleTotT[3];

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
  string tab1_caption = "Event yield for inclusive category in " + to_string(year) + ".";
  string tab2_caption = "Systematic and statistical uncertainties in \\% for muon(above) and electron(below) channel for inclusive category in " + to_string(year) + ".";
  string tab3_caption = "Systematic and statistical uncertainties in \\% for muon(above) and electron(below) channel for inclusive category in " + to_string(year) + ".";
  string nEvents = "";
  if(forPaper) nEvents = "$N_{events}  \\pm unc$";
  else nEvents = "$N_{events} \\pm stat \\pm sys$";
  
  //Inclusive Mjj
  outFile<<"\\begin{table}"<<endl;
  outFile<<"\\caption{"<<tab1_caption<<"}"<<endl;
  outFile<<"\\label{tab:sec07_eventYield_Inc_"<<year<<"}"<<endl;
  outFile<<"\\centering\\begin{adjustbox}{width=0.7\\textwidth}"<<endl;
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
  outFile<<GetInclusive("$H^{+} + H^{-} (m=80$ GeV)", ifile++, false, year, isKFL, isInc, cType, muTot, eleTot)<<endl; outFile<<"\\\\"<<endl;
  outFile<<GetInclusive("$H^{+} + H^{-} (m=90$ GeV)", ifile++, false, year, isKFL, isInc, cType, muTot, eleTot)<<endl; outFile<<"\\\\"<<endl;
  outFile<<GetInclusive("$H^{+} + H^{-} (m=100$ GeV)", ifile++, false, year, isKFL, isInc, cType, muTot, eleTot)<<endl; outFile<<"\\\\"<<endl;
  outFile<<GetInclusive("$H^{+} + H^{-} (m=110$ GeV)", ifile++, false, year, isKFL, isInc, cType, muTot, eleTot)<<endl; outFile<<"\\\\"<<endl;
  outFile<<GetInclusive("$H^{+} + H^{-} (m=120$ GeV)", ifile++, false, year, isKFL, isInc, cType, muTot, eleTot)<<endl; outFile<<"\\\\"<<endl;
  outFile<<GetInclusive("$H^{+} + H^{-} (m=130$ GeV)", ifile++, false, year, isKFL, isInc, cType, muTot, eleTot)<<endl; outFile<<"\\\\"<<endl;
  outFile<<GetInclusive("$H^{+} + H^{-} (m=140$ GeV)", ifile++, false, year, isKFL, isInc, cType, muTot, eleTot)<<endl; outFile<<"\\\\"<<endl;
  outFile<<GetInclusive("$H^{+} + H^{-} (m=150$ GeV)", ifile++, false, year, isKFL, isInc, cType, muTot, eleTot)<<endl; outFile<<"\\\\"<<endl;
  outFile<<GetInclusive("$H^{+} + H^{-} (m=155$ GeV)", ifile++, false, year, isKFL, isInc, cType, muTot, eleTot)<<endl; outFile<<"\\\\"<<endl;
  outFile<<GetInclusive("$H^{+} + H^{-} (m=160$ GeV)", ifile++, false, year, isKFL, isInc, cType, muTot, eleTot)<<endl; outFile<<"\\\\"<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<GetInclusive("SM $t\\bar{t}$ + jets", ifile++, false, year, isKFL, isInc, cType, muTot, eleTot)<<endl; outFile<<"\\\\"<<endl;
  outFile<<GetInclusive("Single ~t", ifile++, false, year, isKFL, isInc, cType, muTot, eleTot)<<endl; outFile<<"\\\\"<<endl;
  outFile<<GetInclusive("W + jets", ifile++, false, year, isKFL, isInc, cType, muTot, eleTot)<<endl; outFile<<"\\\\"<<endl;
  outFile<<GetInclusive("$Z/\\gamma$ + jets", ifile++, false, year, isKFL, isInc, cType, muTot, eleTot)<<endl; outFile<<"\\\\"<<endl;
  outFile<<GetInclusive("VV", ifile++, false, year, isKFL, isInc, cType, muTot, eleTot)<<endl; outFile<<"\\\\"<<endl; ifile = ifile+2;
  //outFile<<GetInclusive("MC QCD", ifile++, true, year, isKFL, isInc, cType, muTot, eleTot)<<endl; outFile<<"\\\\"<<endl; ifile++ ;
  outFile<<GetInclusive("DD QCD", ifile++, true, year, isKFL, isInc, cType, muTot, eleTot)<<endl; outFile<<"\\\\"<<endl; ifile++ ;
  outFile<<"\\hline "<<endl;
  outFile<<GetInclusive("All background", ifile, true, year, isKFL, isInc, cType, muTot, eleTot)<<endl; outFile<<"\\\\"<<endl; ifileData = ifile;
  outFile<<"\\hline "<<endl;
  outFile<<GetInclusive("Data", ifile++, true, year, isKFL, isInc, cType, muTot, eleTot)<<endl; outFile<<"\\\\"<<endl;  ifile++ ;
  outFile<<"\\hline "<<endl;
  outFile<<GetInclusive("Data/Bkg", ifileData, true, year, isKFL, isInc, cType, muTot, eleTot)<<endl; outFile<<"\\\\"<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<"\\end{tabular}"<<endl;
  outFile<<"\\end{adjustbox}"<<endl;
  outFile<<"\\end{table}"<<endl;
  outFile<<""<<endl;
  outFile<<""<<endl;
  
  
  ifile = 1;
  bool ismu = true;
  //outFile<<"\\begin{landscape}"<<endl;
  outFile<<"\\begin{table}"<<endl;
  outFile<<"\\centering\\caption{"+tab2_caption+"}"<<endl;
  outFile<<"\\label{tab:sec07_syst_Inc_"<<year<<"}"<<endl;
  outFile<<"\\begin{adjustbox}{width=\\textwidth}"<<endl;
  ///outFile<<"\\footnotesize\\setlength{\\tabcolsep}{0.3pt}"<<endl;
  outFile<<"\\begin{tabular}{  c c c c c  c c c  c  ccc  cc   c  c c c c   c c c  c c }"<<endl;
  outFile<<"\\hline "<<endl;  
  //outFile<<" Category & Process &  Pileup & Lepton & Prefire & jet \\& $p_\\text{T}^\\text{miss}$ & b\\&c tagging & Normalization  &  Statistical \\\\ "
  outFile<<" Category & Process &  {\\rotatebox{90}{Pileup (corr.)}} & {\\rotatebox{90}{Prefire}} & {\\rotatebox{90}{Lepton}} "
    //<<"& {\\rotatebox{90}{jet \\& $p_\\text{T}^\\text{miss}$ (corr.)}} "
	 <<"& {\\rotatebox{90}{JES (corr., shape)}} & {\\rotatebox{90}{JER (corr., shape)}} & {\\rotatebox{90}{pileup jet identification}} "
	 <<"& {\\rotatebox{90}{b\\&c tagging stat. (shape)}} "
	 <<"& {\\rotatebox{90}{b\\&c tagging XS DY-b}} & {\\rotatebox{90}{b\\&c tagging XS DY-c}} & {\\rotatebox{90}{b\\&c tagging XS Wjet-c}} "
	 <<"& {\\rotatebox{90}{b\\&c tagging Interp.}} & {\\rotatebox{90}{b\\&c tagging Extrap.}} "
    	 <<"& {\\rotatebox{90}{PDF}} "
	 <<"& {\\rotatebox{90}{Renorm. (corr., shape)}}  & {\\rotatebox{90}{Factor. (corr.)}} "
    	 <<"& {\\rotatebox{90}{ISR (corr.)}}  & {\\rotatebox{90}{FSR (corr., shape)}} "
    	 <<"& {\\rotatebox{90}{CP5}}  & {\\rotatebox{90}{top quark mass (shape)}}  & {\\rotatebox{90}{$h_{\\text{damp}}$ (shape)}}  "
	 <<"& {\\rotatebox{90}{Normalization}}  "
	 <<"& {\\rotatebox{90}{Statistical}} \\\\ "
   	 <<""<<endl;
  
  //pu, mu, btagb, btagl, prefire, jec, jer, norm
  outFile<<"\\hline "<<endl;
  outFile<<"\\multicolumn{24}{c}{\$\\mu\$ + jets } \\\\"<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<GetDifferential("$H^{+} + H^{-} (m=80$ GeV)", ifile++, false, year, isKFL, isInc, cType, ismu)<<endl;  
  outFile<<GetDifferential("$H^{+} + H^{-} (m=90$ GeV)", ifile++, false, year, isKFL, isInc, cType, ismu)<<endl;  
  outFile<<GetDifferential("$H^{+} + H^{-} (m=100$ GeV)", ifile++, false, year, isKFL, isInc, cType, ismu)<<endl; 
  outFile<<GetDifferential("$H^{+} + H^{-} (m=110$ GeV)", ifile++, false, year, isKFL, isInc, cType, ismu)<<endl; 
  outFile<<GetDifferential("$H^{+} + H^{-} (m=120$ GeV)", ifile++, false, year, isKFL, isInc, cType, ismu)<<endl; 
  outFile<<GetDifferential("$H^{+} + H^{-} (m=130$ GeV)", ifile++, false, year, isKFL, isInc, cType, ismu)<<endl; 
  outFile<<GetDifferential("$H^{+} + H^{-} (m=140$ GeV)", ifile++, false, year, isKFL, isInc, cType, ismu)<<endl; 
  outFile<<GetDifferential("$H^{+} + H^{-} (m=150$ GeV)", ifile++, false, year, isKFL, isInc, cType, ismu)<<endl; 
  outFile<<GetDifferential("$H^{+} + H^{-} (m=155$ GeV)", ifile++, false, year, isKFL, isInc, cType, ismu)<<endl; 
  outFile<<GetDifferential("$H^{+} + H^{-} (m=160$ GeV)", ifile++, false, year, isKFL, isInc, cType, ismu)<<endl; 
  outFile<<"\\hline "<<endl;
  outFile<<GetDifferential("SM $t\\bar{t}$ + jets", ifile++, false, year, isKFL, isInc, cType, ismu)<<endl;
  outFile<<GetDifferential("Single ~t", ifile++, false, year, isKFL, isInc, cType, ismu)<<endl;
  outFile<<GetDifferential("W + jets", ifile++, false, year, isKFL, isInc, cType, ismu)<<endl;
  outFile<<GetDifferential("$Z/\\gamma$ + jets", ifile++, false, year, isKFL, isInc, cType, ismu)<<endl;
  outFile<<GetDifferential("VV", ifile++, false, year, isKFL, isInc, cType, ismu)<<endl; ifile = ifile+2;
  outFile<<GetDifferential("DD QCD", ifile++, true, year, isKFL, isInc, cType, ismu)<<endl; ifile++ ;
  ifile = 1;
  ismu = false;
  outFile<<"\\hline "<<endl;
  outFile<<"\\multicolumn{24}{c}{$e$ + jets } \\\\"<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<GetDifferential("$H^{+} + H^{-} (m=80$ GeV)", ifile++, false, year, isKFL, isInc, cType, ismu)<<endl;
  outFile<<GetDifferential("$H^{+} + H^{-} (m=90$ GeV)", ifile++, false, year, isKFL, isInc, cType, ismu)<<endl;
  outFile<<GetDifferential("$H^{+} + H^{-} (m=100$ GeV)", ifile++, false, year, isKFL, isInc, cType, ismu)<<endl;
  outFile<<GetDifferential("$H^{+} + H^{-} (m=110$ GeV)", ifile++, false, year, isKFL, isInc, cType, ismu)<<endl;
  outFile<<GetDifferential("$H^{+} + H^{-} (m=120$ GeV)", ifile++, false, year, isKFL, isInc, cType, ismu)<<endl;
  outFile<<GetDifferential("$H^{+} + H^{-} (m=130$ GeV)", ifile++, false, year, isKFL, isInc, cType, ismu)<<endl;
  outFile<<GetDifferential("$H^{+} + H^{-} (m=140$ GeV)", ifile++, false, year, isKFL, isInc, cType, ismu)<<endl;
  outFile<<GetDifferential("$H^{+} + H^{-} (m=150$ GeV)", ifile++, false, year, isKFL, isInc, cType, ismu)<<endl;
  outFile<<GetDifferential("$H^{+} + H^{-} (m=155$ GeV)", ifile++, false, year, isKFL, isInc, cType, ismu)<<endl;
  outFile<<GetDifferential("$H^{+} + H^{-} (m=160$ GeV)", ifile++, false, year, isKFL, isInc, cType, ismu)<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<GetDifferential("SM $t\\bar{t}$ + jets", ifile++, false, year, isKFL, isInc, cType, ismu)<<endl;
  outFile<<GetDifferential("Single ~t", ifile++, false, year, isKFL, isInc, cType, ismu)<<endl;
  outFile<<GetDifferential("W + jets", ifile++, false, year, isKFL, isInc, cType, ismu)<<endl;
  outFile<<GetDifferential("$Z/\\gamma$ + jets", ifile++, false, year, isKFL, isInc, cType, ismu)<<endl;
  outFile<<GetDifferential("VV", ifile++, false, year, isKFL, isInc, cType, ismu)<<endl; ifile = ifile+2;
  outFile<<GetDifferential("DD QCD", ifile++, true, year, isKFL, isInc, cType, ismu)<<endl; ifile++ ;
  outFile<<"\\hline "<<endl;  
  outFile<<"\\hline "<<endl;
  outFile<<"\\end{tabular}"<<endl;
  outFile<<"\\end{adjustbox}"<<endl;
  outFile<<"\\end{table}"<<endl;
  //outFile<<"\\end{landscape}"<<endl;
  outFile<<""<<endl;
  outFile<<""<<endl;
  outFile<<"%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%"<<endl;

  
  // //////////////////////////////////////////////////////////////////////////////////////////////////
  // //exclusive loose charm
  // //////////////////////////////////////////////////////////////////////////////////////////////////
  
  isKFL = false;
  isInc = false;
  cType = 'L';
  tab1_caption = "Event yield for exclusive charm tagging category in " + to_string(year) + ".";;
  tab2_caption = "Systematic and statistical uncertainties in \\% for muon channel for exclusive charm tagging category in " + to_string(year) + ".";;
  tab3_caption = "Systematic and statistical uncertainties in \\% for electron channel for exclusive charm tagging category in " + to_string(year) + ".";;
  
  nEvents = "";
  if(forPaper) nEvents = "$N_{events}  \\pm unc$";
  else nEvents = "$N_{events} \\pm stat \\pm sys$";
  //Exclusive Mjj
  outFile<<"\\begin{table}"<<endl;
  outFile<<"\\caption{"<<tab1_caption<<"}"<<endl;
  outFile<<"\\label{tab:sec07_eventYield_ExcL_"<<year<<"}"<<endl;
  outFile<<"\\begin{adjustbox}{width=\\textwidth}"<<endl;
  outFile<<"\\begin{tabular}{cc cc cc cc}"<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<" Process & "<<nEvents<<" & "<<nEvents<<"& "<<nEvents<<" & "<<nEvents<<"& "<<nEvents<<" & "<<nEvents<<"\\\\ "<<endl;
  outFile<<" & $\\mu$ + jets &  e + jets & $\\mu$ + jets &  e + jets & $\\mu$ + jets &  e + jets\\\\"<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<"\\hline "<<endl;
  
  //CalcSystTable(1);
  ifile = 1;
  //GetInclusive("$H^{+} + H^{-} (m=80$ GeV)", 1);
  cType = 'L'; outFile<<GetInclusive("$H^{+} + H^{-} (m=80$ GeV)", ifile, false, year, isKFL, isInc, cType, muTotL, eleTotL);
  cType = 'M'; outFile<<GetInclusive("", ifile, false, year, isKFL, isInc, cType, muTotM, eleTotM);
  cType = 'T'; outFile<<GetInclusive("", ifile++, false, year, isKFL, isInc, cType, muTotT, eleTotT); outFile<<"\\\\"<<endl;
  cType = 'L'; outFile<<GetInclusive("$H^{+} + H^{-} (m=90$ GeV)", ifile, false, year, isKFL, isInc, cType, muTotL, eleTotL);
  cType = 'M'; outFile<<GetInclusive("", ifile, false, year, isKFL, isInc, cType, muTotM, eleTotM);
  cType = 'T'; outFile<<GetInclusive("", ifile++, false, year, isKFL, isInc, cType, muTotT, eleTotT); outFile<<"\\\\"<<endl;
  cType = 'L'; outFile<<GetInclusive("$H^{+} + H^{-} (m=100$ GeV)", ifile, false, year, isKFL, isInc, cType, muTotL, eleTotL);
  cType = 'M'; outFile<<GetInclusive("", ifile, false, year, isKFL, isInc, cType, muTotM, eleTotM);
  cType = 'T'; outFile<<GetInclusive("", ifile++, false, year, isKFL, isInc, cType, muTotT, eleTotT); outFile<<"\\\\"<<endl;
  cType = 'L'; outFile<<GetInclusive("$H^{+} + H^{-} (m=110$ GeV)", ifile, false, year, isKFL, isInc, cType, muTotL, eleTotL);
  cType = 'M'; outFile<<GetInclusive("", ifile, false, year, isKFL, isInc, cType, muTotM, eleTotM);
  cType = 'T'; outFile<<GetInclusive("", ifile++, false, year, isKFL, isInc, cType, muTotT, eleTotT); outFile<<"\\\\"<<endl;
  cType = 'L'; outFile<<GetInclusive("$H^{+} + H^{-} (m=120$ GeV)", ifile, false, year, isKFL, isInc, cType, muTotL, eleTotL);
  cType = 'M'; outFile<<GetInclusive("", ifile, false, year, isKFL, isInc, cType, muTotM, eleTotM);
  cType = 'T'; outFile<<GetInclusive("", ifile++, false, year, isKFL, isInc, cType, muTotT, eleTotT); outFile<<"\\\\"<<endl;
  cType = 'L'; outFile<<GetInclusive("$H^{+} + H^{-} (m=130$ GeV)", ifile, false, year, isKFL, isInc, cType, muTotL, eleTotL);
  cType = 'M'; outFile<<GetInclusive("", ifile, false, year, isKFL, isInc, cType, muTotM, eleTotM);
  cType = 'T'; outFile<<GetInclusive("", ifile++, false, year, isKFL, isInc, cType, muTotT, eleTotT); outFile<<"\\\\"<<endl;
  cType = 'L'; outFile<<GetInclusive("$H^{+} + H^{-} (m=140$ GeV)", ifile, false, year, isKFL, isInc, cType, muTotL, eleTotL);
  cType = 'M'; outFile<<GetInclusive("", ifile, false, year, isKFL, isInc, cType, muTotM, eleTotM);
  cType = 'T'; outFile<<GetInclusive("", ifile++, false, year, isKFL, isInc, cType, muTotT, eleTotT); outFile<<"\\\\"<<endl;
  cType = 'L'; outFile<<GetInclusive("$H^{+} + H^{-} (m=150$ GeV)", ifile, false, year, isKFL, isInc, cType, muTotL, eleTotL);
  cType = 'M'; outFile<<GetInclusive("", ifile, false, year, isKFL, isInc, cType, muTotM, eleTotM);
  cType = 'T'; outFile<<GetInclusive("", ifile++, false, year, isKFL, isInc, cType, muTotT, eleTotT); outFile<<"\\\\"<<endl;
  cType = 'L'; outFile<<GetInclusive("$H^{+} + H^{-} (m=155$ GeV)", ifile, false, year, isKFL, isInc, cType, muTotL, eleTotL);
  cType = 'M'; outFile<<GetInclusive("", ifile, false, year, isKFL, isInc, cType, muTotM, eleTotM);
  cType = 'T'; outFile<<GetInclusive("", ifile++, false, year, isKFL, isInc, cType, muTotT, eleTotT); outFile<<"\\\\"<<endl;
  cType = 'L'; outFile<<GetInclusive("$H^{+} + H^{-} (m=160$ GeV)", ifile, false, year, isKFL, isInc, cType, muTotL, eleTotL);
  cType = 'M'; outFile<<GetInclusive("", ifile, false, year, isKFL, isInc, cType, muTotM, eleTotM);
  cType = 'T'; outFile<<GetInclusive("", ifile++, false, year, isKFL, isInc, cType, muTotT, eleTotT); outFile<<"\\\\"<<endl;
  outFile<<"\\hline "<<endl;
  cType = 'L'; outFile<<GetInclusive("SM $t\\bar{t}$ + jets", ifile, false, year, isKFL, isInc, cType, muTotL, eleTotL);
  cType = 'M'; outFile<<GetInclusive("", ifile, false, year, isKFL, isInc, cType, muTotM, eleTotM);
  cType = 'T'; outFile<<GetInclusive("", ifile++, false, year, isKFL, isInc, cType, muTotT, eleTotT); outFile<<"\\\\"<<endl;
  cType = 'L'; outFile<<GetInclusive("Single ~t", ifile, false, year, isKFL, isInc, cType, muTotL, eleTotL);
  cType = 'M'; outFile<<GetInclusive("", ifile, false, year, isKFL, isInc, cType, muTotM, eleTotM);
  cType = 'T'; outFile<<GetInclusive("", ifile++, false, year, isKFL, isInc, cType, muTotT, eleTotT); outFile<<"\\\\"<<endl;
  cType = 'L'; outFile<<GetInclusive("W + jets", ifile, false, year, isKFL, isInc, cType, muTotL, eleTotL);
  cType = 'M'; outFile<<GetInclusive("", ifile, false, year, isKFL, isInc, cType, muTotM, eleTotM);
  cType = 'T'; outFile<<GetInclusive("", ifile++, false, year, isKFL, isInc, cType, muTotT, eleTotT); outFile<<"\\\\"<<endl;
  cType = 'L'; outFile<<GetInclusive("$Z/\\gamma$ + jets", ifile, false, year, isKFL, isInc, cType, muTotL, eleTotL);
  cType = 'M'; outFile<<GetInclusive("", ifile, false, year, isKFL, isInc, cType, muTotM, eleTotM);
  cType = 'T'; outFile<<GetInclusive("", ifile++, false, year, isKFL, isInc, cType, muTotT, eleTotT); outFile<<"\\\\"<<endl;
  cType = 'L'; outFile<<GetInclusive("VV", ifile, false, year, isKFL, isInc, cType, muTotL, eleTotL);
  cType = 'M'; outFile<<GetInclusive("", ifile, false, year, isKFL, isInc, cType, muTotM, eleTotM);
  cType = 'T'; outFile<<GetInclusive("", ifile++, false, year, isKFL, isInc, cType, muTotT, eleTotT); outFile<<"\\\\"<<endl;
  ifile++;ifile++;//to skip MC QCD
  cType = 'L'; outFile<<GetInclusive("QCD multijet", ifile, false, year, isKFL, isInc, cType, muTotL, eleTotL);
  cType = 'M'; outFile<<GetInclusive("", ifile, false, year, isKFL, isInc, cType, muTotM, eleTotM);
  cType = 'T'; outFile<<GetInclusive("", ifile++, false, year, isKFL, isInc, cType, muTotT, eleTotT); outFile<<"\\\\"<<endl;
  outFile<<"\\hline "<<endl;
  cType = 'L'; outFile<<GetInclusive("All background", ifile, true, year, isKFL, isInc, cType, muTotL, eleTotL);
  cType = 'M'; outFile<<GetInclusive("All", ifile, true, year, isKFL, isInc, cType, muTotM, eleTotM);
  cType = 'T'; outFile<<GetInclusive("All", ifile, true, year, isKFL, isInc, cType, muTotT, eleTotT); outFile<<"\\\\"<<endl;
  outFile<<"\\hline "<<endl;
  ifile++;
  cType = 'L'; outFile<<GetInclusive("Data", ifile, true, year, isKFL, isInc, cType, muTotL, eleTotL);
  cType = 'M'; outFile<<GetInclusive("", ifile, true, year, isKFL, isInc, cType, muTotM, eleTotM);
  cType = 'T'; outFile<<GetInclusive("", ifile, true, year, isKFL, isInc, cType, muTotT, eleTotT);outFile<<"\\\\"<<endl;
  // outFile<<"\\hline "<<endl;
  // outFile<<GetInclusive("Data", ifile++, true, year, isKFL, isInc, cType, muTot, eleTot)<<endl; ifile++ ;
  // outFile<<"\\hline "<<endl;
  // outFile<<GetInclusive("Data/Bkg", ifileData, true, year, isKFL, isInc, cType, muTot, eleTot)<<endl;
  outFile<<"\\hline "<<endl;
  outFile<<"\\end{tabular}"<<endl;
  outFile<<"\\end{adjustbox}"<<endl;
  outFile<<"\\end{table}"<<endl;
  outFile<<""<<endl;
  outFile<<""<<endl;
  

  ismu = true;
  //outFile<<"\\begin{landscape}"<<endl;
  outFile<<"\\begin{table}"<<endl;
  outFile<<"\\centering\\caption{"+tab2_caption+"}"<<endl;
  outFile<<"\\label{tab:sec07_syst_Exc_mu_"<<year<<"}"<<endl;
  outFile<<"\\begin{adjustbox}{width=\\textwidth}"<<endl;
  ///outFile<<"\\footnotesize\\setlength{\\tabcolsep}{0.3pt}"<<endl;
  outFile<<"\\begin{tabular}{  c c c c c  c c c  c  ccc  cc   c  c c c c   c c c  c c }"<<endl;
  outFile<<"\\hline "<<endl;  
  //outFile<<" Category & Process &  Pileup & Lepton & Prefire & jet \\& $p_\\text{T}^\\text{miss}$ & b\\&c tagging & Normalization  &  Statistical \\\\ "
  outFile<<" Category & Process &  {\\rotatebox{90}{Pileup (corr.)}} & {\\rotatebox{90}{Prefire}} & {\\rotatebox{90}{Lepton}} "
    //<<"& {\\rotatebox{90}{jet \\& $p_\\text{T}^\\text{miss}$ (corr.)}} "
	 <<"& {\\rotatebox{90}{JES (corr., shape)}} & {\\rotatebox{90}{JER (corr., shape)}} & {\\rotatebox{90}{pileup jet identification}} "
	 <<"& {\\rotatebox{90}{b\\&c tagging stat. (shape)}} "
	 <<"& {\\rotatebox{90}{b\\&c tagging XS DY-b}} & {\\rotatebox{90}{b\\&c tagging XS DY-c}} & {\\rotatebox{90}{b\\&c tagging XS Wjet-c}} "
	 <<"& {\\rotatebox{90}{b\\&c tagging Interp.}} & {\\rotatebox{90}{b\\&c tagging Extrap.}} "
    	 <<"& {\\rotatebox{90}{PDF}} "
	 <<"& {\\rotatebox{90}{Renorm. (corr., shape)}}  & {\\rotatebox{90}{Factor. (corr.)}} "
    	 <<"& {\\rotatebox{90}{ISR (corr.)}}  & {\\rotatebox{90}{FSR (corr., shape)}} "
    	 <<"& {\\rotatebox{90}{CP5}}  & {\\rotatebox{90}{top quark mass (shape)}}  & {\\rotatebox{90}{$h_{\\text{damp}}$ (shape)}}  "
	 <<"& {\\rotatebox{90}{Normalization}}  "
	 <<"& {\\rotatebox{90}{Statistical}} \\\\ "
   	 <<""<<endl;
  
  outFile<<"\\hline "<<endl;
  outFile<<"\\multicolumn{24}{c}{\$\\mu\$ + jets } \\\\"<<endl;
  outFile<<"\\hline "<<endl;
  cType = 'L';   ifile = 1;
  outFile<<"loose "<<endl;
  outFile<<GetDifferential("$H^{+} + H^{-} (m=90$ GeV)", ifile++, false, year, isKFL, isInc, cType, ismu)<<endl;
  outFile<<GetDifferential("$H^{+} + H^{-} (m=90$ GeV)", ifile++, false, year, isKFL, isInc, cType, ismu)<<endl;
  outFile<<GetDifferential("$H^{+} + H^{-} (m=100$ GeV)", ifile++, false, year, isKFL, isInc, cType, ismu)<<endl;
  outFile<<GetDifferential("$H^{+} + H^{-} (m=110$ GeV)", ifile++, false, year, isKFL, isInc, cType, ismu)<<endl;
  outFile<<GetDifferential("$H^{+} + H^{-} (m=120$ GeV)", ifile++, false, year, isKFL, isInc, cType, ismu)<<endl;
  outFile<<GetDifferential("$H^{+} + H^{-} (m=130$ GeV)", ifile++, false, year, isKFL, isInc, cType, ismu)<<endl;
  outFile<<GetDifferential("$H^{+} + H^{-} (m=140$ GeV)", ifile++, false, year, isKFL, isInc, cType, ismu)<<endl;
  outFile<<GetDifferential("$H^{+} + H^{-} (m=150$ GeV)", ifile++, false, year, isKFL, isInc, cType, ismu)<<endl;
  outFile<<GetDifferential("$H^{+} + H^{-} (m=155$ GeV)", ifile++, false, year, isKFL, isInc, cType, ismu)<<endl;
  outFile<<GetDifferential("$H^{+} + H^{-} (m=160$ GeV)", ifile++, false, year, isKFL, isInc, cType, ismu)<<endl;
  ifile = 11;
  outFile<<GetDifferential("SM $t\\bar{t}$ + jets", ifile++, false, year, isKFL, isInc, cType, ismu)<<endl;
  outFile<<GetDifferential("Single ~t", ifile++, false, year, isKFL, isInc, cType, ismu)<<endl;
  outFile<<GetDifferential("W + jets", ifile++, false, year, isKFL, isInc, cType, ismu)<<endl;
  outFile<<GetDifferential("$Z/\\gamma$ + jets", ifile++, false, year, isKFL, isInc, cType, ismu)<<endl;
  outFile<<GetDifferential("VV", ifile++, false, year, isKFL, isInc, cType, ismu)<<endl; ifile = ifile+2;
  outFile<<GetDifferential("QCD multijet", ifile++, true, year, isKFL, isInc, cType, ismu)<<endl; ifile++ ;
  outFile<<"\\hline "<<endl;  
  cType = 'M';   ifile = 1;
  outFile<<"medium "<<endl;
  outFile<<GetDifferential("$H^{+} + H^{-} (m=90$ GeV)", ifile++, false, year, isKFL, isInc, cType, ismu)<<endl;
  outFile<<GetDifferential("$H^{+} + H^{-} (m=90$ GeV)", ifile++, false, year, isKFL, isInc, cType, ismu)<<endl;
  outFile<<GetDifferential("$H^{+} + H^{-} (m=100$ GeV)", ifile++, false, year, isKFL, isInc, cType, ismu)<<endl;
  outFile<<GetDifferential("$H^{+} + H^{-} (m=110$ GeV)", ifile++, false, year, isKFL, isInc, cType, ismu)<<endl;
  outFile<<GetDifferential("$H^{+} + H^{-} (m=120$ GeV)", ifile++, false, year, isKFL, isInc, cType, ismu)<<endl;
  outFile<<GetDifferential("$H^{+} + H^{-} (m=130$ GeV)", ifile++, false, year, isKFL, isInc, cType, ismu)<<endl;
  outFile<<GetDifferential("$H^{+} + H^{-} (m=140$ GeV)", ifile++, false, year, isKFL, isInc, cType, ismu)<<endl;
  outFile<<GetDifferential("$H^{+} + H^{-} (m=150$ GeV)", ifile++, false, year, isKFL, isInc, cType, ismu)<<endl;
  outFile<<GetDifferential("$H^{+} + H^{-} (m=155$ GeV)", ifile++, false, year, isKFL, isInc, cType, ismu)<<endl;
  outFile<<GetDifferential("$H^{+} + H^{-} (m=160$ GeV)", ifile++, false, year, isKFL, isInc, cType, ismu)<<endl;
  ifile = 11;
  outFile<<GetDifferential("SM $t\\bar{t}$ + jets", ifile++, false, year, isKFL, isInc, cType, ismu)<<endl;
  outFile<<GetDifferential("Single ~t", ifile++, false, year, isKFL, isInc, cType, ismu)<<endl;
  outFile<<GetDifferential("W + jets", ifile++, false, year, isKFL, isInc, cType, ismu)<<endl;
  outFile<<GetDifferential("$Z/\\gamma$ + jets", ifile++, false, year, isKFL, isInc, cType, ismu)<<endl;
  outFile<<GetDifferential("VV", ifile++, false, year, isKFL, isInc, cType, ismu)<<endl; ifile = ifile+2;
  outFile<<GetDifferential("QCD multijet", ifile++, true, year, isKFL, isInc, cType, ismu)<<endl; ifile++ ;
  outFile<<"\\hline "<<endl;  
  cType = 'T';   ifile = 1;
  outFile<<"tight "<<endl;
  outFile<<GetDifferential("$H^{+} + H^{-} (m=90$ GeV)", ifile++, false, year, isKFL, isInc, cType, ismu)<<endl;
  outFile<<GetDifferential("$H^{+} + H^{-} (m=90$ GeV)", ifile++, false, year, isKFL, isInc, cType, ismu)<<endl;
  outFile<<GetDifferential("$H^{+} + H^{-} (m=100$ GeV)", ifile++, false, year, isKFL, isInc, cType, ismu)<<endl;
  outFile<<GetDifferential("$H^{+} + H^{-} (m=110$ GeV)", ifile++, false, year, isKFL, isInc, cType, ismu)<<endl;
  outFile<<GetDifferential("$H^{+} + H^{-} (m=120$ GeV)", ifile++, false, year, isKFL, isInc, cType, ismu)<<endl;
  outFile<<GetDifferential("$H^{+} + H^{-} (m=130$ GeV)", ifile++, false, year, isKFL, isInc, cType, ismu)<<endl;
  outFile<<GetDifferential("$H^{+} + H^{-} (m=140$ GeV)", ifile++, false, year, isKFL, isInc, cType, ismu)<<endl;
  outFile<<GetDifferential("$H^{+} + H^{-} (m=150$ GeV)", ifile++, false, year, isKFL, isInc, cType, ismu)<<endl;
  outFile<<GetDifferential("$H^{+} + H^{-} (m=155$ GeV)", ifile++, false, year, isKFL, isInc, cType, ismu)<<endl;
  outFile<<GetDifferential("$H^{+} + H^{-} (m=160$ GeV)", ifile++, false, year, isKFL, isInc, cType, ismu)<<endl;
  ifile = 11;
  outFile<<GetDifferential("SM $t\\bar{t}$ + jets", ifile++, false, year, isKFL, isInc, cType, ismu)<<endl;
  outFile<<GetDifferential("Single ~t", ifile++, false, year, isKFL, isInc, cType, ismu)<<endl;
  outFile<<GetDifferential("W + jets", ifile++, false, year, isKFL, isInc, cType, ismu)<<endl;
  outFile<<GetDifferential("$Z/\\gamma$ + jets", ifile++, false, year, isKFL, isInc, cType, ismu)<<endl;
  outFile<<GetDifferential("VV", ifile++, false, year, isKFL, isInc, cType, ismu)<<endl; ifile = ifile+2;
  outFile<<GetDifferential("QCD multijet", ifile++, true, year, isKFL, isInc, cType, ismu)<<endl; ifile++ ;
  outFile<<"\\hline "<<endl;
  outFile<<"\\end{tabular}"<<endl;
  outFile<<"\\end{adjustbox}"<<endl;
  outFile<<"\\end{table}"<<endl;
  //outFile<<"\\end{landscape}"<<endl;

  outFile<<""<<endl;
  outFile<<""<<endl;

  ismu = false;
  //outFile<<"\\begin{landscape}"<<endl;
  outFile<<"\\begin{table}"<<endl;
  outFile<<"\\centering\\caption{"+tab3_caption+"}"<<endl;
  outFile<<"\\label{tab:sec07_syst_Exc_ele_"<<year<<"}"<<endl;
  outFile<<"\\begin{adjustbox}{width=\\textwidth}"<<endl;
  ///outFile<<"\\footnotesize\\setlength{\\tabcolsep}{0.3pt}"<<endl;
  outFile<<"\\begin{tabular}{  c c c c c  c c c  c  ccc  cc   c  c c c c   c c c  c c }"<<endl;
  outFile<<"\\hline "<<endl;  
  //outFile<<" Category & Process &  Pileup & Lepton & Prefire & jet \\& $p_\\text{T}^\\text{miss}$ & b\\&c tagging & Normalization  &  Statistical \\\\ "
  outFile<<" Category & Process &  {\\rotatebox{90}{Pileup (corr.)}} & {\\rotatebox{90}{Prefire}} & {\\rotatebox{90}{Lepton}} "
    //<<"& {\\rotatebox{90}{jet \\& $p_\\text{T}^\\text{miss}$ (corr.)}} "
	 <<"& {\\rotatebox{90}{JES (corr., shape)}} & {\\rotatebox{90}{JER (corr., shape)}} & {\\rotatebox{90}{pileup jet identification}} "
	 <<"& {\\rotatebox{90}{b\\&c tagging stat. (shape)}} "
	 <<"& {\\rotatebox{90}{b\\&c tagging XS DY-b}} & {\\rotatebox{90}{b\\&c tagging XS DY-c}} & {\\rotatebox{90}{b\\&c tagging XS Wjet-c}} "
	 <<"& {\\rotatebox{90}{b\\&c tagging Interp.}} & {\\rotatebox{90}{b\\&c tagging Extrap.}} "
    	 <<"& {\\rotatebox{90}{PDF}} "
	 <<"& {\\rotatebox{90}{Renorm. (corr., shape)}}  & {\\rotatebox{90}{Factor. (corr.)}} "
    	 <<"& {\\rotatebox{90}{ISR (corr.)}}  & {\\rotatebox{90}{FSR (corr., shape)}} "
    	 <<"& {\\rotatebox{90}{CP5}}  & {\\rotatebox{90}{top quark mass (shape)}}  & {\\rotatebox{90}{$h_{\\text{damp}}$ (shape)}}  "
	 <<"& {\\rotatebox{90}{Normalization}}  "
	 <<"& {\\rotatebox{90}{Statistical}} \\\\ "
   	 <<""<<endl;
  
  outFile<<"\\hline "<<endl;
  outFile<<"\\multicolumn{24}{c}{\$e\$ + jets } \\\\"<<endl;
  outFile<<"\\hline "<<endl;
  cType = 'L';   ifile = 1;
  outFile<<"loose "<<endl;
  outFile<<GetDifferential("$H^{+} + H^{-} (m=90$ GeV)", ifile++, false, year, isKFL, isInc, cType, ismu)<<endl;
  outFile<<GetDifferential("$H^{+} + H^{-} (m=90$ GeV)", ifile++, false, year, isKFL, isInc, cType, ismu)<<endl;
  outFile<<GetDifferential("$H^{+} + H^{-} (m=100$ GeV)", ifile++, false, year, isKFL, isInc, cType, ismu)<<endl;
  outFile<<GetDifferential("$H^{+} + H^{-} (m=110$ GeV)", ifile++, false, year, isKFL, isInc, cType, ismu)<<endl;
  outFile<<GetDifferential("$H^{+} + H^{-} (m=120$ GeV)", ifile++, false, year, isKFL, isInc, cType, ismu)<<endl;
  outFile<<GetDifferential("$H^{+} + H^{-} (m=130$ GeV)", ifile++, false, year, isKFL, isInc, cType, ismu)<<endl;
  outFile<<GetDifferential("$H^{+} + H^{-} (m=140$ GeV)", ifile++, false, year, isKFL, isInc, cType, ismu)<<endl;
  outFile<<GetDifferential("$H^{+} + H^{-} (m=150$ GeV)", ifile++, false, year, isKFL, isInc, cType, ismu)<<endl;
  outFile<<GetDifferential("$H^{+} + H^{-} (m=155$ GeV)", ifile++, false, year, isKFL, isInc, cType, ismu)<<endl;
  outFile<<GetDifferential("$H^{+} + H^{-} (m=160$ GeV)", ifile++, false, year, isKFL, isInc, cType, ismu)<<endl;
  ifile = 11;
  outFile<<GetDifferential("SM $t\\bar{t}$ + jets", ifile++, false, year, isKFL, isInc, cType, ismu)<<endl;
  outFile<<GetDifferential("Single ~t", ifile++, false, year, isKFL, isInc, cType, ismu)<<endl;
  outFile<<GetDifferential("W + jets", ifile++, false, year, isKFL, isInc, cType, ismu)<<endl;
  outFile<<GetDifferential("$Z/\\gamma$ + jets", ifile++, false, year, isKFL, isInc, cType, ismu)<<endl;
  outFile<<GetDifferential("VV", ifile++, false, year, isKFL, isInc, cType, ismu)<<endl; ifile = ifile+2;
  outFile<<GetDifferential("QCD multijet", ifile++, true, year, isKFL, isInc, cType, ismu)<<endl; ifile++ ;
  outFile<<"\\hline "<<endl;  
  cType = 'M';   ifile = 1;
  outFile<<"medium "<<endl;
  outFile<<GetDifferential("$H^{+} + H^{-} (m=90$ GeV)", ifile++, false, year, isKFL, isInc, cType, ismu)<<endl;
  outFile<<GetDifferential("$H^{+} + H^{-} (m=90$ GeV)", ifile++, false, year, isKFL, isInc, cType, ismu)<<endl;
  outFile<<GetDifferential("$H^{+} + H^{-} (m=100$ GeV)", ifile++, false, year, isKFL, isInc, cType, ismu)<<endl;
  outFile<<GetDifferential("$H^{+} + H^{-} (m=110$ GeV)", ifile++, false, year, isKFL, isInc, cType, ismu)<<endl;
  outFile<<GetDifferential("$H^{+} + H^{-} (m=120$ GeV)", ifile++, false, year, isKFL, isInc, cType, ismu)<<endl;
  outFile<<GetDifferential("$H^{+} + H^{-} (m=130$ GeV)", ifile++, false, year, isKFL, isInc, cType, ismu)<<endl;
  outFile<<GetDifferential("$H^{+} + H^{-} (m=140$ GeV)", ifile++, false, year, isKFL, isInc, cType, ismu)<<endl;
  outFile<<GetDifferential("$H^{+} + H^{-} (m=150$ GeV)", ifile++, false, year, isKFL, isInc, cType, ismu)<<endl;
  outFile<<GetDifferential("$H^{+} + H^{-} (m=155$ GeV)", ifile++, false, year, isKFL, isInc, cType, ismu)<<endl;
  outFile<<GetDifferential("$H^{+} + H^{-} (m=160$ GeV)", ifile++, false, year, isKFL, isInc, cType, ismu)<<endl;
  ifile = 11;
  outFile<<GetDifferential("SM $t\\bar{t}$ + jets", ifile++, false, year, isKFL, isInc, cType, ismu)<<endl;
  outFile<<GetDifferential("Single ~t", ifile++, false, year, isKFL, isInc, cType, ismu)<<endl;
  outFile<<GetDifferential("W + jets", ifile++, false, year, isKFL, isInc, cType, ismu)<<endl;
  outFile<<GetDifferential("$Z/\\gamma$ + jets", ifile++, false, year, isKFL, isInc, cType, ismu)<<endl;
  outFile<<GetDifferential("VV", ifile++, false, year, isKFL, isInc, cType, ismu)<<endl; ifile = ifile+2;
  outFile<<GetDifferential("QCD multijet", ifile++, true, year, isKFL, isInc, cType, ismu)<<endl; ifile++ ;
  outFile<<"\\hline "<<endl;  
  cType = 'T';   ifile = 1;
  outFile<<"tight "<<endl;
  outFile<<GetDifferential("$H^{+} + H^{-} (m=90$ GeV)", ifile++, false, year, isKFL, isInc, cType, ismu)<<endl;
  outFile<<GetDifferential("$H^{+} + H^{-} (m=90$ GeV)", ifile++, false, year, isKFL, isInc, cType, ismu)<<endl;
  outFile<<GetDifferential("$H^{+} + H^{-} (m=100$ GeV)", ifile++, false, year, isKFL, isInc, cType, ismu)<<endl;
  outFile<<GetDifferential("$H^{+} + H^{-} (m=110$ GeV)", ifile++, false, year, isKFL, isInc, cType, ismu)<<endl;
  outFile<<GetDifferential("$H^{+} + H^{-} (m=120$ GeV)", ifile++, false, year, isKFL, isInc, cType, ismu)<<endl;
  outFile<<GetDifferential("$H^{+} + H^{-} (m=130$ GeV)", ifile++, false, year, isKFL, isInc, cType, ismu)<<endl;
  outFile<<GetDifferential("$H^{+} + H^{-} (m=140$ GeV)", ifile++, false, year, isKFL, isInc, cType, ismu)<<endl;
  outFile<<GetDifferential("$H^{+} + H^{-} (m=150$ GeV)", ifile++, false, year, isKFL, isInc, cType, ismu)<<endl;
  outFile<<GetDifferential("$H^{+} + H^{-} (m=155$ GeV)", ifile++, false, year, isKFL, isInc, cType, ismu)<<endl;
  outFile<<GetDifferential("$H^{+} + H^{-} (m=160$ GeV)", ifile++, false, year, isKFL, isInc, cType, ismu)<<endl;
  ifile = 11;
  outFile<<GetDifferential("SM $t\\bar{t}$ + jets", ifile++, false, year, isKFL, isInc, cType, ismu)<<endl;
  outFile<<GetDifferential("Single ~t", ifile++, false, year, isKFL, isInc, cType, ismu)<<endl;
  outFile<<GetDifferential("W + jets", ifile++, false, year, isKFL, isInc, cType, ismu)<<endl;
  outFile<<GetDifferential("$Z/\\gamma$ + jets", ifile++, false, year, isKFL, isInc, cType, ismu)<<endl;
  outFile<<GetDifferential("VV", ifile++, false, year, isKFL, isInc, cType, ismu)<<endl; ifile = ifile+2;
  outFile<<GetDifferential("QCD multijet", ifile++, true, year, isKFL, isInc, cType, ismu)<<endl; ifile++ ;
  outFile<<"\\hline "<<endl;
  outFile<<"\\end{tabular}"<<endl;
  outFile<<"\\end{adjustbox}"<<endl;
  outFile<<"\\end{table}"<<endl;
  //outFile<<"\\end{landscape}"<<endl;
  
  outFile<<""<<endl;
  outFile<<""<<endl;

  // outFile<<"%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%"<<endl;
  
  outFile<<"\\end{document}"<<endl;
  outFile.close();
  
  return true;
}

string GetDifferential(string rowtitle, int ifile, bool inc, int year, bool isKFL, bool isInc, char cType, bool ismu)
{
  int CalcSystTable(int ifile, bool isMu, double output[], double error_percnt[], double error_percntH[], int year, bool isKFL, bool isIncl, char cType);
  
  const int  nofSyst = 22;//10;
  
  double muOut[3];
  double eleOut[3];
  double muErr[23]; //nofSyst + stat
  double eleErr[23]; //nofSyst + stat
  double muErrH[23]; //nofSyst + stat
  double eleErrH[23]; //nofSyst + stat
  
  for(int i=0;i<23;i++) muErr[i] = eleErr[i] = eleErrH[i] = muErrH[i] = 0.0 ;
  for(int i=0;i<3;i++) muOut[i] = eleOut[i] = 0.0 ;
  CalcSystTable(ifile, 1, muOut, muErr, muErrH, year, isKFL, isInc, cType);
  ifile = (inc) ? ifile+1 : ifile ;
  CalcSystTable(ifile, 0, eleOut, eleErr, eleErrH, year, isKFL, isInc, cType);
  
  string combined = "";
  cout<<"Diff sample " << sampleType[ifile-1] <<", RowTitle : " << rowtitle << endl;
  string sampleName = sampleType[ifile-1];
  
  // if(sampleName.find("QCDdd")==string::npos){
  //   combined = rowtitle
  //     + " & " + Form("$%3.2f$",((ismu)?muErr[0]:eleErr[0])) 
  //     + " & " + Form("$%3.2f$",((ismu)?muErr[1]:eleErr[1])) 
  //     + " & " + Form("$%3.2f$",((ismu)?muErr[2]:eleErr[2])) 
  //     + " & " + Form("$%3.2f$",((ismu)?muErr[3]:eleErr[3])) 
  //     + " & " + Form("$%3.2f$",((ismu)?muErr[4]:eleErr[4])) 
  //     + " & " + Form("$%3.2f$",((ismu)?muErr[5]:eleErr[5])) 
  //     + " & " + Form("$%3.2f$",((ismu)?muErr[6]:eleErr[6])) 
  //     + " & " + Form("$%3.2f$",((ismu)?muErr[7]:eleErr[7])) 
  //     + " & " + Form("$%3.2f$",((ismu)?muErr[8]:eleErr[8])) 
  //     + " & " + Form("$%3.2f$",((ismu)?muErr[9]:eleErr[9])) 
  //     + " & " + Form("$%3.2f$",((ismu)?muErr[10]:eleErr[10])) 
  //     + " & " + Form("$%3.2f$",((ismu)?muErr[11]:eleErr[11])) 
  //     + " & " + Form("$%3.2f$",((ismu)?muErr[12]:eleErr[12])) 
  //     + " & " + Form("$%3.2f$",((ismu)?muErr[13]:eleErr[13])) 
  //     + " & " + Form("$%3.2f$",((ismu)?muErr[14]:eleErr[14])) 
  //     + " & " + Form("$%3.2f$",((ismu)?muErr[15]:eleErr[15])) 
  //     + " & " + Form("$%3.2f$",((ismu)?muErr[16]:eleErr[16])) 
  //     + " & " + Form("$%3.2f$",((ismu)?muErr[17]:eleErr[17])) 
  //     + " & " + Form("$%3.2f$",((ismu)?muErr[18]:eleErr[18])) 
  //     //+ " & " + Form("$%3.2f(%3.2f)$",muErr[26],eleErr[26]) 
  //     // + " & " + Form("$%3.2f(%3.2f)$",muErr[27],eleErr[27]) 
  //     +"\\\\";
  // }else{
  //   combined = rowtitle 
  //     + " & " + "--"
  //     + " & " + "--"
  //     + " & " + "--"
  //     + " & " + "--"
  //     + " & " + "--"
  //     + " & " + "--"
  //     + " & " + "--"
  //     + " & " + "--"
  //     + " & " + "--"
  //     + " & " + "--"
  //     + " & " + "--"
  //     + " & " + "--"
  //     + " & " + "--"
  //     + " & " + "--"
  //     + " & " + "--"
  //     + " & " + "--"
  //     + " & " + "--"
  //     + " & " + Form("$%3.2f$",((ismu)?100.*muOut[2]/muOut[0]:100.*eleOut[2]/eleOut[0])) 
  //     + " & " + Form("$%3.2f$",((ismu)?100.*muOut[1]/muOut[0]:100.*eleOut[1]/eleOut[0])) 
  //     // + " & " + Form("$%3.2f(%3.2f)$",100.*muOut[2]/muOut[0],100.*eleOut[2]/eleOut[0]) 
  //     // + " & " + Form("$%3.2f(%3.2f)$",100.*muOut[1]/muOut[0],100.*eleOut[1]/eleOut[0]) 
  //     // + " & " + Form("$%3.2f(%3.2f)$",muErr[10],eleErr[10]) 
  //     +"\\\\";
  //   cout<<" isMu : "<< ismu << ", Diff : " << ((ismu)?muOut[2]:eleOut[2]) << ", Nom : "<< ((ismu)?muOut[0]:eleOut[0]) << ", stat : " << ((ismu)?muOut[1]:eleOut[1]) << endl;
  // }
  
  // Pileup(0), Lepton(1), Prefire(2), JES(3), JER(4), PDF(5), Renormalization(6), Factorization(7), ISR(8), FSR(9), PU JetID(10), b\\&c tagging Interpolation(11), b\\&c tagging Extrapolation(12),
  // b\\&c tagging XS DY-b(13), b\\&c tagging XS DY-c(14), b\\&c tagging XS Wjet-c(15), b\\&c tagging statistics(16), Normalization(17), cp5(18), mtop(19), hdamp(20), Statistical(21)
  double pileup_m = muErr[0];
  double pileup_e = eleErr[0];
  double lepton_m = muErr[1];
  double lepton_e = eleErr[1];
  double pref_m = muErr[2];
  double pref_e = eleErr[2];
  string prefire;
  if(year==2018)
    prefire = "--";
  else{
    if(ismu)
      prefire = Form("$%2.1f$",pref_m);
    else
      prefire = Form("$%2.1f$",pref_e);
  }
  double jetmet_m = TMath::Sqrt(muErr[3]*muErr[3] + muErr[4]*muErr[4] + muErr[10]*muErr[10]);
  double jetmet_e = TMath::Sqrt(eleErr[3]*eleErr[3] + eleErr[4]*eleErr[4] + eleErr[10]*eleErr[10]);
  double bcjets_m = TMath::Sqrt(muErr[11]*muErr[11] + muErr[12]*muErr[12] + muErr[13]*muErr[13] + muErr[14]*muErr[14] + muErr[15]*muErr[15] + muErr[16]*muErr[16]);
  double bcjets_e = TMath::Sqrt(eleErr[11]*eleErr[11] + eleErr[12]*eleErr[12] + eleErr[13]*eleErr[13] + eleErr[14]*eleErr[14] + eleErr[15]*eleErr[15] + eleErr[16]*eleErr[16]);
  double bcjets_stat_m = muErr[16];
  double bcjets_stat_e = eleErr[16];
  double bcjets_flavcomp_m = TMath::Sqrt(muErr[13]*muErr[13] + muErr[14]*muErr[14] + muErr[15]*muErr[15]);
  double bcjets_flavcomp_e = TMath::Sqrt(eleErr[13]*eleErr[13] + eleErr[14]*eleErr[14] + eleErr[15]*eleErr[15]);
  double bcjets_intexp_m = TMath::Sqrt(muErr[11]*muErr[11] + muErr[12]*muErr[12]);
  double bcjets_intexp_e = TMath::Sqrt(eleErr[11]*eleErr[11] + eleErr[12]*eleErr[12]);
  // double norm_m = TMath::Sqrt(muErr[5]*muErr[5] + muErr[6]*muErr[6] + muErr[7]*muErr[7] + muErr[8]*muErr[8] + muErr[9]*muErr[9] + muErr[17]*muErr[17]);
  // double norm_e = TMath::Sqrt(eleErr[5]*eleErr[5] + eleErr[6]*eleErr[6] + eleErr[7]*eleErr[7] + eleErr[8]*eleErr[8] + eleErr[9]*eleErr[9] + eleErr[17]*eleErr[17]);
  double norm_m = muErr[20];
  double norm_e = eleErr[20];
  if(sampleName.find("TTbar")==string::npos){
    norm_m = muErr[17];
    norm_e = eleErr[17];
  }
  double renormfact_m = TMath::Sqrt(muErr[6]*muErr[6] + muErr[7]*muErr[7]);
  double renormfact_e = TMath::Sqrt(eleErr[6]*eleErr[6] + eleErr[7]*eleErr[7]);
  double isrfsr_m = TMath::Sqrt(muErr[8]*muErr[8] + muErr[9]*muErr[9]);
  double isrfsr_e = TMath::Sqrt(eleErr[8]*eleErr[8] + eleErr[9]*eleErr[9]);
  
  double qcd_m = 100.*muOut[2]/muOut[0];
  double qcd_e = 100.*eleOut[2]/eleOut[0];
  double qcdstat_m = 100.*muOut[1]/muOut[0];
  double qcdstat_e = 100.*eleOut[1]/eleOut[0];

  // Pileup(0), Lepton(1), Prefire(2), JES(3), JER(4), PDF(5), Renormalization(6), Factorization(7), ISR(8), FSR(9), PU JetID(10), b\\&c tagging Interpolation(11), b\\&c tagging Extrapolation(12),
  // b\\&c tagging XS DY-b(13), b\\&c tagging XS DY-c(14), b\\&c tagging XS Wjet-c(15), b\\&c tagging statistics(16), Normalization(17), cp5(18), mtop(19), hdamp(20), Statistical(21)

  if(sampleName.find("QCDdd")==string::npos){
    if(sampleName.find("TTbar")!=string::npos){
      combined = string(" & ") + rowtitle
	+ " & " + Form("$%2.1f$",(ismu)?pileup_m:pileup_e)
	+ " & " + prefire
	+ " & " + Form("$%2.1f$",(ismu)?lepton_m:lepton_e)
	+ " & " + Form("$%2.1f$",(ismu)?muErr[3]:eleErr[3])
	+ " & " + Form("$%2.1f$",(ismu)?muErr[4]:eleErr[4])
	+ " & " + Form("$%2.1f$",(ismu)?muErr[10]:eleErr[10])
	+ " & " + Form("$%2.1f$",(ismu)?bcjets_stat_m:bcjets_stat_e)
	+ " & " + Form("$%2.1f$",(ismu)?muErr[13]:eleErr[13])
	+ " & " + Form("$%2.1f$",(ismu)?muErr[14]:eleErr[14])
	+ " & " + Form("$%2.1f$",(ismu)?muErr[15]:eleErr[15])
	+ " & " + Form("$%2.1f$",(ismu)?muErr[11]:eleErr[11])
	+ " & " + Form("$%2.1f$",(ismu)?muErr[12]:eleErr[12])
	+ " & " + Form("$%2.1f$",(ismu)?muErr[5]:eleErr[5])
	+ " & " + Form("$%2.1f$",(ismu)?muErr[6]:eleErr[6])
	+ " & " + Form("$%2.1f$",(ismu)?muErr[7]:eleErr[7])
	+ " & " + Form("$%2.1f$",(ismu)?muErr[8]:eleErr[8])
	+ " & " + Form("$%2.1f$",(ismu)?muErr[9]:eleErr[9])
	+ " & " + Form("$%2.1f$",(ismu)?muErr[17]:eleErr[17])
	+ " & " + Form("$%2.1f$",(ismu)?muErr[18]:eleErr[18])
	+ " & " + Form("$%2.1f$",(ismu)?muErr[19]:eleErr[19])
	+ " & " + Form("$%2.1f$",(ismu)?norm_m:norm_e)
	+ " & " + Form("$%2.1f$",(ismu)?muErr[21]:eleErr[21])
	+"\\\\";
    }else{
      combined = string(" & ") + rowtitle
	+ " & " + Form("$%2.1f$",(ismu)?pileup_m:pileup_e) 
	+ " & " + prefire
	+ " & " + Form("$%2.1f$",(ismu)?lepton_m:lepton_e)
	+ " & " + Form("$%2.1f$",(ismu)?muErr[3]:eleErr[3])
	+ " & " + Form("$%2.1f$",(ismu)?muErr[4]:eleErr[4])
	+ " & " + Form("$%2.1f$",(ismu)?muErr[10]:eleErr[10])
	+ " & " + Form("$%2.1f$",(ismu)?bcjets_stat_m:bcjets_stat_e)
	+ " & " + Form("$%2.1f$",(ismu)?muErr[13]:eleErr[13])
	+ " & " + Form("$%2.1f$",(ismu)?muErr[14]:eleErr[14])
	+ " & " + Form("$%2.1f$",(ismu)?muErr[15]:eleErr[15])
	+ " & " + Form("$%2.1f$",(ismu)?muErr[11]:eleErr[11])
	+ " & " + Form("$%2.1f$",(ismu)?muErr[12]:eleErr[12])
	+ " & " + Form("$%2.1f$",(ismu)?muErr[5]:eleErr[5])
	+ " & " + Form("$%2.1f$",(ismu)?muErr[6]:eleErr[6])
	+ " & " + Form("$%2.1f$",(ismu)?muErr[7]:eleErr[7])
	+ " & " + Form("$%2.1f$",(ismu)?muErr[8]:eleErr[8])
	+ " & " + Form("$%2.1f$",(ismu)?muErr[9]:eleErr[9])
	+ " & " + "--"
	+ " & " + "--"
	+ " & " + "--"
	+ " & " + Form("$%2.1f$",(ismu)?norm_m:norm_e)
	+ " & " + Form("$%2.1f$",(ismu)?muErr[18]:eleErr[18])
	+"\\\\";      
    }
  }else{
    combined = string(" & ") + rowtitle 
      + " & " + "--"
      + " & " + "--"
      + " & " + "--"
      + " & " + "--"
      + " & " + "--"
      + " & " + "--"
      + " & " + "--"
      + " & " + "--"
      + " & " + "--"
      + " & " + "--"
      + " & " + "--"
      + " & " + "--"
      + " & " + "--"
      + " & " + "--"
      + " & " + "--"
      + " & " + "--"
      + " & " + "--"
      + " & " + "--"
      + " & " + "--"
      + " & " + "--"
      + " & " + Form("$%2.1f$",(ismu)?qcd_m:qcd_e)
      + " & " + Form("$%2.1f$",(ismu)?qcdstat_m:qcdstat_e)
      +"\\\\";
  }
  
  //cout << combined << endl;
  
  return combined;
}

string GetInclusive(string rowtitle, int ifile, bool inc, int year, bool isKFL, bool isInc, char cType, double *muTot, double *eleTot)
{
  int CalcSystTable(int ifile, bool isMu, double output[], double error_percnt[], double error_percntH[], int year, bool isKFL, bool isIncl, char cType);
  
  const int  nofSyst = 20;
  double muOut[3];
  double eleOut[3];
  double error_percnt[23]; //nofSyst + stat
  double error_percntH[23]; //nofSyst + stat

  cout<<"Inclusive sample " << sampleType[ifile-1] <<", RowTitle : " << rowtitle << endl;
  string sampleName = sampleType[ifile-1];

  for(int i=0;i<23;i++) error_percnt[i] = error_percntH[i] = 0.0 ;
  for(int i=0;i<3;i++) muOut[i] = eleOut[i] = 0.0 ;
  CalcSystTable(ifile, 1, muOut, error_percnt, error_percntH, year, isKFL, isInc, cType);
  ifile = (inc) ? ifile+1 : ifile ;
  for(int i=0;i<23;i++) error_percnt[i] = error_percntH[i] = 0.0 ;
  CalcSystTable(ifile, 0, eleOut, error_percnt, error_percntH, year, isKFL, isInc, cType);  
  
  string combined = "";
  
  // if(rowtitle.find("All")==string::npos){
  //   if(rowtitle == "Data" or rowtitle == "MC QCD"){
  //     combined = rowtitle +" & "+ Form("$%1.0f \\pm %1.0f(%1.1f\\%)$",muOut[0],muOut[1],100.*muOut[1]/muOut[0]) 
  // 	+" & "+ Form("$%1.0f \\pm %1.0f(%1.1f\\%)$",eleOut[0],eleOut[1],100.*eleOut[1]/eleOut[0]) +"\\\\";
  //   }else if(rowtitle == "Data/Bkg"){
  //     combined = rowtitle +" & "+ Form("$%5.4f$",muOut[0]/muTot[0]) 
  // 	+" & "+ Form("$%5.4f$",eleOut[0]/eleTot[0]) +"\\\\";      
  //   }else{
  //     combined = rowtitle +" & "+ Form("$%1.0f \\pm %1.0f(%1.1f\\%) \\pm %1.0f(%1.1f\\%)$",muOut[0],muOut[1],100.*muOut[1]/muOut[0],muOut[2],100.*muOut[2]/muOut[0]) 
  // 	+" & "+ Form("$%1.0f \\pm %1.0f(%1.1f\\%) \\pm %1.0f(%1.1f\\%)$",eleOut[0],eleOut[1],100.*eleOut[1]/eleOut[0],eleOut[2],100.0*eleOut[2]/eleOut[0]) +"\\\\";
  //   }
  // }else{
  //   combined = rowtitle +" & "+ Form("$%1.0f \\pm %1.0f(%1.1f\\%) \\pm %1.0f(%1.1f\\%)$",muTot[0],sqrt(muTot[1]),100.*sqrt(muTot[1])/muTot[0],sqrt(muTot[2]),100.*sqrt(muTot[2])/muTot[0]) 
  //     +" & "+ Form("$%1.0f \\pm %1.0f(%1.1f\\%) \\pm %1.0f(%1.1f\\%)$",eleTot[0],sqrt(eleTot[1]),100.*sqrt(eleTot[1])/eleTot[0],sqrt(eleTot[2]),100.0*sqrt(eleTot[2])/eleTot[0]) +"\\\\";    
  // }
  
  // if(rowtitle.find("All")==string::npos){
  //   if(rowtitle == "Data" or rowtitle == "MC QCD"){
  //     combined = rowtitle +" & "+ Form("$%1.0f \\pm %1.0f$",muOut[0],muOut[1]) 
  // 	+" & "+ Form("$%1.0f \\pm %1.0f$",eleOut[0],eleOut[1]) ;//+"\\\\";
  //   }else if(rowtitle == "Data/Bkg"){
  //     combined = rowtitle +" & "+ Form("$%5.4f$",muOut[0]/muTot[0]) 
  // 	+" & "+ Form("$%5.4f$",eleOut[0]/eleTot[0]) ;//+"\\\\";      
  //   }else{
  //     combined = rowtitle +" & "+ Form("$%1.0f \\pm %1.0f$",muOut[0],TMath::Sqrt(muOut[1]*muOut[1] + muOut[2]*muOut[2])) 
  // 	+" & "+ Form("$%1.0f \\pm %1.0f$",eleOut[0],TMath::Sqrt(eleOut[1]*eleOut[1] + eleOut[2]*eleOut[2])) ;//+"\\\\";
  //   }
  // }else{
  //   if(rowtitle.size()>4)
  //     combined = rowtitle +" & "+ Form("$%1.0f \\pm %1.0f$",muTot[0],TMath::Sqrt(muTot[1] + muTot[2])) 
  // 	+" & "+ Form("$%1.0f \\pm %1.0f$",eleTot[0],TMath::Sqrt(eleTot[1] + eleTot[2])) ;//+"\\\\";
  //   else
  //     combined = string(" & ")+ Form("$%1.0f \\pm %1.0f$",muTot[0],TMath::Sqrt(muTot[1] + muTot[2])) 
  // 	+" & "+ Form("$%1.0f \\pm %1.0f$",eleTot[0],TMath::Sqrt(eleTot[1] + eleTot[2])) ;//+"\\\\";
  // }

  if(rowtitle.find("All")==string::npos){
    if(rowtitle == "Data" or rowtitle == "MC QCD"){
      combined = rowtitle +" & "+ Form("$%1.0f \\pm %1.0f$",muOut[0],muOut[1]) 
  	+" & "+ Form("$%1.0f \\pm %1.0f$",eleOut[0],eleOut[1]) ;
    }else if(rowtitle == "Data/Bkg"){
      combined = rowtitle +" & "+ Form("$%5.4f$",muOut[0]/muTot[0]) 
  	+" & "+ Form("$%5.4f$",eleOut[0]/eleTot[0]) ;
    }else{
      combined = rowtitle +" & "+ Form("$%1.0f \\pm %1.0f \\pm %1.0f$",muOut[0],muOut[1],muOut[2]) 
  	+" & "+ Form("$%1.0f \\pm %1.0f \\pm %1.0f$",eleOut[0],eleOut[1],eleOut[2]) ;
    }
  }else{
    combined = rowtitle +" & "+ Form("$%1.0f \\pm %1.0f \\pm %1.0f$",muTot[0],sqrt(muTot[1]),sqrt(muTot[2])) 
      +" & "+ Form("$%1.0f \\pm %1.0f \\pm %1.0f$",eleTot[0],sqrt(eleTot[1]),sqrt(eleTot[2])) ;
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

int CalcSystTable(int isample, bool isMu, double output[], double error_percnt[], double error_percntH[], int year, bool isKFL = false, bool isIncl = true, char cType = 'L')
{
  
  int PlotRatio(TH1D *h1, TH1D *h2, const char *cname);
  double CalcSysError(TH1D *, TH1D *, TH1D *);
  double CalcShapeError(TH1D *, TH1D *, TH1D *, double&, double&);
  
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
				// 6.1, 6.1, 6.1, 6.1,
				// 6.1, 6.1, 6.1, 6.1,
				// 6.1, 6.1,
                                6.1, 7.0, 4.5, 5.0, 4.0,
                                10.};

  const float norm_ele_syst[] = {6.1, 6.1, 6.1, 6.1,
				 6.1, 6.1, 6.1, 6.1,
				 6.1, 6.1,
				 // 6.1, 6.1, 6.1, 6.1,
				 // 6.1, 6.1, 6.1, 6.1,
				 // 6.1, 6.1,
				 6.1, 7.0, 4.5, 5.0, 4.0,
				 10.};
  
  // const char *systDir[] = {"base", 
  // 			     "puup", "pudown", "mueffup", "mueffdown", 
  // 			     "eleeffup", "eleeffdown",  "jecup", "jecdown", 
  // 			     "jerup", "jerdown", "btagbup", "btagbdown", 
  // 			     "btaglup", "btagldown", "prefireup", "prefiredown",
  //                            "pdfup", "pdfdown", "q2fup", "q2down",
  // 			     "isrup", "isrdown", "fsrup", "fsrdown",
  //                            "bctag1up", "bctag1down", "bctag2up", "bctag2down",
  // 			     "bctag3up", "bctag3down"};
  // outFile<<"Process "
  
  // 	 <<"& {\\rotatebox{90}{Pileup} } & {\\rotatebox{90}{Lepton }} & {\\rotatebox{90}{Prefire }} & {\\rotatebox{90}{JES}  } & { \\rotatebox{90}{JER}  } "
  // 	 <<"& {\\rotatebox{90}{PDF}}  & {\\rotatebox{90}{Renormalization}}  & { \\rotatebox{90}{Factorization} } & { \\rotatebox{90}{ISR} } & { \\rotatebox{90}{FSR} } "
  // 	 <<"& {\\rotatebox{90}{PU JetID}}  & { \\rotatebox{90}{b\\&c tagging Interpolation} } & { \\rotatebox{90}{b\\&c tagging Extrapolation} } & {\\rotatebox{90}{b\\&c tagging XS DY-b}} & {\\rotatebox{90}{b\\&c tagging XS DY-c}}   "
  // 	 <<"& { \\rotatebox{90}{b\\&c tagging XS Wjet-c} } & { \\rotatebox{90}{b\\&c tagging statistics} } &  { \\rotatebox{90}{Normalization} }  & {\\rotatebox{90}{Statistical}  }  \\\\ "
  // 	 <<""<<endl;
  
  const char *systDir[] = {"base",
			   "puup", "pudown", "mueffup", "mueffdown",                    //2,4
			   "eleeffup", "eleeffdown", "prefireup", "prefiredown",        //6,8
			   "jecup", "jecdown", "jerup", "jerdown",                      //10,12,
			   "pdfup", "pdfdown", "q2up", "q2down",                        //14,16
			   "bclhemurup", "bclhemurdown", "bclhemufup", "bclhemufdown",  //18,20
			   "isrup", "isrdown", "fsrup", "fsrdown",                      //22,24
			   "pujetidup", "pujetiddown", "bcintpup", "bcintpdown",        //26,28
			   "bcextpup", "bcextpdown", "bcxdybup", "bcxdybdown",          //30.32
			   "bcxdycup", "bcxdycdown", "bcxwjcup", "bcxwjcdown",          //34.36
			   "bcstatup", "bcstatdown",                                    //38
			   "cp5up", "cp5down","mtopup", "mtopdown", "hdampup", "hdampdown" //40,42,44
  };
  const char *systname[] = {"base",
			   "puup", "pudown", "mueffup", "mueffdown",                    //2,4
			   "eleeffup", "eleeffdown", "prefireup", "prefiredown",        //6,8
			   "jecup", "jecdown", "jerup", "jerdown",                      //10,12,
			   "pdfup", "pdfdown", "q2up", "q2down",                        //14,16
			   "bclhemurup", "bclhemurdown", "bclhemufup", "bclhemufdown",  //18,20
			   "isrup", "isrdown", "fsrup", "fsrdown",                      //22,24
			   "pujetidup", "pujetiddown", "bcintpup", "bcintpdown",        //26,28
			   "bcextpup", "bcextpdown", "bcxdybup", "bcxdybdown",          //30.32
			   "bcxdycup", "bcxdycdown", "bcxwjcup", "bcxwjcdown",          //34.36
			   "bcstatup", "bcstatdown",                                    //38
			   "cp5up", "cp5down","mtopup", "mtopdown", "hdampup", "hdampdown" //40,42,44
  };
  
  //const char *inputdir = "/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/grid_v39_Syst/CBA_KFNewReso" ;
  //const char *inputdir = "/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/grid_v39_Syst/CBA_1718_Resubmit" ;
  //const char *inputdir = "/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/grid_v39_Syst/CBA_CTagM" ;
  //const char *inputdir = "/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/grid_v39_Syst/CBA_GeneratorWt" ;
  //const char *inputdir = "/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/grid_v39_Syst/CBA_CTagDD" ;
  //const char *inputdir = "/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/grid_v40_Syst/CBA_ctagv2-CombHist" ;
  //const char *inputdir = "/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/grid_v40_Syst/CBA_muFmuR-Hist" ;
  //const char *inputdir = "/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/grid_v40_Syst/CBA_elemva80-CombHist" ;
  const char *inputdir = "/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/grid_v40_Syst/CBA_elereliso-CombHist" ;
  //const char *inputdir = "/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/grid_v40_Syst/CBA_elereliso20-CombHist" ;
  //const char *inputdir = "/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/grid_v40_Syst/CBA_elereliso30-CombHist" ;
  
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

  // 	 <<"& {\\rotatebox{90}{Pileup} } & {\\rotatebox{90}{Lepton }} & {\\rotatebox{90}{Prefire }} & {\\rotatebox{90}{JES}  } & { \\rotatebox{90}{JER}  } "
  // 	 <<"& {\\rotatebox{90}{PDF}}  & {\\rotatebox{90}{Renormalization}}  & { \\rotatebox{90}{Factorization} } & { \\rotatebox{90}{ISR} } & { \\rotatebox{90}{FSR} } "
  // 	 <<"& {\\rotatebox{90}{PU JetID}}  & { \\rotatebox{90}{b\\&c tagging Interpolation} } & { \\rotatebox{90}{b\\&c tagging Extrapolation} } & {\\rotatebox{90}{b\\&c tagging XS DY-b}} & {\\rotatebox{90}{b\\&c tagging XS DY-c}}   "
  // 	 <<"& { \\rotatebox{90}{b\\&c tagging XS Wjet-c} } & { \\rotatebox{90}{b\\&c tagging statistics} } &  { \\rotatebox{90}{Normalization} }  & {\\rotatebox{90}{Statistical}  }  \\\\ "
  // 	 <<""<<endl;

  // const char *systDir[] = {"base",
  // 			   "puup", "pudown", "mueffup", "mueffdown",                    //2,4
  // 			   "eleeffup", "eleeffdown", "prefireup", "prefiredown",        //6,8
  // 			   "jecup", "jecdown", "jerup", "jerdown",                      //10,12,
  // 			   "pdfup", "pdfdown", "q2up", "q2down",                        //14,16
  // 			   "bclhemurup", "bclhemurdown", "bclhemufup", "bclhemufdown",  //18,20
  // 			   "isrup", "isrdown", "fsrup", "fsrdown",                      //22,24
  // 			   "pujetidup", "pujetiddown", "bcintpup", "bcintpdown",        //26,28
  // 			   "bcextpup", "bcextpdown", "bcxdybup", "bcxdybdown",          //30.32
  // 			   "bcxdycup", "bcxdycdown", "bcxwjcup", "bcxwjcdown",          //34.36
  // 			   "bcstatup", "bcstatdown",                                    //38
  // 			   "cp5up", "cp5down","mtopup", "mtopdown", "hdampup", "hdampdown" //40,42,44
  // };
  
  // const int  nofSyst = 9;
  // const int  sysidlistMu[nofSyst] = {2, 4, 26, 28, 30, 16, 8, 10, 10};
  // const int  sysidlistEle[nofSyst] = {2, 6, 26, 28, 30, 16, 8, 10, 10};
  // double error[nofSyst];
  // double error_percent[nofSyst];
  
  // const int nSystGroups = 9 ; //pileup, lepton, btag-b, btag-l, prefire, jec, jer, normalization
  // //const char*  syst_group_name[] = {"Pileup", "Lepton", "btag-b", "btag-l", "Prefire", "JEC", "JER", "Norm"};
  // const char*  syst_group_name[] = {"Pileup", "Lepton", "b & c tagging-1", "b & c tagging-2", "b & c tagging-3", "Prefire", "JEC", "JER", "Norm"};
  
  const int  nofSyst = 21;
  const int  nofSystL = 18;
  int  sysidlistMu[nofSyst] = {2, 4, 8, 10, 12, 14, 18, 20, 22, 24, 26, 28, 30, 32, 34, 36, 38, 40, 42, 44, 44};
  int  sysidlistEle[nofSyst] = {2, 6, 8, 10, 12, 14, 18, 20, 22, 24, 26, 28, 30, 32, 34, 36, 38, 40, 42, 44, 44};
  int  sysidlistMuL[nofSystL] = {2, 4, 8, 10, 12, 14, 18, 20, 22, 24, 26, 28, 30, 32, 34, 36, 38, 38};
  int  sysidlistEleL[nofSystL] = {2, 6, 8, 10, 12, 14, 18, 20, 22, 24, 26, 28, 30, 32, 34, 36, 38, 38};

  double error[nofSyst];
  double error_percent[nofSyst];
  
  const int nSystGroups = 21 ; 
  const char*  syst_group_name[] = {"Pileup", "Lepton", "Prefire", "JES", "JER",
				    "PDF", "Renorm", "Facto", "ISR", "FSR",
				    "PU JetID", "bc interp", "bc extrap", "bc dyb", "bc dyc",
				    "bc wjetc", "bc stat",
				    "cp5", "mtop", "hdamp", "Norm"};
  
  double syst_Error[nSystGroups];

  double syst_Error_Percent[nSystGroups];

  int isyst = 0;
  double totSys = 0.0;
  
  double stat_Error = 0.0;
  //double Norm = hBase->IntegralAndError(1,hBase->GetNbinsX(),stat_Error);
  if(baseFileName.find("all_QCDdd")==string::npos)
    hBase->Rebin(50);
  double minBin = hBase->GetXaxis()->FindBin(20.0);
  double maxBin = hBase->GetXaxis()->FindBin(160.0);
  double Norm = hBase->IntegralAndError(minBin,maxBin,stat_Error); 
  double stat_Error_iso20 = 0.0;
  double Norm_iso20 = 0.0;
  if(baseFileName.find("all_QCDdd")!=string::npos){
    double getSysUncQcd(bool isMu, TFile* fData, TFile* fTT, TFile* fST, TFile* fWJ, TFile* fDY, TFile* fVV, TString histDir, TString histName, bool isUncSF, double Norm, double& Norm_iso20);
    TString histName = "";
    if(isKFL)
      histName = (isMu) ? Form("_kb_mjj_mu") : Form("_kb_mjj_ele")  ;
    else{
      if(isIncl){
	if(cType=='L')
	  histName = (isMu) ? Form("_ct_IncL_mjj_mu") : Form("_ct_IncL_mjj_ele")  ;
	else if(cType=='M')
	  histName = (isMu) ? Form("_ct_IncM_mjj_mu") : Form("_ct_IncM_mjj_ele")  ;
	else if(cType=='T')
	  histName = (isMu) ? Form("_ct_IncT_mjj_mu") : Form("_ct_IncT_mjj_ele")  ;
      }else{
	if(cType=='L')
	  histName = (isMu) ? Form("_ct_ExcL_mjj_mu") : Form("_ct_ExcL_mjj_ele")  ;
	else if(cType=='M')
	  histName = (isMu) ? Form("_ct_ExcM_mjj_mu") : Form("_ct_ExcM_mjj_ele")  ;
	else if(cType=='T')
	  histName = (isMu) ? Form("_ct_ExcT_mjj_mu") : Form("_ct_ExcT_mjj_ele")  ;
      }//incl or excl
    }//ctag level

    
    const char* datafile = (isMu) ? Form("%s/%d/all_DataMu.root",inputdir,year) : Form("%s/%d/all_DataEle.root",inputdir,year);
    TFile *fData	= TFile::Open(datafile);
    TFile *fTT = TFile::Open(Form("%s/%d/all_TTbar.root",inputdir,year));
    TFile *fST	= TFile::Open(Form("%s/%d/all_singleTop.root",inputdir,year));
    TFile *fWJ	= TFile::Open(Form("%s/%d/all_Wjets.root",inputdir,year));
    TFile *fDY = TFile::Open(Form("%s/%d/all_DYjets.root",inputdir,year));
    TFile *fVV	= TFile::Open(Form("%s/%d/all_VBFusion.root",inputdir,year));
    
    getSysUncQcd(isMu, fData, fTT, fST, fWJ, fDY, fVV, "", histName, false, Norm, Norm_iso20);
    
  }
  if(baseFileName.find("all_Data")!=string::npos)
    Norm_iso20 = hIso20->IntegralAndError(1,hIso20->GetNbinsX(),stat_Error_iso20); 

  //The following line is for DD row.
  //if(isample>=13){
  if(baseFileName.find("all_QCDdd")!=string::npos or baseFileName.find("all_Data")!=string::npos or baseFileName.find("all_MCQCD")!=string::npos){
  //if(isample>=13){
    output[0] = Norm;
    output[1] = stat_Error ;
    if(baseFileName.find("all_QCDdd")!=string::npos){
      output[2] = TMath::Abs(Norm-Norm_iso20) ;
      cout<<"all_QCDdd :: Norm : " << Norm <<", Norm_iso20 : " << Norm_iso20 << endl;
    }else{
      output[2] = 0 ;
    }
    return true;
  }

  int totSyst = nofSyst ;
  if(baseFileName.find("all_TTbar")==string::npos)
    totSyst = nofSystL;
  
  if(isVerbose)
    cout << "isample : " << isample << ", Processing for : "<<sample[isample] << ", nof Syst : " << totSyst << endl;
  
  for(int idx = 0 ; idx < totSyst ; idx++){
    
    int isysup = (isMu) ? sysidlistMu[idx] : sysidlistEle[idx] ;
    if(baseFileName.find("all_TTbar")==string::npos)
      isysup = (isMu) ? sysidlistMuL[idx] : sysidlistEleL[idx] ;
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
    if(baseFileName.find("all_QCDdd")==string::npos and idx<(totSyst-1)){
      hSysDown->Rebin(50);
      hSysUp->Rebin(50);
    }
    error[idx] = CalcSysError(hSysUp, hBase, hSysDown);
    
    if(idx<(totSyst-1)){
      error_percent[idx] = 100.*error[idx]/Norm ;
    }else{ // This is only for normalization which is predefined
      cout<<"Normalization index : " << idx << endl;
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
  error_percnt[totSyst] = 100.*stat_Error/Norm;
  
  //////////////////////////////////////////////////////
  //// The following lines for testing only//////////////
  syst_Error[isyst] = 0;
  for(int idx = 6 ; idx < totSyst ; idx++){
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
  // double valUp    = hSysUp->Integral();
  // double valBase  = hBase->Integral();
  // double valDown  = hSysDown->Integral();
  
  double valUp    = hSysUp->Integral(hSysUp->GetXaxis()->FindBin(20.0), hSysUp->GetXaxis()->FindBin(160.0));
  double valBase  = hBase->Integral(hBase->GetXaxis()->FindBin(20.0), hBase->GetXaxis()->FindBin(160.0));
  double valDown  = hSysDown->Integral(hSysDown->GetXaxis()->FindBin(20.0), hSysDown->GetXaxis()->FindBin(160.0));


  double sys = TMath::Max(fabs(valUp - valBase), fabs(valBase - valDown));

  return sys;
}

double CalcShapeError(TH1D *hSysUp, TH1D *hBase, TH1D *hSysDown, double& minSyst, double &maxSyst)
{
  // double valUp    = hSysUp->Integral();
  // double valBase  = hBase->Integral();
  // double valDown  = hSysDown->Integral();
  
  double valUp    = hSysUp->Integral(hSysUp->GetXaxis()->FindBin(20.0), hSysUp->GetXaxis()->FindBin(160.0));
  double valBase  = hBase->Integral(hBase->GetXaxis()->FindBin(20.0), hBase->GetXaxis()->FindBin(160.0));
  double valDown  = hSysDown->Integral(hSysDown->GetXaxis()->FindBin(20.0), hSysDown->GetXaxis()->FindBin(160.0));


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


// qcd SF for data-driven QCD

TH1F* getHisto(TFile *inRootFile, TString histPath, TString histName){
  TH1F* hist;
  TString fullPath = histPath+histName;
  //cout<<"\n inRootFile : " << inRootFile->GetName() << "\n histPath : " << histPath << ", histName : " << histName  <<"\n fullPath : " << fullPath << endl;
  string exception_msg (inRootFile->GetName()+TString("/")+fullPath+", does not exist");
  try{
    if(!(inRootFile->Get(fullPath)))
      throw  exception_msg.c_str();
  }catch (const char *e){
    cout<<"WARNING:"<<e<<endl;
  }

  hist = (TH1F*)(inRootFile->Get(fullPath))->Clone(histName);
  
  return hist;
}

//double MyHPlusDataCardMakerNano::getQcdSF(bool isMu, TString baseDir, TFile* fData, TFile* fTT, TFile* fST, TFile* fWJ, TFile* fDY, TFile* fVV, TString histDir, TString histName){
double getQcdSF(bool isMu, TString baseDir, TFile* fData, TFile* fTT, TFile* fST, TFile* fWJ, TFile* fDY, TFile* fVV, TString histDir, TString histName){
  //RegionC = LowMET, NonIso
  TH1F* hVV_RegC = getHisto(fVV,   "VBFusion/"+baseDir+"/NonIsoLowMET/" , histName+"_noniso_lmet");
  TH1F* hDY_RegC = getHisto(fDY,   "DYjets/"+baseDir+"/NonIsoLowMET/" , histName+"_noniso_lmet");
  TH1F* hWJ_RegC = getHisto(fWJ,   "Wjets/"+baseDir+"/NonIsoLowMET/" , histName+"_noniso_lmet");
  TH1F* hST_RegC = getHisto(fST,   "singleTop/"+baseDir+"/NonIsoLowMET/" , histName+"_noniso_lmet");
  TH1F* hTT_RegC = getHisto(fTT,   "TTbar/"+baseDir+"/NonIsoLowMET/" , histName+"_noniso_lmet");
  TH1F* hMC_RegC = (TH1F*)hVV_RegC->Clone("hAllMC_RegC");
  hMC_RegC->Add(hDY_RegC);
  hMC_RegC->Add(hWJ_RegC);
  hMC_RegC->Add(hST_RegC);
  hMC_RegC->Add(hTT_RegC);
  TH1F* hData_RegC = (isMu) ? getHisto(fData, "DataMu/"+baseDir+"/NonIsoLowMET/", histName+"_noniso_lmet") : getHisto(fData, "DataEle/"+baseDir+"/NonIsoLowMET/", histName+"_noniso_lmet");
  
  //RegionD = LowMET, Iso
  TH1F* hVV_RegD = getHisto(fVV,   "VBFusion/"+baseDir+"/LowMET/" , histName+"_lmet");
  TH1F* hDY_RegD = getHisto(fDY,   "DYjets/"+baseDir+"/LowMET/" , histName+"_lmet");
  TH1F* hWJ_RegD = getHisto(fWJ,   "Wjets/"+baseDir+"/LowMET/" , histName+"_lmet");
  TH1F* hST_RegD = getHisto(fST,   "singleTop/"+baseDir+"/LowMET/" , histName+"_lmet");
  TH1F* hTT_RegD = getHisto(fTT,   "TTbar/"+baseDir+"/LowMET/" , histName+"_lmet");
  TH1F* hMC_RegD = (TH1F*)hVV_RegD->Clone("hAllMC_RegD");
  hMC_RegD->Add(hDY_RegD);
  hMC_RegD->Add(hWJ_RegD);
  hMC_RegD->Add(hST_RegD);
  hMC_RegD->Add(hTT_RegD);
  TH1F* hData_RegD=  (isMu) ? getHisto(fData, "DataMu/"+baseDir+"/LowMET/", histName+"_lmet") : getHisto(fData, "DataEle/"+baseDir+"/LowMET/", histName+"_lmet");
  
  TH1F* hDiffC = (TH1F*)hData_RegC->Clone("hDiffC");
  hDiffC->Add(hMC_RegC, -1);
  //If binContent < 0, set it to 0
  for(int ibin=1; ibin<hDiffC->GetNbinsX(); ibin++){
    double binCont = hDiffC->GetBinContent(ibin);
    if(binCont<0){
      hDiffC->SetBinContent(ibin, 0);
      //hDiffC->SetBinError(ibin, 0);
    }
  }
  TH1F* hDiffD = (TH1F*)hData_RegD->Clone("hDiffD");
  hDiffD->Add(hMC_RegD, -1);
  for(int ibin=1; ibin<hDiffD->GetNbinsX(); ibin++){
    double binCont = hDiffD->GetBinContent(ibin);
    if(binCont<0){
      hDiffD->SetBinContent(ibin, 0);
      //hDiffD->SetBinError(ibin, 0);
    }
  }
  double intDiffC   = hDiffC->Integral();
  double intDiffD   = hDiffD->Integral();
  double ratioDiffDC = intDiffD/intDiffC;
  return ratioDiffDC;
}

//double MyHPlusDataCardMakerNano::getQcdDD(bool isMu, TString baseDir, TFile* fData, TFile* fTT, TFile* fST, TFile* fWJ, TFile* fDY, TFile* fVV, TString histDir, TString histName, double qcd_sf=1.0){
double getQcdDD(bool isMu, TString baseDir, TFile* fData, TFile* fTT, TFile* fST, TFile* fWJ, TFile* fDY, TFile* fVV, TString histDir, TString histName, double qcd_sf=1.0){
  /* TH1F* hVV = getHisto(fVV,   baseDir+"/NonIso/"+histDir, histName, fTT); */
  /* TH1F* hDY = getHisto(fDY,   baseDir+"/NonIso/"+histDir, histName, fTT); */
  /* TH1F* hWJ = getHisto(fWJ,   baseDir+"/NonIso/"+histDir, histName, fTT); */
  /* TH1F* hST = getHisto(fST,   baseDir+"/NonIso/"+histDir, histName, fTT); */
  /* TH1F* hTT = getHisto(fTT,   baseDir+"/NonIso/"+histDir, histName, fTT); */
  /* TH1F* hData= getHisto(fData, baseDir+"/NonIso/"+histDir, histName, fTT); */
  
  TH1F* hVV = getHisto(fVV,   "VBFusion/"+baseDir+"/NonIso/" , histName+"_noniso");
  TH1F* hDY = getHisto(fDY,   "DYjets/"+baseDir+"/NonIso/", histName+"_noniso");
  TH1F* hWJ = getHisto(fWJ,   "Wjets/"+baseDir+"/NonIso/", histName+"_noniso");
  TH1F* hST = getHisto(fST,   "singleTop/"+baseDir+"/NonIso/", histName+"_noniso");
  TH1F* hTT = getHisto(fTT,   "TTbar/"+baseDir+"/NonIso/", histName+"_noniso");
  TH1F* hData= (isMu) ? getHisto(fData,"DataMu/"+baseDir+"/NonIso/", histName+"_noniso") : getHisto(fData,"DataEle/"+baseDir+"/NonIso/", histName+"_noniso");
  
  TH1F* hOtherMC = (TH1F*)hVV->Clone("hOtherMC");
  hOtherMC->Add(hDY);
  hOtherMC->Add(hST);
  hOtherMC->Add(hWJ);
  hOtherMC->Add(hTT);
  
  TH1F* hQCD = (TH1F*)hData->Clone(histName+"_noniso");
  hQCD->Add(hOtherMC, -1);
  //If binContent < 0, set it to 0
  for(int ibin=1; ibin<hQCD->GetNbinsX(); ibin++){
    double binCont = hQCD->GetBinContent(ibin);
    if(binCont<0){
      hQCD->SetBinContent(ibin, 0);
      //hQCD->SetBinError(ibin, 0);
    }
  }
  hQCD->Scale(qcd_sf);
  return hQCD->Integral();
}

//double MyHPlusDataCardMakerNano::getSysUncQcd(bool isMu, TFile* fData, TFile* fTT, TFile* fST, TFile* fWJ, TFile* fDY, TFile* fVV, TString histDir, TString histName, bool isUncSF){
double getSysUncQcd(bool isMu, TFile* fData, TFile* fTT, TFile* fST, TFile* fWJ, TFile* fDY, TFile* fVV, TString histDir, TString histName, bool isUncSF, double Norm, double& Norm_iso20){

  double sf_baseIsoDir = getQcdSF(isMu, "base", fData, fTT, fST, fWJ, fDY, fVV, histDir, histName);
  double qcd_baseIsoDir = getQcdDD(isMu, "base", fData, fTT, fST, fWJ, fDY, fVV, histDir, histName, sf_baseIsoDir);
  double sf_baseShiftedIsoDir = getQcdSF(isMu, "iso20", fData, fTT, fST, fWJ, fDY, fVV, histDir, histName);
  double qcd_baseShiftedIsoDir = getQcdDD(isMu, "iso20", fData, fTT, fST, fWJ, fDY, fVV, histDir, histName, sf_baseShiftedIsoDir);

  double sf_unc = abs(sf_baseIsoDir - sf_baseShiftedIsoDir)/sf_baseIsoDir;
  //double qcd_unc = sysSF* abs(qcd_baseIsoDir - qcd_baseShiftedIsoDir)/qcd_baseIsoDir;
  double qcd_unc = abs(qcd_baseIsoDir - qcd_baseShiftedIsoDir)/qcd_baseIsoDir;
  cout<<"-------------------------------------"<<endl;
  cout<<"sf_baseIsoDir 	      = "<<sf_baseIsoDir<<endl;
  cout<<"sf_baseShiftedIsoDir = "<<sf_baseShiftedIsoDir<<endl;
  cout<<"sf_unc               = "<<sf_unc<<endl;
  cout<<"qcd_baseIsoDir 	   = "<<qcd_baseIsoDir<<endl;
  cout<<"qcd_baseShiftedIsoDir = "<<qcd_baseShiftedIsoDir<<endl;
  cout<<"qcd_unc               = "<<qcd_unc<<endl;
  cout<<"-------------------------------------"<<endl;
  if((qcd_baseIsoDir - qcd_baseShiftedIsoDir)>0)
    Norm_iso20 = Norm*(1.0 - qcd_unc);
  else
    Norm_iso20 = Norm*(1.0 + qcd_unc);
  double unc = 0.0;
  if(isUncSF) unc = sf_unc;
  else unc = qcd_unc;
  return 1+unc;
}
