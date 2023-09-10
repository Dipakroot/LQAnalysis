/**********************************************************************
 Created on : 10/04/2021
 Purpose    : Perform Kinematic Fitting 
 Author     : Indranil Das, Visiting Fellow, TIFR
 Email      : indranil.das@cern.ch | indra.ehep@gmail.com
**********************************************************************/

#include "../interface/KinFit.h"
#include <iostream>


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


bool KinFit::Fit(){

  bool			goodCombo = false;
  std::vector<unsigned int>	bjetlist;
  TLorentzVector	neutrino, bjlep, bjhad, cjhad, sjhad;
  TMatrixD		ml(3,3), mn(3,3), mbl(3,3), mbh(3,3), mc(3,3), ms(3,3);
  double		resEt, resEta, resPhi;
  double		JERbase, JERdown, JERup;

  bjetlist.clear();
  for (unsigned int i = 0 ; i < jets.size() ; i++){
    if (btag[i] > btagThresh) bjetlist.push_back(i);
  }

  Chi2    = 1.e9; // This is important to set
  for(unsigned int ib1 = 0 ; ib1 < bjetlist.size() ; ib1++){
    for(unsigned int ib2 = 0 ; ib2 < bjetlist.size() ; ib2++){
      if(bjetlist.at(ib1) == bjetlist.at(ib2)) continue;
      for(unsigned int ij1 = 0 ; ij1 < jets.size() ; ij1++){
	if(ij1 == bjetlist.at(ib1)  or  ij1 == bjetlist.at(ib2)) continue;
	for (unsigned int ij2 = 0 ; ij2 < jets.size() ; ij2++){
	  if(ij2 == bjetlist.at(ib1)  or  ij2 == bjetlist.at(ib2)  or  ij1 == ij2) continue;
	  for(unsigned int inu_root = 0 ; inu_root < 2 ; inu_root++){
	    float nuz = (inu_root==0) ? _nu_pz : _nu_pz_other ;
	      	      
	    neutrino.SetXYZM(_nu_px, _nu_py, nuz, 0.0);
	   
	    bjlep = jets.at(bjetlist.at(ib1));
	    bjhad = jets.at(bjetlist.at(ib2));
	    cjhad = jets.at(ij1);
	    sjhad = jets.at(ij2);
	    
	    ml.Zero() ;  mn.Zero() ;  mbl.Zero() ;  mbh.Zero() ;  mc.Zero() ;  ms.Zero();
	      
	    // This is following covariance matrix setup is using CMS NOTE AN 2005/005.
	    // ml(0,0) = ErrEt (lepton.Et(), lepton.Eta()); // et
	    // ml(1,1) = ErrEta(lepton.Et(), lepton.Eta()); // eta
	    // ml(2,2) = ErrPhi(lepton.Et(), lepton.Eta()); // phi
	      
	    // mn(0,0) = ErrEt (neutrino.Et(), neutrino.Eta()); // et
	    // mn(1,1) = ErrEta(neutrino.Et(), neutrino.Eta()); // eta
	    // mn(2,2) = ErrPhi(neutrino.Et(), neutrino.Eta()); // phi
	      
	    // mbl(0,0) = ErrEt (bjlep.Et(), bjlep.Eta()); // et
	    // mbl(1,1) = ErrEta(bjlep.Et(), bjlep.Eta()); // eta
	    // mbl(2,2) = ErrPhi(bjlep.Et(), bjlep.Eta()); // phi
	      
	    // mbh(0,0) = ErrEt (bjhad.Et(), bjhad.Eta()); // et
	    // mbh(1,1) = ErrEta(bjhad.Et(), bjhad.Eta()); // eta
	    // mbh(2,2) = ErrPhi(bjhad.Et(), bjhad.Eta()); // phi
	      
	    // mc(0,0) = ErrEt (cjhad.Et(), cjhad.Eta()); // et
	    // mc(1,1) = ErrEta(cjhad.Et(), cjhad.Eta()); // eta
	    // mc(2,2) = ErrPhi(cjhad.Et(), cjhad.Eta()); // phi
	      
	    // ms(0,0) = ErrEt (sjhad.Et(), sjhad.Eta()); // et
	    // ms(1,1) = ErrEta(sjhad.Et(), sjhad.Eta()); // eta
	    // ms(2,2) = ErrPhi(sjhad.Et(), sjhad.Eta()); // phi
	    
	    // This is following covariance matrix setup is using TopQuarkAnalysis/TopKinFitter
	    if (leptonType != kElectron and leptonType != kMuon) continue;
	    
	    if(leptonType == kMuon)
	      muonResolution(lepton.Et(), lepton.Eta(), resEt, resEta, resPhi);	    
	    if(leptonType == kElectron)
	      elecResolution(lepton.Et(), lepton.Eta(), resEt, resEta, resPhi);
	    
	    ml(0,0)	= TMath::Power(resEt, 2); // et
	    ml(1,1)	= TMath::Power(resEta, 2); // eta
	    ml(2,2)	= TMath::Power(resPhi, 2); // phi
	    
	    metResolution(neutrino.Et(), resEt, resEta, resPhi);
	    resEta	= 1.e-7; // This is to avoid the matrix inversion problem: such as panic printout below
	    //Error in <TDecompLU::InvertLU>: matrix is singular, 1 diag elements < tolerance of 2.2204e-16
	    mn(0,0)	= TMath::Power(resEt, 2); // et
	    mn(1,1)	= TMath::Power(resEta, 2); // eta
	    mn(2,2)	= TMath::Power(resPhi, 2); // eta
	    
	    bjetResolution(bjlep.Et(), bjlep.Eta(), resEt, resEta, resPhi);
	    JetEnergyResolution(bjlep.Eta(), JERbase, JERdown, JERup);
	    mbl(0,0)	= TMath::Power(resEt, 2); // et
	    //if(isMC){
	      //mbl(0,0)   *= TMath::Power(JERbase, 2);
	    mbl(0,0)   *= TMath::Power(jetsRes.at(bjetlist.at(ib1)), 2);
	      //}
	    mbl(1,1)	= TMath::Power(resEta, 2); // eta
	    mbl(2,2)	= TMath::Power(resPhi, 2); // eta
	    
	    bjetResolution(bjhad.Et(), bjhad.Eta(), resEt, resEta, resPhi);
	    JetEnergyResolution(bjhad.Eta(), JERbase, JERdown, JERup);
	    mbh(0,0)	= TMath::Power(resEt, 2); // et
	    //if(isMC){
	      //mbh(0,0)   *= TMath::Power(JERbase, 2);
	    mbh(0,0)   *= TMath::Power(jetsRes.at(bjetlist.at(ib2)), 2);
	      //}
	    mbh(1,1)	= TMath::Power(resEta, 2); // eta
	    mbh(2,2)	= TMath::Power(resPhi, 2); // eta	      
	      
	    udscResolution(cjhad.Et(), cjhad.Eta(), resEt, resEta, resPhi);
	    JetEnergyResolution(cjhad.Eta(), JERbase, JERdown, JERup);
	    mc(0,0)	= TMath::Power(resEt, 2); // et
	    //if(isMC){
	      //mc(0,0)    *= TMath::Power(JERbase, 2);
	    mc(0,0)    *= TMath::Power(jetsRes.at(ij1), 2);
	      //}
	    mc(1,1)	= TMath::Power(resEta, 2); // eta
	    mc(2,2)	= TMath::Power(resPhi, 2); // eta	      
	      
	    udscResolution(sjhad.Et(), sjhad.Eta(), resEt, resEta, resPhi);
	    JetEnergyResolution(sjhad.Eta(), JERbase, JERdown, JERup);
	    ms(0,0)	= TMath::Power(resEt, 2); // et
	    //if(isMC){
	      //ms(0,0)    *= TMath::Power(JERbase, 2);
	    ms(0,0)    *= TMath::Power(jetsRes.at(ij2), 2);
	      //}
	    ms(1,1)	= TMath::Power(resEta, 2); // eta
	    ms(2,2)	= TMath::Power(resPhi, 2); // eta	      
	    
	    // For collider setup (Et, eta. phi) setup is suggested in KinFit original document  
	    TFitParticleEtEtaPhi *lep = new TFitParticleEtEtaPhi( "lep", "lep", &lepton,   &ml );
	    TFitParticleEtEtaPhi *neu = new TFitParticleEtEtaPhi( "neu", "neu", &neutrino, &mn );
	    TFitParticleEtEtaPhi *bl  = new TFitParticleEtEtaPhi( "bl",  "bl",  &bjlep,    &mbl );
	    TFitParticleEtEtaPhi *bh  = new TFitParticleEtEtaPhi( "bh",  "bh",  &bjhad,    &mbh );
	    TFitParticleEtEtaPhi *cj  = new TFitParticleEtEtaPhi( "cj",  "cj",  &cjhad,    &mc );
	    TFitParticleEtEtaPhi *sj  = new TFitParticleEtEtaPhi( "sj",  "sj",  &sjhad,    &ms );
	      
	    //leptoniccally decayed top constrain
	    TFitConstraintM *ltop = new TFitConstraintM( "ltop", "leptonic top", 0, 0 , mTop); // Values set from PDG 2021
	    ltop->addParticles1( lep, neu, bl );
	    //hadronically decayed top constrain
	    TFitConstraintM *htop = new TFitConstraintM( "htop", "hadronic top", 0, 0 , mTop); // Values set from PDG 2021
	    htop->addParticles1( bh, cj, sj );
	    
	    TKinFitter* fitter = new TKinFitter("fitter", "fitter");
	    fitter->addMeasParticle( lep );
	    fitter->addMeasParticle( neu );
	    fitter->addMeasParticle( bl );
	    fitter->addMeasParticle( bh );
	    fitter->addMeasParticle( cj );
	    fitter->addMeasParticle( sj );
	    fitter->addConstraint( ltop );
	    fitter->addConstraint( htop );
	    
	    // Tested with 2016 analysis
	    fitter->setMaxNbIter( 500 );
	    fitter->setMaxDeltaS( 5e-05 );
	    //fitter->setMaxF( 0.0001 );
	    //fitter->setMaxDeltaS( 5e-03 );
	    fitter->setMaxF( 0.0001 );
	    fitter->setVerbosity(0);
	    
	    //print(fitter);
	    fitter->fit();
	    //print(fitter);
	    
	    if(fitter->getStatus()==0 and fitter->getS() < Chi2){
	      Chi2	 = fitter->getS() ;
	      NDF	 = fitter->getNDF(); 
	      Nb_Iter	 = fitter->getNbIter();
	      blep_id	 = bjetlist.at(ib1) ; 
	      bhad_id	 = bjetlist.at(ib2) ; 
	      chad_id	 = ij1 ;
	      shad_id	 = ij2 ;
	      leptonUM	 = lepton ;
	      neutrinoUM = neutrino ;
	      bjlepUM	 = bjlep ;
	      bjhadUM	 = bjhad ;
	      cjhadUM	 = cjhad ;
	      sjhadUM	 = sjhad ;
	      leptonAF	 = *(fitter->get4Vec(0));
	      neutrinoAF = *(fitter->get4Vec(1));
	      bjlepAF	 = *(fitter->get4Vec(2));
	      bjhadAF	 = *(fitter->get4Vec(3));
	      cjhadAF	 = *(fitter->get4Vec(4));
	      sjhadAF	 = *(fitter->get4Vec(5));
	      goodCombo	 = true;
	    }
	    
	    delete lep;
	    delete neu;
	    delete bl;
	    delete bh;
	    delete cj;
	    delete sj;
	    delete ltop;
	    delete htop;
	    delete fitter;
	      
	  }//inu_root
	}//ijet 2 
      }//ijet 1
    }//bjet 2
  }//bjet 1
  bjetlist.clear();

  return goodCombo;
  
}
