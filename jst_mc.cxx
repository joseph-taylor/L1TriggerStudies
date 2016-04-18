#include "TFile.h"
#include "TTree.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TBranch.h"
#include "TChain.h"
#include <iostream>
#include <sstream>
#include <math.h>
#include <vector>
#include <string>

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
//#include "L1Trigger/L1TNtuples/interface/L1AnalysisRecoJetDataFormat.h"
//#include "L1Trigger/L1TNtuples/interface/L1AnalysisRecoClusterDataFormat.h"
//#include "L1Trigger/L1TNtuples/interface/L1AnalysisRecoMuonDataFormat.h"
//#include "L1Trigger/L1TNtuples/interface/L1AnalysisRecoRpcHitDataFormat.h"
#include "L1Trigger/L1TNtuples/interface/L1AnalysisL1ExtraDataFormat.h"
//#include "L1Trigger/L1TNtuples/interface/L1AnalysisRecoVertexDataFormat.h"
//#include "L1Trigger/L1TNtuples/interface/L1AnalysisRecoTrackDataFormat.h"
//#include "L1Trigger/L1TNtuples/interface/L1AnalysisL1MenuDataFormat.h"
#include "L1Trigger/L1TNtuples/interface/L1AnalysisL1UpgradeDataFormat.h"
//#include "L1Trigger/L1TNtuples/interface/L1AnalysisL1CaloTowerDataFormat.h"
//#include "L1Trigger/L1TNtuples/interface/L1AnalysisCaloTPDataFormat.h"
//#include "L1Trigger/L1TNtuples/interface/L1AnalysisRecoMetFilterDataFormat.h"

//user defined functions
double calc_dPHI(double phi1, double phi2);
double calc_dETA(double eta1, double eta2);
double calc_dR(double dPhi, double dEta);

//Jet structure (use for trigger and reco)
struct Jet{
  vector<float> et;
  vector<float> eta;
  vector<float> phi;
  UInt_t n;
  vector<short> bx;
};  

/////////////////
/////////////////
//MAIN FUNCTION//
/////////////////
/////////////////
void jst_mc(int JST){

 //if (JST!=0 && JST!=2 && JST!=3 && JST!=4 && JST!=5 && JST!=6 && JST!=8 && JST!=10){
 if (JST!=2 && JST!=3 && JST!=4 && JST!=5 && JST!=6){ 
  cout << "TERMINATE: you entered a jetSeedThreshold of: " << JST << endl;
  cout << "This does not correspond to a jetSeedThresholdValue we have data for" << endl << endl;
  return;
 }

 string JSTstring;
 stringstream convert;
 convert << JST;
 JSTstring = convert.str();

 //create a ROOT file to save all the histograms to (actually at end of script)
 //first check the file doesn't exist already so we don't overwrite
 string outputFilename = "output_jst/run259721_zeroBiasReReco_intv14p0Layer1_noL1JEC_jst5/comparison_jetSeedThreshold_" + JSTstring + "GeV.root";
 TFile *kk = TFile::Open( outputFilename.c_str() );
 if (kk!=0){
 cout << "TERMINATE:not going to overwrite file " << outputFilename << endl << endl;
 return;
 }


 //If the input is many .root files 
 //load the TTrees (as TChains)
 //nb: we can use wildcards
 TChain * mcTree = new TChain("l1ExtraTreeGenAk4/L1ExtraTree");
 TChain * upgradeTree = new TChain("l1UpgradeEmuTree/L1UpgradeTree");
 TChain * puTree = new TChain("puInfo/PileupInfo");

  string inputFilename = "/hdfs/L1JEC/CMSSW_8_0_2/L1JetEnergyCorrections/Stage2_HF_QCDFall15_16Mar_int-v14_layer1_noL1JEC_jst"
                         + JSTstring + "_RAWONLY/QCDFlatFall15PU0to50NzshcalRaw/L1Ntuple_Stage2_Fall15MC_HF_layer1_noL1Jec_80X_mcRun2_asymptotic_v6_jst"
                         + JSTstring + "_*.root";

  mcTree->Add( inputFilename.c_str() );
  upgradeTree->Add( inputFilename.c_str() );
  puTree->Add( inputFilename.c_str() );
 }





 Int_t nevent = (Int_t)mcTree->GetEntries();
 int numPUVertices = 0;
 puTree->SetBranchAddress("NumPUVertices", &numPUVertices);
 /////////////////////////////
 //PARAMETERS FOR THE SCRIPT//
 /////////////////////////////
 const double genJet_ETmin = 10;                 //min ET(GeV) for genjet to be considered
 const double dR_matchMax = 0.40;                //max dR allowed for a turnOn 'match'

 /////////////////////////
 //Structures for script//
 /////////////////////////
  struct Jet genjet; 
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

 L1Analysis::L1AnalysisL1ExtraDataFormat      *genJet_ = new L1Analysis::L1AnalysisL1ExtraDataFormat();
 mcTree->SetBranchAddress("L1Extra", &genJet_);

 L1Analysis::L1AnalysisL1UpgradeDataFormat    *upgrade_ = new L1Analysis::L1AnalysisL1UpgradeDataFormat();
 upgradeTree->SetBranchAddress("L1Upgrade", &upgrade_);

 //create the framework for the histograms
 //createHistogramFramework();
 //turnOn histos (pt thresholds of 20,25,30,35,40)
 //nb: num=numerator, den=denominator. At the bottom of script we create efficiency 'histos'

 //central:PU=0-10
 TH1F * hden_central_PU_0_10 = new TH1F("hden_central_PU_0_10", "", 40, 0, 200);
 TH1F * hNum_pt10_central_PU_0_10 = new TH1F("hNum_pt10_central_PU_0_10", "", 40, 0, 200);
 TH1F * hEff_pt10_central_PU_0_10 = new TH1F("hEff_pt10_central_PU_0_10", ";GenJet E_{T} (GeV);efficiency", 40, 0, 200); 
 TH1F * hNum_pt15_central_PU_0_10 = new TH1F("hNum_pt15_central_PU_0_10", "", 40, 0, 200);
 TH1F * hEff_pt15_central_PU_0_10 = new TH1F("hEff_pt15_central_PU_0_10", ";GenJet E_{T} (GeV);efficiency", 40, 0, 200); 
 TH1F * hNum_pt20_central_PU_0_10 = new TH1F("hNum_pt20_central_PU_0_10", "", 40, 0, 200);
 TH1F * hEff_pt20_central_PU_0_10 = new TH1F("hEff_pt20_central_PU_0_10", ";GenJet E_{T} (GeV);efficiency", 40, 0, 200); 
 TH1F * hNum_pt25_central_PU_0_10 = new TH1F("hNum_pt25_central_PU_0_10", "", 40, 0, 200);
 TH1F * hEff_pt25_central_PU_0_10 = new TH1F("hEff_pt25_central_PU_0_10", ";GenJet E_{T} (GeV);efficiency", 40, 0, 200); 
 TH1F * hNum_pt30_central_PU_0_10 = new TH1F("hNum_pt30_central_PU_0_10", "", 40, 0, 200);
 TH1F * hEff_pt30_central_PU_0_10 = new TH1F("hEff_pt30_central_PU_0_10", ";GenJet E_{T} (GeV);efficiency", 40, 0, 200); 


