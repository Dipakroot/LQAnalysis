#include<iostream>
#include"../interface/EventTree.h"

#include<iostream>
#include"../interface/EventTree.h"

EventTree::EventTree(TTree *tr, string year, bool isData)
{
  
  chain = 0x0;
  tree = tr;
  isData_ = isData;
  
  cout<< "tree pointer : " << tree << endl; 

  //std::cout << tree->GetCacheSize() << std::endl;
  tree->SetCacheSize(100*1024*1024);
  tree->SetBranchStatus("*",0);
	
  // keep some important branches
  tree->SetBranchStatus("PV_ndof",1);
  tree->SetBranchAddress("PV_ndof", &pvNDOF_);

  tree->SetBranchStatus("PV_x",1);
  tree->SetBranchAddress("PV_x", &pvX_);

  tree->SetBranchStatus("PV_y",1);
  tree->SetBranchAddress("PV_y", &pvY_);

  tree->SetBranchStatus("PV_z",1);
  tree->SetBranchAddress("PV_z", &pvZ_);

  tree->SetBranchStatus("PV_chi2",1);
  tree->SetBranchAddress("PV_chi2", &pvChi2_);

  if (!isData_){
    tree->SetBranchStatus("Pileup_nPU",1);
    tree->SetBranchAddress("Pileup_nPU", &nPU_);
	
    tree->SetBranchStatus("Pileup_nTrueInt",1);
    tree->SetBranchAddress("Pileup_nTrueInt", &nPUTrue_);
  }

	
  // event
	
  tree->SetBranchStatus("run",1);
  tree->SetBranchAddress("run", &run_);

  tree->SetBranchStatus("event",1);
  tree->SetBranchAddress("event", &event_);
	
  tree->SetBranchStatus("luminosityBlock",1);
  tree->SetBranchAddress("luminosityBlock", &lumis_);

  tree->SetBranchStatus("PV_npvs",1);
  tree->SetBranchAddress("PV_npvs", &nVtx_);

  tree->SetBranchStatus("PV_npvsGood",1);
  tree->SetBranchAddress("PV_npvsGood", &nGoodVtx_);
  
  tree->SetBranchStatus("L1PreFiringWeight_Nom",1);
  tree->SetBranchAddress("L1PreFiringWeight_Nom", &L1PreFiringWeight_Nom_);
  
  tree->SetBranchStatus("L1PreFiringWeight_Up",1);
  tree->SetBranchAddress("L1PreFiringWeight_Up", &L1PreFiringWeight_Up_);

  tree->SetBranchStatus("L1PreFiringWeight_Dn",1);
  tree->SetBranchAddress("L1PreFiringWeight_Dn", &L1PreFiringWeight_Dn_);

  if (!isData_){
    tree->SetBranchStatus("Generator_weight",1);
    tree->SetBranchAddress("Generator_weight", &genWeight_);
    tree->SetBranchStatus("nLHEScaleWeight",1);
    tree->SetBranchAddress("nLHEScaleWeight", &nLHEScaleWeight_);
    
    tree->SetBranchStatus("LHEScaleWeight",1);
    tree->SetBranchAddress("LHEScaleWeight", &LHEScaleWeight_);
    
    tree->SetBranchStatus("nLHEPdfWeight",1);
    tree->SetBranchAddress("nLHEPdfWeight", &nLHEPdfWeight_);
    
    tree->SetBranchStatus("LHEPdfWeight",1);
    tree->SetBranchAddress("LHEPdfWeight", &LHEPdfWeight_);

    tree->SetBranchStatus("PSWeight",1);
    tree->SetBranchAddress("PSWeight", &PSWeight_);
	
    tree->SetBranchStatus("nPSWeight",1);
    tree->SetBranchAddress("nPSWeight", &nPSWeight_);
  }

  // MET
  tree->SetBranchStatus("MET_pt",1);
  tree->SetBranchAddress("MET_pt", &MET_pt_);

  tree->SetBranchStatus("MET_phi",1);
  tree->SetBranchAddress("MET_phi", &MET_phi_);

  if (!isData_){
    tree->SetBranchStatus("GenMET_pt",1);
    tree->SetBranchAddress("GenMET_pt", &GenMET_pt_);
	
    tree->SetBranchStatus("GenMET_phi",1);
    tree->SetBranchAddress("GenMET_phi", &GenMET_phi_);
  }

	
  // electrons	
	
  tree->SetBranchStatus("nElectron",1);
  tree->SetBranchAddress("nElectron", &nEle_);


  tree->SetBranchStatus("Electron_charge",1);
  tree->SetBranchAddress("Electron_charge", &eleCharge_);	

  tree->SetBranchStatus("Electron_pt",1);
  tree->SetBranchAddress("Electron_pt", &elePt_);

  tree->SetBranchStatus("Electron_deltaEtaSC",1);
  tree->SetBranchAddress("Electron_deltaEtaSC", &eleDeltaEtaSC_);

  tree->SetBranchStatus("Electron_eta",1);
  tree->SetBranchAddress("Electron_eta", &eleEta_);

  tree->SetBranchStatus("Electron_phi",1);
  tree->SetBranchAddress("Electron_phi", &elePhi_);

  tree->SetBranchStatus("Electron_mass",1);
  tree->SetBranchAddress("Electron_mass", &eleMass_);

  tree->SetBranchStatus("Electron_pfRelIso03_chg",1);
  tree->SetBranchAddress("Electron_pfRelIso03_chg", &elePFRelChIso_);

  tree->SetBranchStatus("Electron_pfRelIso03_all",1);
  tree->SetBranchAddress("Electron_pfRelIso03_all", &elePFRelIso_);

  tree->SetBranchStatus("Electron_sieie",1);
  tree->SetBranchAddress("Electron_sieie", &eleSIEIE_);
	
  tree->SetBranchStatus("Electron_cutBased",1); 
  tree->SetBranchAddress("Electron_cutBased", &eleIDcutbased_);
  
  tree->SetBranchStatus("Electron_vidNestedWPBitmap",1);
  tree->SetBranchAddress("Electron_vidNestedWPBitmap", &eleVidWPBitmap_);

  tree->SetBranchStatus("Electron_mvaFall17V2noIso_WPL",1); 
  tree->SetBranchAddress("Electron_mvaFall17V2noIso_WPL", &eleIDmvaLoose_);

  tree->SetBranchStatus("Electron_mvaFall17V2noIso_WP80",1); 
  tree->SetBranchAddress("Electron_mvaFall17V2noIso_WP80", &eleIDmvaWP80_);

  tree->SetBranchStatus("Electron_mvaFall17V2noIso_WP90",1); 
  tree->SetBranchAddress("Electron_mvaFall17V2noIso_WP90", &eleIDmvaWP90_);

  tree->SetBranchStatus("Electron_dxy",1);
  tree->SetBranchAddress("Electron_dxy", &eleD0_);

  tree->SetBranchStatus("Electron_dz",1);
  tree->SetBranchAddress("Electron_dz", &eleDz_);

    
  tree->SetBranchStatus("Electron_dr03EcalRecHitSumEt",1);
  tree->SetBranchAddress("Electron_dr03EcalRecHitSumEt", &eleEcalSumEtDr03_);

  tree->SetBranchStatus("Electron_dr03HcalDepth1TowerSumEt",1);
  tree->SetBranchAddress("Electron_dr03HcalDepth1TowerSumEt", &eleHcalSumEtDr03_);

  tree->SetBranchStatus("Electron_dr03TkSumPt",1);
  tree->SetBranchAddress("Electron_dr03TkSumPt", &eleTrkSumPtDr03_);

  // muons
  // keep some branches in the skim
	
  tree->SetBranchStatus("nMuon",1);
  tree->SetBranchAddress("nMuon", &nMuon_);

  tree->SetBranchStatus("Muon_charge",1);
  tree->SetBranchAddress("Muon_charge", &muCharge_);
	
  tree->SetBranchStatus("Muon_pt",1);
  tree->SetBranchAddress("Muon_pt", &muPt_);

  tree->SetBranchStatus("Muon_eta",1);
  tree->SetBranchAddress("Muon_eta", &muEta_);

  tree->SetBranchStatus("Muon_phi",1);
  tree->SetBranchAddress("Muon_phi", &muPhi_);

  tree->SetBranchStatus("Muon_mass",1);
  tree->SetBranchAddress("Muon_mass", &muMass_);
  
  // tree->SetBranchStatus("Muon_pfRelIso04_all",1);
  // tree->SetBranchAddress("Muon_pfRelIso04_all", &muPFRelIso_);
  
  tree->SetBranchStatus("Muon_pfRelIso03_all",1);
  tree->SetBranchAddress("Muon_pfRelIso03_all", &muPFRelIso_);

  tree->SetBranchStatus("Muon_tightId",1);
  tree->SetBranchAddress("Muon_tightId", &muTightId_);

  tree->SetBranchStatus("Muon_mediumId",1);
  tree->SetBranchAddress("Muon_mediumId", &muMediumId_);

  tree->SetBranchStatus("Muon_looseId",1);
  tree->SetBranchAddress("Muon_looseId", &muLooseId_);

  tree->SetBranchStatus("Muon_mediumPromptId",1);
  tree->SetBranchAddress("Muon_mediumPromptId", &muMediumPromptId_);

  tree->SetBranchStatus("Muon_isPFcand",1);
  tree->SetBranchAddress("Muon_isPFcand", &muIsPFMuon_);

  tree->SetBranchStatus("Muon_isGlobal",1);
  tree->SetBranchAddress("Muon_isGlobal", &muIsGlobal_);

  tree->SetBranchStatus("Muon_isTracker",1);
  tree->SetBranchAddress("Muon_isTracker", &muIsTracker_);

  tree->SetBranchStatus("Muon_dxy",1);
  tree->SetBranchAddress("Muon_dxy", &mudxy_);

  tree->SetBranchStatus("Muon_dz",1);
  tree->SetBranchAddress("Muon_dz", &mudz_);

  tree->SetBranchStatus("Muon_nTrackerLayers",1);
  tree->SetBranchAddress("Muon_nTrackerLayers", &munTrackerLayers_);

  tree->SetBranchStatus("Muon_genPartIdx",1);
  tree->SetBranchAddress("Muon_genPartIdx", &muGenPartIdx_);
  
  //For Taus -Analysis
  tree->SetBranchStatus("nTau",1);
  tree->SetBranchAddress("nTau", &nTau_);

  tree->SetBranchStatus("Tau_charge",1);
  tree->SetBranchAddress("Tau_charge", &tauCharge_);

  tree->SetBranchStatus("Tau_decayMode",1);
  tree->SetBranchAddress("Tau_decayMode", &tauDecayMode_);

  tree->SetBranchStatus("Tau_dxy",1);
  tree->SetBranchAddress("Tau_dxy", &tauDxy_);

  tree->SetBranchStatus("Tau_dz",1);
  tree->SetBranchAddress("Tau_dz", &tauDz_);

  tree->SetBranchStatus("Tau_eta",1);
  tree->SetBranchAddress("Tau_eta", &tauEta_);

  //chain->SetBranchStatus("Tau_idDecayMode",1);
  //chain->SetBranchAddress("Tau_idDecayMode", &tau_idDecayMode_);

  //chain->SetBranchStatus("Tau_idDecayModeNewDMs",1);
  //chain->SetBranchAddress("Tau_idDecayModeNewDMs", &tau_idDecayModeNewDMs_);

  tree->SetBranchStatus("Tau_idDeepTau2017v2p1VSe",1);
  tree->SetBranchAddress("Tau_idDeepTau2017v2p1VSe", &tauIdDeepTau2017v2p1VSe_);

  tree->SetBranchStatus("Tau_idDeepTau2017v2p1VSjet",1);
  tree->SetBranchAddress("Tau_idDeepTau2017v2p1VSjet", &tauIdDeepTau2017v2p1VSjet_);

  tree->SetBranchStatus("Tau_idDeepTau2017v2p1VSmu",1);
  tree->SetBranchAddress("Tau_idDeepTau2017v2p1VSmu", &tauIdDeepTau2017v2p1VSmu_);

  tree->SetBranchStatus("Tau_mass",1);
  tree->SetBranchAddress("Tau_mass", &tauMass_);

  tree->SetBranchStatus("Tau_phi",1);
  tree->SetBranchAddress("Tau_phi", &tauPhi_);

  tree->SetBranchStatus("Tau_pt",1);
  tree->SetBranchAddress("Tau_pt", &tauPt_);

  tree->SetBranchStatus("Tau_rawDeepTau2017v2p1VSe",1);
  tree->SetBranchAddress("Tau_rawDeepTau2017v2p1VSe", &tauRawDeepTau2017v2p1VSe_);

  tree->SetBranchStatus("Tau_rawDeepTau2017v2p1VSjet",1);
  tree->SetBranchAddress("Tau_rawDeepTau2017v2p1VSjet", &tauRawDeepTau2017v2p1VSjet_);

  tree->SetBranchStatus("Tau_rawDeepTau2017v2p1VSmu",1);
  tree->SetBranchAddress("Tau_rawDeepTau2017v2p1VSmu", &tauRawDeepTau2017v2p1VSmu_);

  tree->SetBranchStatus("Tau_genPartFlav",1);
  tree->SetBranchAddress("Tau_genPartFlav", &tauGenPartFlav_);

  // jets
	
  tree->SetBranchStatus("nJet",1);
  tree->SetBranchAddress("nJet", &nJet_);
 
  tree->SetBranchStatus("Jet_pt",1);
  tree->SetBranchAddress("Jet_pt", &jetPt_);

  tree->SetBranchStatus("Jet_rawFactor",1);
  tree->SetBranchAddress("Jet_rawFactor", &jetRawFactor_);
	
  tree->SetBranchStatus("Jet_eta",1);
  tree->SetBranchAddress("Jet_eta", &jetEta_);
	
  tree->SetBranchStatus("Jet_phi",1);
  tree->SetBranchAddress("Jet_phi", &jetPhi_);

  tree->SetBranchStatus("Jet_mass",1);
  tree->SetBranchAddress("Jet_mass", &jetMass_);

  tree->SetBranchStatus("Jet_jetId",1);
  tree->SetBranchAddress("Jet_jetId", &jetID_);

  tree->SetBranchStatus("Jet_puId",1);
  tree->SetBranchAddress("Jet_puId", &jetPUID_);

  tree->SetBranchStatus("Jet_puIdDisc",1);
  tree->SetBranchAddress("Jet_puIdDisc", &jetpuIdDisc_);

  tree->SetBranchStatus("Jet_area",1);
  tree->SetBranchAddress("Jet_area", &jetArea_);

  tree->SetBranchStatus("Jet_btagCMVA",1);
  tree->SetBranchAddress("Jet_btagCMVA", &jetBtagCMVA_);

  tree->SetBranchStatus("Jet_btagCSVV2",1);
  tree->SetBranchAddress("Jet_btagCSVV2", &jetBtagCSVV2_);
  
  tree->SetBranchStatus("Jet_btagDeepB",1);
  tree->SetBranchAddress("Jet_btagDeepB", &jetBtagDeepB_);
  
  tree->SetBranchStatus("Jet_btagDeepCvB",1);
  tree->SetBranchAddress("Jet_btagDeepCvB", &jetBtagDeepCvB_);
  
  tree->SetBranchStatus("Jet_btagDeepCvL",1);
  tree->SetBranchAddress("Jet_btagDeepCvL", &jetBtagDeepCvL_);
  
  // tree->SetBranchStatus("Jet_btagDeepC",1);
  // tree->SetBranchAddress("Jet_btagDeepC", &jetBtagDeepC_);
  
  tree->SetBranchStatus("Jet_btagDeepFlavB",1);
  tree->SetBranchAddress("Jet_btagDeepFlavB", &jetBtagDeepFlavB_);
  
  tree->SetBranchStatus("Jet_btagDeepFlavCvB",1);
  tree->SetBranchAddress("Jet_btagDeepFlavCvB", &jetBtagDeepFlavCvB_);
  
  tree->SetBranchStatus("Jet_btagDeepFlavCvL",1);
  tree->SetBranchAddress("Jet_btagDeepFlavCvL", &jetBtagDeepFlavCvL_);
  
  tree->SetBranchStatus("Jet_chEmEF",1);
  tree->SetBranchAddress("Jet_chEmEF", &jetchEmEF_);

  tree->SetBranchStatus("Jet_neEmEF",1);
  tree->SetBranchAddress("Jet_neEmEF", &jetneEmEF_);

  tree->SetBranchStatus("Jet_chHEF",1);
  tree->SetBranchAddress("Jet_chHEF", &jetchHEF_);

  tree->SetBranchStatus("Jet_neHEF",1);
  tree->SetBranchAddress("Jet_neHEF", &jetneHEF_);

  if (!isData_){
    tree->SetBranchStatus("Jet_partonFlavour",1);
    tree->SetBranchAddress("Jet_partonFlavour", &jetPartFlvr_);

    tree->SetBranchStatus("Jet_hadronFlavour",1);
    tree->SetBranchAddress("Jet_hadronFlavour", &jetHadFlvr_);
	
    tree->SetBranchStatus("Jet_genJetIdx",1);
    tree->SetBranchAddress("Jet_genJetIdx", &jetGenJetIdx_);
  }

  // Gen Partons
  if (!isData_){

    tree->SetBranchStatus("nLHEPart",1);
    tree->SetBranchAddress("nLHEPart", &nLHEPart_);

    tree->SetBranchStatus("LHEPart_pdgId",1);
    tree->SetBranchAddress("LHEPart_pdgId", &LHEPart_pdgId_);

    tree->SetBranchStatus("LHEPart_pt",1);
    tree->SetBranchAddress("LHEPart_pt", &LHEPart_pt_);

    tree->SetBranchStatus("LHEPart_eta",1);
    tree->SetBranchAddress("LHEPart_eta", &LHEPart_eta_);

    tree->SetBranchStatus("LHEPart_phi",1);
    tree->SetBranchAddress("LHEPart_phi", &LHEPart_phi_);

    tree->SetBranchStatus("LHEPart_mass",1);
    tree->SetBranchAddress("LHEPart_mass", &LHEPart_mass_);

    tree->SetBranchStatus("nGenPart",1);
    tree->SetBranchAddress("nGenPart", &nGenPart_);
	
    tree->SetBranchStatus("GenPart_pt",1);
    tree->SetBranchAddress("GenPart_pt", &GenPart_pt_);
	
    tree->SetBranchStatus("GenPart_eta",1);
    tree->SetBranchAddress("GenPart_eta", &GenPart_eta_);
	
    tree->SetBranchStatus("GenPart_phi",1);
    tree->SetBranchAddress("GenPart_phi", &GenPart_phi_);

    tree->SetBranchStatus("GenPart_mass",1);
    tree->SetBranchAddress("GenPart_mass", &GenPart_mass_);

    tree->SetBranchStatus("GenPart_genPartIdxMother",1);
    tree->SetBranchAddress("GenPart_genPartIdxMother", &GenPart_genPartIdxMother_);

    tree->SetBranchStatus("GenPart_pdgId",1);
    tree->SetBranchAddress("GenPart_pdgId", &GenPart_pdgId_);
	
    tree->SetBranchStatus("GenPart_status",1);
    tree->SetBranchAddress("GenPart_status", &GenPart_status_);
	
    tree->SetBranchStatus("GenPart_statusFlags",1);
    tree->SetBranchAddress("GenPart_statusFlags", &GenPart_statusFlags_);
    

    tree->SetBranchStatus("nGenJet",1);
    tree->SetBranchAddress("nGenJet", &nGenJet_);
	
    tree->SetBranchStatus("GenJet_pt",1);
    tree->SetBranchAddress("GenJet_pt", &GenJet_pt_);

    tree->SetBranchStatus("GenJet_eta",1);
    tree->SetBranchAddress("GenJet_eta", &GenJet_eta_);

    tree->SetBranchStatus("GenJet_phi",1);
    tree->SetBranchAddress("GenJet_phi", &GenJet_phi_);
 
    tree->SetBranchStatus("GenJet_mass",1);
    tree->SetBranchAddress("GenJet_mass", &GenJet_mass_);

    tree->SetBranchStatus("GenJet_partonFlavour",1);
    tree->SetBranchAddress("GenJet_partonFlavour", &GenJet_partonFlavour_);
	
    tree->SetBranchStatus("GenJet_hadronFlavour",1);
    tree->SetBranchAddress("GenJet_hadronFlavour", &GenJet_hadronFlavour_);
  }

  //Fliters
  tree->SetBranchStatus("Flag_goodVertices",1);
  tree->SetBranchAddress("Flag_goodVertices",&Flag_goodVertices_);

  tree->SetBranchStatus("Flag_globalSuperTightHalo2016Filter",1);
  tree->SetBranchAddress("Flag_globalSuperTightHalo2016Filter", &Flag_globalSuperTightHalo2016Filter_);

  tree->SetBranchStatus("Flag_HBHENoiseFilter",1);
  tree->SetBranchAddress("Flag_HBHENoiseFilter", &Flag_HBHENoiseFilter_);

  tree->SetBranchStatus("Flag_HBHENoiseIsoFilter",1);
  tree->SetBranchAddress("Flag_HBHENoiseIsoFilter", &Flag_HBHENoiseIsoFilter_);

  tree->SetBranchStatus("Flag_EcalDeadCellTriggerPrimitiveFilter",1);
  tree->SetBranchAddress("Flag_EcalDeadCellTriggerPrimitiveFilter", &Flag_EcalDeadCellTriggerPrimitiveFilter_);

  tree->SetBranchStatus("Flag_BadPFMuonFilter",1);
  tree->SetBranchAddress("Flag_BadPFMuonFilter",&Flag_BadPFMuonFilter_);

  if(year =="2017" || year == "2018"){
    tree->SetBranchStatus("Flag_ecalBadCalibFilter",1);
    tree->SetBranchAddress("Flag_ecalBadCalibFilter",&Flag_ecalBadCalibFilter_);
  }

  //TRIGGERS

  if (year=="2016"){
    tree->SetBranchStatus("HLT_Ele27_WPTight_Gsf",1);
    tree->SetBranchAddress("HLT_Ele27_WPTight_Gsf",&HLT_Ele27_WPTight_Gsf_);
	
    // tree->SetBranchStatus("HLT_Ele105_CaloIdVT_GsfTrkIdT",1);
    // tree->SetBranchAddress("HLT_Ele105_CaloIdVT_GsfTrkIdT",&HLT_Ele105_CaloIdVT_GsfTrkIdT_);
	
    // tree->SetBranchStatus("HLT_Ele115_CaloIdVT_GsfTrkIdT",1);
    // tree->SetBranchAddress("HLT_Ele115_CaloIdVT_GsfTrkIdT",&HLT_Ele115_CaloIdVT_GsfTrkIdT_);
	
    // tree->SetBranchStatus("HLT_Ele32_eta2p1_WPTight_Gsf",1);
    // tree->SetBranchAddress("HLT_Ele32_eta2p1_WPTight_Gsf",&HLT_Ele32_eta2p1_WPTight_Gsf_);

    tree->SetBranchStatus("HLT_IsoMu24",1);
    tree->SetBranchAddress("HLT_IsoMu24",&HLT_IsoMu24_);
	
    tree->SetBranchStatus("HLT_IsoTkMu24",1);
    tree->SetBranchAddress("HLT_IsoTkMu24",&HLT_IsoTkMu24_);
	
  }
    
  if (year=="2017"){
    tree->SetBranchStatus("HLT_Ele32_WPTight_Gsf_L1DoubleEG",1);
    tree->SetBranchAddress("HLT_Ele32_WPTight_Gsf_L1DoubleEG",&HLT_Ele32_WPTight_Gsf_L1DoubleEG_);
    
    // tree->SetBranchStatus("HLT_Ele32_WPTight_Gsf",1);
    // tree->SetBranchAddress("HLT_Ele32_WPTight_Gsf",&HLT_Ele32_WPTight_Gsf_);
    
    tree->SetBranchStatus("HLT_Ele35_WPTight_Gsf",1);
    tree->SetBranchAddress("HLT_Ele35_WPTight_Gsf",&HLT_Ele35_WPTight_Gsf_);
	
    // tree->SetBranchStatus("HLT_Ele115_CaloIdVT_GsfTrkIdT",1);
    // tree->SetBranchAddress("HLT_Ele115_CaloIdVT_GsfTrkIdT",&HLT_Ele115_CaloIdVT_GsfTrkIdT_);
	
    tree->SetBranchStatus("HLT_IsoMu24",1);
    tree->SetBranchAddress("HLT_IsoMu24",&HLT_IsoMu24_);
	
    // tree->SetBranchStatus("HLT_IsoTkMu24",1);
    // tree->SetBranchAddress("HLT_IsoTkMu24",&HLT_IsoTkMu24_);

    // tree->SetBranchStatus("HLT_IsoMu24_eta2p1",1);
    // tree->SetBranchAddress("HLT_IsoMu24_eta2p1",&HLT_IsoMu24_eta2p1_);

    tree->SetBranchStatus("HLT_IsoMu27",1);
    tree->SetBranchAddress("HLT_IsoMu27",&HLT_IsoMu27_);

    tree->SetBranchStatus("L1_SingleEG24",1);
    tree->SetBranchStatus("L1_SingleEG26",1);
    tree->SetBranchStatus("L1_SingleEG30",1);
    tree->SetBranchStatus("L1_SingleEG32",1);
    tree->SetBranchStatus("L1_SingleEG34",1);
    tree->SetBranchStatus("L1_SingleEG36",1);
    tree->SetBranchStatus("L1_SingleEG38",1);
    tree->SetBranchStatus("L1_SingleEG40",1);
    tree->SetBranchStatus("L1_SingleEG42",1);
    tree->SetBranchStatus("L1_SingleEG45",1);
    tree->SetBranchStatus("L1_SingleEG50",1);
    tree->SetBranchStatus("L1_SingleEG34er2p1",1);
    tree->SetBranchStatus("L1_SingleEG36er2p1",1);
    tree->SetBranchStatus("L1_SingleEG38er2p1",1);
    tree->SetBranchStatus("L1_SingleIsoEG24er2p1",1);
    tree->SetBranchStatus("L1_SingleIsoEG26er2p1",1);
    tree->SetBranchStatus("L1_SingleIsoEG28er2p1",1);
    tree->SetBranchStatus("L1_SingleIsoEG30er2p1",1);
    tree->SetBranchStatus("L1_SingleIsoEG32er2p1",1);
    tree->SetBranchStatus("L1_SingleIsoEG34er2p1",1);
    tree->SetBranchStatus("L1_SingleIsoEG36er2p1",1);
    tree->SetBranchStatus("L1_SingleIsoEG24",1);
    tree->SetBranchStatus("L1_SingleIsoEG26",1);
    tree->SetBranchStatus("L1_SingleIsoEG28",1);
    tree->SetBranchStatus("L1_SingleIsoEG30",1);
    tree->SetBranchStatus("L1_SingleIsoEG32",1);    
    tree->SetBranchStatus("L1_SingleIsoEG34",1);
    tree->SetBranchStatus("L1_SingleIsoEG36",1);
    tree->SetBranchStatus("L1_SingleIsoEG38",1);

    tree->SetBranchAddress("L1_SingleEG24",&L1_SingleEG24_);
    tree->SetBranchAddress("L1_SingleEG26",&L1_SingleEG26_);
    tree->SetBranchAddress("L1_SingleEG30",&L1_SingleEG30_);
    tree->SetBranchAddress("L1_SingleEG32",&L1_SingleEG32_);
    tree->SetBranchAddress("L1_SingleEG34",&L1_SingleEG34_);
    tree->SetBranchAddress("L1_SingleEG36",&L1_SingleEG36_);
    tree->SetBranchAddress("L1_SingleEG38",&L1_SingleEG38_);
    tree->SetBranchAddress("L1_SingleEG40",&L1_SingleEG40_);
    tree->SetBranchAddress("L1_SingleEG42",&L1_SingleEG42_);
    tree->SetBranchAddress("L1_SingleEG45",&L1_SingleEG45_);
    tree->SetBranchAddress("L1_SingleEG50",&L1_SingleEG50_);
    tree->SetBranchAddress("L1_SingleEG34er2p1",&L1_SingleEG34er2p1_);
    tree->SetBranchAddress("L1_SingleEG36er2p1",&L1_SingleEG36er2p1_);
    tree->SetBranchAddress("L1_SingleEG38er2p1",&L1_SingleEG38er2p1_);
    tree->SetBranchAddress("L1_SingleIsoEG24er2p1",&L1_SingleIsoEG24er2p1_);
    tree->SetBranchAddress("L1_SingleIsoEG26er2p1",&L1_SingleIsoEG26er2p1_);
    tree->SetBranchAddress("L1_SingleIsoEG28er2p1",&L1_SingleIsoEG28er2p1_);
    tree->SetBranchAddress("L1_SingleIsoEG30er2p1",&L1_SingleIsoEG30er2p1_);
    tree->SetBranchAddress("L1_SingleIsoEG32er2p1",&L1_SingleIsoEG32er2p1_);
    tree->SetBranchAddress("L1_SingleIsoEG34er2p1",&L1_SingleIsoEG34er2p1_);
    tree->SetBranchAddress("L1_SingleIsoEG36er2p1",&L1_SingleIsoEG36er2p1_);
    tree->SetBranchAddress("L1_SingleIsoEG24",&L1_SingleIsoEG24_);
    tree->SetBranchAddress("L1_SingleIsoEG26",&L1_SingleIsoEG26_);
    tree->SetBranchAddress("L1_SingleIsoEG28",&L1_SingleIsoEG28_);
    tree->SetBranchAddress("L1_SingleIsoEG30",&L1_SingleIsoEG30_);
    tree->SetBranchAddress("L1_SingleIsoEG32",&L1_SingleIsoEG32_);
    tree->SetBranchAddress("L1_SingleIsoEG34",&L1_SingleIsoEG34_);
    tree->SetBranchAddress("L1_SingleIsoEG36",&L1_SingleIsoEG36_);
    tree->SetBranchAddress("L1_SingleIsoEG38",&L1_SingleIsoEG38_);



  }
  
  if (year=="2018"){
    tree->SetBranchStatus("HLT_Ele32_WPTight_Gsf",1);
    tree->SetBranchAddress("HLT_Ele32_WPTight_Gsf",&HLT_Ele32_WPTight_Gsf_);

    // tree->SetBranchStatus("HLT_Ele35_WPTight_Gsf",1);
    // tree->SetBranchAddress("HLT_Ele35_WPTight_Gsf",&HLT_Ele35_WPTight_Gsf_);

    // tree->SetBranchStatus("HLT_Ele38_WPTight_Gsf",1);
    // tree->SetBranchAddress("HLT_Ele38_WPTight_Gsf",&HLT_Ele38_WPTight_Gsf_);

    // tree->SetBranchStatus("HLT_Ele32_WPTight_Gsf_L1DoubleEG",1);
    // tree->SetBranchAddress("HLT_Ele32_WPTight_Gsf_L1DoubleEG",&HLT_Ele32_WPTight_Gsf_L1DoubleEG_);

    // tree->SetBranchStatus("HLT_Ele115_CaloIdVT_GsfTrkIdT",1);
    // tree->SetBranchAddress("HLT_Ele115_CaloIdVT_GsfTrkIdT",&HLT_Ele115_CaloIdVT_GsfTrkIdT_);
	
    // tree->SetBranchStatus("HLT_DoubleEle25_CaloIdL_MW",1);
    // tree->SetBranchAddress("HLT_DoubleEle25_CaloIdL_MW",&HLT_DoubleEle25_CaloIdL_MW_);

    tree->SetBranchStatus("HLT_IsoMu24",1);
    tree->SetBranchAddress("HLT_IsoMu24",&HLT_IsoMu24_);

    //added for Tau -Analysis                                                                                                                                                               
    tree->SetBranchStatus("HLT_DoubleMediumChargedIsoPFTauHPS35_Trk1_eta2p1_Reg",1);
    tree->SetBranchAddress("HLT_DoubleMediumChargedIsoPFTauHPS35_Trk1_eta2p1_Reg",&HLT_DoubleMediumChargedIsoPFTauHPS35_Trk1_eta2p1_Reg_);

    tree->SetBranchStatus("HLT_DoubleMediumChargedIsoPFTauHPS35_Trk1_TightID_eta2p1_Reg",1);
    tree->SetBranchAddress("HLT_DoubleMediumChargedIsoPFTauHPS35_Trk1_TightID_eta2p1_Reg",&HLT_DoubleMediumChargedIsoPFTauHPS35_Trk1_TightID_eta2p1_Reg_);




  }	

  tree->SetBranchStatus("fixedGridRhoFastjetAll",1);
  tree->SetBranchAddress("fixedGridRhoFastjetAll", &rho_);

  // tree->SetBranchStatus("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL",1);
  // tree->SetBranchAddress("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL",&HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_);
    
  // tree->SetBranchStatus("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ",1);
  // tree->SetBranchAddress("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ",&HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_);
    
  // tree->SetBranchStatus("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL",1);
  // tree->SetBranchAddress("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL",&HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_);
    
  // tree->SetBranchStatus("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ",1);
  // tree->SetBranchAddress("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ",&HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_);
    
  // tree->SetBranchStatus("HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL",1);
  // tree->SetBranchAddress("HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL",&HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_);
    
  // tree->SetBranchStatus("HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ",1);
  // tree->SetBranchAddress("HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ",&HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_);



}

