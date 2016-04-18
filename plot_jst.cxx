#include "TFile.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TLegend.h"
#include "TStyle.h"
#include "TEfficiency.h"
#include <string>
#include <TLatex.h>
#include <TCanvas.h>
#include <iostream>
#include <sstream>


void plot_L1vRECO(int JST, string histoName, int histoDim, string logOnOff);
void plot_turnOn_jst(string PUrange, string PTthreshold, string calSection);

void doPlots(){

  // plot_L1vRECO(0, "hETS_central_PU_0_10", 2, "log");
  // plot_L1vRECO(0, "hETS_central_PU_15_25", 2, "log");
  // plot_L1vRECO(0, "hETS_central_PU_30_40", 2, "log");
  plot_L1vRECO(2, "hETS_central_PU_0_10", 2, "log");
  plot_L1vRECO(2, "hETS_central_PU_15_25", 2, "log");
  plot_L1vRECO(2, "hETS_central_PU_30_40", 2, "log");
  plot_L1vRECO(3, "hETS_central_PU_0_10", 2, "log");
  plot_L1vRECO(3, "hETS_central_PU_15_25", 2, "log");
  plot_L1vRECO(3, "hETS_central_PU_30_40", 2, "log");
  plot_L1vRECO(4, "hETS_central_PU_0_10", 2, "log");
  plot_L1vRECO(4, "hETS_central_PU_15_25", 2, "log");
  plot_L1vRECO(4, "hETS_central_PU_30_40", 2, "log");
  plot_L1vRECO(5, "hETS_central_PU_0_10", 2, "log");
  plot_L1vRECO(5, "hETS_central_PU_15_25", 2, "log");
  plot_L1vRECO(5, "hETS_central_PU_30_40", 2, "log");
  plot_L1vRECO(6, "hETS_central_PU_0_10", 2, "log");
  plot_L1vRECO(6, "hETS_central_PU_15_25", 2, "log");
  plot_L1vRECO(6, "hETS_central_PU_30_40", 2, "log");
  // plot_L1vRECO(8, "hETS_central_PU_0_10", 2, "log");
  // plot_L1vRECO(8, "hETS_central_PU_15_25", 2, "log");
  // plot_L1vRECO(8, "hETS_central_PU_30_40", 2, "log");
  // plot_L1vRECO(10, "hETS_central_PU_0_10", 2, "log");
  // plot_L1vRECO(10, "hETS_central_PU_15_25", 2, "log");
  // plot_L1vRECO(10, "hETS_central_PU_30_40", 2, "log");

  plot_turnOn_jst("0_10", "10", "central");
  plot_turnOn_jst("15_25", "10", "central");
  plot_turnOn_jst("30_40", "10", "central");
  plot_turnOn_jst("0_10", "15", "central");
  plot_turnOn_jst("15_25", "15", "central");
  plot_turnOn_jst("30_40", "15", "central");
  plot_turnOn_jst("0_10", "20", "central");
  plot_turnOn_jst("15_25", "20", "central");
  plot_turnOn_jst("30_40", "20", "central");
  plot_turnOn_jst("0_10", "25", "central");
  plot_turnOn_jst("15_25", "25", "central");
  plot_turnOn_jst("30_40", "25", "central");
  plot_turnOn_jst("0_10", "30", "central");
  plot_turnOn_jst("15_25", "30", "central");
  plot_turnOn_jst("30_40", "30", "central");

  // plot_L1vRECO(0, "hETS_hf_PU_0_10", 2, "log");
  // plot_L1vRECO(0, "hETS_hf_PU_15_25", 2, "log");
  // plot_L1vRECO(0, "hETS_hf_PU_30_40", 2, "log");
  plot_L1vRECO(2, "hETS_hf_PU_0_10", 2, "log");
  plot_L1vRECO(2, "hETS_hf_PU_15_25", 2, "log");
  plot_L1vRECO(2, "hETS_hf_PU_30_40", 2, "log");
  plot_L1vRECO(3, "hETS_hf_PU_0_10", 2, "log");
  plot_L1vRECO(3, "hETS_hf_PU_15_25", 2, "log");
  plot_L1vRECO(3, "hETS_hf_PU_30_40", 2, "log");
  plot_L1vRECO(4, "hETS_hf_PU_0_10", 2, "log");
  plot_L1vRECO(4, "hETS_hf_PU_15_25", 2, "log");
  plot_L1vRECO(4, "hETS_hf_PU_30_40", 2, "log");
  plot_L1vRECO(5, "hETS_hf_PU_0_10", 2, "log");
  plot_L1vRECO(5, "hETS_hf_PU_15_25", 2, "log");
  plot_L1vRECO(5, "hETS_hf_PU_30_40", 2, "log");
  plot_L1vRECO(6, "hETS_hf_PU_0_10", 2, "log");
  plot_L1vRECO(6, "hETS_hf_PU_15_25", 2, "log");
  plot_L1vRECO(6, "hETS_hf_PU_30_40", 2, "log");
  // plot_L1vRECO(8, "hETS_hf_PU_0_10", 2, "log");
  // plot_L1vRECO(8, "hETS_hf_PU_15_25", 2, "log");
  // plot_L1vRECO(8, "hETS_hf_PU_30_40", 2, "log");
  // plot_L1vRECO(10, "hETS_hf_PU_0_10", 2, "log");
  // plot_L1vRECO(10, "hETS_hf_PU_15_25", 2, "log");
  // plot_L1vRECO(10, "hETS_hf_PU_30_40", 2, "log");

  plot_turnOn_jst("0_10", "10", "hf");
  plot_turnOn_jst("15_25", "10", "hf");
  plot_turnOn_jst("30_40", "10", "hf");
  plot_turnOn_jst("0_10", "15", "hf");
  plot_turnOn_jst("15_25", "15", "hf");
  plot_turnOn_jst("30_40", "15", "hf");
  plot_turnOn_jst("0_10", "20", "hf");
  plot_turnOn_jst("15_25", "20", "hf");
  plot_turnOn_jst("30_40", "20", "hf");
  plot_turnOn_jst("0_10", "25", "hf");
  plot_turnOn_jst("15_25", "25", "hf");
  plot_turnOn_jst("30_40", "25", "hf");
  plot_turnOn_jst("0_10", "30", "hf");
  plot_turnOn_jst("15_25", "30", "hf");
  plot_turnOn_jst("30_40", "30", "hf");

  return;  
}










