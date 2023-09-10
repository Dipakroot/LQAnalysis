#include"../interface/Selector.h"

TRandom* generator = gRandom;

Selector::Selector(){

    isNanoAOD = true;
    
    year = "2016";

    // jets
    jet_Pt_cut = 30.; //Default
    jet_Eta_cut = 2.4;
        
    printEvent = -1;
    IsDebug = false;
    
    looseJetID = false;
    veto_lep_jet_dR = 0.4; // remove jets with a lepton closer than this cut level
    JERsystLevel  = 1;
    JECsystLevel  = 1;
    elesmearLevel = 1;
    elescaleLevel = 1;
    useDeepCSVbTag = false;
    //https://twiki.cern.ch/twiki/bin/viewauth/CMS/BtagRecommendation80XReReco
    // // CSVv2M
    // btag_cut = 0.8484;  
    // DeepJet
    btag_cut = 0.2598 ; 
    // DeepCSV
    btag_cut_DeepCSV = 0.6001;
    
    // whether to invert lepton requirements for 
    QCDselect = false;
    DDselect = false;
    
    // electrons 
    ele_Pt_cut = 35.0; // Default
    ele_Eta_cut = 2.4;
    // electron nanoAOD VETO
    ele_PtLoose_cut = 15.0;
    ele_EtaLoose_cut = 2.4;
    ele_RelIso_tight_EB = 0.0821;
    ele_RelIso_tight_EE = 0.0695;
    ele_RelIso_loose_EB = 0.175;
    ele_RelIso_loose_EE = 0.159;
    
    // muons nanoAOD 
    mu_Pt_cut = 30; // Default
    mu_Eta_tight = 2.4;
    mu_RelIso_tight = 0.15;
    // muons nanoAOD VETO
    mu_PtLoose_cut = 15.0;
    mu_Eta_loose = 2.4;
    mu_RelIso_loose = 0.25;
    
    // for Tau Analysis
    tau_Pt_cut = 30;
    tau_Eta_cut = 2.3;
    tau_vsJet_cut = 0;
    tau_vsJet_cut_loose = 0;
    tau_vsJet_cut_medium = 0;
    tau_vsJet_cut_tight = 0;
    tau_vsEle_cut = 0;
    tau_vsMu_cut = 0;
    tau_d0_cut = 0;
    tau_dz_cut = 0;


    mu_Iso_invert = false;
    //smearJetPt = true; // Deafult
    smearJetPt = false;
    smearEle = true;
    scaleEle = true;
    
    ///////// MiniAOD ///////////////////
    //muons miniAOD MEDIUM
    mu_Pt_cut_miniAOD = 26.0;
    s = 0 ;
    m = 0;
    isPreVFP = false ; isPostVFP = false ;

    //electron miniAOD MEDIUM
    ele_Pt_cut_miniAOD = 30.0;
    ele_Eta_cut_miniAOD = 2.5;
    ele_muon_dR_miniAOD = 0.4;

    //jets miniAOD
    looseJetID_miniAOD = true;
    jet_Pt_cut_miniAOD = 25.; 
    jet_Eta_cut_miniAOD = 2.4;
    veto_lep_jet_dR_miniAOD = 0.4;
    ////////////////////////////////////
    
    //met defaults
    METPt  = -9999;
    METPhi  = -9999;
    METUnc = 1.0;
    selectMETUnc = false;

  
}

void Selector::init_JER(std::string inputPrefix){
  
    // jetResolution = new JME::JetResolution((inputPrefix+"_MC_PtResolution_AK4PFchs.txt").c_str());
    // jetResolutionScaleFactor = new JME::JetResolutionScaleFactor((inputPrefix+"_MC_SF_AK4PFchs.txt").c_str());
  if(year=="2016"){
    jetResolutiona = new JME::JetResolution((inputPrefix+"/preVFP_JRV3/Summer20UL16APV_JRV3_MC_PtResolution_AK4PFchs.txt").c_str());
    jetResolutionScaleFactora = new JME::JetResolutionScaleFactor((inputPrefix+"/preVFP_JRV3/Summer20UL16APV_JRV3_MC_SF_AK4PFchs.txt").c_str());

    jetResolutionb = new JME::JetResolution((inputPrefix+"/postVFP_JRV3/Summer20UL16_JRV3_MC_PtResolution_AK4PFchs.txt").c_str());
    jetResolutionScaleFactorb = new JME::JetResolutionScaleFactor((inputPrefix+"/postVFP_JRV3/Summer20UL16_JRV3_MC_SF_AK4PFchs.txt").c_str());
  }else{
    jetResolution = new JME::JetResolution((inputPrefix+"_MC_PtResolution_AK4PFchs.txt").c_str());
    jetResolutionScaleFactor = new JME::JetResolutionScaleFactor((inputPrefix+"_MC_SF_AK4PFchs.txt").c_str());
  }
    //jetParam = new JME::JetParameters();

    // cout << "INIT JER" << endl;
    // JERParam = new JetCorrectorParameters((inputPrefix+"_MC_PtResolution_AK4PFchs.txt").c_str());
    // cout << "INIT JER" << endl;
    // std::vector<JetCorrectorParameters> vPar;
    // cout << "INIT JER" << endl;
    // vPar.push_back(*JERParam);
    // cout << "INIT JER" << endl;
    // JetCorrector = new FactorizedJetCorrector(vPar);
    // cout << "INIT JER" << endl;

    // cout << JetCorrector << endl;
}