EventTree::EventTree(int nFiles, bool xRootDAccess, string year, bool isData, char** fileNames){
  tree = 0x0;
  chain = new TChain("Events");

  isData_ = isData;

  //std::cout << chain->GetCacheSize() << std::endl;
  chain->SetCacheSize(100*1024*1024);
  if (xRootDAccess){
    //string dir = "root://cms-xrd-global.cern.ch/";
    string dir = "root://cmsxrootd.fnal.gov/";
    for(int fileI=0; fileI<nFiles; fileI++){
      string fName = (string) fileNames[fileI];
      chain->Add( (dir + fileNames[fileI]).c_str() );
      cout << fName << "  " << chain->GetEntries() << endl;
    }
  }
  else{
    for(int fileI=0; fileI<nFiles; fileI++){
      chain->Add(fileNames[fileI]);
    }
  }
  chain->SetBranchStatus("*",0);
	
  // keep some important branches
  chain->SetBranchStatus("PV_ndof",1);
  chain->SetBranchAddress("PV_ndof", &pvNDOF_);

  chain->SetBranchStatus("PV_x",1);
  chain->SetBranchAddress("PV_x", &pvX_);

  chain->SetBranchStatus("PV_y",1);
  chain->SetBranchAddress("PV_y", &pvY_);

  chain->SetBranchStatus("PV_z",1);
  chain->SetBranchAddress("PV_z", &pvZ_);

  chain->SetBranchStatus("PV_chi2",1);
  chain->SetBranchAddress("PV_chi2", &pvChi2_);

  if (!isData_){
    chain->SetBranchStatus("Pileup_nPU",1);
    chain->SetBranchAddress("Pileup_nPU", &nPU_);
	
    chain->SetBranchStatus("Pileup_nTrueInt",1);
    chain->SetBranchAddress("Pileup_nTrueInt", &nPUTrue_);
  }

	
  // event
	
  chain->SetBranchStatus("run",1);
  chain->SetBranchAddress("run", &run_);

  chain->SetBranchStatus("event",1);
  chain->SetBranchAddress("event", &event_);
	
  chain->SetBranchStatus("luminosityBlock",1);
  chain->SetBranchAddress("luminosityBlock", &lumis_);

  chain->SetBranchStatus("PV_npvs",1);
  chain->SetBranchAddress("PV_npvs", &nVtx_);

  chain->SetBranchStatus("PV_npvsGood",1);
  chain->SetBranchAddress("PV_npvsGood", &nGoodVtx_);
  
  chain->SetBranchStatus("L1PreFiringWeight_Nom",1);
  chain->SetBranchAddress("L1PreFiringWeight_Nom", &L1PreFiringWeight_Nom_);
  
  chain->SetBranchStatus("L1PreFiringWeight_Up",1);
  chain->SetBranchAddress("L1PreFiringWeight_Up", &L1PreFiringWeight_Up_);

  chain->SetBranchStatus("L1PreFiringWeight_Dn",1);
  chain->SetBranchAddress("L1PreFiringWeight_Dn", &L1PreFiringWeight_Dn_);

  if (!isData_){
    chain->SetBranchStatus("Generator_weight",1);
    chain->SetBranchAddress("Generator_weight", &genWeight_);
    chain->SetBranchStatus("nLHEScaleWeight",1);
    chain->SetBranchAddress("nLHEScaleWeight", &nLHEScaleWeight_);
    
    chain->SetBranchStatus("LHEScaleWeight",1);
    chain->SetBranchAddress("LHEScaleWeight", &LHEScaleWeight_);
    
    chain->SetBranchStatus("nLHEPdfWeight",1);
    chain->SetBranchAddress("nLHEPdfWeight", &nLHEPdfWeight_);
    
    chain->SetBranchStatus("LHEPdfWeight",1);
    chain->SetBranchAddress("LHEPdfWeight", &LHEPdfWeight_);

    chain->SetBranchStatus("PSWeight",1);
    chain->SetBranchAddress("PSWeight", &PSWeight_);
	
    chain->SetBranchStatus("nPSWeight",1);
    chain->SetBranchAddress("nPSWeight", &nPSWeight_);
  }

  // MET
  chain->SetBranchStatus("MET_pt",1);
  chain->SetBranchAddress("MET_pt", &MET_pt_);

  chain->SetBranchStatus("MET_phi",1);
  chain->SetBranchAddress("MET_phi", &MET_phi_);

  if (!isData_){
    chain->SetBranchStatus("GenMET_pt",1);
    chain->SetBranchAddress("GenMET_pt", &GenMET_pt_);
	
    chain->SetBranchStatus("GenMET_phi",1);
    chain->SetBranchAddress("GenMET_phi", &GenMET_phi_);
  }

	
  // electrons	
	
  chain->SetBranchStatus("nElectron",1);
  chain->SetBranchAddress("nElectron", &nEle_);


  chain->SetBranchStatus("Electron_charge",1);
  chain->SetBranchAddress("Electron_charge", &eleCharge_);	

  chain->SetBranchStatus("Electron_pt",1);
  chain->SetBranchAddress("Electron_pt", &elePt_);

  chain->SetBranchStatus("Electron_deltaEtaSC",1);
  chain->SetBranchAddress("Electron_deltaEtaSC", &eleDeltaEtaSC_);

  chain->SetBranchStatus("Electron_eta",1);
  chain->SetBranchAddress("Electron_eta", &eleEta_);

  chain->SetBranchStatus("Electron_phi",1);
  chain->SetBranchAddress("Electron_phi", &elePhi_);

  chain->SetBranchStatus("Electron_mass",1);
  chain->SetBranchAddress("Electron_mass", &eleMass_);

  chain->SetBranchStatus("Electron_pfRelIso03_chg",1);
  chain->SetBranchAddress("Electron_pfRelIso03_chg", &elePFRelChIso_);

  chain->SetBranchStatus("Electron_pfRelIso03_all",1);
  chain->SetBranchAddress("Electron_pfRelIso03_all", &elePFRelIso_);

  chain->SetBranchStatus("Electron_sieie",1);
  chain->SetBranchAddress("Electron_sieie", &eleSIEIE_);
	
  chain->SetBranchStatus("Electron_cutBased",1);
  chain->SetBranchAddress("Electron_cutBased", &eleIDcutbased_);

  chain->SetBranchStatus("Electron_vidNestedWPBitmap",1);
  chain->SetBranchAddress("Electron_vidNestedWPBitmap", &eleVidWPBitmap_);
  
  chain->SetBranchStatus("Electron_mvaFall17V2noIso_WPL",1); 
  chain->SetBranchAddress("Electron_mvaFall17V2noIso_WPL", &eleIDmvaLoose_);

  chain->SetBranchStatus("Electron_mvaFall17V2noIso_WP80",1); 
  chain->SetBranchAddress("Electron_mvaFall17V2noIso_WP80", &eleIDmvaWP80_);

  chain->SetBranchStatus("Electron_mvaFall17V2noIso_WP90",1); 
  chain->SetBranchAddress("Electron_mvaFall17V2noIso_WP90", &eleIDmvaWP90_);

  chain->SetBranchStatus("Electron_dxy",1);
  chain->SetBranchAddress("Electron_dxy", &eleD0_);

  chain->SetBranchStatus("Electron_dz",1);
  chain->SetBranchAddress("Electron_dz", &eleDz_);

    
  chain->SetBranchStatus("Electron_dr03EcalRecHitSumEt",1);
  chain->SetBranchAddress("Electron_dr03EcalRecHitSumEt", &eleEcalSumEtDr03_);

  chain->SetBranchStatus("Electron_dr03HcalDepth1TowerSumEt",1);
  chain->SetBranchAddress("Electron_dr03HcalDepth1TowerSumEt", &eleHcalSumEtDr03_);

  chain->SetBranchStatus("Electron_dr03TkSumPt",1);
  chain->SetBranchAddress("Electron_dr03TkSumPt", &eleTrkSumPtDr03_);

  // muons
  // keep some branches in the skim
	
  chain->SetBranchStatus("nMuon",1);
  chain->SetBranchAddress("nMuon", &nMuon_);

  chain->SetBranchStatus("Muon_charge",1);
  chain->SetBranchAddress("Muon_charge", &muCharge_);
	
  chain->SetBranchStatus("Muon_pt",1);
  chain->SetBranchAddress("Muon_pt", &muPt_);

  chain->SetBranchStatus("Muon_eta",1);
  chain->SetBranchAddress("Muon_eta", &muEta_);

  chain->SetBranchStatus("Muon_phi",1);
  chain->SetBranchAddress("Muon_phi", &muPhi_);

  chain->SetBranchStatus("Muon_mass",1);
  chain->SetBranchAddress("Muon_mass", &muMass_);

  // chain->SetBranchStatus("Muon_pfRelIso04_all",1);
  // chain->SetBranchAddress("Muon_pfRelIso04_all", &muPFRelIso_);

  chain->SetBranchStatus("Muon_pfRelIso03_all",1);
  chain->SetBranchAddress("Muon_pfRelIso03_all", &muPFRelIso_);
  
  chain->SetBranchStatus("Muon_tightId",1);
  chain->SetBranchAddress("Muon_tightId", &muTightId_);

  chain->SetBranchStatus("Muon_mediumId",1);
  chain->SetBranchAddress("Muon_mediumId", &muMediumId_);

  chain->SetBranchStatus("Muon_looseId",1);
  chain->SetBranchAddress("Muon_looseId", &muLooseId_);

  chain->SetBranchStatus("Muon_mediumPromptId",1);
  chain->SetBranchAddress("Muon_mediumPromptId", &muMediumPromptId_);

  chain->SetBranchStatus("Muon_isPFcand",1);
  chain->SetBranchAddress("Muon_isPFcand", &muIsPFMuon_);

  chain->SetBranchStatus("Muon_isGlobal",1);
  chain->SetBranchAddress("Muon_isGlobal", &muIsGlobal_);

  chain->SetBranchStatus("Muon_isTracker",1);
  chain->SetBranchAddress("Muon_isTracker", &muIsTracker_);

  chain->SetBranchStatus("Muon_dxy",1);
  chain->SetBranchAddress("Muon_dxy", &mudxy_);

  chain->SetBranchStatus("Muon_dz",1);
  chain->SetBranchAddress("Muon_dz", &mudz_);

  chain->SetBranchStatus("Muon_nTrackerLayers",1);
  chain->SetBranchAddress("Muon_nTrackerLayers", &munTrackerLayers_);

  chain->SetBranchStatus("Muon_genPartIdx",1);
  chain->SetBranchAddress("Muon_genPartIdx", &muGenPartIdx_);


  //For Taus -Analysis

  chain->SetBranchStatus("nTau",1);
  chain->SetBranchAddress("nTau", &nTau_);

  chain->SetBranchStatus("Tau_charge",1);
  chain->SetBranchAddress("Tau_charge", &tauCharge_);

  chain->SetBranchStatus("Tau_decayMode",1);
  chain->SetBranchAddress("Tau_decayMode", &tauDecayMode_);

  chain->SetBranchStatus("Tau_dxy",1);
  chain->SetBranchAddress("Tau_dxy", &tauDxy_);

  chain->SetBranchStatus("Tau_dz",1);
  chain->SetBranchAddress("Tau_dz", &tauDz_);

  chain->SetBranchStatus("Tau_eta",1);
  chain->SetBranchAddress("Tau_eta", &tauEta_);

  //chain->SetBranchStatus("Tau_idDecayMode",1);
  //chain->SetBranchAddress("Tau_idDecayMode", &tau_idDecayMode_);

  //chain->SetBranchStatus("Tau_idDecayModeNewDMs",1);
  //chain->SetBranchAddress("Tau_idDecayModeNewDMs", &tau_idDecayModeNewDMs_);

  chain->SetBranchStatus("Tau_idDeepTau2017v2p1VSe",1);
  chain->SetBranchAddress("Tau_idDeepTau2017v2p1VSe", &tauIdDeepTau2017v2p1VSe_);

  chain->SetBranchStatus("Tau_idDeepTau2017v2p1VSjet",1);
  chain->SetBranchAddress("Tau_idDeepTau2017v2p1VSjet", &tauIdDeepTau2017v2p1VSjet_);

  chain->SetBranchStatus("Tau_idDeepTau2017v2p1VSmu",1);
  chain->SetBranchAddress("Tau_idDeepTau2017v2p1VSmu", &tauIdDeepTau2017v2p1VSmu_);

  chain->SetBranchStatus("Tau_mass",1);
  chain->SetBranchAddress("Tau_mass", &tauMass_);

  chain->SetBranchStatus("Tau_phi",1);
  chain->SetBranchAddress("Tau_phi", &tauPhi_);

  chain->SetBranchStatus("Tau_pt",1);
  chain->SetBranchAddress("Tau_pt", &tauPt_);

  chain->SetBranchStatus("Tau_rawDeepTau2017v2p1VSe",1);
  chain->SetBranchAddress("Tau_rawDeepTau2017v2p1VSe", &tauRawDeepTau2017v2p1VSe_);

  chain->SetBranchStatus("Tau_rawDeepTau2017v2p1VSjet",1);
  chain->SetBranchAddress("Tau_rawDeepTau2017v2p1VSjet", &tauRawDeepTau2017v2p1VSjet_);

  chain->SetBranchStatus("Tau_rawDeepTau2017v2p1VSmu",1);
  chain->SetBranchAddress("Tau_rawDeepTau2017v2p1VSmu", &tauRawDeepTau2017v2p1VSmu_);

  chain->SetBranchStatus("Tau_genPartFlav",1);
  chain->SetBranchAddress("Tau_genPartFlav", &tauGenPartFlav_);

  // jets
	
  chain->SetBranchStatus("nJet",1);
  chain->SetBranchAddress("nJet", &nJet_);
 
  chain->SetBranchStatus("Jet_pt",1);
  chain->SetBranchAddress("Jet_pt", &jetPt_);

  chain->SetBranchStatus("Jet_rawFactor",1);
  chain->SetBranchAddress("Jet_rawFactor", &jetRawFactor_);
	
  chain->SetBranchStatus("Jet_eta",1);
  chain->SetBranchAddress("Jet_eta", &jetEta_);
	
  chain->SetBranchStatus("Jet_phi",1);
  chain->SetBranchAddress("Jet_phi", &jetPhi_);

  chain->SetBranchStatus("Jet_mass",1);
  chain->SetBranchAddress("Jet_mass", &jetMass_);

  chain->SetBranchStatus("Jet_jetId",1);
  chain->SetBranchAddress("Jet_jetId", &jetID_);

  chain->SetBranchStatus("Jet_puId",1);
  chain->SetBranchAddress("Jet_puId", &jetPUID_);

  chain->SetBranchStatus("Jet_puIdDisc",1);
  chain->SetBranchAddress("Jet_puIdDisc", &jetpuIdDisc_);

  chain->SetBranchStatus("Jet_area",1);
  chain->SetBranchAddress("Jet_area", &jetArea_);

  chain->SetBranchStatus("Jet_btagCMVA",1);
  chain->SetBranchAddress("Jet_btagCMVA", &jetBtagCMVA_);

  chain->SetBranchStatus("Jet_btagCSVV2",1);
  chain->SetBranchAddress("Jet_btagCSVV2", &jetBtagCSVV2_);

  chain->SetBranchStatus("Jet_btagDeepB",1);
  chain->SetBranchAddress("Jet_btagDeepB", &jetBtagDeepB_);
  
  chain->SetBranchStatus("Jet_btagDeepCvB",1);
  chain->SetBranchAddress("Jet_btagDeepCvB", &jetBtagDeepCvB_);
  
  chain->SetBranchStatus("Jet_btagDeepCvL",1);
  chain->SetBranchAddress("Jet_btagDeepCvL", &jetBtagDeepCvL_);
  
  // chain->SetBranchStatus("Jet_btagDeepC",1);
  // chain->SetBranchAddress("Jet_btagDeepC", &jetBtagDeepC_);
  
  chain->SetBranchStatus("Jet_btagDeepFlavB",1);
  chain->SetBranchAddress("Jet_btagDeepFlavB", &jetBtagDeepFlavB_);
  
  chain->SetBranchStatus("Jet_btagDeepFlavCvB",1);
  chain->SetBranchAddress("Jet_btagDeepFlavCvB", &jetBtagDeepFlavCvB_);
  
  chain->SetBranchStatus("Jet_btagDeepFlavCvL",1);
  chain->SetBranchAddress("Jet_btagDeepFlavCvL", &jetBtagDeepFlavCvL_);

  chain->SetBranchStatus("Jet_chEmEF",1);
  chain->SetBranchAddress("Jet_chEmEF", &jetchEmEF_);

  chain->SetBranchStatus("Jet_neEmEF",1);
  chain->SetBranchAddress("Jet_neEmEF", &jetneEmEF_);

  chain->SetBranchStatus("Jet_chHEF",1);
  chain->SetBranchAddress("Jet_chHEF", &jetchHEF_);

  chain->SetBranchStatus("Jet_neHEF",1);
  chain->SetBranchAddress("Jet_neHEF", &jetneHEF_);

  if (!isData_){
    chain->SetBranchStatus("Jet_partonFlavour",1);
    chain->SetBranchAddress("Jet_partonFlavour", &jetPartFlvr_);

    chain->SetBranchStatus("Jet_hadronFlavour",1);
    chain->SetBranchAddress("Jet_hadronFlavour", &jetHadFlvr_);
	
    chain->SetBranchStatus("Jet_genJetIdx",1);
    chain->SetBranchAddress("Jet_genJetIdx", &jetGenJetIdx_);
  }

  // Gen Partons
  if (!isData_){

    chain->SetBranchStatus("nLHEPart",1);
    chain->SetBranchAddress("nLHEPart", &nLHEPart_);
    
    chain->SetBranchStatus("LHEPart_pdgId",1);
    chain->SetBranchAddress("LHEPart_pdgId", &LHEPart_pdgId_);
    
    chain->SetBranchStatus("LHEPart_pt",1);
    chain->SetBranchAddress("LHEPart_pt", &LHEPart_pt_);

    chain->SetBranchStatus("LHEPart_eta",1);
    chain->SetBranchAddress("LHEPart_eta", &LHEPart_eta_);

    chain->SetBranchStatus("LHEPart_phi",1);
    chain->SetBranchAddress("LHEPart_phi", &LHEPart_phi_);
    
    chain->SetBranchStatus("LHEPart_mass",1);
    chain->SetBranchAddress("LHEPart_mass", &LHEPart_mass_);

    chain->SetBranchStatus("nGenPart",1);
    chain->SetBranchAddress("nGenPart", &nGenPart_);
	
    chain->SetBranchStatus("GenPart_pt",1);
    chain->SetBranchAddress("GenPart_pt", &GenPart_pt_);
	
    chain->SetBranchStatus("GenPart_eta",1);
    chain->SetBranchAddress("GenPart_eta", &GenPart_eta_);
	
    chain->SetBranchStatus("GenPart_phi",1);
    chain->SetBranchAddress("GenPart_phi", &GenPart_phi_);

    chain->SetBranchStatus("GenPart_mass",1);
    chain->SetBranchAddress("GenPart_mass", &GenPart_mass_);

    chain->SetBranchStatus("GenPart_genPartIdxMother",1);
    chain->SetBranchAddress("GenPart_genPartIdxMother", &GenPart_genPartIdxMother_);

    chain->SetBranchStatus("GenPart_pdgId",1);
    chain->SetBranchAddress("GenPart_pdgId", &GenPart_pdgId_);
	
    chain->SetBranchStatus("GenPart_status",1);
    chain->SetBranchAddress("GenPart_status", &GenPart_status_);
	
    chain->SetBranchStatus("GenPart_statusFlags",1);
    chain->SetBranchAddress("GenPart_statusFlags", &GenPart_statusFlags_);
    

    chain->SetBranchStatus("nGenJet",1);
    chain->SetBranchAddress("nGenJet", &nGenJet_);
	
    chain->SetBranchStatus("GenJet_pt",1);
    chain->SetBranchAddress("GenJet_pt", &GenJet_pt_);

    chain->SetBranchStatus("GenJet_eta",1);
    chain->SetBranchAddress("GenJet_eta", &GenJet_eta_);

    chain->SetBranchStatus("GenJet_phi",1);
    chain->SetBranchAddress("GenJet_phi", &GenJet_phi_);
 
    chain->SetBranchStatus("GenJet_mass",1);
    chain->SetBranchAddress("GenJet_mass", &GenJet_mass_);

    chain->SetBranchStatus("GenJet_partonFlavour",1);
    chain->SetBranchAddress("GenJet_partonFlavour", &GenJet_partonFlavour_);
	
    chain->SetBranchStatus("GenJet_hadronFlavour",1);
    chain->SetBranchAddress("GenJet_hadronFlavour", &GenJet_hadronFlavour_);
  }

  //Fliters
  chain->SetBranchStatus("Flag_goodVertices",1);
  chain->SetBranchAddress("Flag_goodVertices",&Flag_goodVertices_);

  chain->SetBranchStatus("Flag_globalSuperTightHalo2016Filter",1);
  chain->SetBranchAddress("Flag_globalSuperTightHalo2016Filter", &Flag_globalSuperTightHalo2016Filter_);

  chain->SetBranchStatus("Flag_HBHENoiseFilter",1);
  chain->SetBranchAddress("Flag_HBHENoiseFilter", &Flag_HBHENoiseFilter_);

  chain->SetBranchStatus("Flag_HBHENoiseIsoFilter",1);
  chain->SetBranchAddress("Flag_HBHENoiseIsoFilter", &Flag_HBHENoiseIsoFilter_);

  chain->SetBranchStatus("Flag_EcalDeadCellTriggerPrimitiveFilter",1);
  chain->SetBranchAddress("Flag_EcalDeadCellTriggerPrimitiveFilter", &Flag_EcalDeadCellTriggerPrimitiveFilter_);

  chain->SetBranchStatus("Flag_BadPFMuonFilter",1);
  chain->SetBranchAddress("Flag_BadPFMuonFilter",&Flag_BadPFMuonFilter_);

  if(year =="2017" || year == "2018"){
    chain->SetBranchStatus("Flag_ecalBadCalibFilter",1);
    chain->SetBranchAddress("Flag_ecalBadCalibFilter",&Flag_ecalBadCalibFilter_);
  }

  //TRIGGERS

  if (year=="2016"){
    chain->SetBranchStatus("HLT_Ele27_WPTight_Gsf",1);
    chain->SetBranchAddress("HLT_Ele27_WPTight_Gsf",&HLT_Ele27_WPTight_Gsf_);
	
    // chain->SetBranchStatus("HLT_Ele105_CaloIdVT_GsfTrkIdT",1);
    // chain->SetBranchAddress("HLT_Ele105_CaloIdVT_GsfTrkIdT",&HLT_Ele105_CaloIdVT_GsfTrkIdT_);
	
    // chain->SetBranchStatus("HLT_Ele115_CaloIdVT_GsfTrkIdT",1);
    // chain->SetBranchAddress("HLT_Ele115_CaloIdVT_GsfTrkIdT",&HLT_Ele115_CaloIdVT_GsfTrkIdT_);
	
    // chain->SetBranchStatus("HLT_Ele32_eta2p1_WPTight_Gsf",1);
    // chain->SetBranchAddress("HLT_Ele32_eta2p1_WPTight_Gsf",&HLT_Ele32_eta2p1_WPTight_Gsf_);

    chain->SetBranchStatus("HLT_IsoMu24",1);
    chain->SetBranchAddress("HLT_IsoMu24",&HLT_IsoMu24_);
	
    chain->SetBranchStatus("HLT_IsoTkMu24",1);
    chain->SetBranchAddress("HLT_IsoTkMu24",&HLT_IsoTkMu24_);
	
  }
    
  if (year=="2017"){
    chain->SetBranchStatus("HLT_Ele32_WPTight_Gsf_L1DoubleEG",1);
    chain->SetBranchAddress("HLT_Ele32_WPTight_Gsf_L1DoubleEG",&HLT_Ele32_WPTight_Gsf_L1DoubleEG_);
	
    // chain->SetBranchStatus("HLT_Ele32_WPTight_Gsf",1);
    // chain->SetBranchAddress("HLT_Ele32_WPTight_Gsf",&HLT_Ele32_WPTight_Gsf_);
	
    chain->SetBranchStatus("HLT_Ele35_WPTight_Gsf",1);
    chain->SetBranchAddress("HLT_Ele35_WPTight_Gsf",&HLT_Ele35_WPTight_Gsf_);
	
    // chain->SetBranchStatus("HLT_Ele115_CaloIdVT_GsfTrkIdT",1);
    // chain->SetBranchAddress("HLT_Ele115_CaloIdVT_GsfTrkIdT",&HLT_Ele115_CaloIdVT_GsfTrkIdT_);
	
    chain->SetBranchStatus("HLT_IsoMu24",1);
    chain->SetBranchAddress("HLT_IsoMu24",&HLT_IsoMu24_);
	
    // chain->SetBranchStatus("HLT_IsoTkMu24",1);
    // chain->SetBranchAddress("HLT_IsoTkMu24",&HLT_IsoTkMu24_);

    // chain->SetBranchStatus("HLT_IsoMu24_eta2p1",1);
    // chain->SetBranchAddress("HLT_IsoMu24_eta2p1",&HLT_IsoMu24_eta2p1_);

    chain->SetBranchStatus("HLT_IsoMu27",1);
    chain->SetBranchAddress("HLT_IsoMu27",&HLT_IsoMu27_);

    chain->SetBranchStatus("L1_SingleEG24",1);
    chain->SetBranchStatus("L1_SingleEG26",1);
    chain->SetBranchStatus("L1_SingleEG30",1);
    chain->SetBranchStatus("L1_SingleEG32",1);
    chain->SetBranchStatus("L1_SingleEG34",1);
    chain->SetBranchStatus("L1_SingleEG36",1);
    chain->SetBranchStatus("L1_SingleEG38",1);
    chain->SetBranchStatus("L1_SingleEG40",1);
    chain->SetBranchStatus("L1_SingleEG42",1);
    chain->SetBranchStatus("L1_SingleEG45",1);
    chain->SetBranchStatus("L1_SingleEG50",1);
    chain->SetBranchStatus("L1_SingleEG34er2p1",1);
    chain->SetBranchStatus("L1_SingleEG36er2p1",1);
    chain->SetBranchStatus("L1_SingleEG38er2p1",1);
    chain->SetBranchStatus("L1_SingleIsoEG24er2p1",1);
    chain->SetBranchStatus("L1_SingleIsoEG26er2p1",1);
    chain->SetBranchStatus("L1_SingleIsoEG28er2p1",1);
    chain->SetBranchStatus("L1_SingleIsoEG30er2p1",1);
    chain->SetBranchStatus("L1_SingleIsoEG32er2p1",1);
    chain->SetBranchStatus("L1_SingleIsoEG34er2p1",1);
    chain->SetBranchStatus("L1_SingleIsoEG36er2p1",1);
    chain->SetBranchStatus("L1_SingleIsoEG24",1);
    chain->SetBranchStatus("L1_SingleIsoEG26",1);
    chain->SetBranchStatus("L1_SingleIsoEG28",1);
    chain->SetBranchStatus("L1_SingleIsoEG30",1);
    chain->SetBranchStatus("L1_SingleIsoEG32",1);    
    chain->SetBranchStatus("L1_SingleIsoEG34",1);
    chain->SetBranchStatus("L1_SingleIsoEG36",1);
    chain->SetBranchStatus("L1_SingleIsoEG38",1);

    chain->SetBranchAddress("L1_SingleEG24",&L1_SingleEG24_);
    chain->SetBranchAddress("L1_SingleEG26",&L1_SingleEG26_);
    chain->SetBranchAddress("L1_SingleEG30",&L1_SingleEG30_);
    chain->SetBranchAddress("L1_SingleEG32",&L1_SingleEG32_);
    chain->SetBranchAddress("L1_SingleEG34",&L1_SingleEG34_);
    chain->SetBranchAddress("L1_SingleEG36",&L1_SingleEG36_);
    chain->SetBranchAddress("L1_SingleEG38",&L1_SingleEG38_);
    chain->SetBranchAddress("L1_SingleEG40",&L1_SingleEG40_);
    chain->SetBranchAddress("L1_SingleEG42",&L1_SingleEG42_);
    chain->SetBranchAddress("L1_SingleEG45",&L1_SingleEG45_);
    chain->SetBranchAddress("L1_SingleEG50",&L1_SingleEG50_);
    chain->SetBranchAddress("L1_SingleEG34er2p1",&L1_SingleEG34er2p1_);
    chain->SetBranchAddress("L1_SingleEG36er2p1",&L1_SingleEG36er2p1_);
    chain->SetBranchAddress("L1_SingleEG38er2p1",&L1_SingleEG38er2p1_);
    chain->SetBranchAddress("L1_SingleIsoEG24er2p1",&L1_SingleIsoEG24er2p1_);
    chain->SetBranchAddress("L1_SingleIsoEG26er2p1",&L1_SingleIsoEG26er2p1_);
    chain->SetBranchAddress("L1_SingleIsoEG28er2p1",&L1_SingleIsoEG28er2p1_);
    chain->SetBranchAddress("L1_SingleIsoEG30er2p1",&L1_SingleIsoEG30er2p1_);
    chain->SetBranchAddress("L1_SingleIsoEG32er2p1",&L1_SingleIsoEG32er2p1_);
    chain->SetBranchAddress("L1_SingleIsoEG34er2p1",&L1_SingleIsoEG34er2p1_);
    chain->SetBranchAddress("L1_SingleIsoEG36er2p1",&L1_SingleIsoEG36er2p1_);
    chain->SetBranchAddress("L1_SingleIsoEG24",&L1_SingleIsoEG24_);
    chain->SetBranchAddress("L1_SingleIsoEG26",&L1_SingleIsoEG26_);
    chain->SetBranchAddress("L1_SingleIsoEG28",&L1_SingleIsoEG28_);
    chain->SetBranchAddress("L1_SingleIsoEG30",&L1_SingleIsoEG30_);
    chain->SetBranchAddress("L1_SingleIsoEG32",&L1_SingleIsoEG32_);
    chain->SetBranchAddress("L1_SingleIsoEG34",&L1_SingleIsoEG34_);
    chain->SetBranchAddress("L1_SingleIsoEG36",&L1_SingleIsoEG36_);
    chain->SetBranchAddress("L1_SingleIsoEG38",&L1_SingleIsoEG38_);



  }
  
  if (year=="2018"){
    chain->SetBranchStatus("HLT_Ele32_WPTight_Gsf",1);
    chain->SetBranchAddress("HLT_Ele32_WPTight_Gsf",&HLT_Ele32_WPTight_Gsf_);

    // chain->SetBranchStatus("HLT_Ele35_WPTight_Gsf",1);
    // chain->SetBranchAddress("HLT_Ele35_WPTight_Gsf",&HLT_Ele35_WPTight_Gsf_);

    // chain->SetBranchStatus("HLT_Ele38_WPTight_Gsf",1);
    // chain->SetBranchAddress("HLT_Ele38_WPTight_Gsf",&HLT_Ele38_WPTight_Gsf_);

    // chain->SetBranchStatus("HLT_Ele32_WPTight_Gsf_L1DoubleEG",1);
    // chain->SetBranchAddress("HLT_Ele32_WPTight_Gsf_L1DoubleEG",&HLT_Ele32_WPTight_Gsf_L1DoubleEG_);

    // chain->SetBranchStatus("HLT_Ele115_CaloIdVT_GsfTrkIdT",1);
    // chain->SetBranchAddress("HLT_Ele115_CaloIdVT_GsfTrkIdT",&HLT_Ele115_CaloIdVT_GsfTrkIdT_);
	
    // chain->SetBranchStatus("HLT_DoubleEle25_CaloIdL_MW",1);
    // chain->SetBranchAddress("HLT_DoubleEle25_CaloIdL_MW",&HLT_DoubleEle25_CaloIdL_MW_);

    chain->SetBranchStatus("HLT_IsoMu24",1);
    chain->SetBranchAddress("HLT_IsoMu24",&HLT_IsoMu24_);

    //added for Tau -Analysis
    chain->SetBranchStatus("HLT_DoubleMediumChargedIsoPFTauHPS35_Trk1_eta2p1_Reg",1);
    chain->SetBranchAddress("HLT_DoubleMediumChargedIsoPFTauHPS35_Trk1_eta2p1_Reg",&HLT_DoubleMediumChargedIsoPFTauHPS35_Trk1_eta2p1_Reg_);

    chain->SetBranchStatus("HLT_DoubleMediumChargedIsoPFTauHPS35_Trk1_TightID_eta2p1_Reg",1);
    chain->SetBranchAddress("HLT_DoubleMediumChargedIsoPFTauHPS35_Trk1_TightID_eta2p1_Reg",&HLT_DoubleMediumChargedIsoPFTauHPS35_Trk1_TightID_eta2p1_Reg_);

  }	

  chain->SetBranchStatus("fixedGridRhoFastjetAll",1);
  chain->SetBranchAddress("fixedGridRhoFastjetAll", &rho_);

  // chain->SetBranchStatus("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL",1);
  // chain->SetBranchAddress("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL",&HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_);
    
  // chain->SetBranchStatus("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ",1);
  // chain->SetBranchAddress("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ",&HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_);
    
  // chain->SetBranchStatus("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL",1);
  // chain->SetBranchAddress("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL",&HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_);
    
  // chain->SetBranchStatus("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ",1);
  // chain->SetBranchAddress("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ",&HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_);
    
  // chain->SetBranchStatus("HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL",1);
  // chain->SetBranchAddress("HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL",&HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_);
    
  // chain->SetBranchStatus("HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ",1);
  // chain->SetBranchAddress("HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ",&HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_);



}

EventTree::~EventTree(){
  if(chain)
    delete chain;
  //if(tree)
  //  delete tree;
    // will be some memory leak due to created vectors
}

Long64_t EventTree::GetEntries(){

  Long64_t entries = 0;

  if(chain)
    entries = chain->GetEntries();
  else if(tree)
    entries = tree->GetEntries();

  return entries;
}

Int_t EventTree::GetEntry(Long64_t entry){
    
    Long64_t entries = 0;
    
    if(chain){
      chain->GetEntry(entry);
      entries = chain->GetEntries();
    }else if(tree){
      tree->GetEntry(entry);
      entries = tree->GetEntries();
    }

    return entries;
}
