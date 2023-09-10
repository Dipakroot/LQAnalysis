/**********************************************************************
 Created on : 14/07/2021
 Purpose    : Analyse the Skim tree.
              (format adapted from h1analysis)
 Author     : Indranil Das, Visiting Fellow, TIFR
 Email      : indranil.das@cern.ch | indra.ehep@gmail.com
 Adapted to work on LQ -> Ttau analysis
**********************************************************************/

#ifndef SkimAna_h
#define SkimAna_h

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

#include "interface/PUReweight.h"
#include "interface/EventTree.h"
#include "interface/Selector.h"
#include "interface/EventPick.h"
#include "interface/ScaleFactorFunction.h"
#include "interface/JECvariation.h"
#include "interface/UncertaintySourcesList.h"
#include "interface/muSF_reader.h"
#include "interface/eleSF_reader.h"
#include "interface/BTagCalibrationStandalone.h"

#include "TMath.h"
#include "TLorentzVector.h"
#include "PhysicsTools/KinFitter/interface/TFitConstraintM.h"
#include "PhysicsTools/KinFitter/interface/TFitConstraintMGaus.h"
#include "PhysicsTools/KinFitter/interface/TFitConstraintEp.h"
#include "PhysicsTools/KinFitter/interface/TFitParticleEtEtaPhi.h"
#include "PhysicsTools/KinFitter/interface/TFitParticleEScaledMomDev.h"
#include "PhysicsTools/KinFitter/interface/TFitParticleMCMomDev.h"
#include "PhysicsTools/KinFitter/interface/TKinFitter.h"

#include "correction.h"

#ifndef MCONLY
#include "rapidjson/document.h"
#endif

class  TH1F;
class  TH1D;
class  TH2D;
class  TH2F;

typedef struct  {
  double chi2, mass, mW, A, B;
  int ndf, nb_iter;
  unsigned int bjlep_id, bjhad_id, cjhad_id, sjhad_id;
  double chi2_thad, chi2_tlep ;
  TLorentzVector leptonAF, neutrinoAF, bjlepAF, bjhadAF, cjhadAF, sjhadAF;  
  TLorentzVector leptonBF, neutrinoBF, bjlepBF, bjhadBF, cjhadBF, sjhadBF;    
  TLorentzVector leptonAF_tlep, neutrinoAF_tlep, bjlepAF_tlep; 
  TLorentzVector bjhadAF_thad,  cjhadAF_thad,    sjhadAF_thad;  
  double  reslepEta, reslepPhi, resneuEta, resneuPhi, resbjlepEta, resbjlepPhi, resbjhadEta, resbjhadPhi, rescjhadEta, rescjhadPhi, ressjhadEta, ressjhadPhi ; 
} Chi2Array;


bool compareChi2Array(Chi2Array i1, Chi2Array i2)
{
  return (i1.chi2 < i2.chi2);
}

class METzCalculator {

 public:
  /// constructor
  METzCalculator();
  //METzCalculator(const edm::ParameterSEt& iConf);
  /// destructor
  virtual ~METzCalculator();
  /// Set MET
  void SetMET(TLorentzVector MET) {
    MET_ = MET;
  }
  /// Set Muon
  void SetLepton(TLorentzVector lepton) {
    lepton_ = lepton;
  }
  /// Set lepton type. The default (set in the constructor) is "muon"
  /// to be compatible with earlier code.
  /// The values are from the 2010 PDG tables.
  void SetLeptonType(std::string leptonName) {
    if(leptonName == "muon")      leptonMass_ = 0.105658367;
    if(leptonName == "electron")  leptonMass_ = 0.00051099891;
    if(leptonName == "tau")       leptonMass_ = 1.77682;
  }

  /// Calculate MEz
  /// options to choose roots from quadratic equation:
  /// type = 0 (defalut): if real roots, pick the one nearest to
  ///                     the lepton Pz except when the Pz so chosen
  ///                     is greater than 300 GeV in which case pick
  ///                     the most central root.
  /// type = 1: if real roots, choose the one closest to the lepton Pz
  ///           if complex roots, use only the real part.
  /// type = 2: if real roots, choose the most central solution.
  ///           if complex roots, use only the real part.
  /// type = 3: if real roots, pick the largest value of the cosine*
  double Calculate(int type = 0);
  /// check for complex root
  bool IsComplex() const { return isComplex_; };
  double getOther() const { return otherSol_; };
  void Print() {
    std::cout << " METzCalculator: pxmu = " << lepton_.Px() << " pzmu= " << lepton_.Pz() << std::endl;
    std::cout << " METzCalculator: pxnu = " << MET_.Px() << " pynu= " << MET_.Py() << std::endl;
  }
	
 private:
	
  bool isComplex_;
  TLorentzVector lepton_;
  TLorentzVector MET_;
  double otherSol_;
  double leptonMass_;
};

class KinFit{

 public:

    enum LeptonType {kElectron, kMuon, kTau};
  
    KinFit(){
      Clear();
      mTop	 = 172.76;
      isComplex  = false;
      useExtReso = false;
      fResoIn	 = 0x0;
    }
    
    // The following are the mandatory setters
    /////////////////////////////////////////////////////////////////////////////
    // For a given year
    void SetBtagThresh(double thresh_){ btagThresh		= thresh_;}

    // For a given event
    void Clear(){
      	//--------------------
	_nu_px	     = -9999.0;
	_nu_py	     = -9999.0;
	_nu_pz	     = -9999.0; 
	_nu_pz_other = -9999.0; 
	_nu_pt	     = -9999.0;
	_nu_phi	     = -9999.0;
	leptonType   = kTau;

	//--------------------
	nCombinations = 0;
	nCombinations_tlep = 0;			
	nCombinations_thad = 0;

	jets.clear();
	jetsRes.clear();
	btag.clear();


	leptonAF.clear();        neutrinoAF.clear(); 	      bjlepAF.clear();
	leptonUM.clear();        neutrinoUM.clear();        bjlepUM.clear(); 
	leptonAF_tlep.clear();   neutrinoAF_tlep.clear();   bjlepAF_tlep.clear();

	bjhadAF.clear(); 	       cjhadAF.clear();           sjhadAF.clear();
	bjhadUM.clear();	       cjhadUM.clear();           sjhadUM.clear();
	bjhadAF_thad.clear();    cjhadAF_thad.clear();      sjhadAF_thad.clear();

	blep_id.clear();	  bhad_id.clear();	    chad_id.clear();	shad_id.clear();
	Chi2.clear();	      Chi2_tlep.clear();	Chi2_thad.clear();
	NDF.clear();        Nb_Iter.clear();
	  
	ReslepEta.clear();	ReslepPhi.clear();	  	ResneuEta.clear();		ResneuPhi.clear();
	ResbjlepEta.clear();	ResbjlepPhi.clear();	ResbjhadEta.clear();	ResbjhadPhi.clear();
	RescjhadEta.clear();	RescjhadPhi.clear();	RessjhadEta.clear();	RessjhadPhi.clear(); 

	  
    }    
    void SetJetVector(std::vector<TLorentzVector> jets_){ jets	= jets_;}
    void SetJetResVector(std::vector<double> jetres_){ jetsRes	= jetres_;}
    void SetBtagVector(std::vector<double> jetsTag_){ btag	= jetsTag_;}
    void SetLepton(TLorentzVector lepton_){ lepton		= lepton_;}
    void SetLeptonType(LeptonType ltype_){ leptonType		= ltype_;} 
    void SetMET(double px_, double py_, double pz_, double pz_other_) {  
      _nu_px	   = px_;
      _nu_py	   = py_;
      _nu_pz	   = pz_;
      _nu_pz_other = pz_other_;
    }
    void SetMETPtPhi(double MET_pt_ , double MET_phi_) {
      _nu_pt	   = MET_pt_;
      _nu_phi	   = MET_phi_;
    }
    /////////////////////////////////////////////////////////////////////////////

    // The following are the optional setters
    /////////////////////////////////////////////////////////////////////////////
    void SetTopMass(double topMass) { mTop = topMass ;}

    // external inputs for jet/lep/met resolution estimation 
    void SetResoInputPath(std::string inputPathReso) {inputResoPath = inputPathReso;}
    void LoadObjReso();
    void UseExtReso()  { useExtReso = true;}
    void UnloadObjReso();
    /////////////////////////////////////////////////////////////////////////////
    
    // The return of fit function is "true" if fit is converged
    /////////////////////////////////////////////////////////////////////////////
    bool Fit();
    /////////////////////////////////////////////////////////////////////////////
    
    // The following are the minimal getters
    /////////////////////////////////////////////////////////////////////////////
    unsigned int	GetNCombinations()		{ return nCombinations;}
    TLorentzVector	GetLepton(unsigned int i)	{ return leptonAF.at(i);}
    TLorentzVector	GetNeutrino(unsigned int i)	{ return neutrinoAF.at(i);}
    TLorentzVector	GetBLepton(unsigned int i)	{ return bjlepAF.at(i);}
    TLorentzVector	GetBHadron(unsigned int i)	{ return bjhadAF.at(i);}
    TLorentzVector	GetCHadron(unsigned int i)	{ return cjhadAF.at(i);}
    TLorentzVector	GetSHadron(unsigned int i)	{ return sjhadAF.at(i);}

    unsigned int	GetNCombinations_tlep()		{ return nCombinations_tlep;}
    TLorentzVector	GetLepton_tlep(unsigned int i)	{ return leptonAF_tlep.at(i);}
    TLorentzVector	GetNeutrino_tlep(unsigned int i){ return neutrinoAF_tlep.at(i);}
    TLorentzVector	GetBLepton_tlep(unsigned int i)	{ return bjlepAF_tlep.at(i);}

    unsigned int	GetNCombinations_thad()		{ return nCombinations_thad;}
    TLorentzVector	GetBHadron_thad(unsigned int i)	{ return bjhadAF_thad.at(i);}
    TLorentzVector	GetCHadron_thad(unsigned int i)	{ return cjhadAF_thad.at(i);}
    TLorentzVector	GetSHadron_thad(unsigned int i)	{ return sjhadAF_thad.at(i);}

    unsigned int	GetJetID_BLep(unsigned int i)	{ return blep_id.at(i);}
    unsigned int	GetJetID_BHad(unsigned int i)	{ return bhad_id.at(i);}
    unsigned int	GetJetID_CHad(unsigned int i)	{ return chad_id.at(i);}
    unsigned int	GetJetID_SHad(unsigned int i)	{ return shad_id.at(i);}
    /////////////////////////////////////////////////////////////////////////////
    
    // The following are the additional getters
    /////////////////////////////////////////////////////////////////////////////
    TLorentzVector	GetLeptonUM(unsigned int i)	{ return leptonUM.at(i);}
    TLorentzVector	GetNeutrinoUM(unsigned int i)	{ return neutrinoUM.at(i);}
    TLorentzVector	GetBLeptonUM(unsigned int i)	{ return bjlepUM.at(i);}
    TLorentzVector	GetBHadronUM(unsigned int i)	{ return bjhadUM.at(i);}
    TLorentzVector	GetCHadronUM(unsigned int i)	{ return cjhadUM.at(i);}
    TLorentzVector	GetSHadronUM(unsigned int i)	{ return sjhadUM.at(i);}

    bool		IsComplex()                     { return isComplex; };
    int			GetNDF(unsigned int i)		{ return NDF.at(i); }
    int			GetNumberOfIter(unsigned int i)	{ return Nb_Iter.at(i); }	// Number of iterations to converge
    double		GetChi2(unsigned int i)		{ return Chi2.at(i); }
    double		GetChi2_tlep(unsigned int i)	{ return Chi2_tlep.at(i); }
    double		GetChi2_thad(unsigned int i)	{ return Chi2_thad.at(i); }
    
    double              GetResLepEta(unsigned int i)    { return ReslepEta.at(i);}
    double              GetResLepPhi(unsigned int i)    { return ReslepPhi.at(i);}
    double              GetResNeuEta(unsigned int i)    { return ResneuEta.at(i);}
    double              GetResNeuPhi(unsigned int i)    { return ResneuPhi.at(i);}
    double              GetResBjLepEta(unsigned int i)  { return ResbjlepEta.at(i);}
    double              GetResBjLepPhi(unsigned int i)  { return ResbjlepPhi.at(i);}
    double              GetResBjHadEta(unsigned int i)  { return ResbjhadEta.at(i);}
    double              GetResBjHadPhi(unsigned int i)  { return ResbjhadPhi.at(i);}
    double              GetResCjHadEta(unsigned int i)  { return RescjhadEta.at(i);}
    double              GetResCjHadPhi(unsigned int i)  { return RescjhadPhi.at(i);}
    double              GetResSjHadEta(unsigned int i)  { return RessjhadEta.at(i);}
    double              GetResSjHadPhi(unsigned int i)  { return RessjhadPhi.at(i);}
    double		GetBtagThresh()                 { return btagThresh; }
    double		GetTopMass()                    { return mTop; }

    /////////////////////////////////////////////////////////////////////////////
    
    struct PtDescending
    {
      inline bool operator() (const pair<unsigned int, TLorentzVector>& a, const pair<unsigned int, TLorentzVector>& b)
      {
        return (a.second.Pt() > b.second.Pt());
      }
    };

 private:
    
    void	print(TKinFitter *fitter);
    
    // The elements of covariance matrix setup following CMS NOTE AN 2005/005
    double	ErrEt(float Et, float Eta) ;
    double	ErrEta(float Et, float Eta) ;
    double	ErrPhi(float Et, float Eta) ;
	
    // The elements of covariance matrix setup following TopQuarkAnalysis/TopKinFitter
    int udscResolution(double et, double eta, double& resEt, double& resEta, double& resPhi);
    int bjetResolution(double et, double eta, double& resEt, double& resEta, double& resPhi);
    int muonResolution(double et, double eta, double& resEt, double& resEta, double& resPhi);
    int elecResolution(double et, double eta, double& resEt, double& resEta, double& resPhi);
    int metResolution(double et, double& resEt, double& resEta, double& resPhi);
    int JetEnergyResolution(double eta, double& JERbase, double& JERdown, double& JERup);

    // The following variables are set by mandatory setters
    // To be set for a given year
    double			btagThresh;
    // To be set for a given event
    std::vector<TLorentzVector> jets;
    std::vector<double>		jetsRes;
    std::vector<double>		btag;
    double			_nu_px, _nu_py, _nu_pz, _nu_pz_other, _nu_pt, _nu_phi; 
    TLorentzVector		lepton;
    LeptonType			leptonType;

    // The following variables are optional setters
    double			mTop;

    // external inputs for jet/lep/met resolution estimation 
    std::string inputResoPath;
    TFile *fResoIn;
    TH2F *hBJetETRes, *hBJetEtaRes, *hBJetPhiRes;
    TH2F *hLJetETRes, *hLJetEtaRes, *hLJetPhiRes;
    TH2F *hMuETRes, *hMuEtaRes, *hMuPhiRes;
    TH2F *hEleETRes, *hEleEtaRes, *hElePhiRes;
    TH1F *hMETETRes, *hMETPhiRes;

    TH2F *hBJetPtDiff, *hBJetEtaDiff, *hBJetPhiDiff, *hBJetEnDiff;
    TH2F *hLJetPtDiff, *hLJetEtaDiff, *hLJetPhiDiff, *hLJetEnDiff;
    TH2F *hMuPtDiff, *hMuEtaDiff, *hMuPhiDiff, *hMuEnDiff;
    TH2F *hElePtDiff, *hEleEtaDiff, *hElePhiDiff, *hEleEnDiff;
    TH1F *hMETPtDiff, *hMETPhiDiff;

    bool useExtReso ; 
    double GetReso2D(TH2F *h2, double eta, double et);
    double GetReso1D(TH1F *h1, double et);
    int udscExtResolution(double et, double eta, double& resEt, double& resEta, double& resPhi);
    int bjetExtResolution(double et, double eta, double& resEt, double& resEta, double& resPhi);
    int muonExtResolution(double et, double eta, double& resEt, double& resEta, double& resPhi);
    int elecExtResolution(double et, double eta, double& resEt, double& resEta, double& resPhi);
    int metExtResolution(double et, double& resEt, double& resEta, double& resPhi);
    
    
    // The following variables are minimal getters
    // Number of converged combinations
    unsigned int		nCombinations, 		nCombinations_tlep, 	nCombinations_thad;                                            

    // Four vectors after KinFit
    std::vector<TLorentzVector> leptonAF,       neutrinoAF,       bjlepAF;
    std::vector<TLorentzVector> bjhadAF,        cjhadAF,          sjhadAF;
    std::vector<TLorentzVector> leptonAF_tlep,  neutrinoAF_tlep,  bjlepAF_tlep;
    std::vector<TLorentzVector> bjhadAF_thad,   cjhadAF_thad,     sjhadAF_thad;
    
    std::vector<unsigned int>	blep_id, bhad_id, chad_id, shad_id;
    
    // The following variables are additional getters
    std::vector<double>		Chi2, Chi2_tlep, Chi2_thad;
    std::vector<int>		NDF, Nb_Iter ;
    // Unmodified four vectors before KinFit
    std::vector<TLorentzVector>	leptonUM,  neutrinoUM,  bjlepUM;
    std::vector<TLorentzVector>	bjhadUM,   cjhadUM,     sjhadUM;	
    std::vector<double>		ReslepEta,    ReslepPhi,    ResneuEta,    ResneuPhi;
    std::vector<double>		ResbjlepEta,  ResbjlepPhi,  ResbjhadEta,  ResbjhadPhi;
    std::vector<double>		RescjhadEta,  RescjhadPhi,  RessjhadEta,  RessjhadPhi;
    bool		        isComplex;
    //double                      bjlepbtag, bjhadbtag, cjhadbtag, sjhadbtag; 
    
};


class SkimAna : public TSelector {
   public :

   struct PtDescending
   { 
      inline bool operator() (const pair<unsigned int, double>& a, const pair<unsigned int, double>& b)
      {
        return (a.second > b.second);
      }
    };
   
   ////// Added for di-tau analysis //////////////
   struct DiTauInfo 
   { 
     DiTauInfo(){}; 
     int diTauCharge_; 
     double sumPt_; 
     int index1_; 
     int index2_;
     float diTauMass_;
     TLorentzVector lepVector1_;
     TLorentzVector lepVector2_;
   }; 

   struct SortDiTauPairs 
   { 
     bool operator() (const DiTauInfo t1, const DiTauInfo t2) 
     { 
       // 1st criterion: OS 
       if ( t1.diTauCharge_ < t2.diTauCharge_ ) return true; 
       if ( t1.diTauCharge_ > t2.diTauCharge_ ) return false; 
       // 2nd criterion: sumPt of diTau pair 
       return (t1.sumPt_ > t2.sumPt_);  
     } 
   }; 
   ///////////////////////////////////////////////
   
   //File operation pointers
   ////////////////////////////////////////////////////////
   TFile            *fFile[3];
   TDirectory       **fFileDir;
   TDirectory       **fSelColDir;
   TProofOutputFile *fProofFile[3]; // For optimized merging of the ntuple

   //Declaration of histograms
   ////////////////////////////////////////////////////////   

   //Declaration of output tree
   ////////////////////////////////////////////////////////
   TTree          *outputTree;//!
   TTree          *outputBjetTree;//!
   std::vector<bool>	 _selStep;
   ////////////////////////////////////////////////////////
   
   Long64_t        fProcessed;//!
   TTree          *fChain;//!    //pointer to the analyzed TTree or TChain
   bool           IsDebug;
   int            nCTag;
   /* //Declaration of leaves types */
   /* //////////////////////////////////////////////////////// */
   /* UInt_t          nJet_; */
   /* Float_t         jetPt_[200]; */
   /* Float_t         jetEta_[200]; */
   /* Float_t         jetPhi_[200]; */
   /* Float_t         jetMass_[200]; */
   /* // Float_t         jetRawFactor_[200]; */
   /* // Int_t           jetID_[200]; */
   /* // Float_t         jetArea_[200]; */
   /* // Float_t         jetBtagCMVA_[200]; */
   /* Float_t         jetBtagCSVV2_[200]; */
   /* Float_t         jetBtagDeepB_[200]; */
   /* Float_t         jetBtagDeepC_[200]; */
   /* // Float_t         jetBtagDeepFlavB_[200]; */
   /* // Float_t         jetchEmEF_[200]; */
   /* // Float_t         jetneEmEF_[200]; */
   /* Int_t           jetPartFlvr_[200]; */
   /* Int_t           jetHadFlvr_[200]; */
   /* Int_t           jetGenJetIdx_[200]; */
   /* //////////////////////////////////////////////////////// */

   
   //Declaration of leaves types
   ////////////////////////////////////////////////////////
  UInt_t       	_run = 0 ;
  Long64_t	_event = 0 ;
  UInt_t       	_lumis = 0 ;
  Bool_t	_isData = 0 ;

  UInt_t       	_prevrun = 0 ;
  UInt_t       	_prevlumis = 0 ;
  
#ifndef MCONLY
  rapidjson::Document fGoldenJsonRunLumi;
#endif
  
  Float_t	_PUweight = 0 ;
  Float_t	_PUweight_Up = 0 ;
  Float_t	_PUweight_Do = 0 ;
  
  /* Float_t		 _q2weight_Up = 0 ; */
  /* Float_t		 _q2weight_Do = 0 ; */
  Float_t		 _q2weight_nominal = 0 ;
  /* std::vector<float>	*_genScaleSystWeights = 0 ; */
  
  Float_t		 _pdfWeight = 0 ;
  /* Float_t		 _pdfuncer = 0 ; */
  /* Float_t		 _pdfweight_Up = 0 ; */
  /* Float_t		 _pdfweight_Do = 0 ; */
  /* std::vector<float>	*_pdfSystWeight = 0 ; */
  
  /* Float_t	_ISRweight_Up = 0 ; */
  /* Float_t	_ISRweight_Do = 0 ; */
  
  /* Float_t	_FSRweight_Up = 0 ; */
  /* Float_t	_FSRweight_Do = 0 ; */
  
  float	_prefireSF = 0 ;
  float	_prefireSF_Up = 0 ;
  float	_prefireSF_Do = 0 ;
  
  float	_btagWeight_1a = 0 ;
  float	_btagWeight_1a_b_Up = 0 ;
  float	_btagWeight_1a_b_Do = 0 ;
  float	_btagWeight_1a_l_Up = 0 ;
  float	_btagWeight_1a_l_Do = 0 ;
  
  std::vector<float>	*_btagWeight = 0 ;
  std::vector<float>	*_btagWeight_b_Up = 0 ;
  std::vector<float>	*_btagWeight_b_Do = 0 ;
  std::vector<float>	*_btagWeight_l_Up = 0 ;
  std::vector<float>	*_btagWeight_l_Do = 0 ;
  
  std::vector<float>	*_btagSF = 0 ;
  std::vector<float>	*_btagSF_b_Up = 0 ;
  std::vector<float>	*_btagSF_b_Do = 0 ;
  std::vector<float>	*_btagSF_l_Up = 0 ;
  std::vector<float>	*_btagSF_l_Do = 0 ;
  
  /* Float_t	_muEffWeight = 0 ; */
  /* Float_t	_muEffWeight_Up = 0 ; */
  /* Float_t	_muEffWeight_Do = 0 ; */
  
  Float_t	_muEffWeight_IdIso = 0 ;
  Float_t	_muEffWeight_IdIso_Up = 0 ;
  Float_t	_muEffWeight_IdIso_Do = 0 ;
  
  Float_t	_muEffWeight_Trig = 0 ;
  Float_t	_muEffWeight_Trig_Up = 0 ;
  Float_t	_muEffWeight_Trig_Do = 0 ;
  
  /* Float_t	_eleEffWeight = 0 ; */
  /* Float_t	_eleEffWeight_Up = 0 ; */
  /* Float_t	_eleEffWeight_Do = 0 ; */
  
  Float_t	_eleEffWeight_IdReco = 0 ;
  Float_t	_eleEffWeight_IdReco_Up = 0 ;
  Float_t	_eleEffWeight_IdReco_Do = 0 ;
  
  Float_t	_eleEffWeight_Trig = 0 ;
  Float_t	_eleEffWeight_Trig_Up = 0 ;
  Float_t	_eleEffWeight_Trig_Do = 0 ;

  Float_t	_evtWeight = 0 ;
  /* Float_t	_sampleWeight = 0 ; */
  Float_t	_lumiWeight = 0 ;

  Int_t		_nVtx = 0 ;
  Int_t		_nGoodVtx = 0 ;

  Float_t	_genMET = 0 ;
        
  Float_t	_pfMET = 0 ;
  Float_t	_pfMETPhi = 0 ;
  Float_t	_nu_px = 0 ;
  Float_t	_nu_py = 0 ;
  Float_t	_nu_pz = 0 ;
  Float_t	_nu_pz_other = 0 ;
  Float_t	_WtransMass = 0 ;
  
  int		_kFType = 0;
  Float_t	_chi2 = 0 ;
  Float_t	_chi2_thad = 0 ;
  Float_t	_chi2_tlep = 0 ;
  int		_NDF = 0 ;
  int		_Nbiter = 0 ;
  Float_t	_M_jj = 0 ;
  Float_t	_M_jjkF = 0 ;
  double        _prob = -1.0;
  unsigned int		_bjlep_id = 0 ;
  unsigned int		_bjhad_id = 0 ;
  unsigned int		_cjhad_id = 0 ;
  unsigned int		_sjhad_id = 0 ;

  Float_t	_Rdiffbjlep = 0 ;
  Float_t	_Rdiffbjhad = 0 ;
  Float_t	_Rdiffcjhad = 0 ;
  Float_t	_Rdiffsjhad = 0 ;

  Float_t	_lepPt = 0 ;
  Float_t	_lepEta = 0 ;
  Float_t	_lepPhi = 0 ;
  Float_t	_lepEnergy = 0 ;
  Float_t	_lepMass = 0 ;
  Float_t	_metPx = 0 ;
  Float_t	_metPy = 0 ;
  Float_t	_metPz = 0 ;

  Float_t	_jetBlepPt = 0 ;
  Float_t	_jetBlepEta = 0 ;
  Float_t	_jetBlepPhi = 0 ;
  Float_t	_jetBlepEnergy = 0 ;
  Float_t	_jetBhadPt = 0 ;
  Float_t	_jetBhadEta = 0 ;
  Float_t	_jetBhadPhi = 0 ;
  Float_t	_jetBhadEnergy = 0 ;
  Float_t	_jetChadPt = 0 ;
  Float_t	_jetChadEta = 0 ;
  Float_t	_jetChadPhi = 0 ;
  Float_t	_jetChadEnergy = 0 ;
  Float_t	_jetShadPt = 0 ;
  Float_t	_jetShadEta = 0 ;
  Float_t	_jetShadPhi = 0 ;
  Float_t	_jetShadEnergy = 0 ;

  Float_t	_jetBlepPtUM = 0 ;
  Float_t	_jetBlepEtaUM = 0 ;
  Float_t	_jetBlepPhiUM = 0 ;
  Float_t	_jetBlepEnergyUM = 0 ;
  Float_t	_jetBhadPtUM = 0 ;
  Float_t	_jetBhadEtaUM = 0 ;
  Float_t	_jetBhadPhiUM = 0 ;
  Float_t	_jetBhadEnergyUM = 0 ;
  Float_t	_jetChadPtUM = 0 ;
  Float_t	_jetChadEtaUM = 0 ;
  Float_t	_jetChadPhiUM = 0 ;
  Float_t	_jetChadEnergyUM = 0 ;
  Float_t	_jetShadPtUM = 0 ;
  Float_t	_jetShadEtaUM = 0 ;
  Float_t	_jetShadPhiUM = 0 ;
  Float_t	_jetShadEnergyUM = 0 ;
  
  Int_t			 _nEle = 0 ;
  Int_t			 _nEleLoose = 0 ;
  std::vector<float>	 *_elePt = 0 ;
  std::vector<float>	 *_eleEta = 0 ;
  std::vector<float>	 *_elePhi = 0 ;
  std::vector<float>	 *_eleSCEta = 0 ;
  std::vector<float>	 *_elePFRelIso = 0 ;
  std::vector<float>	 *_eleCharge = 0 ;
  
  Int_t			 _nMu = 0 ;
  Int_t			 _nMuLoose = 0 ;
  std::vector<float>	 *_muPt = 0 ;
  std::vector<float>	 *_muEta = 0 ;
  std::vector<float>	 *_muPhi = 0 ;
  std::vector<float>	 *_muPFRelIso = 0 ;
  std::vector<float>	 *_muCharge = 0 ;  

  //added for Tau analysis/////////
  UInt_t              _nTau = 0;
  int tauId_1 =-1;
  int tauId_2 =-1;
  float  pairCharge =0;
  float ditau_m =0;

  std::vector<float>   *_tauPt = 0;
  std::vector<float>   *_tauEta = 0;
  std::vector<float>   *_tauPhi = 0;
  std::vector<float>   *_tauCharge = 0;

  std::vector<float>   *_tauPt1 =0;
  std::vector<float>   *_tauEta1=0;
  std::vector<float>   *_tauPhi1=0;
  std::vector<float>   *_tauPt2=0;
  std::vector<float>   *_tauEta2=0;
  std::vector<float>   *_tauPhi2=0;
  std::vector<float>   *_DitauMass=0;
  std::vector<int>    *_DitauCharge=0;
  std::vector<float>  * _DitauSumPt=0;

  ///////////////////////////////

  Int_t			 _nJet = 0 ;
  Int_t			 _nBJet = 0 ;
  std::vector<float>	 *_jetPt = 0;
  std::vector<float>	 *_jetEta = 0 ;
  std::vector<float>	 *_jetPhi = 0 ;
  std::vector<float>	 *_jetMass = 0 ;

  Int_t			 _nfwdJet = 0 ;
  std::vector<float>	 *_fwdJetPt = 0 ;
  std::vector<float>	 *_fwdJetEta = 0 ;
  std::vector<float>	 *_fwdJetPhi = 0 ;
  std::vector<float>	 *_fwdJetMass = 0 ;

  std::vector<float>	 *_jetCMVA = 0 ;
  std::vector<float>	 *_jetCSVV2 = 0 ;
  std::vector<float>	 *_jetDeepB = 0 ;
  std::vector<float>	 *_jetDeepC = 0 ;

  std::vector<int>	 *_jetGenJetIdx = 0 ;

  Int_t			 _nGenJet = 0 ;
  std::vector<float>	 *_genJetPt = 0 ;
  std::vector<float>	 *_genJetEta = 0 ;
  std::vector<float>	 *_genJetPhi = 0 ;
  std::vector<float>	 *_genJetMass = 0 ;
  std::vector<float>	 *_genJetPartonFlavour = 0 ;
  std::vector<float>	 *_genJetHadronFlavour = 0 ;

  Int_t			 _nGenPart = 0 ;
  std::vector<float>	 *_genPt = 0 ;
  std::vector<float>	 *_genEta = 0 ;
  std::vector<float>	 *_genPhi = 0 ;
  std::vector<float>	 *_genMass = 0 ;
  std::vector<int>	 *_genStatus = 0 ;
  std::vector<int>	 *_genStatusFlag = 0 ;
  std::vector<int>	 *_genPDGID = 0 ;
  std::vector<int>	 *_genMomIdx = 0 ;
  
  double  _reslepEta = 0,   _reslepPhi = 0,   _resneuEta = 0,   _resneuPhi = 0, 
          _resbjlepEta = 0, _resbjlepPhi = 0, _resbjhadEta = 0, _resbjhadPhi = 0, 
          _rescjhadEta = 0, _rescjhadPhi = 0, _ressjhadEta = 0, _ressjhadPhi = 0; 

  double  _bjlepDeepCSV = 0, _bjhadDeepCSV = 0, _cjhadDeepCSV = 0, _sjhadDeepCSV = 0;
  double  _bjlepBdisc = -20., _bjhadBdisc = -20., _cjhadBdisc = -20., _sjhadBdisc = -20.;
  double  _bjlepCvsLdisc = -20., _bjhadCvsLdisc = -20., _cjhadCvsLdisc = -20., _sjhadCvsLdisc = -20.;
  double  _bjlepCvsBdisc = -20., _bjhadCvsBdisc = -20., _cjhadCvsBdisc = -20., _sjhadCvsBdisc = -20.;

  double lepCharge=0,lepCharge1=0, lepCharge2=0;
  
