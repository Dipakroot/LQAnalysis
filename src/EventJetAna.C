/**********************************************************************
 Created on : 29/03/2021
 Purpose    : Analyse the jet of the event for leptonic and hadronic vertex
 Author     : Indranil Das, Visiting Fellow
 Email      : indranil.das@cern.ch | indra.ehep@gmail.com
**********************************************************************/
#include "../interface/EventJetAna.h"
#define EventJetAna_cxx

int jecvar012_g = 1; // 0:down, 1:norm, 2:up
int jervar012_g = 1; // 0:down, 1:norm, 2:up
int musmear012_g = 1; // 0:down, 1:norm, 2: up
int elesmear012_g = 1; // 0:down, 1:norm, 2: up
int elescale012_g = 1;
bool dileptonsample;
bool qcdSample;

#ifdef EventJetAna_cxx

EventJetAna::EventJetAna()
{
  //double getEvtWeight(string, int, double, double);
  //void initCrossSections();
  //int InitRecoTree(TTree *&);
  //char **infile = 0;
  const int nFiles = 1;
  infile = new char*[nFiles];
  infile[0] = new char[1000];
  //infile[1] = new char[1000]; 
  sprintf(infile[0],"/Data/root_files/AOD_files/NanoAOD_framework/Test_macro/Skim/2016/TTbarPowheg_Semilept_Skim_NanoAOD_1of21.root");
  //sprintf(infile[1],"/Data/root_files/AOD_files/NanoAOD_framework/Test_macro/Skim/2016/TTbarPowheg_Semilept_Skim_NanoAOD_2of21.root");
  
  string year = "2016"; 
  bool isData = false;
  isMC = !isData ;
  
  printf("\n\n");

  tree = new EventTree(nFiles, false, year, isData, infile);

  isSystematicRun = false;

  initCrossSections();
   
  std::string PUfilename; 
  std::string PUfilename_up;
  std::string PUfilename_down;

  if (year=="2016"){
    PUfilename      = "weight/PileupSF/Data_2016BCDGH_Pileup.root";
    PUfilename_up   = "weight/PileupSF/Data_2016BCDGH_Pileup_scaledUp.root";
    PUfilename_down = "weight/PileupSF/Data_2016BCDGH_Pileup_scaledDown.root";
    //cout << "Executing ... here " << endl ;
  }
  if (year=="2017"){
    PUfilename      = "weight/PileupSF/Data_2017BCDEF_Pileup.root";
    PUfilename_up   = "weight/PileupSF/Data_2017BCDEF_Pileup_scaledUp.root";
    PUfilename_down = "weight/PileupSF/Data_2017BCDEF_Pileup_scaledDown.root";
  }
  if (year=="2018"){
    PUfilename      = "weight/PileupSF/Data_2018ABCD_Pileup.root";
    PUfilename_up   = "weight/PileupSF/Data_2018ABCD_Pileup_scaledUp.root";
    PUfilename_down = "weight/PileupSF/Data_2018ABCD_Pileup_scaledDown.root";
  }
  
  selector = new Selector();
  
  evtPick = new EventPick("");
  
  cout <<" Sample name1 : "  << infile[0] << endl;
  GetSampleName(infile);
  

  selector->year = year;
  evtPick->year = year;
  
  // selector->printEvent = eventNum;
  // evtPick->printEvent = eventNum;

  evtPick->Njet_ge = 2;
  evtPick->NBjet_ge = 0;
  
  evtPick->applyMetFilter = true; 
  bool applyHemVeto=true; 
  //bool applyHemVeto=false; //test
  selector->looseJetID = false;
  selector->useDeepCSVbTag = true;
    
  if (isMC){
    if (year=="2016") selector->init_JER("weight/JetSF/JER/Summer16_25nsV1");
    if (year=="2017") selector->init_JER("weight/JetSF/JER/Fall17_V3");
    if (year=="2018") selector->init_JER("weight/JetSF/JER/Autumn18_V7b");
  }



  if (year=="2016") selector->btag_cut_DeepCSV = 0.6321;
  if (year=="2017") selector->btag_cut_DeepCSV = 0.4941;
  if (year=="2018") selector->btag_cut_DeepCSV = 0.4184;
  
  BTagCalibration calib;
  if (!selector->useDeepCSVbTag){
    if (year=="2016") calib = BTagCalibration("csvv2", "weight/BtagSF/CSVv2_Moriond17_B_H.csv");
    if (year=="2017") calib = BTagCalibration("csvv2", "weight/BtagSF/CSVv2_94XSF_V2_B_F.csv");
    if (year=="2018") calib = BTagCalibration("csvv2", "weight/BtagSF/CSVv2_94XSF_V2_B_F.csv");
  } else {
    if (year=="2016"){ calib = BTagCalibration("deepcsv", "weight/BtagSF/DeepCSV_2016LegacySF_V1.csv");}
    if (year=="2017"){ calib = BTagCalibration("deepcsv", "weight/BtagSF/DeepCSV_94XSF_V3_B_F.csv");}
    if (year=="2018"){ calib = BTagCalibration("deepcsv", "weight/BtagSF/DeepCSV_102XSF_V1.csv");} //DeepCSV_102XSF_V1.csv
    
    loadBtagEff(sampletype,year);
    
  }
  
  topEvent.SetBtagThresh(selector->btag_cut_DeepCSV);


  BTagCalibrationReader reader(BTagEntry::OP_MEDIUM,  // operating point
			       "central",             // central sys type
			       {"up", "down"});      // other sys types
  
  reader.load(calib,                // calibration instance
	      BTagEntry::FLAV_B,    // btag flavour
	      "comb");               // measurement type
  
  reader.load(calib,                // calibration instance
	      BTagEntry::FLAV_C,    // btag flavour
	      "comb");               // measurement type
  
  reader.load(calib,                // calibration instance
	      BTagEntry::FLAV_UDSG,    // btag flavour
	      "incl");               // measurement type
  
  
  // if(qcdSample)       {selector->QCDselect = true; evtPick->QCDselect = true;}


  // if (qcdSample){
  // 	outputFileName.replace(0,outputDirectory.size()+1, outputDirectory + "/QCDcr_");
  // }

  //TFile *outputFile = new TFile(outputFileName.c_str(),"recreate");
  TFile *outputFile = new TFile("output.root","recreate");
  outputTree = new TTree("RecoNtuple_Skim","RecoNtuple_Skim");
  
  PUReweight* PUweighter = new PUReweight(nFiles, infile, PUfilename);
  PUReweight* PUweighterUp = new PUReweight(nFiles, infile, PUfilename_up);
  PUReweight* PUweighterDown = new PUReweight(nFiles, infile, PUfilename_down);

  cout << "DONE" << endl;
    
  tree->GetEntry(0);
        
  std::cout << "isMC: " << isMC << endl;
  
  outputTree->SetAutoSave();

  InitVariables();
  InitBranches();
  
  string JECsystLevel = "";
  JECvariation* jecvar = 0;
  
  if (isMC && jecvar012_g!=1) {
    //		jecvar = new JECvariation("weight/JetSF/Summer16_23Sep2016V4", isMC, "Total");//SubTotalAbsolute");
    cout << "Applying JEC uncertainty variations : " << JECsystLevel << endl;
    if (year=="2016") jecvar = new JECvariation("weight/JetSF/Summer16_07Aug2017_V11", isMC, JECsystLevel);
    if (year=="2017") jecvar = new JECvariation("weight/JetSF/Fall17_17Nov2017_V32", isMC, JECsystLevel);
    if (year=="2018") jecvar = new JECvariation("weight/JetSF/Autumn18_V19", isMC, JECsystLevel);
  }

  double luminosity = 1.;
  if (year=="2016") luminosity=35921.875595;
  if (year=="2017") luminosity=41529.548819;
  if (year=="2018") luminosity=59740.565202;
    
  double nMC_total = 0.;
  useGenWeightScaling = true;
  
  double nMC_thisFile = 0.;
  char** fileNames = infile;
  for(int fileI=0; fileI<nFiles; fileI++){
    TFile *_file = TFile::Open(fileNames[fileI],"read");
    TH1D *hEvents = (TH1D*) _file->Get("hEvents");
    nMC_thisFile = (hEvents->GetBinContent(2)); //sum of gen weights
    cout<<"nMC_thisFile : "<<nMC_thisFile <<endl;
    if (nMC_thisFile==0) {useGenWeightScaling=false;} //if bin isn't filled, fall back to using positive - negative bins
    nMC_total += nMC_thisFile;
  }
  
  if (!useGenWeightScaling){
    for(int fileI=0; fileI<nFiles; fileI++){
      TFile *_file = TFile::Open(fileNames[fileI],"read");
      TH1D *hEvents = (TH1D*) _file->Get("hEvents");
      nMC_total += (hEvents->GetBinContent(3) - hEvents->GetBinContent(1));  //positive weight - neg weight 
    }
  }
  
  if (nMC_total==0){
    nMC_total=1;
  }
  
  _lumiWeight = getEvtWeight(sampletype, std::stoi(year), luminosity, nMC_total);
  
  cout << "Luminosity : " << luminosity << endl;
  
  _PUweight       = 1.;
  _muEffWeight    = 1.;
  _muEffWeight_Do = 1.;
  _muEffWeight_Up = 1.;
  _eleEffWeight    = 1.;
  _eleEffWeight_Up = 1.;
  _eleEffWeight_Do = 1.;
  
  Long64_t nEntr = tree->GetEntries();
  cout<<nEntr<<endl;

  if (year=="2016"){
    muSFa = new MuonSF("weight/MuEleSF/mu2016/EfficienciesStudies_2016_legacy_rereco_rootfiles_RunBCDEF_SF_ID.root", "NUM_TightID_DEN_genTracks_eta_pt",
		       "weight/MuEleSF/mu2016/EfficienciesStudies_2016_legacy_rereco_rootfiles_RunBCDEF_SF_ISO.root", "NUM_TightRelIso_DEN_TightIDandIPCut_eta_pt",
		       "weight/MuEleSF/mu2016/EfficienciesStudies_2016_trigger_EfficienciesAndSF_RunBtoF.root", "IsoMu24_OR_IsoTkMu24_PtEtaBins/abseta_pt_ratio");
	
    muSFb = new MuonSF("weight/MuEleSF/mu2016/EfficienciesStudies_2016_legacy_rereco_rootfiles_RunGH_SF_ID.root", "NUM_TightID_DEN_genTracks_eta_pt",
		       "weight/MuEleSF/mu2016/EfficienciesStudies_2016_legacy_rereco_rootfiles_RunGH_SF_ISO.root", "NUM_TightRelIso_DEN_TightIDandIPCut_eta_pt",
		       "weight/MuEleSF/mu2016/EfficienciesStudies_2016_trigger_EfficienciesAndSF_RunGtoH.root", "IsoMu24_OR_IsoTkMu24_PtEtaBins/abseta_pt_ratio");
	
    eleSF = new ElectronSF("weight/MuEleSF/ele2016/2016LegacyReReco_ElectronTight_Fall17V2.root",
			   "weight/MuEleSF/ele2016/EGM2D_BtoH_GT20GeV_RecoSF_Legacy2016.root",
			   "weight/MuEleSF/ele2016/sf_ele_2016_trig_v5.root");
	
  } else if (year=="2017") {
	
    muSFa = new MuonSF("weight/MuEleSF/mu2017/RunBCDEF_SF_ID.root", "NUM_TightID_DEN_genTracks_pt_abseta",
		       "weight/MuEleSF/mu2017/RunBCDEF_SF_ISO.root", "NUM_TightRelIso_DEN_TightIDandIPCut_pt_abseta",
		       "weight/MuEleSF/mu2017/EfficienciesAndSF_RunBtoF_Nov17Nov2017.root", "IsoMu27_PtEtaBins/abseta_pt_ratio");
	
    eleSF = new ElectronSF("weight/MuEleSF/ele2017/2017_ElectronTight.root",
			   "weight/MuEleSF/ele2017/egammaEffi.txt_EGM2D_runBCDEF_passingRECO.root",
			   "weight/MuEleSF/ele2017/sf_ele_2017_trig_v5.root");

  } else if (year=="2018") {

    muSFa = new MuonSF("weight/MuEleSF/mu2018/EfficienciesStudies_2018_rootfiles_RunABCD_SF_ID.root",  "NUM_TightID_DEN_TrackerMuons_pt_abseta",
		       "weight/MuEleSF/mu2018/EfficienciesStudies_2018_rootfiles_RunABCD_SF_ISO.root", "NUM_TightRelIso_DEN_TightIDandIPCut_pt_abseta",
		       "weight/MuEleSF/mu2018/EfficienciesStudies_2018_trigger_EfficienciesAndSF_2018Data_BeforeMuonHLTUpdate.root", "IsoMu24_PtEtaBins/abseta_pt_ratio");
	
    muSFb = new MuonSF("weight/MuEleSF/mu2018/EfficienciesStudies_2018_rootfiles_RunABCD_SF_ID.root",  "NUM_TightID_DEN_TrackerMuons_pt_abseta",
		       "weight/MuEleSF/mu2018/EfficienciesStudies_2018_rootfiles_RunABCD_SF_ISO.root", "NUM_TightRelIso_DEN_TightIDandIPCut_pt_abseta",
		       "weight/MuEleSF/mu2018/EfficienciesStudies_2018_trigger_EfficienciesAndSF_2018Data_AfterMuonHLTUpdate.root", "IsoMu24_PtEtaBins/abseta_pt_ratio");

    eleSF = new ElectronSF("weight/MuEleSF/ele2018/2018_ElectronTight.root",
			   "weight/MuEleSF/ele2018/egammaEffi.txt_EGM2D_updatedAll.root",
			   "weight/MuEleSF/ele2018/sf_ele_2018_trig_v5.root");
  }
  
  int dumpFreq = 1;
  
  if (nEntr >50)     { dumpFreq = 5; }
  if (nEntr >100)     { dumpFreq = 10; }
  if (nEntr >500)     { dumpFreq = 50; }
  if (nEntr >1000)    { dumpFreq = 100; }
  if (nEntr >5000)    { dumpFreq = 500; }
  if (nEntr >10000)   { dumpFreq = 1000; }
  if (nEntr >50000)   { dumpFreq = 5000; }
  if (nEntr >100000)  { dumpFreq = 10000; }
  if (nEntr >500000)  { dumpFreq = 50000; }
  if (nEntr >1000000) { dumpFreq = 100000; }
  if (nEntr >5000000) { dumpFreq = 500000; }
  if (nEntr >10000000){ dumpFreq = 1000000; }
  
  int count_HEM=0;  
  int entryStart;
  int entryStop;
  int nJob = -1;
  if (nJob==-1){
    entryStart = 0;
    entryStop=nEntr;
    //entryStop=30000;
  } 
  // else {
  //   int evtPerJob = nEntr/totJob;
  //   entryStart = (nJob-1) * evtPerJob;
  //   entryStop = (nJob) * evtPerJob;
  //   if (nJob==totJob){
  //     entryStop = nEntr;
  //   }
  // }
  
  bool probeEvent = false;
  
  for(Long64_t entry=entryStart; entry<entryStop; entry++){
    
    //if(entry%dumpFreq == 0)
    if(entry%dumpFreq == 0)
      std::cout << "processing entry " << entry << " out of " << entryStop << endl; 

    tree->GetEntry(entry);

    if(probeEvent)
      cout << endl << "1 : Entry "<< entry  <<",  Event : " << tree->event_ << endl;
    
    if( isMC ){
      if (jecvar012_g != 1){
	jecvar->applyJEC(tree, jecvar012_g); // 0:down, 1:norm, 2:up
      }
    }
    
    //HEM test 
    bool isHemVetoObj = false;
    int nHEM_ele=0;
    bool HEM_ele_Veto=false;
    for(int eleInd = 0; eleInd < int(tree->nEle_) ; ++eleInd){
      double eta = tree->eleEta_[eleInd];
      double pt = tree->elePt_[eleInd];
      double phi = tree->elePhi_[eleInd];
      bool ele_HEM_pt_pass  = pt >= 15 ;
      bool ele_HEM_eta_pass = eta > -3.0 && eta < -1.4 ;
      bool ele_HEM_phi_pass = phi > -1.57 && phi < -0.87;
      if ( ele_HEM_pt_pass &&  ele_HEM_eta_pass &&  ele_HEM_phi_pass) nHEM_ele++;
    }
    HEM_ele_Veto = (nHEM_ele>=1);
    isHemVetoObj = HEM_ele_Veto && year=="2018";
    
    if(probeEvent)
      cout << "2 : Entry "<< entry  <<",  Event : " << tree->event_ << endl;
    
    if(_isData &&  tree->run_>=319077 && isHemVetoObj && applyHemVeto){ 
      count_HEM++;
      continue; 
    }
    
    if(probeEvent)
      cout << "3 : Entry "<< entry  <<",  Event : " << tree->event_ << endl;

    if( !applyHemVeto) isHemVetoObj=false;
    
    selector->clear_vectors();
    evtPick->process_event(tree, selector, _PUweight);
    
    if(probeEvent)
      cout << "4 : Entry "<< entry  <<",  Event : " << tree->event_ << endl;

    if ( evtPick->passPresel_ele || evtPick->passPresel_mu ) {
      
      if(probeEvent)
	cout << "5 : Entry "<< entry  <<",  Event : " << tree->event_ << endl;

      //if (!(evtPick->passAll_ele || evtPick->passAll_mu)) continue;

      if(probeEvent)
	cout << "6 : Entry "<< entry  <<",  Event : " << tree->event_ << endl;

      // FillEvent(year);
      FillEvent(year,isHemVetoObj,entry); //HEM test
      
      if(isMC) {
    	_PUweight    = PUweighter->getWeight(tree->nPUTrue_);
    	_PUweight_Up = PUweighterUp->getWeight(tree->nPUTrue_);
    	_PUweight_Do = PUweighterDown->getWeight(tree->nPUTrue_);
	
    	_btagWeight_1a      = getBtagSF_1a("central", reader);
    	_btagWeight_1a_b_Up = getBtagSF_1a("b_up",    reader);
    	_btagWeight_1a_b_Do = getBtagSF_1a("b_down",  reader);
    	_btagWeight_1a_l_Up = getBtagSF_1a("l_up",    reader);
    	_btagWeight_1a_l_Do = getBtagSF_1a("l_down",  reader);
				
    	_btagWeight      = getBtagSF_1c("central", reader, _btagSF);
    	_btagWeight_b_Up = getBtagSF_1c("b_up",    reader, _btagSF_b_Up);
    	_btagWeight_b_Do = getBtagSF_1c("b_down",  reader, _btagSF_b_Do);				
    	_btagWeight_l_Up = getBtagSF_1c("l_up",    reader, _btagSF_l_Up);
    	_btagWeight_l_Do = getBtagSF_1c("l_down",  reader, _btagSF_l_Do);				

    	if (evtPick->passPresel_mu) {
	  vector<double> muWeights;
	  vector<double> muWeights_Do;
	  vector<double> muWeights_Up;    

	  int muInd_ = selector->Muons.at(0);

	  if (year=="2016"){
	    vector<double> muWeights_a    = muSFa->getMuSF(tree->muPt_[muInd_],tree->muEta_[muInd_],1, 2016);
	    vector<double> muWeights_b    = muSFb->getMuSF(tree->muPt_[muInd_],tree->muEta_[muInd_],1, 2016);

	    vector<double> muWeights_a_Do = muSFa->getMuSF(tree->muPt_[muInd_],tree->muEta_[muInd_],0, 2016);
	    vector<double> muWeights_b_Do = muSFb->getMuSF(tree->muPt_[muInd_],tree->muEta_[muInd_],0, 2016);

	    vector<double> muWeights_a_Up = muSFa->getMuSF(tree->muPt_[muInd_],tree->muEta_[muInd_],2, 2016);
	    vector<double> muWeights_b_Up = muSFb->getMuSF(tree->muPt_[muInd_],tree->muEta_[muInd_],2, 2016);
		
	    for (int _i=0; _i < int(muWeights_a.size()); _i++){
	      muWeights.push_back( muWeights_a.at(_i) * 19.695422959/35.921875595 + 
				   muWeights_b.at(_i) * 16.226452636/35.921875595);

	      muWeights_Do.push_back( muWeights_a_Do.at(_i) * 19.695422959/35.921875595 + 
				      muWeights_b_Do.at(_i) * 16.226452636/35.921875595);

	      muWeights_Up.push_back( muWeights_a_Up.at(_i) * 19.695422959/35.921875595 + 
				      muWeights_b_Up.at(_i) * 16.226452636/35.921875595);

	    }
	  }
	  if (year=="2017"){    
	    muWeights    = muSFa->getMuSF(tree->muPt_[muInd_],tree->muEta_[muInd_],1, 2017);
	    muWeights_Do = muSFa->getMuSF(tree->muPt_[muInd_],tree->muEta_[muInd_],0, 2017);
	    muWeights_Up = muSFa->getMuSF(tree->muPt_[muInd_],tree->muEta_[muInd_],2, 2017);
	  }
	  if(year=="2018"){
	    vector<double> muWeights_a    = muSFa->getMuSF(tree->muPt_[muInd_],tree->muEta_[muInd_],1, 2018);
	    vector<double> muWeights_b    = muSFb->getMuSF(tree->muPt_[muInd_],tree->muEta_[muInd_],1, 2018);

	    vector<double> muWeights_a_Do = muSFa->getMuSF(tree->muPt_[muInd_],tree->muEta_[muInd_],0, 2018);
	    vector<double> muWeights_b_Do = muSFb->getMuSF(tree->muPt_[muInd_],tree->muEta_[muInd_],0, 2018);

	    vector<double> muWeights_a_Up = muSFa->getMuSF(tree->muPt_[muInd_],tree->muEta_[muInd_],2, 2018);
	    vector<double> muWeights_b_Up = muSFb->getMuSF(tree->muPt_[muInd_],tree->muEta_[muInd_],2, 2018);
		
	    for (int _i=0; _i < int(muWeights_a.size()); _i++){
	      muWeights.push_back( muWeights_a.at(_i) * 8.950818835/59.740565202 +
				   muWeights_b.at(_i) * 50.789746366/59.740565202);

	      muWeights_Do.push_back( muWeights_a_Do.at(_i) * 8.950818835/59.740565202 +
				      muWeights_b_Do.at(_i) * 50.789746366/59.740565202);

	      muWeights_Up.push_back( muWeights_a_Up.at(_i) * 8.950818835/59.740565202 +
				      muWeights_b_Up.at(_i) * 50.789746366/59.740565202);

	    }


	    // _muEffWeight    = (muSFa->getMuSF(tree->muPt_[muInd_],tree->muEta_[muInd_],1, 2018) * 8.950818835/59.688059536 + 
	    // 		   muSFb->getMuSF(tree->muPt_[muInd_],tree->muEta_[muInd_],1, 2018) * 50.737240701/59.688059536);

	    // _muEffWeight_Do = (muSFa->getMuSF(tree->muPt_[muInd_],tree->muEta_[muInd_],0, 2018) * 8.950818835/59.688059536 + 
	    // 		   muSFb->getMuSF(tree->muPt_[muInd_],tree->muEta_[muInd_],0, 2018) * 50.737240701/59.688059536);

	    // _muEffWeight_Up = (muSFa->getMuSF(tree->muPt_[muInd_],tree->muEta_[muInd_],2, 2018) * 8.950818835/59.688059536 + 
	    // 		   muSFb->getMuSF(tree->muPt_[muInd_],tree->muEta_[muInd_],2, 2018) * 50.737240701/59.688059536);
			
	  }
	  _muEffWeight    = muWeights.at(0);
	  _muEffWeight_Up = muWeights_Up.at(0);
	  _muEffWeight_Do = muWeights_Do.at(0);

	  _muEffWeight_IdIso    = muWeights.at(1)    * muWeights.at(2)   ;
	  _muEffWeight_IdIso_Up = muWeights_Up.at(1) * muWeights_Up.at(2);
	  _muEffWeight_IdIso_Do = muWeights_Do.at(1) * muWeights_Do.at(2);

	  _muEffWeight_Trig    = muWeights.at(3);
	  _muEffWeight_Trig_Up = muWeights_Up.at(3);
	  _muEffWeight_Trig_Do = muWeights_Do.at(3);

	  if (entry/1000000000 == 1){
	    cout << "Total Muon SF:" << endl;
	    cout << "    ID   = " << muWeights.at(1) << endl;
	    cout << "    Iso  = " << muWeights.at(2) << endl;
	    cout << "    Trig = " << muWeights.at(3) << endl;
	    cout << "    Total= " << muWeights.at(0) << endl;
	  }
	  _eleEffWeight    = 1.;
	  _eleEffWeight_Up = 1.;
	  _eleEffWeight_Do = 1.;
    	}
    	if (evtPick->passPresel_ele) {
	  int eleInd_ = selector->Electrons.at(0);
	  _muEffWeight    = 1.;
	  _muEffWeight_Do = 1.;
	  _muEffWeight_Up = 1.;

		    
	  vector<double> eleWeights    = eleSF->getEleSF(tree->elePt_[eleInd_],tree->eleEta_[eleInd_] + tree->eleDeltaEtaSC_[eleInd_],1);
	  vector<double> eleWeights_Do = eleSF->getEleSF(tree->elePt_[eleInd_],tree->eleEta_[eleInd_] + tree->eleDeltaEtaSC_[eleInd_],0);
	  vector<double> eleWeights_Up = eleSF->getEleSF(tree->elePt_[eleInd_],tree->eleEta_[eleInd_] + tree->eleDeltaEtaSC_[eleInd_],2);


	  _eleEffWeight    = eleWeights.at(0);
	  _eleEffWeight_Do = eleWeights_Do.at(0);
	  _eleEffWeight_Up = eleWeights_Up.at(0);

	  _eleEffWeight_IdReco    = eleWeights.at(1)    * eleWeights.at(2)   ;
	  _eleEffWeight_IdReco_Do = eleWeights_Do.at(1) * eleWeights_Do.at(2);
	  _eleEffWeight_IdReco_Up = eleWeights_Up.at(1) * eleWeights_Up.at(2);

	  _eleEffWeight_Trig    = eleWeights.at(3);
	  _eleEffWeight_Trig_Do = eleWeights_Do.at(3);
	  _eleEffWeight_Trig_Up = eleWeights_Up.at(3);

    	}
      }

      if (!isMC){
    	if (selector->bJets.size() == 0){
	  _btagWeight.push_back(1.0);
	  _btagWeight.push_back(0.0);
	  _btagWeight.push_back(0.0);
    	}				
    	if (selector->bJets.size() == 1){
	  _btagWeight.push_back(0.0);
	  _btagWeight.push_back(1.0);
	  _btagWeight.push_back(0.0);
    	}				
    	if (selector->bJets.size() >= 2){
	  _btagWeight.push_back(0.0);
	  _btagWeight.push_back(0.0);
	  _btagWeight.push_back(1.0);
    	}				
      }
      
      outputTree->Fill();
      if (entry/100000000 == 1){
    	cout << "--------------------------------------------" << endl;
    	cout << "Scale Factor Summary" << endl;
    	cout << std::setprecision(10) << "  evtWeight="<<_evtWeight << "  btagWeight=" << _btagWeight_1a << "  eleEffWeight="<<_eleEffWeight<<"  muEffWeight="<<_muEffWeight;
    	cout << "  PUscale="<<_PUweight;
    	cout<<endl;
      }
      InitVariables();
    }
  }
  outputFile->cd();
  //outputTree->Write("",kCanDelete);
  outputTree->Write();
  
  outputFile->Close();

  cout <<" Sample name2 : "  << sampletype.data()  << endl;
  PUfilename.clear();
  PUfilename_up.clear();
  PUfilename_up.clear();

  outputFile->Delete();

}

