#pragma once

#ifndef Particle_H
#define Particle_H

class Particle: public TObject
{
    public:
  
        int pdgid;
        float Px;
        float Py;
        float Pz;
        float Energy;
	int Id;
	float Trand;
	//float Rrand;
        Particle();  
        Particle(int pdg, float px, float py, float pz, float energy, int id, float trand);// float rrand);
	~Particle();
	float GetEnergy();
	int GetPDG();
	float GetXMom();
	float GetYMom();
	float GetZMom();
	float GetMomMag();
	int GetID();
	float GetTrand();
	//float GetRrand();
};

#endif
