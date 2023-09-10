/**********************************************************************
 Created on : 16/07/2022
 Purpose    : Prepare the histograms for analysis
 Author     : Indranil Das, Visiting Fellow
 Email      : indranil.das@cern.ch | indra.ehep@gmail.com
**********************************************************************/
#if !defined(__CINT__) || defined(__MAKECINT__)

#include <TROOT.h>
#include <TChain.h>
#include <TEntryList.h>
#include <TFile.h>
//#include <TProofOutputFile.h>
#include <TSelector.h>
#include <vector>

#include "TH2.h"
#include "TF1.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TPaveStats.h"
#include "TMath.h"
//#include "TProof.h"

#include "TParticlePDG.h"
#include "TDatabasePDG.h"

#include "TLorentzVector.h"
#include "TVector3.h"

#include <fstream>

//////////////////////
#include <fstream>
#include <string>
#include <cstring>

//#include "KinAna.h"
#include "TH2.h"
#include "TF1.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TPaveStats.h"
#include "TMath.h"
#include "TProof.h"
#include "TObjString.h"
#include "TParticlePDG.h"
#include "TDatabasePDG.h"
//////////////////////

#include <TROOT.h>
#include <TTree.h>
#include <TChain.h>
#include <TEntryList.h>
#include <TFile.h>
#include <TProofOutputFile.h>
#include <TSelector.h>
#include <TGraphAsymmErrors.h>
#include <TH2.h>
#include <TProfile.h>
#include <TParticlePDG.h>
#include <TDatabasePDG.h>
#include <TRandom3.h>

#include <vector>
#include <iostream>
#include <map>
#include <algorithm>
#include <ctime>
#include <iomanip>
#include <cmath>
#include <stdexcept>

#include "TMath.h"
#include "TLorentzVector.h"

/////////////////////
using namespace std;

#endif

class  TH1F;
class  TH1D;
class  TH2D;
class  TH2F;


class KinAna : public TSelector {
public :
   
  //File operation pointers
  ////////////////////////////////////////////////////////
  TFile            *fFile[3];
  TDirectory       **fFileDir;
  TDirectory       **fSelColDir;
  TProofOutputFile *fProofFile[3]; // For optimized merging of the ntuple


  /* //Declaration of leaves types */
  /* //////////////////////////////////////////////////////// */
  Long64_t        fProcessed;//!
  TTree          *fChain;//!    //pointer to the analyzed TTree or TChain
  bool           IsDebug;
  int            nCTag;

  ///////////////////////////////////////////////////////
  // Object values
  ///////////////////////////////////////////////////////
  Double_t  chi2;
  Float_t   jetChadPt;
  Float_t   jetChadEta;
  Float_t   jetChadPhi;
  Float_t   jetChadEn;
  Float_t   jetShadPt;
  Float_t   jetShadEta;
  Float_t   jetShadPhi;
  Float_t   jetShadEn;
  Float_t   metPx;
  Float_t   metPy;
  Float_t   metPz;
  Float_t   lepPt;
  Float_t   lepEta;
  Float_t   lepPhi;
  Float_t   lepEn;
  Float_t   jetBhadPt;
  Float_t   jetBhadEta;
  Float_t   jetBhadPhi;
  Float_t   jetBhadEn;
  Float_t   jetBlepPt;
  Float_t   jetBlepEta;
  Float_t   jetBlepPhi;
  Float_t   jetBlepEn;
  Int_t     nJet;
  
  TLorentzVector leptonAF, neutrinoAF, bjlepAF, bjhadAF, cjhadAF, sjhadAF;
  ///////////////////////////////////////////////////////
  // Type of KF Event
  ///////////////////////////////////////////////////////
  Bool_t singleMu;
  Bool_t singleEle;
  
  Bool_t muonIsoCut;  
  Bool_t muonNonIsoCut;
  Bool_t eleIsoCut;
  Bool_t eleNonIsoCut;
  
  Bool_t isLowMET;
  
  Bool_t hasKFMu;
  Bool_t hasKFEle;
  
  Bool_t isKFValid;
  Bool_t isCTagged;

  ///////////////////////////////////////////////////////
  // Weight/SF
  ///////////////////////////////////////////////////////
  Double_t weight, mjjKF;
  Double_t wt_before, wt_after, wt_ratio;
  
  Double_t _sampleWeight;
  
  Double_t _PUWeight;
  Double_t _PUWeight_Up;
  Double_t _PUWeight_Do;
  
  Double_t _prefireWeight;
  Double_t _prefireWeight_Up;
  Double_t _prefireWeight_Do;

  Double_t _muEffWeight;
  Double_t _muEffWeight_Up;
  Double_t _muEffWeight_Do;
  
  Double_t _eleEffWeight;
  Double_t _eleEffWeight_Up;
  Double_t _eleEffWeight_Do;
  
  Double_t _PUJetIDWeight;
  Double_t _PUJetIDWeight_Up;
  Double_t _PUJetIDWeight_Do;

  // CShapeCalib EOY
  Double_t _bcTagWeight;
  Double_t _bcTagWeight_stat_Up, _bcTagWeight_stat_Do, _bcTagWeight_pu_Up, _bcTagWeight_pu_Do; 
  Double_t _bcTagWeight_eleid_Up, _bcTagWeight_eleid_Do, _bcTagWeight_muid_Up, _bcTagWeight_muid_Do; 
  Double_t _bcTagWeight_lhemuf_Up, _bcTagWeight_lhemuf_Do, _bcTagWeight_lhemur_Up, _bcTagWeight_lhemur_Do; 
  Double_t _bcTagWeight_isr_Up, _bcTagWeight_isr_Do, _bcTagWeight_fsr_Up, _bcTagWeight_fsr_Do; 
  Double_t _bcTagWeight_xdy_Up, _bcTagWeight_xdy_Do, _bcTagWeight_xst_Up, _bcTagWeight_xst_Do; 
  Double_t _bcTagWeight_xwj_Up, _bcTagWeight_xwj_Do, _bcTagWeight_xtt_Up,  _bcTagWeight_xtt_Do; 
  Double_t _bcTagWeight_jes_Up, _bcTagWeight_jes_Do, _bcTagWeight_jer_Up, _bcTagWeight_jer_Do; 
  Double_t _bcTagWeight_bfrag_Up, _bcTagWeight_bfrag_Do; 
  
   /* // CShapeCalib UL */
   /* Double_t _bcTagWeight_stat_Up, _bcTagWeight_stat_Do, _bcTagWeight_pu_Up, _bcTagWeight_pu_Do;  */
   /* Double_t _bcTagWeight_intp_Up, _bcTagWeight_intp_Do, _bcTagWeight_extp_Up, _bcTagWeight_extp_Do;     */
   /* Double_t _bcTagWeight_lhemuf_Up, _bcTagWeight_lhemuf_Do, _bcTagWeight_lhemur_Up, _bcTagWeight_lhemur_Do;  */
   /* Double_t _bcTagWeight_isr_Up, _bcTagWeight_isr_Do, _bcTagWeight_fsr_Up, _bcTagWeight_fsr_Do;  */
   /* Double_t _bcTagWeight_xdyb_Up, _bcTagWeight_xdyb_Do, _bcTagWeight_xdyc_Up, _bcTagWeight_xdyc_Do;  */
   /* Double_t _bcTagWeight_xwjc_Up, _bcTagWeight_xwjc_Do;  */
   /* Double_t _bcTagWeight_jes_Up, _bcTagWeight_jes_Do, _bcTagWeight_jer_Up, _bcTagWeight_jer_Do;  */

   //Theory weights
  Float_t _q2weight_Up, _q2weight_Do;
  Float_t _pdfweight_Up, _pdfweight_Do, _pdfuncer;
  Float_t _ISRweight_Up, _ISRweight_Do;
  Float_t _FSRweight_Up, _FSRweight_Do;
  

  ///////////////////////////////////////////////////////
  // BCDisc and related values
  ///////////////////////////////////////////////////////
  Int_t count_cJetsIncL, count_cJetsIncM, count_cJetsIncT;
  Double_t cjhadCvsBdisc, sjhadCvsBdisc ;
  Double_t cjhadCvsLdisc, sjhadCvsLdisc ;

  Bool_t useDeepCSVbTag;
  Float_t btag_cut_DeepCSVa, btag_cut_DeepCSVb, btag_cut_DeepCSV; //DeepCSV
  Float_t btag_cuta, btag_cutb, btag_cut; //DeepJet
  Float_t ctag_CvsL_L_cuta, ctag_CvsB_L_cuta, ctag_CvsL_M_cuta, ctag_CvsB_M_cuta, ctag_CvsL_T_cuta, ctag_CvsB_T_cuta;
  Float_t ctag_CvsL_L_cutb, ctag_CvsB_L_cutb, ctag_CvsL_M_cutb, ctag_CvsB_M_cutb, ctag_CvsL_T_cutb, ctag_CvsB_T_cutb;
  Float_t ctag_CvsL_L_cut, ctag_CvsB_L_cut, ctag_CvsL_M_cut, ctag_CvsB_M_cut, ctag_CvsL_T_cut, ctag_CvsB_T_cut; 


   ////////////////////////////////////////////////////////
   //Assorted
   TString fSample;
   TString fFileName;
   TString fSampleDir;
   TString fSampleType;
    TString fMode;
   Int_t fYear;
   Int_t fIndex;
   Int_t fTotal;
   bool isData ;
   TString fBasePath ;
   TString fSyst ;
   vector<TString> fSystList;
   TString fRefFile, fRefPath;
   TFile *fRefF;
   Bool_t isPreVFP, isPostVFP;
   ////////////////////////////////////////////////////////

   ////////////////////////////////////////////////////////
   //Systematics
   enum SystType {kBase,
   		  kPUDown, kPUUp, kMuEffDown, kMuEffUp, kEleEffDown, kEleEffUp,
   		  kJECUp, kJECDown, kJERUp, kJERDown, kBTagbDown, kBTagbUp,
   		  kBTaglDown, kBTaglUp, kPdfDown, kPdfUp, kQ2Down, kQ2Up,
   		  kFsrDown, kFsrUp, kIsrDown, kIsrUp, kPreFireUp, kPreFireDown,
		  kIso20, kMETUp, kMETDown,
		  kCP5Up, kCP5Down, khDampUp, khDampDown, kmTopUp, kmTopDown
   };
   enum SlType { kSlEle, kSlMu, kSlTau, kSlcs, kSlud, kSlus,  kSldc};
   

   int puvar012_g ;		// 0:down, 1:norm, 2:up
   int mueffvar012_g ;		// 0:down, 1:norm, 2:up
   int eleeffvar012_g ;		// 0:down, 1:norm, 2:up
   int jecvar012_g ;		// 0:down, 1:norm, 2:up
   int jervar012_g ;		// 0:down, 1:norm, 2:up
   int btagbvar012_g ;		// 0:down, 1:norm, 2:up
   int btaglvar012_g ;		// 0:down, 1:norm, 2:up
   int pdfvar012_g ;		// 0:down, 1:norm, 2:up
   int q2var012_g ;		// 0:down, 1:norm, 2:up
   int fsrvar012_g ;		// 0:down, 1:norm, 2:up
   int isrvar012_g ;		// 0:down, 1:norm, 2:up
   int prefirevar012_g ;       	// 0:down, 1:norm, 2:up
   /* int musmear012_g ;	// 0:down, 1:norm, 2: up */
   /* int elesmear012_g ;	// 0:down, 1:norm, 2: up */
   SystType systType;
   SlType slType;

   // input files
   int nFiles;
   char **fileNames = 0x0;
   
  string PUJetIDSystType ;
  string btagSystType ;
  string ctagSystType;
  string bctagSystType ;
  
   ////////////////////////////////////////////////////////
   // Histogram for checking
   int fNSyst ;
   int fNDDReg ; 
   int fNBCFHists ;
   int fNCFHists ; 
   TH1D           **hCutFlow;//
   int fNBWtHists ; 
   int fNWtHists;
   TH1D           **histWt;//
   int fNBObHists ; 
   int fNObHists ;
   TH1D           **histObs;//
   int fNBSelCols;
   int fNBSelColHists;
   int fNSelColHists;
   int fNBSelColProfiles;
   int fNSelColProfiles;
   TH1D           **hControl;//
   TProfile       **pControl;//
  ////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////
   
   
   KinAna(TTree *tree=0);
   //KinAna();
   
   virtual ~KinAna() ;

   void    Reset();

   int     Version() const {return 1;}
   void    Begin(TTree *tree);
   void    SlaveBegin(TTree *tree);
   void    Init(TTree *tree);
   // void    InitOutBranches();
   // void    InitBjetOutBranches();
   Bool_t  Notify();
   Bool_t  Process(Long64_t entry);
   void    SetOption(const char *option) { fOption = option; }
   void    SetObject(TObject *obj) { fObject = obj; }
   void    SetInputList(TList *input) {fInput = input;}
   TList  *GetOutputList() const { return fOutput; }
   void    SlaveTerminate();
   void    Terminate();

   void    SetRefFile(const char *reffile) { fRefFile = reffile; }
   void    GetArguments();
   void    SelectSyst();
   void    SetTrio();
   // void    Clean(void); //clear vector and arrays while read each event

   Int_t   CreateHistoArrays();
   
   
   // //// Fill the main physics object histograms 
   // bool    FillBTagObs();
   bool    FillKFCFObs();
   bool    FillCTagObs();   

  // /// These are called by above functions for cutflow and physics object filling functions
  bool    FillCFHists(TList *list, string hist_extn, bool isMu, double value, double wt, double wt_nobtagwt);
  bool    FillKFHists(TList *list, string hist_extn, bool isMu, double wt, double wt_nobtagwt);
  bool    FillCTHists(TList *list, string hist_extn, bool isMu, double wt,
		       int count_cJetsIncL, int count_cJetsIncM, int count_cJetsIncT, 
		       bool isIncL, bool isIncM, bool isIncT,
		       double ctagLwt, double ctagMwt, double ctagTwt);
  
   
   // /// Calculate the combine wt
   bool    GetCombinedWt(TString systname, double& combined_muwt, double& combined_muwt_nobtagwt, double& combined_elewt, double& combined_elewt_nobtagwt);
   bool    GetCTagWt(char CType, TString systname, double& ctagwt);
  bool    GetWtRatio(TString systname, TString DDzone, string hist_extn);
   // /// Fill the control histograms
   // bool    FillKinFitControlHists();
   // bool    FillCTagControlHists();
   void  FillWtHists(void);
   bool    ExecSerial(const char* infile);
   
   
   //ClassDef(KinAna,2);

};

//#endif

//_____________________________________________________________________
KinAna::KinAna(TTree * /*tree*/)
{
  // Constructor

   Reset();
}
//_____________________________________________________________________
void KinAna::Reset()
{
   // Reset the data members to theit initial value

   fFileDir		= 0;
   fFile[0]		= 0;
   fProofFile[0]	= 0;
   fFile[1]		= 0;
   fProofFile[1]	= 0;
   fFile[2]		= 0;
   fProofFile[2]	= 0;
   
   fChain		= 0;
   fProcessed		= 0;
   //outputTree           = 0;
   IsDebug              = false;

   fSample		= "";
   fFileName		= "";
   fSampleDir		= "";
   fSampleType		= "";
   fMode		= "";
   fYear		= 2016;
   fBasePath		= "";   
   fSyst		= "";   
   isData		= false;
}
//_____________________________________________________________________
KinAna::~KinAna()
{
  if (fFile[0]) {
    SafeDelete(fFile[0]);
  }
  if (fFile[1]) {
    SafeDelete(fFile[1]);
  }
  if (fFile[2]) {
    SafeDelete(fFile[2]);
  }
}
//_____________________________________________________________________
void KinAna::Init(TTree *tree)
{
  //   Set branch addresses
  
  //tree = event->chain ;
  Info("Init","tree: %p", tree);
  
  if (tree == 0) return;
  
  // //ESetBranchAddressStatus brAddrStatus;
  // Int_t brAddrStatus;
  
  // tree->SetCacheSize(100*1024*1024);
  // tree->SetBranchStatus("*",0);
  
  // tree->SetBranchStatus("PV_ndof",1);
  // tree->SetBranchAddress("PV_ndof", &(event->pvNDOF_));
  
  //   tree->SetBranchStatus("L1PreFiringWeight_Nom",1);
  //   brAddrStatus = tree->SetBranchAddress("L1PreFiringWeight_Nom", &(event->L1PreFiringWeight_Nom_));
  //   if(brAddrStatus == TTree::kMissingBranch || brAddrStatus == TTree::kInternalError){
  //     event->L1PreFiringWeight_Nom_ =  1.0 ;
  //     Info("Init", "Setting event->L1PreFiringWeight_Nom_ =  1.0");
  //   }

  tree->SetCacheSize(100*1024*1024);
  tree->SetBranchStatus("*",0);

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////
  tree->SetBranchStatus("chi2",1);		   tree->SetBranchAddress("chi2", &chi2);
  tree->SetBranchStatus("jetChadPt",1);		   tree->SetBranchAddress("jetChadPt", &jetChadPt);
  tree->SetBranchStatus("jetChadEta",1);	   tree->SetBranchAddress("jetChadEta", &jetChadEta);
  tree->SetBranchStatus("jetChadPhi",1);	   tree->SetBranchAddress("jetChadPhi", &jetChadPhi);
  tree->SetBranchStatus("jetChadEnergy",1);	   tree->SetBranchAddress("jetChadEnergy", &jetChadEn);
  tree->SetBranchStatus("jetShadPt",1);		   tree->SetBranchAddress("jetShadPt", &jetShadPt);
  tree->SetBranchStatus("jetShadEta",1);	   tree->SetBranchAddress("jetShadEta", &jetShadEta);
  tree->SetBranchStatus("jetShadPhi",1);	   tree->SetBranchAddress("jetShadPhi", &jetShadPhi);
  tree->SetBranchStatus("jetShadEnergy",1);	   tree->SetBranchAddress("jetShadEnergy", &jetShadEn);
  tree->SetBranchStatus("metPx",1);		   tree->SetBranchAddress("metPx", &metPx);
  tree->SetBranchStatus("metPy",1);		   tree->SetBranchAddress("metPy", &metPy);
  tree->SetBranchStatus("metPz",1);		   tree->SetBranchAddress("metPz", &metPz);
  tree->SetBranchStatus("lepPt",1);		   tree->SetBranchAddress("lepPt", &lepPt);
  tree->SetBranchStatus("lepEta",1);		   tree->SetBranchAddress("lepEta", &lepEta);
  tree->SetBranchStatus("lepPhi",1);		   tree->SetBranchAddress("lepPhi", &lepPhi);
  tree->SetBranchStatus("lepEnergy",1);		   tree->SetBranchAddress("lepEnergy", &lepEn);
  tree->SetBranchStatus("jetBhadPt",1);		   tree->SetBranchAddress("jetBhadPt", &jetBhadPt);
  tree->SetBranchStatus("jetBhadEta",1);	   tree->SetBranchAddress("jetBhadEta", &jetBhadEta);
  tree->SetBranchStatus("jetBhadPhi",1);	   tree->SetBranchAddress("jetBhadPhi", &jetBhadPhi);
  tree->SetBranchStatus("jetBhadEnergy",1);	   tree->SetBranchAddress("jetBhadEnergy", &jetBhadEn);
  tree->SetBranchStatus("jetBlepPt",1);		   tree->SetBranchAddress("jetBlepPt", &jetBlepPt);
  tree->SetBranchStatus("jetBlepEta",1);	   tree->SetBranchAddress("jetBlepEta", &jetBlepEta);
  tree->SetBranchStatus("jetBlepPhi",1);	   tree->SetBranchAddress("jetBlepPhi", &jetBlepPhi);
  tree->SetBranchStatus("jetBlepEnergy",1);	   tree->SetBranchAddress("jetBlepEnergy", &jetBlepEn);

  tree->SetBranchStatus("nJet",1);		   tree->SetBranchAddress("nJet", &nJet);
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  tree->SetBranchStatus("singleMu",1);		   tree->SetBranchAddress("singleMu", &singleMu);
  tree->SetBranchStatus("singleEle",1);		   tree->SetBranchAddress("singleEle", &singleEle);
  tree->SetBranchStatus("muonIsoCut",1);	   tree->SetBranchAddress("muonIsoCut", &muonIsoCut);
  tree->SetBranchStatus("muonNonIsoCut",1);	   tree->SetBranchAddress("muonNonIsoCut", &muonNonIsoCut);
  tree->SetBranchStatus("eleIsoCut",1);		   tree->SetBranchAddress("eleIsoCut", &eleIsoCut);
  tree->SetBranchStatus("eleNonIsoCut",1);	   tree->SetBranchAddress("eleNonIsoCut", &eleNonIsoCut);
  tree->SetBranchStatus("isLowMET",1);		   tree->SetBranchAddress("isLowMET", &isLowMET);
  tree->SetBranchStatus("hasKFMu",1);		   tree->SetBranchAddress("hasKFMu", &hasKFMu);
  tree->SetBranchStatus("hasKFEle",1);		   tree->SetBranchAddress("hasKFEle", &hasKFEle);  
  tree->SetBranchStatus("isKFValid",1);		   tree->SetBranchAddress("isKFValid", &isKFValid);
  tree->SetBranchStatus("isCTagged",1);		   tree->SetBranchAddress("isCTagged", &isCTagged);

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////


  tree->SetBranchStatus("sampleWeight",1);	   tree->SetBranchAddress("sampleWeight", &_sampleWeight);
  
  tree->SetBranchStatus("PUWeight",1);		   tree->SetBranchAddress("PUWeight", &_PUWeight);
  tree->SetBranchStatus("PUWeight_Up",1);	   tree->SetBranchAddress("PUWeight_Up", &_PUWeight_Up);
  tree->SetBranchStatus("PUWeight_Do",1);	   tree->SetBranchAddress("PUWeight_Do", &_PUWeight_Do);
  
  tree->SetBranchStatus("prefireWeight",1);	   tree->SetBranchAddress("prefireWeight", &_prefireWeight);
  tree->SetBranchStatus("prefireWeight_Up",1);	   tree->SetBranchAddress("prefireWeight_Up", &_prefireWeight_Up);
  tree->SetBranchStatus("prefireWeight_Do",1);	   tree->SetBranchAddress("prefireWeight_Do", &_prefireWeight_Do);

  tree->SetBranchStatus("muEffWeight",1);	   tree->SetBranchAddress("muEffWeight", &_muEffWeight);
  tree->SetBranchStatus("muEffWeight_Up",1);	   tree->SetBranchAddress("muEffWeight_Up", &_muEffWeight_Up);
  tree->SetBranchStatus("muEffWeight_Do",1);	   tree->SetBranchAddress("muEffWeight_Do", &_muEffWeight_Do);
  
  tree->SetBranchStatus("eleEffWeight",1);	   tree->SetBranchAddress("eleEffWeight", &_eleEffWeight);
  tree->SetBranchStatus("eleEffWeight_Up",1);	   tree->SetBranchAddress("eleEffWeight_Up", &_eleEffWeight_Up);
  tree->SetBranchStatus("eleEffWeight_Do",1);	   tree->SetBranchAddress("eleEffWeight_Do", &_eleEffWeight_Do);
  
  tree->SetBranchStatus("puJetIDWeight",1);	   tree->SetBranchAddress("puJetIDWeight", &_PUJetIDWeight);
  tree->SetBranchStatus("puJetIDWeight_Up",1);	   tree->SetBranchAddress("puJetIDWeight_Up", &_PUJetIDWeight_Up);
  tree->SetBranchStatus("puJetIDWeight_Do",1);	   tree->SetBranchAddress("puJetIDWeight_Do", &_PUJetIDWeight_Do);

  // CShapeCalib EOY
  tree->SetBranchStatus("bcTagWeight",1);		   tree->SetBranchAddress("bcTagWeight", &_bcTagWeight); 
  tree->SetBranchStatus("bcTagWeight_stat_Up",1);	   tree->SetBranchAddress("bcTagWeight_stat_Up", &_bcTagWeight_stat_Up); 
  tree->SetBranchStatus("bcTagWeight_stat_Do",1);	   tree->SetBranchAddress("bcTagWeight_stat_Do", &_bcTagWeight_stat_Do);
  tree->SetBranchStatus("bcTagWeight_pu_Up",1);		   tree->SetBranchAddress("bcTagWeight_pu_Up", &_bcTagWeight_pu_Up);
  tree->SetBranchStatus("bcTagWeight_pu_Do",1);		   tree->SetBranchAddress("bcTagWeight_pu_Do", &_bcTagWeight_pu_Do); 
  tree->SetBranchStatus("bcTagWeight_eleid_Up",1);	   tree->SetBranchAddress("bcTagWeight_eleid_Up", &_bcTagWeight_eleid_Up); 
  tree->SetBranchStatus("bcTagWeight_eleid_Do",1);	   tree->SetBranchAddress("bcTagWeight_eleid_Do", &_bcTagWeight_eleid_Do);
  tree->SetBranchStatus("bcTagWeight_muid_Up",1);	   tree->SetBranchAddress("bcTagWeight_muid_Up", &_bcTagWeight_muid_Up);
  tree->SetBranchStatus("bcTagWeight_muid_Do",1);	   tree->SetBranchAddress("bcTagWeight_muid_Do", &_bcTagWeight_muid_Do); 
  tree->SetBranchStatus("bcTagWeight_lhemuf_Up",1);	   tree->SetBranchAddress("bcTagWeight_lhemuf_Up", &_bcTagWeight_lhemuf_Up); 
  tree->SetBranchStatus("bcTagWeight_lhemuf_Do",1);	   tree->SetBranchAddress("bcTagWeight_lhemuf_Do", &_bcTagWeight_lhemuf_Do);
  tree->SetBranchStatus("bcTagWeight_lhemur_Up",1);	   tree->SetBranchAddress("bcTagWeight_lhemur_Up", &_bcTagWeight_lhemur_Up);
  tree->SetBranchStatus("bcTagWeight_lhemur_Do",1);	   tree->SetBranchAddress("bcTagWeight_lhemur_Do", &_bcTagWeight_lhemur_Do); 
  tree->SetBranchStatus("bcTagWeight_isr_Up",1);	   tree->SetBranchAddress("bcTagWeight_isr_Up", &_bcTagWeight_isr_Up); 
  tree->SetBranchStatus("bcTagWeight_isr_Do",1);	   tree->SetBranchAddress("bcTagWeight_isr_Do", &_bcTagWeight_isr_Do);
  tree->SetBranchStatus("bcTagWeight_fsr_Up",1);	   tree->SetBranchAddress("bcTagWeight_fsr_Up", &_bcTagWeight_fsr_Up);
  tree->SetBranchStatus("bcTagWeight_fsr_Do",1);	   tree->SetBranchAddress("bcTagWeight_fsr_Do", &_bcTagWeight_fsr_Do); 
  tree->SetBranchStatus("bcTagWeight_xdy_Up",1);	   tree->SetBranchAddress("bcTagWeight_xdy_Up", &_bcTagWeight_xdy_Up); 
  tree->SetBranchStatus("bcTagWeight_xdy_Do",1);	   tree->SetBranchAddress("bcTagWeight_xdy_Do", &_bcTagWeight_xdy_Do);
  tree->SetBranchStatus("bcTagWeight_xst_Up",1);	   tree->SetBranchAddress("bcTagWeight_xst_Up", &_bcTagWeight_xst_Up);
  tree->SetBranchStatus("bcTagWeight_xst_Do",1);	   tree->SetBranchAddress("bcTagWeight_xst_Do", &_bcTagWeight_xst_Do); 
  tree->SetBranchStatus("bcTagWeight_xwj_Up",1);	   tree->SetBranchAddress("bcTagWeight_xwj_Up", &_bcTagWeight_xwj_Up); 
  tree->SetBranchStatus("bcTagWeight_xwj_Do",1);	   tree->SetBranchAddress("bcTagWeight_xwj_Do", &_bcTagWeight_xwj_Do);
  tree->SetBranchStatus("bcTagWeight_xtt_Up",1);	   tree->SetBranchAddress("bcTagWeight_xtt_Up", &_bcTagWeight_xtt_Up);
  tree->SetBranchStatus("bcTagWeight_xtt_Do",1);	   tree->SetBranchAddress("bcTagWeight_xtt_Do", &_bcTagWeight_xtt_Do); 
  tree->SetBranchStatus("bcTagWeight_jes_Up",1);	   tree->SetBranchAddress("bcTagWeight_jes_Up", &_bcTagWeight_jes_Up); 
  tree->SetBranchStatus("bcTagWeight_jes_Do",1);	   tree->SetBranchAddress("bcTagWeight_jes_Do", &_bcTagWeight_jes_Do);
  tree->SetBranchStatus("bcTagWeight_jer_Up",1);	   tree->SetBranchAddress("bcTagWeight_jer_Up", &_bcTagWeight_jer_Up);
  tree->SetBranchStatus("bcTagWeight_jer_Do",1);	   tree->SetBranchAddress("bcTagWeight_jer_Do", &_bcTagWeight_jer_Do); 
  tree->SetBranchStatus("bcTagWeight_bfrag_Up",1);	   tree->SetBranchAddress("bcTagWeight_bfrag_Up", &_bcTagWeight_bfrag_Up); 
  tree->SetBranchStatus("bcTagWeight_bfrag_Do",1);	   tree->SetBranchAddress("bcTagWeight_bfrag_Do", &_bcTagWeight_bfrag_Do); 
  
   /* // CShapeCalib UL */
   /* tree->SetBranchStatus("bcTagWeight_stat_Up",1);   tree->SetBranchAddress("bcTagWeight_stat_Up", &_bcTagWeight_stat_Up); 
   tree->SetBranchStatus("bcTagWeight_stat_Do",1);   tree->SetBranchAddress("bcTagWeight_stat_Do", &_bcTagWeight_stat_Do);
   tree->SetBranchStatus("bcTagWeight_pu_Up",1);   tree->SetBranchAddress("bcTagWeight_pu_Up", &_bcTagWeight_pu_Up);
    tree->SetBranchStatus("bcTagWeight_pu_Do",1);   tree->SetBranchAddress("bcTagWeight_pu_Do", &_bcTagWeight_pu_Do);  */
   /* tree->SetBranchStatus("bcTagWeight_intp_Up",1);   tree->SetBranchAddress("bcTagWeight_intp_Up", &_bcTagWeight_intp_Up); 
   tree->SetBranchStatus("bcTagWeight_intp_Do",1);   tree->SetBranchAddress("bcTagWeight_intp_Do", &_bcTagWeight_intp_Do);
   tree->SetBranchStatus("bcTagWeight_extp_Up",1);   tree->SetBranchAddress("bcTagWeight_extp_Up", &_bcTagWeight_extp_Up);
    tree->SetBranchStatus("bcTagWeight_extp_Do",1);   tree->SetBranchAddress("bcTagWeight_extp_Do", &_bcTagWeight_extp_Do);     */
   /* tree->SetBranchStatus("bcTagWeight_lhemuf_Up",1);   tree->SetBranchAddress("bcTagWeight_lhemuf_Up", &_bcTagWeight_lhemuf_Up); 
   tree->SetBranchStatus("bcTagWeight_lhemuf_Do",1);   tree->SetBranchAddress("bcTagWeight_lhemuf_Do", &_bcTagWeight_lhemuf_Do);
   tree->SetBranchStatus("bcTagWeight_lhemur_Up",1);   tree->SetBranchAddress("bcTagWeight_lhemur_Up", &_bcTagWeight_lhemur_Up);
    tree->SetBranchStatus("bcTagWeight_lhemur_Do",1);   tree->SetBranchAddress("bcTagWeight_lhemur_Do", &_bcTagWeight_lhemur_Do);  */
   /* tree->SetBranchStatus("bcTagWeight_isr_Up",1);   tree->SetBranchAddress("bcTagWeight_isr_Up", &_bcTagWeight_isr_Up); 
   tree->SetBranchStatus("bcTagWeight_isr_Do",1);   tree->SetBranchAddress("bcTagWeight_isr_Do", &_bcTagWeight_isr_Do);
   tree->SetBranchStatus("bcTagWeight_fsr_Up",1);   tree->SetBranchAddress("bcTagWeight_fsr_Up", &_bcTagWeight_fsr_Up);
    tree->SetBranchStatus("bcTagWeight_fsr_Do",1);   tree->SetBranchAddress("bcTagWeight_fsr_Do", &_bcTagWeight_fsr_Do);  */
   /* tree->SetBranchStatus("bcTagWeight_xdyb_Up",1);   tree->SetBranchAddress("bcTagWeight_xdyb_Up", &_bcTagWeight_xdyb_Up); 
   tree->SetBranchStatus("bcTagWeight_xdyb_Do",1);   tree->SetBranchAddress("bcTagWeight_xdyb_Do", &_bcTagWeight_xdyb_Do);
   tree->SetBranchStatus("bcTagWeight_xdyc_Up",1);   tree->SetBranchAddress("bcTagWeight_xdyc_Up", &_bcTagWeight_xdyc_Up);
    tree->SetBranchStatus("bcTagWeight_xdyc_Do",1);   tree->SetBranchAddress("bcTagWeight_xdyc_Do", &_bcTagWeight_xdyc_Do);  */
   /* tree->SetBranchStatus("bcTagWeight_xwjc_Up",1);   tree->SetBranchAddress("bcTagWeight_xwjc_Up", &_bcTagWeight_xwjc_Up); 
   tree->SetBranchStatus("bcTagWeight_xwjc_Do",1);   tree->SetBranchAddress("bcTagWeight_xwjc_Do", &_bcTagWeight_xwjc_Do);  */
   /* tree->SetBranchStatus("bcTagWeight_jes_Up",1);   tree->SetBranchAddress("bcTagWeight_jes_Up", &_bcTagWeight_jes_Up); 
   tree->SetBranchStatus("bcTagWeight_jes_Do",1);   tree->SetBranchAddress("bcTagWeight_jes_Do", &_bcTagWeight_jes_Do);
   tree->SetBranchStatus("bcTagWeight_jer_Up",1);   tree->SetBranchAddress("bcTagWeight_jer_Up", &_bcTagWeight_jer_Up);
    tree->SetBranchStatus("bcTagWeight_jer_Do",1);   tree->SetBranchAddress("bcTagWeight_jer_Do", &_bcTagWeight_jer_Do);  */

   //Theory weights
  tree->SetBranchStatus("q2weight_Up",1);	   tree->SetBranchAddress("q2weight_Up", &_q2weight_Up);
  tree->SetBranchStatus("q2weight_Do",1);	   tree->SetBranchAddress("q2weight_Do", &_q2weight_Do);
  tree->SetBranchStatus("pdfweight_Up",1);	   tree->SetBranchAddress("pdfweight_Up", &_pdfweight_Up);
  tree->SetBranchStatus("pdfweight_Do",1);	   tree->SetBranchAddress("pdfweight_Do", &_pdfweight_Do);
  tree->SetBranchStatus("ISRweight_Up",1);	   tree->SetBranchAddress("ISRweight_Up", &_ISRweight_Up);
  tree->SetBranchStatus("ISRweight_Do",1);	   tree->SetBranchAddress("ISRweight_Do", &_ISRweight_Do);
  tree->SetBranchStatus("FSRweight_Up",1);	   tree->SetBranchAddress("FSRweight_Up", &_FSRweight_Up);
  tree->SetBranchStatus("FSRweight_Do",1);	   tree->SetBranchAddress("FSRweight_Do", &_FSRweight_Do);
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////

  // tree->SetBranchStatus("count_cJetsIncL",1);	   tree->SetBranchAddress("count_cJetsIncL", &count_cJetsIncL);
  // tree->SetBranchStatus("count_cJetsIncM",1);	   tree->SetBranchAddress("count_cJetsIncM", &count_cJetsIncM);
  // tree->SetBranchStatus("count_cJetsIncT",1);	   tree->SetBranchAddress("count_cJetsIncT", &count_cJetsIncT);
  
  tree->SetBranchStatus("cjhadCvsBdisc",1);	   tree->SetBranchAddress("cjhadCvsBdisc", &cjhadCvsBdisc);
  tree->SetBranchStatus("cjhadCvsLdisc",1);	   tree->SetBranchAddress("cjhadCvsLdisc", &cjhadCvsLdisc);
  tree->SetBranchStatus("sjhadCvsBdisc",1);	   tree->SetBranchAddress("sjhadCvsBdisc", &sjhadCvsBdisc);
  tree->SetBranchStatus("sjhadCvsLdisc",1);	   tree->SetBranchAddress("sjhadCvsLdisc", &sjhadCvsLdisc);
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////

  fChain    = tree;
  tree->GetEntry(0);  //Important to set the events weights via Notify and ScaleLumi metho
  
}


