#include "TFile.h"
#include "TTree.h"
#include "TH1F.h"
#include "TH2F.h"
#include <iostream>
#include <math.h>
#include <vector>
#include <string>
#include "TChain.h"
#include "L1Trigger/L1TNtuples/interface/L1AnalysisRecoMetDataFormat.h"
#include "L1Trigger/L1TNtuples/interface/L1AnalysisL1UpgradeDataFormat.h"
#include "L1Trigger/L1TNtuples/interface/L1AnalysisRecoMetFilterDataFormat.h"
#include "L1Trigger/L1TNtuples/interface/L1AnalysisL1ExtraDataFormat.h" 
#include "L1Trigger/L1TNtuples/interface/L1AnalysisEventDataFormat.h"   
/* 
creates turnOn efficiencies and comparison histograms for energy sums
How to use:
1. select l1==hw/emu (~lines 44-45) nb:must use reco as a reference for sums.
2. write the output directory name (~line 58) *** runNumber, triggerType, version, HW/EMU, metFilter?!!***
3. setup the TChains with the right file locations (~line 67+)...keeping a log in path2Ntuples.txt

other option a: can select the efficiency thresholds for each type of esum (~line 182+)
other option b: can select to whether we apply the reco met filter or not (~line46). Note: Mention on/off in outputDir.
*/ 

bool met_filter(Bool_t,Bool_t,Bool_t,Bool_t,Bool_t,Bool_t,Bool_t,Bool_t);
double calc_dPHI(double,double);

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

