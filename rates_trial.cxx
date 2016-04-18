#include "TMath.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TChain.h"
#include <iostream>
#include <string>
#include "L1Trigger/L1TNtuples/interface/L1AnalysisL1UpgradeDataFormat.h"

// todo: put errors in rates

void rates_trial(){
  
  bool hwOn = true;   //are we using data from hardware?
  bool emuOn = true;  //are we using data from emulator?

  if (hwOn==false && emuOn==false){
    cout << "exiting as neither hardware or emulator selected" << endl;
    return;
  }

  double numBunch = 2; //the number of bunches used for the run of interest
  double expectedLum = 1.15; //expected luminostiy of 2016 runs (*10^34)
  double runLum = 0.00037; //luminosity of the run of interest (*10^34)

  string outputFilename = "output_rates/run269224_zeroBias_v34p0_update/histos.root";
  TFile* kk = TFile::Open( outputFilename.c_str() );
  if (kk!=0){
    cout << "TERMINATE: not going to overwrite file " << outputFilename << endl;
    return;
  }

  // make trees
  TChain * treeL1emu = new TChain("l1UpgradeEmuTree/L1UpgradeTree");
  if (emuOn){
    treeL1emu->Add("/hdfs/L1JEC/CMSSW_8_0_2/L1JetEnergyCorrections/ZeroBias_run269224_v34p0/com2016_1/*.root");
    treeL1emu->Add("/hdfs/L1JEC/CMSSW_8_0_2/L1JetEnergyCorrections/ZeroBias_run269224_v34p0/com2016_2/*.root");
    treeL1emu->Add("/hdfs/L1JEC/CMSSW_8_0_2/L1JetEnergyCorrections/ZeroBias_run269224_v34p0/com2016_3/*.root");
    treeL1emu->Add("/hdfs/L1JEC/CMSSW_8_0_2/L1JetEnergyCorrections/ZeroBias_run269224_v34p0/com2016_4/*.root");
    treeL1emu->Add("/hdfs/L1JEC/CMSSW_8_0_2/L1JetEnergyCorrections/ZeroBias_run269224_v34p0/com2016_5/*.root");
    treeL1emu->Add("/hdfs/L1JEC/CMSSW_8_0_2/L1JetEnergyCorrections/ZeroBias_run269224_v34p0/com2016_6/*.root");
    treeL1emu->Add("/hdfs/L1JEC/CMSSW_8_0_2/L1JetEnergyCorrections/ZeroBias_run269224_v34p0/com2016_7/*.root");
    treeL1emu->Add("/hdfs/L1JEC/CMSSW_8_0_2/L1JetEnergyCorrections/ZeroBias_run269224_v34p0/com2016_8/*.root");
  }
  L1Analysis::L1AnalysisL1UpgradeDataFormat    *l1emu_ = new L1Analysis::L1AnalysisL1UpgradeDataFormat();
  treeL1emu->SetBranchAddress("L1Upgrade", &l1emu_);

  TChain * treeL1hw = new TChain("l1UpgradeTree/L1UpgradeTree");
  if (hwOn){
    treeL1hw->Add("/hdfs/L1JEC/CMSSW_8_0_2/L1JetEnergyCorrections/ZeroBias_run269224_v34p0/com2016_1/*.root");
    treeL1hw->Add("/hdfs/L1JEC/CMSSW_8_0_2/L1JetEnergyCorrections/ZeroBias_run269224_v34p0/com2016_2/*.root");
    treeL1hw->Add("/hdfs/L1JEC/CMSSW_8_0_2/L1JetEnergyCorrections/ZeroBias_run269224_v34p0/com2016_3/*.root");
    treeL1hw->Add("/hdfs/L1JEC/CMSSW_8_0_2/L1JetEnergyCorrections/ZeroBias_run269224_v34p0/com2016_4/*.root");
    treeL1hw->Add("/hdfs/L1JEC/CMSSW_8_0_2/L1JetEnergyCorrections/ZeroBias_run269224_v34p0/com2016_5/*.root");
    treeL1hw->Add("/hdfs/L1JEC/CMSSW_8_0_2/L1JetEnergyCorrections/ZeroBias_run269224_v34p0/com2016_6/*.root");
    treeL1hw->Add("/hdfs/L1JEC/CMSSW_8_0_2/L1JetEnergyCorrections/ZeroBias_run269224_v34p0/com2016_7/*.root");
    treeL1hw->Add("/hdfs/L1JEC/CMSSW_8_0_2/L1JetEnergyCorrections/ZeroBias_run269224_v34p0/com2016_8/*.root");    
  }
  L1Analysis::L1AnalysisL1UpgradeDataFormat    *l1hw_ = new L1Analysis::L1AnalysisL1UpgradeDataFormat();
  treeL1hw->SetBranchAddress("L1Upgrade", &l1hw_);

  // set parameters for histograms
  // jet bins
  int nJetBins = 200;
  float jetLo = 0.;
  float jetHi = 400.;
  float jetBinWidth = (jetHi-jetLo)/nJetBins;

  // EG bins
  int nEgBins = 150;
  float egLo = 0.;
  float egHi = 300.;
  float egBinWidth = (egHi-egLo)/nEgBins;

  // tau bins
  int nTauBins = 150;
  float tauLo = 0.;
  float tauHi = 300.;
  float tauBinWidth = (tauHi-tauLo)/nTauBins;

  // htSum bins
  int nHtSumBins = 300;
  float htSumLo = 0.;
  float htSumHi = 600.;
  float htSumBinWidth = (htSumHi-htSumLo)/nHtSumBins;

  // mhtSum bins
  int nMhtSumBins = 150;
  float mhtSumLo = 0.;
  float mhtSumHi = 300.;
  float mhtSumBinWidth = (mhtSumHi-mhtSumLo)/nMhtSumBins;

  // etSum bins
  int nEtSumBins = 300;
  float etSumLo = 0.;
  float etSumHi = 600.;
  float etSumBinWidth = (etSumHi-etSumLo)/nEtSumBins;

  // metSum bins
  int nMetSumBins = 150;
  float metSumLo = 0.;
  float metSumHi = 300.;
  float metSumBinWidth = (metSumHi-metSumLo)/nMetSumBins;

  //make histos
  TH1D* singleJetRates_emu = new TH1D("singleJetRates_emu", "", nJetBins, jetLo, jetHi);
  TH1D* doubleJetRates_emu = new TH1D("doubleJetRates_emu", "", nJetBins, jetLo, jetHi);
  TH1D* tripleJetRates_emu = new TH1D("tripleJetRates_emu", "", nJetBins, jetLo, jetHi);
  TH1D* quadJetRates_emu = new TH1D("quadJetRates_emu", "", nJetBins, jetLo, jetHi);
  TH1D* singleEgRates_emu = new TH1D("singleEgRates_emu", "", nEgBins, egLo, egHi);
  TH1D* doubleEgRates_emu = new TH1D("doubleEgRates_emu", "", nEgBins, egLo, egHi);
  TH1D* tauRates_emu = new TH1D("tauRates_emu", "", nTauBins, tauLo, tauHi);
  TH1D* htSumRates_emu = new TH1D("htSumRates_emu","", nHtSumBins, htSumLo, htSumHi);
  TH1D* mhtSumRates_emu = new TH1D("mhtSumRates_emu","", nMhtSumBins, mhtSumLo, mhtSumHi);
  TH1D* etSumRates_emu = new TH1D("etSumRates_emu","", nEtSumBins, etSumLo, etSumHi);
  TH1D* metSumRates_emu = new TH1D("metSumRates_emu","", nMetSumBins, metSumLo, metSumHi); 
  TH1D* leadingJetDist_emu = new TH1D("leadingJetDist_emu", "", nJetBins, jetLo, jetHi);
  TH1D* secondJetDist_emu = new TH1D("secondJetDist_emu", "", nJetBins, jetLo, jetHi);
  TH1D* thirdJetDist_emu = new TH1D("thirdJetDist_emu", "", nJetBins, jetLo, jetHi);
  TH1D* fourthJetDist_emu = new TH1D("fourthJetDist_emu", "", nJetBins, jetLo, jetHi);            
  TH1D* htSumDist_emu = new TH1D("htSumDist_emu","", nHtSumBins, htSumLo, htSumHi);
  TH1D* mhtSumDist_emu = new TH1D("mhtSumDist_emu","", nMhtSumBins, mhtSumLo, mhtSumHi);
  TH1D* etSumDist_emu = new TH1D("etSumDist_emu","", nEtSumBins, etSumLo, etSumHi);
  TH1D* metSumDist_emu = new TH1D("metSumDist_emu","", nMetSumBins, metSumLo, metSumHi); 
  TH1D* leadingEgDist_emu = new TH1D("leadingEgDist_emu", "", nEgBins, egLo, egHi);
  TH1D* secondEgDist_emu = new TH1D("secondEgDist_emu", "", nEgBins, egLo, egHi);
  TH1D* leadingTauDist_emu = new TH1D("leadingTauDist_emu", "", nTauBins, tauLo, tauHi);

  TH1D* singleJetRates_hw = new TH1D("singleJetRates_hw", "", nJetBins, jetLo, jetHi);
  TH1D* doubleJetRates_hw = new TH1D("doubleJetRates_hw", "", nJetBins, jetLo, jetHi);
  TH1D* tripleJetRates_hw = new TH1D("tripleJetRates_hw", "", nJetBins, jetLo, jetHi);
  TH1D* quadJetRates_hw = new TH1D("quadJetRates_hw", "", nJetBins, jetLo, jetHi);
  TH1D* singleEgRates_hw = new TH1D("singleEgRates_hw", "", nEgBins, egLo, egHi);
  TH1D* doubleEgRates_hw = new TH1D("doubleEgRates_hw", "", nEgBins, egLo, egHi);
  TH1D* tauRates_hw = new TH1D("tauRates_hw", "", nTauBins, tauLo, tauHi);
  TH1D* htSumRates_hw = new TH1D("htSumRates_hw","", nHtSumBins, htSumLo, htSumHi);
  TH1D* mhtSumRates_hw = new TH1D("mhtSumRates_hw","", nMhtSumBins, mhtSumLo, mhtSumHi);
  TH1D* etSumRates_hw = new TH1D("etSumRates_hw","", nEtSumBins, etSumLo, etSumHi);
  TH1D* metSumRates_hw = new TH1D("metSumRates_hw","", nMetSumBins, metSumLo, metSumHi); 
  TH1D* leadingJetDist_hw = new TH1D("leadingJetDist_hw", "", nJetBins, jetLo, jetHi);
  TH1D* secondJetDist_hw = new TH1D("secondJetDist_hw", "", nJetBins, jetLo, jetHi);
  TH1D* thirdJetDist_hw = new TH1D("thirdJetDist_hw", "", nJetBins, jetLo, jetHi);
  TH1D* fourthJetDist_hw = new TH1D("fourthJetDist_hw", "", nJetBins, jetLo, jetHi);            
  TH1D* htSumDist_hw = new TH1D("htSumDist_hw","", nHtSumBins, htSumLo, htSumHi);
  TH1D* mhtSumDist_hw = new TH1D("mhtSumDist_hw","", nMhtSumBins, mhtSumLo, mhtSumHi);
  TH1D* etSumDist_hw = new TH1D("etSumDist_hw","", nEtSumBins, etSumLo, etSumHi);
  TH1D* metSumDist_hw = new TH1D("metSumDist_hw","", nMetSumBins, metSumLo, metSumHi); 
  TH1D* leadingEgDist_hw = new TH1D("leadingEgDist_hw", "", nEgBins, egLo, egHi);
  TH1D* secondEgDist_hw = new TH1D("secondEgDist_hw", "", nEgBins, egLo, egHi);
  TH1D* leadingTauDist_hw = new TH1D("leadingTauDist_hw", "", nTauBins, tauLo, tauHi);


  // get number of entries
  Long64_t nentries = treeL1emu->GetEntries();  
  /////////////////////////////////
  // loop through all the entries//
  /////////////////////////////////
  for (Long64_t jentry=0; jentry<nentries; jentry++){
    if((jentry%10000)==0) std::cout << "Done " << jentry  << " events of " << nentries << std::endl;

    //do routine for L1 emulator quantites
    if (emuOn){
      treeL1emu->GetEntry(jentry);
      // get jetEt*, egEt*, tauEt, htSum, mhtSum, etSum, metSum
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
      //EG pt's are not given in descending order
      for (UInt_t c=0; c<l1emu_->nEGs; c++){
        if (l1emu_->egEt[c] >= egEt_1){
          egEt_2 = egEt_1;
          egEt_1 = l1emu_->egEt[c];
        }
        else if (l1emu_->egEt[c] < egEt_1 && l1emu_->egEt[c] > egEt_2){
          egEt_2 = l1emu_->egEt[c];
        }
      }

      double tauEt = 0;
      //tau pt's are not given in descending order
      for (UInt_t c=0; c<l1emu_->nTaus; c++){
        if (l1emu_->tauEt[c] > tauEt){
          tauEt = l1emu_->tauEt[c];
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
      leadingTauDist_emu->Fill(tauEt);

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
        if( (tauEt) >= tauLo + (bin*tauBinWidth) ) tauRates_emu->Fill(tauLo+(bin*tauBinWidth));  //GeV
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
      double jetEt_1 = 0;
      double jetEt_2 = 0;
      double jetEt_3 = 0;
      double jetEt_4 = 0;
      //jet's in hardware are not ordered!!
      for (UInt_t c=0; c<l1hw_->nJets; c++){
        if (l1hw_->jetEt[c] >= jetEt_1){
          jetEt_4 = jetEt_3;
          jetEt_3 = jetEt_2;
          jetEt_2 = jetEt_1;
          jetEt_1 = l1hw_->jetEt[c];
        }
        else if (l1hw_->jetEt[c] < jetEt_1 && l1hw_->jetEt[c] > jetEt_2){
          jetEt_4 = jetEt_3;
          jetEt_3 = jetEt_2;      
          jetEt_2 = l1hw_->jetEt[c];
        }
        else if (l1hw_->jetEt[c] < jetEt_2 && l1hw_->jetEt[c] > jetEt_3){
          jetEt_4 = jetEt_3;     
          jetEt_3 = l1hw_->jetEt[c];
        }
        else if (l1hw_->jetEt[c] < jetEt_3 && l1hw_->jetEt[c] > jetEt_4){   
          jetEt_4 = l1hw_->jetEt[c];
        }

      }
        
      double egEt_1 = 0;
      double egEt_2 = 0;
      //EG pt's are not given in descending order
      for (UInt_t c=0; c<l1hw_->nEGs; c++){
        if (l1hw_->egEt[c] >= egEt_1){
          egEt_2 = egEt_1;
          egEt_1 = l1hw_->egEt[c];
        }
        else if (l1hw_->egEt[c] < egEt_1 && l1hw_->egEt[c] > egEt_2){
          egEt_2 = l1hw_->egEt[c];
        }
      }

      double tauEt = 0;
      //tau pt's are not given in descending order
      for (UInt_t c=0; c<l1hw_->nTaus; c++){
        if (l1hw_->tauEt[c] > tauEt){
          tauEt = l1hw_->tauEt[c];
        }
      }
                 
      double htSum = l1hw_->sumEt[1];
      double mhtSum = l1hw_->sumEt[3];
      double etSum = l1hw_->sumEt[0];
      double metSum = l1hw_->sumEt[2];

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
      leadingTauDist_hw->Fill(tauEt);

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
        if( (tauEt) >= tauLo + (bin*tauBinWidth) ) tauRates_hw->Fill(tauLo+(bin*tauBinWidth));  //GeV
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

  // normalisation factor for rate histograms
  double norm = 11246*(numBunch/nentries)*(expectedLum/runLum); //11kHz in the orbit frequency
  TFile g( outputFilename.c_str() , "new");
  
  if (emuOn){
    singleJetRates_emu->Scale(norm);
    doubleJetRates_emu->Scale(norm);
    tripleJetRates_emu->Scale(norm);
    quadJetRates_emu->Scale(norm);
    singleEgRates_emu->Scale(norm);
    doubleEgRates_emu->Scale(norm);
    tauRates_emu->Scale(norm);
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
    tauRates_emu->Write();
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
  }

  if (hwOn){
    singleJetRates_hw->Scale(norm);
    doubleJetRates_hw->Scale(norm);
    tripleJetRates_hw->Scale(norm);
    quadJetRates_hw->Scale(norm);
    singleEgRates_hw->Scale(norm);
    doubleEgRates_hw->Scale(norm);
    tauRates_hw->Scale(norm);
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
    tauRates_hw->Write();
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
  }
 
}//closes the function 'rates'