//_____________________________________________________________________
Bool_t KinAna::Notify()
{
  //   called when loading a new file
  //   get branch pointers
  
  Info("Notify","processing fSampleType %s and file: %s",fSampleType.Data(), fChain->GetCurrentFile()->GetName());  
  

  return kTRUE;
}

Int_t KinAna::CreateHistoArrays()
{
  // Create the histogram arrays
  
  fNDDReg = 4;
  ////////////////////////////// Cut flow histograms //////////////////////////////////
  fNBCFHists = 6;//18;
  fNCFHists = fNDDReg*fNBCFHists; // if fNBCFHists = 100, then == 0:99 for Iso HighMET | 100:199 for Iso LowMET | 200:299 nonIso HighMET | 300:399 nonIso LowMET
  int totNHists = fNCFHists*fNSyst;
  hCutFlow = new TH1D*[totNHists];
  ////////////////////////////// Cut flow histograms //////////////////////////////////
  
  ////////////////////////////////// Observables //////////////////////////////////////
  fNBObHists = 52;//132;
  fNObHists = fNDDReg*fNBObHists; // if fNBaseHists = 100, then == 0:99 for Iso HighMET | 100:199 for Iso LowMET | 200:299 nonIso HighMET | 300:399 nonIso LowMET
  totNHists = fNObHists*fNSyst;
  histObs = new TH1D*[totNHists];
  ////////////////////////////////// Observables //////////////////////////////////////
  
  ////////////////////// Weight and other histograms histograms ///////////////////////
  fNBWtHists = 69;
  fNWtHists = fNDDReg*fNBWtHists; // if fNBaseHists = 100, then == 0:99 for Iso HighMET | 100:199 for Iso LowMET | 200:299 nonIso HighMET | 300:399 nonIso LowMET
  totNHists = fNWtHists*fNSyst;
  histWt = new TH1D*[totNHists];
  ///////////////////// Weight and other histograms histograms ////////////////////////
  
  TDirectory *savedir = gDirectory;
  savedir->cd();
  fFile[0]->cd();
  
  //fNHist = fNSyst;
  fFileDir = new TDirectory*[fNSyst*fNDDReg];  
  
  TDirectory *d1 = fFile[0]->mkdir(fSample.Data());
  cout<<"===============Sample : "<<fSample.Data()<<endl;
  d1->cd();
  
  for(int isyst=0;isyst<fNSyst;isyst++){
    
    //if(isData && isyst>0) continue;
    bool isForwarded = false;
    if(isData){
      if(fSystList[isyst]==fSyst) isForwarded = true;
    }else{
      if(fSyst=="base"){
	isForwarded = true;
      }else{
	if(fSystList[isyst]==fSyst) isForwarded = true;
      }
    }
    if(!isForwarded) continue;

    TDirectory *d2 = d1->mkdir(fSystList[isyst].Data());
    d2->cd();
    fFileDir[isyst*fNDDReg + 0] = d2->mkdir("Iso");
    fFileDir[isyst*fNDDReg + 1] = d2->mkdir("LowMET");
    fFileDir[isyst*fNDDReg + 2] = d2->mkdir("NonIso");
    fFileDir[isyst*fNDDReg + 3] = d2->mkdir("NonIsoLowMET");
    
    cout<<"Syst : " << fSystList[isyst].Data()  << ", requested syst : " << fSyst
	// <<", Dir1 name : " << fFileDir[isyst*fNDDReg + 0]->GetName()
	// <<", Dir2 name : " << fFileDir[isyst*fNDDReg + 1]->GetName()
	<< endl;

    //fFileDir[isyst*fNDDReg + 0]->pwd(); //fFileDir[isyst*fNDDReg+0]->GetPath() ;

    ////////////////////////////// Cut flow histograms //////////////////////////////////
    fFileDir[isyst*fNDDReg + 0]->cd();
    //fFileDir[isyst*fNDDReg + 0]->pwd(); cout <<" path " << fFileDir[isyst*fNDDReg+0]->GetPath() << endl;
    int hidx = 0;
    hCutFlow[fNCFHists*isyst + hidx++] = new TH1D("_cutflow_data", "_cutflow_data", 12, 0, 12);
    hCutFlow[fNCFHists*isyst + hidx++] = new TH1D("_cutflowUS_mu", "_cutflowUS_mu", 12, 0, 12);
    hCutFlow[fNCFHists*isyst + hidx++] = new TH1D("_cutflow_mu", "_cutflow_mu", 12, 0, 12);
    hCutFlow[fNCFHists*isyst + hidx++] = new TH1D("_cutflowUS_ele", "_cutflowUS_ele", 12, 0, 12);
    hCutFlow[fNCFHists*isyst + hidx++] = new TH1D("_cutflow_ele", "_cutflow_ele", 12, 0, 12);
    hCutFlow[fNCFHists*isyst + 5] = new TH1D("_cutflow5", "_cutflow5", 12, 0, 12);
    
    // hCutFlow[fNCFHists*isyst + 19] = new TH1D("_cutflow_nofSldc_ele", "_cutflow_nofSldc_ele", 12, 0, 12);
    
    for(int icf=0;icf<fNBCFHists;icf++)
      hCutFlow[fNCFHists*isyst + icf]->SetDirectory(fFileDir[isyst*fNDDReg + 0]);

    fFileDir[isyst*fNDDReg + 1]->cd();
    //fFileDir[isyst*fNDDReg + 1]->pwd(); cout <<" path " << fFileDir[isyst*fNDDReg+1]->GetPath() << endl;
    int minHs = fNBCFHists ;
    for(int ilmet=minHs;ilmet<(minHs+fNBCFHists);ilmet++){
      hCutFlow[fNCFHists*isyst + ilmet] = (TH1D *)hCutFlow[ilmet-minHs]->Clone(Form("%s_lmet",hCutFlow[ilmet-minHs]->GetName()));
      hCutFlow[fNCFHists*isyst + ilmet]->SetTitle(Form("%s_lmet",hCutFlow[ilmet-minHs]->GetTitle()));
      hCutFlow[fNCFHists*isyst + ilmet]->SetDirectory(fFileDir[isyst*fNDDReg + 1]);
    }
    
    fFileDir[isyst*fNDDReg + 2]->cd();
    //fFileDir[isyst*fNDDReg + 2]->pwd(); cout <<" path " << fFileDir[isyst*fNDDReg+2]->GetPath() << endl;
    minHs = 2*fNBCFHists ;
    for(int iniso=minHs;iniso<(minHs+fNBCFHists);iniso++){
      hCutFlow[fNCFHists*isyst + iniso] = (TH1D *)hCutFlow[iniso-minHs]->Clone(Form("%s_noniso",hCutFlow[iniso-minHs]->GetName()));
      hCutFlow[fNCFHists*isyst + iniso]->SetTitle(Form("%s_noniso",hCutFlow[iniso-minHs]->GetTitle()));
      hCutFlow[fNCFHists*isyst + iniso]->SetDirectory(fFileDir[isyst*fNDDReg + 2]);
    }

    fFileDir[isyst*fNDDReg + 3]->cd();
    //fFileDir[isyst*fNDDReg + 3]->pwd(); cout <<" path " << fFileDir[isyst*fNDDReg+3]->GetPath() << endl;
    minHs = 3*fNBCFHists ;
    for(int inisolmet=minHs;inisolmet<(minHs+fNBCFHists);inisolmet++){
      hCutFlow[fNCFHists*isyst + inisolmet] = (TH1D *)hCutFlow[inisolmet-minHs]->Clone(Form("%s_noniso_lmet",hCutFlow[inisolmet-minHs]->GetName()));
      hCutFlow[fNCFHists*isyst + inisolmet]->SetTitle(Form("%s_noniso_lmet",hCutFlow[inisolmet-minHs]->GetTitle()));
      hCutFlow[fNCFHists*isyst + inisolmet]->SetDirectory(fFileDir[isyst*fNDDReg + 3]);
    }
    ////////////////////////////// Cut flow histograms //////////////////////////////////

    ////////////////////////////////// Observables //////////////////////////////////////
    fFileDir[isyst*fNDDReg + 0]->cd();
    //fFileDir[isyst*fNDDReg + 0]->pwd(); cout <<" path " << fFileDir[isyst*fNDDReg+0]->GetPath() << endl;
    hidx = 0;
    histObs[fNObHists*isyst + hidx++] = new TH1D("_kb_pt_mu","_kb_pt_mu",100, 0., 1000.);
    histObs[fNObHists*isyst + hidx++] = new TH1D("_kb_eta_mu","_kb_eta_mu", 30, -3., 3.);
    histObs[fNObHists*isyst + hidx++] = new TH1D("_kb_phi_mu","_kb_phi_mu", 35, -3.5, 3.5);
    histObs[fNObHists*isyst + hidx++] = new TH1D("_kb_pt_ele","_kb_pt_ele",100, 0., 1000.);
    histObs[fNObHists*isyst + hidx++] = new TH1D("_kb_eta_ele","_kb_eta_ele", 30, -3., 3.);
    histObs[fNObHists*isyst + hidx++] = new TH1D("_kb_phi_ele","_kb_phi_ele", 35, -3.5, 3.5);
    histObs[fNObHists*isyst + hidx++] = new TH1D("_kb_pt_mu_jets","_kb_pt_mu_jets",100, 0., 1000.);
    histObs[fNObHists*isyst + hidx++] = new TH1D("_kb_eta_mu_jets","_kb_eta_mu_jets", 30, -3., 3.);
    histObs[fNObHists*isyst + hidx++] = new TH1D("_kb_phi_mu_jets","_kb_phi_mu_jets", 35, -3.5, 3.5);
    histObs[fNObHists*isyst + hidx++] = new TH1D("_kb_pt_ele_jets","_kb_pt_ele_jets",100, 0., 1000.);
    histObs[fNObHists*isyst + hidx++] = new TH1D("_kb_eta_ele_jets","_kb_eta_ele_jets", 30, -3., 3.);
    histObs[fNObHists*isyst + hidx++] = new TH1D("_kb_phi_ele_jets","_kb_phi_ele_jets", 35, -3.5, 3.5);
    histObs[fNObHists*isyst + hidx++] = new TH1D("_kb_pt_mu_met","_kb_pt_mu_met",100, 0., 1000.);
    histObs[fNObHists*isyst + hidx++] = new TH1D("_kb_phi_mu_met","_kb_phi_mu_met", 35, -3.5, 3.5);
    histObs[fNObHists*isyst + hidx++] = new TH1D("_kb_pt_ele_met","_kb_pt_ele_met",100, 0., 1000.);
    histObs[fNObHists*isyst + hidx++] = new TH1D("_kb_phi_ele_met","_kb_phi_ele_met", 35, -3.5, 3.5);
    histObs[fNObHists*isyst + hidx++] = new TH1D("_kb_njet_mu","_kb_njet_mu", 30, 0., 30);
    histObs[fNObHists*isyst + hidx++] = new TH1D("_kb_nbjet_mu","_kb_nbjet_mu", 30, 0., 30);
    histObs[fNObHists*isyst + hidx++] = new TH1D("_kb_njet_ele","_kb_njet_ele", 30, 0., 30);
    histObs[fNObHists*isyst + hidx++] = new TH1D("_kb_nbjet_ele","_kb_nbjet_ele", 30, 0., 30);
    histObs[fNObHists*isyst + hidx++] = new TH1D("_kb_mjj_mu","_kb_mjj_mu", 2400, 0., 240);
    histObs[fNObHists*isyst + hidx++] = new TH1D("_kb_mjj_ele","_kb_mjj_ele", 2400, 0., 240);
    histObs[fNObHists*isyst + hidx++] = new TH1D("_kb_mjj_bf_mu","_kb_mjj_bf_mu", 2400, 0., 240);
    histObs[fNObHists*isyst + hidx++] = new TH1D("_kb_mjj_bf_ele","_kb_mjj_bf_ele", 2400, 0., 240);
    
    histObs[fNObHists*isyst + hidx++] = new TH1D("_ct_yLyMyT_mjj_mu","_ct_yLyMyT_mjj_mu", 2400, 0., 240);
    histObs[fNObHists*isyst + hidx++] = new TH1D("_ct_yLyMnT_mjj_mu","_ct_yLyMnT_mjj_mu", 2400, 0., 240);
    histObs[fNObHists*isyst + hidx++] = new TH1D("_ct_yLnMyT_mjj_mu","_ct_yLnMyT_mjj_mu", 2400, 0., 240);
    histObs[fNObHists*isyst + hidx++] = new TH1D("_ct_yLnMnT_mjj_mu","_ct_yLnMnT_mjj_mu", 2400, 0., 240);
    histObs[fNObHists*isyst + hidx++] = new TH1D("_ct_yMyT_mjj_mu","_ct_yMyT_mjj_mu", 2400, 0., 240);
    histObs[fNObHists*isyst + hidx++] = new TH1D("_ct_yMnT_mjj_mu","_ct_yMnT_mjj_mu", 2400, 0., 240);
    histObs[fNObHists*isyst + hidx++] = new TH1D("_ct_yT_mjj_mu","_ct_yT_mjj_mu", 2400, 0., 240);
    histObs[fNObHists*isyst + hidx++] = new TH1D("_ct_IncL_mjj_mu","_ct_IncL_mjj_mu", 2400, 0., 240);
    histObs[fNObHists*isyst + hidx++] = new TH1D("_ct_IncM_mjj_mu","_ct_IncM_mjj_mu", 2400, 0., 240);
    histObs[fNObHists*isyst + hidx++] = new TH1D("_ct_IncT_mjj_mu","_ct_IncT_mjj_mu", 2400, 0., 240);
    histObs[fNObHists*isyst + hidx++] = new TH1D("_ct_ExcL_mjj_mu","_ct_ExcL_mjj_mu", 2400, 0., 240);
    histObs[fNObHists*isyst + hidx++] = new TH1D("_ct_ExcM_mjj_mu","_ct_ExcM_mjj_mu", 2400, 0., 240);
    histObs[fNObHists*isyst + hidx++] = new TH1D("_ct_ExcT_mjj_mu","_ct_ExcT_mjj_mu", 2400, 0., 240);
    histObs[fNObHists*isyst + hidx++] = new TH1D("_ct_Exc0_mjj_mu","_ct_Exc0_mjj_mu", 2400, 0., 240);

    histObs[fNObHists*isyst + hidx++] = new TH1D("_ct_yLyMyT_mjj_ele","_ct_yLyMyT_mjj_ele", 2400, 0., 240);
    histObs[fNObHists*isyst + hidx++] = new TH1D("_ct_yLyMnT_mjj_ele","_ct_yLyMnT_mjj_ele", 2400, 0., 240);
    histObs[fNObHists*isyst + hidx++] = new TH1D("_ct_yLnMyT_mjj_ele","_ct_yLnMyT_mjj_ele", 2400, 0., 240);
    histObs[fNObHists*isyst + hidx++] = new TH1D("_ct_yLnMnT_mjj_ele","_ct_yLnMnT_mjj_ele", 2400, 0., 240);
    histObs[fNObHists*isyst + hidx++] = new TH1D("_ct_yMyT_mjj_ele","_ct_yMyT_mjj_ele", 2400, 0., 240);
    histObs[fNObHists*isyst + hidx++] = new TH1D("_ct_yMnT_mjj_ele","_ct_yMnT_mjj_ele", 2400, 0., 240);
    histObs[fNObHists*isyst + hidx++] = new TH1D("_ct_yT_mjj_ele","_ct_yT_mjj_ele", 2400, 0., 240);
    histObs[fNObHists*isyst + hidx++] = new TH1D("_ct_IncL_mjj_ele","_ct_IncL_mjj_ele", 2400, 0., 240);
    histObs[fNObHists*isyst + hidx++] = new TH1D("_ct_IncM_mjj_ele","_ct_IncM_mjj_ele", 2400, 0., 240);
    histObs[fNObHists*isyst + hidx++] = new TH1D("_ct_IncT_mjj_ele","_ct_IncT_mjj_ele", 2400, 0., 240);
    histObs[fNObHists*isyst + hidx++] = new TH1D("_ct_ExcL_mjj_ele","_ct_ExcL_mjj_ele", 2400, 0., 240);
    histObs[fNObHists*isyst + hidx++] = new TH1D("_ct_ExcM_mjj_ele","_ct_ExcM_mjj_ele", 2400, 0., 240);
    histObs[fNObHists*isyst + hidx++] = new TH1D("_ct_ExcT_mjj_ele","_ct_ExcT_mjj_ele", 2400, 0., 240);
    histObs[fNObHists*isyst + 51] = new TH1D("_ct_Exc0_mjj_ele","_ct_Exc0_mjj_ele", 2400, 0., 240);
    
    for(int icf=0;icf<fNBObHists;icf++)
      histObs[fNObHists*isyst + icf]->SetDirectory(fFileDir[isyst*fNDDReg + 0]);
    
    fFileDir[isyst*fNDDReg + 1]->cd();
    //fFileDir[isyst*fNDDReg + 1]->pwd(); cout <<" path " << fFileDir[isyst*fNDDReg+1]->GetPath() << endl;
    minHs = fNBObHists ;
    for(int ilmet=minHs;ilmet<(minHs+fNBObHists);ilmet++){
      histObs[fNObHists*isyst + ilmet] = (TH1D *)histObs[ilmet-minHs]->Clone(Form("%s_lmet",histObs[ilmet-minHs]->GetName()));
      histObs[fNObHists*isyst + ilmet]->SetTitle(Form("%s_lmet",histObs[ilmet-minHs]->GetTitle()));
      histObs[fNObHists*isyst + ilmet]->SetDirectory(fFileDir[isyst*fNDDReg + 1]);
    }
    
    fFileDir[isyst*fNDDReg + 2]->cd();
    //fFileDir[isyst*fNDDReg + 2]->pwd(); cout <<" path " << fFileDir[isyst*fNDDReg+2]->GetPath() << endl;
    minHs = 2*fNBObHists ;
    for(int iniso=minHs;iniso<(minHs+fNBObHists);iniso++){
      histObs[fNObHists*isyst + iniso] = (TH1D *)histObs[iniso-minHs]->Clone(Form("%s_noniso",histObs[iniso-minHs]->GetName()));
      histObs[fNObHists*isyst + iniso]->SetTitle(Form("%s_noniso",histObs[iniso-minHs]->GetTitle()));
      histObs[fNObHists*isyst + iniso]->SetDirectory(fFileDir[isyst*fNDDReg + 2]);
    }

    fFileDir[isyst*fNDDReg + 3]->cd();
    //fFileDir[isyst*fNDDReg + 3]->pwd(); cout <<" path " << fFileDir[isyst*fNDDReg+3]->GetPath() << endl;
    minHs = 3*fNBObHists ;
    for(int inisolmet=minHs;inisolmet<(minHs+fNBObHists);inisolmet++){
      histObs[fNObHists*isyst + inisolmet] = (TH1D *)histObs[inisolmet-minHs]->Clone(Form("%s_noniso_lmet",histObs[inisolmet-minHs]->GetName()));
      histObs[fNObHists*isyst + inisolmet]->SetTitle(Form("%s_noniso_lmet",histObs[inisolmet-minHs]->GetTitle()));
      histObs[fNObHists*isyst + inisolmet]->SetDirectory(fFileDir[isyst*fNDDReg + 3]);
    }
    ////////////////////////////////// Observables //////////////////////////////////////

    ////////////////////// Weight and other histograms histograms ///////////////////////
    fFileDir[isyst*fNDDReg + 0]->cd();
    hidx = 0;
    histWt[fNWtHists*isyst + hidx++] = new TH1D("_sampleWeight","_sampleWeight",200, -10, 10);
    histWt[fNWtHists*isyst + hidx++] = new TH1D("_PUWeight","_PUWeight",200, -10, 10);
    histWt[fNWtHists*isyst + hidx++] = new TH1D("_PUWeight_Up","_PUWeight_Up",200, -10, 10);
    histWt[fNWtHists*isyst + hidx++] = new TH1D("_PUWeight_Do","_PUWeight_Do",200, -10, 10);
    histWt[fNWtHists*isyst + hidx++] = new TH1D("_prefireWeight","_prefireWeight",200, -10, 10);
    histWt[fNWtHists*isyst + hidx++] = new TH1D("_prefireWeight_Up","_prefireWeight_Up",200, -10, 10);
    histWt[fNWtHists*isyst + hidx++] = new TH1D("_prefireWeight_Do","_prefireWeight_Do",200, -10, 10);
    histWt[fNWtHists*isyst + hidx++] = new TH1D("_muEffWeight","_muEffWeight",200, -10, 10);
    histWt[fNWtHists*isyst + hidx++] = new TH1D("_muEffWeight_Up","_muEffWeight_Up",200, -10, 10);
    histWt[fNWtHists*isyst + hidx++] = new TH1D("_muEffWeight_Do","_muEffWeight_Do",200, -10, 10);
    histWt[fNWtHists*isyst + hidx++] = new TH1D("_eleEffWeight","_eleEffWeight",200, -10, 10);
    histWt[fNWtHists*isyst + hidx++] = new TH1D("_eleEffWeight_Up","_eleEffWeight_Up",200, -10, 10);
    histWt[fNWtHists*isyst + hidx++] = new TH1D("_eleEffWeight_Do","_eleEffWeight_Do",200, -10, 10);
    histWt[fNWtHists*isyst + hidx++] = new TH1D("_PUJetIDWeight","_PUJetIDWeight",200, -10, 10);
    histWt[fNWtHists*isyst + hidx++] = new TH1D("_PUJetIDWeight_Up","_PUJetIDWeight_Up",200, -10, 10);
    histWt[fNWtHists*isyst + hidx++] = new TH1D("_PUJetIDWeight_Do","_PUJetIDWeight_Do",200, -10, 10);
    histWt[fNWtHists*isyst + hidx++] = new TH1D("_bcTagWeight","_bcTagWeight",300, -10, 50);
    histWt[fNWtHists*isyst + hidx++] = new TH1D("_bcTagWeight_stat_Up","_bcTagWeight_stat_Up",300, -10, 50);
    histWt[fNWtHists*isyst + hidx++] = new TH1D("_bcTagWeight_stat_Do","_bcTagWeight_stat_Do",300, -10, 50);
    histWt[fNWtHists*isyst + hidx++] = new TH1D("_bcTagWeight_pu_Up","_bcTagWeight_pu_Up",300, -10, 50);
    histWt[fNWtHists*isyst + hidx++] = new TH1D("_bcTagWeight_pu_Do","_bcTagWeight_pu_Do",300, -10, 50);    
    histWt[fNWtHists*isyst + hidx++] = new TH1D("_bcTagWeight_eleid_Up","_bcTagWeight_eleid_Up",300, -10, 50);
    histWt[fNWtHists*isyst + hidx++] = new TH1D("_bcTagWeight_eleid_Do","_bcTagWeight_eleid_Do",300, -10, 50);
    histWt[fNWtHists*isyst + hidx++] = new TH1D("_bcTagWeight_muid_Up","_bcTagWeight_muid_Up",300, -10, 50);
    histWt[fNWtHists*isyst + hidx++] = new TH1D("_bcTagWeight_muid_Do","_bcTagWeight_muid_Do",300, -10, 50);
    histWt[fNWtHists*isyst + hidx++] = new TH1D("_bcTagWeight_lhemuf_Up","_bcTagWeight_lhemuf_Up",300, -10, 50);
    histWt[fNWtHists*isyst + hidx++] = new TH1D("_bcTagWeight_lhemuf_Do","_bcTagWeight_lhemuf_Do",300, -10, 50);
    histWt[fNWtHists*isyst + hidx++] = new TH1D("_bcTagWeight_lhemur_Up","_bcTagWeight_lhemur_Up",300, -10, 50);
    histWt[fNWtHists*isyst + hidx++] = new TH1D("_bcTagWeight_lhemur_Do","_bcTagWeight_lhemur_Do",300, -10, 50);
    histWt[fNWtHists*isyst + hidx++] = new TH1D("_bcTagWeight_isr_Up","_bcTagWeight_isr_Up",300, -10, 50);
    histWt[fNWtHists*isyst + hidx++] = new TH1D("_bcTagWeight_isr_Do","_bcTagWeight_isr_Do",300, -10, 50);
    histWt[fNWtHists*isyst + hidx++] = new TH1D("_bcTagWeight_fsr_Up","_bcTagWeight_fsr_Up",300, -10, 50);
    histWt[fNWtHists*isyst + hidx++] = new TH1D("_bcTagWeight_fsr_Do","_bcTagWeight_fsr_Do",300, -10, 50);
    histWt[fNWtHists*isyst + hidx++] = new TH1D("_bcTagWeight_xdy_Up","_bcTagWeight_xdy_Up",300, -10, 50);
    histWt[fNWtHists*isyst + hidx++] = new TH1D("_bcTagWeight_xdy_Do","_bcTagWeight_xdy_Do",300, -10, 50);
    histWt[fNWtHists*isyst + hidx++] = new TH1D("_bcTagWeight_xst_Up","_bcTagWeight_xst_Up",300, -10, 50);
    histWt[fNWtHists*isyst + hidx++] = new TH1D("_bcTagWeight_xst_Do","_bcTagWeight_xst_Do",300, -10, 50);
    histWt[fNWtHists*isyst + hidx++] = new TH1D("_bcTagWeight_xwj_Up","_bcTagWeight_xwj_Up",300, -10, 50);
    histWt[fNWtHists*isyst + hidx++] = new TH1D("_bcTagWeight_xwj_Do","_bcTagWeight_xwj_Do",300, -10, 50);
    histWt[fNWtHists*isyst + hidx++] = new TH1D("_bcTagWeight_xtt_Up","_bcTagWeight_xtt_Up",300, -10, 50);
    histWt[fNWtHists*isyst + hidx++] = new TH1D("_bcTagWeight_xtt_Do","_bcTagWeight_xtt_Do",300, -10, 50);
    histWt[fNWtHists*isyst + hidx++] = new TH1D("_bcTagWeight_jes_Up","_bcTagWeight_jes_Up",300, -10, 50);
    histWt[fNWtHists*isyst + hidx++] = new TH1D("_bcTagWeight_jes_Do","_bcTagWeight_jes_Do",300, -10, 50);
    histWt[fNWtHists*isyst + hidx++] = new TH1D("_bcTagWeight_jer_Up","_bcTagWeight_jer_Up",300, -10, 50);
    histWt[fNWtHists*isyst + hidx++] = new TH1D("_bcTagWeight_jer_Do","_bcTagWeight_jer_Do",300, -10, 50);
    histWt[fNWtHists*isyst + hidx++] = new TH1D("_bcTagWeight_bfrag_Up","_bcTagWeight_bfrag_Up",300, -10, 50);
    histWt[fNWtHists*isyst + hidx++] = new TH1D("_bcTagWeight_bfrag_Do","_bcTagWeight_bfrag_Do",300, -10, 50);  
    /* // CShapeCalib UL */
    /* histWt[fNWtHists*isyst + hidx++] = new TH1D("_bcTagWeight_stat_Up","_bcTagWeight_stat_Up",300, -10, 50);
       histWt[fNWtHists*isyst + hidx++] = new TH1D("_bcTagWeight_stat_Do","_bcTagWeight_stat_Do",300, -10, 50);
       histWt[fNWtHists*isyst + hidx++] = new TH1D("_bcTagWeight_pu_Up","_bcTagWeight_pu_Up",300, -10, 50);
       histWt[fNWtHists*isyst + hidx++] = new TH1D("_bcTagWeight_pu_Do","_bcTagWeight_pu_Do",300, -10, 50);
    */
    /* histWt[fNWtHists*isyst + hidx++] = new TH1D("_bcTagWeight_intp_Up","_bcTagWeight_intp_Up",300, -10, 50);
       histWt[fNWtHists*isyst + hidx++] = new TH1D("_bcTagWeight_intp_Do","_bcTagWeight_intp_Do",300, -10, 50);
       histWt[fNWtHists*isyst + hidx++] = new TH1D("_bcTagWeight_extp_Up","_bcTagWeight_extp_Up",300, -10, 50);
       histWt[fNWtHists*isyst + hidx++] = new TH1D("_bcTagWeight_extp_Do","_bcTagWeight_extp_Do",300, -10, 50);
    */
    /* histWt[fNWtHists*isyst + hidx++] = new TH1D("_bcTagWeight_lhemuf_Up","_bcTagWeight_lhemuf_Up",300, -10, 50);
       histWt[fNWtHists*isyst + hidx++] = new TH1D("_bcTagWeight_lhemuf_Do","_bcTagWeight_lhemuf_Do",300, -10, 50);
       histWt[fNWtHists*isyst + hidx++] = new TH1D("_bcTagWeight_lhemur_Up","_bcTagWeight_lhemur_Up",300, -10, 50);
       histWt[fNWtHists*isyst + hidx++] = new TH1D("_bcTagWeight_lhemur_Do","_bcTagWeight_lhemur_Do",300, -10, 50);
    */
    /* histWt[fNWtHists*isyst + hidx++] = new TH1D("_bcTagWeight_isr_Up","_bcTagWeight_isr_Up",300, -10, 50);
       histWt[fNWtHists*isyst + hidx++] = new TH1D("_bcTagWeight_isr_Do","_bcTagWeight_isr_Do",300, -10, 50);
       histWt[fNWtHists*isyst + hidx++] = new TH1D("_bcTagWeight_fsr_Up","_bcTagWeight_fsr_Up",300, -10, 50);
       histWt[fNWtHists*isyst + hidx++] = new TH1D("_bcTagWeight_fsr_Do","_bcTagWeight_fsr_Do",300, -10, 50);
    */
    /* histWt[fNWtHists*isyst + hidx++] = new TH1D("_bcTagWeight_xdyb_Up","_bcTagWeight_xdyb_Up",300, -10, 50);
       histWt[fNWtHists*isyst + hidx++] = new TH1D("_bcTagWeight_xdyb_Do","_bcTagWeight_xdyb_Do",300, -10, 50);
       histWt[fNWtHists*isyst + hidx++] = new TH1D("_bcTagWeight_xdyc_Up","_bcTagWeight_xdyc_Up",300, -10, 50);
       histWt[fNWtHists*isyst + hidx++] = new TH1D("_bcTagWeight_xdyc_Do","_bcTagWeight_xdyc_Do",300, -10, 50);
    */
    /* Double_t _bcTagWeight_xwjc_Up, _bcTagWeight_xwjc_Do;  */
    /* histWt[fNWtHists*isyst + hidx++] = new TH1D("_bcTagWeight_jes_Up","_bcTagWeight_jes_Up",300, -10, 50);
       histWt[fNWtHists*isyst + hidx++] = new TH1D("_bcTagWeight_jes_Do","_bcTagWeight_jes_Do",300, -10, 50);
       histWt[fNWtHists*isyst + hidx++] = new TH1D("_bcTagWeight_jer_Up","_bcTagWeight_jer_Up",300, -10, 50);
       histWt[fNWtHists*isyst + hidx++] = new TH1D("_bcTagWeight_jer_Do","_bcTagWeight_jer_Do",300, -10, 50);
    */
    histWt[fNWtHists*isyst + hidx++] = new TH1D("_pdfweight_Up","_pdfweight_Up",200, -10, 10);
    histWt[fNWtHists*isyst + hidx++] = new TH1D("_pdfweight_Do","_pdfweight_Do",200, -10, 10);
    histWt[fNWtHists*isyst + hidx++] = new TH1D("_q2weight_Up","_q2weight_Up",200, -10, 10);
    histWt[fNWtHists*isyst + hidx++] = new TH1D("_q2weight_Do","_q2weight_Do",200, -10, 10);
    histWt[fNWtHists*isyst + hidx++] = new TH1D("_FSRweight_Up","_FSRweight_Up",300, -10, 50);
    histWt[fNWtHists*isyst + hidx++] = new TH1D("_FSRweight_Do","_FSRweight_Do",300, -10, 50);
    histWt[fNWtHists*isyst + hidx++] = new TH1D("_ISRweight_Up","_ISRweight_Up",200, -10, 10);
    histWt[fNWtHists*isyst + hidx++] = new TH1D("_ISRweight_Do","_ISRweight_Do",200, -10, 10);

    histWt[fNWtHists*isyst + hidx++] = new TH1D("_ctagWeight_yLyMyT","_ctagWeight_yLyMyT",200, -10, 10);
    histWt[fNWtHists*isyst + hidx++] = new TH1D("_ctagWeight_yLyMnT","_ctagWeight_yLyMnT",200, -10, 10);
    histWt[fNWtHists*isyst + hidx++] = new TH1D("_ctagWeight_yLnMyT","_ctagWeight_yLnMyT",200, -10, 10);
    histWt[fNWtHists*isyst + hidx++] = new TH1D("_ctagWeight_yLnMnT","_ctagWeight_yLnMnT",200, -10, 10);
    histWt[fNWtHists*isyst + hidx++] = new TH1D("_ctagWeight_yMyT","_ctagWeight_yMyT",200, -10, 10);
    histWt[fNWtHists*isyst + hidx++] = new TH1D("_ctagWeight_yMnT","_ctagWeight_yMnT",200, -10, 10);
    histWt[fNWtHists*isyst + hidx++] = new TH1D("_ctagWeight_yT","_ctagWeight_yT",200, -10, 10);
    histWt[fNWtHists*isyst + hidx++] = new TH1D("_ctagWeight_IncL","_ctagWeight_IncL",200, -10, 10);
    histWt[fNWtHists*isyst + hidx++] = new TH1D("_ctagWeight_IncM","_ctagWeight_IncM",200, -10, 10);
    histWt[fNWtHists*isyst + hidx++] = new TH1D("_ctagWeight_IncT","_ctagWeight_IncT",200, -10, 10);
    histWt[fNWtHists*isyst + hidx++] = new TH1D("_ctagWeight_ExcL","_ctagWeight_ExcL",200, -10, 10);
    histWt[fNWtHists*isyst + hidx++] = new TH1D("_ctagWeight_ExcM","_ctagWeight_ExcM",200, -10, 10);
    histWt[fNWtHists*isyst + hidx++] = new TH1D("_ctagWeight_ExcT","_ctagWeight_ExcT",200, -10, 10);
    histWt[fNWtHists*isyst + 68] = new TH1D("_ctagWeight_Exc0","_ctagWeight_ExcT",200, -10, 10);

    
    for(int icf=0;icf<fNBWtHists;icf++)
      histWt[fNWtHists*isyst + icf]->SetDirectory(fFileDir[isyst*fNDDReg + 0]);
  
    fFileDir[isyst*fNDDReg + 1]->cd();
    //fFileDir[isyst*fNDDReg + 1]->pwd(); cout <<" path " << fFileDir[isyst*fNDDReg+1]->GetPath() << endl;
    minHs = fNBWtHists ;
    for(int ilmet=minHs;ilmet<(minHs+fNBWtHists);ilmet++){
      histWt[fNWtHists*isyst + ilmet] = (TH1D *)histWt[ilmet-minHs]->Clone(Form("%s_lmet",histWt[ilmet-minHs]->GetName()));
      histWt[fNWtHists*isyst + ilmet]->SetTitle(Form("%s_lmet",histWt[ilmet-minHs]->GetTitle()));
      histWt[fNWtHists*isyst + ilmet]->SetDirectory(fFileDir[isyst*fNDDReg + 1]);
    }
    
    fFileDir[isyst*fNDDReg + 2]->cd();
    //fFileDir[isyst*fNDDReg + 2]->pwd(); cout <<" path " << fFileDir[isyst*fNDDReg+2]->GetPath() << endl;
    minHs = 2*fNBWtHists ;
    for(int iniso=minHs;iniso<(minHs+fNBWtHists);iniso++){
      histWt[fNWtHists*isyst + iniso] = (TH1D *)histWt[iniso-minHs]->Clone(Form("%s_noniso",histWt[iniso-minHs]->GetName()));
      histWt[fNWtHists*isyst + iniso]->SetTitle(Form("%s_noniso",histWt[iniso-minHs]->GetTitle()));
      histWt[fNWtHists*isyst + iniso]->SetDirectory(fFileDir[isyst*fNDDReg + 2]);
    }

    fFileDir[isyst*fNDDReg + 3]->cd();
    //fFileDir[isyst*fNDDReg + 3]->pwd(); cout <<" path " << fFileDir[isyst*fNDDReg+3]->GetPath() << endl;
    minHs = 3*fNBWtHists ;
    for(int inisolmet=minHs;inisolmet<(minHs+fNBWtHists);inisolmet++){
      histWt[fNWtHists*isyst + inisolmet] = (TH1D *)histWt[inisolmet-minHs]->Clone(Form("%s_noniso_lmet",histWt[inisolmet-minHs]->GetName()));
      histWt[fNWtHists*isyst + inisolmet]->SetTitle(Form("%s_noniso_lmet",histWt[inisolmet-minHs]->GetTitle()));
      histWt[fNWtHists*isyst + inisolmet]->SetDirectory(fFileDir[isyst*fNDDReg + 3]);
    }
    ////////////////////// Weight and other histograms histograms ///////////////////////

  }

  savedir->cd();

  // for(int isyst=0;isyst<fNSyst;isyst++){
  //   cout << "Nof Objects " << fFileDir[isyst*fNDDReg + 0]->GetList()->GetEntries() << endl ; 
  //   cout << "First Object " << fFileDir[isyst*fNDDReg + 0]->GetList()->At(0)->GetName() << endl ; 
  //   cout << "Last Object " << fFileDir[isyst*fNDDReg + 0]->GetList()->At(fFileDir[isyst*fNDDReg + 0]->GetList()->GetEntries()-1)->GetName() << endl ; 
  //   cout << "Nof Objects " << fFileDir[isyst*fNDDReg + 3]->GetList()->GetEntries() << endl ; 
  //   cout << "First Object " << fFileDir[isyst*fNDDReg + 3]->GetList()->At(0)->GetName() << endl ; 
  //   cout << "Last Object " << fFileDir[isyst*fNDDReg + 3]->GetList()->At(fFileDir[isyst*fNDDReg + 3]->GetList()->GetEntries()-1)->GetName() << endl ; 
  // }
  
  
  savedir->cd();
  
  if(fSyst=="base"){
    fNBSelCols = 4; //Nof cutflow columns
    fNBSelColHists = 2; //nof histograms 
    fNSelColHists = fNBSelCols*fNBSelColHists;
    hControl = new TH1D*[fNSelColHists];
    fNBSelColProfiles = 2; //nof TProfiles 
    fNSelColProfiles = fNBSelCols*fNBSelColProfiles;
    pControl = new TProfile*[fNSelColProfiles];
    const char *cfcols[] = {"KinFit", "ctagL", "ctagM", "ctagT"} ;
    
    fSelColDir = new TDirectory*[fNBSelCols];  
    
    TDirectory *basePath = d1->GetDirectory(Form("%s/base",d1->GetPath()));

    for(int iscl=0;iscl<fNBSelCols;iscl++){
      fSelColDir[iscl] = basePath->mkdir(Form("%s",cfcols[iscl]));
      fSelColDir[iscl]->cd();
      int hidx = 0;
      hControl[iscl*fNBSelColHists + hidx++] = new TH1D("pv_npvs","pv_npvs",100, 0., 100.);
      hControl[iscl*fNBSelColHists + 1] = new TH1D("kfProbUS","kfProbUS",200, -0.5, 1.5);

      hidx = 0;
      pControl[iscl*fNBSelColProfiles + hidx++] = new TProfile("ctagL_s","ctagL_s",100, 0., 1000., 0., 4.);
      pControl[iscl*fNBSelColProfiles + 1] = new TProfile("probMjj","probMjj",200, -0.5, 1.5, 0., 200.);
    }
  }//fSyst==base


  return true;
}