//MAIN FUNCTION//
void eSums(){

  bool hwOn = true;  //are we using data from hardware?
  bool emuOn = false;  //are we using data from emulator?
  bool metFiltersOn = false;  //avoids using bad events (might kill everything in commisioning runs...)

  if (hwOn==false && emuOn==false){
    cout << "exiting as neither hardware or emulator selected" << endl;
    return;}

  if (hwOn==true && emuOn==true){
    cout << "exiting as both hardware and emulator selected" << endl;
    return;}

  //create a ROOT file to save all the histograms to (actually at end of script)
  //first check the file doesn't exist already so we don't overwrite
  string dirName = "output_eSums/multipleRunsB0005_singleMuon_v67p0_hwPf_tightLepVetoMuMultZeroCentral_noCutsHf_withOfflineCorrectios/"; //***runNumber, triggerType, version, HW/EMU, metFilter?!!***
  string outputFilename = dirName + "histos.root";
  TFile *kk = TFile::Open( outputFilename.c_str() );
  if (kk!=0){
    cout << "TERMINATE:not going to overwrite file" << endl;
    return;
  }
  cout << "Loading up the TChains..." << endl;
  TChain * recoTree = new TChain("l1JetRecoTree/JetRecoTree");
  recoTree->Add("root://eoscms.cern.ch//eos/cms/store/group/dpg_trigger/comm_trigger/L1Trigger/L1Menu2016/Stage2/Collision2016-wRECO-l1t-integration-v67p0/SingleMuon/crab_Collision2016-wRECO-l1t-integration-v67p0__SingleMuon_2016B_v2/160702_220353/0005/*.root");

  TChain * metFilterTree = new TChain("l1MetFilterRecoTree/MetFilterRecoTree");
  metFilterTree->Add("root://eoscms.cern.ch//eos/cms/store/group/dpg_trigger/comm_trigger/L1Trigger/L1Menu2016/Stage2/Collision2016-wRECO-l1t-integration-v67p0/SingleMuon/crab_Collision2016-wRECO-l1t-integration-v67p0__SingleMuon_2016B_v2/160702_220353/0005/*.root");

  TChain * l1emuTree = new TChain("l1UpgradeEmuTree/L1UpgradeTree");
  if (emuOn){
    l1emuTree->Add("");
  }

  TChain * l1hwTree = new TChain("l1UpgradeTree/L1UpgradeTree");
  if (hwOn){
    l1hwTree->Add("root://eoscms.cern.ch//eos/cms/store/group/dpg_trigger/comm_trigger/L1Trigger/L1Menu2016/Stage2/Collision2016-wRECO-l1t-integration-v67p0/SingleMuon/crab_Collision2016-wRECO-l1t-integration-v67p0__SingleMuon_2016B_v2/160702_220353/0005/*.root");
  }

  TChain * eventTree = new TChain("l1EventTree/L1EventTree");
  eventTree->Add("root://eoscms.cern.ch//eos/cms/store/group/dpg_trigger/comm_trigger/L1Trigger/L1Menu2016/Stage2/Collision2016-wRECO-l1t-integration-v67p0/SingleMuon/crab_Collision2016-wRECO-l1t-integration-v67p0__SingleMuon_2016B_v2/160702_220353/0005/*.root"); 
  L1Analysis::L1AnalysisEventDataFormat    *event_ = new L1Analysis::L1AnalysisEventDataFormat();
  eventTree->SetBranchAddress("Event", &event_);  

  //load the number of event entries
  Int_t nevent = (Int_t)recoTree->GetEntries();

  //Structures used in script
  struct energySums l1Sums;
  struct energySums recoSums;

  //set the branch addresses
  L1Analysis::L1AnalysisRecoMetDataFormat      *recoMet_ = new L1Analysis::L1AnalysisRecoMetDataFormat();
  recoTree->SetBranchAddress("Sums", &recoMet_);
  L1Analysis::L1AnalysisRecoMetFilterDataFormat      *recoMetFilter_ = new L1Analysis::L1AnalysisRecoMetFilterDataFormat();
  metFilterTree->SetBranchAddress("MetFilters", &recoMetFilter_);
  L1Analysis::L1AnalysisL1UpgradeDataFormat    *l1emu_ = new L1Analysis::L1AnalysisL1UpgradeDataFormat();
  l1emuTree->SetBranchAddress("L1Upgrade", &l1emu_);
  L1Analysis::L1AnalysisL1UpgradeDataFormat    *l1hw_ = new L1Analysis::L1AnalysisL1UpgradeDataFormat();
  l1hwTree->SetBranchAddress("L1Upgrade", &l1hw_);

  //create the framework for the histograms
  // phi bins
  int nPhiBins = 50;

  // et bins
  int nEtBins = 100;
  float etLo = -1.0;

  // eSumScat bins
  int nL1eSumScatBins = 200;
  float l1eSumScatLo = 0;
  int nRecoESumScatBins = 200;
  float recoESumScatLo = 0;

  //distributions
  TH1F * hMETphi_l1 = new TH1F("hMETphi_l1", ";#phi_{L1}^{MET}", nPhiBins, -M_PI, M_PI);
  TH1F * hMHTphi_l1 = new TH1F("hMHTphi_l1", ";#phi_{L1}^{MHT}", nPhiBins, -M_PI, M_PI);
  TH1F * hMETphi_reco = new TH1F("hMETphi_reco", ";#phi_{RECO}^{MET}", nPhiBins, -M_PI, M_PI);
  TH1F * hMHTphi_reco = new TH1F("hMHTphi_reco", ";#phi_{RECO}^{MHT}", nPhiBins, 0, 2*M_PI);

  // //resolutions
  TH1F * hdET_ETT = new TH1F("hdET_ETT", ";(ETT_{L1} - ETT_{RECO})/ETT_{RECO}", nEtBins, etLo, 1.0);
  TH1F * hdET_MET = new TH1F("hdET_MET", ";(MET_{L1} - MET_{RECO})/MET_{RECO}", nEtBins, etLo, 3.5);
  TH1F * hdET_HTT = new TH1F("hdET_HTT", ";(HTT_{L1} - HTT_{RECO})/HTT_{RECO}", nEtBins, etLo, 3.0);
  TH1F * hdET_MHT = new TH1F("hdET_MHT", ";(MHT_{L1} - MHT_{RECO})/MHT_{RECO}", nEtBins, etLo, 2.0);
  TH1F * hdPhi_MET = new TH1F("hdPhi_MET", ";#phi_{RECO}^{MET} - #phi_{L1}^{MET}", nPhiBins, -M_PI, M_PI);
  TH1F * hdPhi_MHT = new TH1F("hdPhi_MHT", ";#phi_{RECO}^{MHT} - #phi_{L1}^{MHT}", nPhiBins, -M_PI, M_PI);
  TH2F * hETS_ETT = new TH2F("hETS_ETT", "", nRecoESumScatBins, recoESumScatLo, 2000, nL1eSumScatBins, l1eSumScatLo, 800);
  hETS_ETT->GetXaxis()->SetTitle("RECO ETT (GeV)");
  hETS_ETT->GetYaxis()->SetTitle("L1 ETT (GeV)");
  TH2F * hETS_MET = new TH2F("hETS_MET", "", nRecoESumScatBins, recoESumScatLo, 300, nL1eSumScatBins, l1eSumScatLo, 300);
  hETS_MET->GetXaxis()->SetTitle("RECO MET (GeV)");
  hETS_MET->GetYaxis()->SetTitle("L1 MET (GeV)");
  TH2F * hETS_HTT = new TH2F("hETS_HTT", "", nRecoESumScatBins, recoESumScatLo, 1200, nL1eSumScatBins, l1eSumScatLo, 1200);
  hETS_HTT->GetXaxis()->SetTitle("RECO HTT (GeV)");
  hETS_HTT->GetYaxis()->SetTitle("L1 HTT (GeV)");
  TH2F * hETS_MHT = new TH2F("hETS_MHT", "", nRecoESumScatBins, recoESumScatLo, 300, nL1eSumScatBins, l1eSumScatLo, 300);
  hETS_MHT->GetXaxis()->SetTitle("RECO MHT (GeV)");
  hETS_MHT->GetYaxis()->SetTitle("L1 MHT (GeV)");

  //turnOns Efficiencies//
  // turnOn bins
  int nTurnOnBinsETT = 40;
  float turnOnLoETT = 0;
  float turnOnHiETT = 1000;

  int nTurnOnBinsMET = 40;
  float turnOnLoMET = 0;
  float turnOnHiMET = 500;

  int nTurnOnBinsHTT = 40;
  float turnOnLoHTT = 0;
  float turnOnHiHTT = 1000;

  int nTurnOnBinsMHT = 40;
  float turnOnLoMHT = 0;
  float turnOnHiMHT = 500;

  // turnOns histos
  // nb: num=numerator, den=denominator. At the bottom of script we create the ratio
  vector<TH1F*> vectorOfNumsETT;
  vector<TH1F*> vectorOfEffsETT;
  vector<TH1F*> vectorOfNumsMET;
  vector<TH1F*> vectorOfEffsMET;
  vector<TH1F*> vectorOfNumsHTT;
  vector<TH1F*> vectorOfEffsHTT;
  vector<TH1F*> vectorOfNumsMHT;
  vector<TH1F*> vectorOfEffsMHT;

  TH1F * hden_ETT = new TH1F("hden_ETT", "", nTurnOnBinsETT, turnOnLoETT, turnOnHiETT);
  TH1F * hden_MET = new TH1F("hden_MET", "", nTurnOnBinsMET, turnOnLoMET, turnOnHiMET);
  TH1F * hden_HTT = new TH1F("hden_HTT", "", nTurnOnBinsHTT, turnOnLoHTT, turnOnHiHTT);
  TH1F * hden_MHT = new TH1F("hden_MHT", "", nTurnOnBinsMHT, turnOnLoMHT, turnOnHiMHT);

  vector<int> thresholdsVectorETT;
  thresholdsVectorETT.push_back(100);
  thresholdsVectorETT.push_back(125);
  thresholdsVectorETT.push_back(150);
  thresholdsVectorETT.push_back(175);
  thresholdsVectorETT.push_back(200);
  thresholdsVectorETT.push_back(250);

  vector<int> thresholdsVectorMET;
  thresholdsVectorMET.push_back(40);
  thresholdsVectorMET.push_back(60);
  thresholdsVectorMET.push_back(80);
  thresholdsVectorMET.push_back(100);
  thresholdsVectorMET.push_back(120);

  vector<int> thresholdsVectorHTT;
  thresholdsVectorHTT.push_back(100);
  thresholdsVectorHTT.push_back(125);
  thresholdsVectorHTT.push_back(150);
  thresholdsVectorHTT.push_back(175);
  thresholdsVectorHTT.push_back(200);
  thresholdsVectorHTT.push_back(250);

  vector<int> thresholdsVectorMHT;
  thresholdsVectorMHT.push_back(40);
  thresholdsVectorMHT.push_back(60);
  thresholdsVectorMHT.push_back(80);
  thresholdsVectorMHT.push_back(100);
  thresholdsVectorMHT.push_back(120);

  for (unsigned int c=0; c<thresholdsVectorETT.size(); c++){
    string thresholdString = to_string(thresholdsVectorETT[c]);
    string centralNumName = "hnum_ETT_" + thresholdString;
    TH1F * h1 = new TH1F(centralNumName.c_str(), "", nTurnOnBinsETT, turnOnLoETT, turnOnHiETT);
    vectorOfNumsETT.push_back(h1);
  }

  for (unsigned int c=0; c<thresholdsVectorMET.size(); c++){
    string thresholdString = to_string(thresholdsVectorMET[c]);
    string centralNumName = "hnum_MET_" + thresholdString;
    TH1F * h1 = new TH1F(centralNumName.c_str(), "", nTurnOnBinsMET, turnOnLoMET, turnOnHiMET);
    vectorOfNumsMET.push_back(h1);
  }

  for (unsigned int c=0; c<thresholdsVectorHTT.size(); c++){
    string thresholdString = to_string(thresholdsVectorHTT[c]);
    string centralNumName = "hnum_HTT_" + thresholdString;
    TH1F * h1 = new TH1F(centralNumName.c_str(), "", nTurnOnBinsHTT, turnOnLoHTT, turnOnHiHTT);
    vectorOfNumsHTT.push_back(h1);
  }

  for (unsigned int c=0; c<thresholdsVectorMHT.size(); c++){
    string thresholdString = to_string(thresholdsVectorMHT[c]);
    string centralNumName = "hnum_MHT_" + thresholdString;
    TH1F * h1 = new TH1F(centralNumName.c_str(), "", nTurnOnBinsMHT, turnOnLoMHT, turnOnHiMHT);
    vectorOfNumsMHT.push_back(h1);
  }    

  ///////////////////////////////
  //loop through all the events//
  ///////////////////////////////
 for (Int_t i=0; i<nevent; i++){
 
    if (i % 10000 == 0){
    cout << i << " out of " << nevent << endl;} 	

    // //lumi break clause
    eventTree->GetEntry(i);
    if (
           event_->run != 275282
        && event_->run != 275283
        && event_->run != 275284
        && event_->run != 275285
        && event_->run != 275286
        && event_->run != 275289
        && event_->run != 275290
        && event_->run != 275291
        && event_->run != 275292
        && event_->run != 275293
        && event_->run != 275309
        && event_->run != 275310
        && event_->run != 275311
        && event_->run != 275319
        && event_->run != 275326
        && event_->run != 275337
        && event_->run != 275338
        && event_->run != 275344
        && event_->run != 275345
        && event_->run != 275370
         && event_->run != 275371
        && event_->run != 275375
        && event_->run != 275376
        && event_->run != 275657
        && event_->run != 275658
        && event_->run != 275659
        && event_->run != 275757
        && event_->run != 275758
        && event_->run != 275759
        && event_->run != 275761
        && event_->run != 275763
        && event_->run != 275764
        && event_->run != 275766
        && event_->run != 275767
        && event_->run != 275768
        && event_->run != 275769
        && event_->run != 275772
        && event_->run != 275773
        && event_->run != 275774
        && event_->run != 275776
        && event_->run != 275777
        && event_->run != 275778
        && event_->run != 275781
         && event_->run != 275782
        && event_->run != 275783                      
        )
    {
      //skip the corresponding event
      continue;
    }



		//load info for the event
    recoTree->GetEntry(i);
    metFilterTree->GetEntry(i);
    if (emuOn){l1emuTree->GetEntry(i);}
    if (hwOn){l1hwTree->GetEntry(i);}

    recoSums.ett = recoMet_->sumEt;
    // recoSums.met = recoMet_->met;
    recoSums.met = recoMet_->caloMetBE;
    recoSums.htt = recoMet_->Ht;
    recoSums.mht = recoMet_->mHt;
    // recoSums.metPhi = recoMet_->metPhi;
    recoSums.metPhi = recoMet_->caloMetPhiBE;
    recoSums.mhtPhi = recoMet_->mHtPhi;
   
    if (emuOn){ // need to do a fix like below at one point...
      l1Sums.ett = l1emu_->sumEt[0];
      l1Sums.met = l1emu_->sumEt[2];
      l1Sums.htt = l1emu_->sumEt[1];
      l1Sums.mht = l1emu_->sumEt[3];
      l1Sums.metPhi = l1emu_->sumPhi[2];
      l1Sums.mhtPhi = l1emu_->sumPhi[3];
    }

    if (hwOn){
      // numbers different due to nonZero BX in HW (could cause a seg fault if this all changes)
      // l1Sums.ett = l1hw_->sumEt[8];
      // l1Sums.met = l1hw_->sumEt[10];
      // l1Sums.htt = l1hw_->sumEt[9];
      // l1Sums.mht = l1hw_->sumEt[11];
      // l1Sums.metPhi = l1hw_->sumPhi[10];
      // l1Sums.mhtPhi = l1hw_->sumPhi[11];

      for (unsigned int c=0; c<l1hw_->nSums; c++){
          if( l1hw_->sumBx[c] != 0 ) continue;
          if( l1hw_->sumType[c] == L1Analysis::kTotalEt ) l1Sums.ett = l1hw_->sumEt[c];
          if( l1hw_->sumType[c] == L1Analysis::kTotalHt ) l1Sums.htt = l1hw_->sumEt[c];
          if( l1hw_->sumType[c] == L1Analysis::kMissingEt ) {l1Sums.met = l1hw_->sumEt[c]; l1Sums.metPhi = l1hw_->sumPhi[c];}
          if( l1hw_->sumType[c] == L1Analysis::kMissingHt ) {l1Sums.mht = l1hw_->sumEt[c]; l1Sums.mhtPhi = l1hw_->sumPhi[c];}
      }






    }

    if(metFiltersOn==false || met_filter(recoMetFilter_->hbheNoiseFilter, recoMetFilter_->hbheNoiseIsoFilter, recoMetFilter_->cscTightHalo2015Filter, recoMetFilter_->ecalDeadCellTPFilter,
                              recoMetFilter_->goodVerticesFilter, recoMetFilter_->eeBadScFilter, recoMetFilter_->chHadTrackResFilter, recoMetFilter_->muonBadTrackFilter)){

      // fill the histograms
      hMETphi_reco->Fill(recoSums.metPhi);
      hMHTphi_reco->Fill(recoSums.mhtPhi);
      hMETphi_l1->Fill(l1Sums.metPhi); 
      hMHTphi_l1->Fill(l1Sums.mhtPhi);

      hdET_ETT->Fill((l1Sums.ett-recoSums.ett)/recoSums.ett);
      hETS_ETT->Fill(recoSums.ett,l1Sums.ett);

      hdET_MET->Fill((l1Sums.met-recoSums.met)/recoSums.met);
      hETS_MET->Fill(recoSums.met,l1Sums.met);
      hdPhi_MET->Fill(calc_dPHI(recoSums.metPhi,l1Sums.metPhi));
  		
      hdET_HTT->Fill((l1Sums.htt-recoSums.htt)/recoSums.htt);
      hETS_HTT->Fill(recoSums.htt,l1Sums.htt);

      hdET_MHT->Fill((l1Sums.mht-recoSums.mht)/recoSums.mht);
      hETS_MHT->Fill(recoSums.mht,l1Sums.mht);
      hdPhi_MHT->Fill(calc_dPHI(recoSums.mhtPhi,l1Sums.mhtPhi));
       
      // trigger turnOns
      hden_ETT->Fill(recoSums.ett);
      hden_MET->Fill(recoSums.met);
      hden_HTT->Fill(recoSums.htt);
      hden_MHT->Fill(recoSums.mht);

      for (unsigned int c=0; c<thresholdsVectorETT.size(); c++){
        if (l1Sums.ett>thresholdsVectorETT[c]){
          vectorOfNumsETT[c]->Fill(recoSums.ett);
        }
      }

      for (unsigned int c=0; c<thresholdsVectorMET.size(); c++){
        if (l1Sums.met>thresholdsVectorMET[c]){
          vectorOfNumsMET[c]->Fill(recoSums.met);
        }
      }

      for (unsigned int c=0; c<thresholdsVectorHTT.size(); c++){
        if (l1Sums.htt>thresholdsVectorHTT[c]){
          vectorOfNumsHTT[c]->Fill(recoSums.htt);
        }
      }

      for (unsigned int c=0; c<thresholdsVectorMHT.size(); c++){
        if (l1Sums.mht>thresholdsVectorMHT[c]){
          vectorOfNumsMHT[c]->Fill(recoSums.mht);
        }
      }

    }//closes 'if' we pass the reco met filter
	
  }//closes loop through the events

  //save the output ROOT file
  //write the histograms
  TFile g( outputFilename.c_str() , "new");

  // distributions
  hMETphi_l1->Write();
  hMHTphi_l1->Write();
  hMETphi_reco->Write();
  hMHTphi_reco->Write();

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
  hden_ETT->Write();
  hden_MET->Write();
  hden_HTT->Write();
  hden_MHT->Write();

  for (unsigned int c=0; c<thresholdsVectorETT.size(); c++){
    string thresholdString = to_string(thresholdsVectorETT[c]);
    string centralEffName = "hEff_ETT_" + thresholdString;
    TH1F * heff = new TH1F(centralEffName.c_str(), ";reco ETT E_{T} (GeV);efficiency", nTurnOnBinsETT, turnOnLoETT, turnOnHiETT);
    heff->Divide(vectorOfNumsETT[c], hden_ETT);
    vectorOfEffsETT.push_back(heff);
    vectorOfNumsETT[c]->Write();
    vectorOfEffsETT[c]->Write();
  }

  for (unsigned int c=0; c<thresholdsVectorMET.size(); c++){
    string thresholdString = to_string(thresholdsVectorMET[c]);
    string centralEffName = "hEff_MET_" + thresholdString;
    TH1F * heff = new TH1F(centralEffName.c_str(), ";reco MET E_{T} (GeV);efficiency", nTurnOnBinsMET, turnOnLoMET, turnOnHiMET);
    heff->Divide(vectorOfNumsMET[c], hden_MET);
    vectorOfEffsMET.push_back(heff);
    vectorOfNumsMET[c]->Write();
    vectorOfEffsMET[c]->Write();
  }

  for (unsigned int c=0; c<thresholdsVectorHTT.size(); c++){
    string thresholdString = to_string(thresholdsVectorHTT[c]);
    string centralEffName = "hEff_HTT_" + thresholdString;
    TH1F * heff = new TH1F(centralEffName.c_str(), ";reco HTT E_{T} (GeV);efficiency", nTurnOnBinsHTT, turnOnLoHTT, turnOnHiHTT);
    heff->Divide(vectorOfNumsHTT[c], hden_HTT);
    vectorOfEffsHTT.push_back(heff);
    vectorOfNumsHTT[c]->Write();
    vectorOfEffsHTT[c]->Write();
  }

  for (unsigned int c=0; c<thresholdsVectorMHT.size(); c++){
    string thresholdString = to_string(thresholdsVectorMHT[c]);
    string centralEffName = "hEff_MHT_" + thresholdString;
    TH1F * heff = new TH1F(centralEffName.c_str(), ";reco MHT E_{T} (GeV);efficiency", nTurnOnBinsMHT, turnOnLoMHT, turnOnHiMHT);
    heff->Divide(vectorOfNumsMHT[c], hden_MHT);
    vectorOfEffsMHT.push_back(heff);
    vectorOfNumsMHT[c]->Write();
    vectorOfEffsMHT[c]->Write();
  }    

}//closes the 'main' function

bool met_filter(Bool_t hbheNoiseFilter, Bool_t hbheNoiseIsoFilter, Bool_t cscTightHalo2015Filter, Bool_t ecalDeadCellTPFilter,
                Bool_t goodVerticesFilter, Bool_t eeBadScFilter, Bool_t chHadTrackResFilter, Bool_t muonBadTrackFilter){
  bool metPass;
  if (hbheNoiseFilter==1 && hbheNoiseIsoFilter==1 && cscTightHalo2015Filter==1 && ecalDeadCellTPFilter==1 
      && goodVerticesFilter==1 && eeBadScFilter==1 && chHadTrackResFilter==1 && muonBadTrackFilter==1){
    metPass = true;}//this met has passed
  else{metPass = false;}//this met has failed 
  return metPass;
}

double calc_dPHI(double phi1, double phi2){
  double dPhi = phi1 - phi2;
  if (dPhi>M_PI){dPhi=dPhi-2*M_PI;}
  if (dPhi<-M_PI){dPhi=dPhi+2*M_PI;}
  return dPhi;
}