  double		 _M3 = 0 ;
  double		 _HT = 0 ;
  bool			 _passPresel_Ele = 0 ;
  bool			 _passPresel_Mu = 0 ;
  bool                   _passPresel_Tau = 0 ; // for Tau Analysis
  bool			 _passAll_Ele = 0 ;
  bool			 _passAll_Mu = 0 ;
  bool                   _passAll_Tau = 0 ; // for Tau Analysis 


  

   ////////////////////////////////////////////////////////

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

   vector<pair<unsigned int, double>>	ljetlist;
   vector<pair<unsigned int, double>>	bjetlist;

   bool isNanoAOD;
   bool doTreeSave;
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
   
   //Event level variables
   map<string,double> totEvents;
   map<string,double> totEventsUS;
   map<string,vector<string>> fnameList;
   map<string,double> LumiWZ;
   float luminosity, lumiFracI, lumiFracII;
   double _local_evtWeight = 1.0;
   double _sampleWeight = 1.0 ; 
   bool isPreVFP,isPostVFP ;

   //PrefireWeight;
   double _prefireWeight = 1.0;
   double _prefireWeight_Up = 1.0;
   double _prefireWeight_Do = 1.0;

   //PU
   PUReweight *PUweighter = 0x0;//, 
   PUReweight *PUweighterUp = 0x0;//
   PUReweight *PUweighterDown = 0x0;//

   double _PUWeight = 1.0;
   double _PUWeight_Up = 1.0;
   double _PUWeight_Do = 1.0;
   
   //The Trio
   EventTree *event = 0x0;
   Selector *selector = 0x0;
   EventPick *evtPick = 0x0;
   
   //JECJERPUJetID
   JECvariation *jecvar = 0x0;
   JECvariation *jecvara = 0x0;
   JECvariation *jecvarb = 0x0;
   TFile *fPUJetIDa = 0x0, *fPUJetIDb = 0x0, *fPUJetID = 0x0;
   TH2D *hPUJetIDEffa, *hPUJetIDEffb, *hPUJetIDEff;
   std::unique_ptr<correction::CorrectionSet> cseta = 0x0, csetb = 0x0, cset = 0x0;
   string PUJetIDSystType ;
   double _PUJetIDWeight;
   double _PUJetIDWeight_Up;
   double _PUJetIDWeight_Do;

   //Btag
   BTagCalibration calib;
   BTagCalibration caliba;
   BTagCalibration calibb;
   BTagCalibration calibC;
   BTagCalibration calibCa;
   BTagCalibration calibCb;
   BTagCalibrationReader reader;
   BTagCalibrationReader readera;
   BTagCalibrationReader readerb;
   BTagCalibrationReader reader_CL;
   BTagCalibrationReader readera_CL;
   BTagCalibrationReader readerb_CL;
   BTagCalibrationReader reader_CM;
   BTagCalibrationReader readera_CM;
   BTagCalibrationReader readerb_CM;
   BTagCalibrationReader reader_CT;
   BTagCalibrationReader readera_CT;
   BTagCalibrationReader readerb_CT;
   TH2D *l_eff = 0x0, *c_eff = 0x0, *b_eff = 0x0;
   string btagSystType ;

   TH2D *l_CL_eff = 0x0, *c_CL_eff = 0x0, *b_CL_eff = 0x0;
   TH2D *l_CM_eff = 0x0, *c_CM_eff = 0x0, *b_CM_eff = 0x0;
   TH2D *l_CT_eff = 0x0, *c_CT_eff = 0x0, *b_CT_eff = 0x0;
   //string ctagLSystType, ctagMSystType, ctagTSystType ;
   string ctagSystType;
   double _bTagWeight = 1.0 ;
   double _bTagWeight_b_Up = 1.0 ;
   double _bTagWeight_b_Do = 1.0 ;
   double _bTagWeight_l_Up = 1.0 ;
   double _bTagWeight_l_Do = 1.0 ;
   double _bTagWeight_bc1_Up = 1.0 ;
   double _bTagWeight_bc1_Do = 1.0 ;
   double _bTagWeight_bc2_Up = 1.0 ;
   double _bTagWeight_bc2_Do = 1.0 ;
   double _bTagWeight_bc3_Up = 1.0 ;
   double _bTagWeight_bc3_Do = 1.0 ;

   int count_cJetsIncL   = 0;
   int count_cJetsIncM   = 0;
   int count_cJetsIncT   = 0;
   double _cTagLWeight = 1.0 ;
   double _cTagLWeight_bc1_Up = 1.0 ;
   double _cTagLWeight_bc1_Do = 1.0 ;
   double _cTagLWeight_bc2_Up = 1.0 ;
   double _cTagLWeight_bc2_Do = 1.0 ;
   double _cTagLWeight_bc3_Up = 1.0 ;
   double _cTagLWeight_bc3_Do = 1.0 ;
   double _cTagMWeight = 1.0 ;
   double _cTagMWeight_bc1_Up = 1.0 ;
   double _cTagMWeight_bc1_Do = 1.0 ;
   double _cTagMWeight_bc2_Up = 1.0 ;
   double _cTagMWeight_bc2_Do = 1.0 ;
   double _cTagMWeight_bc3_Up = 1.0 ;
   double _cTagMWeight_bc3_Do = 1.0 ;
   double _cTagTWeight = 1.0 ;
   double _cTagTWeight_bc1_Up = 1.0 ;
   double _cTagTWeight_bc1_Do = 1.0 ;
   double _cTagTWeight_bc2_Up = 1.0 ;
   double _cTagTWeight_bc2_Do = 1.0 ;
   double _cTagTWeight_bc3_Up = 1.0 ;
   double _cTagTWeight_bc3_Do = 1.0 ;

   double wt_before = 1.0 ; double  wt_after = 1.0;
   TFile *fBCSFFile = 0x0;
   TFile *fBCSFFile_a = 0x0;
   TFile *fBCSFFile_b = 0x0;
   TH2F *SFb_hist=0x0, *SFc_hist=0x0, *SFl_hist=0x0;
   // CShapeCalib EOY
   TH2F *SFb_hist_StatUp = 0x0, *SFc_hist_StatUp = 0x0, *SFl_hist_StatUp = 0x0;
   TH2F *SFb_hist_StatDown = 0x0, *SFc_hist_StatDown = 0x0, *SFl_hist_StatDown = 0x0; 
   TH2F *SFb_hist_EleIDSFUp = 0x0, *SFc_hist_EleIDSFUp = 0x0, *SFl_hist_EleIDSFUp = 0x0; 
   TH2F *SFb_hist_EleIDSFDown = 0x0, *SFc_hist_EleIDSFDown = 0x0, *SFl_hist_EleIDSFDown = 0x0; 
   TH2F *SFb_hist_MuIDSFUp = 0x0, *SFc_hist_MuIDSFUp = 0x0, *SFl_hist_MuIDSFUp = 0x0; 
   TH2F *SFb_hist_MuIDSFDown = 0x0, *SFc_hist_MuIDSFDown = 0x0, *SFl_hist_MuIDSFDown = 0x0; 
   TH2F *SFb_hist_LHEScaleWeight_muFUp = 0x0, *SFc_hist_LHEScaleWeight_muFUp = 0x0, *SFl_hist_LHEScaleWeight_muFUp = 0x0; 
   TH2F *SFb_hist_LHEScaleWeight_muFDown = 0x0, *SFc_hist_LHEScaleWeight_muFDown = 0x0, *SFl_hist_LHEScaleWeight_muFDown = 0x0; 
   TH2F *SFb_hist_LHEScaleWeight_muRUp = 0x0, *SFc_hist_LHEScaleWeight_muRUp = 0x0, *SFl_hist_LHEScaleWeight_muRUp = 0x0; 
   TH2F *SFb_hist_LHEScaleWeight_muRDown = 0x0, *SFc_hist_LHEScaleWeight_muRDown = 0x0, *SFl_hist_LHEScaleWeight_muRDown = 0x0; 
   TH2F *SFb_hist_PSWeightISRUp = 0x0, *SFc_hist_PSWeightISRUp = 0x0, *SFl_hist_PSWeightISRUp = 0x0; 
   TH2F *SFb_hist_PSWeightISRDown = 0x0, *SFc_hist_PSWeightISRDown = 0x0, *SFl_hist_PSWeightISRDown = 0x0; 
   TH2F *SFb_hist_PSWeightFSRUp = 0x0, *SFc_hist_PSWeightFSRUp = 0x0, *SFl_hist_PSWeightFSRUp = 0x0; 
   TH2F *SFb_hist_PSWeightFSRDown = 0x0, *SFc_hist_PSWeightFSRDown = 0x0, *SFl_hist_PSWeightFSRDown = 0x0; 
   TH2F *SFb_hist_PUWeightUp = 0x0, *SFc_hist_PUWeightUp = 0x0, *SFl_hist_PUWeightUp = 0x0; 
   TH2F *SFb_hist_PUWeightDown = 0x0, *SFc_hist_PUWeightDown = 0x0, *SFl_hist_PUWeightDown = 0x0; 
   TH2F *SFb_hist_XSec_DYJetsUp = 0x0, *SFc_hist_XSec_DYJetsUp = 0x0, *SFl_hist_XSec_DYJetsUp = 0x0; 
   TH2F *SFb_hist_XSec_DYJetsDown = 0x0, *SFc_hist_XSec_DYJetsDown = 0x0, *SFl_hist_XSec_DYJetsDown = 0x0; 
   TH2F *SFb_hist_XSec_STUp = 0x0, *SFc_hist_XSec_STUp = 0x0, *SFl_hist_XSec_STUp = 0x0; 
   TH2F *SFb_hist_XSec_STDown = 0x0, *SFc_hist_XSec_STDown = 0x0, *SFl_hist_XSec_STDown = 0x0; 
   TH2F *SFb_hist_XSec_WJetsUp = 0x0, *SFc_hist_XSec_WJetsUp = 0x0, *SFl_hist_XSec_WJetsUp = 0x0; 
   TH2F *SFb_hist_XSec_WJetsDown = 0x0, *SFc_hist_XSec_WJetsDown = 0x0, *SFl_hist_XSec_WJetsDown = 0x0; 
   TH2F *SFb_hist_XSec_ttbarUp = 0x0, *SFc_hist_XSec_ttbarUp = 0x0, *SFl_hist_XSec_ttbarUp = 0x0; 
   TH2F *SFb_hist_XSec_ttbarDown = 0x0, *SFc_hist_XSec_ttbarDown = 0x0, *SFl_hist_XSec_ttbarDown = 0x0; 
   TH2F *SFb_hist_bFragUp = 0x0, *SFc_hist_bFragUp = 0x0, *SFl_hist_bFragUp = 0x0; 
   TH2F *SFb_hist_bFragDown = 0x0, *SFc_hist_bFragDown = 0x0, *SFl_hist_bFragDown = 0x0; 
   TH2F *SFb_hist_jesTotalUp = 0x0, *SFc_hist_jesTotalUp = 0x0, *SFl_hist_jesTotalUp = 0x0; 
   TH2F *SFb_hist_jesTotalDown = 0x0, *SFc_hist_jesTotalDown = 0x0, *SFl_hist_jesTotalDown = 0x0; 
   TH2F *SFb_hist_jerUp = 0x0, *SFc_hist_jerUp = 0x0, *SFl_hist_jerUp = 0x0; 
   TH2F *SFb_hist_jerDown = 0x0, *SFc_hist_jerDown = 0x0, *SFl_hist_jerDown = 0x0; 

   // CShapeCalib UL
  // TH2F *SFb_hist_StatUp = 0x0, *SFc_hist_StatUp = 0x0, *SFl_hist_StatUp = 0x0;
  // TH2F *SFb_hist_StatDown = 0x0, *SFc_hist_StatDown = 0x0, *SFl_hist_StatDown = 0x0;
  TH2F *SFb_hist_InterpUp = 0x0, *SFc_hist_InterpUp = 0x0, *SFl_hist_InterpUp = 0x0;
  TH2F *SFb_hist_InterpDown = 0x0, *SFc_hist_InterpDown = 0x0, *SFl_hist_InterpDown = 0x0;
  TH2F *SFb_hist_ExtrapUp = 0x0, *SFc_hist_ExtrapUp = 0x0, *SFl_hist_ExtrapUp = 0x0;
  TH2F *SFb_hist_ExtrapDown = 0x0, *SFc_hist_ExtrapDown = 0x0, *SFl_hist_ExtrapDown = 0x0;
  // TH2F *SFb_hist_LHEScaleWeight_muFUp = 0x0, *SFc_hist_LHEScaleWeight_muFUp = 0x0, *SFl_hist_LHEScaleWeight_muFUp = 0x0;
  // TH2F *SFb_hist_LHEScaleWeight_muFDown = 0x0, *SFc_hist_LHEScaleWeight_muFDown = 0x0, *SFl_hist_LHEScaleWeight_muFDown = 0x0;
  // TH2F *SFb_hist_LHEScaleWeight_muRUp = 0x0, *SFc_hist_LHEScaleWeight_muRUp = 0x0, *SFl_hist_LHEScaleWeight_muRUp = 0x0;
  // TH2F *SFb_hist_LHEScaleWeight_muRDown = 0x0, *SFc_hist_LHEScaleWeight_muRDown = 0x0, *SFl_hist_LHEScaleWeight_muRDown = 0x0;
  // TH2F *SFb_hist_PSWeightISRUp = 0x0, *SFc_hist_PSWeightISRUp = 0x0, *SFl_hist_PSWeightISRUp = 0x0;
  // TH2F *SFb_hist_PSWeightISRDown = 0x0, *SFc_hist_PSWeightISRDown = 0x0, *SFl_hist_PSWeightISRDown = 0x0;
  // TH2F *SFb_hist_PSWeightFSRUp = 0x0, *SFc_hist_PSWeightFSRUp = 0x0, *SFl_hist_PSWeightFSRUp = 0x0;
  // TH2F *SFb_hist_PSWeightFSRDown = 0x0, *SFc_hist_PSWeightFSRDown = 0x0, *SFl_hist_PSWeightFSRDown = 0x0;
  // TH2F *SFb_hist_PUWeightUp = 0x0, *SFc_hist_PUWeightUp = 0x0, *SFl_hist_PUWeightUp = 0x0;
  // TH2F *SFb_hist_PUWeightDown = 0x0, *SFc_hist_PUWeightDown = 0x0, *SFl_hist_PUWeightDown = 0x0;
  TH2F *SFb_hist_XSec_BRUnc_DYJets_bUp = 0x0, *SFc_hist_XSec_BRUnc_DYJets_bUp = 0x0, *SFl_hist_XSec_BRUnc_DYJets_bUp = 0x0;
  TH2F *SFb_hist_XSec_BRUnc_DYJets_bDown = 0x0, *SFc_hist_XSec_BRUnc_DYJets_bDown = 0x0, *SFl_hist_XSec_BRUnc_DYJets_bDown = 0x0;
  TH2F *SFb_hist_XSec_BRUnc_DYJets_cUp = 0x0, *SFc_hist_XSec_BRUnc_DYJets_cUp = 0x0, *SFl_hist_XSec_BRUnc_DYJets_cUp = 0x0;
  TH2F *SFb_hist_XSec_BRUnc_DYJets_cDown = 0x0, *SFc_hist_XSec_BRUnc_DYJets_cDown = 0x0, *SFl_hist_XSec_BRUnc_DYJets_cDown = 0x0;
  TH2F *SFb_hist_XSec_BRUnc_WJets_cUp = 0x0, *SFc_hist_XSec_BRUnc_WJets_cUp = 0x0, *SFl_hist_XSec_BRUnc_WJets_cUp = 0x0;
  TH2F *SFb_hist_XSec_BRUnc_WJets_cDown = 0x0, *SFc_hist_XSec_BRUnc_WJets_cDown = 0x0, *SFl_hist_XSec_BRUnc_WJets_cDown = 0x0;
  // TH2F *SFb_hist_jesTotalUp = 0x0, *SFc_hist_jesTotalUp = 0x0, *SFl_hist_jesTotalUp = 0x0;
  // TH2F *SFb_hist_jesTotalDown = 0x0, *SFc_hist_jesTotalDown = 0x0, *SFl_hist_jesTotalDown = 0x0;
  // TH2F *SFb_hist_jerUp = 0x0, *SFc_hist_jerUp = 0x0, *SFl_hist_jerUp = 0x0;
  // TH2F *SFb_hist_jerDown = 0x0, *SFc_hist_jerDown = 0x0, *SFl_hist_jerDown = 0x0;

   string bctagSystType ;
   double _bcTagWeight = 1.0 ;
   
   // CShapeCalib EOY
   double _bcTagWeight_stat_Up = 1.0, _bcTagWeight_stat_Do = 1.0, _bcTagWeight_pu_Up = 1.0, _bcTagWeight_pu_Do = 1.0; 
   double _bcTagWeight_eleid_Up = 1.0, _bcTagWeight_eleid_Do = 1.0, _bcTagWeight_muid_Up = 1.0, _bcTagWeight_muid_Do = 1.0; 
   double _bcTagWeight_lhemuf_Up = 1.0, _bcTagWeight_lhemuf_Do = 1.0, _bcTagWeight_lhemur_Up = 1.0, _bcTagWeight_lhemur_Do = 1.0; 
   double _bcTagWeight_isr_Up = 1.0, _bcTagWeight_isr_Do = 1.0, _bcTagWeight_fsr_Up = 1.0, _bcTagWeight_fsr_Do = 1.0; 
   double _bcTagWeight_xdy_Up = 1.0, _bcTagWeight_xdy_Do = 1.0, _bcTagWeight_xst_Up = 1.0, _bcTagWeight_xst_Do = 1.0; 
   double _bcTagWeight_xwj_Up = 1.0, _bcTagWeight_xwj_Do = 1.0, _bcTagWeight_xtt_Up = 1.0,  _bcTagWeight_xtt_Do = 1.0; 
   double _bcTagWeight_jes_Up = 1.0, _bcTagWeight_jes_Do = 1.0, _bcTagWeight_jer_Up = 1.0, _bcTagWeight_jer_Do = 1.0; 
   double _bcTagWeight_bfrag_Up = 1.0, _bcTagWeight_bfrag_Do = 1.0; 

  
   /* // CShapeCalib UL */
   /* double _bcTagWeight_stat_Up = 1.0, _bcTagWeight_stat_Do = 1.0, _bcTagWeight_pu_Up = 1.0, _bcTagWeight_pu_Do = 1.0;  */
   double _bcTagWeight_intp_Up = 1.0, _bcTagWeight_intp_Do = 1.0, _bcTagWeight_extp_Up = 1.0, _bcTagWeight_extp_Do = 1.0;
   /* double _bcTagWeight_lhemuf_Up = 1.0, _bcTagWeight_lhemuf_Do = 1.0, _bcTagWeight_lhemur_Up = 1.0, _bcTagWeight_lhemur_Do = 1.0;  */
   /* double _bcTagWeight_isr_Up = 1.0, _bcTagWeight_isr_Do = 1.0, _bcTagWeight_fsr_Up = 1.0, _bcTagWeight_fsr_Do = 1.0;  */
   double _bcTagWeight_xdyb_Up = 1.0, _bcTagWeight_xdyb_Do = 1.0, _bcTagWeight_xdyc_Up = 1.0, _bcTagWeight_xdyc_Do = 1.0;
   double _bcTagWeight_xwjc_Up = 1.0, _bcTagWeight_xwjc_Do = 1.0;
   /* double _bcTagWeight_jes_Up = 1.0, _bcTagWeight_jes_Do = 1.0, _bcTagWeight_jer_Up = 1.0, _bcTagWeight_jer_Do = 1.0;  */

   /////////////////////// MC section //////////////////////////
   ////Histos
   TLorentzVector pLHE[2], pGP[2], pGJ[2], pRJ[2], pRJAna[2], pTemp;
   map<double,int> delRtoID0;
   map<double,int> delRtoID1;
   map<double, int>::iterator itr_ptr0, itr_ptr1;
   int genJetMatch[2];
   float DeltaRCut = 0.1;
   bool hasGPmatchLHE = false;
   bool hasGJmatchLHE = false;
   bool hasRJmatchGJ = false;
   int recoJetMatch[2];
   bool _found_GJ1_lhe = false;
   bool _found_GJ2_lhe = false;
   bool _found_cjhad_lhe = false;
   bool _found_sjhad_lhe = false;
   float _lhe1Pt,_lhe1Eta,_lhe1Phi,_lhe1Energy;
   float _lhe2Pt,_lhe2Eta,_lhe2Phi,_lhe2Energy;
   int  _lhe1PDG, _lhe2PDG;
   int  _chadPDG, _shadPDG;
   float _lhe1dR,_lhe2dR;
   /////////////////////////////////////////////////////////////

   
   //Lepton SF
   MuonSF *muSFa = 0x0;
   MuonSF *muSFb = 0x0;
   ElectronSF *eleSFa = 0x0;
   ElectronSF *eleSFb = 0x0;
   double _muEffWeight = 1.0;
   double _muEffWeight_Up = 1.0;
   double _muEffWeight_Do = 1.0;
   double _eleEffWeight = 1.0;
   double _eleEffWeight_Up = 1.0;
   double _eleEffWeight_Do = 1.0;
   bool isMuTightID = false;
   bool isEleTightID = false;
   //miniAOD Tracker Eff
   TFile *f_trackSF_BCDEF = 0x0;
   TFile *f_trackSF_GH = 0x0;
   TGraphAsymmErrors *tg_trackSF_BCDEF;
   TGraphAsymmErrors *tg_trackSF_GH;
   bool singleMu = false;
   bool singleEle = false;
   bool muonIsoCut = false;
   bool muonNonIsoCut = false;
   double muonpfRelIso = -1.0;
   bool eleIsoCut = false;
   bool eleNonIsoCut = false;
   double elepfRelIso = -1.0;
   bool doubleTau = false; //For Tau Analysis
   
   // MET
   float METThreshold = 20. ;
   bool isLowMET = false;

   //top pt
   double _topPtReWeight = 1.0;
  
   //Theory weights
   float _q2weight_Up = 1.0, _q2weight_Do = 1.0 ;
   float _muRweight_Up = 1.0, _muRweight_Do = 1.0 ;
   float _muFweight_Up = 1.0, _muFweight_Do = 1.0 ;
   float _pdfweight_Up = 1.0, _pdfweight_Do = 1.0 , _pdfuncer = 0.0;
   float _ISRweight_Up = 1.0, _ISRweight_Do = 1.0;
   float _FSRweight_Up = 1.0, _FSRweight_Do = 1.0;

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

   TH1F           *hMinChi2_mu,  *h2MinChi2_mu, *h3MinChi2_mu, *h4MinChi2_mu, *h5MinChi2_mu;
   TH1F           *hMinChi2_ele,  *h2MinChi2_ele, *h3MinChi2_ele, *h4MinChi2_ele, *h5MinChi2_ele;
   ////////////////////////////////////////////////////////
   
   ////////////////////////////////////////////////////////
   KinFit kinFit ; 
   std::string inputPathReso;
   std::vector<TLorentzVector> jetVectors;
   std::vector<double> jetResVectors;
   std::vector<double> jetBtagVectors;
   std::vector<double> jetCvsLtagVectors;
   std::vector<double> jetCvsBtagVectors;
   TLorentzVector jetVector;
   TLorentzVector lepVector;
   TLorentzVector lepVector2;
   TLorentzVector	leptonBF, neutrinoBF, bjlepBF, bjhadBF, cjhadBF, sjhadBF;
   TLorentzVector	leptonAF, neutrinoAF, bjlepAF, bjhadAF, cjhadAF, sjhadAF;
   TLorentzVector	lepTopAF, hadTopAF;

   TLorentzVector	leptonAF_tlep,  neutrinoAF_tlep,  bjlepAF_tlep;
   TLorentzVector   bjhadAF_thad,   cjhadAF_thad,     sjhadAF_thad;
   TLorentzVector   lepTopAF_tlep,  hadTopAF_thad;

   double  fmTop ;
   double  kinFitMinChi2 ;
   bool    hasKFMu = false, hasKFEle = false;
   bool    isKFValid = false;
   bool    isCTagged = false;
   ////////////////////////////////////////////////////////
   
   SkimAna(TTree *tree=0);
   //SkimAna();
   
   virtual ~SkimAna() ;

   void    Reset();

   int     Version() const {return 1;}
   void    Begin(TTree *tree);
   void    SlaveBegin(TTree *tree);
   void    Init(TTree *tree);
   void    InitOutBranches();
   void    InitBjetOutBranches();
   Bool_t  Notify();
   Bool_t  Process(Long64_t entry);
   void    SetOption(const char *option) { fOption = option; }
   void    SetObject(TObject *obj) { fObject = obj; }
   void    SetInputList(TList *input) {fInput = input;}
   TList  *GetOutputList() const { return fOutput; }
   void    SlaveTerminate();
   void    Terminate();
   
   void    GetArguments();
   void    SelectSyst();
   void    SetTrio();
   void    LoadGoldenJSON();
   void    GetNumberofEvents();
   void    LoadPU();
   void    LoadJECJER();
   void    LoadBTag();
   void    LoadBCTag();
   void    LoadLeptonSF();
   void    Clean(void); //clear vector and arrays while read each event

   Int_t   CreateHistoArrays();
   
   double  ScaleLumiZ(Int_t nLHEPart);
   double  ScaleLumiW(Int_t nLHEPart);
   double  getMuonTrackSF(TGraphAsymmErrors *tg, double eta);
   void    GetMuonEff(double iso);
   void    GetElectronEff();
   void    GetPUJetIDSF_1a();
   void    GetBtagSF_1a();
   void    FillBJetTree();   
   void    GetCLtagSF_1a();   
   void    GetCMtagSF_1a();   
   void    GetCTtagSF_1a();   
   void    GetLMTBCtagSF_2b();
   Bool_t  GetBCTagWt();
   float   topPtReweight();
   void    TheoWeights();
   bool    ProcessKinFit(bool, bool);
   
   /// Fill CutFlow histograms, Note that the cutflow for BTag and KinFit are filled in the object histogram functiuons below
   bool    FillEventCutFlow();
   bool    FillLeptonCutFlow();
   bool    FillNjetCutFlow();
   bool    FillMETCutFlow();
   
   //// Fill the main physics object histograms 
   bool    FillBTagObs();
   bool    FillKFCFObs();
   bool    FillCTagObs();   

   /// They are called by above cutflow histograms
   bool    FillEventCFHists(int isyst, double combined_muwt, double combined_muwt1, double combined_elewt, double combined_tauwt);
   bool    FillLeptonCFHists(int isyst, double combined_muwt, double combined_muwt1, double combined_elewt, double combined_tauwt);
   bool    FillNjetCFHists(int isyst, double combined_muwt, double combined_muwt1, double combined_elewt, double combined_tauwt);
   bool    FillMETCFHists(int isyst, double combined_muwt, double combined_muwt1, double combined_elewt);
   bool    FillBTagCFBTHists(int isyst, double combined_muwt, double combined_muwt1, double combined_elewt, double combined_elewt1);

   /// These are called by above functions for cutflow and physics object filling functions
   bool    FillCFHists(TList *list, string hist_extn, bool isMu, double value, double wt, double wt_nobtagwt);
   bool    FillKFHists(TList *list, string hist_extn, bool isMu, double wt, double wt_nobtagwt);
   bool    FillBTHists(TList *list, string hist_extn, bool isMu, double wt, double wt_nobtagwt);
   bool    FillCTHists(TList *list, string hist_extn, bool isMu, double wt,
		       int count_cJetsIncL, int count_cJetsIncM, int count_cJetsIncT, 
		       bool isIncL, bool isIncM, bool isIncT,
		       double ctagLwt, double ctagMwt, double ctagTwt);
   
   /// Fill Wt histograms
   bool    FillEventWt();
   bool    FillLeptonIso();
   bool    FillLeptonWt();
   bool    FillNjetWt();
   bool    FillBTagWt();
   
   /// Calculate the combine wt
   bool    GetCombinedWt(TString systname, double& combined_muwt, double& combined_muwt_nobtagwt, double& combined_elewt, double& combined_elewt_nobtagwt);
   bool    GetCTagWt(char CType, TString systname, double& ctagwt);
   
   /// Fill the control histograms
   bool    FillEventControlHists();
   bool    FillTriggerControlHists();
   bool    FillLeptonControlHists();
   bool    FillJetControlHists();
   bool    FillMETControlHists();
   bool    FillBTagControlHists();
   bool    FillKinFitControlHists();
   bool    FillCTagControlHists();

   bool    SelectTTbarChannel();
   bool    FillMCInfo();
  
   bool    ExecSerial(const char* infile);
   
   
   //ClassDef(SkimAna,2);

};

#endif



/* //_____________________________________________________________________ */
/* SkimAna::SkimAna() */
/* { */
/*   // Constructor */
  
/*    Reset(); */
/* } */

