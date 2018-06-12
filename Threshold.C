#include "TRandom3.h"

float Sigmoid(float pmag, float momThresh, float Eff){
  return Eff/(1+exp(-((5*(pmag-momThresh)))));
}
    
vector<Particle> threshold(vector<Particle> PartVec, float prot_thresh, float pi_pm_thresh, float Eff){

  vector<Particle> PartVecAbove;
  PartVecAbove.clear();
  float pmag;
  int pdg;
  for(unsigned int i=0;i < PartVec.size();i++){

    Particle Part = PartVec[i];
    pmag=Part.GetMomMag();
    pdg = Part.GetPDG();

    //float r = Part.GetTrand();
     
    float r = ((double) rand() / (RAND_MAX));

    if (abs(pdg) == 211 && r < Sigmoid(pmag,pi_pm_thresh,Eff)){
      PartVecAbove.push_back(Part);
    }
    else if (abs(pdg) == 2212 && r < Sigmoid(pmag, prot_thresh,Eff)){
      PartVecAbove.push_back(Part);
    }
    else if (abs(pdg) != 211 && abs(pdg) != 2212 && abs(pdg) != 2112 && abs(pdg) != 12 && abs(pdg) != 14 && abs(pdg) != 130 && abs(pdg) != 310 && abs(pdg) != 221 && abs(pdg) != 3122 && r < Sigmoid(pmag, 0, Eff)) {                //not detecting any neutral particles excpet pi0 as this decays into photons mostly
      PartVecAbove.push_back(Part);
    }
  }
  
  return (PartVecAbove);
} 

vector<Particle> liquidMomThresh(vector<Particle> PartVec){
	
  float prot_thresh = 0.2; //2212
  float pi_pm_thresh = 0.059; // +/-211
  float Eff = 0.90; //Efficiency
  
  return threshold(PartVec, prot_thresh, pi_pm_thresh, Eff);
  
}

vector<Particle> gasMomThresh(vector<Particle> PartVec){
	
  float prot_thresh = 0.058; //2212
  float pi_pm_thresh = 0.016; // +/-211
  float Eff = .90; //Efficiency

  return threshold(PartVec, prot_thresh, pi_pm_thresh, Eff);
}

  
