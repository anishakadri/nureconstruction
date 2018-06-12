#include "TRandom.h"
#include <ctime>
#include "TObject.h"
#include <iostream>
#include <string>
#include "TROOT.h"
#include "TChain.h"
#include "TFile.h"
#include "TLorentzVector.h"
#include "TVector2.h"
#include "TH2.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TRandom3.h"
#include <random>
#include <cmath>
#include "Particle.C"
#include "Resolution.C"
#include "Identify.C"
#include "Threshold.C"
#include "Calorimetric.C"
#include "Kinematic.C"
#include "TAxis.h"
#include "TGaxis.h"
#include "TStyle.h"

int greadenergy(){
  TFile* file = new TFile("/home/priyanka/Documents/project/Msci-project/GENIE.root");
  TTree* tree = (TTree*)file->Get("FlatTree_VARS");

  //Historgram set-up
  TH1D* hE = new TH1D("hE","True energy", 100, 0, 10);
  hE->GetXaxis()->SetTitle("Energy (Gev)");
  hE->GetYaxis()->SetTitle("Number of events");
  //hE->SetFillColor(kTeal-5);
  hE->SetLineColor(kBlack);
  
  TH1D* hCL = new TH1D("hCL"," ", 100, 0, 10);
  hCL->GetXaxis()->SetTitle("Energy (Gev)");
  hCL->GetYaxis()->SetTitle("Number of events");
  //hCL->SetFillColor(kAzure-6);
  hCL->SetLineColor(kBlack);

  TH1D* hCL_diff = new TH1D("hCL_diff"," ", 1000, -0.1, 0.2);
  hCL_diff->GetXaxis()->SetTitle("Energy (Gev)");
  hCL_diff->GetYaxis()->SetTitle("Number of events");
  //hCL_diff->SetFillColor(kAzure-6);
  hCL_diff->SetLineColor(kBlack);

  TH2D* hCL_diff_true = new TH2D("hCL_diff_true"," ",300,0,10,200,-8,5);
  hCL_diff_true->GetXaxis()->SetTitle("True Energy (GeV)");
  hCL_diff_true->GetYaxis()->SetTitle("Calorimetric reconstructed energy difference (GeV)");
  
  TH2D* hCL_diff_true_frac = new TH2D("hCL_diff_true_frac"," ",300,0,10,200,-0.4,0.2);
  hCL_diff_true_frac->GetXaxis()->SetTitle("True Energy (GeV)");
  hCL_diff_true_frac->GetYaxis()->SetTitle("Fractional calorimetric reconstructed energy difference");

  TH1D* hCL_diff_frac = new TH1D("hCL_diff_frac"," ",100,-0.6,0.6);
  hCL_diff_frac->GetXaxis()->SetTitle("(E_cal - E_true)/E_true");
  hCL_diff_frac->GetYaxis()->SetTitle("No. of events");
  //hCL_diff_frac->SetFillColor(kAzure-6);
  
  TH1D* hCG = new TH1D("hCG"," ",100,-1,10);
  hCG->GetXaxis()->SetTitle("Energy (Gev)");
  hCG->GetYaxis()->SetTitle("Number of events");
  //hCG->SetFillColor(kAzure-6);
  hCG->SetLineColor(kBlack);
  
  TH1D* hCG_diff = new TH1D("hCG_diff"," ",100,-3,2);
  hCG_diff->GetXaxis()->SetTitle("Energy (Gev)");
  hCG_diff->GetYaxis()->SetTitle("Number of events");
  //hCG_diff->SetFillColor(kAzure-6);
  hCG_diff->SetLineColor(kBlack);

  TH2D* hCG_diff_true = new TH2D("hCG_diff_true"," ",100,0,12,100,-10,0.5);
  hCG_diff_true->GetXaxis()->SetTitle("True Energy (GeV)");
  hCG_diff_true->GetYaxis()->SetTitle("Calorimetric reconstructed energy difference (GeV)");
  
  TH2D* hCG_diff_true_frac = new TH2D("hCG_diff_true_frac"," ",100,0,12,100,-1,1);
  hCG_diff_true_frac->GetXaxis()->SetTitle("True Energy (GeV)");
  hCG_diff_true_frac->GetYaxis()->SetTitle("Fractional calorimetric reconstructed energy difference");

  TH1F* hCG_diff_frac = new TH1F("hCG_diff_frac"," ",100,-0.6,0.6);
  hCG_diff_frac->GetXaxis()->SetTitle("(E_cal - E_true)/E_true");
  hCG_diff_frac->GetYaxis()->SetTitle("No. of events");

  TH1D* hKL = new TH1D("hKL"," ",100,-1,10);
  hKL->GetXaxis()->SetTitle("Energy (Gev)");
  hKL->GetYaxis()->SetTitle("Number of events");
  //hKL->SetFillColor(kAzure-6);
  hKL->SetLineColor(kBlack);

  TH1D* hKL_diff = new TH1D("hKL_diff"," ",100,-10,5);
  hKL_diff->GetXaxis()->SetTitle("Energy (Gev)");
  hKL_diff->GetYaxis()->SetTitle("Number of events");
  //hKL_diff->SetFillColor(kAzure-6);
  hKL_diff->SetLineColor(kBlack);

  TH2D* hKL_diff_true = new TH2D("hKL_diff_true"," ",300,0,10,300,-20,20);
  hKL_diff_true->GetXaxis()->SetTitle("True Energy (GeV)");
  hKL_diff_true->GetYaxis()->SetTitle("Kinematic reconstructed energy difference (GeV)");
  
  TH2D* hKL_diff_true_frac = new TH2D("hKL_diff_true_frac"," ",300,0,10,200,-30,30);
  hKL_diff_true_frac->GetXaxis()->SetTitle("True Energy (GeV)");
  hKL_diff_true_frac->GetYaxis()->SetTitle("Fractional kinematic reconstructed energy difference");
  
  TH1D* hKL_diff_frac = new TH1D("hKL_diff_frac"," ",100,-1,1);
  hKL_diff_frac->GetXaxis()->SetTitle("(E_kin - E_true)/E_true");
  hKL_diff_frac->GetYaxis()->SetTitle("No. of events");

  TH1D* hKG = new TH1D("hKG","Gas TPC - Kinematic",100,0,10);
  hKG->GetXaxis()->SetTitle("Energy (Gev)");
  hKG->GetYaxis()->SetTitle("Number of events");
  //hKG->SetFillColor(kAzure-6);
  hKG->SetLineColor(kBlack);
  
  TH1D* hKG_diff = new TH1D("hKG_diff","Gas TPC - Kinematic difference",100,-1,1);
  hKG_diff->GetXaxis()->SetTitle("Energy (Gev)");
  hKG_diff->GetYaxis()->SetTitle("Number of events");
  //hKG_diff->SetFillColor(kAzure-6);
  hKG_diff->SetLineColor(kBlack);

  TH2D* hKG_diff_true = new TH2D("hKG_diff_true","Gas TPC - Kinematic difference as function of true energy",100,0,12,100,-10,10);
  hKG_diff_true->GetXaxis()->SetTitle("True Energy (GeV)");
  hKG_diff_true->GetYaxis()->SetTitle("Kinematic reconstructed energy difference (GeV)");
  
  TH2D* hKG_diff_true_frac = new TH2D("hKG_diff_true_frac","Gas TPC - Fractional kinematic difference as function of true energy",100,0,12,100,-1,10);
  hKG_diff_true_frac->GetXaxis()->SetTitle("True Energy (GeV)");
  hKG_diff_true_frac->GetYaxis()->SetTitle("Fractional kinematic reconstructed energy difference");

  TH1D* hKG_diff_frac = new TH1D("hKG_diff_frac"," ",100,-1,1);
  hKG_diff_frac->GetXaxis()->SetTitle("(E_kin - E_true)/E_true");
  hKG_diff_frac->GetYaxis()->SetTitle("No. of events");
  
  TH2D* hCKL_diff = new TH2D("hCKL_diff","Liquid TPC - Cal - kin energy as a function of true energy",100,0,12,100,-10,10);
  hCKL_diff->GetXaxis()->SetTitle("True Energy (GeV)");
  hCKL_diff->GetYaxis()->SetTitle("E_cal - E_kin (GeV)");

  TH2D* hCKL_diff_frac = new TH2D("hCKL_diff_frac","Liquid TPC - Fractional Cal - kin energy as a function of true energy",100,0,12,100,-10,10);
  hCKL_diff_frac->GetXaxis()->SetTitle("True Energy (GeV)");
  hCKL_diff_frac->GetYaxis()->SetTitle("(E_cal - E_kin)/E_true");

  TH2D* hCKG_diff = new TH2D("hCKG_diff","Gas TPC - Cal - kin energy as a function of true energy",100,0,12,100,-10,10);
  hCKG_diff->GetXaxis()->SetTitle("True Energy (GeV)");
  hCKG_diff->GetYaxis()->SetTitle("E_cal - E_kin (GeV)");
 
  TH2D* hCKG_diff_frac = new TH2D("hCKG_diff_frac","Gas TPC - Fractional Cal - kin energy as a function of true energy",100,0,12,100,-10,10);
  hCKG_diff_frac->GetXaxis()->SetTitle("True Energy (GeV)");
  hCKG_diff_frac->GetYaxis()->SetTitle("(E_cal - E_kin)/E_true");
  
  TH3D* hL_cal_kin_diff_true_frac = new TH3D("hL_cal_kin_diff_true_frac","Liquid TPC - Fractional calorimetric and kinematic as a function of true",100,-1,0.1,100,-1,1,100,0,12);
  hL_cal_kin_diff_true_frac->GetXaxis()->SetTitle("Fractional Calorimetirc Energy");
  hL_cal_kin_diff_true_frac->GetYaxis()->SetTitle("Fractional Kinematic energy");
  hL_cal_kin_diff_true_frac->GetZaxis()->SetTitle("True (GeV)");

  TH3D* hL_cal_kin_diff_true = new TH3D("hL_cal_kin_diff_true","Liquid TPC - Calorimetric and kinematic differences as a function of true",100,-0.8,0.1,100,-1,1.5,100,0,12);
  hL_cal_kin_diff_true->GetXaxis()->SetTitle("Calorimetirc Energy difference (GeV)");
  hL_cal_kin_diff_true->GetYaxis()->SetTitle("Kinematic energy difference (GeV)");
  hL_cal_kin_diff_true->GetZaxis()->SetTitle("True (GeV)");

  TH1D* hFrac_slice_0001 = new TH1D("hFrac_Slice_0001"," ",100,-0.8,1);
  TH1D* hFrac_slice_0102 = new TH1D("hFrac_Slice_0102"," ",100,-1,1);
  TH1D* hFrac_slice_0203 = new TH1D("hFrac_Slice_0203"," ",100,-1,1);
  TH1D* hFrac_slice_0304 = new TH1D("hFrac_Slice_0304"," ",100,-0.8,1);
  TH1D* hFrac_slice_0405 = new TH1D("hFrac_Slice_0405"," ",100,-0.8,1);
  TH1D* hFrac_slice_0506 = new TH1D("hFrac_Slice_0506"," ",100,-0.8,1);
  TH1D* hFrac_slice_0607 = new TH1D("hFrac_Slice_0607"," ",100,-0.8,1);
  TH1D* hFrac_slice_0708 = new TH1D("hFrac_Slice_0708"," ",100,-0.8,1);
  TH1D* hFrac_slice_0809 = new TH1D("hFrac_Slice_0809"," ",100,-0.8,1);
  TH1D* hFrac_slice_0910 = new TH1D("hFrac_Slice_0910"," ",100,-0.8,1);
  TH1D* hFrac_slice_1011 = new TH1D("hFrac_Slice_1011"," ",100,-0.8,1);
  TH1D* hFrac_slice_1112 = new TH1D("hFrac_Slice_1112"," ",100,-0.8,1);
  TH1D* hFrac_slice_1213 = new TH1D("hFrac_Slice_1213"," ",100,-0.8,1);
  TH1D* hFrac_slice_1314 = new TH1D("hFrac_Slice_1314"," ",100,-0.8,1);
  TH1D* hFrac_slice_1415 = new TH1D("hFrac_Slice_1415"," ",100,-0.8,1);
  TH1D* hFrac_slice_1520 = new TH1D("hFrac_Slice_1520"," ",100,-0.8,1);
  TH1D* hFrac_slice_2025 = new TH1D("hFrac_Slice_2025"," ",100,-0.8,1);
  TH1D* hFrac_slice_2530 = new TH1D("hFrac_Slice_2530"," ",100,-0.8,1);
  TH1D* hFrac_slice_3035 = new TH1D("hFrac_Slice_3035"," ",100,-0.8,1);
  TH1D* hFrac_slice_3540 = new TH1D("hFrac_Slice_3540"," ",100,-0.8,1);
  TH1D* hFrac_slice_4045 = new TH1D("hFrac_Slice_4045"," ",100,-0.8,1);
  TH1D* hFrac_slice_4550 = new TH1D("hFrac_Slice_4550"," ",100,-0.8,1);
  TH1D* hFrac_slice_5055 = new TH1D("hFrac_Slice_5055"," ",100,-0.8,1);
  TH1D* hFrac_slice_5560 = new TH1D("hFrac_Slice_5560"," ",100,-0.8,1);
  TH1D* hFrac_slice_6065 = new TH1D("hFrac_Slice_6065"," ",100,-0.8,1);
  TH1D* hFrac_slice_6570 = new TH1D("hFrac_Slice_6570"," ",100,-0.8,1);
  TH1D* hFrac_slice_7075 = new TH1D("hFrac_Slice_7075"," ",100,-0.8,1);
  TH1D* hFrac_slice_7580 = new TH1D("hFrac_Slice_7580"," ",100,-0.8,1);
  TH1D* hFrac_slice_8085 = new TH1D("hFrac_Slice_8085"," ",100,-0.8,1);
  TH1D* hFrac_slice_8590 = new TH1D("hFrac_Slice_8590"," ",100,-0.8,1);
  TH1D* hFrac_slice_9095 = new TH1D("hFrac_Slice_9095"," ",100,-0.8,1);
  TH1D* hFrac_slice_95100 = new TH1D("hFrac_Slice_90100"," ",100,-0.8,1);
  TH1D* hFrac_slice_100105 = new TH1D("hFrac_Slice_100105"," ",100,-0.8,1);
  TH1D* hFrac_slice_105110 = new TH1D("hFrac_Slice_105110"," ",100,-0.8,1);
  TH1D* hFrac_slice_110115 = new TH1D("hFrac_Slice_110115"," ",100,-0.8,1);
  TH1D* hFrac_slice_115120 = new TH1D("hFrac_Slice_115120"," ",100,-0.8,1);
  
  TH2D* hcal_kin = new TH2D("hcal_kin"," ", 100,-10,0.2,100,-6,10);

  TH2D* hdiff = new TH2D("hdiff"," ",100,0,24,100,-1,1);
  hdiff->GetXaxis()->SetTitle("NFSP");
  hdiff->GetYaxis()->SetTitle("E_cal - E_true (GeV)");
  
  TH1D* hproton = new TH1D("hproton"," ",100, 0, 2);
  hproton->GetXaxis()->SetTitle("Proton momentum (GeV)");
  hproton->GetYaxis()->SetTitle("Number of protons");
  TH1D* hprotonres = new TH1D("hprotonres"," ",100,0,2);
  TH1D* hprotonliquid = new TH1D("hprotonliquid"," ",100,0,2);

  TH1D* hmuon = new TH1D("hmuon"," ", 100,0,5);
  hmuon->GetXaxis()->SetTitle("Muon momentum (GeV)");
  hmuon->GetYaxis()->SetTitle("Number of muons");
  TH1D* hmuonres = new TH1D("hmuonres"," ",100,0,5);
  TH1D* hmuonliquid = new TH1D("hmuonlqiuid"," ",100,0,5);

  TH1D* hpipm = new TH1D("hpipm"," ",100, 0, 2);
  hpipm->GetXaxis()->SetTitle("Neutral pion momentum (GeV)");
  hpipm->GetYaxis()->SetTitle("Number of neutral pions");
  TH1D* hpipmres = new TH1D("hpipmres"," ",100,0,2);
  TH1D* hpipmliquid = new TH1D("hpipmliquid"," ",100,0,2);

  TH2D* hnfspmode = new TH2D("hnfspmode"," ",100, 0, 60, 100, 0, 24);
  TH2D* hmodeediff = new TH2D("hmodeediff"," ",100, 0, 60, 100, -1,1);

  TH1D* hCR_diff_frac = new TH1D("hCR_diff_frac"," ",100,-1,1);
  
  
  TGaxis::SetMaxDigits(4);
  //gStyle->SetOptStat(0);     //Stats box

  vector<Particle> PartVecAboveLiquid;
  vector<Particle> PartVecAboveGas;
  vector<Particle> PartVec;

  //Variables from tree
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

  int id = 0;
  Long64_t nentries = tree->GetEntries();
  //int countpipm = 0;
  //int countpi0 = 0;

  int countmode1 = 0;
  int countmodepi = 0;
  int countmodeother=0;
  int countccqe = 0;
  int countcc1pi =0;
  int countother = 0;
  int countccqeright = 0;
  int countcc1piright = 0;
  int countotherright = 0;
  
  TRandom3 ranobj;
  for(unsigned int iEntry=0;iEntry<nentries;iEntry++){

    tree->GetEntry(iEntry);
    PartVec.clear();
    PartVecAboveLiquid.clear();
    PartVecAboveGas.clear();
      
    for (int i = 0; i < nfsp; ++i)  {
	
	id++;
	float Trand = ranobj.Rndm();
	Particle Part = Particle(pdg[i], px[i], py[i],pz[i], energy[i], id, Trand);
	PartVec.push_back(Part);
    }
    
    vector<Particle> PartVec1;
    //PartVec1 = PartVec;
    PartVec = resolution(PartVec);
    

    //PartVecAboveLiquid = PartVec;
    //PartVecAboveGas = PartVec;

    PartVecAboveLiquid = liquidMomThresh(PartVec);
    PartVecAboveGas = gasMomThresh(PartVec);

    

    //Preliminary plots
    /*
    for(int i = 0; i<PartVec.size();i++){
      int pdgid = PartVec[i].GetPDG();
      if (pdgid == 13) {
	hmuon->Fill(PartVec[i].GetMomMag());
      }
      if (pdgid == 2212) {
	hproton->Fill(PartVec[i].GetMomMag());
      }
      if (abs(pdgid) == 211) {
	hpipm->Fill(PartVec[i].GetMomMag());
      }
    }
    
    for(int i = 0; i<PartVec1.size();i++){
      int pdgid = PartVec1[i].GetPDG();
      if (pdgid == 13) {
	hmuongas->Fill(PartVec1[i].GetMomMag());
      }
      if (pdgid == 2212) {
	hprotongas->Fill(PartVec1[i].GetMomMag());
      }
      if (abs(pdgid) == 211) {
	hpipmgas->Fill(PartVec1[i].GetMomMag());
      }
    }
    
    for(int i = 0; i<PartVecAboveLiquid.size();i++){
      int pdgid = PartVecAboveLiquid[i].GetPDG();
      if (pdgid == 13) {
	hmuonliquid->Fill(PartVecAboveLiquid[i].GetMomMag());
      }
      if (pdgid == 2212) {
	hprotonliquid->Fill(PartVecAboveLiquid[i].GetMomMag());
      }
      if (abs(pdgid) == 211) {
	hpipmliquid->Fill(PartVecAboveLiquid[i].GetMomMag());
      }
    }
    */

    if (mode == 1) countmode1++;
    else if (mode == 11 || mode == 13) countmodepi++;
    else if (mode < 27) countmodeother++;
    
    hnfspmode->Fill(mode,nfsp);
    
    float ECL=0;
    float ECL_diff=0;
    float ECL_diff_frac=0;
    float EKL=0;
    float EKL_diff=0;
    float EKL_diff_frac=0;
    float ECKL_diff=0;
    float ECKL_diff_frac=0;
    float ECG=0;
    float ECG_diff=0;
    float ECG_diff_frac=0;
    float EKG=0;
    float EKG_diff=0;
    float EKG_diff_frac=0;
    float ECKG_diff=0;
    float ECKG_diff_frac=0;

    //TEMP
    float ECR=0;
    float ECR_diff=0;
    float ECR_diff_frac=0;


    

    /////select mode/topology - liquid

    //if (mode == 1){
    //if (mode != 11 && mode != 13 && mode != 16 && mode<27){                                                     //individual true modes
    if (mode < 27 && mode != 16 && mode != 36 && id_0pi(PartVecAboveLiquid)==1){                               //0pi from detected particles 
    //if (mode <27 && mode != 16 && mode != 36 && id_1pi(PartVecAboveLiquid) ==1){                                //1pi from detected particles
    //if (mode < 27 && mode != 16 && mode != 36 && id_0pi(PartVecAboveLiquid) == 0 && id_1pi(PartVec) == 0) {    //other
      countccqe++;
      if (mode ==1) countccqeright++;
      ECL = calorimetric(PartVecAboveLiquid);
      if (ECL != 0){
        ECL_diff = ECL-Enu_t;
	/*
	if (ECL_diff<-0.7){
	  cout<<"MODE  "<<mode<<endl;
	  for (int i = 0; i<PartVecAboveLiquid.size();i++){
	    cout<<PartVecAboveLiquid[i].GetPDG()<<endl;
	  }
	}*/
        ECL_diff_frac = ECL_diff/Enu_t;
	hCL->Fill(ECL);
	hCL_diff->Fill(ECL_diff);
	hCL_diff_true->Fill(Enu_t,ECL_diff);
	hCL_diff_true_frac->Fill(Enu_t,ECL_diff_frac);
	hCL_diff_frac->Fill(ECL_diff_frac);
	hdiff->Fill(PartVec.size(),ECL_diff);
	hmodeediff->Fill(mode,ECL_diff);

		
	//investigating ECL_diff with nfsp
	
	/*	if (nfsp == 3 && ECL_diff>0.8) {
	  cout<<"Mode: "<<mode<<"   E_true: "<<Enu_t<<"   E_cal: "<<ECL<<endl<<"Particles:"<<endl;
	  for (int i = 0; i<PartVec.size();i++){
	    Particle part = PartVec[i];
	    if (part.GetPDG() == 2212) hproton->Fill(part.GetEnergy());
	    else if (part.GetPDG() == 2112) hneutron->Fill(part.GetEnergy());
	    else if (part.GetPDG() == 111) {
	      countpi0++;
	      hpi0->Fill(part.GetEnergy());
	    }
	    else if (part.GetPDG() == abs(211)) {
	      countpipm++;
	      hpipm->Fill(part.GetEnergy());
	    }
	    cout<<"PDG: "<<part.GetPDG()<<"    Energy: "<<part.GetEnergy()<<endl;
	    //hCL_diff_true_frac->Fill(Enu_t,ECL_diff_frac);
	  }
	  }*/
	

	if (Enu_t < 0.1) hFrac_slice_0001->Fill(ECL_diff_frac);
	else if (Enu_t > 0.1 && Enu_t < 0.2) hFrac_slice_0102->Fill(ECL_diff_frac);
	else if (Enu_t > 0.2 && Enu_t < 0.3) hFrac_slice_0203->Fill(ECL_diff_frac);
	else if (Enu_t > 0.3 && Enu_t < 0.4) hFrac_slice_0304->Fill(ECL_diff_frac);
	else if (Enu_t > 0.4 && Enu_t < 0.5) hFrac_slice_0405->Fill(ECL_diff_frac);
	else if (Enu_t > 0.5 && Enu_t < 0.6) hFrac_slice_0506->Fill(ECL_diff_frac);
	else if (Enu_t > 0.6 && Enu_t < 0.7) hFrac_slice_0607->Fill(ECL_diff_frac);
	else if (Enu_t > 0.7 && Enu_t < 0.8) hFrac_slice_0708->Fill(ECL_diff_frac);
	else if (Enu_t > 0.8 && Enu_t < 0.9) hFrac_slice_0809->Fill(ECL_diff_frac);
	else if (Enu_t > 0.9 && Enu_t < 1.0) hFrac_slice_0910->Fill(ECL_diff_frac);
	else if (Enu_t > 1.0 && Enu_t < 1.1) hFrac_slice_1011->Fill(ECL_diff_frac);
	else if (Enu_t > 1.1 && Enu_t < 1.2) hFrac_slice_1112->Fill(ECL_diff_frac);
	else if (Enu_t > 1.2 && Enu_t < 1.3) hFrac_slice_1213->Fill(ECL_diff_frac);
	else if (Enu_t > 1.3 && Enu_t < 1.4) hFrac_slice_1314->Fill(ECL_diff_frac);
	else if (Enu_t > 1.4 && Enu_t < 1.5) hFrac_slice_1415->Fill(ECL_diff_frac);
	else if (Enu_t > 1.5 && Enu_t < 2.0) hFrac_slice_1520->Fill(ECL_diff_frac);
	else if (Enu_t > 2.0 && Enu_t < 2.5) hFrac_slice_2025->Fill(ECL_diff_frac);
	else if (Enu_t > 2.5 && Enu_t < 3.0) hFrac_slice_2530->Fill(ECL_diff_frac);
	else if (Enu_t > 3.0 && Enu_t < 3.5) hFrac_slice_3035->Fill(ECL_diff_frac);
	else if (Enu_t > 3.5 && Enu_t < 4.0) hFrac_slice_3540->Fill(ECL_diff_frac);
	else if (Enu_t > 4.0 && Enu_t < 4.5) hFrac_slice_4045->Fill(ECL_diff_frac);
	else if (Enu_t > 4.5 && Enu_t < 5.0) hFrac_slice_4550->Fill(ECL_diff_frac);
	else if (Enu_t > 5.0 && Enu_t < 5.5) hFrac_slice_5055->Fill(ECL_diff_frac);
	else if (Enu_t > 5.5 && Enu_t < 6.0) hFrac_slice_5560->Fill(ECL_diff_frac);
	else if (Enu_t > 6.0 && Enu_t < 6.5) hFrac_slice_6065->Fill(ECL_diff_frac);
	else if (Enu_t > 6.5 && Enu_t < 7.0) hFrac_slice_6570->Fill(ECL_diff_frac);
	else if (Enu_t > 7.0 && Enu_t < 7.5) hFrac_slice_7075->Fill(ECL_diff_frac);
	else if (Enu_t > 7.5 && Enu_t < 8.0) hFrac_slice_7580->Fill(ECL_diff_frac);
	else if (Enu_t > 8.0 && Enu_t < 8.5) hFrac_slice_8085->Fill(ECL_diff_frac);
	else if (Enu_t > 8.5 && Enu_t < 9.0) hFrac_slice_8590->Fill(ECL_diff_frac);
	else if (Enu_t > 9.0 && Enu_t < 9.5) hFrac_slice_9095->Fill(ECL_diff_frac);
	else if (Enu_t > 9.5 && Enu_t < 10.0) hFrac_slice_95100->Fill(ECL_diff_frac);
	else if (Enu_t > 10.0 && Enu_t < 10.5) hFrac_slice_100105->Fill(ECL_diff_frac);
	else if (Enu_t > 10.5 && Enu_t < 11.0) hFrac_slice_105110->Fill(ECL_diff_frac);
	else if (Enu_t > 11.0 && Enu_t < 11.5) hFrac_slice_110115->Fill(ECL_diff_frac);
	else hFrac_slice_115120->Fill(ECL_diff_frac);
      }

      //showing effects of resolution on reconstructed
      
      ECR = kinematic(PartVec1,coslep);
      if (ECR != 0){
	ECR_diff = ECR-Enu_t;
	ECR_diff_frac = ECR_diff/Enu_t;
	hCR_diff_frac->Fill(ECR_diff_frac);
      }
      
      
      EKL = kinematic(PartVecAboveLiquid,coslep);       //for when looking at 0pi modes
      //EKL = cc1pikinematic(PartVecAboveLiquid,coslep);         //for when looking at 1pi modes
      if (EKL != 0){
	EKL_diff = EKL - Enu_t;
	EKL_diff_frac = EKL_diff/Enu_t;
	hKL->Fill(EKL);
	hKL_diff->Fill(EKL_diff);
	hKL_diff_true->Fill(Enu_t,EKL_diff);
	hKL_diff_true_frac->Fill(Enu_t,EKL_diff_frac);
	hKL_diff_frac->Fill(EKL_diff_frac);
	if (ECL_diff != 0) {
          hL_cal_kin_diff_true->Fill(ECL_diff, EKL_diff, Enu_t);
          hcal_kin->Fill(ECL_diff,EKL_diff);
	}

	//hdiff->Fill(PartVec.size(),EKL_diff);

	//investigating EKL_diff with nfsp
	
	/*if (EKL_diff<-0.5) {
	  cout<<"E_true: "<<Enu_t<<"   E_kin: "<<EKL<<"   E_cal: "<<ECL<<endl<<"Particles:"<<endl;
	  for (int i = 0; i<PartVec.size();i++){
	    Particle part = PartVec[i];
	    cout<<"PDG: "<<part.GetPDG()<<"    Energy: "<<part.GetEnergy()<<endl;
	    }
	  }*/
      }
      
      if (ECL != 0 && EKL != 0){
	ECKL_diff = ECL - EKL;
	ECKL_diff_frac = ECKL_diff / Enu_t;
	hCKL_diff->Fill(Enu_t,ECKL_diff);
	hCKL_diff_frac->Fill(Enu_t,ECKL_diff_frac);
	hL_cal_kin_diff_true_frac->Fill(ECL_diff_frac,EKL_diff_frac,Enu_t);
      }
    }
    
    /////select mode/topology - gas
    //if (mode ==1){
    //if(mode==1 && mode != 16 && mode != 36){                                                               //individual true modes
    //if (mode<27 && mode != 16 && mode != 36 && id_0pi(PartVecAboveGas)==1){                                           //0pi from detected particles 
    if (mode<27 && mode != 16 && mode != 36 && id_1pi(PartVecAboveLiquid) ==1){                                          //1pi from detected particles
    //if (mode <27 && mode != 16 && mode != 36 && id_0pi(PartVecAboveGas) == 0 && id_1pi(PartVecAboveGas) == 0) {        //other

      countcc1pi++;
      if (mode == 11 || mode == 13) countcc1piright++;
    
      ECG = calorimetric(PartVecAboveGas);
      if (ECG != 0) {
	ECG_diff = ECG-Enu_t;
	ECG_diff_frac = ECG_diff/Enu_t;
	hCG->Fill(ECG,0.001);
	hCG_diff->Fill(ECG_diff);
	hCG_diff_true->Fill(Enu_t,ECG_diff);
	hCG_diff_true_frac->Fill(Enu_t,ECG_diff_frac);
	hCG_diff_frac->Fill(ECG_diff_frac);
      }
	
      EKG = kinematic(PartVecAboveGas,coslep);          //for when looking at 0pi modes
      //EKG = cc1pikinematic(PartVecAboveGas,coslep);     //for when looking at 1pi modes
      if (EKG != 0){
	EKG_diff = EKG-Enu_t;
	EKG_diff_frac = EKG_diff/Enu_t;
	hKG->Fill(EKG);
	hKG_diff->Fill(EKG_diff);
	hKG_diff_true->Fill(Enu_t,EKG_diff);
	hKG_diff_true_frac->Fill(Enu_t,EKG_diff_frac);
	hKG_diff_frac->Fill(EKG_diff_frac);
      }
      	
      if (ECG != 0 && EKG != 0){
	ECKG_diff = ECG - EKG;
	ECKG_diff_frac = ECKG_diff / Enu_t;
	hCKG_diff->Fill(Enu_t,ECKG_diff);
	hCKG_diff_frac->Fill(Enu_t,ECKG_diff_frac);
      }
      
      hE->Fill(Enu_t);
    }

    if (mode<27 && mode != 16 && id_0pi(PartVecAboveLiquid) == 0 && id_1pi(PartVecAboveLiquid)== 0){
      countother++;
      /*
      cout<<"Mode  "<<mode<<endl;
      for (int i=0; i<PartVecAboveGas.size();i++){
	Particle m = PartVecAboveGas[i];
	cout<<m.GetPDG()<<endl;
	}*/
      if (mode != 1 && mode != 11 && mode != 13) {
	countotherright++;
      }
    }
  }
  
  cout<<"Modes"<<endl<<"Mode 1   "<<countmode1<<endl<<"Mode 1pi   "<<countmodepi<<endl<<"Other modes   "<<countmodeother<<endl;
  cout<<"Identified"<<endl<<"CCQE   "<<countccqe<<endl<<"CC1pi   "<<countcc1pi<<endl<<"OTHER   "<<countother<<endl;
  cout<<"Correct"<<endl<<"mode 1 as CCQE   "<<countccqeright<<endl<<"mode 11 or 13 as cc1pi   "<<countcc1piright<<endl<<"other modes as other   "<<countotherright<<endl;
  //cout<<"PI 0:  "<<countpi0<<"   Pi pm:  "<< countpipm<<endl;

  /*
  TF1 *fit = new TF1("fit","crystalball");
  fit->SetParameters(2200,0.02,0.002,1,1);
  
  hFrac_slice_0001->Fit("fit");
  hFrac_slice_0102->Fit("fit");
  hFrac_slice_0203->Fit("fit");
  hFrac_slice_0304->Fit("fit");
  hFrac_slice_0405->Fit("fit");
  hFrac_slice_0506->Fit("fit");
  hFrac_slice_0607->Fit("fit");
  hFrac_slice_0708->Fit("fit");
  hFrac_slice_0809->Fit("fit");
  hFrac_slice_0910->Fit("fit");
  hFrac_slice_1011->Fit("fit");
  hFrac_slice_1112->Fit("fit");
  hFrac_slice_1213->Fit("fit");
  hFrac_slice_1314->Fit("fit");
  hFrac_slice_1415->Fit("fit");
  hFrac_slice_1520->Fit("fit");
  hFrac_slice_2025->Fit("fit");
  hFrac_slice_2530->Fit("fit");
  hFrac_slice_3035->Fit("fit");
  hFrac_slice_3540->Fit("fit");
  hFrac_slice_4045->Fit("fit");
  hFrac_slice_4550->Fit("fit");
  hFrac_slice_5055->Fit("fit");
  hFrac_slice_5560->Fit("fit");
  hFrac_slice_6065->Fit("fit");
  hFrac_slice_6570->Fit("fit");
  hFrac_slice_7075->Fit("fit");
  hFrac_slice_7580->Fit("fit");
  hFrac_slice_8085->Fit("fit");
  hFrac_slice_8590->Fit("fit");
  hFrac_slice_9095->Fit("fit");
  hFrac_slice_95100->Fit("fit");
  hFrac_slice_100105->Fit("fit");
  hFrac_slice_105110->Fit("fit");
  hFrac_slice_110115->Fit("fit");
  hFrac_slice_115120->Fit("fit");
  */
  //plotting two 1D histograms on same canvas - different scales

  /*
  TCanvas *c1 = new TCanvas("c1","cal and kin energy difference",200,10,700,500);
  TPad *pad1 = new TPad("pad1","",0,0,1,1);
  TPad *pad2 = new TPad("pad2","",0,0,1,1);
  TPad *pad3 = new TPad("pad3","",0,0,1,1);

  pad2->SetFillStyle(4000);
  pad3->SetFillStyle(4000);
  pad1->Draw();
  pad1->cd();
  
  hE->Draw();
  pad1->Update();
  //TPaveStats *ps1 = (TPaveStats*)hCL->GetListOfFunctions()->FindObject("stats");
  //ps1->SetX1NDC(0.4);
  //ps1->SetX2NDC(0.6);
  pad1->Modified();
  c1->cd();

  double ymin = 0;
  double ymax = 140000;
  double dy = (ymax-ymin)/0.8;
  double xmin = 0;
  double xmax = 10;
  double dx = (xmax-xmin)/0.8;
  float rightmax = 1.1*hKL->GetMaximum();
  float scale = gPad->GetUymax()/rightmax;
  //pad2->Range(xmin-0.1*dx,ymin-0.1*dy,xmax+0.1*dx,ymax+0.1*dy);
  //pad2->Draw();
  //pad2->cd();    
  hKL->SetLineColor(kRed);
  hKL->Scale(scale);
  hKL->Draw("same");
  //pad2->Update();
  //TPaveStats *ps2 = (TPaveStats*)hKL->GetListOfFunctions()->FindObject("stats");
  //ps2->SetX1NDC(0.65);
  //ps2->SetX2NDC(0.85);
  //ps2->SetTextColor(kRed);
  //pad2->Modified();
  //c1->cd();
  
  ymin = 0;
  ymax = 240000;
  dy = (ymax-ymin)/0.8;
  xmin = 0;
  xmax = 10;
  dx = (xmax-xmax)/0.8;
  pad3->Range(xmin-0.1*dx,ymin-0.1*dy,xmax+0.1*dx,ymax+0.1*dy);
  pad3->Draw();
  pad2->cd();
  hE->SetLineColor(kGreen);
  hE->Draw("][same");
  */

  //Two 1D  histograms, same canvas, same scale - showing effect of res and thresh on reconstructed

  /*
  gStyle->SetHatchesSpacing(0.5);
  
  TCanvas *calres = new TCanvas("calres","Calorimetric energy: with and without resolution and threshold");
  hKG_diff_frac->SetLineColor(kBlack);
  hKG_diff_frac->SetFillColor(kGray);
  hKG_diff_frac->Draw();
  calres->Update();
  hKL_diff_frac->SetLineColor(kRed);
  hKL_diff_frac->SetFillStyle(3409);
  hKL_diff_frac->SetFillColor(kRed);
  hKL_diff_frac->Draw("same");
  calres->Update();
  hCR_diff_frac->SetLineColor(kBlue);
  hCR_diff_frac->SetFillStyle(3003);
  hCR_diff_frac->SetFillColor(kBlue);
  hCR_diff_frac->Draw("same");
  auto legend1 = new TLegend(0.2,0.7,0.4,0.85);
  legend1->SetBorderSize(0);
  legend1->AddEntry(hKG_diff_frac,"Original","f");
  legend1->AddEntry(hCR_diff_frac,"Resolution","f");
  legend1->AddEntry(hKL_diff_frac,"Threshold","f");
  legend1->Draw();
  */
  /*
  TCanvas *resmuon = new TCanvas("resmuon","Muon momentum: before and after resolution");
  hmuon->SetLineColor(kGray);
  hmuon->SetLineWidth(3);
  hmuon->Draw();
  hmuongas->SetLineColor(kGray+3);
  resmuon->Update();
  hmuongas->Draw("same");
  resmuon->Update();
  hmuonliquid->SetLineColor(kBlack);
  hmuonliquid->Draw("same");
  auto legend2 = new TLegend(0.6,0.7,0.9,0.85);
  legend2->SetBorderSize(0);
  legend2->AddEntry(hmuon,"Before threshold","l");
  legend2->AddEntry(hmuongas,"GAr threshold","l");
  legend2->AddEntry(hmuonliquid,"LAr threshold","l");
  legend2->Draw();
  */
  /*
  TCanvas *respipm = new TCanvas("respipm","Pipm momentum: before and after resolution");
  hpipm->SetLineColor(kGray);
  hpipm->SetLineWidth(3);
  hpipm->Draw();
  hpipmgas->SetLineColor(kGray+1);
  hpipmgas->SetLineWidth(2);
  respipm->Update();
  hpipmgas->Draw("same");
  respipm->Update();
  hpipmliquid->SetLineColor(kBlack);
  hpipmliquid->Draw("same");
  auto legend4 = new TLegend(0.55,0.7,0.9,0.85);
  legend4->AddEntry(hpipm,"Before threshold","l");
  legend4->AddEntry(hpipmgas,"GAr threshold","l");
  legend4->AddEntry(hpipmliquid,"LAr threshold","l");
  legend4->SetBorderSize(0);
  legend4->Draw();
  
  gStyle->SetLegendTextSize(0.05);
  */
 
  /*
  TCanvas *c = new TCanvas("c", "Genie");
  //c->SetGrid();
  hCL_diff_true_frac->Draw("colz");
  */
  
  return (0);
}