void Selector::init_RoccoR(std::string path)
{
  rc16 = RoccoR(Form("%s/weight/RoccoR/RoccoR2016.txt",path.c_str()));
  rc16a = RoccoR(Form("%s/weightUL/RoccoR/RoccoR2016aUL.txt",path.c_str()));
  rc16b = RoccoR(Form("%s/weightUL/RoccoR/RoccoR2016bUL.txt",path.c_str()));
  rc17 = RoccoR(Form("%s/weightUL/RoccoR/RoccoR2017UL.txt",path.c_str()));
  rc18 = RoccoR(Form("%s/weightUL/RoccoR/RoccoR2018UL.txt",path.c_str()));

  if(IsDebug) Info("Selector::init_RoccoR","Rochester correction files loaded.");
}

void Selector::process_objects(string path, EventTree* inp_tree){
    tree = inp_tree;
    clear_vectors();
    if(IsDebug) Info("Selector::process_objects","Cleared vectors");
        
}

void Selector::clear_vectors(){

    Electrons.clear();
    ElectronsLoose.clear();
    ElectronsMedium.clear();
    ElectronsNoIso.clear();
    ElectronsNoIsoLoose.clear();

    Muons.clear();
    MuonsLoose.clear();
    MuonsNoIso.clear();
    MuonsNoIsoLoose.clear();
    MuonsMiniAOD.clear();

    TausLoose.clear();
    TausMedium.clear();
    TausTight.clear();
    Taus.clear();

    Jets.clear();
    bJets.clear();
    FwdJets.clear();

    MuRelIso_corr.clear();
    // JetsJERPt.clear();
    // JetsPreSelPt.clear();;
    // JetsCleaningPt.clear();;
    // JetsPreSel.clear();;
    // JetsCleaning.clear();;
    JetsPtSmeared.clear();
    jet_resolution.clear();
    jet_isTagged.clear();

    JetsNoCorr.clear();

    nEleSelIso = 0;
    nMuSelIso = 0;
}

void Selector::filter_electrons(EventTree *event){
  
  tree = event;

  for(int eleInd = 0; eleInd < int(tree->nEle_) and int(tree->nEle_) <= 20 ; ++eleInd){
    //20 is the arraysize for electron as defined in EventTree.h

    double eta = tree->eleEta_[eleInd];
    double absEta = TMath::Abs(eta);
    double phi = tree->elePhi_[eleInd];
    double SCeta = eta + tree->eleDeltaEtaSC_[eleInd];
    double absSCEta = TMath::Abs(SCeta);
	
    double pt = tree->elePt_[eleInd];
        
    // // EA subtraction
    double PFrelIso_corr = tree->elePFRelIso_[eleInd];
    
    // uint eleID = tree->eleIDcutbased_[eleInd];
    // bool passVetoID   = eleID >= 1;
    // bool passLooseID  = eleID >= 2;
    // bool passMediumID = eleID >= 3;
    // bool passTightID  = eleID >= 4;
    
    bool passMVALooseID = tree->eleIDmvaLoose_[eleInd];
    bool passMVAWP80ID = tree->eleIDmvaWP80_[eleInd];
    //bool passMVAWP90ID = tree->eleIDmvaWP90_[eleInd];
    
    bool passRelIsoSel = ((absSCEta < 1.479 && PFrelIso_corr < ele_RelIso_tight_EB) ||
			   (absSCEta > 1.479 && PFrelIso_corr < ele_RelIso_tight_EE));
    bool passRelIsoVeto = ((absSCEta < 1.479 && PFrelIso_corr < ele_RelIso_loose_EB) ||
			   (absSCEta > 1.479 && PFrelIso_corr < ele_RelIso_loose_EE));
    
    // make sure it doesn't fall within the gap
    bool passEtaEBEEGap = (absSCEta < 1.4442) || (absSCEta > 1.566);
	
    // D0 and Dz cuts are different for barrel and endcap
    bool passD0 = ((absSCEta < 1.479 && TMath::Abs(tree->eleD0_[eleInd]) < 0.05) ||
		   (absSCEta > 1.479 && TMath::Abs(tree->eleD0_[eleInd]) < 0.1));
    bool passDz = ((absSCEta < 1.479 && TMath::Abs(tree->eleDz_[eleInd]) < 0.1) ||
		   (absSCEta > 1.479 && TMath::Abs(tree->eleDz_[eleInd]) < 0.2));
        
        
    // bool eleSel = (passEtaEBEEGap && 
    // 		   absSCEta <= ele_Eta_cut &&
    // 		   pt >= ele_Pt_cut &&
    // 		   passMediumID &&
    // 		   passD0 &&
    // 		   passDz);
	
    // bool looseSel = ( passEtaEBEEGap && 
    // 		      absSCEta <= ele_EtaLoose_cut &&
    // 		      pt >= ele_PtLoose_cut &&
    // 		      passVetoID &&
    // 		      passD0 &&
    // 		      passDz);
    
    bool eleSel = (passEtaEBEEGap && 
		   absSCEta <= ele_Eta_cut &&
		   pt >= ele_Pt_cut &&
		   passMVAWP80ID &&
		   passD0 &&
		   passDz);
	
    bool looseSel = ( passEtaEBEEGap && 
		      absSCEta <= ele_EtaLoose_cut &&
		      pt >= ele_PtLoose_cut &&
		      passMVALooseID &&
		      passRelIsoVeto &&
		      passD0 &&
		      passDz);
	

    if( eleSel ){
      Electrons.push_back(eleInd);
      if(passRelIsoSel) nEleSelIso++ ;
    }else if( looseSel ){ 
      ElectronsLoose.push_back(eleInd);
    }
  }//ele loop

    
}

