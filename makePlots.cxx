#include "TFile.h"
#include "TF1.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TStyle.h"
#include "TLegend.h"
#include "TEfficiency.h"
#include <TCanvas.h>
#include <TLatex.h>
#include <string>
#include <iostream>

//TODO: insert error message explanations/terminations to avoid seg faults...
// && sort out energy sums width fit vector... && ratio box slickness...
/*
makes pretty plots from histograms in .root files
How to use:
For simple running...just change lines
65-71: the set type of plots you want to make (rates_hwEmu, rates_emuOnly, rates_hwOnly, rates_emuOnlyCompare, rates_hwEmuDiffFiles, jets, esums)
74,75: the path to the .root file with the histograms (the pdf output will be saved here also)
*/

class rootPlotMaker{
//private class members: only accessible from within other members of this class
	vector<TFile*> inputFileObjects;
    TFile * inputFile2D;
    TFile * inputFileEff;
	vector<TH1F*> histogramObjects;
    TH2F * histogram2D;	
    vector<TEfficiency> efficiencyObjects;
    vector<TF1*> turnOnFits;
    vector<TH1F*> numeratorObjects;
    TH1F * denominatorObject;    	
	TCanvas * canvas = new TCanvas("canvas", "", 650, 600);
	TLegend legend;
	TLatex additionalText;
public:
//public class members: can be individually accessed from outside the class
	void loadHistogramsInfo(vector<string>,vector<string>,vector<int>,vector<int>,vector<int>);
	void loadHistogram2D(string,string);
	void loadEfficiencies(string,vector<string>,string,vector<string>,vector<int>,vector<int>,vector<int>,vector<double>,bool);
	void plotAndSave(int,string,string);
	// extension functions you can run (after loading and before plotting)...not complete, add as you need
	void turnGridLinesOn();
	void turnLogXon();
	void turnLogYon();
	void turnLogZon();
	void setTitle(string);
	void setAxisTitles(string,string);
	void setAxisTitleOffset(double,double);
	void setAxisTitleSize(double,double);
	void setXaxisRange(double,double);
	void setYaxisRange(double,double);
	void setXaxisLimits(double,double);
	void setYaxisLimits(double,double);
	void setCanvasSize(double,double);
	void insertLegend(vector<string>,double,double,double,double);
	void insertAdditionalText(string);
	void setAdditionalTextLocation(double,double);
	void autoSetAdditionalTextLocation(bool);
	void setAdditionalTextSize(double);
};// end of class definition

