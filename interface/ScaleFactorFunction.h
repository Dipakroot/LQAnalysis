
//////////////////////////
// Cross Sections Used  //
//////////////////////////

std::map<std::string, vector<double> > crossSections;
std::map<std::string, vector<double> > numberOfEvents;

void initCrossSections(){

  crossSections["LQsToTauTauTTbar_LQM1000"]  =  {5.73, 5.73, 5.73}; //NLO
  crossSections["LQsToTauTauTTbar_LQM1100"]  =  {2.86, 2.86, 2.86}; //NLO
  crossSections["LQsToTauTauTTbar_LQM1200"]  =  {1.50, 1.50, 1.50}; //NLO
  
  /* crossSections["HminusM080"] = {19.13, 19.13, 19.13}; */
  /* crossSections["HminusM090"] = {19.13, 19.13, 19.13}; */
  /* crossSections["HminusM100"] = {19.13, 19.13, 19.13}; */
  /* crossSections["HminusM110"] = {19.13, 19.13, 19.13}; */
  /* crossSections["HminusM120"] = {19.13, 19.13, 19.13}; */
  /* crossSections["HminusM130"] = {19.13, 19.13, 19.13}; */
  /* crossSections["HminusM140"] = {19.13, 19.13, 19.13}; */
  /* crossSections["HminusM150"] = {19.13, 19.13, 19.13}; */
  /* crossSections["HminusM155"] = {19.13, 19.13, 19.13}; */
  /* crossSections["HminusM160"] = {19.13, 19.13, 19.13}; */

  /* crossSections["HplusM080"] = {19.13, 19.13, 19.13}; */
  /* crossSections["HplusM090"] = {19.13, 19.13, 19.13}; */
  /* crossSections["HplusM100"] = {19.13, 19.13, 19.13}; */
  /* crossSections["HplusM110"] = {19.13, 19.13, 19.13}; */
  /* crossSections["HplusM120"] = {19.13, 19.13, 19.13}; //Try 56.15 to get the previous values */
  /* crossSections["HplusM130"] = {19.13, 19.13, 19.13}; */
  /* crossSections["HplusM140"] = {19.13, 19.13, 19.13}; */
  /* crossSections["HplusM150"] = {19.13, 19.13, 19.13}; */
  /* crossSections["HplusM155"] = {19.13, 19.13, 19.13}; */
  /* crossSections["HplusM160"] = {19.13, 19.13, 19.13}; */

  crossSections["HminusM080"] = {266.16, 266.16, 266.16};
  crossSections["HminusM090"] = {266.16, 266.16, 266.16};
  crossSections["HminusM100"] = {266.16, 266.16, 266.16};
  crossSections["HminusM110"] = {266.16, 266.16, 266.16};
  crossSections["HminusM120"] = {266.16, 266.16, 266.16};
  crossSections["HminusM130"] = {266.16, 266.16, 266.16};
  crossSections["HminusM140"] = {266.16, 266.16, 266.16};
  crossSections["HminusM150"] = {266.16, 266.16, 266.16};
  crossSections["HminusM155"] = {266.16, 266.16, 266.16};
  crossSections["HminusM160"] = {266.16, 266.16, 266.16};

  crossSections["HplusM080"] = {266.16, 266.16, 266.16};
  crossSections["HplusM090"] = {266.16, 266.16, 266.16};
  crossSections["HplusM100"] = {266.16, 266.16, 266.16};
  crossSections["HplusM110"] = {266.16, 266.16, 266.16};
  crossSections["HplusM120"] = {266.16, 266.16, 266.16}; 
  crossSections["HplusM130"] = {266.16, 266.16, 266.16};
  crossSections["HplusM140"] = {266.16, 266.16, 266.16};
  crossSections["HplusM150"] = {266.16, 266.16, 266.16};
  crossSections["HplusM155"] = {266.16, 266.16, 266.16};
  crossSections["HplusM160"] = {266.16, 266.16, 266.16};

  /* crossSections["TTbarPowheg_Dilepton"] = {687.10, 0.0, 0.0}; */
  /* crossSections["TTbarPowheg_Hadronic"] = {687.10, 0.0, 0.0}; */
  /* crossSections["TTbarPowheg_Semilept"] = {687.10, 0.0, 0.0}; */
  crossSections["TTbarPowheg_Dilepton"]       =  { 87.315, 87.315, 87.315};
  crossSections["TTbarPowheg_Semilept"]       =  {364.352,364.352,364.352};
  crossSections["TTbarPowheg_Hadronic"]       =  {380.095,380.095,380.095};
  
  crossSections["TTbarPowheg_Dilepton_CP5up"]		 =  { 87.315, 87.315, 87.315};
  crossSections["TTbarPowheg_Dilepton_CP5down"]	 =  { 87.315, 87.315, 87.315};
  crossSections["TTbarPowheg_Dilepton_hdampup"]	 =  { 87.315, 87.315, 87.315};
  crossSections["TTbarPowheg_Dilepton_hdampdown"]      =  { 87.315, 87.315, 87.315};
  /* crossSections["TTbarPowheg_Dilepton_mtop1695"]       =  { 87.315, 87.315, 87.315}; */
  /* crossSections["TTbarPowheg_Dilepton_mtop1755"]       =  { 87.315, 87.315, 87.315}; */
  crossSections["TTbarPowheg_Dilepton_mtop1715"]       =  { 87.315, 87.315, 87.315};
  crossSections["TTbarPowheg_Dilepton_mtop1735"]       =  { 87.315, 87.315, 87.315};

  crossSections["TTbarPowheg_Semilept_CP5up"]		 =  {364.352,364.352,364.352};
  crossSections["TTbarPowheg_Semilept_CP5down"]	 =  {364.352,364.352,364.352};
  crossSections["TTbarPowheg_Semilept_hdampup"]	 =  {364.352,364.352,364.352};
  crossSections["TTbarPowheg_Semilept_hdampdown"]      =  {364.352,364.352,364.352};
  /* crossSections["TTbarPowheg_Semilept_mtop1695"]       =  {364.352,364.352,364.352}; */
  /* crossSections["TTbarPowheg_Semilept_mtop1755"]       =  {364.352,364.352,364.352}; */
  crossSections["TTbarPowheg_Semilept_mtop1715"]       =  {364.352,364.352,364.352};
  crossSections["TTbarPowheg_Semilept_mtop1735"]       =  {364.352,364.352,364.352};
    
  crossSections["TTbarPowheg_Hadronic_CP5up"]		 =  {380.095,380.095,380.095};
  crossSections["TTbarPowheg_Hadronic_CP5down"]	 =  {380.095,380.095,380.095};
  crossSections["TTbarPowheg_Hadronic_hdampup"]	 =  {380.095,380.095,380.095};
  crossSections["TTbarPowheg_Hadronic_hdampdown"]      =  {380.095,380.095,380.095};
  /* crossSections["TTbarPowheg_Hadronic_mtop1695"]       =  {380.095,380.095,380.095}; */
  /* crossSections["TTbarPowheg_Hadronic_mtop1755"]       =  {380.095,380.095,380.095}; */
  crossSections["TTbarPowheg_Hadronic_mtop1715"]       =  {380.095,380.095,380.095};
  crossSections["TTbarPowheg_Hadronic_mtop1735"]       =  {380.095,380.095,380.095};
  
  /* //UL */
  /* crossSections["ST_s_channel"] = {3.55, 3.55, 3.55}; */
  /* crossSections["ST_t_channel"] = {113.40, 113.40, 113.40}; */
  /* crossSections["ST_tbar_channel"] = {67.93, 67.93, 67.93}; */
  /* crossSections["ST_tW_channel"] = {32.45, 32.45, 32.45}; */
  /* crossSections["ST_tbarW_channel"] = {32.51, 32.51, 32.51}; */
  // MiniAOD
  crossSections["ST_s_channel"]		=  {3.36, 3.36, 3.36}; //// Default setting
  crossSections["ST_t_channel"]		=  {136.02, 136.02, 136.02};
  crossSections["ST_tbar_channel"]		=  { 80.95,  80.95,  80.95};
  crossSections["ST_tW_channel"]		=  { 35.85,  35.85,  35.85};
  crossSections["ST_tbarW_channel"]		=  { 35.85,  35.85,  35.85};

  /* //UL */
  /* crossSections["Wjets"] = {53690.00, 53690.00, 53690.00}; */
  /* crossSections["W1jets"] = {8919.00, 8919.00, 8919.00}; */
  /* crossSections["W2jets"] = {2824.00, 2824.00, 2824.00}; */
  /* crossSections["W3jets"] = {822.70, 822.70, 822.70}; */
  /* crossSections["W4jets"] = {389.00, 389.00, 389.00}; */
  /* //MiniAOD */
  crossSections["Wjets"]			=  {50690., 50690., 50690.};//50380.0;
  crossSections["W1jets"]			=  {9493.0, 9493.0, 9493.0};//9493.0;
  crossSections["W2jets"]			=  {3120.0, 3120.0, 3120.0}; //3120.0;
  crossSections["W3jets"]			=  { 942.3,  942.3,  942.3};//942.3;
  crossSections["W4jets"]			=  { 524.2,  524.2,  524.2};//524.2;

  /* crossSections["DYjetsM10to50"] = {15970.00, 0.0, 0.0}; */
  crossSections["DYjetsM10to50"]	=  {15810.0, 15810.0, 15810.0}; //16290.
  crossSections["DY1jetsM10to50"] = {565.30, 565.30, 565.30};
  crossSections["DY2jetsM10to50"] = {314.80, 314.80, 314.80};
  crossSections["DY3jetsM10to50"] = {76.94, 76.94, 76.94};
  crossSections["DY4jetsM10to50"] = {28.61, 28.61, 28.61};

  /* //UL */
  /* crossSections["DYjetsM50"] = {5361.00, 5361.00, 5361.00}; */
  /* crossSections["DY1jetsM50"] = {927.80, 927.80, 927.80}; */
  /* crossSections["DY2jetsM50"] = {292.70, 292.70, 292.70}; */
  /* crossSections["DY3jetsM50"] = {86.27, 86.27, 86.27}; */
  /* crossSections["DY4jetsM50"] = {40.85, 40.85, 40.85}; */
  // MiniAOD
  crossSections["DYjetsM50"]			=  {4963.0, 4963.0, 4963.0}; // 4957. , 6077.22 (NNLO) so kf = 1.2245 for LO=4963
  crossSections["DY1jetsM50"]			=  {1012.0, 1012.0, 1012.0}; //1003.0
  crossSections["DY2jetsM50"]			=  { 334.7,  334.7,  334.7}; //336.7
  crossSections["DY3jetsM50"]			=  { 102.3,  102.3,  102.3}; //102.9
  crossSections["DY4jetsM50"]			=  { 54.52,  54.52,  54.52}; //54.71
  
  /* //UL */
  /* crossSections["WW"] = {75.59, 75.59, 75.59}; */
  /* crossSections["WZ"] = {27.49, 27.49, 27.49}; */
  /* crossSections["ZZ"] = {12.11, 12.11, 12.11}; */
  // MiniAOD
  crossSections["WW"]				= {118.7, 118.7, 118.7};
  crossSections["WZ"]				= {46.74, 46.74, 46.74};
  crossSections["ZZ"]				= {17.72, 17.72, 17.72};

  //UL
  crossSections["QCD_Pt15to20_Mu"] = {2799000.00, 2799000.00, 2799000.00};
  crossSections["QCD_Pt20to30_Mu"] = {2538000.00, 2538000.00, 2538000.00};
  crossSections["QCD_Pt30to50_Mu"] = {1359000.00, 1359000.00, 1359000.00};
  crossSections["QCD_Pt50to80_Mu"] = {377000.00, 377000.00, 377000.00};
  crossSections["QCD_Pt80to120_Mu"] = {87470.00, 87470.00, 87470.00};
  crossSections["QCD_Pt120to170_Mu"] = {21280.00, 21280.00, 21280.00};
  crossSections["QCD_Pt170to300_Mu"] = {7012.00, 7012.00, 7012.00};
  crossSections["QCD_Pt300to470_Mu"] = {617.20, 617.20, 617.20};
  crossSections["QCD_Pt470to600_Mu"] = {59.20, 59.20, 59.20};
  crossSections["QCD_Pt600to800_Mu"] = {18.20, 18.20, 18.20};
  crossSections["QCD_Pt800to1000_Mu"] = {3.21, 3.21, 3.21};
  crossSections["QCD_Pt1000toInf_Mu"] = {1.09, 1.09, 1.09};

  crossSections["QCD_Pt20to30_Ele"] = {4865000.00, 4865000.00, 4865000.00};
  crossSections["QCD_Pt30to50_Ele"] = {6287000.00, 6287000.00, 6287000.00};
  crossSections["QCD_Pt50to80_Ele"] = {1990000.00, 1990000.00, 1990000.00};
  crossSections["QCD_Pt80to120_Ele"] = {358600.00, 358600.00, 358600.00};
  crossSections["QCD_Pt120to170_Ele"] = {66860.00, 66860.00, 66860.00};
  crossSections["QCD_Pt170to300_Ele"] = {16320.00, 16320.00, 16320.00};
  crossSections["QCD_Pt300toInf_Ele"] = {1088.00, 1088.00, 1088.00};

  /* crossSections["QCD_Pt15to20_Mu"]		= {3819570.0, 3819570.0, 3819570.0}; */
  /* crossSections["QCD_Pt20to30_Mu"]		= {2960198.4   , 2960198.4   , 2960198.4   }; */
  /* crossSections["QCD_Pt30to50_Mu"]		= {1652471.46  , 1652471.46  , 1652471.46  }; */
  /* crossSections["QCD_Pt50to80_Mu"]		= { 437504.1   ,  437504.1   ,  437504.1   }; */
  /* crossSections["QCD_Pt80to120_Mu"]		= { 106033.6648,  106033.6648,  106033.6648}; */
  /* crossSections["QCD_Pt120to170_Mu"]		= {  25190.5151,   25190.5151,   25190.5151}; */
  /* crossSections["QCD_Pt170to300_Mu"]		= {   8654.4932,    8654.4932,    8654.4932}; */
  /* crossSections["QCD_Pt300to470_Mu"]		= {    797.3527,     797.3527,     797.3527}; */
  /* crossSections["QCD_Pt470to600_Mu"]		= {     79.0255,      79.0255,      79.0255}; */
  /* crossSections["QCD_Pt600to800_Mu"]		= {     25.0951,      25.0951,      25.0951}; */
  /* crossSections["QCD_Pt800to1000_Mu"]		= {      4.7074,       4.7074,       4.7074}; */
  /* crossSections["QCD_Pt1000toInf_Mu"]		= {      1.6213,       1.6213,       1.6213}; */

  /* crossSections["QCD_Pt20to30_Ele"]		= {5352960., 5352960., 5352960.}; */
  /* crossSections["QCD_Pt30to50_Ele"]		= {9928000., 9928000., 9928000.}; */
  /* crossSections["QCD_Pt50to80_Ele"]		= {2890800., 2890800., 2890800.}; */
  /* crossSections["QCD_Pt80to120_Ele"]		= { 350000.,  350000.,  350000.}; */
  /* crossSections["QCD_Pt120to170_Ele"]		= {  62964.,   62964.,   62964.}; */
  /* crossSections["QCD_Pt170to300_Ele"]		= {  18810.,   18810.,   18810.}; */
  /* crossSections["QCD_Pt300toInf_Ele"]		= {   1350.,    1350.,    1350.}; */

  /* crossSections["TTbarPowheg_inclusive"]     	=  {831.76, 831.76, 831.76};  //ttbar NNLO (http://inspirehep.net/search?p=find+eprint+1112.5675) */
  /* crossSections["TTbarPowheg_Dilepton"]       =  { 87.315, 87.315, 87.315}; */
  /* crossSections["TTbarPowheg_Semilept"]       =  {364.352,364.352,364.352}; */
  /* crossSections["TTbarPowheg_Hadronic"]       =  {380.095,380.095,380.095}; */
  /* crossSections["TTbarMadgraph_inclusive"]    =  {831.76, 831.76, 831.76}; */
    
  /* crossSections["TTbarPowheg_Dilepton_CP5up"]		 =  { 87.315, 87.315, 87.315}; */
  /* crossSections["TTbarPowheg_Dilepton_CP5down"]	 =  { 87.315, 87.315, 87.315}; */
  /* crossSections["TTbarPowheg_Dilepton_hdampup"]	 =  { 87.315, 87.315, 87.315}; */
  /* crossSections["TTbarPowheg_Dilepton_hdampdown"]      =  { 87.315, 87.315, 87.315}; */
  /* crossSections["TTbarPowheg_Dilepton_mtop1695"]       =  { 87.315, 87.315, 87.315}; */
  /* crossSections["TTbarPowheg_Dilepton_mtop1755"]       =  { 87.315, 87.315, 87.315}; */

  /* crossSections["TTbarPowheg_Semilept_CP5up"]		 =  {364.352,364.352,364.352}; */
  /* crossSections["TTbarPowheg_Semilept_CP5down"]	 =  {364.352,364.352,364.352}; */
  /* crossSections["TTbarPowheg_Semilept_hdampup"]	 =  {364.352,364.352,364.352}; */
  /* crossSections["TTbarPowheg_Semilept_hdampdown"]      =  {364.352,364.352,364.352}; */
  /* crossSections["TTbarPowheg_Semilept_mtop1695"]       =  {364.352,364.352,364.352}; */
  /* crossSections["TTbarPowheg_Semilept_mtop1755"]       =  {364.352,364.352,364.352}; */
    
  /* crossSections["TTbarPowheg_Hadronic_CP5up"]		 =  {380.095,380.095,380.095}; */
  /* crossSections["TTbarPowheg_Hadronic_CP5down"]	 =  {380.095,380.095,380.095}; */
  /* crossSections["TTbarPowheg_Hadronic_hdampup"]	 =  {380.095,380.095,380.095}; */
  /* crossSections["TTbarPowheg_Hadronic_hdampdown"]      =  {380.095,380.095,380.095}; */
  /* crossSections["TTbarPowheg_Hadronic_mtop1695"]       =  {380.095,380.095,380.095}; */
  /* crossSections["TTbarPowheg_Hadronic_mtop1755"]       =  {380.095,380.095,380.095}; */
    
  /* // Obtained using CMSDAS and CMS_XSDB */
  /* //crossSections["TTbarPowheg_Dilepton"]       =  { 88.29, 88.29, 88.29}; //687.1 */
  /* //crossSections["TTbarPowheg_Semilept"]       =  {365.34, 365.34, 365.34}; //687.1 */
  /* //crossSections["TTbarPowheg_Hadronic"]       =  {377.96, 377.96, 377.96}; //687.1 */
    
    
  /* // // Default setting */
  /* /\* crossSections["HplusM080"]               =  {6.77, 6.77, 6.77};  *\/ */
  /* // //MiniAOD setting */
  /* crossSections["HplusM080"]                  =  {21.55, 21.55, 21.55}; //831.76*0.21322.39*scaleSig;  */
  /* //with scaleSig = 0.12155 = 2*0.065*(1-0.065), where 6.5% is the observed limit for 90 GeV at 8 TeV */
  /* crossSections["HplusM090"]                  =  {21.55, 21.55, 21.55};  */
  /* crossSections["HplusM100"]                  =  {21.55, 21.55, 21.55};  */
  /* crossSections["HplusM110"]                  =  {21.55, 21.55, 21.55};  */
  /* crossSections["HplusM120"]                  =  {21.55, 21.55, 21.55};  */
  /* crossSections["HplusM130"]                  =  {21.55, 21.55, 21.55};  */
  /* crossSections["HplusM140"]                  =  {21.55, 21.55, 21.55};  */
  /* crossSections["HplusM150"]                  =  {21.55, 21.55, 21.55};  */
  /* crossSections["HplusM155"]                  =  {21.55, 21.55, 21.55};  */
  /* crossSections["HplusM160"]                  =  {21.55, 21.55, 21.55};  */
    

  /* // Obtained from MiniAOD except s_channel using the updated https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns#Single_top */
  /* crossSections["ST_s_channel"]		=  {3.36, 3.36, 3.36}; //// Default setting */
  /* /\* crossSections["ST_s_channel"]		=  { 10.32,  10.32,  10.32}; *\/ */
  /* crossSections["ST_t_channel"]		=  {136.02, 136.02, 136.02}; */
  /* crossSections["ST_tbar_channel"]		=  { 80.95,  80.95,  80.95}; */
  /* crossSections["ST_tW_channel"]		=  { 35.85,  35.85,  35.85}; */
  /* crossSections["ST_tbarW_channel"]		=  { 35.85,  35.85,  35.85}; */
    
  /* // Obtained using CMSDAS and CMS_XSDB */
  /* /\* crossSections["ST_s_channel"]		=  { 3.74,  3.74,  3.74};  *\/ */
  /* /\* crossSections["ST_t_channel"]		=  {113.3, 113.3, 113.3}; *\/ */
  /* /\* crossSections["ST_tbar_channel"]		=  {67.91, 67.91, 67.91}; *\/ */
  /* /\* crossSections["ST_tW_channel"]		=  {34.91, 34.91, 34.91}; *\/ */
  /* /\* crossSections["ST_tbarW_channel"]		=  {34.97, 34.97, 34.97}; *\/ */
        
  /* // // Default */
  /* /\* crossSections["DYjetsM50"]		=  {6077.22, 6077.22, 6077.22}; //https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns *\/ */
  /* /\* crossSections["DYjetsM50_ext1"]		=  {6077.22, 6077.22, 6077.22}; //https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns *\/ */
  /* /\* crossSections["DYjetsM50_ext2"]		=  {6077.22, 6077.22, 6077.22}; //https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns *\/ */
  /* /\* crossSections["DYjetsM10to50"]		=  {18610., 18610., 18610.}; //https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns *\/ */
  /* /\* crossSections["DYjetsM10to50_ext1"]	=  {18610., 18610., 18610.}; //https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns *\/ */

  /* // Obtained using CMSDAS and CMS_XSDB */
  /* crossSections["DYjetsM10to50"]	=  {15810.0, 15810.0, 15810.0}; //16290. */
  /* crossSections["DY1jetsM10to50"]	=  {  565.8,   565.8,   565.8}; //1003.0  */
  /* crossSections["DY2jetsM10to50"]	=  {  314.7,   314.7,   314.7}; //336.7  */
  /* crossSections["DY3jetsM10to50"]	=  {  77.15,   77.15,   77.15}; //102.9  */
  /* crossSections["DY4jetsM10to50"]	=  {  28.47,   28.47,   28.47}; //54.71  */
    
  /* crossSections["DYjetsM50"]			=  {5343.0, 5343.0, 5343.0}; // 4957. , 6077.22 (NNLO) so kf = 1.2245 for LO=4963 */

  /* crossSections["DY1jetsM50"]			=  {1012.0, 1012.0, 1012.0}; //1003.0  */
  /* crossSections["DY2jetsM50"]			=  { 334.7,  334.7,  334.7}; //336.7  */
  /* crossSections["DY3jetsM50"]			=  { 102.3,  102.3,  102.3}; //102.9  */
  /* crossSections["DY4jetsM50"]			=  { 54.52,  54.52,  54.52}; //54.71  */

    
  /* // Unused crossSections["WjetsInclusive"]   = {61526.7, 61526.7, 61526.7}; //https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns#W_jets */
  /* // // Default */
  /* /\* crossSections["W1jets"]			=  {11775.9345, 11775.9345, 11775.9345};//9493.0; *\/ */
  /* /\* crossSections["W2jets"]			=  { 3839.4345,  3839.4345,  3839.4345}; //3120.0; *\/ */
  /* /\* crossSections["W2jets_ext1"]		=  { 3839.4345,  3839.4345,  3839.4345}; //3120.0; *\/ */
  /* /\* crossSections["W3jets"]			=  { 1165.8108,  1165.8108,  1165.8108};//942.3; *\/ */
  /* /\* crossSections["W3jets_ext1"]		=  { 1165.8108,  1165.8108,  1165.8108};//942.3; *\/ */
  /* /\* crossSections["W4jets"]			=  {  592.9176,   592.9176,   592.9176};//524.2; *\/ */
  /* /\* crossSections["W4jets_ext1"]		=  {  592.9176,   592.9176,   592.9176};//524.2; *\/ */
  /* /\* crossSections["W4jets_ext2"]		=  {  592.9176,   592.9176,   592.9176};//524.2; *\/ */
  /* //MiniAOD */
  /* crossSections["W1jets"]			=  {9493.0, 9493.0, 9493.0};//9493.0; */
  /* crossSections["W2jets"]			=  {3120.0, 3120.0, 3120.0}; //3120.0; */
  /* crossSections["W2jets_ext1"]		=  {3120.0, 3120.0, 3120.0}; //3120.0; */
  /* crossSections["W3jets"]			=  { 942.3,  942.3,  942.3};//942.3; */
  /* crossSections["W3jets_ext1"]		=  { 942.3,  942.3,  942.3};//942.3; */
  /* crossSections["W4jets"]			=  { 524.2,  524.2,  524.2};//524.2; */
  /* crossSections["W4jets_ext1"]		=  { 524.2,  524.2,  524.2};//524.2; */
  /* crossSections["W4jets_ext2"]		=  { 524.2,  524.2,  524.2};//524.2; */
  /* crossSections["Wjets"]			=  {50690., 50690., 50690.};//50380.0; */
  /* crossSections["Wjets_ext1"]			=  {50690., 50690., 50690.};//524.2; */
  /* crossSections["Wjets_ext2"]			=  {50690., 50690., 50690.};//524.2; */
  /* crossSections["WJetsToQQ"]			=  {95.14, 95.14, 95.14};  //Added */

  /* /\* // Obtained using CMSDAS and CMS_XSDB *\/ */
  /* /\* crossSections["W1jets"]			=  {9625.0, 9625.0, 9625.0}; //9578.0 *\/ */
  /* /\* crossSections["W2jets"]			=  {3161.0, 3161.0, 3161.0}; //3154.0; *\/ */
  /* /\* crossSections["W2jets_ext1"]		=  {3161.0, 3161.0, 3161.0};  *\/ */
  /* /\* crossSections["W3jets"]			=  { 958.0,  958.0,  958.0}; // *\/ */
  /* /\* crossSections["W3jets_ext1"]		=  { 958.0,  958.0,  958.0};//942.3; *\/ */
  /* /\* crossSections["W4jets"]			=  { 494.6,  494.6,  494.6};//495.7; *\/ */
  /* /\* crossSections["W4jets_ext1"]		=  { 494.6,  494.6,  494.6};//524.2; *\/ */
  /* /\* crossSections["W4jets_ext2"]		=  { 494.6,  494.6,  494.6};//524.2; *\/ */
  /* /\* crossSections["Wjets"]			=  {50260., 50260., 50260.};//50380.0; *\/ */
  /* /\* crossSections["Wjets_ext1"]			=  {50260., 50260., 50260.};//524.2; *\/ */
  /* /\* crossSections["Wjets_ext2"]			=  {50260., 50260., 50260.};//524.2; *\/ */
  /* /\* crossSections["WJetsToQQ"]			=  {95.14, 95.14, 95.14};  //Added *\/ */

  /* /\* crossSections["DYjetsM10to50"]		= {18610.0, 18610.0, 18610.0};  *\/ */
  /* /\* crossSections["DYjetsM50"]		= {6077.22, 6077.22, 6077.22}; *\/ */

  /* // // Default */
  /* /\* crossSections["WW"]				= {75.8 ,75.8 ,75.8 }; *\/ */
  /* /\* crossSections["WW_ext1"]			= {75.8 ,75.8 ,75.8 }; *\/ */
  /* /\* crossSections["WZ"]				= {27.6 ,27.6 ,27.6 }; *\/ */
  /* /\* crossSections["WZ_ext1"]			= {27.6 ,27.6 ,27.6 }; *\/ */
  /* /\* crossSections["ZZ"]				= {12.14,12.14,12.14}; *\/ */
  /* /\* crossSections["ZZ_ext1"]			= {12.14,12.14,12.14}; *\/ */
  /* // MiniAOD */
  /* crossSections["WW"]				= {118.7, 118.7, 118.7}; */
  /* crossSections["WW_ext1"]			= {118.7, 118.7, 118.7}; */
  /* crossSections["WZ"]				= {46.74, 46.74, 46.74}; */
  /* crossSections["WZ_ext1"]			= {46.74, 46.74, 46.74}; */
  /* crossSections["ZZ"]				= {17.72, 17.72, 17.72}; */
  /* crossSections["ZZ_ext1"]			= {17.72, 17.72, 17.72}; */
  /* // Obtained using CMSDAS and CMS_XSDB */
  /* /\* crossSections["WW"]				= { 64.3,  64.3,  64.3}; // 64.28 *\/ */
  /* /\* crossSections["WW_ext1"]			= { 64.3,  64.3,  64.3}; *\/ */
  /* /\* crossSections["WZ"]				= {23.43, 23.43, 23.43}; // 23.48 *\/ */
  /* /\* crossSections["WZ_ext1"]			= {23.43, 23.43, 23.43}; *\/ */
  /* /\* crossSections["ZZ"]				= {10.16, 10.16, 10.16}; *\/ */
  /* /\* crossSections["ZZ_ext1"]			= {10.16, 10.16, 10.16}; *\/ */
    
    
  /* //Product fo XS and filter eff from table at: */
  /* //https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns#QCD */
  /* crossSections["QCD_Pt15to20_Mu"]		= {3819570.0, 3819570.0, 3819570.0}; */
  /* crossSections["QCD_Pt20to30_Mu"]		= {2960198.4   , 2960198.4   , 2960198.4   }; */
  /* crossSections["QCD_Pt30to50_Mu"]		= {1652471.46  , 1652471.46  , 1652471.46  }; */
  /* crossSections["QCD_Pt50to80_Mu"]		= { 437504.1   ,  437504.1   ,  437504.1   }; */
  /* crossSections["QCD_Pt80to120_Mu"]		= { 106033.6648,  106033.6648,  106033.6648}; */
  /* crossSections["QCD_Pt80to120_Mu_ext1"]	= { 106033.6648,  106033.6648,  106033.6648}; */
  /* crossSections["QCD_Pt120to170_Mu"]		= {  25190.5151,   25190.5151,   25190.5151}; */
  /* crossSections["QCD_Pt120to170_Mu_ext1"]	= {  25190.5151,   25190.5151,   25190.5151}; */
  /* crossSections["QCD_Pt170to300_Mu"]		= {   8654.4932,    8654.4932,    8654.4932}; */
  /* crossSections["QCD_Pt170to300_Mu_ext1"]	= {   8654.4932,    8654.4932,    8654.4932}; */
  /* crossSections["QCD_Pt300to470_Mu"]		= {    797.3527,     797.3527,     797.3527}; */
  /* crossSections["QCD_Pt300to470_Mu_ext1"]	= {    797.3527,     797.3527,     797.3527}; */
  /* crossSections["QCD_Pt300to470_Mu_ext2"]	= {    797.3527,     797.3527,     797.3527}; */
  /* crossSections["QCD_Pt300to470_Mu_ext3"]	= {    797.3527,     797.3527,     797.3527}; */
  /* crossSections["QCD_Pt470to600_Mu"]		= {     79.0255,      79.0255,      79.0255}; */
  /* crossSections["QCD_Pt470to600_Mu_ext1"]	= {     79.0255,      79.0255,      79.0255}; */
  /* crossSections["QCD_Pt470to600_Mu_ext2"]	= {     79.0255,      79.0255,      79.0255}; */
  /* crossSections["QCD_Pt600to800_Mu"]		= {     25.0951,      25.0951,      25.0951}; */
  /* crossSections["QCD_Pt600to800_Mu_ext1"]	= {     25.0951,      25.0951,      25.0951}; */
  /* crossSections["QCD_Pt800to1000_Mu"]		= {      4.7074,       4.7074,       4.7074}; */
  /* crossSections["QCD_Pt800to1000_Mu_ext1"]	= {      4.7074,       4.7074,       4.7074}; */
  /* crossSections["QCD_Pt800to1000_Mu_ext2"]	= {      4.7074,       4.7074,       4.7074}; */
  /* crossSections["QCD_Pt1000toInf_Mu"]		= {      1.6213,       1.6213,       1.6213}; */
  /* crossSections["QCD_Pt1000toInf_Mu_ext1"]	= {      1.6213,       1.6213,       1.6213}; */

  /* crossSections["QCD_Pt20to30_Ele"]		= {5352960., 5352960., 5352960.}; */
  /* crossSections["QCD_Pt30to50_Ele"]		= {9928000., 9928000., 9928000.}; */
  /* crossSections["QCD_Pt30to50_Ele_ext1"]	= {9928000., 9928000., 9928000.}; */
  /* crossSections["QCD_Pt50to80_Ele"]		= {2890800., 2890800., 2890800.}; */
  /* crossSections["QCD_Pt50to80_Ele_ext1"]	= {2890800., 2890800., 2890800.}; */
  /* crossSections["QCD_Pt80to120_Ele"]		= { 350000.,  350000.,  350000.}; */
  /* crossSections["QCD_Pt80to120_Ele_ext1"]	= { 350000.,  350000.,  350000.}; */
  /* crossSections["QCD_Pt120to170_Ele"]		= {  62964.,   62964.,   62964.}; */
  /* crossSections["QCD_Pt120to170_Ele_ext1"]	= {  62964.,   62964.,   62964.}; */
  /* crossSections["QCD_Pt170to300_Ele"]		= {  18810.,   18810.,   18810.}; */
  /* crossSections["QCD_Pt300toInf_Ele"]		= {   1350.,    1350.,    1350.}; */
    
  return;
}

