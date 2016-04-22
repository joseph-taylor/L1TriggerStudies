#include "TFile.h"
#include "TH1F.h"
#include "TStyle.h"
#include "TLegend.h"
#include <TCanvas.h>
#include <TLatex.h>
#include <string>
#include <iostream>


//todo: put this into a plotting class?




void individual_plot(string dirName,string outputFileName,string xaxisName,string yaxisName,
					 bool setOwnRange,double xStartPoint,double xFinishPoint,bool logOn,
					 bool legendOn,double legXmin,double legYmin,double legXmax,double legYmax,
					 int numberOfHistos,string histoName1,string legName1,int histoStyle1,
					 int histoColour1,string histoName2,string legName2,int histoStyle2,
					 int histoColour2,string histoName3,string legName3,int histoStyle3,
					 int histoColour3,string histoName4,string legName4,int histoStyle4,
					 int histoColour4,string histoName5,string legName5,int histoStyle5,
					 int histoColour5,string histoName6,string legName6,int histoStyle6,
					 int histoColour6,bool additionalTextOn,string additionalText,bool autoPosition,
					 double textStartXPos,double textStartYPos);




void plot_rates(){

	string dirName = "output_rates/run269224_zeroBias_v34p0/";
	string additionalText = "CMS Preliminary, #sqrt{s}=13 TeV, ZeroBias run259721";
//emu and hw
//Rates



	//singleDoubleTripleJetsRates
	individual_plot(dirName.c_str(),								     //dirName
					"singleDoubleJetRates",								 //outputFileName
					"L1 Jet E_{T} Threshold (GeV)",						 //xaxisName
					"Rate (Hz)",										 //yaxisName
					false,0,0,											 //setOwnRange,xStartPoint,yStartPoint

					true,												 //logOn
					true, 0.60, 0.60, 0.85, 0.85,						 //legendOn: legend coords (xmin, ymin, xmax, ymax)

					6,													 //number of histos (currently four is the maximum)

					"singleJetRates_emu",								 //histoName1
					"singleJet_emu",									 //legNam1
					1,													 //histoStyle1 (1=nondotted, 7=dotted)
					2,													 //histoColour1

					"singleJetRates_hw",								 //histo2
					"singleJet_hw",
					7,
					2,

					"doubleJetRates_emu",                         		 //histo3
					"doubleJet_emu",
					1,
					4,

					"doubleJetRates_hw",                         		 //histo4
					"doubleJet_hw",
					7,
					4,


					"tripleJetRates_emu",                         		 //histo3
					"tripleJet_emu",
					1,
					1,

					"tripleJetRates_hw",                         		 //histo4
					"tripleJet_hw",
					7,
					1,





					true,                                                    //additionalTextOn
					additionalText.c_str(),  //the additional text
					false, 10, 2*pow(10,8)								 //autoPosition?, textStartXpos, textStartYpos
					);












// 	//singleDoubleJetsRates
// 	individual_plot(dirName.c_str(),								     //dirName
// 					"singleDoubleJetRates",								 //outputFileName
// 					"L1 Jet E_{T} Threshold (GeV)",						 //xaxisName
// 					"Rate (Hz)",										 //yaxisName
// 					false,0,0,											 //setOwnRange,xStartPoint,yStartPoint

// 					true,												 //logOn
// 					true, 0.60, 0.60, 0.85, 0.85,						 //legendOn: legend coords (xmin, ymin, xmax, ymax)

// 					4,													 //number of histos (currently four is the maximum)

// 					"singleJetRates_emu",								 //histoName1
// 					"singleJet_emu",									 //legNam1
// 					1,													 //histoStyle1 (1=nondotted, 7=dotted)
// 					2,													 //histoColour1

// 					"singleJetRates_hw",								 //histo2
// 					"singleJet_hw",
// 					7,
// 					2,

// 					"doubleJetRates_emu",                         		 //histo3
// 					"doubleJet_emu",
// 					1,
// 					4,

// 					"doubleJetRates_hw",                         		 //histo4
// 					"doubleJet_hw",
// 					7,
// 					4,

// 					true,                                                    //additionalTextOn
// 					additionalText.c_str(),  //the additional text
// 					false, 10, 1.5*pow(10,8)								 //autoPosition?, textStartXpos, textStartYpos
// 					);


// 	//singleDoubleEGsRates
// 	individual_plot(dirName.c_str(),"singleDoubleEGRates","L1 EG E_{T} Threshold (GeV)","Rate (Hz)",true,0,200,
// 					true,true, 0.60, 0.60, 0.85, 0.85,4,"singleEgRates_emu","singleEg_emu",1,2,"singleEgRates_hw",
// 					"singleEg_hw",7,2,"doubleEgRates_emu","doubleEg_emu",1,4,"doubleEgRates_hw","doubleEg_hw",7,4,
// 					true,additionalText.c_str(),false,10,1.5*pow(10,8));


// 	//ett htt Rates
// 	individual_plot(dirName.c_str(),								     //dirName
// 					"ett_htt_Rates",    								 //outputFileName
// 					"L1 Sum E_{T} Threshold (GeV)",						 //xaxisName
// 					"Rate (Hz)",										 //yaxisName
// 					false,0,0,											 //setOwnRange,xStartPoint,yStartPoint

// 					true,												 //logOn
// 					true, 0.60, 0.60, 0.85, 0.85,						 //legendOn: legend coords (xmin, ymin, xmax, ymax)

// 					4,													 //number of histos (currently four is the maximum)

// 					"etSumRates_emu",								 //histoName1
// 					"ETT_emu",									 //legNam1
// 					1,													 //histoStyle1 (1=nondotted, 7=dotted)
// 					2,													 //histoColour1

// 					"etSumRates_hw",								 //histo2
// 					"ETT_hw",
// 					7,
// 					2,

// 					"htSumRates_emu",                         		 //histo3
// 					"HTT_emu",
// 					1,
// 					4,

// 					"htSumRates_hw",                         		 //histo4
// 					"HTT_hw",
// 					7,
// 					4,

// 					true,                                                    //additionalTextOn
// 					additionalText.c_str(),  //the additional text
// 					false, 10, 1.5*pow(10,8)								 //autoPosition?, textStartXpos, textStartYpos
// 					);



// 	//met mht Rates
// 	individual_plot(dirName.c_str(),								     //dirName
// 					"met_mht_Rates",    								 //outputFileName
// 					"L1 Sum E_{T} Threshold (GeV)",						 //xaxisName
// 					"Rate (Hz)",										 //yaxisName
// 					false,0,0,											 //setOwnRange,xStartPoint,yStartPoint

// 					true,												 //logOn
// 					true, 0.60, 0.60, 0.85, 0.85,						 //legendOn: legend coords (xmin, ymin, xmax, ymax)

// 					4,													 //number of histos (currently four is the maximum)

// 					"metSumRates_emu",								 //histoName1
// 					"MET_emu",									 //legNam1
// 					1,													 //histoStyle1 (1=nondotted, 7=dotted)
// 					2,													 //histoColour1

// 					"metSumRates_hw",								 //histo2
// 					"MET_hw",
// 					7,
// 					2,

// 					"mhtSumRates_emu",                         		 //histo3
// 					"MHT_emu",
// 					1,
// 					4,

// 					"mhtSumRates_hw",                         		 //histo4
// 					"MHT_hw",
// 					7,
// 					4,

// 					true,                                                    //additionalTextOn
// 					additionalText.c_str(),  //the additional text
// 					false, 10, 1.5*pow(10,8)								 //autoPosition?, textStartXpos, textStartYpos
// 					);



// 	//TAU Rates
// 	individual_plot(dirName.c_str(),								     //dirName
// 					"tau_Rates",    								 //outputFileName
// 					"L1 Tau E_{T} Threshold (GeV)",						 //xaxisName
// 					"Rate (Hz)",										 //yaxisName
// 					true,0,150,											 //setOwnRange,xStartPoint,yStartPoint

// 					true,												 //logOn
// 					true, 0.60, 0.60, 0.85, 0.85,						 //legendOn: legend coords (xmin, ymin, xmax, ymax)

// 					2,													 //number of histos (currently four is the maximum)

// 					"tauRates_emu",								 //histoName1
// 					"singleTau_emu",									 //legNam1
// 					1,													 //histoStyle1 (1=nondotted, 7=dotted)
// 					2,													 //histoColour1

// 					"tauRates_hw",								 //histo2
// 					"singleTau_hw",
// 					7,
// 					2,

// 					"",                         		 //histo3
// 					"",
// 					0,
// 					0,

// 					"",                         		 //histo4
// 					"",
// 					0,
// 					0,

// 					true,                                                    //additionalTextOn
// 					additionalText.c_str(),  //the additional text
// 					false, 10, 1.5*pow(10,8)								 //autoPosition?, textStartXpos, textStartYpos
// 					);



// //Distributions

// 	//singleDoubleJetsDists
// 	individual_plot(dirName.c_str(),								     //dirName
// 					"singleDoubleJetDist",								 //outputFileName
// 					"L1 Jet E_{T} (GeV)",						 //xaxisName
// 					"",										 //yaxisName
// 					false,0,0,											 //setOwnRange,xStartPoint,yStartPoint

// 					true,												 //logOn
// 					true, 0.60, 0.60, 0.85, 0.85,						 //legendOn: legend coords (xmin, ymin, xmax, ymax)

// 					4,													 //number of histos (currently four is the maximum)

// 					"leadingJetDist_emu",								 //histoName1
// 					"leadingJet_emu",									 //legNam1
// 					1,													 //histoStyle1 (1=nondotted, 7=dotted)
// 					2,													 //histoColour1

// 					"leadingJetDist_hw",								 //histo2
// 					"leadingJet_hw",
// 					7,
// 					2,

// 					"secondJetDist_emu",                         		 //histo3
// 					"secondJet_emu",
// 					1,
// 					4,

// 					"secondJetDist_hw",                         		 //histo4
// 					"secondJet_hw",
// 					7,
// 					4,

// 					true,                                                    //additionalTextOn
// 					additionalText.c_str(),  //the additional text
// 					true, 10, 200										 //autoPosition?, textStartXpos, textStartYpos
// 					);


// 	//singleDoubleEGsDist
// 	individual_plot(dirName.c_str(),								     //dirName
// 					"singleDoubleEGDist",								 //outputFileName
// 					"L1 EG E_{T} (GeV)",						 //xaxisName
// 					"",										 //yaxisName
// 					true,0,200,											 //setOwnRange,xStartPoint,yStartPoint

// 					true,												 //logOn
// 					true, 0.60, 0.60, 0.85, 0.85,						 //legendOn: legend coords (xmin, ymin, xmax, ymax)

// 					4,													 //number of histos (currently four is the maximum)

// 					"leadingEgDist_emu",								 //histoName1
// 					"leadingEg_emu",									 //legNam1
// 					1,													 //histoStyle1 (1=nondotted, 7=dotted)
// 					2,													 //histoColour1

// 					"leadingEgDist_hw",								 //histo2
// 					"leadingEg_hw",
// 					7,
// 					2,

// 					"secondEgDist_emu",                         		 //histo3
// 					"secondEg_emu",
// 					1,
// 					4,

// 					"secondEgDist_hw",                         		 //histo4
// 					"secondEg_hw",
// 					7,
// 					4,

// 					true,                                                    //additionalTextOn
// 					additionalText.c_str(),  //the additional text
// 					true, 10, 200										 //autoPosition?, textStartXpos, textStartYpos
// 					);


// 	//ett htt Dist
// 	individual_plot(dirName.c_str(),								     //dirName
// 					"ett_htt_Dist",    								 //outputFileName
// 					"L1 Sum E_{T} (GeV)",						 //xaxisName
// 					"",										 //yaxisName
// 					false,0,0,											 //setOwnRange,xStartPoint,yStartPoint

// 					true,												 //logOn
// 					true, 0.60, 0.60, 0.85, 0.85,						 //legendOn: legend coords (xmin, ymin, xmax, ymax)

// 					4,													 //number of histos (currently four is the maximum)

// 					"etSumDist_emu",								 //histoName1
// 					"ETT_emu",									 //legNam1
// 					1,													 //histoStyle1 (1=nondotted, 7=dotted)
// 					2,													 //histoColour1

// 					"etSumDist_hw",								 //histo2
// 					"ETT_hw",
// 					7,
// 					2,

// 					"htSumDist_emu",                         		 //histo3
// 					"HTT_emu",
// 					1,
// 					4,

// 					"htSumDist_hw",                         		 //histo4
// 					"HTT_hw",
// 					7,
// 					4,

// 					true,                                                    //additionalTextOn
// 					additionalText.c_str(),  //the additional text
// 					true, 10, 200										 //autoPosition?, textStartXpos, textStartYpos
// 					);



// 	//met mht Dist
// 	individual_plot(dirName.c_str(),								     //dirName
// 					"met_mht_Dist",    								 //outputFileName
// 					"L1 Sum E_{T} (GeV)",						 //xaxisName
// 					"",										 //yaxisName
// 					false,0,0,											 //setOwnRange,xStartPoint,yStartPoint

// 					true,												 //logOn
// 					true, 0.60, 0.60, 0.85, 0.85,						 //legendOn: legend coords (xmin, ymin, xmax, ymax)

// 					4,													 //number of histos (currently four is the maximum)

// 					"metSumDist_emu",								 //histoName1
// 					"MET_emu",									 //legNam1
// 					1,													 //histoStyle1 (1=nondotted, 7=dotted)
// 					2,													 //histoColour1

// 					"metSumDist_hw",								 //histo2
// 					"MET_hw",
// 					7,
// 					2,

// 					"mhtSumDist_emu",                         		 //histo3
// 					"MHT_emu",
// 					1,
// 					4,

// 					"mhtSumDist_hw",                         		 //histo4
// 					"MHT_hw",
// 					7,
// 					4,

// 					true,                                                    //additionalTextOn
// 					additionalText.c_str(),  //the additional text
// 					true, 10, 200									 //autoPosition?, textStartXpos, textStartYpos
// 					);



// 	//TAU Dist
// 	individual_plot(dirName.c_str(),								     //dirName
// 					"tau_Dist",    								 //outputFileName
// 					"L1 Tau E_{T} (GeV)",						 //xaxisName
// 					"",										 //yaxisName
// 					true,0,150,											 //setOwnRange,xStartPoint,yStartPoint

// 					true,												 //logOn
// 					true, 0.60, 0.60, 0.85, 0.85,						 //legendOn: legend coords (xmin, ymin, xmax, ymax)

// 					2,													 //number of histos (currently four is the maximum)

// 					"leadingTauDist_emu",								 //histoName1
// 					"leadingTau_emu",									 //legNam1
// 					1,													 //histoStyle1 (1=nondotted, 7=dotted)
// 					2,													 //histoColour1

// 					"leadingTauDist_hw",								 //histo2
// 					"leadingTau_hw",
// 					7,
// 					2,

// 					"",                         		 //histo3
// 					"",
// 					0,
// 					0,

// 					"",                         		 //histo4
// 					"",
// 					0,
// 					0,

// 					true,                                                    //additionalTextOn
// 					additionalText.c_str(),  //the additional text
// 					true, 10, 200										 //autoPosition?, textStartXpos, textStartYpos
// 					);






// //emu only
// //Rates
// 	//singleDoubleJetsRates
// 	individual_plot(dirName.c_str(),								     //dirName
// 					"singleDoubleJetRates",								 //outputFileName
// 					"L1 Jet E_{T} Threshold (GeV)",						 //xaxisName
// 					"Rate (Hz)",										 //yaxisName
// 					false,0,0,											 //setOwnRange,xStartPoint,yStartPoint

// 					true,												 //logOn
// 					true, 0.60, 0.60, 0.85, 0.85,						 //legendOn: legend coords (xmin, ymin, xmax, ymax)

// 					2,													 //number of histos (currently four is the maximum)

// 					"singleJetRates_emu",								 //histoName1
// 					"singleJet_emu",									 //legNam1
// 					1,													 //histoStyle1 (1=nondotted, 7=dotted)
// 					2,													 //histoColour1



// 					"doubleJetRates_emu",                         		 //histo3
// 					"doubleJet_emu",
// 					1,
// 					4,


// 					"singleJetRates_hw",								 //histo2
// 					"singleJet_hw",
// 					7,
// 					2,
// 					"doubleJetRates_hw",                         		 //histo4
// 					"doubleJet_hw",
// 					7,
// 					4,

// 					true,                                                    //additionalTextOn
// 					additionalText.c_str(),  //the additional text
// 					false, 10, 1.5*pow(10,8)								 //autoPosition?, textStartXpos, textStartYpos
// 					);


// 	//singleDoubleEGsRates
// 	individual_plot(dirName.c_str(),								     //dirName
// 					"singleDoubleEGRates",								 //outputFileName
// 					"L1 EG E_{T} Threshold (GeV)",						 //xaxisName
// 					"Rate (Hz)",										 //yaxisName
// 					true,0,200,											 //setOwnRange,xStartPoint,yStartPoint

// 					true,												 //logOn
// 					true, 0.60, 0.60, 0.85, 0.85,						 //legendOn: legend coords (xmin, ymin, xmax, ymax)

// 					2,													 //number of histos (currently four is the maximum)

// 					"singleEgRates_emu",								 //histoName1
// 					"singleEg_emu",									 //legNam1
// 					1,													 //histoStyle1 (1=nondotted, 7=dotted)
// 					2,													 //histoColour1



// 					"doubleEgRates_emu",                         		 //histo3
// 					"doubleEg_emu",
// 					1,
// 					4,


// 					"singleEgRates_hw",								 //histo2
// 					"singleEg_hw",
// 					7,
// 					2,
// 					"doubleEgRates_hw",                         		 //histo4
// 					"doubleEg_hw",
// 					7,
// 					4,

// 					true,                                                    //additionalTextOn
// 					additionalText.c_str(),  //the additional text
// 					false, 10, 1.5*pow(10,8)								 //autoPosition?, textStartXpos, textStartYpos
// 					);


// 	//ett htt Rates
// 	individual_plot(dirName.c_str(),								     //dirName
// 					"ett_htt_Rates",    								 //outputFileName
// 					"L1 Sum E_{T} Threshold (GeV)",						 //xaxisName
// 					"Rate (Hz)",										 //yaxisName
// 					false,0,0,											 //setOwnRange,xStartPoint,yStartPoint

// 					true,												 //logOn
// 					true, 0.60, 0.60, 0.85, 0.85,						 //legendOn: legend coords (xmin, ymin, xmax, ymax)

// 					2,													 //number of histos (currently four is the maximum)

// 					"etSumRates_emu",								 //histoName1
// 					"ETT_emu",									 //legNam1
// 					1,													 //histoStyle1 (1=nondotted, 7=dotted)
// 					2,													 //histoColour1



// 					"htSumRates_emu",                         		 //histo3
// 					"HTT_emu",
// 					1,
// 					4,

// 					"etSumRates_hw",								 //histo2
// 					"ETT_hw",
// 					7,
// 					2,
// 					"htSumRates_hw",                         		 //histo4
// 					"HTT_hw",
// 					7,
// 					4,

// 					true,                                                    //additionalTextOn
// 					additionalText.c_str(),  //the additional text
// 					false, 10, 1.5*pow(10,8)								 //autoPosition?, textStartXpos, textStartYpos
// 					);



// 	//met mht Rates
// 	individual_plot(dirName.c_str(),								     //dirName
// 					"met_mht_Rates",    								 //outputFileName
// 					"L1 Sum E_{T} Threshold (GeV)",						 //xaxisName
// 					"Rate (Hz)",										 //yaxisName
// 					false,0,0,											 //setOwnRange,xStartPoint,yStartPoint

// 					true,												 //logOn
// 					true, 0.60, 0.60, 0.85, 0.85,						 //legendOn: legend coords (xmin, ymin, xmax, ymax)

// 					2,													 //number of histos (currently four is the maximum)

// 					"metSumRates_emu",								 //histoName1
// 					"MET_emu",									 //legNam1
// 					1,													 //histoStyle1 (1=nondotted, 7=dotted)
// 					2,													 //histoColour1



// 					"mhtSumRates_emu",                         		 //histo3
// 					"MHT_emu",
// 					1,
// 					4,


// 					"metSumRates_hw",								 //histo2
// 					"MET_hw",
// 					7,
// 					2,
// 					"mhtSumRates_hw",                         		 //histo4
// 					"MHT_hw",
// 					7,
// 					4,

// 					true,                                                    //additionalTextOn
// 					additionalText.c_str(),  //the additional text
// 					false, 10, 1.5*pow(10,8)								 //autoPosition?, textStartXpos, textStartYpos
// 					);



// 	//TAU Rates
// 	individual_plot(dirName.c_str(),								     //dirName
// 					"tau_Rates",    								 //outputFileName
// 					"L1 Tau E_{T} Threshold (GeV)",						 //xaxisName
// 					"Rate (Hz)",										 //yaxisName
// 					true,0,150,											 //setOwnRange,xStartPoint,yStartPoint

// 					true,												 //logOn
// 					true, 0.60, 0.60, 0.85, 0.85,						 //legendOn: legend coords (xmin, ymin, xmax, ymax)

// 					1,													 //number of histos (currently four is the maximum)

// 					"tauRates_emu",								 //histoName1
// 					"singleTau_emu",									 //legNam1
// 					1,													 //histoStyle1 (1=nondotted, 7=dotted)
// 					2,													 //histoColour1

// 					"tauRates_hw",								 //histo2
// 					"singleTau_hw",
// 					7,
// 					2,

// 					"",                         		 //histo3
// 					"",
// 					0,
// 					0,

// 					"",                         		 //histo4
// 					"",
// 					0,
// 					0,

// 					true,                                                    //additionalTextOn
// 					additionalText.c_str(),  //the additional text
// 					false, 10, 1.5*pow(10,8)								 //autoPosition?, textStartXpos, textStartYpos
// 					);



// //Distributions

// 	//singleDoubleJetsDists
// 	individual_plot(dirName.c_str(),								     //dirName
// 					"singleDoubleJetDist",								 //outputFileName
// 					"L1 Jet E_{T} (GeV)",						 //xaxisName
// 					"",										 //yaxisName
// 					false,0,0,											 //setOwnRange,xStartPoint,yStartPoint

// 					true,												 //logOn
// 					true, 0.60, 0.60, 0.85, 0.85,						 //legendOn: legend coords (xmin, ymin, xmax, ymax)

// 					2,													 //number of histos (currently four is the maximum)

// 					"leadingJetDist_emu",								 //histoName1
// 					"leadingJet_emu",									 //legNam1
// 					1,													 //histoStyle1 (1=nondotted, 7=dotted)
// 					2,													 //histoColour1



// 					"secondJetDist_emu",                         		 //histo3
// 					"secondJet_emu",
// 					1,
// 					4,

// 					"leadingJetDist_hw",								 //histo2
// 					"leadingJet_hw",
// 					7,
// 					2,
// 					"secondJetDist_hw",                         		 //histo4
// 					"secondJet_hw",
// 					7,
// 					4,

// 					true,                                                    //additionalTextOn
// 					additionalText.c_str(),  //the additional text
// 					true, 10, 200										 //autoPosition?, textStartXpos, textStartYpos
// 					);


// 	//singleDoubleEGsDist
// 	individual_plot(dirName.c_str(),								     //dirName
// 					"singleDoubleEGDist",								 //outputFileName
// 					"L1 EG E_{T} (GeV)",						 //xaxisName
// 					"",										 //yaxisName
// 					true,0,200,											 //setOwnRange,xStartPoint,yStartPoint

// 					true,												 //logOn
// 					true, 0.60, 0.60, 0.85, 0.85,						 //legendOn: legend coords (xmin, ymin, xmax, ymax)

// 					2,													 //number of histos (currently four is the maximum)

// 					"leadingEgDist_emu",								 //histoName1
// 					"leadingEg_emu",									 //legNam1
// 					1,													 //histoStyle1 (1=nondotted, 7=dotted)
// 					2,													 //histoColour1



// 					"secondEgDist_emu",                         		 //histo3
// 					"secondEg_emu",
// 					1,
// 					4,

// 					"leadingEgDist_hw",								 //histo2
// 					"leadingEg_hw",
// 					7,
// 					2,
// 					"secondEgDist_hw",                         		 //histo4
// 					"secondEg_hw",
// 					7,
// 					4,

// 					true,                                                    //additionalTextOn
// 					additionalText.c_str(),  //the additional text
// 					true, 10, 200										 //autoPosition?, textStartXpos, textStartYpos
// 					);


// 	//ett htt Dist
// 	individual_plot(dirName.c_str(),								     //dirName
// 					"ett_htt_Dist",    								 //outputFileName
// 					"L1 Sum E_{T} (GeV)",						 //xaxisName
// 					"",										 //yaxisName
// 					false,0,0,											 //setOwnRange,xStartPoint,yStartPoint

// 					true,												 //logOn
// 					true, 0.60, 0.60, 0.85, 0.85,						 //legendOn: legend coords (xmin, ymin, xmax, ymax)

// 					2,													 //number of histos (currently four is the maximum)

// 					"etSumDist_emu",								 //histoName1
// 					"ETT_emu",									 //legNam1
// 					1,													 //histoStyle1 (1=nondotted, 7=dotted)
// 					2,													 //histoColour1



// 					"htSumDist_emu",                         		 //histo3
// 					"HTT_emu",
// 					1,
// 					4,

// 					"etSumDist_hw",								 //histo2
// 					"ETT_hw",
// 					7,
// 					2,
// 					"htSumDist_hw",                         		 //histo4
// 					"HTT_hw",
// 					7,
// 					4,

// 					true,                                                    //additionalTextOn
// 					additionalText.c_str(),  //the additional text
// 					true, 10, 200										 //autoPosition?, textStartXpos, textStartYpos
// 					);



// 	//met mht Dist
// 	individual_plot(dirName.c_str(),								     //dirName
// 					"met_mht_Dist",    								 //outputFileName
// 					"L1 Sum E_{T} (GeV)",						 //xaxisName
// 					"",										 //yaxisName
// 					false,0,0,											 //setOwnRange,xStartPoint,yStartPoint

// 					true,												 //logOn
// 					true, 0.60, 0.60, 0.85, 0.85,						 //legendOn: legend coords (xmin, ymin, xmax, ymax)

// 					2,													 //number of histos (currently four is the maximum)

// 					"metSumDist_emu",								 //histoName1
// 					"MET_emu",									 //legNam1
// 					1,													 //histoStyle1 (1=nondotted, 7=dotted)
// 					2,													 //histoColour1



// 					"mhtSumDist_emu",                         		 //histo3
// 					"MHT_emu",
// 					1,
// 					4,

// 					"metSumDist_hw",								 //histo2
// 					"MET_hw",
// 					7,
// 					2,
// 					"mhtSumDist_hw",                         		 //histo4
// 					"MHT_hw",
// 					7,
// 					4,

// 					true,                                                    //additionalTextOn
// 					additionalText.c_str(),  //the additional text
// 					true, 10, 200									 //autoPosition?, textStartXpos, textStartYpos
// 					);



// 	//TAU Dist
// 	individual_plot(dirName.c_str(),								     //dirName
// 					"tau_Dist",    								 //outputFileName
// 					"L1 Tau E_{T} (GeV)",						 //xaxisName
// 					"",										 //yaxisName
// 					true,0,150,											 //setOwnRange,xStartPoint,yStartPoint

// 					true,												 //logOn
// 					true, 0.60, 0.60, 0.85, 0.85,						 //legendOn: legend coords (xmin, ymin, xmax, ymax)

// 					1,													 //number of histos (currently four is the maximum)

// 					"leadingTauDist_emu",								 //histoName1
// 					"leadingTau_emu",									 //legNam1
// 					1,													 //histoStyle1 (1=nondotted, 7=dotted)
// 					2,													 //histoColour1

// 					"",								 //histo2
// 					"",
// 					0,
// 					0,

// 					"",                         		 //histo3
// 					"",
// 					0,
// 					0,

// 					"",                         		 //histo4
// 					"",
// 					0,
// 					0,

// 					true,                                                //additionalTextOn
// 					additionalText.c_str(), 							 //the additional text
// 					true, 10, 200										 //autoPosition?, textStartXpos, textStartYpos
// 					);


}