void makePlots(){

	// ***select one of the routines***
	string plotSetType = "rates_hwEmu";
	//string plotSetType = "rates_emuOnly";
	//string plotSetType = "rates_hwOnly";
	// string plotSetType = "rates_emuCompare"; //nb: currently need to change legend names by hand
	// string plotSetType = "rates_hwEmuDiffFiles"; // gah, ratio box stuff needs fixing...
	//string plotSetType = "rates_hwDiffFiles";
	// string plotSetType = "jets";
	// string plotSetType = "esums";

	// ***set unique parameters***
	string directoryName = "output_rates/run274157_zeroBias_808intv59p0_HW-EMU/"; //also the directory where we save final plots
	string secondFileDirectoryName = "output_rates/run274157_zeroBias_808intv59p0_HW/"; //only used if reading a second file (rates_emuCompare or rates_hwEmuDiffFiles)
	
	string inputFileName = "histos.root"; // should have set up analysis macros to name output this filename
	string secondInputFileName = "histos.root";
	string path = directoryName + inputFileName;
	string path2 = secondFileDirectoryName + secondInputFileName;

	//creates standard input objects (at the moment operating on eight seperate lines max)
	//(histogram selection and legend naming should be in sync with the following)
    vector<int> histogramLineWidths_allSize2; // all the same width of 2
    histogramLineWidths_allSize2.assign(8,2);

   	vector<int> histogramLineWidths_alt23; // alternates between size 2 and 3 (for dotted lines)
    histogramLineWidths_alt23.push_back(2);
    histogramLineWidths_alt23.push_back(3);
    histogramLineWidths_alt23.push_back(2);
    histogramLineWidths_alt23.push_back(3);
    histogramLineWidths_alt23.push_back(2);
    histogramLineWidths_alt23.push_back(3);
    histogramLineWidths_alt23.push_back(2);
    histogramLineWidths_alt23.push_back(3);

    vector<int> histogramLineColours_allDifferent;    // all very different colours
    histogramLineColours_allDifferent.push_back(kRed);
    histogramLineColours_allDifferent.push_back(kBlue+1);
    histogramLineColours_allDifferent.push_back(kGreen+3);
    histogramLineColours_allDifferent.push_back(kBlack);
    histogramLineColours_allDifferent.push_back(kMagenta+1);
    histogramLineColours_allDifferent.push_back(kOrange+7);
    histogramLineColours_allDifferent.push_back(kCyan+1);
    histogramLineColours_allDifferent.push_back(kGreen);

    vector<int> histogramLineColours_twosDifferent;  // different colours in sets of two
    histogramLineColours_twosDifferent.push_back(kRed);
    histogramLineColours_twosDifferent.push_back(kRed);
    histogramLineColours_twosDifferent.push_back(kBlue+1);
    histogramLineColours_twosDifferent.push_back(kBlue+1);
    histogramLineColours_twosDifferent.push_back(kGreen+3);
    histogramLineColours_twosDifferent.push_back(kGreen+3);
    histogramLineColours_twosDifferent.push_back(kBlack);
    histogramLineColours_twosDifferent.push_back(kBlack);

    vector<int> histogramLineStyles_allSolidLines;  // all solid lines
    histogramLineStyles_allSolidLines.assign(8,1);

	vector<int> histogramLineStyles_altSolidDotted; // alternate between solid and dotted 
    histogramLineStyles_altSolidDotted.push_back(1);
    histogramLineStyles_altSolidDotted.push_back(7);
    histogramLineStyles_altSolidDotted.push_back(1);
    histogramLineStyles_altSolidDotted.push_back(7);
    histogramLineStyles_altSolidDotted.push_back(1);
    histogramLineStyles_altSolidDotted.push_back(7);
    histogramLineStyles_altSolidDotted.push_back(1);
    histogramLineStyles_altSolidDotted.push_back(7);

	vector<string> inputFilePath_allSame;
	inputFilePath_allSame.assign(8, path.c_str());	

	vector<string> inputFilePath_twoFiles;
	inputFilePath_twoFiles.push_back(path.c_str());	
	inputFilePath_twoFiles.push_back(path2.c_str());	
	inputFilePath_twoFiles.push_back(path.c_str());	
	inputFilePath_twoFiles.push_back(path2.c_str());	
	inputFilePath_twoFiles.push_back(path.c_str());	
	inputFilePath_twoFiles.push_back(path2.c_str());	
	inputFilePath_twoFiles.push_back(path.c_str());	
	inputFilePath_twoFiles.push_back(path2.c_str());	

	//used to tune the fits
	vector<double> widthVector_jetCentral;
	widthVector_jetCentral.push_back(10);
	widthVector_jetCentral.push_back(10);
	widthVector_jetCentral.push_back(10);
	widthVector_jetCentral.push_back(20);			
	widthVector_jetCentral.push_back(20);	
	widthVector_jetCentral.push_back(40);
	widthVector_jetCentral.push_back(40);

	vector<double> widthVector_jetHF;
	widthVector_jetHF.push_back(10);
	widthVector_jetHF.push_back(10);
	widthVector_jetHF.push_back(10);
	widthVector_jetHF.push_back(20);			
	widthVector_jetHF.push_back(20);	
	widthVector_jetHF.push_back(25);
	widthVector_jetHF.push_back(20);

	vector<double> widthVector_jetBarrel;
	widthVector_jetBarrel.push_back(10);
	widthVector_jetBarrel.push_back(10);
	widthVector_jetBarrel.push_back(10);
	widthVector_jetBarrel.push_back(20);			
	widthVector_jetBarrel.push_back(20);	
	widthVector_jetBarrel.push_back(40);
	widthVector_jetBarrel.push_back(40);

	vector<double> widthVector_jetEndcap;
	widthVector_jetEndcap.push_back(10);
	widthVector_jetEndcap.push_back(10);
	widthVector_jetEndcap.push_back(10);
	widthVector_jetEndcap.push_back(20);			
	widthVector_jetEndcap.push_back(20);	
	widthVector_jetEndcap.push_back(40);
	widthVector_jetEndcap.push_back(40);
			
	// ***INFO***
	// create rootPlotMaker classes and use to make plots
	// to make a new 1d plot, copy and paste a _vx1 type then change the number
	// to make a new 2d plot, copy and paste a _vxy1 type then change the number
	// to make a new eff plot, copy and paste a _ve1 type then change the number
	// key parameters to change:
	// histogram names, legend names & position (if legend desired), pdf file name





	if (plotSetType=="rates_hwEmu"){

		rootPlotMaker plot_vx5;
		vector<string> histoNames_vx5;
		histoNames_vx5.push_back("etSumRates_emu");
		histoNames_vx5.push_back("etSumRates_hw");
		histoNames_vx5.push_back("htSumRates_emu");   
		histoNames_vx5.push_back("htSumRates_hw");     
		vector<string> legIconNames_vx5;
		legIconNames_vx5.push_back("Total E_{T} emu");
		legIconNames_vx5.push_back("Total E_{T} hw");
		legIconNames_vx5.push_back("Total H_{T} emu");
		legIconNames_vx5.push_back("Total H_{T} hw");
		plot_vx5.loadHistogramsInfo(inputFilePath_allSame,histoNames_vx5,histogramLineWidths_alt23,
									   histogramLineColours_twosDifferent,histogramLineStyles_altSolidDotted);
		// plot_vx5.setXaxisRange(0,600);
		plot_vx5.turnGridLinesOn();
		plot_vx5.turnLogYon();
		plot_vx5.insertLegend(legIconNames_vx5, 0.55, 0.90, 0.55, 0.90);
		plot_vx5.plotAndSave(11, directoryName.c_str(), "rates_et_ht_emuHw.pdf");


		rootPlotMaker plot_vx6;
		vector<string> histoNames_vx6;
		histoNames_vx6.push_back("metSumRates_emu");
		histoNames_vx6.push_back("metSumRates_hw");
		histoNames_vx6.push_back("mhtSumRates_emu");   
		histoNames_vx6.push_back("mhtSumRates_hw");     
		vector<string> legIconNames_vx6;
		legIconNames_vx6.push_back("Missing E_{T} emu");
		legIconNames_vx6.push_back("Missing E_{T} hw");
		legIconNames_vx6.push_back("Missing H_{T} emu");
		legIconNames_vx6.push_back("Missing H_{T} hw");
		plot_vx6.loadHistogramsInfo(inputFilePath_allSame,histoNames_vx6,histogramLineWidths_alt23,
									   histogramLineColours_twosDifferent,histogramLineStyles_altSolidDotted);
		// plot_vx6.setXaxisRange(0,300);
		plot_vx6.turnGridLinesOn();
		plot_vx6.turnLogYon();
		plot_vx6.insertLegend(legIconNames_vx6, 0.55, 0.90, 0.55, 0.90);
		plot_vx6.plotAndSave(11, directoryName.c_str(), "rates_met_mht_emuHw.pdf");


		rootPlotMaker plot_vx7;
		vector<string> histoNames_vx7;
		histoNames_vx7.push_back("singleJetRates_emu");
		histoNames_vx7.push_back("singleJetRates_hw");
		histoNames_vx7.push_back("doubleJetRates_emu");
		histoNames_vx7.push_back("doubleJetRates_hw");
		histoNames_vx7.push_back("tripleJetRates_emu");
		histoNames_vx7.push_back("tripleJetRates_hw");
		histoNames_vx7.push_back("quadJetRates_emu");
		histoNames_vx7.push_back("quadJetRates_hw");     
		vector<string> legIconNames_vx7;
		legIconNames_vx7.push_back("SingleJet emu");
		legIconNames_vx7.push_back("SingleJet hw");
		legIconNames_vx7.push_back("DoubleJet emu");
		legIconNames_vx7.push_back("DoubleJet hw");
		legIconNames_vx7.push_back("TripleJet emu");
		legIconNames_vx7.push_back("TripleJet hw");
		legIconNames_vx7.push_back("QuadJet emu");
		legIconNames_vx7.push_back("QuadJet hw");
		plot_vx7.loadHistogramsInfo(inputFilePath_allSame,histoNames_vx7,histogramLineWidths_alt23,
									   histogramLineColours_twosDifferent,histogramLineStyles_altSolidDotted);
		// plot_vx7.setXaxisRange(0,400);		
		plot_vx7.turnGridLinesOn();
		plot_vx7.turnLogYon();
		plot_vx7.insertLegend(legIconNames_vx7, 0.55, 0.90, 0.55, 0.90);
		plot_vx7.plotAndSave(11, directoryName.c_str(), "rates_jets1234_emuHw.pdf");


		rootPlotMaker plot_vx8;
		vector<string> histoNames_vx8;
		histoNames_vx8.push_back("singleEgRates_emu");
		histoNames_vx8.push_back("singleEgRates_hw");
		histoNames_vx8.push_back("singleISOEgRates_emu");
		histoNames_vx8.push_back("singleISOEgRates_hw");		
		histoNames_vx8.push_back("doubleEgRates_emu");
		histoNames_vx8.push_back("doubleEgRates_hw");
		histoNames_vx8.push_back("doubleISOEgRates_emu");
		histoNames_vx8.push_back("doubleISOEgRates_hw");
		vector<string> legIconNames_vx8;
		legIconNames_vx8.push_back("SingleEG emu");
		legIconNames_vx8.push_back("SingleEG hw");
		legIconNames_vx8.push_back("isoSingleEG emu");
		legIconNames_vx8.push_back("isoSingleEG hw");
		legIconNames_vx8.push_back("DoubleEG emu");
		legIconNames_vx8.push_back("DoubleEG hw");
		legIconNames_vx8.push_back("isoDoubleEG emu");
		legIconNames_vx8.push_back("isoDoubleEG hw");
		plot_vx8.loadHistogramsInfo(inputFilePath_allSame,histoNames_vx8,histogramLineWidths_alt23,
									   histogramLineColours_twosDifferent,histogramLineStyles_altSolidDotted);
		plot_vx8.setXaxisRange(0,200);
		plot_vx8.turnGridLinesOn();
		plot_vx8.turnLogYon();
		plot_vx8.insertLegend(legIconNames_vx8, 0.55, 0.90, 0.55, 0.90);
		plot_vx8.plotAndSave(11, directoryName.c_str(), "rates_eg12_emuHw.pdf");


		rootPlotMaker plot_vx9;
		vector<string> histoNames_vx9;
  		histoNames_vx9.push_back("singleTauRates_emu");
		histoNames_vx9.push_back("sinlgeTauRates_hw");
  		histoNames_vx9.push_back("singleISOTauRates_emu");
		histoNames_vx9.push_back("sinlgeISOTauRates_hw");		
		histoNames_vx9.push_back("doubleTauRates_emu");
		histoNames_vx9.push_back("doubleTauRates_hw");   
		histoNames_vx9.push_back("doubleISOTauRates_emu");
		histoNames_vx9.push_back("doubleISOTauRates_hw");  
		vector<string> legIconNames_vx9;
		legIconNames_vx9.push_back("SingleTau emu");
		legIconNames_vx9.push_back("SingleTau hw");
		legIconNames_vx9.push_back("isoSingleTau emu");
		legIconNames_vx9.push_back("isoSingleTau hw");
		legIconNames_vx9.push_back("DoubleTau emu");
		legIconNames_vx9.push_back("DoubleTau hw");
		legIconNames_vx9.push_back("isoDoubleTau emu");
		legIconNames_vx9.push_back("isoDoubleTau hw");
		plot_vx9.loadHistogramsInfo(inputFilePath_allSame,histoNames_vx9,histogramLineWidths_alt23,
									   histogramLineColours_twosDifferent,histogramLineStyles_altSolidDotted);

		plot_vx9.setXaxisRange(0,200);
		plot_vx9.turnGridLinesOn();
		plot_vx9.turnLogYon();
		plot_vx9.insertLegend(legIconNames_vx9, 0.55, 0.90, 0.55, 0.90);
		plot_vx9.plotAndSave(11, directoryName.c_str(), "rates_tau12_emuHw.pdf");

	} // closes 'if' plotSetType=="rates_hwEmu"





	if (plotSetType=="rates_emuOnly"){

		string additionalTextString = "CMS preliminary, run272022, L_{inst}=1.4x10^{32}cm^{-2}s^{-1}";

		// rootPlotMaker plot_vx1;
		// vector<string> histoNames_vx1;
		// histoNames_vx1.push_back("etSumDist_emu");
		// histoNames_vx1.push_back("htSumDist_emu");       
		// vector<string> legIconNames_vx1;
		// legIconNames_vx1.push_back("ett_emu");
		// legIconNames_vx1.push_back("ht_emu");
		// plot_vx1.loadHistogramsInfo(inputFilePath_allSame,histoNames_vx1,histogramLineWidths_allSize2,
		// 							   histogramLineColours_allDifferent,histogramLineStyles_allSolidLines);
		// plot_vx1.turnGridLinesOn();
		// plot_vx1.turnLogYon();
		// plot_vx1.insertLegend(legIconNames_vx1, 0.65, 0.85, 0.65, 0.85);
		// plot_vx1.plotAndSave(1, directoryName.c_str(), "dist_et_ht_emu.pdf");


		// rootPlotMaker plot_vx2;
		// vector<string> histoNames_vx2;
		// histoNames_vx2.push_back("metSumDist_emu");
		// histoNames_vx2.push_back("mhtSumDist_emu");     
		// vector<string> legIconNames_vx2;
		// legIconNames_vx2.push_back("met_emu");
		// legIconNames_vx2.push_back("mht_emu");
		// plot_vx2.loadHistogramsInfo(inputFilePath_allSame,histoNames_vx2,histogramLineWidths_allSize2,
		// 							   histogramLineColours_allDifferent,histogramLineStyles_allSolidLines);
		// plot_vx2.turnGridLinesOn();
		// plot_vx2.turnLogYon();
		// plot_vx2.insertLegend(legIconNames_vx2, 0.65, 0.85, 0.65, 0.85);
		// plot_vx2.plotAndSave(1, directoryName.c_str(), "dist_met_mht_emu.pdf");


		// rootPlotMaker plot_vx3;
		// vector<string> histoNames_vx3;
		// histoNames_vx3.push_back("leadingJetDist_emu");
		// histoNames_vx3.push_back("secondJetDist_emu");
		// histoNames_vx3.push_back("thirdJetDist_emu");
		// histoNames_vx3.push_back("fourthJetDist_emu");  
		// vector<string> legIconNames_vx3;
		// legIconNames_vx3.push_back("SingleJet_emu");
		// legIconNames_vx3.push_back("DoubleJet_emu");
		// legIconNames_vx3.push_back("TripleJet_emu");
		// legIconNames_vx3.push_back("QuadJet_emu");
		// plot_vx3.loadHistogramsInfo(inputFilePath_allSame,histoNames_vx3,histogramLineWidths_allSize2,
		// 							   histogramLineColours_allDifferent,histogramLineStyles_allSolidLines);
		// plot_vx3.turnGridLinesOn();
		// plot_vx3.turnLogYon();
		// plot_vx3.insertLegend(legIconNames_vx3, 0.65, 0.85, 0.65, 0.85);
		// plot_vx3.plotAndSave(1, directoryName.c_str(), "dist_jets1234_emu.pdf");


		// rootPlotMaker plot_vx4;
		// vector<string> histoNames_vx4;
		// histoNames_vx4.push_back("leadingEgDist_emu");
		// histoNames_vx4.push_back("secondEgDist_emu");
		// histoNames_vx4.push_back("leadingTauDist_emu");
		// histoNames_vx4.push_back("secondTauDist_emu");  
		// vector<string> legIconNames_vx4;
		// legIconNames_vx4.push_back("eg1_emu");
		// legIconNames_vx4.push_back("eg2_emu");
		// legIconNames_vx4.push_back("tau1_emu");
		// legIconNames_vx4.push_back("tau2_emu");
		// plot_vx4.loadHistogramsInfo(inputFilePath_allSame,histoNames_vx4,histogramLineWidths_allSize2,
		// 							   histogramLineColours_allDifferent,histogramLineStyles_allSolidLines);
		// plot_vx4.setXaxisRange(0,200);
		// plot_vx4.turnGridLinesOn();
		// plot_vx4.turnLogYon();
		// plot_vx4.insertLegend(legIconNames_vx4, 0.65, 0.85, 0.65, 0.85);
		// plot_vx4.plotAndSave(1, directoryName.c_str(), "dist_eg12_tau_emu.pdf");


		rootPlotMaker plot_vx5;
		vector<string> histoNames_vx5;
		histoNames_vx5.push_back("etSumRates_emu");
		histoNames_vx5.push_back("htSumRates_emu");       
		vector<string> legIconNames_vx5;
		legIconNames_vx5.push_back("Total E_{T}");
		legIconNames_vx5.push_back("Total H_{T}");
		plot_vx5.loadHistogramsInfo(inputFilePath_allSame,histoNames_vx5,histogramLineWidths_allSize2,
									   histogramLineColours_allDifferent,histogramLineStyles_allSolidLines);
		// plot_vx5.setXaxisRange(0,600);
		plot_vx5.turnGridLinesOn();
		plot_vx5.turnLogYon();
		plot_vx5.insertLegend(legIconNames_vx5, 0.65, 0.85, 0.65, 0.85);
		// plot_vx5.insertAdditionalText(additionalTextString.c_str());
		// plot_vx5.setAdditionalTextLocation(0,40000000);
		plot_vx5.plotAndSave(1, directoryName.c_str(), "rates_et_ht_emu.pdf");


		rootPlotMaker plot_vx6;
		vector<string> histoNames_vx6;
		histoNames_vx6.push_back("metSumRates_emu");
		histoNames_vx6.push_back("mhtSumRates_emu");       
		vector<string> legIconNames_vx6;
		legIconNames_vx6.push_back("Missing E_{T}");
		legIconNames_vx6.push_back("Missing H_{T}");
		plot_vx6.loadHistogramsInfo(inputFilePath_allSame,histoNames_vx6,histogramLineWidths_allSize2,
									   histogramLineColours_allDifferent,histogramLineStyles_allSolidLines);
		// plot_vx6.setXaxisRange(0,300);
		plot_vx6.turnGridLinesOn();
		plot_vx6.turnLogYon();
		plot_vx6.insertLegend(legIconNames_vx6, 0.65, 0.85, 0.65, 0.85);
		// plot_vx6.insertAdditionalText(additionalTextString.c_str());
		// plot_vx6.setAdditionalTextLocation(0,40000000);
		plot_vx6.plotAndSave(1, directoryName.c_str(), "rates_met_mht_emu.pdf");


		rootPlotMaker plot_vx7;
		vector<string> histoNames_vx7;
		histoNames_vx7.push_back("singleJetRates_emu");
		histoNames_vx7.push_back("doubleJetRates_emu");
		histoNames_vx7.push_back("tripleJetRates_emu");
		histoNames_vx7.push_back("quadJetRates_emu");    
		vector<string> legIconNames_vx7;
		legIconNames_vx7.push_back("Single Jet");
		legIconNames_vx7.push_back("Double Jet");
		legIconNames_vx7.push_back("Triple Jet");
		legIconNames_vx7.push_back("Quad Jet");
		plot_vx7.loadHistogramsInfo(inputFilePath_allSame,histoNames_vx7,histogramLineWidths_allSize2,
									   histogramLineColours_allDifferent,histogramLineStyles_allSolidLines);
		// plot_vx7.setXaxisRange(0,400);
		plot_vx7.turnGridLinesOn();
		plot_vx7.turnLogYon();
		plot_vx7.insertLegend(legIconNames_vx7, 0.65, 0.85, 0.65, 0.85);
		// plot_vx7.insertAdditionalText(additionalTextString.c_str());
		// plot_vx7.setAdditionalTextLocation(0,40000000);
		plot_vx7.plotAndSave(1, directoryName.c_str(), "rates_jets1234_emu.pdf");


		rootPlotMaker plot_vx8;
		vector<string> histoNames_vx8;
		histoNames_vx8.push_back("singleEgRates_emu");
		histoNames_vx8.push_back("singleISOEgRates_emu");
		histoNames_vx8.push_back("doubleEgRates_emu");
		histoNames_vx8.push_back("doubleISOEgRates_emu");
		vector<string> legIconNames_vx8;
		legIconNames_vx8.push_back("Single EG");
		legIconNames_vx8.push_back("Single Iso EG");
		legIconNames_vx8.push_back("Double EG");
		legIconNames_vx8.push_back("Double Iso EG");
		plot_vx8.loadHistogramsInfo(inputFilePath_allSame,histoNames_vx8,histogramLineWidths_allSize2,
									   histogramLineColours_allDifferent,histogramLineStyles_allSolidLines);
		// plot_vx8.setXaxisRange(0,300);
		plot_vx8.turnGridLinesOn();
		plot_vx8.turnLogYon();
		plot_vx8.insertLegend(legIconNames_vx8, 0.65, 0.85, 0.65, 0.85);
		// plot_vx8.insertAdditionalText(additionalTextString.c_str());
		// plot_vx8.setAdditionalTextLocation(0,40000000);
		plot_vx8.plotAndSave(1, directoryName.c_str(), "rates_eg12_emu.pdf");


		rootPlotMaker plot_vx9;
		vector<string> histoNames_vx9;
		histoNames_vx9.push_back("singleTauRates_emu");
		histoNames_vx9.push_back("singleISOTauRates_emu");
		histoNames_vx9.push_back("doubleTauRates_emu");
		histoNames_vx9.push_back("doubleISOTauRates_emu");
		vector<string> legIconNames_vx9;
		legIconNames_vx9.push_back("Single Tau");
		legIconNames_vx9.push_back("Single ISO Tau");
		legIconNames_vx9.push_back("Double Tau");
		legIconNames_vx9.push_back("Double ISO Tau");
		plot_vx9.loadHistogramsInfo(inputFilePath_allSame,histoNames_vx9,histogramLineWidths_allSize2,
									   histogramLineColours_allDifferent,histogramLineStyles_allSolidLines);
		// plot_vx9.setXaxisRange(0,300);
		plot_vx9.turnGridLinesOn();
		plot_vx9.turnLogYon();
		plot_vx9.insertLegend(legIconNames_vx9, 0.65, 0.85, 0.65, 0.85);
		// plot_vx9.insertAdditionalText(additionalTextString.c_str());
		// plot_vx9.setAdditionalTextLocation(0,40000000);
		plot_vx9.plotAndSave(1, directoryName.c_str(), "rates_tau12_emu.pdf");

	} // closes 'if' plotSetType=="rates_emuOnly"





	if (plotSetType=="rates_hwOnly"){

		string additionalTextString = "CMS preliminary, run272022, L_{inst}=1.4x10^{32}cm^{-2}s^{-1}";

		// rootPlotMaker plot_vx1;
		// vector<string> histoNames_vx1;
		// histoNames_vx1.push_back("etSumDist_hw");
		// histoNames_vx1.push_back("htSumDist_hw");       
		// vector<string> legIconNames_vx1;
		// legIconNames_vx1.push_back("ett_hw");
		// legIconNames_vx1.push_back("ht_hw");
		// plot_vx1.loadHistogramsInfo(inputFilePath_allSame,histoNames_vx1,histogramLineWidths_allSize2,
		// 							   histogramLineColours_allDifferent,histogramLineStyles_allSolidLines);
		// plot_vx1.turnGridLinesOn();
		// plot_vx1.turnLogYon();
		// plot_vx1.insertLegend(legIconNames_vx1, 0.65, 0.85, 0.65, 0.85);
		// plot_vx1.plotAndSave(1, directoryName.c_str(), "dist_et_ht_hw.pdf");


		// rootPlotMaker plot_vx2;
		// vector<string> histoNames_vx2;
		// histoNames_vx2.push_back("metSumDist_hw");
		// histoNames_vx2.push_back("mhtSumDist_hw");     
		// vector<string> legIconNames_vx2;
		// legIconNames_vx2.push_back("met_hw");
		// legIconNames_vx2.push_back("mht_hw");
		// plot_vx2.loadHistogramsInfo(inputFilePath_allSame,histoNames_vx2,histogramLineWidths_allSize2,
		// 							   histogramLineColours_allDifferent,histogramLineStyles_allSolidLines);
		// plot_vx2.turnGridLinesOn();
		// plot_vx2.turnLogYon();
		// plot_vx2.insertLegend(legIconNames_vx2, 0.65, 0.85, 0.65, 0.85);
		// plot_vx2.plotAndSave(1, directoryName.c_str(), "dist_met_mht_hw.pdf");


		// rootPlotMaker plot_vx3;
		// vector<string> histoNames_vx3;
		// histoNames_vx3.push_back("leadingJetDist_hw");
		// histoNames_vx3.push_back("secondJetDist_hw");
		// histoNames_vx3.push_back("thirdJetDist_hw");
		// histoNames_vx3.push_back("fourthJetDist_hw");  
		// vector<string> legIconNames_vx3;
		// legIconNames_vx3.push_back("SingleJet_hw");
		// legIconNames_vx3.push_back("DoubleJet_hw");
		// legIconNames_vx3.push_back("TripleJet_hw");
		// legIconNames_vx3.push_back("QuadJet_hw");
		// plot_vx3.loadHistogramsInfo(inputFilePath_allSame,histoNames_vx3,histogramLineWidths_allSize2,
		// 							   histogramLineColours_allDifferent,histogramLineStyles_allSolidLines);
		// plot_vx3.turnGridLinesOn();
		// plot_vx3.turnLogYon();
		// plot_vx3.insertLegend(legIconNames_vx3, 0.65, 0.85, 0.65, 0.85);
		// plot_vx3.plotAndSave(1, directoryName.c_str(), "dist_jets1234_hw.pdf");


		// rootPlotMaker plot_vx4;
		// vector<string> histoNames_vx4;
		// histoNames_vx4.push_back("leadingEgDist_hw");
		// histoNames_vx4.push_back("secondEgDist_hw");
		// histoNames_vx4.push_back("leadingTauDist_hw");
		// histoNames_vx4.push_back("secondTauDist_hw"); 
		// vector<string> legIconNames_vx4;
		// legIconNames_vx4.push_back("eg1_hw");
		// legIconNames_vx4.push_back("eg2_hw");
		// legIconNames_vx4.push_back("tau1_hw");
		// legIconNames_vx4.push_back("tau2_hw");
		// plot_vx4.loadHistogramsInfo(inputFilePath_allSame,histoNames_vx4,histogramLineWidths_allSize2,
		// 							   histogramLineColours_allDifferent,histogramLineStyles_allSolidLines);
		// plot_vx4.setXaxisRange(0,200);
		// plot_vx4.turnGridLinesOn();
		// plot_vx4.turnLogYon();
		// plot_vx4.insertLegend(legIconNames_vx4, 0.65, 0.85, 0.65, 0.85);
		// plot_vx4.plotAndSave(1, directoryName.c_str(), "dist_eg12_tau_hw.pdf");


		rootPlotMaker plot_vx5;
		vector<string> histoNames_vx5;
		histoNames_vx5.push_back("etSumRates_hw");
		histoNames_vx5.push_back("htSumRates_hw");       
		vector<string> legIconNames_vx5;
		legIconNames_vx5.push_back("Total E_{T}");
		legIconNames_vx5.push_back("Total H_{T}");
		plot_vx5.loadHistogramsInfo(inputFilePath_allSame,histoNames_vx5,histogramLineWidths_allSize2,
									   histogramLineColours_allDifferent,histogramLineStyles_allSolidLines);
		// plot_vx5.setXaxisRange(0,600);
		plot_vx5.turnGridLinesOn();
		plot_vx5.turnLogYon();
		plot_vx5.insertLegend(legIconNames_vx5, 0.65, 0.85, 0.65, 0.85);
		// plot_vx5.insertAdditionalText(additionalTextString.c_str());
		// plot_vx5.setAdditionalTextLocation(0,40000000);
		plot_vx5.plotAndSave(1, directoryName.c_str(), "rates_et_ht_hw.pdf");


		rootPlotMaker plot_vx6;
		vector<string> histoNames_vx6;
		histoNames_vx6.push_back("metSumRates_hw");
		histoNames_vx6.push_back("mhtSumRates_hw");       
		vector<string> legIconNames_vx6;
		legIconNames_vx6.push_back("Missing E_{T}");
		legIconNames_vx6.push_back("Missing H_{T}");
		plot_vx6.loadHistogramsInfo(inputFilePath_allSame,histoNames_vx6,histogramLineWidths_allSize2,
									   histogramLineColours_allDifferent,histogramLineStyles_allSolidLines);
		// plot_vx6.setXaxisRange(0,300);
		plot_vx6.turnGridLinesOn();
		plot_vx6.turnLogYon();
		plot_vx6.insertLegend(legIconNames_vx6, 0.65, 0.85, 0.65, 0.85);
		// plot_vx6.insertAdditionalText(additionalTextString.c_str());
		// plot_vx6.setAdditionalTextLocation(0,40000000);
		plot_vx6.plotAndSave(1, directoryName.c_str(), "rates_met_mht_hw.pdf");


		rootPlotMaker plot_vx7;
		vector<string> histoNames_vx7;
		histoNames_vx7.push_back("singleJetRates_hw");
		histoNames_vx7.push_back("doubleJetRates_hw");
		histoNames_vx7.push_back("tripleJetRates_hw");
		histoNames_vx7.push_back("quadJetRates_hw");    
		vector<string> legIconNames_vx7;
		legIconNames_vx7.push_back("Single Jet");
		legIconNames_vx7.push_back("Double Jet");
		legIconNames_vx7.push_back("Triple Jet");
		legIconNames_vx7.push_back("Quad Jet");
		plot_vx7.loadHistogramsInfo(inputFilePath_allSame,histoNames_vx7,histogramLineWidths_allSize2,
									   histogramLineColours_allDifferent,histogramLineStyles_allSolidLines);
		// plot_vx7.setXaxisRange(0,400);
		plot_vx7.turnGridLinesOn();
		plot_vx7.turnLogYon();
		plot_vx7.insertLegend(legIconNames_vx7, 0.65, 0.85, 0.65, 0.85);
		// plot_vx7.insertAdditionalText(additionalTextString.c_str());
		// plot_vx7.setAdditionalTextLocation(0,40000000);
		plot_vx7.plotAndSave(1, directoryName.c_str(), "rates_jets1234_hw.pdf");


		rootPlotMaker plot_vx8;
		vector<string> histoNames_vx8;
		histoNames_vx8.push_back("singleEgRates_hw");
		histoNames_vx8.push_back("singleISOEgRates_hw");
		histoNames_vx8.push_back("doubleEgRates_hw");
		histoNames_vx8.push_back("doubleISOEgRates_hw");
		vector<string> legIconNames_vx8;
		legIconNames_vx8.push_back("Single EG");
		legIconNames_vx8.push_back("Single Iso EG");
		legIconNames_vx8.push_back("Double EG");
		legIconNames_vx8.push_back("Double Iso EG");
		plot_vx8.loadHistogramsInfo(inputFilePath_allSame,histoNames_vx8,histogramLineWidths_allSize2,
									   histogramLineColours_allDifferent,histogramLineStyles_allSolidLines);
		// plot_vx8.setXaxisRange(0,300);
		plot_vx8.setYaxisLimits(200,40000000);
		plot_vx8.turnGridLinesOn();
		plot_vx8.turnLogYon();
		plot_vx8.insertLegend(legIconNames_vx8, 0.65, 0.85, 0.65, 0.85);
		// plot_vx8.insertAdditionalText(additionalTextString.c_str());
		// plot_vx8.setAdditionalTextLocation(0,40000000);
		plot_vx8.plotAndSave(1, directoryName.c_str(), "rates_eg12_hw.pdf");


		rootPlotMaker plot_vx9;
		vector<string> histoNames_vx9;
		histoNames_vx9.push_back("singleTauRates_hw");
		histoNames_vx9.push_back("singleISOTauRates_hw");
		histoNames_vx9.push_back("doubleTauRates_hw");
		histoNames_vx9.push_back("doubleISOTauRates_hw");
		vector<string> legIconNames_vx9;
		legIconNames_vx9.push_back("Single Tau");
		legIconNames_vx9.push_back("Single ISO Tau");
		legIconNames_vx9.push_back("Double Tau");
		legIconNames_vx9.push_back("Double ISO Tau");
		plot_vx9.loadHistogramsInfo(inputFilePath_allSame,histoNames_vx9,histogramLineWidths_allSize2,
									   histogramLineColours_allDifferent,histogramLineStyles_allSolidLines);
		// plot_vx9.setXaxisRange(0,300);
		plot_vx9.turnGridLinesOn();
		plot_vx9.turnLogYon();
		plot_vx9.insertLegend(legIconNames_vx9, 0.65, 0.85, 0.65, 0.85);
		// plot_vx9.insertAdditionalText(additionalTextString.c_str());
		// plot_vx9.setAdditionalTextLocation(0,40000000);
		plot_vx9.plotAndSave(1, directoryName.c_str(), "rates_tau12_hw.pdf");

	} // closes 'if' plotSetType=="rates_hwOnly"



	//need to do something clever here to avoid redundancy when doing multiple comparisons...

	if (plotSetType=="rates_emuCompare"){

		rootPlotMaker plot_vx5;
		vector<string> histoNames_vx5;
		histoNames_vx5.push_back("etSumRates_emu");
		histoNames_vx5.push_back("etSumRates_emu");
		histoNames_vx5.push_back("htSumRates_emu");    
		histoNames_vx5.push_back("htSumRates_emu");    
		vector<string> legIconNames_vx5;
		legIconNames_vx5.push_back("Total E_{T} v48p4 fullEmu"); // currently have to change this by hand
		legIconNames_vx5.push_back("Total E_{T} v48p0 standardEmu");
		legIconNames_vx5.push_back("Total H_{T} v48p4 fullEmu");
		legIconNames_vx5.push_back("Total H_{T} v48p0 standardEmu");
		plot_vx5.loadHistogramsInfo(inputFilePath_twoFiles,histoNames_vx5,histogramLineWidths_alt23,
									   histogramLineColours_twosDifferent,histogramLineStyles_altSolidDotted);
		// plot_vx5.setXaxisRange(0,600);
		plot_vx5.turnGridLinesOn();
		plot_vx5.turnLogYon();
		plot_vx5.insertLegend(legIconNames_vx5, 0.55, 0.88, 0.72, 0.90);
		plot_vx5.plotAndSave(11, directoryName.c_str(), "rates_et_ht_emu_COMPARISON.pdf");


		rootPlotMaker plot_vx6;
		vector<string> histoNames_vx6;
		histoNames_vx6.push_back("metSumRates_emu");
		histoNames_vx6.push_back("metSumRates_emu");
		histoNames_vx6.push_back("mhtSumRates_emu");       
		histoNames_vx6.push_back("mhtSumRates_emu");     
		vector<string> legIconNames_vx6;
		legIconNames_vx6.push_back("Missing E_{T} v48p4 fullEmu");
		legIconNames_vx6.push_back("Missing E_{T} v48p0 standardEmu");
		legIconNames_vx6.push_back("Missing H_{T} v48p4 fullEmu");
		legIconNames_vx6.push_back("Missing H_{T} v48p0 standardEmu");
		plot_vx6.loadHistogramsInfo(inputFilePath_twoFiles,histoNames_vx6,histogramLineWidths_alt23,
									   histogramLineColours_twosDifferent,histogramLineStyles_altSolidDotted);
		plot_vx6.setXaxisRange(0,200);
		plot_vx6.turnGridLinesOn();
		plot_vx6.turnLogYon();
		plot_vx6.insertLegend(legIconNames_vx6, 0.55, 0.88, 0.72, 0.90);
		plot_vx6.plotAndSave(11, directoryName.c_str(), "rates_met_mht_emu_COMPARISON.pdf");


		rootPlotMaker plot_vx7;
		vector<string> histoNames_vx7;
		histoNames_vx7.push_back("singleJetRates_emu");
		histoNames_vx7.push_back("singleJetRates_emu");
		histoNames_vx7.push_back("doubleJetRates_emu");
		histoNames_vx7.push_back("doubleJetRates_emu");
		histoNames_vx7.push_back("tripleJetRates_emu");
		histoNames_vx7.push_back("tripleJetRates_emu");
		histoNames_vx7.push_back("quadJetRates_emu");    
		histoNames_vx7.push_back("quadJetRates_emu"); 
		vector<string> legIconNames_vx7;
		legIconNames_vx7.push_back("SingleJet v48p4 fullEmu");
		legIconNames_vx7.push_back("SingleJet v48p0 standardEmu");
		legIconNames_vx7.push_back("DoubleJet v48p4 fullEmu");
		legIconNames_vx7.push_back("DoubleJet v48p0 standardEmu");
		legIconNames_vx7.push_back("TripleJet v48p4 fullEmu");
		legIconNames_vx7.push_back("TripleJet v48p0 standardEmu");
		legIconNames_vx7.push_back("QuadJet v48p4 fullEmu");
		legIconNames_vx7.push_back("QuadJet v48p0 standardEmu");
		plot_vx7.loadHistogramsInfo(inputFilePath_twoFiles,histoNames_vx7,histogramLineWidths_alt23,
									   histogramLineColours_twosDifferent,histogramLineStyles_altSolidDotted);
		plot_vx7.setXaxisRange(0,300);
		plot_vx7.turnGridLinesOn();
		plot_vx7.turnLogYon();
		plot_vx7.insertLegend(legIconNames_vx7, 0.55, 0.88, 0.55, 0.90);
		plot_vx7.plotAndSave(11, directoryName.c_str(), "rates_jets1234_emu_COMPARISON.pdf");


		rootPlotMaker plot_vx8;
		vector<string> histoNames_vx8;
		histoNames_vx8.push_back("singleEgRates_emu");
		histoNames_vx8.push_back("singleEgRates_emu");
		histoNames_vx8.push_back("singleISOEgRates_emu");
		histoNames_vx8.push_back("singleISOEgRates_emu");
		histoNames_vx8.push_back("doubleEgRates_emu");
		histoNames_vx8.push_back("doubleEgRates_emu");
		histoNames_vx8.push_back("doubleISOEgRates_emu");
		histoNames_vx8.push_back("doubleISOEgRates_emu");
		vector<string> legIconNames_vx8;
		legIconNames_vx8.push_back("SingleEG_v48p4 fullEmu");
		legIconNames_vx8.push_back("SingleEG_v48p0 standardEmu");
		legIconNames_vx8.push_back("isoSingleEG_v48p4 fullEmu");
		legIconNames_vx8.push_back("isoSingleEG_rv48p0 standardEmu");		
		legIconNames_vx8.push_back("DoubleEG_v48p4 fullEmu");
		legIconNames_vx8.push_back("DoubleEG_v48p0 standardEmu");
		legIconNames_vx8.push_back("isoDoubleEG_v48p4 fullEmu");
		legIconNames_vx8.push_back("isoDoubleEG_v48p0 standardEmu");
		plot_vx8.loadHistogramsInfo(inputFilePath_twoFiles,histoNames_vx8,histogramLineWidths_alt23,
									   histogramLineColours_twosDifferent,histogramLineStyles_altSolidDotted);
		plot_vx8.setXaxisRange(0,200);
		plot_vx8.turnGridLinesOn();
		plot_vx8.turnLogYon();
		plot_vx8.insertLegend(legIconNames_vx8, 0.55, 0.88, 0.55, 0.90);
		plot_vx8.plotAndSave(11, directoryName.c_str(), "rates_eg12_emu_COMPARISON.pdf");


		rootPlotMaker plot_vx9;
		vector<string> histoNames_vx9;
		histoNames_vx9.push_back("singleTauRates_emu");  
		histoNames_vx9.push_back("singleTauRates_emu");
		histoNames_vx9.push_back("singleISOTauRates_emu");  
		histoNames_vx9.push_back("singleISOTauRates_emu"); 
		histoNames_vx9.push_back("doubleTauRates_emu");  
		histoNames_vx9.push_back("doubleTauRates_emu"); 
		histoNames_vx9.push_back("doubleISOTauRates_emu");  
		histoNames_vx9.push_back("doubleISOTauRates_emu");  		  
		vector<string> legIconNames_vx9;
		legIconNames_vx9.push_back("SingleTau_v48p4 fullEmu");
		legIconNames_vx9.push_back("SingleTau_v48p0 standardEmu");
		legIconNames_vx9.push_back("isoSingleTau_v48p4 fullEmu");
		legIconNames_vx9.push_back("isoSingleTau_rv48p0 standardEmu");		
		legIconNames_vx9.push_back("DoubleTau_v48p4 fullEmu");
		legIconNames_vx9.push_back("DoubleTau_v48p0 standardEmu");
		legIconNames_vx9.push_back("isoDoubleTau_v48p4 fullEmu");
		legIconNames_vx9.push_back("isoDoubleTau_v48p0 standardEmu");
		plot_vx9.loadHistogramsInfo(inputFilePath_twoFiles,histoNames_vx9,histogramLineWidths_alt23,
									   histogramLineColours_twosDifferent,histogramLineStyles_altSolidDotted);
		plot_vx9.setXaxisRange(0,200);
		plot_vx9.turnGridLinesOn();
		plot_vx9.turnLogYon();
		plot_vx9.insertLegend(legIconNames_vx9, 0.55, 0.88, 0.55, 0.90);
		plot_vx9.plotAndSave(11, directoryName.c_str(), "rates_tau12_emu_COMPARISON.pdf");

	} // closes 'if' plotSetType=="rates_emuCompare"





	if (plotSetType=="rates_hwEmuDiffFiles"){

		string additionalTextString = "CMS preliminary, run272798";

		rootPlotMaker plot_vx5;
		vector<string> histoNames_vx5;
		histoNames_vx5.push_back("etSumRates_emu");
		histoNames_vx5.push_back("etSumRates_hw");
		histoNames_vx5.push_back("htSumRates_emu");    
		histoNames_vx5.push_back("htSumRates_hw");    
		vector<string> legIconNames_vx5;
		legIconNames_vx5.push_back("Total E_{T} emu");
		legIconNames_vx5.push_back("Total E_{T} hw");
		legIconNames_vx5.push_back("Total H_{T} emu");
		legIconNames_vx5.push_back("Total H_{T} hw");
		plot_vx5.loadHistogramsInfo(inputFilePath_twoFiles,histoNames_vx5,histogramLineWidths_alt23,
									   histogramLineColours_twosDifferent,histogramLineStyles_altSolidDotted);
		// plot_vx5.setXaxisRange(0,500);
		plot_vx5.turnGridLinesOn();
		plot_vx5.turnLogYon();
		plot_vx5.insertLegend(legIconNames_vx5, 0.55, 0.88, 0.72, 0.90);
		plot_vx5.insertAdditionalText(additionalTextString.c_str());
		plot_vx5.setAdditionalTextLocation(0.1,8.5);
		plot_vx5.plotAndSave(11, directoryName.c_str(), "rates_et_ht_emuHwDiffFile.pdf");

		rootPlotMaker plot_vx6;
		vector<string> histoNames_vx6;
		histoNames_vx6.push_back("metSumRates_emu");
		histoNames_vx6.push_back("metSumRates_hw");
		histoNames_vx6.push_back("mhtSumRates_emu");       
		histoNames_vx6.push_back("mhtSumRates_hw");     
		vector<string> legIconNames_vx6;
		legIconNames_vx6.push_back("Missing E_{T} emu");
		legIconNames_vx6.push_back("Missing E_{T} hw");
		legIconNames_vx6.push_back("Missing H_{T} emu");
		legIconNames_vx6.push_back("Missing H_{T} hw");
		plot_vx6.loadHistogramsInfo(inputFilePath_twoFiles,histoNames_vx6,histogramLineWidths_alt23,
									   histogramLineColours_twosDifferent,histogramLineStyles_altSolidDotted);
		plot_vx6.setXaxisRange(0,200);
		plot_vx6.turnGridLinesOn();
		plot_vx6.turnLogYon();
		plot_vx6.insertLegend(legIconNames_vx6, 0.55, 0.88, 0.72, 0.90);
		plot_vx6.insertAdditionalText(additionalTextString.c_str());
		plot_vx6.setAdditionalTextLocation(0.1,8.5);
		plot_vx6.plotAndSave(11, directoryName.c_str(), "rates_met_mht_emuHwDiffFile.pdf");

		rootPlotMaker plot_vx7;
		vector<string> histoNames_vx7;
		histoNames_vx7.push_back("singleJetRates_emu");
		histoNames_vx7.push_back("singleJetRates_hw");
		histoNames_vx7.push_back("doubleJetRates_emu");
		histoNames_vx7.push_back("doubleJetRates_hw");
		histoNames_vx7.push_back("tripleJetRates_emu");
		histoNames_vx7.push_back("tripleJetRates_hw");
		histoNames_vx7.push_back("quadJetRates_emu");    
		histoNames_vx7.push_back("quadJetRates_hw"); 
		vector<string> legIconNames_vx7;
		legIconNames_vx7.push_back("SingleJet emu");
		legIconNames_vx7.push_back("SingleJet hw");
		legIconNames_vx7.push_back("DoubleJet emu");
		legIconNames_vx7.push_back("DoubleJet hw");
		legIconNames_vx7.push_back("TripleJet emu");
		legIconNames_vx7.push_back("TripleJet hw");
		legIconNames_vx7.push_back("QuadJet emu");
		legIconNames_vx7.push_back("QuadJet hw");
		plot_vx7.loadHistogramsInfo(inputFilePath_twoFiles,histoNames_vx7,histogramLineWidths_alt23,
									   histogramLineColours_twosDifferent,histogramLineStyles_altSolidDotted);
		plot_vx7.setXaxisRange(0,300);
		plot_vx7.turnGridLinesOn();
		plot_vx7.turnLogYon();
		plot_vx7.insertLegend(legIconNames_vx7, 0.55, 0.88, 0.55, 0.90);
		plot_vx7.insertAdditionalText(additionalTextString.c_str());
		plot_vx7.setAdditionalTextLocation(0.1,8.5);
		plot_vx7.plotAndSave(11, directoryName.c_str(), "rates_jets1234_emuHwDiffFile.pdf");

		rootPlotMaker plot_vx8;
		vector<string> histoNames_vx8;
		histoNames_vx8.push_back("singleEgRates_emu");
		histoNames_vx8.push_back("singleEgRates_hw");
		histoNames_vx8.push_back("singleISOEgRates_emu");
		histoNames_vx8.push_back("singleISOEgRates_hw");		
		histoNames_vx8.push_back("doubleEgRates_emu");
		histoNames_vx8.push_back("doubleEgRates_hw");
 		histoNames_vx8.push_back("doubleISOEgRates_emu");
		histoNames_vx8.push_back("doubleISOEgRates_hw");
		vector<string> legIconNames_vx8;
		legIconNames_vx8.push_back("SingleEG emu");
		legIconNames_vx8.push_back("SingleEG hw");
		legIconNames_vx8.push_back("isoSingleEG emu");
		legIconNames_vx8.push_back("isoSingleEG hw");		
		legIconNames_vx8.push_back("DoubleEG emu");
		legIconNames_vx8.push_back("DoubleEG hw");
		legIconNames_vx8.push_back("isoDoubleEG emu");
		legIconNames_vx8.push_back("isoDoubleEG hw");
		plot_vx8.loadHistogramsInfo(inputFilePath_twoFiles,histoNames_vx8,histogramLineWidths_alt23,
									   histogramLineColours_twosDifferent,histogramLineStyles_altSolidDotted);
		plot_vx8.setXaxisRange(0,200);
		plot_vx8.turnGridLinesOn();
		plot_vx8.turnLogYon();
		plot_vx8.insertLegend(legIconNames_vx8, 0.55, 0.88, 0.55, 0.90);
		plot_vx8.plotAndSave(11, directoryName.c_str(), "rates_eg12_emuHwDiffFile.pdf");

		rootPlotMaker plot_vx9;
		vector<string> histoNames_vx9;
		histoNames_vx9.push_back("singleTauRates_emu");  
		histoNames_vx9.push_back("singleTauRates_hw");
		histoNames_vx9.push_back("singleISOTauRates_emu");  
		histoNames_vx9.push_back("singleISOTauRates_hw");    
		histoNames_vx9.push_back("doubleTauRates_emu");  
		histoNames_vx9.push_back("doubleTauRates_hw");
		histoNames_vx9.push_back("doubleISOTauRates_emu");  
		histoNames_vx9.push_back("doubleISOTauRates_hw");
		vector<string> legIconNames_vx9;
		legIconNames_vx9.push_back("SingleTau emu");
		legIconNames_vx9.push_back("SingleTau hw");
		legIconNames_vx9.push_back("isoSingleTau emu");
		legIconNames_vx9.push_back("isoSingleTau hw");		
		legIconNames_vx9.push_back("DoubleTau emu");
		legIconNames_vx9.push_back("DoubleTau hw");
		legIconNames_vx9.push_back("isoDoubleTau emu");
		legIconNames_vx9.push_back("isoDoubleTau hw");	
		plot_vx9.loadHistogramsInfo(inputFilePath_twoFiles,histoNames_vx9,histogramLineWidths_alt23,
									   histogramLineColours_twosDifferent,histogramLineStyles_altSolidDotted);
		plot_vx9.setXaxisRange(0,200);
		plot_vx9.turnGridLinesOn();
		plot_vx9.turnLogYon();
		plot_vx9.insertLegend(legIconNames_vx9, 0.55, 0.88, 0.55, 0.90);
		plot_vx9.plotAndSave(11, directoryName.c_str(), "rates_tau12_emuHwDiffFile.pdf");

	} // closes 'if' plotSetType=="rates_hwEmuDiffFiles"







	if (plotSetType=="rates_hwDiffFiles"){

		string additionalTextString = "CMS preliminary";

		rootPlotMaker plot_vx5;
		vector<string> histoNames_vx5;
		histoNames_vx5.push_back("etSumRates_hw");
		histoNames_vx5.push_back("etSumRates_hw");
		histoNames_vx5.push_back("htSumRates_hw");    
		histoNames_vx5.push_back("htSumRates_hw");    
		vector<string> legIconNames_vx5;
		legIconNames_vx5.push_back("Total E_{T} run273301");
		legIconNames_vx5.push_back("Total E_{T} run272798");
		legIconNames_vx5.push_back("Total H_{T} run273301");
		legIconNames_vx5.push_back("Total H_{T} run272798");
		plot_vx5.loadHistogramsInfo(inputFilePath_twoFiles,histoNames_vx5,histogramLineWidths_alt23,
									   histogramLineColours_twosDifferent,histogramLineStyles_altSolidDotted);
		// plot_vx5.setXaxisRange(0,500);
		plot_vx5.turnGridLinesOn();
		plot_vx5.turnLogYon();
		plot_vx5.insertLegend(legIconNames_vx5, 0.55, 0.88, 0.72, 0.90);
		plot_vx5.insertAdditionalText(additionalTextString.c_str());
		plot_vx5.setAdditionalTextLocation(0.1,8.5);
		plot_vx5.plotAndSave(11, directoryName.c_str(), "rates_et_ht_hwHwDiffFile.pdf");

		rootPlotMaker plot_vx6;
		vector<string> histoNames_vx6;
		histoNames_vx6.push_back("metSumRates_hw");
		histoNames_vx6.push_back("metSumRates_hw");
		histoNames_vx6.push_back("mhtSumRates_hw");       
		histoNames_vx6.push_back("mhtSumRates_hw");     
		vector<string> legIconNames_vx6;
		legIconNames_vx6.push_back("Missing E_{T} run273301");
		legIconNames_vx6.push_back("Missing E_{T} run272798");
		legIconNames_vx6.push_back("Missing H_{T} run273301");
		legIconNames_vx6.push_back("Missing H_{T} run272798");
		plot_vx6.loadHistogramsInfo(inputFilePath_twoFiles,histoNames_vx6,histogramLineWidths_alt23,
									   histogramLineColours_twosDifferent,histogramLineStyles_altSolidDotted);
		plot_vx6.setXaxisRange(0,200);
		plot_vx6.turnGridLinesOn();
		plot_vx6.turnLogYon();
		plot_vx6.insertLegend(legIconNames_vx6, 0.55, 0.88, 0.72, 0.90);
		plot_vx6.insertAdditionalText(additionalTextString.c_str());
		plot_vx6.setAdditionalTextLocation(0.1,8.5);
		plot_vx6.plotAndSave(11, directoryName.c_str(), "rates_met_mht_hwHwDiffFile.pdf");

		rootPlotMaker plot_vx7;
		vector<string> histoNames_vx7;
		histoNames_vx7.push_back("singleJetRates_hw");
		histoNames_vx7.push_back("singleJetRates_hw");
		histoNames_vx7.push_back("doubleJetRates_hw");
		histoNames_vx7.push_back("doubleJetRates_hw");
		histoNames_vx7.push_back("tripleJetRates_hw");
		histoNames_vx7.push_back("tripleJetRates_hw");
		histoNames_vx7.push_back("quadJetRates_hw");    
		histoNames_vx7.push_back("quadJetRates_hw"); 
		vector<string> legIconNames_vx7;
		legIconNames_vx7.push_back("SingleJet run273301");
		legIconNames_vx7.push_back("SingleJet run272798");
		legIconNames_vx7.push_back("DoubleJet run273301");
		legIconNames_vx7.push_back("DoubleJet run272798");
		legIconNames_vx7.push_back("TripleJet run273301");
		legIconNames_vx7.push_back("TripleJet run272798");
		legIconNames_vx7.push_back("QuadJet run273301");
		legIconNames_vx7.push_back("QuadJet run272798");
		plot_vx7.loadHistogramsInfo(inputFilePath_twoFiles,histoNames_vx7,histogramLineWidths_alt23,
									   histogramLineColours_twosDifferent,histogramLineStyles_altSolidDotted);
		plot_vx7.setXaxisRange(0,300);
		plot_vx7.turnGridLinesOn();
		plot_vx7.turnLogYon();
		plot_vx7.insertLegend(legIconNames_vx7, 0.55, 0.88, 0.55, 0.90);
		plot_vx7.insertAdditionalText(additionalTextString.c_str());
		plot_vx7.setAdditionalTextLocation(0.1,8.5);
		plot_vx7.plotAndSave(11, directoryName.c_str(), "rates_jets1234_hwHwDiffFile.pdf");

		rootPlotMaker plot_vx8;
		vector<string> histoNames_vx8;
		histoNames_vx8.push_back("singleEgRates_hw");
		histoNames_vx8.push_back("singleEgRates_hw");
		histoNames_vx8.push_back("singleISOEgRates_hw");
		histoNames_vx8.push_back("singleISOEgRates_hw");		
		histoNames_vx8.push_back("doubleEgRates_hw");
		histoNames_vx8.push_back("doubleEgRates_hw");
 		histoNames_vx8.push_back("doubleISOEgRates_hw");
		histoNames_vx8.push_back("doubleISOEgRates_hw");
		vector<string> legIconNames_vx8;
		legIconNames_vx8.push_back("SingleEG run273301");
		legIconNames_vx8.push_back("SingleEG run272798");
		legIconNames_vx8.push_back("isoSingleEG run273301");
		legIconNames_vx8.push_back("isoSingleEG hrun272798");		
		legIconNames_vx8.push_back("DoubleEG run273301");
		legIconNames_vx8.push_back("DoubleEG run272798");
		legIconNames_vx8.push_back("isoDoubleEG run273301");
		legIconNames_vx8.push_back("isoDoubleEG run272798");
		plot_vx8.loadHistogramsInfo(inputFilePath_twoFiles,histoNames_vx8,histogramLineWidths_alt23,
									   histogramLineColours_twosDifferent,histogramLineStyles_altSolidDotted);
		plot_vx8.setXaxisRange(0,200);
		plot_vx8.turnGridLinesOn();
		plot_vx8.turnLogYon();
		plot_vx8.insertLegend(legIconNames_vx8, 0.55, 0.88, 0.55, 0.90);
		plot_vx8.plotAndSave(11, directoryName.c_str(), "rates_eg12_hwHwDiffFile.pdf");

		rootPlotMaker plot_vx9;
		vector<string> histoNames_vx9;
		histoNames_vx9.push_back("singleTauRates_hw");  
		histoNames_vx9.push_back("singleTauRates_hw");
		histoNames_vx9.push_back("singleISOTauRates_hw");  
		histoNames_vx9.push_back("singleISOTauRates_hw");    
		histoNames_vx9.push_back("doubleTauRates_hw");  
		histoNames_vx9.push_back("doubleTauRates_hw");
		histoNames_vx9.push_back("doubleISOTauRates_hw");  
		histoNames_vx9.push_back("doubleISOTauRates_hw");
		vector<string> legIconNames_vx9;
		legIconNames_vx9.push_back("SingleTau run273301");
		legIconNames_vx9.push_back("SingleTau run272798");
		legIconNames_vx9.push_back("isoSingleTau run273301");
		legIconNames_vx9.push_back("isoSingleTau hrun272798");		
		legIconNames_vx9.push_back("DoubleTau run273301");
		legIconNames_vx9.push_back("DoubleTau run272798");
		legIconNames_vx9.push_back("isoDoubleTau run273301");
		legIconNames_vx9.push_back("isoDoubleTau hrun272798");	
		plot_vx9.loadHistogramsInfo(inputFilePath_twoFiles,histoNames_vx9,histogramLineWidths_alt23,
									   histogramLineColours_twosDifferent,histogramLineStyles_altSolidDotted);
		plot_vx9.setXaxisRange(0,200);
		plot_vx9.turnGridLinesOn();
		plot_vx9.turnLogYon();
		plot_vx9.insertLegend(legIconNames_vx9, 0.55, 0.88, 0.55, 0.90);
		plot_vx9.plotAndSave(11, directoryName.c_str(), "rates_tau12_hwDiffFile.pdf");

	} // closes 'if' plotSetType=="rates_hwEmuDiffFiles"









	if (plotSetType=="jets"){

		string additionalTextString = "CMS preliminary, singleMuon, run273301";

		rootPlotMaker plot_ve1;
	    vector<string> histoNums_ve1;
	    histoNums_ve1.push_back("hnum36_central");
	    histoNums_ve1.push_back("hnum52_central");
	    histoNums_ve1.push_back("hnum68_central");   
	    histoNums_ve1.push_back("hnum92_central"); 
	    histoNums_ve1.push_back("hnum128_central");
	    histoNums_ve1.push_back("hnum176_central"); 
	    histoNums_ve1.push_back("hnum200_central"); 
	    string histoDen_ve1 = "hden_central";
	    vector<string> histoEffs_ve1;
	    histoEffs_ve1.push_back("hT36_central");
	    histoEffs_ve1.push_back("hT52_central");
	    histoEffs_ve1.push_back("hT68_central");   
	    histoEffs_ve1.push_back("hT92_central"); 
	    histoEffs_ve1.push_back("hT128_central");
	    histoEffs_ve1.push_back("hT176_central"); 
	    histoEffs_ve1.push_back("hT200_central");
		vector<string> legIconNames_ve1;
		legIconNames_ve1.push_back("L1 Jet E_{T} > 36GeV");
		legIconNames_ve1.push_back("L1 Jet E_{T} > 52GeV");
		legIconNames_ve1.push_back("L1 Jet E_{T} > 68GeV");
		legIconNames_ve1.push_back("L1 Jet E_{T} > 92GeV");
		legIconNames_ve1.push_back("L1 Jet E_{T} > 128GeV");
		legIconNames_ve1.push_back("L1 Jet E_{T} > 176GeV");
		legIconNames_ve1.push_back("L1 Jet E_{T} > 200GeV");
		plot_ve1.loadEfficiencies(path,histoNums_ve1,histoDen_ve1,histoEffs_ve1,histogramLineWidths_allSize2,
						     	   histogramLineColours_allDifferent,histogramLineStyles_allSolidLines,
						     	   widthVector_jetCentral,true);//last bit of bool is fit on/off
		plot_ve1.insertLegend(legIconNames_ve1, 0.60, 0.88, 0.12, 0.40);
		plot_ve1.setXaxisRange(0,300);
		plot_ve1.turnGridLinesOn();
		plot_ve1.insertAdditionalText(additionalTextString.c_str());
		plot_ve1.setAdditionalTextLocation(0,1.07);
		plot_ve1.plotAndSave(3, directoryName.c_str(), "jetEfficiencyTurnOns_central.pdf");

		rootPlotMaker plot_ve2;
	    vector<string> histoNums_ve2;
	    histoNums_ve2.push_back("hnum36_hf");
	    histoNums_ve2.push_back("hnum52_hf");
	    histoNums_ve2.push_back("hnum68_hf");   
	    histoNums_ve2.push_back("hnum92_hf"); 
	    histoNums_ve2.push_back("hnum128_hf");
	    histoNums_ve2.push_back("hnum176_hf"); 
	    // histoNums_ve2.push_back("hnum200_hf"); 
	    string histoDen_ve2 = "hden_hf";
	    vector<string> histoEffs_ve2;
	    histoEffs_ve2.push_back("hT36_hf");
	    histoEffs_ve2.push_back("hT52_hf");
	    histoEffs_ve2.push_back("hT68_hf");   
	    histoEffs_ve2.push_back("hT92_hf"); 
	    histoEffs_ve2.push_back("hT128_hf");
	    histoEffs_ve2.push_back("hT176_hf"); 
	    // histoEffs_ve2.push_back("hT200_hf");
		vector<string> legIconNames_ve2;
		legIconNames_ve2.push_back("L1 Jet E_{T}>36GeV");
		legIconNames_ve2.push_back("L1 Jet E_{T}>52GeV");
		legIconNames_ve2.push_back("L1 Jet E_{T}>68GeV");
		legIconNames_ve2.push_back("L1 Jet E_{T}>92GeV");
		legIconNames_ve2.push_back("L1 Jet E_{T}>128GeV");
		legIconNames_ve2.push_back("L1 Jet E_{T}>176GeV");
		// legIconNames_ve2.push_back("L1 Jet E_{T}>200GeV");
		plot_ve2.loadEfficiencies(path,histoNums_ve2,histoDen_ve2,histoEffs_ve2,histogramLineWidths_allSize2,
						     	   histogramLineColours_allDifferent,histogramLineStyles_allSolidLines,
						     	   widthVector_jetHF,true);
		plot_ve2.insertLegend(legIconNames_ve2, 0.60, 0.88, 0.12, 0.40);
		plot_ve2.setXaxisRange(0,300);
		plot_ve2.turnGridLinesOn();
		plot_ve2.insertAdditionalText(additionalTextString.c_str());
		plot_ve2.setAdditionalTextLocation(0,1.07);
		plot_ve2.plotAndSave(3, directoryName.c_str(), "jetEfficiencyTurnOns_hf.pdf");


		rootPlotMaker plot_ve3;
	    vector<string> histoNums_ve3;
	    histoNums_ve3.push_back("hnum36_barrel");
	    histoNums_ve3.push_back("hnum52_barrel");
	    histoNums_ve3.push_back("hnum68_barrel");   
	    histoNums_ve3.push_back("hnum92_barrel"); 
	    histoNums_ve3.push_back("hnum128_barrel");
	    histoNums_ve3.push_back("hnum176_barrel"); 
	    histoNums_ve3.push_back("hnum200_barrel"); 
	    string histoDen_ve3 = "hden_barrel";
	    vector<string> histoEffs_ve3;
	    histoEffs_ve3.push_back("hT36_barrel");
	    histoEffs_ve3.push_back("hT52_barrel");
	    histoEffs_ve3.push_back("hT68_barrel");   
	    histoEffs_ve3.push_back("hT92_barrel"); 
	    histoEffs_ve3.push_back("hT128_barrel");
	    histoEffs_ve3.push_back("hT176_barrel"); 
	    histoEffs_ve3.push_back("hT200_barrel");
		vector<string> legIconNames_ve3;
		legIconNames_ve3.push_back("L1 Jet E_{T}>36GeV");
		legIconNames_ve3.push_back("L1 Jet E_{T}>52GeV");
		legIconNames_ve3.push_back("L1 Jet E_{T}>68GeV");
		legIconNames_ve3.push_back("L1 Jet E_{T}>92GeV");
		legIconNames_ve3.push_back("L1 Jet E_{T}>128GeV");
		legIconNames_ve3.push_back("L1 Jet E_{T}>176GeV");
		legIconNames_ve3.push_back("L1 Jet E_{T}>200GeV");
		plot_ve3.loadEfficiencies(path,histoNums_ve3,histoDen_ve3,histoEffs_ve3,histogramLineWidths_allSize2,
						     	   histogramLineColours_allDifferent,histogramLineStyles_allSolidLines,
						     	   widthVector_jetBarrel,true);
		plot_ve3.insertLegend(legIconNames_ve3, 0.60, 0.88, 0.12, 0.40);
		plot_ve3.setXaxisRange(0,300);
		plot_ve3.turnGridLinesOn();
		plot_ve3.insertAdditionalText(additionalTextString.c_str());
		plot_ve3.setAdditionalTextLocation(0,1.07);
		plot_ve3.plotAndSave(3, directoryName.c_str(), "jetEfficiencyTurnOns_barrel.pdf");



		rootPlotMaker plot_ve4;
	    vector<string> histoNums_ve4;
	    histoNums_ve4.push_back("hnum36_endcap");
	    histoNums_ve4.push_back("hnum52_endcap");
	    histoNums_ve4.push_back("hnum68_endcap");   
	    histoNums_ve4.push_back("hnum92_endcap"); 
	    histoNums_ve4.push_back("hnum128_endcap");
	    histoNums_ve4.push_back("hnum176_endcap"); 
	    histoNums_ve4.push_back("hnum200_endcap"); 
	    string histoDen_ve4 = "hden_endcap";
	    vector<string> histoEffs_ve4;
	    histoEffs_ve4.push_back("hT36_endcap");
	    histoEffs_ve4.push_back("hT52_endcap");
	    histoEffs_ve4.push_back("hT68_endcap");   
	    histoEffs_ve4.push_back("hT92_endcap"); 
	    histoEffs_ve4.push_back("hT128_endcap");
	    histoEffs_ve4.push_back("hT176_endcap"); 
	    histoEffs_ve4.push_back("hT200_endcap");
		vector<string> legIconNames_ve4;
		legIconNames_ve4.push_back("L1 Jet E_{T}>36GeV");
		legIconNames_ve4.push_back("L1 Jet E_{T}>52GeV");
		legIconNames_ve4.push_back("L1 Jet E_{T}>68GeV");
		legIconNames_ve4.push_back("L1 Jet E_{T}>92GeV");
		legIconNames_ve4.push_back("L1 Jet E_{T}>128GeV");
		legIconNames_ve4.push_back("L1 Jet E_{T}>176GeV");
		legIconNames_ve4.push_back("L1 Jet E_{T}>200GeV");
		plot_ve4.loadEfficiencies(path,histoNums_ve4,histoDen_ve4,histoEffs_ve4,histogramLineWidths_allSize2,
						     	   histogramLineColours_allDifferent,histogramLineStyles_allSolidLines,
						     	   widthVector_jetEndcap,true);
		plot_ve4.insertLegend(legIconNames_ve4, 0.60, 0.88, 0.12, 0.40);
		plot_ve4.setXaxisRange(0,300);
		plot_ve4.turnGridLinesOn();
		plot_ve4.insertAdditionalText(additionalTextString.c_str());
		plot_ve4.setAdditionalTextLocation(0,1.07);
		plot_ve4.plotAndSave(3, directoryName.c_str(), "jetEfficiencyTurnOns_endcap.pdf");

		// // central
		// rootPlotMaker plot_vx01;
		// vector<string> histoNames_vx01;
		// histoNames_vx01.push_back("hdPhi_central");
		// plot_vx01.loadHistogramsInfo(inputFilePath_allSame,histoNames_vx01,histogramLineWidths_allSize2,
		// 							   histogramLineColours_allDifferent,histogramLineStyles_allSolidLines);
		// plot_vx01.turnGridLinesOn();
		// plot_vx01.plotAndSave(1, directoryName.c_str(), "dPhi_central.pdf");

		// rootPlotMaker plot_vx02;
		// vector<string> histoNames_vx02;
		// histoNames_vx02.push_back("hdEta_central");
		// plot_vx02.loadHistogramsInfo(inputFilePath_allSame,histoNames_vx02,histogramLineWidths_allSize2,
		// 							   histogramLineColours_allDifferent,histogramLineStyles_allSolidLines);
		// plot_vx02.turnGridLinesOn();
		// plot_vx02.plotAndSave(1, directoryName.c_str(), "dEta_central.pdf");

		// rootPlotMaker plot_vx03;
		// vector<string> histoNames_vx03;
		// histoNames_vx03.push_back("hdR_central");
		// plot_vx03.loadHistogramsInfo(inputFilePath_allSame,histoNames_vx03,histogramLineWidths_allSize2,
		// 							   histogramLineColours_allDifferent,histogramLineStyles_allSolidLines);
		// plot_vx03.turnGridLinesOn();
		// plot_vx03.plotAndSave(1, directoryName.c_str(), "dR_central.pdf");

		// rootPlotMaker plot_vx04;
		// vector<string> histoNames_vx04;
		// histoNames_vx04.push_back("hdET_central");
		// plot_vx04.loadHistogramsInfo(inputFilePath_allSame,histoNames_vx04,histogramLineWidths_allSize2,
		// 							   histogramLineColours_allDifferent,histogramLineStyles_allSolidLines);
		// plot_vx04.turnGridLinesOn();
		// plot_vx04.plotAndSave(1, directoryName.c_str(), "dET_central.pdf");

		// rootPlotMaker plot_vxy01;
		// plot_vxy01.loadHistogram2D(path.c_str(), "hPosScat_central");
		// plot_vxy01.turnLogZon();
		// plot_vxy01.plotAndSave(2, directoryName.c_str(), "positionScatter_central.pdf");

		// rootPlotMaker plot_vxy02;    
		// plot_vxy02.loadHistogram2D(path.c_str(), "hETS_central");
		// plot_vxy02.turnLogZon();
		// plot_vxy02.plotAndSave(2, directoryName.c_str(), "energyScatter_central.pdf");

		// rootPlotMaker plot_vxy03;    
		// plot_vxy03.loadHistogram2D(path.c_str(), "hdPhiVsET_central");
		// plot_vxy03.turnLogZon();
		// plot_vxy03.plotAndSave(2, directoryName.c_str(), "dPhivET_central.pdf");

		// rootPlotMaker plot_vxy04;    
		// plot_vxy04.loadHistogram2D(path.c_str(), "hdEtaVsET_central");
		// plot_vxy04.turnLogZon();
		// plot_vxy04.plotAndSave(2, directoryName.c_str(), "dEtavET_central.pdf");

		// rootPlotMaker plot_vxy05;    
		// plot_vxy05.loadHistogram2D(path.c_str(), "hdEtVsET_central");
		// plot_vxy05.turnLogZon();
		// plot_vxy05.plotAndSave(2, directoryName.c_str(), "dETvET_central.pdf");


		// // hf
		// rootPlotMaker plot_vx11;
		// vector<string> histoNames_vx11;
		// histoNames_vx11.push_back("hdPhi_hf");
		// plot_vx11.loadHistogramsInfo(inputFilePath_allSame,histoNames_vx11,histogramLineWidths_allSize2,
		// 							   histogramLineColours_allDifferent,histogramLineStyles_allSolidLines);
		// plot_vx11.turnGridLinesOn();
		// plot_vx11.plotAndSave(1, directoryName.c_str(), "dPhi_hf.pdf");

		// rootPlotMaker plot_vx12;
		// vector<string> histoNames_vx12;
		// histoNames_vx12.push_back("hdEta_hf");
		// plot_vx12.loadHistogramsInfo(inputFilePath_allSame,histoNames_vx12,histogramLineWidths_allSize2,
		// 							   histogramLineColours_allDifferent,histogramLineStyles_allSolidLines);
		// plot_vx12.turnGridLinesOn();
		// plot_vx12.plotAndSave(1, directoryName.c_str(), "dEta_hf.pdf");

		// rootPlotMaker plot_vx13;
		// vector<string> histoNames_vx13;
		// histoNames_vx13.push_back("hdR_hf");
		// plot_vx13.loadHistogramsInfo(inputFilePath_allSame,histoNames_vx13,histogramLineWidths_allSize2,
		// 							   histogramLineColours_allDifferent,histogramLineStyles_allSolidLines);
		// plot_vx13.turnGridLinesOn();
		// plot_vx13.plotAndSave(1, directoryName.c_str(), "dR_hf.pdf");

		// rootPlotMaker plot_vx14;
		// vector<string> histoNames_vx14;
		// histoNames_vx14.push_back("hdET_hf");
		// plot_vx14.loadHistogramsInfo(inputFilePath_allSame,histoNames_vx14,histogramLineWidths_allSize2,
		// 							   histogramLineColours_allDifferent,histogramLineStyles_allSolidLines);
		// plot_vx14.turnGridLinesOn();
		// plot_vx14.plotAndSave(1, directoryName.c_str(), "dET_hf.pdf");

		// rootPlotMaker plot_vxy11;
		// plot_vxy11.loadHistogram2D(path.c_str(), "hPosScat_hf");
		// plot_vxy11.turnLogZon();
		// plot_vxy11.plotAndSave(2, directoryName.c_str(), "positionScatter_hf.pdf");

		// rootPlotMaker plot_vxy12;    
		// plot_vxy12.loadHistogram2D(path.c_str(), "hETS_hf");
		// plot_vxy12.turnLogZon();
		// plot_vxy12.plotAndSave(2, directoryName.c_str(), "energyScatter_hf.pdf");

		// rootPlotMaker plot_vxy13;    
		// plot_vxy13.loadHistogram2D(path.c_str(), "hdPhiVsET_hf");
		// plot_vxy13.turnLogZon();
		// plot_vxy13.plotAndSave(2, directoryName.c_str(), "dPhivET_hf.pdf");

		// rootPlotMaker plot_vxy14;    
		// plot_vxy14.loadHistogram2D(path.c_str(), "hdEtaVsET_hf");
		// plot_vxy14.turnLogZon();
		// plot_vxy14.plotAndSave(2, directoryName.c_str(), "dEtavET_hf.pdf");

		// rootPlotMaker plot_vxy15;    
		// plot_vxy15.loadHistogram2D(path.c_str(), "hdEtVsET_hf");
		// plot_vxy15.turnLogZon();
		// plot_vxy15.plotAndSave(2, directoryName.c_str(), "dETvET_hf.pdf");



		// // barrel
		// rootPlotMaker plot_vx21;
		// vector<string> histoNames_vx21;
		// histoNames_vx21.push_back("hdPhi_barrel");
		// plot_vx21.loadHistogramsInfo(inputFilePath_allSame,histoNames_vx21,histogramLineWidths_allSize2,
		// 							   histogramLineColours_allDifferent,histogramLineStyles_allSolidLines);
		// plot_vx21.turnGridLinesOn();
		// plot_vx21.plotAndSave(1, directoryName.c_str(), "dPhi_barrel.pdf");

		// rootPlotMaker plot_vx22;
		// vector<string> histoNames_vx22;
		// histoNames_vx22.push_back("hdEta_barrel");
		// plot_vx22.loadHistogramsInfo(inputFilePath_allSame,histoNames_vx22,histogramLineWidths_allSize2,
		// 							   histogramLineColours_allDifferent,histogramLineStyles_allSolidLines);
		// plot_vx22.turnGridLinesOn();
		// plot_vx22.plotAndSave(1, directoryName.c_str(), "dEta_barrel.pdf");

		// rootPlotMaker plot_vx23;
		// vector<string> histoNames_vx23;
		// histoNames_vx23.push_back("hdR_barrel");
		// plot_vx23.loadHistogramsInfo(inputFilePath_allSame,histoNames_vx23,histogramLineWidths_allSize2,
		// 							   histogramLineColours_allDifferent,histogramLineStyles_allSolidLines);
		// plot_vx23.turnGridLinesOn();
		// plot_vx23.plotAndSave(1, directoryName.c_str(), "dR_barrel.pdf");

		// rootPlotMaker plot_vx24;
		// vector<string> histoNames_vx24;
		// histoNames_vx24.push_back("hdET_barrel");
		// plot_vx24.loadHistogramsInfo(inputFilePath_allSame,histoNames_vx24,histogramLineWidths_allSize2,
		// 							   histogramLineColours_allDifferent,histogramLineStyles_allSolidLines);
		// plot_vx24.turnGridLinesOn();
		// plot_vx24.plotAndSave(1, directoryName.c_str(), "dET_barrel.pdf");

		// rootPlotMaker plot_vxy21;
		// plot_vxy21.loadHistogram2D(path.c_str(), "hPosScat_barrel");
		// plot_vxy21.turnLogZon();
		// plot_vxy21.plotAndSave(2, directoryName.c_str(), "positionScatter_barrel.pdf");

		// rootPlotMaker plot_vxy22;    
		// plot_vxy22.loadHistogram2D(path.c_str(), "hETS_barrel");
		// plot_vxy22.turnLogZon();
		// plot_vxy22.plotAndSave(2, directoryName.c_str(), "energyScatter_barrel.pdf");

		// rootPlotMaker plot_vxy23;    
		// plot_vxy23.loadHistogram2D(path.c_str(), "hdPhiVsET_barrel");
		// plot_vxy23.turnLogZon();
		// plot_vxy23.plotAndSave(2, directoryName.c_str(), "dPhivET_barrel.pdf");

		// rootPlotMaker plot_vxy24;    
		// plot_vxy24.loadHistogram2D(path.c_str(), "hdEtaVsET_barrel");
		// plot_vxy24.turnLogZon();
		// plot_vxy24.plotAndSave(2, directoryName.c_str(), "dEtavET_barrel.pdf");

		// rootPlotMaker plot_vxy25;    
		// plot_vxy25.loadHistogram2D(path.c_str(), "hdEtVsET_barrel");
		// plot_vxy25.turnLogZon();
		// plot_vxy25.plotAndSave(2, directoryName.c_str(), "dETvET_barrel.pdf");




		// // endcap
		// rootPlotMaker plot_vx31;
		// vector<string> histoNames_vx31;
		// histoNames_vx31.push_back("hdPhi_endcap");
		// plot_vx31.loadHistogramsInfo(inputFilePath_allSame,histoNames_vx31,histogramLineWidths_allSize2,
		// 							   histogramLineColours_allDifferent,histogramLineStyles_allSolidLines);
		// plot_vx31.turnGridLinesOn();
		// plot_vx31.plotAndSave(1, directoryName.c_str(), "dPhi_endcap.pdf");

		// rootPlotMaker plot_vx32;
		// vector<string> histoNames_vx32;
		// histoNames_vx32.push_back("hdEta_endcap");
		// plot_vx32.loadHistogramsInfo(inputFilePath_allSame,histoNames_vx32,histogramLineWidths_allSize2,
		// 							   histogramLineColours_allDifferent,histogramLineStyles_allSolidLines);
		// plot_vx32.turnGridLinesOn();
		// plot_vx32.plotAndSave(1, directoryName.c_str(), "dEta_endcap.pdf");

		// rootPlotMaker plot_vx33;
		// vector<string> histoNames_vx33;
		// histoNames_vx33.push_back("hdR_endcap");
		// plot_vx33.loadHistogramsInfo(inputFilePath_allSame,histoNames_vx33,histogramLineWidths_allSize2,
		// 							   histogramLineColours_allDifferent,histogramLineStyles_allSolidLines);
		// plot_vx33.turnGridLinesOn();
		// plot_vx33.plotAndSave(1, directoryName.c_str(), "dR_endcap.pdf");

		// rootPlotMaker plot_vx34;
		// vector<string> histoNames_vx34;
		// histoNames_vx34.push_back("hdET_endcap");
		// plot_vx34.loadHistogramsInfo(inputFilePath_allSame,histoNames_vx34,histogramLineWidths_allSize2,
		// 							   histogramLineColours_allDifferent,histogramLineStyles_allSolidLines);
		// plot_vx34.turnGridLinesOn();
		// plot_vx34.plotAndSave(1, directoryName.c_str(), "dET_endcap.pdf");

		// rootPlotMaker plot_vxy31;
		// plot_vxy31.loadHistogram2D(path.c_str(), "hPosScat_endcap");
		// plot_vxy31.turnLogZon();
		// plot_vxy31.plotAndSave(2, directoryName.c_str(), "positionScatter_endcap.pdf");

		// rootPlotMaker plot_vxy32;    
		// plot_vxy32.loadHistogram2D(path.c_str(), "hETS_endcap");
		// plot_vxy32.turnLogZon();
		// plot_vxy32.plotAndSave(2, directoryName.c_str(), "energyScatter_endcap.pdf");

		// rootPlotMaker plot_vxy33;    
		// plot_vxy33.loadHistogram2D(path.c_str(), "hdPhiVsET_endcap");
		// plot_vxy33.turnLogZon();
		// plot_vxy33.plotAndSave(2, directoryName.c_str(), "dPhivET_endcap.pdf");

		// rootPlotMaker plot_vxy34;    
		// plot_vxy34.loadHistogram2D(path.c_str(), "hdEtaVsET_endcap");
		// plot_vxy34.turnLogZon();
		// plot_vxy34.plotAndSave(2, directoryName.c_str(), "dEtavET_endcap.pdf");

		// rootPlotMaker plot_vxy35;    
		// plot_vxy35.loadHistogram2D(path.c_str(), "hdEtVsET_endcap");
		// plot_vxy35.turnLogZon();
		// plot_vxy35.plotAndSave(2, directoryName.c_str(), "dETvET_endcap.pdf");


	} // closes 'if' plotSetType=="jets"




	if (plotSetType=="esums"){

		rootPlotMaker plot_ve1;
	    vector<string> histoNums_ve1;
	    histoNums_ve1.push_back("hnum_ETT_100");
	    histoNums_ve1.push_back("hnum_ETT_125");
	    histoNums_ve1.push_back("hnum_ETT_150");   
	    histoNums_ve1.push_back("hnum_ETT_175"); 
	    histoNums_ve1.push_back("hnum_ETT_200");
	    histoNums_ve1.push_back("hnum_ETT_250"); 
	    string histoDen_ve1 = "hden_ETT";
	    vector<string> histoEffs_ve1;
	    histoEffs_ve1.push_back("hEff_ETT_100");
	    histoEffs_ve1.push_back("hEff_ETT_125");
	    histoEffs_ve1.push_back("hEff_ETT_150");   
	    histoEffs_ve1.push_back("hEff_ETT_175"); 
	    histoEffs_ve1.push_back("hEff_ETT_200");
	    histoEffs_ve1.push_back("hEff_ETT_250"); 
		vector<string> legIconNames_ve1;
		legIconNames_ve1.push_back("ETT>100");
		legIconNames_ve1.push_back("ETT>125");
		legIconNames_ve1.push_back("ETT>150");
		legIconNames_ve1.push_back("ETT>175");
		legIconNames_ve1.push_back("ETT>200");
		legIconNames_ve1.push_back("ETT>250");
		plot_ve1.loadEfficiencies(path,histoNums_ve1,histoDen_ve1,histoEffs_ve1,histogramLineWidths_allSize2,
						     	   histogramLineColours_allDifferent,histogramLineStyles_allSolidLines,
						     	   widthVector_jetCentral,false);
		plot_ve1.insertLegend(legIconNames_ve1, 0.65, 0.85, 0.15, 0.35);
		plot_ve1.turnGridLinesOn();
		plot_ve1.plotAndSave(31, directoryName.c_str(), "ETT_EfficiencyTurnOns.pdf");


		rootPlotMaker plot_ve2;
	    vector<string> histoNums_ve2;
	    histoNums_ve2.push_back("hnum_HTT_100");
	    histoNums_ve2.push_back("hnum_HTT_125");
	    histoNums_ve2.push_back("hnum_HTT_150");   
	    histoNums_ve2.push_back("hnum_HTT_175"); 
	    histoNums_ve2.push_back("hnum_HTT_200");
	    histoNums_ve2.push_back("hnum_HTT_250"); 
	    string histoDen_ve2 = "hden_HTT";
	    vector<string> histoEffs_ve2;
	    histoEffs_ve2.push_back("hEff_HTT_100");
	    histoEffs_ve2.push_back("hEff_HTT_125");
	    histoEffs_ve2.push_back("hEff_HTT_150");   
	    histoEffs_ve2.push_back("hEff_HTT_175"); 
	    histoEffs_ve2.push_back("hEff_HTT_200");
	    histoEffs_ve2.push_back("hEff_HTT_250"); 
		vector<string> legIconNames_ve2;
		legIconNames_ve2.push_back("HTT>100");
		legIconNames_ve2.push_back("HTT>125");
		legIconNames_ve2.push_back("HTT>150");
		legIconNames_ve2.push_back("HTT>175");
		legIconNames_ve2.push_back("HTT>200");
		legIconNames_ve2.push_back("HTT>250");
		plot_ve2.loadEfficiencies(path,histoNums_ve2,histoDen_ve2,histoEffs_ve2,histogramLineWidths_allSize2,
						     	   histogramLineColours_allDifferent,histogramLineStyles_allSolidLines,
						     	   widthVector_jetCentral,true);
		plot_ve2.insertLegend(legIconNames_ve2, 0.65, 0.85, 0.15, 0.35);
		plot_ve2.turnGridLinesOn();
		plot_ve2.plotAndSave(3, directoryName.c_str(), "HTT_EfficiencyTurnOns.pdf");


		rootPlotMaker plot_ve3;
	    vector<string> histoNums_ve3;
	    histoNums_ve3.push_back("hnum_MET_40");
	    histoNums_ve3.push_back("hnum_MET_60");
	    histoNums_ve3.push_back("hnum_MET_80");   
	    histoNums_ve3.push_back("hnum_MET_100"); 
	    string histoDen_ve3 = "hden_MET";
	    vector<string> histoEffs_ve3;
	    histoEffs_ve3.push_back("hEff_MET_40");
	    histoEffs_ve3.push_back("hEff_MET_60");
	    histoEffs_ve3.push_back("hEff_MET_80");   
	    histoEffs_ve3.push_back("hEff_MET_100"); 
		vector<string> legIconNames_ve3;
		legIconNames_ve3.push_back("MET>40");
		legIconNames_ve3.push_back("MET>60");
		legIconNames_ve3.push_back("MET>80");
		legIconNames_ve3.push_back("MET>100");
		plot_ve3.loadEfficiencies(path,histoNums_ve3,histoDen_ve3,histoEffs_ve3,histogramLineWidths_allSize2,
						     	   histogramLineColours_allDifferent,histogramLineStyles_allSolidLines,
						     	   widthVector_jetCentral,true);
		plot_ve3.insertLegend(legIconNames_ve3, 0.65, 0.85, 0.15, 0.35);
		plot_ve3.turnGridLinesOn();
		plot_ve3.plotAndSave(3, directoryName.c_str(), "MET_EfficiencyTurnOns.pdf");


		rootPlotMaker plot_ve4;
	    vector<string> histoNums_ve4;
	    histoNums_ve4.push_back("hnum_MHT_40");
	    histoNums_ve4.push_back("hnum_MHT_60");
	    histoNums_ve4.push_back("hnum_MHT_80");   
	    histoNums_ve4.push_back("hnum_MHT_100"); 
	    string histoDen_ve4 = "hden_MHT";
	    vector<string> histoEffs_ve4;
	    histoEffs_ve4.push_back("hEff_MHT_40");
	    histoEffs_ve4.push_back("hEff_MHT_60");
	    histoEffs_ve4.push_back("hEff_MHT_80");   
	    histoEffs_ve4.push_back("hEff_MHT_100"); 
		vector<string> legIconNames_ve4;
		legIconNames_ve4.push_back("MHT>40");
		legIconNames_ve4.push_back("MHT>60");
		legIconNames_ve4.push_back("MHT>80");
		legIconNames_ve4.push_back("MHT>100");
		plot_ve4.loadEfficiencies(path,histoNums_ve4,histoDen_ve4,histoEffs_ve4,histogramLineWidths_allSize2,
						     	   histogramLineColours_allDifferent,histogramLineStyles_allSolidLines,
						     	   widthVector_jetCentral,true);
		plot_ve4.insertLegend(legIconNames_ve4, 0.65, 0.85, 0.15, 0.35);
		plot_ve4.turnGridLinesOn();
		plot_ve4.plotAndSave(3, directoryName.c_str(), "MHT_EfficiencyTurnOns.pdf");


		rootPlotMaker plot_vx1;
		vector<string> histoNames_vx1;
		histoNames_vx1.push_back("hMETphi_reco");
		histoNames_vx1.push_back("hMETphi_l1");       
		vector<string> legIconNames_vx1;
		legIconNames_vx1.push_back("reco_metPhi");
		legIconNames_vx1.push_back("l1_metPhi");
		plot_vx1.loadHistogramsInfo(inputFilePath_allSame,histoNames_vx1,histogramLineWidths_allSize2,
									   histogramLineColours_allDifferent,histogramLineStyles_allSolidLines);
		plot_vx1.turnGridLinesOn();
		plot_vx1.insertLegend(legIconNames_vx1, 0.65, 0.85, 0.65, 0.85);
		plot_vx1.plotAndSave(1, directoryName.c_str(), "dist_metPhi.pdf");


		rootPlotMaker plot_vx2;
		vector<string> histoNames_vx2;
		histoNames_vx2.push_back("hMHTphi_reco");
		histoNames_vx2.push_back("hMHTphi_l1");       
		vector<string> legIconNames_vx2;
		legIconNames_vx2.push_back("reco_mhtPhi");
		legIconNames_vx2.push_back("l1_mhtPhi");
		plot_vx2.loadHistogramsInfo(inputFilePath_allSame,histoNames_vx2,histogramLineWidths_allSize2,
									   histogramLineColours_allDifferent,histogramLineStyles_allSolidLines);
		plot_vx2.turnGridLinesOn();
		plot_vx2.insertLegend(legIconNames_vx2, 0.65, 0.85, 0.65, 0.85);
		plot_vx2.plotAndSave(1, directoryName.c_str(), "dist_mhtPhi.pdf");


		rootPlotMaker plot_vx3;
		vector<string> histoNames_vx3;
		histoNames_vx3.push_back("hdPhi_MET");   
		plot_vx3.loadHistogramsInfo(inputFilePath_allSame,histoNames_vx3,histogramLineWidths_allSize2,
									   histogramLineColours_allDifferent,histogramLineStyles_allSolidLines);
		plot_vx3.turnGridLinesOn();
		plot_vx3.plotAndSave(1, directoryName.c_str(), "dPhi_met.pdf");


		rootPlotMaker plot_vx4;
		vector<string> histoNames_vx4;
		histoNames_vx4.push_back("hdPhi_MHT");    
		plot_vx4.loadHistogramsInfo(inputFilePath_allSame,histoNames_vx4,histogramLineWidths_allSize2,
									   histogramLineColours_allDifferent,histogramLineStyles_allSolidLines);
		plot_vx4.turnGridLinesOn();
		plot_vx4.plotAndSave(1, directoryName.c_str(), "dPhi_mht.pdf");


		rootPlotMaker plot_vx5;
		vector<string> histoNames_vx5;
		histoNames_vx5.push_back("hdET_ETT");     
		plot_vx5.loadHistogramsInfo(inputFilePath_allSame,histoNames_vx5,histogramLineWidths_allSize2,
									   histogramLineColours_allDifferent,histogramLineStyles_allSolidLines);
		plot_vx5.turnGridLinesOn();
		plot_vx5.plotAndSave(1, directoryName.c_str(), "dET_ETT.pdf");


		rootPlotMaker plot_vx6;
		vector<string> histoNames_vx6;
		histoNames_vx6.push_back("hdET_HTT");    
		plot_vx6.loadHistogramsInfo(inputFilePath_allSame,histoNames_vx6,histogramLineWidths_allSize2,
									   histogramLineColours_allDifferent,histogramLineStyles_allSolidLines);
		plot_vx6.turnGridLinesOn();
		plot_vx6.plotAndSave(1, directoryName.c_str(), "dET_HTT.pdf");


		rootPlotMaker plot_vx7;
		vector<string> histoNames_vx7;
		histoNames_vx7.push_back("hdET_MET");    
		plot_vx7.loadHistogramsInfo(inputFilePath_allSame,histoNames_vx7,histogramLineWidths_allSize2,
									   histogramLineColours_allDifferent,histogramLineStyles_allSolidLines);
		plot_vx7.turnGridLinesOn();
		plot_vx7.plotAndSave(1, directoryName.c_str(), "dET_MET.pdf");


		rootPlotMaker plot_vx8;
		vector<string> histoNames_vx8;
		histoNames_vx8.push_back("hdET_MHT");    
		plot_vx8.loadHistogramsInfo(inputFilePath_allSame,histoNames_vx8,histogramLineWidths_allSize2,
									   histogramLineColours_allDifferent,histogramLineStyles_allSolidLines);
		plot_vx8.turnGridLinesOn();
		plot_vx8.plotAndSave(1, directoryName.c_str(), "dET_MHT.pdf");


		rootPlotMaker plot_vxy1;
		plot_vxy1.loadHistogram2D(path.c_str(), "hETS_ETT");
		plot_vxy1.turnLogZon();
		plot_vxy1.plotAndSave(2, directoryName.c_str(), "energyScatter_ETT.pdf");


		rootPlotMaker plot_vxy2;    
		plot_vxy2.loadHistogram2D(path.c_str(), "hETS_HTT");
		plot_vxy2.turnLogZon();
		plot_vxy2.plotAndSave(2, directoryName.c_str(), "energyScatter_HTT.pdf");


		rootPlotMaker plot_vxy3;
		plot_vxy3.loadHistogram2D(path.c_str(), "hETS_MET");
		plot_vxy3.turnLogZon();
		plot_vxy3.plotAndSave(2, directoryName.c_str(), "energyScatter_MET.pdf");


		rootPlotMaker plot_vxy4;    
		plot_vxy4.loadHistogram2D(path.c_str(), "hETS_MHT");
		plot_vxy4.turnLogZon();
		plot_vxy4.plotAndSave(2, directoryName.c_str(), "energyScatter_MHT.pdf");
	} // closes 'if' plotSetType=="esums"

return;
} // close makePlots function

