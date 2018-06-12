#pragma once

#ifndef Event_H
#define Event_H


class Event: public TObject
{
    public:
  
        int id;
        float E0; //true Energy
        float ECL; //Reconstructed Calorimetric Energy, Liquid
        float ECG; //Reconstructed Calorimetric Energy, Gas
        float EKL; //Reconstructed Kinematic Energy, Liquid
        float EKG; //Reconstructed Kinematic Energy, Gas
		int nfsp0; //True nfsp
		int nfspL; //nfsp after Liquid threshold
		int nfspG; //nfsp after Gas threshold
		int mode; //mode
		int topL; //Liq topology
		int topG; //Gas topology
        Event();  
        Event(int id, float E0, float ECL, float ECG, float EKL, float EKG, int nfsp0, int nfspL, int nfspG, int mode, int topL, int topG);
		~Event();
		int Getid();
        float GetE0(); 
        float GetECL(); 
        float GetECG(); 
        float GetEKL(); 
        float GetEKG(); 
		int Getnfsp0(); 
		int GetnfspL(); 
		int GetnfspG(); 
		int Getmode(); 
		int GettopL();
		int GettopG(); 
};

#endif