EventJetAna::~EventJetAna()
{
  
  delete l_eff;
  delete c_eff;
  delete b_eff;

  delete evtPick;
  delete selector;
  crossSections.clear();  
  delete tree;
  delete[] infile;
}

void EventJetAna::GetSampleName(char** filenames)
{
  string fname(filenames[0]);
  fname = fname.substr(fname.find_last_of("/")+1,fname.size());
  fname = fname.substr(0,fname.find("_Skim"));
  sampletype = fname;
  return ;
}

void EventJetAna::FillEvent(std::string year, bool isHemVetoObj, Long64_t ientry) //HEM test
{

  _run             = tree->run_;
  _event           = tree->event_;
  _lumis           = tree->lumis_;
  _isData	   = !isMC;
  
  _nVtx		   = tree->nVtx_;
  _nGoodVtx	   = tree->nGoodVtx_;
  
  if (useGenWeightScaling){
    _evtWeight     = _lumiWeight *  tree->genWeight_; 
  }else{
    //event weight needs to be positive or negative depending on sign of genWeight (to account for mc@nlo negative weights)
    _evtWeight     = _lumiWeight *  ((tree->genWeight_ >= 0) ? 1 : -1);  
  }
  
  if (_isData) {
    _evtWeight     = 1.;
  }

  //MC HEM test
  if(isMC && isHemVetoObj){
    _evtWeight     = _evtWeight*0.3518;
  }

  _genMET	   = tree->GenMET_pt_;
  _pfMET	   = tree->MET_pt_;
  _pfMETPhi    	   = tree->MET_phi_;
    
  _nEle		   = selector->Electrons.size();
  _nEleLoose       = selector->ElectronsLoose.size();
  _nMu		   = selector->Muons.size();
  _nMuLoose        = selector->MuonsLoose.size();
    
  _nJet            = selector->Jets.size();
  _nfwdJet         = selector->FwdJets.size();
  _nBJet           = selector->bJets.size();

  _nGenPart        = tree->nGenPart_;
  _nGenJet         = tree->nGenJet_;

  //TODO
  //        _pdfWeight       = tree->pdfWeight_;	
  
  double ht = 0.0;
  ht               += tree->MET_pt_;
  
  for( int i_jet = 0; i_jet < _nJet; i_jet++)
    ht             += tree->jetPt_[i_jet];
  _HT              = ht; 
  
  for (int i_ele = 0; i_ele <_nEle; i_ele++){
    int eleInd = selector->Electrons.at(i_ele);
    _elePt.push_back(tree->elePt_[eleInd]);
    _elePhi.push_back(tree->elePhi_[eleInd]);
    _eleSCEta.push_back(tree->eleEta_[eleInd] + tree->eleDeltaEtaSC_[eleInd]);
    
    _elePFRelIso.push_back(tree->elePFRelIso_[eleInd]);
    
    lepVector.SetPtEtaPhiM(tree->elePt_[eleInd],
			   tree->eleEta_[eleInd] + tree->eleDeltaEtaSC_[eleInd],
			   tree->elePhi_[eleInd],
			   tree->eleMass_[eleInd]);
    lepCharge      = tree->eleCharge_[eleInd];
  }


  for (int i_mu = 0; i_mu <_nMu; i_mu++){
    int muInd = selector->Muons.at(i_mu);
    _muPt.push_back(tree->muPt_[muInd]);
    _muPhi.push_back(tree->muPhi_[muInd]);
    _muEta.push_back(tree->muEta_[muInd]);
    _muPFRelIso.push_back(tree->muPFRelIso_[muInd]);

    lepVector.SetPtEtaPhiM(tree->muPt_[muInd],
			   tree->muEta_[muInd],
			   tree->muPhi_[muInd],
			   tree->muMass_[muInd]);
    lepCharge      = tree->muCharge_[muInd];
  }
  
  // if (dileptonsample){
  //   if (_nMu==2) {

  //     int muInd1 = selector->Muons.at(0);
  //     int muInd2 = selector->Muons.at(1);

  //     lepVector.SetPtEtaPhiM(tree->muPt_[muInd1],
  // 			     tree->muEta_[muInd1],
  // 			     tree->muPhi_[muInd1],
  // 			     tree->muMass_[muInd1]);
  //     lepVector2.SetPtEtaPhiM(tree->muPt_[muInd2],
  // 			      tree->muEta_[muInd2],
  // 			      tree->muPhi_[muInd2],
  // 			      tree->muMass_[muInd2]);	

  //     _DilepMass = (lepVector+lepVector2).M();
  //     _DilepDelR = lepVector.DeltaR(lepVector2);
	    
  //   }
	
	
  //   if (_nEle==2){
  //     int eleInd1 = selector->Electrons.at(0);
  //     int eleInd2 = selector->Electrons.at(1);
	    
  //     lepVector.SetPtEtaPhiM(tree->elePt_[eleInd1],
  // 			     tree->eleEta_[eleInd1],
  // 			     tree->elePhi_[eleInd1],
  // 			     tree->eleMass_[eleInd1]);
  //     lepVector2.SetPtEtaPhiM(tree->elePt_[eleInd2],
  // 			      tree->eleEta_[eleInd2],
  // 			      tree->elePhi_[eleInd2],
  // 			      tree->eleMass_[eleInd2]);
	    
  //     _DilepMass = (lepVector+lepVector2).M();
  //     _DilepDelR = lepVector.DeltaR(lepVector2);
	    
  //   }
  // }
    
  _passPresel_Ele  = evtPick->passPresel_ele;
  _passPresel_Mu   = evtPick->passPresel_mu;
  _passAll_Ele     = evtPick->passAll_ele;
  _passAll_Mu      = evtPick->passAll_mu;
  

  //int parentPID = -1;
  for (int i_jet = 0; i_jet < _nfwdJet; i_jet++){
    int jetInd = selector->FwdJets.at(i_jet);
    _fwdJetPt.push_back(tree->jetPt_[jetInd]);
    _fwdJetEta.push_back(tree->jetEta_[jetInd]);
    _fwdJetPhi.push_back(tree->jetPhi_[jetInd]);
    _fwdJetMass.push_back(tree->jetMass_[jetInd]);
  }


  jetVectors.clear();
  jetResolutionVectors.clear();
  jetBtagVectors.clear();

  for (int i_jet = 0; i_jet <_nJet; i_jet++){
		
    int jetInd = selector->Jets.at(i_jet);
    _jetPt.push_back(tree->jetPt_[jetInd]);
    _jetEta.push_back(tree->jetEta_[jetInd]);
    _jetPhi.push_back(tree->jetPhi_[jetInd]);
    _jetMass.push_back(tree->jetMass_[jetInd]);

    _jetCMVA.push_back(tree->jetBtagCMVA_[jetInd]);
    _jetCSVV2.push_back(tree->jetBtagCSVV2_[jetInd]);
    _jetDeepB.push_back(tree->jetBtagDeepB_[jetInd]);
    _jetDeepC.push_back(tree->jetBtagDeepC_[jetInd]);
	
    jetVector.SetPtEtaPhiM(tree->jetPt_[jetInd], tree->jetEta_[jetInd], tree->jetPhi_[jetInd], tree->jetMass_[jetInd]);
	
    _jetGenJetIdx.push_back(tree->jetGenJetIdx_[jetInd]);

    double resolution = selector->jet_resolution.at(i_jet);

    jetVectors.push_back(jetVector);
    jetResolutionVectors.push_back(resolution);
    jetBtagVectors.push_back(tree->jetBtagDeepB_[jetInd]);
	
    if (selector->jet_isTagged.at(i_jet)){
      //	if ( (tree->jetBtagDeepB_[jetInd]) > selector->btag_cut_DeepCSV){
      bjetVectors.push_back(jetVector);
      bjetResVectors.push_back(resolution);
    } else {
      ljetVectors.push_back(jetVector);
      ljetResVectors.push_back(resolution);
    }
  }	

  //Compute M3
  _M3 = -1.;
  double maxPt = -1;
  if (_nJet>2) {
    TLorentzVector jet1;
    TLorentzVector jet2;
    TLorentzVector jet3;
    for (int i_jet1 = 0; i_jet1 <_nJet-2; i_jet1++){
      int jetInd1 = selector->Jets.at(i_jet1);
      jet1.SetPtEtaPhiM(tree->jetPt_[jetInd1],tree->jetEta_[jetInd1],tree->jetPhi_[jetInd1],tree->jetMass_[jetInd1]);
	    
      for (int i_jet2 = i_jet1+1; i_jet2 <_nJet-1; i_jet2++){
	int jetInd2 = selector->Jets.at(i_jet2);
	jet2.SetPtEtaPhiM(tree->jetPt_[jetInd2],tree->jetEta_[jetInd2],tree->jetPhi_[jetInd2],tree->jetMass_[jetInd2]);

	for (int i_jet3 = i_jet2+1; i_jet3 <_nJet; i_jet3++){
	  int jetInd3 = selector->Jets.at(i_jet3);
	  jet3.SetPtEtaPhiM(tree->jetPt_[jetInd3],tree->jetEta_[jetInd3],tree->jetPhi_[jetInd3],tree->jetMass_[jetInd3]);

	  if ((jet1 + jet2 + jet3).Pt()>maxPt){
	    _M3 = (jet1 + jet2 + jet3).M();
	    maxPt=(jet1 + jet2 + jet3).Pt();
	  }
		    
	}
      }
    }
  }
  
  // // Calculate MET z
  metZ.SetLepton(lepVector);
  
  if(_passPresel_Ele)
    metZ.SetLeptonType("electron");
  if(_passPresel_Mu)
    metZ.SetLeptonType("muon");

  METVector.SetPtEtaPhiM(tree->MET_pt_,
  			   0.,
  			   tree->MET_phi_,
  			   0.);
  
  metZ.SetMET(METVector);
  
  //Calculate transverse mass variables
  //W transverse mass		
  
  _WtransMass = TMath::Sqrt(2*lepVector.Pt()*tree->MET_pt_*( 1.0 - TMath::Cos( lepVector.DeltaPhi(METVector))));
  
  // TLorentzVector tempLep;
  // tempLep.SetPtEtaPhiM(lepVector.Pt(),
  // 			 lepVector.Eta(),
  // 			 lepVector.Phi(),
  // 			 0.1056);
  
  _nu_px = METVector.Px();
  _nu_py = METVector.Py();
  _nu_pz = metZ.Calculate();
  _nu_pz_other = metZ.getOther();
  
  METVector.SetPz(_nu_pz);

  // cout << _nu_pz << "   ----   " << _nu_pz_other << endl;

  // for (int __j = 0; __j < isBjet.size(); __j++){
  // 	if (isBjet.at(__j)) b_ind.push_back(__j);
  // 	else j_ind.push_back(__j);
  // }
    

  // topEvent.SetBJetVector(bjetVectors);
  // topEvent.SetLJetVector(ljetVectors);
  // topEvent.SetLepton(lepVector);
  // topEvent.SetMET(METVector);
    
  // topEvent.SetBJetResVector(bjetResVectors);
  // topEvent.SetLJetResVector(ljetResVectors);
  // topEvent.SetIgnoreBtag(true);

  topEvent.SetJetVector(jetVectors);
  topEvent.SetJetResVector(jetResolutionVectors);
  topEvent.SetBtagVector(jetBtagVectors);

  topEvent.SetLepton(lepVector);
  topEvent.SetMET(METVector);
  
  
  topEvent.Calculate();
  
  if (topEvent.GoodCombination()){
    bhad = jetVectors[topEvent.getBHad()];
    blep = jetVectors[topEvent.getBLep()];
    Wj1 = jetVectors[topEvent.getJ1()];
    Wj2 = jetVectors[topEvent.getJ2()];
    METVector.SetPz(topEvent.getNuPz());
    
    _chi2 = topEvent.getChi2();
    _M_bjj = ( bhad + Wj1 + Wj2 ).M();
    _M_jj  = ( Wj1 + Wj2 ).M();
	
    _TopHad_pt = ( bhad + Wj1 + Wj2 ).Pt();
    _TopHad_eta = ( bhad + Wj1 + Wj2 ).Eta();
    _TopLep_pt = ( blep + lepVector + METVector ).Pt();
    _TopLep_eta = ( blep + lepVector + METVector ).Eta();
    _TopLep_charge = lepCharge;

    _MassCuts = (_M_bjj > 160 && 
		 _M_bjj < 180 && 
		 _M_jj > 70 &&
		 _M_jj < 90);

    _blep_id  = int(topEvent.getBLep());
    _bhad_id  = int(topEvent.getBHad());
  }
    
  ljetVectors.clear();
  bjetVectors.clear();
    
  ljetResVectors.clear();
  bjetResVectors.clear();
    
    
  if (isMC){

    // Float_t LHE scale variation weights (w_var / w_nominal); 
    // [0] is mur=0.5 muf=0.5 ; 
    // [1] is mur=0.5 muf=1 ; 
    // [2] is mur=0.5 muf=2 ; 
    // [3] is mur=1 muf=0.5 ; 
    // [4] is mur=1 muf=1 ; 
    // [5] is mur=1 muf=2 ; 
    // [6] is mur=2 muf=0.5 ; 
    // [7] is mur=2 muf=1 ; 
    // [8] is mur=2 muf=2 

    _q2weight_Up = 1.;
    _q2weight_Do = 1.;

    if (tree->nLHEScaleWeight_==9){
      for (int i = 0; i < 9; i++){
	if(i==2||i==6){continue;}
	_genScaleSystWeights.push_back(tree->LHEScaleWeight_[i]);
      }
      double nomWeight=tree->LHEScaleWeight_[4];
      if (nomWeight!=0){
	_q2weight_Up = *max_element(_genScaleSystWeights.begin(), _genScaleSystWeights.end())/nomWeight;
	_q2weight_Do = *min_element(_genScaleSystWeights.begin(), _genScaleSystWeights.end())/nomWeight;
      }
    }

    if (tree->nLHEScaleWeight_==44){
      _genScaleSystWeights.push_back(tree->LHEScaleWeight_[0]);
      _genScaleSystWeights.push_back(tree->LHEScaleWeight_[5]);
      _genScaleSystWeights.push_back(tree->LHEScaleWeight_[15]);
      _genScaleSystWeights.push_back(tree->LHEScaleWeight_[24]);
      _genScaleSystWeights.push_back(tree->LHEScaleWeight_[34]);
      _genScaleSystWeights.push_back(tree->LHEScaleWeight_[39]);

      _q2weight_Up = *max_element(_genScaleSystWeights.begin(), _genScaleSystWeights.end());
      _q2weight_Do = *min_element(_genScaleSystWeights.begin(), _genScaleSystWeights.end());
    }

    double pdfMean = 0.;
    for (int j=0; j < int(tree->nLHEPdfWeight_); j++ ){
      _pdfSystWeight.push_back(tree->LHEPdfWeight_[j]);
      pdfMean += tree->LHEPdfWeight_[j];
    }
    pdfMean = pdfMean/_pdfSystWeight.size();
	    
    double pdfVariance = 0.;
    for (int j=0; j < int(_pdfSystWeight.size()); j++){
      pdfVariance += pow((_pdfSystWeight[j]-pdfMean),2.);
    }

    if (TMath::AreEqualAbs(pdfMean,0.0,1.0e-7)) 
      pdfMean = 1;

    _pdfuncer = sqrt(pdfVariance/_pdfSystWeight.size())/pdfMean;
    _pdfweight_Up = (1. + _pdfuncer);
    _pdfweight_Do = (1. - _pdfuncer);

    _ISRweight_Up = 1.;
    _ISRweight_Do = 1.;

    _FSRweight_Up = 1.;
    _FSRweight_Do = 1.;
	
    if (tree->nPSWeight_==4){
      if (tree->genWeight_ != 0){
	_ISRweight_Up = tree->PSWeight_[2];
	_ISRweight_Do = tree->PSWeight_[0];

	_FSRweight_Up = tree->PSWeight_[3];
	_FSRweight_Do = tree->PSWeight_[1];
      }
    }

  }

    
    
  for (int i_mc = 0; i_mc <_nGenPart; i_mc++){
    _genPt.push_back(tree->GenPart_pt_[i_mc]);
    _genPhi.push_back(tree->GenPart_phi_[i_mc]);
    _genEta.push_back(tree->GenPart_eta_[i_mc]);
    _genMass.push_back(tree->GenPart_mass_[i_mc]);
    _genStatus.push_back(tree->GenPart_status_[i_mc]);
    _genStatusFlag.push_back(tree->GenPart_statusFlags_[i_mc]);
    _genPDGID.push_back(tree->GenPart_pdgId_[i_mc]);
    _genMomIdx.push_back(tree->GenPart_genPartIdxMother_[i_mc]);
  }

  for (int i_genJet = 0; i_genJet < _nGenJet; i_genJet++){
    _genJetPt.push_back(tree->GenJet_pt_[i_genJet]);
    _genJetEta.push_back(tree->GenJet_eta_[i_genJet]);
    _genJetPhi.push_back(tree->GenJet_phi_[i_genJet]);
    _genJetMass.push_back(tree->GenJet_mass_[i_genJet]);
  }
}