//_____________________________________________________________________________
void KinAna::GetArguments(){
  
  TString option = GetOption();
  //Info("GetArguments","ending KinAna with process option: %s", option.Data());
  
  Ssiz_t from = 0;
  TString tok;
  // Now analyze the arguments
  while (option.Tokenize(tok , from , "|")) {
    if(tok.BeginsWith("sample"))
      fSample = ((TObjString *) (tok.Tokenize("="))->At(1))->GetString();
    if(tok.BeginsWith("input"))
      fFileName = ((TObjString *) (tok.Tokenize("="))->At(1))->GetString();
    if(tok.BeginsWith("ref"))
      fRefPath = ((TObjString *) (tok.Tokenize("="))->At(1))->GetString();
    if(tok.BeginsWith("year"))
      fYear = (((TObjString *) (tok.Tokenize("="))->At(1))->GetString()).Atoi();
    if(tok.BeginsWith("mode"))
      fMode = ((TObjString *) (tok.Tokenize("="))->At(1))->GetString();
    if(tok.BeginsWith("index"))
      fIndex = (((TObjString *) (tok.Tokenize("="))->At(1))->GetString()).Atoi();
    if(tok.BeginsWith("total"))
      fTotal = (((TObjString *) (tok.Tokenize("="))->At(1))->GetString()).Atoi();
    if(tok.BeginsWith("syst"))
      fSyst = ((TObjString *) (tok.Tokenize("="))->At(1))->GetString();
  }
  fSyst.ToLower();
  fIndex++;

  if(fSample.BeginsWith("Data")){
    fSampleDir = "data_obs";
    isData = true;
  }else{
    fSampleDir = fSample;
    isData = false;
  }
  
  TString hostname = gSystem->HostName();
  if(fMode.Contains("proof")){
    if(hostname.BeginsWith("Indra-Rjn"))
      fBasePath = "/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna";
    else if(hostname.BeginsWith("lxplus"))
      fBasePath = "/tmp/idas/CBA_Skim";
    else if(hostname.BeginsWith("ui"))
      fBasePath = "/tmp/idas/CBA_Skim";
    else if(hostname.BeginsWith("lnx3"))
      fBasePath = "/home/indra/CMS-Analysis/NanoAOD-Analysis/KinFit_Skim/CBA_Skim";
    //fBasePath += "/KinAna";
  }else{
    fBasePath = gSystem->pwd();
  }
  isPreVFP = fRefPath.Contains("/pre/") ? true : false ;
  isPostVFP = fRefPath.Contains("/post/") ? true : false ;
  
}
//_____________________________________________________________________________
void KinAna::SelectSyst()
{
  
  puvar012_g		= 1 ;		// 0:down, 1:norm, 2:up
  mueffvar012_g		= 1 ;		// 0:down, 1:norm, 2:up
  eleeffvar012_g	= 1 ;		// 0:down, 1:norm, 2:up
  btagbvar012_g		= 1 ;		// 0:down, 1:norm, 2:up
  btaglvar012_g		= 1 ;		// 0:down, 1:norm, 2:up
  pdfvar012_g		= 1 ;		// 0:down, 1:norm, 2:up
  q2var012_g		= 1 ;		// 0:down, 1:norm, 2:up
  fsrvar012_g		= 1 ;		// 0:down, 1:norm, 2:up
  isrvar012_g		= 1 ;		// 0:down, 1:norm, 2:up
  prefirevar012_g	= 1 ;           // 0:down, 1:norm, 2:up
  PUJetIDSystType	= "nom";
  btagSystType		= "central" ;
  ctagSystType		= "central" ;
  bctagSystType         ="central" ;
  
  // ctagMSystType		= "central" ;
  // ctagTSystType		= "central" ;
  
  jecvar012_g		= 1 ;		// 0:down, 1:norm, 2:up
  jervar012_g		= 1 ;		// 0:down, 1:norm, 2:up
  
  // fNSyst = 34 ; 
  // //fSystList = new char*[fNSyst];
  // const char *syst[] = {"base", 
  // 			"puup", "pudown", "mueffup", "mueffdown", 
  // 			"eleeffup", "eleeffdown",  "jecup", "jecdown", 
  // 			"jerup", "jerdown", "btagbup", "btagbdown", 
  // 			"btaglup", "btagldown", "prefireup", "prefiredown",
  // 			"pdfup", "pdfdown", "q2fup", "q2down",
  // 			"isrup", "isrdown", "fsrup", "fsrdown",
  // 			"iso20", "metup", "metdown",
  //                       "cp5up","cp5down","hdampup","hdampdown", 
  // 			"mtopup", "mtopdown"};
  
  // for(int isyst=0;isyst<fNSyst;isyst++){
  //   //fSystList[isyst] = new char[20];
  //   //strcpy(fSystList[isyst],syst[isyst]);
  //   fSystList.push_back(syst[isyst]);
  // }

  const char *systbase[] = {"base", 
			    "pdfup", "pdfdown", "q2up", "q2down",
			    "isrup", "isrdown", "fsrup", "fsrdown",
			    "puup", "pudown", "prefireup", "prefiredown",
			    "mueffup", "mueffdown", "eleeffup", "eleeffdown", 
			    "pujetidup", "pujetiddown",  //19
			    // //OLD
			    // "btagbup", "btagbdown", 
			    // "btaglup", "btagldown", 
                            // "bctag1up", "bctag1down", 
			    // "bctag2up", "bctag2down",
                            // "bctag3up", "bctag3down" //10
			    //CShapeCalib EOY
			    "bcstatup", "bcstatdown",
			    "bclhemufup", "bclhemufdown", "bclhemurup", "bclhemurdown",
			    "bcxdyup", "bcxdydown", "bcxstup", "bcxstdown", 
			    "bcxwjup", "bcxwjdown", "bcxttup", "bcxttdown", 
			    "bcbfragup", "bcbfragdown" //16
			    // CShapeCalib UL
			    // "bcstatup", "bcstatdown",
			    // "bcintpup", "bcintpdown", "bcextpup", "bcextpdown",
			    // "bclhemufup", "bclhemufdown", "bclhemurup", "bclhemurdown",
			    // "bcxdybup", "bcxdybdown", "bcxdycup", "bcxdycdown",
			    // "bcxwjcup", "bcxwjcdown"//16

                            };
  
  if (fSyst == "base"){

    Info("SelectSyst","Syst : %s", fSyst.Data()); 
    systType = kBase ;
    if(isData){
      fNSyst = 1;
      fSystList.push_back(fSyst);       
    }else{
      fNSyst = 35; 
      for(int isyst=0;isyst<fNSyst;isyst++)
	fSystList.push_back(systbase[isyst]);
    }
  } else if (fSyst == "jecup") {
    
    systType = kJECUp;
    jecvar012_g = 2;      
    Info("SelectSyst","Syst : %s", fSyst.Data()); 
    fNSyst = 1;
    fSystList.push_back(fSyst);

  } else if (fSyst == "jecdown") {
    
    systType = kJECDown;
    jecvar012_g = 0;      
    Info("SelectSyst","Syst : %s", fSyst.Data()); 
    fNSyst = 1;
    fSystList.push_back(fSyst);
    
  } else if (fSyst == "jerup") {

    systType = kJERUp;
    jervar012_g = 2;      
    Info("SelectSyst","Syst : %s", fSyst.Data()); 
    fNSyst = 1;
    fSystList.push_back(fSyst);

  } else if (fSyst == "jerdown") {

    systType = kJERDown;
    jervar012_g = 0;      
    Info("SelectSyst","Syst : %s", fSyst.Data()); 
    fNSyst = 1;
    fSystList.push_back(fSyst);
    
  } else if (fSyst == "iso20") {
    
    systType = kIso20;    
    Info("SelectSyst","Syst : %s", fSyst.Data()); 
    fNSyst = 1;
    fSystList.push_back(fSyst);

  } else if (fSyst == "metup") {

    systType = kMETUp;
    Info("SelectSyst","Syst : %s", fSyst.Data()); 
    fNSyst = 1;
    fSystList.push_back(fSyst);
    
  } else if (fSyst == "metdown") {
    
    systType = kMETDown;
    Info("SelectSyst","Syst : %s", fSyst.Data()); 
    fNSyst = 1;
    fSystList.push_back(fSyst);

  } else if (fSyst == "cp5up") {
    
    systType = kCP5Up;
    Info("SelectSyst","Syst : %s", fSyst.Data()); 
    fNSyst = 1;
    fSystList.push_back(fSyst);

  } else if (fSyst == "cp5down") {
    
    systType = kCP5Down;
    Info("SelectSyst","Syst : %s", fSyst.Data()); 
    fNSyst = 1;
    fSystList.push_back(fSyst);

  } else if (fSyst == "hdampup") {
    
    systType = khDampUp;
    Info("SelectSyst","Syst : %s", fSyst.Data()); 
    fNSyst = 1;
    fSystList.push_back(fSyst);

  } else if (fSyst == "hdampdown") {
    
    systType = khDampDown;
    Info("SelectSyst","Syst : %s", fSyst.Data()); 
    fNSyst = 1;
    fSystList.push_back(fSyst);

  } else if (fSyst == "mtopup") {
    
    systType = kmTopUp;
    Info("SelectSyst","Syst : %s", fSyst.Data()); 
    fNSyst = 1;
    fSystList.push_back(fSyst);
    
  } else if (fSyst == "mtopdown") {
    
    systType = kmTopDown;
    Info("SelectSyst","Syst : %s", fSyst.Data()); 
    fNSyst = 1;
    fSystList.push_back(fSyst);

  }
  
  
  
}