// FUNCTIONS FROM rootPlotMaker CLASS //
void rootPlotMaker::loadHistogramsInfo(vector<string> inputFilePathDummy,
						   vector<string> histogramNamesDummy,
						   vector<int> histogramLineWidthsDummy,
						   vector<int> histogramLineColoursDummy,
						   vector<int> histogramLineStylesDummy){

	for (unsigned int i=0; i<histogramNamesDummy.size(); i++){
		inputFileObjects.push_back(TFile::Open(inputFilePathDummy[i].c_str()));
		histogramObjects.push_back((TH1F*)inputFileObjects[i]->Get(histogramNamesDummy[i].c_str()));
		histogramObjects[i]->SetLineWidth(histogramLineWidthsDummy[i]);
		histogramObjects[i]->SetLineColor(histogramLineColoursDummy[i]);
		histogramObjects[i]->SetLineStyle(histogramLineStylesDummy[i]);
	}
	histogramObjects[0]->GetXaxis()->SetTitleOffset(1.2);
	histogramObjects[0]->GetYaxis()->SetTitleOffset(1.2);
	gStyle->SetOptStat(0);
	return;
}

void rootPlotMaker::loadHistogram2D(string inputFilename2D, string histogramName2D){
	
	inputFile2D = TFile::Open(inputFilename2D.c_str());
	histogram2D = (TH2F*)inputFile2D->Get(histogramName2D.c_str());
	histogram2D->GetXaxis()->SetTitleOffset(1.2);
	histogram2D->GetYaxis()->SetTitleOffset(1.2);
	return;
}

