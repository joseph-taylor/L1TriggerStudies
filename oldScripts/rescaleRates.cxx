#include "TFile.h"
#include "TH1F.h"
#include <string>

void rescaleRates(){
	
	TFile * f = new TFile("../output_rates/run272818_zeroBias_807intv48p0_HW_rescale/histos.root");
	
	TH1F * h1 = (TH1F*)f->Get("singleJetRates_hw");
	TH1F * h2 = (TH1F*)f->Get("doubleJetRates_hw");	
	TH1F * h3 = (TH1F*)f->Get("tripleJetRates_hw");
	TH1F * h4 = (TH1F*)f->Get("quadJetRates_hw");
	TH1F * h5 = (TH1F*)f->Get("singleEgRates_hw");
	TH1F * h6 = (TH1F*)f->Get("doubleEgRates_hw");
	TH1F * h7 = (TH1F*)f->Get("singleTauRates_hw");
	TH1F * h8 = (TH1F*)f->Get("doubleTauRates_hw");					
	TH1F * h9 = (TH1F*)f->Get("singleISOEgRates_hw");
	TH1F * h10 = (TH1F*)f->Get("doubleISOEgRates_hw");
	TH1F * h11 = (TH1F*)f->Get("singleISOTauRates_hw");
	TH1F * h12 = (TH1F*)f->Get("doubleISOTauRates_hw");	
	TH1F * h13 = (TH1F*)f->Get("htSumRates_hw");
	TH1F * h14 = (TH1F*)f->Get("mhtSumRates_hw");
	TH1F * h15 = (TH1F*)f->Get("etSumRates_hw");
	TH1F * h16 = (TH1F*)f->Get("metSumRates_hw");

    TH1F * h17 = (TH1F*)f->Get("leadingJetDist_hw");
    TH1F * h18 = (TH1F*)f->Get("secondJetDist_hw");
    TH1F * h19 = (TH1F*)f->Get("thirdJetDist_hw");
    TH1F * h20 = (TH1F*)f->Get("fourthJetDist_hw");
    TH1F * h21 = (TH1F*)f->Get("htSumDist_hw");
    TH1F * h22 = (TH1F*)f->Get("mhtSumDist_hw");
    TH1F * h23 = (TH1F*)f->Get("etSumDist_hw");
    TH1F * h24 = (TH1F*)f->Get("metSumDist_hw");
    TH1F * h25 = (TH1F*)f->Get("leadingEgDist_hw");
    TH1F * h26 = (TH1F*)f->Get("secondEgDist_hw");
    TH1F * h27 = (TH1F*)f->Get("leadingTauDist_hw");
    TH1F * h28 = (TH1F*)f->Get("secondTauDist_hw");
    TH1F * h29 = (TH1F*)f->Get("leadingISOEgDist_hw");
    TH1F * h30 = (TH1F*)f->Get("secondISOEgDist_hw");
    TH1F * h31 = (TH1F*)f->Get("leadingISOTauDist_hw");
    TH1F * h32 = (TH1F*)f->Get("secondISOTauDist_hw");




	// TH1F * h1 = (TH1F*)f->Get("singleJetRates_emu");
	// TH1F * h2 = (TH1F*)f->Get("doubleJetRates_emu");	
	// TH1F * h3 = (TH1F*)f->Get("tripleJetRates_emu");
	// TH1F * h4 = (TH1F*)f->Get("quadJetRates_emu");
	// TH1F * h5 = (TH1F*)f->Get("singleEgRates_emu");
	// TH1F * h6 = (TH1F*)f->Get("doubleEgRates_emu");
	// TH1F * h7 = (TH1F*)f->Get("singleTauRates_emu");
	// TH1F * h8 = (TH1F*)f->Get("doubleTauRates_emu");					
	// TH1F * h9 = (TH1F*)f->Get("singleISOEgRates_emu");
	// TH1F * h10 = (TH1F*)f->Get("doubleISOEgRates_emu");
	// TH1F * h11 = (TH1F*)f->Get("singleISOTauRates_emu");
	// TH1F * h12 = (TH1F*)f->Get("doubleISOTauRates_emu");	
	// TH1F * h13 = (TH1F*)f->Get("htSumRates_emu");
	// TH1F * h14 = (TH1F*)f->Get("mhtSumRates_emu");
	// TH1F * h15 = (TH1F*)f->Get("etSumRates_emu");
	// TH1F * h16 = (TH1F*)f->Get("metSumRates_emu");

    // TH1F * h17 = (TH1F*)f->Get("leadingJetDist_hw");
    // TH1F * h18 = (TH1F*)f->Get("secondJetDist_hw");
    // TH1F * h19 = (TH1F*)f->Get("thirdJetDist_hw");
    // TH1F * h20 = (TH1F*)f->Get("fourthJetDist_hw");
    // TH1F * h21 = (TH1F*)f->Get("htSumDist_hw");
    // TH1F * h22 = (TH1F*)f->Get("mhtSumDist_hw");
    // TH1F * h23 = (TH1F*)f->Get("etSumDist_hw");
    // TH1F * h24 = (TH1F*)f->Get("metSumDist_hw");
    // TH1F * h25 = (TH1F*)f->Get("leadingEgDist_hw");
    // TH1F * h26 = (TH1F*)f->Get("secondEgDist_hw");
    // TH1F * h27 = (TH1F*)f->Get("leadingTauDist_hw");
    // TH1F * h28 = (TH1F*)f->Get("secondTauDist_hw");
    // TH1F * h29 = (TH1F*)f->Get("leadingISOEgDist_hw");
    // TH1F * h30 = (TH1F*)f->Get("secondISOEgDist_hw");
    // TH1F * h31 = (TH1F*)f->Get("leadingISOTauDist_hw");
    // TH1F * h32 = (TH1F*)f->Get("secondISOTauDist_hw");




	double runLum = 0.081; //luminosity of the run of interest (*10^34)
	double expectedLum = 1.15; //expected luminostiy of 2016 runs (*10^34)

	// going from 'natural' to 1.5e34
	// double scaleFactor = expectedLum/runLum;

	// going from 1.5e34 to 'natural'
	double scaleFactor = runLum/expectedLum;

	h1->Scale(scaleFactor);
	h2->Scale(scaleFactor);
	h3->Scale(scaleFactor);
	h4->Scale(scaleFactor);
	h5->Scale(scaleFactor);
	h6->Scale(scaleFactor);
	h7->Scale(scaleFactor);
	h8->Scale(scaleFactor);
	h9->Scale(scaleFactor);
	h10->Scale(scaleFactor);
	h11->Scale(scaleFactor);
	h12->Scale(scaleFactor);
	h13->Scale(scaleFactor);
	h14->Scale(scaleFactor);
	h15->Scale(scaleFactor);
	h16->Scale(scaleFactor);
	// note that at no point have we been scaling the distributions

	string outputFilename = "../output_rates/run272818_zeroBias_807intv48p0_HW_noRescale/histos.root";
	TFile g( outputFilename.c_str() , "new");
	h1->Write();
	h2->Write();
	h3->Write();
	h4->Write();		
	h5->Write();
	h6->Write();
	h7->Write();
	h8->Write();
	h9->Write();
	h10->Write();
	h11->Write();
	h12->Write();
	h13->Write();
	h14->Write();		
	h15->Write();
	h16->Write();
	h17->Write();
	h18->Write();
	h19->Write();
	h20->Write();		
	h21->Write();
	h22->Write();
	h23->Write();
	h24->Write();
	h25->Write();
	h26->Write();
	h27->Write();
	h28->Write();
	h29->Write();
	h30->Write();		
	h31->Write();
	h32->Write();
}


