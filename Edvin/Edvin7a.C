/* 
   In this ROOT function we generate a distribution according to sin(x)
   between 0 and pi

   To run do:
   root 
   .L rootgenerate_sinx.C+ 
   rootfuncgenerate(10000)
*/

// include C++ STL headers 
#include <iostream>
#include <fstream>


using namespace std;

// ROOT library obejcts
#include <TF1.h> // 1d function class
#include <TH1.h> // 1d histogram classes
#include <TStyle.h>  // style object
#include <TMath.h>   // math functions
#include <TCanvas.h> // canvas object

//________________________________________________________________________
void rootfuncgenerate(Int_t nEvents, Double_t v2, Int_t nTracks) {

Int_t j = nEvents;
Int_t k = nTracks; 

Double_t phi[j][k];

  cout << "Generating " << nEvents << " events" << endl << endl;

  // create histogram that we will fill with random values
  TH1D* hPhi = new TH1D("hPhi", "ROOT func generated 1+v2*cos(2x) distribution; x; Counts", 
			100, 0, 2*TMath::Pi());

  // Define the function we want to generate
  TF1* fv2 = new TF1("fv2", "1+2*[0]*cos(2*x)", 0, 2*TMath::Pi());
  fv2->SetParameter(0,v2);
  
  // make a loop for the number of events
  for(Int_t n = 0; n < nEvents; ++n) {
    
    if((n+1)%1000==0)
      cout << "event " << n+1 << endl;
    
    for(Int_t i = 0; i<nTracks; ++i) {  
		 
		 //adds random values to the array
		phi[n][i]=(fv2->GetRandom()); 
		
		// fill our dist histogram
		hPhi->Fill(phi[n][i]);
		}

	}
  
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
  fitFunc->SetParameter(1, v2);
  fitFunc->SetLineColor(kRed);
  hPhi->Fit(fitFunc);
  
  // Save the canvas as a picture
  c1->SaveAs("Histogram_Generator.png");
  
  

ofstream file("phi_dist.dat");

  for(Int_t n = 0; n < nEvents; ++n) {
    
    file << "Event " << n << endl << "nTracks " << nTracks << endl;
    
    for(Int_t i = 0; i<nTracks; ++i) {  
		 
		 //adds the value to the file
		file << i << "  :  " << phi[n][i] << endl;	
		}
	}

file.close();  
  
}