void Selector::filter_muons(EventTree *event){
  
  tree = event;
  
  for(int muInd = 0; muInd < int(tree->nMuon_) and int(tree->nMuon_) <= 15; ++muInd){
    //15 is the arraysize for muon as defined in EventTree.h
    
    float eta = tree->muEta_[muInd];
    float pt = tree->muPt_[muInd];
    float phi = tree->muPhi_[muInd];
    int nTrackerLayers = tree->munTrackerLayers_[muInd];
    int charge =  tree->muCharge_[muInd];
    float mudxy = tree->mudxy_[muInd];
    float mudz = tree->mudz_[muInd];

    //Protection for crash during RochCorr
    if(TMath::Abs(charge)!=1 or nTrackerLayers>=20 or nTrackerLayers<0
       or !(TMath::Finite(eta)) or !(TMath::Finite(pt)) or !(TMath::Finite(phi))
       or TMath::Abs(mudxy)>=0.2 or TMath::Abs(mudz)>=0.5) continue; 
    //max nTrackerLayers should be 18 as seen in data and MC
    
    double SFRochCorr = 1.0;
    if(!TMath::AreEqualAbs(eta,0.0,1.0e-7) and !TMath::AreEqualAbs(pt,0.0,1.0e-7) and !TMath::AreEqualAbs(phi,0.0,1.0e-7)){
      if (tree->isData_){
	if(year=="2016"){
	  if(isPreVFP)
	    SFRochCorr *= rc16a.kScaleDT(charge, pt, eta, phi);
	  if(isPostVFP)
	    SFRochCorr *= rc16b.kScaleDT(charge, pt, eta, phi);
	}else if(year=="2017"){
	  SFRochCorr *= rc17.kScaleDT(charge, pt, eta, phi);
	}else if(year=="2018"){
	  SFRochCorr *= rc18.kScaleDT(charge, pt, eta, phi);
	}
      }else{
	int genIdx = tree->muGenPartIdx_[muInd];
	
	if ( (genIdx>-1) && (genIdx < int(tree->nGenPart_))){
	  double genPt = tree->GenPart_pt_[genIdx];
	  //cout << "rec PT " << pt << ", Gen PT " << genPt << endl;
	  if(year=="2016"){
	    if(isPreVFP)
	      SFRochCorr *= rc16a.kSpreadMC(charge, pt, eta, phi, genPt);
	    if(isPostVFP)
	      SFRochCorr *= rc16b.kSpreadMC(charge, pt, eta, phi, genPt);	
	  }else if(year=="2017"){
	    SFRochCorr *= rc17.kSpreadMC(charge, pt, eta, phi, genPt);	
	  }else if(year=="2018"){
	    SFRochCorr *= rc18.kSpreadMC(charge, pt, eta, phi, genPt);	
	  }
	}else{
	  if(year=="2016"){
	    if(isPreVFP)
	      SFRochCorr *= rc16a.kSmearMC(charge, pt, eta, phi, nTrackerLayers, generator->Rndm());
	    if(isPostVFP)
	      SFRochCorr *= rc16b.kSmearMC(charge, pt, eta, phi, nTrackerLayers, generator->Rndm());	
	  }else if(year=="2017"){
	    SFRochCorr *= rc17.kSmearMC(charge, pt, eta, phi, nTrackerLayers, generator->Rndm());	
	  }else if(year=="2018"){
	    SFRochCorr *= rc18.kSmearMC(charge, pt, eta, phi, nTrackerLayers, generator->Rndm());	
	  }	  
	}//if GenPart

      }//is Data or MC
    }
    tree->muRoccoR_[muInd] = SFRochCorr;
    pt = pt*SFRochCorr;
    
    double PFrelIso_corr = tree->muPFRelIso_[muInd];
    
    //bool vetoMuonID = tree->muIsPFMuon_[muInd] && (tree->muIsTracker_[muInd] || tree->muIsGlobal_[muInd]);
    //bool mediumMuonID = tree->muMediumId_[muInd];
    bool looseMuonID = tree->muLooseId_[muInd]; //This is same as veto condition defined above
    bool mediumPromptMuonID = tree->muMediumPromptId_[muInd];
    
    bool muSel = (TMath::Abs(eta) <= mu_Eta_tight &&
		  pt >= mu_Pt_cut &&
		  mediumPromptMuonID 
		  //mediumMuonID 
		  );
    
    bool passLoose = (TMath::Abs(eta) <= mu_Eta_loose &&
		      pt >= mu_PtLoose_cut &&
		      looseMuonID &&
		      PFrelIso_corr < mu_RelIso_loose);
    
    if(muSel){
      Muons.push_back(muInd);
      if(PFrelIso_corr<mu_RelIso_tight) nMuSelIso++;
    }else if (passLoose){
      MuonsLoose.push_back(muInd);
    }
    
  }//muon loop
}

