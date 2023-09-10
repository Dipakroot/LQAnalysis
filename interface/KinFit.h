/**********************************************************************
 Created on : 10/04/2021
 Purpose    : Perform Kinematic Fitting 
 Author     : Indranil Das, Visiting Fellow, TIFR
 Email      : indranil.das@cern.ch | indra.ehep@gmail.com
**********************************************************************/
#ifndef KinFit_h
#define KinFit_h


#include <vector>

#include "TMath.h"
#include "TLorentzVector.h"

#include "PhysicsTools/KinFitter/interface/TFitConstraintM.h"
#include "PhysicsTools/KinFitter/interface/TFitParticleEtEtaPhi.h"
#include "PhysicsTools/KinFitter/interface/TKinFitter.h"

#include "METzCalculator.h"

class KinFit{

 public:

    enum LeptonType {kElectron, kMuon, kTau};

    KinFit(){
      ClearVectors();
      _nu_px		= -9999.0;
      _nu_py		= -9999.0;
      _nu_pz		= -9999.0; 
      _nu_pz_other	= -9999.0; 
      leptonType	= kTau;
      mTop		= 172.76;
      isMC		= false;
      Chi2		= 1.e9;
      NDF		= -9999;
      Nb_Iter		= -9999;
      blep_id		= -9999; 
      bhad_id		= -9999; 
      chad_id		= -9999; 
      shad_id		= -9999;
    }
    
    // The following are the mandatory setters
    /////////////////////////////////////////////////////////////////////////////
    // For a given year
    void SetBtagThresh(double thresh_){ btagThresh		= thresh_;}
    void SetMC(bool ifmc){ isMC					= ifmc;} 
    
    // For a given event
    void ClearVectors(){
	jets.clear();
	jetsRes.clear();
	btag.clear();
	_nu_px	     = -9999.0;
	_nu_py	     = -9999.0;
	_nu_pz	     = -9999.0; 
	_nu_pz_other = -9999.0; 
	leptonType   = kTau;
	Chi2	     = 1.e9;
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
    /////////////////////////////////////////////////////////////////////////////

    // The SetTop mass an option
    /////////////////////////////////////////////////////////////////////////////
    void SetTopMass(double topmass){ mTop			= topmass;} 
    /////////////////////////////////////////////////////////////////////////////
    
    // The return of fit function is "true" if fit is converged
    /////////////////////////////////////////////////////////////////////////////
    bool Fit();
    /////////////////////////////////////////////////////////////////////////////
    
    // The following are the minimal getters
    /////////////////////////////////////////////////////////////////////////////
    TLorentzVector	GetLepton()		{ return leptonAF;}
    TLorentzVector	GetNeutrino()		{ return neutrinoAF;}
    TLorentzVector	GetBLepton()		{ return bjlepAF;}
    TLorentzVector	GetBHadron()		{ return bjhadAF;}
    TLorentzVector	GetCHadron()		{ return cjhadAF;}
    TLorentzVector	GetSHadron()		{ return sjhadAF;}
    unsigned int	GetJetID_BLep()		{ return blep_id;}
    unsigned int	GetJetID_BHad()		{ return bhad_id;}
    unsigned int	GetJetID_CHad()		{ return chad_id;}
    unsigned int	GetJetID_SHad()		{ return shad_id;}
    /////////////////////////////////////////////////////////////////////////////

    // The following are the additional getters
    /////////////////////////////////////////////////////////////////////////////
    TLorentzVector	GetLeptonUM()		{ return leptonUM;}
    TLorentzVector	GetNeutrinoUM()		{ return neutrinoUM;}
    TLorentzVector	GetBLeptonUM()		{ return bjlepUM;}
    TLorentzVector	GetBHadronUM()		{ return bjhadUM;}
    TLorentzVector	GetCHadronUM()		{ return cjhadUM;}
    TLorentzVector	GetSHadronUM()		{ return sjhadUM;}
    double		GetChi2()		{ return Chi2; }
    int			GetNDF()		{ return NDF; }
    int			GetNumberOfIter()	{ return Nb_Iter; } // Number of iterations to converge
    /////////////////////////////////////////////////////////////////////////////

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
    double			_nu_px, _nu_py, _nu_pz, _nu_pz_other; 
    TLorentzVector		lepton;
    LeptonType			leptonType;
    bool                        isMC;

    // Optional : To be set for a given event
    double                      mTop;

    // The following variables are minimal getters
    TLorentzVector		leptonAF, neutrinoAF, bjlepAF, bjhadAF, cjhadAF, sjhadAF; // Four vectors after KinFit
    unsigned int	        blep_id, bhad_id, chad_id, shad_id;
    
    // The following variables are additional getters
    double			Chi2;
    int				NDF, Nb_Iter ;
    TLorentzVector		leptonUM, neutrinoUM, bjlepUM, bjhadUM, cjhadUM, sjhadUM; // Unmodified four vectors before KinFit
    
};

#endif
