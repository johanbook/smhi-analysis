

#include <iostream>
#include <fstream>
#include <TF1.h> // 1d function class
#include <TH1.h> // 1d histogram classes
#include <TStyle.h>  // style object
#include <TMath.h>   // math functions
#include <TCanvas.h> // canvas object
void analyze_v2_2particle(){
	
	Int_t nEvents = 0;
	string helpString;
	
	//method 1
	Double_t diff1 = 0;	
	
	//method 2
	Double_t diff2 = 0;	
	
	  // create histogram that we will fill with the given values
  TH1D* hPhi = new TH1D("hPhi", "ROOT func found in data file; x; Counts", 
			100, 0, 2*TMath::Pi());
			
	ifstream file("phi_dist.dat");
	Int_t eventNo = -1;
	
	while(file >> helpString >> eventNo){
		
		//cout << "Reading event : " << eventNo << endl;
		nEvents++;
		
		Int_t nTracks = -1;
		file >> helpString >> nTracks;
		//cout << "Event contains " << nTracks << " tracks" << endl;
		
		Double_t phi[nTracks];
		Int_t trackNo;
		
		
		for(Int_t nt = 0; nt < nTracks; nt++){
			
			file >> helpString >> helpString >> phi[nt];
			
			// fill our dist histogram
			hPhi->Fill(phi[nt]);
		}
		
				// -------------------------- 2-particle stuff    ------------------------
	
		//method 1
		Double_t sum_cos2_diff = 0;
			
		//method 2
		Double_t sum_cos2 = 0;	
		Double_t sum_sin2 = 0;	

	
		for(Int_t i = 0; i < nTracks; i++){	
			
		sum_cos2 += TMath::Cos(2*phi[i]);	
		sum_sin2 += TMath::Sin(2*phi[i]);	
			
			for(Int_t j = i+1; j < nTracks; j++){
				
				sum_cos2_diff += 2*TMath::Cos(2*(phi[i]-phi[j]));			
			}	
		}
		
		//method 1
		diff1 += sum_cos2_diff / (nTracks * (nTracks-1) );
		
		//method 2
		diff2 += (sum_cos2*sum_cos2 + sum_sin2*sum_sin2 - nTracks)/(nTracks*(nTracks-1));
		
	}

		diff1 = TMath::Sqrt(diff1 / nEvents);
		diff2 = TMath::Sqrt(diff2 / nEvents);
			
	cout << "Method 1: v2 (average of " << nEvents << " events) = "<< diff1 << endl;
	cout << "Method 2: v2 (average of " << nEvents << " events) = "<< diff2 << endl;
	
	
	// -----------------  Creating the histogram  ---------------------------------------
	
	
	  // Set ROOT drawing styles
  gStyle->SetOptStat(1111);
  gStyle->SetOptFit(1111);

  // create canvas for hSin
  TCanvas* c1 = new TCanvas("c1", "sin canvas", 900, 600);
  hPhi->SetMinimum(0);
  hPhi->Draw();
  
  // create 1d function that we will use to fit our generated data to ensure
  // that the generation works
  TF1* fitFunc = new TF1("fitFunc", "[0]*(1+2*[1]*cos(2*x))", 0, 2*TMath::Pi());
  fitFunc->SetParameter(0, 1);
  fitFunc->SetParameter(1, diff1);
  fitFunc->SetLineColor(kRed);
  hPhi->Fit(fitFunc);
  
  // Save the canvas as a picture
  c1->SaveAs("Histogram_Analyzer.png");
	
}
