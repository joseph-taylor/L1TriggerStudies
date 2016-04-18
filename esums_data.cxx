#include "TFile.h"
#include "TTree.h"
#include "TH1F.h"
#include "TH2F.h"
#include <iostream>
#include <math.h>
#include <vector>
#include <string>

//#include "L1AnalysisEventDataFormat.h"
//#include "L1AnalysisSimulationDataFormat.h"
//#include "L1AnalysisGCTDataFormat.h"
//#include "L1AnalysisGTDataFormat.h"
//#include "L1AnalysisGMTDataFormat.h"
//#include "L1AnalysisGTDataFormat.h"
//#include "L1AnalysisRCTDataFormat.h"
//#include "L1AnalysisDTTFDataFormat.h"
//#include "L1AnalysisCSCTFDataFormat.h"
#include "L1AnalysisRecoMetDataFormat.h"
#include "L1AnalysisRecoJetDataFormat.h"
//#include "L1AnalysisRecoClusterDataFormat.h"
#include "L1AnalysisRecoMuon2DataFormat.h"
//#include "L1AnalysisRecoRpcHitDataFormat.h"
//#include "L1AnalysisL1ExtraDataFormat.h"
//#include "L1AnalysisRecoVertexDataFormat.h"
//#include "L1AnalysisRecoTrackDataFormat.h"
//#include "L1AnalysisL1MenuDataFormat.h"
#include "L1AnalysisL1UpgradeDataFormat.h"
//#include "L1AnalysisL1CaloTowerDataFormat.h"
//#include "L1AnalysisCaloTPDataFormat.h"
#include "L1AnalysisRecoMetFilterDataFormat.h"
    

bool met_filter(Bool_t hbheNoiseFilter, Bool_t hbheNoiseIsoFilter, Bool_t cscTightHalo2015Filter, Bool_t ecalDeadCellTPFilter,
                Bool_t goodVerticesFilter, Bool_t eeBadScFilter, Bool_t chHadTrackResFilter, Bool_t muonBadTrackFilter){

  bool metPass;
  if (hbheNoiseFilter==1 && hbheNoiseIsoFilter==1 && cscTightHalo2015Filter==1 && ecalDeadCellTPFilter==1 
      && goodVerticesFilter==1 && eeBadScFilter==1 && chHadTrackResFilter==1 && muonBadTrackFilter==1){
    metPass = true;}//this met has passed
  else{metPass = false;}
  return metPass;
}






//this is wrong if using Emu tree...for hw
  // //function:input iEta and output physical Eta value
  // //NB: in reality the index will not be greater than 36*2
  // //    as the Jets are 9x9 towers and the centres are indexed
  // vector<float> getEtaVec(vector<short> iEta){
  //   vector<float> eta;
  //   const float towerIndex2phys[40] = {0.0435, 0.1305, 0.2175, 0.3045, 0.3915, 0.4785, 0.5655, 
  //                                      0.6525, 0.7395, 0.8265, 0.9135, 1.0005, 1.0875, 1.1745,
  //                                      1.2615, 1.3485,
                       
  //                                      1.4355, 1.5225, 1.6095, 1.6965, 1.7850,
  //                                      1.8800, 1.9865, 2.1075, 2.2470, 2.4110, 2.5750, 2.8250,
                                           
  //                                      2.9960, 3.2265, 3.4015, 3.5765, 3.7515, 3.9260, 
  //                                      4.1020, 4.2770, 4.4505, 4.6270, 4.8025, 5.0400};
    
  //   for (UInt_t j=0; j<iEta.size(); j++){
  //   iEta[j] = iEta[j]/2;
    
  //   if(iEta[j]>0){eta.push_back(towerIndex2phys[iEta[j]-1]);}
  //   else{eta.push_back(-towerIndex2phys[-iEta[j]-1]);}
  //   }
  //   return eta;
  //   }




  // //function:calculate dPhi for two phi inputs
  // //NB:this is phi1-phi2
  // double calc_dPHI(double phi1, double phi2){
  // 	double dPhi = phi1 - phi2;
  // 	if (dPhi>M_PI){dPhi=dPhi-2*M_PI;}
  // 	if (dPhi<-M_PI){dPhi=dPhi+2*M_PI;}
  // 	return dPhi;
  // 	}

  	
 