//nb: the string names provided must be inbetween quotation marks eg "hETS_ETT"
void plot_L1vRECO(int JST, string histoName, int dimNum, string logOnOff){

  string JSTstring;
  stringstream convert;
  convert << JST;
  JSTstring = convert.str();
  string rootFileName = "comparison_jetSeedThreshold_" + JSTstring + "GeV.root";
  string titleName = histoName + "_jst" + JSTstring + "_" + logOnOff;
  //string saveName = "pdf_output/" + titleName + ".pdf";
  string saveName = "output_jst/run259721_zeroBiasReReco_intv14p0Layer1_noL1JEC_jst5/" + titleName + ".pdf"; 
  //select the root file containing the plot
  TFile * f = new TFile( rootFileName.c_str() );
  if (f==0){
    cout << endl << "For input: " << titleName << endl;
    cout << "You have not provided a valid JST(filename)" << endl;
    cout << "The correct format is:" << endl;
    cout << "JST, histogramName, histogramDimension (1or2), log Or linear (typed exactly)" << endl;
    return;
  }
  if (logOnOff!="log" && logOnOff!="linear"){
    cout << endl << "For input: " << titleName << endl;
    cout << "You have not provided a valid log/linear setting" << endl;
    cout << "The correct format is:" << endl;
    cout << "JST, histogramName, histogramDimension (1or2), log Or linear (typed exactly)" << endl;
    return;
    }

  ////////////
  //1d plots//
  ////////////
  if (dimNum == 1){
    TH1F * h = (TH1F*)f->Get( histoName.c_str() );
    if (h==0){
      cout << endl << "For input: " << titleName << endl;
      cout << "You have not provided a valid histoName" << endl;
      cout << "The correct format is:" << endl;
      cout << "JST, histogramName, histogramDimension (1or2),  log Or linear (typed exactly)" << endl;
      return;
    }

  h->SetTitle(titleName.c_str());

  //h->GetXaxis()->SetTitle("");
  h->GetXaxis()->SetTitleOffset(1.0);
  //h->GetXaxis()->SetTitleSize(0.040);
  //h->GetXaxis()->SetRangeUser(0, 1000);

  //h->GetYaxis()->SetTitle("Num Entries");
  h->GetYaxis()->SetTitleOffset(2.0);
  //h->GetYaxis()->SetTitleSize(0.040);
  //h->GetYaxis()->SetRangeUser(0, 1000);

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  if(logOnOff=="log"){gPad->SetLogy();}

  h->SetLineWidth(2);
  h->SetLineColor(2);
  //h->SetMarkerStyle(21);
  //h->SetMarkerSize(0.7);
  //h->SetMarkerColor(2);
  h->Draw("same");
  gStyle->SetOptStat(0);
  // int nbins = h->GetNbinsX();
  // double x = h->GetBinLowEdge(nbins/2);
  // double y = h->GetMaximum();
  // TLatex *texl = new TLatex(x,1.08*y,"CMS Preliminary, #sqrt{s}=13 TeV");
  // texl->SetTextSize(0.035);
  // texl->Draw("same");
  c->SaveAs( saveName.c_str() );
  c->Close();
  }

  ////////////
  //2d plots//
  ////////////
  if (dimNum == 2){
    TH2F * h = (TH2F*)f->Get( histoName.c_str() );
    if (h==0){
      cout << endl << "For input: " << titleName << endl;
      cout << "You have not provided a valid histoName" << endl;
      cout << "The correct format is:" << endl;
      cout << "JST, histogramName, histogramDimension (1or2)" << endl;
      return;
    }
    h->SetTitle(titleName.c_str());

    //h->GetXaxis()->SetTitle("");
    h->GetXaxis()->SetTitleOffset(1.0);
    //h->GetXaxis()->SetTitleSize(0.040);
    //h->GetXaxis()->SetRangeUser(0, 1000);

    //h->GetYaxis()->SetTitle("Num Entries");
    h->GetYaxis()->SetTitleOffset(2.0);
    //h->GetYaxis()->SetTitleSize(0.040);
    //h->GetYaxis()->SetRangeUser(0, 1000);

    TCanvas* c=new TCanvas("c","c",650,600);
    c->SetLeftMargin(0.15);  
    if(logOnOff=="log"){gPad->SetLogz();} 
    h->Draw("same, cols, z");
    gStyle->SetOptStat(0);
    // int nbinsX = h->GetNbinsX();
    // int nbinsY = h->GetNbinsY();
    // double x = h->GetXaxis()->GetBinCenter(nbinsX/2);
    // double y = h->GetYaxis()->GetBinUpEdge(nbinsY);  
    // TLatex *texl = new TLatex(x,1.05*y,"CMS Preliminary, #sqrt{s}=13 TeV");  
    // texl->SetTextSize(0.035);
    // texl->Draw("same");
    c->SaveAs( saveName.c_str() );
    c->Close();
  }
  //incorrect dimNum entry
  if (dimNum != 1 && dimNum !=2){
    cout << endl << "For input: " << titleName << endl;
    cout << "You have not put in a plot dimension of 1 or 2" << endl;
    cout << "The correct format is:" << endl;
    cout << "JST, histogramName, histogramDimension (1or2),  log Or linear (typed exactly)" << endl;
    return;
  }
}//closes the 'plot_L1vsRECO' function