// For Tau Analysis
void Selector::filter_taus(EventTree *event){

  tree = event;
  //  cout << " (inside from filter_taus)"<<"tree->event="<<tree->event_<<"___tree->nTau_=" << tree->nTau_ << endl;
  /*if (tree->event_==1561){
    cout << "Found Event, Starting Taus" << endl;
    cout << " nTau=" << tree->nTau_ << endl;
    }*/
  for(int tauInd = 0; tauInd < tree->nTau_; ++tauInd){
   
    double eta = tree->tauEta_[tauInd];
    double pt = tree->tauPt_[tauInd];
    double dz = tree->tauDz_[tauInd];
    Int_t  charge = tree->tauCharge_[tauInd];
    Int_t decayMode = tree->tauDecayMode_[tauInd];

    int tauIdDeepTau2017v2p1VSe = tree->tauIdDeepTau2017v2p1VSe_[tauInd];
    int tauIdDeepTau2017v2p1VSjet = tree->tauIdDeepTau2017v2p1VSjet_[tauInd];
    int tauIdDeepTau2017v2p1VSmu = tree->tauIdDeepTau2017v2p1VSmu_[tauInd];
    
    
    bool hadronicTau = (decayMode ==0 || decayMode==1 ||decayMode==2 ||decayMode==5 ||decayMode==6 ||decayMode== 10 ||decayMode== 11) ; 
      
    bool generalTau =( pt >= tau_Pt_cut && 
		       TMath::Abs(eta) <= tau_Eta_cut &&
                        dz <0.2 &&
		       TMath::Abs(charge) ==1
		       );
    bool looseTauID =( tauIdDeepTau2017v2p1VSe >= 1 &&
                       tauIdDeepTau2017v2p1VSjet >=1 && 
                       tauIdDeepTau2017v2p1VSmu >= 1 
		       );
    bool looseTauIDTest =( tauIdDeepTau2017v2p1VSjet >=1 &&
			   tauIdDeepTau2017v2p1VSmu >= 1
			   );

    bool mediumTauID =( tauIdDeepTau2017v2p1VSe >=16 &&
                       tauIdDeepTau2017v2p1VSjet >=16 &&
                       tauIdDeepTau2017v2p1VSmu>=4
			);

    bool tightTauID =( tauIdDeepTau2017v2p1VSe > 128 &&
                       tauIdDeepTau2017v2p1VSjet >128 &&
                       tauIdDeepTau2017v2p1VSmu> 8
                       );

    bool passLoose = ( hadronicTau && generalTau && looseTauID );
    bool passLooseTest = (hadronicTau && generalTau && looseTauIDTest );
    bool passMedium = (hadronicTau && generalTau && mediumTauID);

    bool passTight = ( hadronicTau && generalTau && tightTauID );
    
    //cout << "This is inside tau filter" << endl;
    
    
    /*
    if (tree->event_==printEvent){
      cout << "-- " << tauInd <<" passTight="<<passTight<< "passMedium" << passMedium <<" passLoose="<<passLoose <<" pt="<<pt<< " eta="<<eta<< " phi="<<tree->tauPhi_[tauInd]<< " tightID="<<tightTauID<< "mediumID" << mediumTauID<<" looseID="<<looseTauID << endl;
    }
    */
    if(passMedium)
      Taus.push_back(tauInd); 
    
    if(passLoose)
      TausLoose.push_back(tauInd);                                                                                                                                       
    if(passMedium)
      TausMedium.push_back(tauInd); 
    
    if(passTight)
      TausTight.push_back(tauInd);       
    
  }
}