// https://twiki.cern.ch/twiki/bin/viewauth/CMS/TopPtReweighting
double EventJetAna::SFtop(double pt){
    return exp(0.0615 - 0.0005*pt);
}

double EventJetAna::topPtWeight(){
    double toppt=0.0;
    double antitoppt=0.0;
    double weight = 1.0;

    // TODO needs to be reimplemented with NANOAOD
    for(int mcInd=0; mcInd< int(tree->nGenPart_) ; ++mcInd){
    	if(tree->GenPart_pdgId_[mcInd]==6  && tree->GenPart_statusFlags_[mcInd]>>13&1) toppt = tree->GenPart_pt_[mcInd];
    	if(tree->GenPart_pdgId_[mcInd]==-6 && tree->GenPart_statusFlags_[mcInd]>>13&1) antitoppt = tree->GenPart_pt_[mcInd];
    }
    if(toppt > 0.001 && antitoppt > 0.001)
	weight = sqrt( SFtop(toppt) * SFtop(antitoppt) );
    
    //This has been changed, the new prescription is to not use the top pt reweighting, and the syst is using it
    return weight;
    
}

void EventJetAna::loadBtagEff(string sampleName, string year){
    std::string fName = "weight/BtagSF/btag_efficiencies_"+year+".root";
    std::string effType = "Other";
    if (sampletype.find("TTGamma") != std::string::npos){
	effType = "Top";
    }
    if (sampletype.find("TTbar") != std::string::npos){
	effType = "Top";
    }
    
    std::string leffName = effType+"_l_efficiency";
    std::string ceffName = effType+"_c_efficiency";
    std::string beffName = effType+"_b_efficiency";

    TFile* inputFile = TFile::Open(fName.c_str(),"read");
    l_eff = (TH2D*) inputFile->Get(leffName.c_str());
    c_eff = (TH2D*) inputFile->Get(ceffName.c_str());
    b_eff = (TH2D*) inputFile->Get(beffName.c_str());
}				   