//_____________________________________________________________________
SkimAna::SkimAna(TTree * /*tree*/)
{
  // Constructor

   Reset();
}
//_____________________________________________________________________
void SkimAna::Reset()
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
   outputTree           = 0;
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
   isNanoAOD		= true;
   doTreeSave		= false;
}
//_____________________________________________________________________
SkimAna::~SkimAna()
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
void SkimAna::Init(TTree *tree)
{
  //   Set branch addresses
  
  //tree = event->chain ;
  Info("Init","tree: %p", tree);
  
  if (tree == 0) return;

  //event = new EventTree(tree, Form("%d",fYear), isData);
  //event = new EventTree();
  
  //ESetBranchAddressStatus brAddrStatus;
  Int_t brAddrStatus;
  
  tree->SetCacheSize(100*1024*1024);
  tree->SetBranchStatus("*",0);
  
  event->isData_ = isData ;

  tree->SetBranchStatus("PV_ndof",1);
  tree->SetBranchAddress("PV_ndof", &(event->pvNDOF_));

  tree->SetBranchStatus("PV_x",1);
  tree->SetBranchAddress("PV_x", &(event->pvX_));

  tree->SetBranchStatus("PV_y",1);
  tree->SetBranchAddress("PV_y", &(event->pvY_));

  tree->SetBranchStatus("PV_z",1);
  tree->SetBranchAddress("PV_z", &(event->pvZ_));

  tree->SetBranchStatus("PV_chi2",1);
  tree->SetBranchAddress("PV_chi2", &(event->pvChi2_));

  if (!isData){
    tree->SetBranchStatus("Pileup_nPU",1);
    tree->SetBranchAddress("Pileup_nPU", &(event->nPU_));
	
    tree->SetBranchStatus("Pileup_nTrueInt",1);
    tree->SetBranchAddress("Pileup_nTrueInt", &(event->nPUTrue_));
  }
  
  // event
	
  tree->SetBranchStatus("run",1);
  tree->SetBranchAddress("run", &(event->run_));

  tree->SetBranchStatus("event",1);
  tree->SetBranchAddress("event", &(event->event_));
	
  tree->SetBranchStatus("luminosityBlock",1);
  tree->SetBranchAddress("luminosityBlock", &(event->lumis_));

  tree->SetBranchStatus("PV_npvs",1);
  tree->SetBranchAddress("PV_npvs", &(event->nVtx_));

  tree->SetBranchStatus("PV_npvsGood",1);
  tree->SetBranchAddress("PV_npvsGood", &(event->nGoodVtx_));
  
  if (!isData){
    
    tree->SetBranchStatus("L1PreFiringWeight_Nom",1);
    brAddrStatus = tree->SetBranchAddress("L1PreFiringWeight_Nom", &(event->L1PreFiringWeight_Nom_));
    if(brAddrStatus == TTree::kMissingBranch || brAddrStatus == TTree::kInternalError){
      event->L1PreFiringWeight_Nom_ =  1.0 ;
      Info("Init", "Setting event->L1PreFiringWeight_Nom_ =  1.0");
    }

    tree->SetBranchStatus("L1PreFiringWeight_Up",1);
    brAddrStatus = tree->SetBranchAddress("L1PreFiringWeight_Up", &(event->L1PreFiringWeight_Up_));
    if(brAddrStatus == TTree::kMissingBranch || brAddrStatus == TTree::kInternalError){
      event->L1PreFiringWeight_Up_ =  1.0 ;
      Info("Init", "Setting event->L1PreFiringWeight_Up_ =  1.0");
    }
    
    tree->SetBranchStatus("L1PreFiringWeight_Dn",1);
    brAddrStatus = tree->SetBranchAddress("L1PreFiringWeight_Dn", &(event->L1PreFiringWeight_Dn_));
    if(brAddrStatus == TTree::kMissingBranch || brAddrStatus == TTree::kInternalError){
      event->L1PreFiringWeight_Dn_ =  1.0 ;
      Info("Init", "Setting event->L1PreFiringWeight_Dn_ =  1.0");
    }
    
    tree->SetBranchStatus("Generator_weight",1);
    tree->SetBranchAddress("Generator_weight", &(event->genWeight_));

    tree->SetBranchStatus("nLHEScaleWeight",1);
    brAddrStatus = tree->SetBranchAddress("nLHEScaleWeight", &(event->nLHEScaleWeight_));
    if(brAddrStatus == TTree::kMissingBranch || brAddrStatus == TTree::kInternalError){
      event->nLHEScaleWeight_ =  0 ;
      Info("Init", "Setting event->nLHEScaleWeight_ =  0");
    }
    
    tree->SetBranchStatus("LHEScaleWeight",1);
    tree->SetBranchAddress("LHEScaleWeight", &(event->LHEScaleWeight_));
    
    tree->SetBranchStatus("nLHEPdfWeight",1);
    brAddrStatus = tree->SetBranchAddress("nLHEPdfWeight", &(event->nLHEPdfWeight_));
    if(brAddrStatus == TTree::kMissingBranch || brAddrStatus == TTree::kInternalError){
      event->nLHEPdfWeight_ =  0 ;
      Info("Init", "Setting event->nLHEPdfWeight_ =  0");
    }
    
    tree->SetBranchStatus("LHEPdfWeight",1);
    tree->SetBranchAddress("LHEPdfWeight", &(event->LHEPdfWeight_));

    tree->SetBranchStatus("PSWeight",1);
    tree->SetBranchAddress("PSWeight", &(event->PSWeight_));
	
    tree->SetBranchStatus("nPSWeight",1);
    brAddrStatus = tree->SetBranchAddress("nPSWeight", &(event->nPSWeight_));
    if(brAddrStatus == TTree::kMissingBranch || brAddrStatus == TTree::kInternalError){
      event->nPSWeight_ =  0 ;
      Info("Init", "Setting event->nPSWeight_ =  0");
    }

  }
  // MET
  tree->SetBranchStatus("MET_pt",1);
  tree->SetBranchAddress("MET_pt", &(event->MET_pt_));

  tree->SetBranchStatus("MET_phi",1);
  tree->SetBranchAddress("MET_phi", &(event->MET_phi_));

  if (!isData){
    tree->SetBranchStatus("GenMET_pt",1);
    tree->SetBranchAddress("GenMET_pt", &(event->GenMET_pt_));
	
    tree->SetBranchStatus("GenMET_phi",1);
    tree->SetBranchAddress("GenMET_phi", &(event->GenMET_phi_));
  }

  // electrons	
	
  tree->SetBranchStatus("nElectron",1);
  tree->SetBranchAddress("nElectron", &(event->nEle_));

  tree->SetBranchStatus("Electron_charge",1);
  tree->SetBranchAddress("Electron_charge", &(event->eleCharge_));	

  tree->SetBranchStatus("Electron_pt",1);
  tree->SetBranchAddress("Electron_pt", &(event->elePt_));

  tree->SetBranchStatus("Electron_deltaEtaSC",1);
  tree->SetBranchAddress("Electron_deltaEtaSC", &(event->eleDeltaEtaSC_));

  tree->SetBranchStatus("Electron_eta",1);
  tree->SetBranchAddress("Electron_eta", &(event->eleEta_));

  tree->SetBranchStatus("Electron_phi",1);
  tree->SetBranchAddress("Electron_phi", &(event->elePhi_));

  tree->SetBranchStatus("Electron_mass",1);
  tree->SetBranchAddress("Electron_mass", &(event->eleMass_));

  tree->SetBranchStatus("Electron_pfRelIso03_chg",1);
  tree->SetBranchAddress("Electron_pfRelIso03_chg", &(event->elePFRelChIso_));

  tree->SetBranchStatus("Electron_pfRelIso03_all",1);
  tree->SetBranchAddress("Electron_pfRelIso03_all", &(event->elePFRelIso_));

  tree->SetBranchStatus("Electron_sieie",1);
  tree->SetBranchAddress("Electron_sieie", &(event->eleSIEIE_));
	
  tree->SetBranchStatus("Electron_cutBased",1);
  tree->SetBranchAddress("Electron_cutBased", &(event->eleIDcutbased_));
  
  tree->SetBranchStatus("Electron_vidNestedWPBitmap",1);
  tree->SetBranchAddress("Electron_vidNestedWPBitmap", &(event->eleVidWPBitmap_));
  
  tree->SetBranchStatus("Electron_mvaFall17V2noIso_WPL",1); 
  tree->SetBranchAddress("Electron_mvaFall17V2noIso_WPL", &(event->eleIDmvaLoose_));
  
  tree->SetBranchStatus("Electron_mvaFall17V2noIso_WP80",1); 
  tree->SetBranchAddress("Electron_mvaFall17V2noIso_WP80", &(event->eleIDmvaWP80_));
  
  tree->SetBranchStatus("Electron_mvaFall17V2noIso_WP90",1); 
  tree->SetBranchAddress("Electron_mvaFall17V2noIso_WP90", &(event->eleIDmvaWP90_));			 

  tree->SetBranchStatus("Electron_dxy",1);
  tree->SetBranchAddress("Electron_dxy", &(event->eleD0_));

  tree->SetBranchStatus("Electron_dz",1);
  tree->SetBranchAddress("Electron_dz", &(event->eleDz_));

    
  tree->SetBranchStatus("Electron_dr03EcalRecHitSumEt",1);
  brAddrStatus = tree->SetBranchAddress("Electron_dr03EcalRecHitSumEt", &(event->eleEcalSumEtDr03_));
  if(brAddrStatus == TTree::kMissingBranch || brAddrStatus == TTree::kInternalError){
      event->eleEcalSumEtDr03_[0] =  0 ;
      Info("Init", "Setting event->eleEcalSumEtDr03_ = 0x0");
    }

  tree->SetBranchStatus("Electron_dr03HcalDepth1TowerSumEt",1);
  tree->SetBranchAddress("Electron_dr03HcalDepth1TowerSumEt", &(event->eleHcalSumEtDr03_));

  tree->SetBranchStatus("Electron_dr03TkSumPt",1);
  tree->SetBranchAddress("Electron_dr03TkSumPt", &(event->eleTrkSumPtDr03_));

  // muons
  // keep some branches in the skim
	
  tree->SetBranchStatus("nMuon",1);
  tree->SetBranchAddress("nMuon", &(event->nMuon_));

  tree->SetBranchStatus("Muon_charge",1);
  tree->SetBranchAddress("Muon_charge", &(event->muCharge_));
	
  tree->SetBranchStatus("Muon_pt",1);
  tree->SetBranchAddress("Muon_pt", &(event->muPt_));

  tree->SetBranchStatus("Muon_eta",1);
  tree->SetBranchAddress("Muon_eta", &(event->muEta_));

  tree->SetBranchStatus("Muon_phi",1);
  tree->SetBranchAddress("Muon_phi", &(event->muPhi_));

  tree->SetBranchStatus("Muon_mass",1);
  tree->SetBranchAddress("Muon_mass", &(event->muMass_));

  // tree->SetBranchStatus("Muon_pfRelIso04_all",1);
  // tree->SetBranchAddress("Muon_pfRelIso04_all", &(event->muPFRelIso_));

  tree->SetBranchStatus("Muon_pfRelIso03_all",1);
  tree->SetBranchAddress("Muon_pfRelIso03_all", &(event->muPFRelIso_));

  tree->SetBranchStatus("Muon_tightId",1);
  tree->SetBranchAddress("Muon_tightId", &(event->muTightId_));

  tree->SetBranchStatus("Muon_mediumId",1);
  tree->SetBranchAddress("Muon_mediumId", &(event->muMediumId_));

  tree->SetBranchStatus("Muon_looseId",1);
  tree->SetBranchAddress("Muon_looseId", &(event->muLooseId_));

  tree->SetBranchStatus("Muon_mediumPromptId",1);
  tree->SetBranchAddress("Muon_mediumPromptId", &(event->muMediumPromptId_));

  tree->SetBranchStatus("Muon_isPFcand",1);
  tree->SetBranchAddress("Muon_isPFcand", &(event->muIsPFMuon_));

  tree->SetBranchStatus("Muon_isGlobal",1);
  tree->SetBranchAddress("Muon_isGlobal", &(event->muIsGlobal_));

  tree->SetBranchStatus("Muon_isTracker",1);
  tree->SetBranchAddress("Muon_isTracker", &(event->muIsTracker_));

  tree->SetBranchStatus("Muon_dxy",1);
  tree->SetBranchAddress("Muon_dxy", &(event->mudxy_));

  tree->SetBranchStatus("Muon_dz",1);
  tree->SetBranchAddress("Muon_dz", &(event->mudz_));

  tree->SetBranchStatus("Muon_nTrackerLayers",1);
  tree->SetBranchAddress("Muon_nTrackerLayers", &(event->munTrackerLayers_));
  
  if (!isData){
    tree->SetBranchStatus("Muon_genPartIdx",1);
    tree->SetBranchAddress("Muon_genPartIdx", &(event->muGenPartIdx_));
  }

  //For Tau Analysis ////////////////////////////

  tree->SetBranchStatus("nTau",1);
  tree->SetBranchAddress("nTau", &(event->nTau_));

  tree->SetBranchStatus("Tau_charge",1);
  tree->SetBranchAddress("Tau_charge", &(event->tauCharge_));

  tree->SetBranchStatus("Tau_decayMode",1);
  tree->SetBranchAddress("Tau_decayMode", &(event->tauDecayMode_));

  tree->SetBranchStatus("Tau_dxy",1);
  tree->SetBranchAddress("Tau_dxy", &(event->tauDxy_));

  tree->SetBranchStatus("Tau_dz",1);
  tree->SetBranchAddress("Tau_dz", &(event->tauDz_));

  tree->SetBranchStatus("Tau_eta",1);
  tree->SetBranchAddress("Tau_eta", &(event->tauEta_));

  //tree->SetBranchStatus("Tau_idDecayMode",1);
  //tree->SetBranchAddress("Tau_idDecayMode", &(event->tau_idDecayMode_));

  //tree->SetBranchStatus("Tau_idDecayModeNewDMs",1);
  //tree->SetBranchAddress("Tau_idDecayModeNewDMs", &(event->tau_idDecayModeNewDMs_));

  tree->SetBranchStatus("Tau_idDeepTau2017v2p1VSe",1);
  tree->SetBranchAddress("Tau_idDeepTau2017v2p1VSe", &(event->tauIdDeepTau2017v2p1VSe_));

  tree->SetBranchStatus("Tau_idDeepTau2017v2p1VSjet",1);
  tree->SetBranchAddress("Tau_idDeepTau2017v2p1VSjet", &(event->tauIdDeepTau2017v2p1VSjet_));

  tree->SetBranchStatus("Tau_idDeepTau2017v2p1VSmu",1);
  tree->SetBranchAddress("Tau_idDeepTau2017v2p1VSmu", &(event->tauIdDeepTau2017v2p1VSmu_));

  tree->SetBranchStatus("Tau_mass",1);
  tree->SetBranchAddress("Tau_mass", &(event->tauMass_));

  tree->SetBranchStatus("Tau_phi",1);
  tree->SetBranchAddress("Tau_phi", &(event->tauPhi_));

  tree->SetBranchStatus("Tau_pt",1);
  tree->SetBranchAddress("Tau_pt", &(event->tauPt_));

  tree->SetBranchStatus("Tau_rawDeepTau2017v2p1VSe",1);
  tree->SetBranchAddress("Tau_rawDeepTau2017v2p1VSe", &(event->tauRawDeepTau2017v2p1VSe_));

  tree->SetBranchStatus("Tau_rawDeepTau2017v2p1VSjet",1);
  tree->SetBranchAddress("Tau_rawDeepTau2017v2p1VSjet", &(event->tauRawDeepTau2017v2p1VSjet_));

  tree->SetBranchStatus("Tau_rawDeepTau2017v2p1VSmu",1);
  tree->SetBranchAddress("Tau_rawDeepTau2017v2p1VSmu", &(event->tauRawDeepTau2017v2p1VSmu_));

  tree->SetBranchStatus("Tau_genPartFlav",1);
  tree->SetBranchAddress("Tau_genPartFlav", &(event->tauGenPartFlav_));
  ///////////////////////////////////////////////////////////////////

  // jets
	
  tree->SetBranchStatus("nJet",1);
  tree->SetBranchAddress("nJet", &(event->nJet_));
 
  tree->SetBranchStatus("Jet_pt",1);
  tree->SetBranchAddress("Jet_pt", &(event->jetPt_));

  tree->SetBranchStatus("Jet_rawFactor",1);
  tree->SetBranchAddress("Jet_rawFactor", &(event->jetRawFactor_));
	
  tree->SetBranchStatus("Jet_eta",1);
  tree->SetBranchAddress("Jet_eta", &(event->jetEta_));
	
  tree->SetBranchStatus("Jet_phi",1);
  tree->SetBranchAddress("Jet_phi", &(event->jetPhi_));

  tree->SetBranchStatus("Jet_mass",1);
  tree->SetBranchAddress("Jet_mass", &(event->jetMass_));

  tree->SetBranchStatus("Jet_jetId",1);
  tree->SetBranchAddress("Jet_jetId", &(event->jetID_));

  tree->SetBranchStatus("Jet_puId",1);
  tree->SetBranchAddress("Jet_puId", &(event->jetPUID_));

  tree->SetBranchStatus("Jet_puIdDisc",1);
  tree->SetBranchAddress("Jet_puIdDisc", &(event->jetpuIdDisc_));

  tree->SetBranchStatus("Jet_area",1);
  tree->SetBranchAddress("Jet_area", &(event->jetArea_));

  /* tree->SetBranchStatus("Jet_btagCMVA",1); */
  /* tree->SetBranchAddress("Jet_btagCMVA", &(event->jetBtagCMVA_)); */

  tree->SetBranchStatus("Jet_btagCSVV2",1);
  tree->SetBranchAddress("Jet_btagCSVV2", &(event->jetBtagCSVV2_));

  tree->SetBranchStatus("Jet_btagDeepB",1);
  tree->SetBranchAddress("Jet_btagDeepB", &(event->jetBtagDeepB_));

  tree->SetBranchStatus("Jet_btagDeepCvB",1);
  tree->SetBranchAddress("Jet_btagDeepCvB", &(event->jetBtagDeepCvB_));
  
  tree->SetBranchStatus("Jet_btagDeepCvL",1);
  tree->SetBranchAddress("Jet_btagDeepCvL", &(event->jetBtagDeepCvL_));

  /* tree->SetBranchStatus("Jet_btagDeepC",1); */
  /* tree->SetBranchAddress("Jet_btagDeepC", &(event->jetBtagDeepC_)); */

  tree->SetBranchStatus("Jet_btagDeepFlavB",1);
  tree->SetBranchAddress("Jet_btagDeepFlavB", &(event->jetBtagDeepFlavB_));

  tree->SetBranchStatus("Jet_btagDeepFlavCvB",1);
  tree->SetBranchAddress("Jet_btagDeepFlavCvB", &(event->jetBtagDeepFlavCvB_));
  
  tree->SetBranchStatus("Jet_btagDeepFlavCvL",1);
  tree->SetBranchAddress("Jet_btagDeepFlavCvL", &(event->jetBtagDeepFlavCvL_));

  tree->SetBranchStatus("Jet_chEmEF",1);
  tree->SetBranchAddress("Jet_chEmEF", &(event->jetchEmEF_));

  tree->SetBranchStatus("Jet_neEmEF",1);
  tree->SetBranchAddress("Jet_neEmEF", &(event->jetneEmEF_));
  
  tree->SetBranchStatus("Jet_chHEF",1);
  tree->SetBranchAddress("Jet_chHEF", &(event->jetchHEF_));

  tree->SetBranchStatus("Jet_neHEF",1);
  tree->SetBranchAddress("Jet_neHEF", &(event->jetneHEF_));

  if (!isData){
    tree->SetBranchStatus("Jet_partonFlavour",1);
    tree->SetBranchAddress("Jet_partonFlavour", &(event->jetPartFlvr_));

    tree->SetBranchStatus("Jet_hadronFlavour",1);
    tree->SetBranchAddress("Jet_hadronFlavour", &(event->jetHadFlvr_));
	
    tree->SetBranchStatus("Jet_genJetIdx",1);
    tree->SetBranchAddress("Jet_genJetIdx", &(event->jetGenJetIdx_));
  }

  // Gen Partons
  if (!isData){

    tree->SetBranchStatus("nLHEPart",1);
    brAddrStatus = tree->SetBranchAddress("nLHEPart", &(event->nLHEPart_));
    if(brAddrStatus == TTree::kMissingBranch || brAddrStatus == TTree::kInternalError){
      event->nLHEPart_ =  0 ;
      Info("Init", "Setting event->nLHEPart_ =  0");
    }
    
    tree->SetBranchStatus("LHEPart_pdgId",1);
    tree->SetBranchAddress("LHEPart_pdgId", &(event->LHEPart_pdgId_));

    tree->SetBranchStatus("LHEPart_pt",1);
    tree->SetBranchAddress("LHEPart_pt", &(event->LHEPart_pt_));

    tree->SetBranchStatus("LHEPart_eta",1);
    tree->SetBranchAddress("LHEPart_eta", &(event->LHEPart_eta_));

    tree->SetBranchStatus("LHEPart_phi",1);
    tree->SetBranchAddress("LHEPart_phi", &(event->LHEPart_phi_));

    tree->SetBranchStatus("LHEPart_mass",1);
    tree->SetBranchAddress("LHEPart_mass", &(event->LHEPart_mass_));

    tree->SetBranchStatus("nGenPart",1);
    tree->SetBranchAddress("nGenPart", &(event->nGenPart_));
	
    tree->SetBranchStatus("GenPart_pt",1);
    tree->SetBranchAddress("GenPart_pt", &(event->GenPart_pt_));
	
    tree->SetBranchStatus("GenPart_eta",1);
    tree->SetBranchAddress("GenPart_eta", &(event->GenPart_eta_));
	
    tree->SetBranchStatus("GenPart_phi",1);
    tree->SetBranchAddress("GenPart_phi", &(event->GenPart_phi_));

    tree->SetBranchStatus("GenPart_mass",1);
    tree->SetBranchAddress("GenPart_mass", &(event->GenPart_mass_));

    tree->SetBranchStatus("GenPart_genPartIdxMother",1);
    tree->SetBranchAddress("GenPart_genPartIdxMother", &(event->GenPart_genPartIdxMother_));

    tree->SetBranchStatus("GenPart_pdgId",1);
    tree->SetBranchAddress("GenPart_pdgId", &(event->GenPart_pdgId_));
	
    tree->SetBranchStatus("GenPart_status",1);
    tree->SetBranchAddress("GenPart_status", &(event->GenPart_status_));
	
    tree->SetBranchStatus("GenPart_statusFlags",1);
    tree->SetBranchAddress("GenPart_statusFlags", &(event->GenPart_statusFlags_));
    

    tree->SetBranchStatus("nGenJet",1);
    tree->SetBranchAddress("nGenJet", &(event->nGenJet_));
	
    tree->SetBranchStatus("GenJet_pt",1);
    tree->SetBranchAddress("GenJet_pt", &(event->GenJet_pt_));

    tree->SetBranchStatus("GenJet_eta",1);
    tree->SetBranchAddress("GenJet_eta", &(event->GenJet_eta_));

    tree->SetBranchStatus("GenJet_phi",1);
    tree->SetBranchAddress("GenJet_phi", &(event->GenJet_phi_));
 
    tree->SetBranchStatus("GenJet_mass",1);
    tree->SetBranchAddress("GenJet_mass", &(event->GenJet_mass_));

    tree->SetBranchStatus("GenJet_partonFlavour",1);
    tree->SetBranchAddress("GenJet_partonFlavour", &(event->GenJet_partonFlavour_));
	
    tree->SetBranchStatus("GenJet_hadronFlavour",1);
    brAddrStatus = tree->SetBranchAddress("GenJet_hadronFlavour", &(event->GenJet_hadronFlavour_));
    /* if(brAddrStatus == TTree::kMissingBranch || brAddrStatus == TTree::kInternalError){ */
    /*   event->GenJet_hadronFlavour_[0] =  0 ; */
    /*   Info("Init", "Setting event->GenJet_hadronFlavour_ =  0x0"); */
    /* } */

  }

  //Fliters
  tree->SetBranchStatus("Flag_goodVertices",1);
  tree->SetBranchAddress("Flag_goodVertices", &(event->Flag_goodVertices_));

  tree->SetBranchStatus("Flag_globalSuperTightHalo2016Filter",1);
  tree->SetBranchAddress("Flag_globalSuperTightHalo2016Filter", &(event->Flag_globalSuperTightHalo2016Filter_));

  tree->SetBranchStatus("Flag_HBHENoiseFilter",1);
  tree->SetBranchAddress("Flag_HBHENoiseFilter", &(event->Flag_HBHENoiseFilter_));

  tree->SetBranchStatus("Flag_HBHENoiseIsoFilter",1);
  tree->SetBranchAddress("Flag_HBHENoiseIsoFilter", &(event->Flag_HBHENoiseIsoFilter_));

  tree->SetBranchStatus("Flag_EcalDeadCellTriggerPrimitiveFilter",1);
  tree->SetBranchAddress("Flag_EcalDeadCellTriggerPrimitiveFilter", &(event->Flag_EcalDeadCellTriggerPrimitiveFilter_));

  tree->SetBranchStatus("Flag_BadPFMuonFilter",1);
  tree->SetBranchAddress("Flag_BadPFMuonFilter", &(event->Flag_BadPFMuonFilter_));

  if(fYear ==2017 || fYear == 2018){
    tree->SetBranchStatus("Flag_ecalBadCalibFilter",1);
    tree->SetBranchAddress("Flag_ecalBadCalibFilter", &(event->Flag_ecalBadCalibFilter_));
  }

  //TRIGGERS

  if (fYear==2016){
    tree->SetBranchStatus("HLT_Ele27_WPTight_Gsf",1);
    tree->SetBranchAddress("HLT_Ele27_WPTight_Gsf", &(event->HLT_Ele27_WPTight_Gsf_));
	
    // tree->SetBranchStatus("HLT_Ele105_CaloIdVT_GsfTrkIdT",1);
    // tree->SetBranchAddress("HLT_Ele105_CaloIdVT_GsfTrkIdT", &(event->HLT_Ele105_CaloIdVT_GsfTrkIdT_));
	
    // tree->SetBranchStatus("HLT_Ele115_CaloIdVT_GsfTrkIdT",1);
    // tree->SetBranchAddress("HLT_Ele115_CaloIdVT_GsfTrkIdT", &(event->HLT_Ele115_CaloIdVT_GsfTrkIdT_));
	
    // tree->SetBranchStatus("HLT_Ele32_eta2p1_WPTight_Gsf",1);
    // tree->SetBranchAddress("HLT_Ele32_eta2p1_WPTight_Gsf", &(event->HLT_Ele32_eta2p1_WPTight_Gsf_));

    tree->SetBranchStatus("HLT_IsoMu24",1);
    tree->SetBranchAddress("HLT_IsoMu24", &(event->HLT_IsoMu24_));
	
    tree->SetBranchStatus("HLT_IsoTkMu24",1);
    tree->SetBranchAddress("HLT_IsoTkMu24", &(event->HLT_IsoTkMu24_));
	
  }
    
  if (fYear==2017){
    tree->SetBranchStatus("HLT_Ele32_WPTight_Gsf_L1DoubleEG",1);
    tree->SetBranchAddress("HLT_Ele32_WPTight_Gsf_L1DoubleEG", &(event->HLT_Ele32_WPTight_Gsf_L1DoubleEG_));
	
    // tree->SetBranchStatus("HLT_Ele32_WPTight_Gsf",1);
    // tree->SetBranchAddress("HLT_Ele32_WPTight_Gsf", &(event->HLT_Ele32_WPTight_Gsf_));
    
    tree->SetBranchStatus("HLT_Ele35_WPTight_Gsf",1);
    tree->SetBranchAddress("HLT_Ele35_WPTight_Gsf", &(event->HLT_Ele35_WPTight_Gsf_));
	
    // tree->SetBranchStatus("HLT_Ele115_CaloIdVT_GsfTrkIdT",1);
    // tree->SetBranchAddress("HLT_Ele115_CaloIdVT_GsfTrkIdT", &(event->HLT_Ele115_CaloIdVT_GsfTrkIdT_));
	
    tree->SetBranchStatus("HLT_IsoMu24",1);
    tree->SetBranchAddress("HLT_IsoMu24", &(event->HLT_IsoMu24_));
	
    // tree->SetBranchStatus("HLT_IsoTkMu24",1);
    // tree->SetBranchAddress("HLT_IsoTkMu24", &(event->HLT_IsoTkMu24_));

    // tree->SetBranchStatus("HLT_IsoMu24_eta2p1",1);
    // tree->SetBranchAddress("HLT_IsoMu24_eta2p1", &(event->HLT_IsoMu24_eta2p1_));
    
    tree->SetBranchStatus("HLT_IsoMu27",1);
    tree->SetBranchAddress("HLT_IsoMu27", &(event->HLT_IsoMu27_));

    tree->SetBranchStatus("L1_SingleEG24",1);
    brAddrStatus = tree->SetBranchAddress("L1_SingleEG24", &(event->L1_SingleEG24_));
    // Info("Init", "L1_SingleEG24 brAddrStatus : %d",brAddrStatus);

    tree->SetBranchStatus("L1_SingleEG26",1);
    brAddrStatus = tree->SetBranchAddress("L1_SingleEG26", &(event->L1_SingleEG26_));
    // Info("Init", "L1_SingleEG26 brAddrStatus : %d",brAddrStatus);

    tree->SetBranchStatus("L1_SingleEG30",1);
    brAddrStatus = tree->SetBranchAddress("L1_SingleEG30", &(event->L1_SingleEG30_));
    // Info("Init", "L1_SingleEG30 brAddrStatus : %d",brAddrStatus);

    tree->SetBranchStatus("L1_SingleEG32",1);
    brAddrStatus = tree->SetBranchAddress("L1_SingleEG32", &(event->L1_SingleEG32_));
    // Info("Init", "L1_SingleEG32 brAddrStatus : %d",brAddrStatus);

    tree->SetBranchStatus("L1_SingleEG34",1);
    brAddrStatus = tree->SetBranchAddress("L1_SingleEG34", &(event->L1_SingleEG34_));
    // Info("Init", "L1_SingleEG34 brAddrStatus : %d",brAddrStatus);
    
    tree->SetBranchStatus("L1_SingleEG36",1);
    brAddrStatus = tree->SetBranchAddress("L1_SingleEG36", &(event->L1_SingleEG36_));
    // Info("Init", "L1_SingleEG36 brAddrStatus : %d",brAddrStatus);

    tree->SetBranchStatus("L1_SingleEG38",1);
    brAddrStatus = tree->SetBranchAddress("L1_SingleEG38", &(event->L1_SingleEG38_));
    // Info("Init", "L1_SingleEG38 brAddrStatus : %d",brAddrStatus);

    tree->SetBranchStatus("L1_SingleEG40",1);
    brAddrStatus = tree->SetBranchAddress("L1_SingleEG40", &(event->L1_SingleEG40_));
    // Info("Init", "L1_SingleEG40 brAddrStatus : %d",brAddrStatus);

    tree->SetBranchStatus("L1_SingleEG42",1);
    brAddrStatus = tree->SetBranchAddress("L1_SingleEG42", &(event->L1_SingleEG42_));
    // Info("Init", "L1_SingleEG42 brAddrStatus : %d",brAddrStatus);
    if(brAddrStatus == TTree::kMissingBranch || brAddrStatus == TTree::kInternalError){
      event->L1_SingleEG42_ =  true ;
      Info("Init", "Setting event->L1_SingleEG42_ to true");
    }

    tree->SetBranchStatus("L1_SingleEG45",1);
    brAddrStatus = tree->SetBranchAddress("L1_SingleEG45", &(event->L1_SingleEG45_));
    // Info("Init", "L1_SingleEG45 brAddrStatus : %d",brAddrStatus);

    tree->SetBranchStatus("L1_SingleEG50",1);
    brAddrStatus = tree->SetBranchAddress("L1_SingleEG50", &(event->L1_SingleEG50_));
    // Info("Init", "L1_SingleEG50 brAddrStatus : %d",brAddrStatus);
    if(brAddrStatus == TTree::kMissingBranch || brAddrStatus == TTree::kInternalError){
      event->L1_SingleEG50_ =  true ;
      Info("Init", "Setting event->L1_SingleEG50_ to true");
    }

    
    tree->SetBranchStatus("L1_SingleEG34er2p1",1);
    brAddrStatus = tree->SetBranchAddress("L1_SingleEG34er2p1", &(event->L1_SingleEG34er2p1_));
    // Info("Init", "L1_SingleEG34er2p1 brAddrStatus : %d",brAddrStatus);
    
    tree->SetBranchStatus("L1_SingleEG36er2p1",1);
    brAddrStatus = tree->SetBranchAddress("L1_SingleEG36er2p1", &(event->L1_SingleEG36er2p1_));
    // Info("Init", "L1_SingleEG36er2p1 brAddrStatus : %d",brAddrStatus);

    tree->SetBranchStatus("L1_SingleEG38er2p1",1);
    brAddrStatus = tree->SetBranchAddress("L1_SingleEG38er2p1", &(event->L1_SingleEG38er2p1_));
    // Info("Init", "L1_SingleEG38er2p1 brAddrStatus : %d",brAddrStatus);


    tree->SetBranchStatus("L1_SingleIsoEG24er2p1",1);
    brAddrStatus = tree->SetBranchAddress("L1_SingleIsoEG24er2p1", &(event->L1_SingleIsoEG24er2p1_));
    // Info("Init", "L1_SingleEG42er2p1 brAddrStatus : %d",brAddrStatus);

    tree->SetBranchStatus("L1_SingleIsoEG26er2p1",1);
    brAddrStatus = tree->SetBranchAddress("L1_SingleIsoEG26er2p1", &(event->L1_SingleIsoEG26er2p1_));
    // Info("Init", "L1_SingleIsoEG26er2p1 brAddrStatus : %d",brAddrStatus);

    tree->SetBranchStatus("L1_SingleIsoEG28er2p1",1);
    brAddrStatus = tree->SetBranchAddress("L1_SingleIsoEG28er2p1", &(event->L1_SingleIsoEG28er2p1_));
    // Info("Init", "L1_SingleIsoEG28er2p1 brAddrStatus : %d",brAddrStatus);

    tree->SetBranchStatus("L1_SingleIsoEG30er2p1",1);
    brAddrStatus = tree->SetBranchAddress("L1_SingleIsoEG30er2p1", &(event->L1_SingleIsoEG30er2p1_));
    // Info("Init", "L1_SingleIsoEG30er2p1 brAddrStatus : %d",brAddrStatus);

    tree->SetBranchStatus("L1_SingleIsoEG32er2p1",1);
    brAddrStatus = tree->SetBranchAddress("L1_SingleIsoEG32er2p1", &(event->L1_SingleIsoEG32er2p1_));
    // Info("Init", "L1_SingleIsoEG32er2p1 brAddrStatus : %d",brAddrStatus);

    tree->SetBranchStatus("L1_SingleIsoEG34er2p1",1);
    brAddrStatus = tree->SetBranchAddress("L1_SingleIsoEG34er2p1", &(event->L1_SingleIsoEG34er2p1_));
    // Info("Init", "L1_SingleIsoEG34er2p1 brAddrStatus : %d",brAddrStatus);

    tree->SetBranchStatus("L1_SingleIsoEG36er2p1",1);
    brAddrStatus = tree->SetBranchAddress("L1_SingleIsoEG36er2p1", &(event->L1_SingleIsoEG36er2p1_));
    // Info("Init", "L1_SingleIsoEG36er2p1 brAddrStatus : %d",brAddrStatus);


    tree->SetBranchStatus("L1_SingleIsoEG24",1);
    brAddrStatus = tree->SetBranchAddress("L1_SingleIsoEG24", &(event->L1_SingleIsoEG24_));
    // Info("Init", "L1_SingleIsoEG24 brAddrStatus : %d",brAddrStatus);
    
    tree->SetBranchStatus("L1_SingleIsoEG26",1);
    brAddrStatus = tree->SetBranchAddress("L1_SingleIsoEG26", &(event->L1_SingleIsoEG26_));
    // Info("Init", "L1_SingleIsoEG26 brAddrStatus : %d",brAddrStatus);

    tree->SetBranchStatus("L1_SingleIsoEG28",1);
    brAddrStatus = tree->SetBranchAddress("L1_SingleIsoEG28", &(event->L1_SingleIsoEG28_));
    // Info("Init", "L1_SingleIsoEG28 brAddrStatus : %d",brAddrStatus);

    tree->SetBranchStatus("L1_SingleIsoEG30",1);
    brAddrStatus = tree->SetBranchAddress("L1_SingleIsoEG30", &(event->L1_SingleIsoEG30_));
    // Info("Init", "L1_SingleIsoEG30 brAddrStatus : %d",brAddrStatus);

    tree->SetBranchStatus("L1_SingleIsoEG32",1);
    brAddrStatus = tree->SetBranchAddress("L1_SingleIsoEG32", &(event->L1_SingleIsoEG32_));
    // Info("Init", "L1_SingleIsoEG32 brAddrStatus : %d",brAddrStatus);
    
    tree->SetBranchStatus("L1_SingleIsoEG34",1);
    brAddrStatus = tree->SetBranchAddress("L1_SingleIsoEG34", &(event->L1_SingleIsoEG34_));
    // Info("Init", "L1_SingleIsoEG34 brAddrStatus : %d",brAddrStatus);

    tree->SetBranchStatus("L1_SingleIsoEG36",1);
    brAddrStatus = tree->SetBranchAddress("L1_SingleIsoEG36", &(event->L1_SingleIsoEG36_));
    // Info("Init", "L1_SingleIsoEG36 brAddrStatus : %d",brAddrStatus);

    tree->SetBranchStatus("L1_SingleIsoEG38",1);
    brAddrStatus = tree->SetBranchAddress("L1_SingleIsoEG38", &(event->L1_SingleIsoEG38_));
    // Info("Init", "L1_SingleIsoEG38 brAddrStatus : %d",brAddrStatus);


  }
  
  if (fYear==2018){
    tree->SetBranchStatus("HLT_Ele32_WPTight_Gsf",1);
    tree->SetBranchAddress("HLT_Ele32_WPTight_Gsf", &(event->HLT_Ele32_WPTight_Gsf_));

    // tree->SetBranchStatus("HLT_Ele35_WPTight_Gsf",1);
    // tree->SetBranchAddress("HLT_Ele35_WPTight_Gsf", &(event->HLT_Ele35_WPTight_Gsf_));

    // tree->SetBranchStatus("HLT_Ele38_WPTight_Gsf",1);
    // tree->SetBranchAddress("HLT_Ele38_WPTight_Gsf", &(event->HLT_Ele38_WPTight_Gsf_));

    // tree->SetBranchStatus("HLT_Ele32_WPTight_Gsf_L1DoubleEG",1);
    // tree->SetBranchAddress("HLT_Ele32_WPTight_Gsf_L1DoubleEG", &(event->HLT_Ele32_WPTight_Gsf_L1DoubleEG_));

    // tree->SetBranchStatus("HLT_Ele115_CaloIdVT_GsfTrkIdT",1);
    // tree->SetBranchAddress("HLT_Ele115_CaloIdVT_GsfTrkIdT", &(event->HLT_Ele115_CaloIdVT_GsfTrkIdT_));
	
    // tree->SetBranchStatus("HLT_DoubleEle25_CaloIdL_MW",1);
    // tree->SetBranchAddress("HLT_DoubleEle25_CaloIdL_MW", &(event->HLT_DoubleEle25_CaloIdL_MW_));

    tree->SetBranchStatus("HLT_IsoMu24",1);
    tree->SetBranchAddress("HLT_IsoMu24", &(event->HLT_IsoMu24_));

    //added for Tau Analysis/////////////
    tree->SetBranchStatus("HLT_DoubleMediumChargedIsoPFTauHPS35_Trk1_eta2p1_Reg",1);
    tree->SetBranchAddress("HLT_DoubleMediumChargedIsoPFTauHPS35_Trk1_eta2p1_Reg",&(event->HLT_DoubleMediumChargedIsoPFTauHPS35_Trk1_eta2p1_Reg_));

    tree->SetBranchStatus("HLT_DoubleMediumChargedIsoPFTauHPS35_Trk1_TightID_eta2p1_Reg",1);
    tree->SetBranchAddress("HLT_DoubleMediumChargedIsoPFTauHPS35_Trk1_TightID_eta2p1_Reg",&(event->HLT_DoubleMediumChargedIsoPFTauHPS35_Trk1_TightID_eta2p1_Reg_));
    ////////////////////////////////

  }	
  
  tree->SetBranchStatus("fixedGridRhoFastjetAll",1);
  tree->SetBranchAddress("fixedGridRhoFastjetAll", &(event->rho_));
  
  // tree->SetBranchStatus("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL",1);
  // tree->SetBranchAddress("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL", &(event->HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_));
    
  // tree->SetBranchStatus("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ",1);
  // tree->SetBranchAddress("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ", &(event->HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_));
    
  // tree->SetBranchStatus("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL",1);
  // tree->SetBranchAddress("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL", &(event->HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_));
    
  // tree->SetBranchStatus("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ",1);
  // tree->SetBranchAddress("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ", &(event->HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_));
    
  // tree->SetBranchStatus("HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL",1);
  // tree->SetBranchAddress("HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL", &(event->HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_));
    
  // tree->SetBranchStatus("HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ",1);
  // tree->SetBranchAddress("HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ", &(event->HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_));
  
  gRandom->SetSeed(357913);
  
  event->SetTree(tree);
  fChain    = tree;
  tree->GetEntry(0);  //Important to set the events weights via Notify and ScaleLumi metho
  
}
//_____________________________________________________________________