void Selector::filter_jets(int tauId_1, int tauId_2){
  
  for(int jetInd = 0; jetInd < int(tree->nJet_) && int(tree->nJet_) <= 200 ; ++jetInd){ //200 is the array size for jets as defined in EventTree 
    
    double pt = tree->jetPt_[jetInd];
    double eta = tree->jetEta_[jetInd];
    double phi = tree->jetPhi_[jetInd];
    double smearedpt = tree->jetPt_[jetInd];
    
    //Applied for Legacy Rereco
    // //tight ID for 2016 (bit 0), tightLeptVeto for 2017 (bit 1)
    int jetID_cutBit = 1;
    if (year=="2016"){ jetID_cutBit = 0; }
    //bool jetID_pass = (tree->jetID_[jetInd]>>0 & 1 && looseJetID) || (tree->jetID_[jetInd]>>jetID_cutBit & 1);
    
    //Default applied for LRR
    //bool jetID_pass = (tree->jetID_[jetInd]>=2) ;    
    //Applied for UL
    //bool jetID_pass = (tree->jetID_[jetInd]>=2) ;    
    //Applied for UL
    //bool jetID_pass = (tree->jetID_[jetInd]>=2 and (tree->jetPUID_[jetInd]>=1 or pt>=50.0)) ; //lwp
    //tight PU
    //bool jetID_pass = (tree->jetID_[jetInd]>=2 and (tree->jetPUID_[jetInd]>=7 or pt>=50.0)) ; //twp
    //TLV only
    bool jetID_pass = (tree->jetID_[jetInd]>=6 && (tree->jetPUID_[jetInd]>=1 || pt>=50.0)) ; //twp previous
    //Tightmost test
    //bool jetID_pass = (tree->jetID_[jetInd]>=6 and (tree->jetPUID_[jetInd]>=7 or pt>=50.0)) ; //twp
    
    
    double jetSF = 1.;

    double resolution = 0.;
    if (!tree->isData_){
      jetParam.setJetEta(tree->jetEta_[jetInd]);
      jetParam.setJetPt(tree->jetPt_[jetInd]);
      jetParam.setJetArea(tree->jetArea_[jetInd]);
      jetParam.setRho(tree->rho_);
      if(year=="2016"){
	if(isPreVFP){
	  resolution = jetResolutiona->getResolution(jetParam);  
	  if (JERsystLevel==1) jetSF = jetResolutionScaleFactora->getScaleFactor(jetParam,Variation::NOMINAL);
	  if (JERsystLevel==0) jetSF = jetResolutionScaleFactora->getScaleFactor(jetParam,Variation::DOWN);
	  if (JERsystLevel==2) jetSF = jetResolutionScaleFactora->getScaleFactor(jetParam,Variation::UP);
	}
	if(isPostVFP){
	  resolution = jetResolutionb->getResolution(jetParam);  
	  if (JERsystLevel==1) jetSF = jetResolutionScaleFactorb->getScaleFactor(jetParam,Variation::NOMINAL);
	  if (JERsystLevel==0) jetSF = jetResolutionScaleFactorb->getScaleFactor(jetParam,Variation::DOWN);
	  if (JERsystLevel==2) jetSF = jetResolutionScaleFactorb->getScaleFactor(jetParam,Variation::UP);
	}
      }else{
	
	resolution = jetResolution->getResolution(jetParam);  
	if (JERsystLevel==1) jetSF = jetResolutionScaleFactor->getScaleFactor(jetParam,Variation::NOMINAL);
	if (JERsystLevel==0) jetSF = jetResolutionScaleFactor->getScaleFactor(jetParam,Variation::DOWN);
	if (JERsystLevel==2) jetSF = jetResolutionScaleFactor->getScaleFactor(jetParam,Variation::UP);

      }
      double jetSmear = 1.;
      
      if(IsDebug) 
	cout << "\t genID : " << tree->jetGenJetIdx_[jetInd] << ", ngenjet : " << int(tree->nGenJet_) << ", recojet : " << int(tree->nJet_) <<  endl;
      
      int genIdx = tree->jetGenJetIdx_[jetInd];
      
      if ( (genIdx>-1) && (genIdx < int(tree->nGenJet_))){
	double genJetPt = tree->GenJet_pt_[genIdx];
	jetSmear = 1. + (jetSF - 1.) * (pt - genJetPt)/pt;
      }else{
	jetSmear = 1 + generator->Gaus(0, resolution) * sqrt( max(jetSF*jetSF - 1, 0.) );
      }
      
      smearedpt = pt*jetSmear;
      
      if (smearJetPt) // Default
	pt = pt*jetSmear;
      
    }//isMC

    bool passDR_lep_jet = true;

    //loop over selected electrons
    for(std::vector<int>::const_iterator eleInd = Electrons.begin(); eleInd != Electrons.end(); eleInd++) 
      if (dR(eta, phi, tree->eleEta_[*eleInd], tree->elePhi_[*eleInd]) < veto_lep_jet_dR) passDR_lep_jet = false;
    
    //loop over selected muons
    for(std::vector<int>::const_iterator muInd = Muons.begin(); muInd != Muons.end(); muInd++) 
      if (dR(eta, phi, tree->muEta_[*muInd], tree->muPhi_[*muInd]) < veto_lep_jet_dR) passDR_lep_jet = false;

    //loop over selected taus                                                                                                                   
    //for(std::vector<int>::const_iterator tauInd = Taus.begin(); tauInd != Taus.end(); tauInd++)                                             
    //if (dR(eta, phi, tree->tauEta_[*tauInd], tree->tauPhi_[*tauInd]) < veto_lep_jet_dR) passDR_lep_jet = false;                       
    if (dR(eta, phi, tree->tauEta_[tauId_1], tree->tauPhi_[tauId_1]) < veto_lep_jet_dR) passDR_lep_jet = false;                          
    if (dR(eta, phi, tree->tauEta_[tauId_2], tree->tauPhi_[tauId_2]) < veto_lep_jet_dR) passDR_lep_jet = false; 
    
                                                                                                                                
    bool jetSel = (TMath::Abs(eta) <= jet_Eta_cut &&
		      pt >= jet_Pt_cut &&
		      jetID_pass &&
		   passDR_lep_jet);
    
    if( jetSel ){
      Jets.push_back(jetInd);
      JetsPtSmeared.push_back(smearedpt);
      //jet_resolution.push_back(resolution);
      jet_resolution.push_back(jetSF);
      if (!useDeepCSVbTag){
	//if( tree->jetBtagCSVV2_[jetInd] > btag_cut){
	if( tree->jetBtagDeepFlavB_[jetInd] > btag_cut){
	  bJets.push_back(jetInd);
	  jet_isTagged.push_back(true);
	} else {
	  jet_isTagged.push_back(false);
	}
      } else {
	if( tree->jetBtagDeepB_[jetInd] > btag_cut_DeepCSV){
	  bJets.push_back(jetInd);
	  jet_isTagged.push_back(true);
	} else {
	  jet_isTagged.push_back(false);
	}
      }
    }//presel condition
    
  }//main jet loop 
  
}