//_____________________________________________________________________________
void KinAna::SetTrio()
{
  
  useDeepCSVbTag = false;
  
  if (useDeepCSVbTag){
    // While changing cut to L,M,T make sure to change the efficiency file

    //btag
    if (fYear==2016){
      btag_cut_DeepCSVa = 0.6001; 
      btag_cut_DeepCSVb = 0.5847;
      btag_cut_DeepCSV = (btag_cut_DeepCSVa + btag_cut_DeepCSVb)/2.0;
    }
    if (fYear==2017) btag_cut_DeepCSV = 0.4506;
    if (fYear==2018) btag_cut_DeepCSV = 0.4168;

  }else{
    //btag
    if (fYear==2016){
      btag_cuta = 0.2598 ; 
      btag_cutb = 0.2489 ;
      btag_cut = (btag_cuta + btag_cutb)/2.0;
    }
    if (fYear==2017) btag_cut = 0.3040 ;
    if (fYear==2018) btag_cut = 0.2783 ;

    //ctag
    if (fYear==2016){
      ctag_CvsL_L_cuta = 0.039 ; 
      ctag_CvsB_L_cuta = 0.327 ; 
      ctag_CvsL_M_cuta = 0.098 ; 
      ctag_CvsB_M_cuta = 0.370 ; 
      ctag_CvsL_T_cuta = 0.270 ; 
      ctag_CvsB_T_cuta = 0.256 ; 

      ctag_CvsL_L_cutb = 0.039 ; 
      ctag_CvsB_L_cutb = 0.305 ; 
      ctag_CvsL_M_cutb = 0.099 ; 
      ctag_CvsB_M_cutb = 0.353 ; 
      ctag_CvsL_T_cutb = 0.269 ; 
      ctag_CvsB_T_cutb = 0.247 ;
      
      // ctag_CvsL_L_cut = (ctag_CvsL_L_cuta + ctag_CvsL_L_cutb)/2.0;
      // ctag_CvsB_L_cut = (ctag_CvsB_L_cuta + ctag_CvsB_L_cutb)/2.0;
      // ctag_CvsL_M_cut = (ctag_CvsL_M_cuta + ctag_CvsL_M_cutb)/2.0;
      // ctag_CvsB_M_cut = (ctag_CvsB_M_cuta + ctag_CvsB_M_cutb)/2.0;
      // ctag_CvsL_T_cut = (ctag_CvsL_T_cuta + ctag_CvsL_T_cutb)/2.0;
      // ctag_CvsB_T_cut = (ctag_CvsB_T_cuta + ctag_CvsB_T_cutb)/2.0;

      if(isPreVFP){
	ctag_CvsL_L_cut = ctag_CvsL_L_cuta ;
	ctag_CvsB_L_cut = ctag_CvsB_L_cuta ;
	ctag_CvsL_M_cut = ctag_CvsL_M_cuta ;
	ctag_CvsB_M_cut = ctag_CvsB_M_cuta ;
	ctag_CvsL_T_cut = ctag_CvsL_T_cuta ;
	ctag_CvsB_T_cut = ctag_CvsB_T_cuta ;
      }
      if(isPostVFP){
	ctag_CvsL_L_cut = ctag_CvsL_L_cutb ;
	ctag_CvsB_L_cut = ctag_CvsB_L_cutb ;
	ctag_CvsL_M_cut = ctag_CvsL_M_cutb ;
	ctag_CvsB_M_cut = ctag_CvsB_M_cutb ;
	ctag_CvsL_T_cut = ctag_CvsL_T_cutb ;
	ctag_CvsB_T_cut = ctag_CvsB_T_cutb ;
      }

    }
    if (fYear==2017){
      ctag_CvsL_L_cut = 0.03 ;
      ctag_CvsB_L_cut = 0.4 ;
      ctag_CvsL_M_cut = 0.085 ; 
      ctag_CvsB_M_cut = 0.34 ; 
      ctag_CvsL_T_cut = 0.52 ;
      ctag_CvsB_T_cut = 0.05 ; 
    }
    if (fYear==2018){
      ctag_CvsL_L_cut = 0.038 ;
      ctag_CvsB_L_cut = 0.246 ;
      ctag_CvsL_M_cut = 0.099 ;
      ctag_CvsB_M_cut = 0.325 ;
      ctag_CvsL_T_cut = 0.282 ;
      ctag_CvsB_T_cut = 0.267 ;
    }
    
  }
  
  
}


//_____________________________________________________________________________
void KinAna::Begin(TTree */*tree*/)
{
   // This is needed when re-processing the object
   Reset();
   
   //print the option specified in the Process function.
   TString option = GetOption();
   Info("Begin", "starting KinAna with process option: %s", option.Data());
   
   //if (fChain) fChain->SetEntryList(0);
}


//_____________________________________________________________________________
void KinAna::SlaveBegin(TTree *tree)
{  
  //print the option specified in the Process function.
  TString option = GetOption();
  Info("SlaveBegin",
       "starting KinAna with process option: %s (tree: %p)", option.Data(), tree);
  
  GetArguments();  //set class attributes from input arguments
  Info("SlaveBegin",
       "sample : %s, year : %d, mode : %s", fSample.Data(), fYear, fMode.Data());

  SelectSyst();   // Setters for systematics types
  SetTrio();      // SetTrio method sets the hadler values of three classe EventTree(), Selector(), EventPick() 
  // // Info("SlaveBegin",
  // //      "Chain %p (tree: %p)", event->chain, tree);
  
  //initialize the Tree branch addresses
  Init(tree);     //initialize the Tree branch addresses
  
  char *filename[1];
  
  filename[0] = Form("%s_hist_%s_%dof%d.root",fSample.Data(),fSyst.Data(),fIndex,fTotal) ;
  // filename[1] = Form("%s_tree_%s_%dof%d.root",fSample.Data(),fSyst.Data(),fIndex,fTotal) ;
  // filename[2] = Form("%s_bjet_%s_%dof%d.root",fSample.Data(),fSyst.Data(),fIndex,fTotal) ;
  
  for(int ifile=0;ifile<1;ifile++){
    
    if(fMode.BeginsWith("proof")){
      fProofFile[ifile] = new TProofOutputFile(filename[ifile], "M");
      fFile[ifile] = fProofFile[ifile]->OpenFile("RECREATE");
      if (fFile[ifile] && fFile[ifile]->IsZombie()) SafeDelete(fFile[ifile]);
    }else{
      fFile[ifile] = TFile::Open(filename[ifile],"RECREATE");
    }
    
    // Cannot continue
    if (!fFile[ifile]) {
      TString amsg = TString::Format("KinAna::SlaveBegin: could not create '%s':"
				     " instance is invalid!", fFile[ifile]->GetName());
      Abort(amsg, kAbortProcess);
      return;
    }
        
  }//ifile loop
  
  Info("SlaveBegin", "Create Histos");
  CreateHistoArrays();    // Create output histogram arrays
  // IsDebug = true;
  
  if(fMode.BeginsWith("proof")) fRefFile = fRefPath ;
  fRefF = TFile::Open(fRefFile.Data());
  
  Info("SlaveBegin", "End of SlaveBegin");
  
  nCTag = 0;

}

// //_____________________________________________________________________________

// void KinAna::Clean(){
  
// }    



//_____________________________________________________________________________
Bool_t KinAna::Process(Long64_t entry)
{
  // entry is the entry number in the current Tree
  
  // Clean();
  // // to read complete event, call fChain->GetTree()->GetEntry(entry)  
  fChain->GetTree()->GetEntry(entry);  
  
  fProcessed++;
  fStatus++;
  
  // //Collection at tree entry level before applying any weight
  // ////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // if(systType == kBase) FillEventControlHists();
  // ////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  int mod_num = 10000;
  if(fProcessed%mod_num==0){
    Info("Process","Processing : %lld(%lld) of number of events : %lld, year : %d", 
	 fProcessed, entry, fChain->GetEntries(), fYear);
  }
  if(IsDebug) Info("Process","Completed process count");
  
  FillWtHists();
  cjhadAF.SetPtEtaPhiE(jetChadPt, jetChadEta, jetChadPhi, jetChadEn);
  sjhadAF.SetPtEtaPhiE(jetShadPt, jetShadEta, jetShadPhi, jetShadEn);
  neutrinoAF.SetXYZM(metPx, metPy, metPz, 0.0);
  bjhadAF.SetPtEtaPhiE(jetBhadPt, jetBhadEta, jetBhadPhi, jetBhadEn);
  bjlepAF.SetPtEtaPhiE(jetBlepPt, jetBlepEta, jetBlepPhi, jetBlepEn);
  leptonAF.SetPtEtaPhiE(lepPt, lepEta, lepPhi, lepEn);

  
  wt_ratio = 1.0;
  
  
  //Processes for KinFit selection will be placed in block below
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////
  FillKFCFObs();
  // if(systType == kBase) FillKinFitControlHists();
  // if(IsDebug) Info("Process","Completed KinFit processing");
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////


  //Processes for CTagging will be placed in block below
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////
  FillCTagObs();
  // if(systType == kBase) FillCTagControlHists();
  // if(IsDebug) Info("Process","Completed CTagging");
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////

  
  return kTRUE;

}


//_____________________________________________________________________________
void KinAna::FillWtHists(){

  // for(int isyst=0;isyst<fNSyst;isyst++){
  //   TList *list = (TList *)fFileDir[isyst*fNDDReg + 0]->GetList();
  //   ((TH1D *) list->FindObject("_sampleWeight"))->Fill(_sampleWeight);
  //   ((TH1D *) list->FindObject("_PUWeight"))->Fill(_PUWeight);
  //   ((TH1D *) list->FindObject("_prefireWeight"))->Fill(_prefireWeight);
  //   ((TH1D *) list->FindObject("_PUWeight_Up"))->Fill(_PUWeight_Up);
  //   ((TH1D *) list->FindObject("_PUWeight_Do"))->Fill(_PUWeight_Do);
  // }
  
  for(int isyst=0;isyst<fNSyst;isyst++){
    if((muonIsoCut or eleIsoCut) and !isLowMET){
      TList *list = (TList *)fFileDir[isyst*fNDDReg + 0]->GetList();
      // ((TH1D *) list->FindObject("_sampleWeight"))->Fill(_sampleWeight);
      // ((TH1D *) list->FindObject("_PUWeight"))->Fill(_PUWeight);
      // ((TH1D *) list->FindObject("_prefireWeight"))->Fill(_prefireWeight);
      // ((TH1D *) list->FindObject("_PUWeight_Up"))->Fill(_PUWeight_Up);
      // ((TH1D *) list->FindObject("_PUWeight_Do"))->Fill(_PUWeight_Do);

      ((TH1D *) list->FindObject("_sampleWeight"))->Fill(_sampleWeight);
  
      ((TH1D *) list->FindObject("_PUWeight"))->Fill(_PUWeight);
      ((TH1D *) list->FindObject("_PUWeight_Up"))->Fill(_PUWeight_Up);
      ((TH1D *) list->FindObject("_PUWeight_Do"))->Fill(_PUWeight_Do);
  
      ((TH1D *) list->FindObject("_prefireWeight"))->Fill(_prefireWeight);
      ((TH1D *) list->FindObject("_prefireWeight_Up"))->Fill(_prefireWeight_Up);
      ((TH1D *) list->FindObject("_prefireWeight_Do"))->Fill(_prefireWeight_Do);

      ((TH1D *) list->FindObject("_muEffWeight"))->Fill(_muEffWeight);
      ((TH1D *) list->FindObject("_muEffWeight_Up"))->Fill(_muEffWeight_Up);
      ((TH1D *) list->FindObject("_muEffWeight_Do"))->Fill(_muEffWeight_Do);
  
      ((TH1D *) list->FindObject("_eleEffWeight"))->Fill(_eleEffWeight);
      ((TH1D *) list->FindObject("_eleEffWeight_Up"))->Fill(_eleEffWeight_Up);
      ((TH1D *) list->FindObject("_eleEffWeight_Do"))->Fill(_eleEffWeight_Do);
  
      ((TH1D *) list->FindObject("_PUJetIDWeight"))->Fill(_PUJetIDWeight);
      ((TH1D *) list->FindObject("_PUJetIDWeight_Up"))->Fill(_PUJetIDWeight_Up);
      ((TH1D *) list->FindObject("_PUJetIDWeight_Do"))->Fill(_PUJetIDWeight_Do);

      // CShapeCalib EOY
      ((TH1D *) list->FindObject("_bcTagWeight"))->Fill(_bcTagWeight); 
      ((TH1D *) list->FindObject("_bcTagWeight_stat_Up"))->Fill(_bcTagWeight_stat_Up); 
      ((TH1D *) list->FindObject("_bcTagWeight_stat_Do"))->Fill(_bcTagWeight_stat_Do);
      ((TH1D *) list->FindObject("_bcTagWeight_pu_Up"))->Fill(_bcTagWeight_pu_Up);
      ((TH1D *) list->FindObject("_bcTagWeight_pu_Do"))->Fill(_bcTagWeight_pu_Do); 
      ((TH1D *) list->FindObject("_bcTagWeight_eleid_Up"))->Fill(_bcTagWeight_eleid_Up); 
      ((TH1D *) list->FindObject("_bcTagWeight_eleid_Do"))->Fill(_bcTagWeight_eleid_Do);
      ((TH1D *) list->FindObject("_bcTagWeight_muid_Up"))->Fill(_bcTagWeight_muid_Up);
      ((TH1D *) list->FindObject("_bcTagWeight_muid_Do"))->Fill(_bcTagWeight_muid_Do); 
      ((TH1D *) list->FindObject("_bcTagWeight_lhemuf_Up"))->Fill(_bcTagWeight_lhemuf_Up); 
      ((TH1D *) list->FindObject("_bcTagWeight_lhemuf_Do"))->Fill(_bcTagWeight_lhemuf_Do);
      ((TH1D *) list->FindObject("_bcTagWeight_lhemur_Up"))->Fill(_bcTagWeight_lhemur_Up);
      ((TH1D *) list->FindObject("_bcTagWeight_lhemur_Do"))->Fill(_bcTagWeight_lhemur_Do); 
      ((TH1D *) list->FindObject("_bcTagWeight_isr_Up"))->Fill(_bcTagWeight_isr_Up); 
      ((TH1D *) list->FindObject("_bcTagWeight_isr_Do"))->Fill(_bcTagWeight_isr_Do);
      ((TH1D *) list->FindObject("_bcTagWeight_fsr_Up"))->Fill(_bcTagWeight_fsr_Up);
      ((TH1D *) list->FindObject("_bcTagWeight_fsr_Do"))->Fill(_bcTagWeight_fsr_Do); 
      ((TH1D *) list->FindObject("_bcTagWeight_xdy_Up"))->Fill(_bcTagWeight_xdy_Up); 
      ((TH1D *) list->FindObject("_bcTagWeight_xdy_Do"))->Fill(_bcTagWeight_xdy_Do);
      ((TH1D *) list->FindObject("_bcTagWeight_xst_Up"))->Fill(_bcTagWeight_xst_Up);
      ((TH1D *) list->FindObject("_bcTagWeight_xst_Do"))->Fill(_bcTagWeight_xst_Do); 
      ((TH1D *) list->FindObject("_bcTagWeight_xwj_Up"))->Fill(_bcTagWeight_xwj_Up); 
      ((TH1D *) list->FindObject("_bcTagWeight_xwj_Do"))->Fill(_bcTagWeight_xwj_Do);
      ((TH1D *) list->FindObject("_bcTagWeight_xtt_Up"))->Fill(_bcTagWeight_xtt_Up);
      ((TH1D *) list->FindObject("_bcTagWeight_xtt_Do"))->Fill(_bcTagWeight_xtt_Do); 
      ((TH1D *) list->FindObject("_bcTagWeight_jes_Up"))->Fill(_bcTagWeight_jes_Up); 
      ((TH1D *) list->FindObject("_bcTagWeight_jes_Do"))->Fill(_bcTagWeight_jes_Do);
      ((TH1D *) list->FindObject("_bcTagWeight_jer_Up"))->Fill(_bcTagWeight_jer_Up);
      ((TH1D *) list->FindObject("_bcTagWeight_jer_Do"))->Fill(_bcTagWeight_jer_Do); 
      ((TH1D *) list->FindObject("_bcTagWeight_bfrag_Up"))->Fill(_bcTagWeight_bfrag_Up); 
      ((TH1D *) list->FindObject("_bcTagWeight_bfrag_Do"))->Fill(_bcTagWeight_bfrag_Do); 
  
      /* // CShapeCalib UL */
      /* ((TH1D *) list->FindObject("_bcTagWeight_stat_Up"))->Fill(_bcTagWeight_stat_Up); 
	 ((TH1D *) list->FindObject("_bcTagWeight_stat_Do"))->Fill(_bcTagWeight_stat_Do);
	 ((TH1D *) list->FindObject("_bcTagWeight_pu_Up"))->Fill(_bcTagWeight_pu_Up);
	 ((TH1D *) list->FindObject("_bcTagWeight_pu_Do"))->Fill(_bcTagWeight_pu_Do);  */
      /* ((TH1D *) list->FindObject("_bcTagWeight_intp_Up"))->Fill(_bcTagWeight_intp_Up); 
	 ((TH1D *) list->FindObject("_bcTagWeight_intp_Do"))->Fill(_bcTagWeight_intp_Do);
	 ((TH1D *) list->FindObject("_bcTagWeight_extp_Up"))->Fill(_bcTagWeight_extp_Up);
	 ((TH1D *) list->FindObject("_bcTagWeight_extp_Do"))->Fill(_bcTagWeight_extp_Do);     */
      /* ((TH1D *) list->FindObject("_bcTagWeight_lhemuf_Up"))->Fill(_bcTagWeight_lhemuf_Up); 
	 ((TH1D *) list->FindObject("_bcTagWeight_lhemuf_Do"))->Fill(_bcTagWeight_lhemuf_Do);
	 ((TH1D *) list->FindObject("_bcTagWeight_lhemur_Up"))->Fill(_bcTagWeight_lhemur_Up);
	 ((TH1D *) list->FindObject("_bcTagWeight_lhemur_Do"))->Fill(_bcTagWeight_lhemur_Do);  */
      /* ((TH1D *) list->FindObject("_bcTagWeight_isr_Up"))->Fill(_bcTagWeight_isr_Up); 
	 ((TH1D *) list->FindObject("_bcTagWeight_isr_Do"))->Fill(_bcTagWeight_isr_Do);
	 ((TH1D *) list->FindObject("_bcTagWeight_fsr_Up"))->Fill(_bcTagWeight_fsr_Up);
	 ((TH1D *) list->FindObject("_bcTagWeight_fsr_Do"))->Fill(_bcTagWeight_fsr_Do);  */
      /* ((TH1D *) list->FindObject("_bcTagWeight_xdyb_Up"))->Fill(_bcTagWeight_xdyb_Up); 
	 ((TH1D *) list->FindObject("_bcTagWeight_xdyb_Do"))->Fill(_bcTagWeight_xdyb_Do);
	 ((TH1D *) list->FindObject("_bcTagWeight_xdyc_Up"))->Fill(_bcTagWeight_xdyc_Up);
	 ((TH1D *) list->FindObject("_bcTagWeight_xdyc_Do"))->Fill(_bcTagWeight_xdyc_Do);  */
      /* ((TH1D *) list->FindObject("_bcTagWeight_xwjc_Up"))->Fill(_bcTagWeight_xwjc_Up); 
	 ((TH1D *) list->FindObject("_bcTagWeight_xwjc_Do"))->Fill(_bcTagWeight_xwjc_Do);  */
      /* ((TH1D *) list->FindObject("_bcTagWeight_jes_Up"))->Fill(_bcTagWeight_jes_Up); 
	 ((TH1D *) list->FindObject("_bcTagWeight_jes_Do"))->Fill(_bcTagWeight_jes_Do);
	 ((TH1D *) list->FindObject("_bcTagWeight_jer_Up"))->Fill(_bcTagWeight_jer_Up);
	 ((TH1D *) list->FindObject("_bcTagWeight_jer_Do"))->Fill(_bcTagWeight_jer_Do);  */

      //Theory weights
      ((TH1D *) list->FindObject("_q2weight_Up"))->Fill(_q2weight_Up);
      ((TH1D *) list->FindObject("_q2weight_Do"))->Fill(_q2weight_Do);
      ((TH1D *) list->FindObject("_pdfweight_Up"))->Fill(_pdfweight_Up);
      ((TH1D *) list->FindObject("_pdfweight_Do"))->Fill(_pdfweight_Do);
      ((TH1D *) list->FindObject("_ISRweight_Up"))->Fill(_ISRweight_Up);
      ((TH1D *) list->FindObject("_ISRweight_Do"))->Fill(_ISRweight_Do);
      ((TH1D *) list->FindObject("_FSRweight_Up"))->Fill(_FSRweight_Up);
      ((TH1D *) list->FindObject("_FSRweight_Do"))->Fill(_FSRweight_Do);
    }
  }

 
  return;
}


//_____________________________________________________________________________
bool KinAna::FillCFHists(TList *list, string hist_extn, bool isMu, double value, double wt, double wt_nobtag){
  
  ((TH1D *) list->FindObject(Form("_cutflow_data%s",hist_extn.c_str())))->Fill(value);
  if(isMu){
    ((TH1D *) list->FindObject(Form("_cutflowUS_mu%s",hist_extn.c_str())))->Fill(value);
    ((TH1D *) list->FindObject(Form("_cutflow_mu%s",hist_extn.c_str())))->Fill(value, wt);
    ((TH1D *) list->FindObject(Form("_cutflow5%s",hist_extn.c_str())))->Fill(value, wt_nobtag);
  }else{
    ((TH1D *) list->FindObject(Form("_cutflowUS_ele%s",hist_extn.c_str())))->Fill(value);
    ((TH1D *) list->FindObject(Form("_cutflow_ele%s",hist_extn.c_str())))->Fill(value, wt);
  }

  return true;
}


//_____________________________________________________________________________
bool KinAna::FillCTHists(TList *list, string hist_extn, bool isMu, double wt, 
			  int count_cJetsIncL, int count_cJetsIncM, int count_cJetsIncT,
			  bool isIncL, bool isIncM, bool isIncT,
			  double ctagLwt, double ctagMwt, double ctagTwt){
  
  
  string lep = (isMu) ? "mu" : "ele";
  
  if(!isData){    
    
    if(count_cJetsIncL > 0){
      if(isIncL && isIncM && isIncT){
	((TH1D *) list->FindObject(Form("_ct_yLyMyT_mjj_%s%s",lep.c_str(),hist_extn.c_str())))->Fill((cjhadAF+sjhadAF).M(), ctagLwt*wt);
	((TH1D *) list->FindObject(Form("_ctagWeight_yLyMyT%s",hist_extn.c_str())))->Fill(ctagLwt);
      }
      if(isIncL && isIncM && !isIncT){
	((TH1D *) list->FindObject(Form("_ct_yLyMnT_mjj_%s%s",lep.c_str(),hist_extn.c_str())))->Fill((cjhadAF+sjhadAF).M(), ctagLwt*wt);
	((TH1D *) list->FindObject(Form("_ctagWeight_yLyMnT%s",hist_extn.c_str())))->Fill(ctagLwt);	
      }
      if(isIncL && !isIncM && isIncT){
	((TH1D *) list->FindObject(Form("_ct_yLnMyT_mjj_%s%s",lep.c_str(),hist_extn.c_str())))->Fill((cjhadAF+sjhadAF).M(), ctagLwt*wt);
	((TH1D *) list->FindObject(Form("_ctagWeight_yLnMyT%s",hist_extn.c_str())))->Fill(ctagLwt);	
      }
      if(isIncL && !isIncM && !isIncT){
	((TH1D *) list->FindObject(Form("_ct_yLnMnT_mjj_%s%s",lep.c_str(),hist_extn.c_str())))->Fill((cjhadAF+sjhadAF).M(), ctagLwt*wt);
	((TH1D *) list->FindObject(Form("_ctagWeight_yLnMnT%s",hist_extn.c_str())))->Fill(ctagLwt);		
      }
    }//count_cJetsIncL>0

    if(count_cJetsIncM > 0){
      if(isIncM && isIncT){
	((TH1D *) list->FindObject(Form("_ct_yMyT_mjj_%s%s",lep.c_str(),hist_extn.c_str())))->Fill((cjhadAF+sjhadAF).M(), ctagMwt*wt);
	((TH1D *) list->FindObject(Form("_ctagWeight_yMyT%s",hist_extn.c_str())))->Fill(ctagMwt);		
      }
      if(isIncM && !isIncT){	
	((TH1D *) list->FindObject(Form("_ct_yMnT_mjj_%s%s",lep.c_str(),hist_extn.c_str())))->Fill((cjhadAF+sjhadAF).M(), ctagMwt*wt);
	((TH1D *) list->FindObject(Form("_ctagWeight_yMnT%s",hist_extn.c_str())))->Fill(ctagMwt);		
      }
    }//count_cJetsIncM>0

    if(count_cJetsIncT > 0){
      if(isIncT){
	((TH1D *) list->FindObject(Form("_ct_yT_mjj_%s%s",lep.c_str(),hist_extn.c_str())))->Fill((cjhadAF+sjhadAF).M(), ctagTwt*wt);
	((TH1D *) list->FindObject(Form("_ctagWeight_yT%s",hist_extn.c_str())))->Fill(ctagTwt);		
      }
    }//count_cJetsIncT>0
    
  }//isMC
  
  //Inclusive categorization
  if(count_cJetsIncL > 0){
    ((TH1D *) list->FindObject(Form("_ct_IncL_mjj_%s%s",lep.c_str(),hist_extn.c_str())))->Fill((cjhadAF+sjhadAF).M(), ctagLwt*wt);
    ((TH1D *) list->FindObject(Form("_ctagWeight_IncL%s",hist_extn.c_str())))->Fill(ctagLwt);	
  }
  if(count_cJetsIncM > 0){
    ((TH1D *) list->FindObject(Form("_ct_IncM_mjj_%s%s",lep.c_str(),hist_extn.c_str())))->Fill((cjhadAF+sjhadAF).M(), ctagMwt*wt);
    ((TH1D *) list->FindObject(Form("_ctagWeight_IncM%s",hist_extn.c_str())))->Fill(ctagMwt);  
  }
  if(count_cJetsIncT > 0){
    ((TH1D *) list->FindObject(Form("_ct_IncT_mjj_%s%s",lep.c_str(),hist_extn.c_str())))->Fill((cjhadAF+sjhadAF).M(), ctagTwt*wt);
    ((TH1D *) list->FindObject(Form("_ctagWeight_IncT%s",hist_extn.c_str())))->Fill(ctagTwt);  
  }
  
  //Exclusive categorization
  if(count_cJetsIncT> 0){
    ((TH1D *) list->FindObject(Form("_ct_ExcT_mjj_%s%s",lep.c_str(),hist_extn.c_str())))->Fill((cjhadAF+sjhadAF).M(), ctagTwt*wt);
    ((TH1D *) list->FindObject(Form("_ctagWeight_ExcT%s",hist_extn.c_str())))->Fill(ctagTwt);		
  }
  else if(count_cJetsIncM> 0){ 
    ((TH1D *) list->FindObject(Form("_ct_ExcM_mjj_%s%s",lep.c_str(),hist_extn.c_str())))->Fill((cjhadAF+sjhadAF).M(), ctagMwt*wt);
    ((TH1D *) list->FindObject(Form("_ctagWeight_ExcM%s",hist_extn.c_str())))->Fill(ctagMwt);		
  }
  else if(count_cJetsIncL > 0){ 
    ((TH1D *) list->FindObject(Form("_ct_ExcL_mjj_%s%s",lep.c_str(),hist_extn.c_str())))->Fill((cjhadAF+sjhadAF).M(), ctagLwt*wt);
    ((TH1D *) list->FindObject(Form("_ctagWeight_ExcL%s",hist_extn.c_str())))->Fill(ctagLwt);		
  }
  else{
    ((TH1D *) list->FindObject(Form("_ct_Exc0_mjj_%s%s",lep.c_str(),hist_extn.c_str())))->Fill((cjhadAF+sjhadAF).M(), wt);
    ((TH1D *) list->FindObject(Form("_ctagWeight_Exc0%s",hist_extn.c_str())))->Fill(wt);		
  }
  
  return true;
}

