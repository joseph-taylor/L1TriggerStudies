#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
#include "TH1F.h"
#include "TH2F.h"
#include <iostream>
#include <math.h>
#include <vector>
#include <string>

/* 
creates turnOn efficiencies and comparison histograms for jets
How to use:
1. select l1==hw/emu && ref==pf/gen (~lines 80-83)
2. select one cleaning option for central pf jets and one cleaning option for forward pf jets (~lines 105-115)
3. write the output directory name (~line 120) ***triggerType, runNumber, version, HW/EMU and PF/GEN, cleaningInformation!!!***MAKE SURE IT EXISTS
4. setup the TChains with the right file locations (~line 135+)...keeping a log in path2Ntuples.txt

other option a: can select the efficiency thresholds (~line 273+)
*/

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
#include "L1Trigger/L1TNtuples/interface/L1AnalysisL1ExtraDataFormat.h"
//#include "L1Trigger/L1TNtuples/interface/L1AnalysisRecoVertexDataFormat.h"
//#include "L1Trigger/L1TNtuples/interface/L1AnalysisRecoTrackDataFormat.h"
//#include "L1Trigger/L1TNtuples/interface/L1AnalysisL1MenuDataFormat.h"
#include "L1Trigger/L1TNtuples/interface/L1AnalysisL1UpgradeDataFormat.h"
//#include "L1Trigger/L1TNtuples/interface/L1AnalysisL1CaloTowerDataFormat.h"
//#include "L1Trigger/L1TNtuples/interface/L1AnalysisCaloTPDataFormat.h"
//#include "L1Trigger/L1TNtuples/interface/L1AnalysisRecoMetFilterDataFormat.h"

bool tightJetID_central(float,float,float,float,float,float,short,short,short,short,short);
bool tightLepVeto_central(float,float,float,float,float,float,short,short,short,short,short);
bool tightLepVetoElMultZero_central(float,float,float,float,float,float,short,short,short,short,short);
bool tightLepVetoMuMultZero_central(float,float,float,float,float,float,short,short,short,short,short);
bool tightLepVetoMuElMultZero_central(float,float,float,float,float,float,short,short,short,short,short);
bool tightJetID_hf(float,short,short);
bool centralJetCleaning(string,float,float,float,float,float,float,short,short,short,short,short);
bool hfJetCleaning(string,float,short,short);
double calc_dPHI(double,double);
double calc_dETA(double,double);
double calc_dR(double,double);
  	
//Jet structure
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

