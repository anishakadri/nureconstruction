#include "Particle.h"

Particle::Particle()
{
  pdgid = 0;
  Px = 0.;
  Py = 0.;
  Pz = 0.;
  Energy = 0.;
  Id = 0;
  Trand = 0;    //random number for threshold
  //Rrand = 0;    //random number for resolution
}

Particle::Particle(int pdg, float px, float py, float pz, float energy, int id, float trand)//, float rrand)
{
    pdgid = pdg;
    Px = px;
    Py = py;
    Pz = pz;
    Energy = energy;
    Id = id;
    Trand = trand;
    //Rrand = rrand;
    
}

Particle::~Particle(){}


float Particle::GetEnergy(){
  return (Energy);
}

int Particle::GetPDG(){
  return (pdgid);
}

float Particle::GetXMom(){
  return Px;
}

float Particle::GetYMom(){
  return Py;
}

float Particle::GetZMom(){
  return Pz;
}

float Particle::GetMomMag(){
  return sqrt(pow(Px,2.0)+pow(Py,2.0)+pow(Pz,2.0));
}

int Particle::GetID(){
  return Id;
}

float Particle::GetTrand(){
  return Trand;
}

/*float Particle::GetRrand(){
  return Rrand;
  }*/
