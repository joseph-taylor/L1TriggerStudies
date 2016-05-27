#include "TMath.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1F.h"
#include "TChain.h"
#include <iostream>
#include <fstream>
#include <string>
#include "L1Trigger/L1TNtuples/interface/L1AnalysisEventDataFormat.h"
#include "L1Trigger/L1TNtuples/interface/L1AnalysisL1UpgradeDataFormat.h"
/* TODO: put errors in rates...
creates the the rates and distributions for l1 trigger objects
How to use:
1. select HW, emu, or both for the analysis (~lines 25,26)
2. input the number of bunches in the run (~line 33)
3. input the instantaneous luminosity of the run (~line 34) [only if we scale to 2016 nominal]
4. change the outputFilename (~line 37) ***runNumber, triggerType, version, hw/emu/both, rescaleORnot***
5. set the .root inputFile string (~line 45)
   ...path2Ntuples.txt should hold most useful paths
6. select whether you rescale to L=1.5e34 (~line560??...) generally have it setup to rescale
nb: for 2&3 I have provided the info in runInfoForRates.txt
AT LINE210 PUT IN YOUR LUMISECTION CRITERIA!!! */

void rates(){
  
  bool hwOn = true;   //are we using data from hardware? (upgrade trigger had to be running!!!)
  bool emuOn = false;  //are we using data from emulator?

  if (hwOn==false && emuOn==false){
    cout << "exiting as neither hardware or emulator selected" << endl;
    return;
  }

  double numBunch = 589; //the number of bunches colliding for the run of interest
  double runLum = 0.1725; //luminosity of the run of interest (*10^34)
  double expectedLum = 1.15; //expected luminostiy of 2016 runs (*10^34)

  string outputDirectory = "run273301_zeroBias_807intv53p1_HW";  //***runNumber, triggerType, version, hw/emu/both***MAKE SURE IT EXISTS
  string outputFilename = "output_rates/" + outputDirectory + "/histos.root";
  TFile* kk = TFile::Open( outputFilename.c_str() );
  if (kk!=0){
    cout << "TERMINATE: not going to overwrite file " << outputFilename << endl;
    return;
  }

  string inputFile01 = "root://eoscms.cern.ch//eos/cms/store/group/dpg_trigger/comm_trigger/L1Trigger/L1Menu2016/Stage2/Collision2016-unpacked-l1t-integration-v53p1-CMSSW-807/ZeroBias/crab_Collision2016-unpacked-l1t-integration-v53p1-CMSSW-807__273301_ZeroBias/160518_023920/0000/*.root";
  // string inputFile02 = "root://eoscms.cern.ch//eos/cms/store/group/dpg_trigger/comm_trigger/L1Trigger/L1Menu2016/Stage2/l1t-integration-v48p0-CMSSW-807/ZeroBias2/crab_l1t-integration-v48p0-CMSSW-807__259721_ZeroBias2/160512_105739/0000/*.root";
  // string inputFile03 = "root://eoscms.cern.ch//eos/cms/store/group/dpg_trigger/comm_trigger/L1Trigger/L1Menu2016/Stage2/l1t-integration-v48p0-CMSSW-807/ZeroBias3/crab_l1t-integration-v48p0-CMSSW-807__259721_ZeroBias3/160512_105752/0000/*.root";
  // string inputFile04 = "root://eoscms.cern.ch//eos/cms/store/group/dpg_trigger/comm_trigger/L1Trigger/L1Menu2016/Stage2/l1t-integration-v48p0-CMSSW-807/ZeroBias4/crab_l1t-integration-v48p0-CMSSW-807__259721_ZeroBias4/160512_105712/0000/*.root";

  // make trees
  cout << "Loading up the TChain..." << endl;
  TChain * treeL1emu = new TChain("l1UpgradeEmuTree/L1UpgradeTree");
  if (emuOn){
    treeL1emu->Add(inputFile01.c_str());
    // treeL1emu->Add(inputFile02.c_str());
    // treeL1emu->Add(inputFile03.c_str());
    // treeL1emu->Add(inputFile04.c_str());
  }
  TChain * treeL1hw = new TChain("l1UpgradeTree/L1UpgradeTree");
  if (hwOn){
    treeL1hw->Add(inputFile01.c_str());
    // treeL1emu->Add(inputFile02.c_str());
    // treeL1emu->Add(inputFile03.c_str());
    // treeL1emu->Add(inputFile04.c_str());  
  }
  TChain * eventTree = new TChain("l1EventTree/L1EventTree");
  eventTree->Add(inputFile01.c_str()); 
  // eventTree->Add(inputFile02.c_str());
  // eventTree->Add(inputFile03.c_str());
  // eventTree->Add(inputFile04.c_str());     

  L1Analysis::L1AnalysisL1UpgradeDataFormat    *l1emu_ = new L1Analysis::L1AnalysisL1UpgradeDataFormat();
  treeL1emu->SetBranchAddress("L1Upgrade", &l1emu_);
  L1Analysis::L1AnalysisL1UpgradeDataFormat    *l1hw_ = new L1Analysis::L1AnalysisL1UpgradeDataFormat();
  treeL1hw->SetBranchAddress("L1Upgrade", &l1hw_);
  L1Analysis::L1AnalysisEventDataFormat    *event_ = new L1Analysis::L1AnalysisEventDataFormat();
  eventTree->SetBranchAddress("Event", &event_);

  // get number of entries
  Long64_t nentries;
  if (emuOn) nentries = treeL1emu->GetEntries();
  else nentries = treeL1hw->GetEntries();
  int goodLumiEventCount = 0;

  string outputTxtFilename = "output_rates/" + outputDirectory + "/extraInfo.txt";
  ofstream myfile; // save info about the run, including rates for a given lumi section, and number of events we used.
  myfile.open(outputTxtFilename.c_str());
  eventTree->GetEntry(0);
  myfile << "run number = " << event_->run << endl;

  // set parameters for histograms
  // jet bins
  int nJetBins = 400;
  float jetLo = 0.;
  float jetHi = 400.;
  float jetBinWidth = (jetHi-jetLo)/nJetBins;

  // EG bins
  int nEgBins = 300;
  float egLo = 0.;
  float egHi = 300.;
  float egBinWidth = (egHi-egLo)/nEgBins;

  // tau bins
  int nTauBins = 300;
  float tauLo = 0.;
  float tauHi = 300.;
  float tauBinWidth = (tauHi-tauLo)/nTauBins;

  // htSum bins
  int nHtSumBins = 600;
  float htSumLo = 0.;
  float htSumHi = 600.;
  float htSumBinWidth = (htSumHi-htSumLo)/nHtSumBins;

  // mhtSum bins
  int nMhtSumBins = 300;
  float mhtSumLo = 0.;
  float mhtSumHi = 300.;
  float mhtSumBinWidth = (mhtSumHi-mhtSumLo)/nMhtSumBins;

  // etSum bins
  int nEtSumBins = 600;
  float etSumLo = 0.;
  float etSumHi = 600.;
  float etSumBinWidth = (etSumHi-etSumLo)/nEtSumBins;

  // metSum bins
  int nMetSumBins = 300;
  float metSumLo = 0.;
  float metSumHi = 300.;
  float metSumBinWidth = (metSumHi-metSumLo)/nMetSumBins;

  string axR = ";Threshold E_{T} (GeV);rate (Hz)";
  string axD = ";E_{T} (GeV);events/bin";

  //make histos
  TH1F* singleJetRates_emu = new TH1F("singleJetRates_emu", axR.c_str(), nJetBins, jetLo, jetHi);
  TH1F* doubleJetRates_emu = new TH1F("doubleJetRates_emu", axR.c_str(), nJetBins, jetLo, jetHi);
  TH1F* tripleJetRates_emu = new TH1F("tripleJetRates_emu", axR.c_str(), nJetBins, jetLo, jetHi);
  TH1F* quadJetRates_emu = new TH1F("quadJetRates_emu", axR.c_str(), nJetBins, jetLo, jetHi);
  TH1F* singleEgRates_emu = new TH1F("singleEgRates_emu", axR.c_str(), nEgBins, egLo, egHi);
  TH1F* doubleEgRates_emu = new TH1F("doubleEgRates_emu", axR.c_str(), nEgBins, egLo, egHi);
  TH1F* singleTauRates_emu = new TH1F("singleTauRates_emu", axR.c_str(), nTauBins, tauLo, tauHi);
  TH1F* doubleTauRates_emu = new TH1F("doubleTauRates_emu", axR.c_str(), nTauBins, tauLo, tauHi);
  TH1F* singleISOEgRates_emu = new TH1F("singleISOEgRates_emu", axR.c_str(), nEgBins, egLo, egHi);
  TH1F* doubleISOEgRates_emu = new TH1F("doubleISOEgRates_emu", axR.c_str(), nEgBins, egLo, egHi);
  TH1F* singleISOTauRates_emu = new TH1F("singleISOTauRates_emu", axR.c_str(), nTauBins, tauLo, tauHi);
  TH1F* doubleISOTauRates_emu = new TH1F("doubleISOTauRates_emu", axR.c_str(), nTauBins, tauLo, tauHi);
  TH1F* htSumRates_emu = new TH1F("htSumRates_emu",axR.c_str(), nHtSumBins, htSumLo, htSumHi);
  TH1F* mhtSumRates_emu = new TH1F("mhtSumRates_emu",axR.c_str(), nMhtSumBins, mhtSumLo, mhtSumHi);
  TH1F* etSumRates_emu = new TH1F("etSumRates_emu",axR.c_str(), nEtSumBins, etSumLo, etSumHi);
  TH1F* metSumRates_emu = new TH1F("metSumRates_emu",axR.c_str(), nMetSumBins, metSumLo, metSumHi); 
  
  TH1F* leadingJetDist_emu = new TH1F("leadingJetDist_emu", axD.c_str(), nJetBins, jetLo, jetHi);
  TH1F* secondJetDist_emu = new TH1F("secondJetDist_emu", axD.c_str(), nJetBins, jetLo, jetHi);
  TH1F* thirdJetDist_emu = new TH1F("thirdJetDist_emu", axD.c_str(), nJetBins, jetLo, jetHi);
  TH1F* fourthJetDist_emu = new TH1F("fourthJetDist_emu", axD.c_str(), nJetBins, jetLo, jetHi);            
  TH1F* htSumDist_emu = new TH1F("htSumDist_emu",axD.c_str(), nHtSumBins, htSumLo, htSumHi);
  TH1F* mhtSumDist_emu = new TH1F("mhtSumDist_emu",axD.c_str(), nMhtSumBins, mhtSumLo, mhtSumHi);
  TH1F* etSumDist_emu = new TH1F("etSumDist_emu",axD.c_str(), nEtSumBins, etSumLo, etSumHi);
  TH1F* metSumDist_emu = new TH1F("metSumDist_emu",axD.c_str(), nMetSumBins, metSumLo, metSumHi); 
  TH1F* leadingEgDist_emu = new TH1F("leadingEgDist_emu", axD.c_str(), nEgBins, egLo, egHi);
  TH1F* secondEgDist_emu = new TH1F("secondEgDist_emu", axD.c_str(), nEgBins, egLo, egHi);
  TH1F* leadingTauDist_emu = new TH1F("leadingTauDist_emu", axD.c_str(), nTauBins, tauLo, tauHi);
  TH1F* secondTauDist_emu = new TH1F("secondTauDist_emu", axD.c_str(), nTauBins, tauLo, tauHi);
  TH1F* leadingISOEgDist_emu = new TH1F("leadingISOEgDist_emu", axD.c_str(), nEgBins, egLo, egHi);
  TH1F* secondISOEgDist_emu = new TH1F("secondISOEgDist_emu", axD.c_str(), nEgBins, egLo, egHi);
  TH1F* leadingISOTauDist_emu = new TH1F("leadingISOTauDist_emu", axD.c_str(), nTauBins, tauLo, tauHi);
  TH1F* secondISOTauDist_emu = new TH1F("secondISOTauDist_emu", axD.c_str(), nTauBins, tauLo, tauHi);

  TH1F* singleJetRates_hw = new TH1F("singleJetRates_hw", axR.c_str(), nJetBins, jetLo, jetHi);
  TH1F* doubleJetRates_hw = new TH1F("doubleJetRates_hw", axR.c_str(), nJetBins, jetLo, jetHi);
  TH1F* tripleJetRates_hw = new TH1F("tripleJetRates_hw", axR.c_str(), nJetBins, jetLo, jetHi);
  TH1F* quadJetRates_hw = new TH1F("quadJetRates_hw", axR.c_str(), nJetBins, jetLo, jetHi);
  TH1F* singleEgRates_hw = new TH1F("singleEgRates_hw", axR.c_str(), nEgBins, egLo, egHi);
  TH1F* doubleEgRates_hw = new TH1F("doubleEgRates_hw", axR.c_str(), nEgBins, egLo, egHi);
  TH1F* singleTauRates_hw = new TH1F("singleTauRates_hw", axR.c_str(), nTauBins, tauLo, tauHi);
  TH1F* doubleTauRates_hw = new TH1F("doubleTauRates_hw", axR.c_str(), nTauBins, tauLo, tauHi);
  TH1F* singleISOEgRates_hw = new TH1F("singleISOEgRates_hw", axR.c_str(), nEgBins, egLo, egHi);
  TH1F* doubleISOEgRates_hw = new TH1F("doubleISOEgRates_hw", axR.c_str(), nEgBins, egLo, egHi);
  TH1F* singleISOTauRates_hw = new TH1F("singleISOTauRates_hw", axR.c_str(), nTauBins, tauLo, tauHi);
  TH1F* doubleISOTauRates_hw = new TH1F("doubleISOTauRates_hw", axR.c_str(), nTauBins, tauLo, tauHi);
  TH1F* htSumRates_hw = new TH1F("htSumRates_hw",axR.c_str(), nHtSumBins, htSumLo, htSumHi);
  TH1F* mhtSumRates_hw = new TH1F("mhtSumRates_hw",axR.c_str(), nMhtSumBins, mhtSumLo, mhtSumHi);
  TH1F* etSumRates_hw = new TH1F("etSumRates_hw",axR.c_str(), nEtSumBins, etSumLo, etSumHi);
  TH1F* metSumRates_hw = new TH1F("metSumRates_hw",axR.c_str(), nMetSumBins, metSumLo, metSumHi); 
  
  TH1F* leadingJetDist_hw = new TH1F("leadingJetDist_hw", axD.c_str(), nJetBins, jetLo, jetHi);
  TH1F* secondJetDist_hw = new TH1F("secondJetDist_hw", axD.c_str(), nJetBins, jetLo, jetHi);
  TH1F* thirdJetDist_hw = new TH1F("thirdJetDist_hw", axD.c_str(), nJetBins, jetLo, jetHi);
  TH1F* fourthJetDist_hw = new TH1F("fourthJetDist_hw", axD.c_str(), nJetBins, jetLo, jetHi);            
  TH1F* htSumDist_hw = new TH1F("htSumDist_hw",axD.c_str(), nHtSumBins, htSumLo, htSumHi);
  TH1F* mhtSumDist_hw = new TH1F("mhtSumDist_hw",axD.c_str(), nMhtSumBins, mhtSumLo, mhtSumHi);
  TH1F* etSumDist_hw = new TH1F("etSumDist_hw",axD.c_str(), nEtSumBins, etSumLo, etSumHi);
  TH1F* metSumDist_hw = new TH1F("metSumDist_hw",axD.c_str(), nMetSumBins, metSumLo, metSumHi); 
  TH1F* leadingEgDist_hw = new TH1F("leadingEgDist_hw", axD.c_str(), nEgBins, egLo, egHi);
  TH1F* secondEgDist_hw = new TH1F("secondEgDist_hw", axD.c_str(), nEgBins, egLo, egHi);
  TH1F* leadingTauDist_hw = new TH1F("leadingTauDist_hw", axD.c_str(), nTauBins, tauLo, tauHi);
  TH1F* secondTauDist_hw = new TH1F("secondTauDist_hw", axD.c_str(), nTauBins, tauLo, tauHi);
  TH1F* leadingISOEgDist_hw = new TH1F("leadingISOEgDist_hw", axD.c_str(), nEgBins, egLo, egHi);
  TH1F* secondISOEgDist_hw = new TH1F("secondISOEgDist_hw", axD.c_str(), nEgBins, egLo, egHi);
  TH1F* leadingISOTauDist_hw = new TH1F("leadingISOTauDist_hw", axD.c_str(), nTauBins, tauLo, tauHi);
  TH1F* secondISOTauDist_hw = new TH1F("secondISOTauDist_hw", axD.c_str(), nTauBins, tauLo, tauHi);

  /////////////////////////////////
  // loop through all the entries//
  /////////////////////////////////
  for (Long64_t jentry=0; jentry<nentries; jentry++){
    if((jentry%10000)==0) std::cout << "Done " << jentry  << " events of " << nentries << std::endl;

    //lumi break clause
    eventTree->GetEntry(jentry);
    // if (event_->lumi < 224
    //     || event_->lumi > 1800
    //     || event_->lumi == 948
    //     || event_->lumi == 960
    //     || event_->lumi == 973
    //     || event_->lumi == 996                
    //     || event_->lumi == 1023
    //     || event_->lumi == 1024
    //     || event_->lumi == 1037
    //     || event_->lumi == 1038  
    //     || event_->lumi == 1052
    //     || event_->lumi == 1053
    //     || event_->lumi == 1061
    //     || event_->lumi == 1062                
    //     || event_->lumi == 1063
    //     || event_->lumi == 1064
    //     || event_->lumi == 1065
    //     || event_->lumi == 1066 
    //     || event_->lumi == 1067
    //     || event_->lumi == 1361                
    //     || event_->lumi == 1362
    //     || event_->lumi == 1371
    //     || event_->lumi == 1372
    //     || event_->lumi == 1373
    //     || event_->lumi == 1719
    //     || event_->lumi == 1720)
    // {
    //   //skip the corresponding event
    //   continue;
    // }

    goodLumiEventCount++;

    //do routine for L1 emulator quantites
    if (emuOn){
      treeL1emu->GetEntry(jentry);
      // get jetEt*, egEt*, tauEt, htSum, mhtSum, etSum, metSum
      // ALL EMU OBJECTS HAVE BX=0...
      double jetEt_1 = 0;
      double jetEt_2 = 0;
      double jetEt_3 = 0;
      double jetEt_4 = 0;
      if (l1emu_->nJets>0) jetEt_1 = l1emu_->jetEt[0];
      if (l1emu_->nJets>1) jetEt_2 = l1emu_->jetEt[1];
      if (l1emu_->nJets>2) jetEt_3 = l1emu_->jetEt[2];
      if (l1emu_->nJets>3) jetEt_4 = l1emu_->jetEt[3];       
      
      double egEt_1 = 0;
      double egEt_2 = 0;
      //EG pt's are not given in descending order...bx?
      for (UInt_t c=0; c<l1emu_->nEGs; c++){
        if (l1emu_->egEt[c] > egEt_1){
          egEt_2 = egEt_1;
          egEt_1 = l1emu_->egEt[c];
        }
        else if (l1emu_->egEt[c] <= egEt_1 && l1emu_->egEt[c] > egEt_2){
          egEt_2 = l1emu_->egEt[c];
        }
      }

      double tauEt_1 = 0;
      double tauEt_2 = 0;
      //tau pt's are not given in descending order
      for (UInt_t c=0; c<l1emu_->nTaus; c++){
        if (l1emu_->tauEt[c] > tauEt_1){
          tauEt_2 = tauEt_1;
          tauEt_1 = l1emu_->tauEt[c];
        }
        else if (l1emu_->tauEt[c] <= tauEt_1 && l1emu_->tauEt[c] > tauEt_2){
          tauEt_2 = l1emu_->tauEt[c];
        }
      }

      double egISOEt_1 = 0;
      double egISOEt_2 = 0;
      //EG pt's are not given in descending order...bx?
      for (UInt_t c=0; c<l1emu_->nEGs; c++){
        if (l1emu_->egEt[c] > egISOEt_1 && l1emu_->egIso[c]==1){
          egISOEt_2 = egISOEt_1;
          egISOEt_1 = l1emu_->egEt[c];
        }
        else if (l1emu_->egEt[c] <= egISOEt_1 && l1emu_->egEt[c] > egISOEt_2 && l1emu_->egIso[c]==1){
          egISOEt_2 = l1emu_->egEt[c];
        }
      }

      double tauISOEt_1 = 0;
      double tauISOEt_2 = 0;
      //tau pt's are not given in descending order
      for (UInt_t c=0; c<l1emu_->nTaus; c++){
        if (l1emu_->tauEt[c] > tauISOEt_1 && l1emu_->tauIso[c]==1){
          tauISOEt_2 = tauISOEt_1;
          tauISOEt_1 = l1emu_->tauEt[c];
        }
        else if (l1emu_->tauEt[c] <= tauISOEt_1 && l1emu_->tauEt[c] > tauISOEt_2 && l1emu_->tauIso[c]==1){
          tauISOEt_2 = l1emu_->tauEt[c];
        }
      }

      double htSum = l1emu_->sumEt[1];
      double mhtSum = l1emu_->sumEt[3];
      double etSum = l1emu_->sumEt[0];
      double metSum = l1emu_->sumEt[2];

      // fill the distributions
      leadingJetDist_emu->Fill(jetEt_1);
      secondJetDist_emu->Fill(jetEt_2);
      thirdJetDist_emu->Fill(jetEt_3);
      fourthJetDist_emu->Fill(jetEt_4);
      htSumDist_emu->Fill(htSum);
      mhtSumDist_emu->Fill(mhtSum);
      etSumDist_emu->Fill(etSum);
      metSumDist_emu->Fill(metSum);
      leadingEgDist_emu->Fill(egEt_1);
      secondEgDist_emu->Fill(egEt_2);
      leadingTauDist_emu->Fill(tauEt_1);
      secondTauDist_emu->Fill(tauEt_2);
      leadingISOEgDist_emu->Fill(egISOEt_1);
      secondISOEgDist_emu->Fill(egISOEt_2);
      leadingISOTauDist_emu->Fill(tauISOEt_1);
      secondISOTauDist_emu->Fill(tauISOEt_2);

      // for each bin fill according to whether our object has a larger corresponding energy
      for(int bin=0; bin<nJetBins; bin++){
        if( (jetEt_1) >= jetLo + (bin*jetBinWidth) ) singleJetRates_emu->Fill(jetLo+(bin*jetBinWidth));  //GeV
      } 

      for(int bin=0; bin<nJetBins; bin++){
        if( (jetEt_2) >= jetLo + (bin*jetBinWidth) ) doubleJetRates_emu->Fill(jetLo+(bin*jetBinWidth));  //GeV
      }  

      for(int bin=0; bin<nJetBins; bin++){
        if( (jetEt_3) >= jetLo + (bin*jetBinWidth) ) tripleJetRates_emu->Fill(jetLo+(bin*jetBinWidth));  //GeV
      }  

      for(int bin=0; bin<nJetBins; bin++){
        if( (jetEt_4) >= jetLo + (bin*jetBinWidth) ) quadJetRates_emu->Fill(jetLo+(bin*jetBinWidth));  //GeV
      }  
             
      for(int bin=0; bin<nEgBins; bin++){
        if( (egEt_1) >= egLo + (bin*egBinWidth) ) singleEgRates_emu->Fill(egLo+(bin*egBinWidth));  //GeV
      } 

      for(int bin=0; bin<nEgBins; bin++){
        if( (egEt_2) >= egLo + (bin*egBinWidth) ) doubleEgRates_emu->Fill(egLo+(bin*egBinWidth));  //GeV
      }  

      for(int bin=0; bin<nTauBins; bin++){
        if( (tauEt_1) >= tauLo + (bin*tauBinWidth) ) singleTauRates_emu->Fill(tauLo+(bin*tauBinWidth));  //GeV
      }

      for(int bin=0; bin<nTauBins; bin++){
        if( (tauEt_2) >= tauLo + (bin*tauBinWidth) ) doubleTauRates_emu->Fill(tauLo+(bin*tauBinWidth));  //GeV
      } 

      for(int bin=0; bin<nEgBins; bin++){
        if( (egISOEt_1) >= egLo + (bin*egBinWidth) ) singleISOEgRates_emu->Fill(egLo+(bin*egBinWidth));  //GeV
      } 

      for(int bin=0; bin<nEgBins; bin++){
        if( (egISOEt_2) >= egLo + (bin*egBinWidth) ) doubleISOEgRates_emu->Fill(egLo+(bin*egBinWidth));  //GeV
      }  

      for(int bin=0; bin<nTauBins; bin++){
        if( (tauISOEt_1) >= tauLo + (bin*tauBinWidth) ) singleISOTauRates_emu->Fill(tauLo+(bin*tauBinWidth));  //GeV
      }

      for(int bin=0; bin<nTauBins; bin++){
        if( (tauISOEt_2) >= tauLo + (bin*tauBinWidth) ) doubleISOTauRates_emu->Fill(tauLo+(bin*tauBinWidth));  //GeV
      } 

      for(int bin=0; bin<nHtSumBins; bin++){
        if( (htSum) >= htSumLo+(bin*htSumBinWidth) ) htSumRates_emu->Fill(htSumLo+(bin*htSumBinWidth)); //GeV
      }

      for(int bin=0; bin<nMhtSumBins; bin++){
        if( (mhtSum) >= mhtSumLo+(bin*mhtSumBinWidth) ) mhtSumRates_emu->Fill(mhtSumLo+(bin*mhtSumBinWidth)); //GeV           
      }

      for(int bin=0; bin<nEtSumBins; bin++){
        if( (etSum) >= etSumLo+(bin*etSumBinWidth) ) etSumRates_emu->Fill(etSumLo+(bin*etSumBinWidth)); //GeV           
      }

      for(int bin=0; bin<nMetSumBins; bin++){
        if( (metSum) >= metSumLo+(bin*metSumBinWidth) ) metSumRates_emu->Fill(metSumLo+(bin*metSumBinWidth)); //GeV           
      }  
    }// closes if 'emuOn' is true


    //do routine for L1 hardware quantities
    if (hwOn){
      treeL1hw->GetEntry(jentry);
      // get jetEt*, egEt*, tauEt, htSum, mhtSum, etSum, metSum
      // ***INCLUDES NON_ZERO bx*** can't just read values off
      double jetEt_1 = 0;
      double jetEt_2 = 0;
      double jetEt_3 = 0;
      double jetEt_4 = 0;
      for (UInt_t c=0; c<l1hw_->nJets; c++){
        if (l1hw_->jetBx[c]==0 && l1hw_->jetEt[c] > jetEt_1){
          jetEt_4 = jetEt_3;
          jetEt_3 = jetEt_2;
          jetEt_2 = jetEt_1;
          jetEt_1 = l1hw_->jetEt[c];
        }
        else if (l1hw_->jetBx[c]==0 && l1hw_->jetEt[c] <= jetEt_1 && l1hw_->jetEt[c] > jetEt_2){
          jetEt_4 = jetEt_3;
          jetEt_3 = jetEt_2;      
          jetEt_2 = l1hw_->jetEt[c];
        }
        else if (l1hw_->jetBx[c]==0 && l1hw_->jetEt[c] <= jetEt_2 && l1hw_->jetEt[c] > jetEt_3){
          jetEt_4 = jetEt_3;     
          jetEt_3 = l1hw_->jetEt[c];
        }
        else if (l1hw_->jetBx[c]==0 && l1hw_->jetEt[c] <= jetEt_3 && l1hw_->jetEt[c] > jetEt_4){   
          jetEt_4 = l1hw_->jetEt[c];
        }
      }

      double egEt_1 = 0;
      double egEt_2 = 0;
      for (UInt_t c=0; c<l1hw_->nEGs; c++){
        if (l1hw_->egBx[c]==0 && l1hw_->egEt[c] > egEt_1){
          egEt_2 = egEt_1;
          egEt_1 = l1hw_->egEt[c];
        }
        else if (l1hw_->egBx[c]==0 && l1hw_->egEt[c] <= egEt_1 && l1hw_->egEt[c] > egEt_2){
          egEt_2 = l1hw_->egEt[c];
        }
      }

      double tauEt_1 = 0;
      double tauEt_2 = 0;
      //tau pt's are not given in descending order
      for (UInt_t c=0; c<l1hw_->nTaus; c++){
        if (l1hw_->tauBx[c]==0 && l1hw_->tauEt[c] > tauEt_1){
          tauEt_1 = l1hw_->tauEt[c];
        }
        else if (l1hw_->tauBx[c]==0 && l1hw_->tauEt[c] <= tauEt_1 && l1hw_->tauEt[c] > tauEt_2){
          tauEt_2 = l1hw_->tauEt[c];
        }
      }

      double egISOEt_1 = 0;
      double egISOEt_2 = 0;
      //EG pt's are not given in descending order...bx?
      for (UInt_t c=0; c<l1hw_->nEGs; c++){
        if (l1hw_->egBx[c]==0 && l1hw_->egEt[c] > egISOEt_1 && l1hw_->egIso[c]==1){
          egISOEt_2 = egISOEt_1;
          egISOEt_1 = l1hw_->egEt[c];
        }
        else if (l1hw_->egBx[c]==0 && l1hw_->egEt[c] <= egISOEt_1 && l1hw_->egEt[c] > egISOEt_2 && l1hw_->egIso[c]==1){
          egISOEt_2 = l1hw_->egEt[c];
        }
      }

      double tauISOEt_1 = 0;
      double tauISOEt_2 = 0;
      //tau pt's are not given in descending order
      for (UInt_t c=0; c<l1hw_->nTaus; c++){
        if (l1hw_->tauBx[c]==0 && l1hw_->tauEt[c] > tauISOEt_1 && l1hw_->tauIso[c]==1){
          tauISOEt_2 = tauISOEt_1;
          tauISOEt_1 = l1hw_->tauEt[c];
        }
        else if (l1hw_->tauBx[c]==0 && l1hw_->tauEt[c] <= tauISOEt_1 && l1hw_->tauEt[c] > tauISOEt_2 && l1hw_->tauIso[c]==1){
          tauISOEt_2 = l1hw_->tauEt[c];
        }
      }

      double htSum = 0;
      double mhtSum = 0;
      double etSum = 0;
      double metSum = 0;
      // HW includes -2,-1,0,1,2 bx info (hence the different numbers, could cause a seg fault if this changes)
      for (unsigned int c=0; c<l1hw_->sumEt.size(); c++){

        if (l1hw_->sumType[c]==0 && l1hw_->sumBx[c]==0) etSum = l1hw_->sumEt[c];
        if (l1hw_->sumType[c]==1 && l1hw_->sumBx[c]==0) htSum = l1hw_->sumEt[c];
        if (l1hw_->sumType[c]==2 && l1hw_->sumBx[c]==0) metSum = l1hw_->sumEt[c];
        if (l1hw_->sumType[c]==3 && l1hw_->sumBx[c]==0) mhtSum = l1hw_->sumEt[c];                
      }

      // fill the distributions
      leadingJetDist_hw->Fill(jetEt_1);
      secondJetDist_hw->Fill(jetEt_2);
      thirdJetDist_hw->Fill(jetEt_3);
      fourthJetDist_hw->Fill(jetEt_4);
      htSumDist_hw->Fill(htSum);
      mhtSumDist_hw->Fill(mhtSum);
      etSumDist_hw->Fill(etSum);
      metSumDist_hw->Fill(metSum);
      leadingEgDist_hw->Fill(egEt_1);
      secondEgDist_hw->Fill(egEt_2);
      leadingTauDist_hw->Fill(tauEt_1);
      secondTauDist_hw->Fill(tauEt_2);
      leadingISOEgDist_hw->Fill(egISOEt_1);
      secondISOEgDist_hw->Fill(egISOEt_2);
      leadingISOTauDist_hw->Fill(tauISOEt_1);
      secondISOTauDist_hw->Fill(tauISOEt_2);

      // for each bin fill according to whether our object has a larger corresponding energy
      for(int bin=0; bin<nJetBins; bin++){
        if( (jetEt_1) >= jetLo + (bin*jetBinWidth) ) singleJetRates_hw->Fill(jetLo+(bin*jetBinWidth));  //GeV
      } 

      for(int bin=0; bin<nJetBins; bin++){
        if( (jetEt_2) >= jetLo + (bin*jetBinWidth) ) doubleJetRates_hw->Fill(jetLo+(bin*jetBinWidth));  //GeV
      }  

      for(int bin=0; bin<nJetBins; bin++){
        if( (jetEt_3) >= jetLo + (bin*jetBinWidth) ) tripleJetRates_hw->Fill(jetLo+(bin*jetBinWidth));  //GeV
      }  

      for(int bin=0; bin<nJetBins; bin++){
        if( (jetEt_4) >= jetLo + (bin*jetBinWidth) ) quadJetRates_hw->Fill(jetLo+(bin*jetBinWidth));  //GeV
      }  
             
      for(int bin=0; bin<nEgBins; bin++){
        if( (egEt_1) >= egLo + (bin*egBinWidth) ) singleEgRates_hw->Fill(egLo+(bin*egBinWidth));  //GeV
      } 

      for(int bin=0; bin<nEgBins; bin++){
        if( (egEt_2) >= egLo + (bin*egBinWidth) ) doubleEgRates_hw->Fill(egLo+(bin*egBinWidth));  //GeV
      }  

      for(int bin=0; bin<nTauBins; bin++){
        if( (tauEt_1) >= tauLo + (bin*tauBinWidth) ) singleTauRates_hw->Fill(tauLo+(bin*tauBinWidth));  //GeV
      } 

      for(int bin=0; bin<nTauBins; bin++){
        if( (tauEt_2) >= tauLo + (bin*tauBinWidth) ) doubleTauRates_hw->Fill(tauLo+(bin*tauBinWidth));  //GeV
      } 

      for(int bin=0; bin<nEgBins; bin++){
        if( (egISOEt_1) >= egLo + (bin*egBinWidth) ) singleISOEgRates_hw->Fill(egLo+(bin*egBinWidth));  //GeV
      } 

      for(int bin=0; bin<nEgBins; bin++){
        if( (egISOEt_2) >= egLo + (bin*egBinWidth) ) doubleISOEgRates_hw->Fill(egLo+(bin*egBinWidth));  //GeV
      }  

      for(int bin=0; bin<nTauBins; bin++){
        if( (tauISOEt_1) >= tauLo + (bin*tauBinWidth) ) singleISOTauRates_hw->Fill(tauLo+(bin*tauBinWidth));  //GeV
      }

      for(int bin=0; bin<nTauBins; bin++){
        if( (tauISOEt_2) >= tauLo + (bin*tauBinWidth) ) doubleISOTauRates_hw->Fill(tauLo+(bin*tauBinWidth));  //GeV
      } 

      for(int bin=0; bin<nHtSumBins; bin++){
        if( (htSum) >= htSumLo+(bin*htSumBinWidth) ) htSumRates_hw->Fill(htSumLo+(bin*htSumBinWidth)); //GeV
      }

      for(int bin=0; bin<nMhtSumBins; bin++){
        if( (mhtSum) >= mhtSumLo+(bin*mhtSumBinWidth) ) mhtSumRates_hw->Fill(mhtSumLo+(bin*mhtSumBinWidth)); //GeV           
      }

      for(int bin=0; bin<nEtSumBins; bin++){
        if( (etSum) >= etSumLo+(bin*etSumBinWidth) ) etSumRates_hw->Fill(etSumLo+(bin*etSumBinWidth)); //GeV           
      }

      for(int bin=0; bin<nMetSumBins; bin++){
        if( (metSum) >= metSumLo+(bin*metSumBinWidth) ) metSumRates_hw->Fill(metSumLo+(bin*metSumBinWidth)); //GeV           
      }  
    }// closes if 'hwOn' is true

  }// closes loop through events

  TFile g( outputFilename.c_str() , "new");
  // normalisation factor for rate histograms (11kHz in the orbit frequency)
  // double norm = 11246*(numBunch/goodLumiEventCount); // no lumi rescale
  double norm = 11246*(numBunch/goodLumiEventCount)*(expectedLum/runLum); //scale to nominal lumi

  if (emuOn){
    singleJetRates_emu->Scale(norm);
    doubleJetRates_emu->Scale(norm);
    tripleJetRates_emu->Scale(norm);
    quadJetRates_emu->Scale(norm);
    singleEgRates_emu->Scale(norm);
    doubleEgRates_emu->Scale(norm);
    singleTauRates_emu->Scale(norm);
    doubleTauRates_emu->Scale(norm);
    singleISOEgRates_emu->Scale(norm);
    doubleISOEgRates_emu->Scale(norm);
    singleISOTauRates_emu->Scale(norm);
    doubleISOTauRates_emu->Scale(norm);
    htSumRates_emu->Scale(norm);
    mhtSumRates_emu->Scale(norm);
    etSumRates_emu->Scale(norm);
    metSumRates_emu->Scale(norm);

    //set the errors for the rates
    //want error -> error * sqrt(norm)

    singleJetRates_emu->Write();
    doubleJetRates_emu->Write();
    tripleJetRates_emu->Write();
    quadJetRates_emu->Write();
    singleEgRates_emu->Write();
    doubleEgRates_emu->Write();
    singleTauRates_emu->Write();
    doubleTauRates_emu->Write();
    singleISOEgRates_emu->Write();
    doubleISOEgRates_emu->Write();
    singleISOTauRates_emu->Write();
    doubleISOTauRates_emu->Write();
    htSumRates_emu->Write();
    mhtSumRates_emu->Write();
    etSumRates_emu->Write();
    metSumRates_emu->Write();

    leadingJetDist_emu->Write();
    secondJetDist_emu->Write();
    thirdJetDist_emu->Write();
    fourthJetDist_emu->Write();
    htSumDist_emu->Write();
    mhtSumDist_emu->Write();
    etSumDist_emu->Write();
    metSumDist_emu->Write();
    leadingEgDist_emu->Write();
    secondEgDist_emu->Write();
    leadingTauDist_emu->Write();
    secondTauDist_emu->Write();
    leadingISOEgDist_emu->Write();
    secondISOEgDist_emu->Write();
    leadingISOTauDist_emu->Write();
    secondISOTauDist_emu->Write();
  }

  if (hwOn){
    singleJetRates_hw->Scale(norm);
    doubleJetRates_hw->Scale(norm);
    tripleJetRates_hw->Scale(norm);
    quadJetRates_hw->Scale(norm);
    singleEgRates_hw->Scale(norm);
    doubleEgRates_hw->Scale(norm);
    singleTauRates_hw->Scale(norm);
    doubleTauRates_hw->Scale(norm);
    singleISOEgRates_hw->Scale(norm);
    doubleISOEgRates_hw->Scale(norm);
    singleISOTauRates_hw->Scale(norm);
    doubleISOTauRates_hw->Scale(norm);
    htSumRates_hw->Scale(norm);
    mhtSumRates_hw->Scale(norm);
    etSumRates_hw->Scale(norm);
    metSumRates_hw->Scale(norm);

    singleJetRates_hw->Write();
    doubleJetRates_hw->Write();
    tripleJetRates_hw->Write();
    quadJetRates_hw->Write();
    singleEgRates_hw->Write();
    doubleEgRates_hw->Write();
    singleTauRates_hw->Write();
    doubleTauRates_hw->Write();
    singleISOEgRates_hw->Write();
    doubleISOEgRates_hw->Write();
    singleISOTauRates_hw->Write();
    doubleISOTauRates_hw->Write();
    htSumRates_hw->Write();
    mhtSumRates_hw->Write();
    etSumRates_hw->Write();
    metSumRates_hw->Write();

    leadingJetDist_hw->Write();
    secondJetDist_hw->Write();
    thirdJetDist_hw->Write();
    fourthJetDist_hw->Write();
    htSumDist_hw->Write();
    mhtSumDist_hw->Write();
    etSumDist_hw->Write();
    metSumDist_hw->Write();
    leadingEgDist_hw->Write();
    secondEgDist_hw->Write();
    leadingTauDist_hw->Write();
    secondTauDist_hw->Write();
    leadingISOEgDist_hw->Write();
    secondISOEgDist_hw->Write();
    leadingISOTauDist_hw->Write();
    secondISOTauDist_hw->Write();
  }
  myfile << "using the following ntuple: " << inputFile01 << endl;
  myfile << "number of colliding bunches = " << numBunch << endl;
  myfile << "run luminosity = " << runLum << endl;
  myfile << "expected luminosity = " << expectedLum << endl; 
  myfile << "norm factor used = " << norm << endl;
  myfile << "number of good events = " << goodLumiEventCount << endl;
  myfile.close(); 
}//closes the function 'rates'