//_____________________________________________________________________________
bool KinAna::FillKFHists(TList *list, string hist_extn, bool isMu, double wt, double wt_nobtag){
  
  string lep = (isMu) ? "mu" : "ele";
  

  ((TH1D *) list->FindObject(Form("_kb_pt_%s%s",lep.c_str(),hist_extn.c_str())))->Fill(leptonAF.Pt(), wt);
  ((TH1D *) list->FindObject(Form("_kb_eta_%s%s",lep.c_str(),hist_extn.c_str())))->Fill(leptonAF.Eta(), wt);
  ((TH1D *) list->FindObject(Form("_kb_phi_%s%s",lep.c_str(),hist_extn.c_str())))->Fill(leptonAF.Phi(), wt);

  ((TH1D *) list->FindObject(Form("_kb_pt_%s_jets%s",lep.c_str(),hist_extn.c_str())))->Fill(bjlepAF.Pt(), wt);
  ((TH1D *) list->FindObject(Form("_kb_pt_%s_jets%s",lep.c_str(),hist_extn.c_str())))->Fill(bjhadAF.Pt(), wt);
  ((TH1D *) list->FindObject(Form("_kb_pt_%s_jets%s",lep.c_str(),hist_extn.c_str())))->Fill(cjhadAF.Pt(), wt);
  ((TH1D *) list->FindObject(Form("_kb_pt_%s_jets%s",lep.c_str(),hist_extn.c_str())))->Fill(sjhadAF.Pt(), wt);

  ((TH1D *) list->FindObject(Form("_kb_eta_%s_jets%s",lep.c_str(),hist_extn.c_str())))->Fill(bjlepAF.Eta(), wt);
  ((TH1D *) list->FindObject(Form("_kb_eta_%s_jets%s",lep.c_str(),hist_extn.c_str())))->Fill(bjhadAF.Eta(), wt);
  ((TH1D *) list->FindObject(Form("_kb_eta_%s_jets%s",lep.c_str(),hist_extn.c_str())))->Fill(cjhadAF.Eta(), wt);
  ((TH1D *) list->FindObject(Form("_kb_eta_%s_jets%s",lep.c_str(),hist_extn.c_str())))->Fill(sjhadAF.Eta(), wt);
	    
  ((TH1D *) list->FindObject(Form("_kb_phi_%s_jets%s",lep.c_str(),hist_extn.c_str())))->Fill(bjlepAF.Phi(), wt);
  ((TH1D *) list->FindObject(Form("_kb_phi_%s_jets%s",lep.c_str(),hist_extn.c_str())))->Fill(bjhadAF.Phi(), wt);
  ((TH1D *) list->FindObject(Form("_kb_phi_%s_jets%s",lep.c_str(),hist_extn.c_str())))->Fill(cjhadAF.Phi(), wt);
  ((TH1D *) list->FindObject(Form("_kb_phi_%s_jets%s",lep.c_str(),hist_extn.c_str())))->Fill(sjhadAF.Phi(), wt);

  ((TH1D *) list->FindObject(Form("_kb_pt_%s_met%s",lep.c_str(),hist_extn.c_str())))->Fill(neutrinoAF.Pt(), wt);
  ((TH1D *) list->FindObject(Form("_kb_phi_%s_met%s",lep.c_str(),hist_extn.c_str())))->Fill(neutrinoAF.Phi(), wt);
  ((TH1D *) list->FindObject(Form("_kb_njet_%s%s",lep.c_str(),hist_extn.c_str())))->Fill(nJet, wt);
  //((TH1D *) list->FindObject(Form("_kb_nbjet_%s%s",lep.c_str(),hist_extn.c_str())))->Fill(selector->bJets.size(), wt);
  
  ((TH1D *) list->FindObject(Form("_kb_mjj_%s%s",lep.c_str(),hist_extn.c_str())))->Fill((cjhadAF+sjhadAF).M(), wt);
  //((TH1D *) list->FindObject(Form("_kb_mjj_bf_%s%s",lep.c_str(),hist_extn.c_str())))->Fill((cjhadBF+sjhadBF).M(), wt);

  // if(_kFType == 13 and hist_extn == ""){
      
  //   ((TH1D *) list->FindObject(Form("_bjet1Pt_AF_%s",lep.c_str())))->Fill(bjhadAF.Pt(), wt);
  //   ((TH1D *) list->FindObject(Form("_bjet1Pt_BF_%s",lep.c_str())))->Fill(bjhadBF.Pt(), wt);
  //   ((TH1D *) list->FindObject(Form("_bjet2Pt_AF_%s",lep.c_str())))->Fill(bjlepAF.Pt(), wt);
  //   ((TH1D *) list->FindObject(Form("_bjet2Pt_BF_%s",lep.c_str())))->Fill(bjlepBF.Pt(), wt);
      
  //   ((TH1D *) list->FindObject(Form("_ljet1Pt_AF_%s",lep.c_str())))->Fill( ((cjhadAF.Pt()>sjhadAF.Pt()) ? cjhadAF.Pt() : sjhadAF.Pt()), wt);
  //   ((TH1D *) list->FindObject(Form("_ljet1Pt_BF_%s",lep.c_str())))->Fill( ((cjhadAF.Pt()>sjhadAF.Pt()) ? cjhadBF.Pt() : sjhadBF.Pt()), wt);
  //   ((TH1D *) list->FindObject(Form("_ljet2Pt_AF_%s",lep.c_str())))->Fill( ((cjhadAF.Pt()>sjhadAF.Pt()) ? sjhadAF.Pt() : cjhadAF.Pt()), wt);
  //   ((TH1D *) list->FindObject(Form("_ljet2Pt_BF_%s",lep.c_str())))->Fill( ((cjhadAF.Pt()>sjhadAF.Pt()) ? sjhadBF.Pt() : cjhadBF.Pt()), wt);
      
  // }

  // }
  
  return true;
}

bool KinAna::GetWtRatio(TString systname, TString DDzone, string hist_extn){
  
  // TH1D *hWtBefore = (TH1D *)fRefF->Get(Form("%s/%s/%s/_wt_before%s",fSample.Data(),systname.Data(), DDzone.Data(), hist_extn.c_str()));
  // TH1D *hWtAfter = (TH1D *)fRefF->Get(Form("%s/%s/%s/_wt_after%s",fSample.Data(),systname.Data(), DDzone.Data(), hist_extn.c_str()));
  TH1D *hWtBefore = (TH1D *)fRefF->Get(Form("%s/%s/Iso/_wt_before",fSample.Data(),systname.Data()));
  TH1D *hWtAfter = (TH1D *)fRefF->Get(Form("%s/%s/Iso/_wt_after",fSample.Data(),systname.Data()));
  
  wt_before = hWtBefore->GetBinContent(nJet+1);
  wt_after = hWtAfter->GetBinContent(nJet+1);
  if(!TMath::AreEqualAbs(wt_after,0.0,1.0e-4))
    wt_ratio = wt_before/wt_after;
  else
    wt_ratio = 1.0;

  return true;
}

//_____________________________________________________________________________
bool KinAna::GetCTagWt(char CType, TString systname, double& ctagwt){
  
  if(CType=='L' or CType=='M' or CType=='T'){
    // ctagwt = _cTagLWeight ; 
    // if(systname == "bctag1up") ctagwt = _cTagLWeight_bc1_Up ; if(systname == "bctag1down") ctagwt = _cTagLWeight_bc1_Do ; 
    // if(systname == "bctag2up") ctagwt = _cTagLWeight_bc2_Up ; if(systname == "bctag2down") ctagwt = _cTagLWeight_bc2_Do ; 
    // if(systname == "bctag3up") ctagwt = _cTagLWeight_bc3_Up ; if(systname == "bctag3down") ctagwt = _cTagLWeight_bc3_Do ; 
    ctagwt = _bcTagWeight ;
    if(systname == "bcstatup") ctagwt = _bcTagWeight_stat_Up ;		if(systname == "bcstatdown") ctagwt = _bcTagWeight_stat_Do ;
    if(systname == "puup") ctagwt = _bcTagWeight_pu_Up ;		if(systname == "pudown") ctagwt = _bcTagWeight_pu_Do ; 
    if(systname == "eleeffup") ctagwt = _bcTagWeight_eleid_Up ;	if(systname == "eleeffdown") ctagwt = _bcTagWeight_eleid_Do ; 
    if(systname == "mueffup") ctagwt = _bcTagWeight_muid_Up ;		if(systname == "mueffdown") ctagwt = _bcTagWeight_muid_Do ; 
    if(systname == "bclhemufup") ctagwt = _bcTagWeight_lhemuf_Up ;	if(systname == "bclhemufdown") ctagwt = _bcTagWeight_lhemuf_Do ; 
    if(systname == "bclhemurup") ctagwt = _bcTagWeight_lhemur_Up ;	if(systname == "bclhemurdown") ctagwt = _bcTagWeight_lhemur_Do ; 
    if(systname == "isrup") ctagwt = _bcTagWeight_isr_Up ;		if(systname == "isrdown") ctagwt = _bcTagWeight_isr_Do ; 
    if(systname == "fsrup") ctagwt = _bcTagWeight_fsr_Up ;		if(systname == "fsrdown") ctagwt = _bcTagWeight_fsr_Do ; 
    if(systname == "bcxdyup") ctagwt = _bcTagWeight_xdy_Up ;		if(systname == "bcxdydown") ctagwt = _bcTagWeight_xdy_Do ; 
    if(systname == "bcxstup") ctagwt = _bcTagWeight_xst_Up ;		if(systname == "bcxstdown") ctagwt = _bcTagWeight_xst_Do ; 
    if(systname == "bcxwjup") ctagwt = _bcTagWeight_xwj_Up ;		if(systname == "bcxwjdown") ctagwt = _bcTagWeight_xwj_Do ; 
    if(systname == "bcxttup") ctagwt = _bcTagWeight_xtt_Up ;		if(systname == "bcxttdown") ctagwt = _bcTagWeight_xtt_Do ; 
    if(systname == "jecup") ctagwt = _bcTagWeight_jes_Up ;		if(systname == "jecdown") ctagwt = _bcTagWeight_jes_Do ; 
    if(systname == "jerup") ctagwt = _bcTagWeight_jer_Up ;		if(systname == "jerdown") ctagwt = _bcTagWeight_jer_Do ; 
    if(systname == "bcbfragup") ctagwt = _bcTagWeight_bfrag_Up ;	if(systname == "bcbfragdown") ctagwt = _bcTagWeight_bfrag_Do ; 
  }
  
  return true;
}

//_____________________________________________________________________________
bool KinAna::GetCombinedWt(TString systname, double& combined_muwt, double& combined_muwt_nobtagwt, double& combined_elewt, double& combined_elewt_nobtagwt){

  double puwt = _PUWeight ; if(systname == "puup") puwt = _PUWeight_Up ; if(systname == "pudown") puwt = _PUWeight_Do ;
  double prefirewt = _prefireWeight ; if(systname == "prefireup")  prefirewt = _prefireWeight_Up ; if(systname == "prefiredown") prefirewt = _prefireWeight_Do ;
  double muwt = _muEffWeight ; if(systname == "mueffup") muwt = _muEffWeight_Up ; if(systname == "mueffdown") muwt = _muEffWeight_Do ; 
  double elewt = _eleEffWeight ; if(systname == "eleeffup") elewt = _eleEffWeight_Up ; if(systname == "eleeffdown") elewt = _eleEffWeight_Do ; 
  double pujetidwt = _PUJetIDWeight ; if(systname == "pujetidup") pujetidwt = _PUJetIDWeight_Up ; if(systname == "pujetidup") pujetidwt = _PUJetIDWeight_Do ; 

  // double btagwt = _bTagWeight ; if(systname == "btagbup") btagwt = _bTagWeight_b_Up ; if(systname == "btagbdown") btagwt = _bTagWeight_b_Do ; 
  // if(systname == "btaglup") btagwt = _bTagWeight_l_Up ; if(systname == "btagldown") btagwt = _bTagWeight_l_Do ; 
  // if(systname == "bctag1up") btagwt = _bTagWeight_bc1_Up ; if(systname == "bctag1down") btagwt = _bTagWeight_bc1_Do ; 
  // if(systname == "bctag2up") btagwt = _bTagWeight_bc2_Up ; if(systname == "bctag2down") btagwt = _bTagWeight_bc2_Do ; 
  // if(systname == "bctag3up") btagwt = _bTagWeight_bc3_Up ; if(systname == "bctag3down") btagwt = _bTagWeight_bc3_Do ; 

  //CShapeCalib EOY
  // "bcstatup", "bcstatdown",
  // "bclhemufup", "bclhemufdown", "bclhemurup", "bclhemurdown",
  // "bcxdyup", "bcxdydown", "bcxstup", "bcxstdown", 
  // "bcxwjup", "bcxwjdown", "bcxttup", "bcxttdown", 
  // "bcbfragup", "bcbfragdown" //16
  
  //CShapeCalib EOY
  double btagwt = _bcTagWeight ; if(systname == "bcstatup") btagwt = _bcTagWeight_stat_Up ; if(systname == "bcstatdown") btagwt = _bcTagWeight_stat_Do ;
  if(systname == "puup") btagwt = _bcTagWeight_pu_Up ; if(systname == "pudown") btagwt = _bcTagWeight_pu_Do ; 
  if(systname == "eleeffup") btagwt = _bcTagWeight_eleid_Up ; if(systname == "eleeffdown") btagwt = _bcTagWeight_eleid_Do ; 
  if(systname == "mueffup") btagwt = _bcTagWeight_muid_Up ; if(systname == "mueffdown") btagwt = _bcTagWeight_muid_Do ; 
  if(systname == "bclhemufup") btagwt = _bcTagWeight_lhemuf_Up ; if(systname == "bclhemufdown") btagwt = _bcTagWeight_lhemuf_Do ; 
  if(systname == "bclhemurup") btagwt = _bcTagWeight_lhemur_Up ; if(systname == "bclhemurdown") btagwt = _bcTagWeight_lhemur_Do ; 
  if(systname == "isrup") btagwt = _bcTagWeight_isr_Up ; if(systname == "isrdown") btagwt = _bcTagWeight_isr_Do ; 
  if(systname == "fsrup") btagwt = _bcTagWeight_fsr_Up ; if(systname == "fsrdown") btagwt = _bcTagWeight_fsr_Do ; 
  if(systname == "bcxdyup") btagwt = _bcTagWeight_xdy_Up ; if(systname == "bcxdydown") btagwt = _bcTagWeight_xdy_Do ; 
  if(systname == "bcxstup") btagwt = _bcTagWeight_xst_Up ; if(systname == "bcxstdown") btagwt = _bcTagWeight_xst_Do ; 
  if(systname == "bcxwjup") btagwt = _bcTagWeight_xwj_Up ; if(systname == "bcxwjdown") btagwt = _bcTagWeight_xwj_Do ; 
  if(systname == "bcxttup") btagwt = _bcTagWeight_xtt_Up ; if(systname == "bcxttdown") btagwt = _bcTagWeight_xtt_Do ; 
  if(systname == "jecup") btagwt = _bcTagWeight_jes_Up ; if(systname == "jecdown") btagwt = _bcTagWeight_jes_Do ; 
  if(systname == "jerup") btagwt = _bcTagWeight_jer_Up ; if(systname == "jerdown") btagwt = _bcTagWeight_jer_Do ; 
  if(systname == "bcbfragup") btagwt = _bcTagWeight_bfrag_Up ; if(systname == "bcbfragdown") btagwt = _bcTagWeight_bfrag_Do ; 
  
  // CShapeCalib UL
  // "bcstatup", "bcstatdown",
  // "bcintpup", "bcintpdown", "bcextpup", "bcextpdown",
  // "bclhemufup", "bclhemufdown", "bclhemurup", "bclhemurdown",
  // "bcxdybup", "bcxdybdown", "bcxdycup", "bcxdycdown",
  // "bcxwjcup", "bcxwjcdown"//16
  
  // CShapeCalib UL
  // double btagwt = _bcTagWeight ; if(systname == "bcstatup") btagwt = _bcTagWeight_stat_Up ; if(systname == "bcstatdown") btagwt = _bcTagWeight_stat_Do ;
  // if(systname == "puup") btagwt = _bcTagWeight_pu_Up ; if(systname == "pudown") btagwt = _bcTagWeight_pu_Do ; 
  // if(systname == "bcintpup") btagwt = _bcTagWeight_intp_Up ; if(systname == "bcintpdown") btagwt = _bcTagWeight_intp_Do ; 
  // if(systname == "bcextpup") btagwt = _bcTagWeight_extp_Up ; if(systname == "bcextpdown") btagwt = _bcTagWeight_extp_Do ; 
  // if(systname == "bclhemufup") btagwt = _bcTagWeight_lhemuf_Up ; if(systname == "bclhemufdown") btagwt = _bcTagWeight_lhemuf_Do ; 
  // if(systname == "bclhemurup") btagwt = _bcTagWeight_lhemur_Up ; if(systname == "bclhemurdown") btagwt = _bcTagWeight_lhemur_Do ; 
  // if(systname == "isrup") btagwt = _bcTagWeight_isr_Up ; if(systname == "isrdown") btagwt = _bcTagWeight_isr_Do ; 
  // if(systname == "fsrup") btagwt = _bcTagWeight_fsr_Up ; if(systname == "fsrdown") btagwt = _bcTagWeight_fsr_Do ; 
  // if(systname == "bcxdybup") btagwt = _bcTagWeight_xdyb_Up ; if(systname == "bcxdybdown") btagwt = _bcTagWeight_xdyb_Do ; 
  // if(systname == "bcxdycup") btagwt = _bcTagWeight_xdyc_Up ; if(systname == "bcxdycdown") btagwt = _bcTagWeight_xdyc_Do ; 
  // if(systname == "bcxwjcup") btagwt = _bcTagWeight_xwjc_Up ; if(systname == "bcxwjcdown") btagwt = _bcTagWeight_xwjc_Do ; 
  // if(systname == "jecup") btagwt = _bcTagWeight_jes_Up ; if(systname == "jecdown") btagwt = _bcTagWeight_jes_Do ; 
  // if(systname == "jerup") btagwt = _bcTagWeight_jer_Up ; if(systname == "jerdown") btagwt = _bcTagWeight_jer_Do ; 
  
  double pdfwt = 1.0 ; if(systname == "pdfup") pdfwt = _pdfweight_Up ; if(systname == "pdfdown") pdfwt = _pdfweight_Do ;
  double q2wt = 1.0 ; if(systname == "q2up") q2wt = _q2weight_Up ; if(systname == "q2down") q2wt = _q2weight_Do ;
  double isrwt = 1.0 ; if(systname == "isrup") isrwt = _ISRweight_Up ; if(systname == "isrdown") isrwt = _ISRweight_Do ;
  double fsrwt = 1.0 ; if(systname == "fsrup") fsrwt = _FSRweight_Up ; if(systname == "fsrdown") fsrwt = _FSRweight_Do ;
  
  combined_muwt = _sampleWeight * prefirewt * puwt * muwt * pujetidwt * pdfwt * q2wt * isrwt * fsrwt * btagwt * wt_ratio;
  combined_muwt_nobtagwt = _sampleWeight * prefirewt * puwt * muwt * pujetidwt * pdfwt * q2wt * isrwt * fsrwt * wt_ratio;
  combined_elewt = _sampleWeight * prefirewt * puwt * elewt * pujetidwt * pdfwt * q2wt * isrwt * fsrwt * btagwt * wt_ratio;
  combined_elewt_nobtagwt = _sampleWeight * prefirewt * puwt * elewt * pujetidwt * pdfwt * q2wt * isrwt * fsrwt * wt_ratio;

  //cout<<"combined_muwt : " << combined_muwt << endl;
  
  return true;
}

//_____________________________________________________________________________
bool KinAna::FillCTagObs(){
  
  count_cJetsIncL   = 0;
  count_cJetsIncM   = 0;
  count_cJetsIncT   = 0;
 
  bool isIncL = false;
  bool isIncM = false;
  bool isIncT = false;
  
  float ctagTh_CvsL_L = (useDeepCSVbTag) ? btag_cut_DeepCSV  : ctag_CvsL_L_cut  ;
  float ctagTh_CvsB_L = (useDeepCSVbTag) ? btag_cut_DeepCSV  : ctag_CvsB_L_cut  ;
  float ctagTh_CvsL_M = (useDeepCSVbTag) ? btag_cut_DeepCSV  : ctag_CvsL_M_cut  ;
  float ctagTh_CvsB_M = (useDeepCSVbTag) ? btag_cut_DeepCSV  : ctag_CvsB_M_cut  ;
  float ctagTh_CvsL_T = (useDeepCSVbTag) ? btag_cut_DeepCSV  : ctag_CvsL_T_cut  ;
  float ctagTh_CvsB_T = (useDeepCSVbTag) ? btag_cut_DeepCSV  : ctag_CvsB_T_cut  ;

  //cout<<"Thresh : ctagTh_CvsL_L : " << ctagTh_CvsL_L <<", ctagTh_CvsB_L : "<<ctag_CvsB_L_cut<<endl;
  
  for (unsigned int ijet = 0; ijet < 2; ijet++){
    
    float jet_CvsL = 0.0;
    float jet_CvsB = 0.0;
    if(ijet==0) { //cjhad
      jet_CvsL = cjhadCvsLdisc;
      jet_CvsB = cjhadCvsBdisc;
    }else{ //sjhad
      jet_CvsL = sjhadCvsLdisc;
      jet_CvsB = sjhadCvsBdisc;
    }   

    if(jet_CvsL > ctagTh_CvsL_L and jet_CvsB > ctagTh_CvsB_L) {
      isIncL = true;
      count_cJetsIncL++;
    }
    if(jet_CvsL > ctagTh_CvsL_M and jet_CvsB > ctagTh_CvsB_M){
      isIncM = true;
      count_cJetsIncM++;
    }
    if(jet_CvsL > ctagTh_CvsL_T and jet_CvsB > ctagTh_CvsB_T){
      isIncT = true;
      count_cJetsIncT++;	
    }
  }//jet loop
  //cout<<"count_cJetsIncL : " << count_cJetsIncL <<", count_cJetsIncM : " << count_cJetsIncM <<", count_cJetsIncT : " << count_cJetsIncT << endl;
  
  double combined_muwt = 1.0,  combined_muwt_nobtagwt = 1.0, combined_elewt = 1.0, combined_elewt_nobtagwt = 1.0;
  double ctagLwt = 1.0, ctagMwt = 1.0, ctagTwt = 1.0;
  if(hasKFMu and muonIsoCut){
    for(int isyst=0;isyst<fNSyst;isyst++){	
      TString systname = fSystList[isyst];
      //GetCombinedWt(systname, combined_muwt, combined_muwt_nobtagwt, combined_elewt, combined_elewt_nobtagwt);
      GetCTagWt('L', systname, ctagLwt); GetCTagWt('M', systname, ctagMwt); GetCTagWt('T', systname, ctagTwt);
      if(!isLowMET){
	////////////////// base ////////////////////////////
	TList *lIso = (TList *)fFileDir[isyst*fNDDReg + 0]->GetList();
	GetWtRatio(systname, fFileDir[isyst*fNDDReg + 0]->GetName(),"");
	GetCombinedWt(systname, combined_muwt, combined_muwt_nobtagwt, combined_elewt, combined_elewt_nobtagwt);
	if(count_cJetsIncL > 0) FillCFHists(lIso, "", true, 7.0, ctagLwt*combined_muwt_nobtagwt, ctagLwt*combined_muwt);
	if(count_cJetsIncM > 0) FillCFHists(lIso, "", true, 8.0, ctagMwt*combined_muwt_nobtagwt, ctagMwt*combined_muwt);
	if(count_cJetsIncT > 0) FillCFHists(lIso, "", true, 9.0, ctagTwt*combined_muwt_nobtagwt, ctagTwt*combined_muwt);
	FillCTHists(lIso,"", true, combined_muwt_nobtagwt, count_cJetsIncL, count_cJetsIncM, count_cJetsIncT, isIncL, isIncM, isIncT, ctagLwt, ctagMwt, ctagTwt);
	/////////////////////////////////////////////////////
      }else{
	TList *lLowMET = (TList *)fFileDir[isyst*fNDDReg + 1]->GetList();
	GetWtRatio(systname, fFileDir[isyst*fNDDReg + 1]->GetName(),"_lmet");
	GetCombinedWt(systname, combined_muwt, combined_muwt_nobtagwt, combined_elewt, combined_elewt_nobtagwt);
	if(count_cJetsIncL > 0) FillCFHists(lLowMET,"_lmet", true, 7.0, ctagLwt*combined_muwt_nobtagwt, ctagLwt*combined_muwt);
	if(count_cJetsIncM > 0) FillCFHists(lLowMET,"_lmet", true, 8.0, ctagMwt*combined_muwt_nobtagwt, ctagMwt*combined_muwt);
	if(count_cJetsIncT > 0) FillCFHists(lLowMET,"_lmet", true, 9.0, ctagTwt*combined_muwt_nobtagwt, ctagTwt*combined_muwt);
	FillCTHists(lLowMET,"_lmet", true, combined_muwt_nobtagwt, count_cJetsIncL, count_cJetsIncM, count_cJetsIncT, isIncL, isIncM, isIncT, ctagLwt, ctagMwt, ctagTwt);
      }//lowmet
    }//syst loop
  }//muon iso
  if(hasKFMu and muonNonIsoCut){
    for(int isyst=0;isyst<fNSyst;isyst++){	
      TString systname = fSystList[isyst];
      //GetCombinedWt(systname, combined_muwt, combined_muwt_nobtagwt, combined_elewt, combined_elewt_nobtagwt);
      GetCTagWt('L', systname, ctagLwt); GetCTagWt('M', systname, ctagMwt); GetCTagWt('T', systname, ctagTwt);
      if(!isLowMET){
	TList *lNonIso = (TList *)fFileDir[isyst*fNDDReg + 2]->GetList();
	GetWtRatio(systname, fFileDir[isyst*fNDDReg + 2]->GetName(),"_noniso");
	GetCombinedWt(systname, combined_muwt, combined_muwt_nobtagwt, combined_elewt, combined_elewt_nobtagwt);
	if(count_cJetsIncL > 0) FillCFHists(lNonIso,"_noniso", true, 7.0, ctagLwt*combined_muwt_nobtagwt, ctagLwt*combined_muwt);
	if(count_cJetsIncM > 0) FillCFHists(lNonIso,"_noniso", true, 8.0, ctagMwt*combined_muwt_nobtagwt, ctagMwt*combined_muwt);
	if(count_cJetsIncT > 0) FillCFHists(lNonIso,"_noniso", true, 9.0, ctagTwt*combined_muwt_nobtagwt, ctagTwt*combined_muwt);
	FillCTHists(lNonIso,"_noniso", true, combined_muwt_nobtagwt, count_cJetsIncL, count_cJetsIncM, count_cJetsIncT, isIncL, isIncM, isIncT, ctagLwt, ctagMwt, ctagTwt);
	/////////////////////////////////////////////////////
      }else{
	TList *lNonIsoLowMET = (TList *)fFileDir[isyst*fNDDReg + 3]->GetList();
	GetWtRatio(systname, fFileDir[isyst*fNDDReg + 3]->GetName(),"_noniso_lmet");
	GetCombinedWt(systname, combined_muwt, combined_muwt_nobtagwt, combined_elewt, combined_elewt_nobtagwt);
	if(count_cJetsIncL > 0) FillCFHists(lNonIsoLowMET,"_noniso_lmet", true, 7.0, ctagLwt*combined_muwt_nobtagwt, ctagLwt*combined_muwt);
	if(count_cJetsIncM > 0) FillCFHists(lNonIsoLowMET,"_noniso_lmet", true, 8.0, ctagMwt*combined_muwt_nobtagwt, ctagMwt*combined_muwt);
	if(count_cJetsIncT > 0) FillCFHists(lNonIsoLowMET,"_noniso_lmet", true, 9.0, ctagTwt*combined_muwt_nobtagwt, ctagTwt*combined_muwt);
	FillCTHists(lNonIsoLowMET,"_noniso_lmet", true, combined_muwt_nobtagwt, count_cJetsIncL, count_cJetsIncM, count_cJetsIncT, isIncL, isIncM, isIncT, ctagLwt, ctagMwt, ctagTwt);
      }//lowmet
    }//syst loop
  }//muon iso
    
  if(hasKFEle and eleIsoCut){
    for(int isyst=0;isyst<fNSyst;isyst++){	
      TString systname = fSystList[isyst];
      //GetCombinedWt(systname, combined_muwt, combined_muwt_nobtagwt, combined_elewt, combined_elewt_nobtagwt);
      GetCTagWt('L', systname, ctagLwt); GetCTagWt('M', systname, ctagMwt); GetCTagWt('T', systname, ctagTwt);
      if(!isLowMET){
	////////////////// base ////////////////////////////
	TList *lIso = (TList *)fFileDir[isyst*fNDDReg + 0]->GetList();
	GetWtRatio(systname, fFileDir[isyst*fNDDReg + 0]->GetName(),"");
	GetCombinedWt(systname, combined_muwt, combined_muwt_nobtagwt, combined_elewt, combined_elewt_nobtagwt);
	if(count_cJetsIncL > 0) FillCFHists(lIso, "", false, 7.0, ctagLwt*combined_elewt_nobtagwt, 1.0);
	if(count_cJetsIncM > 0) FillCFHists(lIso, "", false, 8.0, ctagMwt*combined_elewt_nobtagwt, 1.0);
	if(count_cJetsIncT > 0) FillCFHists(lIso, "", false, 9.0, ctagTwt*combined_elewt_nobtagwt, 1.0);
	FillCTHists(lIso,"", false, combined_elewt_nobtagwt, count_cJetsIncL, count_cJetsIncM, count_cJetsIncT, isIncL, isIncM, isIncT, ctagLwt, ctagMwt, ctagTwt);
	/////////////////////////////////////////////////////
      }else{
	TList *lLowMET = (TList *)fFileDir[isyst*fNDDReg + 1]->GetList();
	GetWtRatio(systname, fFileDir[isyst*fNDDReg + 1]->GetName(),"_lmet");
	GetCombinedWt(systname, combined_muwt, combined_muwt_nobtagwt, combined_elewt, combined_elewt_nobtagwt);
	if(count_cJetsIncL > 0) FillCFHists(lLowMET,"_lmet", false, 7.0, ctagLwt*combined_elewt_nobtagwt, 1.0);
	if(count_cJetsIncM > 0) FillCFHists(lLowMET,"_lmet", false, 8.0, ctagMwt*combined_elewt_nobtagwt, 1.0);
	if(count_cJetsIncT > 0) FillCFHists(lLowMET,"_lmet", false, 9.0, ctagTwt*combined_elewt_nobtagwt, 1.0);
	FillCTHists(lLowMET,"_lmet", false, combined_elewt_nobtagwt, count_cJetsIncL, count_cJetsIncM, count_cJetsIncT, isIncL, isIncM, isIncT, ctagLwt, ctagMwt, ctagTwt);
	//FillKFHists(lLowMET,"_lmet",true,combined_muwt);
      }//lowmet
    }//syst loop
  }//muon iso
  if(hasKFEle and eleNonIsoCut){
    for(int isyst=0;isyst<fNSyst;isyst++){	
      TString systname = fSystList[isyst];
      //GetCombinedWt(systname, combined_muwt, combined_muwt_nobtagwt, combined_elewt, combined_elewt_nobtagwt);
      GetCTagWt('L', systname, ctagLwt); GetCTagWt('M', systname, ctagMwt); GetCTagWt('T', systname, ctagTwt);
      if(!isLowMET){
	TList *lNonIso = (TList *)fFileDir[isyst*fNDDReg + 2]->GetList();
	GetWtRatio(systname, fFileDir[isyst*fNDDReg + 2]->GetName(),"_noniso");
	GetCombinedWt(systname, combined_muwt, combined_muwt_nobtagwt, combined_elewt, combined_elewt_nobtagwt);
	if(count_cJetsIncL > 0) FillCFHists(lNonIso,"_noniso", false, 7.0, ctagLwt*combined_elewt_nobtagwt, 1.0);
	if(count_cJetsIncM > 0) FillCFHists(lNonIso,"_noniso", false, 8.0, ctagMwt*combined_elewt_nobtagwt, 1.0);
	if(count_cJetsIncT > 0) FillCFHists(lNonIso,"_noniso", false, 9.0, ctagTwt*combined_elewt_nobtagwt, 1.0);
	FillCTHists(lNonIso,"_noniso", false, combined_elewt_nobtagwt, count_cJetsIncL, count_cJetsIncM, count_cJetsIncT, isIncL, isIncM, isIncT, ctagLwt, ctagMwt, ctagTwt);
	/////////////////////////////////////////////////////
      }else{
	TList *lNonIsoLowMET = (TList *)fFileDir[isyst*fNDDReg + 3]->GetList();
	GetWtRatio(systname, fFileDir[isyst*fNDDReg + 3]->GetName(),"_noniso_lmet");
	GetCombinedWt(systname, combined_muwt, combined_muwt_nobtagwt, combined_elewt, combined_elewt_nobtagwt);
	if(count_cJetsIncL > 0) FillCFHists(lNonIsoLowMET,"_noniso_lmet", false, 7.0, ctagLwt*combined_elewt_nobtagwt, 1.0);
	if(count_cJetsIncM > 0) FillCFHists(lNonIsoLowMET,"_noniso_lmet", false, 8.0, ctagMwt*combined_elewt_nobtagwt, 1.0);
	if(count_cJetsIncT > 0) FillCFHists(lNonIsoLowMET,"_noniso_lmet", false, 9.0, ctagTwt*combined_elewt_nobtagwt, 1.0);
	FillCTHists(lNonIsoLowMET,"_noniso_lmet", false, combined_elewt_nobtagwt, count_cJetsIncL, count_cJetsIncM, count_cJetsIncT, isIncL, isIncM, isIncT, ctagLwt, ctagMwt, ctagTwt);
      }//lowmet
    }//syst loop
  }//muon iso
    
  return true;
}
//_____________________________________________________________________________