void individual_plot(string dirName,
					 string outputFileName,

					 string xaxisName,
					 string yaxisName,

					 bool setOwnRange,
					 double xStartPoint,
					 double xFinishPoint,

					 bool logOn,

					 bool legendOn,
					 double legXmin,
					 double legYmin,
 					 double legXmax,
					 double legYmax,

					 int numberOfHistos,

					 string histoName1,
					 string legName1,
					 int histoStyle1,
					 int histoColour1,

					 string histoName2,
					 string legName2,
					 int histoStyle2,
					 int histoColour2,

					 string histoName3,
					 string legName3,
					 int histoStyle3,
					 int histoColour3,

					 string histoName4,
					 string legName4,
					 int histoStyle4,
					 int histoColour4,

					 string histoName5,
					 string legName5,
					 int histoStyle5,
					 int histoColour5,

					 string histoName6,
					 string legName6,
					 int histoStyle6,
					 int histoColour6,

					 bool additionalTextOn,
					 string additionalText,
					 bool autoPosition,
					 double textStartXPos,
					 double textStartYPos){

	string inputFileName = dirName + "histos.root";
	TFile * f = new TFile( inputFileName.c_str() );
	if (f==0){
		cout << "Cannot load file " << inputFileName << endl;
		return;
	}

	TCanvas * c = new TCanvas("c","",650,600);
	gStyle->SetOptStat(0);
	if (logOn) gPad->SetLogy();	

    TH1F * h1 = (TH1F*)f->Get( histoName1.c_str() );
    TH1F * h2 = (TH1F*)f->Get( histoName2.c_str() );
    TH1F * h3 = (TH1F*)f->Get( histoName3.c_str() );
    TH1F * h4 = (TH1F*)f->Get( histoName4.c_str() );
    TH1F * h5 = (TH1F*)f->Get( histoName5.c_str() );
    TH1F * h6 = (TH1F*)f->Get( histoName6.c_str() );

 	TLegend * leg = new TLegend(legXmin, legYmin, legXmax, legYmax);
  	leg->SetLineColor(0);
    
    if (setOwnRange) h1->GetXaxis()->SetRangeUser(xStartPoint,xFinishPoint);

    if (numberOfHistos==1){
	  	h1->SetLineColor(histoColour1);
	    h1->SetLineWidth(2);
	    h1->SetLineStyle(histoStyle1);
        h1->GetXaxis()->SetTitleOffset(1.2);
        h1->GetYaxis()->SetTitleOffset(1.2);
	    h1->GetXaxis()->SetTitle(xaxisName.c_str());
	    h1->GetYaxis()->SetTitle(yaxisName.c_str());
	    h1->Draw("same");
	    if (legendOn){
	    	leg->AddEntry(h1, legName1.c_str(), "L");
	    	leg->Draw();
	    }
	}

    if (numberOfHistos==2){
	  	h1->SetLineColor(histoColour1);
	    h1->SetLineWidth(2);
	    h1->SetLineStyle(histoStyle1);
        h1->GetXaxis()->SetTitleOffset(1.2);
        h1->GetYaxis()->SetTitleOffset(1.2);
	    h1->GetXaxis()->SetTitle(xaxisName.c_str());
	    h1->GetYaxis()->SetTitle(yaxisName.c_str());
	    h1->Draw("same");
      	h2->SetLineColor(histoColour2);
	    h2->SetLineWidth(2);
	    h2->SetLineStyle(histoStyle2);
	    h2->Draw("same");
	    if (legendOn){
		    leg->AddEntry(h1, legName1.c_str(), "L");
	      	leg->AddEntry(h2, legName2.c_str(), "L");  	
		    leg->Draw();
		}
	}

    if (numberOfHistos==3){
	  	h1->SetLineColor(histoColour1);
	    h1->SetLineWidth(2);
	    h1->SetLineStyle(histoStyle1);
        h1->GetXaxis()->SetTitleOffset(1.2);
        h1->GetYaxis()->SetTitleOffset(1.2);
	    h1->GetXaxis()->SetTitle(xaxisName.c_str());
	    h1->GetYaxis()->SetTitle(yaxisName.c_str());
	    h1->Draw("same");
      	h2->SetLineColor(histoColour2);
	    h2->SetLineWidth(2);
	    h2->SetLineStyle(histoStyle2);
	    h2->Draw("same");
      	h3->SetLineColor(histoColour3);
	    h3->SetLineWidth(2);
	    h3->SetLineStyle(histoStyle3);
	    h3->Draw("same");
	    if (legendOn){
		    leg->AddEntry(h1, legName1.c_str(), "L");
	      	leg->AddEntry(h2, legName2.c_str(), "L");
	      	leg->AddEntry(h3, legName3.c_str(), "L");
		    leg->Draw();
		}
	}

    if (numberOfHistos==4){
	  	h1->SetLineColor(histoColour1);
	    h1->SetLineWidth(2);
	    h1->SetLineStyle(histoStyle1);
        h1->GetXaxis()->SetTitleOffset(1.2);
        h1->GetYaxis()->SetTitleOffset(1.2);
	    h1->GetXaxis()->SetTitle(xaxisName.c_str());
	    h1->GetYaxis()->SetTitle(yaxisName.c_str());
	    h1->Draw("same");
      	h2->SetLineColor(histoColour2);
	    h2->SetLineWidth(2);
	    h2->SetLineStyle(histoStyle2);
	    h2->Draw("same");
      	h3->SetLineColor(histoColour3);
	    h3->SetLineWidth(2);
	    h3->SetLineStyle(histoStyle3);
	    h3->Draw("same");
      	h4->SetLineColor(histoColour4);
	    h4->SetLineWidth(2);
	    h4->SetLineStyle(histoStyle4);
	    h4->Draw("same");
	    if (legendOn){
		    leg->AddEntry(h1, legName1.c_str(), "L");
	      	leg->AddEntry(h2, legName2.c_str(), "L");
	      	leg->AddEntry(h3, legName3.c_str(), "L");
	      	leg->AddEntry(h4, legName4.c_str(), "L");
		    leg->Draw();
		}
	}

	    if (numberOfHistos==6){
	  	h1->SetLineColor(histoColour1);
	    h1->SetLineWidth(2);
	    h1->SetLineStyle(histoStyle1);
        h1->GetXaxis()->SetTitleOffset(1.2);
        h1->GetYaxis()->SetTitleOffset(1.2);
	    h1->GetXaxis()->SetTitle(xaxisName.c_str());
	    h1->GetYaxis()->SetTitle(yaxisName.c_str());
	    h1->Draw("same");
      	h2->SetLineColor(histoColour2);
	    h2->SetLineWidth(3);
	    h2->SetLineStyle(histoStyle2);
	    h2->Draw("same");
      	h3->SetLineColor(histoColour3);
	    h3->SetLineWidth(2);
	    h3->SetLineStyle(histoStyle3);
	    h3->Draw("same");
      	h4->SetLineColor(histoColour4);
	    h4->SetLineWidth(3);
	    h4->SetLineStyle(histoStyle4);
	    h4->Draw("same");
	    h5->SetLineColor(histoColour5);
	    h5->SetLineWidth(2);
	    h5->SetLineStyle(histoStyle5);
	    h5->Draw("same");
      	h6->SetLineColor(histoColour6);
	    h6->SetLineWidth(3);
	    h6->SetLineStyle(histoStyle6);
	    h6->Draw("same");
	    if (legendOn){
		    leg->AddEntry(h1, legName1.c_str(), "L");
	      	leg->AddEntry(h2, legName2.c_str(), "L");
	      	leg->AddEntry(h3, legName3.c_str(), "L");
	      	leg->AddEntry(h4, legName4.c_str(), "L");
	 		leg->AddEntry(h5, legName5.c_str(), "L");
	      	leg->AddEntry(h6, legName6.c_str(), "L");
		    leg->Draw();
		}
	}




	if (autoPosition){
    	textStartXPos = h1->GetXaxis()->GetBinCenter(1);
    	if (logOn) textStartYPos = 3*(h1->GetMaximum());
    	else textStartYPos = 1.1*(h1->GetMaximum());

	}

 	TLatex *texl = new TLatex(textStartXPos,textStartYPos,additionalText.c_str());
  	texl->SetTextSize(0.035);
  	if (additionalTextOn) texl->Draw("same"); 

	string saveName = dirName + outputFileName +".pdf";
	//c->SaveAs( saveName.c_str() );
	//c->Close();

     return;
}
