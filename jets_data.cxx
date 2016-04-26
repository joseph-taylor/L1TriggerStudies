#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
#include "TH1F.h"
#include "TH2F.h"
#include <iostream>
#include <math.h>
#include <vector>
#include <string>

//TODO:add dET and dPhi etc, as a functions of reco et
//and the distributions...

//#include "L1Trigger/L1TNtuples/interface/L1AnalysisEventDataFormat.h"
//#include "L1Trigger/L1TNtuples/interface/L1AnalysisSimulationDataFormat.h"
//#include "L1Trigger/L1TNtuples/interface/L1AnalysisGCTDataFormat.h"
//#include "L1Trigger/L1TNtuples/interface/L1AnalysisGTDataFormat.h"
//#include "L1Trigger/L1TNtuples/interface/L1AnalysisGMTDataFormat.h"
//#include "L1Trigger/L1TNtuples/interface/L1AnalysisGTDataFormat.h"
//#include "L1Trigger/L1TNtuples/interface/L1AnalysisRCTDataFormat.h"
//#include "L1Trigger/L1TNtuples/interface/L1AnalysisDTTFDataFormat.h"
//#include "L1Trigger/L1TNtuples/interface/L1AnalysisCSCTFDataFormat.h"
//#include "L1Trigger/L1TNtuples/interface/L1AnalysisRecoMetDataFormat.h"
#include "L1Trigger/L1TNtuples/interface/L1AnalysisRecoJetDataFormat.h"
//#include "L1Trigger/L1TNtuples/interface/L1AnalysisRecoClusterDataFormat.h"
//#include "L1Trigger/L1TNtuples/interface/L1AnalysisRecoMuonDataFormat.h"
//#include "L1Trigger/L1TNtuples/interface/L1AnalysisRecoRpcHitDataFormat.h"
//#include "L1Trigger/L1TNtuples/interface/L1AnalysisL1ExtraDataFormat.h"
//#include "L1Trigger/L1TNtuples/interface/L1AnalysisRecoVertexDataFormat.h"
//#include "L1Trigger/L1TNtuples/interface/L1AnalysisRecoTrackDataFormat.h"
//#include "L1Trigger/L1TNtuples/interface/L1AnalysisL1MenuDataFormat.h"
#include "L1Trigger/L1TNtuples/interface/L1AnalysisL1UpgradeDataFormat.h"
//#include "L1Trigger/L1TNtuples/interface/L1AnalysisL1CaloTowerDataFormat.h"
//#include "L1Trigger/L1TNtuples/interface/L1AnalysisCaloTPDataFormat.h"
#include "L1Trigger/L1TNtuples/interface/L1AnalysisRecoMetFilterDataFormat.h"



bool tightJetID_central(float eta, float nhef, float pef, float mef, float chef, float eef,
                        short chMult, short nhMult, short phMult, short elMult, short muMult){
  //nb:this function does not use mef:but this way we keep the same input system
  bool jetPass;
  if (abs(eta)<=3.00 && nhef<0.90 && pef<0.90 && (chMult+nhMult+phMult+elMult+muMult)>1     
        && (abs(eta)>2.4||(abs(eta)<=2.4 && chef>0 && (chMult+elMult+muMult)>0 && eef<0.99))){
    jetPass = true;}//this jet has passed
  else{jetPass = false;}//this jet has failed, or is outside the central zone           
  return jetPass;
}



bool tightLepVeto_central(float eta, float nhef, float pef, float mef, float chef, float eef,
                        short chMult, short nhMult, short phMult, short elMult, short muMult){
  bool jetPass;
  if (abs(eta)<=3.00 && nhef<0.90 && pef<0.90 && (chMult+nhMult+phMult+elMult+muMult)>1 && mef<0.8    
        && (abs(eta)>2.4||(abs(eta)<=2.4 && chef>0 && (chMult+elMult+muMult)>0 && eef<0.90))){
    jetPass = true;}//this jet has passed
  else{jetPass = false;}//this jet has failed, or is outside the central zone           
  return jetPass;
}



bool tightLepVeto_elMultZero_central(float eta, float nhef, float pef, float mef, float chef, float eef,
                                     short chMult, short nhMult, short phMult, short elMult, short muMult){
  bool jetPass;
  if (elMult==0 &&
        abs(eta)<=3.00 && nhef<0.90 && pef<0.90 && (chMult+nhMult+phMult+elMult+muMult)>1 && mef<0.8    
        && (abs(eta)>2.4||(abs(eta)<=2.4 && chef>0 && (chMult+elMult+muMult)>0 && eef<0.90))){
    jetPass = true;}//this jet has passed
  else{jetPass = false;}//this jet has failed, or is outside the central zone           
  return jetPass;
}



bool tightLepVeto_muMultZero_central(float eta, float nhef, float pef, float mef, float chef, float eef,
                                     short chMult, short nhMult, short phMult, short elMult, short muMult){
  bool jetPass;
  if (muMult==0 &&
        abs(eta)<=3.00 && nhef<0.90 && pef<0.90 && (chMult+nhMult+phMult+elMult+muMult)>1 && mef<0.8    
        && (abs(eta)>2.4||(abs(eta)<=2.4 && chef>0 && (chMult+elMult+muMult)>0 && eef<0.90))){
    jetPass = true;}//this jet has passed
  else{jetPass = false;}//this jet has failed, or is outside the central zone           
  return jetPass;
}



bool tightLepVeto_muElMultZero_central(float eta, float nhef, float pef, float mef, float chef, float eef,
                                     short chMult, short nhMult, short phMult, short elMult, short muMult){
  bool jetPass;
  if (elMult==0 && muMult==0 &&
        abs(eta)<=3.00 && nhef<0.90 && pef<0.90 && (chMult+nhMult+phMult+elMult+muMult)>1 && mef<0.8    
        && (abs(eta)>2.4||(abs(eta)<=2.4 && chef>0 && (chMult+elMult+muMult)>0 && eef<0.90))){
    jetPass = true;}//this jet has passed
  else{jetPass = false;}//this jet has failed, or is outside the central zone           
  return jetPass;
}



bool tightJetID_hf(float pef, short nhMult, short phMult){
  bool jetPass;
  if (pef<0.90 && (nhMult+phMult)>10){jetPass = true;}//this hf jet has passed
  else{jetPass = false;}//this hf jet has failed
  return jetPass;
}



