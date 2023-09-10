#include<TH2F.h>
#include<TFile.h>

#include <iostream>


using namespace std;

class ElectronSF
{
 public:
    ElectronSF(string id_fname, string reco_fname, string trig_fname){
	TFile* idFile = TFile::Open(id_fname.c_str(),"READ");
	idHist = (TH2F*) idFile->Get("EGamma_SF2D");

	TFile* recoFile = TFile::Open(reco_fname.c_str(),"READ");
	recoHist = (TH2F*) recoFile->Get("EGamma_SF2D");

	TFile* trigFile = TFile::Open(trig_fname.c_str(),"READ");
	trigHist = (TH2F*) trigFile->Get("EGamma_SF2D");
    }

    std::vector<double> getEleSF(double pt, double eta, int systLevel, bool verbose=false);
    double getEleSF(TH2F *h2, double eta, double pt, int systLevel);
    
 private:
    TH2F* idHist;
    TH2F* recoHist;
    TH2F* trigHist;
};

double ElectronSF::getEleSF(TH2F *h2, double eta, double pt, int systLevel){

  TAxis *axisX = h2->GetXaxis();
  TAxis *axisY = h2->GetYaxis();

  //Get max of x and y range
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
  double sf = h2->GetBinContent(binX, binY);
  double err = h2->GetBinError(binX, binY);
  if (TMath::AreEqualAbs(sf,0.0,1.e-7) and TMath::AreEqualAbs(err,0.0,1.e-7))
    return 1.0;
  else
    return sf + (systLevel -1)*err;
}


