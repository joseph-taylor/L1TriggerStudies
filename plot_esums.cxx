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

void plot_L1vRECO(string rootFileName, string histoName, int dimNum, string logOnOff);
void plot_turnOn(string rootFileName, string histoType);

void plot_all_loop(string rootFileName){

plot_L1vRECO(rootFileName, "hMETphi_l1", 1, "linear");
plot_L1vRECO(rootFileName, "hMHTphi_l1", 1, "linear");
plot_L1vRECO(rootFileName, "hMHTphi_l1", 1, "log");
plot_L1vRECO(rootFileName, "hETT_l1", 1, "linear");
plot_L1vRECO(rootFileName, "hMET_l1", 1, "linear");
plot_L1vRECO(rootFileName, "hHTT_l1", 1, "linear");
plot_L1vRECO(rootFileName, "hHTT_l1", 1, "log");
plot_L1vRECO(rootFileName, "hMHT_l1", 1, "linear");
plot_L1vRECO(rootFileName, "hMHT_l1", 1, "log");
plot_L1vRECO(rootFileName, "hMETphi_reco", 1, "linear");
plot_L1vRECO(rootFileName, "hMHTphi_reco", 1, "linear");
plot_L1vRECO(rootFileName, "hMHTphi_reco", 1, "log");
plot_L1vRECO(rootFileName, "hETT_reco", 1, "linear");
plot_L1vRECO(rootFileName, "hMET_reco", 1, "linear");
plot_L1vRECO(rootFileName, "hHTT_reco", 1, "linear");
plot_L1vRECO(rootFileName, "hHTT_reco", 1, "log");
plot_L1vRECO(rootFileName, "hMHT_reco", 1, "linear");
plot_L1vRECO(rootFileName, "hMHT_reco", 1, "log");

plot_L1vRECO(rootFileName, "hdET_ETT", 1, "linear");
plot_L1vRECO(rootFileName, "hdET_MET", 1, "linear");
plot_L1vRECO(rootFileName, "hdET_HTT", 1, "linear");
plot_L1vRECO(rootFileName, "hdET_HTT", 1, "log");
plot_L1vRECO(rootFileName, "hdET_MHT", 1, "linear");
plot_L1vRECO(rootFileName, "hdET_MHT", 1, "log");
//plot_L1vRECO(rootFileName, "hdPhi_MET", 1, "linear");
//plot_L1vRECO(rootFileName, "hdPhi_MHT", 1, "linear");
plot_L1vRECO(rootFileName, "hETS_ETT", 2, "linear");
plot_L1vRECO(rootFileName, "hETS_MET", 2, "linear");
plot_L1vRECO(rootFileName, "hETS_HTT", 2, "linear");
plot_L1vRECO(rootFileName, "hETS_MHT", 2, "linear");
plot_L1vRECO(rootFileName, "hETS_ETT", 2, "log");
plot_L1vRECO(rootFileName, "hETS_MET", 2, "log");
plot_L1vRECO(rootFileName, "hETS_HTT", 2, "log");
plot_L1vRECO(rootFileName, "hETS_MHT", 2, "log");
plot_L1vRECO(rootFileName, "h_myl1_HTT_l1", 1, "linear");


plot_turnOn(rootFileName, "ETT");
plot_turnOn(rootFileName, "MET");
plot_turnOn(rootFileName, "HTT");
plot_turnOn(rootFileName, "MHT");
return;  
}










//nb: the string names provided must be inbetween quotation marks eg "hETS_ETT"
void plot_L1vRECO(string rootFileName, string histoName, int dimNum, string logOnOff){

//select the root file containing the plot
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
        return;
        }
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
  int nbins = h->GetNbinsX();
  double x = h->GetBinLowEdge(nbins/2);
  double y = h->GetMaximum();
  TLatex *texl = new TLatex(x,1.08*y,"CMS Preliminary, #sqrt{s}=13 TeV");
  texl->SetTextSize(0.035);
  texl->Draw("same");
  string saveName = histoName + "_" + logOnOff + ".pdf";
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
  string saveName = histoName + "_" + logOnOff + ".pdf";
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