//MAIN FUNCTION
void jets(){

  bool hwOn = true;  //are we using data from hardware?
  bool emuOn = false;  //are we using data from emulator?
  bool recoOn = true; //are we using reco data?
  bool mcOn = false;  //are we using mc data?

  if (hwOn==false && emuOn==false){
    cout << "exiting as neither hardware or emulator selected" << endl;
    return;}

  if (hwOn==true && emuOn==true){
    cout << "exiting as both hardware and emulator selected" << endl;
    return;}

  if (recoOn==false && mcOn==false){
    cout << "exiting as neither reco or mc selected" << endl;
    return;}

  if (hwOn==true && emuOn==true){
    cout << "exiting as both reco and mc selected" << endl;
    return;}

  if (hwOn==true && mcOn==true){
    cout << "exiting as selecting hardware and mc doesn't make sense" << endl;
    return;}

  // pick one of the following cleaning cuts for pf_central
  // string typeOfCleaning_central = "noCleaning_central";
  // string typeOfCleaning_central = "tightJetID_central";
  // string typeOfCleaning_central = "tightLepVeto_central";
  // string typeOfCleaning_central = "tightLepVetoElMultZero_central";
  string typeOfCleaning_central = "tightLepVetoMuMultZero_central";
  // string typeOfCleaning_central = "tightLepVetoMuElMultZero_central";

  // pick one of the following cleaning cuts for pf_hf
  // string typeOfCleaning_hf = "noCleaning_hf";
  string typeOfCleaning_hf = "tightJetID_hf";


  //create a ROOT file to save all the histograms to (actually at end of script)
  //first check the file doesn't exist already so we don't overwrite
  string dirName = "output_jets/runXXXXXX_singleMuon_807intv48p0_hwPf_cenTightLepVetoMuZero_hfTightJetID/"; //***runNumber, triggerType, version, HW/EMU and PF/GEN, cleaningInformation!!!***
  string outputFilename = dirName + "histos.root";

  TFile *kk = TFile::Open( outputFilename.c_str() );
  if (kk!=0){
  cout << "TERMINATE:not going to overwrite file" << endl;
  return;
  }

  // make trees
  cout << "Loading up the TChains..." << endl;
  TChain * l1emuTree = new TChain("l1UpgradeEmuTree/L1UpgradeTree");
  TChain * l1hwTree = new TChain("l1UpgradeTree/L1UpgradeTree");
  TChain * recoTree = new TChain("l1JetRecoTree/JetRecoTree");
  TChain * mcTree = new TChain("l1ExtraTreeGenAk4/L1ExtraTree");

  if (emuOn){
    l1emuTree->Add("");
  }

  if (hwOn){
    l1hwTree->Add("root://eoscms.cern.ch//eos/cms/store/group/dpg_trigger/comm_trigger/L1Trigger/L1Menu2016/Stage2/Collision2016-RECO-l1t-integration-v48p0-CMSSW-807/SingleMuon/crab_Collision2016-RECO-l1t-integration-v48p0-CMSSW-807__SingleMuon/160511_154953/0000/*.root");
  }

  if (recoOn){
    recoTree->Add("root://eoscms.cern.ch//eos/cms/store/group/dpg_trigger/comm_trigger/L1Trigger/L1Menu2016/Stage2/Collision2016-RECO-l1t-integration-v48p0-CMSSW-807/SingleMuon/crab_Collision2016-RECO-l1t-integration-v48p0-CMSSW-807__SingleMuon/160511_154953/0000/*.root");
  }

  if (mcOn){
      mcTree->Add("");
  }

  //Parameters for the script (nb:hf actually is between 3<->5, but this keeps it isolated from edge effects)
  const double refJet_ETmin = 10;                //min ET(GeV) for REF jet to be considered
  const double refJet_etaMaxCentral = 3.00;      //max eta for REF jet to be CENTRAL
  const double refJet_etaMinHF = 3.50;           //max eta for REF jet to be HF
  const double refJet_etaMaxHF = 4.50;           //max eta for REF jet to be HF
  const double dR_matchMax = 0.40;                //max dR allowed for a turnOn 'match'

  //Structures for script
  struct Jet refjet;
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
  L1Analysis::L1AnalysisL1UpgradeDataFormat    *l1emu_ = new L1Analysis::L1AnalysisL1UpgradeDataFormat();
  l1emuTree->SetBranchAddress("L1Upgrade", &l1emu_);
  L1Analysis::L1AnalysisL1UpgradeDataFormat    *l1hw_ = new L1Analysis::L1AnalysisL1UpgradeDataFormat();
  l1hwTree->SetBranchAddress("L1Upgrade", &l1hw_);
  L1Analysis::L1AnalysisRecoJetDataFormat      *recoJet_ = new L1Analysis::L1AnalysisRecoJetDataFormat();
  recoTree->SetBranchAddress("Jet", &recoJet_);
  L1Analysis::L1AnalysisL1ExtraDataFormat      *genJet_ = new L1Analysis::L1AnalysisL1ExtraDataFormat();
  mcTree->SetBranchAddress("L1Extra", &genJet_);

  //create the framework for the histograms
  // phi bins
  int nPhiBins = 100;
  float phiLo = -0.5;
  float phiHi = 0.5;

  // eta bins
  int nEtaBins = 100;
  float etaLo = -0.5;
  float etaHi = 0.5;

  // dR bins
  int ndRBins = 100;
  float dRLo = 0;
  float dRHi = 1.0;

  // et bins
  int nEtBins = 100;
  float etLo = -2.0;
  float etHi = 4.0;

  // l1EtScat bins
  int nL1EtScatBins = 500;
  float L1EtScatLo = 0;
  float L1EtScatmHi = 250;

  // refEtScat bins
  int nRefEtScatBins = 500;
  float refEtScatLo = 0;
  float refEtScatHi = 250;

  //comparison histos
  TH1F * hdPhi_central = new TH1F("hdPhi_central", ";#phi_{ref} - #phi_{L1}", nPhiBins, phiLo, phiHi);
  TH1F * hdEta_central = new TH1F("hdEta_central", ";#eta_{ref} - #eta_{L1}", nEtaBins, etaLo, etaHi);
  TH1F * hdR_central = new TH1F("hdR_central", ";dR_{ref - L1}", ndRBins, dRLo, dRHi);
  TH1F * hdET_central = new TH1F("hdET_central", ";(ET_{L1} - ET_{ref})/ET_{ref}", nEtBins, etLo, etHi);
  TH2F * hPosScat_central = new TH2F("hPosScat_central", "", nPhiBins, phiLo, phiHi, nEtaBins, etaLo, etaHi);
  hPosScat_central->GetXaxis()->SetTitle("#phi_{ref} - #phi_{L1}");
  hPosScat_central->GetYaxis()->SetTitle("#eta_{ref} - #eta_{L1}");
  TH2F * hETS_central = new TH2F("hETS_central", "", nRefEtScatBins, refEtScatLo, refEtScatHi, nL1EtScatBins, L1EtScatLo, L1EtScatmHi);
  hETS_central->GetXaxis()->SetTitle("ref E_{T} (GeV)");
  hETS_central->GetYaxis()->SetTitle("L1 upgrade E_{T} (GeV)");

  TH1F * hdPhi_hf = new TH1F("hdPhi_hf", ";#phi_{ref} - #phi_{L1}", nPhiBins, phiLo, phiHi);
  TH1F * hdEta_hf = new TH1F("hdEta_hf", ";#eta_{ref} - #eta_{L1}", nEtaBins, etaLo, etaHi);
  TH1F * hdR_hf = new TH1F("hdR_hf", ";dR_{ref - L1}", ndRBins, dRLo, dRHi);
  TH1F * hdET_hf = new TH1F("hdET_hf", ";(ET_{L1} - ET_{ref})/ET_{ref}", nEtBins, etLo, etHi);
  TH2F * hPosScat_hf = new TH2F("hPosScat_hf", "", nPhiBins, phiLo, phiHi, nEtaBins, etaLo, etaHi);
  hPosScat_hf->GetXaxis()->SetTitle("#phi_{ref} - #phi_{L1}");
  hPosScat_hf->GetYaxis()->SetTitle("#eta_{ref} - #eta_{L1}");
  TH2F * hETS_hf = new TH2F("hETS_hf", "", nRefEtScatBins, refEtScatLo, refEtScatHi, nL1EtScatBins, L1EtScatLo, L1EtScatmHi);
  hETS_hf->GetXaxis()->SetTitle("ref E_{T} (GeV)");
  hETS_hf->GetYaxis()->SetTitle("L1 upgrade E_{T} (GeV)");

  // turnOn bins
  int nTurnOnBins = 40;
  float turnOnLo = 0;
  float turnOnHi = 400;

  // turnOns histos
  // nb: num=numerator, den=denominator. At the bottom of script we create the ratio
  vector<TH1F*> vectorOfNumsCentral;
  vector<TH1F*> vectorOfEffsCentral;
  vector<TH1F*> vectorOfNumsHF;
  vector<TH1F*> vectorOfEffsHF;

  vector<int> thresholdsVector;
  thresholdsVector.push_back(36);
  thresholdsVector.push_back(52);
  thresholdsVector.push_back(68);
  thresholdsVector.push_back(92);
  thresholdsVector.push_back(128);
  thresholdsVector.push_back(176);
  thresholdsVector.push_back(200);

  for (unsigned int c=0; c<thresholdsVector.size(); c++){
    string thresholdString = to_string(thresholdsVector[c]);
    string centralNumName = "hnum" + thresholdString + "_central";
    string hfNumName = "hnum" + thresholdString + "_hf";
    TH1F * h1 = new TH1F(centralNumName.c_str(), "", nTurnOnBins, turnOnLo, turnOnHi);
    TH1F * h2 = new TH1F(hfNumName.c_str(), "", nTurnOnBins, turnOnLo, turnOnHi);
    vectorOfNumsCentral.push_back(h1);
    vectorOfNumsHF.push_back(h2);
  }
  TH1F * hden_central = new TH1F("hden_central", "", nTurnOnBins, turnOnLo, turnOnHi);
  TH1F * hden_hf = new TH1F("hden_hf", "", nTurnOnBins, turnOnLo, turnOnHi);

  ////////////////////////////////
  // loop through all the events//
  ////////////////////////////////
  Long64_t nevent;
  if (recoOn){nevent = recoTree->GetEntries();}
  if (mcOn){nevent = mcTree->GetEntries();}
  for (Long64_t i=0; i<nevent; i++){
  	
    if (emuOn){l1emuTree->GetEntry(i);}
    if (hwOn){l1hwTree->GetEntry(i);}
    if (recoOn){recoTree->GetEntry(i);}
    if (mcOn){mcTree->GetEntry(i);}    
              
    //////////////////////////////////////
    ///analysis///////////////////////////
    //////////////////////////////////////
    //now fill in the jet structures for the event
    //how to read values
    //Int_t nJets = recoJet_->nJets;
    //vector<int> vec = upgrade_->jetIet;
    //vec[j]

    if (recoOn){
      refjet.et = recoJet_->et;
      refjet.eta = recoJet_->eta;
      refjet.phi = recoJet_->phi;
      refjet.n = recoJet_->nJets;
      refjet.nhef = recoJet_->nhef;
      refjet.pef = recoJet_->pef;
      refjet.mef = recoJet_->mef;
      refjet.chef = recoJet_->chef;
      refjet.eef = recoJet_->eef;
      refjet.chMult = recoJet_->chMult;
      refjet.nhMult = recoJet_->nhMult;
      refjet.phMult = recoJet_->phMult;
      refjet.elMult = recoJet_->elMult;
      refjet.muMult = recoJet_->muMult;
    }
    if (mcOn){
      refjet.et = genJet_->cenJetEt;
      refjet.eta = genJet_->cenJetEta;
      refjet.phi = genJet_->cenJetPhi;
      refjet.n = genJet_->nCenJets;
    }
    if (emuOn){
      l1jet.et = l1emu_->jetEt;
      l1jet.eta = l1emu_->jetEta;
      l1jet.phi = l1emu_->jetPhi;
      l1jet.n = l1emu_->nJets;
      l1jet.bx = l1emu_->jetBx;
    }
    if (hwOn){
      l1jet.et = l1hw_->jetEt;
      l1jet.eta = l1hw_->jetEta;
      l1jet.phi = l1hw_->jetPhi;
      l1jet.n = l1hw_->nJets;
      l1jet.bx = l1hw_->jetBx;
    }

    bool central_logic = false;
    bool hf_logic = false;
    int centralIndex;
    int hfIndex;

    // finds the ref jets we wish to compare l1jets against
    if (recoOn){
      // insert the reco cleaning you wish to apply to central (see list of functions up top)
      for (UInt_t j=0; j<refjet.n; j++){   
        if (refjet.et[j] > refJet_ETmin
            && abs(refjet.eta[j]) < refJet_etaMaxCentral
            && centralJetCleaning(typeOfCleaning_central.c_str(), refjet.eta[j], refjet.nhef[j], refjet.pef[j], refjet.mef[j], refjet.chef[j], refjet.eef[j],
                                   refjet.chMult[j], refjet.nhMult[j], refjet.phMult[j], refjet.elMult[j], refjet.muMult[j])
            ){
          centralIndex = j;
          central_logic = true;
          break;
        }
      }
      // insert the reco cleaning you wish to apply to hf (see list of functions up top)
      for (UInt_t j=0; j<refjet.n; j++){   
        if (refjet.et[j] > refJet_ETmin
            && abs(refjet.eta[j]) > refJet_etaMinHF
            && abs(refjet.eta[j]) < refJet_etaMaxHF
            && hfJetCleaning(typeOfCleaning_hf.c_str(), refjet.pef[j], refjet.nhMult[j], refjet.phMult[j])
            ){   
          hfIndex = j;
          hf_logic = true;
          break;
        }
      }
    }// closes 'if' recoOn
    

    if (mcOn){
      for (UInt_t j=0; j<refjet.n; j++){   
        if (refjet.et[j] > refJet_ETmin
            && abs(refjet.eta[j]) < refJet_etaMaxCentral){
          centralIndex = j;
          central_logic = true;
          break;
        }
      }
      for (UInt_t j=0; j<refjet.n; j++){   
        if (refjet.et[j] > refJet_ETmin
            && abs(refjet.eta[j]) > refJet_etaMinHF
            && abs(refjet.eta[j]) < refJet_etaMaxHF){   
          hfIndex = j;
          hf_logic = true;
          break;
        }
      }
    }// closes 'if' mcOn


    /////////////////////
    //Barrel and Endcap//
    /////////////////////
    if (central_logic){
    
      //now loop through the Upgrade Jets to find
      //the best matching to the REF jet in question (in terms of dR)
      double dR_min=99999.99;        //use to determine the best match jet
      UInt_t k_min=9999;             //use to index the best match jet          
      int countL1=0;                 //use this quantity as bx may be zero for some l1 jets

      for (UInt_t k=0; k<l1jet.n; k++){
        if(l1jet.bx[k]==0){
          double dPhi = calc_dPHI( refjet.phi[centralIndex], l1jet.phi[k] );
          double dEta = calc_dETA( refjet.eta[centralIndex], l1jet.eta[k] );   
          double dR = calc_dR( dPhi, dEta);
          if (countL1==0){dR_min = dR; k_min = k;}
          if (countL1>0 && dR<dR_min){dR_min = dR; k_min = k;}
          countL1++;
        }
      }
      
      //now make plots and turnOns using the best match
      hden_central->Fill(refjet.et[centralIndex]);
      if (countL1==0){hETS_central->Fill(refjet.et[centralIndex],0);}     
      if (countL1 > 0){
        double dPhi = calc_dPHI( refjet.phi[centralIndex], l1jet.phi[k_min] );
        double dEta = calc_dETA( refjet.eta[centralIndex], l1jet.eta[k_min] );     
        hdPhi_central->Fill(dPhi);
        hdEta_central->Fill(dEta);
        hdR_central->Fill(dR_min);
        hPosScat_central->Fill(dPhi, dEta);
        hdET_central->Fill( (l1jet.et[k_min]-refjet.et[centralIndex])/refjet.et[centralIndex] ); 
        hETS_central->Fill(refjet.et[centralIndex], l1jet.et[k_min] );
        
        if (dR_min < dR_matchMax){
          for (unsigned int c=0; c<thresholdsVector.size(); c++){
            if (l1jet.et[k_min]>thresholdsVector[c]){
              vectorOfNumsCentral[c]->Fill(refjet.et[centralIndex]);
            }
          }
        }//closes 'if' upgrade jet matches to the REF jet
      }//closes 'if' we have countL1>0
    }//closes 'if' central logic. ie we have a ref jet


    //////
    //hf//
    //////
    if (hf_logic){
    
      //now loop through the Upgrade Jets to find
      //the best matching to the REF jet in question (in terms of dR)
      double dR_min=99999.99;        //use to determine the best match jet
      UInt_t k_min=9999;             //use to index the best match jet          
      int countL1=0;                 //use this quantity as bx may be zero for some l1 jets

      for (UInt_t k=0; k<l1jet.n; k++){
        if(l1jet.bx[k]==0){
          double dPhi = calc_dPHI( refjet.phi[hfIndex], l1jet.phi[k] );
          double dEta = calc_dETA( refjet.eta[hfIndex], l1jet.eta[k] );   
          double dR = calc_dR( dPhi, dEta);
          if (countL1==0){dR_min = dR; k_min = k;}
          if (countL1>0 && dR<dR_min){dR_min = dR; k_min = k;}
          countL1++;
        }
      }
      
      //now make plots and turnOns using the best match
      hden_hf->Fill(refjet.et[hfIndex]);
      if (countL1==0){hETS_hf->Fill(refjet.et[hfIndex],0);}
      if (countL1 > 0){
        double dPhi = calc_dPHI( refjet.phi[hfIndex], l1jet.phi[k_min] );
        double dEta = calc_dETA( refjet.eta[hfIndex], l1jet.eta[k_min] );     
        hdPhi_hf->Fill(dPhi);
        hdEta_hf->Fill(dEta);
        hdR_hf->Fill(dR_min);
        hdET_hf->Fill( (l1jet.et[k_min]-refjet.et[hfIndex])/refjet.et[hfIndex] ); 
        hETS_hf->Fill(refjet.et[hfIndex], l1jet.et[k_min] );
        hPosScat_hf->Fill(dPhi, dEta);        

        if (dR_min < dR_matchMax){
          for (unsigned int c=0; c<thresholdsVector.size(); c++){
            if (l1jet.et[k_min]>thresholdsVector[c]){
              vectorOfNumsHF[c]->Fill(refjet.et[hfIndex]);
            }
          }
        }//closes 'if' upgrade jet matches to the REF jet
      }//closes 'if' we have countL1>0
    }//closes 'if' hf logic. ie we have a ref jet


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
  hPosScat_central->Write();

  hdPhi_hf->Write();
  hdEta_hf->Write();
  hdR_hf->Write();
  hdET_hf->Write();
  hETS_hf->Write();
  hPosScat_hf->Write();

  hden_central->Write();
  hden_hf->Write();
  for (unsigned int c=0; c<thresholdsVector.size(); c++){

    string thresholdString = to_string(thresholdsVector[c]);
    string centralEffName = "hT" + thresholdString + "_central";
    string hfEffName = "hT" + thresholdString + "_hf";
    TH1F * heff1 = new TH1F(centralEffName.c_str(), ";Offline Jet E_{T} (GeV);Efficiency", nTurnOnBins, turnOnLo, turnOnHi);
    TH1F * heff2 = new TH1F(hfEffName.c_str(), ";Offline Jet E_{T} (GeV);Efficiency", nTurnOnBins, turnOnLo, turnOnHi);
    heff1->Divide(vectorOfNumsCentral[c], hden_central);
    heff2->Divide(vectorOfNumsHF[c], hden_hf);
    vectorOfEffsCentral.push_back(heff1);
    vectorOfEffsHF.push_back(heff2);
    vectorOfNumsCentral[c]->Write();
    vectorOfNumsHF[c]->Write();
    vectorOfEffsCentral[c]->Write();
    vectorOfEffsHF[c]->Write();
  }

}//closes the 'main' function


bool centralJetCleaning(string typeOfCleaning_central, float eta, float nhef, float pef, float mef, float chef, float eef,
                        short chMult, short nhMult, short phMult, short elMult, short muMult){

  bool jetPassCentral = true;

  if (typeOfCleaning_central=="noCleaning_central")jetPassCentral = true;
  if (typeOfCleaning_central=="tightJetID_central"){
    jetPassCentral = tightJetID_central(eta,nhef,pef,mef,chef,eef,chMult,nhMult,phMult,elMult,muMult);
  }
  if (typeOfCleaning_central=="tightLepVeto_central"){
    jetPassCentral = tightLepVeto_central(eta,nhef,pef,mef,chef,eef,chMult,nhMult,phMult,elMult,muMult);    
  }
  if (typeOfCleaning_central=="tightLepVetoElMultZero_central"){
    jetPassCentral = tightLepVetoElMultZero_central(eta,nhef,pef,mef,chef,eef,chMult,nhMult,phMult,elMult,muMult);       
  }
  if (typeOfCleaning_central=="tightLepVetoMuMultZero_central"){
     jetPassCentral = tightLepVetoMuMultZero_central(eta,nhef,pef,mef,chef,eef,chMult,nhMult,phMult,elMult,muMult);   
  }   
  if (typeOfCleaning_central=="tightLepVetoMuElMultZero_central"){
      jetPassCentral = tightLepVetoMuElMultZero_central(eta,nhef,pef,mef,chef,eef,chMult,nhMult,phMult,elMult,muMult);    
    } 
  return jetPassCentral;
}

bool hfJetCleaning(string typeOfCleaning_hf, float pef, short nhMult, short phMult){

  bool jetPassHF = true;

  if (typeOfCleaning_hf=="noCleaning_hf")jetPassHF = true;
  if (typeOfCleaning_hf=="tightJetID_hf"){
      jetPassHF = tightJetID_hf(pef,nhMult,phMult);    
  }
  return jetPassHF;
}

bool tightJetID_central(float eta, float nhef, float pef, float mef, float chef, float eef,
                        short chMult, short nhMult, short phMult, short elMult, short muMult){
  //nb:this function does not use mef:but this way we keep the same input framework
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

// additionally includes 0 electron multiplicity
bool tightLepVetoElMultZero_central(float eta, float nhef, float pef, float mef, float chef, float eef,
                                     short chMult, short nhMult, short phMult, short elMult, short muMult){
  bool jetPass;
  if (elMult==0 &&
        abs(eta)<=3.00 && nhef<0.90 && pef<0.90 && (chMult+nhMult+phMult+elMult+muMult)>1 && mef<0.8    
        && (abs(eta)>2.4||(abs(eta)<=2.4 && chef>0 && (chMult+elMult+muMult)>0 && eef<0.90))){
    jetPass = true;}//this jet has passed
  else{jetPass = false;}//this jet has failed, or is outside the central zone           
  return jetPass;
}

// additionally includes 0 muon multiplicity (good for when running on single muon dataset for example)
bool tightLepVetoMuMultZero_central(float eta, float nhef, float pef, float mef, float chef, float eef,
                                     short chMult, short nhMult, short phMult, short elMult, short muMult){
  bool jetPass;
  if (muMult==0 &&
        abs(eta)<=3.00 && nhef<0.90 && pef<0.90 && (chMult+nhMult+phMult+elMult+muMult)>1 && mef<0.8    
        && (abs(eta)>2.4||(abs(eta)<=2.4 && chef>0 && (chMult+elMult+muMult)>0 && eef<0.90))){
    jetPass = true;}//this jet has passed
  else{jetPass = false;}//this jet has failed, or is outside the central zone           
  return jetPass;
}

// additionally includes 0 electron or muon multiplicity
bool tightLepVetoMuElMultZero_central(float eta, float nhef, float pef, float mef, float chef, float eef,
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