bool KinAna::FillKFCFObs(){
  
  double combined_muwt = 1.0,  combined_muwt_nobtagwt = 1.0, combined_elewt = 1.0, combined_elewt_nobtagwt = 1.0;


  if(systType == kBase){

    // if(ProcessKinFit((singleMu and muonIsoCut), false)){
    //   hasKFMu = true;
    if((singleMu and muonIsoCut) and !singleEle){
      
      for(int isyst=0;isyst<fNSyst;isyst++){
	
	TString systname = fSystList[isyst];
	
	if(!systname.Contains("jec") and !systname.Contains("jer") and !systname.Contains("iso20") and !systname.Contains("met") 
	   and !systname.Contains("cp5") and !systname.Contains("hdamp") and !systname.Contains("mtop") ) {

	  if(!isLowMET){

	    ////////////////// base ////////////////////////////
	    TList *lIso = (TList *)fFileDir[isyst*fNDDReg + 0]->GetList();
	    GetWtRatio(systname, fFileDir[isyst*fNDDReg + 0]->GetName(),"");
	    GetCombinedWt(systname, combined_muwt, combined_muwt_nobtagwt, combined_elewt, combined_elewt_nobtagwt);
	    //FillCFHists(TList *list, string hist_extn, bool isMu, double value, double wt, double wt_nobtagwt)
	    FillCFHists(lIso, "", true, 6.0, combined_muwt, combined_muwt_nobtagwt);
	    //FillKFHists(TList *list, string hist_extn, bool isMu, double wt);
	    FillKFHists(lIso,"",true,combined_muwt, combined_muwt_nobtagwt);
	    /////////////////////////////////////////////////////

	  }else{

	    TList *lLowMET = (TList *)fFileDir[isyst*fNDDReg + 1]->GetList();
	    GetWtRatio(systname, fFileDir[isyst*fNDDReg + 1]->GetName(),"_lmet");
	    GetCombinedWt(systname, combined_muwt, combined_muwt_nobtagwt, combined_elewt, combined_elewt_nobtagwt);
	    FillCFHists(lLowMET,"_lmet", true, 6.0, combined_muwt, combined_muwt_nobtagwt);
	    FillKFHists(lLowMET,"_lmet",true,combined_muwt,combined_muwt_nobtagwt);

	  }//lowmet
	}//not jec jer
      }//syst loop
    }//muon iso
	
    // if(ProcessKinFit((singleMu and muonNonIsoCut), false)){      
    //   hasKFMu = true;
    if((singleMu and muonNonIsoCut) and !singleEle){      


      for(int isyst=0;isyst<fNSyst;isyst++){
	
	TString systname = fSystList[isyst];
	
	if(!systname.Contains("jec") and !systname.Contains("jer") and !systname.Contains("iso20") and !systname.Contains("met")
	   and !systname.Contains("cp5") and !systname.Contains("hdamp") and !systname.Contains("mtop") ) {
	
	  if(!isLowMET){

	    TList *lNonIso = (TList *)fFileDir[isyst*fNDDReg + 2]->GetList();
	    GetWtRatio(systname, fFileDir[isyst*fNDDReg + 2]->GetName(),"_noniso");
	    GetCombinedWt(systname, combined_muwt, combined_muwt_nobtagwt, combined_elewt, combined_elewt_nobtagwt);
	    FillCFHists(lNonIso,"_noniso", true, 6.0, combined_muwt, combined_muwt_nobtagwt);
	    FillKFHists(lNonIso,"_noniso",true,combined_muwt,combined_muwt_nobtagwt);

	  }else{

	    TList *lNonIsoLowMET = (TList *)fFileDir[isyst*fNDDReg + 3]->GetList();
	    GetWtRatio(systname, fFileDir[isyst*fNDDReg + 3]->GetName(),"_noniso_lmet");
	    GetCombinedWt(systname, combined_muwt, combined_muwt_nobtagwt, combined_elewt, combined_elewt_nobtagwt);
	    FillCFHists(lNonIsoLowMET,"_noniso_lmet", true, 6.0, combined_muwt, combined_muwt_nobtagwt);
	    FillKFHists(lNonIsoLowMET,"_noniso_lmet",true,combined_muwt,combined_muwt_nobtagwt);
	    
	  }//lowmet
	}//no jec jer
      }//syst loop
    }// muon noniso
	
    //elec
    // if(ProcessKinFit(false, (singleEle and eleIsoCut))){
    //   hasKFEle = true;
    if(!singleMu and (singleEle and eleIsoCut)){

      for(int isyst=0;isyst<fNSyst;isyst++){
	
	TString systname = fSystList[isyst];
	
	if(!systname.Contains("jec") and !systname.Contains("jer") and !systname.Contains("iso20") and !systname.Contains("met")
	   and !systname.Contains("cp5") and !systname.Contains("hdamp") and !systname.Contains("mtop") ) {
	
	  if(!isLowMET){
	    
	    ////////////////// base ////////////////////////////	    
	    TList *lIso = (TList *)fFileDir[isyst*fNDDReg + 0]->GetList();
	    GetWtRatio(systname, fFileDir[isyst*fNDDReg + 0]->GetName(),"");
	    GetCombinedWt(systname, combined_muwt, combined_muwt_nobtagwt, combined_elewt, combined_elewt_nobtagwt);
	    ////FillCFHists(TList *list, string hist_extn, bool isMu, double value, double wt, double wt_nobtagwt)
	    FillCFHists(lIso,"", false, 6.0, combined_elewt, 1.0);
	    //FillKFHists(TList *list, string hist_extn, bool isMu, double wt);
	    FillKFHists(lIso,"",false,combined_elewt,combined_elewt_nobtagwt);	    
	    /////////////////////////////////////////////////////

	  }else{

	    TList *lLowMET = (TList *)fFileDir[isyst*fNDDReg + 1]->GetList();
	    GetWtRatio(systname, fFileDir[isyst*fNDDReg + 1]->GetName(),"_lmet");
	    GetCombinedWt(systname, combined_muwt, combined_muwt_nobtagwt, combined_elewt, combined_elewt_nobtagwt);
	    FillCFHists(lLowMET,"_lmet", false, 6.0, combined_elewt, 1.0);
	    FillKFHists(lLowMET,"_lmet",false,combined_elewt,combined_elewt_nobtagwt);	    	    
	    
	  }//lowmet
	}//no jec jer
      }//syst loop
    }//ele iso
	
    // if(ProcessKinFit(false, (singleEle and eleNonIsoCut))){
    //   hasKFEle = true;
    if(!singleMu and (singleEle and eleNonIsoCut)){
      for(int isyst=0;isyst<fNSyst;isyst++){
	
	TString systname = fSystList[isyst];
	
	if(!systname.Contains("jec") and !systname.Contains("jer") and !systname.Contains("iso20") and !systname.Contains("met")
	   and !systname.Contains("cp5") and !systname.Contains("hdamp") and !systname.Contains("mtop") ) {
	
	  if(!isLowMET){

	    TList *lNonIso = (TList *)fFileDir[isyst*fNDDReg + 2]->GetList();
	    GetWtRatio(systname, fFileDir[isyst*fNDDReg + 2]->GetName(),"_noniso");
	    GetCombinedWt(systname, combined_muwt, combined_muwt_nobtagwt, combined_elewt, combined_elewt_nobtagwt);
	    FillCFHists(lNonIso,"_noniso", false, 6.0, combined_elewt, 1.0);
	    FillKFHists(lNonIso,"_noniso",false,combined_elewt,combined_elewt_nobtagwt);	    
	    
	  }else{
	    
	    TList *lNonIsoLowMET = (TList *)fFileDir[isyst*fNDDReg + 3]->GetList();
	    GetWtRatio(systname, fFileDir[isyst*fNDDReg + 3]->GetName(),"_noniso_lmet");
	    GetCombinedWt(systname, combined_muwt, combined_muwt_nobtagwt, combined_elewt, combined_elewt_nobtagwt);
	    FillCFHists(lNonIsoLowMET,"_noniso_lmet", false, 6.0, combined_elewt, 1.0);
	    FillKFHists(lNonIsoLowMET,"_noniso_lmet",false,combined_elewt,combined_elewt_nobtagwt);	    
	    
	  }//lowmet
	}//jec jer condn
      }//syst loop
    }//ele noniso

  }else if(systType == kIso20){ //if systType == kBase
    
    // combined_muwt = _sampleWeight*_prefireWeight*_PUWeight*_muEffWeight*_PUJetIDWeight*_bTagWeight;
    // combined_muwt_nobtagwt = _sampleWeight*_PUWeight*_muEffWeight*_PUJetIDWeight*_bTagWeight;
    // combined_elewt = _sampleWeight*_prefireWeight*_PUWeight*_eleEffWeight*_PUJetIDWeight*_bTagWeight;

    // if(ProcessKinFit((singleMu and muonIsoCut), false)){
    //   hasKFMu = true;
    if((singleMu and muonIsoCut) and !singleEle){
      for(int isyst=0;isyst<fNSyst;isyst++){
	TString systname = fSystList[isyst];
	if(systname.Contains("iso20")) {
	  //GetCombinedWt(systname, combined_muwt, combined_muwt_nobtagwt, combined_elewt, combined_elewt_nobtagwt);
	  if(!isLowMET){
	    ////////////////// base ////////////////////////////
	    TList *lIso = (TList *)fFileDir[isyst*fNDDReg + 0]->GetList();
	    GetWtRatio(systname, fFileDir[isyst*fNDDReg + 0]->GetName(),"");
	    GetCombinedWt(systname, combined_muwt, combined_muwt_nobtagwt, combined_elewt, combined_elewt_nobtagwt);
	    FillCFHists(lIso, "", true, 6.0, combined_muwt, combined_muwt_nobtagwt);
	    //FillKFHists(TList *list, string hist_extn, bool isMu, double wt);
	    FillKFHists(lIso,"",true,combined_muwt,combined_muwt_nobtagwt);
	    /////////////////////////////////////////////////////
	  }else{
	    TList *lLowMET = (TList *)fFileDir[isyst*fNDDReg + 1]->GetList();
	    GetWtRatio(systname, fFileDir[isyst*fNDDReg + 1]->GetName(),"_lmet");
	    GetCombinedWt(systname, combined_muwt, combined_muwt_nobtagwt, combined_elewt, combined_elewt_nobtagwt);
	    FillCFHists(lLowMET,"_lmet", true, 6.0, combined_muwt, combined_muwt_nobtagwt);
	    FillKFHists(lLowMET,"_lmet",true,combined_muwt,combined_muwt_nobtagwt);
	  }//lowmet
	}//iso20 condn
      }//syst loop
    }//muon iso

    
    // if(ProcessKinFit((singleMu and muonNonIsoCut), false)){
    //   hasKFMu = true;
    if((singleMu and muonNonIsoCut) and !singleEle){      
      for(int isyst=0;isyst<fNSyst;isyst++){
	TString systname = fSystList[isyst];
	if(systname.Contains("iso20")) {
	  //GetCombinedWt(systname, combined_muwt, combined_muwt_nobtagwt, combined_elewt, combined_elewt_nobtagwt);
	  if(!isLowMET){
	    TList *lNonIso = (TList *)fFileDir[isyst*fNDDReg + 2]->GetList();
	    GetWtRatio(systname, fFileDir[isyst*fNDDReg + 2]->GetName(),"_noniso");
	    GetCombinedWt(systname, combined_muwt, combined_muwt_nobtagwt, combined_elewt, combined_elewt_nobtagwt);
	    FillCFHists(lNonIso,"_noniso", true, 6.0, combined_muwt, combined_muwt_nobtagwt);
	    FillKFHists(lNonIso,"_noniso",true,combined_muwt,combined_muwt_nobtagwt);
	  }else{
	    TList *lNonIsoLowMET = (TList *)fFileDir[isyst*fNDDReg + 3]->GetList();
	    GetWtRatio(systname, fFileDir[isyst*fNDDReg + 3]->GetName(),"_noniso_lmet");
	    GetCombinedWt(systname, combined_muwt, combined_muwt_nobtagwt, combined_elewt, combined_elewt_nobtagwt);
	    FillCFHists(lNonIsoLowMET,"_noniso_lmet", true, 6.0, combined_muwt, combined_muwt_nobtagwt);
	    FillKFHists(lNonIsoLowMET,"_noniso_lmet",true,combined_muwt,combined_muwt_nobtagwt);
	  }//lowmet
	}//iso20 condn
      }//syst loop
    }// muon noniso
	
    //elec
    // if(ProcessKinFit(false, (singleEle and eleIsoCut))){
    //   hasKFEle = true;
    if(!singleMu and (singleEle and eleIsoCut)){
      for(int isyst=0;isyst<fNSyst;isyst++){
	TString systname = fSystList[isyst];
	if(systname.Contains("iso20")) {
	  //GetCombinedWt(systname, combined_muwt, combined_muwt_nobtagwt, combined_elewt, combined_elewt_nobtagwt);
	  if(!isLowMET){	    
	    ////////////////// base ////////////////////////////	    
	    TList *lIso = (TList *)fFileDir[isyst*fNDDReg + 0]->GetList();
	    GetWtRatio(systname, fFileDir[isyst*fNDDReg + 0]->GetName(),"");
	    GetCombinedWt(systname, combined_muwt, combined_muwt_nobtagwt, combined_elewt, combined_elewt_nobtagwt);
	    //FillKFHists(TList *list, string hist_extn, bool isMu, double wt);
	    FillCFHists(lIso,"",false, 6.0, combined_elewt, 1.0);
	    FillKFHists(lIso,"",false,combined_elewt,combined_elewt_nobtagwt);	    
	    /////////////////////////////////////////////////////
	  }else{
	    TList *lLowMET = (TList *)fFileDir[isyst*fNDDReg + 1]->GetList();
	    GetWtRatio(systname, fFileDir[isyst*fNDDReg + 1]->GetName(),"_lmet");
	    GetCombinedWt(systname, combined_muwt, combined_muwt_nobtagwt, combined_elewt, combined_elewt_nobtagwt);
	    FillCFHists(lLowMET,"_lmet",false, 6.0, combined_elewt, 1.0);
	    FillKFHists(lLowMET,"_lmet",false,combined_elewt,combined_elewt);	    	    
	  }//lowmet
	}//iso20 condn
      }//syst loop
    }//ele iso
	
    // if(ProcessKinFit(false, (singleEle and eleNonIsoCut))){
    //   hasKFEle = true;
    if(!singleMu and (singleEle and eleNonIsoCut)){
      for(int isyst=0;isyst<fNSyst;isyst++){
	TString systname = fSystList[isyst];
	if(systname.Contains("iso20")) {
	  //GetCombinedWt(systname, combined_muwt, combined_muwt_nobtagwt, combined_elewt, combined_elewt_nobtagwt);
	  if(!isLowMET){
	    TList *lNonIso = (TList *)fFileDir[isyst*fNDDReg + 2]->GetList();
	    GetWtRatio(systname, fFileDir[isyst*fNDDReg + 2]->GetName(),"_noniso");
	    GetCombinedWt(systname, combined_muwt, combined_muwt_nobtagwt, combined_elewt, combined_elewt_nobtagwt);
	    FillCFHists(lNonIso,"_noniso",false, 6.0, combined_elewt, 1.0);
	    FillKFHists(lNonIso,"_noniso",false,combined_elewt,combined_elewt);	    	    
	  }else{
	    TList *lNonIsoLowMET = (TList *)fFileDir[isyst*fNDDReg + 3]->GetList();
	    GetWtRatio(systname, fFileDir[isyst*fNDDReg + 3]->GetName(),"_noniso_lmet");
	    GetCombinedWt(systname, combined_muwt, combined_muwt_nobtagwt, combined_elewt, combined_elewt_nobtagwt);
	    FillCFHists(lNonIsoLowMET,"_noniso_lmet",false, 6.0, combined_elewt, 1.0);
	    FillKFHists(lNonIsoLowMET,"_noniso_lmet",false,combined_elewt,combined_elewt);	    
	  }//lowmet
	}//iso20 condn
      }//syst loop
    }//ele noniso

  }else { //if systType == kBase

    // combined_muwt = _sampleWeight*_prefireWeight*_PUWeight*_muEffWeight*_PUJetIDWeight*_bTagWeight;
    // combined_muwt_nobtagwt = _sampleWeight*_PUWeight*_muEffWeight*_PUJetIDWeight*_bTagWeight;
    // combined_elewt = _sampleWeight*_prefireWeight*_PUWeight*_eleEffWeight*_PUJetIDWeight*_bTagWeight;

    // if(ProcessKinFit((singleMu and muonIsoCut), false)){
    //   hasKFMu = true;
    if((singleMu and muonIsoCut) and !singleEle){      
      for(int isyst=0;isyst<fNSyst;isyst++){
	TString systname = fSystList[isyst];
	if( (systType == kJECUp and systname == "jecup") or (systType == kJECDown and systname == "jecdown") 
	    or (systType == kJERUp and systname == "jerup") or (systType == kJERDown and systname == "jerdown")
	    or (systType == kMETUp and systname == "metup") or (systType == kMETDown and systname == "metdown")
	    or (systType == kCP5Up and systname == "cp5up") or (systType == kCP5Down and systname == "cp5down")
	    or (systType == khDampUp and systname == "hdampup") or (systType == khDampDown and systname == "hdampdown")
	    or (systType == kmTopUp and systname == "mtopup") or (systType == kmTopDown and systname == "mtopdown")){	    

	  //GetCombinedWt(systname, combined_muwt, combined_muwt_nobtagwt, combined_elewt, combined_elewt_nobtagwt);

	  if(!isLowMET){
	    ////////////////// base ////////////////////////////
	    TList *lIso = (TList *)fFileDir[isyst*fNDDReg + 0]->GetList();
	    GetWtRatio(systname, fFileDir[isyst*fNDDReg + 0]->GetName(),"");
	    GetCombinedWt(systname, combined_muwt, combined_muwt_nobtagwt, combined_elewt, combined_elewt_nobtagwt);
	    FillCFHists(lIso, "", true, 6.0, combined_muwt, combined_muwt_nobtagwt);
	    //FillKFHists(TList *list, string hist_extn, bool isMu, double wt);
	    FillKFHists(lIso,"",true,combined_muwt,combined_muwt_nobtagwt);
	    /////////////////////////////////////////////////////
	  }else{
	    TList *lLowMET = (TList *)fFileDir[isyst*fNDDReg + 1]->GetList();
	    GetWtRatio(systname, fFileDir[isyst*fNDDReg + 1]->GetName(),"_lmet");
	    GetCombinedWt(systname, combined_muwt, combined_muwt_nobtagwt, combined_elewt, combined_elewt_nobtagwt);
	    FillCFHists(lLowMET,"_lmet", true, 6.0, combined_muwt, combined_muwt_nobtagwt);
	    FillKFHists(lLowMET,"_lmet",true,combined_muwt,combined_muwt_nobtagwt);
	  }//lowmet
	}//jec jer condn
      }//syst loop
    }//muon iso
	
    // if(ProcessKinFit((singleMu and muonNonIsoCut), false)){
    //   hasKFMu = true;
    if((singleMu and muonNonIsoCut) and !singleEle){      
      for(int isyst=0;isyst<fNSyst;isyst++){
	TString systname = fSystList[isyst];
	if( (systType == kJECUp and systname == "jecup") or (systType == kJECDown and systname == "jecdown") 
	    or (systType == kJERUp and systname == "jerup") or (systType == kJERDown and systname == "jerdown")
	    or (systType == kMETUp and systname == "metup") or (systType == kMETDown and systname == "metdown")	    
	    or (systType == kCP5Up and systname == "cp5up") or (systType == kCP5Down and systname == "cp5down")
	    or (systType == khDampUp and systname == "hdampup") or (systType == khDampDown and systname == "hdampdown")
	    or (systType == kmTopUp and systname == "mtopup") or (systType == kmTopDown and systname == "mtopdown")){	    
	    
	  //GetCombinedWt(systname, combined_muwt, combined_muwt_nobtagwt, combined_elewt, combined_elewt_nobtagwt);

	  if(!isLowMET){
	    TList *lNonIso = (TList *)fFileDir[isyst*fNDDReg + 2]->GetList();
	    GetWtRatio(systname, fFileDir[isyst*fNDDReg + 2]->GetName(),"_noniso");
	    GetCombinedWt(systname, combined_muwt, combined_muwt_nobtagwt, combined_elewt, combined_elewt_nobtagwt);
	    FillCFHists(lNonIso,"_noniso", true, 6.0, combined_muwt, combined_muwt_nobtagwt);
	    FillKFHists(lNonIso,"_noniso",true,combined_muwt,combined_muwt_nobtagwt);
	  }else{
	    TList *lNonIsoLowMET = (TList *)fFileDir[isyst*fNDDReg + 3]->GetList();
	    GetWtRatio(systname, fFileDir[isyst*fNDDReg + 3]->GetName(),"_noniso_lmet");
	    GetCombinedWt(systname, combined_muwt, combined_muwt_nobtagwt, combined_elewt, combined_elewt_nobtagwt);
	    FillCFHists(lNonIsoLowMET,"_noniso_lmet", true, 6.0, combined_muwt, combined_muwt_nobtagwt);
	    FillKFHists(lNonIsoLowMET,"_noniso_lmet",true,combined_muwt,combined_muwt_nobtagwt);
	  }//lowmet
	}//jec jer condn
      }//syst loop
    }// muon noniso

    //elec
    // if(ProcessKinFit(false, (singleEle and eleIsoCut))){
    //   hasKFEle = true;
    if(!singleMu and (singleEle and eleIsoCut)){
      for(int isyst=0;isyst<fNSyst;isyst++){
	TString systname = fSystList[isyst];
	if( (systType == kJECUp and systname == "jecup") or (systType == kJECDown and systname == "jecdown") 
	    or (systType == kJERUp and systname == "jerup") or (systType == kJERDown and systname == "jerdown")
	    or (systType == kMETUp and systname == "metup") or (systType == kMETDown and systname == "metdown")
	    or (systType == kCP5Up and systname == "cp5up") or (systType == kCP5Down and systname == "cp5down")
	    or (systType == khDampUp and systname == "hdampup") or (systType == khDampDown and systname == "hdampdown")
	    or (systType == kmTopUp and systname == "mtopup") or (systType == kmTopDown and systname == "mtopdown")){	    	    

	  GetCombinedWt(systname, combined_muwt, combined_muwt_nobtagwt, combined_elewt, combined_elewt_nobtagwt);
	  
	  if(!isLowMET){	    
	    ////////////////// base ////////////////////////////	    
	    TList *lIso = (TList *)fFileDir[isyst*fNDDReg + 0]->GetList();
	    GetWtRatio(systname, fFileDir[isyst*fNDDReg + 0]->GetName(),"");
	    GetCombinedWt(systname, combined_muwt, combined_muwt_nobtagwt, combined_elewt, combined_elewt_nobtagwt);
	    //FillKFHists(TList *list, string hist_extn, bool isMu, double wt);
	    FillCFHists(lIso,"",false, 6.0, combined_elewt, 1.0);
	    FillKFHists(lIso,"",false,combined_elewt,combined_elewt_nobtagwt);	    
	    /////////////////////////////////////////////////////
	  }else{
	    TList *lLowMET = (TList *)fFileDir[isyst*fNDDReg + 1]->GetList();
	    GetWtRatio(systname, fFileDir[isyst*fNDDReg + 1]->GetName(),"_lmet");
	    GetCombinedWt(systname, combined_muwt, combined_muwt_nobtagwt, combined_elewt, combined_elewt_nobtagwt);
	    FillCFHists(lLowMET,"_lmet",false, 6.0, combined_elewt, 1.0);
	    FillKFHists(lLowMET,"_lmet",false,combined_elewt,combined_elewt_nobtagwt);	    	    
	  }//lowmet
	}//jec jer condn
      }//syst loop
    }//ele iso
	
    // if(ProcessKinFit(false, (singleEle and eleNonIsoCut))){
    //   hasKFEle = true;
    if(!singleMu and (singleEle and eleNonIsoCut)){
      for(int isyst=0;isyst<fNSyst;isyst++){
	TString systname = fSystList[isyst];
	if( (systType == kJECUp and systname == "jecup") or (systType == kJECDown and systname == "jecdown") 
	    or (systType == kJERUp and systname == "jerup") or (systType == kJERDown and systname == "jerdown")
	    or (systType == kMETUp and systname == "metup") or (systType == kMETDown and systname == "metdown")
	    or (systType == kCP5Up and systname == "cp5up") or (systType == kCP5Down and systname == "cp5down")
	    or (systType == khDampUp and systname == "hdampup") or (systType == khDampDown and systname == "hdampdown")
	    or (systType == kmTopUp and systname == "mtopup") or (systType == kmTopDown and systname == "mtopdown")){	    	    
	  
	  GetCombinedWt(systname, combined_muwt, combined_muwt_nobtagwt, combined_elewt, combined_elewt_nobtagwt);
	  
	  if(!isLowMET){
	    TList *lNonIso = (TList *)fFileDir[isyst*fNDDReg + 2]->GetList();
	    GetWtRatio(systname, fFileDir[isyst*fNDDReg + 2]->GetName(),"_noniso");
	    GetCombinedWt(systname, combined_muwt, combined_muwt_nobtagwt, combined_elewt, combined_elewt_nobtagwt);
	    FillCFHists(lNonIso,"_noniso",false, 6.0, combined_elewt, 1.0);
	    FillKFHists(lNonIso,"_noniso",false,combined_elewt,combined_elewt_nobtagwt);	    	    
	  }else{
	    TList *lNonIsoLowMET = (TList *)fFileDir[isyst*fNDDReg + 3]->GetList();
	    GetWtRatio(systname, fFileDir[isyst*fNDDReg + 3]->GetName(),"_noniso_lmet");
	    GetCombinedWt(systname, combined_muwt, combined_muwt_nobtagwt, combined_elewt, combined_elewt_nobtagwt);
	    FillCFHists(lNonIsoLowMET,"_noniso_lmet",false, 6.0, combined_elewt, 1.0);
	    FillKFHists(lNonIsoLowMET,"_noniso_lmet",false,combined_elewt,combined_elewt_nobtagwt);	    
	  }//lowmet
	}//jec jer condn
      }//syst loop
    }//ele noniso

  }//syst base vs jec/jer condn
  
  return true;
}