//central:PU=15-25
 TH1F * hden_central_PU_15_25 = new TH1F("hden_central_PU_15_25", "", 40, 0, 200);
 TH1F * hNum_pt10_central_PU_15_25 = new TH1F("hNum_pt10_central_PU_15_25", "", 40, 0, 200);
 TH1F * hEff_pt10_central_PU_15_25 = new TH1F("hEff_pt10_central_PU_15_25", ";GenJet E_{T} (GeV);efficiency", 40, 0, 200); 
 TH1F * hNum_pt15_central_PU_15_25 = new TH1F("hNum_pt15_central_PU_15_25", "", 40, 0, 200);
 TH1F * hEff_pt15_central_PU_15_25 = new TH1F("hEff_pt15_central_PU_15_25", ";GenJet E_{T} (GeV);efficiency", 40, 0, 200);
 TH1F * hNum_pt20_central_PU_15_25 = new TH1F("hNum_pt20_central_PU_15_25", "", 40, 0, 200);
 TH1F * hEff_pt20_central_PU_15_25 = new TH1F("hEff_pt20_central_PU_15_25", ";GenJet E_{T} (GeV);efficiency", 40, 0, 200); 
 TH1F * hNum_pt25_central_PU_15_25 = new TH1F("hNum_pt25_central_PU_15_25", "", 40, 0, 200);
 TH1F * hEff_pt25_central_PU_15_25 = new TH1F("hEff_pt25_central_PU_15_25", ";GenJet E_{T} (GeV);efficiency", 40, 0, 200); 
 TH1F * hNum_pt30_central_PU_15_25 = new TH1F("hNum_pt30_central_PU_15_25", "", 40, 0, 200);
 TH1F * hEff_pt30_central_PU_15_25 = new TH1F("hEff_pt30_central_PU_15_25", ";GenJet E_{T} (GeV);efficiency", 40, 0, 200); 