struct energySums{
	float ett;
	float ettBx;
	float met;
	float metBx;
	float metPhi;
	float htt;
	float httBx;
	float mht;
	float mhtBx;
	float mhtPhi;
	};




/////////////////
/////////////////
//MAIN FUNCTION//
/////////////////
/////////////////
void esums_data(){

  //create a ROOT file to save all the histograms to (actually at end of script)
  //first check the file doesn't exist already so we don't overwrite
  string outputFilename = "comparisons_eSums_stage2_tightLepVetoMuonMuMultZero.root";
  TFile *kk = TFile::Open( outputFilename.c_str() );
  if (kk!=0){
  cout << "TERMINATE:not going to overwrite file" << endl;
  return;
  }

//load the ROOT file we will work on
TFile * f = new TFile("/storage/jt15104/L1Trigger_upgrade_ntuples/run260627_SingleMuReReco_HF_L1JEC_001.root");

//load the TTrees from said ROOT file
TTree * recoTree = (TTree*)f->Get("l1JetRecoTree/JetRecoTree");
TTree * upgradeTree = (TTree*)f->Get("l1UpgradeEmuTree/L1UpgradeTree");
TTree * muonTree = (TTree*)f->Get("l1MuonRecoTree/Muon2RecoTree");
TTree * metFilterTree = (TTree*)f->Get("l1MetFilterRecoTree/MetFilterRecoTree");

//load the number of event entries
Int_t neventRECO = (Int_t)recoTree->GetEntries();

/////////////////////////////
//Structures used in script//
/////////////////////////////
   struct Jet l1jet;
   struct Jet recojet;
   struct Particle muon;
   struct energySums l1Sums;
   struct energySums myL1sums;
   struct energySums recoSums;


  //  reference of branch class types
  //  L1Analysis::L1AnalysisEventDataFormat        *event_ = new L1Analysis::L1AnalysisEventDataFormat();
  //  L1Analysis::L1AnalysisSimulationDataFormat   *simulation_;
  //  L1Analysis::L1AnalysisGCTDataFormat          *gct_;
  //  L1Analysis::L1AnalysisGMTDataFormat          *gmt_;
  //  L1Analysis::L1AnalysisGTDataFormat           *gt_;
  //  L1Analysis::L1AnalysisRCTDataFormat          *rct_;
  //  L1Analysis::L1AnalysisDTTFDataFormat         *dttf_;
  //  L1Analysis::L1AnalysisCSCTFDataFormat        *csctf_;
  //  L1Analysis::L1AnalysisRecoMetDataFormat      *recoMet_;
  //  L1Analysis::L1AnalysisRecoMuonDataFormat     *recoMuon_;   //THIS IS OUT OF DATE
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
L1Analysis::L1AnalysisRecoMetDataFormat      *recoMet_ = new L1Analysis::L1AnalysisRecoMetDataFormat();
recoTree->SetBranchAddress("Sums", &recoMet_);

L1Analysis::L1AnalysisL1UpgradeDataFormat    *upgrade_ = new L1Analysis::L1AnalysisL1UpgradeDataFormat();
upgradeTree->SetBranchAddress("L1Upgrade", &upgrade_);

L1Analysis::L1AnalysisRecoMetFilterDataFormat      *recoMetFilter_ = new L1Analysis::L1AnalysisRecoMetFilterDataFormat();
metFilterTree->SetBranchAddress("MetFilters", &recoMetFilter_);





///////////////////////////////////////////
//create the framework for the histograms//
///////////////////////////////////////////

//distributions
TH1F * hMETphi_l1 = new TH1F("hMETphi_l1", ";#phi_{L1}^{MET}", 40, -M_PI, M_PI);
TH1F * hMHTphi_l1 = new TH1F("hMHTphi_l1", ";#phi_{L1}^{MHT}", 40, -M_PI, M_PI);
TH1F * hETT_l1 = new TH1F("hETT_l1", ";ETT_{L1} (GeV)", 40, 0, 400);
TH1F * hMET_l1 = new TH1F("hMET_l1", ";MET_{L1} (GeV)", 40, 0, 150);
TH1F * hHTT_l1 = new TH1F("hHTT_l1", ";HTT_{L1} (GeV)", 40, 0, 400);
TH1F * hHTT_l1_ZOOM = new TH1F("hHTT_l1_ZOOM", ";HTT_{L1} (GeV)", 50, 0, 50);
TH1F * hMHT_l1 = new TH1F("hMHT_l1", ";MHT_{L1} (GeV)", 40, 0, 150);
TH1F * h_LeadingL1jetPtForL1HTTis0 = new TH1F("h_LeadingL1jetPtForL1HTTis0", ";LeadingL1jetPt (GeV)", 40, 0, 100);
TH1F * h_LeadingL1jetPtForL1HTTnot0 = new TH1F("h_LeadingL1jetPtForL1HTTnot0", ";LeadingL1jetPt (GeV)", 40, 0, 100);
TH2F * h_LeadingL1jetEtaPhiForL1HTTis0 = new TH2F("h_LeadingL1jetEtaPhiForL1HTTis0", ";eta;phi", 50, -5, 5, 50, -M_PI, M_PI);
TH2F * h_LeadingL1jetEtaPhiForL1HTTnot0 = new TH2F("h_LeadingL1jetEtaPhiForL1HTTnot0", ";eta;phi", 50, -5, 5, 50, -M_PI, M_PI);
TH1F * hMETphi_reco = new TH1F("hMETphi_reco", ";#phi_{RECO}^{MET}", 40, -M_PI, M_PI);
TH1F * hMHTphi_reco = new TH1F("hMHTphi_reco", ";#phi_{RECO}^{MHT}", 40, 0, 2*M_PI);
TH1F * hETT_reco = new TH1F("hETT_reco", ";ETT_{RECO} (GeV)", 40, 0, 2000);
TH1F * hMET_reco = new TH1F("hMET_reco", ";MET_{RECO} (GeV)", 40, 0, 150);
TH1F * hHTT_reco = new TH1F("hHTT_reco", ";HTT_{RECO} (GeV)", 40, 0, 400);
TH1F * hMHT_reco = new TH1F("hMHT_reco", ";MHT_{RECO} (GeV)", 40, 0, 150);


//resolutions
TH1F * hdET_ETT = new TH1F("hdET_ETT", ";(ETT_{L1} - ETT_{RECO})/ETT_{RECO}", 100, -1.0, 1.0);
TH1F * hdET_MET = new TH1F("hdET_MET", ";(MET_{L1} - MET_{RECO})/MET_{RECO}", 100, -1.0, 3.5);
TH1F * hdET_HTT = new TH1F("hdET_HTT", ";(HTT_{L1} - HTT_{RECO})/HTT_{RECO}", 100, -1.0, 3.0);
TH1F * hdET_MHT = new TH1F("hdET_MHT", ";(MHT_{L1} - MHT_{RECO})/MHT_{RECO}", 100, -1.0, 2.0);
// TH1F * hdPhi_MET = new TH1F("hdPhi_MET", ";#phi_{RECO}^{MET} - #phi_{L1}^{MET}", 50, -M_PI, M_PI);
// TH1F * hdPhi_MHT = new TH1F("hdPhi_MHT", ";#phi_{RECO}^{MHT} - #phi_{L1}^{MHT}", 50, -M_PI, M_PI);
TH2F * hETS_ETT = new TH2F("hETS_ETT", "", 200, 0, 2000, 200, 0, 800);
hETS_ETT->GetXaxis()->SetTitle("RECO ETT (GeV)");
hETS_ETT->GetYaxis()->SetTitle("L1 upgrade ETT (GeV)");
TH2F * hETS_MET = new TH2F("hETS_MET", "", 200, 0, 300, 200, 0, 300);
hETS_MET->GetXaxis()->SetTitle("RECO MET (GeV)");
hETS_MET->GetYaxis()->SetTitle("L1 upgrade MET (GeV)");
TH2F * hETS_HTT = new TH2F("hETS_HTT", "", 200, 0, 1200, 200, 0, 1200);
hETS_HTT->GetXaxis()->SetTitle("RECO HTT (GeV)");
hETS_HTT->GetYaxis()->SetTitle("L1 upgrade HTT (GeV)");
TH2F * hETS_MHT = new TH2F("hETS_MHT", "", 200, 0, 300, 200, 0, 300);
hETS_MHT->GetXaxis()->SetTitle("RECO MHT (GeV)");
hETS_MHT->GetYaxis()->SetTitle("L1 upgrade MHT (GeV)");


//distributions and resolutions for *my* htt
TH1F * h_myl1_HTT_l1 = new TH1F("h_myl1_HTT_l1", ";*my* HTT_{L1} (GeV)", 40, 0, 400);
TH1F * h_myl1_LeadingL1jetPtForL1HTTis0 = new TH1F("h_myl1_LeadingL1jetPtForL1HTTis0", ";LeadingL1jetPt (GeV)", 40, 0, 100);
TH1F * h_myl1_LeadingL1jetPtForL1HTTnot0 = new TH1F("h_myl1_LeadingL1jetPtForL1HTTnot0", ";LeadingL1jetPt (GeV)", 40, 0, 100);
TH2F * h_myl1_LeadingL1jetEtaPhiForL1HTTis0 = new TH2F("h_myl1_LeadingL1jetEtaPhiForL1HTTis0", ";eta;phi", 50, -5, 5, 50, -M_PI, M_PI);
TH2F * h_myl1_LeadingL1jetEtaPhiForL1HTTnot0 = new TH2F("h_myl1_LeadingL1jetEtaPhiForL1HTTnot0", ";eta;phi", 50, -5, 5, 50, -M_PI, M_PI);

TH1F * h_myl1_dET_HTT = new TH1F("h_myl1_dET_HTT", ";(*my*HTT_{L1} - HTT_{RECO})/HTT_{RECO}", 100, -1.0, 3.0);
TH2F * h_myl1_ETS_HTT = new TH2F("h_myl1_ETS_HTT", "", 200, 0, 1200, 200, 0, 1200);
h_myl1_ETS_HTT->GetXaxis()->SetTitle("RECO HTT (GeV)");
h_myl1_ETS_HTT->GetYaxis()->SetTitle("*my*L1 upgrade HTT (GeV)");
TH2F * h_myl1_origl1_ETS_HTT = new TH2F("h_myl1_origl1_ETS_HTT", "", 200, 0, 1200, 200, 0, 1200);
h_myl1_origl1_ETS_HTT->GetXaxis()->SetTitle("*my*L1 upgrade HTT (GeV)");
h_myl1_origl1_ETS_HTT->GetYaxis()->SetTitle("L1 upgrade HTT (GeV)");


//turnOns//
TH1F * hden_ETT = new TH1F("hden_ETT", "", 40, 0, 3000);
TH1F * hden_MET = new TH1F("hden_MET", "", 40, 0, 500);
TH1F * hden_HTT = new TH1F("hden_HTT", "", 40, 0, 300);
TH1F * hden_MHT = new TH1F("hden_MHT", "", 40, 0, 500);
TH1F * hnum_ETT_100 = new TH1F("hnum_ETT_100", "", 40, 0, 3000);
TH1F * hnum_ETT_125 = new TH1F("hnum_ETT_125", "", 40, 0, 3000);
TH1F * hnum_ETT_150 = new TH1F("hnum_ETT_150", "", 40, 0, 3000);
TH1F * hnum_ETT_175 = new TH1F("hnum_ETT_175", "", 40, 0, 3000);
TH1F * hnum_ETT_200 = new TH1F("hnum_ETT_200", "", 40, 0, 3000);
TH1F * hnum_ETT_250 = new TH1F("hnum_ETT_250", "", 40, 0, 3000);
TH1F * hnum_MET_40 = new TH1F("hnum_MET_40", "", 40, 0, 500);
TH1F * hnum_MET_60 = new TH1F("hnum_MET_60", "", 40, 0, 500);
TH1F * hnum_MET_80 = new TH1F("hnum_MET_80", "", 40, 0, 500);
TH1F * hnum_MET_100 = new TH1F("hnum_MET_100", "", 40, 0, 500);
TH1F * hnum_HTT_100 = new TH1F("hnum_HTT_100", "", 40, 0, 300);
TH1F * hnum_HTT_125 = new TH1F("hnum_HTT_125", "", 40, 0, 300);
TH1F * hnum_HTT_150 = new TH1F("hnum_HTT_150", "", 40, 0, 300);
TH1F * hnum_HTT_175 = new TH1F("hnum_HTT_175", "", 40, 0, 300);
TH1F * hnum_HTT_200 = new TH1F("hnum_HTT_200", "", 40, 0, 300);
TH1F * hnum_HTT_250 = new TH1F("hnum_HTT_250", "", 40, 0, 300);
TH1F * hnum_MHT_40 = new TH1F("hnum_MHT_40", "", 40, 0, 500);
TH1F * hnum_MHT_60 = new TH1F("hnum_MHT_60", "", 40, 0, 500);
TH1F * hnum_MHT_80 = new TH1F("hnum_MHT_80", "", 40, 0, 500);
TH1F * hnum_MHT_100 = new TH1F("hnum_MHT_100", "", 40, 0, 500);
TH1F * hEff_ETT_100 = new TH1F("hEff_ETT_100", ";reco ETT (GeV);efficiency", 40, 0, 3000);
TH1F * hEff_ETT_125 = new TH1F("hEff_ETT_125", ";reco ETT (GeV);efficiency", 40, 0, 3000);
TH1F * hEff_ETT_150 = new TH1F("hEff_ETT_150", ";reco ETT (GeV);efficiency", 40, 0, 3000);
TH1F * hEff_ETT_175 = new TH1F("hEff_ETT_175", ";reco ETT (GeV);efficiency", 40, 0, 3000);
TH1F * hEff_ETT_200 = new TH1F("hEff_ETT_200", ";reco ETT (GeV);efficiency", 40, 0, 3000);
TH1F * hEff_ETT_250 = new TH1F("hEff_ETT_250", ";reco ETT (GeV);efficiency", 40, 0, 3000);
TH1F * hEff_MET_40 = new TH1F("hEff_MET_40", ";reco MET (GeV);efficiency", 40, 0, 500);
TH1F * hEff_MET_60 = new TH1F("hEff_MET_60", ";reco MET (GeV);efficiency", 40, 0, 500);
TH1F * hEff_MET_80 = new TH1F("hEff_MET_80", ";reco MET (GeV);efficiency", 40, 0, 500);
TH1F * hEff_MET_100 = new TH1F("hEff_MET_100", ";reco MET (GeV);efficiency", 40, 0, 500);
TH1F * hEff_HTT_100 = new TH1F("hEff_HTT_100", ";reco HTT (GeV);efficiency", 40, 0, 300);
TH1F * hEff_HTT_125 = new TH1F("hEff_HTT_125", ";reco HTT (GeV);efficiency", 40, 0, 300);
TH1F * hEff_HTT_150 = new TH1F("hEff_HTT_150", ";reco HTT (GeV);efficiency", 40, 0, 300);
TH1F * hEff_HTT_175 = new TH1F("hEff_HTT_175", ";reco HTT (GeV);efficiency", 40, 0, 300);
TH1F * hEff_HTT_200 = new TH1F("hEff_HTT_200", ";reco HTT (GeV);efficiency", 40, 0, 300);
TH1F * hEff_HTT_250 = new TH1F("hEff_HTT_250", ";reco HTT (GeV);efficiency", 40, 0, 300);
TH1F * hEff_MHT_40 = new TH1F("hEff_MHT_40", ";reco MHT (GeV);efficiency", 40, 0, 500);
TH1F * hEff_MHT_60 = new TH1F("hEff_MHT_60", ";reco MHT (GeV);efficiency", 40, 0, 500);
TH1F * hEff_MHT_80 = new TH1F("hEff_MHT_80", ";reco MHT (GeV);efficiency", 40, 0, 500);
TH1F * hEff_MHT_100 = new TH1F("hEff_MHT_100", ";reco MHT (GeV);efficiency", 40, 0, 500);



///////////////////////////////
///////////////////////////////
//loop through all the events//
///////////////////////////////
///////////////////////////////
 for (Int_t i=0; i<neventRECO; i++){
			
		//load the Tree info for the event
    int nb = recoTree->GetEntry(i);
    if (nb==0){
    cout << "did not load JetRecoTree for entry " << i << endl;
    return;}
    
    nb = upgradeTree->GetEntry(i);
    if (nb==0) {
    cout << "did not load L1UpgradeTree for entry " << i << endl;
    return;}

    nb = metFilterTree->GetEntry(i);
    if (nb==0) {
    cout << "did not load MetFilterRecoTree for entry " << i << endl;
    return;}
                
    ////////////////////////
    //ENERGY_SUMS_ANALYSIS//
    ////////////////////////

    //get the sum values
    double etSum = upgrade_->sumEt[0];
    double metSum = upgrade_->sumEt[2];
    double htSum = upgrade_->sumEt[1];
    double mhtSum = upgrade_->sumEt[3];

        recoSums.htt = recoMet_->Ht;
        recoSums.mht = recoMet_->mHt;
        recoSums.mhtPhi = recoMet_->mHtPhi;
        recoSums.ett = recoMet_->sumEt;
recoMet_->met
recoMet_->metPhim

    if(met_filter(recoMetFilter_->hbheNoiseFilter, recoMetFilter_->hbheNoiseIsoFilter, recoMetFilter_->cscTightHalo2015Filter, recoMetFilter_->ecalDeadCellTPFilter,
                  recoMetFilter_->goodVerticesFilter, recoMetFilter_->eeBadScFilter, recoMetFilter_->chHadTrackResFilter, recoMetFilter_->muonBadTrackFilter)){
      ///////////////////////
      //fill the histograms//
      ///////////////////////
      hMETphi_reco->Fill(recoSums.metPhi);
      hMHTphi_reco->Fill(recoSums.mhtPhi);
      hETT_reco->Fill(recoSums.ett);
      hMET_reco->Fill(recoSums.met);
      hHTT_reco->Fill(recoSums.htt);
      hMHT_reco->Fill(recoSums.mht);  
      
      //require that l1quantities have bx==0
      if(l1Sums.ettBx==0){
      hETT_l1->Fill(l1Sums.ett);  
      hdET_ETT->Fill((l1Sums.ett-recoSums.ett)/recoSums.ett);
      hETS_ETT->Fill(recoSums.ett,l1Sums.ett);
      }

      if(l1Sums.metBx==0){
      hMET_l1->Fill(l1Sums.met);
      hMETphi_l1->Fill(l1Sums.metPhi);  
      hdET_MET->Fill((l1Sums.met-recoSums.met)/recoSums.met);
      hETS_MET->Fill(recoSums.met,l1Sums.met);
      hdPhi_MET->Fill(calc_dPHI(recoSums.metPhi,l1Sums.metPhi));
      }
  		
      if(l1Sums.httBx==0){
      hHTT_l1->Fill(l1Sums.htt);
      hdET_HTT->Fill((l1Sums.htt-recoSums.htt)/recoSums.htt);
      hETS_HTT->Fill(recoSums.htt,l1Sums.htt);
      }

      if(l1Sums.mhtBx==0){
      hMHT_l1->Fill(l1Sums.mht);
      hMHTphi_l1->Fill(l1Sums.mhtPhi);
      hdET_MHT->Fill((l1Sums.mht-recoSums.mht)/recoSums.mht);
      hETS_MHT->Fill(recoSums.mht,l1Sums.mht);
      hdPhi_MHT->Fill(calc_dPHI(recoSums.mhtPhi,l1Sums.mhtPhi));
      }
       
      //trigger turnOns
      if(l1Sums.ettBx==0)  hden_ETT->Fill(recoSums.ett);
      if(l1Sums.metBx==0)  hden_MET->Fill(recoSums.met);
      if(l1Sums.httBx==0)  hden_HTT->Fill(recoSums.htt);
      if(l1Sums.mhttBx==0) hden_MHT->Fill(recoSums.mht);

      if(l1Sums.ett>100 && l1Sums.ettBx==0){hnum_ETT_100->Fill(recoSums.ett);}
      if(l1Sums.ett>125 && l1Sums.ettBx==0){hnum_ETT_125->Fill(recoSums.ett);}
      if(l1Sums.ett>150 && l1Sums.ettBx==0){hnum_ETT_150->Fill(recoSums.ett);}        
      if(l1Sums.ett>175 && l1Sums.ettBx==0){hnum_ETT_175->Fill(recoSums.ett);}
      if(l1Sums.ett>200 && l1Sums.ettBx==0){hnum_ETT_200->Fill(recoSums.ett);}
      if(l1Sums.ett>250 && l1Sums.ettBx==0){hnum_ETT_250->Fill(recoSums.ett);}

      if(l1Sums.met>40 && l1Sums.metBx==0){hnum_MET_40->Fill(recoSums.met);}
      if(l1Sums.met>60 && l1Sums.metBx==0){hnum_MET_60->Fill(recoSums.met);}
      if(l1Sums.met>80 && l1Sums.metBx==0){hnum_MET_80->Fill(recoSums.met);}        
      if(l1Sums.met>100 && l1Sums.metBx==0){hnum_MET_100->Fill(recoSums.met);}

      if(l1Sums.htt>100 && l1Sums.httBx==0){hnum_HTT_100->Fill(recoSums.htt);}
      if(l1Sums.htt>125 && l1Sums.httBx==0){hnum_HTT_125->Fill(recoSums.htt);}
      if(l1Sums.htt>150 && l1Sums.httBx==0){hnum_HTT_150->Fill(recoSums.htt);}        
      if(l1Sums.htt>175 && l1Sums.httBx==0){hnum_HTT_175->Fill(recoSums.htt);}
      if(l1Sums.htt>200 && l1Sums.httBx==0){hnum_HTT_200->Fill(recoSums.htt);}
      if(l1Sums.htt>250 && l1Sums.httBx==0){hnum_HTT_250->Fill(recoSums.htt);}

      if(l1Sums.mht>40 && l1Sums.mhtBx==0){hnum_MHT_40->Fill(recoSums.mht);}
      if(l1Sums.mht>60 && l1Sums.mhtBx==0){hnum_MHT_60->Fill(recoSums.mht);}
      if(l1Sums.mht>80 && l1Sums.mhtBx==0){hnum_MHT_80->Fill(recoSums.mht);}        
      if(l1Sums.mht>100 && l1Sums.mhtBx==0){hnum_MHT_100->Fill(recoSums.mht);}

    }//closes 'if' we pass the reco met filter
    if (i % 10000 == 0){
	    cout << i << " out of " << neventRECO << endl;}		
  ///////////////////////////////////
  }//closes loop through the events//
  ///////////////////////////////////

  //save the output ROOT file
  //write the histograms
  TFile g( outputFilename.c_str() , "new");

  //distributions
  hMETphi_l1->Write();
  hMHTphi_l1->Write();
  hETT_l1->Write();
  hMET_l1->Write();
  hHTT_l1->Write();

  hMHT_l1->Write();
  hMETphi_reco->Write();
  hMHTphi_reco->Write();
  hETT_reco->Write();
  hMET_reco->Write();
  hHTT_reco->Write();
  hMHT_reco->Write();

  //resolutions
  hdET_ETT->Write();
  hdET_MET->Write();
  hdET_HTT->Write();
  hdET_MHT->Write();
  hdPhi_MET->Write();
  hdPhi_MHT->Write();
  hETS_ETT->Write();
  hETS_MET->Write();
  hETS_HTT->Write();
  hETS_MHT->Write();

  //turnOns
  hEff_ETT_100->Divide(hnum_ETT_100, hden_ETT);
  hEff_ETT_125->Divide(hnum_ETT_125, hden_ETT);
  hEff_ETT_150->Divide(hnum_ETT_150, hden_ETT);
  hEff_ETT_175->Divide(hnum_ETT_175, hden_ETT);
  hEff_ETT_200->Divide(hnum_ETT_200, hden_ETT);
  hEff_ETT_250->Divide(hnum_ETT_250, hden_ETT);
  hEff_ETT_100->Write();
  hEff_ETT_125->Write();
  hEff_ETT_150->Write();
  hEff_ETT_175->Write();
  hEff_ETT_200->Write();
  hEff_ETT_250->Write();
  hnum_ETT_100->Write();
  hnum_ETT_125->Write();
  hnum_ETT_150->Write();
  hnum_ETT_175->Write();
  hnum_ETT_200->Write();
  hnum_ETT_250->Write();
  hden_ETT->Write();

  hEff_MET_40->Divide(hnum_MET_40, hden_MET);
  hEff_MET_60->Divide(hnum_MET_60, hden_MET);
  hEff_MET_80->Divide(hnum_MET_80, hden_MET);
  hEff_MET_100->Divide(hnum_MET_100, hden_MET);
  hEff_MET_40->Write();
  hEff_MET_60->Write();
  hEff_MET_80->Write();
  hEff_MET_100->Write();
  hnum_MET_40->Write();
  hnum_MET_60->Write();
  hnum_MET_80->Write();
  hnum_MET_100->Write();
  hden_MET->Write();

  hEff_HTT_100->Divide(hnum_HTT_100, hden_HTT);
  hEff_HTT_125->Divide(hnum_HTT_125, hden_HTT);
  hEff_HTT_150->Divide(hnum_HTT_150, hden_HTT);
  hEff_HTT_175->Divide(hnum_HTT_175, hden_HTT);
  hEff_HTT_200->Divide(hnum_HTT_200, hden_HTT);
  hEff_HTT_250->Divide(hnum_HTT_250, hden_HTT);
  hEff_HTT_100->Write();
  hEff_HTT_125->Write();
  hEff_HTT_150->Write();
  hEff_HTT_175->Write();
  hEff_HTT_200->Write();
  hEff_HTT_250->Write();
  hnum_HTT_100->Write();
  hnum_HTT_125->Write();
  hnum_HTT_150->Write();
  hnum_HTT_175->Write();
  hnum_HTT_200->Write();
  hnum_HTT_250->Write();
  hden_HTT->Write();

  hEff_MHT_40->Divide(hnum_MHT_40, hden_MHT);
  hEff_MHT_60->Divide(hnum_MHT_60, hden_MHT);
  hEff_MHT_80->Divide(hnum_MHT_80, hden_MHT);
  hEff_MHT_100->Divide(hnum_MHT_100, hden_MHT);
  hEff_MHT_40->Write();
  hEff_MHT_60->Write();
  hEff_MHT_80->Write();
  hEff_MHT_100->Write();
  hnum_MHT_40->Write();
  hnum_MHT_60->Write();
  hnum_MHT_80->Write();
  hnum_MHT_100->Write();
  hden_MHT->Write();

}//closes the 'main' function

