#include "TMath.h"
#include "TFile.h"
#include "TTree.h"
#include "TH2F.h"
#include "TChain.h"
#include <iostream>
#include <string>
#include "L1Trigger/L1TNtuples/interface/L1AnalysisL1CaloTowerDataFormat.h"
#include "L1Trigger/L1TNtuples/interface/L1AnalysisL1UpgradeDataFormat.h"

//currently only for et
//could also do met, ht and mht

// //function: add two pt vectors together in the (2d) transverse plane
// //output: first element is magnitude, second element is phi
// vector<float> addTwoVectors(float pt1, float phi1, float pt2, float phi2){
// 	vector<float> output;
// 	float xpt = pt1*cos(phi1) + pt2*cos(phi2);
// 	float ypt = pt1*sin(phi1) + pt2*sin(phi2);
// 	output.push_back(sqrt(pow(xpt,2)+pow(ypt,2)));
// 	float phiOut = atan(ypt/xpt);
//     if ( xpt < 0 && ypt > 0 ){phiOut = phiOut + M_PI;}
//     if ( xpt < 0 && ypt < 0 ){phiOut = phiOut - M_PI;}
// 	output.push_back(phiOut);
// 	return output;
// }




        // vector<float> recoMetVec;
        // recoMetVec.push_back(recoMet_->met);
        // recoMetVec.push_back(recoMet_->metPhi);
        // for(UInt_t k=0; k<muon.n; k++){
        // if(muon.looseID[k]){
        // // recoSums.htt = recoSums.htt - muon.et[k];
        // recoSums.ett = recoSums.ett - muon.et[k];
        // // recoMhtVec = addTwoVectors(recoMhtVec[0], recoMhtVec[1], muon.et[k], muon.phi[k]);
        // recoMetVec = addTwoVectors(recoMetVec[0], recoMetVec[1], muon.et[k], muon.phi[k]);
        // }




void test_sums(){

	string outputFilename = "output_testSums/ZeroBiasReReco_run259721_6Apr_jetmetUpdateForJoe_L1JEC/histos.root";
  	TFile* kk = TFile::Open( outputFilename.c_str() );
	if (kk!=0){
		cout << "TERMINATE: not going to overwrite file" << endl;
		return;
	}

	// make trees
	TChain * treeL1Up = new TChain("l1UpgradeEmuTree/L1UpgradeTree");
	TChain * treeL1Towers = new TChain("l1CaloTowerEmuTree/L1CaloTowerTree");
	treeL1Up->Add("/hdfs/L1JEC/CMSSW_8_0_2/L1JetEnergyCorrections/ZeroBiasReReco_run259721_6Apr_jetmetUpdateForJoe_L1JEC/Run2015D_1/L1Ntuple_*.root");
	treeL1Up->Add("/hdfs/L1JEC/CMSSW_8_0_2/L1JetEnergyCorrections/ZeroBiasReReco_run259721_6Apr_jetmetUpdateForJoe_L1JEC/Run2015D_2/L1Ntuple_*.root");
	treeL1Towers->Add("/hdfs/L1JEC/CMSSW_8_0_2/L1JetEnergyCorrections/ZeroBiasReReco_run259721_6Apr_jetmetUpdateForJoe_L1JEC/Run2015D_1/L1Ntuple_*.root");
	treeL1Towers->Add("/hdfs/L1JEC/CMSSW_8_0_2/L1JetEnergyCorrections/ZeroBiasReReco_run259721_6Apr_jetmetUpdateForJoe_L1JEC/Run2015D_2/L1Ntuple_*.root");

	// set branch addresses
	L1Analysis::L1AnalysisL1UpgradeDataFormat    *upgrade_ = new L1Analysis::L1AnalysisL1UpgradeDataFormat();
	treeL1Up->SetBranchAddress("L1Upgrade", &upgrade_);

	L1Analysis::L1AnalysisL1CaloTowerDataFormat  *l1Tower_ = new L1Analysis::L1AnalysisL1CaloTowerDataFormat();
	treeL1Towers->SetBranchAddress("L1CaloTower", &l1Tower_);

	//make the histos
	TH2F * h_ETT = new TH2F("h_ETT", "", 200, 0, 1000, 200, 0, 1000);
	h_ETT->GetXaxis()->SetTitle("L1 ETT (GeV)");
	h_ETT->GetYaxis()->SetTitle("recalculated ETT (GeV)");

	// get entries
	Long64_t nentries = treeL1Up->GetEntries();  

	// loop through all the entries
	nentries = 100000;
	for (Long64_t jentry=0; jentry<nentries; jentry++){

		if((jentry%10000)==0) std::cout << "Done " << jentry  << " events of " << nentries << std::endl;
		treeL1Up->GetEntry(jentry);
		treeL1Towers->GetEntry(jentry);

		//get the sum values
		double etSum = upgrade_->sumEt[0];
		// double metSum = upgrade_->sumEt[2];
		// double htSum = upgrade_->sumEt[1];
		// double mhtSum = upgrade_->sumEt[3];

		//make sum values
		double etCalc = 0;
		for (UInt_t c=0; c<l1Tower_->ieta.size(); c++){
			if ( abs(l1Tower_->ieta[c]) <= 28 ){
				etCalc = etCalc + 0.5 * l1Tower_->iet[c];
			}
		}

		//fill the histos
		h_ETT->Fill(etSum, etCalc);

	}//closes loop through events

	// write histos
	TFile g( outputFilename.c_str() , "new");
	h_ETT->Write();
}