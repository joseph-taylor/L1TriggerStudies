#include "TFile.h"
#include "TH1F.h"
#include "TF1.h"
#include "TH2F.h"
#include "TLegend.h"
#include "TStyle.h"
#include "TEfficiency.h"
#include <string>
#include <TLatex.h>
#include <TCanvas.h>
#include <iostream>

void plot_L1vRECO(string dirName, string histoName, int dimNum, string logOnOff);
void plot_turnOn(string dirName, string histoType);

void plot_jets(){

  //should only have to change this...
  string dirName = "output_jets/run269224_zeroBias_v34p0_HW/";

  // plot_L1vRECO(dirName.c_str(), "hdPhi_central", 1, "linear");
  // plot_L1vRECO(dirName.c_str(), "hdEta_central", 1, "linear");
  // plot_L1vRECO(dirName.c_str(), "hdR_central", 1, "linear");
  // plot_L1vRECO(dirName.c_str(), "hdET_central", 1, "linear");
  // plot_L1vRECO(dirName.c_str(), "hETS_central", 2, "linear");
  // plot_L1vRECO(dirName.c_str(), "hETS_central", 2, "log");

  // plot_L1vRECO(dirName.c_str(), "hdPhi_central_WAC", 1, "linear");
  // plot_L1vRECO(dirName.c_str(), "hdEta_central_WAC", 1, "linear");
  // plot_L1vRECO(dirName.c_str(), "hdR_central_WAC", 1, "linear");
  // plot_L1vRECO(dirName.c_str(), "hdET_central_WAC", 1, "linear");
  // plot_L1vRECO(dirName.c_str(), "hETS_central_WAC", 2, "linear");
  // plot_L1vRECO(dirName.c_str(), "hETS_central_WAC", 2, "log");

  // plot_L1vRECO(dirName.c_str(), "hdPhi_hf", 1, "linear");
  // plot_L1vRECO(dirName.c_str(), "hdEta_hf", 1, "linear");
  // plot_L1vRECO(dirName.c_str(), "hdR_hf", 1, "linear");
  // plot_L1vRECO(dirName.c_str(), "hdET_hf", 1, "linear");
  // plot_L1vRECO(dirName.c_str(), "hETS_hf", 2, "linear");
  // plot_L1vRECO(dirName.c_str(), "hETS_hf", 2, "log");

  // plot_L1vRECO(dirName.c_str(), "hdPhi_hf_WAC", 1, "linear");
  // plot_L1vRECO(dirName.c_str(), "hdEta_hf_WAC", 1, "linear");
  // plot_L1vRECO(dirName.c_str(), "hdR_hf_WAC", 1, "linear");
  // plot_L1vRECO(dirName.c_str(), "hdET_hf_WAC", 1, "linear");
  // plot_L1vRECO(dirName.c_str(), "hETS_hf_WAC", 2, "linear");
  // plot_L1vRECO(dirName.c_str(), "hETS_hf_WAC", 2, "log");

  plot_turnOn(dirName.c_str(), "central");
  // plot_turnOn(dirName.c_str(), "central_WAC");
  // plot_turnOn(dirName.c_str(), "hf");
  // plot_turnOn(dirName.c_str(), "hf_WAC");

  return;  
}





//nb: the string names provided must be inbetween quotation marks eg "hETS_ETT"
void plot_L1vRECO(string dirName, string histoName, int dimNum, string logOnOff){

  //select the root file containing the plot
  string rootFileName = dirName + "histos.root";
  TFile * f = new TFile( rootFileName.c_str() );
  if (f==0){
    cout << "You have not provided a valid fileName" << endl;
    cout << "The correct format is:" << endl;
    cout << "rootFileName, histogramName, histogramDimension (1or2), log Or linear (typed exactly)" << endl;
    return;}
  if (logOnOff!="log" && logOnOff!="linear"){
    cout << "You have not provided a valid log/linear setting" << endl;
    cout << "The correct format is:" << endl;
    cout << "rootFileName, histogramName, histogramDimension (1or2), log Or linear (typed exactly)" << endl;
    return;}

  //1d plots
  if (dimNum == 1){
    TH1F * h = (TH1F*)f->Get( histoName.c_str() );
    if (h==0){
      cout << "You have not provided a valid histoName" << endl;
      cout << "The correct format is:" << endl;
      cout << "rootFileName, histogramName, histogramDimension (1or2),  log Or linear (typed exactly)" << endl;
      return;}
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
    string saveName = dirName + histoName + "_" + logOnOff + ".pdf";
    c->SaveAs( saveName.c_str() );
    c->Close();
  }


  //2d plots
  if (dimNum == 2){
    TH2F * h = (TH2F*)f->Get( histoName.c_str() );
    if (h==0){
      cout << "You have not provided a valid histoName" << endl;
      cout << "The correct format is:" << endl;
      cout << "rootFileName, histogramName, histogramDimension (1or2)" << endl;
      return;}
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
      h->Draw("same, cols");
      gStyle->SetOptStat(0);

      int nbinsX = h->GetNbinsX();
      int nbinsY = h->GetNbinsY();
      double x = h->GetXaxis()->GetBinCenter(nbinsX/2);
      double y = h->GetYaxis()->GetBinUpEdge(nbinsY);  
      TLatex *texl = new TLatex(x,1.05*y,"CMS Preliminary, #sqrt{s}=13 TeV");  
      texl->SetTextSize(0.035);
      texl->Draw("same");
      string saveName = dirName + histoName + "_" + logOnOff + ".pdf";
      c->SaveAs( saveName.c_str() );
      c->Close();
  }
  //incorrect dimNum entry
  if (dimNum != 1 && dimNum !=2){
    cout << "You have not put in a plot dimension of 1 or 2" << endl;
    cout << "The correct format is:" << endl;
    cout << "rootFileName, histogramName, histogramDimension (1or2),  log Or linear (typed exactly)" << endl;
    return;
  }
}//closes the 'plot_L1vsRECO' function










