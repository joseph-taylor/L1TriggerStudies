#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
#include "TH1F.h"
#include "TH2F.h"
#include <iostream>
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
};  	





/////////////////
/////////////////
//MAIN FUNCTION//
/////////////////
/////////////////
void jets_data(){

  //create a ROOT file to save all the histograms to (actually at end of script)
  //first check the file doesn't exist already so we don't overwrite
  string dirName = "output_jets/run259721_zeroBiasReReco_intv14p0Layer1_noL1JEC_jst5/";
  string outputFilename = dirName + "histos.root";

  TFile *kk = TFile::Open( outputFilename.c_str() );
  if (kk!=0){
  cout << "TERMINATE:not going to overwrite file" << endl;
  return;
  }

  // make trees
  TChain * upgradeTree = new TChain("l1UpgradeEmuTree/L1UpgradeTree");
  TChain * mcTree = new TChain("l1ExtraTreeGenAk4/L1ExtraTree");

  upgradeTree->Add("/hdfs/L1JEC/L1JetEnergyCorrections/Stg2_Run2015D_run259721_zeroBiasReReco_intv14p0Layer1_noL1JEC_jst5/Run2015D_1/L1Ntuple_Stage2_ReReco_HF_noL1Jec_80X_dataRun2_v8_jst5_*.root");
  mcTree->Add("/hdfs/L1JEC/L1JetEnergyCorrections/Stg2_Run2015D_run259721_zeroBiasReReco_intv14p0Layer1_noL1JEC_jst5/Run2015D_1/L1Ntuple_Stage2_ReReco_HF_noL1Jec_80X_dataRun2_v8_jst5_*.root");
  
  Int_t nevent = (Int_t)mcTree->GetEntries();

  /////////////////////////////
  //PARAMETERS FOR THE SCRIPT//
  /////////////////////////////
  const double genJet_ETmin = 10;                //min ET(GeV) for genjet to be considered
  const double genJet_etaMaxCentral = 3.00;      //max eta for genjet to be CENTRAL
  const double genJet_etaMinHF = 3.50;           //max eta for genjet to be HF
  const double genJet_etaMaxHF = 4.50;           //max eta for genjet to be HF
  const double dR_matchMax = 0.40;               //max dR allowed for a turnOn 'match'
  //nb:hf actually is between 3<->5, but this keeps it isolated from edge effects

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

  //set the branch addresses
  L1Analysis::L1AnalysisL1ExtraDataFormat      *genJet_ = new L1Analysis::L1AnalysisL1ExtraDataFormat();
  mcTree->SetBranchAddress("L1Extra", &genJet_);

  L1Analysis::L1AnalysisL1UpgradeDataFormat    *upgrade_ = new L1Analysis::L1AnalysisL1UpgradeDataFormat();
  upgradeTree->SetBranchAddress("L1Upgrade", &upgrade_);





  ///////////////////////////////////////////
  //create the framework for the histograms//nb: WAC stands for 'with additional (recojet) cleaning'
  ///////////////////////////////////////////
  //comparison histos
  TH1F * hdPhi_central = new TH1F("hdPhi_central", ";#phi_{RECO} - #phi_{L1}", 100, -0.5, 0.5);
  TH1F * hdEta_central = new TH1F("hdEta_central", ";#eta_{RECO} - #eta_{L1}", 100, -0.5, 0.5);
  TH1F * hdR_central = new TH1F("hdR_central", ";dR_{RECO - L1}", 100, 0, 1.0);
  TH1F * hdET_central = new TH1F("hdET_central", ";(ET_{L1} - ET_{RECO})/ET_{RECO}", 100, -2.0, 4.0);
  TH2F * hETS_central = new TH2F("hETS_central", "", 500, 0, 250, 500, 0, 250);
  hETS_central->GetXaxis()->SetTitle("RECO E_{T} (GeV)");
  hETS_central->GetYaxis()->SetTitle("L1 upgrade E_{T} (GeV)");

  TH1F * hdPhi_hf = new TH1F("hdPhi_hf", ";#phi_{RECO} - #phi_{L1}", 100, -0.5, 0.5);
  TH1F * hdEta_hf = new TH1F("hdEta_hf", ";#eta_{RECO} - #eta_{L1}", 100, -0.5, 0.5);
  TH1F * hdR_hf = new TH1F("hdR_hf", ";dR_{RECO - L1}", 100, 0, 1.0);
  TH1F * hdET_hf = new TH1F("hdET_hf", ";(ET_{L1} - ET_{RECO})/ET_{RECO}", 100, -2.0, 4.0);
  TH2F * hETS_hf = new TH2F("hETS_hf", "", 500, 0, 250, 500, 0, 250);
  hETS_hf->GetXaxis()->SetTitle("RECO E_{T} (GeV)");
  hETS_hf->GetYaxis()->SetTitle("L1 upgrade E_{T} (GeV)");

  //turnOn histos
  //nb: num=numerator, den=denominator. At the bottom of script we create efficiency 'histos'
  TH1F * hden_central = new TH1F("hden_central", "", 40, 0, 400);
  TH1F * hnum36_central = new TH1F("hnum36_central", "", 40, 0, 400);
  TH1F * hT36_central = new TH1F("hT36_central", ";RECO Jet E_{T} (GeV);efficiency", 40, 0, 400);
  TH1F * hnum52_central = new TH1F("hnum52_central", "", 40, 0, 400);
  TH1F * hT52_central = new TH1F("hT52_central", ";RECO Jet E_{T} (GeV);efficiency", 40, 0, 400);
  TH1F * hnum68_central = new TH1F("hnum68_central", "", 40, 0, 400);
  TH1F * hT68_central = new TH1F("hT68_central", ";RECO Jet E_{T} (GeV);efficiency", 40, 0, 400);
  TH1F * hnum92_central = new TH1F("hnum92_central", "", 40, 0, 400);
  TH1F * hT92_central = new TH1F("hT92_central", ";RECO Jet E_{T} (GeV);efficiency", 40, 0, 400);
  TH1F * hnum128_central = new TH1F("hnum128_central", "", 40, 0, 400);
  TH1F * hT128_central = new TH1F("hT128_central", ";RECO Jet E_{T} (GeV);efficiency", 40, 0, 400);
  TH1F * hnum176_central = new TH1F("hnum176_central", "", 40, 0, 400);
  TH1F * hT176_central = new TH1F("hT176_central", ";RECO Jet E_{T} (GeV);efficiency", 40, 0, 400);
  TH1F * hnum200_central = new TH1F("hnum200_central", "", 40, 0, 400);
  TH1F * hT200_central = new TH1F("hT200_central", ";RECO Jet E_{T} (GeV);efficiency", 40, 0, 400);

  TH1F * hden_hf = new TH1F("hden_hf", "", 40, 0, 400);
  TH1F * hnum36_hf = new TH1F("hnum36_hf", "", 40, 0, 400);
  TH1F * hT36_hf = new TH1F("hT36_hf", ";RECO Jet E_{T} (GeV);efficiency", 40, 0, 400);
  TH1F * hnum52_hf = new TH1F("hnum52_hf", "", 40, 0, 400);
  TH1F * hT52_hf = new TH1F("hT52_hf", ";RECO Jet E_{T} (GeV);efficiency", 40, 0, 400);
  TH1F * hnum68_hf = new TH1F("hnum68_hf", "", 40, 0, 400);
  TH1F * hT68_hf = new TH1F("hT68_hf", ";RECO Jet E_{T} (GeV);efficiency", 40, 0, 400);
  TH1F * hnum92_hf = new TH1F("hnum92_hf", "", 40, 0, 400);
  TH1F * hT92_hf = new TH1F("hT92_hf", ";RECO Jet E_{T} (GeV);efficiency", 40, 0, 400);
  TH1F * hnum128_hf = new TH1F("hnum128_hf", "", 40, 0, 400);
  TH1F * hT128_hf = new TH1F("hT128_hf", ";RECO Jet E_{T} (GeV);efficiency", 40, 0, 400);
  TH1F * hnum176_hf = new TH1F("hnum176_hf", "", 40, 0, 400);
  TH1F * hT176_hf = new TH1F("hT176_hf", ";RECO Jet E_{T} (GeV);efficiency", 40, 0, 400);
  TH1F * hnum200_hf = new TH1F("hnum200_hf", "", 40, 0, 400);
  TH1F * hT200_hf = new TH1F("hT200_hf", ";RECO Jet E_{T} (GeV);efficiency", 40, 0, 400);




  ///////////////////////////////
  ///////////////////////////////
  //loop through all the events//
  ///////////////////////////////
  ///////////////////////////////
  for (Int_t i=0; i<100000; i++){
  //for (Int_t i=0; i<nevent; i++){
  			
  		//load the Tree info for the event
          int nb = mcTree->GetEntry(i);
          if (nb==0){
          cout << "did not load JetRecoTree for entry " << i << endl;
          return;}
          
          nb = upgradeTree->GetEntry(i);
          if (nb==0){
          cout << "did not load L1UpgradeTree for entry " << i << endl;
          return;}
                   
          //////////////////////////////////////
          ///analysis///////////////////////////
          //////////////////////////////////////
          //now fill in the jet structures for the event
          //how to read values
          //Int_t nJets = recoJet_->nJets;
          //vector<int> vec = upgrade_->jetIet;
          //vec[j]
   genjet.et = genJet_->cenJetEt;
   genjet.eta = genJet_->cenJetEta;
   genjet.phi = genJet_->cenJetPhi;
   genjet.n = genJet_->nCenJets;
          
           l1jet.et = upgrade_->jetEt;
           l1jet.eta = upgrade_->jetEta;
           l1jet.phi = upgrade_->jetPhi;
           l1jet.n = upgrade_->nJets;
           l1jet.bx = upgrade_->jetBx;
              
            bool central_logic = true;
            bool hf_logic = true;


          //currently setup so that we look at all...


          ///////////////////////////////////////////////
          //loop through all the reco jets for this event
          ///////////////////////////////////////////////
          for (UInt_t j=0; j<genjet.n; j++){   



            if(j==0){//this is to ensure that we only select the leading jets for turnOns
              central_logic = true;
              hf_logic = true;

            }


          //-------------------
          /////////////////////
          //Barrel and Endcap//
          /////////////////////
          //find CENTRAL jets in the RECO data with ET>recoJet_ETmin (20GeV)
          if (genjet.et[j] > recoJet_ETmin && abs(genjet.eta[j]) < recoJet_etaMaxCentral){
          

          //now loop through the Upgrade Jets to find
          //the best matching to the RECO jet in question (in terms of dR)
          double dR_min=99999.99;        //use to determine the best match jet
          UInt_t k_min=9999;             //use to index the best match jet
          
          int countL1=0;
          for (UInt_t k=0; k<l1jet.n; k++){
          if(l1jet.bx[k]==0){
          double dPhi = calc_dPHI( genjet.phi[j], l1jet.phi[k] );
          double dEta = calc_dETA( genjet.eta[j], l1jet.eta[k] );   
          double dR = calc_dR( dPhi, dEta);
          if (countL1==0){dR_min = dR; k_min = k;}
          if (countL1>0 && dR<dR_min){dR_min = dR; k_min = k;}
          countL1++;
          }
          }
          
          //NOW plot comparison histograms for 'central' info about our best match
          if (countL1 > 0){
          double dPhi = calc_dPHI( genjet.phi[j], l1jet.phi[k_min] ); //probs would be best off
          double dEta = calc_dETA( genjet.eta[j], l1jet.eta[k_min] ); //saving in one object...      
          hdPhi_central->Fill(dPhi);
          hdEta_central->Fill(dEta);
          hdR_central->Fill(dR_min);
          hdET_central->Fill( (l1jet.et[k_min]-genjet.et[j])/genjet.et[j] ); 
          hETS_central->Fill(genjet.et[j], l1jet.et[k_min] );
          }

          //NOW make the trigger turnOns for 'central'
          if(central_logic){
          hden_central->Fill(genjet.et[j]);
          central_logic = false;
          if (dR_min < dR_matchMax){
            if (l1jet.et[k_min]>36){
            hnum36_central->Fill(genjet.et[j]);
            }                
            if (l1jet.et[k_min]>52){
            hnum52_central->Fill(genjet.et[j]);
            }        
            if (l1jet.et[k_min]>68){
            hnum68_central->Fill(genjet.et[j]);
            }
            if (l1jet.et[k_min]>92){
            hnum92_central->Fill(genjet.et[j]);
            }                
            if (l1jet.et[k_min]>128){
            hnum128_central->Fill(genjet.et[j]);
            }        
            if (l1jet.et[k_min]>176){
            hnum176_central->Fill(genjet.et[j]);
            }
            if (l1jet.et[k_min]>200){
            hnum200_central->Fill(genjet.et[j]);
            }
          }//closes 'if' upgrade jet matches to the RECO jet
          }//closes 'if' central_logic==true



          }//closes 'if' reco jet is central and et>etmin
          //---------------------------------------------








          //-------------------
          /////////////////////
          // H F //////////////
          /////////////////////
          //find FORWARD jets in the RECO data with ET>recoJet_ETmin (20GeV)
          if (genjet.et[j] > recoJet_ETmin && abs(genjet.eta[j]) > recoJet_etaMinHF
                                            && abs(genjet.eta[j]) < recoJet_etaMaxHF){

          //now loop through the Upgrade Jets to find
          //the best matching to the RECO jet in question (in terms of dR)
          double dR_min=99999.99;        //use to determine the best match jet
          UInt_t k_min=9999;             //use to index the best match jet
          
          int countL1=0;
          for (UInt_t k=0; k<l1jet.n; k++){
          if(l1jet.bx[k]==0){
          double dPhi = calc_dPHI( genjet.phi[j], l1jet.phi[k] );
          double dEta = calc_dETA( genjet.eta[j], l1jet.eta[k] );   
          double dR = calc_dR( dPhi, dEta);
          if (countL1==0){dR_min = dR; k_min = k;}
          if (countL1>0 && dR<dR_min){dR_min = dR; k_min = k;}
          countL1++;
          }
          }
          
          //NOW plot comparison histograms for 'hf' info about our best match
          if (countL1 > 0){
          double dPhi = calc_dPHI( genjet.phi[j], l1jet.phi[k_min] ); //probs would be best off
          double dEta = calc_dETA( genjet.eta[j], l1jet.eta[k_min] ); //saving in one object...      
          hdPhi_hf->Fill(dPhi);
          hdEta_hf->Fill(dEta);
          hdR_hf->Fill(dR_min);
          hdET_hf->Fill( (l1jet.et[k_min]-genjet.et[j])/genjet.et[j] ); 
          hETS_hf->Fill(genjet.et[j], l1jet.et[k_min] );
          }

          //NOW make the trigger turnOns for 'hf'
          if(hf_logic){
          hden_hf->Fill(genjet.et[j]);
          hf_logic = false;
          if (dR_min < dR_matchMax){
            if (l1jet.et[k_min]>36){
            hnum36_hf->Fill(genjet.et[j]);
            }                
            if (l1jet.et[k_min]>52){
            hnum52_hf->Fill(genjet.et[j]);
            }        
            if (l1jet.et[k_min]>68){
            hnum68_hf->Fill(genjet.et[j]);
            }
            if (l1jet.et[k_min]>92){
            hnum92_hf->Fill(genjet.et[j]);
            }                
            if (l1jet.et[k_min]>128){
            hnum128_hf->Fill(genjet.et[j]);
            }        
            if (l1jet.et[k_min]>176){
            hnum176_hf->Fill(genjet.et[j]);
            }
            if (l1jet.et[k_min]>200){
            hnum200_hf->Fill(genjet.et[j]);
            }
          }//closes 'if' upgrade jet matches to the RECO jet
          }//closes 'if' hf_logic==true


          }//closes 'if' reco jet is Forward and et>etmin
          //---------------------------------------------


        }//closes loop through RECO jet entries for the given event 
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

  hdPhi_hf->Write();
  hdEta_hf->Write();
  hdR_hf->Write();
  hdET_hf->Write();
  hETS_hf->Write();


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

}//closes the 'main' function