float EventJetAna::getBtagSF_1a(string sysType, BTagCalibrationReader reader, bool verbose){

    double weight = 1.0;

    double jetPt;
    double jetEta;
    double jetBtag;
    int jetFlavor;
    double SFb;
    double Eff;

    double pMC=1;
    double pData=1;
	
    string b_sysType = "central";
    string l_sysType = "central";
    if (sysType=="b_up"){
	b_sysType = "up";
    } else if (sysType=="b_down"){
	b_sysType = "down";
    } else if (sysType=="l_up"){
	l_sysType = "up";
    } else if (sysType=="l_down"){
	l_sysType = "down";
    }	
    if (verbose){
	cout << "Btagging Scale Factors"<<endl;
    }

    for(std::vector<int>::const_iterator jetInd = selector->Jets.begin(); jetInd != selector->Jets.end(); jetInd++){

	jetPt = tree->jetPt_[*jetInd];
	jetEta = fabs(tree->jetEta_[*jetInd]);
	jetFlavor = abs(tree->jetHadFlvr_[*jetInd]);
	jetBtag = tree->jetBtagDeepB_[*jetInd];

	if (jetFlavor == 5){
	    SFb = reader.eval_auto_bounds(b_sysType, BTagEntry::FLAV_B, jetEta, jetPt); 
	    int xbin = b_eff->GetXaxis()->FindBin(min(jetPt,799.));
	    int ybin = b_eff->GetYaxis()->FindBin(abs(jetEta));
	    Eff = b_eff->GetBinContent(xbin,ybin);
	}
	else if(jetFlavor == 4){
	    SFb = reader.eval_auto_bounds(b_sysType, BTagEntry::FLAV_C, jetEta, jetPt); 
	    int xbin = c_eff->GetXaxis()->FindBin(min(jetPt,799.));
	    int ybin = c_eff->GetYaxis()->FindBin(abs(jetEta));
	    Eff = c_eff->GetBinContent(xbin,ybin);
	}
	else {
	    SFb = reader.eval_auto_bounds(l_sysType, BTagEntry::FLAV_UDSG, jetEta, jetPt); 
	    int xbin = l_eff->GetXaxis()->FindBin(min(jetPt,799.));
	    int ybin = l_eff->GetYaxis()->FindBin(abs(jetEta));
	    Eff = l_eff->GetBinContent(xbin,ybin);
	}

	if (jetBtag>selector->btag_cut_DeepCSV){
	    pMC *= Eff;
	    pData *= Eff*SFb;
	} else {
	    pMC *= 1. - Eff;
	    pData *= 1. - (Eff*SFb);
	}
	if (verbose){
	    cout << "    jetPt="<<jetPt<<"  jetEta="<<jetEta<<"  jetFlavor="<<jetFlavor<<"  jetBtag="<<jetBtag<<"  Tagged="<<(jetBtag>selector->btag_cut_DeepCSV)<<"  Eff="<<Eff<<"  SF="<<SFb<<endl;
	    cout << "          --p(MC)="<<pMC<<"  --p(Data)="<<pData << endl;
	}
    }

    //    weight = pData/pMC;
    if (pMC==0){
	//      cout << "Inf weight" << endl;
	//	cout << pData << " / " << pMC << endl;
	weight = 0.;
    } else {
	weight = pData/pMC;
    }
    if (verbose){
	cout << "  FinalWeight="<<weight<<endl;
    }

    return weight;

}


