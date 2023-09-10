/**********************************************************************
 Created on : 23/10/2022
 Purpose    : Read the Electron Branch elements
 Author     : Indranil Das, Visiting Fellow
 Email      : indranil.das@cern.ch | indra.ehep@gmail.com
**********************************************************************/
int ReadEleBranch(const char *infile="TTbarPowheg_Dilepton_postVFP_Skim_NanoAOD_1of10.root")
{
  TH1F *hRelIso_Incl = new TH1F("hRelIso_Incl","hRelIso_Incl", 10000, -1., 49.);
  TH1F *hRelIso_veto = new TH1F("hRelIso_veto","hRelIso_veto", 10000, -1., 49.);
  TH1F *hRelIso_loose = new TH1F("hRelIso_loose","hRelIso_loose", 10000, -1., 49.);
  TH1F *hRelIso_medium = new TH1F("hRelIso_medium","hRelIso_medium", 10000, -1., 49.);
  TH1F *hRelIso_iso_medium = new TH1F("hRelIso_iso_medium","hRelIso_iso_medium", 10000, -1., 49.);
  TH1F *hRelIso_noniso_medium = new TH1F("hRelIso_noniso_medium","hRelIso_noniso_medium", 10000, -1., 49.);
  TH1F *hRelIso_medium_lmet = new TH1F("hRelIso_medium_lmet","hRelIso_medium_lmet", 10000, -1., 49.);
  TH1F *hRelIso_iso_medium_lmet = new TH1F("hRelIso_iso_medium_lmet","hRelIso_iso_medium_lmet", 100000, -0.2, 0.2 );
  TH1F *hRelIso_noniso_medium_lmet = new TH1F("hRelIso_noniso_medium_lmet","hRelIso_noniso_medium_lmet", 10000, -1., 49.);
  TH1F *hRelIso_medium_hmet = new TH1F("hRelIso_medium_hmet","hRelIso_medium_hmet", 10000, -1., 49.);
  TH1F *hRelIso_iso_medium_hmet = new TH1F("hRelIso_iso_medium_hmet","hRelIso_iso_medium_hmet", 100000, -0.2, 0.2 );
  TH1F *hRelIso_noniso_medium_hmet = new TH1F("hRelIso_noniso_medium_hmet","hRelIso_noniso_medium_hmet", 10000, -1., 49.);
  TH1F *hRelIso_tight = new TH1F("hRelIso_tight","hRelIso_tight", 10000, -1., 49.);
  
  TEfficiency *hEffPt = new TEfficiency("hEffPt","Efficiency;#it{p}_{T} GeV/#it{c};#epsilon", 100, 0., 100.);
  TH1F *hPt = new TH1F("hPt","hPt", 100, -1., 99.);
  
  TFile *fin = TFile::Open(infile);
  TTree *tr = (TTree *)fin->Get("Events");
  
  tr->SetCacheSize(500*1024*1024);
  tr->SetBranchStatus("*",0);

  unsigned int run;
  tr->SetBranchStatus("run",1);
  tr->SetBranchAddress("run",&run);

  UInt_t  nEle_;
  tr->SetBranchStatus("nElectron",1);
  tr->SetBranchAddress("nElectron", &(nEle_));

  Float_t elePFRelIso_[20];
  tr->SetBranchStatus("Electron_pfRelIso03_all",1);
  tr->SetBranchAddress("Electron_pfRelIso03_all", &(elePFRelIso_));

  Float_t elePFRelIsoCh_[20];
  tr->SetBranchStatus("Electron_pfRelIso03_chg",1);
  tr->SetBranchAddress("Electron_pfRelIso03_chg", &(elePFRelIsoCh_));

  Int_t eleIDcutbased_[20];
  tr->SetBranchStatus("Electron_cutBased",1); 
  tr->SetBranchAddress("Electron_cutBased", &(eleIDcutbased_));

  Float_t elePt_[20];
  tr->SetBranchStatus("Electron_pt",1); 
  tr->SetBranchAddress("Electron_pt", &(elePt_));
  
  Float_t MET_pt;
  tr->SetBranchStatus("MET_pt",1); 
  tr->SetBranchAddress("MET_pt", &(MET_pt));
  
  Bool_t Electron_mvaFall17V2Iso_[20];
  tr->SetBranchStatus("Electron_mvaFall17V2Iso",1); 
  tr->SetBranchAddress("Electron_mvaFall17V2Iso", &(Electron_mvaFall17V2Iso_));

  Bool_t Electron_mvaFall17V2Iso_WPL_[20];
  tr->SetBranchStatus("Electron_mvaFall17V2Iso_WPL",1); 
  tr->SetBranchAddress("Electron_mvaFall17V2Iso_WPL", &(Electron_mvaFall17V2Iso_WPL_));

  Bool_t Electron_mvaFall17V2Iso_WP80_[20];
  tr->SetBranchStatus("Electron_mvaFall17V2Iso_WP80",1); 
  tr->SetBranchAddress("Electron_mvaFall17V2Iso_WP80", &(Electron_mvaFall17V2Iso_WP80_));

  Bool_t Electron_mvaFall17V2Iso_WP90_[20];
  tr->SetBranchStatus("Electron_mvaFall17V2Iso_WP90",1); 
  tr->SetBranchAddress("Electron_mvaFall17V2Iso_WP90", &(Electron_mvaFall17V2Iso_WP90_));
  
  Bool_t Electron_mvaFall17V2noIso_[20];
  tr->SetBranchStatus("Electron_mvaFall17V2noIso",1); 
  tr->SetBranchAddress("Electron_mvaFall17V2noIso", &(Electron_mvaFall17V2noIso_));

  Bool_t Electron_mvaFall17V2noIso_WPL_[20];
  tr->SetBranchStatus("Electron_mvaFall17V2noIso_WPL",1); 
  tr->SetBranchAddress("Electron_mvaFall17V2noIso_WPL", &(Electron_mvaFall17V2noIso_WPL_));
  
  Bool_t Electron_mvaFall17V2noIso_WP80_[20];
  tr->SetBranchStatus("Electron_mvaFall17V2noIso_WP80",1); 
  tr->SetBranchAddress("Electron_mvaFall17V2noIso_WP80", &(Electron_mvaFall17V2noIso_WP80_));

  Bool_t Electron_mvaFall17V2noIso_WP90_[20];
  tr->SetBranchStatus("Electron_mvaFall17V2noIso_WP90",1); 
  tr->SetBranchAddress("Electron_mvaFall17V2noIso_WP90", &(Electron_mvaFall17V2noIso_WP90_));
  
  
  cout << "Total Entries : " << tr->GetEntries() << endl;
  for(Long64_t ievent=0;ievent<tr->GetEntries();ievent++){
  //for(Long64_t ievent=0;ievent<100000;ievent++){
    tr->GetEntry(ievent);
    for(int iele = 0 ; iele < nEle_ ; iele++){
      if(ievent%100000==0)
	printf("event : %lld, iele : %d, cutid : %d, relIso_all : %f, relIso_chg : %f\n", ievent, iele, eleIDcutbased_[iele], elePFRelIso_[iele], elePFRelIsoCh_[iele]);
      hRelIso_Incl->Fill(elePFRelIso_[iele]);
      
      if(eleIDcutbased_[iele]>=1) //vetoid
	hRelIso_veto->Fill(elePFRelIso_[iele]);
      if(eleIDcutbased_[iele]>=2) //looseid
	hRelIso_loose->Fill(elePFRelIso_[iele]);


      hEffPt->Fill( (eleIDcutbased_[iele]>=3), elePt_[iele]);
      if(eleIDcutbased_[iele]>=3){ //medium ID
	hRelIso_medium->Fill(elePFRelIso_[iele]);	
	hPt->Fill(elePt_[iele]);
	if(elePFRelIso_[iele]<0.0821)
	  hRelIso_iso_medium->Fill(elePFRelIso_[iele]);
	else
	  hRelIso_noniso_medium->Fill(elePFRelIso_[iele]);
      }
      
      if(MET_pt < 20.0){
	if(eleIDcutbased_[iele]>=3){
	  if(elePFRelIso_[iele]<0.0821)
	    hRelIso_iso_medium_lmet->Fill(elePFRelIso_[iele]);
	  else
	    hRelIso_noniso_medium_lmet->Fill(elePFRelIso_[iele]);
	}
      }else { //MET
	if(eleIDcutbased_[iele]>=3){
	  if(elePFRelIso_[iele]<0.0821)
	    hRelIso_iso_medium_hmet->Fill(elePFRelIso_[iele]);
	  else 
	    hRelIso_noniso_medium_hmet->Fill(elePFRelIso_[iele]);
	}
      }      
      if(eleIDcutbased_[iele]>=4)
	hRelIso_tight->Fill(elePFRelIso_[iele]);

      ////////////////// MVA //////////////////////////////////////////
      // if(Electron_mvaFall17V2noIso_[iele]) //vetoid ?
      // 	hRelIso_veto->Fill(elePFRelIso_[iele]);
      // if(Electron_mvaFall17V2noIso_WPL_[iele]) //looseid ?
      // 	hRelIso_loose->Fill(elePFRelIso_[iele]);

      // hEffPt->Fill(Electron_mvaFall17V2noIso_WP80_[iele], elePt_[iele]);
      // //hEffPt->Fill(Electron_mvaFall17V2noIso_[iele], elePt_[iele]);
      // if(Electron_mvaFall17V2noIso_WP80_[iele]){ //medium ID ?
      // 	hRelIso_medium->Fill(elePFRelIso_[iele]);
      // 	hPt->Fill(elePt_[iele]);
      // 	if(elePFRelIso_[iele]<0.0821)
      // 	  hRelIso_iso_medium->Fill(elePFRelIso_[iele]);
      // 	else 
      // 	  hRelIso_noniso_medium->Fill(elePFRelIso_[iele]);
      // }
      
      // if(MET_pt < 20.0){
      // 	if(Electron_mvaFall17V2noIso_WP80_[iele]){ //medium ID ?
      // 	  if(elePFRelIso_[iele]<0.0821)
      // 	    hRelIso_iso_medium_lmet->Fill(elePFRelIso_[iele]);
      // 	  else 
      // 	    hRelIso_noniso_medium_lmet->Fill(elePFRelIso_[iele]);
      // 	}
      // }else { //METpt
      // 	if(Electron_mvaFall17V2noIso_WP80_[iele]){ //medium ID ?
      // 	  if(elePFRelIso_[iele]<0.0821)
      // 	    hRelIso_iso_medium_hmet->Fill(elePFRelIso_[iele]);
      // 	  else 
      // 	    hRelIso_noniso_medium_hmet->Fill(elePFRelIso_[iele]);
      // 	}
      // }
      
      // if(Electron_mvaFall17V2noIso_WP90_[iele])
      // 	hRelIso_tight->Fill(elePFRelIso_[iele]);

    }//ele loop
  }//event loop

  hRelIso_Incl->GetXaxis()->SetTitle("Electron_pfRelIso03_all");
  hRelIso_veto->GetXaxis()->SetTitle("Electron_pfRelIso03_all");
  hRelIso_loose->GetXaxis()->SetTitle("Electron_pfRelIso03_all");
  hRelIso_medium->GetXaxis()->SetTitle("Electron_pfRelIso03_all");
  hRelIso_iso_medium->GetXaxis()->SetTitle("Electron_pfRelIso03_all");
  hRelIso_noniso_medium->GetXaxis()->SetTitle("Electron_pfRelIso03_all");
  hRelIso_medium_lmet->GetXaxis()->SetTitle("Electron_pfRelIso03_all");
  hRelIso_iso_medium_lmet->GetXaxis()->SetTitle("Electron_pfRelIso03_all");
  hRelIso_noniso_medium_lmet->GetXaxis()->SetTitle("Electron_pfRelIso03_all");
  hRelIso_medium_hmet->GetXaxis()->SetTitle("Electron_pfRelIso03_all");
  hRelIso_iso_medium_hmet->GetXaxis()->SetTitle("Electron_pfRelIso03_all");
  hRelIso_noniso_medium_hmet->GetXaxis()->SetTitle("Electron_pfRelIso03_all");
  hRelIso_tight->GetXaxis()->SetTitle("Electron_pfRelIso03_all");
  hPt->GetXaxis()->SetTitle("Muon_pt");
  
  TCanvas *c1 = new TCanvas("c1","c1",1200,800);
  c1->Divide(2,2);
  c1->cd(1);
  c1->cd(1)->SetLogy();
  hRelIso_veto->Draw();
  c1->cd(2);
  c1->cd(2)->SetLogy();
  hRelIso_loose->Draw();
  c1->cd(3);
  c1->cd(3)->SetLogy();
  hRelIso_medium->Draw();
  c1->cd(4);
  c1->cd(4)->SetLogy();
  hRelIso_tight->Draw();
  
  TCanvas *c2 = new TCanvas("c2","c2",1200,800);
  c2->SetLogy();
  hRelIso_Incl->Draw();
  
  TCanvas *c3 = new TCanvas("c3","c3",1200,800);
  c3->Divide(2,1);
  c3->cd(1);
  c3->cd(1)->SetLogy();
  hRelIso_iso_medium->Draw();
  c3->cd(2)->SetLogy();
  hRelIso_noniso_medium->Draw();
  
  TCanvas *c4 = new TCanvas("c4","c4",1200,800);
  c4->Divide(2,2);
  c4->cd(1)->SetLogy();
  hRelIso_iso_medium_hmet->Draw();
  c4->cd(2)->SetLogy();
  hRelIso_noniso_medium_hmet->Draw();
  c4->cd(3)->SetLogy();
  hRelIso_iso_medium_lmet->Draw();
  c4->cd(4)->SetLogy();
  hRelIso_noniso_medium_lmet->Draw();

  TCanvas *c5 = new TCanvas("c5","c5",1200,800);
  c5->Divide(2,1);
  c5->cd(1);
  hPt->Draw();
  c5->cd(2);
  hEffPt->Draw();
  
  TFile *fout = new TFile("output.root","recreate");
  c1->Write();
  c2->Write();
  c3->Write();
  c4->Write();
  c5->Write();
  fout->Close();
  
  //delete fin;
  return true;
}