void plot_turnOn(string dirName, string histoType){
  if(histoType!="central" && histoType!="central_WAC" && histoType!="hf" && histoType!="hf_WAC"){
    cout << "You have not provided a valid histoType" << endl;
    cout << "The correct format is:" << endl;
    cout << "rootFileName, histoType (central, central_WAC, hf, hf_WAC)" << endl;
    return;
  }
  string rootFileName = dirName + "histos.root";
  TFile * f = new TFile( rootFileName.c_str() );
  //put in string before hand
  string name_01 = "hT36_" + histoType;
  string name_02 = "hT52_" + histoType;
  string name_03 = "hT68_" + histoType;
  string name_04 = "hT92_" + histoType;
  string name_05 = "hT128_" + histoType;
  string name_06 = "hT176_" + histoType;
  string name_07 = "hT200_" + histoType;
  string name_08 = "hnum36_" + histoType;
  string name_09 = "hnum52_" + histoType;
  string name_10 = "hnum68_" + histoType;
  string name_11 = "hnum92_" + histoType;
  string name_12 = "hnum128_" + histoType;
  string name_13 = "hnum176_" + histoType;
  string name_14 = "hnum200_" + histoType;
  string name_15 = "hden_" + histoType;

  TH1F * hT36 = (TH1F*)f->Get( name_01.c_str() );
  TH1F * hT52 = (TH1F*)f->Get( name_02.c_str() );
  TH1F * hT68 = (TH1F*)f->Get( name_03.c_str() );
  TH1F * hT92 = (TH1F*)f->Get( name_04.c_str() );
  TH1F * hT128 = (TH1F*)f->Get( name_05.c_str() );
  TH1F * hT176 = (TH1F*)f->Get( name_06.c_str() );
  TH1F * hT200 = (TH1F*)f->Get( name_07.c_str() );

  TH1F * hnum36 = (TH1F*)f->Get( name_08.c_str() );
  TH1F * hnum52 = (TH1F*)f->Get( name_09.c_str() );
  TH1F * hnum68 = (TH1F*)f->Get( name_10.c_str() );
  TH1F * hnum92 = (TH1F*)f->Get( name_11.c_str() );
  TH1F * hnum128 = (TH1F*)f->Get( name_12.c_str() );
  TH1F * hnum176 = (TH1F*)f->Get( name_13.c_str() );
  TH1F * hnum200 = (TH1F*)f->Get( name_14.c_str() );
  TH1F * hdenALL = (TH1F*)f->Get( name_15.c_str() );
  //--------------------------------------------------------
  //hT36_central->SetTitle("");
  hT36->GetXaxis()->SetTitle("PF Jet E_{T} (GeV)");
  hT36->GetYaxis()->SetTitle("efficiency");

  TEfficiency * hT36e = new TEfficiency(*hnum36,*hdenALL);
  TEfficiency * hT52e = new TEfficiency(*hnum52,*hdenALL);
  TEfficiency * hT68e = new TEfficiency(*hnum68,*hdenALL);
  TEfficiency * hT92e = new TEfficiency(*hnum92,*hdenALL);
  TEfficiency * hT128e = new TEfficiency(*hnum128,*hdenALL);
  TEfficiency * hT176e = new TEfficiency(*hnum176,*hdenALL);
  TEfficiency * hT200e = new TEfficiency(*hnum200,*hdenALL);

// // trial fitting...
TF1* f1 = new TF1("f1","[0]*TMath::Erf((x-[1])/[2])",0,150);
f1->SetParameters(0.9, 25., 10.);
f1->SetLineColor(1);
hT36->Fit(f1);

// // //trial fitting...
// TF1* f2 = new TF1("f2","[0]*TMath::Erf((x-[1])/[2])",0,400);
// f2->SetParameters(0.95, 35., 30.);
// f1->SetLineColor(2);
// hT52e->Fit(f2);

// //trial fitting...
// TF1* f3 = new TF1("f3","[0]*TMath::Erf((x-[1])/[2])",0,400);
// f3->SetParameters(1, 50., 10.);
// f3->SetLineColor(4);
// hT68e->Fit(f3);

// //trial fitting...
// TF1* f4 = new TF1("f4","[0]*TMath::Erf((x-[1])/[2])",0,400);
// f4->SetParameters(1, 50., 10.);
// f4->SetLineColor(8);
// hT92e->Fit(f4);


  hT36->SetLineColor(1);     //black
  hT52->SetLineColor(2);     //red
  hT68->SetLineColor(4);     //blue
  hT92->SetLineColor(8);
  hT128->SetLineColor(6);
  hT176->SetLineColor(9);
  hT200->SetLineColor(3);

  hT36->SetLineWidth(2);
  hT52->SetLineWidth(2);
  hT68->SetLineWidth(2);
  hT92->SetLineWidth(2);
  hT128->SetLineWidth(2);
  hT176->SetLineWidth(2);
  hT200->SetLineWidth(2);

  hT36e->SetLineColor(1);    //black
  hT52e->SetLineColor(2);    //red
  hT68e->SetLineColor(4);    //blue
  hT92e->SetLineColor(8);    //darkgreen
  hT128e->SetLineColor(6);   //pink
  hT176e->SetLineColor(9);   //purple
  hT200e->SetLineColor(3);   //green

  hT36e->SetLineWidth(2);
  hT52e->SetLineWidth(2);
  hT68e->SetLineWidth(2);
  hT92e->SetLineWidth(2);
  hT128e->SetLineWidth(2);
  hT176e->SetLineWidth(2);
  hT200e->SetLineWidth(2);

  hT36e->SetMarkerColor(1);    //black
  hT52e->SetMarkerColor(2);    //red
  hT68e->SetMarkerColor(4);    //blue
  hT92e->SetMarkerColor(8);
  hT128e->SetMarkerColor(6);
  hT176e->SetMarkerColor(9);
  hT200e->SetMarkerColor(3);

  hT36e->SetMarkerStyle(20);
  hT52e->SetMarkerStyle(20);
  hT68e->SetMarkerStyle(20);
  hT92e->SetMarkerStyle(20);
  hT128e->SetMarkerStyle(20);
  hT176e->SetMarkerStyle(20);
  hT200e->SetMarkerStyle(20);

  hT36e->SetMarkerSize(1);
  hT52e->SetMarkerSize(1);
  hT68e->SetMarkerSize(1);
  hT92e->SetMarkerSize(1);
  hT128e->SetMarkerSize(1);
  hT176e->SetMarkerSize(1);
  hT200e->SetMarkerSize(1);
   
  TCanvas* c=new TCanvas("c","c",650,600); //650,600
  c->SetLeftMargin(0.15);
  c->SetGrid();


//usually do this with the histogram object...
  // hT36->GetXaxis()->SetRangeUser(0,150); //usually 400
  // hT36->GetYaxis()->SetRangeUser(0,1);
  // hT36->GetYaxis()->SetTitleOffset(1.5);
  // hT36->GetXaxis()->SetTitleOffset(1.0);

  hT36->Draw("AP, same");
  // hT52->Draw("P, same");
  // hT68->Draw("P, same");
  // hT92->Draw("P, same");
  // hT128->Draw("C, same");
  // hT176->Draw("C, same");
  //hT200->Draw("C, same");

  // hT36e->Draw("AP");
  // hT52e->Draw("same");
  // hT68e->Draw("same");
  // hT92e->Draw("same");
  // hT128e->Draw("same");
  // hT176e->Draw("same");
  //hT200e->Draw("same");

  gStyle->SetOptStat(0);
  // TLegend * leg = new TLegend(0.7, 0.15, 0.9, 0.48); //(xmin, ymin, xmax, ymax)
  // leg->SetLineColor(0);
  //   leg->AddEntry(hT36e, "L1>36GeV", "L");
  // leg->AddEntry(hT52e, "L1>52GeV", "L");
  // leg->AddEntry(hT68e, "L1>68GeV", "L");
  // leg->AddEntry(hT92e, "L1>92GeV", "L");
  // leg->AddEntry(hT36, "L1>36GeV", "L");
  // leg->AddEntry(hT52, "L1>52GeV", "L");
  // leg->AddEntry(hT68, "L1>68GeV", "L");
  // leg->AddEntry(hT92, "L1>92GeV", "L");
  // leg->AddEntry(hT128, "L1>128GeV", "L");
  // leg->AddEntry(hT176, "L1>176GeV", "L");
  //leg->AddEntry(hT200, "L1>200GeV", "L");
  //leg->Draw();

 // TLatex *texl = new TLatex(0.1,1.05,"CMS Preliminary, #sqrt{s}=13 TeV, ZeroBias run269224");
 //  texl->SetTextSize(0.035);
 //  texl->Draw("same"); 

 string saveName = dirName + "turnOn_" + histoType + ".pdf";
 //c->SaveAs( saveName.c_str() );
  //c->Close();

}//closes the 'plot_turnOn' function
