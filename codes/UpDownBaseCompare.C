/**********************************************************************
 Created on : 12/09/2021
 Purpose    : Compare Up/Down with base
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

using namespace std;

int UpDownBaseCompare(int isMu = 1, int year = 2016, int isysup = 26){
  
  int PlotRatio(TH1D *h1, TH1D *h2, TH1D *h3, const char *cname);
  
  const char *samples[] = {"HplusM080", "HplusM090", "HplusM100", "HplusM140", 
			   "HplusM150", "HplusM155", "HplusM160", "HplusM120", 
			   "DataMu", "DataEle", "TTbar", "singleTop", 
			   "Wjets", "DYjets", "VBFusion", "MCQCDMu", 
			   "MCQCDEle"};
  
  const int nShapes = 0;
  const char* listShapes[] = {""};
  // const int nShapes = 13;
  // const char* listShapes[] = {"pdf", "q2", "isr", "fsr", //4
  // 			      //"bclhemuf", "bclhemur",
  // 			      "bcstat", "bcxdy",//8
  // 			      "bcxst", "bcxwj", "bcxtt", "bcbfrag",//12
  // 			      //"bcintp", "bcextp",
  // 			      "bcxdyb", "bcxdyc",//16
  //                             "bcwjc"}; //17

  // const int nShapes = 17;
  // const char* listShapes[] = {"pdf", "q2", "isr", "fsr", //4
  // 			      "bclhemuf", "bclhemur", "btagb", "btagl",//8
  // 			      "bctag1", "bctag2", "bctag3", "toppt",//12
  // 			      "hdamp", "mtop", "cp5", "jec",
  //                             "jer"}; //15



  // const char *syst_2016[] = {"base", 
  // 			     "pdfup", "pdfdown", "q2fup", "q2down",                        //2,4
  // 			     "isrup", "isrdown", "fsrup", "fsrdown",                       //6,8
  // 			     "puup", "pudown", "prefireup", "prefiredown",                 //10,12
  // 			     "mueffup", "mueffdown", "eleeffup", "eleeffdown",             //14,16
  // 			     "pujetidup", "pujetiddown", "metup", "metdown",               //18,20
  // 			     "jecup", "jecdown", "jerup", "jerdown",                       //22,24
  // 			     "bclhemufup", "bclhemufdown", "bclhemurup", "bclhemurdown",   //26,28
  // 			     "btagbup", "btagbdown", "btaglup", "btagldown",               //30,32
  // 			     "bctag1up", "bctag1down", "bctag2up", "bctag2down",           //34,36
  // 			     "bctag3up", "bctag3down", "topptup", "topptdown"};            //38,40
  
  const char *syst_2016[] = {"base", 
  			     "pdfup", "pdfdown", "q2up", "q2down",//2,4
  			     "isrup", "isrdown", "fsrup", "fsrdown",//6,8
  			     "puup", "pudown", "prefireup", "prefiredown",//10,12,
  			     "mueffup", "mueffdown", "eleeffup", "eleeffdown", //14,16
  			     "pujetidup", "pujetiddown", "metup", "metdown",//18,20
  			     "jecup", "jecdown", "jerup", "jerdown",//22,24
  			     // CShapeCalib EOY
  			     "bcstatup", "bcstatdown",//26
  			     "bclhemufup", "bclhemufdown", "bclhemurup", "bclhemurdown",//28,30
  			     "bcintpup", "bcintpdown", "bcextpup", "bcextpdown", //32,34
  			     "bcxdybup", "bcxdybdown", "bcxdycup", "bcxdycdown", //36,38
  			     "bcxwjcup", "bcxwjcdown",//40
  			     "cp5up", "cp5down","mtopup", "mtopdown", "hdampup", "hdampdown"//42,44,46
  };
  
  const char *syst_2017[] = {"base", 
  			     "pdfup", "pdfdown", "q2up", "q2down",//2,4
  			     "isrup", "isrdown", "fsrup", "fsrdown",//6,8
  			     "puup", "pudown", "prefireup", "prefiredown",//10,12,
  			     "mueffup", "mueffdown", "eleeffup", "eleeffdown", //14,16
  			     "pujetidup", "pujetiddown", "metup", "metdown",//18,20
  			     "jecup", "jecdown", "jerup", "jerdown",//22,24
  			     // CShapeCalib EOY
  			     "bcstatup", "bcstatdown",//26
  			     "bclhemufup", "bclhemufdown", "bclhemurup", "bclhemurdown",//28,30
  			     "bcintpup", "bcintpdown", "bcextpup", "bcextpdown", //32,34
  			     "bcxdybup", "bcxdybdown", "bcxdycup", "bcxdycdown", //36,38
  			     "bcxwjcup", "bcxwjcdown",//40
  			     "cp5up", "cp5down","mtopup", "mtopdown", "hdampup", "hdampdown"//42,44,46
  };  
  
  const char *syst_2018[] = {"base", 
  			     "pdfup", "pdfdown", "q2up", "q2down",//2,4
  			     "isrup", "isrdown", "fsrup", "fsrdown",//6,8
  			     "puup", "pudown", "prefireup", "prefiredown",//10,12,
  			     "mueffup", "mueffdown", "eleeffup", "eleeffdown", //14,16
  			     "pujetidup", "pujetiddown", "metup", "metdown",//18,20
  			     "jecup", "jecdown", "jerup", "jerdown",//22,24
  			     // CShapeCalib EOY
  			     "bcstatup", "bcstatdown",//26
  			     "bclhemufup", "bclhemufdown", "bclhemurup", "bclhemurdown",//28,30
  			     "bcintpup", "bcintpdown", "bcextpup", "bcextpdown", //32,34
  			     "bcxdybup", "bcxdybdown", "bcxdycup", "bcxdycdown", //36,38
  			     "bcxwjcup", "bcxwjcdown",//40
  			     "cp5up", "cp5down","mtopup", "mtopdown", "hdampup", "hdampdown"//42,44,46
  };

   // const char *syst_2016[] = {"base", 
   // 			      "pdfup", "pdfdown", "q2fup", "q2down",                        //2,4
   // 			      "isrup", "isrdown", "fsrup", "fsrdown",                       //6,8
   // 			      "puup", "pudown", "prefireup", "prefiredown",                 //10,12
   // 			      "mueffup", "mueffdown", "eleeffup", "eleeffdown",             //14,16
   // 			      "pujetidup", "pujetiddown", "metup", "metdown",               //18,20
   // 			      "jecup", "jecdown", "jerup", "jerdown",                       //22,24
   // 			      "bclhemufup", "bclhemufdown", "bclhemurup", "bclhemurdown",   //26,28
   // 			      "btagbup", "btagbdown", "btaglup", "btagldown",               //30,32
   // 			      "bctag1up", "bctag1down", "bctag2up", "bctag2down",           //34,36
   // 			      "bctag3up", "bctag3down", "topptup", "topptdown",             //38,40
   // 			      "cp5up", "cp5down","mtopup", "mtopdown",                      //42,44
   // 			      "hdampup", "hdampdown"};                                      //46
   // const char *syst_2017[] = {"base", 
   // 			      "pdfup", "pdfdown", "q2fup", "q2down",                        //2,4
   // 			      "isrup", "isrdown", "fsrup", "fsrdown",                       //6,8
   // 			      "puup", "pudown", "prefireup", "prefiredown",                 //10,12
   // 			      "mueffup", "mueffdown", "eleeffup", "eleeffdown",             //14,16
   // 			      "pujetidup", "pujetiddown", "metup", "metdown",               //18,20
   // 			      "jecup", "jecdown", "jerup", "jerdown",                       //22,24
   // 			      "bclhemufup", "bclhemufdown", "bclhemurup", "bclhemurdown",   //26,28
   // 			      "btagbup", "btagbdown", "btaglup", "btagldown",               //30,32
   // 			      "bctag1up", "bctag1down", "bctag2up", "bctag2down",           //34,36
   // 			      "bctag3up", "bctag3down", "topptup", "topptdown",             //38,40
   // 			      "cp5up", "cp5down","mtopup", "mtopdown",                      //42,44
   // 			      "hdampup", "hdampdown"};                                      //46
   // const char *syst_2018[] = {"base", 
   // 			      "pdfup", "pdfdown", "q2fup", "q2down",                        //2,4
   // 			      "isrup", "isrdown", "fsrup", "fsrdown",                       //6,8
   // 			      "puup", "pudown", "prefireup", "prefiredown",                 //10,12
   // 			      "mueffup", "mueffdown", "eleeffup", "eleeffdown",             //14,16
   // 			      "pujetidup", "pujetiddown", "metup", "metdown",               //18,20
   // 			      "jecup", "jecdown", "jerup", "jerdown",                       //22,24
   // 			      "bclhemufup", "bclhemufdown", "bclhemurup", "bclhemurdown",   //26,28
   // 			      "btagbup", "btagbdown", "btaglup", "btagldown",               //30,32
   // 			      "bctag1up", "bctag1down", "bctag2up", "bctag2down",           //34,36
   // 			      "bctag3up", "bctag3down", "topptup", "topptdown",             //38,40
   // 			      "cp5up", "cp5down","mtopup", "mtopdown",                      //42,44
   // 			      "hdampup", "hdampdown"};                                      //46


  //const char *inputdir = "/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/grid_v28_Syst/CBA_Skim_Syst" ;
  //const char *inputdir = "/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/grid_v30_Syst/CBA_Skim_Syst_MDPt" ;
  //const char *inputdir = "/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/grid_v39_Syst/CBA_CTagM" ;
  //const char *inputdir = "/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/grid_v39_Syst/CBA_CTagDD" ;
  //const char *inputdir = "/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/grid_v40_Syst/CBA_CTagnPUJetID" ;
  //const char *inputdir = "/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/grid_v40_Syst/CBA_Nom1_100MeVBin" ;
  //const char *inputdir = "/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/grid_v40_Syst/CBA_CTagValidated-Hist" ;
  
  //const char *inputdir = "/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/grid_v40_Syst/CBA_CTagReWt-Hist" ;
  //const char *inputdir = "/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/grid_v40_Syst/CBA_CTagReWt" ;
  //const char *inputdir = "/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/grid_v40_Syst/CBA_muFmuR" ;  
  //const char *inputdir = "/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/grid_v40_Syst/CBA_muFmuR-Hist" ;
  //const char *inputdir = "/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/grid_v40_Syst/CBA_elemva80-CombHist" ;
  //const char *inputdir = "/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/grid_v40_Syst/CBA_elereliso-CombHist" ;
  //const char *inputdir = "/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/grid_v40_Syst/CBA_yearend22" ;
  const char *inputdir = "/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/grid_v40_Syst/CBA_elereliso30-CombHist" ;


  int isample = 11; isample--; //11 for TTbar,  8  for HplusM120
  //int isample = 8; isample--; //11 for TTbar,  8  for HplusM120
  //int isample = 13; isample--; //11 for TTbar,  8  for HplusM120
  int ibase = 1; ibase--;
  int isysdown = isysup ;
  //int isysup = 2; 
  isysup--;

  string lep = (isMu==1) ? "mu" : "ele" ;
  const char *histname = Form("_kb_mjj_%s",lep.c_str());
  //const char *histname = Form("_ct_ExcT_mjj_%s",lep.c_str());
  
  // const char *histnameup = (isysup<=16) ? Form("%s",histname) :  Form("%s_%s",histname,syst_2016[isysup]) ;
  // const char *histnamedown = (isysdown<=17) ? Form("%s",histname) :  Form("%s_%s",histname,syst_2016[isysdown]) ;
  
  // vector<string> lstShps;
  // for(int i=0;i<nShapes;i++)
  //   lstShps.push_back(listShapes[i]);
  
  if(year==2016)
    cout << "sample : "<<samples[isample] << ", hisname : " << histname << ", ibase : "<<ibase << ", sysup : "<< syst_2016[isysup] << ", sysdown : " << syst_2016[isysdown] << endl;
  else if(year==2017)
    cout << "sample : "<<samples[isample] << ", hisname : " << histname << ", ibase : "<<ibase << ", sysup : "<< syst_2017[isysup] << ", sysdown : " << syst_2017[isysdown] << endl;
  else if(year==2018)
    cout << "sample : "<<samples[isample] << ", hisname : " << histname << ", ibase : "<<ibase << ", sysup : "<< syst_2018[isysup] << ", sysdown : " << syst_2018[isysdown] << endl;

  
  TFile *finBase = TFile::Open(Form("%s/%d/all_%s.root",inputdir,year,samples[isample])); 
  TH1D *hBase = 0x0;
  TH1D *hSysUp = 0x0;
  TH1D *hSysDown = 0x0;

  if(year==2016){
    hBase = (TH1D *)finBase->Get(Form("%s/base/Iso/%s",samples[isample],histname));
    hSysUp = (TH1D *)finBase->Get(Form("%s/%s/Iso/%s",samples[isample],syst_2016[isysup],histname));
    hSysDown = (TH1D *)finBase->Get(Form("%s/%s/Iso/%s",samples[isample],syst_2016[isysdown],histname));
  }else if(year==2017){
    hBase = (TH1D *)finBase->Get(Form("%s/base/Iso/%s",samples[isample],histname));
    hSysUp = (TH1D *)finBase->Get(Form("%s/%s/Iso/%s",samples[isample],syst_2017[isysup],histname));
    hSysDown = (TH1D *)finBase->Get(Form("%s/%s/Iso/%s",samples[isample],syst_2017[isysdown],histname));
  }else if(year==2018){
    hBase = (TH1D *)finBase->Get(Form("%s/base/Iso/%s",samples[isample],histname));
    hSysUp = (TH1D *)finBase->Get(Form("%s/%s/Iso/%s",samples[isample],syst_2018[isysup],histname));
    hSysDown = (TH1D *)finBase->Get(Form("%s/%s/Iso/%s",samples[isample],syst_2018[isysdown],histname));
  }
  
  
  // hBase->Sumw2();
  // hSysUp->Sumw2();
  // hSysDown->Sumw2();

  int rebin = 50;
  hBase->Rebin(rebin);
  hSysUp->Rebin(rebin);
  hSysDown->Rebin(rebin);

  bool isShape = false;
  TString histUp = hSysUp->GetDirectory()->GetMotherDir()->GetName();
  TString histDown = hSysDown->GetDirectory()->GetMotherDir()->GetName();
  
  for(int i=0;i<nShapes;i++)
    if(histUp.Contains(listShapes[i]) or histDown.Contains(listShapes[i])) isShape = true ;
  
  if(isShape){
    hSysUp->Scale(hBase->Integral()/hSysUp->Integral());
    hSysDown->Scale(hBase->Integral()/hSysDown->Integral());
    cout << "Using shape comparison " << endl;
  }
  
  Double_t error_frac = max(fabs(hSysUp->Integral() - hBase->Integral()), fabs(hBase->Integral() - hSysDown->Integral()))/hBase->Integral();
  TH1D *hRelErrUp = (TH1D *)hBase->Clone("hRelErrUp");
  TH1D *hRelErrDown = (TH1D *)hBase->Clone("hRelErrDown");
  for(int ibin=1; ibin<hRelErrUp->GetNbinsX(); ibin++){
    //cout<<"ibin : "<<ibin<<", Error Frac : "<<error_frac<<endl;
    hRelErrUp->SetBinContent(ibin, 1+error_frac);
    hRelErrUp->SetBinError(ibin, 0.1*error_frac);
    hRelErrDown->SetBinContent(ibin, 1.-error_frac);
    hRelErrDown->SetBinError(ibin, 0.1*error_frac);
  }
  hRelErrUp->SetTitle(Form("Max. Unc. %5.3lf",(1+error_frac)));
    
  hBase->SetLineColor(kRed);
  hSysUp->SetLineColor(kBlue);
  hSysDown->SetLineColor(kGreen+1);
  hRelErrUp->SetLineColor(kMagenta);
  hRelErrDown->SetLineColor(kMagenta);
    
  hBase->SetLineWidth(2);
  hSysUp->SetLineWidth(2);
  hSysDown->SetLineWidth(2);
  hRelErrUp->SetLineWidth(2);
  hRelErrDown->SetLineWidth(2);

  TLegend *leg = new TLegend(0.6729323,0.803838,0.9974937,0.9957356);
  leg->SetFillColor(10);
  //leg->SetHeader("m_{H^{+}} = 120 GeV, #mu + jets (2016)");
  //leg->SetHeader("m_{H^{+}} = 120 GeV, #it{e} + jets (2016)");
  leg->SetHeader(Form("%s : %s (%d)",samples[isample],histname,year));
  if(year==2016){
    leg->AddEntry(hSysUp, Form("%s",syst_2016[isysup]) ,"lfp");
    leg->AddEntry(hBase, Form("%s",syst_2016[ibase]) ,"lfp");
    leg->AddEntry(hSysDown, Form("%s",syst_2016[isysdown]) ,"lfp");
  }else if(year==2017){
    leg->AddEntry(hSysUp, Form("%s",syst_2017[isysup]) ,"lfp");
    leg->AddEntry(hBase, Form("%s",syst_2017[ibase]) ,"lfp");
    leg->AddEntry(hSysDown, Form("%s",syst_2017[isysdown]) ,"lfp");
  }else if(year==2018){
    leg->AddEntry(hSysUp, Form("%s",syst_2018[isysup]) ,"lfp");
    leg->AddEntry(hBase, Form("%s",syst_2018[ibase]) ,"lfp");
    leg->AddEntry(hSysDown, Form("%s",syst_2018[isysdown]) ,"lfp");
  }
  leg->AddEntry(hRelErrUp, Form("total uncertainty band") ,"lfp");
  if(isample==7)
    hSysUp->SetMaximum(1.2*hSysUp->GetBinContent(hSysUp->FindBin(120.0)));
  else
    hSysUp->SetMaximum(1.2*hSysUp->GetBinContent(hSysUp->FindBin(80.0)));
  hSysUp->SetTitle("");
  hSysUp->GetXaxis()->SetRangeUser(0.,170.);
  PlotRatio(hSysUp, hBase, hRelErrUp, "c1");
  PlotRatio(hSysDown, hBase, hRelErrDown, "c1");
  leg->Draw();
  
  TCanvas *c1 = (TCanvas *)gROOT->GetListOfCanvases()->FindObject("c1");
  if(year==2016){
    c1->SaveAs(Form("%s_%s_sys_%d.pdf",lep.c_str(),syst_2016[isysup],year));
  }else if(year==2017){
    c1->SaveAs(Form("%s_%s_sys_%d.pdf",lep.c_str(),syst_2017[isysup],year));
  }else if(year==2018){
    c1->SaveAs(Form("%s_%s_sys_%d.pdf",lep.c_str(),syst_2018[isysup],year));
  }
  
  c1->SaveAs("output.pdf");
  
  return true;
}

int PlotRatio(TH1D *h1, TH1D *h2, TH1D *hAvgErr, const char *cname)
{
  //cout<<"h1 name : "<<h1->GetName() <<", Directory : " << h1->GetDirectory()->GetMotherDir()->GetName() << endl;

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

    h3->Sumw2();
    h3->SetStats(0);      // No statistics on lower plot
    h3->Divide(h2);
    
    h3->SetMinimum(0.8);  // Define Y ..
    h3->SetMaximum(1.2); // .. range
    
    // cout << "h3->GetBinContent(h3->FindBin(80.0))" << h3->GetBinContent(h3->FindBin(80.0)) << endl;
    // h3->SetMaximum(1+2*(h3->GetBinContent(h3->FindBin(80.0))-1.));
    // h3->SetMinimum(1-2*(h3->GetBinContent(h3->FindBin(80.0))-1.));

    // float minX = 20.;
    // float maxX = 170.;
    // int minbinX = h3->FindBin(minX);
    // int maxbinX = h3->FindBin(maxX);
    // double integral = h3->Integral(minbinX,maxbinX);
    // double avgBinContent = integral/double(maxbinX-minbinX);
    // //cout << "Avg bin " << avgBinContent << endl;
    // h3->SetMaximum(1+1.2*(avgBinContent-1.));
    // h3->SetMinimum(1-1.2*(avgBinContent-1.));
    
    //h3->SetMarkerStyle(21);
    h3->Draw("ep");       // Draw the ratio plot
    hAvgErr->Draw("ep same");
    
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
    hAvgErr->Draw("ep same");
    pad1->cd();
  }

  return true;
}