// //_____________________________________________________________________________

// bool KinAna::FillKinFitControlHists(){
  
//   double combined_muwt = _sampleWeight*_prefireWeight*_PUWeight*_muEffWeight*_bTagWeight;
//   double combined_elewt = _sampleWeight*_prefireWeight*_PUWeight*_eleEffWeight*_bTagWeight;
  
//   int iscl = 6 ; //6 for KinFit
//   TList *list = (TList *)fSelColDir[iscl]->GetList();
//   if(singleMu and hasKFMu and muonIsoCut and !isLowMET){
//     ((TH1D *) list->FindObject("pv_npvs"))->Fill(event->nVtx_, combined_muwt);
//     ((TH1D *) list->FindObject("pv_z"))->Fill(event->pvZ_, combined_muwt);
//     ((TH1D *) list->FindObject("pt_mu"))->Fill(leptonAF.Pt(), combined_muwt);
//     ((TH1D *) list->FindObject("eta_mu"))->Fill(leptonAF.Eta(), combined_muwt);
//     ((TH1D *) list->FindObject("iso_mu"))->Fill(event->muPFRelIso_[selector->MuonsNoIso.at(0)], combined_muwt);
    
//     ((TH1D *) list->FindObject("pt_jet1_bjet"))->Fill(bjlepAF.Pt(), combined_muwt);
//     ((TH1D *) list->FindObject("eta_jet1_bjet"))->Fill(bjlepAF.Eta(), combined_muwt);
//     ((TH1D *) list->FindObject("pt_jet2_bjet"))->Fill(bjhadAF.Pt(), combined_muwt);
//     ((TH1D *) list->FindObject("eta_jet2_bjet"))->Fill(bjhadAF.Eta(), combined_muwt);
//     ((TH1D *) list->FindObject("pt_jet1_ljet"))->Fill(cjhadAF.Pt(), combined_muwt);
//     ((TH1D *) list->FindObject("eta_jet1_ljet"))->Fill(cjhadAF.Eta(), combined_muwt);
//     ((TH1D *) list->FindObject("pt_jet2_ljet"))->Fill(sjhadAF.Pt(), combined_muwt);
//     ((TH1D *) list->FindObject("eta_jet2_ljet"))->Fill(sjhadAF.Eta(), combined_muwt);

//     ((TH1D *) list->FindObject("mjj_test_mu"))->Fill((sjhadAF+cjhadAF).M(), combined_muwt);

//     bool isApplicable[4],hasPassed[4];
//     isApplicable[0] = (selector->JetsPtSmeared.at(_bjlep_id)<50.)? true : false;
//     isApplicable[1] = (selector->JetsPtSmeared.at(_bjhad_id)<50.)? true : false;
//     isApplicable[2] = (selector->JetsPtSmeared.at(_cjhad_id)<50.)? true : false;
//     isApplicable[3] = (selector->JetsPtSmeared.at(_sjhad_id)<50.)? true : false;
//     hasPassed[0] = (event->jetpuIdDisc_[selector->Jets.at(_bjlep_id)]>0.5) ? true : false;
//     hasPassed[1] = (event->jetpuIdDisc_[selector->Jets.at(_bjhad_id)]>0.5) ? true : false;
//     hasPassed[2] = (event->jetpuIdDisc_[selector->Jets.at(_cjhad_id)]>0.5) ? true : false;
//     hasPassed[3] = (event->jetpuIdDisc_[selector->Jets.at(_sjhad_id)]>0.5) ? true : false;
    
//     if( (isApplicable[0] and hasPassed[0]) and (isApplicable[1] and hasPassed[1]) and  (isApplicable[2] and hasPassed[2]) and (isApplicable[3] and hasPassed[3])){
//       ((TH1D *) list->FindObject("pv_npvs_jetpupass"))->Fill(event->nVtx_, combined_muwt);
//       ((TH1D *) list->FindObject("pv_z_jetpupass"))->Fill(event->pvZ_, combined_muwt);
//     }
//     if( (isApplicable[0] and !hasPassed[0]) or (isApplicable[1] and !hasPassed[1]) or (isApplicable[2] and !hasPassed[2]) or (isApplicable[3] and !hasPassed[3])){
//       ((TH1D *) list->FindObject("pv_npvs_jetpufail"))->Fill(event->nVtx_, combined_muwt);
//       ((TH1D *) list->FindObject("pv_z_jetpufail"))->Fill(event->pvZ_, combined_muwt);
//     }

//   }
//   if(singleEle and hasKFEle){
//     ((TH1D *) list->FindObject("pv_npvs"))->Fill(event->nVtx_, combined_muwt);
//     ((TH1D *) list->FindObject("pv_z"))->Fill(event->pvZ_, combined_muwt);
//     ((TH1D *) list->FindObject("pt_ele"))->Fill(leptonAF.Pt(), combined_elewt);
//     ((TH1D *) list->FindObject("eta_ele"))->Fill(leptonAF.Eta(), combined_elewt);
//     ((TH1D *) list->FindObject("iso_ele"))->Fill(event->elePFRelIso_[selector->ElectronsNoIso.at(0)], combined_elewt);
    
//     ((TH1D *) list->FindObject("pt_jet1_bjet"))->Fill(bjlepAF.Pt(), combined_elewt);
//     ((TH1D *) list->FindObject("eta_jet1_bjet"))->Fill(bjlepAF.Eta(), combined_elewt);
//     ((TH1D *) list->FindObject("pt_jet2_bjet"))->Fill(bjhadAF.Pt(), combined_elewt);
//     ((TH1D *) list->FindObject("eta_jet2_bjet"))->Fill(bjhadAF.Eta(), combined_elewt);
//     ((TH1D *) list->FindObject("pt_jet1_ljet"))->Fill(cjhadAF.Pt(), combined_elewt);
//     ((TH1D *) list->FindObject("eta_jet1_ljet"))->Fill(cjhadAF.Eta(), combined_elewt);
//     ((TH1D *) list->FindObject("pt_jet2_ljet"))->Fill(sjhadAF.Pt(), combined_elewt);
//     ((TH1D *) list->FindObject("eta_jet2_ljet"))->Fill(sjhadAF.Eta(), combined_elewt);

//     bool isApplicable[4],hasPassed[4];
//     isApplicable[0] = (selector->JetsPtSmeared.at(_bjlep_id)<50.)? true : false;
//     isApplicable[1] = (selector->JetsPtSmeared.at(_bjhad_id)<50.)? true : false;
//     isApplicable[2] = (selector->JetsPtSmeared.at(_cjhad_id)<50.)? true : false;
//     isApplicable[3] = (selector->JetsPtSmeared.at(_sjhad_id)<50.)? true : false;
//     hasPassed[0] = (event->jetpuIdDisc_[selector->Jets.at(_bjlep_id)]>0.5) ? true : false;
//     hasPassed[1] = (event->jetpuIdDisc_[selector->Jets.at(_bjhad_id)]>0.5) ? true : false;
//     hasPassed[2] = (event->jetpuIdDisc_[selector->Jets.at(_cjhad_id)]>0.5) ? true : false;
//     hasPassed[3] = (event->jetpuIdDisc_[selector->Jets.at(_sjhad_id)]>0.5) ? true : false;
    
//     if( (isApplicable[0] and hasPassed[0]) and (isApplicable[1] and hasPassed[1]) and  (isApplicable[2] and hasPassed[2]) and (isApplicable[3] and hasPassed[3])){
//       ((TH1D *) list->FindObject("pv_npvs_jetpupass"))->Fill(event->nVtx_, combined_elewt);
//       ((TH1D *) list->FindObject("pv_z_jetpupass"))->Fill(event->pvZ_, combined_elewt);
//     }
//     if( (isApplicable[0] and !hasPassed[0]) or (isApplicable[1] and !hasPassed[1]) or (isApplicable[2] and !hasPassed[2]) or (isApplicable[3] and !hasPassed[3])){
//       ((TH1D *) list->FindObject("pv_npvs_jetpufail"))->Fill(event->nVtx_, combined_elewt);
//       ((TH1D *) list->FindObject("pv_z_jetpufail"))->Fill(event->pvZ_, combined_elewt);
//     }
//   }
  
//   if(!isData){    
    
//     int nofLHEljets = 0;
//     int ljetsLHEPDG[10];
//     TLorentzVector ljetsLHE[10];
//     for (unsigned int imc = 0 ; imc < event->nLHEPart_ ; imc++ ){      
//       TParticlePDG *partPDG = TDatabasePDG::Instance()->GetParticle(event->LHEPart_pdgId_[imc]);
//       // if(!partPDG){
//       // 	printf("\t CTag : LHE : %03d, PDG : %5d ( noPDGname), (Pt, Eta, Phi, Mass, R) = (%5.2f, %5.2f, %5.2f, %5.2f, %5.2f)\n", 
//       // 	       imc, event->LHEPart_pdgId_[imc], event->LHEPart_pt_[imc], 
//       // 	       event->LHEPart_eta_[imc] , event->LHEPart_phi_[imc], event->LHEPart_mass_[imc], TMath::Sqrt(event->LHEPart_eta_[imc]*event->LHEPart_eta_[imc] + event->LHEPart_phi_[imc]*event->LHEPart_phi_[imc]) );
	
//       // }else{
//       // 	printf("\t Ctag : LHE : %03d, PDG : %5d (%7s), (Pt, Eta, Phi, Mass, R) = (%5.2f, %5.2f, %5.2f, %5.2f, %5.2f)\n", 
//       // 	       imc, event->LHEPart_pdgId_[imc], partPDG->GetName(), event->LHEPart_pt_[imc],
//       // 	       event->LHEPart_eta_[imc] , event->LHEPart_phi_[imc], event->LHEPart_mass_[imc], TMath::Sqrt(event->LHEPart_eta_[imc]*event->LHEPart_eta_[imc] + event->LHEPart_phi_[imc]*event->LHEPart_phi_[imc]) );
//       // }      
//       if(((TMath::Abs(event->LHEPart_pdgId_[imc])>=1 and TMath::Abs(event->LHEPart_pdgId_[imc])<=4) or event->LHEPart_pdgId_[imc]==21) and imc>=2) {
//   	// printf("\t Ljet : %03d, PDG : %5d (%7s), (Pt, Eta, Phi, Mass, R) = (%5.2f, %5.2f, %5.2f, %5.2f, %5.2f)\n", 
//   	//        imc, event->LHEPart_pdgId_[imc], partPDG->GetName(), event->LHEPart_pt_[imc],
//   	//        event->LHEPart_eta_[imc] , event->LHEPart_phi_[imc], event->LHEPart_mass_[imc], TMath::Sqrt(event->LHEPart_eta_[imc]*event->LHEPart_eta_[imc] + event->LHEPart_phi_[imc]*event->LHEPart_phi_[imc]) );
//   	ljetsLHE[nofLHEljets].SetPtEtaPhiM(event->LHEPart_pt_[imc], event->LHEPart_eta_[imc] , event->LHEPart_phi_[imc], event->LHEPart_mass_[imc]);
// 	ljetsLHEPDG[nofLHEljets] = event->LHEPart_pdgId_[imc];
// 	if(singleMu and muonIsoCut and !isLowMET)
// 	  ((TH1D *) list->FindObject("lheFlav"))->Fill(event->LHEPart_pdgId_[imc], combined_muwt);
// 	nofLHEljets++;
//       }//found light jet
//     }// LHE particle loop
    
//     const int maxNJets = 20;
//     int nofRecoljets = 0;
//     int ljetsRecoPDG[maxNJets];
//     TLorentzVector ljetsReco[maxNJets];
//     int nofGenljets = 0;
//     int ljetsGenPDG[maxNJets];
//     TLorentzVector ljetsGen[maxNJets];
//     int LHEindex = -1;
//     double DelRLHEGenJet = -1.0;
//     int nofmatch = 0;
//     for (unsigned int ijet = 0; ijet < selector->Jets.size(); ijet++){
//       int jetInd = selector->Jets.at(ijet);
//       if( (TMath::Abs(event->jetPartFlvr_[jetInd])>=1 and TMath::Abs(event->jetPartFlvr_[jetInd])<=4) or TMath::Abs(event->jetPartFlvr_[jetInd])==21){
//   	// printf("\t ljet JetArray : (flav, btag) : (%d, %3.2f), (pt,eta,phi,M,R) = (%5.2f, %5.2f, %5.2f, %5.2f, %5.2f)\n", 
//   	//        event->jetPartFlvr_[jetInd], event->jetBtagDeepFlavB_[jetInd],
//   	//        selector->JetsPtSmeared.at(ijet), event->jetEta_[jetInd] , event->jetPhi_[jetInd] , event->jetMass_[jetInd],
//   	//        TMath::Sqrt(event->jetEta_[jetInd]*event->jetEta_[jetInd] + event->jetPhi_[jetInd]*event->jetPhi_[jetInd]));
// 	ljetsReco[nofRecoljets].SetPtEtaPhiM(selector->JetsPtSmeared.at(ijet), event->jetEta_[jetInd] , event->jetPhi_[jetInd] , event->jetMass_[jetInd]);
// 	int genIdx = int(event->jetGenJetIdx_[jetInd]);
// 	if ( (genIdx>-1) && (genIdx < int(event->nGenJet_))){
// 	  TParticlePDG *partPDG = TDatabasePDG::Instance()->GetParticle(event->GenJet_partonFlavour_[genIdx]);
// 	  ljetsGen[nofGenljets].SetPtEtaPhiM(event->GenJet_pt_[genIdx], event->GenJet_eta_[genIdx] , event->GenJet_phi_[genIdx], event->GenJet_mass_[genIdx]);
// 	  DelRLHEGenJet = -1.0;
// 	  for(int imc=0;imc<nofLHEljets;imc++){
// 	    if(ljetsLHEPDG[imc]==event->GenJet_partonFlavour_[genIdx]){
// 	      DelRLHEGenJet = ljetsLHE[imc].DeltaR(ljetsGen[nofGenljets]);
// 	      LHEindex = imc;
// 	    }
// 	  }
// 	  // printf("\t  Genjet : \"%s\", (pflav/hflav) : (%d/%d), (pt,eta,phi,M) = (%5.2f, %5.2f, %5.2f, %5.2f), DeltaR : %5.3f, DeltaRGenLHE : %5.2f\n",
// 	  // 	 partPDG->GetName(),event->GenJet_partonFlavour_[genIdx], event->GenJet_hadronFlavour_[genIdx], 
// 	  // 	 //event->jetPartFlvr_[jetInd], event->jetHadFlvr_[jetInd], 
// 	  // 	 event->GenJet_pt_[genIdx], event->GenJet_eta_[genIdx] , event->GenJet_phi_[genIdx], event->GenJet_mass_[genIdx],
// 	  // 	 ljetsReco[nofRecoljets].DeltaR(ljetsGen[nofGenljets]), DelRLHEGenJet);	  
	  
// 	  if(singleMu and muonIsoCut and !isLowMET){
// 	    ((TH1D *) list->FindObject("delRGenRec"))->Fill(ljetsReco[nofRecoljets].DeltaR(ljetsGen[nofGenljets]), combined_muwt);
// 	    ((TH1D *) list->FindObject("delRGenRecUS"))->Fill(ljetsReco[nofRecoljets].DeltaR(ljetsGen[nofGenljets]));
// 	    ((TH1D *) list->FindObject("genFlav"))->Fill(event->GenJet_partonFlavour_[genIdx], combined_muwt);
// 	    if(LHEindex>-1) {
// 	      ((TH1D *) list->FindObject("delRLHEGen"))->Fill(DelRLHEGenJet, combined_muwt);
// 	    }
// 	  }//if Muon KF

// 	  nofGenljets++;
// 	}//GenJet
	
	
// 	if(singleMu and muonIsoCut and !isLowMET){
// 	  ((TH1D *) list->FindObject("recoFlav"))->Fill(event->jetPartFlvr_[jetInd], combined_muwt);
// 	  ((TH1D *) list->FindObject("recoFlavUS"))->Fill(event->jetPartFlvr_[jetInd]);
// 	  if(hasKFMu){
// 	    if(ijet == _cjhad_id) {
// 	      ((TH1D *) list->FindObject("delRRecKF"))->Fill(cjhadAF.DeltaR(ljetsReco[nofRecoljets]), combined_muwt);
// 	      ((TH1D *) list->FindObject("delRRecKFUS"))->Fill(cjhadAF.DeltaR(ljetsReco[nofRecoljets]));
// 	      ((TH1D *) list->FindObject("kfFlav"))->Fill(event->jetPartFlvr_[jetInd], combined_muwt);
// 	      ((TH1D *) list->FindObject("kfFlavUS"))->Fill(event->jetPartFlvr_[jetInd]);
// 	      ((TProfile *) list->FindObject("probDelRRecKF"))->Fill(_prob, cjhadAF.DeltaR(ljetsReco[nofRecoljets]), combined_muwt);
// 	      ((TProfile *) list->FindObject("probDelRRecKFUS"))->Fill(_prob, cjhadAF.DeltaR(ljetsReco[nofRecoljets]));
// 	      for(int imc=0;imc<nofLHEljets;imc++){
// 		if(ljetsLHEPDG[imc]==event->jetPartFlvr_[jetInd] and ljetsLHE[imc].DeltaR(cjhadAF) < 0.4)
// 		  nofmatch++;
// 	      }
// 	    }
// 	    if(ijet == _sjhad_id){
// 	      ((TH1D *) list->FindObject("delRRecKF"))->Fill(sjhadAF.DeltaR(ljetsReco[nofRecoljets]), combined_muwt);
// 	      ((TH1D *) list->FindObject("delRRecKFUS"))->Fill(sjhadAF.DeltaR(ljetsReco[nofRecoljets]));
// 	      ((TH1D *) list->FindObject("kfFlav"))->Fill(event->jetPartFlvr_[jetInd], combined_muwt);
// 	      ((TH1D *) list->FindObject("kfFlavUS"))->Fill(event->jetPartFlvr_[jetInd]);
// 	      ((TProfile *) list->FindObject("probDelRRecKF"))->Fill(_prob, sjhadAF.DeltaR(ljetsReco[nofRecoljets]), combined_muwt);
// 	      ((TProfile *) list->FindObject("probDelRRecKFUS"))->Fill(_prob, sjhadAF.DeltaR(ljetsReco[nofRecoljets]));
// 	      for(int imc=0;imc<nofLHEljets;imc++){
// 		if(ljetsLHEPDG[imc]==event->jetPartFlvr_[jetInd] and ljetsLHE[imc].DeltaR(sjhadAF) < 0.4)
// 		  nofmatch++;
// 	      }
// 	    }
// 	  }//has Muon KF
// 	}//SingleMu
// 	nofRecoljets++;
//       }//condn for light jet or gluon
//     }//Reco jet loop
//     if(singleMu and hasKFMu and muonIsoCut and !isLowMET){
//       ((TH1D *) list->FindObject("kfProb"))->Fill(_prob, combined_muwt);
//       ((TH1D *) list->FindObject("kfProbUS"))->Fill(_prob);
//       ((TProfile *) list->FindObject("probMatch"))->Fill(_prob, nofmatch/2.);
//       ((TProfile *) list->FindObject("probMjj"))->Fill(_prob, (cjhadAF+sjhadAF).M(), combined_muwt);
//     }
//   }//IsData
  
//   return true;
// }

// //_____________________________________________________________________________
// bool KinAna::FillCTagControlHists()
// {
//   int count_cJetsIncL   = 0;
//   int count_cJetsIncM   = 0;
//   int count_cJetsIncT   = 0;

//   bool isIncL = false;
//   bool isIncM = false;
//   bool isIncT = false;

//   int iscl = 7 ; //7 for CTagL
//   TList *listL = (TList *)fSelColDir[iscl]->GetList();
//   iscl = 8 ; //8 for CTagM
//   TList *listM = (TList *)fSelColDir[iscl]->GetList();

//   double ctagTh_CvsL_L = (selector->useDeepCSVbTag) ? selector->btag_cut_DeepCSV  : selector->ctag_CvsL_L_cut  ;
//   double ctagTh_CvsB_L = (selector->useDeepCSVbTag) ? selector->btag_cut_DeepCSV  : selector->ctag_CvsB_L_cut  ;
//   double ctagTh_CvsL_M = (selector->useDeepCSVbTag) ? selector->btag_cut_DeepCSV  : selector->ctag_CvsL_M_cut  ;
//   double ctagTh_CvsB_M = (selector->useDeepCSVbTag) ? selector->btag_cut_DeepCSV  : selector->ctag_CvsB_M_cut  ;
//   double ctagTh_CvsL_T = (selector->useDeepCSVbTag) ? selector->btag_cut_DeepCSV  : selector->ctag_CvsL_T_cut  ;
//   double ctagTh_CvsB_T = (selector->useDeepCSVbTag) ? selector->btag_cut_DeepCSV  : selector->ctag_CvsB_T_cut  ;

//   // Info("FillCTagControlHists","");
//   // Info("FillCTagControlHists","Event : %d (%d), Mu : %d, Ele : %d",fProcessed,nCTag++,hasKFMu,hasKFEle);
//   // Info("FillCTagControlHists","bjlep : %d, bjhad : %d, cjhad : %d, sjhad : %d",_bjlep_id,_bjhad_id,_cjhad_id,_sjhad_id);
//   // Info("FillCTagControlHists","Loose (cVsB/cVsL) : (%4.3f, %4.3f), Medium (cVsB/cVsL) : (%4.3f, %4.3f), Tight (cVsB/cVsL) : (%4.3f, %4.3f)",
//   //      ctagTh_CvsB_L,ctagTh_CvsL_L, ctagTh_CvsB_M,ctagTh_CvsL_M, ctagTh_CvsB_T,ctagTh_CvsL_T);
//   // Info("FillCTagControlHists","KF jet1 : (pt,eta,phi,M) = (%5.2f, %5.2f, %5.2f, %5.2f)", cjhadAF.Pt(), cjhadAF.Eta() , cjhadAF.Phi() , cjhadAF.M());
//   // Info("FillCTagControlHists","KF jet2 : (pt,eta,phi,M) = (%5.2f, %5.2f, %5.2f, %5.2f)", sjhadAF.Pt(), sjhadAF.Eta() , sjhadAF.Phi() , sjhadAF.M());

//   bool found[2], match[2];
//   double ljet_pt[2];
//   bool foundM[2], matchM[2];
//   double ljet_ptM[2];

//   found[0] = false, found[1] = false;
//   match[0] = false, match[1] = false;

//   foundM[0] = false, foundM[1] = false;
//   matchM[0] = false, matchM[1] = false;

//   for (unsigned int ijet = 0; ijet < selector->Jets.size(); ijet++){
//     if(ijet != _cjhad_id and ijet != _sjhad_id) continue ; 
//     int jetInd = selector->Jets.at(ijet);
//     double jet_CvsL = (selector->useDeepCSVbTag) ? event->jetBtagDeepCvL_[jetInd] : event->jetBtagDeepFlavCvL_[jetInd] ;
//     double jet_CvsB = (selector->useDeepCSVbTag) ? event->jetBtagDeepCvB_[jetInd] : event->jetBtagDeepFlavCvB_[jetInd] ;
//     if(jet_CvsL > ctagTh_CvsL_L and jet_CvsB > ctagTh_CvsB_L) {
//       isIncL = true;
//       count_cJetsIncL++;
//     }
//     if(jet_CvsL > ctagTh_CvsL_M and jet_CvsB > ctagTh_CvsB_M){
//       isIncM = true;
//       count_cJetsIncM++;
//     }
//     if(jet_CvsL > ctagTh_CvsL_T and jet_CvsB > ctagTh_CvsB_T){
//       isIncT = true;
//       count_cJetsIncT++;	
//     }
//     if(jet_CvsL > ctagTh_CvsL_L and jet_CvsB > ctagTh_CvsB_L){
//       // Info("FillCTagControlHists","JA : Loose for ijet : %d, jetInd : %d, (jet_CvsB,jet_CvsL) = (%4.3f, %4.3f), (pflav/hflav) : (%d/%d), (pt,eta,phi,M) = (%5.2f, %5.2f, %5.2f, %5.2f)", 
//       // 	   ijet, jetInd, jet_CvsB, jet_CvsL,
//       // 	   event->jetPartFlvr_[jetInd], event->jetHadFlvr_[jetInd],
//       // 	   selector->JetsPtSmeared.at(ijet), event->jetEta_[jetInd] , event->jetPhi_[jetInd] , event->jetMass_[jetInd]);
//       if(count_cJetsIncL==1) {
// 	found[0] = true;
// 	ljet_pt[0] = selector->JetsPtSmeared.at(ijet);
//       }
//       if(count_cJetsIncL==2) {
// 	found[1] = true;
// 	ljet_pt[1] = selector->JetsPtSmeared.at(ijet);
//       }
//       if(!isData){
// 	int genIdx = int(event->jetGenJetIdx_[jetInd]);
// 	if ( (genIdx>-1) && (genIdx < int(event->nGenJet_))){
// 	  TParticlePDG *partPDG = TDatabasePDG::Instance()->GetParticle(event->GenJet_partonFlavour_[genIdx]);
// 	  // Info("FillCTagControlHists","\tJA : Loose Genjet for particle : \"%s\", (pflav/hflav) : (%d/%d), (pt,eta,phi,M) = (%5.2f, %5.2f, %5.2f, %5.2f)",
// 	  //      partPDG->GetName(),event->GenJet_partonFlavour_[genIdx], event->GenJet_hadronFlavour_[genIdx], 
// 	  //      //event->jetPartFlvr_[jetInd], event->jetHadFlvr_[jetInd], 
// 	  //      event->GenJet_pt_[genIdx], event->GenJet_eta_[genIdx] , event->GenJet_phi_[genIdx], event->GenJet_mass_[genIdx]);
// 	  if(count_cJetsIncL==1){
// 	    if(TMath::Abs(event->GenJet_partonFlavour_[genIdx])==4) match[0] = true;
// 	  }
// 	  if(count_cJetsIncL==2){
// 	    if(TMath::Abs(event->GenJet_partonFlavour_[genIdx])==4) match[1] = true;
// 	  }
// 	}
//       }//if MC
//     }
//     if(jet_CvsL > ctagTh_CvsL_M and jet_CvsB > ctagTh_CvsB_M){
//       // Info("FillCTagControlHists","JA : Medium for ijet : %d, jetInd : %d, (jet_CvsB,jet_CvsL) = (%4.3f, %4.3f), (pt,eta,phi,M) = (%5.2f, %5.2f, %5.2f, %5.2f)", 
//       // 	   ijet, jetInd, jet_CvsB, jet_CvsL,
//       // 	   selector->JetsPtSmeared.at(ijet), event->jetEta_[jetInd] , event->jetPhi_[jetInd] , event->jetMass_[jetInd]);
//       if(count_cJetsIncM==1) {
// 	foundM[0] = true;
// 	ljet_ptM[0] = selector->JetsPtSmeared.at(ijet);
//       }
//       if(count_cJetsIncM==2) {
// 	foundM[1] = true;
// 	ljet_ptM[1] = selector->JetsPtSmeared.at(ijet);
//       }
//       if(!isData){
// 	int genIdx = int(event->jetGenJetIdx_[jetInd]);
// 	if ( (genIdx>-1) && (genIdx < int(event->nGenJet_))){
// 	  TParticlePDG *partPDG = TDatabasePDG::Instance()->GetParticle(event->GenJet_partonFlavour_[genIdx]);
// 	  // Info("FillCTagControlHists","\tJA : Medium Genjet for particle : \"%s\", (pflav/hflav) : (%d/%d), (pt,eta,phi,M) = (%5.2f, %5.2f, %5.2f, %5.2f)",
// 	  //      partPDG->GetName(),event->GenJet_partonFlavour_[genIdx], event->GenJet_hadronFlavour_[genIdx], 
// 	  //      //event->jetPartFlvr_[jetInd], event->jetHadFlvr_[jetInd], 
// 	  //      event->GenJet_pt_[genIdx], event->GenJet_eta_[genIdx] , event->GenJet_phi_[genIdx], event->GenJet_mass_[genIdx]);
// 	  if(count_cJetsIncM==1){
// 	    if(TMath::Abs(event->GenJet_partonFlavour_[genIdx])==4) matchM[0] = true;
// 	  }
// 	  if(count_cJetsIncM==2){
// 	    if(TMath::Abs(event->GenJet_partonFlavour_[genIdx])==4) matchM[1] = true;
// 	  }
// 	}
//       }//if MC
//     }
//     // if(jet_CvsL > ctagTh_CvsL_T and jet_CvsB > ctagTh_CvsB_T){
//     //   Info("FillCTagControlHists","JA : Tight for ijet : %d, jetInd : %d, (jet_CvsB,jet_CvsL) = (%4.3f, %4.3f), (pt,eta,phi,M) = (%5.2f, %5.2f, %5.2f, %5.2f)", 
//     // 	   ijet, jetInd, jet_CvsB, jet_CvsL,
//     // 	   selector->JetsPtSmeared.at(ijet), event->jetEta_[jetInd] , event->jetPhi_[jetInd] , event->jetMass_[jetInd]);
//     //   int genIdx = int(event->jetGenJetIdx_[jetInd]);
//     //   if ( (genIdx>-1) && (genIdx < int(event->nGenJet_))){
//     // 	TParticlePDG *partPDG = TDatabasePDG::Instance()->GetParticle(event->GenJet_partonFlavour_[genIdx]);
//     // 	Info("FillCTagControlHists","\tJA : Tight Genjet for particle : \"%s\", (pflav/hflav) : (%d/%d), (pt,eta,phi,M) = (%5.2f, %5.2f, %5.2f, %5.2f)",
//     // 	     partPDG->GetName(),event->GenJet_partonFlavour_[genIdx], event->GenJet_hadronFlavour_[genIdx], 
//     // 	     //event->jetPartFlvr_[jetInd], event->jetHadFlvr_[jetInd], 
//     // 	     event->GenJet_pt_[genIdx], event->GenJet_eta_[genIdx] , event->GenJet_phi_[genIdx], event->GenJet_mass_[genIdx]);
//     //   }
//     // }
//   }//jet loop
  