std::vector<double> ElectronSF::getEleSF(double pt, double eta, int systLevel, bool verbose){


    /* int eleEtaRegion_ID = -1; */
    /* int elePtRegion_ID = -1; */

    /* int eleEtaRegion_RECO = -1; */
    /* int elePtRegion_RECO = -1; */

    /* int eleEtaRegion_TRIG = -1; */
    /* int elePtRegion_TRIG = -1; */

    /* if (eta < -2.000) { eleEtaRegion_ID = 1;} */
    /* else if (eta < -1.566) { eleEtaRegion_ID = 2;} */
    /* else if (eta < -1.444) { eleEtaRegion_ID = 3;} */
    /* else if (eta < -0.800) { eleEtaRegion_ID = 4;} */
    /* else if (eta < 0.000) { eleEtaRegion_ID = 5;} */
    /* else if (eta < 0.800) { eleEtaRegion_ID = 6;} */
    /* else if (eta < 1.444) { eleEtaRegion_ID = 7;} */
    /* else if (eta < 1.566) { eleEtaRegion_ID = 8;} */
    /* else if (eta < 2.000) { eleEtaRegion_ID = 9;} */
    /* else { eleEtaRegion_ID = 10; } */

    /* if (pt < 20.) { elePtRegion_ID = 1; } */
    /* else if (pt < 35.) { elePtRegion_ID = 2; } */
    /* else if (pt < 50.) { elePtRegion_ID = 3; } */
    /* else if (pt < 100.) { elePtRegion_ID = 4; } */
    /* else if (pt < 200.) { elePtRegion_ID = 5; } */
    /* else { elePtRegion_ID = 6; } */


    /* if (eta < -2.000) { eleEtaRegion_RECO = 1;} */
    /* else if (eta < -1.566) { eleEtaRegion_RECO = 2;} */
    /* else if (eta < -1.444) { eleEtaRegion_RECO = 3;} */
    /* else if (eta < -1.000) { eleEtaRegion_RECO = 4;} */
    /* else if (eta < -0.500) { eleEtaRegion_RECO = 5;} */
    /* else if (eta < 0.000) { eleEtaRegion_RECO = 6;} */
    /* else if (eta < 0.500) { eleEtaRegion_RECO = 7;} */
    /* else if (eta < 1.000) { eleEtaRegion_RECO = 8;} */
    /* else if (eta < 1.444) { eleEtaRegion_RECO = 9;} */
    /* else if (eta < 1.566) { eleEtaRegion_RECO= 10;} */
    /* else if (eta < 2.000) { eleEtaRegion_RECO= 11;} */
    /* else { eleEtaRegion_RECO = 12; } */

    /* if (pt < 45.) { elePtRegion_RECO = 1; } */
    /* else if (pt < 75.) { elePtRegion_RECO = 2; } */
    /* else if (pt < 100.) { elePtRegion_RECO = 3; } */
    /* else { elePtRegion_RECO = 4; } */

   
    /* if (eta < -2.000) { eleEtaRegion_TRIG = 1;} */
    /* else if (eta < -1.566) { eleEtaRegion_TRIG = 2;} */
    /* else if (eta < -1.444) { eleEtaRegion_TRIG = 3;} */
    /* else if (eta < -0.800) { eleEtaRegion_TRIG = 4;} */
    /* else if (eta < 0.000) { eleEtaRegion_TRIG = 5;} */
    /* else if (eta < 0.800) { eleEtaRegion_TRIG = 6;} */
    /* else if (eta < 1.444) { eleEtaRegion_TRIG = 7;} */
    /* else if (eta < 1.566) { eleEtaRegion_TRIG = 8;} */
    /* else if (eta < 2.000) { eleEtaRegion_TRIG = 9;} */
    /* else { eleEtaRegion_TRIG = 10; } */

    /* if (pt < 50.) { elePtRegion_TRIG = 1; } */
    /* else if (pt < 70.) { elePtRegion_TRIG = 2; } */
    /* else if (pt < 100.) { elePtRegion_TRIG = 3; } */
    /* else if (pt < 150.) { elePtRegion_TRIG = 4; } */
    /* else if (pt < 200.) { elePtRegion_TRIG = 5; } */
    /* else { elePtRegion_TRIG = 6; } */


    /* double id_SF_value = idHist->GetBinContent(eleEtaRegion_ID,elePtRegion_ID); */
    /* double id_SF_error = idHist->GetBinError(eleEtaRegion_ID,elePtRegion_ID); */

    /* double id_SF = id_SF_value + (systLevel-1)*id_SF_error; */

    /* double reco_SF_value = recoHist->GetBinContent(eleEtaRegion_RECO,elePtRegion_RECO); */
    /* double reco_SF_error = recoHist->GetBinError(eleEtaRegion_RECO,elePtRegion_RECO); */

    /* double reco_SF = reco_SF_value + (systLevel-1)*reco_SF_error; */

    /* double trig_SF_value = trigHist->GetBinContent(eleEtaRegion_TRIG,elePtRegion_TRIG); */
    /* double trig_SF_error = trigHist->GetBinError(eleEtaRegion_TRIG,elePtRegion_TRIG); */

    /* double trig_SF = trig_SF_value + (systLevel-1)*trig_SF_error; */

    /* std::vector<double> eleEffSF {id_SF*reco_SF*trig_SF, id_SF, reco_SF, trig_SF}; */

    /* if (verbose) {  */
    /* 	cout << "Electron Scale Factors: " << endl; */
    /* 	cout << "    ID   = " << id_SF << endl; */
    /* 	cout << "    Reco = " << reco_SF << endl; */
    /* 	cout << "    Trig = " << trig_SF << endl; */
    /* 	cout << "    TOTAL= " << eleEffSF.at(0) << endl; */
    /* } */

  double idSF    = 1.0;
  double recoSF   = 1.0;
  double trigSF  = 1.0;

  idSF    = getEleSF(idHist, eta, pt, systLevel);//eta: -2.4, 2.4
  recoSF   = getEleSF(recoHist, eta, pt, systLevel);
  trigSF  = getEleSF(trigHist, eta, pt, systLevel);//eta: 0, 2.4

  vector<double> eleEffSF {idSF*recoSF*trigSF, idSF, recoSF, trigSF};
  if (verbose){
    cout<<"----------------------------"<<endl;
    cout << "Muon Scale Factors: " << endl;
    cout<<  "    pt   = " <<pt<<endl;
    cout<<  "    eta   = " <<eta<<endl;
    cout << "    ID   = " << idSF << endl;
    cout << "    Reco  = " << recoSF << endl;
    cout << "    Trig = " << trigSF << endl;
    cout << "    Total= " << idSF*recoSF*trigSF << endl;
  }

    return eleEffSF;

}