bool met_filter(Bool_t hbheNoiseFilter, Bool_t hbheNoiseIsoFilter, Bool_t cscTightHalo2015Filter, Bool_t ecalDeadCellTPFilter,
                Bool_t goodVerticesFilter, Bool_t eeBadScFilter, Bool_t chHadTrackResFilter, Bool_t muonBadTrackFilter){

  bool metPass;
  if (hbheNoiseFilter==1 && hbheNoiseIsoFilter==1 && cscTightHalo2015Filter==1 && ecalDeadCellTPFilter==1 
      && goodVerticesFilter==1 && eeBadScFilter==1 && chHadTrackResFilter==1 && muonBadTrackFilter==1){
    metPass = true;}//this met has passed
  else{metPass = false;}
  return metPass;
}



//function:calculate dPhi for two phi inputs
//NB:this is phi1-phi2
double calc_dPHI(double phi1, double phi2){
	double dPhi = phi1 - phi2;
	if (dPhi>M_PI){dPhi=dPhi-2*M_PI;}
	if (dPhi<-M_PI){dPhi=dPhi+2*M_PI;}
	return dPhi;
	}
	


//function:calculate dEta for two eta inputs
//NB:this is eta1-eta2
double calc_dETA(double eta1, double eta2){
	double dEta = eta1 - eta2;
	return dEta;
	}
		


//function: Calculates dR given the dPhi and dEta
double calc_dR(double dPhi, double dEta){
	double dR = sqrt(  pow(dPhi,2)  +  pow(dEta,2) );
	return dR;
  }
  	


//Jet structure (use for trigger and reco)
struct Jet{
  vector<float> et;
  vector<float> eta;
  vector<float> phi;
  UInt_t n;
  vector<short> bx;
  //the following are just for reco cleaning
  vector<float> nhef;       //neutral hadron energy fraction
  vector<float> pef;        //neutral EM (photon) energy fraction
  vector<float> mef;        //muon energy fraction
  vector<float> chef;       //charged hadron energy fraction
  vector<float> eef;        //charged EM (electron) energy fraction
  vector<short> chMult;     //charged hadron multiplicity
  vector<short> nhMult;     //neutral hadron multiplicity
  vector<short> phMult;     //photon multiplicity
  vector<short> elMult;     //electron multiplicity
  vector<short> muMult;     //muon multiplicity
};  	