/*
void Selector::filter_jets(int tauId_1, int tauId_2){

  
  cout<<"inside from filter_jets....and tauId's are= "<<tauId_1<<"...&.."<<tauId_2<<endl;
  
  for(int jetInd = 0; jetInd < tree->nJet_ && tree->nJet_ <= 200; ++jetInd){ //200 is the array size for jets as defined in EventTree 
    // if(jetInd!=tauId_1 || jetInd !=tauId_2){
      cout<<"inside from filter_jets"<<endl;
      double pt = tree->jetPt_[jetInd];
      double eta = tree->jetEta_[jetInd];
      double phi = tree->jetPhi_[jetInd];
      double smearedpt = tree->jetPt_[jetInd];
      
      //Applied for Legacy Rereco
      // //tight ID for 2016 (bit 0), tightLeptVeto for 2017 (bit 1)
      int jetID_cutBit = 1;
      if (year=="2016"){ jetID_cutBit = 0; }
      bool jetID_pass = (tree->jetID_[jetInd]>>0 & 1 && looseJetID) || (tree->jetID_[jetInd]>>jetID_cutBit & 1);
      
      //Default applied for LRR
      //bool jetID_pass = (tree->jetID_[jetInd]>=2) ;    
      //Applied for UL
      //bool jetID_pass = (tree->jetID_[jetInd]>=2) ;    
      //Applied for UL
      //bool jetID_pass = (tree->jetID_[jetInd]>=2 and (tree->jetPUID_[jetInd]>=1 or pt>=50.0)) ; //lwp
      //tight PU
      //bool jetID_pass = (tree->jetID_[jetInd]>=2 and (tree->jetPUID_[jetInd]>=7 or pt>=50.0)) ; //twp
      //TLV only
      // bool jetID_pass = (tree->jetID_[jetInd]>=6 && (tree->jetPUID_[jetInd]>=1 || pt>=50.0)) ; //twp //previous one
      //Tightmost test
      //bool jetID_pass = (tree->jetID_[jetInd]>=6 and (tree->jetPUID_[jetInd]>=7 or pt>=50.0)) ; //twp
      
      
      double jetSF = 1.;
      
      double resolution = 0.;
      if (!tree->isData_){
	jetParam.setJetEta(tree->jetEta_[jetInd]);
	jetParam.setJetPt(tree->jetPt_[jetInd]);
	jetParam.setJetArea(tree->jetArea_[jetInd]);
	jetParam.setRho(tree->rho_);
	if(year=="2016"){
	  if(isPreVFP){
	    resolution = jetResolutiona->getResolution(jetParam);  
	    if (JERsystLevel==1) jetSF = jetResolutionScaleFactora->getScaleFactor(jetParam,Variation::NOMINAL);
	    if (JERsystLevel==0) jetSF = jetResolutionScaleFactora->getScaleFactor(jetParam,Variation::DOWN);
	    if (JERsystLevel==2) jetSF = jetResolutionScaleFactora->getScaleFactor(jetParam,Variation::UP);
	  }
	  if(isPostVFP){
	    resolution = jetResolutionb->getResolution(jetParam);  
	    if (JERsystLevel==1) jetSF = jetResolutionScaleFactorb->getScaleFactor(jetParam,Variation::NOMINAL);
	    if (JERsystLevel==0) jetSF = jetResolutionScaleFactorb->getScaleFactor(jetParam,Variation::DOWN);
	    if (JERsystLevel==2) jetSF = jetResolutionScaleFactorb->getScaleFactor(jetParam,Variation::UP);
	}
	}else{
	  
	  resolution = jetResolution->getResolution(jetParam);  
	  if (JERsystLevel==1) jetSF = jetResolutionScaleFactor->getScaleFactor(jetParam,Variation::NOMINAL);
	  if (JERsystLevel==0) jetSF = jetResolutionScaleFactor->getScaleFactor(jetParam,Variation::DOWN);
	  if (JERsystLevel==2) jetSF = jetResolutionScaleFactor->getScaleFactor(jetParam,Variation::UP);
	  
	}
	double jetSmear = 1.;
	
	if(IsDebug) 
	  cout << "\t genID : " << tree->jetGenJetIdx_[jetInd] << ", ngenjet : " << int(tree->nGenJet_) << ", recojet : " << int(tree->nJet_) <<  endl;
	
	int genIdx = tree->jetGenJetIdx_[jetInd];
	
	if ( (genIdx>-1) && (genIdx < int(tree->nGenJet_))){
	  double genJetPt = tree->GenJet_pt_[genIdx];
	  jetSmear = 1. + (jetSF - 1.) * (pt - genJetPt)/pt;
	}else{
	  jetSmear = 1 + generator->Gaus(0, resolution) * sqrt( max(jetSF*jetSF - 1, 0.) );
	}
	
	smearedpt = pt*jetSmear;
	
	if (smearJetPt) // Default
	  pt = pt*jetSmear;
	
      }//isMC
      
      bool passDR_lep_jet = true;
      
      //loop over selected electrons
      for(std::vector<int>::const_iterator eleInd = Electrons.begin(); eleInd != Electrons.end(); eleInd++) 
	if (dR(eta, phi, tree->eleEta_[*eleInd], tree->elePhi_[*eleInd]) < veto_lep_jet_dR) passDR_lep_jet = false;
      
      //loop over selected muons
      for(std::vector<int>::const_iterator muInd = Muons.begin(); muInd != Muons.end(); muInd++) 
	if (dR(eta, phi, tree->muEta_[*muInd], tree->muPhi_[*muInd]) < veto_lep_jet_dR) passDR_lep_jet = false;
      
      //loop over selected taus                                                                                                                
                                                                                                                                   
      //  for(std::vector<int>::const_iterator tauInd = Taus.begin(); tauInd != Taus.end(); tauInd++)
      //	if (dR(eta, phi, tree->tauEta_[*tauInd], tree->tauPhi_[*tauInd]) < veto_lep_jet_dR) passDR_lep_jet = false;
      
      
      if (dR(eta, phi, tree->tauEta_[tauId_1], tree->tauPhi_[tauId_1]) < veto_lep_jet_dR) passDR_lep_jet = false;
      if (dR(eta, phi, tree->tauEta_[tauId_2], tree->tauPhi_[tauId_2]) < veto_lep_jet_dR) passDR_lep_jet = false;
      
      bool jetSel = (TMath::Abs(eta) <= jet_Eta_cut &&
		     pt >= jet_Pt_cut &&
		     jetID_pass &&
		     passDR_lep_jet);
      
      if( jetSel ){
	Jets.push_back(jetInd);
	JetsPtSmeared.push_back(smearedpt);
	//jet_resolution.push_back(resolution);
	jet_resolution.push_back(jetSF);
	if (!useDeepCSVbTag){
	  //if( tree->jetBtagCSVV2_[jetInd] > btag_cut){
	  if( tree->jetBtagDeepFlavB_[jetInd] > btag_cut){
	    bJets.push_back(jetInd);
	    jet_isTagged.push_back(true);
	  } else {
	    jet_isTagged.push_back(false);
	  }
	} else {
	  if( tree->jetBtagDeepB_[jetInd] > btag_cut_DeepCSV){
	    bJets.push_back(jetInd);
	    jet_isTagged.push_back(true);
	  } else {
	    jet_isTagged.push_back(false);
	  }
	}		
      }//presel condition
      // }
    }//main jet loop 
    
  }
*/
void Selector::filter_jetsNoCorr(){
  
  
  for(int jetInd = 0; jetInd < int(tree->nJet_) and int(tree->nJet_) <= 200 ; ++jetInd){
    
    double pt = tree->jetPt_[jetInd];
    double eta = tree->jetEta_[jetInd];
    double phi = tree->jetPhi_[jetInd];
    
    //Default applied for LRR
    //bool jetID_pass = (tree->jetID_[jetInd]>=2) ;    
    //bool jetID_pass = (tree->jetID_[jetInd]>=2 and (tree->jetPUID_[jetInd]>=1 or pt>=50.0)) ; //loose wp
    //TLV only
    bool jetID_pass = (tree->jetID_[jetInd]>=6 and (tree->jetPUID_[jetInd]>=1 or pt>=50.0)) ; //twp

    if(IsDebug) Info("Selector::filter_jetsNoCorr","applied filter");
    //////////////////////////////////////////////// NanoAOD selection //////////////////////////////////////////////////////////
    bool passDR_lep_jet = true;
    //loop over selected electrons
    for(std::vector<int>::const_iterator eleInd = Electrons.begin(); eleInd != Electrons.end(); eleInd++) 
      if (dR(eta, phi, tree->eleEta_[*eleInd], tree->elePhi_[*eleInd]) < veto_lep_jet_dR) passDR_lep_jet = false;

    //loop over selected muons
    for(std::vector<int>::const_iterator muInd = Muons.begin(); muInd != Muons.end(); muInd++) 
      if (dR(eta, phi, tree->muEta_[*muInd], tree->muPhi_[*muInd]) < veto_lep_jet_dR) passDR_lep_jet = false;
      
    bool jetPresel = (pt >= jet_Pt_cut and TMath::Abs(eta) <= jet_Eta_cut and jetID_pass and passDR_lep_jet);
    if(IsDebug) Info("Selector::filter_jetsNoCorr","Processed nano");
    //////////////////////////////////////////////// NanoAOD selection //////////////////////////////////////////////////////////
    
    if( jetPresel ){
      JetsNoCorr.push_back(jetInd);
    }//presel condition

  }//main jet loop 
    
}


