/* 
   Name:Sara Gabrielli
   To run do:
   root 
   .L Shifted_HotColdHist.C+ 
	Sara_Analyze2()
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

void Sara_Analyze2();

		 //define the Gaussian function  			
double Gaussian(double* x, double* par);

void Sara_Analyze2(){
		Int_t yearNo,hotdayNo,colddayNo;
		Int_t eff_nyears=285;//effective number of the years that are considered for the hottest and the coldest temperature histogram
		Int_t Array_years[285],Array_hotdays[285],Array_colddays[285];
		

		//open file1 
		 ifstream file1("../data/year_hotday_coldday.dat");
		 
		 Int_t count=0;//counter for the while cycle
		 while(file1 >> yearNo >> hotdayNo >>colddayNo)
			 if(yearNo!=0){//this passage is needed since the array obtained with Sara_Producefiles.cpp had some elements equal to 0, corrisponding to data not coming from Uppsala.
				 Array_years[count]=yearNo;
				 Array_hotdays[count]=hotdayNo;
				 Array_colddays[count]=colddayNo;
				 if( Array_colddays[count]<100){ //shift the coldest days which occur at the beginning of the year to the right part of the histogram
				 Array_colddays[count]=Array_colddays[count]+366;}
				 //cout<< Array_years[count]<<" "<<Array_hotdays[count]<<" "<<Array_colddays[count]<<endl; //test
				 count++;
				 }
		 
		//close file1
		 file1.close();
		 
		//create histograms for the hottest days and the coldest days
		TH1D* hHot = new TH1D("hHot", "Distribution of the hottest days; Day ; Counts", 365, 100, 465);
		TH1D* hCold1 = new TH1D("hCold1", "Distribution of the coldest days; Day ; Counts", 365, 100, 465);
		//fill the histograms
			for(Int_t i = 0; i < 285; i++) {
			hHot->Fill(Array_hotdays[i]);
			hCold1->Fill(Array_colddays[i]);
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

		
		TF1* funcHot= new TF1("Gaussian", Gaussian, 100, 465, 3);
		funcHot->SetParameters(5, 200, 60); //Starting values for fitting
		funcHot->SetLineColor(kBlack);
		funcHot->SetLineWidth(1);
		
		hHot->Fit(funcHot, "QR");//Fitting the hottest days histogram
		cout << "The mean is " << funcHot->GetParameter(1) << endl;
		cout << "Its uncertainty is " << funcHot->GetParError(1) << endl;
		
		TF1* funcCold= new TF1("Gaussian", Gaussian, 100,465, 3);
		funcCold->SetParameters(5, 200, 60); //Starting values for fitting
	
		hCold1->Fit(funcCold, "QR");//Fitting the coldest days histogram
		cout << "The mean (cold) is " << funcCold->GetParameter(1) << endl;
		cout<< "And thus tha average coldest day is"<<funcCold->GetParameter(1) - 366 << endl; // It is already verified that the coldest day is more likely to happen at the beginning of the year
		cout << "Its uncertainty is " << funcCold->GetParError(1) << endl;

		
		TLegend *leg = new TLegend(0.65, 0.75, 0.92, 0.92, "", "NDC");
		leg->SetFillStyle(0); //Hollow fill (transparent)
		leg->SetBorderSize(0); //Get rid of the border
		leg->AddEntry(hHot, "", "F"); //Use object title, draw fill
		leg->AddEntry(hCold1, "", "F"); //Use custom title
		hHot->Draw();
		hCold1->Draw("SAME"); //Draw on top of the existing plot
		leg->Draw(); //Legends are automatically drawn with "SAME"
		
		  // Save the canvas as a picture
		  //hot->SaveAs("Distr_Hottestdays.jpg");
		  cold->SaveAs("Distr_Coldestdays.eps");

	}
	
	double Gaussian(double* x, double* par) { //A custom function
		return par[0]*exp(-0.5*(x[0]*x[0] - 2*x[0]*par[1] +
		par[1]*par[1])/(par[2]*par[2]));
		}