void plot_turnOn_jst(string PUrange, string PTthreshold, string calSection){

  //TFile * f0 = new TFile("comparison_jetSeedThreshold_0GeV.root");
  TFile * f2 = new TFile("comparison_jetSeedThreshold_2GeV.root");
  TFile * f3 = new TFile("comparison_jetSeedThreshold_3GeV.root");
  TFile * f4 = new TFile("comparison_jetSeedThreshold_4GeV.root");
  TFile * f5 = new TFile("comparison_jetSeedThreshold_5GeV.root");
  TFile * f6 = new TFile("comparison_jetSeedThreshold_6GeV.root");
  //TFile * f8 = new TFile("comparison_jetSeedThreshold_8GeV.root");
  //TFile * f10 = new TFile("comparison_jetSeedThreshold_10GeV.root");

  string hDenName = "hden_" + calSection + "_PU_" + PUrange;
  string hNumName = "hNum_pt" + PTthreshold + "_" + calSection + "_PU_" + PUrange;
  string hEffName = "hEff_pt" + PTthreshold + "_" + calSection + "_PU_" + PUrange;

  string titleName = "ptThreshold_" + PTthreshold + "GeV__PU_" + PUrange + "__" + calSection;
  //string saveName = "pdf_output/" + titleName + ".pdf";
  string saveName = "output_jst/run259721_zeroBiasReReco_intv14p0Layer1_noL1JEC_jst5/" + titleName + ".pdf";

  //TH1F * hEff0 = (TH1F*)f0->Get(hEffName.c_str());
  TH1F * hEff2 = (TH1F*)f2->Get(hEffName.c_str());
  TH1F * hEff3 = (TH1F*)f3->Get(hEffName.c_str());
  TH1F * hEff4 = (TH1F*)f4->Get(hEffName.c_str());
  TH1F * hEff5 = (TH1F*)f5->Get(hEffName.c_str());
  TH1F * hEff6 = (TH1F*)f6->Get(hEffName.c_str());
  //TH1F * hEff8 = (TH1F*)f8->Get(hEffName.c_str());
  //TH1F * hEff10 = (TH1F*)f10->Get(hEffName.c_str());

  //TH1F * hNum0 = (TH1F*)f0->Get(hNumName.c_str());
  TH1F * hNum2 = (TH1F*)f2->Get(hNumName.c_str());
  TH1F * hNum3 = (TH1F*)f3->Get(hNumName.c_str());
  TH1F * hNum4 = (TH1F*)f4->Get(hNumName.c_str());
  TH1F * hNum5 = (TH1F*)f5->Get(hNumName.c_str());
  TH1F * hNum6 = (TH1F*)f6->Get(hNumName.c_str());
  //TH1F * hNum8 = (TH1F*)f8->Get(hNumName.c_str());
  //TH1F * hNum10 = (TH1F*)f10->Get(hNumName.c_str());

  //TH1F * hden0 = (TH1F*)f0->Get(hDenName.c_str());
  TH1F * hden2 = (TH1F*)f2->Get(hDenName.c_str());
  TH1F * hden3 = (TH1F*)f3->Get(hDenName.c_str());
  TH1F * hden4 = (TH1F*)f4->Get(hDenName.c_str());  
  TH1F * hden5 = (TH1F*)f5->Get(hDenName.c_str());
  TH1F * hden6 = (TH1F*)f6->Get(hDenName.c_str());
  //TH1F * hden8 = (TH1F*)f8->Get(hDenName.c_str());
  //TH1F * hden10 = (TH1F*)f10->Get(hDenName.c_str());

  // if (hEff0==0 || hEff2==0 || hEff3==0 || hEff4==0 || hEff5==0 || hEff6==0 || hEff8==0 || hEff10==0 ||
  //     hNum0==0 || hNum2==0 || hNum3==0 || hNum4==0 || hNum5==0 || hNum6==0 || hNum8==0 || hNum10==0 ||
  //     hden0==0 || hden2==0 || hden3==0 || hden4==0 || hden5==0 || hden6==0 || hden8==0 || hden10==0){
  //   cout << endl << "Could not get all required histograms for the setup: " + titleName << endl;
  //   return;
  // }

  // //--------------------------------------------------------
    if (hEff2==0 || hEff3==0 || hEff4==0 || hEff5==0 || hEff6==0 ||
        hNum2==0 || hNum3==0 || hNum4==0 || hNum5==0 || hNum6==0 ||
        hden2==0 || hden3==0 || hden4==0 || hden5==0 || hden6==0){
    cout << endl << "Could not get all required histograms for the setup: " + titleName << endl;
    return;
  }
  //--------------------------------------------------------
  hEff2->SetTitle(titleName.c_str());
  hEff2->GetXaxis()->SetTitle("genJet E_{T} (GeV)");
  hEff2->GetYaxis()->SetTitle("efficiency");

  //TEfficiency * hEff0e = new TEfficiency(*hNum0,*hden0);
  TEfficiency * hEff2e = new TEfficiency(*hNum2,*hden2);
  TEfficiency * hEff3e = new TEfficiency(*hNum3,*hden3);
  TEfficiency * hEff4e = new TEfficiency(*hNum4,*hden4);
  TEfficiency * hEff5e = new TEfficiency(*hNum5,*hden5);
  TEfficiency * hEff6e = new TEfficiency(*hNum6,*hden6);
  //TEfficiency * hEff8e = new TEfficiency(*hNum8,*hden8);
  //TEfficiency * hEff10e = new TEfficiency(*hNum10,*hden10);

  //hEff0->SetLineColor(1);     //black
  hEff2->SetLineColor(1);     //black
  hEff3->SetLineColor(6);     //pink
  hEff4->SetLineColor(8);     //darkGreen
  hEff5->SetLineColor(4);     //blue
  hEff6->SetLineColor(2);     //red
  //hEff8->SetLineColor(3);     //green
  //hEff10->SetLineColor(7);    //turquiose

  //hEff0->SetLineWidth(2);
  hEff2->SetLineWidth(2);
  hEff3->SetLineWidth(2);
  hEff4->SetLineWidth(2);
  hEff5->SetLineWidth(2);
  hEff6->SetLineWidth(2);
  //hEff8->SetLineWidth(2);
  //hEff10->SetLineWidth(2);

  //hEff0e->SetLineColor(1);    
  hEff2e->SetLineColor(1);
  hEff3e->SetLineColor(6);
  hEff4e->SetLineColor(8);
  hEff5e->SetLineColor(4);
  hEff6e->SetLineColor(2);
  //hEff8e->SetLineColor(3);
  //hEff10e->SetLineColor(7);

  //hEff0e->SetLineWidth(2);
  hEff2e->SetLineWidth(2);
  hEff3e->SetLineWidth(2);
  hEff4e->SetLineWidth(2);
  hEff5e->SetLineWidth(2);
  hEff6e->SetLineWidth(2);
  //hEff8e->SetLineWidth(2);
  //hEff10e->SetLineWidth(2);

  //hEff0e->SetMarkerColor(1); 
  hEff2e->SetMarkerColor(1);
  hEff3e->SetMarkerColor(6);
  hEff4e->SetMarkerColor(8);
  hEff5e->SetMarkerColor(4);
  hEff6e->SetMarkerColor(2);
  //hEff8e->SetMarkerColor(3);
  //hEff10e->SetMarkerColor(7);

  //hEff0e->SetMarkerStyle(20);
  hEff2e->SetMarkerStyle(20);
  hEff3e->SetMarkerStyle(20);
  hEff4e->SetMarkerStyle(20);
  hEff5e->SetMarkerStyle(20);
  hEff6e->SetMarkerStyle(20);
  //hEff8e->SetMarkerStyle(20);
  //hEff10e->SetMarkerStyle(20);

  //hEff0e->SetMarkerSize(1);
  hEff2e->SetMarkerSize(1);
  hEff3e->SetMarkerSize(1);
  hEff4e->SetMarkerSize(1);
  hEff5e->SetMarkerSize(1);
  hEff6e->SetMarkerSize(1);
  //hEff8e->SetMarkerSize(1);
  //hEff10e->SetMarkerSize(1);
   
  TCanvas* c=new TCanvas("c","c",650,600); //650,600
  c->SetLeftMargin(0.15);
  c->SetGrid();

  hEff2->GetXaxis()->SetRangeUser(0,120);
  hEff2->GetYaxis()->SetRangeUser(0,1);
  hEff2->GetYaxis()->SetTitleOffset(1.5);
  hEff2->GetXaxis()->SetTitleOffset(1.0);

  hEff2->Draw("C, same");
  //hEff0->Draw("C, same");
  hEff3->Draw("C, same");
  hEff4->Draw("C, same");
  hEff5->Draw("C, same");
  hEff6->Draw("C, same");
  //hEff8->Draw("C, same");
  //hEff10->Draw("C, same");

  //hEff0e->Draw("same");
  hEff2e->Draw("same");
  hEff3e->Draw("same");
  hEff4e->Draw("same");
  hEff5e->Draw("same");
  hEff6e->Draw("same");
  //hEff8e->Draw("same");
  //hEff10e->Draw("same");

  gStyle->SetOptStat(0);
  TLegend * leg = new TLegend(0.7, 0.15, 0.9, 0.48); //(xmin, ymin, xmax, ymax)
  leg->SetLineColor(0);
  //leg->AddEntry(hEff0, "JST=0GeV", "L");
  leg->AddEntry(hEff2, "JST=2GeV", "L");
  leg->AddEntry(hEff3, "JST=3GeV", "L");
  leg->AddEntry(hEff4, "JST=4GeV", "L");
  leg->AddEntry(hEff5, "JST=5GeV", "L");
  leg->AddEntry(hEff6, "JST=6GeV", "L");
  //leg->AddEntry(hEff8, "JST=8GeV", "L");
  //leg->AddEntry(hEff10, "JST=10GeV", "L");
  leg->Draw();

  // TLatex *texl = new TLatex(0.1,1.05,"CMS Preliminary, #sqrt{s}=13 TeV");
  // texl->SetTextSize(0.035);
  // texl->Draw("same"); 

  c->SaveAs(saveName.c_str());
  c->Close();
}//closes the 'plot_turnOn' function