//central:PU=30-40
 TH1F * hden_central_PU_30_40 = new TH1F("hden_central_PU_30_40", "", 40, 0, 200);
 TH1F * hNum_pt10_central_PU_30_40 = new TH1F("hNum_pt10_central_PU_30_40", "", 40, 0, 200);
 TH1F * hEff_pt10_central_PU_30_40 = new TH1F("hEff_pt10_central_PU_30_40", ";GenJet E_{T} (GeV);efficiency", 40, 0, 200); 
 TH1F * hNum_pt15_central_PU_30_40 = new TH1F("hNum_pt15_central_PU_30_40", "", 40, 0, 200);
 TH1F * hEff_pt15_central_PU_30_40 = new TH1F("hEff_pt15_central_PU_30_40", ";GenJet E_{T} (GeV);efficiency", 40, 0, 200);
 TH1F * hNum_pt20_central_PU_30_40 = new TH1F("hNum_pt20_central_PU_30_40", "", 40, 0, 200);
 TH1F * hEff_pt20_central_PU_30_40 = new TH1F("hEff_pt20_central_PU_30_40", ";GenJet E_{T} (GeV);efficiency", 40, 0, 200); 
 TH1F * hNum_pt25_central_PU_30_40 = new TH1F("hNum_pt25_central_PU_30_40", "", 40, 0, 200);
 TH1F * hEff_pt25_central_PU_30_40 = new TH1F("hEff_pt25_central_PU_30_40", ";GenJet E_{T} (GeV);efficiency", 40, 0, 200); 
 TH1F * hNum_pt30_central_PU_30_40 = new TH1F("hNum_pt30_central_PU_30_40", "", 40, 0, 200);
 TH1F * hEff_pt30_central_PU_30_40 = new TH1F("hEff_pt30_central_PU_30_40", ";GenJet E_{T} (GeV);efficiency", 40, 0, 200); 


 //hf:PU=0-10
 TH1F * hden_hf_PU_0_10 = new TH1F("hden_hf_PU_0_10", "", 40, 0, 200);
 TH1F * hNum_pt10_hf_PU_0_10 = new TH1F("hNum_pt10_hf_PU_0_10", "", 40, 0, 200);
 TH1F * hEff_pt10_hf_PU_0_10 = new TH1F("hEff_pt10_hf_PU_0_10", ";GenJet E_{T} (GeV);efficiency", 40, 0, 200); 
 TH1F * hNum_pt15_hf_PU_0_10 = new TH1F("hNum_pt15_hf_PU_0_10", "", 40, 0, 200);
 TH1F * hEff_pt15_hf_PU_0_10 = new TH1F("hEff_pt15_hf_PU_0_10", ";GenJet E_{T} (GeV);efficiency", 40, 0, 200); 
 TH1F * hNum_pt20_hf_PU_0_10 = new TH1F("hNum_pt20_hf_PU_0_10", "", 40, 0, 200);
 TH1F * hEff_pt20_hf_PU_0_10 = new TH1F("hEff_pt20_hf_PU_0_10", ";GenJet E_{T} (GeV);efficiency", 40, 0, 200); 
 TH1F * hNum_pt25_hf_PU_0_10 = new TH1F("hNum_pt25_hf_PU_0_10", "", 40, 0, 200);
 TH1F * hEff_pt25_hf_PU_0_10 = new TH1F("hEff_pt25_hf_PU_0_10", ";GenJet E_{T} (GeV);efficiency", 40, 0, 200); 
 TH1F * hNum_pt30_hf_PU_0_10 = new TH1F("hNum_pt30_hf_PU_0_10", "", 40, 0, 200);
 TH1F * hEff_pt30_hf_PU_0_10 = new TH1F("hEff_pt30_hf_PU_0_10", ";GenJet E_{T} (GeV);efficiency", 40, 0, 200); 


 //hf:PU=15-25
 TH1F * hden_hf_PU_15_25 = new TH1F("hden_hf_PU_15_25", "", 40, 0, 200);
 TH1F * hNum_pt10_hf_PU_15_25 = new TH1F("hNum_pt10_hf_PU_15_25", "", 40, 0, 200);
 TH1F * hEff_pt10_hf_PU_15_25 = new TH1F("hEff_pt10_hf_PU_15_25", ";GenJet E_{T} (GeV);efficiency", 40, 0, 200); 
 TH1F * hNum_pt15_hf_PU_15_25 = new TH1F("hNum_pt15_hf_PU_15_25", "", 40, 0, 200);
 TH1F * hEff_pt15_hf_PU_15_25 = new TH1F("hEff_pt15_hf_PU_15_25", ";GenJet E_{T} (GeV);efficiency", 40, 0, 200);
 TH1F * hNum_pt20_hf_PU_15_25 = new TH1F("hNum_pt20_hf_PU_15_25", "", 40, 0, 200);
 TH1F * hEff_pt20_hf_PU_15_25 = new TH1F("hEff_pt20_hf_PU_15_25", ";GenJet E_{T} (GeV);efficiency", 40, 0, 200); 
 TH1F * hNum_pt25_hf_PU_15_25 = new TH1F("hNum_pt25_hf_PU_15_25", "", 40, 0, 200);
 TH1F * hEff_pt25_hf_PU_15_25 = new TH1F("hEff_pt25_hf_PU_15_25", ";GenJet E_{T} (GeV);efficiency", 40, 0, 200); 
 TH1F * hNum_pt30_hf_PU_15_25 = new TH1F("hNum_pt30_hf_PU_15_25", "", 40, 0, 200);
 TH1F * hEff_pt30_hf_PU_15_25 = new TH1F("hEff_pt30_hf_PU_15_25", ";GenJet E_{T} (GeV);efficiency", 40, 0, 200); 


