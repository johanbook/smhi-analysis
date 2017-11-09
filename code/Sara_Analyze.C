/* 
   Name:Sara Gabrielli
   To run do:
   root 
   .L Sara_Analyze.C+ 
	Sara_Analyze()
*/
#include <iostream>
#include <fstream>
using namespace std;

// ROOT library obejcts
#include <TF1.h> // 1d function class
#include <TH1.h> // 1d histogram classes
#include <TStyle.h>  // style object
#include <TMath.h>   // math functions
#include <TCanvas.h> // canvas object
#include <TGraph.h>
#include <TGraph2D.h>
#include <TLegend.h>
#include <TRandom.h>

void Sara_Analyze();

		 //define the Gaussian function  			
double Gaussian(double* x, double* par);

void Sara_Analyze(){
		Int_t yearNo,hotdayNo,colddayNo;
		Int_t eff_nyears=285;//effective number of the years that are considered for the hottest and the coldest temperature histogram
		Int_t Array_years[285],Array_hotdays[285],Array_colddays[285];
		
		Int_t years,days;
		Double_t temps;
		Int_t eff_nlines=101481;
		Int_t Array_alltheyears[101481], Array_allthedays[101481];
		Double_t Array_allthetemps [101481];

		//open file1 
		 ifstream file1("../data/year_hotday_coldday.dat");
		 
		 Int_t count=0;//counter for the while cycle
		 while(file1 >> yearNo >> hotdayNo >>colddayNo)
			 if(yearNo!=0){//this passage is needed since the array obtained with Sara_Producefiles.cpp had some elements equal to 0, corrisponding to data not coming from Uppsala.
				 Array_years[count]=yearNo;
				 Array_hotdays[count]=hotdayNo;
				 Array_colddays[count]=colddayNo;
				 //cout<< Array_years[count]<<" "<<Array_hotdays[count]<<" "<<Array_colddays[count]<<endl; //test
				 count++;
				 }
		 
		//close file1
		 file1.close();
		
		//open file2
		 ifstream file2("../data/years_days_temps.dat");
		 Int_t count2=0;
		 while(file2>>years>>days>>temps)
			if(years!=0){
				Array_alltheyears[count2]=years;
				Array_allthedays[count2]=days;
				Array_allthetemps[count2]=temps;
				//cout<<Array_alltheyears[count2]<<" "<<Array_allthedays[count2]<<" "<<Array_allthetemps[count2]<<endl; //test
				count2++;
				}
		//close file2
		 file2.close();
		 
		//create histograms for the hottest days and the coldest days
		TH1D* hHot = new TH1D("hHot", "Distribution of the hottest days; Day ; Counts", 365, 1, 366);
		TH1D* hCold1 = new TH1D("hCold1", "Distribution of the coldest days; Day ; Counts", 365, 100, 366);
		TH1D* hCold2 = new TH1D("hCold2", "Distribution of the coldest days; Day ; Counts", 365, 1, 300);
		//fill the histograms
			for(Int_t i = 0; i < 285; i++) {
			hHot->Fill(Array_hotdays[i]);
			hCold1->Fill(Array_colddays[i]);
			hCold2->Fill(Array_colddays[i]);
			}
	
		  //Set ROOT drawing styles
		  gStyle->SetOptStat(0000);
		  gStyle->SetOptFit(1111);

		  //create canvas for hHot
		  //TCanvas* hot = new TCanvas("hot", "Hot canvas", 900, 600);
		  hHot->SetMinimum(0);
		  hHot->SetFillColor(kRed+1);
		  hHot->SetLineColor(kRed+1);

		  // create 2 canvas for hCold1 and hCold2
		  TCanvas* cold = new TCanvas("cold", "Cold canvas", 900, 600);
		  hCold1->SetMinimum(0);
		  hCold1->SetFillColor(kBlue-7);
		  hCold1->SetLineColor(kBlue-7);
		  hCold1->SetLineWidth(1);
		  //hCold->Draw();
		  
		  TCanvas* cold2 = new TCanvas("cold2", "Cold2 canvas", 900, 600);
		  hCold2->SetMinimum(0);
		  hCold2->SetFillColor(kBlue-7);
		  hCold2->SetLineColor(kBlue-7);
		  hCold2->SetLineWidth(1);
		   
		
		TF1* funcHot= new TF1("Gaussian", Gaussian, 1, 366, 3);
		funcHot->SetParameters(5, 200, 60); //Starting values for fitting
		funcHot->SetLineColor(kBlack);
		funcHot->SetLineWidth(1);
		
		hHot->Fit(funcHot, "QR");//Fitting the hottest days histogram
		cout << "The mean is " << funcHot->GetParameter(1) << endl;
		cout << "Its uncertainty is " << funcHot->GetParError(1) << endl;
		
		TF1* funcCold= new TF1("Gaussian", Gaussian, 300, 50, 3);
		funcCold->SetParameters(5, 200, 60); //Starting values for fitting
	
		
		
		//hCold->Fit(funcCold, "QR");//Fitting the coldest days histogram
		hCold1->Fit("gaus","","",100,366);
		hCold2->Fit("gaus","","",1,300);
		
		TLegend *leg = new TLegend(0.65, 0.75, 0.92, 0.92, "", "NDC");
		leg->SetFillStyle(0); //Hollow fill (transparent)
		leg->SetBorderSize(0); //Get rid of the border
		leg->AddEntry(hHot, "", "F"); //Use object title, draw fill
		leg->AddEntry(hCold1, "", "F"); //Use custom title
		hHot->Draw();
		hCold1->Draw("SAME"); //Draw on top of the existing plot
		hCold2->Draw("SAME"); 
		leg->Draw(); //Legends are automatically drawn with "SAME"
		
		  // Save the canvas as a picture
		  //hot->SaveAs("Distr_Hottestdays.jpg");
		  cold2->SaveAs("Distr_Coldestdays.eps");
		  
	//2nd part:How hottest and coldest days changed over the years
	
	   TCanvas *graph1DHot = new TCanvas("graph1DHot","1D Graph year-day_Hot",200,10,700,500);
		TGraph* grHot = new TGraph(285,Array_years,Array_hotdays);
		grHot->Draw();
		grHot->SetLineColor(kRed+1);
		grHot->GetYaxis()->SetTitle("Day");
		grHot->GetXaxis()->SetTitle("Year");
		
		TCanvas *graph1D = new TCanvas("graph1D","1D Graph year-day",200,10,700,500);
		TGraph* grCold = new TGraph(285,Array_years,Array_colddays);
		grCold->Draw();
		grCold->SetLineColor(kBlue-7);
		grCold->GetYaxis()->SetTitle("Day");
		grCold->GetXaxis()->SetTitle("Year");
		
		graph1DHot->SaveAs("graph1DHot.eps");
		
		graph1D->SaveAs("graph1D.eps");
		
	//3d part: 2D graph
		
	TCanvas *c = new TCanvas("c","Graph2D example",0,0,600,400);
   Double_t x, y, z, P = 6.;
   Int_t np = 101481;
   TGraph2D *dt = new TGraph2D();
   //TRandom *r = new TRandom();
   for (Int_t N=0; N<np; N++) {
      x = Array_alltheyears[N];
      y = Array_allthedays[N];
      z = Array_allthetemps[N];
      dt->SetPoint(N,x,y,z);
   }
   dt->GetXaxis()->SetTitle("Year");
   dt->GetYaxis()->SetTitle("Day");
   dt->GetZaxis()->SetTitle("T(°C)");
   gStyle->SetPalette(1);
   dt->Draw("colz");
   c->SaveAs("2Dgraph.eps");
   c->SaveAs("2DCanvas.root");

	}
	
	double Gaussian(double* x, double* par) { //A custom function
		return par[0]*exp(-0.5*(x[0]*x[0] - 2*x[0]*par[1] +
		par[1]*par[1])/(par[2]*par[2]));
		}