double getEvtWeight(string sampleType, int year, double luminosity, double nEvents_MC, float& xss){
    
    double evtWeight = -1.;

    if( sampleType.substr(0,4)=="Data") {evtWeight = 1.;}
    else if( sampleType=="Test") {evtWeight = 1.;}
    else if( sampleType=="TestAll") {evtWeight = 1.;}
    else if( sampleType=="TestFull") {evtWeight = 1.;}
    else {
		initCrossSections();
	if (crossSections.find(sampleType) != crossSections.end()) {
	    int index = year - 2016;
	    evtWeight = crossSections[sampleType][index] * luminosity / nEvents_MC;
	    xss = crossSections[sampleType][index];
	}
	else {
	    cout << "-------------------------------------------------" << endl;
	    cout << "-------------------------------------------------" << endl;
	    cout << "-- Unable to find event weight for this sample --" << endl;
	    cout << "-- Sample will be saved with a weight of -1    --" << endl;
	    cout << "-------------------------------------------------" << endl;
	    cout << "-------------------------------------------------" << endl;
	}
    }
    cout << "Using event weight " << evtWeight << endl;
    cout << "XS = " << evtWeight/luminosity*nEvents_MC << endl;
    cout << "lumi = " << luminosity << endl;
    cout << "nEvents_MC = " << nEvents_MC << endl;
    
    return evtWeight;
}