//hf:PU=30-40
 TH1F * hden_hf_PU_30_40 = new TH1F("hden_hf_PU_30_40", "", 40, 0, 200);
 TH1F * hNum_pt10_hf_PU_30_40 = new TH1F("hNum_pt10_hf_PU_30_40", "", 40, 0, 200);
 TH1F * hEff_pt10_hf_PU_30_40 = new TH1F("hEff_pt10_hf_PU_30_40", ";GenJet E_{T} (GeV);efficiency", 40, 0, 200); 
 TH1F * hNum_pt15_hf_PU_30_40 = new TH1F("hNum_pt15_hf_PU_30_40", "", 40, 0, 200);
 TH1F * hEff_pt15_hf_PU_30_40 = new TH1F("hEff_pt15_hf_PU_30_40", ";GenJet E_{T} (GeV);efficiency", 40, 0, 200);
 TH1F * hNum_pt20_hf_PU_30_40 = new TH1F("hNum_pt20_hf_PU_30_40", "", 40, 0, 200);
 TH1F * hEff_pt20_hf_PU_30_40 = new TH1F("hEff_pt20_hf_PU_30_40", ";GenJet E_{T} (GeV);efficiency", 40, 0, 200); 
 TH1F * hNum_pt25_hf_PU_30_40 = new TH1F("hNum_pt25_hf_PU_30_40", "", 40, 0, 200);
 TH1F * hEff_pt25_hf_PU_30_40 = new TH1F("hEff_pt25_hf_PU_30_40", ";GenJet E_{T} (GeV);efficiency", 40, 0, 200); 
 TH1F * hNum_pt30_hf_PU_30_40 = new TH1F("hNum_pt30_hf_PU_30_40", "", 40, 0, 200);
 TH1F * hEff_pt30_hf_PU_30_40 = new TH1F("hEff_pt30_hf_PU_30_40", ";GenJet E_{T} (GeV);efficiency", 40, 0, 200); 


 //Energy Scatter Histograms
 TH2F * hETS_central_PU_0_10 = new TH2F("hETS_central_PU_0_10", "", 500, 0, 250, 500, 0, 250);
 hETS_central_PU_0_10->GetXaxis()->SetTitle("GenJet E_{T} (GeV)");
 hETS_central_PU_0_10->GetYaxis()->SetTitle("L1 E_{T} (GeV)");

 TH2F * hETS_central_PU_15_25 = new TH2F("hETS_central_PU_15_25", "", 500, 0, 250, 500, 0, 250);
 hETS_central_PU_15_25->GetXaxis()->SetTitle("GenJet E_{T} (GeV)");
 hETS_central_PU_15_25->GetYaxis()->SetTitle("L1 E_{T} (GeV)");

 TH2F * hETS_central_PU_30_40 = new TH2F("hETS_central_PU_30_40", "", 500, 0, 250, 500, 0, 250);
 hETS_central_PU_30_40->GetXaxis()->SetTitle("GenJet E_{T} (GeV)");
 hETS_central_PU_30_40->GetYaxis()->SetTitle("L1 E_{T} (GeV)");

 TH2F * hETS_hf_PU_0_10 = new TH2F("hETS_hf_PU_0_10", "", 500, 0, 250, 500, 0, 250);
 hETS_hf_PU_0_10->GetXaxis()->SetTitle("GenJet E_{T} (GeV)");
 hETS_hf_PU_0_10->GetYaxis()->SetTitle("L1 E_{T} (GeV)");

 TH2F * hETS_hf_PU_15_25 = new TH2F("hETS_hf_PU_15_25", "", 500, 0, 250, 500, 0, 250);
 hETS_hf_PU_15_25->GetXaxis()->SetTitle("GenJet E_{T} (GeV)");
 hETS_hf_PU_15_25->GetYaxis()->SetTitle("L1 E_{T} (GeV)");

 TH2F * hETS_hf_PU_30_40 = new TH2F("hETS_hf_PU_30_40", "", 500, 0, 250, 500, 0, 250);
 hETS_hf_PU_30_40->GetXaxis()->SetTitle("GenJet E_{T} (GeV)");
 hETS_hf_PU_30_40->GetYaxis()->SetTitle("L1 E_{T} (GeV)");


 ///////////////////////////////
 ///////////////////////////////
 //loop through all the events//
 ///////////////////////////////
 ///////////////////////////////
 //just to keep it ~lightweight for now
 if (nevent>1000000){nevent=1000000;}

 for (Int_t i=0; i<nevent; i++){
			  
   int nb = mcTree->GetEntry(i);
   if (nb==0){
    cout << "did not load l1ExtraTreeGenAk4/L1ExtraTree for entry " << i << endl;
    return;}
   nb = upgradeTree->GetEntry(i);
   if (nb==0){
    cout << "did not load L1UpgradeTree for entry " << i << endl;
    return;}                
   nb =puTree->GetEntry(i);
   if (nb==0){
    cout << "did not load PileupInfo ttree for entry " << i << endl;
    return;}                 
   //////////////////////////////////////
   ///analysis///////////////////////////
   //////////////////////////////////////
   //all mc jets (even hf) stored in 'central'
   genjet.et = genJet_->cenJetEt;
   genjet.eta = genJet_->cenJetEta;
   genjet.phi = genJet_->cenJetPhi;
   genjet.n = genJet_->nCenJets;

   l1jet.et = upgrade_->jetEt;
   l1jet.eta = upgrade_->jetEta;
   l1jet.phi = upgrade_->jetPhi;
   l1jet.n = upgrade_->nJets;
   l1jet.bx = upgrade_->jetBx;


   //need to find the leading central jet
   //need to find the leading hf jet
   int leading_central_index = 0;
   int leading_hf_index = 0;
   bool haveCentralJet = false;
   bool haveHFJet = false;
   for (UInt_t j=0; j<genjet.n; j++){

    if (haveCentralJet==false && fabs(genjet.eta[j]<3.0)){
      leading_central_index = j;
      haveCentralJet = true;
    }
    if (haveHFJet==false && fabs(genjet.eta[j])>3.5 && fabs(genjet.eta[j])<4.5){
      leading_hf_index = j;
      haveHFJet = true; 
    }
   }


    //------------------------------------------------------------------------------------------------------------//
    /////////////////////
    //Barrel and Endcap//
    /////////////////////
    //is the leading central genJet above a given threshold (10GeV)
    if (haveCentralJet && genjet.et[leading_central_index] > genJet_ETmin){
      
      //loop through the Upgrade Jets to find
      //the best matching to the genJet in question (in terms of dR)
      double dR_min=99999.99;        //use to determine the best match jet
      UInt_t k_min=9999;             //use to index the best match jet
      int countL1=0;                 //use this quantity as bx may be zero for some l1 jets
      for (UInt_t k=0; k<l1jet.n; k++){
        if(l1jet.bx[k]==0){
          countL1++;
          double dPhi = calc_dPHI(genjet.phi[leading_central_index],l1jet.phi[k]);
          double dEta = calc_dETA(genjet.eta[leading_central_index],l1jet.eta[k]);   
          double dR = calc_dR(dPhi,dEta);
          if (countL1==0){dR_min = dR; k_min = k;}
          if (countL1>0 && dR<dR_min){dR_min = dR; k_min = k;}
        }
      }
    
     //plot comparison histograms for 'central' info about our best match
     if (l1jet.n > 0){       
       if (numPUVertices<=10){hETS_central_PU_0_10->Fill(genjet.et[leading_central_index],l1jet.et[k_min]);}
       if (numPUVertices>=15 && numPUVertices<=25){hETS_central_PU_15_25->Fill(genjet.et[leading_central_index],l1jet.et[k_min]);}
       if (numPUVertices>=30 && numPUVertices<=40){hETS_central_PU_30_40->Fill(genjet.et[leading_central_index],l1jet.et[k_min]);}
      }

      //now make the trigger turnOns for 'central'
      if (numPUVertices<=10){hden_central_PU_0_10->Fill(genjet.et[leading_central_index]);}
      if (numPUVertices>=15 && numPUVertices<=25){hden_central_PU_15_25->Fill(genjet.et[leading_central_index]);}
      if (numPUVertices>=30 && numPUVertices<=40){hden_central_PU_30_40->Fill(genjet.et[leading_central_index]);}
      if (dR_min < dR_matchMax){

        if (l1jet.et[k_min]>10){
          if (numPUVertices<=10){hNum_pt10_central_PU_0_10->Fill(genjet.et[leading_central_index]);}
          if (numPUVertices>=15 && numPUVertices<=25){hNum_pt10_central_PU_15_25->Fill(genjet.et[leading_central_index]);}
          if (numPUVertices>=30 && numPUVertices<=40){hNum_pt10_central_PU_30_40->Fill(genjet.et[leading_central_index]);}
        }      

        if (l1jet.et[k_min]>15){
          if (numPUVertices<=10){hNum_pt15_central_PU_0_10->Fill(genjet.et[leading_central_index]);}
          if (numPUVertices>=15 && numPUVertices<=25){hNum_pt15_central_PU_15_25->Fill(genjet.et[leading_central_index]);}
          if (numPUVertices>=30 && numPUVertices<=40){hNum_pt15_central_PU_30_40->Fill(genjet.et[leading_central_index]);}
        } 
        
        if (l1jet.et[k_min]>20){
          if (numPUVertices<=10){hNum_pt20_central_PU_0_10->Fill(genjet.et[leading_central_index]);}
          if (numPUVertices>=15 && numPUVertices<=25){hNum_pt20_central_PU_15_25->Fill(genjet.et[leading_central_index]);}
          if (numPUVertices>=30 && numPUVertices<=40){hNum_pt20_central_PU_30_40->Fill(genjet.et[leading_central_index]);}
        }   

        if (l1jet.et[k_min]>25){
          if (numPUVertices<=10){hNum_pt25_central_PU_0_10->Fill(genjet.et[leading_central_index]);}
          if (numPUVertices>=15 && numPUVertices<=25){hNum_pt25_central_PU_15_25->Fill(genjet.et[leading_central_index]);}
          if (numPUVertices>=30 && numPUVertices<=40){hNum_pt25_central_PU_30_40->Fill(genjet.et[leading_central_index]);}
        }   

        if (l1jet.et[k_min]>30){
          if (numPUVertices<=10){hNum_pt30_central_PU_0_10->Fill(genjet.et[leading_central_index]);}
          if (numPUVertices>=15 && numPUVertices<=25){hNum_pt30_central_PU_15_25->Fill(genjet.et[leading_central_index]);}
          if (numPUVertices>=30 && numPUVertices<=40){hNum_pt30_central_PU_30_40->Fill(genjet.et[leading_central_index]);}
        }       

      }//closes 'if' upgrade jet matches to the genJet in dR
    }//closes 'if' genJet central and above threshold et
    //------------------------------------------------------------------------------------------------------------//



    //------------------------------------------------------------------------------------------------------------//
    /////////////////////
    //  H  F  ///////////
    /////////////////////
    //is the leading hf genJet above a given threshold (10GeV)
    if (haveHFJet && genjet.et[leading_hf_index] > genJet_ETmin){
      
      //loop through the Upgrade Jets to find
      //the best matching to the genJet in question (in terms of dR)
      double dR_min=99999.99;        //use to determine the best match jet
      UInt_t k_min=9999;             //use to index the best match jet
      int countL1=0;                 //use this quantity as bx may be zero for some l1 jets
      for (UInt_t k=0; k<l1jet.n; k++){
        if(l1jet.bx[k]==0){
          double dPhi = calc_dPHI(genjet.phi[leading_hf_index],l1jet.phi[k]);
          double dEta = calc_dETA(genjet.eta[leading_hf_index],l1jet.eta[k]);   
          double dR = calc_dR( dPhi, dEta);
          if (countL1==0){dR_min = dR; k_min = k;}
          if (countL1>0 && dR<dR_min){dR_min = dR; k_min = k;}
        }
      }
    
     //plot comparison histograms for 'hf' info about our best match
     if (l1jet.n > 0){       
       if (numPUVertices<=10){hETS_hf_PU_0_10->Fill(genjet.et[leading_hf_index],l1jet.et[k_min]);}
       if (numPUVertices>=15 && numPUVertices<=25){hETS_hf_PU_15_25->Fill(genjet.et[leading_hf_index],l1jet.et[k_min]);}
       if (numPUVertices>=30 && numPUVertices<=40){hETS_hf_PU_30_40->Fill(genjet.et[leading_hf_index],l1jet.et[k_min]);}
      }

      //now make the trigger turnOns for 'hf'
      if (numPUVertices<=10){hden_hf_PU_0_10->Fill(genjet.et[leading_hf_index]);}
      if (numPUVertices>=15 && numPUVertices<=25){hden_hf_PU_15_25->Fill(genjet.et[leading_hf_index]);}
      if (numPUVertices>=30 && numPUVertices<=40){hden_hf_PU_30_40->Fill(genjet.et[leading_hf_index]);}
      if (dR_min < dR_matchMax){
        
        if (l1jet.et[k_min]>10){
          if (numPUVertices<=10){hNum_pt10_hf_PU_0_10->Fill(genjet.et[leading_hf_index]);}
          if (numPUVertices>=15 && numPUVertices<=25){hNum_pt10_hf_PU_15_25->Fill(genjet.et[leading_hf_index]);}
          if (numPUVertices>=30 && numPUVertices<=40){hNum_pt10_hf_PU_30_40->Fill(genjet.et[leading_hf_index]);}
        }      

        if (l1jet.et[k_min]>15){
          if (numPUVertices<=10){hNum_pt15_hf_PU_0_10->Fill(genjet.et[leading_hf_index]);}
          if (numPUVertices>=15 && numPUVertices<=25){hNum_pt15_hf_PU_15_25->Fill(genjet.et[leading_hf_index]);}
          if (numPUVertices>=30 && numPUVertices<=40){hNum_pt15_hf_PU_30_40->Fill(genjet.et[leading_hf_index]);}
        }    

        if (l1jet.et[k_min]>20){
          if (numPUVertices<=10){hNum_pt20_hf_PU_0_10->Fill(genjet.et[leading_hf_index]);}
          if (numPUVertices>=15 && numPUVertices<=25){hNum_pt20_hf_PU_15_25->Fill(genjet.et[leading_hf_index]);}
          if (numPUVertices>=30 && numPUVertices<=40){hNum_pt20_hf_PU_30_40->Fill(genjet.et[leading_hf_index]);}
        }   

        if (l1jet.et[k_min]>25){
          if (numPUVertices<=10){hNum_pt25_hf_PU_0_10->Fill(genjet.et[leading_hf_index]);}
          if (numPUVertices>=15 && numPUVertices<=25){hNum_pt25_hf_PU_15_25->Fill(genjet.et[leading_hf_index]);}
          if (numPUVertices>=30 && numPUVertices<=40){hNum_pt25_hf_PU_30_40->Fill(genjet.et[leading_hf_index]);}
        }   

        if (l1jet.et[k_min]>30){
          if (numPUVertices<=10){hNum_pt30_hf_PU_0_10->Fill(genjet.et[leading_hf_index]);}
          if (numPUVertices>=15 && numPUVertices<=25){hNum_pt30_hf_PU_15_25->Fill(genjet.et[leading_hf_index]);}
          if (numPUVertices>=30 && numPUVertices<=40){hNum_pt30_hf_PU_30_40->Fill(genjet.et[leading_hf_index]);}
        }    

      }//closes 'if' upgrade jet matches to the genJet in dR
    }//closes 'if' genJet hf and above threshold et
    //------------------------------------------------------------------------------------------------------------//



   if (i % 10000 == 0){
	 cout << i << " out of " << nevent << " events for JST=" << JST << "GeV" << endl;}		
  }//closes loop through the events

 //save the output ROOT file
 TFile g( outputFilename.c_str() , "new");
 //write the histograms (and do the divisions)
 //central:PU=10-15
 hEff_pt10_central_PU_0_10->Divide(hNum_pt10_central_PU_0_10, hden_central_PU_0_10);
 hEff_pt15_central_PU_0_10->Divide(hNum_pt15_central_PU_0_10, hden_central_PU_0_10);
 hEff_pt20_central_PU_0_10->Divide(hNum_pt20_central_PU_0_10, hden_central_PU_0_10);
 hEff_pt25_central_PU_0_10->Divide(hNum_pt25_central_PU_0_10, hden_central_PU_0_10);
 hEff_pt30_central_PU_0_10->Divide(hNum_pt30_central_PU_0_10, hden_central_PU_0_10);
 hden_central_PU_0_10->Write();
 hNum_pt10_central_PU_0_10->Write();
 hEff_pt10_central_PU_0_10->Write();
 hNum_pt15_central_PU_0_10->Write();
 hEff_pt15_central_PU_0_10->Write();
 hNum_pt20_central_PU_0_10->Write();
 hEff_pt20_central_PU_0_10->Write();
 hNum_pt25_central_PU_0_10->Write();
 hEff_pt25_central_PU_0_10->Write();
 hNum_pt30_central_PU_0_10->Write();
 hEff_pt30_central_PU_0_10->Write();


 //central:PU=15-25
 hEff_pt10_central_PU_15_25->Divide(hNum_pt10_central_PU_15_25, hden_central_PU_15_25);
 hEff_pt15_central_PU_15_25->Divide(hNum_pt15_central_PU_15_25, hden_central_PU_15_25);
 hEff_pt20_central_PU_15_25->Divide(hNum_pt20_central_PU_15_25, hden_central_PU_15_25);
 hEff_pt25_central_PU_15_25->Divide(hNum_pt25_central_PU_15_25, hden_central_PU_15_25);
 hEff_pt30_central_PU_15_25->Divide(hNum_pt30_central_PU_15_25, hden_central_PU_15_25);
 hden_central_PU_15_25->Write();
 hNum_pt10_central_PU_15_25->Write();
 hEff_pt10_central_PU_15_25->Write();
 hNum_pt15_central_PU_15_25->Write();
 hEff_pt15_central_PU_15_25->Write();
 hNum_pt20_central_PU_15_25->Write();
 hEff_pt20_central_PU_15_25->Write();
 hNum_pt25_central_PU_15_25->Write();
 hEff_pt25_central_PU_15_25->Write();
 hNum_pt30_central_PU_15_25->Write();
 hEff_pt30_central_PU_15_25->Write();


 //central:PU=30-40
 hEff_pt10_central_PU_30_40->Divide(hNum_pt10_central_PU_30_40, hden_central_PU_30_40);
 hEff_pt15_central_PU_30_40->Divide(hNum_pt15_central_PU_30_40, hden_central_PU_30_40);
 hEff_pt20_central_PU_30_40->Divide(hNum_pt20_central_PU_30_40, hden_central_PU_30_40);
 hEff_pt25_central_PU_30_40->Divide(hNum_pt25_central_PU_30_40, hden_central_PU_30_40);
 hEff_pt30_central_PU_30_40->Divide(hNum_pt30_central_PU_30_40, hden_central_PU_30_40);
 hden_central_PU_30_40->Write();
 hNum_pt10_central_PU_30_40->Write();
 hEff_pt10_central_PU_30_40->Write();
 hNum_pt15_central_PU_30_40->Write();
 hEff_pt15_central_PU_30_40->Write();
 hNum_pt20_central_PU_30_40->Write();
 hEff_pt20_central_PU_30_40->Write();
 hNum_pt25_central_PU_30_40->Write();
 hEff_pt25_central_PU_30_40->Write(); 
 hNum_pt30_central_PU_30_40->Write();
 hEff_pt30_central_PU_30_40->Write();


 //hf:PU=0-10
 hEff_pt10_hf_PU_0_10->Divide(hNum_pt10_hf_PU_0_10, hden_hf_PU_0_10);
 hEff_pt15_hf_PU_0_10->Divide(hNum_pt15_hf_PU_0_10, hden_hf_PU_0_10);
 hEff_pt20_hf_PU_0_10->Divide(hNum_pt20_hf_PU_0_10, hden_hf_PU_0_10);
 hEff_pt25_hf_PU_0_10->Divide(hNum_pt25_hf_PU_0_10, hden_hf_PU_0_10);
 hEff_pt30_hf_PU_0_10->Divide(hNum_pt30_hf_PU_0_10, hden_hf_PU_0_10);
 hden_hf_PU_0_10->Write();
 hNum_pt10_hf_PU_0_10->Write();
 hEff_pt10_hf_PU_0_10->Write();
 hNum_pt15_hf_PU_0_10->Write();
 hEff_pt15_hf_PU_0_10->Write();
 hNum_pt20_hf_PU_0_10->Write();
 hEff_pt20_hf_PU_0_10 ->Write();
 hNum_pt25_hf_PU_0_10->Write();
 hEff_pt25_hf_PU_0_10->Write();
 hNum_pt30_hf_PU_0_10->Write();
 hEff_pt30_hf_PU_0_10->Write();


 //hf:PU=15-25
 hEff_pt10_hf_PU_15_25->Divide(hNum_pt10_hf_PU_15_25, hden_hf_PU_15_25);
 hEff_pt15_hf_PU_15_25->Divide(hNum_pt15_hf_PU_15_25, hden_hf_PU_15_25);
 hEff_pt20_hf_PU_15_25->Divide(hNum_pt20_hf_PU_15_25, hden_hf_PU_15_25);
 hEff_pt25_hf_PU_15_25->Divide(hNum_pt25_hf_PU_15_25, hden_hf_PU_15_25);
 hEff_pt30_hf_PU_15_25->Divide(hNum_pt30_hf_PU_15_25, hden_hf_PU_15_25);
 hden_hf_PU_15_25->Write();
 hNum_pt10_hf_PU_15_25->Write();
 hEff_pt10_hf_PU_15_25->Write();
 hNum_pt15_hf_PU_15_25->Write();
 hEff_pt15_hf_PU_15_25->Write();
 hNum_pt20_hf_PU_15_25->Write();
 hEff_pt20_hf_PU_15_25->Write(); 
 hNum_pt25_hf_PU_15_25->Write();
 hEff_pt25_hf_PU_15_25->Write(); 
 hNum_pt30_hf_PU_15_25->Write();
 hEff_pt30_hf_PU_15_25->Write(); 


 //hf:PU=30-40
 hEff_pt10_hf_PU_30_40->Divide(hNum_pt10_hf_PU_30_40, hden_hf_PU_30_40);
 hEff_pt15_hf_PU_30_40->Divide(hNum_pt15_hf_PU_30_40, hden_hf_PU_30_40);
 hEff_pt20_hf_PU_30_40->Divide(hNum_pt20_hf_PU_30_40, hden_hf_PU_30_40);
 hEff_pt25_hf_PU_30_40->Divide(hNum_pt25_hf_PU_30_40, hden_hf_PU_30_40);
 hEff_pt30_hf_PU_30_40->Divide(hNum_pt30_hf_PU_30_40, hden_hf_PU_30_40);
 hden_hf_PU_30_40->Write();
 hNum_pt10_hf_PU_30_40->Write();
 hEff_pt10_hf_PU_30_40->Write();
 hNum_pt15_hf_PU_30_40->Write();
 hEff_pt15_hf_PU_30_40->Write();
 hNum_pt20_hf_PU_30_40->Write();
 hEff_pt20_hf_PU_30_40->Write();
 hNum_pt25_hf_PU_30_40->Write();
 hEff_pt25_hf_PU_30_40->Write();
 hNum_pt30_hf_PU_30_40->Write();
 hEff_pt30_hf_PU_30_40->Write();


