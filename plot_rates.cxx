#include "TFile.h"
#include "TH1F.h"
#include "TStyle.h"
#include <TCanvas.h>
#include <string>
#include <iostream>

// improve by packaging this up
// todo: wrap this up in functions


// void individual_plot(string dirName, int numberOfHistos, string histoName, string outPutFileName,
// 					 string xaxisName, string yaxisName, double xStartPoint, double xFinishPoint){


// 	string inputFileName = dirName + "histos.root";
// 	TFile * f = new TFile( fileName.c_str() );
// 	if (f==0){
// 		cout << "Cannot load file " << inputFileName << endl;
// 		return;
// 	}

//     TH1F * h = (TH1F*)f->Get( histoName.c_str() );
//     if (h==0){
//       cout << "Cannot open histogram" << endl;

//       return;}



//     TH1F * singleJetRatesEmu = (TH1F*)f->Get("singleJetRates_emu");
//     singleJetRatesEmu->SetLineColor(2);
//     singleJetRatesEmu->SetLineWidth(2);
//     singleJetRatesEmu->GetXaxis()->SetTitle("single L1emu Jet E_{T} Threshold (GeV)");
//     singleJetRatesEmu->GetYaxis()->SetTitle("Rate (Hz)");    
// 	//singleJetRatesEmu->GetXaxis()->SetRangeUser(0,300);
// 	//singleJetRatesEmu->GetYaxis()->SetRangeUser(10,200000);
// 	TCanvas * cEMU_jet1 = new TCanvas("cEMU_jet1","",650,600);
// 	gPad->SetLogy();	
// 	gStyle->SetOptStat(0);
// 	singleJetRatesEmu->Draw();
// 	string singleJetRatesEmuSaveName = dirName + "singleJetRatesEmu.pdf";
// 	cEMU_jet1->SaveAs( singleJetRatesEmuSaveName.c_str() );
// 	cEMU_jet1->Close();



// }