void rootPlotMaker::loadEfficiencies(string inputFilenameEffDummy, vector<string> histoNumeratorNames,
									   string histoDenominatorName, vector<string> histoEffNames, vector<int> histogramLineWidthsDummy,
						   			   vector<int> histogramLineColoursDummy, vector<int> histogramLineStylesDummy, vector<double> fitWidthsVector, bool fitOn){

	for (unsigned int i=0; i<histoNumeratorNames.size(); i++){

		inputFileEff = TFile::Open(inputFilenameEffDummy.c_str());
		numeratorObjects.push_back((TH1F*)inputFileEff->Get(histoNumeratorNames[i].c_str()));
		denominatorObject = (TH1F*)inputFileEff->Get(histoDenominatorName.c_str());
		histogramObjects.push_back((TH1F*)inputFileEff->Get(histoEffNames[i].c_str())); // re-use so we can use the same manipulations of the plot
		histogramObjects[i]->SetLineWidth(histogramLineWidthsDummy[i]);
		histogramObjects[i]->SetLineColor(histogramLineColoursDummy[i]);
		histogramObjects[i]->SetLineStyle(histogramLineStylesDummy[i]);		
		efficiencyObjects.push_back(TEfficiency(*numeratorObjects[i],*denominatorObject));
		efficiencyObjects[i].SetLineWidth(histogramLineWidthsDummy[i]);
		efficiencyObjects[i].SetLineColor(histogramLineColoursDummy[i]);
		efficiencyObjects[i].SetLineStyle(histogramLineStylesDummy[i]);
		// TODO: put this stuff in...
		// efficiencyObjects[i]->SetMarkerSize(histogramMarkerSizesDummy[i]);		
		// efficiencyObjects[i]->SetMarkerColor(histogramMarkerColoursDummy[i]);
		// efficiencyObjects[i]->SetMarkerStyle(histogramMarkerStylesDummy[i]);

		if (fitOn){
			//find initial parameter for the fit...
			double parameterCenter = histogramObjects[i]->GetBinCenter(histogramObjects[i]->GetNbinsX()-1);
			for (Int_t j=1; j<histogramObjects[i]->GetNbinsX(); j++){

				if (histogramObjects[i]->GetBinContent(j) > 0.50){
					parameterCenter = histogramObjects[i]->GetBinCenter(j);
					break;
				}
			}

			// cout << endl << endl << "centre param = "<< parameterCenter << endl;
			TF1* errFunc = new TF1("errFunc","[0]*0.5*(TMath::Erf((x-[1])/[2])+1)",0,histogramObjects[i]->GetXaxis()->GetXmax());
		    turnOnFits.push_back(errFunc);
		    turnOnFits[i]->SetParameters(1, parameterCenter, fitWidthsVector[i]);
		    turnOnFits[i]->SetParLimits(0,0,1);
		    turnOnFits[i]->SetLineColor(histogramLineColoursDummy[i]);
		    efficiencyObjects[i].Fit(turnOnFits[i]);
		    // histogramObjects[i]->Fit(turnOnFits[i]);

		    cout << "height fit: " << turnOnFits[i]->GetParameter(0);
		    cout << "centre fit: " << turnOnFits[i]->GetParameter(0);
		    cout << "width fit: " << turnOnFits[i]->GetParameter(0);		    		    
		}
	}
	histogramObjects[0]->GetXaxis()->SetTitleOffset(1.2);
	histogramObjects[0]->GetYaxis()->SetTitleOffset(1.2);
	gStyle->SetOptStat(0);
	return;
}
	
