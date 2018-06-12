#include "constants.h"

float calorimetric(vector<Particle> PartVec){
	
  float En;
  float E_cal;
  bool hasLep=kFALSE;   //set to true if not charged current
	
  for(unsigned int i=0;i < PartVec.size(); i++){
    Particle Part = PartVec[i];
	
    En=Part.GetEnergy();	
    int pdg = Part.GetPDG();		
    
    if(pdg == 2212){
      E_cal += (En - mproton);
    }
    else if(pdg == 2112){
      E_cal += (En - mneutron);
    }
    else if(abs(pdg) == 4122 || abs(pdg) == 3122 || abs(pdg) == 4222 || abs(pdg) == 3222 || abs(pdg) == 4212 | abs(pdg) == 3212){
      E_cal += (En - mneutron);
    }
    else{
      if (pdg == 11 || pdg == 13) {
      hasLep = kTRUE;
      }
      E_cal += En;
    }
  }
  if (hasLep){       
    return E_cal;
    }
  else return 0;
}