void SkimAna::InitOutBranches(){
  
    outputTree->Branch("run"			, &(event->run_)       		); 
    outputTree->Branch("nanoEventId"		, &(event->event_)     		); 
    outputTree->Branch("skimEventId"    	, &fProcessed     		); 
    outputTree->Branch("sampleWeight"    	, &_sampleWeight       		); 
    outputTree->Branch("prefireWeight"		, &_prefireWeight      		);
    outputTree->Branch("prefireWeight_Up"	, &_prefireWeight_Up		);
    outputTree->Branch("prefireWeight_Do"	, &_prefireWeight_Do		);
    outputTree->Branch("PUWeight"		, &_PUWeight			);
    outputTree->Branch("PUWeight_Up"		, &_PUWeight_Up			);
    outputTree->Branch("PUWeight_Do"		, &_PUWeight_Do			);
    
    outputTree->Branch("singleMu"		, &singleMu			);
    outputTree->Branch("singleEle"		, &singleEle			);
    outputTree->Branch("muonIsoCut"		, &muonIsoCut			);
    outputTree->Branch("muonNonIsoCut"		, &muonNonIsoCut       		);
    outputTree->Branch("eleIsoCut"		, &eleIsoCut			);
    outputTree->Branch("eleNonIsoCut"		, &eleNonIsoCut       		);
    outputTree->Branch("isLowMET"		, &isLowMET       		);

    outputTree->Branch("muonpfRelIso"		, &muonpfRelIso			);
    outputTree->Branch("elepfRelIso"		, &elepfRelIso			);
    outputTree->Branch("METPt"  		, &(selector->METPt)	       	);
    
    outputTree->Branch("muEffWeight"		, &_muEffWeight			);
    outputTree->Branch("muEffWeight_Up"		, &_muEffWeight_Up		);
    outputTree->Branch("muEffWeight_Do"		, &_muEffWeight_Do		);
    outputTree->Branch("eleEffWeight"		, &_eleEffWeight		);
    outputTree->Branch("eleEffWeight_Up"	, &_eleEffWeight_Up		);
    outputTree->Branch("eleEffWeight_Do"	, &_eleEffWeight_Do		);

    outputTree->Branch("puJetIDWeight"		, &_PUJetIDWeight		);
    outputTree->Branch("puJetIDWeight_Up"	, &_PUJetIDWeight_Up		);
    outputTree->Branch("puJetIDWeight_Do"	, &_PUJetIDWeight_Do		);

    outputTree->Branch("muRweight_Up"		, &_muRweight_Up       	        );
    outputTree->Branch("muRweight_Do"		, &_muRweight_Do       	        );
    outputTree->Branch("muFweight_Up"		, &_muFweight_Up       	        );
    outputTree->Branch("muFweight_Do"		, &_muFweight_Do       	        );
    outputTree->Branch("q2weight_Up"		, &_q2weight_Up		        );
    outputTree->Branch("q2weight_Do"		, &_q2weight_Do		        );
    outputTree->Branch("pdfweight_Up"		, &_pdfweight_Up		);
    outputTree->Branch("pdfweight_Do"		, &_pdfweight_Do		);
    outputTree->Branch("ISRweight_Up"		, &_ISRweight_Up		);
    outputTree->Branch("ISRweight_Do"		, &_ISRweight_Do		);
    outputTree->Branch("FSRweight_Up"		, &_FSRweight_Up		);
    outputTree->Branch("FSRweight_Do"		, &_FSRweight_Do		);

    // outputTree->Branch("bTagWeight"		, &_bTagWeight			);
    // outputTree->Branch("bTagWeight_b_Up"	, &_bTagWeight_b_Up		);
    // outputTree->Branch("bTagWeight_b_Do"	, &_bTagWeight_b_Do		);
    // outputTree->Branch("bTagWeight_l_Up"	, &_bTagWeight_l_Up		);
    // outputTree->Branch("bTagWeight_l_Do"	, &_bTagWeight_l_Do		);
    // outputTree->Branch("bTagWeight_bc1_Up"	, &_bTagWeight_bc1_Up		);
    // outputTree->Branch("bTagWeight_bc1_Do"	, &_bTagWeight_bc1_Do		);
    // outputTree->Branch("bTagWeight_bc2_Up"	, &_bTagWeight_bc2_Up		);
    // outputTree->Branch("bTagWeight_bc2_Do"	, &_bTagWeight_bc2_Do		);
    // outputTree->Branch("bTagWeight_bc3_Up"	, &_bTagWeight_bc3_Up		);
    // outputTree->Branch("bTagWeight_bc3_Do"	, &_bTagWeight_bc3_Do		);
    
    outputTree->Branch("isCTagged"		, &isCTagged         		);
    outputTree->Branch("count_cJetsIncL"	, &count_cJetsIncL      	);
    outputTree->Branch("count_cJetsIncM"	, &count_cJetsIncM      	);
    outputTree->Branch("count_cJetsIncT"	, &count_cJetsIncT      	);
    // outputTree->Branch("cTagLWeight"		, &_cTagLWeight			);
    // outputTree->Branch("cTagLWeight_bc1_Up"	, &_cTagLWeight_bc1_Up		);
    // outputTree->Branch("cTagLWeight_bc1_Do"	, &_cTagLWeight_bc1_Do		);
    // outputTree->Branch("cTagLWeight_bc2_Up"	, &_cTagLWeight_bc2_Up		);
    // outputTree->Branch("cTagLWeight_bc2_Do"	, &_cTagLWeight_bc2_Do		);
    // outputTree->Branch("cTagLWeight_bc3_Up"	, &_cTagLWeight_bc3_Up		);
    // outputTree->Branch("cTagLWeight_bc3_Do"	, &_cTagLWeight_bc3_Do		);

    // outputTree->Branch("cTagMWeight"		, &_cTagMWeight			);
    // outputTree->Branch("cTagMWeight_bc1_Up"	, &_cTagMWeight_bc1_Up		);
    // outputTree->Branch("cTagMWeight_bc1_Do"	, &_cTagMWeight_bc1_Do		);
    // outputTree->Branch("cTagMWeight_bc2_Up"	, &_cTagMWeight_bc2_Up		);
    // outputTree->Branch("cTagMWeight_bc2_Do"	, &_cTagMWeight_bc2_Do		);
    // outputTree->Branch("cTagMWeight_bc3_Up"	, &_cTagMWeight_bc3_Up		);
    // outputTree->Branch("cTagMWeight_bc3_Do"	, &_cTagMWeight_bc3_Do		);

    // outputTree->Branch("cTagTWeight"		, &_cTagTWeight			);
    // outputTree->Branch("cTagTWeight_bc1_Up"	, &_cTagTWeight_bc1_Up		);
    // outputTree->Branch("cTagTWeight_bc1_Do"	, &_cTagTWeight_bc1_Do		);
    // outputTree->Branch("cTagTWeight_bc2_Up"	, &_cTagTWeight_bc2_Up		);
    // outputTree->Branch("cTagTWeight_bc2_Do"	, &_cTagTWeight_bc2_Do		);
    // outputTree->Branch("cTagTWeight_bc3_Up"	, &_cTagTWeight_bc3_Up		);
    // outputTree->Branch("cTagTWeight_bc3_Do"	, &_cTagTWeight_bc3_Do		);
    
    outputTree->Branch("nJet"			, &_nJet			);
    outputTree->Branch("nBJet"  		, &_nBJet			);
    outputTree->Branch("wt_before"		, &wt_before			);
    outputTree->Branch("wt_after"		, &wt_after			);
    outputTree->Branch("topPtReWeight"		, &_topPtReWeight       	);
    outputTree->Branch("bcTagWeight"		, &_bcTagWeight       		);
    //CTagShape EOY
    outputTree->Branch("bcTagWeight_stat_Up"	, &_bcTagWeight_stat_Up       	);    
    outputTree->Branch("bcTagWeight_stat_Do"	, &_bcTagWeight_stat_Do       	);    
    outputTree->Branch("bcTagWeight_pu_Up"	, &_bcTagWeight_pu_Up       	);    
    outputTree->Branch("bcTagWeight_pu_Do"	, &_bcTagWeight_pu_Do       	);    
    outputTree->Branch("bcTagWeight_eleid_Up"	, &_bcTagWeight_eleid_Up      	);    
    outputTree->Branch("bcTagWeight_eleid_Do"	, &_bcTagWeight_eleid_Do      	);    
    outputTree->Branch("bcTagWeight_muid_Up"	, &_bcTagWeight_muid_Up       	);    
    outputTree->Branch("bcTagWeight_muid_Do"	, &_bcTagWeight_muid_Do       	);    
    outputTree->Branch("bcTagWeight_lhemuf_Up"	, &_bcTagWeight_lhemuf_Up     	);    
    outputTree->Branch("bcTagWeight_lhemuf_Do"	, &_bcTagWeight_lhemuf_Do     	);    
    outputTree->Branch("bcTagWeight_lhemur_Up"	, &_bcTagWeight_lhemur_Up    	);    
    outputTree->Branch("bcTagWeight_lhemur_Do"	, &_bcTagWeight_lhemur_Do     	);    
    outputTree->Branch("bcTagWeight_isr_Up"	, &_bcTagWeight_isr_Up       	);    
    outputTree->Branch("bcTagWeight_isr_Do"	, &_bcTagWeight_isr_Do       	);    
    outputTree->Branch("bcTagWeight_fsr_Up"	, &_bcTagWeight_fsr_Up       	);    
    outputTree->Branch("bcTagWeight_fsr_Do"	, &_bcTagWeight_fsr_Do       	);    
    outputTree->Branch("bcTagWeight_xdy_Up"	, &_bcTagWeight_xdy_Up       	);    
    outputTree->Branch("bcTagWeight_xdy_Do"	, &_bcTagWeight_xdy_Do       	);    
    outputTree->Branch("bcTagWeight_xst_Up"	, &_bcTagWeight_xst_Up       	);    
    outputTree->Branch("bcTagWeight_xst_Do"	, &_bcTagWeight_xst_Do       	);     
    outputTree->Branch("bcTagWeight_xwj_Up"	, &_bcTagWeight_xwj_Up       	);    
    outputTree->Branch("bcTagWeight_xwj_Do"	, &_bcTagWeight_xwj_Do       	);    
    outputTree->Branch("bcTagWeight_xtt_Up"	, &_bcTagWeight_xtt_Up       	);    
    outputTree->Branch("bcTagWeight_xtt_Do"	, &_bcTagWeight_xtt_Do       	);    
    outputTree->Branch("bcTagWeight_jes_Up"	, &_bcTagWeight_jes_Up       	);    
    outputTree->Branch("bcTagWeight_jes_Do"	, &_bcTagWeight_jes_Do       	);    
    outputTree->Branch("bcTagWeight_jer_Up"	, &_bcTagWeight_jer_Up       	);    
    outputTree->Branch("bcTagWeight_jer_Do"	, &_bcTagWeight_jer_Do       	);    
    outputTree->Branch("bcTagWeight_bfrag_Up"	, &_bcTagWeight_bfrag_Up      	);    
    outputTree->Branch("bcTagWeight_bfrag_Do"	, &_bcTagWeight_bfrag_Do      	);        
    outputTree->Branch("bcTagWeight_intp_Up"	, &_bcTagWeight_intp_Up	 ); 
    outputTree->Branch("bcTagWeight_intp_Do"	, &_bcTagWeight_intp_Do	 );
    outputTree->Branch("bcTagWeight_extp_Up"	, &_bcTagWeight_extp_Up	 );
    outputTree->Branch("bcTagWeight_extp_Do"	, &_bcTagWeight_extp_Do	 );
    outputTree->Branch("bcTagWeight_xdyb_Up"	, &_bcTagWeight_xdyb_Up	 ); 
    outputTree->Branch("bcTagWeight_xdyb_Do"	, &_bcTagWeight_xdyb_Do	 );
    outputTree->Branch("bcTagWeight_xdyc_Up"	, &_bcTagWeight_xdyc_Up	 );
    outputTree->Branch("bcTagWeight_xdyc_Do"	, &_bcTagWeight_xdyc_Do	 );
    outputTree->Branch("bcTagWeight_xwjc_Up"	, &_bcTagWeight_xwjc_Up	 ); 
    outputTree->Branch("bcTagWeight_xwjc_Do"	, &_bcTagWeight_xwjc_Do	 );

    outputTree->Branch("chi2"			, &kinFitMinChi2       		);
    outputTree->Branch("ndf"			, &_NDF         		);
    outputTree->Branch("prob"			, &_prob         		);
    outputTree->Branch("isKFValid"		, &isKFValid         		);
    outputTree->Branch("hasKFMu"		, &hasKFMu         		);
    outputTree->Branch("hasKFEle"		, &hasKFEle         		);
    outputTree->Branch("Rdiffbjlep"		, &_Rdiffbjlep         		);
    outputTree->Branch("Rdiffbjhad"		, &_Rdiffbjhad         		);
    outputTree->Branch("Rdiffcjhad"		, &_Rdiffcjhad         		);
    outputTree->Branch("Rdiffsjhad"		, &_Rdiffsjhad         		);
    
    outputTree->Branch("lepPt"			, &_lepPt			);
    outputTree->Branch("lepEta"			, &_lepEta			);
    outputTree->Branch("lepPhi"			, &_lepPhi			);
    outputTree->Branch("lepEnergy"		, &_lepEnergy			);

    outputTree->Branch("tauPt"                 , &_tauPt                        );
    outputTree->Branch("tauPhi"                , &_tauPhi                       );
    outputTree->Branch("tauEta"                , &_tauEta                       );
    outputTree->Branch("tauCharge"             , &_tauCharge                    );

    outputTree->Branch("tau1_Pt"                 , &_tauPt1                     );
    outputTree->Branch("tau1_Phi"                , &_tauPhi1                    );
    outputTree->Branch("tau1_Eta"                , &_tauEta1                    );
    // outputTree->Branch("tau1_Charge"             , &_tauCharg                );
    
    outputTree->Branch("tau2_Pt"                 , &_tauPt2                     );
    outputTree->Branch("tau2_Phi"                , &_tauPhi2                    );
    outputTree->Branch("tau2_Eta"                , &_tauEta2                    );
    //outputTree->Branch("tau2_Charge"             , &_tauCharge2               );
    
    outputTree->Branch("DiTau_Mass"                 , &_DitauMass               );
    outputTree->Branch("DiTau_sumPt"                , &_DitauSumPt              );
    outputTree->Branch("DiTau_Charge"                , &_DitauCharge            );
    

    outputTree->Branch("metPx"			, &_metPx			);
    outputTree->Branch("metPy"			, &_metPy			);
    outputTree->Branch("metPz"			, &_metPz			);

    outputTree->Branch("jetBlepPt"		, &_jetBlepPt			);
    outputTree->Branch("jetBlepEta"		, &_jetBlepEta			);
    outputTree->Branch("jetBlepPhi"		, &_jetBlepPhi			);
    outputTree->Branch("jetBlepEnergy"		, &_jetBlepEnergy		);

    outputTree->Branch("jetBhadPt"		, &_jetBhadPt			);
    outputTree->Branch("jetBhadEta"		, &_jetBhadEta			);
    outputTree->Branch("jetBhadPhi"		, &_jetBhadPhi			);
    outputTree->Branch("jetBhadEnergy"		, &_jetBhadEnergy		);

    outputTree->Branch("jetChadPt"		, &_jetChadPt			);
    outputTree->Branch("jetChadEta"		, &_jetChadEta			);
    outputTree->Branch("jetChadPhi"		, &_jetChadPhi			);
    outputTree->Branch("jetChadEnergy"		, &_jetChadEnergy		);

    outputTree->Branch("jetShadPt"		, &_jetShadPt			);
    outputTree->Branch("jetShadEta"		, &_jetShadEta			);
    outputTree->Branch("jetShadPhi"		, &_jetShadPhi			);
    outputTree->Branch("jetShadEnergy"		, &_jetShadEnergy		);
    
    outputTree->Branch("bjlepBdisc"		, &_bjlepBdisc       		);
    outputTree->Branch("bjhadBdisc"		, &_bjhadBdisc       		);
    outputTree->Branch("cjhadBdisc"		, &_cjhadBdisc       		);
    outputTree->Branch("sjhadBdisc"		, &_sjhadBdisc       		);
    
    outputTree->Branch("bjlepCvsLdisc"		, &_bjlepCvsLdisc              	);
    outputTree->Branch("bjhadCvsLdisc"		, &_bjhadCvsLdisc      		);
    outputTree->Branch("cjhadCvsLdisc"		, &_cjhadCvsLdisc      		);
    outputTree->Branch("sjhadCvsLdisc"		, &_sjhadCvsLdisc      		);
    
    outputTree->Branch("bjlepCvsBdisc"		, &_bjlepCvsBdisc		);
    outputTree->Branch("bjhadCvsBdisc"		, &_bjhadCvsBdisc		);
    outputTree->Branch("cjhadCvsBdisc"		, &_cjhadCvsBdisc		);
    outputTree->Branch("sjhadCvsBdisc"		, &_sjhadCvsBdisc		);

    outputTree->Branch("kFType"	        	, &_kFType      		);
    outputTree->Branch("found_GJ1_lhe"		, &_found_GJ1_lhe		);
    outputTree->Branch("found_GJ2_lhe"		, &_found_GJ2_lhe		);
    outputTree->Branch("found_cjhad_lhe"	, &_found_cjhad_lhe		);
    outputTree->Branch("found_sjhad_lhe"	, &_found_sjhad_lhe		);

    outputTree->Branch("lhe1Pt"			, &_lhe1Pt			);
    outputTree->Branch("lhe1Eta"		, &_lhe1Eta			);
    outputTree->Branch("lhe1Phi"		, &_lhe1Phi			);
    outputTree->Branch("lhe1Energy"		, &_lhe1Energy			);

    outputTree->Branch("lhe2Pt"			, &_lhe2Pt			);
    outputTree->Branch("lhe2Eta"		, &_lhe2Eta			);
    outputTree->Branch("lhe2Phi"		, &_lhe2Phi			);
    outputTree->Branch("lhe2Energy"		, &_lhe2Energy			);
    
    outputTree->Branch("lhe1PDG"		, &_lhe1PDG			);
    outputTree->Branch("lhe2PDG"		, &_lhe2PDG			);
    
    outputTree->Branch("chadPDG"		, &_chadPDG			);
    outputTree->Branch("shadPDG"		, &_shadPDG			);
    outputTree->Branch("lhe1dR"			, &_lhe1dR			);
    outputTree->Branch("lhe2dR"			, &_lhe2dR			);

}

//_____________________________________________________________________

void SkimAna::InitBjetOutBranches(){
  
  outputBjetTree->Branch("run"          	, &(event->run_)       		); 
  outputBjetTree->Branch("nanoEventId"    	, &(event->event_)     		); 
  outputBjetTree->Branch("skimEventId"    	, &fProcessed     		); 
  outputBjetTree->Branch("sampleWeight"    	, &_sampleWeight       		); 
  outputBjetTree->Branch("prefireWeight"       	, &_prefireWeight      		);
  outputBjetTree->Branch("prefireWeight_Up"	, &_prefireWeight_Up		);
  outputBjetTree->Branch("prefireWeight_Do"	, &_prefireWeight_Do		);
  outputBjetTree->Branch("PUWeight"     	, &_PUWeight			);
  outputBjetTree->Branch("PUWeight_Up"  	, &_PUWeight_Up			);
  outputBjetTree->Branch("PUWeight_Do"  	, &_PUWeight_Do			);
  
  outputBjetTree->Branch("singleMu"     	, &singleMu			);
  outputBjetTree->Branch("singleEle"    	, &singleEle			);
  outputBjetTree->Branch("muonIsoCut"   	, &muonIsoCut			);
  outputBjetTree->Branch("muonNonIsoCut"        , &muonNonIsoCut       		);
  outputBjetTree->Branch("eleIsoCut"     	, &eleIsoCut			);
  outputBjetTree->Branch("eleNonIsoCut"         , &eleNonIsoCut       		);
  outputBjetTree->Branch("isLowMET"             , &isLowMET       		);
  outputBjetTree->Branch("muEffWeight"   	, &_muEffWeight			);
  outputBjetTree->Branch("muEffWeight_Up"	, &_muEffWeight_Up		);
  outputBjetTree->Branch("muEffWeight_Do"	, &_muEffWeight_Do		);
  outputBjetTree->Branch("eleEffWeight"  	, &_eleEffWeight		);
  outputBjetTree->Branch("eleEffWeight_Up"	, &_eleEffWeight_Up		);
  outputBjetTree->Branch("eleEffWeight_Do"	, &_eleEffWeight_Do		);
  
  outputBjetTree->Branch("puJetIDWeight"	, &_PUJetIDWeight		);
  outputBjetTree->Branch("puJetIDWeight_Up"	, &_PUJetIDWeight_Up		);
  outputBjetTree->Branch("puJetIDWeight_Do"	, &_PUJetIDWeight_Do		);

  outputBjetTree->Branch("muRweight_Up"		, &_muRweight_Up       	        );
  outputBjetTree->Branch("muRweight_Do"		, &_muRweight_Do       	        );
  outputBjetTree->Branch("muFweight_Up"		, &_muFweight_Up       	        );
  outputBjetTree->Branch("muFweight_Do"		, &_muFweight_Do       	        );
  outputBjetTree->Branch("q2weight_Up"		, &_q2weight_Up		        );
  outputBjetTree->Branch("q2weight_Do"		, &_q2weight_Do		        );
  outputBjetTree->Branch("pdfweight_Up"		, &_pdfweight_Up		);
  outputBjetTree->Branch("pdfweight_Do"		, &_pdfweight_Do		);
  outputBjetTree->Branch("ISRweight_Up"		, &_ISRweight_Up		);
  outputBjetTree->Branch("ISRweight_Do"		, &_ISRweight_Do		);
  outputBjetTree->Branch("FSRweight_Up"		, &_FSRweight_Up		);
  outputBjetTree->Branch("FSRweight_Do"		, &_FSRweight_Do		);

  // outputBjetTree->Branch("bTagWeight"		, &_bTagWeight			);
  // outputBjetTree->Branch("bTagWeight_b_Up"	, &_bTagWeight_b_Up		);
  // outputBjetTree->Branch("bTagWeight_b_Do"	, &_bTagWeight_b_Do		);
  // outputBjetTree->Branch("bTagWeight_l_Up"	, &_bTagWeight_l_Up		);
  // outputBjetTree->Branch("bTagWeight_l_Do"	, &_bTagWeight_l_Do		);
  // outputBjetTree->Branch("bTagWeight_bc1_Up"	, &_bTagWeight_bc1_Up		);
  // outputBjetTree->Branch("bTagWeight_bc1_Do"	, &_bTagWeight_bc1_Do		);
  // outputBjetTree->Branch("bTagWeight_bc2_Up"	, &_bTagWeight_bc2_Up		);
  // outputBjetTree->Branch("bTagWeight_bc2_Do"	, &_bTagWeight_bc2_Do		);
  // outputBjetTree->Branch("bTagWeight_bc3_Up"	, &_bTagWeight_bc3_Up		);
  // outputBjetTree->Branch("bTagWeight_bc3_Do"	, &_bTagWeight_bc3_Do		);

  outputBjetTree->Branch("bcTagWeight"		, &_bcTagWeight       		);
  //CTagShape EOY
  outputBjetTree->Branch("bcTagWeight_stat_Up"	, &_bcTagWeight_stat_Up       	);    
  outputBjetTree->Branch("bcTagWeight_stat_Do"	, &_bcTagWeight_stat_Do       	);    
  outputBjetTree->Branch("bcTagWeight_pu_Up"	, &_bcTagWeight_pu_Up       	);    
  outputBjetTree->Branch("bcTagWeight_pu_Do"	, &_bcTagWeight_pu_Do       	);    
  outputBjetTree->Branch("bcTagWeight_eleid_Up"	, &_bcTagWeight_eleid_Up      	);    
  outputBjetTree->Branch("bcTagWeight_eleid_Do"	, &_bcTagWeight_eleid_Do      	);    
  outputBjetTree->Branch("bcTagWeight_muid_Up"	, &_bcTagWeight_muid_Up       	);    
  outputBjetTree->Branch("bcTagWeight_muid_Do"	, &_bcTagWeight_muid_Do       	);    
  outputBjetTree->Branch("bcTagWeight_lhemuf_Up"	, &_bcTagWeight_lhemuf_Up     	);    
  outputBjetTree->Branch("bcTagWeight_lhemuf_Do"	, &_bcTagWeight_lhemuf_Do     	);    
  outputBjetTree->Branch("bcTagWeight_lhemur_Up"	, &_bcTagWeight_lhemur_Up    	);    
  outputBjetTree->Branch("bcTagWeight_lhemur_Do"	, &_bcTagWeight_lhemur_Do     	);    
  outputBjetTree->Branch("bcTagWeight_isr_Up"	, &_bcTagWeight_isr_Up       	);    
  outputBjetTree->Branch("bcTagWeight_isr_Do"	, &_bcTagWeight_isr_Do       	);    
  outputBjetTree->Branch("bcTagWeight_fsr_Up"	, &_bcTagWeight_fsr_Up       	);    
  outputBjetTree->Branch("bcTagWeight_fsr_Do"	, &_bcTagWeight_fsr_Do       	);    
  outputBjetTree->Branch("bcTagWeight_xdy_Up"	, &_bcTagWeight_xdy_Up       	);    
  outputBjetTree->Branch("bcTagWeight_xdy_Do"	, &_bcTagWeight_xdy_Do       	);    
  outputBjetTree->Branch("bcTagWeight_xst_Up"	, &_bcTagWeight_xst_Up       	);    
  outputBjetTree->Branch("bcTagWeight_xst_Do"	, &_bcTagWeight_xst_Do       	);     
  outputBjetTree->Branch("bcTagWeight_xwj_Up"	, &_bcTagWeight_xwj_Up       	);    
  outputBjetTree->Branch("bcTagWeight_xwj_Do"	, &_bcTagWeight_xwj_Do       	);    
  outputBjetTree->Branch("bcTagWeight_xtt_Up"	, &_bcTagWeight_xtt_Up       	);    
  outputBjetTree->Branch("bcTagWeight_xtt_Do"	, &_bcTagWeight_xtt_Do       	);    
  outputBjetTree->Branch("bcTagWeight_jes_Up"	, &_bcTagWeight_jes_Up       	);    
  outputBjetTree->Branch("bcTagWeight_jes_Do"	, &_bcTagWeight_jes_Do       	);    
  outputBjetTree->Branch("bcTagWeight_jer_Up"	, &_bcTagWeight_jer_Up       	);    
  outputBjetTree->Branch("bcTagWeight_jer_Do"	, &_bcTagWeight_jer_Do       	);    
  outputBjetTree->Branch("bcTagWeight_bfrag_Up"	, &_bcTagWeight_bfrag_Up      	);    
  outputBjetTree->Branch("bcTagWeight_bfrag_Do"	, &_bcTagWeight_bfrag_Do      	);    
  outputBjetTree->Branch("bcTagWeight_intp_Up"	, &_bcTagWeight_intp_Up	 ); 
  outputBjetTree->Branch("bcTagWeight_intp_Do"	, &_bcTagWeight_intp_Do	 );
  outputBjetTree->Branch("bcTagWeight_extp_Up"	, &_bcTagWeight_extp_Up	 );
  outputBjetTree->Branch("bcTagWeight_extp_Do"	, &_bcTagWeight_extp_Do	 );
  outputBjetTree->Branch("bcTagWeight_xdyb_Up"	, &_bcTagWeight_xdyb_Up	 ); 
  outputBjetTree->Branch("bcTagWeight_xdyb_Do"	, &_bcTagWeight_xdyb_Do	 );
  outputBjetTree->Branch("bcTagWeight_xdyc_Up"	, &_bcTagWeight_xdyc_Up	 );
  outputBjetTree->Branch("bcTagWeight_xdyc_Do"	, &_bcTagWeight_xdyc_Do	 );
  outputBjetTree->Branch("bcTagWeight_xwjc_Up"	, &_bcTagWeight_xwjc_Up	 ); 
  outputBjetTree->Branch("bcTagWeight_xwjc_Do"	, &_bcTagWeight_xwjc_Do	 );
     

  outputBjetTree->Branch("lepPt"		, &_lepPt			);
  outputBjetTree->Branch("lepEta"		, &_lepEta			);
  outputBjetTree->Branch("lepPhi"		, &_lepPhi			);
  outputBjetTree->Branch("lepMass"		, &_lepMass			);

  outputBjetTree->Branch("tauPt"                , &_tauPt                       );
  outputBjetTree->Branch("tauPhi"               , &_tauPhi                      );
  outputBjetTree->Branch("tauEta"               , &_tauEta                      );
  outputBjetTree->Branch("tauCharge"            , &_tauCharge                   );
  
  outputBjetTree->Branch("metPt"		, &(event->MET_pt_)	       	);
  outputBjetTree->Branch("metPhi"		, &(event->MET_phi_)   		);

  outputBjetTree->Branch("nJet"			, &_nJet			);
  outputBjetTree->Branch("nBJet"		, &_nBJet			);
  outputBjetTree->Branch("jetPt"		, &_jetPt			);
  outputBjetTree->Branch("jetEta"		, &_jetEta			);
  outputBjetTree->Branch("jetPhi"		, &_jetPhi			);
  outputBjetTree->Branch("jetMass"		, &_jetMass			);
  outputBjetTree->Branch("jetDeepB"		, &_jetDeepB			);

}