void Selector::filter_mets(){
  
  TLorentzVector MET;
  MET.SetPtEtaPhiM(tree->MET_pt_, 0., tree->MET_phi_, 0.);
  
  TVector3 jet, jetSmeared;
  double metX = MET.Px(); 
  double metY = MET.Py();
  if (!tree->isData_){
    for (unsigned int ijet = 0; ijet < JetsNoCorr.size(); ijet++){		
      int jetInd = JetsNoCorr.at(ijet);
      double pt = tree->jetPt_[jetInd];
      double eta = tree->jetEta_[jetInd];
      double phi = tree->jetPhi_[jetInd];

      jetParam.setJetEta(tree->jetEta_[jetInd]);
      jetParam.setJetPt(tree->jetPt_[jetInd]);
      jetParam.setJetArea(tree->jetArea_[jetInd]);
      jetParam.setRho(tree->rho_);
      double resolution = 1.0;
      double jetSF = 1.0;
      
      if(year=="2016"){
	if(isPreVFP){
	  resolution = jetResolutiona->getResolution(jetParam);  
	  if (JERsystLevel==1) jetSF = jetResolutionScaleFactora->getScaleFactor(jetParam,Variation::NOMINAL);
	  if (JERsystLevel==0) jetSF = jetResolutionScaleFactora->getScaleFactor(jetParam,Variation::DOWN);
	  if (JERsystLevel==2) jetSF = jetResolutionScaleFactora->getScaleFactor(jetParam,Variation::UP);
	}
	if(isPostVFP){
	  resolution = jetResolutionb->getResolution(jetParam);  
	  if (JERsystLevel==1) jetSF = jetResolutionScaleFactorb->getScaleFactor(jetParam,Variation::NOMINAL);
	  if (JERsystLevel==0) jetSF = jetResolutionScaleFactorb->getScaleFactor(jetParam,Variation::DOWN);
	  if (JERsystLevel==2) jetSF = jetResolutionScaleFactorb->getScaleFactor(jetParam,Variation::UP);
	}
      }else{
	
	resolution = jetResolution->getResolution(jetParam);  
	if (JERsystLevel==1) jetSF = jetResolutionScaleFactor->getScaleFactor(jetParam,Variation::NOMINAL);
	if (JERsystLevel==0) jetSF = jetResolutionScaleFactor->getScaleFactor(jetParam,Variation::DOWN);
	if (JERsystLevel==2) jetSF = jetResolutionScaleFactor->getScaleFactor(jetParam,Variation::UP);

      }

      
      int genIdx = tree->jetGenJetIdx_[jetInd];
      double jetSmear = 1.0 ;
      if ( (genIdx>-1) && (genIdx < int(tree->nGenJet_))){
      	double genJetPt = tree->GenJet_pt_[genIdx];
      	jetSmear = 1. + (jetSF - 1.) * (pt - genJetPt)/pt;
      }else{
      	jetSmear = 1 + generator->Gaus(0, resolution) * sqrt( max(jetSF*jetSF - 1, 0.) );
      }
      
      jet.SetPtEtaPhi(pt,eta,phi);
      jetSmeared.SetPtEtaPhi(jetSmear*pt,eta,phi);
      
      metX += jet.Px(); 
      metY += jet.Py(); 

      metX -= jetSmeared.Px();
      metY -= jetSmeared.Py();

    }
  }//isMC
  
  MET.SetXYZM(metX, metY, 0., 0.);
  
  METPt  = MET.Pt();
  METPhi = MET.Phi();

  
}



