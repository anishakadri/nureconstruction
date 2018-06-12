//ROOT6 Libraries

#include "TRandom.h"
#include "TObject.h"
#include "TROOT.h"
#include "TChain.h"
#include "TFile.h"
#include "TLorentzVector.h"
#include "TVector2.h"
#include "TH2.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TRandom3.h"
#include "TAxis.h"
#include "TGaxis.h"
#include "TStyle.h"

// C Libraries

#include <random>
#include <cmath>
#include <iostream>
#include <string>
#include <ctime>

//Analysis Libraries

#include "Particle.C"
#include "Event.C"
#include "Detector.C"

//Reconstruction

#include "reconstruct.C"

vector<Event> read(){

  TFile* file = new TFile("/home/priyanka/Documents/project/Msci-project/Eshita4.root");
  TTree* tree = (TTree*)file->Get("FlatTree_VARS");

  //Detected Events

  vector<Event> EventVec;

  //TRUE Particles

  vector<Particle> PartVec0;

  //Detected Particles

  vector<Particle> PartVecR; //After Resolution
  vector<Particle> PartVecL; //After Liquid Thres
  vector<Particle> PartVecG; //After Gas Thres

  //True Vars

  vector<float> PMom0; //true proton momentums
  vector<float> MuMom0; //true muon momentums

  //Detected Vars

  vector<float> PMom_det;
  vector<float> MuMom_det;

  //TRUTH DATA from tree

  int nfsp;                //number of final state particles
  int pdg[240];
  float px[240];
  float py[240];
  float pz[240];
  float energy[240];
  int mode;
  float Enu_t;
  float coslep;

  tree->SetBranchAddress("nfsp",&nfsp);
  tree->SetBranchAddress("pdg",&pdg);
  tree->SetBranchAddress("px",&px);
  tree->SetBranchAddress("py",&py);
  tree->SetBranchAddress("pz",&pz);
  tree->SetBranchAddress("E",&energy);
  tree->SetBranchAddress("Mode",&mode);
  tree->SetBranchAddress("Enu_true",&Enu_t);
  tree->SetBranchAddress("CosLep",&coslep);

  int part_id = 0;
  Long64_t nentries = tree->GetEntries();
  TRandom3 ranobj;

  int event_id = 0;
  for(unsigned int iEntry=0;iEntry<nentries;iEntry++){

    event_id ++;

    //acessing event i

    tree->GetEntry(iEntry);

    //empty vectors

    PartVec0.clear();
    PartVecR.clear();
    PartVecL.clear();
    PartVecG.clear();

    //acessing particle i in event i

    for (int i = 0; i < nfsp; ++i)  {
      part_id++;
      float Trand = ranobj.Rndm();
      Particle Part = Particle(pdg[i], px[i], py[i],pz[i], energy[i], part_id, Trand);
      PartVec0.push_back(Part);
    }

    PartVecR = resolution(PartVec0); //apply resolution
    PartVecL = liquidMomThresh(PartVecR); //apply Liqupart_id thresh
    PartVecG = gasMomThresh(PartVecR);  //apply gas thresh

    //vectors of proton and muon momentum

    for(int i = 0; i<PartVec0.size();i++){
      int pdgid = PartVec0[i].GetPDG();
      if (pdgid == 13) {
	MuMom0.push_back(PartVec0[i].GetMomMag());
      }

      if (pdgid == 2212) {
	PMom0.push_back(PartVec0[i].GetMomMag());
      }
    }

    for(int i = 0; i<PartVecR.size();i++){
      int pdgid = PartVecR[i].GetPDG();
      if (pdgid == 13) {
	MuMom_det.push_back(PartVecR[i].GetMomMag());
      }

      if (pdgid == 2212) {
	PMom_det.push_back(PartVecR[i].GetMomMag());
      }
    }

    //create detected event

    float ECL = calorimetric(PartVecL);
    float ECG = calorimetric(PartVecG);
    float EKL = 0.;
    float EKG = 0.;
    float E0 = Enu_t;
    int nfsp0 = nfsp;
    int nfspL = PartVecL.size();
    int nfspG = PartVecG.size();
    int topL = 2; //default = other
    int topG = 2;

    if (id_0pi(PartVecL) == 1){
      topL = 0;
      EKL = kinematic(PartVecL,coslep);
    }

    if (id_0pi(PartVecG) == 1){
      topG = 0;
      EKG = kinematic(PartVecG,coslep);
    }

    if (id_1pi(PartVecL) ==1){
      topL = 1;
      EKL = cc1pikinematic(PartVecL,coslep);
    }

    if (id_1pi(PartVecG) ==1){
      topG = 1;
      EKG = cc1pikinematic(PartVecG,coslep);
    }

    if (id_0pi(PartVecG) == 0 && id_1pi(PartVecG) == 0) {
      topG = 2;
    }

    if (id_0pi(PartVecL) == 0 && id_1pi(PartVecL) == 0) {
      topL = 2;
    }

    Event Event_foo = Event(event_id, E0, ECL, ECG, EKL, EKG, nfsp0, nfspL, nfspG, mode, topL, topG);
    EventVec.push_back(Event_foo);
  }

  //must produce muon/proton distribution from here

  return EventVec;
}

/*

int write(){

  vector<Event> Events = read();

  for(int j = 0; j<Events.size();j++){
  Event Event_foo = Events[j];

  if (Event_foo.GetEKL() != 0.){
    float EKL_diff = Event_foo.GetEKL() - Event_foo.GetE0();
    float EKL_frac = EKL_diff / Event_foo.GetE0();
  }

  if (Event_foo.GetECL() != 0.){
    float ECL_diff = Event_foo.GetECL() - Event_foo.GetE0();
    float ECL_frac = ECL_diff / Event_foo.GetE0();
  }

  if (Event_foo.GetEKG() != 0.){
    float EKG_diff = Event_foo.GetEKG() - Event_foo.GetE0();
    float EKG_frac = ECG_diff / Event_foo.GetE0();
  }

  (Event_foo.GetECG() != 0.){
    float ECG_diff = Event_foo.GetECG() - Event_foo.GetE0();
    float ECG_frac = ECG_diff / Event_foo.GetE0();
  }

  return 0;

    //Define Histograms
    //Fill Histograms
    //hfill->EKL
    //hfil->
}
*/