// plotType 1 = normal 1d; plotType 2 = 2d; plotType 3 = efficiencyPlot.	
void rootPlotMaker::plotAndSave(int plotType, string saveDirName, string savePlotName){

	if (plotType==1){
		for (unsigned int i=0; i<histogramObjects.size(); i++){
			histogramObjects[i]->Draw("same");
		}
	}

	if (plotType==2){
		histogram2D->Draw("cols, z");
	}

	if (plotType==3){
		for (unsigned int i=0; i<efficiencyObjects.size(); i++){	
			
			if (i==0) histogramObjects[i]->Draw("P");
			else histogramObjects[i]->Draw("same, P");
			efficiencyObjects[i].GetListOfFunctions()->AddFirst(turnOnFits[i]);	
			efficiencyObjects[i].Draw("same");
		}
	}

	// plots efficiencies w/o fit
	if (plotType==31){
		for (unsigned int i=0; i<efficiencyObjects.size(); i++){	
			
			if (i==0) histogramObjects[i]->Draw("P");
			else histogramObjects[i]->Draw("same, P");
			efficiencyObjects[i].Draw("same");
		}
	}

	//TODO: finish this off this ratio box
	if (plotType==11){
		TPad *pad1 = new TPad("pad1","pad1",0,0.2,1,1);
		pad1->SetBottomMargin(0.1);
		pad1->Draw();
		pad1->SetGrid();
		pad1->cd();
		gPad->SetLogy();
		for (unsigned int i=0; i<histogramObjects.size(); i++){	
			histogramObjects[i]->Draw("same");		
		}

		canvas->cd();
		TPad *pad2 = new TPad("pad2","pad2",0,0,1,0.2);
		pad2->SetTopMargin(0.05);
		pad2->Draw();
		pad2->SetGrid();
		pad2->cd();

	    vector<int> histogramLineColours_twosDifferent;  // different colours in sets of two
	    histogramLineColours_twosDifferent.push_back(kRed);
	    histogramLineColours_twosDifferent.push_back(kRed);
	    histogramLineColours_twosDifferent.push_back(kBlue+1);
	    histogramLineColours_twosDifferent.push_back(kBlue+1);
	    histogramLineColours_twosDifferent.push_back(kGreen+3);
	    histogramLineColours_twosDifferent.push_back(kGreen+3);
	    histogramLineColours_twosDifferent.push_back(kBlack);
	    histogramLineColours_twosDifferent.push_back(kBlack);

		for (unsigned int i=0; i<histogramObjects.size(); i=i+2){

			TH1F * hratio =(TH1F*)histogramObjects[i]->Clone();
			hratio->Divide(histogramObjects[i], histogramObjects[i+1]);
			hratio->GetYaxis()->SetRangeUser(0.5,1.5);
			hratio->SetMarkerStyle(21);
			hratio->SetMarkerSize(0.4);
			hratio->SetMarkerColor(histogramLineColours_twosDifferent[i]);
			hratio->GetXaxis()->SetTitle("");
			hratio->GetXaxis()->SetLabelSize(0);
			hratio->GetYaxis()->SetTitle("EMU/HW");
			hratio->GetYaxis()->SetTitleSize(0.13);
			hratio->GetYaxis()->SetTitleOffset(0.3);	
			hratio->GetYaxis()->SetLabelSize(0.1);
			hratio->Draw("p, same");
		}
		// pad1->cd();
		canvas->cd();
	}

	legend.Draw("same");
	additionalText.Draw("same");


	string saveName = saveDirName + savePlotName;
	canvas->SaveAs( saveName.c_str() );
	canvas->Close();
 	return;
}

