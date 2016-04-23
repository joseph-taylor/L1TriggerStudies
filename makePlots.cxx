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

//TODO: insert error message explanations/terminations to avoid seg faults

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
    vector<TH1F*> denominatorObjects;    	
	TCanvas * canvas = new TCanvas("canvas", "", 650, 600);
	TLegend legend;
	TLatex additionalText;
public:
//public class members: can be individually accessed from outside the class
	void loadHistogramsInfo(vector<string>,vector<string>,vector<int>,vector<int>,vector<int>);
	void loadHistogram2D(string,string);
	void loadEfficiencies(string,vector<string>,vector<string>,vector<string>,vector<int>,vector<int>,vector<int>);
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
	void setCanvasSize(double,double);
	void insertLegend(vector<string>,double,double,double,double);
	void insertAdditionalText(string);
	void setAdditionalTextLocation(double,double);
	void autoSetAdditionalTextLocation(bool);
	void setAdditionalTextSize(double);
};// end of class definition

void makePlots(){

	// set unique parameters
	// set up to primary operate on a single root file
	string directoryName = "output_jets/run269224_zeroBias_v34p0/"; //also the directory where we save final plots
	string secondFileDirectoryName = "";

	string inputFileName = "histos.root"; // set up analysis macros to name output this
	string secondInputFileName = "histos.root";
	string path = directoryName + inputFileName;
	string path2 = secondFileDirectoryName + secondInputFileName;

	//create standard input objects (at the moment operating on eight seperate lines)
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
    histogramLineColours_allDifferent.push_back(kOrange+10);
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


	// create rootPlotMaker classes and use to make plots
	// to make a new 1d one, copy and paste a _vx1 type then change the key
	// to make a new 2d one, copy and paste a _vxy1 type then change the key
	// to make a new eff one, copy and paste a _ve1 type then change the key
	// key parameters to change:
	// histogram names, legend names & position (if legend desired), pdf file name


	// rootPlotMaker plot_vx1;
	// vector<string> histoNames_vx1;
	// histoNames_vx1.push_back("etSumDist_emu");
	// histoNames_vx1.push_back("etSumDist_hw");
	// histoNames_vx1.push_back("htSumDist_emu");   
	// histoNames_vx1.push_back("htSumDist_hw");     
	// vector<string> legIconNames_vx1;
	// legIconNames_vx1.push_back("et_emu");
	// legIconNames_vx1.push_back("et_hw");
	// legIconNames_vx1.push_back("ht_emu");
	// legIconNames_vx1.push_back("ht_hw");
	// plot_vx1.loadHistogramsInfo(inputFilePath_allSame,histoNames_vx1,histogramLineWidths_allSize2,
	// 				   histogramLineColours_allDifferent,histogramLineStyles_allSolidLines);
	// plot_vx1.insertLegend(legIconNames_vx1, 0.65, 0.85, 0.65, 0.85);
	// plot_vx1.plotAndSave(1, directoryName.c_str(), "et_ht_emuHw_dist.pdf");

	// rootPlotMaker plot_vx2;
	// vector<string> histoNames_vx2;
	// histoNames_vx2.push_back("etSumDist_emu");
	// histoNames_vx2.push_back("etSumDist_hw");
	// histoNames_vx2.push_back("htSumDist_emu");   
	// histoNames_vx2.push_back("htSumDist_hw");     
	// vector<string> legIconNames_vx2;
	// legIconNames_vx2.push_back("et_emu");
	// legIconNames_vx2.push_back("et_hw");
	// legIconNames_vx2.push_back("ht_emu");
	// legIconNames_vx2.push_back("ht_hw");
	// plot_vx2.loadHistogramsInfo(inputFilePath_allSame,histoNames_vx2,histogramLineWidths_allSize2,
	// 				   histogramLineColours_allDifferent,histogramLineStyles_allSolidLines);
	// plot_vx2.insertLegend(legIconNames_vx2, 0.65, 0.85, 0.65, 0.85);
	// plot_vx2.plotAndSave(1, directoryName.c_str(), "et_ht_emuHw_dist.pdf");



	rootPlotMaker plot_ve1;
    vector<string> histoNums_ve1;
    histoNums_ve1.push_back("hnum36_central");
    histoNums_ve1.push_back("hnum52_central");
    histoNums_ve1.push_back("hnum68_central");   
    histoNums_ve1.push_back("hnum92_central"); 
    histoNums_ve1.push_back("hnum128_central"); 
    vector<string> histoDens_ve1;
    histoDens_ve1.push_back("hden_central");
    histoDens_ve1.push_back("hden_central");
    histoDens_ve1.push_back("hden_central");   
    histoDens_ve1.push_back("hden_central"); 
    histoDens_ve1.push_back("hden_central"); 
    vector<string> histoEffs_ve1;
    histoEffs_ve1.push_back("hT36_central");
    histoEffs_ve1.push_back("hT52_central");
    histoEffs_ve1.push_back("hT68_central");   
    histoEffs_ve1.push_back("hT92_central"); 
    histoEffs_ve1.push_back("hT128_central"); 
	vector<string> legIconNames_ve1;
	legIconNames_ve1.push_back("36");
	legIconNames_ve1.push_back("52");
	legIconNames_ve1.push_back("68");
	legIconNames_ve1.push_back("92");
	legIconNames_ve1.push_back("128");
	plot_ve1.loadEfficiencies(path,histoNums_ve1,histoDens_ve1,histoEffs_ve1,histogramLineWidths_allSize2,
					     	   histogramLineColours_allDifferent,histogramLineStyles_allSolidLines);
	plot_ve1.insertLegend(legIconNames_ve1, 0.65, 0.85, 0.65, 0.85);
	plot_ve1.plotAndSave(3, directoryName.c_str(), "turnOnTrial.pdf");

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
									   vector<string> histoDenominatorNames, vector<string> histoEffNames, vector<int> histogramLineWidthsDummy,
						   			   vector<int> histogramLineColoursDummy, vector<int> histogramLineStylesDummy){

	for (unsigned int i=0; i<histoNumeratorNames.size(); i++){

		inputFileEff = TFile::Open(inputFilenameEffDummy.c_str());

		numeratorObjects.push_back((TH1F*)inputFileEff->Get(histoNumeratorNames[i].c_str()));
		denominatorObjects.push_back((TH1F*)inputFileEff->Get(histoDenominatorNames[i].c_str()));

		histogramObjects.push_back((TH1F*)inputFileEff->Get(histoEffNames[i].c_str())); // re-use so we can use the same manipulations of the plot
		histogramObjects[i]->SetLineWidth(histogramLineWidthsDummy[i]);
		histogramObjects[i]->SetLineColor(histogramLineColoursDummy[i]);
		histogramObjects[i]->SetLineStyle(histogramLineStylesDummy[i]);		

		efficiencyObjects.push_back(TEfficiency(*numeratorObjects[i],*denominatorObjects[i]));
		efficiencyObjects[i].SetLineWidth(histogramLineWidthsDummy[i]);
		efficiencyObjects[i].SetLineColor(histogramLineColoursDummy[i]);
		efficiencyObjects[i].SetLineStyle(histogramLineStylesDummy[i]);

		// TODO: put this stuff in...
		// efficiencyObjects[i]->SetMarkerSize(histogramMarkerSizesDummy[i]);		
		// efficiencyObjects[i]->SetMarkerColor(histogramMarkerColoursDummy[i]);
		// efficiencyObjects[i]->SetMarkerStyle(histogramMarkerStylesDummy[i]);

		// TODO: tune the input parameters better by investigating pre-fit
		// TODO: fit to a user defined range using ~efficiencyObjects[i].Fit(turnOnFits[i], "R");	
		TF1* errFunc = new TF1("errFunc","[0]*0.5*(TMath::Erf((x-[1])/[2])+1)",0,histogramObjects[i]->GetXaxis()->GetXmax());
	    turnOnFits.push_back(errFunc);
	    turnOnFits[i]->SetParameters(1.00, 40, 10);
	    turnOnFits[i]->SetLineColor(histogramLineColoursDummy[i]);
	    efficiencyObjects[i].Fit(turnOnFits[i], "R");
	    // histogramObjects[i]->Fit(turnOnFits[i]);
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