/**********************************************************************
 Created on : 07/11/2022
 Purpose    : Compare the njet wt ratio for three years
 Author     : Indranil Das, Visiting Fellow, TIFR
 Email      : indranil.das@cern.ch | indra.ehep@gmail.com
**********************************************************************/

int CompareWtRatio()
{
  string inputpath = "/home/indra/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/grid_v40_Syst/CBA_gdjsoncorr";
  TFile *fin_2016_pre_mc = TFile::Open(Form("%s/pre/all_TTbar.root",inputpath.c_str()));
  TFile *fin_2016_post_mc = TFile::Open(Form("%s/post/all_TTbar.root",inputpath.c_str()));
  TFile *fin_2016_mc = TFile::Open(Form("%s/2016/all_TTbar.root",inputpath.c_str()));
  TFile *fin_2017_mc = TFile::Open(Form("%s/2017/all_TTbar.root",inputpath.c_str()));
  TFile *fin_2018_mc = TFile::Open(Form("%s/2018/all_TTbar.root",inputpath.c_str()));
  TFile *fin_2016_pre_data = TFile::Open(Form("%s/pre/all_DataMu.root",inputpath.c_str()));
  
  TH1D *wt_before_mu_pre_mc = (TH1D *)fin_2016_pre_mc->Get("TTbar/base/Iso/_wt_before_mu");
  TH1D *wt_after_mu_pre_mc = (TH1D *)fin_2016_pre_mc->Get("TTbar/base/Iso/_wt_after_mu");
  TH1D *wt_before_mu_post_mc = (TH1D *)fin_2016_post_mc->Get("TTbar/base/Iso/_wt_before_mu");
  TH1D *wt_after_mu_post_mc = (TH1D *)fin_2016_post_mc->Get("TTbar/base/Iso/_wt_after_mu");
  TH1D *wt_before_mu_2016_mc = (TH1D *)fin_2016_mc->Get("TTbar/base/Iso/_wt_before_mu");
  TH1D *wt_after_mu_2016_mc = (TH1D *)fin_2016_mc->Get("TTbar/base/Iso/_wt_after_mu");
  TH1D *wt_before_mu_2017_mc = (TH1D *)fin_2017_mc->Get("TTbar/base/Iso/_wt_before_mu");
  TH1D *wt_after_mu_2017_mc = (TH1D *)fin_2017_mc->Get("TTbar/base/Iso/_wt_after_mu");
  TH1D *wt_before_mu_2018_mc = (TH1D *)fin_2018_mc->Get("TTbar/base/Iso/_wt_before_mu");
  TH1D *wt_after_mu_2018_mc = (TH1D *)fin_2018_mc->Get("TTbar/base/Iso/_wt_after_mu");
  
  TH1D *wt_before_mu_pre_data = (TH1D *)fin_2016_pre_data->Get("DataMu/base/Iso/_wt_before_mu");
  TH1D *wt_after_mu_pre_data = (TH1D *)fin_2016_pre_data->Get("DataMu/base/Iso/_wt_after_mu");

  TH1D *wt_ratio_mu_pre_mc = (TH1D *)wt_before_mu_pre_mc->Clone("wt_ratio_mu_pre_mc");
  wt_ratio_mu_pre_mc->SetTitle("wt_ratio_mu_pre_mc");
  wt_ratio_mu_pre_mc->Divide(wt_after_mu_pre_mc);

  TH1D *wt_ratio_mu_post_mc = (TH1D *)wt_before_mu_post_mc->Clone("wt_ratio_mu_post_mc");
  wt_ratio_mu_post_mc->SetTitle("wt_ratio_mu_post_mc");
  wt_ratio_mu_post_mc->Divide(wt_after_mu_post_mc);

  TH1D *wt_ratio_mu_2016_mc = (TH1D *)wt_before_mu_2016_mc->Clone("wt_ratio_mu_2016_mc");
  wt_ratio_mu_2016_mc->SetTitle("wt_ratio_mu_2016_mc");
  wt_ratio_mu_2016_mc->Divide(wt_after_mu_2016_mc);

  TH1D *wt_ratio_mu_2017_mc = (TH1D *)wt_before_mu_2017_mc->Clone("wt_ratio_mu_2017_mc");
  wt_ratio_mu_2017_mc->SetTitle("wt_ratio_mu_2017_mc");
  wt_ratio_mu_2017_mc->Divide(wt_after_mu_2017_mc);

  TH1D *wt_ratio_mu_2018_mc = (TH1D *)wt_before_mu_2018_mc->Clone("wt_ratio_mu_2018_mc");
  wt_ratio_mu_2018_mc->SetTitle("wt_ratio_mu_2018_mc");
  wt_ratio_mu_2018_mc->Divide(wt_after_mu_2018_mc);

  TH1D *wt_ratio_mu_pre_data = (TH1D *)wt_before_mu_pre_data->Clone("wt_ratio_mu_pre_data");
  wt_ratio_mu_pre_data->SetTitle("wt_ratio_mu_pre_data");
  wt_ratio_mu_pre_data->Divide(wt_after_mu_pre_data);
  
  wt_ratio_mu_pre_mc->SetLineColor(kBlack);
  wt_ratio_mu_post_mc->SetLineColor(kBlue);
  wt_ratio_mu_2016_mc->SetLineColor(kOrange);
  wt_ratio_mu_2017_mc->SetLineColor(kMagenta);
  wt_ratio_mu_2018_mc->SetLineColor(kGreen+2);
  wt_ratio_mu_pre_data->SetLineColor(kRed);

  wt_ratio_mu_pre_mc->SetLineWidth(2);
  wt_ratio_mu_post_mc->SetLineWidth(2);
  wt_ratio_mu_2016_mc->SetLineWidth(2);
  wt_ratio_mu_2017_mc->SetLineWidth(2);
  wt_ratio_mu_2018_mc->SetLineWidth(2);
  wt_ratio_mu_pre_data->SetLineWidth(2);

  TLegend *legend1=new TLegend(0.39162,0.6771911,0.642121,0.8745237);
  legend1->SetFillColor(0);
  legend1->SetTextFont(22);
  //legend1->SetTextSize(0.02);
  legend1->SetBorderSize(0);
  legend1->AddEntry(wt_ratio_mu_pre_mc,Form("%s",wt_ratio_mu_pre_mc->GetName()),"lpe");
  legend1->AddEntry(wt_ratio_mu_post_mc,Form("%s",wt_ratio_mu_post_mc->GetName()),"lpe");
  legend1->AddEntry(wt_ratio_mu_2016_mc,Form("%s",wt_ratio_mu_2016_mc->GetName()),"lpe");
  legend1->AddEntry(wt_ratio_mu_2017_mc,Form("%s",wt_ratio_mu_2017_mc->GetName()),"lpe");
  legend1->AddEntry(wt_ratio_mu_2018_mc,Form("%s",wt_ratio_mu_2018_mc->GetName()),"lpe");
  TCanvas *c1 = new TCanvas("c1","c1");
  wt_ratio_mu_pre_mc->Draw();
  wt_ratio_mu_post_mc->Draw("sames");
  wt_ratio_mu_2016_mc->Draw("sames");
  wt_ratio_mu_2017_mc->Draw("sames");
  wt_ratio_mu_2018_mc->Draw("sames");
  wt_ratio_mu_pre_data->Draw("sames");
  legend1->Draw();

  return true;
}