// extension functions you can run (after loading and before plotting)...not complete, add as you need them
void rootPlotMaker::turnGridLinesOn(){canvas->SetGrid(); return;}
void rootPlotMaker::turnLogXon(){gPad->SetLogx(); return;}
void rootPlotMaker::turnLogYon(){gPad->SetLogy(); return;}
void rootPlotMaker::turnLogZon(){gPad->SetLogz(); return;}

void rootPlotMaker::setTitle(string title){
	histogramObjects[0]->SetTitle(title.c_str());
	return;}

void rootPlotMaker::setAxisTitles(string xaxisTitle, string yaxisTitle){
	histogramObjects[0]->GetXaxis()->SetTitle(xaxisTitle.c_str());
	histogramObjects[0]->GetYaxis()->SetTitle(yaxisTitle.c_str());		
	return;}

void rootPlotMaker::setAxisTitleOffset(double xaxisTitleOffset, double yaxisTitleOffset){
	histogramObjects[0]->GetXaxis()->SetTitleOffset(xaxisTitleOffset);
	histogramObjects[0]->GetYaxis()->SetTitleOffset(yaxisTitleOffset);
	return;}

void rootPlotMaker::setAxisTitleSize(double xaxisTitleSize, double yaxisTitleSize){
	histogramObjects[0]->GetXaxis()->SetTitleSize(xaxisTitleSize);
	histogramObjects[0]->GetYaxis()->SetTitleSize(yaxisTitleSize);
	return;}