void plot_turnOn(string rootFileName, string histoType){
if(histoType!="ETT" && histoType!="MET" && histoType!="HTT" && histoType!="MHT"){
  cout << "You have not provided a valid histoType" << endl;
    cout << "The correct format is:" << endl;
    cout << "rootFileName, histoType (ETT, MET, HTT or MHT)" << endl;
    return;
}
TFile * f = new TFile( rootFileName.c_str() );

if(histoType=="ETT"){
TH1F * hT100 = (TH1F*)f->Get("hEff_ETT_100");
TH1F * hT125 = (TH1F*)f->Get("hEff_ETT_125");
TH1F * hT150 = (TH1F*)f->Get("hEff_ETT_150");
TH1F * hT175 = (TH1F*)f->Get("hEff_ETT_175");
TH1F * hT200 = (TH1F*)f->Get("hEff_ETT_200");
TH1F * hnum100 = (TH1F*)f->Get("hnum_ETT_100");
TH1F * hnum125 = (TH1F*)f->Get("hnum_ETT_125");
TH1F * hnum150 = (TH1F*)f->Get("hnum_ETT_150");
TH1F * hnum175 = (TH1F*)f->Get("hnum_ETT_175");
TH1F * hnum200 = (TH1F*)f->Get("hnum_ETT_200");
TH1F * hdenALL = (TH1F*)f->Get("hden_ETT");
//-------------------------------------------------------------------------------
//The 100, 125, 150, 175, 200 setup----------------------------------------------
//-------------------------------------------------------------------------------
//hT100_central->SetTitle("");
hT100->GetXaxis()->SetTitle("reco ETT (GeV)");
hT100->GetYaxis()->SetTitle("efficiency");

TEfficiency * hT100e = new TEfficiency(*hnum100,*hdenALL);
TEfficiency * hT125e = new TEfficiency(*hnum125,*hdenALL);
TEfficiency * hT150e = new TEfficiency(*hnum150,*hdenALL);
TEfficiency * hT175e = new TEfficiency(*hnum175,*hdenALL);
TEfficiency * hT200e = new TEfficiency(*hnum200,*hdenALL);

hT100->SetLineColor(1);     //black
hT125->SetLineColor(2);     //red
hT150->SetLineColor(4);     //blue
hT175->SetLineColor(8);
hT200->SetLineColor(6);

hT100->SetLineWidth(2);
hT125->SetLineWidth(2);
hT150->SetLineWidth(2);
hT175->SetLineWidth(2);
hT200->SetLineWidth(2);

hT100e->SetLineColor(1);    //black
hT125e->SetLineColor(2);    //red
hT150e->SetLineColor(4);    //blue
hT175e->SetLineColor(8);    //darkgreen
hT200e->SetLineColor(6);    //pink

hT100e->SetLineWidth(2);
hT125e->SetLineWidth(2);
hT150e->SetLineWidth(2);
hT175e->SetLineWidth(2);
hT200e->SetLineWidth(2);

hT100e->SetMarkerColor(1);    //black
hT125e->SetMarkerColor(2);    //red
hT150e->SetMarkerColor(4);    //blue
hT175e->SetMarkerColor(8);
hT200e->SetMarkerColor(6);

hT100e->SetMarkerStyle(20);
hT125e->SetMarkerStyle(20);
hT150e->SetMarkerStyle(20);
hT175e->SetMarkerStyle(20);
hT200e->SetMarkerStyle(20);

hT100e->SetMarkerSize(1);
hT125e->SetMarkerSize(1);
hT150e->SetMarkerSize(1);
hT175e->SetMarkerSize(1);
hT200e->SetMarkerSize(1);

TCanvas* c=new TCanvas("c","c",650,600);
c->SetLeftMargin(0.15);
c->SetGrid();

//hT100->GetXaxis()->SetRangeUser(0,1000);
hT100->GetYaxis()->SetRangeUser(0,1);
hT100->GetYaxis()->SetTitleOffset(1.5);
hT100->GetXaxis()->SetTitleOffset(1.0);

hT100->Draw("C, same");
hT125->Draw("C, same");
hT150->Draw("C, same");
hT175->Draw("C, same");
hT200->Draw("C, same");

hT100e->Draw("same");
hT125e->Draw("same");
hT150e->Draw("same");
hT175e->Draw("same");
hT200e->Draw("same");

gStyle->SetOptStat(0);
TLegend * leg = new TLegend(0.7, 0.15, 0.9, 0.48); //(xmin, ymin, xmax, ymax)
leg->SetLineColor(0);
leg->AddEntry(hT100, "L1>100GeV", "L");
leg->AddEntry(hT125, "L1>125GeV", "L");
leg->AddEntry(hT150, "L1>150GeV", "L");
leg->AddEntry(hT175, "L1>175GeV", "L");
leg->AddEntry(hT200, "L1>200GeV", "L");
leg->Draw();

 TLatex *texl = new TLatex(0.1,1.05,"CMS Preliminary, #sqrt{s}=13 TeV");
 texl->SetTextSize(0.035);
 texl->Draw("same");

 string saveName = "turnOn_ETT.pdf";
 c->SaveAs( saveName.c_str() );
c->Close();
//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------
}//close 'if' ETT




if(histoType=="HTT"){
TH1F * hT100 = (TH1F*)f->Get("hEff_HTT_100");
TH1F * hT125 = (TH1F*)f->Get("hEff_HTT_125");
TH1F * hT150 = (TH1F*)f->Get("hEff_HTT_150");
TH1F * hT175 = (TH1F*)f->Get("hEff_HTT_175");
TH1F * hT200 = (TH1F*)f->Get("hEff_HTT_200");
TH1F * hnum100 = (TH1F*)f->Get("hnum_HTT_100");
TH1F * hnum125 = (TH1F*)f->Get("hnum_HTT_125");
TH1F * hnum150 = (TH1F*)f->Get("hnum_HTT_150");
TH1F * hnum175 = (TH1F*)f->Get("hnum_HTT_175");
TH1F * hnum200 = (TH1F*)f->Get("hnum_HTT_200");
TH1F * hdenALL = (TH1F*)f->Get("hden_HTT");
//-------------------------------------------------------------------------------
//The 100, 125, 150, 175, 200 setup----------------------------------------------
//-------------------------------------------------------------------------------
//hT100_central->SetTitle("");
hT100->GetXaxis()->SetTitle("reco HTT (GeV)");
hT100->GetYaxis()->SetTitle("efficiency");

TEfficiency * hT100e = new TEfficiency(*hnum100,*hdenALL);
TEfficiency * hT125e = new TEfficiency(*hnum125,*hdenALL);
TEfficiency * hT150e = new TEfficiency(*hnum150,*hdenALL);
TEfficiency * hT175e = new TEfficiency(*hnum175,*hdenALL);
TEfficiency * hT200e = new TEfficiency(*hnum200,*hdenALL);

hT100->SetLineColor(1);     //black
hT125->SetLineColor(2);     //red
hT150->SetLineColor(4);     //blue
hT175->SetLineColor(8);
hT200->SetLineColor(6);

hT100->SetLineWidth(2);
hT125->SetLineWidth(2);
hT150->SetLineWidth(2);
hT175->SetLineWidth(2);
hT200->SetLineWidth(2);

hT100e->SetLineColor(1);    //black
hT125e->SetLineColor(2);    //red
hT150e->SetLineColor(4);    //blue
hT175e->SetLineColor(8);    //darkgreen
hT200e->SetLineColor(6);    //pink

hT100e->SetLineWidth(2);
hT125e->SetLineWidth(2);
hT150e->SetLineWidth(2);
hT175e->SetLineWidth(2);
hT200e->SetLineWidth(2);

hT100e->SetMarkerColor(1);    //black
hT125e->SetMarkerColor(2);    //red
hT150e->SetMarkerColor(4);    //blue
hT175e->SetMarkerColor(8);
hT200e->SetMarkerColor(6);

hT100e->SetMarkerStyle(20);
hT125e->SetMarkerStyle(20);
hT150e->SetMarkerStyle(20);
hT175e->SetMarkerStyle(20);
hT200e->SetMarkerStyle(20);

hT100e->SetMarkerSize(1);
hT125e->SetMarkerSize(1);
hT150e->SetMarkerSize(1);
hT175e->SetMarkerSize(1);
hT200e->SetMarkerSize(1);

TCanvas* c=new TCanvas("c","c",650,600);
c->SetLeftMargin(0.15);
c->SetGrid();

//hT100->GetXaxis()->SetRangeUser(0,1000);
hT100->GetYaxis()->SetRangeUser(0,1);
hT100->GetYaxis()->SetTitleOffset(1.5);
hT100->GetXaxis()->SetTitleOffset(1.0);

hT100->Draw("C, same");
hT125->Draw("C, same");
hT150->Draw("C, same");
hT175->Draw("C, same");
hT200->Draw("C, same");

hT100e->Draw("same");
hT125e->Draw("same");
hT150e->Draw("same");
hT175e->Draw("same");
hT200e->Draw("same");

gStyle->SetOptStat(0);
TLegend * leg = new TLegend(0.7, 0.15, 0.9, 0.48); //(xmin, ymin, xmax, ymax)
leg->SetLineColor(0);
leg->AddEntry(hT100, "L1>100GeV", "L");
leg->AddEntry(hT125, "L1>125GeV", "L");
leg->AddEntry(hT150, "L1>150GeV", "L");
leg->AddEntry(hT175, "L1>175GeV", "L");
leg->AddEntry(hT200, "L1>200GeV", "L");
leg->Draw();

 TLatex *texl = new TLatex(0.1,1.05,"CMS Preliminary, #sqrt{s}=13 TeV");
 texl->SetTextSize(0.035);
 texl->Draw("same"); 

 string saveName = "turnOn_HTT.pdf";
 c->SaveAs( saveName.c_str() );
 c->Close();
//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------
}//close 'if' HTT



if(histoType=="MHT"){
TH1F * hT40 = (TH1F*)f->Get("hEff_MHT_40");
TH1F * hT60 = (TH1F*)f->Get("hEff_MHT_60");
TH1F * hT80 = (TH1F*)f->Get("hEff_MHT_80");
TH1F * hT100 = (TH1F*)f->Get("hEff_MHT_100");
TH1F * hnum40 = (TH1F*)f->Get("hnum_MHT_40");
TH1F * hnum60 = (TH1F*)f->Get("hnum_MHT_60");
TH1F * hnum80 = (TH1F*)f->Get("hnum_MHT_80");
TH1F * hnum100 = (TH1F*)f->Get("hnum_MHT_100");
TH1F * hdenALL = (TH1F*)f->Get("hden_MHT");
//-------------------------------------------------------------------------------
//The 40, 60, 80, 100 setup------------------------------------------------------
//-------------------------------------------------------------------------------
//hT40_central->SetTitle("");
hT40->GetXaxis()->SetTitle("reco MHT (GeV)");
hT40->GetYaxis()->SetTitle("efficiency");

TEfficiency * hT40e = new TEfficiency(*hnum40,*hdenALL);
TEfficiency * hT60e = new TEfficiency(*hnum60,*hdenALL);
TEfficiency * hT80e = new TEfficiency(*hnum80,*hdenALL);
TEfficiency * hT100e = new TEfficiency(*hnum100,*hdenALL);

hT40->SetLineColor(1);     //black
hT60->SetLineColor(2);     //red
hT80->SetLineColor(4);     //blue
hT100->SetLineColor(8);

hT40->SetLineWidth(2);
hT60->SetLineWidth(2);
hT80->SetLineWidth(2);
hT100->SetLineWidth(2);

hT40e->SetLineColor(1);    //black
hT60e->SetLineColor(2);    //red
hT80e->SetLineColor(4);    //blue
hT100e->SetLineColor(8);   //darkgreen

hT40e->SetLineWidth(2);
hT60e->SetLineWidth(2);
hT80e->SetLineWidth(2);
hT100e->SetLineWidth(2);

hT40e->SetMarkerColor(1);    //black
hT60e->SetMarkerColor(2);    //red
hT80e->SetMarkerColor(4);    //blue
hT100e->SetMarkerColor(8);

hT40e->SetMarkerStyle(20);
hT60e->SetMarkerStyle(20);
hT80e->SetMarkerStyle(20);
hT100e->SetMarkerStyle(20);

hT40e->SetMarkerSize(1);
hT60e->SetMarkerSize(1);
hT80e->SetMarkerSize(1);
hT100e->SetMarkerSize(1);

TCanvas* c=new TCanvas("c","c",650,600);
c->SetLeftMargin(0.15);
c->SetGrid();

//hT40->GetXaxis()->SetRangeUser(0,400);
hT40->GetYaxis()->SetRangeUser(0,1);
hT40->GetYaxis()->SetTitleOffset(1.5);
hT40->GetXaxis()->SetTitleOffset(1.0);

hT40->Draw("C, same");
hT60->Draw("C, same");
hT80->Draw("C, same");
hT100->Draw("C, same");
//hT200->Draw("C, same");

hT40e->Draw("same");
hT60e->Draw("same");
hT80e->Draw("same");
hT100e->Draw("same");
//hT200e->Draw("same");

gStyle->SetOptStat(0);
TLegend * leg = new TLegend(0.7, 0.15, 0.9, 0.48); //(xmin, ymin, xmax, ymax)
leg->SetLineColor(0);
leg->AddEntry(hT40, "L1>40GeV", "L");
leg->AddEntry(hT60, "L1>60GeV", "L");
leg->AddEntry(hT80, "L1>80GeV", "L");
leg->AddEntry(hT100, "L1>100GeV", "L");
//leg->AddEntry(hT200, "L1>200GeV", "L");
leg->Draw();

 TLatex *texl = new TLatex(0.1,1.05,"CMS Preliminary, #sqrt{s}=13 TeV");
 texl->SetTextSize(0.035);
 texl->Draw("same");

 string saveName = "turnOn_MHT.pdf";
 c->SaveAs( saveName.c_str() );
 c->Close();
//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------
}//close 'if' MHT



if(histoType=="MET"){
TH1F * hT40 = (TH1F*)f->Get("hEff_MET_40");
TH1F * hT60 = (TH1F*)f->Get("hEff_MET_60");
TH1F * hT80 = (TH1F*)f->Get("hEff_MET_80");
TH1F * hT100 = (TH1F*)f->Get("hEff_MET_100");
TH1F * hnum40 = (TH1F*)f->Get("hnum_MET_40");
TH1F * hnum60 = (TH1F*)f->Get("hnum_MET_60");
TH1F * hnum80 = (TH1F*)f->Get("hnum_MET_80");
TH1F * hnum100 = (TH1F*)f->Get("hnum_MET_100");
TH1F * hdenALL = (TH1F*)f->Get("hden_MET");
//-------------------------------------------------------------------------------
//The 40, 60, 80, 100 setup------------------------------------------------------
//-------------------------------------------------------------------------------
//hT40_central->SetTitle("");
hT40->GetXaxis()->SetTitle("reco MET (GeV)");
hT40->GetYaxis()->SetTitle("efficiency");

TEfficiency * hT40e = new TEfficiency(*hnum40,*hdenALL);
TEfficiency * hT60e = new TEfficiency(*hnum60,*hdenALL);
TEfficiency * hT80e = new TEfficiency(*hnum80,*hdenALL);
TEfficiency * hT100e = new TEfficiency(*hnum100,*hdenALL);

hT40->SetLineColor(1);     //black
hT60->SetLineColor(2);     //red
hT80->SetLineColor(4);     //blue
hT100->SetLineColor(8);

hT40->SetLineWidth(2);
hT60->SetLineWidth(2);
hT80->SetLineWidth(2);
hT100->SetLineWidth(2);

hT40e->SetLineColor(1);    //black
hT60e->SetLineColor(2);    //red
hT80e->SetLineColor(4);    //blue
hT100e->SetLineColor(8);   //darkgreen

hT40e->SetLineWidth(2);
hT60e->SetLineWidth(2);
hT80e->SetLineWidth(2);
hT100e->SetLineWidth(2);

hT40e->SetMarkerColor(1);    //black
hT60e->SetMarkerColor(2);    //red
hT80e->SetMarkerColor(4);    //blue
hT100e->SetMarkerColor(8);

hT40e->SetMarkerStyle(20);
hT60e->SetMarkerStyle(20);
hT80e->SetMarkerStyle(20);
hT100e->SetMarkerStyle(20);

hT40e->SetMarkerSize(1);
hT60e->SetMarkerSize(1);
hT80e->SetMarkerSize(1);
hT100e->SetMarkerSize(1);

TCanvas* c=new TCanvas("c","c",650,600);
c->SetLeftMargin(0.15);
c->SetGrid();

//hT40->GetXaxis()->SetRangeUser(0,400);
hT40->GetYaxis()->SetRangeUser(0,1);
hT40->GetYaxis()->SetTitleOffset(1.5);
hT40->GetXaxis()->SetTitleOffset(1.0);

hT40->Draw("C, same");
hT60->Draw("C, same");
hT80->Draw("C, same");
hT100->Draw("C, same");
//hT200->Draw("C, same");

hT40e->Draw("same");
hT60e->Draw("same");
hT80e->Draw("same");
hT100e->Draw("same");
//hT200e->Draw("same");

gStyle->SetOptStat(0);
TLegend * leg = new TLegend(0.7, 0.15, 0.9, 0.48); //(xmin, ymin, xmax, ymax)
leg->SetLineColor(0);
leg->AddEntry(hT40, "L1>40GeV", "L");
leg->AddEntry(hT60, "L1>60GeV", "L");
leg->AddEntry(hT80, "L1>80GeV", "L");
leg->AddEntry(hT100, "L1>100GeV", "L");
//leg->AddEntry(hT200, "L1>200GeV", "L");
leg->Draw();

 TLatex *texl = new TLatex(0.1,1.05,"CMS Preliminary, #sqrt{s}=13 TeV");
 texl->SetTextSize(0.035);
 texl->Draw("same");

 string saveName = "turnOn_MET.pdf";
 c->SaveAs( saveName.c_str() );
 c->Close();
//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------
}//close 'if' MET

}//closes the 'plot_turnOn' function