//scatterHistos
 hETS_central_PU_0_10->Write();
 hETS_central_PU_15_25->Write();
 hETS_central_PU_30_40->Write();
 hETS_hf_PU_0_10->Write();
 hETS_hf_PU_15_25->Write();
 hETS_hf_PU_30_40->Write();


 //delete all the histograms
 delete hden_central_PU_0_10;
 delete hNum_pt10_central_PU_0_10;
 delete hEff_pt10_central_PU_0_10;
 delete hNum_pt15_central_PU_0_10;
 delete hEff_pt15_central_PU_0_10;
 delete hNum_pt20_central_PU_0_10;
 delete hEff_pt20_central_PU_0_10;
 delete hNum_pt25_central_PU_0_10;
 delete hEff_pt25_central_PU_0_10;
 delete hNum_pt30_central_PU_0_10;
 delete hEff_pt30_central_PU_0_10;
 delete hden_central_PU_15_25;
 delete hNum_pt10_central_PU_15_25;
 delete hEff_pt10_central_PU_15_25;
 delete hNum_pt15_central_PU_15_25;
 delete hEff_pt15_central_PU_15_25;
 delete hNum_pt20_central_PU_15_25;
 delete hEff_pt20_central_PU_15_25;
 delete hNum_pt25_central_PU_15_25;
 delete hEff_pt25_central_PU_15_25;
 delete hNum_pt30_central_PU_15_25;
 delete hEff_pt30_central_PU_15_25;
 delete hden_central_PU_30_40;
 delete hNum_pt10_central_PU_30_40;
 delete hEff_pt10_central_PU_30_40;
 delete hNum_pt15_central_PU_30_40;
 delete hEff_pt15_central_PU_30_40;
 delete hNum_pt20_central_PU_30_40;
 delete hEff_pt20_central_PU_30_40;
 delete hNum_pt25_central_PU_30_40;
 delete hEff_pt25_central_PU_30_40;
 delete hNum_pt30_central_PU_30_40;
 delete hEff_pt30_central_PU_30_40;
 delete hden_hf_PU_0_10;
 delete hNum_pt10_hf_PU_0_10;
 delete hEff_pt10_hf_PU_0_10;
 delete hNum_pt15_hf_PU_0_10;
 delete hEff_pt15_hf_PU_0_10;
 delete hNum_pt20_hf_PU_0_10;
 delete hEff_pt20_hf_PU_0_10;
 delete hNum_pt25_hf_PU_0_10;
 delete hEff_pt25_hf_PU_0_10;
 delete hNum_pt30_hf_PU_0_10;
 delete hEff_pt30_hf_PU_0_10;
 delete hden_hf_PU_15_25;
 delete hNum_pt10_hf_PU_15_25;
 delete hEff_pt10_hf_PU_15_25;
 delete hNum_pt15_hf_PU_15_25;
 delete hEff_pt15_hf_PU_15_25;
 delete hNum_pt20_hf_PU_15_25;
 delete hEff_pt20_hf_PU_15_25;
 delete hNum_pt25_hf_PU_15_25;
 delete hEff_pt25_hf_PU_15_25;
 delete hNum_pt30_hf_PU_15_25;
 delete hEff_pt30_hf_PU_15_25;
 delete hden_hf_PU_30_40;
 delete hNum_pt10_hf_PU_30_40;
 delete hEff_pt10_hf_PU_30_40;
 delete hNum_pt15_hf_PU_30_40;
 delete hEff_pt15_hf_PU_30_40;
 delete hNum_pt20_hf_PU_30_40;
 delete hEff_pt20_hf_PU_30_40;
 delete hNum_pt25_hf_PU_30_40;
 delete hEff_pt25_hf_PU_30_40;
 delete hNum_pt30_hf_PU_30_40;
 delete hEff_pt30_hf_PU_30_40;
 delete hETS_central_PU_0_10;
 delete hETS_central_PU_15_25;
 delete hETS_central_PU_30_40;
 delete hETS_hf_PU_0_10;
 delete hETS_hf_PU_15_25;
 delete hETS_hf_PU_30_40;

}//closes the 'main' function




//////////////////////////////////////
////////USER DEFINED FUNCTIONS////////
//////////////////////////////////////


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