//_____________________________________________________________________________
double SkimAna::ScaleLumiW(Int_t nLHEPart){

  Int_t nJets = nLHEPart - 4; //It was nJets = nLHEPart - 2 in Legacy Rereco
  double fracLumiWt = 1.0;
  
  //2.1208, 0.2342, 0.1192, 0.0562, 0.0676 //using dataset similar volume of miniAOD
  /* switch(nJets) { */
  /* case 0: */
  /*   fracLumiWt = 2.1208 ; */
  /*   break; */
  /* case 1: */
  /*   fracLumiWt = 0.2342 ; */
  /*   break; */
  /* case 2: */
  /*   fracLumiWt = 0.1192 ; */
  /*   break; */
  /* case 3: */
  /*   fracLumiWt = 0.0562 ; */
  /*   break; */
  /* case 4: */
  /*   fracLumiWt = 0.0676 ; */
  /*   break; */
  /* default: */
  /*   fracLumiWt = 1.0; */
  /*   break; */
  /* } */
  /* return fracLumiWt ; */
  
  switch(nJets) {
  case 0:
    fracLumiWt = 1000.0/LumiWZ["Wjets"] ;
    break;
  case 1:
    fracLumiWt = 1000.0/(LumiWZ["W1jets"] + LumiWZ["Wjets"]) ;
    break;
  case 2:
    fracLumiWt = 1000.0/(LumiWZ["W2jets"] + LumiWZ["Wjets"]) ;
    break;
  case 3:
    fracLumiWt = 1000.0/(LumiWZ["W3jets"] + LumiWZ["Wjets"]) ;
    break;
  case 4:
    fracLumiWt = 1000.0/(LumiWZ["W4jets"] + LumiWZ["Wjets"]) ;
    break;
  default:
    fracLumiWt = 1.0;
    break;
  }
  return fracLumiWt ;
  
}


//_____________________________________________________________________________
double SkimAna::ScaleLumiZ(Int_t nLHEPart){

  Int_t nJets = nLHEPart - 4; //It was nJets = nLHEPart - 2 in Legacy Rereco
  double fracLumiWt = 1.0;
  
  //  0.1175, 0.0161, 0.0170, 0.0175, 0.0135
  /* switch(nJets) { */
  /* case 0: */
  /*   fracLumiWt = 0.1175 ; */
  /*   break; */
  /* case 1: */
  /*   fracLumiWt = 0.0161 ; */
  /*   break; */
  /* case 2: */
  /*   fracLumiWt = 0.0170 ; */
  /*   break; */
  /* case 3: */
  /*   fracLumiWt = 0.0175 ; */
  /*   break; */
  /* case 4: */
  /*   fracLumiWt = 0.0135 ; */
  /*   break; */
  /* default: */
  /*   fracLumiWt = 1.0; */
  /*   break; */
  /* } */
  /* return fracLumiWt ; */

  switch(nJets) {
  case 0:
    fracLumiWt = 1000.0/LumiWZ["DYjetsM50"] ;
    break;
  case 1:
    fracLumiWt = 1000.0/(LumiWZ["DY1jetsM50"] + LumiWZ["DYjetsM50"]) ;
    break;
  case 2:
    fracLumiWt = 1000.0/(LumiWZ["DY2jetsM50"] + LumiWZ["DYjetsM50"]) ;
    break;
  case 3:
    fracLumiWt = 1000.0/(LumiWZ["DY3jetsM50"] + LumiWZ["DYjetsM50"]) ;
    break;
  case 4:
    fracLumiWt = 1000.0/(LumiWZ["DY4jetsM50"] + LumiWZ["DYjetsM50"]) ;
    break;
  default:
    fracLumiWt = 1.0;
    break;
  }
  
  return fracLumiWt ;
}

//_____________________________________________________________________________
double SkimAna::getMuonTrackSF(TGraphAsymmErrors *tg, double eta)
{
  Double_t *eta_array = tg->GetX();
  Double_t *sf_array = tg->GetY();
  Int_t n_points = tg->GetN();
  double SF = 1.0;
  if(TMath::Abs(eta)<eta_array[0]-0.10) SF = sf_array[0];//bin width is 0.20
  for(Int_t i = 0; i < n_points; i++){
    if(TMath::Abs(eta)>=eta_array[i]-0.10 && TMath::Abs(eta)< eta_array[i]+0.10) SF = sf_array[i];
  }
  if(TMath::Abs(eta)>=eta_array[n_points-1]+0.10) SF = sf_array[n_points -1];
  return SF;
}

//_____________________________________________________________________________

float SkimAna::topPtReweight()
{
  
  float wt = 1.0;
  
  // if(!fSample.Contains("TTbar") && !fSample.Contains("Hplus"))
  //   return wt;

  //for (int imc = 0 ; imc < int(_genPDGID->size()) ; imc++ ){      
  int momtop = -12348, momtbar = -21356; //should not be initialized to same value
  double topPt = -1, tbarPt = -1;
  //for (int imc = 0 ; imc < 10 ; imc++ ){      
  for (int imc = 0 ; imc < int(event->nGenPart_) ; imc++ ){      
    TParticlePDG *partPDG = TDatabasePDG::Instance()->GetParticle(event->GenPart_pdgId_[imc]);
    if(event->GenPart_pdgId_[imc]==6){
      momtop = event->GenPart_genPartIdxMother_[imc] ;
      topPt = event->GenPart_pt_[imc];
    }
    if(event->GenPart_pdgId_[imc]==-6){
      momtbar = event->GenPart_genPartIdxMother_[imc] ;
      tbarPt = event->GenPart_pt_[imc];
    }
    // if(momtop == momtbar)
    //   break;
  }
  
  double sfTop    = exp(0.09494 - 0.00084*topPt);
  double sfTopBar = exp(0.09494 - 0.00084*tbarPt);
  
  // if(topPt>0 && tbarPt>0 && momtop==momtbar)
  //   wt = wt*sqrt(sfTop*sfTopBar);
  if(topPt>0 && tbarPt>0)
    wt = wt*sqrt(sfTop*sfTopBar);
  
  return wt;
}


//_____________________________________________________________________
Bool_t SkimAna::Notify()
{
//   called when loading a new file
//   get branch pointers
  
  isPreVFP = false ; isPostVFP = false ;
  string fname(fChain->GetCurrentFile()->GetName());
  fname = fname.substr(fname.find_last_of("/")+1,fname.size());
  if(fname.find("_ext4_Skim") != string::npos)
    fname = fname.substr(0,fname.find("_ext4_Skim"));
  else if (fname.find("_ext3_Skim") != string::npos)
    fname = fname.substr(0,fname.find("_ext3_Skim"));
  else if (fname.find("_ext2_Skim") != string::npos)
    fname = fname.substr(0,fname.find("_ext2_Skim"));
  else if (fname.find("_ext1_Skim") != string::npos)
    fname = fname.substr(0,fname.find("_ext1_Skim"));
  else if (fname.find("_preVFP_Skim") != string::npos){
    fname = fname.substr(0,fname.find("_preVFP_Skim"));
    isPreVFP = true;
  }else if (fname.find("_postVFP_Skim") != string::npos){
    fname = fname.substr(0,fname.find("_postVFP_Skim"));
    isPostVFP = true ;
  }else if (fname.find("_Skim") != string::npos)
    fname = fname.substr(0,fname.find("_Skim"));
  
  selector->isPreVFP = isPreVFP ;
  selector->isPostVFP = isPostVFP ;
  
  string inputKFResoPath = inputPathReso;
  if(isPreVFP or isPostVFP){

    if(isPreVFP){ 
      if(selector->useDeepCSVbTag)
	selector->btag_cut_DeepCSV = selector->btag_cut_DeepCSVa ; 
      else{
	selector->btag_cut = selector->btag_cuta ; 
	selector->ctag_CvsL_L_cut = selector->ctag_CvsL_L_cuta ; 
	selector->ctag_CvsB_L_cut = selector->ctag_CvsB_L_cuta ; 
	selector->ctag_CvsL_M_cut = selector->ctag_CvsL_M_cuta ; 
	selector->ctag_CvsB_M_cut = selector->ctag_CvsB_M_cuta ; 
	selector->ctag_CvsL_T_cut = selector->ctag_CvsL_T_cuta ; 
	selector->ctag_CvsB_T_cut = selector->ctag_CvsB_T_cuta ; 
      }
      inputKFResoPath += "/preVFP" ;
      fBCSFFile = fBCSFFile_a ;
    }

    if(isPostVFP){ 
      if(selector->useDeepCSVbTag)
	selector->btag_cut_DeepCSV = selector->btag_cut_DeepCSVb ; 
      else{
	selector->btag_cut = selector->btag_cutb ; 
	selector->ctag_CvsL_L_cut = selector->ctag_CvsL_L_cutb ; 
	selector->ctag_CvsB_L_cut = selector->ctag_CvsB_L_cutb ; 
	selector->ctag_CvsL_M_cut = selector->ctag_CvsL_M_cutb ; 
	selector->ctag_CvsB_M_cut = selector->ctag_CvsB_M_cutb ; 
	selector->ctag_CvsL_T_cut = selector->ctag_CvsL_T_cutb ; 
	selector->ctag_CvsB_T_cut = selector->ctag_CvsB_T_cutb ; 
      }
      inputKFResoPath += "/postVFP" ;
      fBCSFFile = fBCSFFile_b ;
    }
    
    if(selector->useDeepCSVbTag) 
      kinFit.SetBtagThresh(selector->btag_cut_DeepCSV);
    else
      kinFit.SetBtagThresh(selector->btag_cut);
  }
  kinFit.SetResoInputPath(inputKFResoPath);
  kinFit.UnloadObjReso();
  kinFit.LoadObjReso();
  kinFit.UseExtReso();
  
  fSampleType = fname;
  
  Info("Notify","processing fSampleType %s and file: %s",fSampleType.Data(), fChain->GetCurrentFile()->GetName());  
  
  /* if(!isData) */
  /*   _local_evtWeight = getEvtWeight(fname, fYear, luminosity); */
  
  float _xss = 0.0;
  if(!isData){
    
    //_local_evtWeight = getEvtWeight(fname, fYear, luminosity, totEventsUS[fname], _xss);
    _local_evtWeight = getEvtWeight(fname, fYear, luminosity, totEvents[fname], _xss);
    
    double scalelumi = 1.0;
    if(fSampleType.Contains("Wjets") || fSampleType.Contains("W1jets") || fSampleType.Contains("W2jets") || fSampleType.Contains("W3jets") || fSampleType.Contains("W4jets")){
      scalelumi = ScaleLumiW(event->nLHEPart_);
      _local_evtWeight = scalelumi * luminosity/1000.;
      Info("Notify", "Wjets : Updated special event weight : %lf for nLHEPart_ : %d", _local_evtWeight, event->nLHEPart_);
    }
    
    if(fSampleType.Contains("DYjetsM50") || fSampleType.Contains("DY1jetsM50") || fSampleType.Contains("DY2jetsM50") || fSampleType.Contains("DY3jetsM50") || fSampleType.Contains("DY4jetsM50")){
      scalelumi = ScaleLumiZ(event->nLHEPart_) ;
      _local_evtWeight = scalelumi * luminosity/1000.;
      Info("Notify", "DYjets : Updated special event weight : %lf for nLHEPart_ : %d", _local_evtWeight, event->nLHEPart_);
    }
    
    if(PUweighter)
      delete PUweighter;
    if(PUweighterUp)
      delete PUweighterUp;
    if(PUweighterDown)
      delete PUweighterDown;

    LoadPU();
  }//if MC
  
  if(fSampleType.Contains("mtop1695"))
    kinFit.SetTopMass(169.5);
  if(fSampleType.Contains("mtop1755"))
    kinFit.SetTopMass(175.5);
  
  if(fSampleType.Contains("Dilepton"))
    _kFType = 11;
  else if(fSampleType.Contains("Hadronic"))
    _kFType = 12;
  else if(fSampleType.Contains("Semilept"))
    _kFType = 13;
  else if(fSampleType.Contains("ST_s_channel"))
    _kFType = 21;
  else if(fSampleType.Contains("ST_t_channel"))
    _kFType = 22;
  else if(fSampleType.Contains("ST_tbar_channel"))
    _kFType = 23;
  else if(fSampleType.Contains("ST_tW_channel"))
    _kFType = 24;
  else if(fSampleType.Contains("ST_tbarW_channel"))
    _kFType = 25;
  else
    _kFType = 0; // initial value
  
  if(!isData){
    
    /* std::string fBCEffFileName = "" ; */
    /* if(!selector->useDeepCSVbTag){ //Deepjet */
    /*   if (fYear==2016){ */
    /* 	if(isPreVFP) */
    /* 	  fBCEffFileName = Form("%s/weightUL/BtagSF/Efficiency/btag_deepjet/%d/pre/%s_btag_eff_deepjet_%d.root",fBasePath.Data(),fYear,fSample.Data(),fYear);     */
    /* 	if(isPostVFP) */
    /* 	  fBCEffFileName = Form("%s/weightUL/BtagSF/Efficiency/btag_deepjet/%d/post/%s_btag_eff_deepjet_%d.root",fBasePath.Data(),fYear,fSample.Data(),fYear);     */
    /*   }else{ */
    /* 	fBCEffFileName = Form("%s/weightUL/BtagSF/Efficiency/btag_deepjet/%d/%s_btag_eff_deepjet_%d.root",fBasePath.Data(),fYear,fSample.Data(),fYear);     */
    /*   } */
    /* }else{ //DeepCSV     */
    /*   fBCEffFileName = Form("%s/weightUL/BtagSF/Efficiency/btag_deepcsv/%d/%s_btag_eff_deepcsv_%d.root",fBasePath.Data(),fYear,fSample.Data(),fYear);     */
    /* } */
  
    /* Info("Notify","Efficientcy file : %s",fBCEffFileName.c_str()); */
    /* Info("Notify","Btag threshold : %lf",((selector->useDeepCSVbTag) ? selector->btag_cut_DeepCSV  : selector->btag_cut)); */
  
    /* std::string effType = "BTag"; */
    /* std::string effCType = "CTag"; */
  
    /* std::string leffName = effType+"_l_M_efficiency"; */
    /* std::string ceffName = effType+"_c_M_efficiency"; */
    /* std::string beffName = effType+"_b_M_efficiency"; */

    /* std::string leffCName = effCType+"_l_L_efficiency"; */
    /* std::string ceffCName = effCType+"_c_L_efficiency"; */
    /* std::string beffCName = effCType+"_b_L_efficiency"; */
  
    /* TFile* inputFile = TFile::Open(fBCEffFileName.c_str(),"read"); */
    /* l_eff = (TH2D*) inputFile->Get(leffName.c_str()); */
    /* c_eff = (TH2D*) inputFile->Get(ceffName.c_str()); */
    /* b_eff = (TH2D*) inputFile->Get(beffName.c_str()); */

    /* l_CL_eff = (TH2D*) inputFile->Get(leffCName.c_str()); */
    /* c_CL_eff = (TH2D*) inputFile->Get(ceffCName.c_str()); */
    /* b_CL_eff = (TH2D*) inputFile->Get(beffCName.c_str()); */

    /* l_CM_eff = (TH2D*) inputFile->Get(Form("%s_l_M_efficiency",effCType.c_str())); */
    /* c_CM_eff = (TH2D*) inputFile->Get(Form("%s_c_M_efficiency",effCType.c_str())); */
    /* b_CM_eff = (TH2D*) inputFile->Get(Form("%s_b_M_efficiency",effCType.c_str())); */

    /* l_CT_eff = (TH2D*) inputFile->Get(Form("%s_l_T_efficiency",effCType.c_str())); */
    /* c_CT_eff = (TH2D*) inputFile->Get(Form("%s_c_T_efficiency",effCType.c_str())); */
    /* b_CT_eff = (TH2D*) inputFile->Get(Form("%s_b_T_efficiency",effCType.c_str())); */

    //CTagShapeCalibration EOY
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    SFb_hist = (TH2F *)fBCSFFile->Get("SFb_hist");
    SFc_hist = (TH2F *)fBCSFFile->Get("SFc_hist");
    SFl_hist = (TH2F *)fBCSFFile->Get("SFl_hist");
  
    SFb_hist_StatUp = (TH2F *)fBCSFFile->Get("SFb_hist_StatUp");
    SFc_hist_StatUp = (TH2F *)fBCSFFile->Get("SFc_hist_StatUp");
    SFl_hist_StatUp = (TH2F *)fBCSFFile->Get("SFl_hist_StatUp");
    SFb_hist_StatDown = (TH2F *)fBCSFFile->Get("SFb_hist_StatDown");
    SFc_hist_StatDown = (TH2F *)fBCSFFile->Get("SFc_hist_StatDown");
    SFl_hist_StatDown = (TH2F *)fBCSFFile->Get("SFl_hist_StatDown");
    
    SFb_hist_LHEScaleWeight_muFUp = (TH2F *)fBCSFFile->Get("SFb_hist_LHEScaleWeight_muFUp");
    SFc_hist_LHEScaleWeight_muFUp = (TH2F *)fBCSFFile->Get("SFc_hist_LHEScaleWeight_muFUp");
    SFl_hist_LHEScaleWeight_muFUp = (TH2F *)fBCSFFile->Get("SFl_hist_LHEScaleWeight_muFUp");
    SFb_hist_LHEScaleWeight_muFDown = (TH2F *)fBCSFFile->Get("SFb_hist_LHEScaleWeight_muFDown");
    SFc_hist_LHEScaleWeight_muFDown = (TH2F *)fBCSFFile->Get("SFc_hist_LHEScaleWeight_muFDown");
    SFl_hist_LHEScaleWeight_muFDown = (TH2F *)fBCSFFile->Get("SFl_hist_LHEScaleWeight_muFDown");

    SFb_hist_LHEScaleWeight_muRUp = (TH2F *)fBCSFFile->Get("SFb_hist_LHEScaleWeight_muRUp");
    SFc_hist_LHEScaleWeight_muRUp = (TH2F *)fBCSFFile->Get("SFc_hist_LHEScaleWeight_muRUp");
    SFl_hist_LHEScaleWeight_muRUp = (TH2F *)fBCSFFile->Get("SFl_hist_LHEScaleWeight_muRUp");
    SFb_hist_LHEScaleWeight_muRDown = (TH2F *)fBCSFFile->Get("SFb_hist_LHEScaleWeight_muRDown");
    SFc_hist_LHEScaleWeight_muRDown = (TH2F *)fBCSFFile->Get("SFc_hist_LHEScaleWeight_muRDown");
    SFl_hist_LHEScaleWeight_muRDown = (TH2F *)fBCSFFile->Get("SFl_hist_LHEScaleWeight_muRDown");

    SFb_hist_PSWeightISRUp = (TH2F *)fBCSFFile->Get("SFb_hist_PSWeightISRUp");
    SFc_hist_PSWeightISRUp = (TH2F *)fBCSFFile->Get("SFc_hist_PSWeightISRUp");
    SFl_hist_PSWeightISRUp = (TH2F *)fBCSFFile->Get("SFl_hist_PSWeightISRUp");
    SFb_hist_PSWeightISRDown = (TH2F *)fBCSFFile->Get("SFb_hist_PSWeightISRDown");
    SFc_hist_PSWeightISRDown = (TH2F *)fBCSFFile->Get("SFc_hist_PSWeightISRDown");
    SFl_hist_PSWeightISRDown = (TH2F *)fBCSFFile->Get("SFl_hist_PSWeightISRDown");

    SFb_hist_PSWeightFSRUp = (TH2F *)fBCSFFile->Get("SFb_hist_PSWeightFSRUp");
    SFc_hist_PSWeightFSRUp = (TH2F *)fBCSFFile->Get("SFc_hist_PSWeightFSRUp");
    SFl_hist_PSWeightFSRUp = (TH2F *)fBCSFFile->Get("SFl_hist_PSWeightFSRUp");
    SFb_hist_PSWeightFSRDown = (TH2F *)fBCSFFile->Get("SFb_hist_PSWeightFSRDown");
    SFc_hist_PSWeightFSRDown = (TH2F *)fBCSFFile->Get("SFc_hist_PSWeightFSRDown");
    SFl_hist_PSWeightFSRDown = (TH2F *)fBCSFFile->Get("SFl_hist_PSWeightFSRDown");

    SFb_hist_PUWeightUp = (TH2F *)fBCSFFile->Get("SFb_hist_PUWeightUp");
    SFc_hist_PUWeightUp = (TH2F *)fBCSFFile->Get("SFc_hist_PUWeightUp");
    SFl_hist_PUWeightUp = (TH2F *)fBCSFFile->Get("SFl_hist_PUWeightUp");
    SFb_hist_PUWeightDown = (TH2F *)fBCSFFile->Get("SFb_hist_PUWeightDown");
    SFc_hist_PUWeightDown = (TH2F *)fBCSFFile->Get("SFc_hist_PUWeightDown");
    SFl_hist_PUWeightDown = (TH2F *)fBCSFFile->Get("SFl_hist_PUWeightDown");
    
    SFb_hist_jesTotalUp = (TH2F *)fBCSFFile->Get("SFb_hist_jesTotalUp");
    SFc_hist_jesTotalUp = (TH2F *)fBCSFFile->Get("SFc_hist_jesTotalUp");
    SFl_hist_jesTotalUp = (TH2F *)fBCSFFile->Get("SFl_hist_jesTotalUp");
    SFb_hist_jesTotalDown = (TH2F *)fBCSFFile->Get("SFb_hist_jesTotalDown");
    SFc_hist_jesTotalDown = (TH2F *)fBCSFFile->Get("SFc_hist_jesTotalDown");
    SFl_hist_jesTotalDown = (TH2F *)fBCSFFile->Get("SFl_hist_jesTotalDown");
  
    SFb_hist_jerUp = (TH2F *)fBCSFFile->Get("SFb_hist_jerUp");
    SFc_hist_jerUp = (TH2F *)fBCSFFile->Get("SFc_hist_jerUp");
    SFl_hist_jerUp = (TH2F *)fBCSFFile->Get("SFl_hist_jerUp");
    SFb_hist_jerDown = (TH2F *)fBCSFFile->Get("SFb_hist_jerDown");
    SFc_hist_jerDown = (TH2F *)fBCSFFile->Get("SFc_hist_jerDown");
    SFl_hist_jerDown = (TH2F *)fBCSFFile->Get("SFl_hist_jerDown");

    SFb_hist_InterpUp = (TH2F *)fBCSFFile->Get("SFb_hist_InterpUp");
    SFc_hist_InterpUp = (TH2F *)fBCSFFile->Get("SFc_hist_InterpUp");
    SFl_hist_InterpUp = (TH2F *)fBCSFFile->Get("SFl_hist_InterpUp");
    SFb_hist_InterpDown = (TH2F *)fBCSFFile->Get("SFb_hist_InterpDown");
    SFc_hist_InterpDown = (TH2F *)fBCSFFile->Get("SFc_hist_InterpDown");
    SFl_hist_InterpDown = (TH2F *)fBCSFFile->Get("SFl_hist_InterpDown");
  
    SFb_hist_ExtrapUp = (TH2F *)fBCSFFile->Get("SFb_hist_ExtrapUp");
    SFc_hist_ExtrapUp = (TH2F *)fBCSFFile->Get("SFc_hist_ExtrapUp");
    SFl_hist_ExtrapUp = (TH2F *)fBCSFFile->Get("SFl_hist_ExtrapUp");
    SFb_hist_ExtrapDown = (TH2F *)fBCSFFile->Get("SFb_hist_ExtrapDown");
    SFc_hist_ExtrapDown = (TH2F *)fBCSFFile->Get("SFc_hist_ExtrapDown");
    SFl_hist_ExtrapDown = (TH2F *)fBCSFFile->Get("SFl_hist_ExtrapDown");

    SFb_hist_XSec_BRUnc_DYJets_bUp = (TH2F *)fBCSFFile->Get("SFb_hist_XSec_BRUnc_DYJets_bUp");
    SFc_hist_XSec_BRUnc_DYJets_bUp = (TH2F *)fBCSFFile->Get("SFc_hist_XSec_BRUnc_DYJets_bUp");
    SFl_hist_XSec_BRUnc_DYJets_bUp = (TH2F *)fBCSFFile->Get("SFl_hist_XSec_BRUnc_DYJets_bUp");
    SFb_hist_XSec_BRUnc_DYJets_bDown = (TH2F *)fBCSFFile->Get("SFb_hist_XSec_BRUnc_DYJets_bDown");
    SFc_hist_XSec_BRUnc_DYJets_bDown = (TH2F *)fBCSFFile->Get("SFc_hist_XSec_BRUnc_DYJets_bDown");
    SFl_hist_XSec_BRUnc_DYJets_bDown = (TH2F *)fBCSFFile->Get("SFl_hist_XSec_BRUnc_DYJets_bDown");

    SFb_hist_XSec_BRUnc_DYJets_cUp = (TH2F *)fBCSFFile->Get("SFb_hist_XSec_BRUnc_DYJets_cUp");
    SFc_hist_XSec_BRUnc_DYJets_cUp = (TH2F *)fBCSFFile->Get("SFc_hist_XSec_BRUnc_DYJets_cUp");
    SFl_hist_XSec_BRUnc_DYJets_cUp = (TH2F *)fBCSFFile->Get("SFl_hist_XSec_BRUnc_DYJets_cUp");
    SFb_hist_XSec_BRUnc_DYJets_cDown = (TH2F *)fBCSFFile->Get("SFb_hist_XSec_BRUnc_DYJets_cDown");
    SFc_hist_XSec_BRUnc_DYJets_cDown = (TH2F *)fBCSFFile->Get("SFc_hist_XSec_BRUnc_DYJets_cDown");
    SFl_hist_XSec_BRUnc_DYJets_cDown = (TH2F *)fBCSFFile->Get("SFl_hist_XSec_BRUnc_DYJets_cDown");
  
    SFb_hist_XSec_BRUnc_WJets_cUp = (TH2F *)fBCSFFile->Get("SFb_hist_XSec_BRUnc_WJets_cUp");
    SFc_hist_XSec_BRUnc_WJets_cUp = (TH2F *)fBCSFFile->Get("SFc_hist_XSec_BRUnc_WJets_cUp");
    SFl_hist_XSec_BRUnc_WJets_cUp = (TH2F *)fBCSFFile->Get("SFl_hist_XSec_BRUnc_WJets_cUp");
    SFb_hist_XSec_BRUnc_WJets_cDown = (TH2F *)fBCSFFile->Get("SFb_hist_XSec_BRUnc_WJets_cDown");
    SFc_hist_XSec_BRUnc_WJets_cDown = (TH2F *)fBCSFFile->Get("SFc_hist_XSec_BRUnc_WJets_cDown");
    SFl_hist_XSec_BRUnc_WJets_cDown = (TH2F *)fBCSFFile->Get("SFl_hist_XSec_BRUnc_WJets_cDown");  

  }

  return kTRUE;
}


/// constructor
METzCalculator::METzCalculator() {
  isComplex_ = false;
  otherSol_ = 0.;
  leptonMass_ = 0.105658367;
}

/// destructor
METzCalculator::~METzCalculator() {
}

/// member functions
double METzCalculator::Calculate(int type) {

  double M_W  = 80.379;
  double M_mu =  leptonMass_;
  double emu = lepton_.E();
  double pxmu = lepton_.Px();
  double pymu = lepton_.Py();
  double pzmu = lepton_.Pz();
  double pxnu = MET_.Px();
  double pynu = MET_.Py();
  double pznu = 0.;
  otherSol_ = 0.;
		
  double a = M_W*M_W - M_mu*M_mu + 2.0*pxmu*pxnu + 2.0*pymu*pynu;
  double A = 4.0*(emu*emu - pzmu*pzmu);
  double B = -4.0*a*pzmu;
  double C = 4.0*emu*emu*(pxnu*pxnu + pynu*pynu) - a*a;

  double tmproot = B*B - 4.0*A*C;

  if (tmproot<0) {
    isComplex_= true;
    pznu = - B/(2*A); // take real part of complex roots
    otherSol_ = pznu;
    //std::cout << " Neutrino Solutions: complex, real part " << pznu << std::endl;
  }
  else {
    isComplex_ = false;
    double tmpsol1 = (-B + TMath::Sqrt(tmproot))/(2.0*A);
    double tmpsol2 = (-B - TMath::Sqrt(tmproot))/(2.0*A);

    //std::cout << " Neutrino Solutions: " << tmpsol1 << ", " << tmpsol2 << std::endl;
			
    if (type == 0 ) {
      // two real roots, pick the one closest to pz of muon
      if (TMath::Abs(tmpsol2-pzmu) < TMath::Abs(tmpsol1-pzmu)) { pznu = tmpsol2; otherSol_ = tmpsol1;}
      else { pznu = tmpsol1; otherSol_ = tmpsol2; } 
      // if pznu is > 300 pick the most central root
      /* if ( pznu > 300. ) { */
      /* 	if (TMath::Abs(tmpsol1)<TMath::Abs(tmpsol2) ) { pznu = tmpsol1; otherSol_ = tmpsol2; } */
      /* 	else { pznu = tmpsol2; otherSol_ = tmpsol1; } */
      /* } */
    }
    if (type == 1 ) {
      // two real roots, pick the one closest to pz of muon
      if (TMath::Abs(tmpsol2-pzmu) < TMath::Abs(tmpsol1-pzmu)) { pznu = tmpsol2; otherSol_ = tmpsol1; }
      else {pznu = tmpsol1; otherSol_ = tmpsol2; }
    }
    if (type == 2 ) {
      // pick the most central root.
      if (TMath::Abs(tmpsol1)<TMath::Abs(tmpsol2) ) { pznu = tmpsol1; otherSol_ = tmpsol2; }
      else { pznu = tmpsol2; otherSol_ = tmpsol1; }
    }
    if (type == 3 ) {
      // pick the largest value of the cosine
      TVector3 p3w, p3mu;
      p3w.SetXYZ(pxmu+pxnu, pymu+pynu, pzmu+ tmpsol1);
      p3mu.SetXYZ(pxmu, pymu, pzmu );
				
      double sinthcm1 = 2.*(p3mu.Perp(p3w))/M_W;
      p3w.SetXYZ(pxmu+pxnu, pymu+pynu, pzmu+ tmpsol2);
      double sinthcm2 = 2.*(p3mu.Perp(p3w))/M_W;

      double costhcm1 = TMath::Sqrt(1. - sinthcm1*sinthcm1);
      double costhcm2 = TMath::Sqrt(1. - sinthcm2*sinthcm2);

      if ( costhcm1 > costhcm2 ) { pznu = tmpsol1; otherSol_ = tmpsol2; }
      else { pznu = tmpsol2;otherSol_ = tmpsol1; }
    }
		
  }

  //Particle neutrino;
  //neutrino.setP4( LorentzVector(pxnu, pynu, pznu, TMath::Sqrt(pxnu*pxnu + pynu*pynu + pznu*pznu ))) ;

  return pznu;
}