void plot_rates(){

	string dirName = "output_rates/run269224_zeroBias_v34p0_update/";

	string fileName = dirName + "histos.root";
	TFile * f = new TFile( fileName.c_str() );
	if (f==0){
		cout << "Cannot load file" << endl;
		return;
	}

 //    TH1F * singleJetRatesEmu = (TH1F*)f->Get("singleJetRates_emu");
 //    TH1F * singleJetRatesHW = (TH1F*)f->Get("singleJetRates_hw");   
 //    singleJetRatesEmu->SetLineColor(2);
 //    singleJetRatesEmu->SetLineWidth(2);
 //    singleJetRatesHW->SetLineWidth(2);
 //    singleJetRatesEmu->GetXaxis()->SetTitle("single L1 Jet E_{T} Threshold (GeV)");
 //    singleJetRatesEmu->GetYaxis()->SetTitle("Rate (Hz)");    
	// //singleJetRatesEmu->GetXaxis()->SetRangeUser(0,300);
	// //singleJetRatesEmu->GetYaxis()->SetRangeUser(10,200000);
	// TCanvas * cEMU_jet1 = new TCanvas("cEMU_jet1","",650,600);
	// gPad->SetLogy();	
	// gStyle->SetOptStat(0);
	// singleJetRatesEmu->Draw();
	// singleJetRatesHW->Draw("same");
	// string singleJetRatesEmuSaveName = dirName + "singleJetRatesEmuHW.pdf";
	// cEMU_jet1->SaveAs( singleJetRatesEmuSaveName.c_str() );
	// cEMU_jet1->Close();

	TH1F * doubleJetRatesEmu = (TH1F*)f->Get("doubleJetRates_emu");
		TH1F * doubleJetRatesHW = (TH1F*)f->Get("doubleJetRates_hw");
    doubleJetRatesEmu->SetLineColor(2);
    doubleJetRatesEmu->SetLineWidth(2);
    doubleJetRatesHW->SetLineWidth(2);
    doubleJetRatesEmu->GetXaxis()->SetTitle("double L1 Jet E_{T} Threshold (GeV)");
    doubleJetRatesEmu->GetYaxis()->SetTitle("Rate (Hz)");    
	//doubleJetRatesEmu->GetXaxis()->SetRangeUser(0,300);
	//doubleJetRatesEmu->GetYaxis()->SetRangeUser(10,200000);
	TCanvas * cEMU_jet2 = new TCanvas("cEMU_jet2","",650,600);
	gPad->SetLogy();	
	gStyle->SetOptStat(0);
	doubleJetRatesEmu->Draw();
	doubleJetRatesHW->Draw("same");
	string doubleJetRatesEmuSaveName = dirName + "doubleJetRatesEmuHW.pdf";
	cEMU_jet2->SaveAs( doubleJetRatesEmuSaveName.c_str() );
	cEMU_jet2->Close();

	// TH1F * tripleJetRatesEmu = (TH1F*)f->Get("tripleJetRates_emu");
	// 	TH1F * tripleJetRatesHW = (TH1F*)f->Get("tripleJetRates_hw");
 //    tripleJetRatesEmu->SetLineColor(2);
 //    tripleJetRatesEmu->SetLineWidth(2);
 //    tripleJetRatesHW->SetLineWidth(2);
 //    tripleJetRatesEmu->GetXaxis()->SetTitle("triple L1 Jet E_{T} Threshold (GeV)");
 //    tripleJetRatesEmu->GetYaxis()->SetTitle("Rate (Hz)");    
	// //tripleJetRatesEmu->GetXaxis()->SetRangeUser(0,300);
	// //tripleJetRatesEmu->GetYaxis()->SetRangeUser(10,200000);
	// TCanvas * cEMU_jet3 = new TCanvas("cEMU_jet3","",650,600);
	// gPad->SetLogy();	
	// gStyle->SetOptStat(0);
	// tripleJetRatesEmu->Draw();
	// tripleJetRatesHW->Draw("same");
	// string tripleJetRatesEmuSaveName = dirName + "tripleJetRatesEmuHW.pdf";
	// cEMU_jet3->SaveAs( tripleJetRatesEmuSaveName.c_str() );
	// cEMU_jet3->Close();

	// TH1F * quadJetRatesEmu = (TH1F*)f->Get("quadJetRates_emu");
	// 	TH1F * quadJetRatesHW = (TH1F*)f->Get("quadJetRates_hw");
 //    quadJetRatesEmu->SetLineColor(2);
 //    quadJetRatesEmu->SetLineWidth(2);
 //    quadJetRatesHW->SetLineWidth(2);
 //    quadJetRatesEmu->GetXaxis()->SetTitle("quad L1 Jet E_{T} Threshold (GeV)");
 //    quadJetRatesEmu->GetYaxis()->SetTitle("Rate (Hz)");    
	// //quadJetRatesEmu->GetXaxis()->SetRangeUser(0,300);
	// //quadJetRatesEmu->GetYaxis()->SetRangeUser(10,200000);
	// TCanvas * cEMU_jet4 = new TCanvas("cEMU_jet4","",650,600);
	// gPad->SetLogy();	
	// gStyle->SetOptStat(0);
	// quadJetRatesEmu->Draw();
	// quadJetRatesHW->Draw("same");
	// string quadJetRatesEmuSaveName = dirName + "quadJetRatesEmuHW.pdf";
	// cEMU_jet4->SaveAs( quadJetRatesEmuSaveName.c_str() );
	// cEMU_jet4->Close();

	// TH1F * singleEgRatesEmu = (TH1F*)f->Get("singleEgRates_emu");
	// 	TH1F * singleEgRatesHW = (TH1F*)f->Get("singleEgRates_hw");
 //    singleEgRatesEmu->SetLineColor(2);
 //    singleEgRatesEmu->SetLineWidth(2);
 //    singleEgRatesHW->SetLineWidth(2);
 //    singleEgRatesEmu->GetXaxis()->SetTitle("single L1 EG E_{T} Threshold (GeV)");
 //    singleEgRatesEmu->GetYaxis()->SetTitle("Rate (Hz)");    
	// //singleEgRatesEmu->GetXaxis()->SetRangeUser(0,300);
	// //singleEgRatesEmu->GetYaxis()->SetRangeUser(10,200000);
	// TCanvas * cEMU_eg1 = new TCanvas("cEMU_eg1","",650,600);
	// gPad->SetLogy();	
	// gStyle->SetOptStat(0);
	// singleEgRatesEmu->Draw();
	// singleEgRatesHW->Draw("same");
	// string singleEgRatesEmuSaveName = dirName + "singleEgRatesEmuHW.pdf";
	// cEMU_eg1->SaveAs( singleEgRatesEmuSaveName.c_str() );
	// cEMU_eg1->Close();

	// TH1F * doubleEgRatesEmu = (TH1F*)f->Get("doubleEgRates_emu");
	// 	TH1F * doubleEgRatesHW = (TH1F*)f->Get("doubleEgRates_hw");
 //    doubleEgRatesEmu->SetLineColor(2);
 //    doubleEgRatesEmu->SetLineWidth(2);
 //    doubleEgRatesHW->SetLineWidth(2);
 //    doubleEgRatesEmu->GetXaxis()->SetTitle("double L1 EG E_{T} Threshold (GeV)");
 //    doubleEgRatesEmu->GetYaxis()->SetTitle("Rate (Hz)");    
	// //doubleEgRatesEmu->GetXaxis()->SetRangeUser(0,300);
	// //doubleEgRatesEmu->GetYaxis()->SetRangeUser(10,200000);
	// TCanvas * cEMU_eg2 = new TCanvas("cEMU_eg2","",650,600);
	// gPad->SetLogy();	
	// gStyle->SetOptStat(0);
	// doubleEgRatesEmu->Draw();
	// doubleEgRatesHW->Draw("same");
	// string doubleEgRatesEmuSaveName = dirName + "doubleEgRatesEmuHW.pdf";
	// cEMU_eg2->SaveAs( doubleEgRatesEmuSaveName.c_str() );
	// cEMU_eg2->Close();

	// TH1F * tauRatesEmu = (TH1F*)f->Get("tauRates_emu");
	// 	TH1F * tauRatesHW = (TH1F*)f->Get("tauRates_hw");
 //    tauRatesEmu->SetLineColor(2);
 //    tauRatesEmu->SetLineWidth(2);
 //    tauRatesHW->SetLineWidth(2);
 //    tauRatesEmu->GetXaxis()->SetTitle("L1 tau E_{T} Threshold (GeV)");
 //    tauRatesEmu->GetYaxis()->SetTitle("Rate (Hz)");    
	// //tauRatesEmu->GetXaxis()->SetRangeUser(0,300);
	// //tauRatesEmu->GetYaxis()->SetRangeUser(10,200000);
	// TCanvas * cEMU_tau = new TCanvas("cEMU_tau","",650,600);
	// gPad->SetLogy();	
	// gStyle->SetOptStat(0);
	// tauRatesEmu->Draw();
	// tauRatesHW->Draw("same");
	// string tauRatesEmuSaveName = dirName + "tauRatesEmuHW.pdf";
	// cEMU_tau->SaveAs( tauRatesEmuSaveName.c_str() );
	// cEMU_tau->Close();

	// TH1F * htSumRatesEmu = (TH1F*)f->Get("htSumRates_emu");
	// 	TH1F * htSumRatesHW = (TH1F*)f->Get("htSumRates_hw");
 //    htSumRatesEmu->SetLineColor(2);
 //    htSumRatesEmu->SetLineWidth(2);
 //    htSumRatesHW->SetLineWidth(2);
 //    htSumRatesEmu->GetXaxis()->SetTitle("L1 HTT Threshold (GeV)");
 //    htSumRatesEmu->GetYaxis()->SetTitle("Rate (Hz)");    
	// //htSumRatesEmu->GetXaxis()->SetRangeUser(0,300);
	// //htSumRatesEmu->GetYaxis()->SetRangeUser(10,200000);
	// TCanvas * cEMU_htSum = new TCanvas("cEMU_htSum","",650,600);
	// gPad->SetLogy();	
	// gStyle->SetOptStat(0);
	// htSumRatesEmu->Draw();
	// htSumRatesHW->Draw("same");
	// string htSumRatesEmuSaveName = dirName + "htSumRatesEmuHW.pdf";
	// cEMU_htSum->SaveAs( htSumRatesEmuSaveName.c_str() );
	// cEMU_htSum->Close();

	// TH1F * mhtSumRatesEmu = (TH1F*)f->Get("mhtSumRates_emu");
	// 	TH1F * mhtSumRatesHW = (TH1F*)f->Get("mhtSumRates_hw");
 //    mhtSumRatesEmu->SetLineColor(2);
 //    mhtSumRatesEmu->SetLineWidth(2);
 //    mhtSumRatesHW->SetLineWidth(2);
 //    mhtSumRatesEmu->GetXaxis()->SetTitle("L1 MHT Threshold (GeV)");
 //    mhtSumRatesEmu->GetYaxis()->SetTitle("Rate (Hz)");    
	// //mhtSumRatesEmu->GetXaxis()->SetRangeUser(0,300);
	// //mhtSumRatesEmu->GetYaxis()->SetRangeUser(10,200000);
	// TCanvas * cEMU_mhtSum = new TCanvas("cEMU_mhtSum","",650,600);
	// gPad->SetLogy();	
	// gStyle->SetOptStat(0);
	// mhtSumRatesEmu->Draw();
	// mhtSumRatesHW->Draw("same");
	// string mhtSumRatesEmuSaveName = dirName + "mhtSumRatesEmuHW.pdf";
	// cEMU_mhtSum->SaveAs( mhtSumRatesEmuSaveName.c_str() );
	// cEMU_mhtSum->Close();

	// TH1F * etSumRatesEmu = (TH1F*)f->Get("etSumRates_emu");
	// 	TH1F * etSumRatesHW = (TH1F*)f->Get("etSumRates_hw");
 //    etSumRatesEmu->SetLineColor(2);
 //    etSumRatesEmu->SetLineWidth(2);
 //    etSumRatesHW->SetLineWidth(2);
 //    etSumRatesEmu->GetXaxis()->SetTitle("L1 ETT Threshold (GeV)");
 //    etSumRatesEmu->GetYaxis()->SetTitle("Rate (Hz)");    
	// //etSumRatesEmu->GetXaxis()->SetRangeUser(0,300);
	// //etSumRatesEmu->GetYaxis()->SetRangeUser(10,200000);
	// TCanvas * cEMU_etSum = new TCanvas("cEMU_etSum","",650,600);
	// gPad->SetLogy();	
	// gStyle->SetOptStat(0);
	// etSumRatesEmu->Draw();
	// etSumRatesHW->Draw("same");
	// string etSumRatesEmuSaveName = dirName + "etSumRatesEmuHW.pdf";
	// cEMU_etSum->SaveAs( etSumRatesEmuSaveName.c_str() );
	// cEMU_etSum->Close();

	// TH1F * metSumRatesEmu = (TH1F*)f->Get("metSumRates_emu");
	// 	TH1F * metSumRatesHW = (TH1F*)f->Get("metSumRates_hw");
 //    metSumRatesEmu->SetLineColor(2);
 //    metSumRatesEmu->SetLineWidth(2);
 //    metSumRatesHW->SetLineWidth(2);
 //    metSumRatesEmu->GetXaxis()->SetTitle("L1 MET Threshold (GeV)");
 //    metSumRatesEmu->GetYaxis()->SetTitle("Rate (Hz)");    
	// //metSumRatesEmu->GetXaxis()->SetRangeUser(0,300);
	// //metSumRatesEmu->GetYaxis()->SetRangeUser(10,200000);
	// TCanvas * cEMU_metSum = new TCanvas("cEMU_metSum","",650,600);
	// gPad->SetLogy();	
	// gStyle->SetOptStat(0);
	// metSumRatesEmu->Draw();
	// metSumRatesHW->Draw("same");
	// string metSumRatesEmuSaveName = dirName + "metSumRatesEmuHW.pdf";
	// cEMU_metSum->SaveAs( metSumRatesEmuSaveName.c_str() );				
	// cEMU_metSum->Close();









 //    TH1F * singleJetRatesEmu = (TH1F*)f->Get("singleJetRates_emu");
 //    singleJetRatesEmu->SetLineColor(2);
 //    singleJetRatesEmu->SetLineWidth(2);
 //    singleJetRatesEmu->GetXaxis()->SetTitle("single L1emu Jet E_{T} Threshold (GeV)");
 //    singleJetRatesEmu->GetYaxis()->SetTitle("Rate (Hz)");    
	// //singleJetRatesEmu->GetXaxis()->SetRangeUser(0,300);
	// //singleJetRatesEmu->GetYaxis()->SetRangeUser(10,200000);
	// TCanvas * cEMU_jet1 = new TCanvas("cEMU_jet1","",650,600);
	// gPad->SetLogy();	
	// gStyle->SetOptStat(0);
	// singleJetRatesEmu->Draw();
	// string singleJetRatesEmuSaveName = dirName + "singleJetRatesEmu.pdf";
	// cEMU_jet1->SaveAs( singleJetRatesEmuSaveName.c_str() );
	// cEMU_jet1->Close();

	// TH1F * doubleJetRatesEmu = (TH1F*)f->Get("doubleJetRates_emu");
 //    doubleJetRatesEmu->SetLineColor(2);
 //    doubleJetRatesEmu->SetLineWidth(2);
 //    doubleJetRatesEmu->GetXaxis()->SetTitle("double L1emu Jet E_{T} Threshold (GeV)");
 //    doubleJetRatesEmu->GetYaxis()->SetTitle("Rate (Hz)");    
	// //doubleJetRatesEmu->GetXaxis()->SetRangeUser(0,300);
	// //doubleJetRatesEmu->GetYaxis()->SetRangeUser(10,200000);
	// TCanvas * cEMU_jet2 = new TCanvas("cEMU_jet2","",650,600);
	// gPad->SetLogy();	
	// gStyle->SetOptStat(0);
	// doubleJetRatesEmu->Draw();
	// string doubleJetRatesEmuSaveName = dirName + "doubleJetRatesEmu.pdf";
	// cEMU_jet2->SaveAs( doubleJetRatesEmuSaveName.c_str() );
	// cEMU_jet2->Close();

	// TH1F * tripleJetRatesEmu = (TH1F*)f->Get("tripleJetRates_emu");
 //    tripleJetRatesEmu->SetLineColor(2);
 //    tripleJetRatesEmu->SetLineWidth(2);
 //    tripleJetRatesEmu->GetXaxis()->SetTitle("triple L1emu Jet E_{T} Threshold (GeV)");
 //    tripleJetRatesEmu->GetYaxis()->SetTitle("Rate (Hz)");    
	// //tripleJetRatesEmu->GetXaxis()->SetRangeUser(0,300);
	// //tripleJetRatesEmu->GetYaxis()->SetRangeUser(10,200000);
	// TCanvas * cEMU_jet3 = new TCanvas("cEMU_jet3","",650,600);
	// gPad->SetLogy();	
	// gStyle->SetOptStat(0);
	// tripleJetRatesEmu->Draw();
	// string tripleJetRatesEmuSaveName = dirName + "tripleJetRatesEmu.pdf";
	// cEMU_jet3->SaveAs( tripleJetRatesEmuSaveName.c_str() );
	// cEMU_jet3->Close();

	// TH1F * quadJetRatesEmu = (TH1F*)f->Get("quadJetRates_emu");
 //    quadJetRatesEmu->SetLineColor(2);
 //    quadJetRatesEmu->SetLineWidth(2);
 //    quadJetRatesEmu->GetXaxis()->SetTitle("quad L1emu Jet E_{T} Threshold (GeV)");
 //    quadJetRatesEmu->GetYaxis()->SetTitle("Rate (Hz)");    
	// //quadJetRatesEmu->GetXaxis()->SetRangeUser(0,300);
	// //quadJetRatesEmu->GetYaxis()->SetRangeUser(10,200000);
	// TCanvas * cEMU_jet4 = new TCanvas("cEMU_jet4","",650,600);
	// gPad->SetLogy();	
	// gStyle->SetOptStat(0);
	// quadJetRatesEmu->Draw();
	// string quadJetRatesEmuSaveName = dirName + "quadJetRatesEmu.pdf";
	// cEMU_jet4->SaveAs( quadJetRatesEmuSaveName.c_str() );
	// cEMU_jet4->Close();

	// TH1F * singleEgRatesEmu = (TH1F*)f->Get("singleEgRates_emu");
 //    singleEgRatesEmu->SetLineColor(2);
 //    singleEgRatesEmu->SetLineWidth(2);
 //    singleEgRatesEmu->GetXaxis()->SetTitle("single L1emu EG E_{T} Threshold (GeV)");
 //    singleEgRatesEmu->GetYaxis()->SetTitle("Rate (Hz)");    
	// //singleEgRatesEmu->GetXaxis()->SetRangeUser(0,300);
	// //singleEgRatesEmu->GetYaxis()->SetRangeUser(10,200000);
	// TCanvas * cEMU_eg1 = new TCanvas("cEMU_eg1","",650,600);
	// gPad->SetLogy();	
	// gStyle->SetOptStat(0);
	// singleEgRatesEmu->Draw();
	// string singleEgRatesEmuSaveName = dirName + "singleEgRatesEmu.pdf";
	// cEMU_eg1->SaveAs( singleEgRatesEmuSaveName.c_str() );
	// cEMU_eg1->Close();

	// TH1F * doubleEgRatesEmu = (TH1F*)f->Get("doubleEgRates_emu");
 //    doubleEgRatesEmu->SetLineColor(2);
 //    doubleEgRatesEmu->SetLineWidth(2);
 //    doubleEgRatesEmu->GetXaxis()->SetTitle("double L1emu EG E_{T} Threshold (GeV)");
 //    doubleEgRatesEmu->GetYaxis()->SetTitle("Rate (Hz)");    
	// //doubleEgRatesEmu->GetXaxis()->SetRangeUser(0,300);
	// //doubleEgRatesEmu->GetYaxis()->SetRangeUser(10,200000);
	// TCanvas * cEMU_eg2 = new TCanvas("cEMU_eg2","",650,600);
	// gPad->SetLogy();	
	// gStyle->SetOptStat(0);
	// doubleEgRatesEmu->Draw();
	// string doubleEgRatesEmuSaveName = dirName + "doubleEgRatesEmu.pdf";
	// cEMU_eg2->SaveAs( doubleEgRatesEmuSaveName.c_str() );
	// cEMU_eg2->Close();

	// TH1F * tauRatesEmu = (TH1F*)f->Get("tauRates_emu");
 //    tauRatesEmu->SetLineColor(2);
 //    tauRatesEmu->SetLineWidth(2);
 //    tauRatesEmu->GetXaxis()->SetTitle("L1emu tau E_{T} Threshold (GeV)");
 //    tauRatesEmu->GetYaxis()->SetTitle("Rate (Hz)");    
	// //tauRatesEmu->GetXaxis()->SetRangeUser(0,300);
	// //tauRatesEmu->GetYaxis()->SetRangeUser(10,200000);
	// TCanvas * cEMU_tau = new TCanvas("cEMU_tau","",650,600);
	// gPad->SetLogy();	
	// gStyle->SetOptStat(0);
	// tauRatesEmu->Draw();
	// string tauRatesEmuSaveName = dirName + "tauRatesEmu.pdf";
	// cEMU_tau->SaveAs( tauRatesEmuSaveName.c_str() );
	// cEMU_tau->Close();

	// TH1F * htSumRatesEmu = (TH1F*)f->Get("htSumRates_emu");
 //    htSumRatesEmu->SetLineColor(2);
 //    htSumRatesEmu->SetLineWidth(2);
 //    htSumRatesEmu->GetXaxis()->SetTitle("L1emu HTT Threshold (GeV)");
 //    htSumRatesEmu->GetYaxis()->SetTitle("Rate (Hz)");    
	// //htSumRatesEmu->GetXaxis()->SetRangeUser(0,300);
	// //htSumRatesEmu->GetYaxis()->SetRangeUser(10,200000);
	// TCanvas * cEMU_htSum = new TCanvas("cEMU_htSum","",650,600);
	// gPad->SetLogy();	
	// gStyle->SetOptStat(0);
	// htSumRatesEmu->Draw();
	// string htSumRatesEmuSaveName = dirName + "htSumRatesEmu.pdf";
	// cEMU_htSum->SaveAs( htSumRatesEmuSaveName.c_str() );
	// cEMU_htSum->Close();

	// TH1F * mhtSumRatesEmu = (TH1F*)f->Get("mhtSumRates_emu");
 //    mhtSumRatesEmu->SetLineColor(2);
 //    mhtSumRatesEmu->SetLineWidth(2);
 //    mhtSumRatesEmu->GetXaxis()->SetTitle("L1emu MHT Threshold (GeV)");
 //    mhtSumRatesEmu->GetYaxis()->SetTitle("Rate (Hz)");    
	// //mhtSumRatesEmu->GetXaxis()->SetRangeUser(0,300);
	// //mhtSumRatesEmu->GetYaxis()->SetRangeUser(10,200000);
	// TCanvas * cEMU_mhtSum = new TCanvas("cEMU_mhtSum","",650,600);
	// gPad->SetLogy();	
	// gStyle->SetOptStat(0);
	// mhtSumRatesEmu->Draw();
	// string mhtSumRatesEmuSaveName = dirName + "mhtSumRatesEmu.pdf";
	// cEMU_mhtSum->SaveAs( mhtSumRatesEmuSaveName.c_str() );
	// cEMU_mhtSum->Close();

	// TH1F * etSumRatesEmu = (TH1F*)f->Get("etSumRates_emu");
 //    etSumRatesEmu->SetLineColor(2);
 //    etSumRatesEmu->SetLineWidth(2);
 //    etSumRatesEmu->GetXaxis()->SetTitle("L1emu ETT Threshold (GeV)");
 //    etSumRatesEmu->GetYaxis()->SetTitle("Rate (Hz)");    
	// //etSumRatesEmu->GetXaxis()->SetRangeUser(0,300);
	// //etSumRatesEmu->GetYaxis()->SetRangeUser(10,200000);
	// TCanvas * cEMU_etSum = new TCanvas("cEMU_etSum","",650,600);
	// gPad->SetLogy();	
	// gStyle->SetOptStat(0);
	// etSumRatesEmu->Draw();
	// string etSumRatesEmuSaveName = dirName + "etSumRatesEmu.pdf";
	// cEMU_etSum->SaveAs( etSumRatesEmuSaveName.c_str() );
	// cEMU_etSum->Close();

	// TH1F * metSumRatesEmu = (TH1F*)f->Get("metSumRates_emu");
 //    metSumRatesEmu->SetLineColor(2);
 //    metSumRatesEmu->SetLineWidth(2);
 //    metSumRatesEmu->GetXaxis()->SetTitle("L1emu MET Threshold (GeV)");
 //    metSumRatesEmu->GetYaxis()->SetTitle("Rate (Hz)");    
	// //metSumRatesEmu->GetXaxis()->SetRangeUser(0,300);
	// //metSumRatesEmu->GetYaxis()->SetRangeUser(10,200000);
	// TCanvas * cEMU_metSum = new TCanvas("cEMU_metSum","",650,600);
	// gPad->SetLogy();	
	// gStyle->SetOptStat(0);
	// metSumRatesEmu->Draw();
	// string metSumRatesEmuSaveName = dirName + "metSumRatesEmu.pdf";
	// cEMU_metSum->SaveAs( metSumRatesEmuSaveName.c_str() );				
	// cEMU_metSum->Close();




 //    TH1F * singleJetRatesHW = (TH1F*)f->Get("singleJetRates_hw");
 //    singleJetRatesHW->SetLineColor(2);
 //    singleJetRatesHW->SetLineWidth(2);
 //    singleJetRatesHW->GetXaxis()->SetTitle("single L1HW Jet E_{T} Threshold (GeV)");
 //    singleJetRatesHW->GetYaxis()->SetTitle("Rate (Hz)");    
	// //singleJetRatesHW->GetXaxis()->SetRangeUser(0,300);
	// //singleJetRatesHW->GetYaxis()->SetRangeUser(10,200000);
	// TCanvas * cHW_jet1 = new TCanvas("cHW_jet1","",650,600);
	// gPad->SetLogy();	
	// gStyle->SetOptStat(0);
	// singleJetRatesHW->Draw();
	// string singleJetRatesHWSaveName = dirName + "singleJetRatesHW.pdf";
	// cHW_jet1->SaveAs( singleJetRatesHWSaveName.c_str() );
	// cHW_jet1->Close();

	// TH1F * doubleJetRatesHW = (TH1F*)f->Get("doubleJetRates_hw");
 //    doubleJetRatesHW->SetLineColor(2);
 //    doubleJetRatesHW->SetLineWidth(2);
 //    doubleJetRatesHW->GetXaxis()->SetTitle("double L1HW Jet E_{T} Threshold (GeV)");
 //    doubleJetRatesHW->GetYaxis()->SetTitle("Rate (Hz)");    
	// //doubleJetRatesHW->GetXaxis()->SetRangeUser(0,300);
	// //doubleJetRatesHW->GetYaxis()->SetRangeUser(10,200000);
	// TCanvas * cHW_jet2 = new TCanvas("cHW_jet2","",650,600);
	// gPad->SetLogy();	
	// gStyle->SetOptStat(0);
	// doubleJetRatesHW->Draw();
	// string doubleJetRatesHWSaveName = dirName + "doubleJetRatesHW.pdf";
	// cHW_jet2->SaveAs( doubleJetRatesHWSaveName.c_str() );
	// cHW_jet2->Close();

	// TH1F * tripleJetRatesHW = (TH1F*)f->Get("tripleJetRates_hw");
 //    tripleJetRatesHW->SetLineColor(2);
 //    tripleJetRatesHW->SetLineWidth(2);
 //    tripleJetRatesHW->GetXaxis()->SetTitle("triple L1HW Jet E_{T} Threshold (GeV)");
 //    tripleJetRatesHW->GetYaxis()->SetTitle("Rate (Hz)");    
	// //tripleJetRatesHW->GetXaxis()->SetRangeUser(0,300);
	// //tripleJetRatesHW->GetYaxis()->SetRangeUser(10,200000);
	// TCanvas * cHW_jet3 = new TCanvas("cHW_jet3","",650,600);
	// gPad->SetLogy();	
	// gStyle->SetOptStat(0);
	// tripleJetRatesHW->Draw();
	// string tripleJetRatesHWSaveName = dirName + "tripleJetRatesHW.pdf";
	// cHW_jet3->SaveAs( tripleJetRatesHWSaveName.c_str() );
	// cHW_jet3->Close();

	// TH1F * quadJetRatesHW = (TH1F*)f->Get("quadJetRates_hw");
 //    quadJetRatesHW->SetLineColor(2);
 //    quadJetRatesHW->SetLineWidth(2);
 //    quadJetRatesHW->GetXaxis()->SetTitle("quad L1HW Jet E_{T} Threshold (GeV)");
 //    quadJetRatesHW->GetYaxis()->SetTitle("Rate (Hz)");    
	// //quadJetRatesHW->GetXaxis()->SetRangeUser(0,300);
	// //quadJetRatesHW->GetYaxis()->SetRangeUser(10,200000);
	// TCanvas * cHW_jet4 = new TCanvas("cHW_jet4","",650,600);
	// gPad->SetLogy();	
	// gStyle->SetOptStat(0);
	// quadJetRatesHW->Draw();
	// string quadJetRatesHWSaveName = dirName + "quadJetRatesHW.pdf";
	// cHW_jet4->SaveAs( quadJetRatesHWSaveName.c_str() );
	// cHW_jet4->Close();

	// TH1F * singleEgRatesHW = (TH1F*)f->Get("singleEgRates_hw");
 //    singleEgRatesHW->SetLineColor(2);
 //    singleEgRatesHW->SetLineWidth(2);
 //    singleEgRatesHW->GetXaxis()->SetTitle("single L1HW EG E_{T} Threshold (GeV)");
 //    singleEgRatesHW->GetYaxis()->SetTitle("Rate (Hz)");    
	// //singleEgRatesHW->GetXaxis()->SetRangeUser(0,300);
	// //singleEgRatesHW->GetYaxis()->SetRangeUser(10,200000);
	// TCanvas * cHW_eg1 = new TCanvas("cHW_eg1","",650,600);
	// gPad->SetLogy();	
	// gStyle->SetOptStat(0);
	// singleEgRatesHW->Draw();
	// string singleEgRatesHWSaveName = dirName + "singleEgRatesHW.pdf";
	// cHW_eg1->SaveAs( singleEgRatesHWSaveName.c_str() );
	// cHW_eg1->Close();

	// TH1F * doubleEgRatesHW = (TH1F*)f->Get("doubleEgRates_hw");
 //    doubleEgRatesHW->SetLineColor(2);
 //    doubleEgRatesHW->SetLineWidth(2);
 //    doubleEgRatesHW->GetXaxis()->SetTitle("double L1HW EG E_{T} Threshold (GeV)");
 //    doubleEgRatesHW->GetYaxis()->SetTitle("Rate (Hz)");    
	// //doubleEgRatesHW->GetXaxis()->SetRangeUser(0,300);
	// //doubleEgRatesHW->GetYaxis()->SetRangeUser(10,200000);
	// TCanvas * cHW_eg2 = new TCanvas("cHW_eg2","",650,600);
	// gPad->SetLogy();	
	// gStyle->SetOptStat(0);
	// doubleEgRatesHW->Draw();
	// string doubleEgRatesHWSaveName = dirName + "doubleEgRatesHW.pdf";
	// cHW_eg2->SaveAs( doubleEgRatesHWSaveName.c_str() );
	// cHW_eg2->Close();

	// TH1F * tauRatesHW = (TH1F*)f->Get("tauRates_hw");
 //    tauRatesHW->SetLineColor(2);
 //    tauRatesHW->SetLineWidth(2);
 //    tauRatesHW->GetXaxis()->SetTitle("L1HW tau E_{T} Threshold (GeV)");
 //    tauRatesHW->GetYaxis()->SetTitle("Rate (Hz)");    
	// //tauRatesHW->GetXaxis()->SetRangeUser(0,300);
	// //tauRatesHW->GetYaxis()->SetRangeUser(10,200000);
	// TCanvas * cHW_tau = new TCanvas("cHW_tau","",650,600);
	// gPad->SetLogy();	
	// gStyle->SetOptStat(0);
	// tauRatesHW->Draw();
	// string tauRatesHWSaveName = dirName + "tauRatesHW.pdf";
	// cHW_tau->SaveAs( tauRatesHWSaveName.c_str() );
	// cHW_tau->Close();

	// TH1F * htSumRatesHW = (TH1F*)f->Get("htSumRates_hw");
 //    htSumRatesHW->SetLineColor(2);
 //    htSumRatesHW->SetLineWidth(2);
 //    htSumRatesHW->GetXaxis()->SetTitle("L1HW HTT Threshold (GeV)");
 //    htSumRatesHW->GetYaxis()->SetTitle("Rate (Hz)");    
	// //htSumRatesHW->GetXaxis()->SetRangeUser(0,300);
	// //htSumRatesHW->GetYaxis()->SetRangeUser(10,200000);
	// TCanvas * cHW_htSum = new TCanvas("cHW_htSum","",650,600);
	// gPad->SetLogy();	
	// gStyle->SetOptStat(0);
	// htSumRatesHW->Draw();
	// string htSumRatesHWSaveName = dirName + "htSumRatesHW.pdf";
	// cHW_htSum->SaveAs( htSumRatesHWSaveName.c_str() );
	// cHW_htSum->Close();

	// TH1F * mhtSumRatesHW = (TH1F*)f->Get("mhtSumRates_hw");
 //    mhtSumRatesHW->SetLineColor(2);
 //    mhtSumRatesHW->SetLineWidth(2);
 //    mhtSumRatesHW->GetXaxis()->SetTitle("L1HW MHT Threshold (GeV)");
 //    mhtSumRatesHW->GetYaxis()->SetTitle("Rate (Hz)");    
	// //mhtSumRatesHW->GetXaxis()->SetRangeUser(0,300);
	// //mhtSumRatesHW->GetYaxis()->SetRangeUser(10,200000);
	// TCanvas * cHW_mhtSum = new TCanvas("cHW_mhtSum","",650,600);
	// gPad->SetLogy();	
	// gStyle->SetOptStat(0);
	// mhtSumRatesHW->Draw();
	// string mhtSumRatesHWSaveName = dirName + "mhtSumRatesHW.pdf";
	// cHW_mhtSum->SaveAs( mhtSumRatesHWSaveName.c_str() );
	// cHW_mhtSum->Close();

	// TH1F * etSumRatesHW = (TH1F*)f->Get("etSumRates_hw");
 //    etSumRatesHW->SetLineColor(2);
 //    etSumRatesHW->SetLineWidth(2);
 //    etSumRatesHW->GetXaxis()->SetTitle("L1HW ETT Threshold (GeV)");
 //    etSumRatesHW->GetYaxis()->SetTitle("Rate (Hz)");    
	// //etSumRatesHW->GetXaxis()->SetRangeUser(0,300);
	// //etSumRatesHW->GetYaxis()->SetRangeUser(10,200000);
	// TCanvas * cHW_etSum = new TCanvas("cHW_etSum","",650,600);
	// gPad->SetLogy();	
	// gStyle->SetOptStat(0);
	// etSumRatesHW->Draw();
	// string etSumRatesHWSaveName = dirName + "etSumRatesHW.pdf";
	// cHW_etSum->SaveAs( etSumRatesHWSaveName.c_str() );
	// cHW_etSum->Close();

	// TH1F * metSumRatesHW = (TH1F*)f->Get("metSumRates_hw");
 //    metSumRatesHW->SetLineColor(2);
 //    metSumRatesHW->SetLineWidth(2);
 //    metSumRatesHW->GetXaxis()->SetTitle("L1HW MET Threshold (GeV)");
 //    metSumRatesHW->GetYaxis()->SetTitle("Rate (Hz)");    
	// //metSumRatesHW->GetXaxis()->SetRangeUser(0,300);
	// //metSumRatesHW->GetYaxis()->SetRangeUser(10,200000);
	// TCanvas * cHW_metSum = new TCanvas("cHW_metSum","",650,600);
	// gPad->SetLogy();	
	// gStyle->SetOptStat(0);
	// metSumRatesHW->Draw();
	// string metSumRatesHWSaveName = dirName + "metSumRatesHW.pdf";
	// cHW_metSum->SaveAs( metSumRatesHWSaveName.c_str() );				
	// cHW_metSum->Close();

}