double getEvtWeight(string sampleType, int year, double luminosity){
    
    double evtWeight = -1.;

    if( sampleType.substr(0,4)=="Data") {evtWeight = 1.;}
    else if( sampleType=="Test") {evtWeight = 1.;}
    else if( sampleType=="TestAll") {evtWeight = 1.;}
    else if( sampleType=="TestFull") {evtWeight = 1.;}
    else {
      //	initCrossSections();
      if (crossSections.find(sampleType) != crossSections.end()) {
	int index = year - 2016;
	evtWeight = crossSections[sampleType][index] * luminosity / numberOfEvents[sampleType][index];
	//xss = crossSections[sampleType][index];
	cout << "total events " << numberOfEvents[sampleType][index] << endl;
      }
	else {
	    cout << "-------------------------------------------------" << endl;
	    cout << "-------------------------------------------------" << endl;
	    cout << "-- Unable to find event weight for this sample --" << endl;
	    cout << "-- Sample will be saved with a weight of -1    --" << endl;
	    cout << "-------------------------------------------------" << endl;
	    cout << "-------------------------------------------------" << endl;
	}
    }
    cout << "Using event weight " << evtWeight << endl;
    /* cout << "XS = " << evtWeight/luminosity*nEvents_MC << endl; */
    cout << "lumi = " << luminosity << endl;
    /* cout << "nEvents_MC = " << nEvents_MC << endl; */
    
    return evtWeight;
}

