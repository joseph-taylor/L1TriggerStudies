#include "TFile.h"
#include "TH1F.h"
#include "TStyle.h"
#include "TLegend.h"
#include <TCanvas.h>
#include <TLatex.h>
#include <string>
#include <iostream>



class rootPlotMaker{

//private class members: only accessible from within other members of this class

public:
//public class members: can be individually accessed from outside the class



	//got to be careful i think...public variabels nd two instanc

	// would only really have a single 2d plot right??

	vector<TFile*> inputFileObjects;

	//default canvas with stats off
	TCanvas * canvas = new TCanvas("canvas", "", 650, 600);
	gStyle->SetOptStat(0);
	
	TLegend legend;
	TLatex additionalText;
	//multiple 1d plots
	vector<TH1F*> histogramObjects;

	//single 2d histos...

	//we might want our initial objects to be private...think this through later




	//loads up the histograms (includes setting the x and y axis)
	void loadHistogramsInfo(vector<string> inputFilePathDummy,
							   vector<string> histogramNamesDummy,
							   vector<int> histogramLineWidthsDummy,
							   vector<int> histogramLineColoursDummy,
							   vector<int> histogramLineStylesDummy,
							   string xaxisTitleDummy,
							   string yaxisTitleDummy){

		for (unsigned int i=0; i<histogramNamesDummy.size(); i++){

			inputFileObjects.push_back(TFile::Open(inputFilePathDummy[i].c_str()));
			histogramObjects.push_back((TH1F*)inputFileObjects[i]->Get(histogramNamesDummy[i].c_str()));
			histogramObjects[i]->SetLineWidth(histogramLineWidthsDummy[i]);
			histogramObjects[i]->SetLineColor(histogramLineColoursDummy[i]);
			histogramObjects[i]->SetLineStyle(histogramLineStylesDummy[i]);
		}

		//want to auto set xtitle offsets to be 1.2 here
		return;
	}









	void loadHistogram2D(){

	}



	void loadEfficiencies(){


		/*
	pass it a vector of numerators
	pass it a vector of denominators
	create a vector of Teffs
	create a vector?? of fits
		*/

	}



	// extension functions you can run...
	// after you load the histograms
	// before you create the outputs
	// (not complete, add as you go from now)
	void turnGridLinesOn(){canvas->SetGrid(); return;}
	void turnLogXon(){gPad->SetLogx(); return;}
	void turnLogYon(){gPad->SetLogy(); return;}
	void turnLogZon(){gPad->SetLogz(); return;}
	
	void setTitle(string titleDummy){
		histogramObjects[0]->SetTitle(titleDummy.c_str());
		return;}

	void setAxisTitles(string xaxisTitleDummy, string yaxisTitleDummy){
		histogramObjects[0]->GetXaxis()->SetTitle(xaxisTitleDummy.c_str());
		histogramObjects[0]->GetYaxis()->SetTitle(yaxisTitleDummy.c_str());		
		return;}

	void setAxisTitleOffset(double xaxisTitleOffsetDummy, double yaxisTitleOffsetDummy){
		histogramObjects[0]->GetXaxis()->SetTitleOffset(xaxisTitleOffsetDummy);
		histogramObjects[0]->GetYaxis()->SetTitleOffset(yaxisTitleOffsetDummy);
		return;}

	void setAxisTitleSize(double xaxisTitleSizeDummy, double yaxisTitleSizeDummy){
		histogramObjects[0]->GetXaxis()->SetTitleSize(xaxisTitleSizeDummy);
		histogramObjects[0]->GetYaxis()->SetTitleSize(yaxisTitleSizeDummy);
		return;}

	void turnZScaleOn(){}//to do with how you plot...need to include a 'z'

	void setXaxisRange(double xaxisMinDummy, double xaxisMaxDummy){
		histogramObjects[0]->GetXaxis()->SetRangeUser(xaxisMinDummy, xaxisMaxDummy);
		return;}

	void setYaxisRange(double yaxisMinDummy, double yaxisMaxDummy){
		histogramObjects[0]->GetYaxis()->SetRangeUser(yaxisMinDummy, yaxisMaxDummy);
		return;}

	void setCanvasSize(double widthDummy, double heightDummy){
		c->SetCanvasSize(widthDummy,heightDummy);
		return;}


	void insertLegend(vector<string> legendIconNamesDummy, double xmin, 
					  double xmax, double ymin, double ymax){

		for (unsigned int i=0; i<histogramNamesDummy.size(); i++){
			legend.AddEntry(histogramObjects[i], legendIconNamesDummy[i].c_str(), "L");
		}
		legend.SetLineColor(0);
		legend.SetX1(xmin);
		legend.SetX2(xmax);
		legend.SetY1(ymin);	
		legend.SetY2(ymax);
		return;
	}



	void insertAdditionalText(string additionalTextString){

		additionalText.SetTitle(additionalTextString.c_str());
		additionalText.SetTextSize(0.035);
		return;
	}

	void setAdditionalTextLocation(double textStartXPos, double textStartYPos){

		additionalText.SetX(textStartXPos);
		additionalText.SetY(textStartYPos);
		return;
	}

	//nb: might not work if you change the x and y ranges...
	void autoSetAdditionalTextLocation(bool isLogyOn){

		additionalText.SetX(histogramObjects[0]->GetXaxis()->GetBinCenter(1));
		double y;
    	if (isLogyOn) y = 3*(histogramObjects[0]->GetMaximum());
    	else y = 1.1*(histogramObjects[0]->GetMaximum());
		additionalText.SetY(y);
		return;
	}

	void setAdditionalTextSize(double additionalTextSize){

		additionalText.SetTextSize(additionalTextSize);
		return;
	}












//need to work on this...leg, canvas, textextra, histograms...
	void plotAndSave(){

		for (unsigned int i=0; i<histogramObjects.size(); i++){

			histogramObjects[i]->Draw("same");

		}
	}







};







void makePlots(){

	rootPlotMaker trialPlot1;


//pick 1d, 2d or teff style thingy ma bob

    vector<string> histogramNames;
    histogramNames.push_back("mhtSumDist_emu");
    histogramNames.push_back("htSumDist_hw");
    histogramNames.push_back("metSumDist_hw");    

    vector<int> histogramLineWidths;
    histogramLineWidths.push_back(2);
    histogramLineWidths.push_back(2);
    histogramLineWidths.push_back(2);

    vector<int> histogramLineColours;
    histogramLineColours.push_back(kRed);
    histogramLineColours.push_back(kBlue);
    histogramLineColours.push_back(kGreen);

    vector<int> histogramLineStyles;
    histogramLineStyles.push_back(1);
    histogramLineStyles.push_back(7);
    histogramLineStyles.push_back(3);

	vector<string> inputFilePath;
	//all histograms from the same file
	inputFilePath.assign(histogramNames.size(), "histos.root");
	//if you need to load histograms from different files
	//inputFilePath.push_back("histos1.root");
	//inputFilePath.push_back("histos2.root");
	//etc.

	trialPlot1.loadHistogramsInfo(inputFilePath,histogramNames,histogramLineWidths,histogramLineColours,histogramLineStyles);


	vector<string> legendIconNames;
	legendIconNames.push_back("a");
	legendIconNames.push_back("b");
	legendIconNames.push_back("c");
	legendIconNames.push_back("a");

	//now can insert additional options...




	trialPlot1.plotAndSave();
 

//need to do canvas stuff also at some point


return;
}