/////////////////
/////////////////
//MAIN FUNCTION//
/////////////////
/////////////////
void jets_data(){

  //create a ROOT file to save all the histograms to (actually at end of script)
  //first check the file doesn't exist already so we don't overwrite
  string dirName = "output_jets/run269224_zeroBias_v34p0_HW/";
  string outputFilename = dirName + "histos_extra2.root";

  TFile *kk = TFile::Open( outputFilename.c_str() );
  if (kk!=0){
  cout << "TERMINATE:not going to overwrite file" << endl;
  return;
  }

  // make trees
 // TChain * upgradeTree = new TChain("l1UpgradeEmuTree/L1UpgradeTree");
    TChain * upgradeTree = new TChain("l1UpgradeTree/L1UpgradeTree");
  TChain * recoTree = new TChain("l1JetRecoTree/JetRecoTree");
  TChain * metFilterTree = new TChain("l1MetFilterRecoTree/MetFilterRecoTree");

  upgradeTree->Add("/hdfs/L1JEC/CMSSW_8_0_2/L1JetEnergyCorrections/ZeroBias_run269224_v34p0/com2016_1/*.root");
  upgradeTree->Add("/hdfs/L1JEC/CMSSW_8_0_2/L1JetEnergyCorrections/ZeroBias_run269224_v34p0/com2016_2/*.root");
  upgradeTree->Add("/hdfs/L1JEC/CMSSW_8_0_2/L1JetEnergyCorrections/ZeroBias_run269224_v34p0/com2016_3/*.root");
  upgradeTree->Add("/hdfs/L1JEC/CMSSW_8_0_2/L1JetEnergyCorrections/ZeroBias_run269224_v34p0/com2016_4/*.root");
  upgradeTree->Add("/hdfs/L1JEC/CMSSW_8_0_2/L1JetEnergyCorrections/ZeroBias_run269224_v34p0/com2016_5/*.root");
  upgradeTree->Add("/hdfs/L1JEC/CMSSW_8_0_2/L1JetEnergyCorrections/ZeroBias_run269224_v34p0/com2016_6/*.root");
  upgradeTree->Add("/hdfs/L1JEC/CMSSW_8_0_2/L1JetEnergyCorrections/ZeroBias_run269224_v34p0/com2016_7/*.root");
  upgradeTree->Add("/hdfs/L1JEC/CMSSW_8_0_2/L1JetEnergyCorrections/ZeroBias_run269224_v34p0/com2016_8/*.root");
  recoTree->Add("/hdfs/L1JEC/CMSSW_8_0_2/L1JetEnergyCorrections/ZeroBias_run269224_v34p0/com2016_1/*.root");
  recoTree->Add("/hdfs/L1JEC/CMSSW_8_0_2/L1JetEnergyCorrections/ZeroBias_run269224_v34p0/com2016_2/*.root");
  recoTree->Add("/hdfs/L1JEC/CMSSW_8_0_2/L1JetEnergyCorrections/ZeroBias_run269224_v34p0/com2016_3/*.root");
  recoTree->Add("/hdfs/L1JEC/CMSSW_8_0_2/L1JetEnergyCorrections/ZeroBias_run269224_v34p0/com2016_4/*.root");
  recoTree->Add("/hdfs/L1JEC/CMSSW_8_0_2/L1JetEnergyCorrections/ZeroBias_run269224_v34p0/com2016_5/*.root");
  recoTree->Add("/hdfs/L1JEC/CMSSW_8_0_2/L1JetEnergyCorrections/ZeroBias_run269224_v34p0/com2016_6/*.root");
  recoTree->Add("/hdfs/L1JEC/CMSSW_8_0_2/L1JetEnergyCorrections/ZeroBias_run269224_v34p0/com2016_7/*.root");
  recoTree->Add("/hdfs/L1JEC/CMSSW_8_0_2/L1JetEnergyCorrections/ZeroBias_run269224_v34p0/com2016_8/*.root");
  metFilterTree->Add("/hdfs/L1JEC/CMSSW_8_0_2/L1JetEnergyCorrections/ZeroBias_run269224_v34p0/com2016_1/*.root");
  metFilterTree->Add("/hdfs/L1JEC/CMSSW_8_0_2/L1JetEnergyCorrections/ZeroBias_run269224_v34p0/com2016_2/*.root");
  metFilterTree->Add("/hdfs/L1JEC/CMSSW_8_0_2/L1JetEnergyCorrections/ZeroBias_run269224_v34p0/com2016_3/*.root");
  metFilterTree->Add("/hdfs/L1JEC/CMSSW_8_0_2/L1JetEnergyCorrections/ZeroBias_run269224_v34p0/com2016_4/*.root");
  metFilterTree->Add("/hdfs/L1JEC/CMSSW_8_0_2/L1JetEnergyCorrections/ZeroBias_run269224_v34p0/com2016_5/*.root");
  metFilterTree->Add("/hdfs/L1JEC/CMSSW_8_0_2/L1JetEnergyCorrections/ZeroBias_run269224_v34p0/com2016_6/*.root");
  metFilterTree->Add("/hdfs/L1JEC/CMSSW_8_0_2/L1JetEnergyCorrections/ZeroBias_run269224_v34p0/com2016_7/*.root");
  metFilterTree->Add("/hdfs/L1JEC/CMSSW_8_0_2/L1JetEnergyCorrections/ZeroBias_run269224_v34p0/com2016_8/*.root");

  Int_t nevent = (Int_t)recoTree->GetEntries();

  /////////////////////////////
  //PARAMETERS FOR THE SCRIPT//
  /////////////////////////////
  const double recoJet_ETmin = 10;                //min ET(GeV) for RECO jet to be considered
  const double recoJet_etaMaxCentral = 3.00;      //max eta for RECO jet to be CENTRAL
  const double recoJet_etaMinHF = 3.50;           //max eta for RECO jet to be HF
  const double recoJet_etaMaxHF = 4.50;           //max eta for RECO jet to be HF
  const double dR_matchMax = 0.40;                //max dR allowed for a turnOn 'match'
  //nb:hf actually is between 3<->5, but this keeps it isolated from edge effects

  /////////////////////////
  //Structures for script//
  /////////////////////////
   struct Jet recojet;
   struct Jet l1jet;

  // branch class types
  //  L1Analysis::L1AnalysisEventDataFormat        *event_ = new L1Analysis::L1AnalysisEventDataFormat();
  //  L1Analysis::L1AnalysisSimulationDataFormat   *simulation_;
  //  L1Analysis::L1AnalysisGCTDataFormat          *gct_;
  //  L1Analysis::L1AnalysisGMTDataFormat          *gmt_;
  //  L1Analysis::L1AnalysisGTDataFormat           *gt_;
  //  L1Analysis::L1AnalysisRCTDataFormat          *rct_;
  //  L1Analysis::L1AnalysisDTTFDataFormat         *dttf_;
  //  L1Analysis::L1AnalysisCSCTFDataFormat        *csctf_;
  //  L1Analysis::L1AnalysisRecoMetDataFormat      *recoMet_;
  //  L1Analysis::L1AnalysisRecoMuonDataFormat     *recoMuon_;
  //  L1Analysis::L1AnalysisRecoRpcHitDataFormat   *recoRpcHit_;
  //  L1Analysis::L1AnalysisRecoJetDataFormat      *recoJet_ = new L1Analysis::L1AnalysisRecoJetDataFormat();
  //  L1Analysis::L1AnalysisRecoClusterDataFormat  *recoBasicCluster_;
  //  L1Analysis::L1AnalysisRecoClusterDataFormat  *recoSuperCluster_;
  //  L1Analysis::L1AnalysisL1ExtraDataFormat      *l1extra_;
  //  L1Analysis::L1AnalysisL1ExtraDataFormat      *l1emuextra_;
  //  L1Analysis::L1AnalysisRecoVertexDataFormat   *recoVertex_;
  //  L1Analysis::L1AnalysisRecoTrackDataFormat    *recoTrack_;
  //  L1Analysis::L1AnalysisL1MenuDataFormat       *l1menu_;
  //  L1Analysis::L1AnalysisL1UpgradeDataFormat    *upgrade_ = new L1Analysis::L1AnalysisL1UpgradeDataFormat();
  //  L1Analysis::L1AnalysisCaloTPDataFormat       *caloTP_ = new L1Analysis::L1AnalysisCaloTPDataFormat();
  //  L1Analysis::L1AnalysisL1CaloTowerDataFormat  *l1Tower_ = new L1Analysis::L1AnalysisL1CaloTowerDataFormat();

  //set the branch addresses
  L1Analysis::L1AnalysisRecoJetDataFormat      *recoJet_ = new L1Analysis::L1AnalysisRecoJetDataFormat();
  recoTree->SetBranchAddress("Jet", &recoJet_);

  L1Analysis::L1AnalysisL1UpgradeDataFormat    *upgrade_ = new L1Analysis::L1AnalysisL1UpgradeDataFormat();
  upgradeTree->SetBranchAddress("L1Upgrade", &upgrade_);

  L1Analysis::L1AnalysisRecoMetFilterDataFormat      *recoMetFilter_ = new L1Analysis::L1AnalysisRecoMetFilterDataFormat();
  metFilterTree->SetBranchAddress("MetFilters", &recoMetFilter_);



  ///////////////////////////////////////////
  //create the framework for the histograms//nb: WAC stands for 'with additional (recojet) cleaning'
  ///////////////////////////////////////////
  //comparison histos
  TH1F * hdPhi_central = new TH1F("hdPhi_central", ";#phi_{RECO} - #phi_{L1}", 100, -0.5, 0.5);
  TH1F * hdEta_central = new TH1F("hdEta_central", ";#eta_{RECO} - #eta_{L1}", 100, -0.5, 0.5);
  TH1F * hdR_central = new TH1F("hdR_central", ";dR_{RECO - L1}", 100, 0, 1.0);

  TH2F * hPosScat = new TH2F("hPosScat", "", 500, -0.5, 0.5, 500, -0.5, 0.5);
  hPosScat->GetXaxis()->SetTitle("#phi_{PF} - #phi_{L1}");
  hPosScat->GetYaxis()->SetTitle("#eta_{PF} - #eta_{L1}");

  TH1F * hdET_central = new TH1F("hdET_central", ";(ET_{L1} - ET_{RECO})/ET_{RECO}", 100, -2.0, 4.0);
  TH2F * hETS_central = new TH2F("hETS_central", "", 500, 0, 250, 500, 0, 250);
  hETS_central->GetXaxis()->SetTitle("RECO E_{T} (GeV)");
  hETS_central->GetYaxis()->SetTitle("L1 upgrade E_{T} (GeV)");

  TH1F * hdPhi_central_WAC = new TH1F("hdPhi_central_WAC", ";#phi_{RECO} - #phi_{L1}", 100, -0.5, 0.5);
  TH1F * hdEta_central_WAC = new TH1F("hdEta_central_WAC", ";#eta_{RECO} - #eta_{L1}", 100, -0.5, 0.5);
  TH1F * hdR_central_WAC = new TH1F("hdR_central_WAC", ";dR_{RECO - L1}", 100, 0, 1.0);
  TH1F * hdET_central_WAC = new TH1F("hdET_central_WAC", ";(ET_{L1} - ET_{RECO})/ET_{RECO}", 100, -2.0, 4.0);
  TH2F * hETS_central_WAC = new TH2F("hETS_central_WAC", "", 500, 0, 250, 500, 0, 250);
  hETS_central_WAC->GetXaxis()->SetTitle("RECO E_{T} (GeV)");
  hETS_central_WAC->GetYaxis()->SetTitle("L1 upgrade E_{T} (GeV)");

  TH1F * hdPhi_hf = new TH1F("hdPhi_hf", ";#phi_{RECO} - #phi_{L1}", 100, -0.5, 0.5);
  TH1F * hdEta_hf = new TH1F("hdEta_hf", ";#eta_{RECO} - #eta_{L1}", 100, -0.5, 0.5);
  TH1F * hdR_hf = new TH1F("hdR_hf", ";dR_{RECO - L1}", 100, 0, 1.0);
  TH1F * hdET_hf = new TH1F("hdET_hf", ";(ET_{L1} - ET_{RECO})/ET_{RECO}", 100, -2.0, 4.0);
  TH2F * hETS_hf = new TH2F("hETS_hf", "", 500, 0, 250, 500, 0, 250);
  hETS_hf->GetXaxis()->SetTitle("RECO E_{T} (GeV)");
  hETS_hf->GetYaxis()->SetTitle("L1 upgrade E_{T} (GeV)");

  TH1F * hdPhi_hf_WAC = new TH1F("hdPhi_hf_WAC", ";#phi_{RECO} - #phi_{L1}", 100, -0.5, 0.5);
  TH1F * hdEta_hf_WAC = new TH1F("hdEta_hf_WAC", ";#eta_{RECO} - #eta_{L1}", 100, -0.5, 0.5);
  TH1F * hdR_hf_WAC = new TH1F("hdR_hf_WAC", ";dR_{RECO - L1}", 100, 0, 1.0);
  TH1F * hdET_hf_WAC = new TH1F("hdET_hf_WAC", ";(ET_{L1} - ET_{RECO})/ET_{RECO}", 100, -2.0, 4.0);
  TH2F * hETS_hf_WAC = new TH2F("hETS_hf_WAC", "", 250, 0, 250, 250, 0, 250);
  hETS_hf_WAC->GetXaxis()->SetTitle("RECO E_{T} (GeV)");
  hETS_hf_WAC->GetYaxis()->SetTitle("L1 upgrade E_{T} (GeV)");

  //turnOn histos
  //nb: num=numerator, den=denominator. At the bottom of script we create efficiency 'histos'
  TH1F * hden_central = new TH1F("hden_central", "", 40, 0, 400);
  TH1F * hnum36_central = new TH1F("hnum36_central", "", 40, 0, 400);
  TH1F * hT36_central = new TH1F("hT36_central", ";pf_jet E_{T} (GeV);efficiency", 40, 0, 400);
  TH1F * hnum52_central = new TH1F("hnum52_central", "", 40, 0, 400);
  TH1F * hT52_central = new TH1F("hT52_central", ";pf_jet E_{T} (GeV);efficiency", 40, 0, 400);
  TH1F * hnum68_central = new TH1F("hnum68_central", "", 40, 0, 400);
  TH1F * hT68_central = new TH1F("hT68_central", ";pf_jet E_{T} (GeV);efficiency", 40, 0, 400);
  TH1F * hnum92_central = new TH1F("hnum92_central", "", 40, 0, 400);
  TH1F * hT92_central = new TH1F("hT92_central", ";pf_jet E_{T} (GeV);efficiency", 40, 0, 400);
  TH1F * hnum128_central = new TH1F("hnum128_central", "", 40, 0, 400);
  TH1F * hT128_central = new TH1F("hT128_central", ";pf_jet E_{T} (GeV);efficiency", 40, 0, 400);
  TH1F * hnum176_central = new TH1F("hnum176_central", "", 40, 0, 400);
  TH1F * hT176_central = new TH1F("hT176_central", ";pf_jet E_{T} (GeV);efficiency", 40, 0, 400);
  TH1F * hnum200_central = new TH1F("hnum200_central", "", 40, 0, 400);
  TH1F * hT200_central = new TH1F("hT200_central", ";pf_jet E_{T} (GeV);efficiency", 40, 0, 400);

  TH1F * hden_central_WAC = new TH1F("hden_central_WAC", "", 40, 0, 400);
  TH1F * hnum36_central_WAC = new TH1F("hnum36_central_WAC", "", 40, 0, 400);
  TH1F * hT36_central_WAC = new TH1F("hT36_central_WAC", ";pf_jet E_{T} (GeV);efficiency", 40, 0, 400);
  TH1F * hnum52_central_WAC = new TH1F("hnum52_central_WAC", "", 40, 0, 400);
  TH1F * hT52_central_WAC = new TH1F("hT52_central_WAC", ";pf_jet E_{T} (GeV);efficiency", 40, 0, 400);
  TH1F * hnum68_central_WAC = new TH1F("hnum68_central_WAC", "", 40, 0, 400);
  TH1F * hT68_central_WAC = new TH1F("hT68_central_WAC", ";pf_jet E_{T} (GeV);efficiency", 40, 0, 400);
  TH1F * hnum92_central_WAC = new TH1F("hnum92_central_WAC", "", 40, 0, 400);
  TH1F * hT92_central_WAC = new TH1F("hT92_central_WAC", ";pf_jet E_{T} (GeV);efficiency", 40, 0, 400);
  TH1F * hnum128_central_WAC = new TH1F("hnum128_central_WAC", "", 40, 0, 400);
  TH1F * hT128_central_WAC = new TH1F("hT128_central_WAC", ";pf_jet E_{T} (GeV);efficiency", 40, 0, 400);
  TH1F * hnum176_central_WAC = new TH1F("hnum176_central_WAC", "", 40, 0, 400);
  TH1F * hT176_central_WAC = new TH1F("hT176_central_WAC", ";pf_jet E_{T} (GeV);efficiency", 40, 0, 400);
  TH1F * hnum200_central_WAC = new TH1F("hnum200_central_WAC", "", 40, 0, 400);
  TH1F * hT200_central_WAC = new TH1F("hT200_central_WAC", ";pf_jet E_{T} (GeV);efficiency", 40, 0, 400);

  TH1F * hden_hf = new TH1F("hden_hf", "", 40, 0, 400);
  TH1F * hnum36_hf = new TH1F("hnum36_hf", "", 40, 0, 400);
  TH1F * hT36_hf = new TH1F("hT36_hf", ";pf_jet E_{T} (GeV);efficiency", 40, 0, 400);
  TH1F * hnum52_hf = new TH1F("hnum52_hf", "", 40, 0, 400);
  TH1F * hT52_hf = new TH1F("hT52_hf", ";pf_jet E_{T} (GeV);efficiency", 40, 0, 400);
  TH1F * hnum68_hf = new TH1F("hnum68_hf", "", 40, 0, 400);
  TH1F * hT68_hf = new TH1F("hT68_hf", ";pf_jet E_{T} (GeV);efficiency", 40, 0, 400);
  TH1F * hnum92_hf = new TH1F("hnum92_hf", "", 40, 0, 400);
  TH1F * hT92_hf = new TH1F("hT92_hf", ";pf_jet E_{T} (GeV);efficiency", 40, 0, 400);
  TH1F * hnum128_hf = new TH1F("hnum128_hf", "", 40, 0, 400);
  TH1F * hT128_hf = new TH1F("hT128_hf", ";pf_jet E_{T} (GeV);efficiency", 40, 0, 400);
  TH1F * hnum176_hf = new TH1F("hnum176_hf", "", 40, 0, 400);
  TH1F * hT176_hf = new TH1F("hT176_hf", ";pf_jet E_{T} (GeV);efficiency", 40, 0, 400);
  TH1F * hnum200_hf = new TH1F("hnum200_hf", "", 40, 0, 400);
  TH1F * hT200_hf = new TH1F("hT200_hf", ";pf_jet E_{T} (GeV);efficiency", 40, 0, 400);

  TH1F * hden_hf_WAC = new TH1F("hden_hf_WAC", "", 40, 0, 400);
  TH1F * hnum36_hf_WAC = new TH1F("hnum36_hf_WAC", "", 40, 0, 400);
  TH1F * hT36_hf_WAC = new TH1F("hT36_hf_WAC", ";pf_jet E_{T} (GeV);efficiency", 40, 0, 400);
  TH1F * hnum52_hf_WAC = new TH1F("hnum52_hf_WAC", "", 40, 0, 400);
  TH1F * hT52_hf_WAC = new TH1F("hT52_hf_WAC", ";pf_jet E_{T} (GeV);efficiency", 40, 0, 400);
  TH1F * hnum68_hf_WAC = new TH1F("hnum68_hf_WAC", "", 40, 0, 400);
  TH1F * hT68_hf_WAC = new TH1F("hT68_hf_WAC", ";pf_jet E_{T} (GeV);efficiency", 40, 0, 400);
  TH1F * hnum92_hf_WAC = new TH1F("hnum92_hf_WAC", "", 40, 0, 400);
  TH1F * hT92_hf_WAC = new TH1F("hT92_hf_WAC", ";pf_jet E_{T} (GeV);efficiency", 40, 0, 400);
  TH1F * hnum128_hf_WAC = new TH1F("hnum128_hf_WAC", "", 40, 0, 400);
  TH1F * hT128_hf_WAC = new TH1F("hT128_hf_WAC", ";pf_jet E_{T} (GeV);efficiency", 40, 0, 400);
  TH1F * hnum176_hf_WAC = new TH1F("hnum176_hf_WAC", "", 40, 0, 400);
  TH1F * hT176_hf_WAC = new TH1F("hT176_hf_WAC", ";pf_jet E_{T} (GeV);efficiency", 40, 0, 400);
  TH1F * hnum200_hf_WAC = new TH1F("hnum200_hf_WAC", "", 40, 0, 400);
  TH1F * hT200_hf_WAC = new TH1F("hT200_hf_WAC", ";pf_jet E_{T} (GeV);efficiency", 40, 0, 400);



  ///////////////////////////////
  ///////////////////////////////
  //loop through all the events//
  ///////////////////////////////
  ///////////////////////////////
  // nevent = 10000;
  for (Int_t i=0; i<nevent; i++){
  			
    //load the Tree info for the event
    int nb = recoTree->GetEntry(i);
    if (nb==0){
      cout << "did not load JetRecoTree for entry " << i << endl;
      return;}
    
    nb = upgradeTree->GetEntry(i);
    if (nb==0){
      cout << "did not load L1UpgradeTree for entry " << i << endl;
      return;}
    
    nb = metFilterTree->GetEntry(i);
    if (nb==0){
      cout << "did not load metFilterRecoTree for entry " << i << endl;
      return;}

              
    //////////////////////////////////////
    ///analysis///////////////////////////
    //////////////////////////////////////
    //now fill in the jet structures for the event
    //how to read values
    //Int_t nJets = recoJet_->nJets;
    //vector<int> vec = upgrade_->jetIet;
    //vec[j]
    recojet.et = recoJet_->et;
    recojet.eta = recoJet_->eta;
    recojet.phi = recoJet_->phi;
    recojet.n = recoJet_->nJets;

    recojet.nhef = recoJet_->nhef;
    recojet.pef = recoJet_->pef;
    recojet.mef = recoJet_->mef;
    recojet.chef = recoJet_->chef;
    recojet.eef = recoJet_->eef;
    recojet.chMult = recoJet_->chMult;
    recojet.nhMult = recoJet_->nhMult;
    recojet.phMult = recoJet_->phMult;
    recojet.elMult = recoJet_->elMult;
    recojet.muMult = recoJet_->muMult;
    
    l1jet.et = upgrade_->jetEt;
    l1jet.eta = upgrade_->jetEta;
    l1jet.phi = upgrade_->jetPhi;
    l1jet.n = upgrade_->nJets;
    l1jet.bx = upgrade_->jetBx;

    bool central_logic = false;
    bool central_logic_WAC = false;
    bool hf_logic = false;
    bool hf_logic_WAC = false;

    int centralIndex;
    int hfIndex;
    int centralIndexWAC;
    int hfIndexWAC;


    //find the leading central and hf jets in this event
    //(also With Additional Cleaning)
    for (UInt_t j=0; j<recojet.n; j++){   
      if (recojet.et[j] > recoJet_ETmin && abs(recojet.eta[j]) < recoJet_etaMaxCentral){
        centralIndex = j;
        central_logic = true;
        break;
      }
    }


    for (UInt_t j=0; j<recojet.n; j++){   
      if (recojet.et[j] > recoJet_ETmin && abs(recojet.eta[j]) > recoJet_etaMinHF
                            && abs(recojet.eta[j]) < recoJet_etaMaxHF){   
        hfIndex = j;
        hf_logic = true;
        break;
      }
    }

    for (UInt_t j=0; j<recojet.n; j++){   
      if (recojet.et[j] > recoJet_ETmin
          && abs(recojet.eta[j]) < recoJet_etaMaxCentral
          && tightLepVeto_muElMultZero_central(recojet.eta[j], recojet.nhef[j], recojet.pef[j], recojet.mef[j], recojet.chef[j], recojet.eef[j],
                                               recojet.chMult[j], recojet.nhMult[j], recojet.phMult[j], recojet.elMult[j], recojet.muMult[j])
          && met_filter(recoMetFilter_->hbheNoiseFilter, recoMetFilter_->hbheNoiseIsoFilter, recoMetFilter_->cscTightHalo2015Filter, recoMetFilter_->ecalDeadCellTPFilter,
                        recoMetFilter_->goodVerticesFilter, recoMetFilter_->eeBadScFilter, recoMetFilter_->chHadTrackResFilter, recoMetFilter_->muonBadTrackFilter))
      {
        centralIndexWAC = j;
        central_logic_WAC = true;
        break;
      }
    }

    for (UInt_t j=0; j<recojet.n; j++){   
      if (recojet.et[j] > recoJet_ETmin
          && abs(recojet.eta[j]) > recoJet_etaMinHF
          && abs(recojet.eta[j]) < recoJet_etaMaxHF
          && tightJetID_hf(recojet.pef[j], recojet.nhMult[j], recojet.phMult[j])
          && met_filter(recoMetFilter_->hbheNoiseFilter, recoMetFilter_->hbheNoiseIsoFilter, recoMetFilter_->cscTightHalo2015Filter, recoMetFilter_->ecalDeadCellTPFilter,
                        recoMetFilter_->goodVerticesFilter, recoMetFilter_->eeBadScFilter, recoMetFilter_->chHadTrackResFilter, recoMetFilter_->muonBadTrackFilter))
      {   
        hfIndexWAC = j;
        hf_logic_WAC = true;
        break;
      }
    }


    /////////////////////
    //Barrel and Endcap//no cleaning...
    /////////////////////
    if (central_logic){
    
      //now loop through the Upgrade Jets to find
      //the best matching to the RECO jet in question (in terms of dR)
      double dR_min=99999.99;        //use to determine the best match jet
      UInt_t k_min=9999;             //use to index the best match jet          
      int countL1=0;                 //use this quantity as bx may be zero for some l1 jets

      for (UInt_t k=0; k<l1jet.n; k++){
        if(l1jet.bx[k]==0){
          double dPhi = calc_dPHI( recojet.phi[centralIndex], l1jet.phi[k] );
          double dEta = calc_dETA( recojet.eta[centralIndex], l1jet.eta[k] );   
          double dR = calc_dR( dPhi, dEta);
        if (countL1==0){dR_min = dR; k_min = k;}
        if (countL1>0 && dR<dR_min){dR_min = dR; k_min = k;}
        countL1++;
        }
      }
      
      //now make plots and turnOns using the best match
      if (countL1 > 0){
        double dPhi = calc_dPHI( recojet.phi[centralIndex], l1jet.phi[k_min] ); //probs would be best off
        double dEta = calc_dETA( recojet.eta[centralIndex], l1jet.eta[k_min] ); //saving in one object...      
        hdPhi_central->Fill(dPhi);
        hdEta_central->Fill(dEta);
        hdR_central->Fill(dR_min);
        hPosScat->Fill(dPhi, dEta);

        hdET_central->Fill( (l1jet.et[k_min]-recojet.et[centralIndex])/recojet.et[centralIndex] ); 
        hETS_central->Fill(recojet.et[centralIndex], l1jet.et[k_min] );
        
        hden_central->Fill(recojet.et[centralIndex]);
        if (dR_min < dR_matchMax){
          
          if (l1jet.et[k_min]>36){
            hnum36_central->Fill(recojet.et[centralIndex]);
          }                
            if (l1jet.et[k_min]>52){
          hnum52_central->Fill(recojet.et[centralIndex]);
          }        
          if (l1jet.et[k_min]>68){
            hnum68_central->Fill(recojet.et[centralIndex]);
          }
          if (l1jet.et[k_min]>92){
            hnum92_central->Fill(recojet.et[centralIndex]);
          }                
          if (l1jet.et[k_min]>128){
            hnum128_central->Fill(recojet.et[centralIndex]);
          }        
          if (l1jet.et[k_min]>176){
            hnum176_central->Fill(recojet.et[centralIndex]);
          }
          if (l1jet.et[k_min]>200){
            hnum200_central->Fill(recojet.et[centralIndex]);
          }
        }//closes 'if' upgrade jet matches to the RECO jet
      }//closes 'if' we have countL1>0
    }//closes 'if' central logic. ie we have a reco jet





    // /////////////////////
    // //Barrel and Endcap//with cleaning...
    // /////////////////////
    // if (central_logic_WAC){
    
    //   //now loop through the Upgrade Jets to find
    //   //the best matching to the RECO jet in question (in terms of dR)
    //   double dR_min=99999.99;        //use to determine the best match jet
    //   UInt_t k_min=9999;             //use to index the best match jet          
    //   int countL1=0;                 //use this quantity as bx may be zero for some l1 jets

    //   for (UInt_t k=0; k<l1jet.n; k++){
    //     if(l1jet.bx[k]==0){
    //       double dPhi = calc_dPHI( recojet.phi[centralIndexWAC], l1jet.phi[k] );
    //       double dEta = calc_dETA( recojet.eta[centralIndexWAC], l1jet.eta[k] );   
    //       double dR = calc_dR( dPhi, dEta);
    //     if (countL1==0){dR_min = dR; k_min = k;}
    //     if (countL1>0 && dR<dR_min){dR_min = dR; k_min = k;}
    //     countL1++;
    //     }
    //   }
      
    //   //now make plots and turnOns using the best match
    //   if (countL1 > 0){
    //     double dPhi = calc_dPHI( recojet.phi[centralIndexWAC], l1jet.phi[k_min] ); //probs would be best off
    //     double dEta = calc_dETA( recojet.eta[centralIndexWAC], l1jet.eta[k_min] ); //saving in one object...      
    //     hdPhi_central_WAC->Fill(dPhi);
    //     hdEta_central_WAC->Fill(dEta);
    //     hdR_central_WAC->Fill(dR_min);
    //     hdET_central_WAC->Fill( (l1jet.et[k_min]-recojet.et[centralIndexWAC])/recojet.et[centralIndexWAC] ); 
    //     hETS_central_WAC->Fill(recojet.et[centralIndexWAC], l1jet.et[k_min] );
        
    //     hden_central_WAC->Fill(recojet.et[centralIndexWAC]);
    //     if (dR_min < dR_matchMax){
          
    //       if (l1jet.et[k_min]>36){
    //         hnum36_central_WAC->Fill(recojet.et[centralIndexWAC]);
    //       }                
    //         if (l1jet.et[k_min]>52){
    //       hnum52_central_WAC->Fill(recojet.et[centralIndexWAC]);
    //       }        
    //       if (l1jet.et[k_min]>68){
    //         hnum68_central_WAC->Fill(recojet.et[centralIndexWAC]);
    //       }
    //       if (l1jet.et[k_min]>92){
    //         hnum92_central_WAC->Fill(recojet.et[centralIndexWAC]);
    //       }                
    //       if (l1jet.et[k_min]>128){
    //         hnum128_central_WAC->Fill(recojet.et[centralIndexWAC]);
    //       }        
    //       if (l1jet.et[k_min]>176){
    //         hnum176_central_WAC->Fill(recojet.et[centralIndexWAC]);
    //       }
    //       if (l1jet.et[k_min]>200){
    //         hnum200_central_WAC->Fill(recojet.et[centralIndexWAC]);
    //       }
    //     }//closes 'if' upgrade jet matches to the RECO jet
    //   }//closes 'if' we have countL1>0
    // }//closes 'if' central_logic_WAC. ie we have a reco jet




    // /////////////////////
    // //hf//no cleaning...
    // /////////////////////
    // if (hf_logic){
    
    //   //now loop through the Upgrade Jets to find
    //   //the best matching to the RECO jet in question (in terms of dR)
    //   double dR_min=99999.99;        //use to determine the best match jet
    //   UInt_t k_min=9999;             //use to index the best match jet          
    //   int countL1=0;                 //use this quantity as bx may be zero for some l1 jets

    //   for (UInt_t k=0; k<l1jet.n; k++){
    //     if(l1jet.bx[k]==0){
    //       double dPhi = calc_dPHI( recojet.phi[hfIndex], l1jet.phi[k] );
    //       double dEta = calc_dETA( recojet.eta[hfIndex], l1jet.eta[k] );   
    //       double dR = calc_dR( dPhi, dEta);
    //     if (countL1==0){dR_min = dR; k_min = k;}
    //     if (countL1>0 && dR<dR_min){dR_min = dR; k_min = k;}
    //     countL1++;
    //     }
    //   }
      
    //   //now make plots and turnOns using the best match
    //   if (countL1 > 0){
    //     double dPhi = calc_dPHI( recojet.phi[hfIndex], l1jet.phi[k_min] ); //probs would be best off
    //     double dEta = calc_dETA( recojet.eta[hfIndex], l1jet.eta[k_min] ); //saving in one object...      
    //     hdPhi_hf->Fill(dPhi);
    //     hdEta_hf->Fill(dEta);
    //     hdR_hf->Fill(dR_min);
    //     hdET_hf->Fill( (l1jet.et[k_min]-recojet.et[hfIndex])/recojet.et[hfIndex] ); 
    //     hETS_hf->Fill(recojet.et[hfIndex], l1jet.et[k_min] );
        
    //     hden_hf->Fill(recojet.et[hfIndex]);
    //     if (dR_min < dR_matchMax){
          
    //       if (l1jet.et[k_min]>36){
    //         hnum36_hf->Fill(recojet.et[hfIndex]);
    //       }                
    //         if (l1jet.et[k_min]>52){
    //       hnum52_hf->Fill(recojet.et[hfIndex]);
    //       }        
    //       if (l1jet.et[k_min]>68){
    //         hnum68_hf->Fill(recojet.et[hfIndex]);
    //       }
    //       if (l1jet.et[k_min]>92){
    //         hnum92_hf->Fill(recojet.et[hfIndex]);
    //       }                
    //       if (l1jet.et[k_min]>128){
    //         hnum128_hf->Fill(recojet.et[hfIndex]);
    //       }        
    //       if (l1jet.et[k_min]>176){
    //         hnum176_hf->Fill(recojet.et[hfIndex]);
    //       }
    //       if (l1jet.et[k_min]>200){
    //         hnum200_hf->Fill(recojet.et[hfIndex]);
    //       }
    //     }//closes 'if' upgrade jet matches to the RECO jet
    //   }//closes 'if' we have countL1>0
    // }//closes 'if' hf logic. ie we have a reco jet




    // /////////////////////
    // //hf//with cleaning...
    // /////////////////////
    // if (hf_logic_WAC){
    
    //   //now loop through the Upgrade Jets to find
    //   //the best matching to the RECO jet in question (in terms of dR)
    //   double dR_min=99999.99;        //use to determine the best match jet
    //   UInt_t k_min=9999;             //use to index the best match jet          
    //   int countL1=0;                 //use this quantity as bx may be zero for some l1 jets

    //   for (UInt_t k=0; k<l1jet.n; k++){
    //     if(l1jet.bx[k]==0){
    //       double dPhi = calc_dPHI( recojet.phi[hfIndexWAC], l1jet.phi[k] );
    //       double dEta = calc_dETA( recojet.eta[hfIndexWAC], l1jet.eta[k] );   
    //       double dR = calc_dR( dPhi, dEta);
    //     if (countL1==0){dR_min = dR; k_min = k;}
    //     if (countL1>0 && dR<dR_min){dR_min = dR; k_min = k;}
    //     countL1++;
    //     }
    //   }
      
    //   //now make plots and turnOns using the best match
    //   if (countL1 > 0){
    //     double dPhi = calc_dPHI( recojet.phi[hfIndexWAC], l1jet.phi[k_min] ); //probs would be best off
    //     double dEta = calc_dETA( recojet.eta[hfIndexWAC], l1jet.eta[k_min] ); //saving in one object...      
    //     hdPhi_hf_WAC->Fill(dPhi);
    //     hdEta_hf_WAC->Fill(dEta);
    //     hdR_hf_WAC->Fill(dR_min);
    //     hdET_hf_WAC->Fill( (l1jet.et[k_min]-recojet.et[hfIndexWAC])/recojet.et[hfIndexWAC] ); 
    //     hETS_hf_WAC->Fill(recojet.et[hfIndexWAC], l1jet.et[k_min] );
        
    //     hden_hf_WAC->Fill(recojet.et[hfIndexWAC]);
    //     if (dR_min < dR_matchMax){
          
    //       if (l1jet.et[k_min]>36){
    //         hnum36_hf_WAC->Fill(recojet.et[hfIndexWAC]);
    //       }                
    //         if (l1jet.et[k_min]>52){
    //       hnum52_hf_WAC->Fill(recojet.et[hfIndexWAC]);
    //       }        
    //       if (l1jet.et[k_min]>68){
    //         hnum68_hf_WAC->Fill(recojet.et[hfIndexWAC]);
    //       }
    //       if (l1jet.et[k_min]>92){
    //         hnum92_hf_WAC->Fill(recojet.et[hfIndexWAC]);
    //       }                
    //       if (l1jet.et[k_min]>128){
    //         hnum128_hf_WAC->Fill(recojet.et[hfIndexWAC]);
    //       }        
    //       if (l1jet.et[k_min]>176){
    //         hnum176_hf_WAC->Fill(recojet.et[hfIndexWAC]);
    //       }
    //       if (l1jet.et[k_min]>200){
    //         hnum200_hf_WAC->Fill(recojet.et[hfIndexWAC]);
    //       }
    //     }//closes 'if' upgrade jet matches to the RECO jet
    //   }//closes 'if' we have countL1>0
    // }//closes 'if' hf_logic_WAC. ie we have a reco jet




    if (i % 10000 == 0){
  	 cout << i << " out of " << nevent << endl;}		
  }//closes loop through the events

  //save the output ROOT file
  //write the histograms
  TFile g( outputFilename.c_str() , "new");
  //comparison histos
  hdPhi_central->Write();
  hdEta_central->Write();
  hdR_central->Write();
  hdET_central->Write();
  hETS_central->Write();
hPosScat->Write();

  hdPhi_central_WAC->Write();
  hdEta_central_WAC->Write();
  hdR_central_WAC->Write();
  hdET_central_WAC->Write();
  hETS_central_WAC->Write();

  hdPhi_hf->Write();
  hdEta_hf->Write();
  hdR_hf->Write();
  hdET_hf->Write();
  hETS_hf->Write();

  hdPhi_hf_WAC->Write();
  hdEta_hf_WAC->Write();
  hdR_hf_WAC->Write();
  hdET_hf_WAC->Write();
  hETS_hf_WAC->Write();

  //turnOn histos (we write everything so we can do Tefficiency in the plotting script)
  hT36_central->Divide(hnum36_central, hden_central);
  hT52_central->Divide(hnum52_central, hden_central);
  hT68_central->Divide(hnum68_central, hden_central);
  hT92_central->Divide(hnum92_central, hden_central);
  hT128_central->Divide(hnum128_central, hden_central);
  hT176_central->Divide(hnum176_central, hden_central);
  hT200_central->Divide(hnum200_central, hden_central);
  hT36_central->Write();
  hT52_central->Write();
  hT68_central->Write();
  hT92_central->Write();
  hT128_central->Write();
  hT176_central->Write();
  hT200_central->Write();
  hnum36_central->Write();
  hnum52_central->Write();
  hnum68_central->Write();
  hnum92_central->Write();
  hnum128_central->Write();
  hnum176_central->Write();
  hnum200_central->Write();
  hden_central->Write();

  hT36_central_WAC->Divide(hnum36_central_WAC, hden_central_WAC);
  hT52_central_WAC->Divide(hnum52_central_WAC, hden_central_WAC);
  hT68_central_WAC->Divide(hnum68_central_WAC, hden_central_WAC);
  hT92_central_WAC->Divide(hnum92_central_WAC, hden_central_WAC);
  hT128_central_WAC->Divide(hnum128_central_WAC, hden_central_WAC);
  hT176_central_WAC->Divide(hnum176_central_WAC, hden_central_WAC);
  hT200_central_WAC->Divide(hnum200_central_WAC, hden_central_WAC);
  hT36_central_WAC->Write();
  hT52_central_WAC->Write();
  hT68_central_WAC->Write();
  hT92_central_WAC->Write();
  hT128_central_WAC->Write();
  hT176_central_WAC->Write();
  hT200_central_WAC->Write();
  hnum36_central_WAC->Write();
  hnum52_central_WAC->Write();
  hnum68_central_WAC->Write();
  hnum92_central_WAC->Write();
  hnum128_central_WAC->Write();
  hnum176_central_WAC->Write();
  hnum200_central_WAC->Write();
  hden_central_WAC->Write();

  hT36_hf->Divide(hnum36_hf, hden_hf);
  hT52_hf->Divide(hnum52_hf, hden_hf);
  hT68_hf->Divide(hnum68_hf, hden_hf);
  hT92_hf->Divide(hnum92_hf, hden_hf);
  hT128_hf->Divide(hnum128_hf, hden_hf);
  hT176_hf->Divide(hnum176_hf, hden_hf);
  hT200_hf->Divide(hnum200_hf, hden_hf);
  hT36_hf->Write();
  hT52_hf->Write();
  hT68_hf->Write();
  hT92_hf->Write();
  hT128_hf->Write();
  hT176_hf->Write();
  hT200_hf->Write();
  hnum36_hf->Write();
  hnum52_hf->Write();
  hnum68_hf->Write();
  hnum92_hf->Write();
  hnum128_hf->Write();
  hnum176_hf->Write();
  hnum200_hf->Write();
  hden_hf->Write();

  hT36_hf_WAC->Divide(hnum36_hf_WAC, hden_hf_WAC);
  hT52_hf_WAC->Divide(hnum52_hf_WAC, hden_hf_WAC);
  hT68_hf_WAC->Divide(hnum68_hf_WAC, hden_hf_WAC);
  hT92_hf_WAC->Divide(hnum92_hf_WAC, hden_hf_WAC);
  hT128_hf_WAC->Divide(hnum128_hf_WAC, hden_hf_WAC);
  hT176_hf_WAC->Divide(hnum176_hf_WAC, hden_hf_WAC);
  hT200_hf_WAC->Divide(hnum200_hf_WAC, hden_hf_WAC);
  hT36_hf_WAC->Write();
  hT52_hf_WAC->Write();
  hT68_hf_WAC->Write();
  hT92_hf_WAC->Write();
  hT128_hf_WAC->Write();
  hT176_hf_WAC->Write();
  hT200_hf_WAC->Write();
  hnum36_hf_WAC->Write();
  hnum52_hf_WAC->Write();
  hnum68_hf_WAC->Write();
  hnum92_hf_WAC->Write();
  hnum128_hf_WAC->Write();
  hnum176_hf_WAC->Write();
  hnum200_hf_WAC->Write();
  hden_hf_WAC->Write();

}//closes the 'main' function