void rootPlotMaker::setXaxisRange(double xaxisMin, double xaxisMax){
	histogramObjects[0]->GetXaxis()->SetRangeUser(xaxisMin, xaxisMax);
	return;}

void rootPlotMaker::setYaxisRange(double yaxisMin, double yaxisMax){
	histogramObjects[0]->GetYaxis()->SetRangeUser(yaxisMin, yaxisMax);
	return;}

void rootPlotMaker::setXaxisLimits(double xaxisMin, double xaxisMax){
	histogramObjects[0]->GetXaxis()->SetLimits(xaxisMin, xaxisMax);
	return;}

void rootPlotMaker::setYaxisLimits(double yaxisMin, double yaxisMax){
	histogramObjects[0]->GetYaxis()->SetLimits(yaxisMin, yaxisMax);
	return;}


void rootPlotMaker::setCanvasSize(double width, double height){
	canvas->SetCanvasSize(width,height);
	return;}

void rootPlotMaker::insertLegend(vector<string> legendIconNames, double xmin, 
								  double xmax, double ymin, double ymax){

	for (unsigned int i=0; i<histogramObjects.size(); i++){
		legend.AddEntry(histogramObjects[i], legendIconNames[i].c_str(), "L");
	}
	legend.SetLineColor(0);
	legend.SetX1(xmin);
	legend.SetX2(xmax);
	legend.SetY1(ymin);	
	legend.SetY2(ymax);
	return;
}

void rootPlotMaker::insertAdditionalText(string additionalTextString){

	additionalText.SetTitle(additionalTextString.c_str());
	additionalText.SetTextSize(0.035);
	return;
}

void rootPlotMaker::setAdditionalTextLocation(double textStartXPos, double textStartYPos){

	additionalText.SetX(textStartXPos);
	additionalText.SetY(textStartYPos);
	return;
}

//nb: might not work if you change the x and y ranges...
void rootPlotMaker::autoSetAdditionalTextLocation(bool isLogyOn){

	additionalText.SetX(histogramObjects[0]->GetXaxis()->GetBinCenter(1));
	double y;
	if (isLogyOn) y = 3*(histogramObjects[0]->GetMaximum());
	else y = 1.1*(histogramObjects[0]->GetMaximum());
	additionalText.SetY(y);
	return;
}

void rootPlotMaker::setAdditionalTextSize(double additionalTextSize){

	additionalText.SetTextSize(additionalTextSize);
	return;
}