vector<float> EventJetAna::getBtagSF_1c(string sysType, BTagCalibrationReader reader, vector<float> &btagSF){

    // Saving weights w(0|n), w(1|n), w(2|n)
    vector<float> btagWeights;

    double weight0tag = 1.0; 		//w(0|n)
    double weight1tag = 0.0;		//w(1|n)

    double jetPt;
    double jetEta;
    int jetFlavor;
    double SFb;
	
    string b_sysType = "central";
    string l_sysType = "central";
    if (sysType=="b_up"){
	b_sysType = "up";
    } else if (sysType=="b_down"){
	b_sysType = "down";
    } else if (sysType=="l_up"){
	l_sysType = "up";
    } else if (sysType=="l_down"){
	l_sysType = "down";
    }	


    for(std::vector<int>::const_iterator bjetInd = selector->bJets.begin(); bjetInd != selector->bJets.end(); bjetInd++){
	jetPt = tree->jetPt_[*bjetInd];
	jetEta = fabs(tree->jetEta_[*bjetInd]);
	jetFlavor = abs(tree->jetHadFlvr_[*bjetInd]);
		
	if (jetFlavor == 5) SFb = reader.eval_auto_bounds(b_sysType, BTagEntry::FLAV_B, jetEta, jetPt); 
	else if(jetFlavor == 4) SFb = reader.eval_auto_bounds(b_sysType, BTagEntry::FLAV_C, jetEta, jetPt); 
	else {
	    SFb = reader.eval_auto_bounds(l_sysType, BTagEntry::FLAV_UDSG, jetEta, jetPt); 
	}

	btagSF.push_back(SFb);
    }

    if(selector->bJets.size() == 0) {
	btagWeights.push_back(1.0);
	btagWeights.push_back(0.0);
	btagWeights.push_back(0.0);

	return btagWeights;

    } else if (selector->bJets.size() == 1) {
	btagWeights.push_back(1-btagSF.at(0));
	btagWeights.push_back(btagSF.at(0));
	btagWeights.push_back(0.0);
		
	return btagWeights;

    } else {

	// We are following the method 1SFc from the twiki
	// https://twiki.cern.ch/twiki/bin/viewauth/CMS/BTagSFMethods#1c_Event_reweighting_using_scale
      for (int i = 0; i < int((selector->bJets).size()); i++){
	SFb = btagSF.at(i);
	weight0tag *= 1.0 - SFb;
	double prod = SFb;
	for (int j = 0; j < int((selector->bJets).size()); j++){
	  if (j==i) {continue;}
	  prod *= (1.-btagSF.at(j));
	}
	weight1tag += prod;
      }
      btagWeights.push_back(weight0tag);
      btagWeights.push_back(weight1tag);
      btagWeights.push_back(1.0 - weight0tag - weight1tag);
      return btagWeights;
    }
}

#endif

int main(){
  EventJetAna a;
  return 0;
}

// int main(int ac, char** av){
//   EventJetAna(ac, av);
//   return 0;
// }