//   //ctagLSystType  = "central" ;
//   if(!isData){    
    
//     // if(count_cJetsIncL > 0){
//     //   GetCLtagSF_1a(); 
//     //   if(_cTagLWeight < 0.) return kTRUE;
//     //   // Info("FillCTagControlHists","_cTagLWeight_L %5.2f", _cTagLWeight);
//     //   if(found[0] and !found[1]){
//     // 	((TProfile *) listL->FindObject("ctagL_s"))->Fill(ljet_pt[0], _cTagLWeight);
//     // 	if(match[0])
//     // 	  ((TProfile *) listL->FindObject("ctagL_s_p"))->Fill(ljet_pt[0], _cTagLWeight);
//     // 	else
//     // 	  ((TProfile *) listL->FindObject("ctagL_s_f"))->Fill(ljet_pt[0], _cTagLWeight);
//     //   }
//     //   if(found[0] and found[1]){
//     // 	((TProfile *) listL->FindObject("ctagL_d"))->Fill((ljet_pt[0]+ljet_pt[1])/2.0, _cTagLWeight);
//     // 	if(match[0] and match[1])
//     // 	  ((TProfile *) listL->FindObject("ctagL_d_pp"))->Fill((ljet_pt[0]+ljet_pt[1])/2.0, _cTagLWeight);
//     // 	if(match[0] and !match[1])
//     // 	  ((TProfile *) listL->FindObject("ctagL_d_pf"))->Fill(ljet_pt[0], _cTagLWeight);
//     // 	if(!match[0] and match[1])
//     // 	  ((TProfile *) listL->FindObject("ctagL_d_pf"))->Fill(ljet_pt[1], _cTagLWeight);
//     // 	if(!match[0] and !match[1])
//     // 	  ((TProfile *) listL->FindObject("ctagL_d_ff"))->Fill((ljet_pt[0]+ljet_pt[1])/2.0, _cTagLWeight);
//     //   }
//     // }
//     // if(count_cJetsIncM > 0){
//     //   GetCMtagSF_1a(); 
//     //   if(_cTagMWeight < 0.) return kTRUE;
//     //   //Info("FillCTagControlHists","_cTagLWeight_M %5.2f", _cTagLWeight);
//     //   if(found[0] and !foundM[1]){
//     // 	((TProfile *) listM->FindObject("ctagL_s"))->Fill(ljet_pt[0], _cTagLWeight);
//     // 	if(matchM[0])
//     // 	  ((TProfile *) listM->FindObject("ctagL_s_p"))->Fill(ljet_pt[0], _cTagLWeight);
//     // 	else
//     // 	  ((TProfile *) listM->FindObject("ctagL_s_f"))->Fill(ljet_pt[0], _cTagLWeight);
//     //   }
//     //   if(foundM[0] and foundM[1]){
//     // 	((TProfile *) listM->FindObject("ctagL_d"))->Fill((ljet_pt[0]+ljet_pt[1])/2.0, _cTagLWeight);
//     // 	if(matchM[0] and matchM[1])
//     // 	  ((TProfile *) listM->FindObject("ctagL_d_pp"))->Fill((ljet_pt[0]+ljet_pt[1])/2.0, _cTagLWeight);
//     // 	if(matchM[0] and !matchM[1])
//     // 	  ((TProfile *) listM->FindObject("ctagL_d_pf"))->Fill(ljet_pt[0], _cTagLWeight);
//     // 	if(!matchM[0] and matchM[1])
//     // 	  ((TProfile *) listM->FindObject("ctagL_d_pf"))->Fill(ljet_pt[1], _cTagLWeight);
//     // 	if(!matchM[0] and !matchM[1])
//     // 	  ((TProfile *) listM->FindObject("ctagL_d_ff"))->Fill((ljet_pt[0]+ljet_pt[1])/2.0, _cTagLWeight);
//     //   }
//     // }
//     // if(count_cJetsIncT > 0){
//     //   GetCTtagSF_1a(); 
//     //   if(_cTagTWeight < 0.) return kTRUE;
//     // }
    
//   }//isMC


//   // if(!isData){    
    
//   //   TLorentzVector bjet1,bjet2,ljet1,ljet2,lep,neu;
//   //   for (unsigned int imc = 0 ; imc < event->nLHEPart_ ; imc++ ){      
//   //     TParticlePDG *partPDG = TDatabasePDG::Instance()->GetParticle(event->LHEPart_pdgId_[imc]);
//   //     if(!partPDG){
//   // 	printf("\t CTag : LHE : %03d, PDG : %5d ( noPDGname), (Pt, Eta, Phi, Mass, R) = (%5.2f, %5.2f, %5.2f, %5.2f, %5.2f)\n", 
//   // 	       imc, event->LHEPart_pdgId_[imc], event->LHEPart_pt_[imc], 
//   // 	       event->LHEPart_eta_[imc] , event->LHEPart_phi_[imc], event->LHEPart_mass_[imc], TMath::Sqrt(event->LHEPart_eta_[imc]*event->LHEPart_eta_[imc] + event->LHEPart_phi_[imc]*event->LHEPart_phi_[imc]) );
	
//   //     }else{
//   // 	printf("\t Ctag : LHE : %03d, PDG : %5d (%7s), (Pt, Eta, Phi, Mass, R) = (%5.2f, %5.2f, %5.2f, %5.2f, %5.2f)\n", 
//   // 	       imc, event->LHEPart_pdgId_[imc], partPDG->GetName(), event->LHEPart_pt_[imc],
//   // 	       event->LHEPart_eta_[imc] , event->LHEPart_phi_[imc], event->LHEPart_mass_[imc], TMath::Sqrt(event->LHEPart_eta_[imc]*event->LHEPart_eta_[imc] + event->LHEPart_phi_[imc]*event->LHEPart_phi_[imc]) );
//   //     }
//   //     if(event->LHEPart_pdgId_[imc]==5 and imc>=2) 
//   // 	bjet1.SetPtEtaPhiM(event->LHEPart_pt_[imc], event->LHEPart_eta_[imc] , event->LHEPart_phi_[imc], event->LHEPart_mass_[imc]);
//   //     if(event->LHEPart_pdgId_[imc]==-5 and imc>=2) 
//   // 	bjet2.SetPtEtaPhiM(event->LHEPart_pt_[imc], event->LHEPart_eta_[imc] , event->LHEPart_phi_[imc], event->LHEPart_mass_[imc]);
//   //     if((TMath::Abs(event->LHEPart_pdgId_[imc])==11 or TMath::Abs(event->LHEPart_pdgId_[imc])==12 or TMath::Abs(event->LHEPart_pdgId_[imc])==15) and imc>=2) 
//   // 	lep.SetPtEtaPhiM(event->LHEPart_pt_[imc], event->LHEPart_eta_[imc] , event->LHEPart_phi_[imc], event->LHEPart_mass_[imc]);
//   //     if((TMath::Abs(event->LHEPart_pdgId_[imc])==12 or TMath::Abs(event->LHEPart_pdgId_[imc])==12 or TMath::Abs(event->LHEPart_pdgId_[imc])==12) and imc>=2) 
//   // 	neu.SetPtEtaPhiM(event->LHEPart_pt_[imc], event->LHEPart_eta_[imc] , event->LHEPart_phi_[imc], event->LHEPart_mass_[imc]);
//   //     if((event->LHEPart_pdgId_[imc]>=1 and event->LHEPart_pdgId_[imc]<=4) and imc>=2) 
//   // 	ljet1.SetPtEtaPhiM(event->LHEPart_pt_[imc], event->LHEPart_eta_[imc] , event->LHEPart_phi_[imc], event->LHEPart_mass_[imc]);
//   //     if((event->LHEPart_pdgId_[imc]>=-4 and event->LHEPart_pdgId_[imc]<=-1) and imc>=2) 
//   // 	ljet2.SetPtEtaPhiM(event->LHEPart_pt_[imc], event->LHEPart_eta_[imc] , event->LHEPart_phi_[imc], event->LHEPart_mass_[imc]);
//   //   }// mc particle loop

//   //   for (unsigned int ijet = 0; ijet < selector->Jets.size(); ijet++){
//   //     //if(ijet != _cjhad_id and ijet != _sjhad_id) continue ; 
//   //     int jetInd = selector->Jets.at(ijet);
//   //     if( (TMath::Abs(event->jetPartFlvr_[jetInd])>=1 and TMath::Abs(event->jetPartFlvr_[jetInd])<=4) or TMath::Abs(event->jetPartFlvr_[jetInd])==21) 
//   // 	printf("\t ljet JetArray : (flav, btag) : (%d, %3.2f), (pt,eta,phi,M,R) = (%5.2f, %5.2f, %5.2f, %5.2f, %5.2f)\n", 
//   // 	       event->jetPartFlvr_[jetInd], event->jetBtagDeepFlavB_[jetInd],
//   // 	       selector->JetsPtSmeared.at(ijet), event->jetEta_[jetInd] , event->jetPhi_[jetInd] , event->jetMass_[jetInd],
//   // 	       TMath::Sqrt(event->jetEta_[jetInd]*event->jetEta_[jetInd] + event->jetPhi_[jetInd]*event->jetPhi_[jetInd]));
//   //   }

//   //   TLorentzVector jet;
//   //   for (unsigned int ijet = 0; ijet < selector->Jets.size(); ijet++){
//   //     //if(ijet != _cjhad_id and ijet != _sjhad_id) continue ; 
//   //     int jetInd = selector->Jets.at(ijet);
      
//   //     if(ijet == _cjhad_id){
//   // 	jet.SetPtEtaPhiE(_jetChadPt, _jetChadEta , _jetChadPhi , _jetChadEnergy);
//   // 	Info("FillCTagControlHists","ljet1 KinFit : (pt,eta,phi,M,R) = (%5.2f, %5.2f, %5.2f, %5.2f, %5.2f)", 
//   // 	     _jetChadPt, _jetChadEta , _jetChadPhi , jet.M(),
//   // 	     TMath::Sqrt(_jetChadEta*_jetChadEta + _jetChadPhi*_jetChadPhi));
//   // 	// Info("FillCTagControlHists","ljet1 JetArray : (pt,eta,phi,M,R,btag) = (%5.2f, %5.2f, %5.2f, %5.2f, %5.2f, %3.2f)", 
//   // 	//      selector->JetsPtSmeared.at(ijet), event->jetEta_[jetInd] , event->jetPhi_[jetInd] , event->jetMass_[jetInd],
//   // 	//      TMath::Sqrt(event->jetEta_[jetInd]*event->jetEta_[jetInd] + event->jetPhi_[jetInd]*event->jetPhi_[jetInd]), event->jetBtagDeepFlavB_[jetInd]);
//   // 	// int genIdx = int(event->jetGenJetIdx_[jetInd]);
//   // 	// if ( (genIdx>-1) && (genIdx < int(event->nGenJet_))){
//   // 	//   TParticlePDG *partPDG = TDatabasePDG::Instance()->GetParticle(event->GenJet_partonFlavour_[genIdx]);
//   // 	//   Info("FillCTagControlHists","ljet1 GenJet : (flav,pt,eta,phi,M) = (%d, %5.2f, %5.2f, %5.2f, %5.2f)",
//   // 	//        //partPDG->GetName(),event->GenJet_partonFlavour_[genIdx], event->GenJet_hadronFlavour_[genIdx], 
//   // 	//        event->GenJet_partonFlavour_[genIdx],
//   // 	//        event->GenJet_pt_[genIdx], event->GenJet_eta_[genIdx] , event->GenJet_phi_[genIdx], event->GenJet_mass_[genIdx]);
//   // 	// }//genIdx
//   //     }//if ljet 1
      
//   //     if(ijet == _sjhad_id){
//   // 	jet.SetPtEtaPhiE(_jetShadPt, _jetShadEta , _jetShadPhi , _jetShadEnergy);
//   // 	Info("FillCTagControlHists","ljet2 KinFit : (pt,eta,phi,M,R) = (%5.2f, %5.2f, %5.2f, %5.2f, %5.2f)", 
//   // 	     _jetShadPt, _jetShadEta , _jetShadPhi , jet.M(),
//   // 	     TMath::Sqrt(_jetShadEta*_jetShadEta + _jetShadPhi*_jetShadPhi));
//   // 	// Info("FillCTagControlHists","ljet2 JetArray : (pt,eta,phi,M,R,btag) = (%5.2f, %5.2f, %5.2f, %5.2f, %5.2f, %3.2f)", 
//   // 	//      selector->JetsPtSmeared.at(ijet), event->jetEta_[jetInd] , event->jetPhi_[jetInd] , event->jetMass_[jetInd],
//   // 	//      TMath::Sqrt(event->jetEta_[jetInd]*event->jetEta_[jetInd] + event->jetPhi_[jetInd]*event->jetPhi_[jetInd]), event->jetBtagDeepFlavB_[jetInd]);
//   // 	// int genIdx = int(event->jetGenJetIdx_[jetInd]);
//   // 	// if ( (genIdx>-1) && (genIdx < int(event->nGenJet_))){
//   // 	//   TParticlePDG *partPDG = TDatabasePDG::Instance()->GetParticle(event->GenJet_partonFlavour_[genIdx]);
//   // 	//   Info("FillCTagControlHists","ljet2 GenJet : (flav,pt,eta,phi,M) = (%d, %5.2f, %5.2f, %5.2f, %5.2f)",
//   // 	//        //partPDG->GetName(),event->GenJet_partonFlavour_[genIdx], event->GenJet_hadronFlavour_[genIdx], 
//   // 	//        event->GenJet_partonFlavour_[genIdx],
//   // 	//        event->GenJet_pt_[genIdx], event->GenJet_eta_[genIdx] , event->GenJet_phi_[genIdx], event->GenJet_mass_[genIdx]);
//   // 	// }//genIdx
//   //     }//if ljet 1

//   //   }//jet loop

//   // }//if MC

//   return true;
// }

//_____________________________________________________________________________
void KinAna::SlaveTerminate()
{
  
  Info("SlaveTerminate",
       "sample : %s, year : %d, mode : %s", fSample.Data(), fYear, fMode.Data());

  
  // File closure
  TDirectory *savedir = gDirectory;
  
  for(int ifile=0;ifile<1;ifile++){

    savedir->cd();
    
    fFile[ifile]->cd();
    
    for(int isyst=0;isyst<fNSyst;isyst++){

      //method 1
      //fFileDir[isyst*fNDDReg + 0]->cd();
      // for(int icf=0;icf<fNBCFHists;icf++){
      // 	cout << "index : " << fNCFHists*isyst + icf << endl;
      // 	hCutFlow[fNCFHists*isyst + icf]->Write();
      // }
      //method 2
      // for(int il=0;il<fFileDir[isyst*fNDDReg + 0]->GetList()->GetEntries();il++)
      // 	fFileDir[isyst*fNDDReg + 0]->GetList()->At(il)->Write();
      //method 3
      //fFileDir[isyst*fNDDReg + 0]->Write();

      fFileDir[isyst*fNDDReg + 0]->Write();
      fFileDir[isyst*fNDDReg + 1]->Write();
      fFileDir[isyst*fNDDReg + 2]->Write();
      fFileDir[isyst*fNDDReg + 3]->Write();
      fFileDir[isyst*fNDDReg + 0]->cd();
      
      // hMinChi2_mu->Write();
      // h2MinChi2_mu->Write();
      // h3MinChi2_mu->Write();
      // h4MinChi2_mu->Write();
      // h5MinChi2_mu->Write();
      
      // hMinChi2_ele->Write();
      // h2MinChi2_ele->Write();
      // h3MinChi2_ele->Write();
      // h4MinChi2_ele->Write();
      // h5MinChi2_ele->Write();

      fFile[ifile]->cd();
    }
    fFile[ifile]->cd();
    
    // for(int iscl=0;iscl<fNBSelCols;iscl++)
    //   fSelColDir[iscl]->Write();

    fFile[ifile]->cd();

    // for(int icheck=0;icheck<fNWtHists;icheck++)
    //   histWt[icheck]->Write();
    // for(int icheck=0;icheck<fNObHists;icheck++)
    //   histObs[icheck]->Write();

    
    
      
    fFile[ifile]->cd();
    
    savedir->cd();
    
    fFile[ifile]->Close();
    
    
    if (fMode.BeginsWith("proof")) {
      Info("SlaveTerminate", "objects saved into '%s%s': sending related TProofOutputFile ...",
	   fProofFile[ifile]->GetFileName(), fProofFile[ifile]->GetOptionsAnchor());
      fProofFile[ifile]->Print();
      fOutput->Add(fProofFile[ifile]);    
    }
    
  }//file loop
  
  if(fRefF)
    delete fRefF;
  
  // for(int ifile=1;ifile<2;ifile++){
    
  //   savedir->cd();
    
  //   fFile[ifile]->cd();
  //   if(doTreeSave){
  //     outputTree->Write();
  //   }
  //   fFile[ifile]->Close();
  //   savedir->cd();

  //   if (fMode.BeginsWith("proof")) {
  //     Info("SlaveTerminate", "objects saved into '%s%s': sending related TProofOutputFile ...",
  // 	   fProofFile[ifile]->GetFileName(), fProofFile[ifile]->GetOptionsAnchor());
  //     fProofFile[ifile]->Print();
  //     fOutput->Add(fProofFile[ifile]);    
  //   }
  // }

  // for(int ifile=2;ifile<3;ifile++){
  //   savedir->cd();
  //   fFile[ifile]->cd();
  //   if(doTreeSave){
  //     outputBjetTree->Write();
  //   }
  //   fFile[ifile]->Close();
  //   savedir->cd();

  //   if (fMode.BeginsWith("proof")) {
  //     Info("SlaveTerminate", "objects saved into '%s%s': sending related TProofOutputFile ...",
  // 	   fProofFile[ifile]->GetFileName(), fProofFile[ifile]->GetOptionsAnchor());
  //     fProofFile[ifile]->Print();
  //     fOutput->Add(fProofFile[ifile]);    
  //   }
  // }

  // if(PUweighter)
  //   delete PUweighter;
  // if(PUweighterUp)
  //   delete PUweighterUp;
  // if(PUweighterDown)
  //   delete PUweighterDown;
    
  // if(jecvar)
  //   delete jecvar;
  // if(jecvara)
  //   delete jecvar;
  // if(jecvarb)
  //   delete jecvar;
  
  // if(fBCSFFile)
  //   delete fBCSFFile;

  // if(fPUJetIDa)
  //   delete fPUJetIDa;
  // if(fPUJetIDb)
  //   delete fPUJetIDb;
  // if(fPUJetID)
  //   delete fPUJetID;

  // if(event)
  //   delete event;
  // if(selector)
  //   delete selector;
  // if(evtPick)
  //   delete evtPick;
  
  // if(muSFa)
  //   delete muSFa ;
  // if(muSFb)
  //   delete muSFb ;
  // if(eleSFa)
  //   delete eleSFa ;
  // if(eleSFb)
  //   delete eleSFb ;
  
  // if(f_trackSF_BCDEF)
  //   delete f_trackSF_BCDEF;
  // if(f_trackSF_GH)
  //   delete f_trackSF_GH;
  
  // // if(fSystList)
  // //   delete fSystList;
  // fSystList.clear();

  // totEvents.clear();
  // totEventsUS.clear();
  // fnameList.clear();

  // crossSections.clear();
  // numberOfEvents.clear();
  // LumiWZ.clear();
  
  // kinFit.UnloadObjReso();
}

//_____________________________________________________________________________
void KinAna::Terminate()
{
// function called at the end of the event loop

   if (!fInput) Info("Terminate", "processed %lld events", fProcessed);
   
   TString option = GetOption();
   Info("Terminate", "stopping KinAna with process option: %s", option.Data());
   
}

bool KinAna::ExecSerial(const char* infile)
{
  
  TString option = GetOption();
  Info("ExecSerial", "starting KinAna with process option: %s", option.Data());
  Info("ExecSerial", "opening file %s", infile);
  
  TFile *fin = TFile::Open(infile);
  TTree *tree = (TTree *)fin->Get("Kinfit_Reco");
  SlaveBegin(tree);
  tree->GetEntry(0);
  Notify();
  for(Long64_t ientry = 0 ; ientry < tree->GetEntries() ; ientry++){
  //for(Long64_t ientry = 0 ; ientry < 20000 ; ientry++){
  //for(Long64_t ientry = 0 ; ientry < 100000 ; ientry++){
  //for(Long64_t ientry = 0 ; ientry < 500000 ; ientry++){
  //for(Long64_t ientry = 0 ; ientry < 10 ; ientry++){
  //cout<<"Procesing : " << ientry << endl;
    Process(ientry);
  }
  SlaveTerminate();
  
  fin->Close();
  delete fin;
  
  return true;
}

// int main(int argc, char** argv)
// {
//   // year=$1
//   // sample=$2
//   // input=$3
//   // index=$4
//   // syst=$5
  
//   TString op(Form("sample=%s|year=%s|input=%s|index=%s|syst=%s|aod=nano|run=prod|trs=yes",argv[1],argv[2],argv[3],argv[4],argv[5]));

//   cout << "Input filename: " << argv[3] << endl;
//   ifstream fin(argv[3]);
//   int index = atoi(argv[4]);
  
//   string s;
//   int idx = 0;
//   string inputfile = ""; 
//   while(getline(fin,s)){
//     //cout << s << endl;
//     if(idx==index){
//       inputfile = s.c_str();
//     }
//     idx++;
//   }
//   cout <<" Total files "<<idx<<endl; 
//   op += Form("|total=%d",idx); 
 
//   TString hostname = gSystem->HostName();
//   string singleFile = inputfile.substr(inputfile.find_last_of("/")+1,inputfile.size());
//   string xrdcp_command = "";
//   if( hostname.BeginsWith("Indra-Rjn") or hostname.BeginsWith("lnx3") )
//     //xrdcp_command = "cp " + inputfile + " " + singleFile ;
//     xrdcp_command = "ln -s " + inputfile + " " + singleFile ;
//   else
//     xrdcp_command = "xrdcp " + inputfile + " " + singleFile ;
//   cout << xrdcp_command.c_str() << endl;
//   system(xrdcp_command.c_str());
 
//   KinAna *kinana = new KinAna();
//   kinana->SetOption(op.Data());
//   kinana->ExecSerial(singleFile.c_str());
//   delete kinana;
  
//   return 1;
// }


int HistoBuilder()
{

  // year=$1
  // sample=$2
  // input=$3
  // index=$4
  // syst=$5

  string sig = "TTbar";
  string syst = "base";
  string sample_extn = "CBA_CTagValidated";
  string input_path = "/run/media/indra/DHEP_Storage_3/Data/NanoAOD/KinFit/"+sample_extn+"/pre/2016/";
  string input_file_list = "/tmp/histbuild_fl.txt";
  string input_hist_file = "root_files/grid_v40_Syst/"+sample_extn+"/pre/all_TTbar.root";
  string command  = Form("find %s -name \"%s_tree_%s\*.root\" > %s",input_path.c_str(), sig.c_str(), syst.c_str(), input_file_list.c_str());  
  cout << command << endl;
  system(command.c_str());

  const char *year = "2016";
  const char *file_index = "0";

  // TString op(Form("sample=%s|year=%s|input=%s|index=%s|syst=%s|aod=nano|run=prod|trs=yes",argv[1],argv[2],argv[3],argv[4],argv[5]));
  
  TString op(Form("sample=%s|year=%s|input=%s|index=%s|ref=%s|syst=%s|run=prod",sig.c_str(),year,input_file_list.c_str(),file_index,input_hist_file.c_str(),syst.c_str()));
  
  // TChain *tr = new TChain("Kinfit_Reco");

  cout << "Input filename: " << input_file_list << endl;
  ifstream fin(input_file_list.c_str());
  int index = atoi(file_index);
  
  string s;
  int idx = 0;
  string inputfile = ""; 
  while(getline(fin,s)){
    //cout << s << endl;
    if(idx==index){
      inputfile = s.c_str();
    }
    idx++;
  }
  cout <<" Total files "<<idx<<endl; 
  op += Form("|total=%d",idx); 
 
  TString hostname = gSystem->HostName();
  string singleFile = inputfile.substr(inputfile.find_last_of("/")+1,inputfile.size());
  string refFile = input_hist_file.substr(input_hist_file.find_last_of("/")+1,input_hist_file.size());
  
  string xrdcp_command = "";
  string xrdcp_command2 = "";
  if( hostname.BeginsWith("Indra-Rjn") or hostname.BeginsWith("lnx3") ){
    //xrdcp_command = "cp " + inputfile + " " + singleFile ;
    xrdcp_command = "ln -s " + inputfile + " " + singleFile ;
    xrdcp_command2 = "ln -s " + input_hist_file + " " + refFile ;
  }else{
    xrdcp_command = "xrdcp " + inputfile + " " + singleFile ;
    xrdcp_command2 = "xrdcp " + input_hist_file + " " + refFile ;
  }
  cout << xrdcp_command.c_str() << endl;
  system(xrdcp_command.c_str());
  cout << xrdcp_command2.c_str() << endl;
  system(xrdcp_command2.c_str());
 
  KinAna *kinana = new KinAna();
  kinana->SetOption(op.Data());
  kinana->SetRefFile(refFile.c_str());
  kinana->ExecSerial(singleFile.c_str());
  delete kinana;
  
  return 1;
  
}
