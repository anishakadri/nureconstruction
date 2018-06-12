#include "constants.h"
#include <math.h> 

//Calorimetric

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
 //Kinematic CC0Pi

float kinematic(vector<Particle> PartVec, float coslep){

  float E_kin=0;
  float Elep=0;
  float Plep=0;
  
  for (unsigned int i=0;i<PartVec.size();i++){
    Particle Part = PartVec[i];
    int pdg = Part.GetPDG();

    if(pdg==11||pdg==13){
      Elep = Part.GetEnergy();
      Plep = Part.GetMomMag(); 
    }
  }    
  if(Elep != 0 && Plep !=0){
    E_kin = (pow(mproton,2.0)-pow(eff_mass_neutron,2.0)-pow(mmuon,2.0)+(2.0*Elep*eff_mass_neutron))/(2.0*(eff_mass_neutron-Elep+(Plep*coslep)));
  }
  
  return E_kin; 
}      

// Kinematic CC1Pi
float cc1pikinematic(vector<Particle> PartVec,float coslep)
{
  float E_kin = 0;
  float Epi = 0;
  float Ppi = 0;
  float Pzpi = 0;
  float Pxpi = 0;
  float Pypi = 0;
  float cospi = 0;        //not -1, cos(theta) of the pion
  float Elep = 0;
  float Plep = 0;
  float Pzlep = 0;
  float Pxlep = 0;
  float Pylep = 0;
  float PlPpidotprod = 0;
  
  for (unsigned int i=0; i<PartVec.size();i++){
    Particle Part = PartVec[i];

    int pdg = Part.GetPDG();

    if(pdg==abs(211)){
      Epi = Part.GetEnergy();
      Ppi = Part.GetMomMag();
      Pxpi = Part.GetXMom();
      Pypi = Part.GetYMom();
      Pzpi = Part.GetZMom();
    }
    else if (pdg==11||pdg==13){
      Elep = Part.GetEnergy();
      Plep = Part.GetMomMag();
      Pxlep = Part.GetXMom();
      Pylep = Part.GetYMom();
      Pzlep = Part.GetZMom();
    }
  }
    
  PlPpidotprod = (Epi*Elep) + (Pxpi*Pxlep) + (Pypi*Pylep) + (Pzpi*Pylep); 

  cospi = Ppi/Pzpi;

  if (Elep != 0 && Plep != 0 && PlPpidotprod != 0){
    E_kin = (pow(mmuon,2.0)+pow(mpionpm,2.0)-(2*eff_mass_neutron*(Elep+Epi))+(2*PlPpidotprod))/(2*(Elep+Epi-(Plep*coslep)-(Ppi*cospi)-eff_mass_neutron));
  }
  return E_kin;
}