void Selector::metWithUncl()
{

  TLorentzVector MET;
  MET.SetPtEtaPhiM(tree->MET_pt_, 0., tree->MET_phi_, 0.);

  double metX = MET.Px(); 
  double metY = MET.Py();

  if (!tree->isData_){

    TVector3 jet; 
    for (unsigned int ijet = 0; ijet < JetsNoCorr.size(); ijet++){		
      int jetInd = JetsNoCorr.at(ijet);
      double pt = tree->jetPt_[jetInd];
      double eta = tree->jetEta_[jetInd];
      double phi = tree->jetPhi_[jetInd];
      
      jet.SetPtEtaPhi(pt,eta,phi);
      
      metX += jet.Px(); 
      metY += jet.Py(); 
    }

    //loop over selected muons
    TVector3 muon; 
    for(std::vector<int>::const_iterator muInd = Muons.begin(); muInd != Muons.end(); muInd++) {
      muon.SetPtEtaPhi(tree->muPt_[*muInd], tree->muEta_[*muInd], tree->muPhi_[*muInd]);
      metX += muon.Px(); 
      metY += muon.Py(); 
    }

    //loop over selected electrons
    TVector3 electron; 
    for(std::vector<int>::const_iterator eleInd = Electrons.begin(); eleInd != Electrons.end(); eleInd++) {
      electron.SetPtEtaPhi(tree->elePt_[*eleInd], tree->eleEta_[*eleInd], tree->elePhi_[*eleInd]);
      metX += electron.Px(); 
      metY += electron.Py(); 	
    }
    
    metX *= (1 + METUnc*0.1); //vary by 10%
    metY *= (1 + METUnc*0.1);

    //loop over selected electrons
    for(std::vector<int>::const_iterator eleInd = Electrons.begin(); eleInd != Electrons.end(); eleInd++) {
      electron.SetPtEtaPhi(tree->elePt_[*eleInd], tree->eleEta_[*eleInd], tree->elePhi_[*eleInd]);
      metX -= electron.Px(); 
      metY -= electron.Py(); 	
    }

    for(std::vector<int>::const_iterator muInd = Muons.begin(); muInd != Muons.end(); muInd++) {
      muon.SetPtEtaPhi(tree->muPt_[*muInd], tree->muEta_[*muInd], tree->muPhi_[*muInd]);
      metX -= muon.Px(); 
      metY -= muon.Py(); 
    }
    
    for (unsigned int ijet = 0; ijet < JetsNoCorr.size(); ijet++){		
      int jetInd = JetsNoCorr.at(ijet);
      double pt = tree->jetPt_[jetInd];
      double eta = tree->jetEta_[jetInd];
      double phi = tree->jetPhi_[jetInd];
      
      jet.SetPtEtaPhi(pt,eta,phi);
      
      metX -= jet.Px(); 
      metY -= jet.Py(); 
    }
    
  }//isMC

  MET.SetXYZM(metX, metY, 0., 0.);
  
  METPt  = MET.Pt();
  METPhi = MET.Phi();

}

bool Selector::passEleID(int eleInd, int cutVal, bool doRelisoCut){

    Int_t WPcutBits = tree->eleVidWPBitmap_[eleInd];

    int nBits = 3;

    bool MinPtCut                            = (WPcutBits>>(0*nBits) & 7) >= cutVal;
    bool GsfEleSCEtaMultiRangeCut            = (WPcutBits>>(1*nBits) & 7) >= cutVal;
    bool GsfEleDEtaInSeedCut                 = (WPcutBits>>(2*nBits) & 7) >= cutVal;
    bool GsfEleDPhiInCut                     = (WPcutBits>>(3*nBits) & 7) >= cutVal;
    bool GsfEleFull5x5SigmaIEtaIEtaCut       = (WPcutBits>>(4*nBits) & 7) >= cutVal;
    bool GsfEleHadronicOverEMEnergyScaledCut = (WPcutBits>>(5*nBits) & 7) >= cutVal;
    bool GsfEleEInverseMinusPInverseCut      = (WPcutBits>>(6*nBits) & 7) >= cutVal;
    bool GsfEleEffAreaPFIsoCut               = (WPcutBits>>(7*nBits) & 7) >= cutVal;
    bool GsfEleConversionVetoCut             = (WPcutBits>>(8*nBits) & 7) >= cutVal;
    bool GsfEleMissingHitsCut                = (WPcutBits>>(9*nBits) & 7) >= cutVal;

    bool passID = (
		   MinPtCut
		   && GsfEleSCEtaMultiRangeCut
		   && GsfEleDEtaInSeedCut
		   && GsfEleDPhiInCut
		   && GsfEleFull5x5SigmaIEtaIEtaCut
		   && GsfEleHadronicOverEMEnergyScaledCut
		   && GsfEleEInverseMinusPInverseCut
		   && (GsfEleEffAreaPFIsoCut || !doRelisoCut)
		   && GsfEleConversionVetoCut
		   && GsfEleMissingHitsCut
		   );

    return passID;

}


Selector::~Selector(){

  // if(year=="2016"){
  //   delete rca;  
  //   delete rcb;
  // }else
  //   delete rc;
  
}