// Kinfit methods
//////////////////////////////////////////////////////////////////////////////////

double KinFit::ErrEt(float Et, float Eta) {
  double InvPerr2, a, b, c;
  if(fabs(Eta) < 1.4){
    a = 5.6;
    b = 1.25;
    c = 0.033;
  }
  else{
    a = 4.8;
    b = 0.89;
    c = 0.043;
  }
  InvPerr2 = (a * a) + (b * b) * Et + (c * c) * Et * Et;
  return InvPerr2;
}

double KinFit::ErrEta(float Et, float Eta) {
  double InvPerr2, a, b, c;
  if(fabs(Eta) < 1.4){
    a = 1.215;
    b = 0.037;
    c = 7.941 * 0.0001;
  }
  else{
    a = 1.773;
    b = 0.034;
    c = 3.56 * 0.0001;
  }
  InvPerr2 = a/(Et * Et) + b/Et + c;
  return InvPerr2;
}

double KinFit::ErrPhi(float Et, float Eta) {
  double InvPerr2, a, b, c;
  if(fabs(Eta) < 1.4){
    a = 6.65;
    b = 0.04;
    c = 8.49 * 0.00001;
  }
  else{
    a = 2.908;
    b = 0.021;
    c = 2.59 * 0.0001;
  }
  InvPerr2 = a/(Et * Et) + b/Et + c;
  return InvPerr2;
}

void KinFit::print(TKinFitter *fitter)
{
  std::cout << "=============================================" << std ::endl;
  std::cout << "-> Number of measured Particles  : " << fitter->nbMeasParticles() << std::endl;
  std::cout << "-> Number of unmeasured particles: " << fitter->nbUnmeasParticles() << std::endl;
  std::cout << "-> Number of constraints         : " << fitter->nbConstraints() << std::endl;
  std::cout << "-> Number of degrees of freedom  : " << fitter->getNDF() << std::endl;
  std::cout << "-> Number of parameters A        : " << fitter->getNParA() << std::endl;
  std::cout << "-> Number of parameters B        : " << fitter->getNParB() << std::endl;
  std::cout << "-> Maximum number of iterations  : " << fitter->getMaxNumberIter() << std::endl;
  std::cout << "-> Maximum deltaS                : " << fitter->getMaxDeltaS() << std::endl;
  std::cout << "-> Maximum F                     : " << fitter->getMaxF() << std::endl;
  std::cout << "+++++++++++++++++++++++++++++++++++++++++++++" << std ::endl;
  std::cout << "-> Status                        : " << fitter->getStatus() << std::endl;
  std::cout << "-> Number of iterations          : " << fitter->getNbIter() << std::endl;
  std::cout << "-> S                             : " << fitter->getS() << std::endl;
  std::cout << "-> F                             : " << fitter->getF() << std::endl;
  std::cout << "+++++++++++++++++++++++++++++++++++++++++++++" << std ::endl;
  for (int ipart = 0 ; ipart < fitter->nbMeasParticles() ; ipart++ ){
    std::cout << "---------------------------------------------" << std ::endl;
    std::cout<<"-> Particle :" << ipart << ",  name :" << fitter->getMeasParticle(ipart)->GetName() << std::endl;
    fitter->get4Vec(ipart)->Print();
    std::cout << "---------------------------------------------" << std ::endl;
  }
  std::cout << "+++++++++++++++++++++++++++++++++++++++++++++" << std ::endl;
  std::cout << "-> Covariance Matrix                        : " << std::endl;
  fitter->getCovMatrix()->Print();
  std::cout << "---------------------------------------------" << std ::endl;
  std::cout << "-> Fitted Covariance Matrix                        : " << std::endl;
  fitter->getCovMatrixFit()->Print();
  std::cout << "=============================================" << std ::endl;
  
}

int KinFit::udscResolution(double et, double eta, double& resEt, double& resEta, double& resPhi)
{

  double abseta = fabs(eta) ;
  
  if (0.000 <= abseta  and  abseta < 0.087){
    resEt   = et * (TMath::Sqrt( TMath::Power(0.0591,2) + TMath::Power(1/TMath::Sqrt(et),2) + TMath::Power(0.891/et,2) ) ) ;
    resEta  = TMath::Sqrt( TMath::Power(0.00915,2) + TMath::Power(1.51/et,2) ) ;
    resPhi  = TMath::Sqrt( TMath::Power(0.01,2) + TMath::Power(1.6/et,2) ) ;
  }
    
  else if (0.087 <= abseta  and  abseta < 0.174){
    resEt   = et * (TMath::Sqrt( TMath::Power(0.0619,2) + TMath::Power(0.975/TMath::Sqrt(et),2) + TMath::Power(1.54/et,2) ) ) ;
    resEta  = TMath::Sqrt( TMath::Power(0.00887,2) + TMath::Power(1.53/et,2) ) ;
    resPhi  = TMath::Sqrt( TMath::Power(0.00982,2) + TMath::Power(1.61/et,2) ) ;
  }
    
  else if (0.174 <= abseta  and  abseta < 0.261){
    resEt   = et * (TMath::Sqrt( TMath::Power(0.0574,2) + TMath::Power(1/TMath::Sqrt(et),2) + TMath::Power(1.49e-05/et,2) ) ) ;
    resEta  = TMath::Sqrt( TMath::Power(0.00865,2) + TMath::Power(1.54/et,2)) ;
    resPhi  = TMath::Sqrt( TMath::Power(0.0101,2) + TMath::Power(1.59/et,2)) ;
  }
    
  else if (0.261 <= abseta  and  abseta < 0.348){
    resEt   = et * (TMath::Sqrt( TMath::Power(0.0569,2) + TMath::Power(1.01/TMath::Sqrt(et),2) + TMath::Power(1.22e-07/et,2) ) ) ;
    resEta  = TMath::Sqrt( TMath::Power(0.00867,2) + TMath::Power(1.55/et,2) ) ;
    resPhi  = TMath::Sqrt( TMath::Power(0.00988,2) + TMath::Power(1.6/et,2) ) ;
  }
    
  else if (0.348 <= abseta  and  abseta < 0.435){
    resEt   = et * (TMath::Sqrt( TMath::Power(0.057,2) + TMath::Power(1/TMath::Sqrt(et),2) + TMath::Power(2.17e-08/et,2) ) ) ;
    resEta  = TMath::Sqrt( TMath::Power(0.00907,2) + TMath::Power(1.55/et,2) ) ;
    resPhi  = TMath::Sqrt( TMath::Power(0.0102,2) + TMath::Power(1.59/et,2) ) ;
  }
    
  else if (0.435 <= abseta  and  abseta < 0.522){
    resEt   = et * (TMath::Sqrt( TMath::Power(0.0522,2) + TMath::Power(1.02/TMath::Sqrt(et),2) + TMath::Power(2.64e-05/et,2) ) ) ;
    resEta  = TMath::Sqrt( TMath::Power(0.00844,2) + TMath::Power(1.59/et,2) ) ;
    resPhi  = TMath::Sqrt( TMath::Power(0.00982,2) + TMath::Power(1.6/et,2) ) ;
  }
    
  else if (0.522 <= abseta  and  abseta < 0.609){
    resEt   = et * (TMath::Sqrt( TMath::Power(0.0502,2) + TMath::Power(1.02/TMath::Sqrt(et),2) + TMath::Power(2.6e-06/et,2) ) ) ;
    resEta  = TMath::Sqrt( TMath::Power(0.00915,2) + TMath::Power(1.57/et,2) ) ;
    resPhi  = TMath::Sqrt( TMath::Power(0.00979,2) + TMath::Power(1.6/et,2) ) ;
  }
    
  else if (0.609 <= abseta  and  abseta < 0.696){
    resEt   = et * (TMath::Sqrt( TMath::Power(0.053,2) + TMath::Power(1.03/TMath::Sqrt(et),2) + TMath::Power(4.87e-07/et,2) ) ) ;
    resEta  = TMath::Sqrt( TMath::Power(0.00856,2) + TMath::Power(1.58/et,2) ) ;
    resPhi  = TMath::Sqrt( TMath::Power(0.00925,2) + TMath::Power(1.62/et,2) ) ;
  }
    
  else if (0.696 <= abseta  and  abseta < 0.783){
    resEt   = et * (TMath::Sqrt( TMath::Power(0.051,2) + TMath::Power(1.03/TMath::Sqrt(et),2) + TMath::Power(7.53e-06/et,2) ) ) ;
    resEta  = TMath::Sqrt( TMath::Power(0.00897,2) + TMath::Power(1.58/et,2) ) ;
    resPhi  = TMath::Sqrt( TMath::Power(0.00973,2) + TMath::Power(1.61/et,2) ) ;
  }
    
  else if (0.783 <= abseta  and  abseta < 0.870){
    resEt   = et * (TMath::Sqrt( TMath::Power(0.0549,2) + TMath::Power(1.04/TMath::Sqrt(et),2) + TMath::Power(5.62e-08/et,2) ) ) ;
    resEta  = TMath::Sqrt( TMath::Power(0.0095,2) + TMath::Power(1.6/et,2) ) ;
    resPhi  = TMath::Sqrt( TMath::Power(0.00971,2) + TMath::Power(1.62/et,2) ) ;
  }
    
  else if (0.870 <= abseta  and  abseta < 0.957){
    resEt   = et * (TMath::Sqrt( TMath::Power(0.0544,2) + TMath::Power(1.06/TMath::Sqrt(et),2) + TMath::Power(1.07e-05/et,2) ) ) ;
    resEta  = TMath::Sqrt( TMath::Power(0.00836,2) + TMath::Power(1.65/et,2) ) ;
    resPhi  = TMath::Sqrt( TMath::Power(0.00916,2) + TMath::Power(1.64/et,2) ) ;
  }
    
  else if (0.957 <= abseta  and  abseta < 1.044){
    resEt   = et * (TMath::Sqrt( TMath::Power(0.0519,2) + TMath::Power(1.09/TMath::Sqrt(et),2) + TMath::Power(8.43e-06/et,2) ) ) ;
    resEta  = TMath::Sqrt( TMath::Power(0.00782,2) + TMath::Power(1.68/et,2) ) ;
    resPhi  = TMath::Sqrt( TMath::Power(0.00959,2) + TMath::Power(1.66/et,2) ) ;
  }
    
  else if (1.044 <= abseta  and  abseta < 1.131){
    resEt   = et * (TMath::Sqrt( TMath::Power(0.0539,2) + TMath::Power(1.12/TMath::Sqrt(et),2) + TMath::Power(1.97e-07/et,2) ) ) ;
    resEta  = TMath::Sqrt( TMath::Power(0.0093,2) + TMath::Power(1.65/et,2) ) ;
    resPhi  = TMath::Sqrt( TMath::Power(0.00964,2) + TMath::Power(1.67/et,2) ) ;
  }
    
  else if (1.131 <= abseta  and  abseta < 1.218){
    resEt   = et * (TMath::Sqrt( TMath::Power(0.0492,2) + TMath::Power(1.16/TMath::Sqrt(et),2) + TMath::Power(1.37e-08/et,2) ) ) ;
    resEta  = TMath::Sqrt( TMath::Power(0.00986,2) + TMath::Power(1.69/et,2) ) ;
    resPhi  = TMath::Sqrt( TMath::Power(0.00969,2) + TMath::Power(1.71/et,2) ) ;
  }
    
  else if (1.218 <= abseta  and  abseta < 1.305){
    resEt   = et * (TMath::Sqrt( TMath::Power(0.0489,2) + TMath::Power(1.18/TMath::Sqrt(et),2) + TMath::Power(3.44e-07/et,2) ) ) ;
    resEta  = TMath::Sqrt( TMath::Power(0.0124,2) + TMath::Power(1.72/et,2) ) ;
    resPhi  = TMath::Sqrt( TMath::Power(0.00992,2) + TMath::Power(1.76/et,2) ) ;
  }
    
  else if (1.305 <= abseta  and  abseta < 1.392){
    resEt   = et * (TMath::Sqrt( TMath::Power(0.0414,2) + TMath::Power(1.25/TMath::Sqrt(et),2) + TMath::Power(1.98e-07/et,2) ) ) ;
    resEta  = TMath::Sqrt( TMath::Power(0.0181,2) + TMath::Power(1.63/et,2) ) ;
    resPhi  = TMath::Sqrt( TMath::Power(0.0124,2) + TMath::Power(1.79/et,2) ) ;
  }
    
  else if (1.392 <= abseta  and  abseta < 1.479){
    resEt   = et * (TMath::Sqrt( TMath::Power(0.0373,2) + TMath::Power(1.26/TMath::Sqrt(et),2) + TMath::Power(5.4e-07/et,2) ) ) ;
    resEta  = TMath::Sqrt( TMath::Power(0.0121,2) + TMath::Power(1.69/et,2) ) ;
    resPhi  = TMath::Sqrt( TMath::Power(0.0135,2) + TMath::Power(1.8/et,2) ) ;
  }
    
  else if (1.479 <= abseta  and  abseta < 1.566){
    resEt   = et * (TMath::Sqrt( TMath::Power(0.0125,2) + TMath::Power(1.24/TMath::Sqrt(et),2) + TMath::Power(1e-06/et,2) ) ) ;
    resEta  = TMath::Sqrt( TMath::Power(0.0122,2) + TMath::Power(1.69/et,2) ) ;
    resPhi  = TMath::Sqrt( TMath::Power(0.0107,2) + TMath::Power(1.85/et,2) ) ;
  }
    
  else if (1.566 <= abseta  and  abseta < 1.653){
    resEt   = et * (TMath::Sqrt( TMath::Power(1.37e-07,2) + TMath::Power(1.08/TMath::Sqrt(et),2) + TMath::Power(3.06/et,2) ) ) ;
    resEta  = TMath::Sqrt( TMath::Power(0.00975,2) + TMath::Power(1.69/et,2) ) ;
    resPhi  = TMath::Sqrt( TMath::Power(0.00895,2) + TMath::Power(1.84/et,2) ) ;
  }
    
  else if (1.653 <= abseta  and  abseta < 1.740){
    resEt   = et * (TMath::Sqrt( TMath::Power(2.37e-07,2) + TMath::Power(1.04/TMath::Sqrt(et),2) + TMath::Power(3.01/et,2) ) ) ;
    resEta  = TMath::Sqrt( TMath::Power(0.00881,2) + TMath::Power(1.71/et,2) ) ;
    resPhi  = TMath::Sqrt( TMath::Power(0.00902,2) + TMath::Power(1.81/et,2) ) ;
  }
    
  else if (1.740 <= abseta  and  abseta < 1.830){
    resEt   = et * (TMath::Sqrt( TMath::Power(2.3e-07,2) + TMath::Power(1/TMath::Sqrt(et),2) + TMath::Power(3.1/et,2) ) ) ;
    resEta  = TMath::Sqrt( TMath::Power(0.00938,2) + TMath::Power(1.75/et,2) ) ;
    resPhi  = TMath::Sqrt( TMath::Power(0.00861,2) + TMath::Power(1.79/et,2) ) ;
  }
    
  else if (1.830 <= abseta  and  abseta < 1.930){
    resEt   = et * (TMath::Sqrt( TMath::Power(1.25e-07,2) + TMath::Power(0.965/TMath::Sqrt(et),2) + TMath::Power(3.14/et,2) ) ) ;
    resEta  = TMath::Sqrt( TMath::Power(0.00894,2) + TMath::Power(1.8/et,2)) ;
    resPhi  = TMath::Sqrt( TMath::Power(0.00877,2) + TMath::Power(1.75/et,2)) ;
  }
    
  else if (1.930 <= abseta  and  abseta < 2.043){
    resEt   = et * (TMath::Sqrt( TMath::Power(5.78e-08,2) + TMath::Power(0.924/TMath::Sqrt(et),2) + TMath::Power(3.14/et,2) ) ) ;
    resEta  = TMath::Sqrt( TMath::Power(0.00893,2) + TMath::Power(1.83/et,2) ) ;
    resPhi  = TMath::Sqrt( TMath::Power(0.00791,2) + TMath::Power(1.73/et,2) ) ;
  }
    
  else if (2.043 <= abseta  and  abseta < 2.172){
    resEt   = et * (TMath::Sqrt( TMath::Power(4.25e-08,2) + TMath::Power(0.923/TMath::Sqrt(et),2) + TMath::Power(2.85/et,2) ) ) ;
    resEta  = TMath::Sqrt( TMath::Power(0.0099,2) + TMath::Power(1.82/et,2) ) ;
    resPhi  = TMath::Sqrt( TMath::Power(0.00775,2) + TMath::Power(1.73/et,2) ) ;
  }
    
  else if (2.172 <= abseta  and  abseta < 2.322){
    resEt   = et * (TMath::Sqrt( TMath::Power(0.00601,2) + TMath::Power(0.881/TMath::Sqrt(et),2) + TMath::Power(3.23/et,2) ) ) ;
    resEta  = TMath::Sqrt( TMath::Power(0.00944,2) + TMath::Power(1.8/et,2) ) ;
    resPhi  = TMath::Sqrt( TMath::Power(0.00807,2) + TMath::Power(1.71/et,2) ) ;
  }
    
  else if (2.322 <= abseta  and  abseta < 2.500){
    resEt   = et * (TMath::Sqrt( TMath::Power(4.94e-08,2) + TMath::Power(0.86/TMath::Sqrt(et),2) + TMath::Power(3.56/et,2) ) ) ;
    resEta  = TMath::Sqrt( TMath::Power(0.0103,2) + TMath::Power(2.15/et,2) ) ;
    resPhi  = TMath::Sqrt( TMath::Power(0.0103,2) + TMath::Power(1.81/et,2) ) ;
  }

  return true;
}

int KinFit::bjetResolution(double et, double eta, double& resEt, double& resEta, double& resPhi)
{

  double abseta = fabs(eta) ;


  if (0.000 <= abseta and abseta < 0.087) {
    resEt   = et * ( TMath::Sqrt( TMath::Power(0.0686,2) + TMath::Power(1.03/TMath::Sqrt(et),2) + TMath::Power(1.68/et,2) ) )  ;
    resEta  =  TMath::Sqrt( TMath::Power(0.00605,2) + TMath::Power(1.63/et,2) )  ;
    resPhi  =  TMath::Sqrt( TMath::Power(0.00787,2) + TMath::Power(1.74/et,2) )  ;
  }

  else if (0.087 <= abseta and abseta < 0.174) {
    resEt   = et * ( TMath::Sqrt( TMath::Power(0.0737,2) + TMath::Power(1.01/TMath::Sqrt(et),2) + TMath::Power(1.74/et,2) ) )  ;
    resEta  =  TMath::Sqrt( TMath::Power(0.00592,2) + TMath::Power(1.64/et,2) )  ;
    resPhi  =  TMath::Sqrt( TMath::Power(0.00766,2) + TMath::Power(1.74/et,2) )  ;
  }

  else if (0.174 <= abseta and abseta < 0.261) {
    resEt   = et * ( TMath::Sqrt( TMath::Power(0.0657,2) + TMath::Power(1.07/TMath::Sqrt(et),2) + TMath::Power(5.16e-06/et,2) ) )  ;
    resEta  =  TMath::Sqrt( TMath::Power(0.00584,2) + TMath::Power(1.65/et,2) )  ;
    resPhi  =  TMath::Sqrt( TMath::Power(0.00755,2) + TMath::Power(1.74/et,2) )  ;
  }

  else if (0.261 <= abseta and abseta < 0.348) {
    resEt   = et * ( TMath::Sqrt( TMath::Power(0.062,2) + TMath::Power(1.07/TMath::Sqrt(et),2) +  TMath::Power(0.000134/et,2) ) )  ;
    resEta  =  TMath::Sqrt( TMath::Power(0.00593,2) + TMath::Power(1.65/et,2) )  ;
    resPhi  =  TMath::Sqrt( TMath::Power(0.00734,2) + TMath::Power(1.74/et,2) )  ;
  }

  else if (0.348 <= abseta and abseta < 0.435) {
    resEt   = et * ( TMath::Sqrt( TMath::Power(0.0605,2) + TMath::Power(1.07/TMath::Sqrt(et),2) + TMath::Power(1.84e-07/et,2) ) )  ;
    resEta  =  TMath::Sqrt( TMath::Power(0.00584,2) + TMath::Power(1.68/et,2) )  ;
    resPhi  =  TMath::Sqrt( TMath::Power(0.00734,2) + TMath::Power(1.75/et,2) )  ;
  }

  else if (0.435 <= abseta and abseta < 0.522) {
    resEt   = et * ( TMath::Sqrt( TMath::Power(0.059,2) + TMath::Power(1.08/TMath::Sqrt(et),2) + TMath::Power(9.06e-09/et,2) ) )  ;
    resEta  =  TMath::Sqrt( TMath::Power(0.00646,2) + TMath::Power(1.67/et,2) )  ;
    resPhi  =  TMath::Sqrt( TMath::Power(0.00767,2) + TMath::Power(1.74/et,2) )  ;
  }

  else if (0.522 <= abseta and abseta < 0.609) {
    resEt   = et * ( TMath::Sqrt( TMath::Power(0.0577,2) + TMath::Power(1.08/TMath::Sqrt(et),2) + TMath::Power(5.46e-06/et,2) ) )  ;
    resEta  =  TMath::Sqrt( TMath::Power(0.00661,2) + TMath::Power(1.67/et,2) )  ;
    resPhi  =  TMath::Sqrt( TMath::Power(0.00742,2) + TMath::Power(1.75/et,2) )  ;
  }

  else if (0.609 <= abseta and abseta < 0.696) {
    resEt   = et * ( TMath::Sqrt( TMath::Power(0.0525,2) + TMath::Power(1.09/TMath::Sqrt(et),2) + TMath::Power(4.05e-05/et,2) ) )  ;
    resEta  =  TMath::Sqrt( TMath::Power(0.00724,2) + TMath::Power(1.65/et,2) )  ;
    resPhi  =  TMath::Sqrt( TMath::Power(0.00771,2) + TMath::Power(1.73/et,2) )  ;
  }

  else if (0.696 <= abseta and abseta < 0.783) {
    resEt   = et * ( TMath::Sqrt( TMath::Power(0.0582,2) + TMath::Power(1.09/TMath::Sqrt(et),2) + TMath::Power(1.17e-05/et,2) ) )  ;
    resEta  =  TMath::Sqrt( TMath::Power(0.00763,2) + TMath::Power(1.67/et,2) )  ;
    resPhi  =  TMath::Sqrt( TMath::Power(0.00758,2) + TMath::Power(1.76/et,2) )  ;
  }

  else if (0.783 <= abseta and abseta < 0.870) {
    resEt   = et * ( TMath::Sqrt( TMath::Power(0.0649,2) + TMath::Power(1.08/TMath::Sqrt(et),2) + TMath::Power(7.85e-06/et,2) ) )  ;
    resEta  =  TMath::Sqrt( TMath::Power(0.00746,2) + TMath::Power(1.7/et,2) )  ;
    resPhi  =  TMath::Sqrt( TMath::Power(0.00789,2) + TMath::Power(1.75/et,2) )  ;
  }

  else if (0.870 <= abseta and abseta < 0.957) {
    resEt   = et * ( TMath::Sqrt( TMath::Power(0.0654,2) + TMath::Power(1.1/TMath::Sqrt(et),2) + TMath::Power(1.09e-07/et,2) ) )  ;
    resEta  =  TMath::Sqrt( TMath::Power(0.00807,2) + TMath::Power(1.7/et,2) )  ;
    resPhi  =  TMath::Sqrt( TMath::Power(0.00802,2) + TMath::Power(1.76/et,2) )  ;
  }

  else if (0.957 <= abseta and abseta < 1.044) {
    resEt   = et * ( TMath::Sqrt( TMath::Power(0.0669,2) + TMath::Power(1.11/TMath::Sqrt(et),2) + TMath::Power(1.87e-06/et,2) ) )  ;
    resEta  =  TMath::Sqrt( TMath::Power(0.00843,2) + TMath::Power(1.72/et,2) )  ;
    resPhi  =  TMath::Sqrt( TMath::Power(0.0078,2) + TMath::Power(1.79/et,2) )  ;
  }

  else if (1.044 <= abseta and abseta < 1.131) {
    resEt   = et * ( TMath::Sqrt( TMath::Power(0.0643,2) + TMath::Power(1.15/TMath::Sqrt(et),2) + TMath::Power(2.76e-05/et,2) ) )  ;
    resEta  =  TMath::Sqrt( TMath::Power(0.00886,2) + TMath::Power(1.74/et,2) )  ;
    resPhi  =  TMath::Sqrt( TMath::Power(0.00806,2) + TMath::Power(1.82/et,2) )  ;
  }

  else if (1.131 <= abseta and abseta < 1.218) {
    resEt   = et * ( TMath::Sqrt( TMath::Power(0.0645,2) + TMath::Power(1.16/TMath::Sqrt(et),2) + TMath::Power(1.04e-06/et,2) ) )  ;
    resEta  =  TMath::Sqrt( TMath::Power(0.0101,2) + TMath::Power(1.76/et,2) )  ;
    resPhi  =  TMath::Sqrt( TMath::Power(0.00784,2) + TMath::Power(1.86/et,2) )  ;
  }

  else if (1.218 <= abseta and abseta < 1.305) {
    resEt   = et * ( TMath::Sqrt( TMath::Power(0.0637,2) + TMath::Power(1.19/TMath::Sqrt(et),2) + TMath::Power(1.08e-07/et,2) ) )  ;
    resEta  =  TMath::Sqrt( TMath::Power(0.0127,2) + TMath::Power(1.78/et,2) )  ;
    resPhi  =  TMath::Sqrt( TMath::Power(0.00885,2) + TMath::Power(1.9/et,2) )  ;
  }

  else if (1.305 <= abseta and abseta < 1.392) {
    resEt   = et * ( TMath::Sqrt( TMath::Power(0.0695,2) + TMath::Power(1.21/TMath::Sqrt(et),2) + TMath::Power(5.75e-06/et,2) ) )  ;
    resEta  =  TMath::Sqrt( TMath::Power(0.0161,2) + TMath::Power(1.73/et,2) )  ;
    resPhi  =  TMath::Sqrt( TMath::Power(0.0108,2) + TMath::Power(1.93/et,2) )  ;
  }

  else if (1.392 <= abseta and abseta < 1.479) {
    resEt   = et * ( TMath::Sqrt( TMath::Power(0.0748,2) + TMath::Power(1.2/TMath::Sqrt(et),2) + TMath::Power(5.15e-08/et,2) ) )  ;
    resEta  =  TMath::Sqrt( TMath::Power(0.0122,2) + TMath::Power(1.77/et,2) )  ;
    resPhi  =  TMath::Sqrt( TMath::Power(0.0112,2) + TMath::Power(2/et,2) )  ;
  }

  else if (1.479 <= abseta and abseta < 1.566) {
    resEt   = et * ( TMath::Sqrt( TMath::Power(0.0624,2) + TMath::Power(1.23/TMath::Sqrt(et),2) + TMath::Power(2.28e-05/et,2) ) )  ;
    resEta  =  TMath::Sqrt( TMath::Power(0.0123,2) + TMath::Power(1.79/et,2) )  ;
    resPhi  =  TMath::Sqrt( TMath::Power(0.0102,2) + TMath::Power(2.02/et,2) )  ;
  }

  else if (1.566 <= abseta and abseta < 1.653) {
    resEt   = et * ( TMath::Sqrt( TMath::Power(0.0283,2) + TMath::Power(1.25/TMath::Sqrt(et),2) + TMath::Power(4.79e-07/et,2) ) )  ;
    resEta  =  TMath::Sqrt( TMath::Power(0.0111,2) + TMath::Power(1.79/et,2) )  ;
    resPhi  =  TMath::Sqrt( TMath::Power(0.00857,2) + TMath::Power(2.01/et,2) )  ;
  }

  else if (1.653 <= abseta and abseta < 1.740) {
    resEt   = et * ( TMath::Sqrt( TMath::Power(0.0316,2) + TMath::Power(1.21/TMath::Sqrt(et),2) + TMath::Power(5e-05/et,2) ) )  ;
    resEta  =  TMath::Sqrt( TMath::Power(0.0106,2) + TMath::Power(1.8/et,2) )  ;
    resPhi  =  TMath::Sqrt( TMath::Power(0.00856,2) + TMath::Power(1.97/et,2) )  ;
  }

  else if (1.740 <= abseta and abseta < 1.830) {
    resEt   = et * ( TMath::Sqrt( TMath::Power(2.29e-07,2) + TMath::Power(1.2/TMath::Sqrt(et),2) + TMath::Power(1.71e-05/et,2) ) )  ;
    resEta  =  TMath::Sqrt( TMath::Power(0.0115,2) + TMath::Power(1.83/et,2) )  ;
    resPhi  =  TMath::Sqrt( TMath::Power(0.00761,2) + TMath::Power(1.95/et,2) )  ;
  }

  else if (1.830 <= abseta and abseta < 1.930) {
    resEt   = et * ( TMath::Sqrt( TMath::Power(5.18e-09,2) + TMath::Power(1.14/TMath::Sqrt(et),2) + TMath::Power(1.7/et,2) ) )  ;
    resEta  =  TMath::Sqrt( TMath::Power(0.012,2) + TMath::Power(1.88/et,2) )  ;
    resPhi  =  TMath::Sqrt( TMath::Power(0.00721,2) + TMath::Power(1.92/et,2) )  ;
  }

  else if (1.930 <= abseta and abseta < 2.043) {
    resEt   = et * ( TMath::Sqrt( TMath::Power(2.17e-07,2) + TMath::Power(1.09/TMath::Sqrt(et),2) + TMath::Power(2.08/et,2) ) )  ;
    resEta  =  TMath::Sqrt( TMath::Power(0.0131,2) + TMath::Power(1.91/et,2) )  ;
    resPhi  =  TMath::Sqrt( TMath::Power(0.00722,2) + TMath::Power(1.86/et,2) )  ;
  }

  else if (2.043 <= abseta and abseta < 2.172) {
    resEt   = et * ( TMath::Sqrt( TMath::Power(3.65e-07,2) + TMath::Power(1.09/TMath::Sqrt(et),2) + TMath::Power(1.63/et,2) ) )  ;
    resEta  =  TMath::Sqrt( TMath::Power(0.0134,2) + TMath::Power(1.92/et,2) )  ;
    resPhi  =  TMath::Sqrt( TMath::Power(0.00703,2) + TMath::Power(1.86/et,2) )  ;
  }

  else if (2.172 <= abseta and abseta < 2.322) {
    resEt   = et * ( TMath::Sqrt( TMath::Power(2.02e-07,2) + TMath::Power(1.09/TMath::Sqrt(et),2) + TMath::Power(1.68/et,2) ) )  ;
    resEta  =  TMath::Sqrt( TMath::Power(0.0132,2) + TMath::Power(1.89/et,2) )  ;
    resPhi  =  TMath::Sqrt( TMath::Power(0.00845,2) + TMath::Power(1.86/et,2) )  ;
  }

  else if (2.322 <= abseta and abseta < 2.500) {
    resEt   = et * ( TMath::Sqrt( TMath::Power(5.27e-07,2) + TMath::Power(1.12/TMath::Sqrt(et),2) + TMath::Power(1.78/et,2) ) )  ;
    resEta  =  TMath::Sqrt( TMath::Power(0.0121,2) + TMath::Power(2.28/et,2) )  ;
    resPhi  =  TMath::Sqrt( TMath::Power(0.00975,2) + TMath::Power(2/et,2) )  ;        
  }

  return true;
}

int KinFit::muonResolution(double et, double eta, double& resEt, double& resEta, double& resPhi)
{

  double abseta = fabs(eta) ;
  

  if ( 0.000 <= abseta and abseta < 0.100 ) {
    resEt   = et * (0.00517 + 0.000143 * et) ;
    resEta  = TMath::Sqrt( TMath::Power(0.000433,2) + TMath::Power(0.000161/TMath::Sqrt(et),2) + TMath::Power(0.00334/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(7.21e-05,2) + TMath::Power(7e-05/TMath::Sqrt(et),2) + TMath::Power(0.00296/et,2) ) ; 
  }

  else if ( 0.100 <= abseta and abseta < 0.200 ) {
    resEt   = et * (0.00524 + 0.000143 * et); 
    resEta  = TMath::Sqrt( TMath::Power(0.000381,2) + TMath::Power(0.000473/TMath::Sqrt(et),2) + TMath::Power(0.00259/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(6.79e-05,2) + TMath::Power(0.000245/TMath::Sqrt(et),2) + TMath::Power(0.00274/et,2) ) ; 
  }

  else if ( 0.200 <= abseta and abseta < 0.300 ) {
    resEt   = et * (0.00585 + 0.000138 * et); 
    resEta  = TMath::Sqrt( TMath::Power(0.000337,2) + TMath::Power(0.000381/TMath::Sqrt(et),2) + TMath::Power(0.0023/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(7.08e-05,2) + TMath::Power(6.75e-05/TMath::Sqrt(et),2) + TMath::Power(0.00307/et,2) ) ; 
  }

  else if ( 0.300 <= abseta and abseta < 0.400 ) {
    resEt   = et * (0.0065 + 0.000133 * et); 
    resEta  = TMath::Sqrt( TMath::Power(0.000308,2) + TMath::Power(0.000166/TMath::Sqrt(et),2) + TMath::Power(0.00249/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(6.59e-05,2) + TMath::Power(0.000301/TMath::Sqrt(et),2) + TMath::Power(0.00281/et,2) ) ; 
  }

  else if ( 0.400 <= abseta and abseta < 0.500 ) {
    resEt   = et * (0.0071 + 0.000129 * et); 
    resEta  = TMath::Sqrt( TMath::Power(0.000289,2) + TMath::Power(5.37e-09/TMath::Sqrt(et),2) + TMath::Power(0.00243/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(6.27e-05,2) + TMath::Power(0.000359/TMath::Sqrt(et),2) + TMath::Power(0.00278/et,2) ) ; 
  }

  else if ( 0.500 <= abseta and abseta < 0.600 ) {
    resEt   = et * (0.00721 + 0.00013 * et); 
    resEta  = TMath::Sqrt( TMath::Power(0.000279,2) + TMath::Power(0.000272/TMath::Sqrt(et),2) + TMath::Power(0.0026/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(6.46e-05,2) + TMath::Power(0.00036/TMath::Sqrt(et),2) + TMath::Power(0.00285/et,2) ) ; 
  }

  else if ( 0.600 <= abseta and abseta < 0.700 ) {
    resEt   = et * (0.00757 + 0.000129 * et); 
    resEta  = TMath::Sqrt( TMath::Power(0.000282,2) + TMath::Power(3.63e-10/TMath::Sqrt(et),2) + TMath::Power(0.00288/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(6.54e-05,2) + TMath::Power(0.000348/TMath::Sqrt(et),2) + TMath::Power(0.00301/et,2) ) ; 
  }

  else if ( 0.700 <= abseta and abseta < 0.800 ) {
    resEt   = et * (0.0081 + 0.000127 * et); 
    resEta  = TMath::Sqrt( TMath::Power(0.000265,2) + TMath::Power(0.000609/TMath::Sqrt(et),2) + TMath::Power(0.00212/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(6.2e-05,2) + TMath::Power(0.000402/TMath::Sqrt(et),2) + TMath::Power(0.00304/et,2) ) ; 
  }

  else if ( 0.800 <= abseta and abseta < 0.900 ) {
    resEt   = et * (0.00916 + 0.000131 * et); 
    resEta  = TMath::Sqrt( TMath::Power(0.000241,2) + TMath::Power(0.000678/TMath::Sqrt(et),2) + TMath::Power(0.00221/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(6.26e-05,2) + TMath::Power(0.000458/TMath::Sqrt(et),2) + TMath::Power(0.0031/et,2) ) ; 
  }

  else if ( 0.900 <= abseta and abseta < 1.000 ) {
    resEt   = et * (0.0108 + 0.000151 * et); 
    resEta  = TMath::Sqrt( TMath::Power(0.000228,2) + TMath::Power(0.000612/TMath::Sqrt(et),2) + TMath::Power(0.00245/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(7.18e-05,2) + TMath::Power(0.000469/TMath::Sqrt(et),2) + TMath::Power(0.00331/et,2) ) ; 
  }

  else if ( 1.000 <= abseta and abseta < 1.100 ) {
    resEt   = et * (0.0115 + 0.000153 * et); 
    resEta  = TMath::Sqrt( TMath::Power(0.000217,2) + TMath::Power(0.000583/TMath::Sqrt(et),2) + TMath::Power(0.00307/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(6.98e-05,2) + TMath::Power(0.000507/TMath::Sqrt(et),2) + TMath::Power(0.00338/et,2) ) ; 
  }

  else if ( 1.100 <= abseta and abseta < 1.200 ) {
    resEt   = et * (0.013 + 0.000136 * et); 
    resEta  = TMath::Sqrt( TMath::Power(0.000195,2) + TMath::Power(0.000751/TMath::Sqrt(et),2) + TMath::Power(0.00282/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(6.21e-05,2) + TMath::Power(0.000584/TMath::Sqrt(et),2) + TMath::Power(0.00345/et,2) ) ; 
  }

  else if ( 1.200 <= abseta and abseta < 1.300 ) {
    resEt   = et * (0.0144 + 0.000131 * et); 
    resEta  = TMath::Sqrt( TMath::Power(0.000183,2) + TMath::Power(0.000838/TMath::Sqrt(et),2) + TMath::Power(0.00227/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(5.37e-05,2) + TMath::Power(0.000667/TMath::Sqrt(et),2) + TMath::Power(0.00352/et,2) ) ; 
  }

  else if ( 1.300 <= abseta and abseta < 1.400 ) {
    resEt   = et * (0.0149 + 0.000141 * et); 
    resEta  = TMath::Sqrt( TMath::Power(0.000196,2) + TMath::Power(0.000783/TMath::Sqrt(et),2) + TMath::Power(0.00274/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(5.37e-05,2) + TMath::Power(0.000711/TMath::Sqrt(et),2) + TMath::Power(0.00358/et,2) ) ; 
  }

  else if ( 1.400 <= abseta and abseta < 1.500 ) {
    resEt   = et * (0.014 + 0.000155 * et); 
    resEta  = TMath::Sqrt( TMath::Power(0.0002,2) + TMath::Power(0.000832/TMath::Sqrt(et),2) + TMath::Power(0.00254/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(5.98e-05,2) + TMath::Power(0.000713/TMath::Sqrt(et),2) + TMath::Power(0.00362/et,2) ) ; 
  }

  else if ( 1.500 <= abseta and abseta < 1.600 ) {
    resEt   = et * (0.0132 + 0.000169 * et); 
    resEta  = TMath::Sqrt( TMath::Power(0.000205,2) + TMath::Power(0.0007/TMath::Sqrt(et),2) + TMath::Power(0.00304/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(6.21e-05,2) + TMath::Power(0.000781/TMath::Sqrt(et),2) + TMath::Power(0.00348/et,2) ) ; 
  }

  else if ( 1.600 <= abseta and abseta < 1.700 ) {
    resEt   = et * (0.0129 + 0.0002 * et); 
    resEta  = TMath::Sqrt( TMath::Power(0.000214,2) + TMath::Power(0.000747/TMath::Sqrt(et),2) + TMath::Power(0.00319/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(6.92e-05,2) + TMath::Power(0.000865/TMath::Sqrt(et),2) + TMath::Power(0.00337/et,2) ) ; 
  }

  else if ( 1.700 <= abseta and abseta < 1.800 ) {
    resEt   = et * (0.0135 + 0.000264 * et); 
    resEta  = TMath::Sqrt( TMath::Power(0.000238,2) + TMath::Power(0.000582/TMath::Sqrt(et),2) + TMath::Power(0.00343/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(9.13e-05,2) + TMath::Power(0.000896/TMath::Sqrt(et),2) + TMath::Power(0.00348/et,2) ) ; 
  }

  else if ( 1.800 <= abseta and abseta < 1.900 ) {
    resEt   = et * (0.0144 + 0.00034 * et); 
    resEta  = TMath::Sqrt( TMath::Power(0.000263,2) + TMath::Power(0.000721/TMath::Sqrt(et),2) + TMath::Power(0.00322/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(0.000102,2) + TMath::Power(0.000994/TMath::Sqrt(et),2) + TMath::Power(0.00337/et,2) ) ; 
  }

  else if ( 1.900 <= abseta and abseta < 2.000 ) {
    resEt   = et * (0.0147 + 0.000441 * et); 
    resEta  = TMath::Sqrt( TMath::Power(0.000284,2) + TMath::Power(0.000779/TMath::Sqrt(et),2) + TMath::Power(0.0031/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(0.000123,2) + TMath::Power(0.00108/TMath::Sqrt(et),2) + TMath::Power(0.00315/et,2) ) ; 
  }

  else if ( 2.000 <= abseta and abseta < 2.100 ) {
    resEt   = et * (0.0154 + 0.000604 * et); 
    resEta  = TMath::Sqrt( TMath::Power(0.000316,2) + TMath::Power(0.000566/TMath::Sqrt(et),2) + TMath::Power(0.00384/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(0.000169,2) + TMath::Power(0.000947/TMath::Sqrt(et),2) + TMath::Power(0.00422/et,2) ) ; 
  }

  else if ( 2.100 <= abseta and abseta < 2.200 ) {
    resEt   = et * (0.0163 + 0.000764 * et); 
    resEta  = TMath::Sqrt( TMath::Power(0.000353,2) + TMath::Power(0.000749/TMath::Sqrt(et),2) + TMath::Power(0.0038/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(0.000176,2) + TMath::Power(0.00116/TMath::Sqrt(et),2) + TMath::Power(0.00423/et,2) ) ; 
  }

  else if ( 2.200 <= abseta and abseta < 2.300 ) {
    resEt   = et * (0.0173 + 0.000951 * et); 
    resEta  = TMath::Sqrt( TMath::Power(0.000412,2) + TMath::Power(0.00102/TMath::Sqrt(et),2) + TMath::Power(0.00351/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(0.000207,2) + TMath::Power(0.00115/TMath::Sqrt(et),2) + TMath::Power(0.00469/et,2) ) ; 
  }

  else if ( 2.300 <= abseta and abseta < 2.400 ) {
    resEt   = et * (0.0175 + 0.00126 * et); 
    resEta  = TMath::Sqrt( TMath::Power(0.000506,2) + TMath::Power(0.000791/TMath::Sqrt(et),2) + TMath::Power(0.0045/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(0.00027,2) + TMath::Power(0.00113/TMath::Sqrt(et),2) + TMath::Power(0.00528/et,2) ) ; 
  }

  return true;
}

int KinFit::elecResolution(double et, double eta, double& resEt, double& resEta, double& resPhi)
{

  double abseta = fabs(eta) ;


  if ( 0.000 <= abseta and abseta < 0.174 ) {
    resEt   = et * TMath::Sqrt( TMath::Power(0.00534,2) + TMath::Power(0.079/TMath::Sqrt(et),2) + TMath::Power(0.163/et,2) ) ; 
    resEta  = TMath::Sqrt( TMath::Power(0.000452,2) + TMath::Power(0.000285/TMath::Sqrt(et),2) + TMath::Power(0.00376/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(0.000101,2) + TMath::Power(0.0011/TMath::Sqrt(et),2) + TMath::Power(0.00346/et,2) ) ; 
  }

  else if ( 0.174 <= abseta and abseta < 0.261 ) {
    resEt   = et * TMath::Sqrt( TMath::Power(0.00518,2) + TMath::Power(0.0749/TMath::Sqrt(et),2) + TMath::Power(0.227/et,2) ) ; 
    resEta  = TMath::Sqrt( TMath::Power(0.00038,2) + TMath::Power(0.000571/TMath::Sqrt(et),2) + TMath::Power(0.00276/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(9.3e-05,2) + TMath::Power(0.00115/TMath::Sqrt(et),2) + TMath::Power(0.0035/et,2) ) ; 
  }

  else if ( 0.261 <= abseta and abseta < 0.348 ) {
    resEt   = et * TMath::Sqrt( TMath::Power(0.00332,2) + TMath::Power(0.0879/TMath::Sqrt(et),2) + TMath::Power(0.12/et,2) ) ; 
    resEta  = TMath::Sqrt( TMath::Power(0.000351,2) + TMath::Power(1.36e-09/TMath::Sqrt(et),2) + TMath::Power(0.00324/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(0.000103,2) + TMath::Power(0.00117/TMath::Sqrt(et),2) + TMath::Power(0.00333/et,2) ) ; 
  }

  else if ( 0.348 <= abseta and abseta < 0.435 ) {
    resEt   = et * TMath::Sqrt( TMath::Power(0.00445,2) + TMath::Power(0.0895/TMath::Sqrt(et),2) + TMath::Power(0.186/et,2) ) ; 
    resEta  = TMath::Sqrt( TMath::Power(0.000319,2) + TMath::Power(0.00061/TMath::Sqrt(et),2) + TMath::Power(0.00182/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(0.00011,2) + TMath::Power(0.00115/TMath::Sqrt(et),2) + TMath::Power(0.00365/et,2) ) ; 
  }

  else if ( 0.435 <= abseta and abseta < 0.522 ) {
    resEt   = et * TMath::Sqrt( TMath::Power(0.00453,2) + TMath::Power(0.0893/TMath::Sqrt(et),2) + TMath::Power(0.21/et,2) ) ; 
    resEta  = TMath::Sqrt( TMath::Power(0.000301,2) + TMath::Power(0.000612/TMath::Sqrt(et),2) + TMath::Power(0.00146/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(0.000105,2) + TMath::Power(0.00122/TMath::Sqrt(et),2) + TMath::Power(0.00343/et,2) ) ; 
  }

  else if ( 0.522 <= abseta and abseta < 0.609 ) {
    resEt   = et * TMath::Sqrt( TMath::Power(0.00308,2) + TMath::Power(0.0886/TMath::Sqrt(et),2) + TMath::Power(0.188/et,2) ) ; 
    resEta  = TMath::Sqrt( TMath::Power(0.000297,2) + TMath::Power(0.000791/TMath::Sqrt(et),2) + TMath::Power(2.09e-08/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(0.000102,2) + TMath::Power(0.00129/TMath::Sqrt(et),2) + TMath::Power(0.00328/et,2) ) ; 
  }

  else if ( 0.609 <= abseta and abseta < 0.696 ) {
    resEt   = et * TMath::Sqrt( TMath::Power(0.00308,2) + TMath::Power(0.0914/TMath::Sqrt(et),2) + TMath::Power(0.182/et,2) ) ; 
    resEta  = TMath::Sqrt( TMath::Power(0.00032,2) + TMath::Power(0.000329/TMath::Sqrt(et),2) + TMath::Power(0.00325/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(0.000103,2) + TMath::Power(0.00139/TMath::Sqrt(et),2) + TMath::Power(0.00253/et,2) ) ; 
  }

  else if ( 0.696 <= abseta and abseta < 0.783 ) {
    resEt   = et * TMath::Sqrt( TMath::Power(0.00442,2) + TMath::Power(0.0914/TMath::Sqrt(et),2) + TMath::Power(0.231/et,2) ) ; 
    resEta  = TMath::Sqrt( TMath::Power(0.000309,2) + TMath::Power(0.000821/TMath::Sqrt(et),2) + TMath::Power(0.00119/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(0.000115,2) + TMath::Power(0.00139/TMath::Sqrt(et),2) + TMath::Power(0.00293/et,2) ) ; 
  }

  else if ( 0.783 <= abseta and abseta < 0.870 ) {
    resEt   = et * TMath::Sqrt( TMath::Power(0.00455,2) + TMath::Power(0.0949/TMath::Sqrt(et),2) + TMath::Power(0.335/et,2) ) ; 
    resEta  = TMath::Sqrt( TMath::Power(0.000293,2) + TMath::Power(0.000767/TMath::Sqrt(et),2) + TMath::Power(0.00211/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(0.000121,2) + TMath::Power(0.00158/TMath::Sqrt(et),2) + TMath::Power(0.00151/et,2) ) ; 
  }

  else if ( 0.870 <= abseta and abseta < 0.957 ) {
    resEt   = et * TMath::Sqrt( TMath::Power(0.00181,2) + TMath::Power(0.102/TMath::Sqrt(et),2) + TMath::Power(0.333/et,2) ) ; 
    resEta  = TMath::Sqrt( TMath::Power(0.000275,2) + TMath::Power(0.000765/TMath::Sqrt(et),2) + TMath::Power(0.00227/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(0.000128,2) + TMath::Power(0.00169/TMath::Sqrt(et),2) + TMath::Power(1.93e-08/et,2) ) ; 
  }

  else if ( 0.957 <= abseta and abseta < 1.044 ) {
    resEt   = et * TMath::Sqrt( TMath::Power(0.000764,2) + TMath::Power(0.108/TMath::Sqrt(et),2) + TMath::Power(0.42/et,2) ) ; 
    resEta  = TMath::Sqrt( TMath::Power(0.000274,2) + TMath::Power(0.000622/TMath::Sqrt(et),2) + TMath::Power(0.00299/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(0.000145,2) + TMath::Power(0.00179/TMath::Sqrt(et),2) + TMath::Power(1.69e-08/et,2) ) ; 
  }

  else if ( 1.044 <= abseta and abseta < 1.131 ) {
    resEt   = et * TMath::Sqrt( TMath::Power(0.00114,2) + TMath::Power(0.128/TMath::Sqrt(et),2) + TMath::Power(0.55/et,2) ) ; 
    resEta  = TMath::Sqrt( TMath::Power(0.000269,2) + TMath::Power(0.000929/TMath::Sqrt(et),2) + TMath::Power(0.00183/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(0.000185,2) + TMath::Power(0.00182/TMath::Sqrt(et),2) + TMath::Power(2.99e-09/et,2) ) ; 
  }

  else if ( 1.131 <= abseta and abseta < 1.218 ) {
    resEt   = et * TMath::Sqrt( TMath::Power(4.14e-09,2) + TMath::Power(0.155/TMath::Sqrt(et),2) + TMath::Power(0.674/et,2) ) ; 
    resEta  = TMath::Sqrt( TMath::Power(0.000268,2) + TMath::Power(0.000876/TMath::Sqrt(et),2) + TMath::Power(0.00234/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(0.000194,2) + TMath::Power(0.002/TMath::Sqrt(et),2) + TMath::Power(2.39e-08/et,2) ) ; 
  }

  else if ( 1.218 <= abseta and abseta < 1.305 ) {
    resEt   = et * TMath::Sqrt( TMath::Power(8.03e-09,2) + TMath::Power(0.144/TMath::Sqrt(et),2) + TMath::Power(0.8/et,2) ) ; 
    resEta  = TMath::Sqrt( TMath::Power(0.000258,2) + TMath::Power(0.000782/TMath::Sqrt(et),2) + TMath::Power(0.00246/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(0.000226,2) + TMath::Power(0.00206/TMath::Sqrt(et),2) + TMath::Power(5.88e-08/et,2) ) ; 
  }

  else if ( 1.305 <= abseta and abseta < 1.392 ) {
    resEt   = et * TMath::Sqrt( TMath::Power(0.00842,2) + TMath::Power(0.118/TMath::Sqrt(et),2) + TMath::Power(0.951/et,2) ) ; 
    resEta  = TMath::Sqrt( TMath::Power(0.000269,2) + TMath::Power(0.000817/TMath::Sqrt(et),2) + TMath::Power(0.00278/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(0.000247,2) + TMath::Power(0.00225/TMath::Sqrt(et),2) + TMath::Power(1.47e-09/et,2) ) ; 
  }

  else if ( 1.392 <= abseta and abseta < 1.479 ) {
    resEt   = et * TMath::Sqrt( TMath::Power(0.00684,2) + TMath::Power(0.144/TMath::Sqrt(et),2) + TMath::Power(0.892/et,2) ) ; 
    resEta  = TMath::Sqrt( TMath::Power(0.000267,2) + TMath::Power(0.000734/TMath::Sqrt(et),2) + TMath::Power(0.00327/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(0.000234,2) + TMath::Power(0.00233/TMath::Sqrt(et),2) + TMath::Power(4.92e-09/et,2) ) ; 
  }

  else if ( 1.479 <= abseta and abseta < 1.653 ) {
    resEt   = et * TMath::Sqrt( TMath::Power(0.0245,2) + TMath::Power(0.196/TMath::Sqrt(et),2) + TMath::Power(0.555/et,2) ) ; 
    resEta  = TMath::Sqrt( TMath::Power(0.000268,2) + TMath::Power(0.000757/TMath::Sqrt(et),2) + TMath::Power(0.00295/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(0.00025,2) + TMath::Power(0.00268/TMath::Sqrt(et),2) + TMath::Power(7.5e-09/et,2) ) ; 
  }

  else if ( 1.653 <= abseta and abseta < 1.740 ) {
    resEt   = et * TMath::Sqrt( TMath::Power(0.0174,2) + TMath::Power(0.127/TMath::Sqrt(et),2) + TMath::Power(0.894/et,2) ) ; 
    resEta  = TMath::Sqrt( TMath::Power(0.000274,2) + TMath::Power(1.77e-09/TMath::Sqrt(et),2) + TMath::Power(0.00435/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(0.000284,2) + TMath::Power(0.00275/TMath::Sqrt(et),2) + TMath::Power(6.56e-09/et,2) ) ; 
  }

  else if ( 1.740 <= abseta and abseta < 1.830 ) {
    resEt   = et * TMath::Sqrt( TMath::Power(0.0144,2) + TMath::Power(0.133/TMath::Sqrt(et),2) + TMath::Power(0.708/et,2) ) ; 
    resEta  = TMath::Sqrt( TMath::Power(0.000274,2) + TMath::Power(0.00101/TMath::Sqrt(et),2) + TMath::Power(0.000982/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(0.000356,2) + TMath::Power(0.00279/TMath::Sqrt(et),2) + TMath::Power(0.00261/et,2) ) ; 
  }

  else if ( 1.830 <= abseta and abseta < 1.930 ) {
    resEt   = et * TMath::Sqrt( TMath::Power(0.0149,2) + TMath::Power(0.126/TMath::Sqrt(et),2) + TMath::Power(0.596/et,2) ) ; 
    resEta  = TMath::Sqrt( TMath::Power(0.000299,2) + TMath::Power(0.000686/TMath::Sqrt(et),2) + TMath::Power(0.00341/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(0.000347,2) + TMath::Power(0.00298/TMath::Sqrt(et),2) + TMath::Power(1.02e-08/et,2) ) ; 
  }

  else if ( 1.930 <= abseta and abseta < 2.043 ) {
    resEt   = et * TMath::Sqrt( TMath::Power(0.0143,2) + TMath::Power(0.12/TMath::Sqrt(et),2) + TMath::Power(0.504/et,2) ) ; 
    resEta  = TMath::Sqrt( TMath::Power(0.000329,2) + TMath::Power(3.05e-10/TMath::Sqrt(et),2) + TMath::Power(0.00439/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(0.000302,2) + TMath::Power(0.00322/TMath::Sqrt(et),2) + TMath::Power(5.22e-08/et,2) ) ; 
  }

  else if ( 2.043 <= abseta and abseta < 2.172 ) {
    resEt   = et * TMath::Sqrt( TMath::Power(0.0162,2) + TMath::Power(0.0965/TMath::Sqrt(et),2) + TMath::Power(0.483/et,2) ) ; 
    resEta  = TMath::Sqrt( TMath::Power(0.00037,2) + TMath::Power(1.32e-08/TMath::Sqrt(et),2) + TMath::Power(0.00447/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(0.000287,2) + TMath::Power(0.00349/TMath::Sqrt(et),2) + TMath::Power(3e-11/et,2) ) ; 
  }

  else if ( 2.172 <= abseta and abseta < 2.322 ) {
    resEt   = et * TMath::Sqrt( TMath::Power(0.0122,2) + TMath::Power(0.13/TMath::Sqrt(et),2) + TMath::Power(0.207/et,2) ) ; 
    resEta  = TMath::Sqrt( TMath::Power(0.000442,2) + TMath::Power(4.03e-10/TMath::Sqrt(et),2) + TMath::Power(0.00544/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(0.000214,2) + TMath::Power(0.00436/TMath::Sqrt(et),2) + TMath::Power(2.98e-09/et,2) ) ; 
  }

  else if ( 2.322 <= abseta and abseta < 2.500 ) {
    resEt   = et * TMath::Sqrt( TMath::Power(0.0145,2) + TMath::Power(0.127/TMath::Sqrt(et),2) + TMath::Power(0.0782/et,2) ) ; 
    resEta  = TMath::Sqrt( TMath::Power(0.000577,2) + TMath::Power(0.000768/TMath::Sqrt(et),2) + TMath::Power(0.00331/et,2) ) ; 
    resPhi  = TMath::Sqrt( TMath::Power(8.02e-05,2) + TMath::Power(0.00525/TMath::Sqrt(et),2) + TMath::Power(0.00581/et,2) ) ; 
  }


  return true;
}


int KinFit::metResolution(double et, double& resEt, double& resEta, double& resPhi)
{
  
  //summer 2011
  /* resEt   = et * TMath::Sqrt( TMath::Power(0.0351,2) + TMath::Power(0/TMath::Sqrt(et),2) + TMath::Power(20.288/et,2) ) ; */
  /* resEta  = TMath::Sqrt( TMath::Power(0,2) + TMath::Power(0/TMath::Sqrt(et),2) + TMath::Power(0/et,2) ) ; */
  /* resPhi  = TMath::Sqrt( TMath::Power(0,2) + TMath::Power(1.1664/TMath::Sqrt(et),2) + TMath::Power(3.579/et,2)) ; */

  //fall 2011
  resEt   = et * TMath::Sqrt( TMath::Power(0.0337,2) + TMath::Power(0.888/TMath::Sqrt(et),2) + TMath::Power(19.6/et,2) ) ;
  resEta  = TMath::Sqrt( TMath::Power(0,2) + TMath::Power(0/TMath::Sqrt(et),2) + TMath::Power(0/et,2) ) ;
  resPhi  = TMath::Sqrt( TMath::Power(1.28e-08,2) + TMath::Power(1.45/TMath::Sqrt(et),2) + TMath::Power(1.03/et,2) );
  
  return true;
}

int KinFit::JetEnergyResolution(double eta, double& JERbase, double& JERdown, double& JERup)
{

  double abseta = fabs(eta) ;

  if ( 0.0 <= abseta and abseta < 0.5 ) {
    JERbase = 1.109 ; JERdown = 1.044 ; JERup = 1.174 ;
  } else if ( 0.5 <= abseta and abseta < 0.8 ) {
    JERbase = 1.138 ; JERdown = 1.072 ; JERup = 1.204 ;
  } else if ( 0.8 <= abseta and abseta < 1.1 ) {
    JERbase = 1.114 ; JERdown = 1.050 ; JERup = 1.178 ;
  } else if ( 1.1 <= abseta and abseta < 1.3 ) {
    JERbase = 1.123 ; JERdown = 1.022 ; JERup = 1.224 ;
  } else if ( 1.3 <= abseta and abseta < 1.7 ) {
    JERbase = 1.084 ; JERdown = 0.985 ; JERup = 1.183 ;
  } else if ( 1.7 <= abseta and abseta < 1.9 ) {
    JERbase = 1.082 ; JERdown = 0.973 ; JERup = 1.191 ;
  } else if ( 1.9 <= abseta and abseta < 2.1 ) {
    JERbase = 1.140 ; JERdown = 1.020 ; JERup = 1.260 ;
  } else if ( 2.1 <= abseta and abseta < 2.3 ) {
    JERbase = 1.067 ; JERdown = 0.953 ; JERup = 1.181 ;
  } else if ( 2.3 <= abseta and abseta < 2.5 ) {
    JERbase = 1.177 ; JERdown = 0.967 ; JERup = 1.387 ;
  } else if ( 2.5 <= abseta and abseta < 2.8 ) {
    JERbase = 1.364 ; JERdown = 1.203 ; JERup = 1.525 ;
  } else if ( 2.8 <= abseta and abseta < 3.0 ) {
    JERbase = 1.857 ; JERdown = 1.654 ; JERup = 2.060 ;
  } else if ( 3.0 <= abseta and abseta < 3.2 ) {
    JERbase = 1.328 ; JERdown = 1.203 ; JERup = 1.453 ;
  }else {
    JERbase = 1.160 ; JERdown = 1.013 ; JERup = 1.307 ;
  }


  return true;
}

void KinFit::LoadObjReso()
{
  
  fResoIn = TFile::Open(Form("%s/KinFitResolution.root",inputResoPath.c_str()));
  hBJetETRes = (TH2F *)fResoIn->Get("hBJetETRes");
  hBJetEtaRes = (TH2F *)fResoIn->Get("hBJetEtaRes");
  hBJetPhiRes = (TH2F *)fResoIn->Get("hBJetPhiRes");

  hLJetETRes = (TH2F *)fResoIn->Get("hLJetETRes");
  hLJetEtaRes = (TH2F *)fResoIn->Get("hLJetEtaRes");
  hLJetPhiRes = (TH2F *)fResoIn->Get("hLJetPhiRes");

  hMuETRes = (TH2F *)fResoIn->Get("hMuETRes");
  hMuEtaRes = (TH2F *)fResoIn->Get("hMuEtaRes");
  hMuPhiRes = (TH2F *)fResoIn->Get("hMuPhiRes");

  hEleETRes = (TH2F *)fResoIn->Get("hEleETRes");
  hEleEtaRes = (TH2F *)fResoIn->Get("hEleEtaRes");
  hElePhiRes = (TH2F *)fResoIn->Get("hElePhiRes");

  hMETETRes = (TH1F *)fResoIn->Get("hMETETRes");
  hMETPhiRes = (TH1F *)fResoIn->Get("hMETPhiRes");

  hBJetPtDiff = (TH2F *)fResoIn->Get("hBJetPtDiff");
  hBJetEtaDiff = (TH2F *)fResoIn->Get("hBJetEtaDiff");
  hBJetPhiDiff = (TH2F *)fResoIn->Get("hBJetPhiDiff");
  hBJetEnDiff = (TH2F *)fResoIn->Get("hBJetEnDiff");

  hLJetPtDiff = (TH2F *)fResoIn->Get("hLJetPtDiff");
  hLJetEtaDiff = (TH2F *)fResoIn->Get("hLJetEtaDiff");
  hLJetPhiDiff = (TH2F *)fResoIn->Get("hLJetPhiDiff");
  hLJetEnDiff = (TH2F *)fResoIn->Get("hLJetEnDiff");

  hMuPtDiff = (TH2F *)fResoIn->Get("hMuPtDiff");
  hMuEtaDiff = (TH2F *)fResoIn->Get("hMuEtaDiff");
  hMuPhiDiff = (TH2F *)fResoIn->Get("hMuPhiDiff");
  hMuEnDiff = (TH2F *)fResoIn->Get("hMuEnDiff");

  hElePtDiff = (TH2F *)fResoIn->Get("hElePtDiff");
  hEleEtaDiff = (TH2F *)fResoIn->Get("hEleEtaDiff");
  hElePhiDiff = (TH2F *)fResoIn->Get("hElePhiDiff");
  hEleEnDiff = (TH2F *)fResoIn->Get("hEleEnDiff");
  
  hMETPtDiff = (TH1F *)fResoIn->Get("hMETPtDiff");
  hMETPhiDiff = (TH1F *)fResoIn->Get("hMETPhiDiff");
}

void KinFit::UnloadObjReso(){
  
  if(fResoIn){
    fResoIn->Close();
    delete fResoIn;
  }
  
}

double KinFit::GetReso2D(TH2F *h2, double eta, double pt){

  TAxis *axisX = h2->GetXaxis();
  TAxis *axisY = h2->GetYaxis();

  //Get min/max of x and y ranges
  double minX = axisX->GetBinCenter(1);
  double maxX = axisX->GetBinCenter(h2->GetNbinsX());
  
  double minY = axisY->GetBinCenter(1);
  double maxY = axisY->GetBinCenter(h2->GetNbinsY());
  
  //Get the bin numbers for a given eta, pt
  //If pt or eta value is out of hist range, choose the first/last bin
  Int_t binX = -1;
  if(eta <= minX)
    binX = 1;
  else if(eta >= maxX)
    binX = h2->GetNbinsX();
  else
    binX = axisX->FindBin(eta);

  Int_t binY = -1;
  if(pt <= minY)
    binY = 1;
  else if(pt >= maxY)
    binY = h2->GetNbinsY();
  else
    binY = axisY->FindBin(pt);

  //Get the scale factor and error for that bin
  double reso = h2->GetBinContent(binX, binY);
  double resoErr = h2->GetBinError(binX, binY);
  double retVal = gRandom->Gaus(reso, resoErr);

  return retVal;
}

double KinFit::GetReso1D(TH1F *h1, double et){

  TAxis *axisX = h1->GetXaxis();

  //Get min/max of x ranges
  double minX = axisX->GetBinCenter(1);
  double maxX = axisX->GetBinCenter(h1->GetNbinsX());
  
  //Get the bin numbers for a given et
  //If et value is out of hist range, choose the first/last bin
  Int_t binX = -1;
  if(et <= minX)
    binX = 1;
  else if(et >= maxX)
    binX = h1->GetNbinsX();
  else
    binX = axisX->FindBin(et);

  //Get the scale factor and error for that bin
  double reso = h1->GetBinContent(binX);
  double resoErr = h1->GetBinError(binX);
  double retVal = gRandom->Gaus(reso, resoErr);

  return retVal;
}

int KinFit::udscExtResolution(double et, double eta, double& resEt, double& resEta, double& resPhi)
{
  resEt	 = GetReso2D(hLJetETRes, eta, et);
  resEta = GetReso2D(hLJetEtaRes, eta, et);
  resPhi = GetReso2D(hLJetPhiRes, eta, et);
  return true;
}

int KinFit::bjetExtResolution(double et, double eta, double& resEt, double& resEta, double& resPhi)
{
  resEt	 = GetReso2D(hBJetETRes, eta, et);
  resEta = GetReso2D(hBJetEtaRes, eta, et);
  resPhi = GetReso2D(hBJetPhiRes, eta, et);  
  return true;
}

int KinFit::muonExtResolution(double et, double eta, double& resEt, double& resEta, double& resPhi)
{
  resEt	 = GetReso2D(hMuETRes, eta, et);
  resEta = GetReso2D(hMuEtaRes, eta, et);
  resPhi = GetReso2D(hMuPhiRes, eta, et);

  return true;
}

int KinFit::elecExtResolution(double et, double eta, double& resEt, double& resEta, double& resPhi)
{
  resEt	 = GetReso2D(hEleETRes, eta, et);
  resEta = GetReso2D(hEleEtaRes, eta, et);
  resPhi = GetReso2D(hElePhiRes, eta, et);
  
  return true;
}

int KinFit::metExtResolution(double et, double& resEt, double& resEta, double& resPhi)
{
  resEt	 = GetReso1D(hMETETRes, et);
  resEta = 0.0;
  resPhi = GetReso1D(hMETPhiRes, et);
  
  return true;
}

bool KinFit::Fit(){
  
  bool				goodCombo = false, goodCombo_tlep = false, goodCombo_thad = false;
  TLorentzVector		neutrino, bjlep, bjhad, cjhad, sjhad;
  TMatrixD			ml(3,3), mn(3,3), mbl(3,3), mbh(3,3), mc(3,3), ms(3,3);
  double			resEt, resEta, resPhi;
  double			JERbase, JERdown, JERup;

  vector<pair<unsigned int, TLorentzVector>>	ljetlist;
  vector<pair<unsigned int, TLorentzVector>>	bjetlist;

  TLorentzVector		METVector;
  double			reslepEta, reslepPhi, resneuEta, resneuPhi, resbjlepEta, resbjlepPhi, resbjhadEta, resbjhadPhi, rescjhadEta, rescjhadPhi, ressjhadEta, ressjhadPhi ; 
  unsigned int			max_nu	  = 2;

  double ptOffSet, enOffSet;
  double modpt ;
  
  METVector.SetPtEtaPhiM(_nu_pt, 0., _nu_phi, 0.);
  _nu_px = METVector.Px();
  _nu_py = METVector.Py();
  
  bjetlist.clear();
  ljetlist.clear();

  int ib = 0, il = 0;
  for (unsigned int i = 0 ; i < jets.size() ; i++){
    if (btag[i] > btagThresh){ 
      bjetlist.push_back(make_pair(i,jets.at(i)));
      ib++;
    }
    //else{
    ljetlist.push_back(make_pair(i,jets.at(i)));
    il++;
      //}
  }
  
  if(bjetlist.size() < 2 or ljetlist.size() < 4){
    
    bjetlist.clear();
    ljetlist.clear();
    
    return goodCombo;
  }
  
  std::sort ( ljetlist.begin(), ljetlist.end() , PtDescending() ) ;
  std::sort ( bjetlist.begin(), bjetlist.end() , PtDescending() ) ;
  
  
  int loop = 0;

  for (auto bj1 : bjetlist){
    for (auto bj2 : bjetlist){
      if(bj1.first == bj2.first) continue;
      for (auto lj1 : ljetlist){	
	if(lj1.first == bj1.first || lj1.first == bj2.first) continue;
	for (auto lj2 : ljetlist){
	  //if(lj1.first == lj2.first || lj1.second.Pt() < lj2.second.Pt()) continue;
	  if(lj1.first == lj2.first || lj2.first == bj1.first || lj2.first == bj2.first || lj1.second.Pt() < lj2.second.Pt()) continue;
	  
  	  max_nu = 1;
  	  for(unsigned int inu_root = 0 ; inu_root < max_nu ; inu_root++){
  	    //float nuz = (inu_root==0) ? _nu_pz : _nu_pz_other ;
	    
  	    //neutrino.SetXYZM(_nu_px, _nu_py, nuz, 0.0);
  	    neutrino.SetXYZM(_nu_px, _nu_py, 0.0, 0.0);
	    
  	    bjlep = bj1.second;
  	    bjhad = bj2.second;
  	    cjhad = lj1.second;
  	    sjhad = lj2.second;

  	    //bjlepbtag = btag.at(list2jet[ib1]);// bjhadbtag, cjhadbtag, sjhadbtag;

  	    /* cout<<"loop " << loop++ << endl; */
	    /* Info("KinFit::Fit","bjlep : (pt,eta,phi) : (%lf,%lf,%lf), jetres : %lf", bjlep.Pt(), bjlep.Eta(), bjlep.Phi(), jetsRes.at(bj1.first)); */
	    /* Info("KinFit::Fit","bjhad : (pt,eta,phi) : (%lf,%lf,%lf), jetres : %lf", bjhad.Pt(), bjhad.Eta(), bjhad.Phi(), jetsRes.at(bj2.first)); */
	    /* Info("KinFit::Fit","cjhad : (pt,eta,phi) : (%lf,%lf,%lf), jetres : %lf", cjhad.Pt(), cjhad.Eta(), cjhad.Phi(), jetsRes.at(lj1.first)); */
	    /* Info("KinFit::Fit","sjhad : (pt,eta,phi) : (%lf,%lf,%lf), jetres : %lf", sjhad.Pt(), sjhad.Eta(), sjhad.Phi(), jetsRes.at(lj2.first)); */
  	    /* neutrino.Print(); */
  	    /* lepton.Print(); */
  	    /* //cout <<"_nu_pz : " << _nu_pz << " _nu_pz_other : " << _nu_pz_other << endl; */
	    
  	    ml.Zero() ;  mn.Zero() ;  mbl.Zero() ;  mbh.Zero() ;  mc.Zero() ;  ms.Zero();
	      
  	    /* // This is following covariance matrix setup is using CMS NOTE AN 2005/005. */
  	    /* ml(0,0) = ErrEt (lepton.Et(), lepton.Eta()); // et */
  	    /* ml(1,1) = ErrEta(lepton.Et(), lepton.Eta()); // eta */
  	    /* ml(2,2) = ErrPhi(lepton.Et(), lepton.Eta()); // phi */
	      
  	    /* mn(0,0) = ErrEt (neutrino.Et(), neutrino.Eta()); // et */
  	    /* mn(1,1) = ErrEta(neutrino.Et(), neutrino.Eta()); // eta */
  	    /* mn(2,2) = ErrPhi(neutrino.Et(), neutrino.Eta()); // phi */
	      
  	    /* mbl(0,0) = ErrEt (bjlep.Et(), bjlep.Eta()); // et */
  	    /* mbl(1,1) = ErrEta(bjlep.Et(), bjlep.Eta()); // eta */
  	    /* mbl(2,2) = ErrPhi(bjlep.Et(), bjlep.Eta()); // phi */
	      
  	    /* mbh(0,0) = ErrEt (bjhad.Et(), bjhad.Eta()); // et */
  	    /* mbh(1,1) = ErrEta(bjhad.Et(), bjhad.Eta()); // eta */
  	    /* mbh(2,2) = ErrPhi(bjhad.Et(), bjhad.Eta()); // phi */
	    
  	    /* mc(0,0) = ErrEt (cjhad.Et(), cjhad.Eta()); // et */
  	    /* mc(1,1) = ErrEta(cjhad.Et(), cjhad.Eta()); // eta */
  	    /* mc(2,2) = ErrPhi(cjhad.Et(), cjhad.Eta()); // phi */
	      
  	    /* ms(0,0) = ErrEt (sjhad.Et(), sjhad.Eta()); // et */
  	    /* ms(1,1) = ErrEta(sjhad.Et(), sjhad.Eta()); // eta */
  	    /* ms(2,2) = ErrPhi(sjhad.Et(), sjhad.Eta()); // phi */
	    
	    /* reslepEta   = TMath::Sqrt(ml(1,1)) ; */
            /* reslepPhi   = TMath::Sqrt(ml(2,2)) ; */
	    
            /* resneuEta   = TMath::Sqrt(mn(1,1)) ; */
            /* resneuPhi   = TMath::Sqrt(mn(2,2)) ; */

            /* resbjlepEta = TMath::Sqrt(mbl(1,1)) ; */
            /* resbjlepPhi = TMath::Sqrt(mbl(2,2)) ; */

            /* resbjhadEta = TMath::Sqrt(mbh(1,1)) ; */
            /* resbjhadPhi = TMath::Sqrt(mbh(2,2)) ; */
	    
            /* rescjhadEta = TMath::Sqrt(mc(1,1)) ; */
            /* rescjhadPhi = TMath::Sqrt(mc(2,2)) ; */

            /* ressjhadEta = TMath::Sqrt(ms(1,1)) ; */
            /* ressjhadPhi = TMath::Sqrt(ms(2,2)) ; */
	    
  	    // This is following covariance matrix setup is using TopQuarkAnalysis/TopKinFitter
  	    if (leptonType != kElectron and leptonType != kMuon) continue;
	    
  	    if(leptonType == kMuon){
	      
	      if(useExtReso){
		muonExtResolution(lepton.Et(), lepton.Eta(), resEt, resEta, resPhi);
		/* ptOffSet = GetReso2D(hMuPtDiff, lepton.Eta(), lepton.Et()); */
		/* modpt = ((lepton.Pt()-ptOffSet)>0.0) ? (lepton.Pt()-ptOffSet) : 0.0; */
		/* lepton.SetPtEtaPhiM(modpt, lepton.Eta(), lepton.Phi(), lepton.M()); */
	      }else
		muonResolution(lepton.Et(), lepton.Eta(), resEt, resEta, resPhi);
	      
	    }
  	    if(leptonType == kElectron){
	     
	      if(useExtReso){
		elecExtResolution(lepton.Et(), lepton.Eta(), resEt, resEta, resPhi);		
		/* ptOffSet = GetReso2D(hElePtDiff, lepton.Eta(), lepton.Et()); */
		/* modpt = ((lepton.Pt()-ptOffSet)>0.0) ? (lepton.Pt()-ptOffSet) : 0.0; */
		/* lepton.SetPtEtaPhiM(modpt, lepton.Eta(), lepton.Phi(), lepton.M()); */
	      }else
		elecResolution(lepton.Et(), lepton.Eta(), resEt, resEta, resPhi);
	      
	    }	    
  	    ml(0,0)	= TMath::Power(resEt, 2);	// et
  	    ml(1,1)	= TMath::Power(resEta, 2);	// eta
  	    ml(2,2)	= TMath::Power(resPhi, 2);	// phi
	    
  	    reslepEta	= resEta ;
  	    reslepPhi	= resPhi ;
	    
	    if(useExtReso){
	      metExtResolution(neutrino.Et(), resEt, resEta, resPhi);
	      ptOffSet = GetReso1D(hMETPtDiff, neutrino.Et());
	      modpt = ((neutrino.Pt()-ptOffSet)>0.0) ? (neutrino.Pt()-ptOffSet) : 0.0;
	      neutrino.SetPtEtaPhiM(modpt, 0.0, neutrino.Phi(), 0.0);
	    }else
	      metResolution(neutrino.Et(), resEt, resEta, resPhi);

  	    //resEta	= 1.e-7; // This is to avoid the matrix inversion problem: such as panic printout below
  	    resEta	= 9999.; // This is from miniAOD
  	    //Error in <TDecompLU::InvertLU>: matrix is singular, 1 diag elements < tolerance of 2.2204e-16
  	    mn(0,0)	= TMath::Power(resEt, 2); // et
  	    mn(1,1)	= TMath::Power(resEta, 2); // eta
  	    mn(2,2)	= TMath::Power(resPhi, 2); // eta
  	    /* cout <<"_nu Et : " << neutrino.Et()  */
  	    /* 	 << " _nu E : " << neutrino.E()  */
  	    /* 	 << " _nu Pt : " << neutrino.Pt()  */
  	    /* 	 << " _nu |P| : " << neutrino.Vect().Mag()  */
  	    /* 	 << endl; */
	    
  	    /* mn(0,0)	= 9999; // et */
  	    /* mn(1,1)	= 9999; // eta */
  	    /* mn(2,2)	= TMath::Power(0.54, 2); // phi */
  	    /* cout<<"Before fit====="<<endl; */
  	    /* mn.Print(); */
  	    /* cout<<"Before fit====="<<endl; */
	    
  	    resneuEta	= resEta ;
  	    resneuPhi	= resPhi ;
	    
	    if(useExtReso){
	      bjetExtResolution(bjlep.Et(), bjlep.Eta(), resEt, resEta, resPhi);
	      ptOffSet = GetReso2D(hBJetPtDiff, bjlep.Eta(), bjlep.Et());
	      modpt = ((bjlep.Pt()-ptOffSet)>0.0) ? (bjlep.Pt()-ptOffSet) : 0.0;
	      //Info("KinFit::Fit", "Before TFinFitter::Fit Bjlep Pt %lf, offset : %lf, modpt : %lf",bjlep.Pt(),ptOffSet,modpt);
	      bjlep.SetPtEtaPhiM(modpt, bjlep.Eta(), bjlep.Phi(), bjlep.M());
	    }else
	      bjetResolution(bjlep.Et(), bjlep.Eta(), resEt, resEta, resPhi);
  	    //JetEnergyResolution(bjlep.Eta(), JERbase, JERdown, JERup);
	    //mbl(0,0)   *= TMath::Power(JERbase, 2);

  	    mbl(0,0)	= TMath::Power(resEt, 2); // et
	    if(!useExtReso)
	      mbl(0,0)   *= TMath::Power(jetsRes.at(bj1.first), 2);
  	    mbl(1,1)	= TMath::Power(resEta, 2); // eta
  	    mbl(2,2)	= TMath::Power(resPhi, 2); // eta
	    
  	    resbjlepEta = resEta ;
  	    resbjlepPhi = resPhi ;
	    
	    if(useExtReso){
	      bjetExtResolution(bjhad.Et(), bjhad.Eta(), resEt, resEta, resPhi);
	      ptOffSet = GetReso2D(hBJetPtDiff, bjhad.Eta(), bjhad.Et());
	      modpt = ((bjhad.Pt()-ptOffSet)>0.0) ? (bjhad.Pt()-ptOffSet) : 0.0;
	      bjhad.SetPtEtaPhiM(modpt, bjhad.Eta(), bjhad.Phi(), bjhad.M());
	    }else
	      bjetResolution(bjhad.Et(), bjhad.Eta(), resEt, resEta, resPhi);
  	    //JetEnergyResolution(bjhad.Eta(), JERbase, JERdown, JERup);
	    //mbh(0,0)   *= TMath::Power(JERbase, 2);
  	    mbh(0,0)	= TMath::Power(resEt, 2); // et
	    if(!useExtReso)
	      mbh(0,0)   *= TMath::Power(jetsRes.at(bj2.first), 2);
  	    mbh(1,1)	= TMath::Power(resEta, 2); // eta
  	    mbh(2,2)	= TMath::Power(resPhi, 2); // eta
	    
  	    resbjhadEta = resEta ;
  	    resbjhadPhi = resPhi ;
	    
	    if(useExtReso){
	      udscExtResolution(cjhad.Et(), cjhad.Eta(), resEt, resEta, resPhi);
	      ptOffSet = GetReso2D(hBJetPtDiff, cjhad.Eta(), cjhad.Et());
	      modpt = ((cjhad.Pt()-ptOffSet)>0.0) ? (cjhad.Pt()-ptOffSet) : 0.0;
	      cjhad.SetPtEtaPhiM(modpt, cjhad.Eta(), cjhad.Phi(), cjhad.M());
	    }else
	      udscResolution(cjhad.Et(), cjhad.Eta(), resEt, resEta, resPhi);
  	    //JetEnergyResolution(cjhad.Eta(), JERbase, JERdown, JERup);
	    //mc(0,0)    *= TMath::Power(JERbase, 2);
  	    mc(0,0)	= TMath::Power(resEt, 2); // et
	    if(!useExtReso)
	      mc(0,0)   *= TMath::Power(jetsRes.at(lj1.first), 2);
  	    mc(1,1)	= TMath::Power(resEta, 2); // eta
  	    mc(2,2)	= TMath::Power(resPhi, 2); // eta

  	    rescjhadEta = resEta ;
  	    rescjhadPhi = resPhi ;
	      
	    if(useExtReso){
	      udscExtResolution(sjhad.Et(), sjhad.Eta(), resEt, resEta, resPhi);
	      ptOffSet = GetReso2D(hBJetPtDiff, sjhad.Eta(), sjhad.Et());
	      modpt = ((sjhad.Pt()-ptOffSet)>0.0) ? (sjhad.Pt()-ptOffSet) : 0.0;
	      sjhad.SetPtEtaPhiM(modpt, sjhad.Eta(), sjhad.Phi(), sjhad.M());
	    }else
	      udscResolution(sjhad.Et(), sjhad.Eta(), resEt, resEta, resPhi);
  	    //JetEnergyResolution(sjhad.Eta(), JERbase, JERdown, JERup);
	    //ms(0,0)    *= TMath::Power(JERbase, 2);
  	    ms(0,0)	= TMath::Power(resEt, 2); // et
	    if(!useExtReso)
	      ms(0,0)   *= TMath::Power(jetsRes.at(lj2.first), 2);
  	    ms(1,1)	= TMath::Power(resEta, 2); // eta
  	    ms(2,2)	= TMath::Power(resPhi, 2); // eta
	    
  	    ressjhadEta = resEta ;
  	    ressjhadPhi = resPhi ;

  	    // For collider setup (Et, eta. phi) setup is suggested in KinFit original document
  	    TFitParticleEtEtaPhi *lep = new TFitParticleEtEtaPhi( "lep", "lep", &lepton,   &ml );
  	    TFitParticleEtEtaPhi *neu = new TFitParticleEtEtaPhi( "neu", "neu", &neutrino, &mn );
  	    /* TFitParticleEScaledMomDev *lep = new TFitParticleEScaledMomDev( "lep", "lep", &lepton,   &ml ); */
  	    /* TFitParticleEScaledMomDev *neu = new TFitParticleEScaledMomDev( "neu", "neu", &neutrino, &mn ); */
  	    TFitParticleEtEtaPhi *bl  = new TFitParticleEtEtaPhi( "bl",  "bl",  &bjlep,    &mbl );
  	    TFitParticleEtEtaPhi *bh  = new TFitParticleEtEtaPhi( "bh",  "bh",  &bjhad,    &mbh );
  	    TFitParticleEtEtaPhi *cj  = new TFitParticleEtEtaPhi( "cj",  "cj",  &cjhad,    &mc );
  	    TFitParticleEtEtaPhi *sj  = new TFitParticleEtEtaPhi( "sj",  "sj",  &sjhad,    &ms );
	    
  	    //leptoniccally decayed top constrain
  	    //TFitConstraintM *ltop = new TFitConstraintM( "ltop", "leptonic top", 0, 0 , mTop); // Values set from PDG 2021 mTop = 172.76
  	    TFitConstraintMGaus *ltop = new TFitConstraintMGaus( "ltop", "leptonic top", 0, 0 , mTop, 6.9); // Values set from PDG 2021 mTop = 172.76
  	    ltop->addParticles1( lep, neu, bl );

  	    //hadronically decayed top constrain
  	    //TFitConstraintM *htop = new TFitConstraintM( "htop", "hadronic top", 0, 0 , mTop); // Values set from PDG 2021 mTop = 172.76
  	    TFitConstraintMGaus *htop = new TFitConstraintMGaus( "htop", "hadronic top", 0, 0 , mTop, 6.9); // Values set from PDG 2021 mTop = 172.76
  	    htop->addParticles1( bh, cj, sj );
	    
  	    //TFitConstraintM *lW = new TFitConstraintM( "lW", "W mass", 0, 0 , 80.379); // Values set from PDG 2021 mW = 80.379
  	    TFitConstraintMGaus *lW = new TFitConstraintMGaus( "lW", "W mass", 0, 0 , 80.379, 6.4); // Values set from PDG 2021 mW = 80.379
  	    lW->addParticles1( lep, neu);
	    
  	    // TFitConstraintEp *sumPxConstr_  = new TFitConstraintEp("SumPx",        "SumPx", nullptr, TFitConstraintEp::pX, 0.);
  	    // TFitConstraintEp *sumPyConstr_  = new TFitConstraintEp("SumPy",        "SumPy", nullptr, TFitConstraintEp::pY, 0.);
  	    // TFitConstraintEp *sumPzConstr_  = new TFitConstraintEp("SumPz",        "SumPz", nullptr, TFitConstraintEp::pZ, 0.);
  	    // TFitConstraintEp *sumEConstr_   = new TFitConstraintEp("SumE",        "SumE", nullptr, TFitConstraintEp::E, mTop+mTop);

  	    // sumPxConstr_->addParticles(lep, neu, bl, bh, cj, sj);
  	    // sumPyConstr_->addParticles(lep, neu, bl, bh, cj, sj);
  	    // sumPzConstr_->addParticles(lep, neu, bl, bh, cj, sj);
  	    // sumEConstr_->addParticles(lep, neu, bl, bh, cj, sj);

  	    // sumPxConstr_->setConstraint( lepton.Px() + neutrino.Px() + bjlep.Px() + bjhad.Px() + cjhad.Px() + sjhad.Px() );
  	    // sumPyConstr_->setConstraint( lepton.Py() + neutrino.Py() + bjlep.Py() + bjhad.Py() + cjhad.Py() + sjhad.Py() );
  	    // sumPzConstr_->setConstraint( lepton.Pz() + neutrino.Pz() + bjlep.Pz() + bjhad.Pz() + cjhad.Pz() + sjhad.Pz() );
  	    // sumEConstr_->setConstraint( lepton.E() + neutrino.E() + bjlep.E() + bjhad.E() + cjhad.E() + sjhad.E() );
	    
  	    TKinFitter* fitter = new TKinFitter("fitter", "fitter");
  	    fitter->addMeasParticle( lep );
  	    fitter->addMeasParticle( neu );
  	    fitter->addMeasParticle( bl );
  	    fitter->addMeasParticle( bh );
  	    fitter->addMeasParticle( cj );
  	    fitter->addMeasParticle( sj );
  	    fitter->addConstraint( ltop );
  	    fitter->addConstraint( htop );
  	    fitter->addConstraint( lW );
  	    // fitter->addConstraint(sumPxConstr_);
  	    // fitter->addConstraint(sumPyConstr_);
  	    // fitter->addConstraint(sumPzConstr_);
  	    // fitter->addConstraint(sumEConstr_);
	    
  	    TKinFitter* fitter_tlep = new TKinFitter("fitter_tlep", "fitter_tlep");
  	    fitter_tlep->addMeasParticle( lep );   fitter_tlep->addMeasParticle( neu );
  	    fitter_tlep->addMeasParticle( bl );	   fitter_tlep->addConstraint( ltop );
  	    fitter_tlep->addConstraint( lW );
	    
  	    TKinFitter* fitter_thad = new TKinFitter("fitter_thad", "fitter_thad");
  	    fitter_thad->addMeasParticle( bh );	   fitter_thad->addMeasParticle( cj );
            fitter_thad->addMeasParticle( sj );	   fitter_thad->addConstraint( htop );

	    
  	    // Tested with 2016 analysis
  	    fitter->setMaxNbIter( 500 );
  	    fitter->setMaxDeltaS( 5e-05 );
  	    fitter->setMaxF( 0.0001 );
  	    fitter->setVerbosity(0);

  	    fitter_tlep->setMaxNbIter( 500 );   fitter_tlep->setMaxDeltaS( 5e-05 );
  	    fitter_tlep->setMaxF( 0.0001 );	fitter_tlep->setVerbosity(0);
	    
  	    fitter_thad->setMaxNbIter( 500 );   fitter_thad->setMaxDeltaS( 5e-05 );
  	    fitter_thad->setMaxF( 0.0001 );	fitter_thad->setVerbosity(0);
  	    //print(fitter);
  	    fitter->fit();     fitter_tlep->fit();       fitter_thad->fit();
  	    //print(fitter);
	    
  	    /* cout<<"====== After fit"<<endl; */
  	    /* mn.Print(); */
  	    /* cout<<"====== After fit"<<endl; */
  	    /* cout<<endl; */

  	    /* if(fitter->getStatus()==0 and fitter->getS() < Chi2){ */
  	    /*   Chi2	 = fitter->getS() ; */
  	    /*   NDF	 = fitter->getNDF();  */
  	    /*   Nb_Iter	 = fitter->getNbIter(); */
  	    /*   blep_id	 = bjetlist.at(ib1) ;  */
  	    /*   bhad_id	 = bjetlist.at(ib2) ;  */
  	    /*   chad_id	 = ij1 ; */
  	    /*   shad_id	 = ij2 ; */
  	    /*   leptonUM	 = lepton ; */
  	    /*   neutrinoUM = neutrino ; */
  	    /*   bjlepUM	 = bjlep ; */
  	    /*   bjhadUM	 = bjhad ; */
  	    /*   cjhadUM	 = cjhad ; */
  	    /*   sjhadUM	 = sjhad ; */
  	    /*   leptonAF	 = *(fitter->get4Vec(0)); */
  	    /*   neutrinoAF = *(fitter->get4Vec(1)); */
  	    /*   bjlepAF	 = *(fitter->get4Vec(2)); */
  	    /*   bjhadAF	 = *(fitter->get4Vec(3)); */
  	    /*   cjhadAF	 = *(fitter->get4Vec(4)); */
  	    /*   sjhadAF	 = *(fitter->get4Vec(5)); */
  	    /*   goodCombo	 = true; */
  	    /* } */

  	    if(fitter->getStatus()==0 and fitter_tlep->getStatus()==0 and fitter_thad->getStatus()==0){
	      
  	      Chi2.push_back( fitter->getS() );
  	      NDF.push_back( fitter->getNDF() );
  	      Nb_Iter.push_back( fitter->getNbIter() );
  	      blep_id.push_back( bj1.first );
  	      bhad_id.push_back( bj2.first );
  	      chad_id.push_back( lj1.first );
  	      shad_id.push_back( lj2.first );
  	      leptonUM.push_back( lepton );
  	      neutrinoUM.push_back( neutrino );
  	      bjlepUM.push_back( bjlep );
  	      bjhadUM.push_back( bjhad );
  	      cjhadUM.push_back( cjhad );
  	      sjhadUM.push_back( sjhad );
  	      leptonAF.push_back( *(fitter->get4Vec(0)) );
  	      neutrinoAF.push_back( *(fitter->get4Vec(1)) );
  	      bjlepAF.push_back( *(fitter->get4Vec(2)) );
  	      bjhadAF.push_back( *(fitter->get4Vec(3)) );
  	      cjhadAF.push_back( *(fitter->get4Vec(4)) );
  	      sjhadAF.push_back( *(fitter->get4Vec(5)) );
  	      ReslepEta.push_back(reslepEta);
  	      ReslepPhi.push_back(reslepPhi);
  	      ResneuEta.push_back(resneuEta);
  	      ResneuPhi.push_back(resneuPhi);
  	      ResbjlepEta.push_back(resbjlepEta);
  	      ResbjlepPhi.push_back(resbjlepPhi);
  	      ResbjhadEta.push_back(resbjhadEta);
  	      ResbjhadPhi.push_back(resbjhadPhi);
  	      RescjhadEta.push_back(rescjhadEta);
  	      RescjhadPhi.push_back(rescjhadPhi);
  	      RessjhadEta.push_back(ressjhadEta);
  	      RessjhadPhi.push_back(ressjhadPhi);
  	      goodCombo = true;
  	      nCombinations++ ;
	      
  	      Chi2_tlep.push_back( fitter_tlep->getS() );
  	      leptonAF_tlep.push_back( *(fitter_tlep->get4Vec(0)) );
  	      neutrinoAF_tlep.push_back( *(fitter_tlep->get4Vec(1)) );
  	      bjlepAF_tlep.push_back( *(fitter_tlep->get4Vec(2)) );
  	      goodCombo_tlep = true;
  	      nCombinations_tlep++ ;
	      
  	      Chi2_thad.push_back( fitter_thad->getS() );
  	      bjhadAF_thad.push_back( *(fitter_thad->get4Vec(0)) );
  	      cjhadAF_thad.push_back( *(fitter_thad->get4Vec(1)) );
  	      sjhadAF_thad.push_back( *(fitter_thad->get4Vec(2)) );
  	      goodCombo_thad = true;
  	      nCombinations_thad++;
	      
  	    }
	    
  	    /* if(fitter_tlep->getStatus()==0){ */
  	    /*   Chi2_tlep.push_back( fitter_tlep->getS() ); */
  	    /*   leptonAF_tlep.push_back( *(fitter_tlep->get4Vec(0)) ); */
  	    /*   neutrinoAF_tlep.push_back( *(fitter_tlep->get4Vec(1)) ); */
  	    /*   bjlepAF_tlep.push_back( *(fitter_tlep->get4Vec(2)) ); */
  	    /*   goodCombo_tlep = true; */
  	    /*   nCombinations_tlep++ ; */
  	    /* } */

  	    /* if(fitter_thad->getStatus()==0){ */
  	    /*   Chi2_thad.push_back( fitter_thad->getS() ); */
  	    /*   bjhadAF_thad.push_back( *(fitter_thad->get4Vec(0)) ); */
  	    /*   cjhadAF_thad.push_back( *(fitter_thad->get4Vec(1)) ); */
  	    /*   sjhadAF_thad.push_back( *(fitter_thad->get4Vec(2)) ); */
  	    /*   goodCombo_thad = true; */
  	    /*   nCombinations_thad++; */
  	    /* } */
	    
  	    delete lep;
  	    delete neu;
  	    delete bl;
  	    delete bh;
  	    delete cj;
  	    delete sj;
  	    delete ltop;
  	    delete htop;
  	    delete lW;
  	    delete fitter;
	    
  	    delete fitter_tlep;	    delete fitter_thad;
	    
  	  }//inu_root
  	}//ijet 2
      }//ijet 1
    }//bjet 2
  }//bjet 1
    
  //cout<<endl<<endl;
  
  bjetlist.clear();
  ljetlist.clear();
  //list2jet.clear();
  
  /* bool combinedStatus = false; */
  /* if(goodCombo && goodCombo_tlep && goodCombo_thad) */
  /*   combinedStatus = true; */
  
  /* return combinedStatus; */
  
  return goodCombo;
  
}
